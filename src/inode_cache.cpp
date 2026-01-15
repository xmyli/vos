#include "../include/inode_cache.hpp"
#include "../include/panic.hpp"

namespace file {

inode_cache_t::inode_cache_t(file::block_cache_t *block_cache) : block_cache(block_cache) {}

auto inode_cache_t::acquire_cached_inode(inode_index_t inode_index) -> inode_cache_index_t {
    lock.acquire();
    size_t index = SIZE_MAX;
    for (size_t i = 0; i < inode_cache_constants::cache_size; i++) {
        auto &inode = inodes[i];
        if (inode.inode_index == inode_index) {
            index = i;
            break;
        }
    }
    if (index == SIZE_MAX) {
        for (size_t i = 0; i < inode_cache_constants::cache_size; i++) {
            auto &inode = inodes[i];
            if (inode.inode_index == 0) {
                index = i;
                break;
            }
        }
    }
    if (index == SIZE_MAX) {
        for (size_t i = 0; i < inode_cache_constants::cache_size; i++) {
            auto &inode = inodes[i];
            if (inode.reference_count == 0) {
                index = i;
                break;
            }
        }
    }
    if (index == SIZE_MAX) {
        panic("inode_cache::acquire_cached_inode");
    }
    auto &inode = inodes[index];
    if (inode.inode_index != inode_index) {
        inode.inode_index = inode_index;
        inode.is_updated = false;
    }
    inode.reference_count += 1;
    lock.release();
    return inode_cache_index_t{index};
}

auto inode_cache_t::lock_cached_inode(inode_cache_index_t cached_inode_index) -> void {
    inodes[cached_inode_index].lock.acquire();
}

auto inode_cache_t::read_cached_inode(inode_cache_index_t cached_inode_index) -> inode_t {
    if (block_cache == nullptr) {
        panic("inode_cache::read_cached_inode");
    }
    auto &inode = inodes[cached_inode_index];
    if (inode.reference_count < 1) {
        panic("inode_cache::read_cached_inode");
    }
    if (inode.inode_index == 0) {
        panic("inode_cache::read_cached_inode");
    }
    if (!inode.is_updated) {
        auto index_of_block = block_index_t(inode_cache_constants::inode_begin +
                                            inode.inode_index / (device::virtio_blk_block_size / sizeof(inode_t)));
        auto index_of_inode_in_block = inode.inode_index % (device::virtio_blk_block_size / sizeof(inode_t));
        auto block_cache_index = block_cache->acquire_block(index_of_block);
        auto *address_of_inode_in_block_cache = block_cache->get_data<inode_t>(block_cache_index);
        inode.value = (*address_of_inode_in_block_cache)[index_of_inode_in_block];
        inode.is_updated = true;
        block_cache->release_block(block_cache_index, false);
    }
    return inode.value;
}

auto inode_cache_t::write_cached_inode(inode_cache_index_t cached_inode_index, inode_t value) -> void {
    if (block_cache == nullptr) {
        panic("inode_cache::write_cached_inode");
    }
    auto &inode = inodes[cached_inode_index];
    if (inode.reference_count < 1) {
        panic("inode_cache::write_cached_inode");
    }
    if (inode.inode_index == 0) {
        panic("inode_cache::write_cached_inode");
    }
    if (!inode.is_updated) {
        panic("inode_cache::write_cached_inode");
    }
    auto index_of_block = block_index_t(inode_cache_constants::inode_begin +
                                        (inode.inode_index / (device::virtio_blk_block_size / sizeof(inode_t))));
    auto index_of_inode_in_block = inode.inode_index % (device::virtio_blk_block_size / sizeof(inode_t));
    auto block_cache_index = block_cache->acquire_block(index_of_block);
    auto *address_of_inode_in_block_cache = block_cache->get_data<inode_t>(block_cache_index);
    (*address_of_inode_in_block_cache)[index_of_inode_in_block] = value;
    inode.value = value;

    block_cache->release_block(block_cache_index, true);
}

auto inode_cache_t::unlock_cached_inode(inode_cache_index_t cached_inode_index) -> void {
    inodes[cached_inode_index].lock.release();
}

auto inode_cache_t::release_cached_inode(inode_cache_index_t cached_inode_index) -> void {
    lock.acquire();
    auto &inode = inodes[cached_inode_index];
    if (inode.reference_count < 1) {
        panic("inode_cache::release_cached_inode");
    }
    inode.reference_count -= 1;
    lock.release();
}

auto inode_cache_t::get(path_name_t path, bool should_get_parent_directory_instead) -> inode_index_t {
    path_name_t root_directory_path = path_name_t{"/"};
    if (!should_get_parent_directory_instead && path == root_directory_path) {
        return inode_index_t{1};
    }
    auto current_directory_inode_cache_index =
        this->acquire_cached_inode(inode_index_t{inode_cache_constants::root_directory_inode_index});
    this->lock_cached_inode(current_directory_inode_cache_index);
    auto inode_of_current_directory = this->read_cached_inode(current_directory_inode_cache_index);
    uint32_t index_of_inode_on_disk = 0;
    auto name = path.front();
    if (!name || !path.pop_front()) {
        return inode_index_t{0};
    }
    if (should_get_parent_directory_instead) {
        if (path == path_name_t{"/"}) {
            this->unlock_cached_inode(current_directory_inode_cache_index);
            this->release_cached_inode(current_directory_inode_cache_index);
            return inode_index_t{inode_cache_constants::root_directory_inode_index};
        }
        if (!path.pop_back()) {
            return inode_index_t{0};
        }
    }
    while (index_of_inode_on_disk == 0) {
        auto found_inode_index = inode_index_t{0};
        for (size_t i = 0; i < inode_of_current_directory.size / sizeof(directory_entry_t); i++) {
            auto directory_entry = this->read_directory_entry_at_index(current_directory_inode_cache_index, i);
            if (directory_entry.name == name) {
                found_inode_index = directory_entry.inode_index;
                break;
            }
        }
        if (found_inode_index != 0) {
            auto next_inode_index_in_cache = this->acquire_cached_inode(found_inode_index);
            this->lock_cached_inode(next_inode_index_in_cache);
            auto next_inode = this->read_cached_inode(next_inode_index_in_cache);

            if (path == path_name_t{"/"}) {
                if ((next_inode.inode_type == inode_type_t::directory && should_get_parent_directory_instead) ||
                    !should_get_parent_directory_instead) {
                    index_of_inode_on_disk = found_inode_index;
                }
                this->unlock_cached_inode(next_inode_index_in_cache);
                this->release_cached_inode(next_inode_index_in_cache);
                break;
            }
            if (next_inode.inode_type == inode_type_t::directory) {
                this->unlock_cached_inode(current_directory_inode_cache_index);
                this->release_cached_inode(current_directory_inode_cache_index);
                current_directory_inode_cache_index = next_inode_index_in_cache;
                inode_of_current_directory = this->read_cached_inode(current_directory_inode_cache_index);
                name = path.front();
                if (!name || !path.pop_front()) {
                    return inode_index_t{0};
                }
                continue;
            }
        } else {
            break;
        }
    }
    this->unlock_cached_inode(current_directory_inode_cache_index);
    this->release_cached_inode(current_directory_inode_cache_index);

    return inode_index_t{index_of_inode_on_disk};
}

auto inode_cache_t::set(path_name_t path, inode_index_t inode_index) -> bool {
    auto index_of_parent_directory_inode_on_disk = get(path, true);
    if (index_of_parent_directory_inode_on_disk == 0) {
        return false;
    }
    auto index_of_parent_directory_inode_in_cache = this->acquire_cached_inode(index_of_parent_directory_inode_on_disk);
    this->lock_cached_inode(index_of_parent_directory_inode_in_cache);
    auto inode_of_parent_directory = this->read_cached_inode(index_of_parent_directory_inode_in_cache);

    int directory_entry_index = 0;
    bool directory_entry_index_is_available = false;
    while (directory_entry_index * sizeof(directory_entry_t) < inode_of_parent_directory.size) {
        auto directory_entry =
            this->read_directory_entry_at_index(index_of_parent_directory_inode_in_cache, directory_entry_index);
        if (directory_entry.name == path || directory_entry.inode_index == 0) {
            directory_entry_index_is_available = true;
            break;
        }
        directory_entry_index += 1;
    }
    if (!directory_entry_index_is_available) {
        this->resize(index_of_parent_directory_inode_in_cache,
                     inode_of_parent_directory.size + sizeof(directory_entry_t));
    }

    directory_entry_t directory_entry = {.name = path.back(), .inode_index = inode_index};
    this->write_directory_entry_at_index(index_of_parent_directory_inode_in_cache, directory_entry_index,
                                         directory_entry);

    this->unlock_cached_inode(index_of_parent_directory_inode_in_cache);
    this->release_cached_inode(index_of_parent_directory_inode_in_cache);

    auto index_of_inode_on_disk = this->get(path, false);
    auto index_of_inode_in_cache = this->acquire_cached_inode(index_of_inode_on_disk);
    this->lock_cached_inode(index_of_inode_in_cache);
    auto inode = this->read_cached_inode(index_of_inode_in_cache);
    inode.number_of_links += 1;
    this->write_cached_inode(index_of_inode_in_cache, inode);
    this->unlock_cached_inode(index_of_inode_in_cache);
    this->release_cached_inode(index_of_inode_in_cache);
    return true;
}

auto inode_cache_t::unset(path_name_t path) -> void {
    auto index_of_inode_on_disk = get(path, false);
    auto index_of_inode_in_cache = this->acquire_cached_inode(index_of_inode_on_disk);
    this->lock_cached_inode(index_of_inode_in_cache);
    auto inode = this->read_cached_inode(index_of_inode_in_cache);
    inode.number_of_links -= 1;
    this->write_cached_inode(index_of_inode_in_cache, inode);
    this->unlock_cached_inode(index_of_inode_in_cache);
    this->release_cached_inode(index_of_inode_in_cache);

    auto index_of_parent_directory_inode_on_disk = get(path, true);
    auto index_of_parent_directory_inode_in_cache = this->acquire_cached_inode(index_of_parent_directory_inode_on_disk);
    this->lock_cached_inode(index_of_parent_directory_inode_in_cache);
    auto inode_of_parent_directory = this->read_cached_inode(index_of_parent_directory_inode_in_cache);

    auto name = path.back();

    for (int i = 0; i * sizeof(directory_entry_t) < inode_of_parent_directory.size; i++) {
        auto directory_entry = this->read_directory_entry_at_index(index_of_parent_directory_inode_in_cache, i);
        if (directory_entry.name == name) {
            auto index_of_last_directory_entry = inode_of_parent_directory.size / sizeof(directory_entry_t) - 1;
            auto last_directory_entry = this->read_directory_entry_at_index(index_of_parent_directory_inode_in_cache,
                                                                            index_of_last_directory_entry);
            this->write_directory_entry_at_index(index_of_parent_directory_inode_in_cache, i, last_directory_entry);
            this->resize(index_of_parent_directory_inode_in_cache,
                         inode_of_parent_directory.size - sizeof(directory_entry_t));
            break;
        }
    }

    this->unlock_cached_inode(index_of_parent_directory_inode_in_cache);
    this->release_cached_inode(index_of_parent_directory_inode_in_cache);
}

auto inode_cache_t::read(inode_index_t inode_index_on_disk, size_t offset, span_t<byte_t> buffer) -> size_t {
    auto inode_index_in_cache = this->acquire_cached_inode(inode_index_on_disk);
    this->lock_cached_inode(inode_index_in_cache);
    auto inode = this->read_cached_inode(inode_index_in_cache);
    if (offset >= inode.size) {
        this->unlock_cached_inode(inode_index_in_cache);
        this->release_cached_inode(inode_index_in_cache);
        return 0;
    }
    auto number_of_bytes_to_read = buffer.size() > inode.size - offset ? inode.size - offset : buffer.size();
    for (size_t i = 0; i < number_of_bytes_to_read; i++) {
        auto block_index_in_inode = (offset + i) / device::virtio_blk_block_size;
        auto byte_offset_in_block = (offset + i) % device::virtio_blk_block_size;
        auto block_index_on_disk =
            this->get_block_index_on_disk_by_index_in_inode(inode_index_in_cache, block_index_in_inode);
        auto block_index_in_cache = block_cache->acquire_block(block_index_on_disk);
        auto *block = block_cache->get_data(block_index_in_cache);
        buffer[i] = (*block)[byte_offset_in_block];
        block_cache->release_block(block_index_in_cache, false);
    }
    this->unlock_cached_inode(inode_index_in_cache);
    this->release_cached_inode(inode_index_in_cache);
    return number_of_bytes_to_read;
}

auto inode_cache_t::write(inode_index_t inode_index_on_disk, size_t offset, span_t<byte_t> buffer) -> size_t {
    auto inode_index_in_cache = this->acquire_cached_inode(inode_index_on_disk);
    this->lock_cached_inode(inode_index_in_cache);
    auto inode = this->read_cached_inode(inode_index_in_cache);
    if (offset + buffer.size() > inode.size) {
        this->resize(inode_index_in_cache, offset + buffer.size());
    }
    for (size_t i = 0; i < buffer.size(); i++) {
        auto byte = buffer[i];
        auto block_index_in_inode = (offset + i) / device::virtio_blk_block_size;
        auto byte_offset_in_block = (offset + i) % device::virtio_blk_block_size;
        auto block_index_on_disk =
            this->get_block_index_on_disk_by_index_in_inode(inode_index_in_cache, block_index_in_inode);
        auto block_index_in_cache = block_cache->acquire_block(block_index_on_disk);
        auto *block = block_cache->get_data(block_index_in_cache);
        (*block)[byte_offset_in_block] = byte;
        block_cache->release_block(block_index_in_cache, true);
    }
    this->unlock_cached_inode(inode_index_in_cache);
    this->release_cached_inode(inode_index_in_cache);
    return buffer.size();
}

auto inode_cache_t::status(inode_index_t inode_index_on_disk) -> inode_status_t {
    auto index_of_inode_in_cache = this->acquire_cached_inode(inode_index_on_disk);
    this->lock_cached_inode(index_of_inode_in_cache);
    auto inode = this->read_cached_inode(index_of_inode_in_cache);
    this->unlock_cached_inode(index_of_inode_in_cache);
    this->release_cached_inode(index_of_inode_in_cache);
    return {inode.inode_type, inode.size};
}

auto inode_cache_t::allocate(bool is_directory) -> inode_index_t {
    for (uint32_t i = 2; i < inode_cache_constants::maximum_number_of_inodes; i++) {
        auto inode_cache_index = this->acquire_cached_inode(inode_index_t{i});
        this->lock_cached_inode(inode_cache_index);
        auto inode_type = this->read_cached_inode(inode_cache_index).inode_type;
        if (inode_type == inode_type_t::unused) {
            inode_t new_inode = {
                is_directory ? inode_type_t::directory : inode_type_t::file,
            };
            this->write_cached_inode(inode_cache_index, new_inode);
            this->unlock_cached_inode(inode_cache_index);
            this->release_cached_inode(inode_cache_index);
            return inode_index_t{i};
        }
        this->unlock_cached_inode(inode_cache_index);
        this->release_cached_inode(inode_cache_index);
    }
    panic("inode_cache::allocate");
    return inode_index_t{};
}

auto inode_cache_t::deallocate(inode_index_t inode_index) -> void {
    if (inode_index == inode_cache_constants::root_directory_inode_index) {
        return;
    }
    auto inode_cache_index = this->acquire_cached_inode(inode_index);
    this->lock_cached_inode(inode_cache_index);
    auto inode = this->read_cached_inode(inode_cache_index);
    if (inode.number_of_links == 0 && inodes[inode_cache_index].reference_count == 1) {
        if (inode.inode_type == inode_type_t::directory && inode.size > 0) {
            for (int i = 0; i * sizeof(directory_entry_t) < inode.size; i++) {
                auto directory_entry = this->read_directory_entry_at_index(inode_cache_index, i);
                if (directory_entry.inode_index != 0) {
                    auto index_of_inode_in_cache = this->acquire_cached_inode(directory_entry.inode_index);
                    this->lock_cached_inode(index_of_inode_in_cache);
                    auto inode = this->read_cached_inode(index_of_inode_in_cache);
                    inode.number_of_links -= 1;
                    this->write_cached_inode(index_of_inode_in_cache, inode);
                    this->unlock_cached_inode(index_of_inode_in_cache);
                    this->release_cached_inode(index_of_inode_in_cache);
                    this->deallocate(directory_entry.inode_index);
                }
            }
        } else if (inode.inode_type == inode_type_t::unused) {
            panic("inode_cache::deallocate");
        }
        inode.inode_type = inode_type_t::unused;
        this->write_cached_inode(inode_cache_index, inode);
        this->resize(inode_cache_index, 0);
        this->free_pointer_tables(inode_cache_index);
    }
    this->unlock_cached_inode(inode_cache_index);
    this->release_cached_inode(inode_cache_index);
}

auto inode_cache_t::reference(inode_index_t inode_index_on_disk) -> void {
    auto inode_index_in_cache = this->acquire_cached_inode(inode_index_on_disk);
    lock.acquire();
    auto &inode = inodes[inode_index_in_cache];
    inode.reference_count += 1;
    lock.release();
    this->release_cached_inode(inode_index_in_cache);
}

auto inode_cache_t::dereference(inode_index_t inode_index_on_disk) -> void {
    auto inode_index_in_cache = this->acquire_cached_inode(inode_index_on_disk);
    lock.acquire();
    auto &inode = inodes[inode_index_in_cache];
    inode.reference_count -= 1;
    lock.release();
    this->release_cached_inode(inode_index_in_cache);
}

auto inode_cache_t::allocate_block() -> block_index_t {
    uint32_t block_index = 0;
    for (auto index = inode_cache_constants::bitmap_begin; index < inode_cache_constants::bitmap_end; index++) {
        auto cache = block_cache->acquire_block(block_index_t{index});
        auto *data = block_cache->get_data(cache);
        for (size_t offset = 0; offset < device::virtio_blk_block_size; offset++) {
            auto byte = (*data)[offset];
            for (int shift = 0; shift < uint8_width; shift++) {
                if (block_index == 0) {
                    block_index += 1;
                    continue;
                }
                auto bit = (byte.get_value() >> shift) & 0x1;
                if (bit == 0x0) {
                    byte_t new_byte{};
                    new_byte.set_value(byte.get_value() | (0x1 << shift));
                    (*data)[offset] = new_byte;
                    block_cache->release_block(cache, true);
                    return block_index_t{inode_cache_constants::data_begin + block_index};
                }
                block_index += 1;
            }
        }
        block_cache->release_block(cache, false);
    }
    panic("inode_cache::allocate_block");
    return block_index_t{};
}

auto inode_cache_t::deallocate_block(block_index_t index_on_disk) -> void {
    auto index =
        block_index_t(inode_cache_constants::bitmap_begin + (index_on_disk - inode_cache_constants::data_begin) /
                                                                (uint8_width * device::virtio_blk_block_size));
    auto offset =
        ((index_on_disk - inode_cache_constants::data_begin) % (uint8_width * device::virtio_blk_block_size)) /
        uint8_width;
    auto shift = (index_on_disk - inode_cache_constants::data_begin) % uint8_width;
    auto cache = block_cache->acquire_block(index);
    auto *data = block_cache->get_data(cache);
    auto byte = (*data)[offset];
    byte_t new_byte{};
    new_byte.set_value(byte.get_value() & ~(1 << shift));
    (*data)[offset] = new_byte;
    block_cache->release_block(cache, true);
}

auto inode_cache_t::get_block_index_on_disk_by_index_in_inode(inode_cache_index_t inode_index_in_cache,
                                                              uint32_t index_in_inode) -> block_index_t {
    auto inode = this->read_cached_inode(inode_index_in_cache);
    if (index_in_inode < inode_cache_constants::direct_pointers_offset_end_index) {
        return inode.direct_pointers[index_in_inode];
    }
    if (index_in_inode < inode_cache_constants::single_indirect_pointer_offset_end_index) {
        auto index_in_indirect_pointer_table =
            index_in_inode - inode_cache_constants::single_indirect_pointer_offset_begin_index;

        if (inode.single_indirect_pointer == 0) {
            panic("inode_cache::get_block_index_on_disk_by_index_in_inode");
            return {};
        }

        auto first_indirect_pointer_table_cache = block_cache->acquire_block(inode.single_indirect_pointer);
        auto *first_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(first_indirect_pointer_table_cache);
        auto result = (*first_indirect_pointer_table_data)[index_in_indirect_pointer_table];
        block_cache->release_block(first_indirect_pointer_table_cache, false);

        return result;
    }
    if (index_in_inode < inode_cache_constants::double_indirect_pointer_offset_end_index) {
        auto new_index = index_in_inode - inode_cache_constants::double_indirect_pointer_offset_begin_index;
        auto index_in_first_indirect_pointer_table = new_index / inode_cache_constants::number_of_pointers_per_block;
        auto index_in_second_indirect_pointer_table = new_index % inode_cache_constants::number_of_pointers_per_block;

        if (inode.double_indirect_pointer == 0) {
            panic("inode_cache::get_block_index_on_disk_by_index_in_inode");
            return {};
        }

        auto first_indirect_pointer_table_cache = block_cache->acquire_block(inode.double_indirect_pointer);
        auto *first_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(first_indirect_pointer_table_cache);
        auto index_of_second_indirect_pointer_table_on_disk =
            (*first_indirect_pointer_table_data)[index_in_first_indirect_pointer_table];

        if (index_of_second_indirect_pointer_table_on_disk == 0) {
            panic("inode_cache::get_block_index_on_disk_by_index_in_inode");
            return {};
        }

        auto second_indirect_pointer_table_cache =
            block_cache->acquire_block(index_of_second_indirect_pointer_table_on_disk);
        auto *second_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(second_indirect_pointer_table_cache);
        auto result = (*second_indirect_pointer_table_data)[index_in_second_indirect_pointer_table];

        block_cache->release_block(second_indirect_pointer_table_cache, false);
        block_cache->release_block(first_indirect_pointer_table_cache, false);

        return result;
    }
    if (index_in_inode < inode_cache_constants::triple_indirect_pointer_offset_end_index) {
        auto new_index = index_in_inode - inode_cache_constants::triple_indirect_pointer_offset_begin_index;
        auto index_in_first_indirect_pointer_table = new_index / (inode_cache_constants::number_of_pointers_per_block *
                                                                  inode_cache_constants::number_of_pointers_per_block);
        auto index_in_second_indirect_pointer_table =
            (new_index % (inode_cache_constants::number_of_pointers_per_block *
                          inode_cache_constants::number_of_pointers_per_block)) /
            inode_cache_constants::number_of_pointers_per_block;
        auto index_in_third_indirect_pointer_table = new_index % inode_cache_constants::number_of_pointers_per_block;

        if (inode.triple_indirect_pointer == 0) {
            panic("inode_cache::get_block_index_on_disk_by_index_in_inode");
            return {};
        }

        auto first_indirect_pointer_table_cache = block_cache->acquire_block(inode.triple_indirect_pointer);
        auto *first_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(first_indirect_pointer_table_cache);
        auto index_of_second_indirect_pointer_table_on_disk =
            (*first_indirect_pointer_table_data)[index_in_first_indirect_pointer_table];

        if (index_of_second_indirect_pointer_table_on_disk == 0) {
            panic("inode_cache::get_block_index_on_disk_by_index_in_inode");
            return {};
        }

        auto second_indirect_pointer_table_cache =
            block_cache->acquire_block(index_of_second_indirect_pointer_table_on_disk);
        auto *second_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(second_indirect_pointer_table_cache);
        auto index_of_third_indirect_pointer_table_on_disk =
            (*second_indirect_pointer_table_data)[index_in_second_indirect_pointer_table];

        if (index_of_third_indirect_pointer_table_on_disk == 0) {
            panic("inode_cache::get_block_index_on_disk_by_index_in_inode");
            return {};
        }

        auto third_indirect_pointer_table_cache =
            block_cache->acquire_block(index_of_third_indirect_pointer_table_on_disk);
        auto *third_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(third_indirect_pointer_table_cache);
        auto result = (*third_indirect_pointer_table_data)[index_in_third_indirect_pointer_table];

        block_cache->release_block(third_indirect_pointer_table_cache, false);
        block_cache->release_block(second_indirect_pointer_table_cache, false);
        block_cache->release_block(first_indirect_pointer_table_cache, false);

        return result;
    }
    panic("inode_cache::get_block_index_on_disk_by_index_in_inode");
    return {};
}

auto inode_cache_t::set_block_index_on_disk_by_index_in_inode(inode_cache_index_t inode_index_in_cache,
                                                              uint32_t block_index_in_inode,
                                                              block_index_t block_index_on_disk) -> void {
    auto copy_of_inode = this->read_cached_inode(inode_index_in_cache);
    if (block_index_in_inode < inode_cache_constants::direct_pointers_offset_end_index) {
        copy_of_inode.direct_pointers[block_index_in_inode] = block_index_on_disk;
        this->write_cached_inode(inode_index_in_cache, copy_of_inode);
    } else if (block_index_in_inode < inode_cache_constants::single_indirect_pointer_offset_end_index) {
        auto index_in_indirect_pointer_table =
            block_index_in_inode - inode_cache_constants::single_indirect_pointer_offset_begin_index;

        if (copy_of_inode.single_indirect_pointer == 0) {
            auto index_of_newly_allocated_block_on_disk = allocate_block();
            copy_of_inode.single_indirect_pointer = index_of_newly_allocated_block_on_disk;
            this->write_cached_inode(inode_index_in_cache, copy_of_inode);
        }

        auto first_indirect_pointer_table_cache = block_cache->acquire_block(copy_of_inode.single_indirect_pointer);
        auto *first_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(first_indirect_pointer_table_cache);
        (*first_indirect_pointer_table_data)[index_in_indirect_pointer_table] = block_index_on_disk;

        block_cache->release_block(first_indirect_pointer_table_cache, true);
    } else if (block_index_in_inode < inode_cache_constants::double_indirect_pointer_offset_end_index) {
        auto new_index = block_index_in_inode - inode_cache_constants::double_indirect_pointer_offset_begin_index;
        auto index_in_first_indirect_pointer_table = new_index / inode_cache_constants::number_of_pointers_per_block;
        auto index_in_second_indirect_pointer_table = new_index % inode_cache_constants::number_of_pointers_per_block;

        if (copy_of_inode.double_indirect_pointer == 0) {
            auto index_of_newly_allocated_block_on_disk = allocate_block();
            copy_of_inode.double_indirect_pointer = index_of_newly_allocated_block_on_disk;
            this->write_cached_inode(inode_index_in_cache, copy_of_inode);
        }

        bool is_first_indirect_pointer_table_updated = false;
        auto first_indirect_pointer_table_cache = block_cache->acquire_block(copy_of_inode.double_indirect_pointer);
        auto *first_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(first_indirect_pointer_table_cache);
        auto index_of_second_indirect_pointer_table_on_disk =
            (*first_indirect_pointer_table_data)[index_in_first_indirect_pointer_table];

        if (index_of_second_indirect_pointer_table_on_disk == 0) {
            auto index_of_newly_allocated_block_on_disk = allocate_block();
            auto index_of_newly_allocated_block_in_cache =
                block_cache->acquire_block(index_of_newly_allocated_block_on_disk);
            auto *newly_allocated_block = block_cache->get_data(index_of_newly_allocated_block_in_cache);
            for (size_t offset = 0; offset < device::virtio_blk_block_size; offset++) {
                (*newly_allocated_block)[offset] = byte_t{};
            }
            block_cache->release_block(index_of_newly_allocated_block_in_cache, true);
            (*first_indirect_pointer_table_data)[index_in_first_indirect_pointer_table] =
                index_of_newly_allocated_block_on_disk;
            is_first_indirect_pointer_table_updated = true;
            index_of_second_indirect_pointer_table_on_disk = index_of_newly_allocated_block_on_disk;
        }

        auto second_indirect_pointer_table_cache =
            block_cache->acquire_block(index_of_second_indirect_pointer_table_on_disk);
        auto *second_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(second_indirect_pointer_table_cache);
        (*second_indirect_pointer_table_data)[index_in_second_indirect_pointer_table] = block_index_on_disk;

        block_cache->release_block(second_indirect_pointer_table_cache, true);
        block_cache->release_block(first_indirect_pointer_table_cache, is_first_indirect_pointer_table_updated);
    } else if (block_index_in_inode < inode_cache_constants::triple_indirect_pointer_offset_end_index) {
        auto new_index = block_index_in_inode - inode_cache_constants::triple_indirect_pointer_offset_begin_index;
        auto index_in_first_indirect_pointer_table = new_index / (inode_cache_constants::number_of_pointers_per_block *
                                                                  inode_cache_constants::number_of_pointers_per_block);
        auto index_in_second_indirect_pointer_table =
            (new_index % (inode_cache_constants::number_of_pointers_per_block *
                          inode_cache_constants::number_of_pointers_per_block)) /
            inode_cache_constants::number_of_pointers_per_block;
        auto index_in_third_indirect_pointer_table = new_index % inode_cache_constants::number_of_pointers_per_block;

        if (copy_of_inode.triple_indirect_pointer == 0) {
            auto index_of_newly_allocated_block_on_disk = allocate_block();
            copy_of_inode.triple_indirect_pointer = index_of_newly_allocated_block_on_disk;
            this->write_cached_inode(inode_index_in_cache, copy_of_inode);
        }

        auto is_first_indirect_pointer_table_updated = false;
        auto first_indirect_pointer_table_cache = block_cache->acquire_block(copy_of_inode.triple_indirect_pointer);
        auto *first_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(first_indirect_pointer_table_cache);
        auto index_of_second_indirect_pointer_table_on_disk =
            (*first_indirect_pointer_table_data)[index_in_first_indirect_pointer_table];

        if (index_of_second_indirect_pointer_table_on_disk == 0) {
            auto index_of_newly_allocated_block_on_disk = allocate_block();
            auto index_of_newly_allocated_block_in_cache =
                block_cache->acquire_block(index_of_newly_allocated_block_on_disk);
            auto *newly_allocated_block = block_cache->get_data(index_of_newly_allocated_block_in_cache);
            for (size_t offset = 0; offset < device::virtio_blk_block_size; offset++) {
                (*newly_allocated_block)[offset] = byte_t{};
            }
            block_cache->release_block(index_of_newly_allocated_block_in_cache, true);
            (*first_indirect_pointer_table_data)[index_in_first_indirect_pointer_table] =
                index_of_newly_allocated_block_on_disk;
            is_first_indirect_pointer_table_updated = true;
            index_of_second_indirect_pointer_table_on_disk = index_of_newly_allocated_block_on_disk;
        }

        auto is_second_indirect_pointer_table_updated = false;
        auto second_indirect_pointer_table_cache =
            block_cache->acquire_block(index_of_second_indirect_pointer_table_on_disk);
        auto *second_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(second_indirect_pointer_table_cache);
        auto index_of_third_indirect_pointer_table_on_disk =
            (*second_indirect_pointer_table_data)[index_in_second_indirect_pointer_table];

        if (index_of_third_indirect_pointer_table_on_disk == 0) {
            auto index_of_newly_allocated_block_on_disk = allocate_block();
            auto index_of_newly_allocated_block_in_cache =
                block_cache->acquire_block(index_of_newly_allocated_block_on_disk);
            auto *newly_allocated_block = block_cache->get_data(index_of_newly_allocated_block_in_cache);
            for (size_t offset = 0; offset < device::virtio_blk_block_size; offset++) {
                (*newly_allocated_block)[offset] = byte_t{};
            }
            block_cache->release_block(index_of_newly_allocated_block_in_cache, true);
            (*second_indirect_pointer_table_data)[index_in_second_indirect_pointer_table] =
                index_of_newly_allocated_block_on_disk;
            is_second_indirect_pointer_table_updated = true;
            index_of_third_indirect_pointer_table_on_disk = index_of_newly_allocated_block_on_disk;
        }

        auto third_indirect_pointer_table_cache =
            block_cache->acquire_block(index_of_third_indirect_pointer_table_on_disk);
        auto *third_indirect_pointer_table_data =
            block_cache->get_data<block_index_t>(third_indirect_pointer_table_cache);
        (*third_indirect_pointer_table_data)[index_in_third_indirect_pointer_table] = block_index_on_disk;

        block_cache->release_block(third_indirect_pointer_table_cache, true);
        block_cache->release_block(second_indirect_pointer_table_cache, is_second_indirect_pointer_table_updated);
        block_cache->release_block(first_indirect_pointer_table_cache, is_first_indirect_pointer_table_updated);
    }
}

auto inode_cache_t::free_pointer_tables(inode_cache_index_t inode_index_in_cache) -> void {
    auto inode = this->read_cached_inode(inode_index_in_cache);
    for (auto direct_pointer : inode.direct_pointers) {
        if (direct_pointer != 0) {
            panic("inode_cache::free_pointer_tables");
        }
    }
    if (inode.single_indirect_pointer != 0) {
        auto indirect_pointer_table_cache = block_cache->acquire_block(inode.single_indirect_pointer);
        auto *indirect_pointer_table = block_cache->get_data<block_index_t>(indirect_pointer_table_cache);
        for (size_t i = 0; i < device::virtio_blk_block_size / sizeof(uint32_t); i++) {
            if ((*indirect_pointer_table)[i] != 0) {
                panic("inode_cache::free_pointer_tables");
            }
        }
        deallocate_block(inode.single_indirect_pointer);
        block_cache->release_block(indirect_pointer_table_cache, false);
    }
    if (inode.double_indirect_pointer != 0) {
        auto first_indirect_pointer_table_cache = block_cache->acquire_block(inode.double_indirect_pointer);
        auto *first_indirect_pointer_table = block_cache->get_data<block_index_t>(first_indirect_pointer_table_cache);
        for (size_t i = 0; i < device::virtio_blk_block_size / sizeof(uint32_t); i++) {
            auto second_indirect_pointer_table_index_on_disk = (*first_indirect_pointer_table)[i];
            if (second_indirect_pointer_table_index_on_disk != 0) {
                auto second_indirect_pointer_table_cache =
                    block_cache->acquire_block(second_indirect_pointer_table_index_on_disk);
                auto *second_indirect_pointer_table =
                    block_cache->get_data<block_index_t>(second_indirect_pointer_table_cache);
                for (size_t j = 0; j < device::virtio_blk_block_size / sizeof(uint32_t); j++) {
                    if ((*second_indirect_pointer_table)[j] != 0) {
                        panic("inode_cache::free_pointer_tables");
                    }
                }
                deallocate_block(second_indirect_pointer_table_index_on_disk);
                block_cache->release_block(second_indirect_pointer_table_cache, false);
            }
        }
        deallocate_block(inode.double_indirect_pointer);
        block_cache->release_block(first_indirect_pointer_table_cache, false);
    }
    if (inode.triple_indirect_pointer != 0) {
        auto first_indirect_pointer_table_cache = block_cache->acquire_block(inode.triple_indirect_pointer);
        auto *first_indirect_pointer_table = block_cache->get_data<block_index_t>(first_indirect_pointer_table_cache);
        for (size_t i = 0; i < device::virtio_blk_block_size / sizeof(uint32_t); i++) {
            auto second_indirect_pointer_table_index_on_disk = (*first_indirect_pointer_table)[i];
            if (second_indirect_pointer_table_index_on_disk != 0) {
                auto second_indirect_pointer_table_cache =
                    block_cache->acquire_block(second_indirect_pointer_table_index_on_disk);
                auto *second_indirect_pointer_table =
                    block_cache->get_data<block_index_t>(second_indirect_pointer_table_cache);
                for (size_t j = 0; j < device::virtio_blk_block_size / sizeof(uint32_t); j++) {
                    auto third_indirect_pointer_table_index_on_disk = (*second_indirect_pointer_table)[j];
                    if (third_indirect_pointer_table_index_on_disk != 0) {
                        auto third_indirect_pointer_table_cache =
                            block_cache->acquire_block(third_indirect_pointer_table_index_on_disk);
                        auto *third_indirect_pointer_table =
                            block_cache->get_data<block_index_t>(third_indirect_pointer_table_cache);
                        for (size_t k = 0; k < device::virtio_blk_block_size / sizeof(uint32_t); k++) {
                            if ((*third_indirect_pointer_table)[k] != 0) {
                                panic("inode_cache::free_pointer_tables");
                            }
                        }
                        deallocate_block(third_indirect_pointer_table_index_on_disk);
                        block_cache->release_block(third_indirect_pointer_table_cache, false);
                    }
                }
                deallocate_block(second_indirect_pointer_table_index_on_disk);
                block_cache->release_block(second_indirect_pointer_table_cache, false);
            }
        }
        deallocate_block(inode.double_indirect_pointer);
        block_cache->release_block(first_indirect_pointer_table_cache, false);
    }
}

auto inode_cache_t::resize(inode_cache_index_t inode_index_in_cache, size_t new_size) -> void {
    auto inode = this->read_cached_inode(inode_index_in_cache);
    if (new_size < inode.size) {
        auto index_of_first_block_to_deallocate =
            new_size / device::virtio_blk_block_size + (new_size % device::virtio_blk_block_size != 0 ? 1 : 0);
        auto index_of_last_block_to_deallocate =
            inode.size / device::virtio_blk_block_size - (inode.size % device::virtio_blk_block_size == 0 ? 1 : 0);
        for (auto index = index_of_first_block_to_deallocate; index <= index_of_last_block_to_deallocate; index++) {
            auto index_on_disk = get_block_index_on_disk_by_index_in_inode(inode_index_in_cache, index);
            set_block_index_on_disk_by_index_in_inode(inode_index_in_cache, index, {});
            deallocate_block(index_on_disk);
        }
    } else if (new_size > inode.size) {
        auto index_of_first_block_to_allocate =
            inode.size / device::virtio_blk_block_size + (inode.size % device::virtio_blk_block_size != 0 ? 1 : 0);
        auto index_of_last_block_to_allocate =
            new_size / device::virtio_blk_block_size - (new_size % device::virtio_blk_block_size == 0 ? 1 : 0);
        for (auto index = index_of_first_block_to_allocate; index <= index_of_last_block_to_allocate; index++) {
            auto index_of_newly_allocated_block_on_disk = allocate_block();
            set_block_index_on_disk_by_index_in_inode(inode_index_in_cache, index,
                                                      index_of_newly_allocated_block_on_disk);
        }
    }
    inode = this->read_cached_inode(inode_index_in_cache);
    inode.size = new_size;
    this->write_cached_inode(inode_index_in_cache, inode);
}

auto inode_cache_t::read_directory_entry_at_index(inode_cache_index_t inode_index_in_cache, uint64_t index)
    -> directory_entry_t {
    auto block_index_in_inode = (index * sizeof(directory_entry_t)) / device::virtio_blk_block_size;
    auto block_index_on_disk = get_block_index_on_disk_by_index_in_inode(inode_index_in_cache, block_index_in_inode);
    auto block_index_in_cache = block_cache->acquire_block(block_index_on_disk);
    auto *block = block_cache->get_data<directory_entry_t>(block_index_in_cache);
    auto directory_entry_index_in_block =
        ((index * sizeof(directory_entry_t)) % device::virtio_blk_block_size) / sizeof(directory_entry_t);
    auto directory_entry = (*block)[directory_entry_index_in_block];
    block_cache->release_block(block_index_in_cache, false);
    return directory_entry;
}

auto inode_cache_t::write_directory_entry_at_index(inode_cache_index_t inode_index_in_cache, uint64_t index,
                                                   directory_entry_t directory_entry) -> void {
    auto block_index_in_inode = (index * sizeof(directory_entry_t)) / device::virtio_blk_block_size;
    auto block_index_on_disk = get_block_index_on_disk_by_index_in_inode(inode_index_in_cache, block_index_in_inode);
    auto block_index_in_cache = block_cache->acquire_block(block_index_on_disk);
    auto *block = block_cache->get_data<directory_entry_t>(block_index_in_cache);
    auto directory_entry_index_in_block =
        ((index * sizeof(directory_entry_t)) % device::virtio_blk_block_size) / sizeof(directory_entry_t);
    (*block)[directory_entry_index_in_block] = directory_entry;
    block_cache->release_block(block_index_in_cache, true);
}

} // namespace file

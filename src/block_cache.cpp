#include "../include/block_cache.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/panic.hpp"
#include "../include/thread_scheduler.hpp"
#include "../include/virtio_blk.hpp"

namespace file {

block_cache_t::block_cache_t() {
    for (auto i = block_cache_index_t{0}; i < block_cache_constants::cache_size; i = block_cache_index_t{i + 1}) {
        auto &block = blocks[i];
        if (i == 0) {
            block.next = block_cache_index_t{1};
        } else if (i < block_cache_constants::cache_size - 1) {
            block.previous = block_cache_index_t{i - 1};
            block.next = block_cache_index_t{i + 1};
        } else {
            block.previous = block_cache_index_t{i - 1};
        }
    }
}

auto block_cache_t::open_transaction(int number_of_blocks) -> void {
    journal_lock.acquire();
    if (number_of_blocks > block_cache_constants::journal_size) {
        panic("block_cache::open_transaction");
    }
    while (is_closed || maximum_number_of_updated_blocks + number_of_blocks > block_cache_constants::journal_size) {
        process::thread_scheduler::get().sleep(this, journal_lock);
    }
    number_of_open_transactions += 1;
    maximum_number_of_updated_blocks += number_of_blocks;
    journal_lock.release();
}

auto block_cache_t::acquire_block(block_index_t disk_index, bool should_recycle_cache) -> block_cache_index_t {
    if (disk_index == 0) {
        panic("block_cache::acquire_block");
    }
    cache_lock.acquire();
    auto cache_index = block_cache_index_t{UINT64_MAX};
    for (auto i = block_cache_index_t{0}; i < block_cache_constants::cache_size; i = block_cache_index_t{i + 1}) {
        if (blocks[i].index == disk_index) {
            cache_index = i;
            break;
        }
    }
    if (cache_index != UINT64_MAX) {
        blocks[cache_index].number_of_acquired_transactions += 1;
        cache_lock.release();
        blocks[cache_index].lock.acquire();
        return cache_index;
    }
    if (!should_recycle_cache) {
        panic("block_cache::acquire_block");
    }
    for (auto i = block_cache_index_t{0}; i < block_cache_constants::cache_size; i = block_cache_index_t{i + 1}) {
        if (blocks[i].index == 0) {
            cache_index = i;
            break;
        }
    }
    if (cache_index != UINT64_MAX) {
        blocks[cache_index].index = disk_index;
        blocks[cache_index].number_of_acquired_transactions += 1;
        cache_lock.release();
        blocks[cache_index].lock.acquire();
        return cache_index;
    }
    for (auto i = least_recently_used; i != UINT64_MAX; i = blocks[i].previous) {
        if (!blocks[i].dirty && blocks[i].number_of_acquired_transactions == 0) {
            cache_index = i;
            break;
        }
    }
    if (cache_index == UINT64_MAX) {
        panic("block_cache::acquire_block");
    }
    blocks[cache_index].index = disk_index;
    blocks[cache_index].number_of_acquired_transactions += 1;
    blocks[cache_index].updated = false;
    cache_lock.release();
    blocks[cache_index].lock.acquire();
    return cache_index;
}

auto block_cache_t::get_data(block_cache_index_t cache_index, bool should_update_cache)
    -> array_t<byte_t, device::virtio_blk_block_size> * {
    auto &block = blocks[cache_index];
    if (!block.updated) {
        if (should_update_cache) {
            device::virtio_blk::get().read(block.index, &block.data);
            block.updated = true;
        } else {
            panic("block_cache::get_data");
        }
    }
    return &block.data;
}

auto block_cache_t::release_block(block_cache_index_t cache_index, bool updated) -> void {
    if (updated) {
        blocks[cache_index].dirty = true;
        journal_lock.acquire();
        auto disk_index = blocks[cache_index].index;
        bool should_absorb_update = false;
        for (int i = 0; i < metadata.number_of_blocks; i++) {
            if (metadata.block_indices[i] == disk_index) {
                journal_lock.release();
                should_absorb_update = true;
                break;
            }
        }
        if (!should_absorb_update) {
            metadata.block_indices[metadata.number_of_blocks] = disk_index;
            if (metadata.number_of_blocks + 1 > maximum_number_of_updated_blocks) {
                panic("block_cache::release_block");
            }
            metadata.number_of_blocks += 1;
            journal_lock.release();
        }
    }
    blocks[cache_index].number_of_acquired_transactions -= 1;
    blocks[cache_index].lock.release();
    cache_lock.acquire();
    auto &block = blocks[cache_index];
    if (cache_index != most_recently_used) {
        if (cache_index == least_recently_used) {
            least_recently_used = blocks[least_recently_used].previous;
        } else {
            blocks[block.next].previous = block.previous;
        }
        blocks[block.previous].next = block.next;
        block.previous = block_cache_index_t{UINT64_MAX};
        block.next = most_recently_used;
        blocks[most_recently_used].previous = cache_index;
        most_recently_used = cache_index;
    }
    cache_lock.release();
}

auto block_cache_t::close_transaction() -> bool {
    journal_lock.acquire();
    number_of_open_transactions -= 1;
    if (number_of_open_transactions == 0) {
        is_closed = true;
        journal_lock.release();
        for (int i = 0; i < metadata.number_of_blocks; i++) {
            auto disk_index = metadata.block_indices[i];
            auto cache_index = this->acquire_block(disk_index, false);
            auto *data_address = this->get_data(cache_index, false);
            device::virtio_blk::get().write(block_index_t{block_cache_constants::journal_data_begin + i}, data_address);
            this->release_block(cache_index, false);
        }
        device::virtio_blk::get().write(block_index_t{block_cache_constants::journal_metadata_index}, &metadata);
        for (int i = 0; i < metadata.number_of_blocks; i++) {
            auto disk_index = metadata.block_indices[i];
            auto cache_index = this->acquire_block(disk_index, false);
            auto *data_address = this->get_data(cache_index, false);
            device::virtio_blk::get().write(disk_index, data_address);
            blocks[cache_index].dirty = false;
            this->release_block(cache_index, false);
        }
        metadata.number_of_blocks = 0;
        device::virtio_blk::get().write(block_index_t{block_cache_constants::journal_metadata_index}, &metadata);
        journal_lock.acquire();
        maximum_number_of_updated_blocks = 0;
        is_closed = false;
        process::thread_scheduler::get().wake(this);
        journal_lock.release();
        return true;
    }
    journal_lock.release();
    return false;
}

auto block_cache_t::recover_transaction() -> void {
    device::virtio_blk::get().read(block_index_t{block_cache_constants::journal_metadata_index}, &metadata);
    for (int i = 0; i < metadata.number_of_blocks; i++) {
        auto disk_index = metadata.block_indices[i];
        auto cache_index = this->acquire_block(disk_index, false);
        auto *data_address = this->get_data(cache_index, false);
        device::virtio_blk::get().write(block_index_t{block_cache_constants::journal_data_begin + i}, data_address);
        this->release_block(cache_index, false);
    }
    device::virtio_blk::get().write(block_index_t{block_cache_constants::journal_metadata_index}, &metadata);
    for (int i = 0; i < metadata.number_of_blocks; i++) {
        auto disk_index = metadata.block_indices[i];
        auto cache_index = this->acquire_block(disk_index, false);
        auto *data_address = this->get_data(cache_index, false);
        device::virtio_blk::get().write(disk_index, data_address);
        blocks[cache_index].dirty = false;
        this->release_block(cache_index, false);
    }
    metadata.number_of_blocks = 0;
    device::virtio_blk::get().write(block_index_t{block_cache_constants::journal_metadata_index}, &metadata);
}

} // namespace file

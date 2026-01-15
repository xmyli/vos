#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

#include "include/device.hpp"
#include "include/file.hpp"

enum class inode_type_t { unused, directory, file };

struct inode_t {
    inode_type_t inode_type = inode_type_t::unused;
    int number_of_links = 0;
    size_t size = 0;
    std::array<uint32_t, file::inode_cache_constants::number_of_direct_pointers_per_inode> direct_pointers = {};
    uint32_t single_indirect_pointer = 0;
    uint32_t double_indirect_pointer = 0;
    uint32_t triple_indirect_pointer = 0;
};
static_assert(sizeof(inode_t) == file::inode_cache_constants::inode_size);

struct directory_entry_t {
    struct {
        std::array<uint8_t, file::maximum_path_length> data;
        size_t length;
    } name;
    uint32_t inode_index;
};
static_assert(sizeof(directory_entry_t) == file::inode_cache_constants::directory_entry_size);

//////

struct block {
    std::array<std::byte, device::virtio_blk_block_size> data;
};
using blocks = std::array<block, file::inode_cache_constants::single_indirect_pointer_offset_end_index>;

struct directory_table {
    std::array<directory_entry_t, device::virtio_blk_block_size / sizeof(directory_entry_t)> data;
};
using directory_tables =
    std::array<directory_table, file::inode_cache_constants::single_indirect_pointer_offset_end_index>;

struct bitmap {
    std::array<block, file::inode_cache_constants::maximum_number_of_blocks / (8 * device::virtio_blk_block_size)> data;
};

struct inode {
    inode_type_t type;
    std::string name;
    std::size_t size;
    std::variant<std::array<directory_table, file::inode_cache_constants::single_indirect_pointer_offset_end_index>,
                 std::array<block, file::inode_cache_constants::single_indirect_pointer_offset_end_index>>
        data;
    int single_indirect_pointer_table_block_index = 0;
};

void set_bitmap(bitmap &bitmap, int block_index) {
    constexpr auto number_of_bits_in_a_byte = 8;
    auto index = block_index / (number_of_bits_in_a_byte * device::virtio_blk_block_size);
    auto offset = (block_index % (number_of_bits_in_a_byte * device::virtio_blk_block_size)) / number_of_bits_in_a_byte;
    auto shift = block_index % number_of_bits_in_a_byte;
    auto old_value = bitmap.data.at(index).data.at(offset);
    auto new_value = static_cast<uint8_t>(old_value) | (1 << shift);
    bitmap.data.at(index).data.at(offset) = static_cast<std::byte>(new_value);
}

int next_unallocated_block = 1;
auto get_next_unallocated_block(bitmap &bitmap) -> int {
    auto value = next_unallocated_block;
    next_unallocated_block += 1;
    set_bitmap(bitmap, value);
    return value;
}

int next_unallocated_inode = 2;
auto get_next_unallocated_inode() -> int {
    auto value = next_unallocated_inode;
    next_unallocated_inode += 1;
    return value;
}

void insert_directory_entry_into_root_directory(inode &root_directory_inode, std::string name, int index) {
    int table_index = root_directory_inode.size / device::virtio_blk_block_size;
    int entry_index = (root_directory_inode.size % device::virtio_blk_block_size) / sizeof(directory_entry_t);
    directory_entry_t directory_entry = {{"/", 1}, static_cast<uint32_t>(index)};
    for (size_t i = 0; i < name.size() && i < file::maximum_path_length; i++) {
        directory_entry.name.data[i] = name.at(i);
    }
    directory_entry.name.length = name.size() < file::maximum_path_length ? name.size() : file::maximum_path_length;
    root_directory_inode.size += sizeof(directory_entry_t);
    std::get<directory_tables>(root_directory_inode.data).at(table_index).data.at(entry_index) = directory_entry;
}

void write_indirect_pointer_table_entry(std::ofstream &file, int indirect_pointer_table_block_index, int index_of_entry,
                                        uint32_t data_block_index) {
    auto block_offset =
        device::virtio_blk_block_size * (file::inode_cache_constants::data_begin + indirect_pointer_table_block_index);
    auto entry_offset = block_offset + index_of_entry * sizeof(uint32_t);
    auto block_index_to_write = file::inode_cache_constants::data_begin + data_block_index;
    for (size_t byte_offset = 0; byte_offset < sizeof(uint32_t); byte_offset++) {
        file.seekp(entry_offset + byte_offset);
        file.put(reinterpret_cast<char *>(&block_index_to_write)[byte_offset]);
    }
}

void write_block(std::ofstream &file, block &block, int index) {
    auto block_offset = device::virtio_blk_block_size * (file::inode_cache_constants::data_begin + index);
    for (size_t byte_offset = 0; byte_offset < device::virtio_blk_block_size; byte_offset++) {
        file.seekp(block_offset + byte_offset);
        file.put(static_cast<char>(block.data.at(byte_offset)));
    }
}

void write_directory_table(std::ofstream &file, directory_table &directory_table, int index) {
    auto block_offset = device::virtio_blk_block_size * (file::inode_cache_constants::data_begin + index);
    for (size_t entry_offset = 0; entry_offset < device::virtio_blk_block_size / sizeof(directory_entry_t);
         entry_offset++) {
        for (size_t byte_offset = 0; byte_offset < sizeof(directory_entry_t); byte_offset++) {
            file.seekp(block_offset + entry_offset * sizeof(directory_entry_t) + byte_offset);
            file.put(reinterpret_cast<char *>(&directory_table.data.at(entry_offset))[byte_offset]);
        }
    }
}

auto write_inode(std::ofstream &file, bitmap &bitmap, inode &inode, bool is_root_directory = false) -> int {
    inode_t inode_data = {};
    inode_data.inode_type = is_root_directory ? inode_type_t::directory : inode_type_t::file;
    inode_data.size = inode.size;
    inode_data.number_of_links = 1;

    // Write blocks
    const auto number_of_blocks = inode.size % device::virtio_blk_block_size == 0
                                      ? inode.size / device::virtio_blk_block_size
                                      : inode.size / device::virtio_blk_block_size + 1;
    for (int i = 0; i < number_of_blocks; i++) {
        if (i < file::inode_cache_constants::direct_pointers_offset_end_index) {
            auto block_index = get_next_unallocated_block(bitmap);
            if (is_root_directory) {
                write_directory_table(file, std::get<directory_tables>(inode.data).at(i), block_index);
            } else {
                write_block(file, std::get<blocks>(inode.data).at(i), block_index);
            }
            inode_data.direct_pointers[i] = file::inode_cache_constants::data_begin + block_index;
        } else if (i < file::inode_cache_constants::single_indirect_pointer_offset_end_index) {
            // if indirect pointer table does not exist, allocate a new block to it
            if (inode.single_indirect_pointer_table_block_index == 0) {
                inode.single_indirect_pointer_table_block_index = get_next_unallocated_block(bitmap);
                inode_data.single_indirect_pointer =
                    file::inode_cache_constants::data_begin + inode.single_indirect_pointer_table_block_index;
            }
            // write data to the block
            auto block_index = get_next_unallocated_block(bitmap);
            if (is_root_directory) {
                write_directory_table(file, std::get<directory_tables>(inode.data).at(i), block_index);
            } else {
                write_block(file, std::get<blocks>(inode.data).at(i), block_index);
            }
            // write entry to the table
            auto index_of_block_in_single_indirect_pointer_table =
                i - file::inode_cache_constants::direct_pointers_offset_end_index;
            write_indirect_pointer_table_entry(file, inode.single_indirect_pointer_table_block_index,
                                               index_of_block_in_single_indirect_pointer_table, block_index);
        }
    }

    // Write inode
    auto inode_index = is_root_directory ? 1 : get_next_unallocated_inode();
    auto number_of_inodes_per_block = device::virtio_blk_block_size / sizeof(inode_t);
    auto offset_of_block = device::virtio_blk_block_size *
                           (file::inode_cache_constants::inode_begin + inode_index / number_of_inodes_per_block);
    auto offset_of_inode = offset_of_block + (inode_index % number_of_inodes_per_block) * sizeof(inode_t);
    for (size_t offset_of_byte = 0; offset_of_byte < sizeof(inode_t); offset_of_byte++) {
        file.seekp(offset_of_inode + offset_of_byte);
        file.put(reinterpret_cast<char *>(&inode_data)[offset_of_byte]);
    }
    return inode_index;
}

void write_bitmap(std::ofstream &file, bitmap &bitmap) {
    constexpr auto bitmap_offset = device::virtio_blk_block_size * file::inode_cache_constants::bitmap_begin;
    int byte_offset = 0;
    for (auto &block : bitmap.data) {
        for (auto &byte : block.data) {
            file.seekp(bitmap_offset + byte_offset);
            file.put(static_cast<char>(byte));
            byte_offset += 1;
        }
    }
}

auto main(int argc, char *argv[]) -> int {
    std::vector<inode> inodes;

    for (int i = 1; i < argc; i++) {
        std::ifstream file{argv[i], std::ios::binary};
        if (!file.good()) {
            return EXIT_FAILURE;
        }
        auto length{std::filesystem::file_size(argv[i])};
        if (length >
            device::virtio_blk_block_size * file::inode_cache_constants::single_indirect_pointer_offset_end_index) {
            return EXIT_FAILURE;
        }
        std::vector<std::byte> result(length);
        file.read(reinterpret_cast<char *>(result.data()), static_cast<long>(length));

        std::array<block, file::inode_cache_constants::single_indirect_pointer_offset_end_index> blocks;
        std::array<std::byte, device::virtio_blk_block_size> block_data{};

        int index_of_next_block = 0;
        size_t index_of_next_byte = 0;
        for (auto &byte : result) {
            if (index_of_next_byte == device::virtio_blk_block_size) {
                index_of_next_byte = 0;
                blocks.at(index_of_next_block) = {block_data};
                index_of_next_block += 1;
            }
            block_data[index_of_next_byte] = byte;
            index_of_next_byte += 1;
        }
        if (index_of_next_byte != 0) {
            for (size_t i = index_of_next_byte; i < device::virtio_blk_block_size; i++) {
                block_data[i] = std::byte{0};
            }
            blocks.at(index_of_next_block) = {block_data};
            index_of_next_block += 1;
        }

        inodes.push_back(
            {inode_type_t::file, "/" + std::filesystem::path(argv[i]).filename().string(), length, blocks});
    }

    std::ofstream image("fs.img");
    bitmap bitmap = {};
    inode root_directory_inode = {inode_type_t::directory, "/", 0};

    for (auto &inode : inodes) {
        auto inode_index = write_inode(image, bitmap, inode);
        insert_directory_entry_into_root_directory(root_directory_inode, inode.name, inode_index);
    }

    write_inode(image, bitmap, root_directory_inode, true);

    write_bitmap(image, bitmap);

    image.seekp(1048576);
    image.put(0);
    return 0;
}

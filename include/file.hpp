#ifndef FILE_HPP
#define FILE_HPP

#include "device.hpp"

#include <cstddef>
#include <cstdint>

namespace file {

constexpr int maximum_path_length = 108;

enum block_index_t : uint32_t;
enum block_cache_index_t : uint64_t;

namespace block_cache_constants {
    constexpr int journal_size = 64;
    constexpr uint32_t journal_metadata_index = 0;
    constexpr uint32_t journal_data_begin = journal_metadata_index + 1;
    constexpr uint32_t journal_data_end = journal_data_begin + journal_size;
    constexpr int cache_size = 128;
} // namespace block_cache_constants

enum inode_index_t : uint32_t;
enum inode_cache_index_t : uint64_t;

namespace inode_cache_constants {
    constexpr size_t inode_size = 64;
    constexpr size_t directory_entry_size = 128;

    constexpr size_t root_directory_inode_index = 1;

    constexpr uint32_t inode_begin = block_cache_constants::journal_data_end;
    constexpr size_t maximum_number_of_inodes = 256;
    constexpr uint32_t inode_end = inode_begin + (maximum_number_of_inodes * 64) / device::virtio_blk_block_size;
    constexpr uint32_t bitmap_begin = inode_end;
    constexpr size_t maximum_number_of_blocks = 65536;
    constexpr uint32_t bitmap_end = bitmap_begin + maximum_number_of_blocks / (8 * device::virtio_blk_block_size);
    constexpr uint32_t data_begin = bitmap_end;

    constexpr size_t number_of_direct_pointers_per_inode = 9;
    constexpr size_t direct_pointers_offset_begin_index = 0;
    constexpr size_t direct_pointers_offset_end_index =
        direct_pointers_offset_begin_index + number_of_direct_pointers_per_inode;

    constexpr size_t number_of_pointers_per_block = device::virtio_blk_block_size / sizeof(uint32_t);

    constexpr size_t single_indirect_pointer_offset_begin_index = direct_pointers_offset_end_index;
    constexpr size_t single_indirect_pointer_offset_end_index =
        direct_pointers_offset_end_index + number_of_pointers_per_block;

    constexpr size_t double_indirect_pointer_offset_begin_index = single_indirect_pointer_offset_end_index;
    constexpr size_t double_indirect_pointer_offset_end_index =
        single_indirect_pointer_offset_end_index + number_of_pointers_per_block * number_of_pointers_per_block;

    constexpr size_t triple_indirect_pointer_offset_begin_index = double_indirect_pointer_offset_end_index;
    constexpr size_t triple_indirect_pointer_offset_end_index =
        triple_indirect_pointer_offset_begin_index +
        number_of_pointers_per_block * number_of_pointers_per_block * number_of_pointers_per_block;

    constexpr size_t cache_size = 64;
} // namespace inode_cache_constants

namespace descriptor_interface_constants {
    constexpr int maximum_number_of_file_descriptors_per_process = 32;
    constexpr int maximum_number_of_changed_blocks_per_transaction = 8;
} // namespace descriptor_interface_constants

} // namespace file

#endif

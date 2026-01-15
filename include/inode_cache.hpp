#ifndef INODE_CACHE_HPP
#define INODE_CACHE_HPP

#include "../include/path_name.hpp"
#include "../lib/array.hpp"
#include "block_cache.hpp"
#include "external_types.hpp"
#include "file.hpp"
#include "sleep_lock.hpp"

#include <cstddef>
#include <cstdint>

namespace file {

enum class inode_type_t { unused, directory, file };

struct inode_t {
    inode_type_t inode_type = inode_type_t::unused;
    int number_of_links = 0;
    size_t size = 0;
    array_t<block_index_t, inode_cache_constants::number_of_direct_pointers_per_inode> direct_pointers = {};
    block_index_t single_indirect_pointer = {};
    block_index_t double_indirect_pointer = {};
    block_index_t triple_indirect_pointer = {};
};
static_assert(sizeof(inode_t) == inode_cache_constants::inode_size);

struct directory_entry_t {
    path_name_t name;
    inode_index_t inode_index;
};
static_assert(sizeof(directory_entry_t) == inode_cache_constants::directory_entry_size);

struct inode_table_element_t {
    int reference_count = 0;
    inode_index_t inode_index = inode_index_t{0};

    synchronization::sleep_lock lock;
    bool is_updated = false;
    inode_t value;
};

struct inode_status_t {
    inode_type_t type;
    size_t size;
};

class inode_cache_t {
public:
    inode_cache_t(file::block_cache_t *block_cache);
    auto acquire_cached_inode(inode_index_t inode_index) -> inode_cache_index_t;
    auto lock_cached_inode(inode_cache_index_t cached_inode_index) -> void;
    auto read_cached_inode(inode_cache_index_t cached_inode_index) -> inode_t;
    auto write_cached_inode(inode_cache_index_t cached_inode_index, inode_t value) -> void;
    auto unlock_cached_inode(inode_cache_index_t cached_inode_index) -> void;
    auto release_cached_inode(inode_cache_index_t cached_inode_index) -> void;

    auto get(path_name_t path, bool should_get_parent_directory_instead) -> inode_index_t;
    [[nodiscard]] auto set(path_name_t path, inode_index_t inode_index) -> bool;
    auto unset(path_name_t path) -> void;
    auto read(inode_index_t inode_index_on_disk, size_t offset, span_t<byte_t> buffer) -> size_t;
    auto write(inode_index_t inode_index_on_disk, size_t offset, span_t<byte_t> buffer) -> size_t;
    auto status(inode_index_t inode_index_on_disk) -> inode_status_t;
    auto allocate(bool is_directory) -> inode_index_t;
    auto deallocate(inode_index_t inode_index) -> void;
    auto reference(inode_index_t inode_index_on_disk) -> void;
    auto dereference(inode_index_t inode_index_on_disk) -> void;

private:
    file::block_cache_t *block_cache = nullptr;
    synchronization::spin_lock lock;
    array_t<inode_table_element_t, inode_cache_constants::cache_size> inodes;

    auto get_block_index_on_disk_by_index_in_inode(inode_cache_index_t inode_index_in_cache, uint32_t index_in_inode)
        -> block_index_t;
    auto set_block_index_on_disk_by_index_in_inode(inode_cache_index_t inode_index_in_cache,
                                                   uint32_t block_index_in_inode, block_index_t block_index_on_disk)
        -> void;
    auto resize(inode_cache_index_t inode_index_in_cache, size_t new_size) -> void;
    auto read_directory_entry_at_index(inode_cache_index_t inode_index_in_cache, uint64_t index) -> directory_entry_t;
    auto write_directory_entry_at_index(inode_cache_index_t inode_index_in_cache, uint64_t index,
                                        directory_entry_t directory_entry) -> void;
    auto free_pointer_tables(inode_cache_index_t inode_index_in_cache) -> void;
    auto allocate_block() -> block_index_t;
    auto deallocate_block(block_index_t index_on_disk) -> void;
};

} // namespace file

#endif

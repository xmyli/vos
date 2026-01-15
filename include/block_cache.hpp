#ifndef BLOCK_CACHE_HPP
#define BLOCK_CACHE_HPP

#include "../lib/array.hpp"
#include "device.hpp"
#include "reinterpretable.hpp"
#include "sleep_lock.hpp"
#include "virtio_blk.hpp"

namespace file {

struct journal_metadata_t {
    array_t<block_index_t, block_cache_constants::journal_size> block_indices = {};
    int number_of_blocks = 0;
    array_t<byte_t, device::virtio_blk_block_size - sizeof(block_indices) - sizeof(number_of_blocks)> _ = {};
};

struct block_t {
    array_t<byte_t, device::virtio_blk_block_size> data = {};
    synchronization::sleep_lock lock;
    block_cache_index_t previous = block_cache_index_t{UINT64_MAX};
    block_cache_index_t next = block_cache_index_t{UINT64_MAX};
    block_index_t index = block_index_t{0};
    int number_of_acquired_transactions = 0;
    bool updated = false;
    bool dirty = false;
};

class block_cache_t {
public:
    block_cache_t();
    auto open_transaction(int number_of_blocks) -> void;
    auto acquire_block(block_index_t disk_index, bool should_recycle_cache = true) -> block_cache_index_t;
    auto get_data(block_cache_index_t cache_index, bool should_update_cache = true)
        -> array_t<byte_t, device::virtio_blk_block_size> *;
    auto release_block(block_cache_index_t cache_index, bool updated) -> void;
    auto close_transaction() -> bool;
    auto recover_transaction() -> void;

    template <typename T>
    auto get_data(block_cache_index_t cache_index, bool should_update_cache = true)
        -> array_t<T, device::virtio_blk_block_size / sizeof(T)> * {
        return reinterpretable_t<array_t<byte_t, device::virtio_blk_block_size> *>(
                   this->get_data(cache_index, should_update_cache))
            .to<array_t<T, device::virtio_blk_block_size / sizeof(T)>>();
    }

private:
    synchronization::spin_lock cache_lock;
    array_t<block_t, block_cache_constants::cache_size> blocks = {};
    block_cache_index_t most_recently_used = block_cache_index_t{0};
    block_cache_index_t least_recently_used = block_cache_index_t{block_cache_constants::cache_size - 1};

    synchronization::spin_lock journal_lock;
    journal_metadata_t metadata;
    int number_of_open_transactions = 0;
    int maximum_number_of_updated_blocks = 0;
    bool is_closed = false;
};

} // namespace file

#endif

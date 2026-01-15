#ifndef VIRTIO_BLK_HPP
#define VIRTIO_BLK_HPP

#include "../lib/array.hpp"
#include "device.hpp"
#include "external_types.hpp"
#include "memory.hpp"
#include "spin_lock.hpp"

namespace device {

struct virtqueue_t {
    array_t<virtqueue_descriptor, virtio_blk_virtqueue_ring_size> descriptor_table{};
    virtqueue_available_ring available_ring{};
    array_t<byte_t, memory::page_size - sizeof(descriptor_table) - sizeof(available_ring)> _{};
    virtqueue_used_ring used_ring{};
} __attribute__((aligned(memory::page_size)));
static_assert(offsetof(virtqueue_t, used_ring) == memory::page_size);
static_assert(sizeof(virtqueue_t) == 2 * memory::page_size);

class virtio_blk {
public:
    static auto get() -> virtio_blk & {
        static virtio_blk instance;
        return instance;
    }

    static auto initialize() -> void;

    auto read(file::block_index_t block_index, void *data_address) -> void;
    auto write(file::block_index_t block_index, void *data_address) -> void;
    auto interrupt() -> void;

    virtio_blk(const virtio_blk &) = delete;
    auto operator=(const virtio_blk &) -> virtio_blk & = delete;
    virtio_blk(virtio_blk &&) = delete;
    auto operator=(virtio_blk &&) -> virtio_blk & = delete;

private:
    virtqueue_t virtqueue;
    size_t used_ring_index = 0;
    array_t<bool, virtio_blk_virtqueue_ring_size> is_descriptor_free = {};
    array_t<virtio_block_request, virtio_blk_virtqueue_ring_size> operation_request = {};
    array_t<byte_t, virtio_blk_virtqueue_ring_size> operation_status = {};
    array_t<bool, virtio_blk_virtqueue_ring_size> operation_in_progress = {};
    synchronization::spin_lock lock;

    auto allocate_virtqueue_descriptor() -> size_t;
    auto deallocate_virtqueue_descriptor(size_t index) -> void;
    auto read_or_write(file::block_index_t block_index, void *data_address, virtio_request_type operation_type) -> void;

    virtio_blk() = default;
    ~virtio_blk() = default;
};

} // namespace device

#endif

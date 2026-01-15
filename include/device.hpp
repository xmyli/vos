#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <cstddef>
#include <cstdint>

#include "memory.hpp"

namespace device {

constexpr int gicv3_timer_intid = 27;
constexpr int gicv3_pl011_intid = 33;
constexpr int gicv3_pcie_intid = 36;
constexpr int gicv3_virtio_intid = 48;
constexpr int gicv3_spurious_intid = 1023;

constexpr uint64_t timer_prescaler = 1000000;

constexpr int pl011_buffer_size = 64;

constexpr uint16_t e1000_vendor_id = 0x8086;
constexpr uint32_t e1000_device_id = 0x100e;
constexpr uint8_t e1000_collision_threshold = 16;
constexpr uint8_t e1000_collision_distance = 64;
constexpr uint16_t e1000_ipg_transmit_time = 10;
constexpr uint16_t e1000_ipg_receive_time_1 = 8;
constexpr uint16_t e1000_ipg_receive_time_2 = 6;
constexpr uint16_t e1000_descriptor_length = 8;
constexpr uint16_t e1000_number_of_descriptors = 64;
constexpr uint32_t e1000_ethernet_address_low = 0x12005452;
constexpr uint32_t e1000_ethernet_address_high = 0x005634;
constexpr size_t e1000_descriptor_alignment = 16;

constexpr uint32_t virtio_magic_value = 0x74726976;
constexpr uint32_t virtio_blk_version = 1;
constexpr uint32_t virtio_blk_device_id = 2;
constexpr uint32_t virtio_blk_vendor_id = 0x554d4551;
constexpr uint64_t virtio_blk_block_size = 1024;
constexpr uint64_t virtio_blk_sector_size = 512;
constexpr uint64_t virtio_blk_virtqueue_ring_size = 8;

enum class virtio_request_type { read, write };
enum class virtqueue_descriptor_flag { none, next, write, read, indirect };

} // namespace device

#endif

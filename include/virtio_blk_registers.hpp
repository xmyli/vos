#ifndef VIRTIO_BLK_REGISTERS_HPP
#define VIRTIO_BLK_REGISTERS_HPP

#include "../lib/array.hpp"
#include "integer.hpp"

#include <cstdint>

struct virtio_blk_registers_t {
    class magic_value_t {
    public:
        [[nodiscard]] auto get_magic_value_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_magic_value_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class version_t {
    public:
        [[nodiscard]] auto get_version_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_version_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class device_id_t {
    public:
        [[nodiscard]] auto get_device_id_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_device_id_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class vendor_id_t {
    public:
        [[nodiscard]] auto get_vendor_id_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_vendor_id_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class features_t {
    public:
        [[nodiscard]] auto get_virtio_blk_f_barrier_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_barrier_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_size_max_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_size_max_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_seg_max_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_seg_max_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_geometry_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_geometry_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_ro_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_ro_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_blk_size_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_blk_size_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_scsi_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_scsi_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_flush_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_flush_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_topology_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_topology_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_config_wce_bit() const -> bool {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_config_wce_bit(bool value) -> void {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_mq_bit() const -> bool {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_mq_bit(bool value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_discard_bit() const -> bool {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_discard_bit(bool value) -> void {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_write_zeroes_bit() const -> bool {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_write_zeroes_bit(bool value) -> void {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_lifetime_bit() const -> bool {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_lifetime_bit(bool value) -> void {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_secure_erase_bit() const -> bool {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_secure_erase_bit(bool value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_blk_f_zoned_bit() const -> bool {
            constexpr auto offset = 17;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_blk_f_zoned_bit(bool value) -> void {
            constexpr auto offset = 17;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_notify_on_empty_bit() const -> bool {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_notify_on_empty_bit(bool value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_any_layout_bit() const -> bool {
            constexpr auto offset = 27;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_any_layout_bit(bool value) -> void {
            constexpr auto offset = 27;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_indirect_desc_bit() const -> bool {
            constexpr auto offset = 28;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_indirect_desc_bit(bool value) -> void {
            constexpr auto offset = 28;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_event_idx_bit() const -> bool {
            constexpr auto offset = 29;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_event_idx_bit(bool value) -> void {
            constexpr auto offset = 29;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_version_1_bit() const -> bool {
            constexpr auto offset = 32;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_version_1_bit(bool value) -> void {
            constexpr auto offset = 32;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_access_platform_bit() const -> bool {
            constexpr auto offset = 33;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_access_platform_bit(bool value) -> void {
            constexpr auto offset = 33;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_ring_packed_bit() const -> bool {
            constexpr auto offset = 34;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_ring_packed_bit(bool value) -> void {
            constexpr auto offset = 34;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_in_order_bit() const -> bool {
            constexpr auto offset = 35;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_in_order_bit(bool value) -> void {
            constexpr auto offset = 35;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_order_platform_bit() const -> bool {
            constexpr auto offset = 36;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_order_platform_bit(bool value) -> void {
            constexpr auto offset = 36;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_sr_iov_bit() const -> bool {
            constexpr auto offset = 37;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_sr_iov_bit(bool value) -> void {
            constexpr auto offset = 37;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_notification_data_bit() const -> bool {
            constexpr auto offset = 38;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_notification_data_bit(bool value) -> void {
            constexpr auto offset = 38;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_notif_config_data_bit() const -> bool {
            constexpr auto offset = 39;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_notif_config_data_bit(bool value) -> void {
            constexpr auto offset = 39;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_ring_reset_bit() const -> bool {
            constexpr auto offset = 40;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_ring_reset_bit(bool value) -> void {
            constexpr auto offset = 40;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_virtio_f_admin_vq_bit() const -> bool {
            constexpr auto offset = 41;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_virtio_f_admin_vq_bit(bool value) -> void {
            constexpr auto offset = 41;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class guest_page_size_t {
    public:
        [[nodiscard]] auto get_guest_page_size_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_guest_page_size_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class queue_sel_t {
    public:
        [[nodiscard]] auto get_queue_sel_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_queue_sel_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class queue_num_max_t {
    public:
        [[nodiscard]] auto get_queue_size_max_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_queue_size_max_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class queue_num_t {
    public:
        [[nodiscard]] auto get_queue_size_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_queue_size_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class queue_align_t {
    public:
        [[nodiscard]] auto get_queue_align_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_queue_align_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class queue_pfn_t {
    public:
        [[nodiscard]] auto get_queue_pfn_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_queue_pfn_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class queue_notify_t {
    public:
        [[nodiscard]] auto get_queue_notify_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_queue_notify_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class interrupt_status_t {
    public:
        [[nodiscard]] auto get_used_buffer_notification_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_used_buffer_notification_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_configuration_change_notification_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_configuration_change_notification_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class interrupt_ack_t {
    public:
        [[nodiscard]] auto get_used_buffer_notification_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_used_buffer_notification_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_configuration_change_notification_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_configuration_change_notification_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class status_t {
    public:
        [[nodiscard]] auto get_acknowledge_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_acknowledge_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_driver_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_driver_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_driver_ok_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_driver_ok_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_features_ok_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_features_ok_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_device_needs_reset_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_device_needs_reset_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_failed_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_failed_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    static constexpr auto rsv_0_length = 8;
    static constexpr auto rsv_1_length = 4;
    static constexpr auto rsv_2_length = 12;
    static constexpr auto rsv_3_length = 12;
    static constexpr auto rsv_4_length = 8;

    magic_value_t magic_value;
    version_t version;
    device_id_t device_id;
    vendor_id_t vendor_id;
    features_t host_features;
    features_t host_features_sel;
    packed_array_t<packed_byte_t, rsv_0_length> _rsv_0_;
    features_t guest_features;
    features_t guest_features_sel;
    guest_page_size_t guest_page_size;
    packed_array_t<packed_byte_t, rsv_1_length> _rsv_1_;
    queue_sel_t queue_sel;
    queue_num_max_t queue_num_max;
    queue_num_t queue_num;
    queue_align_t queue_align;
    queue_pfn_t queue_pfn;
    packed_array_t<packed_byte_t, rsv_2_length> _rsv_2_;
    queue_notify_t queue_notify;
    packed_array_t<packed_byte_t, rsv_3_length> _rsv_3_;
    interrupt_status_t interrupt_status;
    interrupt_ack_t interrupt_ack;
    packed_array_t<packed_byte_t, rsv_4_length> _rsv_4_;
    status_t status;
} __attribute__((packed));

// NOLINTBEGIN
static_assert(offsetof(virtio_blk_registers_t, magic_value) == 0x0);
static_assert(offsetof(virtio_blk_registers_t, version) == 0x4);
static_assert(offsetof(virtio_blk_registers_t, device_id) == 0x8);
static_assert(offsetof(virtio_blk_registers_t, vendor_id) == 0xc);
static_assert(offsetof(virtio_blk_registers_t, host_features) == 0x10);
static_assert(offsetof(virtio_blk_registers_t, guest_features) == 0x20);
static_assert(offsetof(virtio_blk_registers_t, guest_page_size) == 0x28);
static_assert(offsetof(virtio_blk_registers_t, queue_sel) == 0x30);
static_assert(offsetof(virtio_blk_registers_t, queue_num_max) == 0x34);
static_assert(offsetof(virtio_blk_registers_t, queue_num) == 0x38);
static_assert(offsetof(virtio_blk_registers_t, queue_align) == 0x3c);
static_assert(offsetof(virtio_blk_registers_t, queue_pfn) == 0x40);
static_assert(offsetof(virtio_blk_registers_t, queue_notify) == 0x50);
static_assert(offsetof(virtio_blk_registers_t, interrupt_status) == 0x60);
static_assert(offsetof(virtio_blk_registers_t, interrupt_ack) == 0x64);
static_assert(offsetof(virtio_blk_registers_t, status) == 0x70);
// NOLINTEND

#endif

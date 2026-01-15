#include "../include/virtio_blk.hpp"
#include "../include/device.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/panic.hpp"
#include "../include/thread_scheduler.hpp"

namespace device {

auto virtio_blk::allocate_virtqueue_descriptor() -> size_t {
    for (size_t i = 0; i < virtio_blk_virtqueue_ring_size; i++) {
        auto &value = this->is_descriptor_free[i];
        if (value) {
            value = false;
            return i;
        }
    }
    return -1;
}

auto virtio_blk::deallocate_virtqueue_descriptor(size_t index) -> void {
    if (index >= virtio_blk_virtqueue_ring_size) {
        panic("virtio_blk::deallocate_virtqueue_descriptor");
    }
    if (this->is_descriptor_free[index]) {
        panic("virtio_blk::deallocate_virtqueue_descriptor");
    }
    this->virtqueue.descriptor_table[index].set_address_field(nullptr);
    this->virtqueue.descriptor_table[index].set_length_field(0);
    this->virtqueue.descriptor_table[index].set_flags_field(virtqueue_descriptor_flag::none);
    this->virtqueue.descriptor_table[index].set_next_field(0);
    this->is_descriptor_free[index] = true;
    process::thread_scheduler::get().wake(&this->is_descriptor_free);
}

auto virtio_blk::read_or_write(file::block_index_t block_index, void *data_address, virtio_request_type operation_type)
    -> void {
    this->lock.acquire();

    auto sector_index = block_index * (virtio_blk_block_size / virtio_blk_sector_size);

    array_t<size_t, 3> descriptors = {};
    for (auto &descriptor : descriptors) {
        descriptor = SIZE_MAX;
    }
    int number_of_descriptors = 0;
    while (number_of_descriptors < 3) {
        auto descriptor = allocate_virtqueue_descriptor();
        if (descriptor != SIZE_MAX) {
            descriptors[number_of_descriptors] = descriptor;
            number_of_descriptors += 1;
        } else {
            process::thread_scheduler::get().sleep(&this->is_descriptor_free, this->lock);
        }
    }

    for (auto &descriptor : descriptors) {
        if (descriptor == SIZE_MAX) {
            panic("virtio_blk::read_or_write");
        }
    }

    auto *request_address = &this->operation_request[descriptors[0]];
    (*request_address).set_type_field(operation_type);
    (*request_address).set_sector_field(sector_index);

    auto &first_descriptor = this->virtqueue.descriptor_table[descriptors[0]];
    first_descriptor.set_address_field(request_address);
    first_descriptor.set_length_field(sizeof(virtio_block_request));
    first_descriptor.set_flags_field(virtqueue_descriptor_flag::next);
    first_descriptor.set_next_field(descriptors[1]);

    auto &second_descriptor = this->virtqueue.descriptor_table[descriptors[1]];
    second_descriptor.set_address_field(data_address);
    second_descriptor.set_length_field(virtio_blk_block_size);
    switch (operation_type) {
    case virtio_request_type::read:
        second_descriptor.set_flags_field(virtqueue_descriptor_flag::read);
        break;
    case virtio_request_type::write:
        second_descriptor.set_flags_field(virtqueue_descriptor_flag::next);
        break;
    }
    second_descriptor.set_next_field(descriptors[2]);

    auto &third_descriptor = this->virtqueue.descriptor_table[descriptors[2]];
    third_descriptor.set_address_field(&this->operation_status[descriptors[0]]);
    third_descriptor.set_length_field(1);
    third_descriptor.set_flags_field(virtqueue_descriptor_flag::write);
    third_descriptor.set_next_field(0);
    this->operation_status[descriptors[0]].set_value(~0);

    this->operation_in_progress[descriptors[0]] = true;

    this->virtqueue.available_ring.set_ring_element_at_index(
        this->virtqueue.available_ring.get_index_field() % virtio_blk_virtqueue_ring_size, descriptors[0]);

    __sync_synchronize();

    this->virtqueue.available_ring.set_index_field(this->virtqueue.available_ring.get_index_field() + 1);

    __sync_synchronize();

    reinterpretable_t<>().virtio_blk_registers->queue_notify.set_queue_notify_bits(0);

    while (this->operation_in_progress[descriptors[0]]) {
        process::thread_scheduler::get().sleep(&this->operation_in_progress[descriptors[0]], this->lock);
    }

    this->operation_in_progress[descriptors[0]] = false;
    deallocate_virtqueue_descriptor(descriptors[0]);
    deallocate_virtqueue_descriptor(descriptors[1]);
    deallocate_virtqueue_descriptor(descriptors[2]);

    this->lock.release();
}

auto virtio_blk::read(file::block_index_t block_index, void *data_address) -> void {
    read_or_write(block_index, data_address, virtio_request_type::read);
}

auto virtio_blk::write(file::block_index_t block_index, void *data_address) -> void {
    read_or_write(block_index, data_address, virtio_request_type::write);
}

auto virtio_blk::interrupt() -> void {
    this->lock.acquire();

    reinterpretable_t<>().virtio_blk_registers->interrupt_ack.set_used_buffer_notification_bit(
        reinterpretable_t<>().virtio_blk_registers->interrupt_status.get_used_buffer_notification_bit());
    reinterpretable_t<>().virtio_blk_registers->interrupt_ack.set_configuration_change_notification_bit(
        reinterpretable_t<>().virtio_blk_registers->interrupt_status.get_configuration_change_notification_bit());

    __sync_synchronize();

    while (this->used_ring_index != this->virtqueue.used_ring.get_index_field()) {
        __sync_synchronize();
        auto index =
            this->virtqueue.used_ring.get_ring_element_at_index(this->used_ring_index % virtio_blk_virtqueue_ring_size)
                .get_id_field();

        if (this->operation_status[index].get_value() != 0) {
            panic("virtio_blk::interrupt");
        }

        this->operation_in_progress[index] = false;
        process::thread_scheduler::get().wake(&this->operation_in_progress[index]);

        this->used_ring_index += 1;
    }

    this->lock.release();
}

auto virtio_blk::initialize() -> void {
    if (architecture::get_core_number() == 0) {
        if (reinterpretable_t<>().virtio_blk_registers->magic_value.get_magic_value_bits() != virtio_magic_value) {
            panic("virtio_blk::initialize");
        }

        if (reinterpretable_t<>().virtio_blk_registers->version.get_version_bits() != virtio_blk_version) {
            panic("virtio_blk::initialize");
        }

        if (reinterpretable_t<>().virtio_blk_registers->device_id.get_device_id_bits() != virtio_blk_device_id) {
            panic("virtio_blk::initialize");
        }

        if (reinterpretable_t<>().virtio_blk_registers->vendor_id.get_vendor_id_bits() != virtio_blk_vendor_id) {
            panic("virtio_blk::initialize");
        }

        reinterpretable_t<>().virtio_blk_registers->status.set_acknowledge_bit(true);
        reinterpretable_t<>().virtio_blk_registers->status.set_driver_bit(true);

        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_barrier_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_barrier_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_size_max_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_size_max_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_seg_max_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_seg_max_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_geometry_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_geometry_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_ro_bit(false);
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_blk_size_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_blk_size_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_scsi_bit(false);
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_flush_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_flush_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_topology_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_topology_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_config_wce_bit(false);
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_mq_bit(false);
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_discard_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_discard_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_write_zeroes_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_write_zeroes_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_lifetime_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_lifetime_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_secure_erase_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_secure_erase_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_blk_f_zoned_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_blk_f_zoned_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_notify_on_empty_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_f_notify_on_empty_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_any_layout_bit(false);
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_indirect_desc_bit(false);
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_event_idx_bit(false);
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_version_1_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_f_version_1_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_access_platform_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_f_access_platform_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_ring_packed_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_f_ring_packed_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_in_order_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_f_in_order_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_order_platform_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_f_order_platform_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_sr_iov_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_f_sr_iov_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_notification_data_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_f_notification_data_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_notif_config_data_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_f_notif_config_data_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_ring_reset_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_f_ring_reset_bit());
        reinterpretable_t<>().virtio_blk_registers->guest_features.set_virtio_f_admin_vq_bit(
            reinterpretable_t<>().virtio_blk_registers->host_features.get_virtio_f_admin_vq_bit());

        reinterpretable_t<>().virtio_blk_registers->status.set_features_ok_bit(true);
        reinterpretable_t<>().virtio_blk_registers->status.set_driver_ok_bit(true);

        reinterpretable_t<>().virtio_blk_registers->guest_page_size.set_guest_page_size_bits(memory::page_size);

        reinterpretable_t<>().virtio_blk_registers->queue_sel.set_queue_sel_bits(0);
        if (reinterpretable_t<>().virtio_blk_registers->queue_num_max.get_queue_size_max_bits() == 0) {
            panic("virtio_blk::initialize");
        }
        if (reinterpretable_t<>().virtio_blk_registers->queue_num_max.get_queue_size_max_bits() <
            virtio_blk_virtqueue_ring_size) {
            panic("virtio_blk::initialize");
        }
        reinterpretable_t<>().virtio_blk_registers->queue_num.set_queue_size_bits(virtio_blk_virtqueue_ring_size);
        reinterpretable_t<>().virtio_blk_registers->queue_pfn.set_queue_pfn_bits(
            reinterpretable_t<void *>(&virtio_blk::get().virtqueue).to_integer() / memory::page_size);

        for (auto &value : virtio_blk::get().is_descriptor_free) {
            value = true;
        }
    }
}

} // namespace device

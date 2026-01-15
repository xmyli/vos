#include "../include/e1000.hpp"
#include "../include/buddy_allocator.hpp"
#include "../include/ethernet_protocol.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/panic.hpp"

namespace device {

auto e1000::initialize() -> void {
    if (architecture::get_core_number() == 0) {
        for (int function_index = 0; function_index < pcie_configuration_space_t::maximum_number_of_functions;
             function_index += 1) {
            auto vendor_id = reinterpretable_t<>()
                                 .pcie_configuration_space->functions[function_index]
                                 .vendor_id.get_vendor_id_bits();
            auto device_id = reinterpretable_t<>()
                                 .pcie_configuration_space->functions[function_index]
                                 .device_id.get_device_id_bits();
            if (vendor_id == e1000_vendor_id && device_id == e1000_device_id) {
                reinterpretable_t<>()
                    .pcie_configuration_space->functions[function_index]
                    .command.set_io_space_enable_bit(true);
                reinterpretable_t<>()
                    .pcie_configuration_space->functions[function_index]
                    .command.set_memory_space_enable_bit(true);
                reinterpretable_t<>()
                    .pcie_configuration_space->functions[function_index]
                    .command.set_bus_master_enable_bit(true);
                __sync_synchronize();
                reinterpretable_t<>()
                    .pcie_configuration_space->functions[function_index]
                    .base_address[0]
                    .set_base_address_bits(memory::kernel_address_space_constants::e1000_begin -
                                           memory::kernel_address_space_constants::virtual_address_begin);
            }
        }

        reinterpretable_t<>().e1000_registers->ctrl.set_rst_bit(true);

        for (int i = 0; i < e1000_number_of_descriptors; i++) {
            auto *packet_buffer = networking::packet_buffer_t::allocate();
            e1000::get().receive_packet_buffers[i] = packet_buffer;
            e1000::get().receive_descriptors[i].set_buffer_address_field(packet_buffer->get_packet());
        }
        const auto receive_descriptors_address =
            reinterpretable_t<void *>(&e1000::get().receive_descriptors).to_integer();
        reinterpretable_t<>().e1000_registers->rdbal.set_rdbal_bits(receive_descriptors_address);
        reinterpretable_t<>().e1000_registers->rdbah.set_rdbah_bits(0);
        reinterpretable_t<>().e1000_registers->rdlen.set_len_bits(e1000_descriptor_length);
        reinterpretable_t<>().e1000_registers->rdh.set_rdh_bits(0);
        reinterpretable_t<>().e1000_registers->rdt.set_rdt_bits(e1000_number_of_descriptors - 1);

        for (int i = 0; i < e1000_number_of_descriptors; i++) {
            e1000::get().transmit_descriptors[i].set_descriptor_done_status_field(true);
            e1000::get().transmit_packet_buffers[i] = {};
        }
        const auto transmit_descriptors_address =
            reinterpretable_t<void *>(&e1000::get().transmit_descriptors).to_integer();
        reinterpretable_t<>().e1000_registers->tdbal.set_tdbal_bits(transmit_descriptors_address);
        reinterpretable_t<>().e1000_registers->tdbah.set_tdbah_bits(0);
        reinterpretable_t<>().e1000_registers->tdlen.set_len_bits(e1000_descriptor_length);
        reinterpretable_t<>().e1000_registers->tdh.set_tdh_bits(0);
        reinterpretable_t<>().e1000_registers->tdt.set_tdt_bits(0);

        reinterpretable_t<>().e1000_registers->ral.set_ral_bits(e1000_ethernet_address_low);
        reinterpretable_t<>().e1000_registers->rah.set_rah_bits(e1000_ethernet_address_high);
        reinterpretable_t<>().e1000_registers->rah.set_av_bit(true);
        for (int i = 0; i < e1000_registers_t::mta_length; i++) {
            reinterpretable_t<>().e1000_registers->mta[i].set_mc_bit_vector_bits(0);
        }

        reinterpretable_t<>().e1000_registers->rctl.set_en_bit(true);
        reinterpretable_t<>().e1000_registers->rctl.set_bam_bit(true);
        reinterpretable_t<>().e1000_registers->rctl.set_secrc_bit(true);

        reinterpretable_t<>().e1000_registers->tctl.set_en_bit(true);
        reinterpretable_t<>().e1000_registers->tctl.set_psp_bit(true);
        reinterpretable_t<>().e1000_registers->tctl.set_ct_bits(e1000_collision_threshold);
        reinterpretable_t<>().e1000_registers->tctl.set_cold_bits(e1000_collision_distance);

        reinterpretable_t<>().e1000_registers->tipg.set_ipgt_bits(e1000_ipg_transmit_time);
        reinterpretable_t<>().e1000_registers->tipg.set_ipgr1_bits(e1000_ipg_receive_time_1);
        reinterpretable_t<>().e1000_registers->tipg.set_ipgr2_bits(e1000_ipg_receive_time_2);

        reinterpretable_t<>().e1000_registers->ims.set_rxt0_bit(true);
    }
}

auto e1000::receive() -> void {
    this->lock.acquire();
    while ((this->receive_descriptors[(reinterpretable_t<>().e1000_registers->rdt.get_rdt_bits() + 1) %
                                      e1000_number_of_descriptors]
                .get_descriptor_done_status_field())) {
        uint32_t index = (reinterpretable_t<>().e1000_registers->rdt.get_rdt_bits() + 1) % e1000_number_of_descriptors;
        auto &receive_descriptor = this->receive_descriptors[index];
        auto *receive_packet_buffer = this->receive_packet_buffers[index];
        receive_packet_buffer->set_length(receive_descriptor.get_length_field());
        networking::ethernet_protocol_t::enqueue(receive_packet_buffer);
        auto *new_receive_packet_buffer = networking::packet_buffer_t::allocate();
        this->receive_packet_buffers[index] = new_receive_packet_buffer;
        receive_descriptor.set_buffer_address_field(new_receive_packet_buffer->get_packet());
        receive_descriptor.set_descriptor_done_status_field(false);
        reinterpretable_t<>().e1000_registers->rdt.set_rdt_bits(index);
    }
    this->lock.release();
}

auto e1000::transmit(networking::packet_buffer_t *packet_buffer_address) -> bool {
    lock.acquire();
    auto index = reinterpretable_t<>().e1000_registers->tdt.get_tdt_bits();
    if (index > e1000_number_of_descriptors) {
        panic("e1000::transmit");
    }
    auto &transmit_descriptor = this->transmit_descriptors[index];
    if (!transmit_descriptor.get_descriptor_done_status_field()) {
        lock.release();
        networking::packet_buffer_t::deallocate(packet_buffer_address);
        return false;
    }
    if (transmit_packet_buffers[index] != nullptr) {
        networking::packet_buffer_t::deallocate(transmit_packet_buffers[index]);
    }
    transmit_descriptor.set_buffer_address_field(packet_buffer_address->get_packet());
    transmit_descriptor.set_length_field(packet_buffer_address->get_length());
    transmit_descriptor.set_end_of_packet_command_field(true);
    transmit_descriptor.set_report_status_command_field(true);
    transmit_packet_buffers[index] = packet_buffer_address;
    reinterpretable_t<>().e1000_registers->tdt.set_tdt_bits(
        (reinterpretable_t<>().e1000_registers->tdt.get_tdt_bits() + 1) % e1000_number_of_descriptors);
    lock.release();
    return true;
}

auto e1000::interrupt() -> void {
    reinterpretable_t<>().e1000_registers->icr.set_rxt0_bit(true);
    this->receive();
}

} // namespace device

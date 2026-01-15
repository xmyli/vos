#include "../include/address_resolution_protocol.hpp"
#include "../include/ethernet_protocol.hpp"
#include "../include/external_types.hpp"
#include "../include/panic.hpp"

namespace networking {

auto address_resolution_protocol_t::receive(packet_buffer_t *packet_buffer_address) -> void {
    address_resolution_protocol_packet_header_t header = {};
    if (!packet_buffer_address->pop_front(as_writable_bytes(span_t(&header, 1)))) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (!header.is_ethernet_protocol()) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (!header.is_internet_protocol()) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (header.get_operation_code_field() != address_resolution_protocol_operation_type_t::request_operation) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (header.get_protocol_address_of_target_field() != internet_protocol_constants::local_internet_protocol_address) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    networking::ethernet_address_t hardware_address_of_sender = header.get_hardware_address_of_sender_field();
    packet_buffer_t::deallocate(packet_buffer_address);
    transmit(address_resolution_protocol_operation_type_t::reply_operation, hardware_address_of_sender,
             header.get_protocol_address_of_sender_field());
}

auto address_resolution_protocol_t::transmit(
    address_resolution_protocol_operation_type_t operation_type,
    networking::ethernet_address_t destination_ethernet_address,
    networking::internet_protocol_address_t destination_internet_protocol_address) -> bool {
    address_resolution_protocol_packet_header_t header = {};
    header.set_operation_code_field(operation_type);
    header.set_hardware_address_of_sender_field(
        networking::ethernet_address_t{ethernet_protocol_constants::local_ethernet_address});
    header.set_protocol_address_of_sender_field(
        networking::internet_protocol_address_t{internet_protocol_constants::local_internet_protocol_address});
    header.set_hardware_address_of_target_field(destination_ethernet_address);
    header.set_protocol_address_of_target_field(destination_internet_protocol_address);

    auto *packet_buffer_address = packet_buffer_t::allocate();
    if (packet_buffer_address == nullptr) {
        return false;
    }
    if (!packet_buffer_address->push_front(as_writable_bytes(span_t(&header, 1)))) {
        panic("address_resolution_protocol::transmit");
        return false;
    }

    ethernet_protocol_t::transmit(packet_buffer_address, protocol_type_t::address_resolution_protocol);
    return true;
}

} // namespace networking

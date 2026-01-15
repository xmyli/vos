#include "../include/ethernet_protocol.hpp"
#include "../include/address_resolution_protocol.hpp"
#include "../include/e1000.hpp"
#include "../include/external_types.hpp"
#include "../include/internet_protocol.hpp"
#include "../include/panic.hpp"
#include "../include/thread_scheduler.hpp"

namespace networking {

auto ethernet_protocol_t::receive(packet_buffer_t *packet_buffer_address) -> void {
    ethernet_packet_header_t ethernet_packet_header = {};
    if (!packet_buffer_address->pop_front(as_writable_bytes(span_t(&ethernet_packet_header, 1)))) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (ethernet_packet_header.get_packet_type_field() == protocol_type_t::internet_protocol) {
        internet_protocol_t::receive(packet_buffer_address);
        return;
    }
    if (ethernet_packet_header.get_packet_type_field() == protocol_type_t::address_resolution_protocol) {
        address_resolution_protocol_t::receive(packet_buffer_address);
        return;
    }
    packet_buffer_t::deallocate(packet_buffer_address);
}

auto ethernet_protocol_t::transmit(packet_buffer_t *packet_buffer_address, protocol_type_t protocol_type) -> void {
    ethernet_packet_header_t ethernet_packet_header = {};
    ethernet_packet_header.set_destination_address_field(
        networking::ethernet_address_t{ethernet_protocol_constants::broadcast_ethernet_address});
    ethernet_packet_header.set_source_address_field(
        networking::ethernet_address_t{ethernet_protocol_constants::local_ethernet_address});
    ethernet_packet_header.set_packet_type_field(protocol_type);
    if (!packet_buffer_address->push_front(as_writable_bytes(span_t(&ethernet_packet_header, 1)))) {
        panic("ethernet_protocol::transmit");
        return;
    }
    device::e1000::get().transmit(packet_buffer_address);
}

auto ethernet_protocol_t::enqueue(packet_buffer_t *packet_buffer_address) -> void {
    ethernet_protocol_t::get().receive_lock.acquire();
    ethernet_protocol_t::get().received_packets_queue.enqueue(packet_buffer_address);
    process::thread_scheduler::get().wake(&ethernet_protocol_t::get().received_packets_queue);
    ethernet_protocol_t::get().receive_lock.release();
}

auto ethernet_protocol_t::handle_data_ingress() -> void {
    while (true) {
        ethernet_protocol_t::get().receive_lock.acquire();
        auto *packet_buffer_address = ethernet_protocol_t::get().received_packets_queue.dequeue();
        while (packet_buffer_address == nullptr) {
            process::thread_scheduler::get().sleep(&ethernet_protocol_t::get().received_packets_queue,
                                                   ethernet_protocol_t::get().receive_lock);
            packet_buffer_address = ethernet_protocol_t::get().received_packets_queue.dequeue();
        }
        ethernet_protocol_t::get().receive_lock.release();
        networking::ethernet_protocol_t::receive(packet_buffer_address);
    }
}

} // namespace networking

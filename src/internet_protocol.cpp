#include "../include/internet_protocol.hpp"
#include "../include/ethernet_protocol.hpp"
#include "../include/external_types.hpp"
#include "../include/integer.hpp"
#include "../include/panic.hpp"
#include "../include/transmission_control_protocol.hpp"
#include "../include/user_datagram_protocol.hpp"

namespace networking {

auto get_internet_checksum(span_t<byte_t> buffer) -> uint16_t {
    uint32_t sum = 0;
    for (size_t offset = 0; offset < buffer.size(); offset += 2) {
        uint16_t value = buffer[offset + 1].get_value();
        value <<= uint8_width;
        value += buffer[offset].get_value();
        sum += value;
    }
    if (buffer.size() % 2 != 0) {
        sum += buffer[buffer.size() - 1].get_value();
    }
    while ((sum >> uint16_width) != 0) {
        sum = (sum & UINT16_MAX) + (sum >> uint16_width);
    }
    return ~sum;
}

auto internet_protocol_t::receive(packet_buffer_t *packet_buffer_address) -> void {
    internet_protocol_packet_header_t header = {};
    if (!packet_buffer_address->pop_front(as_writable_bytes(span_t(&header, 1)))) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    byte_t version_and_internet_header_length{};
    version_and_internet_header_length.set_value(internet_protocol_constants::internet_protocol_version |
                                                 internet_protocol_constants::internet_protocol_header_length);
    if (header.get_version_and_internet_header_length_field() != version_and_internet_header_length) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (get_internet_checksum(as_writable_bytes(span_t(&header, 1))) != 0) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (!header.is_fragment_offset_zero()) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (header.get_destination_address_field() != internet_protocol_constants::local_internet_protocol_address) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (header.get_protocol_field() == protocol_type_t::transmission_control_protocol) {
        transmission_control_protocol_t::receive(packet_buffer_address, header);
        return;
    }
    if (header.get_protocol_field() == protocol_type_t::user_datagram_protocol) {
        user_datagram_protocol_t::receive(packet_buffer_address,
                                          header.get_total_length_field() - sizeof(internet_protocol_packet_header_t),
                                          header.get_source_address_field());
        return;
    }
    packet_buffer_t::deallocate(packet_buffer_address);
}

auto internet_protocol_t::transmit(packet_buffer_t *packet_buffer_address, protocol_type_t protocol_type,
                                   networking::internet_protocol_address_t destination_internet_protocol_address)
    -> void {
    internet_protocol_packet_header_t header = {};
    byte_t version_and_internet_header_length{};
    version_and_internet_header_length.set_value(internet_protocol_constants::internet_protocol_version |
                                                 internet_protocol_constants::internet_protocol_header_length);
    header.set_version_and_internet_header_length_field(version_and_internet_header_length);
    header.set_protocol_field(protocol_type);
    header.set_source_address_field(
        networking::internet_protocol_address_t{internet_protocol_constants::local_internet_protocol_address});
    header.set_destination_address_field(destination_internet_protocol_address);
    header.set_total_length_field(sizeof(header) + packet_buffer_address->get_length());
    header.set_time_to_live_field(internet_protocol_constants::internet_protocol_time_to_live);
    header.set_header_checksum_field(get_internet_checksum(as_writable_bytes(span_t(&header, 1))));
    if (!packet_buffer_address->push_front(as_writable_bytes(span_t(&header, 1)))) {
        panic("internet_protocol::transmit");
        return;
    }
    ethernet_protocol_t::transmit(packet_buffer_address, protocol_type_t::internet_protocol);
}

} // namespace networking

#ifndef NETWORKING_HPP
#define NETWORKING_HPP

#include "memory.hpp"

#include <cstddef>
#include <cstdint>

namespace networking {

enum class protocol_type_t {
    undefined_protocol,
    ethernet_protocol,
    internet_protocol,
    address_resolution_protocol,
    transmission_control_protocol,
    user_datagram_protocol
};

enum port_number_t : uint16_t;

namespace packet_buffer_constants {
    constexpr size_t packet_buffer_size = 2 * memory::page_size - memory::page_size / 2;
    constexpr size_t packet_buffer_initial_offset = memory::page_size / 2;
} // namespace packet_buffer_constants

enum ethernet_address_t : uint64_t;

namespace ethernet_protocol_constants {
    constexpr size_t ethernet_address_size = 6;
    constexpr uint64_t local_ethernet_address = 0x563412005452;
    constexpr uint64_t broadcast_ethernet_address = 0xffffffffffff;
} // namespace ethernet_protocol_constants

enum class address_resolution_protocol_operation_type_t { undefined_operation, request_operation, reply_operation };

enum internet_protocol_address_t : uint32_t;

namespace internet_protocol_constants {
    constexpr uint8_t internet_protocol_version = 4 << 4;
    constexpr uint8_t internet_protocol_header_length = 20 >> 2;
    constexpr uint8_t internet_protocol_time_to_live = 100;
    constexpr uint32_t local_internet_protocol_address = 167772687;
} // namespace internet_protocol_constants

namespace transmission_control_protocol_constants {
    constexpr size_t maximum_number_of_connections = 256;
    constexpr size_t maximum_payload_size = 1024;
    constexpr uint16_t default_port_number = 32768;
    constexpr uint32_t initial_sequence_number = 12345;
    constexpr uint16_t initial_window_size = 65535;
    constexpr uint64_t retransmission_timeout_duration = 64;
    constexpr int maximum_number_of_retransmissions = 8;
} // namespace transmission_control_protocol_constants

namespace user_datagram_protocol_constants {
    constexpr size_t maximum_number_of_connections = 256;
    constexpr size_t maximum_payload_size = 1024;
    constexpr uint16_t default_port_number = 32768;
} // namespace user_datagram_protocol_constants

namespace socket_interface_constants {
    constexpr int maximum_number_of_sockets = 64;
    constexpr size_t socket_queue_size = memory::page_size;
} // namespace socket_interface_constants

} // namespace networking

#endif

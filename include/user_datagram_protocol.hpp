#ifndef USER_DATAGRAM_PROTOCOL_HPP
#define USER_DATAGRAM_PROTOCOL_HPP

#include "socket_interface.hpp"
#include "spin_lock.hpp"

namespace networking {

struct user_datagram_protocol_packet_configuration_t {
    networking::port_number_t source_port_number;
    networking::port_number_t destination_port_number;
    networking::internet_protocol_address_t destination_internet_protocol_address;
};

struct user_datagram_protocol_connection_t {
    synchronization::spin_lock lock;

    networking::port_number_t source_port_number = {};

    request_queue_t receive_request_addresses;
    request_queue_t transmit_request_addresses;

    packet_buffer_queue_t received_packets;
};

class user_datagram_protocol_t {
public:
    static auto receive(packet_buffer_t *packet_buffer_address, uint16_t length,
                        networking::internet_protocol_address_t source_internet_protocol_address) -> void;
    static auto transmit(packet_buffer_t *packet_buffer_address,
                         user_datagram_protocol_packet_configuration_t packet_configuration) -> void;
    static auto request(request_t *request_address) -> void;
    static auto handle_transmit_requests() -> void;

    user_datagram_protocol_t(const user_datagram_protocol_t &) = delete;
    auto operator=(const user_datagram_protocol_t &) -> user_datagram_protocol_t & = delete;
    user_datagram_protocol_t(user_datagram_protocol_t &&) = delete;
    auto operator=(user_datagram_protocol_t &&) -> user_datagram_protocol_t & = delete;

private:
    array_t<user_datagram_protocol_connection_t, user_datagram_protocol_constants::maximum_number_of_connections>
        connections;

    static auto get() -> user_datagram_protocol_t & {
        static user_datagram_protocol_t instance;
        return instance;
    }
    user_datagram_protocol_t() = default;
    ~user_datagram_protocol_t() = default;
};

} // namespace networking

#endif

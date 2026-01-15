#ifndef ETHERNET_PROTOCOL_HPP
#define ETHERNET_PROTOCOL_HPP

#include "packet_buffer.hpp"

namespace networking {

class ethernet_protocol_t {
public:
    static auto receive(packet_buffer_t *packet_buffer_address) -> void;
    static auto transmit(packet_buffer_t *packet_buffer_address, protocol_type_t protocol_type) -> void;
    static auto enqueue(packet_buffer_t *packet_buffer_address) -> void;

    static auto handle_data_ingress() -> void;

    ethernet_protocol_t(const ethernet_protocol_t &) = delete;
    auto operator=(const ethernet_protocol_t &) -> ethernet_protocol_t & = delete;
    ethernet_protocol_t(ethernet_protocol_t &&) = delete;
    auto operator=(ethernet_protocol_t &&) -> ethernet_protocol_t & = delete;

private:
    synchronization::spin_lock receive_lock;
    packet_buffer_queue_t received_packets_queue;

    static auto get() -> ethernet_protocol_t & {
        static ethernet_protocol_t instance;
        return instance;
    }
    ethernet_protocol_t() = default;
    ~ethernet_protocol_t() = default;
};

} // namespace networking

#endif

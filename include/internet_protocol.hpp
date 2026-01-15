#ifndef INTERNET_PROTOCOL_HPP
#define INTERNET_PROTOCOL_HPP

#include "packet_buffer.hpp"

namespace networking {

class internet_protocol_t {
public:
    static auto receive(packet_buffer_t *packet_buffer_address) -> void;
    static auto transmit(packet_buffer_t *packet_buffer_address, protocol_type_t protocol_type,
                         networking::internet_protocol_address_t destination_internet_protocol_address) -> void;
};

} // namespace networking

#endif

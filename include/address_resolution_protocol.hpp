#ifndef ADDRESS_RESOLUTION_PROTOCOL_HPP
#define ADDRESS_RESOLUTION_PROTOCOL_HPP

#include "packet_buffer.hpp"

namespace networking {

class address_resolution_protocol_t {
public:
    static auto receive(packet_buffer_t *packet_buffer_address) -> void;
    static auto transmit(address_resolution_protocol_operation_type_t operation_type,
                         ethernet_address_t destination_ethernet_address,
                         internet_protocol_address_t destination_internet_protocol_address) -> bool;
};

} // namespace networking

#endif

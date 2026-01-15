#ifndef E1000_HPP
#define E1000_HPP

#include "../lib/array.hpp"
#include "external_types.hpp"
#include "packet_buffer.hpp"
#include "spin_lock.hpp"

namespace device {

class e1000 {
public:
    static auto get() -> e1000 & {
        static e1000 instance;
        return instance;
    }

    static auto initialize() -> void;

    auto receive() -> void;
    auto transmit(networking::packet_buffer_t *packet_buffer_address) -> bool;
    auto interrupt() -> void;

    e1000(const e1000 &) = delete;
    auto operator=(const e1000 &) -> e1000 & = delete;
    e1000(e1000 &&) = delete;
    auto operator=(e1000 &&) -> e1000 & = delete;

private:
    synchronization::spin_lock lock;

    alignas(
        e1000_descriptor_alignment) array_t<receive_descriptor_t, e1000_number_of_descriptors> receive_descriptors = {};

    array_t<networking::packet_buffer_t *, e1000_number_of_descriptors> receive_packet_buffers = {};

    alignas(e1000_descriptor_alignment)
        array_t<transmit_descriptor_t, e1000_number_of_descriptors> transmit_descriptors = {};

    array_t<networking::packet_buffer_t *, e1000_number_of_descriptors> transmit_packet_buffers = {};

    e1000() = default;
    ~e1000() = default;
};

} // namespace device

#endif

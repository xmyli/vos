#ifndef GICV3_HPP
#define GICV3_HPP

#include "../lib/array.hpp"
#include "device.hpp"
#include "integer.hpp"

namespace device {

class gicv3 {
public:
    static auto get() -> gicv3 & {
        static gicv3 instance;
        return instance;
    }

    static auto initialize() -> void;
    static auto get_interrupt_number() -> uint64_t;
    static void set_interrupt_number(uint64_t interrupt_number);

    gicv3(const gicv3 &) = delete;
    auto operator=(const gicv3 &) -> gicv3 & = delete;
    gicv3(gicv3 &&) = delete;
    auto operator=(gicv3 &&) -> gicv3 & = delete;

private:
    gicv3() = default;
    ~gicv3() = default;
};

} // namespace device

#endif

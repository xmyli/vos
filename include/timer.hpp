#ifndef TIMER_HPP
#define TIMER_HPP

#include "spin_lock.hpp"

#include <cstdint>

namespace device {

class timer {
public:
    static auto get() -> timer & {
        static timer instance;
        return instance;
    }

    static auto initialize() -> void;

    [[nodiscard]] auto now() const -> uint64_t;
    auto interrupt() -> void;

    timer(const timer &) = delete;
    auto operator=(const timer &) -> timer & = delete;
    timer(timer &&) = delete;
    auto operator=(timer &&) -> timer & = delete;

private:
    synchronization::spin_lock lock;
    uint64_t time = 0;

    static void reload();

    timer() = default;
    ~timer() = default;
};

} // namespace device

#endif

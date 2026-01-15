#ifndef PL011_HPP
#define PL011_HPP

#include "../lib/array.hpp"
#include "../lib/printf.hpp"
#include "device.hpp"
#include "spin_lock.hpp"

namespace device {

class pl011 {
public:
    static auto get() -> pl011 & {
        static pl011 instance;
        return instance;
    }

    static auto initialize() -> void;

    static auto printf_unsafe(const char *str) -> void {
        lib::printf(
            +[](char value) {
                byte_t byte{};
                byte.set_value(value);
                pl011::write(byte);
            },
            str);
    }

    template <typename... Args> static auto printf_unsafe(const char *str, Args... args) -> void {
        lib::printf(
            +[](char value) {
                byte_t byte{};
                byte.set_value(value);
                pl011::write(byte);
            },
            str, args...);
    }

    static auto printf(const char *str) -> void {
        pl011::get().printf_lock.acquire();
        lib::printf(
            +[](char value) {
                byte_t byte{};
                byte.set_value(value);
                pl011::write(byte);
            },
            str);
        pl011::get().printf_lock.release();
    }

    template <typename... Args> static auto printf(const char *str, Args... args) -> void {
        pl011::get().printf_lock.acquire();
        lib::printf(
            +[](char value) {
                byte_t byte{};
                byte.set_value(value);
                pl011::write(byte);
            },
            str, args...);
        pl011::get().printf_lock.release();
    }

    auto read_receiver_buffer() -> byte_t;
    auto write_receiver_buffer(byte_t value) -> void;
    auto read_transmitter_buffer() -> byte_t;
    auto write_transmitter_buffer(byte_t value) -> void;

    auto flush_receiver_buffer() -> void;
    auto flush_transmitter_buffer() -> void;

    [[nodiscard]] auto is_initialized() const -> bool;

    auto interrupt() -> void;

    pl011(const pl011 &) = delete;
    auto operator=(const pl011 &) -> pl011 & = delete;
    pl011(pl011 &&) = delete;
    auto operator=(pl011 &&) -> pl011 & = delete;

private:
    array_t<byte_t, pl011_buffer_size> receiver_ring_buffer{};
    size_t receiver_ring_buffer_read_index = 0;
    size_t receiver_ring_buffer_write_index = 0;
    synchronization::spin_lock receiver_ring_buffer_lock;

    array_t<byte_t, pl011_buffer_size> transmitter_ring_buffer{};
    size_t transmitter_ring_buffer_read_index = 0;
    size_t transmitter_ring_buffer_write_index = 0;
    synchronization::spin_lock transmitter_ring_buffer_lock;

    synchronization::spin_lock flush_lock{};

    synchronization::spin_lock printf_lock{};

    bool initialized = false;

    static auto read() -> byte_t;
    static auto write(byte_t value) -> void;

    pl011() = default;
    ~pl011() = default;
};

} // namespace device

#endif

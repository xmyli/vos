#include "../include/pl011.hpp"
#include "../include/device.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/thread_scheduler.hpp"

namespace device {

auto pl011::initialize() -> void {
    if (architecture::get_core_number() == 0) {
        reinterpretable_t<>().pl011_registers->uartlcr_h.set_fen_bit(true);
        reinterpretable_t<>().pl011_registers->uartlcr_h.set_wlen_bits(~0);
        reinterpretable_t<>().pl011_registers->uartcr.set_uarten_bit(true);
        reinterpretable_t<>().pl011_registers->uartcr.set_txe_bit(true);
        reinterpretable_t<>().pl011_registers->uartcr.set_rxe_bit(true);
        reinterpretable_t<>().pl011_registers->uartimsc.set_rxim_bit(true);
        reinterpretable_t<>().pl011_registers->uartimsc.set_txim_bit(true);
        pl011::get().initialized = true;
    }
}

auto pl011::read() -> byte_t {
    if (reinterpretable_t<>().pl011_registers->uartfr.get_rxfe_bit()) {
        return byte_t{};
    }
    byte_t value{};
    value.set_value(reinterpretable_t<>().pl011_registers->uartdr.get_data_bits());
    return value;
}

auto pl011::write(byte_t value) -> void {
    while (reinterpretable_t<>().pl011_registers->uartfr.get_txff_bit()) {
        ;
    }
    reinterpretable_t<>().pl011_registers->uartdr.set_data_bits(value.get_value());
};

auto pl011::read_receiver_buffer() -> byte_t {
    receiver_ring_buffer_lock.acquire();
    while (receiver_ring_buffer_read_index == receiver_ring_buffer_write_index) {
        process::thread_scheduler::get().sleep(this, receiver_ring_buffer_lock);
    }
    auto value = receiver_ring_buffer[receiver_ring_buffer_read_index];
    receiver_ring_buffer_read_index = (receiver_ring_buffer_read_index + 1) % pl011_buffer_size;
    receiver_ring_buffer_lock.release();
    return value;
}

auto pl011::write_receiver_buffer(byte_t value) -> void {
    receiver_ring_buffer_lock.acquire();
    if ((receiver_ring_buffer_write_index + 1) % pl011_buffer_size == receiver_ring_buffer_read_index) {
        receiver_ring_buffer_read_index = (receiver_ring_buffer_read_index + 1) % pl011_buffer_size;
    } else {
        receiver_ring_buffer[receiver_ring_buffer_write_index] = value;
    }
    receiver_ring_buffer_write_index = (receiver_ring_buffer_write_index + 1) % pl011_buffer_size;
    process::thread_scheduler::get().wake(this);
    receiver_ring_buffer_lock.release();
}

auto pl011::read_transmitter_buffer() -> byte_t {
    transmitter_ring_buffer_lock.acquire();
    if (transmitter_ring_buffer_read_index == transmitter_ring_buffer_write_index) {
        transmitter_ring_buffer_lock.release();
        return byte_t{};
    }
    auto value = transmitter_ring_buffer[transmitter_ring_buffer_read_index];
    transmitter_ring_buffer_read_index = (transmitter_ring_buffer_read_index + 1) % pl011_buffer_size;
    process::thread_scheduler::get().wake(this);
    transmitter_ring_buffer_lock.release();
    return value;
}

auto pl011::write_transmitter_buffer(byte_t value) -> void {
    transmitter_ring_buffer_lock.acquire();
    while ((transmitter_ring_buffer_write_index + 1) % pl011_buffer_size == transmitter_ring_buffer_read_index) {
        process::thread_scheduler::get().sleep(this, transmitter_ring_buffer_lock);
    }
    transmitter_ring_buffer[transmitter_ring_buffer_write_index] = value;
    transmitter_ring_buffer_write_index = (transmitter_ring_buffer_write_index + 1) % pl011_buffer_size;
    transmitter_ring_buffer_lock.release();
    if (value.is_zero()) {
        flush_transmitter_buffer();
    }
}

auto pl011::flush_receiver_buffer() -> void {
    flush_lock.acquire();
    while (true) {
        auto value = pl011::get().read();
        if (!value.is_zero()) {
            write_receiver_buffer(value);
        } else {
            break;
        }
    }
    flush_lock.release();
}

auto pl011::flush_transmitter_buffer() -> void {
    flush_lock.acquire();
    auto value = read_transmitter_buffer();
    while (!value.is_zero()) {
        write(value);
        value = read_transmitter_buffer();
    }
    flush_lock.release();
}

auto pl011::is_initialized() const -> bool {
    return this->initialized;
}

void pl011::interrupt() {
    flush_receiver_buffer();
    flush_transmitter_buffer();
    reinterpretable_t<>().pl011_registers->uarticr.set_rxic_bit(true);
    reinterpretable_t<>().pl011_registers->uarticr.set_txic_bit(true);
}

} // namespace device

#include "../include/timer.hpp"
#include "../include/architecture.hpp"
#include "../include/device.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/thread_scheduler.hpp"

#include <cstdint>

namespace device {

inline auto read_cntv_ctl_el0() -> uint64_t {
    uint64_t value = 0;
    asm volatile("mrs %0, cntv_ctl_el0" : "=r"(value));
    return value;
}

inline void write_cntv_ctl_el0(uint64_t value) {
    asm volatile("msr cntv_ctl_el0, %0" : : "r"(value));
}

inline auto read_cntfrq_el0() -> uint64_t {
    uint64_t value = 0;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(value));
    return value;
}

inline void write_cntv_tval_el0(uint64_t value) {
    asm volatile("msr cntv_tval_el0, %0" : : "r"(value));
}

void disable() {
    architecture::cntv_ctl_el0 cntv_ctl_el0_value{};
    cntv_ctl_el0_value.value = read_cntv_ctl_el0();
    cntv_ctl_el0_value.enable = 0;
    cntv_ctl_el0_value.imask = 1;
    write_cntv_ctl_el0(cntv_ctl_el0_value.value);
}

void set_interval() {
    uint64_t cntv_tval_el0_value =
        process::thread_scheduler_constants::time_slice_length_in_microseconds * (read_cntfrq_el0() / timer_prescaler);
    write_cntv_tval_el0(cntv_tval_el0_value);
}

void enable() {
    architecture::cntv_ctl_el0 cntv_ctl_el0_value{};
    cntv_ctl_el0_value.value = read_cntv_ctl_el0();
    cntv_ctl_el0_value.enable = 1;
    cntv_ctl_el0_value.imask = 0;
    write_cntv_ctl_el0(cntv_ctl_el0_value.value);
}

void timer::reload() {
    disable();
    set_interval();
    enable();
}

auto timer::initialize() -> void {
    timer::get().reload();
}

auto timer::now() const -> uint64_t {
    return this->time / architecture::number_of_cores;
}

auto timer::interrupt() -> void {
    timer::get().reload();
    this->lock.acquire();
    this->time += 1;
    this->lock.release();
    process::thread_scheduler::get().wake(this);
    process::thread_scheduler::get().yield();
}

} // namespace device

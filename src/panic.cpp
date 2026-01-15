#include "../include/panic.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/pl011.hpp"
#include "../include/thread_scheduler.hpp"

auto panic(const char *message) -> void {
    if (device::pl011::get().is_initialized()) {
        device::pl011::printf("[%d] KERNEL PANIC: %s (id=%d)\n", architecture::get_core_number(), message,
                              process::thread_scheduler::get().get_current_process_id());
    }
    for (;;) {
        asm volatile("nop");
    }
}

auto panic_unsafe(const char *message) -> void {
    if (device::pl011::get().is_initialized()) {
        device::pl011::printf_unsafe("[%d] KERNEL PANIC: %s (id=%d)\n", architecture::get_core_number(), message,
                                     process::thread_scheduler::get().get_current_process_id());
    }
    for (;;) {
        asm volatile("nop");
    }
}

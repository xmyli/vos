#include "../include/buddy_allocator.hpp"
#include "../include/e1000.hpp"
#include "../include/gicv3.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/thread_scheduler.hpp"
#include "../include/timer.hpp"
#include "../include/virtio_blk.hpp"
#include "../include/virtual_memory.hpp"

extern "C" auto main(void) -> int {
    memory::virtual_memory::initialize();
    device::pl011::initialize();
    process::exception_handler::initialize();
    memory::buddy_allocator::initialize();
    device::gicv3::initialize();
    process::thread_scheduler::initialize();
    device::timer::initialize();
    device::virtio_blk::initialize();
    device::e1000::initialize();

    if (architecture::get_core_number() == 0) {
        architecture::wake_secondary_cores();
    }

    process::thread_scheduler::get().schedule();
}

#include "../include/sleep_lock.hpp"
#include "../include/thread_scheduler.hpp"

namespace synchronization {

void sleep_lock::acquire() {
    lock.acquire();
    while (locked) {
        process::thread_scheduler::get().sleep(this, lock);
    }
    locked = true;
    lock.release();
}

void sleep_lock::release() {
    lock.acquire();
    locked = false;
    process::thread_scheduler::get().wake(this);
    lock.release();
}

} // namespace synchronization

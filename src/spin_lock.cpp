#include "../include/spin_lock.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/panic.hpp"
#include "../include/synchronization.hpp"

namespace synchronization {

void spin_lock::acquire() {
    if (this->locked && cpu_id == architecture::get_core_number()) {
        panic_unsafe("acquire");
    }
    int number_of_tries = 0;
    bool printed = false;
    while (__atomic_test_and_set(&this->locked, __ATOMIC_ACQUIRE)) {
        number_of_tries += 1;
        if (number_of_tries > deadlock_threshold && !printed) {
            panic("acquire, deadlock");
            printed = true;
        }
    }
    this->cpu_id = architecture::get_core_number();
}

void spin_lock::release() {
    if (!this->locked) {
        panic("release");
    }
    this->cpu_id = -1;
    __atomic_clear(&this->locked, __ATOMIC_RELEASE);
}

} // namespace synchronization

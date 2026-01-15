#include <cstdint>

__extension__ using guard_t = uint64_t __attribute__((mode(__DI__)));

extern "C" auto __cxa_guard_acquire(guard_t *guard) -> bool {
    return __atomic_exchange_n(guard, 1, __ATOMIC_ACQUIRE) == 0;
}

extern "C" void __cxa_guard_release(guard_t *guard) {
    __atomic_store_n(guard, 1, __ATOMIC_RELEASE);
}

extern "C" void __cxa_guard_abort(guard_t *guard) {
    __atomic_store_n(guard, 0, __ATOMIC_RELEASE);
}

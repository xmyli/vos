#include "../include/multiprocessing.hpp"
#include "../include/architecture.hpp"
#include "../include/memory.hpp"

namespace architecture {

auto get_core_number() -> int {
    mpidr_el1 mpidr_el1_value{};
    asm volatile("mrs x0, mpidr_el1" : "=r"(mpidr_el1_value.value));
    return mpidr_el1_value.aff0;
}

auto __attribute__((noinline)) psci_call(uint64_t /*_*/, uint64_t /*_*/, uint64_t /*_*/, uint64_t /*_*/) -> void {
    asm volatile("hvc #0x0");
}

auto wake_secondary_cores() -> void {
    for (int core_number = 1; core_number < number_of_cores; core_number++) {
        constexpr uint64_t function = 0xc4000003;
        psci_call(function, core_number, memory::kernel_address_space_constants::physical_address_begin, 0);
    }
}

} // namespace architecture

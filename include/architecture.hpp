#ifndef ARCHITECTURE_HPP
#define ARCHITECTURE_HPP

#include <cstddef>
#include <cstdint>
#include <sys/cdefs.h>

namespace architecture {

constexpr int number_of_cores = 4;
constexpr int svc_exception_code = 0b10101;

union cntv_ctl_el0 {
    struct {
        uint64_t enable : 1;
        uint64_t imask : 1;
        uint64_t istatus : 1;
        uint64_t res0 : 61;
    };
    uint64_t value;
} __attribute((packed));
static_assert(sizeof(cntv_ctl_el0) == sizeof(uint64_t));

union esr_el1 {
    struct {
        uint64_t iss : 25;
        uint64_t il : 1;
        uint64_t ec : 6;
        uint64_t iss2 : 24;
        uint64_t res0 : 8;
    };
    uint64_t value;
} __attribute((packed));
static_assert(sizeof(esr_el1) == sizeof(uint64_t));

union mpidr_el1 {
    struct {
        uint64_t aff0 : 8;
        uint64_t aff1 : 8;
        uint64_t aff2 : 8;
        uint64_t mt : 1;
        uint64_t res0_1 : 5;
        uint64_t u : 1;
        uint64_t res1 : 1;
        uint64_t aff3 : 8;
        uint64_t res0_2 : 24;
    };
    uint64_t value;
} __attribute((packed));
static_assert(sizeof(mpidr_el1) == sizeof(uint64_t));

} // namespace architecture

#endif

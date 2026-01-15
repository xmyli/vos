#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "memory.hpp"

#include <cstddef>
#include <cstdint>

namespace process {

namespace thread_scheduler_constants {
    constexpr uint64_t time_slice_length_in_microseconds = 100000; // 100ms
    constexpr int maximum_number_of_processes = 32;
    constexpr int maximum_number_of_arguments = 64;
} // namespace thread_scheduler_constants

namespace exception_handler_constants::system_call_numbers {
    constexpr int exit = 1;
    constexpr int read = 2;
    constexpr int write = 3;
    constexpr int exec = 4;
    constexpr int fork = 5;
    constexpr int pipe = 6;
    constexpr int yield = 7;
    constexpr int wait = 8;
    constexpr int open = 9;
    constexpr int close = 10;
    constexpr int copy = 11;
    constexpr int socket = 12;
    constexpr int bind = 13;
    constexpr int connect = 14;
    constexpr int listen = 15;
    constexpr int accept = 16;
    constexpr int receive = 17;
    constexpr int transmit = 18;
} // namespace exception_handler_constants::system_call_numbers

namespace pipe_interface_constants {
    constexpr int maximum_number_of_pipes = 64;
}

} // namespace process

#endif

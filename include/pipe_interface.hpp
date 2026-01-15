#ifndef PIPE_INTERFACE_HPP
#define PIPE_INTERFACE_HPP

#include "../lib/array.hpp"
#include "integer.hpp"
#include "memory.hpp"
#include "process.hpp"
#include "spin_lock.hpp"

#include <cstdint>

namespace process {

class pipe_t {
public:
    auto read() -> byte_t;
    auto write(byte_t value) -> void;
    auto open_reader() -> void;
    auto open_writer() -> void;
    auto close_reader() -> void;
    auto close_writer() -> void;
    auto status() -> bool;

private:
    synchronization::spin_lock lock;
    array_t<byte_t, memory::page_size> *buffer = nullptr;
    size_t read_pointer = 0;
    size_t write_pointer = 0;
    int readers_count = 0;
    int writers_count = 0;
};

class pipe_interface {
public:
    auto get() -> int;
    auto read(int pipe_index) -> byte_t;
    auto write(int pipe_index, byte_t value) -> void;
    auto open_reader(int pipe_index) -> void;
    auto open_writer(int pipe_index) -> void;
    auto close_reader(int pipe_index) -> void;
    auto close_writer(int pipe_index) -> void;

private:
    synchronization::spin_lock lock;
    array_t<pipe_t, pipe_interface_constants::maximum_number_of_pipes> pipes;
};

} // namespace process

#endif

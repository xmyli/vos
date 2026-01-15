#include "../include/pipe_interface.hpp"
#include "../include/buddy_allocator.hpp"
#include "../include/thread_scheduler.hpp"
#include "../include/virtual_memory.hpp"

namespace process {

auto pipe_t::read() -> byte_t {
    lock.acquire();
    while (read_pointer == write_pointer) {
        if (this->writers_count < 1) {
            lock.release();
            return byte_t{};
        }
        thread_scheduler::get().sleep(this, lock);
    }
    auto value = (*buffer)[read_pointer];
    read_pointer = (read_pointer + 1) % memory::page_size;
    lock.release();
    thread_scheduler::get().wake(this);
    return value;
}

auto pipe_t::write(byte_t value) -> void {
    lock.acquire();
    if ((write_pointer + 1) % memory::page_size == read_pointer) {
        if (this->readers_count < 1) {
            lock.release();
            return;
        }
        thread_scheduler::get().sleep(this, lock);
    }
    (*buffer)[write_pointer] = value;
    write_pointer = (write_pointer + 1) % memory::page_size;
    thread_scheduler::get().wake(this);
    lock.release();
}

auto pipe_t::open_reader() -> void {
    lock.acquire();
    if (this->readers_count == 0 && this->writers_count == 0) {
        this->buffer = memory::buddy_allocator::get().allocate<array_t<byte_t, memory::page_size>>(0);
        this->read_pointer = 0;
        this->write_pointer = 0;
    }
    this->readers_count += 1;
    lock.release();
}

auto pipe_t::open_writer() -> void {
    lock.acquire();
    if (this->readers_count == 0 && this->writers_count == 0) {
        this->buffer = memory::buddy_allocator::get().allocate<array_t<byte_t, memory::page_size>>(0);
        this->read_pointer = 0;
        this->write_pointer = 0;
    }
    this->writers_count += 1;
    lock.release();
}

auto pipe_t::close_reader() -> void {
    lock.acquire();
    this->readers_count -= 1;
    if (this->readers_count == 0 && this->writers_count == 0) {
        memory::buddy_allocator::get().deallocate(this->buffer);
        this->read_pointer = 0;
        this->write_pointer = 0;
    }
    lock.release();
    thread_scheduler::get().wake(this);
}

auto pipe_t::close_writer() -> void {
    lock.acquire();
    this->writers_count -= 1;
    if (this->readers_count == 0 && this->writers_count == 0) {
        memory::buddy_allocator::get().deallocate(this->buffer);
        this->read_pointer = 0;
        this->write_pointer = 0;
    }
    lock.release();
    thread_scheduler::get().wake(this);
}

auto pipe_t::status() -> bool {
    lock.acquire();
    auto result = this->buffer != nullptr;
    lock.release();
    return result;
}

auto pipe_interface::get() -> int {
    this->lock.acquire();
    for (int i = 0; i < pipe_interface_constants::maximum_number_of_pipes; i++) {
        auto &pipe = this->pipes[i];
        if (!pipe.status()) {
            this->lock.release();
            return i;
        }
    }
    this->lock.release();
    return -1;
}

auto pipe_interface::read(int pipe_index) -> byte_t {
    auto value = this->pipes[pipe_index].read();
    return value;
}

auto pipe_interface::write(int pipe_index, byte_t value) -> void {
    this->pipes[pipe_index].write(value);
}

auto pipe_interface::open_reader(int pipe_index) -> void {
    this->pipes[pipe_index].open_reader();
}

auto pipe_interface::open_writer(int pipe_index) -> void {
    this->pipes[pipe_index].open_writer();
}

auto pipe_interface::close_reader(int pipe_index) -> void {
    this->pipes[pipe_index].close_reader();
}

auto pipe_interface::close_writer(int pipe_index) -> void {
    this->pipes[pipe_index].close_writer();
}

} // namespace process

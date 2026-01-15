#ifndef THREAD_SCHEDULER_HPP
#define THREAD_SCHEDULER_HPP

#include "architecture.hpp"
#include "exception_handler.hpp"
#include "external_types.hpp"
#include "memory.hpp"
#include "path_name.hpp"
#include "process.hpp"
#include "sleep_lock.hpp"
#include "spin_lock.hpp"
#include "virtual_memory.hpp"

#include <cstddef>
#include <cstdint>

namespace process {

enum class process_status { unused, reserved, runnable, running, sleeping, zombie, killed };

struct section_detail_t {
    uintptr_t virtual_address = 0;
    size_t number_of_pages = 0;
};

struct kernel_stack_t {
    array_t<byte_t, memory::kernel_address_space_constants::stack_size - sizeof(exception_frame_t)> bytes{};
    exception_frame_t exception_frame;
};
static_assert(sizeof(kernel_stack_t) == memory::kernel_address_space_constants::stack_size);

struct process {
    synchronization::spin_lock lock;
    process_status status = process_status::unused;
    int parent_id = 0;
    memory::page_table_t *level_0_page_table = nullptr;
    array_t<section_detail_t, memory::page_size / sizeof(section_detail_t)> *section_details = nullptr;
    kernel_stack_t *kernel_stack_begin = nullptr;
    context kernel_mode_state;
    exception_frame_t *user_mode_state = nullptr;
    size_t text_size = 0;
    size_t heap_size = 0;
    size_t stack_size = 0;
    void *condition = nullptr;
};

class thread_scheduler {
public:
    static auto get() -> thread_scheduler & {
        static thread_scheduler instance;
        return instance;
    }

    static auto initialize() -> void;

    auto fork() -> int;
    auto wait() -> int;
    auto exit() -> void;
    auto exec(file::path_name_t executable_file_path, span_t<array_t<byte_t, memory::page_size> *> arguments) -> bool;

    void schedule();
    void yield();

    void sleep(void *condition, synchronization::spin_lock &lock);
    void wake(void *condition);

    auto get_current_process() -> process &;
    auto get_current_process_id() -> int;

    thread_scheduler(const thread_scheduler &) = delete;
    auto operator=(const thread_scheduler &) -> thread_scheduler & = delete;
    thread_scheduler(thread_scheduler &&) = delete;
    auto operator=(thread_scheduler &&) -> thread_scheduler & = delete;

private:
    array_t<context, architecture::number_of_cores> scheduler_thread_contexts;
    array_t<int, architecture::number_of_cores> current_process_indices = {};
    array_t<process, thread_scheduler_constants::maximum_number_of_processes> processes;

    synchronization::spin_lock lock;

    thread_scheduler() = default;
    ~thread_scheduler() = default;
};

} // namespace process

#endif

#include "../include/thread_scheduler.hpp"
#include "../include/buddy_allocator.hpp"
#include "../include/descriptor_interface.hpp"
#include "../include/ethernet_protocol.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/panic.hpp"
#include "../include/process.hpp"
#include "../include/socket_interface.hpp"
#include "../include/timer.hpp"
#include "../include/transmission_control_protocol.hpp"
#include "../include/virtio_blk.hpp"
#include "../include/virtual_memory.hpp"
#include "../lib/span.hpp"

extern "C" void return_from_exception(void *exception_frame_pointer);

namespace process {
using memory::page_table_t;

void deallocate_address_space(memory::page_table_t *level_0_page_table) {
    memory::buddy_allocator::get().deallocate(
        reinterpretable_t<uintptr_t>(level_0_page_table, memory::user_address_space_constants::stack_begin).to<void>());
    level_0_page_table->unmap(memory::user_address_space_constants::stack_begin,
                              memory::user_address_space_constants::stack_size);
    level_0_page_table->clear();
    memory::buddy_allocator::get().deallocate(level_0_page_table);
}

void process_init() {
    auto *exception_frame_address = thread_scheduler::get().get_current_process().user_mode_state;

    thread_scheduler::get().get_current_process().lock.release();

    file::descriptor_interface::get().recover();

    if (thread_scheduler::get().get_current_process_id() == 2) {
        networking::ethernet_protocol_t::handle_data_ingress();
    }

    if (thread_scheduler::get().get_current_process_id() == 3) {
        networking::socket_interface::get().handle_data_egress();
    }

    if (thread_scheduler::get().get_current_process_id() == 4) {
        synchronization::spin_lock lock;
        uint64_t previous_time = 0;
        while (true) {
            auto current_time = device::timer::get().now();
            if (current_time - previous_time >
                networking::transmission_control_protocol_constants::retransmission_timeout_duration) {
                previous_time = current_time;
                networking::transmission_control_protocol_t::timeout();
            }
            lock.acquire();
            thread_scheduler::get().sleep(&device::timer::get(), lock);
            lock.release();
        }
    }

    return_from_exception(exception_frame_address);
}

auto create_init_address_space(void (*image_address)(), size_t image_size) -> memory::page_table_t * {
    auto *level_0_page_table = memory::buddy_allocator::get().allocate<memory::page_table_t>(0);
    for (size_t i = 0; i < sizeof(memory::page_table_t) / sizeof(memory::page_table_descriptor_t); i++) {
        level_0_page_table->set_descriptor_at_index(i, {});
    }
    level_0_page_table->map(memory::user_address_space_constants::image_begin, memory::page_table_t::type_t::user,
                            image_address, image_size);
    auto *new_stack_pages =
        memory::buddy_allocator::get().allocate<void>(memory::user_address_space_constants::stack_size_order);
    level_0_page_table->map(memory::user_address_space_constants::stack_begin, memory::page_table_t::type_t::user,
                            new_stack_pages, memory::user_address_space_constants::stack_size);
    return level_0_page_table;
}

auto create_init_process(void (*image_address)(), size_t image_size) -> process {
    auto *section_detail_page =
        memory::buddy_allocator::get()
            .allocate<array_t<section_detail_t, memory::page_size / sizeof(section_detail_t)>>(0);
    for (size_t i = 0; i < memory::page_size / sizeof(section_detail_t); i++) {
        (*section_detail_page)[i] = section_detail_t();
    }
    auto init_text_number_of_pages =
        image_size % memory::page_size == 0 ? image_size / memory::page_size : image_size / memory::page_size + 1;
    (*section_detail_page)[0] =
        section_detail_t{memory::user_address_space_constants::image_begin, init_text_number_of_pages};
    (*section_detail_page)[1] = section_detail_t{memory::user_address_space_constants::stack_begin,
                                                 1 << memory::user_address_space_constants::stack_size_order};

    auto *kernel_stack_begin = memory::buddy_allocator::get().allocate<kernel_stack_t>(
        memory::kernel_address_space_constants::stack_size_order);

    auto *exception_frame_address = &kernel_stack_begin->exception_frame;
    *exception_frame_address = exception_frame_t();

    context initial_context = {};
    initial_context.set_stack_pointer(exception_frame_address);
    initial_context.set_link_pointer(process_init);

    process new_process = {};
    new_process.status = process_status::runnable;
    new_process.parent_id = -1;
    new_process.level_0_page_table = create_init_address_space(image_address, image_size);
    new_process.section_details = section_detail_page;
    new_process.kernel_stack_begin = kernel_stack_begin;
    new_process.kernel_mode_state = initial_context;
    new_process.user_mode_state = exception_frame_address;
    new_process.text_size =
        image_size % memory::page_size == 0 ? image_size / memory::page_size : image_size / memory::page_size + 1;
    new_process.heap_size = 0;
    new_process.stack_size = memory::user_address_space_constants::stack_size / memory::page_size;
    return new_process;
}

extern "C" void init();
extern "C" void test();

auto thread_scheduler::initialize() -> void {
    if (architecture::get_core_number() == 0) {
        for (auto &process : thread_scheduler::get().processes) {
            process.status = process_status::unused;
        }

        thread_scheduler::get().processes[0] = create_init_process(init, memory::page_size);
        file::descriptor_interface::get().initialize_file_descriptors(0);

        thread_scheduler::get().processes[1] = create_init_process(test, memory::page_size);
        file::descriptor_interface::get().initialize_file_descriptors(1);

        thread_scheduler::get().processes[2] = create_init_process(test, memory::page_size);
        file::descriptor_interface::get().initialize_file_descriptors(2);

        thread_scheduler::get().processes[3] = create_init_process(test, memory::page_size);
        file::descriptor_interface::get().initialize_file_descriptors(3);

        thread_scheduler::get().processes[4] = create_init_process(test, memory::page_size);
        file::descriptor_interface::get().initialize_file_descriptors(4);
    }
}

extern "C" void scheduler_thread_to_process_thread(context *scheduler_thread_context, context *process_thread_context);
extern "C" void process_thread_to_scheduler_thread(context *process_thread_context, context *scheduler_thread_context);

void thread_scheduler::schedule() {
    while (true) {
        for (int i = 0; i < thread_scheduler_constants::maximum_number_of_processes; i++) {
            auto &process = processes[i];
            process.lock.acquire();
            if (process.status == process_status::runnable) {
                process.status = process_status::running;

                current_process_indices[architecture::get_core_number()] = i;
                memory::virtual_memory::set_translation_table_base_0_register(&*process.level_0_page_table);
                memory::virtual_memory::flush_translation_lookaside_buffer();

                scheduler_thread_to_process_thread(&scheduler_thread_contexts[architecture::get_core_number()],
                                                   &process.kernel_mode_state);
            }
            process.lock.release();
            device::pl011::get().flush_receiver_buffer();
            device::pl011::get().flush_transmitter_buffer();
            thread_scheduler::get().wake(&device::pl011::get());
        }
    }
}

void thread_scheduler::yield() {
    get_current_process().lock.acquire();
    get_current_process().status = process_status::runnable;
    process_thread_to_scheduler_thread(&get_current_process().kernel_mode_state,
                                       &scheduler_thread_contexts[architecture::get_core_number()]);
    get_current_process().lock.release();
}

void thread_scheduler::sleep(void *condition, synchronization::spin_lock &lock) {
    get_current_process().lock.acquire();
    lock.release();

    get_current_process().status = process_status::sleeping;

    get_current_process().condition = condition;
    process_thread_to_scheduler_thread(&get_current_process().kernel_mode_state,
                                       &scheduler_thread_contexts[architecture::get_core_number()]);
    get_current_process().condition = {};

    get_current_process().lock.release();
    lock.acquire();
}

void thread_scheduler::wake(void *condition) {
    for (int i = 0; i < thread_scheduler_constants::maximum_number_of_processes; i++) {
        auto &process = processes[i];
        if (i != get_current_process_id()) {
            process.lock.acquire();
            if (process.status == process_status::sleeping && process.condition == condition) {
                process.status = process_status::runnable;
            }
            process.lock.release();
        }
    }
}

auto thread_scheduler::get_current_process() -> process & {
    return processes[get_current_process_id()];
}

auto thread_scheduler::get_current_process_id() -> int {
    return current_process_indices[architecture::get_core_number()];
}

auto thread_scheduler::fork() -> int {
    int new_process_id = -1;
    for (int i = 0; i < thread_scheduler_constants::maximum_number_of_processes; i++) {
        auto &process = processes[i];
        process.lock.acquire();
        if (process.status == process_status::unused) {
            new_process_id = i;
            process.status = process_status::reserved;
            process.lock.release();
            break;
        }
        process.lock.release();
    }
    if (new_process_id == -1) {
        return -1;
    }

    auto &original_process = processes[get_current_process_id()];
    auto &new_process = processes[new_process_id];

    new_process.parent_id = get_current_process_id();

    auto *new_level_0_page_table = memory::buddy_allocator::get().allocate<memory::page_table_t>(0);
    for (size_t i = 0; i < sizeof(memory::page_table_t) / sizeof(memory::page_table_descriptor_t); i++) {
        new_level_0_page_table->set_descriptor_at_index(i, {});
    }
    for (size_t section_index = 0; section_index < memory::page_size / sizeof(section_detail_t); section_index++) {
        auto section = (*original_process.section_details)[section_index];
        if (section.number_of_pages > 0) {
            for (size_t page_offset = 0; page_offset < section.number_of_pages; page_offset += 1) {
                auto *new_page = memory::buddy_allocator::get().allocate<array_t<byte_t, memory::page_size>>(0);
                auto original_page = section.virtual_address + page_offset * memory::page_size;
                new_level_0_page_table->map(original_page, memory::page_table_t::type_t::user, new_page,
                                            memory::page_size);
                auto *physical_address_of_original_data =
                    reinterpretable_t<uintptr_t>(original_process.level_0_page_table, original_page)
                        .to<array_t<byte_t, memory::page_size>>();
                for (size_t offset = 0; offset < memory::page_size; offset++) {
                    (*new_page)[offset] = (*physical_address_of_original_data)[offset];
                }
            }
        }
    }
    auto *new_stack_physical_address =
        memory::buddy_allocator::get().allocate<array_t<byte_t, memory::user_address_space_constants::stack_size>>(
            memory::user_address_space_constants::stack_size_order);
    new_level_0_page_table->map(memory::user_address_space_constants::stack_begin, memory::page_table_t::type_t::user,
                                new_stack_physical_address, memory::page_size);
    auto *original_stack_physical_address =
        reinterpretable_t<uintptr_t>(original_process.level_0_page_table,
                                     memory::user_address_space_constants::stack_begin)
            .to<array_t<byte_t, memory::user_address_space_constants::stack_size>>();

    for (size_t offset = 0; offset < memory::user_address_space_constants::stack_size; offset++) {
        (*new_stack_physical_address)[offset] = (*original_stack_physical_address)[offset];
    }
    new_process.level_0_page_table = new_level_0_page_table;

    auto *new_section_details_page =
        memory::buddy_allocator::get()
            .allocate<array_t<section_detail_t, memory::page_size / sizeof(section_detail_t)>>(0);
    for (size_t i = 0; i < memory::page_size / sizeof(section_detail_t); i++) {
        (*new_section_details_page)[i] = (*original_process.section_details)[i];
    }
    new_process.section_details = new_section_details_page;

    auto *new_kernel_stack_begin = memory::buddy_allocator::get().allocate<kernel_stack_t>(
        memory::kernel_address_space_constants::stack_size_order);
    *new_kernel_stack_begin = *original_process.kernel_stack_begin;
    new_process.kernel_stack_begin = new_kernel_stack_begin;

    new_process.kernel_mode_state.set_stack_pointer(&new_kernel_stack_begin->exception_frame);
    new_process.kernel_mode_state.set_link_pointer(process_init);
    new_process.user_mode_state = &new_kernel_stack_begin->exception_frame;

    new_process.text_size = original_process.text_size;
    new_process.heap_size = original_process.heap_size;
    new_process.stack_size = original_process.stack_size;
    new_process.condition = original_process.condition;

    new_process.user_mode_state->set_x0_field(0);

    file::descriptor_interface::get().clone_file_descriptors(get_current_process_id(), new_process_id);
    file::descriptor_interface::get().initialize_file_descriptors(new_process_id);

    new_process.lock.acquire();
    new_process.status = process_status::runnable;
    new_process.lock.release();

    return new_process_id;
}

auto thread_scheduler::wait() -> int {
    lock.acquire();
    while (true) {
        int number_of_children = 0;
        for (int i = 0; i < thread_scheduler_constants::maximum_number_of_processes; i++) {
            auto &process = processes[i];
            if (process.parent_id == get_current_process_id()) {
                process.lock.acquire();
                number_of_children += 1;
                if (process.status == process_status::zombie) {
                    deallocate_address_space(process.level_0_page_table);
                    memory::buddy_allocator::get().deallocate(process.section_details);
                    memory::buddy_allocator::get().deallocate(process.kernel_stack_begin);
                    process.status = process_status::unused;
                    process.parent_id = -1;
                    process.level_0_page_table = {};
                    process.section_details = {};
                    process.kernel_stack_begin = {};
                    process.kernel_mode_state = {};
                    process.user_mode_state = {};
                    process.text_size = 0;
                    process.heap_size = 0;
                    process.stack_size = 0;
                    process.condition = {};
                    process.lock.release();
                    lock.release();
                    return i;
                }
                process.lock.release();
            }
        }
        if (number_of_children < 1) {
            lock.release();
            return -1;
        }
        sleep(&processes[get_current_process_id()], lock);
    }
}

auto thread_scheduler::exit() -> void {
    if (get_current_process_id() == 0) {
        panic("thread_scheduler::exit");
    }

    file::descriptor_interface::get().remove_file_descriptors(get_current_process_id());

    lock.acquire();

    for (int i = 0; i < thread_scheduler_constants::maximum_number_of_processes; i++) {
        auto &process = processes[i];
        if (process.parent_id == get_current_process_id()) {
            process.parent_id = 0;
            wake(&processes[0]);
        }
    }

    wake(&processes[get_current_process().parent_id]);

    get_current_process().lock.acquire();

    get_current_process().status = process_status::zombie;

    lock.release();

    process_thread_to_scheduler_thread(&get_current_process().kernel_mode_state,
                                       &scheduler_thread_contexts[architecture::get_core_number()]);
}

auto thread_scheduler::exec(file::path_name_t executable_file_path,
                            span_t<array_t<byte_t, memory::page_size> *> arguments) -> bool {
    auto file_descriptor =
        file::descriptor_interface::get().open(thread_scheduler::get().get_current_process_id(), executable_file_path,
                                               true, false, file::open_mode_t::do_not_create);
    if (file_descriptor == -1) {
        return false;
    }

    elf_header_t elf_header = {};
    auto elf_header_span = span_t(&elf_header, 1);
    if (file::descriptor_interface::get().read(thread_scheduler::get().get_current_process_id(), file_descriptor,
                                               as_writable_bytes(elf_header_span)) != sizeof(elf_header_t)) {
        file::descriptor_interface::get().close(thread_scheduler::get().get_current_process_id(), file_descriptor);
        return false;
    }
    if (!elf_header.is_elf()) {
        file::descriptor_interface::get().close(thread_scheduler::get().get_current_process_id(), file_descriptor);
        return false;
    }

    auto *level_0_page_table = memory::buddy_allocator::get().allocate<page_table_t>(0);
    for (size_t i = 0; i < sizeof(memory::page_table_t) / sizeof(memory::page_table_descriptor_t); i++) {
        level_0_page_table->set_descriptor_at_index(i, {});
    }

    auto *section_details = memory::buddy_allocator::get()
                                .allocate<array_t<section_detail_t, memory::page_size / sizeof(section_detail_t)>>(0);
    for (size_t i = 0; i < memory::page_size / sizeof(section_detail_t); i++) {
        (*section_details)[i] = section_detail_t();
    }

    elf_section_header_t elf_section_header{};
    auto elf_section_header_span = span_t(&elf_section_header, 1);
    int next_empty_section_detail_index = 0;
    for (uint64_t i = 0, offset = elf_header.get_phoff_field(); i < elf_header.get_phnum_field();
         i++, offset += sizeof(elf_section_header_t)) {
        file::descriptor_interface::get().seek(thread_scheduler::get().get_current_process_id(), file_descriptor, true,
                                               offset, false, 0);
        if (file::descriptor_interface::get().read(thread_scheduler::get().get_current_process_id(), file_descriptor,
                                                   as_writable_bytes(elf_section_header_span)) !=
            sizeof(elf_section_header_t)) {
            deallocate_address_space(level_0_page_table);
            memory::buddy_allocator::get().deallocate(section_details);
            file::descriptor_interface::get().close(thread_scheduler::get().get_current_process_id(), file_descriptor);
            return false;
        }
        if (!elf_section_header.is_loadable()) {
            level_0_page_table->clear();
            memory::buddy_allocator::get().deallocate(level_0_page_table);
            memory::buddy_allocator::get().deallocate(section_details);
            file::descriptor_interface::get().close(thread_scheduler::get().get_current_process_id(), file_descriptor);
            return false;
        }
        if (elf_section_header.get_memsz_field() < elf_section_header.get_filesz_field()) {
            level_0_page_table->clear();
            memory::buddy_allocator::get().deallocate(level_0_page_table);
            memory::buddy_allocator::get().deallocate(section_details);
            file::descriptor_interface::get().close(thread_scheduler::get().get_current_process_id(), file_descriptor);
            return false;
        }
        if (elf_section_header.get_vaddr_field() + elf_section_header.get_memsz_field() <
            elf_section_header.get_vaddr_field()) {
            level_0_page_table->clear();
            memory::buddy_allocator::get().deallocate(level_0_page_table);
            memory::buddy_allocator::get().deallocate(section_details);
            file::descriptor_interface::get().close(thread_scheduler::get().get_current_process_id(), file_descriptor);
            return false;
        }
        if (elf_section_header.get_memsz_field() > memory::page_size) {
            level_0_page_table->clear();
            memory::buddy_allocator::get().deallocate(level_0_page_table);
            memory::buddy_allocator::get().deallocate(section_details);
            file::descriptor_interface::get().close(thread_scheduler::get().get_current_process_id(), file_descriptor);
            return false;
        }

        auto section_size_in_number_of_pages = elf_section_header.get_filesz_field() % memory::page_size == 0
                                                   ? elf_section_header.get_filesz_field() / memory::page_size
                                                   : elf_section_header.get_filesz_field() / memory::page_size + 1;
        (*section_details)[next_empty_section_detail_index] =
            section_detail_t{elf_section_header.get_vaddr_field(), section_size_in_number_of_pages};
        next_empty_section_detail_index += 1;

        auto *page = reinterpretable_t<uintptr_t>(level_0_page_table, elf_section_header.get_vaddr_field())
                         .to<array_t<byte_t, memory::page_size>>();
        if (page == nullptr) {
            page = memory::buddy_allocator::get().allocate<array_t<byte_t, memory::page_size>>(0);
            for (size_t i = 0; i < memory::page_size; i++) {
                (*page)[i].set_value(0);
            }
            level_0_page_table->map(elf_section_header.get_vaddr_field(), memory::page_table_t::type_t::user, page,
                                    elf_section_header.get_filesz_field());
        }

        auto *address_to_read_into = &(*page)[elf_section_header.get_vaddr_field() % memory::page_size];
        auto elf_section_span = span_t(address_to_read_into, elf_section_header.get_filesz_field());
        file::descriptor_interface::get().seek(thread_scheduler::get().get_current_process_id(), file_descriptor, true,
                                               elf_section_header.get_off_field(), false, 0);
        if (file::descriptor_interface::get().read(thread_scheduler::get().get_current_process_id(), file_descriptor,
                                                   elf_section_span) != elf_section_header.get_filesz_field()) {
            level_0_page_table->clear();
            memory::buddy_allocator::get().deallocate(level_0_page_table);
            memory::buddy_allocator::get().deallocate(section_details);
            file::descriptor_interface::get().close(thread_scheduler::get().get_current_process_id(), file_descriptor);
            return false;
        }
    }

    file::descriptor_interface::get().close(thread_scheduler::get().get_current_process_id(), file_descriptor);

    (*section_details)[next_empty_section_detail_index] = section_detail_t{
        memory::user_address_space_constants::stack_begin, 1 << memory::user_address_space_constants::stack_size_order};
    next_empty_section_detail_index += 1;

    auto *new_stack =
        memory::buddy_allocator::get().allocate<array_t<byte_t, memory::user_address_space_constants::stack_size>>(
            memory::user_address_space_constants::stack_size_order);
    level_0_page_table->map(memory::user_address_space_constants::stack_begin, memory::page_table_t::type_t::user,
                            new_stack, memory::user_address_space_constants::stack_size);
    auto offset = memory::user_address_space_constants::stack_size;
    size_t number_of_arguments = 0;
    array_t<uintptr_t, thread_scheduler_constants::maximum_number_of_arguments> user_space_argument_addresses = {};

    for (int i = 0; arguments[i] != nullptr; i++) {
        auto *argument = arguments[i];
        int argument_size = 0;
        for (int j = 0; argument != nullptr && !(*argument)[j].is_zero(); j++) {
            argument_size += 1;
        }
        offset -= argument_size * sizeof(uintptr_t);
        for (int j = 0; j < argument_size; j++) {
            (*new_stack)[offset + j] = (*argument)[j];
        }
        user_space_argument_addresses[number_of_arguments] = memory::user_address_space_constants::stack_begin + offset;
        number_of_arguments += 1;
    }
    offset -= number_of_arguments * sizeof(uintptr_t);
    for (size_t i = 0; i < number_of_arguments; i++) {
        for (size_t j = 0; j < sizeof(uintptr_t); j++) {
            (*new_stack)[offset + i * sizeof(uintptr_t) + j] =
                as_writable_bytes(span_t(&user_space_argument_addresses[i], 1))[j];
        }
    }

    deallocate_address_space(get_current_process().level_0_page_table);
    get_current_process().level_0_page_table = level_0_page_table;

    memory::buddy_allocator::get().deallocate(get_current_process().section_details);
    get_current_process().section_details = section_details;

    get_current_process().user_mode_state->set_elr_field(elf_header.get_entry_field());
    get_current_process().user_mode_state->reset_spsr_field();
    get_current_process().user_mode_state->set_sp_field(memory::user_address_space_constants::stack_begin + offset);
    get_current_process().user_mode_state->set_x0_field(number_of_arguments);
    get_current_process().user_mode_state->set_x1_field(memory::user_address_space_constants::stack_begin + offset);

    return true;
};

} // namespace process

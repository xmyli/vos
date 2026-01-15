#include "../include/exception_handler.hpp"
#include "../include/buddy_allocator.hpp"
#include "../include/descriptor_interface.hpp"
#include "../include/device.hpp"
#include "../include/e1000.hpp"
#include "../include/gicv3.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/panic.hpp"
#include "../include/path_name.hpp"
#include "../include/process.hpp"
#include "../include/socket_interface.hpp"
#include "../include/thread_scheduler.hpp"
#include "../include/timer.hpp"
#include "../include/virtio_blk.hpp"
#include "../include/virtual_memory.hpp"

extern "C" void exception_vector_table();

namespace process {

auto handle_read_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto *level_0_page_table = thread_scheduler::get().get_current_process().level_0_page_table;
    auto file_descriptor_index = exception_frame_pointer->get_x0_field();
    auto address_of_data_in_user_space = exception_frame_pointer->get_x1_field();
    auto *address_of_data_in_kernel_space =
        reinterpretable_t<uintptr_t>(level_0_page_table, address_of_data_in_user_space).to<byte_t>();
    auto size_of_data = exception_frame_pointer->get_x2_field();
    auto data_span = span_t(address_of_data_in_kernel_space, size_of_data);
    auto number_of_bytes_read = file::descriptor_interface::get().read(thread_scheduler::get().get_current_process_id(),
                                                                       file_descriptor_index, data_span);
    exception_frame_pointer->set_x0_field(number_of_bytes_read);
}

auto handle_write_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto *level_0_page_table = thread_scheduler::get().get_current_process().level_0_page_table;
    auto file_descriptor_index = exception_frame_pointer->get_x0_field();
    auto address_of_data_in_user_space = exception_frame_pointer->get_x1_field();
    auto *address_of_data_in_kernel_space =
        reinterpretable_t<uintptr_t>(level_0_page_table, address_of_data_in_user_space).to<byte_t>();
    auto size_of_data = exception_frame_pointer->get_x2_field();
    auto data_span = span_t(address_of_data_in_kernel_space, size_of_data);
    auto number_of_bytes_written = file::descriptor_interface::get().write(
        thread_scheduler::get().get_current_process_id(), file_descriptor_index, data_span);
    exception_frame_pointer->set_x0_field(number_of_bytes_written);
}

auto handle_exec_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto *level_0_page_table = thread_scheduler::get().get_current_process().level_0_page_table;
    auto address_of_file_path_in_user_space = exception_frame_pointer->get_x0_field();
    const auto *address_of_file_path_in_kernel_space =
        reinterpretable_t<uintptr_t>(level_0_page_table, address_of_file_path_in_user_space).to<const char>();

    auto *address_of_copy_of_argument_list_in_kernel_space =
        memory::buddy_allocator::get()
            .allocate<array_t<array_t<byte_t, memory::page_size> *, memory::page_size / sizeof(uintptr_t)>>(0);
    for (size_t i = 0; i < memory::page_size / sizeof(uintptr_t); i++) {
        (*address_of_copy_of_argument_list_in_kernel_space)[i] = nullptr;
    }

    auto address_of_original_argument_list_in_user_space = exception_frame_pointer->get_x1_field();
    auto *address_of_original_argument_list_in_kernel_space =
        reinterpretable_t<uintptr_t>(level_0_page_table, address_of_original_argument_list_in_user_space)
            .to<array_t<uintptr_t, memory::page_size / sizeof(uintptr_t)>>();

    for (size_t i = 0;
         (*address_of_original_argument_list_in_kernel_space)[i] != 0 && i < memory::page_size / sizeof(uintptr_t);
         i++) {
        auto address_of_original_argument_in_user_space = (*address_of_original_argument_list_in_kernel_space)[i];
        auto *address_of_original_argument_in_kernel_space =
            reinterpretable_t<uintptr_t>(level_0_page_table, address_of_original_argument_in_user_space)
                .to<array_t<byte_t, memory::page_size>>();
        if (address_of_original_argument_in_kernel_space != nullptr) {
            (*address_of_copy_of_argument_list_in_kernel_space)[i] = address_of_original_argument_in_kernel_space;
        } else {
            // TODO: kill the process
            panic("exception_handler::handle_exec_system_call, invalid arguments list");
        }
    }

    auto status = thread_scheduler::get().exec(
        file::path_name_t{address_of_file_path_in_kernel_space},
        span_t(&(*address_of_copy_of_argument_list_in_kernel_space)[0], memory::page_size / sizeof(void *)));
    if (!status) {
        exception_frame_pointer->set_x0_field(0);
    } else {
        thread_scheduler::get().yield();
    }
    memory::buddy_allocator::get().deallocate(address_of_copy_of_argument_list_in_kernel_space);
}

auto handle_fork_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto child_process_id = thread_scheduler::get().fork();
    exception_frame_pointer->set_x0_field(child_process_id);
}

auto handle_pipe_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto *level_0_page_table = thread_scheduler::get().get_current_process().level_0_page_table;
    auto address_of_file_descriptors_buffer_in_user_space = exception_frame_pointer->get_x0_field();
    auto *address_of_file_descriptors_buffer_in_kernel_space =
        reinterpretable_t<uintptr_t>(level_0_page_table, address_of_file_descriptors_buffer_in_user_space)
            .to<array_t<int32_t, 2>>();
    auto result = file::descriptor_interface::get().pipe(address_of_file_descriptors_buffer_in_kernel_space);
    exception_frame_pointer->set_x0_field(result ? 1 : 0);
}

auto handle_yield_system_call(exception_frame_t * /*exception_frame_pointer*/) -> void {
    thread_scheduler::get().yield();
}

auto handle_wait_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto exited_child_process_id = thread_scheduler::get().wait();
    exception_frame_pointer->set_x0_field(exited_child_process_id);
}

auto handle_open_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto *level_0_page_table = thread_scheduler::get().get_current_process().level_0_page_table;
    auto address_of_path_in_user_space = exception_frame_pointer->get_x0_field();
    const auto *address_of_path_in_kernel_space =
        reinterpretable_t<uintptr_t>(level_0_page_table, address_of_path_in_user_space).to<const char>();
    auto readable = exception_frame_pointer->get_x1_field() != 0;
    auto writable = exception_frame_pointer->get_x2_field() != 0;
    file::open_mode_t mode = file::open_mode_t::do_not_create;
    if (exception_frame_pointer->get_x3_field() == 1) {
        mode = file::open_mode_t::create_directory;
    } else if (exception_frame_pointer->get_x3_field() == 2) {
        mode = file::open_mode_t::create_file;
    }
    auto file_descriptor_index = file::descriptor_interface::get().open(
        thread_scheduler::get().get_current_process_id(), file::path_name_t{address_of_path_in_kernel_space}, readable,
        writable, mode);
    exception_frame_pointer->set_x0_field(file_descriptor_index);
}

auto handle_close_system_call(exception_frame_t *exception_frame_pointer) -> void {
    file::descriptor_interface::get().close(thread_scheduler::get().get_current_process_id(),
                                            exception_frame_pointer->get_x0_field());
}

auto handle_copy_system_call(exception_frame_t *exception_frame_pointer) -> void {
    exception_frame_pointer->set_x0_field(
        file::descriptor_interface::get().copy(exception_frame_pointer->get_x0_field()));
}

auto handle_socket_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto socket_index = file::descriptor_interface::get().socket(exception_frame_pointer->get_x0_field() == 0);
    exception_frame_pointer->set_x0_field(socket_index);
}

auto handle_bind_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto file_descriptor_index = exception_frame_pointer->get_x0_field();
    auto source_port_number = exception_frame_pointer->get_x1_field();
    auto success =
        file::descriptor_interface::get().bind(file_descriptor_index, networking::port_number_t(source_port_number));
    exception_frame_pointer->set_x0_field(success ? 1 : 0);
}

auto handle_connect_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto file_descriptor_index = exception_frame_pointer->get_x0_field();
    auto destination_ip_address = exception_frame_pointer->get_x1_field();
    auto destination_port_number = exception_frame_pointer->get_x2_field();
    auto success = file::descriptor_interface::get().connect(
        file_descriptor_index, networking::internet_protocol_address_t(destination_ip_address),
        networking::port_number_t(destination_port_number));
    exception_frame_pointer->set_x0_field(success ? 1 : 0);
}

auto handle_listen_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto file_descriptor_index = exception_frame_pointer->get_x0_field();
    auto success = file::descriptor_interface::get().listen(file_descriptor_index);
    exception_frame_pointer->set_x0_field(success ? 1 : 0);
}

auto handle_accept_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto file_descriptor_index = exception_frame_pointer->get_x0_field();
    auto new_file_descriptor_index = file::descriptor_interface::get().accept(file_descriptor_index);
    exception_frame_pointer->set_x0_field(new_file_descriptor_index);
}

auto handle_receive_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto *level_0_page_table = thread_scheduler::get().get_current_process().level_0_page_table;
    auto file_descriptor_index = exception_frame_pointer->get_x0_field();
    auto address_of_buffer_in_user_space = exception_frame_pointer->get_x1_field();
    auto *address_of_buffer_in_kernel_space =
        reinterpretable_t<uintptr_t>(level_0_page_table, address_of_buffer_in_user_space).to<byte_t>();
    auto size = exception_frame_pointer->get_x2_field();
    auto buffer_span = span_t(address_of_buffer_in_kernel_space, size);
    auto address_of_internet_protocol_address_in_user_space = exception_frame_pointer->get_x3_field();
    auto *address_of_internet_protocol_address_in_kernel_space =
        reinterpretable_t<uintptr_t>(level_0_page_table, address_of_internet_protocol_address_in_user_space)
            .to<networking::internet_protocol_address_t>();
    auto address_of_port_number_in_user_space = exception_frame_pointer->get_x4_field();
    auto *address_of_port_number_in_kernel_space =
        reinterpretable_t<uintptr_t>(level_0_page_table, address_of_port_number_in_user_space)
            .to<networking::port_number_t>();
    if (address_of_buffer_in_kernel_space == nullptr ||
        (address_of_internet_protocol_address_in_kernel_space == nullptr &&
         address_of_internet_protocol_address_in_user_space != 0) ||
        (address_of_port_number_in_kernel_space == nullptr && address_of_port_number_in_user_space != 0)) {
        exception_frame_pointer->set_x0_field(0);
    } else {
        auto number_of_bytes_received = file::descriptor_interface::get().receive(
            file_descriptor_index, buffer_span, address_of_internet_protocol_address_in_kernel_space,
            address_of_port_number_in_kernel_space);
        exception_frame_pointer->set_x0_field(number_of_bytes_received);
    }
}

auto handle_transmit_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto file_descriptor_index = exception_frame_pointer->get_x0_field();
    auto *level_0_page_table = thread_scheduler::get().get_current_process().level_0_page_table;
    auto address_of_buffer_in_user_space = exception_frame_pointer->get_x1_field();
    auto *address_of_buffer_in_kernel_space =
        reinterpretable_t<uintptr_t>(level_0_page_table, address_of_buffer_in_user_space).to<byte_t>();
    auto size = exception_frame_pointer->get_x2_field();
    auto buffer_span = span_t(address_of_buffer_in_kernel_space, size);
    auto internet_protocol_address = exception_frame_pointer->get_x3_field();
    auto port_number = exception_frame_pointer->get_x4_field();
    if (address_of_buffer_in_kernel_space == nullptr) {
        exception_frame_pointer->set_x0_field(0);
    } else {
        auto number_of_bytes_transmitted = file::descriptor_interface::get().transmit(
            file_descriptor_index, buffer_span, networking::internet_protocol_address_t(internet_protocol_address),
            networking::port_number_t(port_number));
        exception_frame_pointer->set_x0_field(number_of_bytes_transmitted);
    }
}

auto handle_system_call(exception_frame_t *exception_frame_pointer) -> void {
    auto system_call_number = exception_frame_pointer->get_x8_field();
    switch (system_call_number) {
    case exception_handler_constants::system_call_numbers::exit:
        thread_scheduler::get().exit();
        break;
    case exception_handler_constants::system_call_numbers::read:
        handle_read_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::write:
        handle_write_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::exec:
        handle_exec_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::fork:
        handle_fork_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::pipe:
        handle_pipe_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::yield:
        handle_yield_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::wait:
        handle_wait_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::open:
        handle_open_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::close:
        handle_close_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::copy:
        handle_copy_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::socket:
        handle_socket_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::bind:
        handle_bind_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::connect:
        handle_connect_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::listen:
        handle_listen_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::accept:
        handle_accept_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::receive:
        handle_receive_system_call(exception_frame_pointer);
        break;
    case exception_handler_constants::system_call_numbers::transmit:
        handle_transmit_system_call(exception_frame_pointer);
        break;
    default:
        panic("exception_handler::handle_system_call");
    }
}

auto exception_handler::initialize() -> void {
    asm volatile("msr vbar_el1, %0" : : "r"(exception_vector_table));
}

extern "C" void handle_exception_level_1_exception(exception_frame_t * /*exception_frame_pointer*/) {
    uint64_t esr_el1_value = 0;
    asm volatile("mrs %0, esr_el1" : "=r"(esr_el1_value));

    uint64_t elr_el1_value = 0;
    asm volatile("mrs %0, elr_el1" : "=r"(elr_el1_value));

    uint64_t far_el1_value = 0;
    asm volatile("mrs %0, far_el1" : "=r"(far_el1_value));
    panic("exception_handler::handle_exception_level_1_exception");
}

extern "C" void handle_exception_level_1_interrupt(exception_frame_t * /*exception_frame_pointer*/) {
    panic("exception_handler::handle_exception_level_1_interrupt");
}

extern "C" void handle_exception_level_0_exception(exception_frame_t *exception_frame_pointer) {
    architecture::esr_el1 esr_el1_value{};
    asm volatile("mrs %0, esr_el1" : "=r"(esr_el1_value.value));
    auto exception_class = esr_el1_value.ec;

    uint64_t elr_el1_value = 0;
    asm volatile("mrs %0, elr_el1" : "=r"(elr_el1_value));

    uint64_t far_el1_value = 0;
    asm volatile("mrs %0, far_el1" : "=r"(far_el1_value));

    if (exception_class == architecture::svc_exception_code) {
        handle_system_call(exception_frame_pointer);
    } else {
        panic("exception_handler::handle_exception_level_0_exception");
    }
}

extern "C" void handle_exception_level_0_interrupt(exception_frame_t * /*exception_frame_pointer*/) {
    auto interrupt_number = device::gicv3::get_interrupt_number();
    switch (interrupt_number) {
    case device::gicv3_timer_intid:
        device::gicv3::set_interrupt_number(interrupt_number);
        device::timer::get().interrupt();
        break;
    case device::gicv3_pl011_intid:
        device::gicv3::set_interrupt_number(interrupt_number);
        device::pl011::get().interrupt();
        break;
    case device::gicv3_pcie_intid:
        device::gicv3::set_interrupt_number(interrupt_number);
        device::e1000::get().interrupt();
        break;
    case device::gicv3_virtio_intid:
        device::gicv3::set_interrupt_number(interrupt_number);
        device::virtio_blk::get().interrupt();
        break;
    case device::gicv3_spurious_intid:
        break;
    default:
        panic("exception_handler::handle_exception_level_0_interrupt");
        break;
    }
}

} // namespace process

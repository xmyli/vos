#include "../include/descriptor_interface.hpp"
#include "../include/buddy_allocator.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/socket_interface.hpp"
#include "../include/thread_scheduler.hpp"
#include "../include/virtio_blk.hpp"
#include "../include/virtual_memory.hpp"

namespace file {

auto descriptor_interface::initialize_file_descriptors(uint64_t process_id) -> void {
    file_descriptors[process_id].lock.acquire();
    file_descriptors[process_id].data[0].type = file_descriptor_type_t::input;
    file_descriptors[process_id].data[0].readable = true;
    file_descriptors[process_id].data[0].writable = false;
    file_descriptors[process_id].data[1].type = file_descriptor_type_t::output;
    file_descriptors[process_id].data[1].readable = false;
    file_descriptors[process_id].data[1].writable = true;
    file_descriptors[process_id].lock.release();
}

auto descriptor_interface::remove_file_descriptors(uint64_t process_id) -> void {
    for (int i = 0; i < descriptor_interface_constants::maximum_number_of_file_descriptors_per_process; i++) {
        auto &file_descriptor = file_descriptors[process_id].data[i];
        if (file_descriptor.type != file_descriptor_type_t::unused) {
            this->close(process_id, i);
        }
    }
}

auto descriptor_interface::clone_file_descriptors(int from_process_id, int to_process_id) -> void {
    if (from_process_id == to_process_id) {
        return;
    }
    if (from_process_id > to_process_id) {
        file_descriptors[to_process_id].lock.acquire();
        file_descriptors[from_process_id].lock.acquire();
    }
    if (from_process_id < to_process_id) {
        file_descriptors[from_process_id].lock.acquire();
        file_descriptors[to_process_id].lock.acquire();
    }
    for (int i = 0; i < descriptor_interface_constants::maximum_number_of_file_descriptors_per_process; i++) {
        auto &original_file_descriptor = file_descriptors[from_process_id].data[i];
        auto &new_file_descriptor = file_descriptors[to_process_id].data[i];
        if (original_file_descriptor.type != file_descriptor_type_t::unused) {
            if (original_file_descriptor.type == file_descriptor_type_t::inode) {
                inode_cache.reference(original_file_descriptor.index_of_inode_on_disk);
            }
            if (original_file_descriptor.type == file_descriptor_type_t::pipe) {
                if (original_file_descriptor.readable) {
                    pipes.open_reader(original_file_descriptor.pipe_index);
                }
                if (original_file_descriptor.writable) {
                    pipes.open_writer(original_file_descriptor.pipe_index);
                }
            }
            new_file_descriptor = original_file_descriptor;
        }
    }
    if (from_process_id > to_process_id) {
        file_descriptors[to_process_id].lock.release();
        file_descriptors[from_process_id].lock.release();
    }
    if (from_process_id < to_process_id) {
        file_descriptors[from_process_id].lock.release();
        file_descriptors[to_process_id].lock.release();
    }
}

auto descriptor_interface::open(uint64_t process_id, path_name_t path, bool readable, bool writable, open_mode_t mode)
    -> int {
    block_cache.open_transaction(descriptor_interface_constants::maximum_number_of_changed_blocks_per_transaction);
    directory_lock.acquire();
    auto index_of_inode_on_disk = inode_cache.get(path, false);
    if (index_of_inode_on_disk == 0) {
        if (mode == open_mode_t::create_directory) {
            index_of_inode_on_disk = inode_cache.allocate(true);
            if (!inode_cache.set(path, index_of_inode_on_disk)) {
                inode_cache.deallocate(index_of_inode_on_disk);
                directory_lock.release();
                block_cache.close_transaction();
                return -1;
            }
        } else if (mode == open_mode_t::create_file) {
            index_of_inode_on_disk = inode_cache.allocate(false);
            if (!inode_cache.set(path, index_of_inode_on_disk)) {
                inode_cache.deallocate(index_of_inode_on_disk);
                directory_lock.release();
                block_cache.close_transaction();
                return -1;
            }
        } else {
            directory_lock.release();
            block_cache.close_transaction();
            return -1;
        }
    }
    inode_cache.reference(index_of_inode_on_disk);
    directory_lock.release();
    block_cache.close_transaction();

    file_descriptors[process_id].lock.acquire();
    int selected_file_descriptor_index = 0;
    for (int i = 0; i < descriptor_interface_constants::maximum_number_of_file_descriptors_per_process; i++) {
        auto &file_descriptor = file_descriptors[process_id].data[i];
        if (file_descriptor.type == file_descriptor_type_t::unused) {
            file_descriptor.type = file_descriptor_type_t::inode;
            file_descriptor.readable = readable;
            file_descriptor.writable = writable;
            file_descriptor.index_of_inode_on_disk = index_of_inode_on_disk;
            file_descriptor.read_offset = 0;
            file_descriptor.write_offset = 0;
            selected_file_descriptor_index = i;
            break;
        }
    }
    file_descriptors[process_id].lock.release();
    return selected_file_descriptor_index;
}

auto descriptor_interface::close(uint64_t process_id, uint64_t file_descriptor_index) -> void {
    block_cache.open_transaction(descriptor_interface_constants::maximum_number_of_changed_blocks_per_transaction);

    file_descriptors[process_id].lock.acquire();
    auto &file_descriptor = file_descriptors[process_id].data[file_descriptor_index];
    if (file_descriptor.type == file_descriptor_type_t::inode) {
        inode_cache.dereference(file_descriptor.index_of_inode_on_disk);
        inode_cache.deallocate(file_descriptor.index_of_inode_on_disk);
    }
    if (file_descriptor.type == file_descriptor_type_t::pipe) {
        if (file_descriptor.readable) {
            pipes.close_reader(file_descriptor.pipe_index);
        }
        if (file_descriptor.writable) {
            pipes.close_writer(file_descriptor.pipe_index);
        }
    }
    if (file_descriptor.type == file_descriptor_type_t::socket) {
        networking::socket_interface::get().handle_close_call(file_descriptor.socket_index);
    }
    file_descriptors[process_id].data[file_descriptor_index].type = file_descriptor_type_t::unused;
    file_descriptors[process_id].data[file_descriptor_index].readable = false;
    file_descriptors[process_id].data[file_descriptor_index].writable = false;
    file_descriptors[process_id].data[file_descriptor_index].index_of_inode_on_disk = inode_index_t{0};
    file_descriptors[process_id].data[file_descriptor_index].read_offset = 0;
    file_descriptors[process_id].data[file_descriptor_index].write_offset = 0;
    file_descriptors[process_id].data[file_descriptor_index].pipe_index = -1;
    file_descriptors[process_id].data[file_descriptor_index].socket_index = -1;
    file_descriptors[process_id].lock.release();
    block_cache.close_transaction();
}

auto descriptor_interface::read(uint64_t process_id, uint64_t file_descriptor_index, span_t<byte_t> buffer) -> size_t {
    file_descriptors[process_id].lock.acquire();
    auto &file_descriptor = file_descriptors[process_id].data[file_descriptor_index];
    if (file_descriptor.type == file_descriptor_type_t::unused) {
        file_descriptors[process_id].lock.release();
        return 0;
    }
    if (!file_descriptor.readable) {
        file_descriptors[process_id].lock.release();
        return 0;
    }
    if (file_descriptor.type == file_descriptor_type_t::inode) {
        if (file_descriptor.index_of_inode_on_disk == 0) {
            file_descriptors[process_id].lock.release();
            return 0;
        }
        block_cache.open_transaction(descriptor_interface_constants::maximum_number_of_changed_blocks_per_transaction);
        auto result = inode_cache.read(file_descriptor.index_of_inode_on_disk, file_descriptor.read_offset, buffer);
        file_descriptor.read_offset += buffer.size();
        block_cache.close_transaction();
        file_descriptors[process_id].lock.release();
        return result;
    }
    if (file_descriptor.type == file_descriptor_type_t::pipe) {
        size_t result = 0;
        for (auto &value : buffer) {
            value = pipes.read(file_descriptor.pipe_index);
            result += 1;
        }
        file_descriptors[process_id].lock.release();
        return result;
    }
    if (file_descriptor.type == file_descriptor_type_t::input) {
        for (auto &value : buffer) {
            value = device::pl011::get().read_receiver_buffer();
        }
        file_descriptors[process_id].lock.release();
        return buffer.size();
    }
    if (file_descriptor.type == file_descriptor_type_t::socket) {
        auto result =
            networking::socket_interface::get().handle_receive_call(file_descriptor.socket_index, buffer, {}, {});
        file_descriptors[process_id].lock.release();
        return result;
    }
    file_descriptors[process_id].lock.release();
    return 0;
}

auto descriptor_interface::write(uint64_t process_id, uint64_t file_descriptor_index, span_t<byte_t> buffer) -> size_t {
    file_descriptors[process_id].lock.acquire();
    auto &file_descriptor = file_descriptors[process_id].data[file_descriptor_index];
    if (file_descriptor.type == file_descriptor_type_t::unused) {
        file_descriptors[process_id].lock.release();
        return 0;
    }
    if (!file_descriptor.writable) {
        file_descriptors[process_id].lock.release();
        return 0;
    }
    if (file_descriptor.type == file_descriptor_type_t::inode) {
        if (file_descriptor.index_of_inode_on_disk == 0) {
            file_descriptors[process_id].lock.release();
            return 0;
        }
        block_cache.open_transaction(descriptor_interface_constants::maximum_number_of_changed_blocks_per_transaction);
        auto result = inode_cache.write(file_descriptor.index_of_inode_on_disk, file_descriptor.write_offset, buffer);
        block_cache.close_transaction();
        file_descriptor.write_offset += buffer.size();
        file_descriptors[process_id].lock.release();
        return result;
    }
    if (file_descriptor.type == file_descriptor_type_t::pipe) {
        size_t result = 0;
        for (auto &value : buffer) {
            pipes.write(file_descriptor.pipe_index, value);
            result += 1;
        }
        file_descriptors[process_id].lock.release();
        return result;
    }
    if (file_descriptor.type == file_descriptor_type_t::output) {
        for (auto &value : buffer) {
            device::pl011::get().write_transmitter_buffer(value);
        }
        file_descriptors[process_id].lock.release();
        return buffer.size();
    }
    if (file_descriptor.type == file_descriptor_type_t::socket) {
        auto result = networking::socket_interface::get().handle_transmit_call(
            file_descriptor.socket_index, buffer, networking::internet_protocol_address_t{},
            networking::port_number_t{});
        file_descriptors[process_id].lock.release();
        return result;
    }
    file_descriptors[process_id].lock.release();
    return 0;
}

auto descriptor_interface::seek(uint64_t process_id, uint64_t file_descriptor_index, bool read, size_t new_read_offset,
                                bool write, size_t new_write_offset) -> void {
    file_descriptors[process_id].lock.acquire();
    if (file_descriptors[process_id].data[file_descriptor_index].type != file_descriptor_type_t::inode) {
        file_descriptors[process_id].lock.release();
        return;
    }
    if (read) {
        file_descriptors[process_id].data[file_descriptor_index].read_offset = new_read_offset;
    }
    if (write) {
        file_descriptors[process_id].data[file_descriptor_index].write_offset = new_write_offset;
    }
    file_descriptors[process_id].lock.release();
}

auto descriptor_interface::link(uint64_t process_id, uint64_t file_descriptor_index, path_name_t new_path) -> bool {
    block_cache.open_transaction(descriptor_interface_constants::maximum_number_of_changed_blocks_per_transaction);
    directory_lock.acquire();
    file_descriptors[process_id].lock.acquire();
    auto &file_descriptor = file_descriptors[process_id].data[file_descriptor_index];
    if (file_descriptor.index_of_inode_on_disk == 0) {
        file_descriptors[process_id].lock.release();
        directory_lock.release();
        block_cache.close_transaction();
        return false;
    }
    if (!inode_cache.set(new_path, file_descriptor.index_of_inode_on_disk)) {
        file_descriptors[process_id].lock.release();
        directory_lock.release();
        block_cache.close_transaction();
        return false;
    }
    file_descriptors[process_id].lock.release();
    directory_lock.release();
    block_cache.close_transaction();
    return true;
}

auto descriptor_interface::unlink(uint64_t process_id, uint64_t file_descriptor_index, path_name_t path) -> void {
    block_cache.open_transaction(descriptor_interface_constants::maximum_number_of_changed_blocks_per_transaction);
    directory_lock.acquire();
    file_descriptors[process_id].lock.acquire();
    auto &file_descriptor = file_descriptors[process_id].data[file_descriptor_index];
    inode_cache.unset(path);
    inode_cache.deallocate(file_descriptor.index_of_inode_on_disk);
    file_descriptors[process_id].lock.release();
    directory_lock.release();
    block_cache.close_transaction();
}

auto descriptor_interface::status(uint64_t process_id, uint64_t file_descriptor_index) -> file_descriptor_status_t {
    block_cache.open_transaction(descriptor_interface_constants::maximum_number_of_changed_blocks_per_transaction);
    file_descriptors[process_id].lock.acquire();
    auto &file_descriptor = file_descriptors[process_id].data[file_descriptor_index];
    if (file_descriptor.type == file_descriptor_type_t::inode) {
        auto inode_status = inode_cache.status(file_descriptor.index_of_inode_on_disk);
        file_descriptors[process_id].lock.release();
        block_cache.close_transaction();
        return {file_descriptor_type_t::inode, inode_status.type, inode_status.size, file_descriptor.readable,
                file_descriptor.writable};
    }
    file_descriptors[process_id].lock.release();
    block_cache.close_transaction();
    return {file_descriptor.type, file::inode_type_t::unused, 0, file_descriptor.readable, file_descriptor.writable};
}

auto descriptor_interface::pipe(array_t<int32_t, 2> *file_descriptors_address) -> bool {
    auto pipe_index = pipes.get();
    if (pipe_index == -1) {
        return false;
    }

    file_descriptors[process::thread_scheduler::get().get_current_process_id()].lock.acquire();
    int read_file_descriptor_index = -1;
    for (int i = 3; i < descriptor_interface_constants::maximum_number_of_file_descriptors_per_process; i++) {
        auto &file_descriptor = file_descriptors[process::thread_scheduler::get().get_current_process_id()].data[i];
        if (file_descriptor.type == file_descriptor_type_t::unused) {
            file_descriptor.type = file_descriptor_type_t::pipe;
            read_file_descriptor_index = i;
            break;
        }
    }
    int write_file_descriptor_index = -1;
    for (int i = 3; i < descriptor_interface_constants::maximum_number_of_file_descriptors_per_process; i++) {
        auto &file_descriptor = file_descriptors[process::thread_scheduler::get().get_current_process_id()].data[i];
        if (file_descriptor.type == file_descriptor_type_t::unused) {
            file_descriptor.type = file_descriptor_type_t::pipe;
            write_file_descriptor_index = i;
            break;
        }
    }
    if (read_file_descriptor_index != -1 && write_file_descriptor_index != -1) {
        auto &read_file_descriptor = file_descriptors[process::thread_scheduler::get().get_current_process_id()]
                                         .data[read_file_descriptor_index];
        read_file_descriptor.type = file_descriptor_type_t::pipe;
        read_file_descriptor.readable = true;
        read_file_descriptor.writable = false;
        read_file_descriptor.pipe_index = pipe_index;
        pipes.open_reader(pipe_index);
        auto &write_file_descriptor = file_descriptors[process::thread_scheduler::get().get_current_process_id()]
                                          .data[write_file_descriptor_index];
        write_file_descriptor.type = file_descriptor_type_t::pipe;
        write_file_descriptor.readable = false;
        write_file_descriptor.writable = true;
        write_file_descriptor.pipe_index = pipe_index;
        pipes.open_writer(pipe_index);

        file_descriptors[process::thread_scheduler::get().get_current_process_id()].lock.release();

        (*file_descriptors_address)[0] = read_file_descriptor_index;
        (*file_descriptors_address)[1] = write_file_descriptor_index;

        return true;
    }
    if (read_file_descriptor_index != -1) {
        auto &read_file_descriptor = file_descriptors[process::thread_scheduler::get().get_current_process_id()]
                                         .data[read_file_descriptor_index];
        read_file_descriptor.type = file_descriptor_type_t::unused;
        read_file_descriptor.readable = false;
        read_file_descriptor.writable = false;
    }
    if (write_file_descriptor_index != -1) {
        auto &write_file_descriptor = file_descriptors[process::thread_scheduler::get().get_current_process_id()]
                                          .data[write_file_descriptor_index];
        write_file_descriptor.type = file_descriptor_type_t::unused;
        write_file_descriptor.readable = false;
        write_file_descriptor.writable = false;
    }
    file_descriptors[process::thread_scheduler::get().get_current_process_id()].lock.release();
    return false;
}

auto descriptor_interface::copy(uint64_t file_descriptor_index) -> int {
    file_descriptors[process::thread_scheduler::get().get_current_process_id()].lock.acquire();
    auto &from_file_descriptor =
        file_descriptors[process::thread_scheduler::get().get_current_process_id()].data[file_descriptor_index];
    int selected_file_descriptor_index = 0;
    for (int i = 0; i < descriptor_interface_constants::maximum_number_of_file_descriptors_per_process; i++) {
        auto &to_file_descriptor = file_descriptors[process::thread_scheduler::get().get_current_process_id()].data[i];
        if (to_file_descriptor.type == file_descriptor_type_t::unused) {
            to_file_descriptor = from_file_descriptor;
            selected_file_descriptor_index = i;
            break;
        }
    }
    if (from_file_descriptor.type == file_descriptor_type_t::inode) {
        inode_cache.reference(from_file_descriptor.index_of_inode_on_disk);
    }
    if (from_file_descriptor.type == file_descriptor_type_t::pipe) {
        if (from_file_descriptor.readable) {
            pipes.open_reader(from_file_descriptor.pipe_index);
        }
        if (from_file_descriptor.writable) {
            pipes.open_writer(from_file_descriptor.pipe_index);
        }
    }
    file_descriptors[process::thread_scheduler::get().get_current_process_id()].lock.release();
    return selected_file_descriptor_index;
}

auto descriptor_interface::socket(bool connected) -> int {
    auto socket_index = networking::socket_interface::get().handle_open_call(
        connected ? networking::socket_type_t::tcp : networking::socket_type_t::udp);
    if (socket_index == -1) {
        return -1;
    }
    file_descriptors[process::thread_scheduler::get().get_current_process_id()].lock.acquire();
    int selected_file_descriptor_index = 0;
    for (int i = 0; i < descriptor_interface_constants::maximum_number_of_file_descriptors_per_process; i++) {
        auto &file_descriptor = file_descriptors[process::thread_scheduler::get().get_current_process_id()].data[i];
        if (file_descriptor.type == file_descriptor_type_t::unused) {
            file_descriptor.type = file_descriptor_type_t::socket;
            file_descriptor.readable = true;
            file_descriptor.writable = true;
            file_descriptor.socket_index = socket_index;
            selected_file_descriptor_index = i;
            break;
        }
    }
    file_descriptors[process::thread_scheduler::get().get_current_process_id()].lock.release();
    if (selected_file_descriptor_index == 0) {
        networking::socket_interface::get().handle_close_call(socket_index);
        return -1;
    }
    return selected_file_descriptor_index;
}

auto descriptor_interface::connect(uint64_t file_descriptor_index,
                                   networking::internet_protocol_address_t destination_internet_protocol_address,
                                   networking::port_number_t destination_port_number) -> bool {
    auto socket_index = this->file_descriptors[process::thread_scheduler::get().get_current_process_id()]
                            .data[file_descriptor_index]
                            .socket_index;
    return networking::socket_interface::get().handle_connect_call(socket_index, destination_internet_protocol_address,
                                                                   destination_port_number);
}

auto descriptor_interface::bind(uint64_t file_descriptor_index, networking::port_number_t source_port_number) -> bool {
    auto socket_index = this->file_descriptors[process::thread_scheduler::get().get_current_process_id()]
                            .data[file_descriptor_index]
                            .socket_index;
    return networking::socket_interface::get().handle_bind_call(socket_index, source_port_number);
}

auto descriptor_interface::listen(uint64_t file_descriptor_index) -> bool {
    auto socket_index = this->file_descriptors[process::thread_scheduler::get().get_current_process_id()]
                            .data[file_descriptor_index]
                            .socket_index;
    return networking::socket_interface::get().handle_listen_call(socket_index);
}

auto descriptor_interface::accept(uint64_t file_descriptor_index) -> int {
    auto socket_index = this->file_descriptors[process::thread_scheduler::get().get_current_process_id()]
                            .data[file_descriptor_index]
                            .socket_index;
    auto new_socket_index = networking::socket_interface::get().handle_accept_call(socket_index);
    if (new_socket_index == -1) {
        return -1;
    }
    file_descriptors[process::thread_scheduler::get().get_current_process_id()].lock.acquire();
    int selected_file_descriptor_index = 0;
    for (int i = 0; i < descriptor_interface_constants::maximum_number_of_file_descriptors_per_process; i++) {
        auto &file_descriptor = file_descriptors[process::thread_scheduler::get().get_current_process_id()].data[i];
        if (file_descriptor.type == file_descriptor_type_t::unused) {
            file_descriptor.type = file_descriptor_type_t::socket;
            file_descriptor.readable = true;
            file_descriptor.writable = true;
            file_descriptor.socket_index = new_socket_index;
            selected_file_descriptor_index = i;
            break;
        }
    }
    file_descriptors[process::thread_scheduler::get().get_current_process_id()].lock.release();
    if (selected_file_descriptor_index == 0) {
        networking::socket_interface::get().handle_close_call(new_socket_index);
        return -1;
    }
    return selected_file_descriptor_index;
}

auto descriptor_interface::receive(uint64_t file_descriptor_index, span_t<byte_t> buffer,
                                   networking::internet_protocol_address_t *internet_protocol_address_address,
                                   networking::port_number_t *port_number_address) -> size_t {
    auto socket_index = this->file_descriptors[process::thread_scheduler::get().get_current_process_id()]
                            .data[file_descriptor_index]
                            .socket_index;
    return networking::socket_interface::get().handle_receive_call(
        socket_index, buffer, internet_protocol_address_address, port_number_address);
}

auto descriptor_interface::transmit(uint64_t file_descriptor_index, span_t<byte_t> buffer,
                                    networking::internet_protocol_address_t internet_protocol_address,
                                    networking::port_number_t port_number) -> size_t {
    auto socket_index = this->file_descriptors[process::thread_scheduler::get().get_current_process_id()]
                            .data[file_descriptor_index]
                            .socket_index;
    return networking::socket_interface::get().handle_transmit_call(socket_index, buffer, internet_protocol_address,
                                                                    port_number);
}

auto descriptor_interface::recover() -> void {
    this->lock.acquire();
    if (this->initialized) {
        this->lock.release();
        return;
    }
    this->initialized = true;
    this->lock.release();
    descriptor_interface::get().block_cache.recover_transaction();
}

} // namespace file

#include "../include/socket_interface.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/thread_scheduler.hpp"
#include "../include/transmission_control_protocol.hpp"
#include "../include/user_datagram_protocol.hpp"

namespace networking {

auto socket_interface::handle_open_call(socket_type_t socket_type) -> int {
    for (int i = 0; i < socket_interface_constants::maximum_number_of_sockets; i++) {
        auto &socket = this->sockets[i];
        socket.lock.acquire();
        if (socket.type == socket_type_t::unused) {
            socket.type = socket_type;
            socket.source_port_number = {};
            socket.control_block_index = SIZE_MAX;
            socket.lock.release();
            return i;
        }
        socket.lock.release();
    }
    return -1;
}

auto socket_interface::handle_close_call(int socket_index) -> bool {
    auto &socket = this->sockets[socket_index];
    socket.lock.acquire();
    request_t request = {};
    request.status = request_status_t::incomplete;
    request.type = request_type_t::close;
    request.active = false;
    request.buffer = {nullptr, 0};
    request.number_of_bytes_to_transfer = 0;
    request.number_of_bytes_transferred = 0;
    request.source_port_number = socket.source_port_number;
    request.destination_internet_protocol_address = {};
    request.destination_port_number = {};
    request.control_block_index = socket.control_block_index;
    request.next = {};
    switch (socket.type) {
    case socket_type_t::unused:
        socket.lock.release();
        return false;
    case socket_type_t::tcp:
        transmission_control_protocol_t::request(&request);
        break;
    case socket_type_t::udp:
        user_datagram_protocol_t::request(&request);
        break;
    }
    request.lock.acquire();
    while (request.status == request_status_t::incomplete) {
        process::thread_scheduler::get().sleep(&request, request.lock);
    }
    auto status = request.status;
    request.lock.release();
    socket.type = socket_type_t::unused;
    socket.source_port_number = {};
    socket.control_block_index = SIZE_MAX;
    socket.lock.release();
    return status == request_status_t::completed;
}

auto socket_interface::handle_bind_call(int socket_index, port_number_t source_port_number) -> bool {
    auto &socket = this->sockets[socket_index];
    socket.lock.acquire();
    auto socket_type = socket.type;
    socket.lock.release();
    for (auto &socket : this->sockets) {
        socket.lock.acquire();
        if (socket.type == socket_type && socket.source_port_number == source_port_number) {
            socket.lock.release();
            return false;
        }
        socket.lock.release();
    }
    socket.lock.acquire();
    switch (socket.type) {
    case socket_type_t::unused: {
        socket.lock.release();
        return false;
    }
    case socket_type_t::tcp: {
        socket.source_port_number = source_port_number;
        socket.lock.release();
        return true;
    }
    case socket_type_t::udp: {
        socket.source_port_number = source_port_number;
        request_t request = {};
        request.status = request_status_t::incomplete;
        request.type = request_type_t::open;
        request.active = false;
        request.buffer = {nullptr, 0};
        request.number_of_bytes_to_transfer = 0;
        request.number_of_bytes_transferred = 0;
        request.source_port_number = socket.source_port_number;
        request.destination_internet_protocol_address = {};
        request.destination_port_number = {};
        request.control_block_index = socket.control_block_index;
        request.next = {};
        user_datagram_protocol_t::request(&request);
        request.lock.acquire();
        while (request.status == request_status_t::incomplete) {
            process::thread_scheduler::get().sleep(&request, request.lock);
        }
        socket.control_block_index = request.control_block_index;
        auto status = request.status;
        request.lock.release();
        socket.lock.release();
        return status == request_status_t::completed;
    }
    default: {
        socket.lock.release();
        return false;
    }
    }
}

auto socket_interface::handle_connect_call(int socket_index,
                                           internet_protocol_address_t destination_internet_protocol_address,
                                           port_number_t destination_port_number) -> bool {
    auto &socket = this->sockets[socket_index];
    socket.lock.acquire();
    if (socket.type != socket_type_t::tcp) {
        socket.lock.release();
        return false;
    }
    if (socket.control_block_index == SIZE_MAX) {
        if (socket.source_port_number == 0) {
            socket.source_port_number = port_number_t{transmission_control_protocol_constants::default_port_number};
        } else {
            socket.lock.release();
            return false;
        }
    }
    request_t request = {};
    request.status = request_status_t::incomplete;
    request.type = request_type_t::open;
    request.active = true;
    request.buffer = {nullptr, 0};
    request.number_of_bytes_to_transfer = 0;
    request.number_of_bytes_transferred = 0;
    request.source_port_number = socket.source_port_number;
    request.destination_internet_protocol_address = destination_internet_protocol_address;
    request.destination_port_number = destination_port_number;
    request.control_block_index = socket.control_block_index;
    request.next = {};
    transmission_control_protocol_t::request(&request);
    request.lock.acquire();
    while (request.status == request_status_t::incomplete) {
        process::thread_scheduler::get().sleep(&request, request.lock);
    }
    socket.control_block_index = request.control_block_index;
    auto status = request.status;
    request.lock.release();
    socket.lock.release();
    return status == request_status_t::completed;
}

auto socket_interface::handle_listen_call(int socket_index) -> bool {
    auto &socket = this->sockets[socket_index];
    socket.lock.acquire();
    if (socket.type != socket_type_t::tcp) {
        socket.lock.release();
        return false;
    }
    if (socket.source_port_number == 0) {
        socket.lock.release();
        return false;
    }
    request_t request = {};
    request.status = request_status_t::incomplete;
    request.type = request_type_t::open;
    request.active = false;
    request.buffer = {nullptr, 0};
    request.number_of_bytes_to_transfer = 0;
    request.number_of_bytes_transferred = 0;
    request.source_port_number = socket.source_port_number;
    request.destination_internet_protocol_address = {};
    request.destination_port_number = {};
    request.control_block_index = socket.control_block_index;
    request.next = {};
    transmission_control_protocol_t::request(&request);
    request.lock.acquire();
    while (request.status == request_status_t::incomplete) {
        process::thread_scheduler::get().sleep(&request, request.lock);
    }
    socket.control_block_index = request.control_block_index;
    auto status = request.status;
    request.lock.release();
    socket.lock.release();
    return status == request_status_t::completed;
}

auto socket_interface::handle_accept_call(int socket_index) -> int {
    auto &socket = this->sockets[socket_index];
    socket.lock.acquire();
    if (socket.type != socket_type_t::tcp) {
        socket.lock.release();
        return -1;
    }
    if (socket.control_block_index == SIZE_MAX) {
        socket.lock.release();
        return -1;
    }

    auto is_established = transmission_control_protocol_t::sleep_until_established(socket.control_block_index);

    if (!is_established) {
        socket.lock.release();
        return -1;
    }

    int new_socket_index = -1;
    for (int i = 0; i < socket_interface_constants::maximum_number_of_sockets; i++) {
        if (i == socket_index) {
            continue;
        }
        auto &new_socket = this->sockets[i];
        new_socket.lock.acquire();
        if (new_socket.type == socket_type_t::unused) {
            new_socket.type = socket_type_t::tcp;
            new_socket.source_port_number = socket.source_port_number;
            new_socket.control_block_index = socket.control_block_index;
            new_socket_index = i;
            new_socket.lock.release();
            break;
        }
        new_socket.lock.release();
    }
    if (new_socket_index == -1) {
        socket.lock.release();
        return -1;
    }
    request_t request = {};
    request.status = request_status_t::incomplete;
    request.type = request_type_t::open;
    request.active = false;
    request.buffer = {nullptr, 0};
    request.number_of_bytes_to_transfer = 0;
    request.number_of_bytes_transferred = 0;
    request.source_port_number = socket.source_port_number;
    request.destination_internet_protocol_address = {};
    request.destination_port_number = {};
    request.control_block_index = socket.control_block_index;
    request.next = {};
    transmission_control_protocol_t::request(&request);
    request.lock.acquire();
    while (request.status == request_status_t::incomplete) {
        process::thread_scheduler::get().sleep(&request, request.lock);
    }
    socket.control_block_index = request.control_block_index;
    auto status = request.status;
    request.lock.release();
    socket.lock.release();
    if (status == request_status_t::completed) {
        return new_socket_index;
    }
    socket.lock.acquire();
    socket.type = socket_type_t::unused;
    socket.source_port_number = {};
    socket.lock.release();
    return -1;
}

auto socket_interface::handle_receive_call(int socket_index, span_t<byte_t> buffer,
                                           internet_protocol_address_t *internet_protocol_address_address,
                                           port_number_t *port_number_address) -> size_t {
    auto &socket = this->sockets[socket_index];
    socket.lock.acquire();
    if (socket.source_port_number == 0) {
        socket.lock.release();
        return 0;
    }
    if (socket.control_block_index == SIZE_MAX) {
        socket.lock.release();
        return 0;
    }
    if (socket.type == socket_type_t::udp &&
        (internet_protocol_address_address == nullptr || port_number_address == nullptr)) {
        socket.lock.release();
        return 0;
    }
    request_t request = {};
    request.status = request_status_t::incomplete;
    request.type = request_type_t::receive;
    request.active = false;
    request.buffer = buffer;
    request.number_of_bytes_to_transfer = buffer.size();
    request.number_of_bytes_transferred = 0;
    request.source_port_number = socket.source_port_number;
    request.destination_internet_protocol_address = {};
    request.destination_port_number = {};
    request.control_block_index = socket.control_block_index;
    request.next = {};
    switch (socket.type) {
    case socket_type_t::unused:
        socket.lock.release();
        return 0;
    case socket_type_t::tcp:
        transmission_control_protocol_t::request(&request);
        break;
    case socket_type_t::udp:
        user_datagram_protocol_t::request(&request);
        break;
    }
    request.lock.acquire();
    while (request.status == request_status_t::incomplete) {
        process::thread_scheduler::get().sleep(&request, request.lock);
    }
    if (socket.type == socket_type_t::udp) {
        *internet_protocol_address_address = request.destination_internet_protocol_address;
        *port_number_address = request.destination_port_number;
    }
    auto status = request.status;
    auto number_of_bytes_transferred = request.number_of_bytes_transferred;
    request.lock.release();
    socket.lock.release();
    if (status == request_status_t::completed) {
        return number_of_bytes_transferred;
    }
    return 0;
}

auto socket_interface::handle_transmit_call(int socket_index, span_t<byte_t> buffer,
                                            internet_protocol_address_t internet_protocol_address,
                                            port_number_t port_number) -> size_t {
    auto &socket = this->sockets[socket_index];
    socket.lock.acquire();
    if (socket.source_port_number == 0) {
        if (socket.type == socket_type_t::udp) {
            socket.source_port_number = port_number_t{user_datagram_protocol_constants::default_port_number};
        } else {
            socket.lock.release();
            return 0;
        }
    }
    if (socket.control_block_index == SIZE_MAX) {
        socket.lock.release();
        return 0;
    }
    if (socket.type == socket_type_t::udp && (internet_protocol_address == 0 || port_number == 0)) {
        socket.lock.release();
        return 0;
    }
    request_t request = {};
    request.status = request_status_t::incomplete;
    request.type = request_type_t::transmit;
    request.active = false;
    request.buffer = buffer;
    request.number_of_bytes_to_transfer = buffer.size();
    request.number_of_bytes_transferred = 0;
    request.source_port_number = socket.source_port_number;
    request.destination_internet_protocol_address = internet_protocol_address;
    request.destination_port_number = port_number;
    request.control_block_index = socket.control_block_index;
    request.next = {};
    switch (socket.type) {
    case socket_type_t::unused:
        socket.lock.release();
        return 0;
    case socket_type_t::tcp:
        transmission_control_protocol_t::request(&request);
        break;
    case socket_type_t::udp:
        user_datagram_protocol_t::request(&request);
        break;
    }
    this->transmit_lock.acquire();
    this->has_data_to_transmit = true;
    process::thread_scheduler::get().wake(&this->has_data_to_transmit);
    this->transmit_lock.release();
    request.lock.acquire();
    while (request.status == request_status_t::incomplete) {
        process::thread_scheduler::get().sleep(&request, request.lock);
    }
    auto status = request.status;
    auto number_of_bytes_transferred = request.number_of_bytes_transferred;
    request.lock.release();
    socket.lock.release();
    if (status == request_status_t::completed) {
        return number_of_bytes_transferred;
    }
    return 0;
}

auto socket_interface::handle_data_egress() -> void {
    while (true) {
        this->transmit_lock.acquire();
        while (!this->has_data_to_transmit) {
            process::thread_scheduler::get().sleep(&this->has_data_to_transmit, this->transmit_lock);
        }
        transmission_control_protocol_t::handle_transmit_requests();
        user_datagram_protocol_t::handle_transmit_requests();
        this->has_data_to_transmit = false;
        this->transmit_lock.release();
    }
}

} // namespace networking

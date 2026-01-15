#ifndef SOCKET_LAYER_HPP
#define SOCKET_LAYER_HPP

#include "../lib/span.hpp"
#include "packet_buffer.hpp"
#include "spin_lock.hpp"
#include "thread_scheduler.hpp"

#include <cstddef>
#include <cstdint>

namespace networking {

enum class request_status_t {
    incomplete,
    completed,
    locally_closed_error,
    remotely_closed_error,
    does_not_exist_error,
    already_exists_error,
    not_enough_resources_error,
    invalid_arguments_error,
    unexpected_error
};

enum class request_type_t { open, close, receive, transmit };

struct request_t {
    synchronization::spin_lock lock;
    request_status_t status = {};
    request_type_t type = {};
    bool active = true;
    span_t<byte_t> buffer{nullptr, 0};
    size_t number_of_bytes_to_transfer = 0;
    size_t number_of_bytes_transferred = 0;
    port_number_t source_port_number = {};
    internet_protocol_address_t destination_internet_protocol_address = {};
    port_number_t destination_port_number = {};
    size_t control_block_index = SIZE_MAX;
    uint32_t acknowledgement_sequence_number{};
    request_t *next = nullptr;
};

class request_queue_t {
public:
    auto enqueue(request_t *request_address) -> void {
        this->lock.acquire();
        if (this->head == nullptr && this->tail == nullptr) {
            this->head = request_address;
            this->tail = request_address;
            this->count += 1;
            this->lock.release();
            return;
        }
        this->tail->next = request_address;
        this->tail = request_address;
        this->count += 1;
        this->lock.release();
    }

    auto dequeue() -> request_t * {
        this->lock.acquire();
        if (this->head == nullptr && this->tail == nullptr) {
            this->lock.release();
            return {};
        }
        if (this->head == this->tail) {
            auto *request_address = this->head;
            this->head = {};
            this->tail = {};
            this->count -= 1;
            this->lock.release();
            return request_address;
        }
        auto *request_address = this->head;
        this->head = head->next;
        this->count -= 1;
        this->lock.release();
        return request_address;
    }

    auto clear(request_status_t request_status) -> void {
        auto *request_address = this->dequeue();
        while (request_address != nullptr) {
            request_address->lock.acquire();
            request_address->status = request_status;
            process::thread_scheduler::get().wake(request_address);
            request_address->lock.release();
            request_address = this->dequeue();
        }
    }

    [[nodiscard]] auto length() const -> int {
        return this->count;
    }

    auto front() -> request_t * {
        return this->head;
    }

private:
    synchronization::spin_lock lock;
    request_t *head = {};
    request_t *tail = {};
    int count = 0;
};

enum class socket_type_t { unused, tcp, udp };

struct socket_t {
    synchronization::spin_lock lock = {};
    socket_type_t type = socket_type_t::unused;
    port_number_t source_port_number = {};
    size_t control_block_index = SIZE_MAX;
};

class socket_interface {
public:
    static auto get() -> socket_interface & {
        static socket_interface instance;
        return instance;
    }

    auto handle_open_call(socket_type_t socket_type) -> int;
    auto handle_close_call(int socket_index) -> bool;
    auto handle_connect_call(int socket_index, internet_protocol_address_t destination_internet_protocol_address,
                             port_number_t destination_port_number) -> bool;
    auto handle_bind_call(int socket_index, port_number_t source_port_number) -> bool;
    auto handle_listen_call(int socket_index) -> bool;
    auto handle_accept_call(int socket_index) -> int;
    auto handle_receive_call(int socket_index, span_t<byte_t> buffer,
                             internet_protocol_address_t *internet_protocol_address_address,
                             port_number_t *port_number_address) -> size_t;
    auto handle_transmit_call(int socket_index, span_t<byte_t> buffer,
                              internet_protocol_address_t internet_protocol_address, port_number_t port_number)
        -> size_t;

    auto handle_data_egress() -> void;

    socket_interface(const socket_interface &) = delete;
    auto operator=(const socket_interface &) -> socket_interface & = delete;
    socket_interface(socket_interface &&) = delete;
    auto operator=(socket_interface &&) -> socket_interface & = delete;

private:
    array_t<socket_t, socket_interface_constants::maximum_number_of_sockets> sockets = {};

    synchronization::spin_lock transmit_lock{};
    bool has_data_to_transmit = false;

    socket_interface() = default;
    ~socket_interface() = default;
};

} // namespace networking

#endif

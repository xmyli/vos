#include "../include/user_datagram_protocol.hpp"
#include "../include/internet_protocol.hpp"
#include "../include/panic.hpp"

namespace networking {

auto user_datagram_protocol_t::receive(packet_buffer_t *packet_buffer_address, uint16_t length,
                                       networking::internet_protocol_address_t source_internet_protocol_address)
    -> void {
    user_datagram_protocol_header_t header = {};
    if (!packet_buffer_address->pop_front(as_writable_bytes(span_t(&header, 1)))) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (header.get_length_field() != length) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    length -= sizeof(user_datagram_protocol_header_t);
    if (length > packet_buffer_address->get_length()) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    auto *temporary_buffer = memory::buddy_allocator::get().allocate<byte_t>(0);
    packet_buffer_address->pop_back(span_t(temporary_buffer, packet_buffer_address->get_length() - length));
    memory::buddy_allocator::get().deallocate(temporary_buffer);
    for (auto &connection : user_datagram_protocol_t::get().connections) {
        if (connection.source_port_number == header.get_destination_port_field()) {
            auto *request_address = connection.receive_request_addresses.dequeue();
            if (request_address != nullptr) {
                auto number_of_bytes_to_transfer = request_address->number_of_bytes_to_transfer;
                if (number_of_bytes_to_transfer > packet_buffer_address->get_length()) {
                    number_of_bytes_to_transfer = packet_buffer_address->get_length();
                }
                packet_buffer_address->pop_front(
                    span_t(&request_address->buffer[request_address->number_of_bytes_transferred],
                           number_of_bytes_to_transfer));
                packet_buffer_t::deallocate(packet_buffer_address);
                request_address->lock.acquire();
                request_address->number_of_bytes_transferred += number_of_bytes_to_transfer;
                request_address->number_of_bytes_to_transfer -= number_of_bytes_to_transfer;
                request_address->status = request_status_t::completed;
                request_address->destination_internet_protocol_address = source_internet_protocol_address;
                request_address->destination_port_number = header.get_source_port_field();
                process::thread_scheduler::get().wake(request_address);
                request_address->lock.release();
            } else {
                packet_buffer_address->push_front(as_writable_bytes(span_t(&header, 1)));
                packet_buffer_address->push_front(as_writable_bytes(span_t(&source_internet_protocol_address, 1)));
                connection.received_packets.enqueue(packet_buffer_address);
            }
            return;
        }
    }
    packet_buffer_t::deallocate(packet_buffer_address);
}

auto user_datagram_protocol_t::transmit(packet_buffer_t *packet_buffer_address,
                                        user_datagram_protocol_packet_configuration_t packet_configuration) -> void {
    user_datagram_protocol_header_t header = {};
    header.set_source_port_field(packet_configuration.source_port_number);
    header.set_destination_port_field(packet_configuration.destination_port_number);
    header.set_length_field(sizeof(header) + packet_buffer_address->get_length());
    if (!packet_buffer_address->push_front(as_writable_bytes(span_t(&header, 1)))) {
        panic("user_datagram_protocol::transmit");
        return;
    }
    internet_protocol_t::transmit(packet_buffer_address, protocol_type_t::user_datagram_protocol,
                                  packet_configuration.destination_internet_protocol_address);
}

auto user_datagram_protocol_t::request(request_t *request_address) -> void {
    request_address->lock.acquire();
    if (request_address->control_block_index == SIZE_MAX) {
        request_address->status = request_status_t::invalid_arguments_error;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
    } else {
        request_address->lock.release();
    }
    switch (request_address->type) {
    case request_type_t::open: {
        for (auto &connection : user_datagram_protocol_t::get().connections) {
            connection.lock.acquire();
            if (connection.source_port_number == request_address->source_port_number) {
                request_address->lock.acquire();
                request_address->status = request_status_t::already_exists_error;
                process::thread_scheduler::get().wake(request_address);
                request_address->lock.release();
                connection.lock.release();
                return;
            }
            connection.lock.release();
        }
        for (size_t control_block_index = 0;
             control_block_index < user_datagram_protocol_constants::maximum_number_of_connections;
             control_block_index += 1) {
            auto &connection = user_datagram_protocol_t::get().connections[control_block_index];
            connection.lock.acquire();
            if (connection.source_port_number == 0) {
                connection.source_port_number = request_address->source_port_number;
                request_address->lock.acquire();
                request_address->status = request_status_t::completed;
                request_address->control_block_index = control_block_index;
                process::thread_scheduler::get().wake(request_address);
                request_address->lock.release();
                connection.lock.release();
                return;
            }
            connection.lock.release();
        }
        request_address->lock.acquire();
        request_address->status = request_status_t::not_enough_resources_error;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
        return;
    }
    case request_type_t::close: {
        for (auto &connection : user_datagram_protocol_t::get().connections) {
            connection.lock.acquire();
            if (connection.source_port_number == request_address->source_port_number) {
                connection.receive_request_addresses.clear(request_status_t::locally_closed_error);
                connection.transmit_request_addresses.clear(request_status_t::locally_closed_error);
                connection.received_packets.clear();
                connection.source_port_number = {};
                request_address->lock.acquire();
                request_address->status = request_status_t::completed;
                process::thread_scheduler::get().wake(request_address);
                request_address->lock.release();
                connection.lock.release();
                return;
            }
            connection.lock.release();
        }
        request_address->lock.acquire();
        request_address->status = request_status_t::does_not_exist_error;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
        return;
    }
    case request_type_t::receive: {
        for (auto &connection : user_datagram_protocol_t::get().connections) {
            connection.lock.acquire();
            if (connection.source_port_number == request_address->source_port_number) {
                auto *packet_buffer_address = connection.received_packets.dequeue();
                if (packet_buffer_address != nullptr) {
                    networking::internet_protocol_address_t internet_protocol_address = {};
                    user_datagram_protocol_header_t user_datagram_protocol_header = {};
                    packet_buffer_address->pop_front(as_writable_bytes(span_t(&internet_protocol_address, 1)));
                    packet_buffer_address->pop_front(as_writable_bytes(span_t(&user_datagram_protocol_header, 1)));
                    auto number_of_bytes_to_transfer = request_address->number_of_bytes_to_transfer;
                    if (number_of_bytes_to_transfer > packet_buffer_address->get_length()) {
                        number_of_bytes_to_transfer = packet_buffer_address->get_length();
                    }
                    packet_buffer_address->pop_front(
                        span_t(&request_address->buffer[request_address->number_of_bytes_transferred],
                               number_of_bytes_to_transfer));
                    packet_buffer_t::deallocate(packet_buffer_address);
                    request_address->lock.acquire();
                    request_address->number_of_bytes_transferred += number_of_bytes_to_transfer;
                    request_address->number_of_bytes_to_transfer -= number_of_bytes_to_transfer;
                    request_address->status = request_status_t::completed;
                    request_address->destination_internet_protocol_address = internet_protocol_address;
                    request_address->destination_port_number = user_datagram_protocol_header.get_source_port_field();
                    process::thread_scheduler::get().wake(request_address);
                    request_address->lock.release();
                } else {
                    connection.receive_request_addresses.enqueue(request_address);
                }
                connection.lock.release();
                return;
            }
            connection.lock.release();
        }
        request_address->lock.acquire();
        request_address->status = request_status_t::does_not_exist_error;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
        return;
    }
    case request_type_t::transmit: {
        for (auto &connection : user_datagram_protocol_t::get().connections) {
            connection.lock.acquire();
            if (connection.source_port_number == request_address->source_port_number) {
                connection.transmit_request_addresses.enqueue(request_address);
                connection.lock.release();
                return;
            }
            connection.lock.release();
        }
        request_address->lock.acquire();
        request_address->status = request_status_t::does_not_exist_error;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
        return;
    }
    }
}

auto user_datagram_protocol_t::handle_transmit_requests() -> void {
    for (auto &connection : user_datagram_protocol_t::get().connections) {
        auto *request_address = connection.transmit_request_addresses.dequeue();
        while (request_address != nullptr) {
            request_address->lock.acquire();
            while (request_address->number_of_bytes_to_transfer > 0) {
                auto number_of_bytes_to_transfer = request_address->number_of_bytes_to_transfer;
                if (number_of_bytes_to_transfer > user_datagram_protocol_constants::maximum_payload_size) {
                    number_of_bytes_to_transfer = user_datagram_protocol_constants::maximum_payload_size;
                }
                auto *packet_buffer_address = packet_buffer_t::allocate();
                packet_buffer_address->push_back(
                    span_t(&request_address->buffer[request_address->number_of_bytes_transferred],
                           number_of_bytes_to_transfer));
                request_address->number_of_bytes_transferred += number_of_bytes_to_transfer;
                request_address->number_of_bytes_to_transfer -= number_of_bytes_to_transfer;
                user_datagram_protocol_packet_configuration_t packet_configuration = {
                    .source_port_number = connection.source_port_number,
                    .destination_port_number = request_address->destination_port_number,
                    .destination_internet_protocol_address = request_address->destination_internet_protocol_address};
                transmit(packet_buffer_address, packet_configuration);
            }
            request_address->status = request_status_t::completed;
            process::thread_scheduler::get().wake(request_address);
            request_address->lock.release();
            request_address = connection.transmit_request_addresses.dequeue();
        }
    }
}

} // namespace networking

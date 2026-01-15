#include "../include/transmission_control_protocol.hpp"
#include "../include/internet_protocol.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/panic.hpp"

namespace networking {

auto get_new_initial_sequence_number() -> uint32_t {
    return transmission_control_protocol_constants::initial_sequence_number;
}

auto transmission_control_protocol_t::receive(packet_buffer_t *packet_buffer_address,
                                              internet_protocol_packet_header_t internet_protocol_header) -> void {
    auto *temporary_buffer = memory::buddy_allocator::get().allocate<byte_t>(0);

    auto padding_size = packet_buffer_address->get_length() -
                        (internet_protocol_header.get_total_length_field() - sizeof(internet_protocol_packet_header_t));
    packet_buffer_address->pop_back(span_t(temporary_buffer, padding_size));

    transmission_control_protocol_header_t transmission_control_protocol_header = {};
    if (!packet_buffer_address->pop_front(as_writable_bytes(span_t(&transmission_control_protocol_header, 1)))) {
        packet_buffer_t::deallocate(packet_buffer_address);
    }

    size_t size_of_options = (transmission_control_protocol_header.get_data_offset_field() >> 4) * sizeof(uint32_t) -
                             sizeof(transmission_control_protocol_header_t);
    packet_buffer_address->pop_front(span_t(temporary_buffer, size_of_options));

    memory::buddy_allocator::get().deallocate(temporary_buffer);

    auto transmission_control_block_index =
        transmission_control_protocol_t::get().get_transmission_control_block_index_by_address(
            transmission_control_protocol_header.get_destination_port_field(),
            internet_protocol_header.get_source_address_field(),
            transmission_control_protocol_header.get_source_port_field(), false);
    if (transmission_control_block_index == SIZE_MAX) {
        transmission_control_block_index =
            transmission_control_protocol_t::get().get_transmission_control_block_index_by_address(
                transmission_control_protocol_header.get_destination_port_field(),
                internet_protocol_header.get_source_address_field(),
                transmission_control_protocol_header.get_source_port_field(), true);
    }
    if (transmission_control_block_index == SIZE_MAX) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }

    transmission_control_protocol_t::get().handle_segment_arrival(transmission_control_block_index,
                                                                  transmission_control_protocol_header,
                                                                  internet_protocol_header, packet_buffer_address);
}

auto transmission_control_protocol_t::transmit(
    packet_buffer_t *packet_buffer_address, transmission_control_block_t &transmission_control_block,
    transmission_control_protocol_packet_configuration_t packet_configuration) -> void {
    transmission_control_protocol_header_t header = {};
    header.set_source_port_field(transmission_control_block.source_port_number);
    header.set_destination_port_field(transmission_control_block.destination_port_number);
    header.set_sequence_number_field(packet_configuration.sequence_number);
    header.set_acknowledgement_number_field(packet_configuration.acknowledgement_number);
    header.set_data_offset_field((sizeof(transmission_control_protocol_header_t) / sizeof(uint32_t)) << 4);
    header.set_acknowledgement_flag(packet_configuration.ack);
    header.set_reset_flag(packet_configuration.rst);
    header.set_synchronization_flag(packet_configuration.syn);
    header.set_finish_flag(packet_configuration.fin);
    if (packet_configuration.fin) {
        transmission_control_block.fin_state = fin_state_t::unacknowledged;
        transmission_control_block.sequence_number_of_fin = packet_configuration.sequence_number;
    }
    header.set_window_field(transmission_control_block.receive_window_size);

    if (!packet_buffer_address->push_front(as_writable_bytes(span_t(&header, 1)))) {
        panic("transmission_control_protocol::transmit");
    }

    pseudo_header_t pseudo_header = {};
    pseudo_header.set_source_address_field(
        networking::internet_protocol_address_t{internet_protocol_constants::local_internet_protocol_address});
    pseudo_header.set_destination_address_field(transmission_control_block.destination_internet_protocol_address);
    pseudo_header.set_protocol_field(protocol_type_t::transmission_control_protocol);
    pseudo_header.set_tcp_length_field(packet_buffer_address->get_length());
    if (!packet_buffer_address->push_front(as_writable_bytes(span_t(&pseudo_header, 1)))) {
        panic("transmission_control_protocol::transmit");
    }

    auto checksum = packet_buffer_address->checksum();
    packet_buffer_address->pop_front(as_writable_bytes(span_t(&pseudo_header, 1)));
    packet_buffer_address->pop_front(as_writable_bytes(span_t(&header, 1)));
    header.set_checksum_field(checksum);

    auto *temporary_buffer = memory::buddy_allocator::get().allocate<byte_t>(0);
    auto temporary_buffer_size = packet_buffer_address->get_length();
    packet_buffer_address->pop_back(span_t(temporary_buffer, temporary_buffer_size));
    packet_buffer_address->push_back(span_t(temporary_buffer, temporary_buffer_size));
    packet_buffer_address->push_front(as_writable_bytes(span_t(&header, 1)));
    auto *packet_buffer_address_for_retransmission = packet_buffer_t::allocate();
    packet_buffer_address_for_retransmission->push_back(span_t(temporary_buffer, temporary_buffer_size));
    packet_buffer_address_for_retransmission->push_front(as_writable_bytes(span_t(&header, 1)));
    memory::buddy_allocator::get().deallocate(temporary_buffer);

    if (packet_configuration.syn || packet_configuration.fin || temporary_buffer_size > 0) {
        packet_buffer_address_for_retransmission->push_front(
            as_writable_bytes(span_t(&transmission_control_block.destination_internet_protocol_address, 1)));
        transmission_control_block.transmitted_data_queue.enqueue(packet_buffer_address_for_retransmission);
    }

    internet_protocol_t::transmit(packet_buffer_address, protocol_type_t::transmission_control_protocol,
                                  transmission_control_block.destination_internet_protocol_address);
}

auto transmission_control_protocol_t::timeout() -> void {
    for (auto &transmission_control_block : transmission_control_protocol_t::get().transmission_control_blocks) {
        if (transmission_control_block.state != connection_state_t::closed &&
            transmission_control_block.state != connection_state_t::listen) {
            auto length = transmission_control_block.transmitted_data_queue.length();
            for (int i = 0; i < length; i++) {
                auto *packet_buffer_address = transmission_control_block.transmitted_data_queue.dequeue();
                if (packet_buffer_address->get_number_of_retransmissions() <
                    transmission_control_protocol_constants::maximum_number_of_retransmissions) {
                    networking::internet_protocol_address_t destination_internet_protocol_address = {};
                    packet_buffer_address->pop_front(
                        as_writable_bytes(span_t(&destination_internet_protocol_address, 1)));

                    transmission_control_protocol_header_t transmission_control_protocol_header = {};
                    auto *temporary_buffer = memory::buddy_allocator::get().allocate<byte_t>(0);
                    packet_buffer_address->pop_front(
                        as_writable_bytes(span_t(&transmission_control_protocol_header, 1)));
                    auto temporary_buffer_size = packet_buffer_address->get_length();
                    packet_buffer_address->pop_back(span_t(temporary_buffer, temporary_buffer_size));
                    packet_buffer_address->push_back(span_t(temporary_buffer, temporary_buffer_size));
                    packet_buffer_address->push_front(
                        as_writable_bytes(span_t(&transmission_control_protocol_header, 1)));
                    packet_buffer_address->push_front(
                        as_writable_bytes(span_t(&destination_internet_protocol_address, 1)));
                    packet_buffer_address->set_number_of_retransmissions(
                        packet_buffer_address->get_number_of_retransmissions() + 1);
                    transmission_control_block.transmitted_data_queue.enqueue(packet_buffer_address);

                    auto *packet_buffer_address_for_retransmission = packet_buffer_t::allocate();
                    packet_buffer_address_for_retransmission->push_back(
                        span_t(temporary_buffer, temporary_buffer_size));
                    packet_buffer_address_for_retransmission->push_front(
                        as_writable_bytes(span_t(&transmission_control_protocol_header, 1)));
                    memory::buddy_allocator::get().deallocate(temporary_buffer);

                    internet_protocol_t::transmit(packet_buffer_address_for_retransmission,
                                                  protocol_type_t::transmission_control_protocol,
                                                  destination_internet_protocol_address);
                } else {
                    delete_transmission_control_block(transmission_control_block,
                                                      request_status_t::remotely_closed_error);
                }
            }
        }
    }
}

auto transmission_control_protocol_t::sleep_until_established(size_t transmission_control_block_index) -> bool {
    auto &transmission_control_block =
        transmission_control_protocol_t::get().transmission_control_blocks[transmission_control_block_index];
    transmission_control_block.lock.acquire();
    while (transmission_control_block.state == connection_state_t::listen ||
           transmission_control_block.state == connection_state_t::syn_sent ||
           transmission_control_block.state == connection_state_t::syn_received) {
        process::thread_scheduler::get().sleep(&transmission_control_block, transmission_control_block.lock);
    }
    auto is_established = false;
    if (transmission_control_block.state == connection_state_t::established ||
        transmission_control_block.state == connection_state_t::close_wait) {
        is_established = true;
    }
    transmission_control_block.lock.release();
    return is_established;
}

auto transmission_control_protocol_t::open_connection(request_t *request_address) -> void {
    for (size_t transmission_control_block_index = 0;
         transmission_control_block_index < transmission_control_protocol_constants::maximum_number_of_connections;
         transmission_control_block_index += 1) {
        auto &transmission_control_block = this->transmission_control_blocks[transmission_control_block_index];
        if (transmission_control_block.state == connection_state_t::closed) {
            transmission_control_block.active_opened = request_address->active;
            transmission_control_block.source_port_number = request_address->source_port_number;
            transmission_control_block.destination_internet_protocol_address =
                request_address->destination_internet_protocol_address;
            transmission_control_block.destination_port_number = request_address->destination_port_number;
            if (request_address->active) {
                if (transmission_control_block.source_port_number == 0) {
                    transmission_control_block.source_port_number =
                        networking::port_number_t{transmission_control_protocol_constants::default_port_number};
                }
                if (request_address->destination_internet_protocol_address == 0 ||
                    request_address->destination_port_number == 0) {
                    request_address->lock.acquire();
                    request_address->status = request_status_t::invalid_arguments_error;
                    process::thread_scheduler::get().wake(request_address);
                    request_address->lock.release();
                    return;
                }
                transmission_control_block.initial_send_sequence_number = get_new_initial_sequence_number();
                auto *syn_segment_address = packet_buffer_t::allocate();
                transmission_control_protocol_packet_configuration_t packet_configuration = {
                    .sequence_number = transmission_control_block.initial_send_sequence_number,
                    .acknowledgement_number{},
                    .ack = false,
                    .rst = false,
                    .syn = true,
                    .fin = false};
                this->transmit(syn_segment_address, transmission_control_block, packet_configuration);
                transmission_control_block.oldest_unacknowledged_sequence_number =
                    transmission_control_block.initial_send_sequence_number;
                transmission_control_block.next_uint32_to_transmit =
                    transmission_control_block.initial_send_sequence_number + 1;
                transmission_control_block.state = connection_state_t::syn_sent;
                process::thread_scheduler::get().wake(&transmission_control_block);
                // device::pl011::printf("closed -> syn_sent\n");
                transmission_control_block.open_request_address = request_address;
                return;
            }
            if (request_address->source_port_number == 0) {
                request_address->lock.acquire();
                request_address->status = request_status_t::invalid_arguments_error;
                process::thread_scheduler::get().wake(request_address);
                request_address->lock.release();
                return;
            }
            transmission_control_block.state = connection_state_t::listen;
            process::thread_scheduler::get().wake(&transmission_control_block);
            // device::pl011::printf("closed -> listen\n");
            request_address->lock.acquire();
            request_address->status = request_status_t::completed;
            request_address->control_block_index = transmission_control_block_index;
            process::thread_scheduler::get().wake(request_address);
            request_address->lock.release();
            return;
        }
    }
    request_address->lock.acquire();
    request_address->status = request_status_t::not_enough_resources_error;
    process::thread_scheduler::get().wake(request_address);
    request_address->lock.release();
}

auto transmission_control_protocol_t::close_connection(request_t *request_address) -> void {
    if (request_address->control_block_index == SIZE_MAX) {
        return;
    }
    auto &transmission_control_block = this->transmission_control_blocks[request_address->control_block_index];
    switch (transmission_control_block.state) {
    case connection_state_t::closed:
    case connection_state_t::listen:
    case connection_state_t::syn_sent: {
        delete_transmission_control_block(transmission_control_block, request_status_t::locally_closed_error);
        request_address->lock.acquire();
        request_address->status = request_status_t::completed;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
        return;
    }
    case connection_state_t::syn_received:
    case connection_state_t::established: {
        transmission_control_block.state = connection_state_t::fin_wait_1;
        // device::pl011::printf("syn_received/established -> fin_wait_1\n");
        auto *fin_segment_address = packet_buffer_t::allocate();
        transmission_control_protocol_packet_configuration_t packet_configuration = {
            .sequence_number = transmission_control_block.next_uint32_to_transmit,
            .acknowledgement_number = transmission_control_block.next_uint32_to_receive,
            .ack = true,
            .rst = false,
            .syn = false,
            .fin = true};
        this->transmit(fin_segment_address, transmission_control_block, packet_configuration);
        transmission_control_block.next_uint32_to_transmit += 1;
        process::thread_scheduler::get().wake(&transmission_control_block);
        transmission_control_block.close_request_address = request_address;
        return;
    }
    case connection_state_t::close_wait: {
        transmission_control_block.state = connection_state_t::last_ack;
        // device::pl011::printf("close_wait -> last_ack\n");
        auto *fin_segment_address = packet_buffer_t::allocate();
        transmission_control_protocol_packet_configuration_t packet_configuration = {
            .sequence_number = transmission_control_block.next_uint32_to_transmit,
            .acknowledgement_number = transmission_control_block.next_uint32_to_receive,
            .ack = true,
            .rst = false,
            .syn = false,
            .fin = true};
        this->transmit(fin_segment_address, transmission_control_block, packet_configuration);
        transmission_control_block.next_uint32_to_transmit += 1;
        process::thread_scheduler::get().wake(&transmission_control_block);
        transmission_control_block.close_request_address = request_address;
        return;
    }
    case connection_state_t::fin_wait_1:
    case connection_state_t::fin_wait_2:
    case connection_state_t::closing:
    case connection_state_t::last_ack:
    case connection_state_t::time_wait: {
        request_address->lock.acquire();
        request_address->status = request_status_t::locally_closed_error;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
        return;
    }
    }
}

auto transmission_control_protocol_t::receive_data(request_t *request_address) -> void {
    if (request_address->control_block_index == SIZE_MAX) {
        request_address->lock.acquire();
        request_address->status = request_status_t::invalid_arguments_error;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
        return;
    }
    auto &transmission_control_block = this->transmission_control_blocks[request_address->control_block_index];
    switch (transmission_control_block.state) {
    case connection_state_t::listen:
    case connection_state_t::syn_sent:
    case connection_state_t::syn_received: {
        transmission_control_block.receive_request_addresses.enqueue(request_address);
        return;
    }
    case connection_state_t::established:
    case connection_state_t::fin_wait_1:
    case connection_state_t::fin_wait_2:
    case connection_state_t::close_wait: {
        while (request_address != nullptr && transmission_control_block.received_data_queue.length() > 0) {
            auto *packet_buffer_address = transmission_control_block.received_data_queue.front();
            auto number_of_bytes_to_transfer = request_address->number_of_bytes_to_transfer;
            if (number_of_bytes_to_transfer > packet_buffer_address->get_length()) {
                number_of_bytes_to_transfer = packet_buffer_address->get_length();
            }
            packet_buffer_address->pop_front(span_t(
                &request_address->buffer[request_address->number_of_bytes_transferred], number_of_bytes_to_transfer));
            if (packet_buffer_address->get_length() == 0) {
                packet_buffer_t::deallocate(packet_buffer_address);
                transmission_control_block.received_data_queue.dequeue();
            }
            request_address->lock.acquire();
            request_address->number_of_bytes_transferred += number_of_bytes_to_transfer;
            request_address->number_of_bytes_to_transfer -= number_of_bytes_to_transfer;
            if (request_address->number_of_bytes_to_transfer == 0) {
                request_address->status = request_status_t::completed;
                process::thread_scheduler::get().wake(request_address);
                request_address->lock.release();
                request_address = {};
            } else {
                request_address->lock.release();
            }
        }
        if (request_address != nullptr) {
            if (request_address->number_of_bytes_transferred > 0 ||
                transmission_control_block.state == connection_state_t::close_wait) {
                request_address->lock.acquire();
                request_address->status = request_status_t::completed;
                process::thread_scheduler::get().wake(request_address);
                request_address->lock.release();
            } else {
                transmission_control_block.receive_request_addresses.enqueue(request_address);
            }
        }
        return;
    }
    case connection_state_t::closed:
    case connection_state_t::closing:
    case connection_state_t::last_ack:
    case connection_state_t::time_wait: {
        request_address->lock.acquire();
        request_address->status = request_status_t::locally_closed_error;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
        return;
    }
    }
}

auto transmission_control_protocol_t::transmit_data(request_t *request_address) -> void {
    if (request_address->control_block_index == SIZE_MAX) {
        request_address->lock.acquire();
        request_address->status = request_status_t::invalid_arguments_error;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
        return;
    }
    auto &transmission_control_block = this->transmission_control_blocks[request_address->control_block_index];
    switch (transmission_control_block.state) {
    case connection_state_t::listen: {
        if (transmission_control_block.destination_internet_protocol_address != 0 &&
            transmission_control_block.destination_port_number != 0) {
            transmission_control_block.active_opened = true;
            transmission_control_block.initial_send_sequence_number = get_new_initial_sequence_number();
            auto *syn_segment_address = packet_buffer_t::allocate();
            transmission_control_protocol_packet_configuration_t packet_configuration = {
                .sequence_number = transmission_control_block.initial_send_sequence_number,
                .acknowledgement_number{},
                .ack = false,
                .rst = false,
                .syn = true,
                .fin = false};
            this->transmit(syn_segment_address, transmission_control_block, packet_configuration);
            transmission_control_block.oldest_unacknowledged_sequence_number =
                transmission_control_block.initial_send_sequence_number;
            transmission_control_block.next_uint32_to_transmit =
                transmission_control_block.initial_send_sequence_number + 1;
            transmission_control_block.state = connection_state_t::syn_sent;
            process::thread_scheduler::get().wake(&transmission_control_block);
            // device::pl011::printf("listen -> syn_sent\n");
            transmission_control_block.lock.acquire();
            transmission_control_block.transmit_request_addresses.enqueue(request_address);
            process::thread_scheduler::get().wake(&transmission_control_block.transmit_request_addresses);
            transmission_control_block.lock.release();
        } else {
            request_address->lock.acquire();
            request_address->status = request_status_t::invalid_arguments_error;
            process::thread_scheduler::get().wake(request_address);
            request_address->lock.release();
        }
        return;
    }
    case connection_state_t::syn_sent:
    case connection_state_t::syn_received:
    case connection_state_t::established:
    case connection_state_t::close_wait: {
        transmission_control_block.lock.acquire();
        transmission_control_block.transmit_request_addresses.enqueue(request_address);
        process::thread_scheduler::get().wake(&transmission_control_block.transmit_request_addresses);
        transmission_control_block.lock.release();
        return;
    }
    case connection_state_t::closed:
    case connection_state_t::fin_wait_1:
    case connection_state_t::fin_wait_2:
    case connection_state_t::closing:
    case connection_state_t::last_ack:
    case connection_state_t::time_wait: {
        request_address->lock.acquire();
        request_address->status = request_status_t::invalid_arguments_error;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
        return;
    }
    }
}

auto transmission_control_protocol_t::handle_segment_arrival(
    size_t transmission_control_block_index,
    transmission_control_protocol_header_t transmission_control_protocol_header,
    internet_protocol_packet_header_t internet_protocol_header, packet_buffer_t *packet_buffer_address) -> void {
    auto &transmission_control_block = this->transmission_control_blocks[transmission_control_block_index];
    switch (transmission_control_block.state) {
    case connection_state_t::closed:
        this->handle_segment_arrival_in_closed_state(transmission_control_block_index,
                                                     transmission_control_protocol_header, packet_buffer_address);
        break;
    case connection_state_t::listen:
        this->handle_segment_arrival_in_listen_state(transmission_control_block_index,
                                                     transmission_control_protocol_header, internet_protocol_header,
                                                     packet_buffer_address);
        break;
    case connection_state_t::syn_sent:
        this->handle_segment_arrival_in_syn_sent_state(transmission_control_block_index,
                                                       transmission_control_protocol_header, internet_protocol_header,
                                                       packet_buffer_address);
        break;
    case connection_state_t::syn_received:
    case connection_state_t::established:
    case connection_state_t::fin_wait_1:
    case connection_state_t::fin_wait_2:
    case connection_state_t::close_wait:
    case connection_state_t::closing:
    case connection_state_t::last_ack:
    case connection_state_t::time_wait:
        this->handle_segment_arrival_in_other_states(transmission_control_block_index,
                                                     transmission_control_protocol_header, internet_protocol_header,
                                                     packet_buffer_address);
        break;
    }
}

auto transmission_control_protocol_t::handle_segment_arrival_in_closed_state(
    size_t transmission_control_block_index,
    transmission_control_protocol_header_t transmission_control_protocol_header, packet_buffer_t *packet_buffer_address)
    -> void {
    auto &transmission_control_block = this->transmission_control_blocks[transmission_control_block_index];
    if (!transmission_control_protocol_header.get_reset_flag()) {
        auto *reset_segment_address = packet_buffer_t::allocate();
        if (transmission_control_protocol_header.get_acknowledgement_flag()) {
            transmission_control_protocol_packet_configuration_t packet_configuration = {
                .sequence_number = transmission_control_protocol_header.get_acknowledgement_number_field(),
                .acknowledgement_number{},
                .ack = false,
                .rst = true,
                .syn = false,
                .fin = false};
            this->transmit(reset_segment_address, transmission_control_block, packet_configuration);
        } else {
            transmission_control_protocol_packet_configuration_t packet_configuration = {
                .sequence_number{},
                .acknowledgement_number = transmission_control_protocol_header.get_sequence_number_field(),
                .ack = true,
                .rst = true,
                .syn = false,
                .fin = false};
            packet_configuration.acknowledgement_number += packet_buffer_address->get_length();
            this->transmit(reset_segment_address, transmission_control_block, packet_configuration);
        }
    }
    packet_buffer_t::deallocate(packet_buffer_address);
}

auto transmission_control_protocol_t::handle_segment_arrival_in_listen_state(
    size_t transmission_control_block_index,
    transmission_control_protocol_header_t transmission_control_protocol_header,
    internet_protocol_packet_header_t internet_protocol_header, packet_buffer_t *packet_buffer_address) -> void {
    auto &transmission_control_block = this->transmission_control_blocks[transmission_control_block_index];
    if (transmission_control_protocol_header.get_reset_flag()) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (transmission_control_protocol_header.get_acknowledgement_flag()) {
        auto *reset_segment_address = packet_buffer_t::allocate();
        transmission_control_protocol_packet_configuration_t packet_configuration = {
            .sequence_number = transmission_control_protocol_header.get_acknowledgement_number_field(),
            .acknowledgement_number{},
            .ack = false,
            .rst = true,
            .syn = false,
            .fin = false};
        this->transmit(reset_segment_address, transmission_control_block, packet_configuration);
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    if (transmission_control_protocol_header.get_synchronization_flag()) {
        transmission_control_block.next_uint32_to_receive =
            transmission_control_protocol_header.get_sequence_number_field() + 1;
        transmission_control_block.initial_receive_sequence_number =
            transmission_control_protocol_header.get_sequence_number_field();
        transmission_control_block.initial_send_sequence_number =
            transmission_control_protocol_header.get_sequence_number_field() + get_new_initial_sequence_number();
        transmission_control_block.oldest_unacknowledged_sequence_number =
            transmission_control_block.initial_send_sequence_number;
        transmission_control_block.next_uint32_to_transmit =
            transmission_control_block.initial_send_sequence_number + 1;
        transmission_control_block.destination_internet_protocol_address =
            internet_protocol_header.get_source_address_field();
        transmission_control_block.destination_port_number =
            transmission_control_protocol_header.get_source_port_field();
        auto *syn_ack_segment_address = packet_buffer_t::allocate();
        transmission_control_protocol_packet_configuration_t packet_configuration = {
            .sequence_number = transmission_control_block.initial_send_sequence_number,
            .acknowledgement_number = transmission_control_block.next_uint32_to_receive,
            .ack = true,
            .rst = false,
            .syn = true,
            .fin = false};
        this->transmit(syn_ack_segment_address, transmission_control_block, packet_configuration);
        transmission_control_block.state = connection_state_t::syn_received;
        process::thread_scheduler::get().wake(&transmission_control_block);
        // device::pl011::printf("listen -> syn_received\n");
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }
    packet_buffer_t::deallocate(packet_buffer_address);
}

auto transmission_control_protocol_t::handle_segment_arrival_in_syn_sent_state(
    size_t transmission_control_block_index,
    transmission_control_protocol_header_t transmission_control_protocol_header,
    internet_protocol_packet_header_t internet_protocol_header, packet_buffer_t *packet_buffer_address) -> void {
    auto &transmission_control_block = this->transmission_control_blocks[transmission_control_block_index];
    if (transmission_control_protocol_header.get_acknowledgement_flag()) {
        if (transmission_control_protocol_header.get_acknowledgement_number_field() <=
                transmission_control_block.initial_send_sequence_number ||
            transmission_control_protocol_header.get_acknowledgement_number_field() >
                transmission_control_block.next_uint32_to_transmit) {
            if (!transmission_control_protocol_header.get_reset_flag()) {
                auto *reset_segment_address = packet_buffer_t::allocate();
                transmission_control_protocol_packet_configuration_t packet_configuration = {
                    .sequence_number = transmission_control_protocol_header.get_acknowledgement_number_field(),
                    .acknowledgement_number{},
                    .ack = false,
                    .rst = true,
                    .syn = false,
                    .fin = false};
                this->transmit(reset_segment_address, transmission_control_block, packet_configuration);
            }
            packet_buffer_t::deallocate(packet_buffer_address);
            return;
        }
        if (transmission_control_protocol_header.get_acknowledgement_number_field() <=
                transmission_control_block.oldest_unacknowledged_sequence_number ||
            transmission_control_protocol_header.get_acknowledgement_number_field() >
                transmission_control_block.next_uint32_to_transmit) {
            packet_buffer_t::deallocate(packet_buffer_address);
            return;
        }
    }

    if (transmission_control_protocol_header.get_reset_flag()) {
        if (transmission_control_protocol_header.get_acknowledgement_flag()) {
            delete_transmission_control_block(transmission_control_block, request_status_t::remotely_closed_error);
        }
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }

    if (transmission_control_protocol_header.get_synchronization_flag()) {
        transmission_control_block.next_uint32_to_receive =
            transmission_control_protocol_header.get_sequence_number_field() + 1;
        transmission_control_block.initial_receive_sequence_number =
            transmission_control_protocol_header.get_sequence_number_field();
        if (transmission_control_protocol_header.get_acknowledgement_flag()) {
            transmission_control_block.oldest_unacknowledged_sequence_number =
                transmission_control_protocol_header.get_acknowledgement_number_field();
        }
        if (transmission_control_block.oldest_unacknowledged_sequence_number >
            transmission_control_block.initial_send_sequence_number) {
            transmission_control_block.state = connection_state_t::established;
            process::thread_scheduler::get().wake(&transmission_control_block);
            // device::pl011::printf("syn_sent -> established\n");
            auto *ack_segment_address = packet_buffer_t::allocate();
            transmission_control_protocol_packet_configuration_t packet_configuration = {
                .sequence_number = transmission_control_block.next_uint32_to_transmit,
                .acknowledgement_number = transmission_control_block.next_uint32_to_receive,
                .ack = true,
                .rst = false,
                .syn = false,
                .fin = false};
            this->transmit(ack_segment_address, transmission_control_block, packet_configuration);
            if (transmission_control_block.open_request_address != nullptr) {
                transmission_control_block.open_request_address->lock.acquire();
                transmission_control_block.open_request_address->status = request_status_t::completed;
                transmission_control_block.open_request_address->destination_internet_protocol_address =
                    internet_protocol_header.get_source_address_field();
                transmission_control_block.open_request_address->destination_port_number =
                    transmission_control_protocol_header.get_source_port_field();
                transmission_control_block.open_request_address->control_block_index = transmission_control_block_index;
                process::thread_scheduler::get().wake(transmission_control_block.open_request_address);
                transmission_control_block.open_request_address->lock.release();
            }
            while (transmission_control_block.receive_request_addresses.length() > 0 &&
                   transmission_control_block.received_data_queue.length() > 0) {
                auto *request_address = transmission_control_block.receive_request_addresses.front();
                auto *packet_buffer_address = transmission_control_block.received_data_queue.front();
                auto number_of_bytes_to_transfer = request_address->number_of_bytes_to_transfer;
                if (number_of_bytes_to_transfer > packet_buffer_address->get_length()) {
                    number_of_bytes_to_transfer = packet_buffer_address->get_length();
                }
                packet_buffer_address->pop_front(
                    span_t(&request_address->buffer[request_address->number_of_bytes_transferred],
                           number_of_bytes_to_transfer));
                if (packet_buffer_address->get_length() == 0) {
                    packet_buffer_t::deallocate(packet_buffer_address);
                    transmission_control_block.received_data_queue.dequeue();
                }
                request_address->lock.acquire();
                request_address->number_of_bytes_transferred += number_of_bytes_to_transfer;
                request_address->number_of_bytes_to_transfer -= number_of_bytes_to_transfer;
                if (request_address->number_of_bytes_to_transfer == 0) {
                    request_address->status = request_status_t::completed;
                    process::thread_scheduler::get().wake(request_address);
                    request_address->lock.release();
                    transmission_control_block.receive_request_addresses.dequeue();
                } else {
                    request_address->lock.release();
                }
            }
            if (transmission_control_block.receive_request_addresses.length() > 0 &&
                transmission_control_block.receive_request_addresses.front()->number_of_bytes_transferred > 0) {
                auto *request_address = transmission_control_block.receive_request_addresses.front();
                request_address->lock.acquire();
                request_address->status = request_status_t::completed;
                process::thread_scheduler::get().wake(request_address);
                request_address->lock.release();
                transmission_control_block.receive_request_addresses.dequeue();
            }
        } else {
            transmission_control_block.state = connection_state_t::syn_received;
            process::thread_scheduler::get().wake(&transmission_control_block);
            // device::pl011::printf("syn_sent -> syn_received\n");
            auto *syn_ack_segment_address = packet_buffer_t::allocate();
            transmission_control_protocol_packet_configuration_t packet_configuration = {
                .sequence_number = transmission_control_block.initial_send_sequence_number,
                .acknowledgement_number = transmission_control_block.next_uint32_to_receive,
                .ack = true,
                .rst = false,
                .syn = true,
                .fin = false};
            this->transmit(syn_ack_segment_address, transmission_control_block, packet_configuration);
            transmission_control_block.transmit_window_size = transmission_control_protocol_header.get_window_field();
            transmission_control_block.last_window_update_sequence_number =
                transmission_control_protocol_header.get_sequence_number_field();
            transmission_control_block.last_window_update_acknowledgement_number =
                transmission_control_protocol_header.get_acknowledgement_number_field();
        }
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }

    packet_buffer_t::deallocate(packet_buffer_address);
}

auto transmission_control_protocol_t::handle_segment_arrival_in_other_states(
    size_t transmission_control_block_index,
    transmission_control_protocol_header_t transmission_control_protocol_header,
    internet_protocol_packet_header_t internet_protocol_header, packet_buffer_t *packet_buffer_address) -> void {
    auto &transmission_control_block = this->transmission_control_blocks[transmission_control_block_index];
    if (transmission_control_protocol_header.get_sequence_number_field() <
            transmission_control_block.next_uint32_to_receive ||
        transmission_control_protocol_header.get_sequence_number_field() + packet_buffer_address->get_length() - 1 >=
            transmission_control_block.next_uint32_to_receive + transmission_control_block.receive_window_size) {
        if (!transmission_control_protocol_header.get_reset_flag()) {
            auto *ack_segment_address = packet_buffer_t::allocate();
            transmission_control_protocol_packet_configuration_t packet_configuration = {
                .sequence_number = transmission_control_block.next_uint32_to_transmit,
                .acknowledgement_number = transmission_control_block.next_uint32_to_receive,
                .ack = true,
                .rst = false,
                .syn = false,
                .fin = false};
            this->transmit(ack_segment_address, transmission_control_block, packet_configuration);
        }
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }

    if (transmission_control_protocol_header.get_sequence_number_field() !=
        transmission_control_block.next_uint32_to_receive) {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }

    if (transmission_control_protocol_header.get_reset_flag()) {
        switch (transmission_control_block.state) {
        case connection_state_t::syn_received:
            if (transmission_control_block.active_opened) {
                delete_transmission_control_block(transmission_control_block, request_status_t::remotely_closed_error);
            } else {
                transmission_control_block.state = connection_state_t::listen;
                process::thread_scheduler::get().wake(&transmission_control_block);
                // device::pl011::printf("syn_received -> listen\n");
                transmission_control_block.transmitted_data_queue.clear();
            }
            packet_buffer_t::deallocate(packet_buffer_address);
            return;
        case connection_state_t::established:
        case connection_state_t::fin_wait_1:
        case connection_state_t::fin_wait_2:
        case connection_state_t::close_wait:
        case connection_state_t::closing:
        case connection_state_t::last_ack:
        case connection_state_t::time_wait:
            delete_transmission_control_block(transmission_control_block, request_status_t::remotely_closed_error);
            packet_buffer_t::deallocate(packet_buffer_address);
            return;
        default:
            panic("transmission_control_protocol::handle_segment_arrival_in_other_states");
        }
    }

    if (transmission_control_protocol_header.get_synchronization_flag()) {
        switch (transmission_control_block.state) {
        case connection_state_t::syn_received: {
            if (!transmission_control_block.active_opened) {
                transmission_control_block.state = connection_state_t::listen;
                process::thread_scheduler::get().wake(&transmission_control_block);
                // device::pl011::printf("syn_received -> listen\n");
                packet_buffer_t::deallocate(packet_buffer_address);
                return;
            }
            [[fallthrough]];
        }
        case connection_state_t::established:
        case connection_state_t::fin_wait_1:
        case connection_state_t::fin_wait_2:
        case connection_state_t::close_wait:
        case connection_state_t::closing:
        case connection_state_t::last_ack:
        case connection_state_t::time_wait: {
            auto *ack_segment_address = packet_buffer_t::allocate();
            transmission_control_protocol_packet_configuration_t packet_configuration = {
                .sequence_number = transmission_control_block.next_uint32_to_transmit,
                .acknowledgement_number = transmission_control_block.next_uint32_to_receive,
                .ack = true,
                .rst = false,
                .syn = false,
                .fin = false};
            this->transmit(ack_segment_address, transmission_control_block, packet_configuration);
            packet_buffer_t::deallocate(packet_buffer_address);
            return;
        }
        default: {
            panic("transmission_control_protocol::handle_segment_arrival_in_other_states");
        }
        }
    }

    if (transmission_control_protocol_header.get_acknowledgement_flag()) {
        switch (transmission_control_block.state) {
        case connection_state_t::syn_received: {
            if (transmission_control_protocol_header.get_acknowledgement_number_field() >
                    transmission_control_block.oldest_unacknowledged_sequence_number &&
                transmission_control_protocol_header.get_acknowledgement_number_field() <=
                    transmission_control_block.next_uint32_to_transmit) {
                transmission_control_block.state = connection_state_t::established;
                process::thread_scheduler::get().wake(&transmission_control_block);
                transmission_control_block.transmit_window_size =
                    transmission_control_protocol_header.get_window_field();
                transmission_control_block.last_window_update_sequence_number =
                    transmission_control_protocol_header.get_sequence_number_field();
                transmission_control_block.last_window_update_acknowledgement_number =
                    transmission_control_protocol_header.get_acknowledgement_number_field();
                if (transmission_control_block.open_request_address != nullptr) {
                    transmission_control_block.open_request_address->lock.acquire();
                    transmission_control_block.open_request_address->status = request_status_t::completed;
                    transmission_control_block.open_request_address->destination_internet_protocol_address =
                        internet_protocol_header.get_source_address_field();
                    transmission_control_block.open_request_address->destination_port_number =
                        transmission_control_protocol_header.get_source_port_field();
                    transmission_control_block.open_request_address->control_block_index =
                        transmission_control_block_index;
                    process::thread_scheduler::get().wake(transmission_control_block.open_request_address);
                    transmission_control_block.open_request_address->lock.release();
                }
                while (transmission_control_block.receive_request_addresses.length() > 0 &&
                       transmission_control_block.received_data_queue.length() > 0) {
                    auto *request_address = transmission_control_block.receive_request_addresses.front();
                    auto *packet_buffer_address = transmission_control_block.received_data_queue.front();
                    auto number_of_bytes_to_transfer = request_address->number_of_bytes_to_transfer;
                    if (number_of_bytes_to_transfer > packet_buffer_address->get_length()) {
                        number_of_bytes_to_transfer = packet_buffer_address->get_length();
                    }
                    packet_buffer_address->pop_front(
                        span_t(&request_address->buffer[request_address->number_of_bytes_transferred],
                               number_of_bytes_to_transfer));
                    if (packet_buffer_address->get_length() == 0) {
                        packet_buffer_t::deallocate(packet_buffer_address);
                        transmission_control_block.received_data_queue.dequeue();
                    }
                    request_address->lock.acquire();
                    request_address->number_of_bytes_transferred += number_of_bytes_to_transfer;
                    request_address->number_of_bytes_to_transfer -= number_of_bytes_to_transfer;
                    if (request_address->number_of_bytes_to_transfer == 0) {
                        request_address->status = request_status_t::completed;
                        process::thread_scheduler::get().wake(request_address);
                        request_address->lock.release();
                        transmission_control_block.receive_request_addresses.dequeue();
                    } else {
                        request_address->lock.release();
                    }
                }
                if (transmission_control_block.receive_request_addresses.length() > 0 &&
                    transmission_control_block.receive_request_addresses.front()->number_of_bytes_transferred > 0) {
                    auto *request_address = transmission_control_block.receive_request_addresses.front();
                    request_address->lock.acquire();
                    request_address->status = request_status_t::completed;
                    process::thread_scheduler::get().wake(request_address);
                    request_address->lock.release();
                    transmission_control_block.receive_request_addresses.dequeue();
                }
                break;
            }
            auto *reset_segment_address = packet_buffer_t::allocate();
            transmission_control_protocol_packet_configuration_t packet_configuration = {
                .sequence_number = transmission_control_protocol_header.get_acknowledgement_number_field(),
                .acknowledgement_number{},
                .ack = false,
                .rst = true,
                .syn = false,
                .fin = false};
            this->transmit(reset_segment_address, transmission_control_block, packet_configuration);
            packet_buffer_t::deallocate(packet_buffer_address);
            return;
        }
        case connection_state_t::established:
        case connection_state_t::fin_wait_1:
        case connection_state_t::fin_wait_2:
        case connection_state_t::close_wait:
        case connection_state_t::closing: {
            if (transmission_control_protocol_header.get_acknowledgement_number_field() >
                    transmission_control_block.oldest_unacknowledged_sequence_number &&
                transmission_control_protocol_header.get_acknowledgement_number_field() <=
                    transmission_control_block.next_uint32_to_transmit) {
                transmission_control_block.oldest_unacknowledged_sequence_number =
                    transmission_control_protocol_header.get_acknowledgement_number_field();
                auto length = transmission_control_block.transmitted_request_addresses.length();
                for (int i = 0; i < length; i++) {
                    auto *request_address = transmission_control_block.transmitted_request_addresses.dequeue();
                    if (request_address->acknowledgement_sequence_number <
                        transmission_control_protocol_header.get_acknowledgement_number_field()) {
                        request_address->lock.acquire();
                        request_address->status = request_status_t::completed;
                        process::thread_scheduler::get().wake(request_address);
                        request_address->lock.release();
                    } else {
                        transmission_control_block.transmitted_request_addresses.enqueue(request_address);
                    }
                }
                length = transmission_control_block.transmitted_data_queue.length();
                for (int i = 0; i < length; i++) {
                    auto *packet_buffer_address = transmission_control_block.transmitted_data_queue.dequeue();
                    transmission_control_protocol_header_t transmission_control_protocol_header = {};
                    packet_buffer_address->pop_front(
                        as_writable_bytes(span_t(&transmission_control_protocol_header, 1)));
                    auto packet_data_size = packet_buffer_address->get_length();
                    packet_buffer_address->push_front(
                        as_writable_bytes(span_t(&transmission_control_protocol_header, 1)));
                    if (transmission_control_protocol_header.get_sequence_number_field() + packet_data_size >=
                        transmission_control_protocol_header.get_acknowledgement_number_field()) {
                        transmission_control_block.transmitted_data_queue.enqueue(packet_buffer_address);
                    }
                }
            } else if (transmission_control_protocol_header.get_acknowledgement_number_field() >
                       transmission_control_block.next_uint32_to_transmit) {
                auto *ack_segment_address = packet_buffer_t::allocate();
                transmission_control_protocol_packet_configuration_t packet_configuration = {
                    .sequence_number = transmission_control_block.next_uint32_to_transmit,
                    .acknowledgement_number = transmission_control_block.next_uint32_to_receive,
                    .ack = true,
                    .rst = false,
                    .syn = false,
                    .fin = false};
                this->transmit(ack_segment_address, transmission_control_block, packet_configuration);
                packet_buffer_t::deallocate(packet_buffer_address);
                return;
            }
            if (transmission_control_protocol_header.get_acknowledgement_number_field() >=
                    transmission_control_block.oldest_unacknowledged_sequence_number &&
                transmission_control_protocol_header.get_acknowledgement_number_field() <=
                    transmission_control_block.next_uint32_to_transmit &&
                (transmission_control_block.last_window_update_sequence_number <
                     transmission_control_protocol_header.get_sequence_number_field() ||
                 (transmission_control_block.last_window_update_sequence_number ==
                      transmission_control_protocol_header.get_sequence_number_field() &&
                  transmission_control_block.last_window_update_acknowledgement_number <=
                      transmission_control_protocol_header.get_acknowledgement_number_field()))) {
                transmission_control_block.transmit_window_size =
                    transmission_control_protocol_header.get_window_field();
                transmission_control_block.last_window_update_sequence_number =
                    transmission_control_protocol_header.get_sequence_number_field();
                transmission_control_block.last_window_update_acknowledgement_number =
                    transmission_control_protocol_header.get_acknowledgement_number_field();
            }
            if (transmission_control_block.state == connection_state_t::fin_wait_1) {
                if (transmission_control_block.fin_state == fin_state_t::unacknowledged &&
                    transmission_control_block.sequence_number_of_fin <
                        transmission_control_protocol_header.get_acknowledgement_number_field()) {
                    transmission_control_block.fin_state = fin_state_t::acknowledged;
                    transmission_control_block.state = connection_state_t::fin_wait_2;
                    process::thread_scheduler::get().wake(&transmission_control_block);
                    // device::pl011::printf("fin_wait_1 -> fin_wait_2\n");
                } else if (transmission_control_block.fin_state == fin_state_t::acknowledged) {
                    transmission_control_block.state = connection_state_t::fin_wait_2;
                    process::thread_scheduler::get().wake(&transmission_control_block);
                    // device::pl011::printf("fin_wait_1 -> fin_wait_2\n");
                }
            }
            if (transmission_control_block.state == connection_state_t::fin_wait_2) {
                if (transmission_control_block.transmitted_data_queue.length() == 0) {
                    delete_transmission_control_block(transmission_control_block,
                                                      request_status_t::locally_closed_error);
                }
            }
            if (transmission_control_block.state == connection_state_t::closing &&
                transmission_control_block.fin_state == fin_state_t::unacknowledged &&
                transmission_control_block.sequence_number_of_fin <
                    transmission_control_protocol_header.get_acknowledgement_number_field()) {
                transmission_control_block.fin_state = fin_state_t::acknowledged;
                transmission_control_block.state = connection_state_t::time_wait;
                process::thread_scheduler::get().wake(&transmission_control_block);
                // device::pl011::printf("closing -> time_wait\n");
                delete_transmission_control_block(transmission_control_block, request_status_t::remotely_closed_error);
            }
            break;
        }
        case connection_state_t::last_ack: {
            if (transmission_control_block.fin_state == fin_state_t::acknowledged ||
                (transmission_control_block.fin_state == fin_state_t::unacknowledged &&
                 transmission_control_block.sequence_number_of_fin <
                     transmission_control_protocol_header.get_acknowledgement_number_field())) {
                delete_transmission_control_block(transmission_control_block, request_status_t::locally_closed_error);
                packet_buffer_t::deallocate(packet_buffer_address);
                return;
            }
            break;
        }
        case connection_state_t::time_wait: {
            auto *ack_segment_address = packet_buffer_t::allocate();
            transmission_control_protocol_packet_configuration_t packet_configuration = {
                .sequence_number = transmission_control_block.next_uint32_to_transmit,
                .acknowledgement_number = transmission_control_protocol_header.get_sequence_number_field(),
                .ack = true,
                .rst = false,
                .syn = false,
                .fin = false};
            packet_configuration.acknowledgement_number += packet_buffer_address->get_length();
            this->transmit(ack_segment_address, transmission_control_block, packet_configuration);
            break;
        }
        default: {
            panic("transmission_control_protocol::handle_segment_arrival_in_other_states");
        }
        }
    } else {
        packet_buffer_t::deallocate(packet_buffer_address);
        return;
    }

    if (packet_buffer_address->get_length() > 0) {
        switch (transmission_control_block.state) {
        case connection_state_t::established:
        case connection_state_t::fin_wait_1:
        case connection_state_t::fin_wait_2: {
            transmission_control_block.next_uint32_to_receive += packet_buffer_address->get_length();
            auto *ack_segment_address = packet_buffer_t::allocate();
            transmission_control_protocol_packet_configuration_t packet_configuration = {
                .sequence_number = transmission_control_block.next_uint32_to_transmit,
                .acknowledgement_number = transmission_control_block.next_uint32_to_receive,
                .ack = true,
                .rst = false,
                .syn = false,
                .fin = false};
            this->transmit(ack_segment_address, transmission_control_block, packet_configuration);
            while (packet_buffer_address != nullptr &&
                   transmission_control_block.receive_request_addresses.length() > 0) {
                auto *request_address = transmission_control_block.receive_request_addresses.front();
                auto number_of_bytes_to_transfer = request_address->number_of_bytes_to_transfer;
                if (number_of_bytes_to_transfer > packet_buffer_address->get_length()) {
                    number_of_bytes_to_transfer = packet_buffer_address->get_length();
                }
                packet_buffer_address->pop_front(
                    span_t(&request_address->buffer[request_address->number_of_bytes_transferred],
                           number_of_bytes_to_transfer));
                if (packet_buffer_address->get_length() == 0) {
                    packet_buffer_t::deallocate(packet_buffer_address);
                    packet_buffer_address = {};
                }
                request_address->lock.acquire();
                request_address->number_of_bytes_transferred += number_of_bytes_to_transfer;
                request_address->number_of_bytes_to_transfer -= number_of_bytes_to_transfer;
                if (request_address->number_of_bytes_to_transfer == 0) {
                    request_address->status = request_status_t::completed;
                    process::thread_scheduler::get().wake(request_address);
                    request_address->lock.release();
                    transmission_control_block.receive_request_addresses.dequeue();
                } else {
                    request_address->lock.release();
                }
            }
            if (packet_buffer_address != nullptr) {
                transmission_control_block.received_data_queue.enqueue(packet_buffer_address);
            }
            if (transmission_control_block.receive_request_addresses.length() > 0 &&
                transmission_control_block.receive_request_addresses.front()->number_of_bytes_transferred > 0) {
                auto *request_address = transmission_control_block.receive_request_addresses.front();
                request_address->lock.acquire();
                request_address->status = request_status_t::completed;
                process::thread_scheduler::get().wake(request_address);
                request_address->lock.release();
                transmission_control_block.receive_request_addresses.dequeue();
            }
            break;
        }
        case connection_state_t::close_wait:
        case connection_state_t::closing:
        case connection_state_t::last_ack:
        case connection_state_t::time_wait: {
            packet_buffer_t::deallocate(packet_buffer_address);
            break;
        }
        default: {
            panic("transmission_control_protocol::handle_segment_arrival_in_other_states");
        }
        }
    } else {
        packet_buffer_t::deallocate(packet_buffer_address);
    }

    if (transmission_control_protocol_header.get_finish_flag()) {
        if (transmission_control_block.state == connection_state_t::closed ||
            transmission_control_block.state == connection_state_t::listen ||
            transmission_control_block.state == connection_state_t::syn_sent) {
            return;
        }
        transmission_control_block.next_uint32_to_receive += 1;
        auto *ack_segment_address = packet_buffer_t::allocate();
        transmission_control_protocol_packet_configuration_t packet_configuration = {
            .sequence_number = transmission_control_block.next_uint32_to_transmit,
            .acknowledgement_number = transmission_control_block.next_uint32_to_receive,
            .ack = true,
            .rst = false,
            .syn = false,
            .fin = false};
        this->transmit(ack_segment_address, transmission_control_block, packet_configuration);
        switch (transmission_control_block.state) {
        case connection_state_t::syn_received:
        case connection_state_t::established:
            transmission_control_block.state = connection_state_t::close_wait;
            process::thread_scheduler::get().wake(&transmission_control_block);
            // device::pl011::printf("syn_received/established -> close_wait\n");
            transmission_control_block.receive_request_addresses.clear(request_status_t::remotely_closed_error);
            return;
        case connection_state_t::fin_wait_1:
            if (transmission_control_block.fin_state == fin_state_t::acknowledged) {
                transmission_control_block.state = connection_state_t::time_wait;
                process::thread_scheduler::get().wake(&transmission_control_block);
                // device::pl011::printf("fin_wait_1 -> time_wait\n");
                transmission_control_protocol_t::delete_transmission_control_block(
                    transmission_control_block, request_status_t::remotely_closed_error);
            } else {
                transmission_control_block.state = connection_state_t::closing;
                process::thread_scheduler::get().wake(&transmission_control_block);
                // device::pl011::printf("fin_wait_1 -> closing\n");
                transmission_control_block.receive_request_addresses.clear(request_status_t::remotely_closed_error);
            }
            return;
        case connection_state_t::fin_wait_2:
            transmission_control_block.state = connection_state_t::time_wait;
            process::thread_scheduler::get().wake(&transmission_control_block);
            // device::pl011::printf("fin_wait_2 -> time_wait\n");
            transmission_control_protocol_t::delete_transmission_control_block(transmission_control_block,
                                                                               request_status_t::remotely_closed_error);
            return;
        case connection_state_t::close_wait:
        case connection_state_t::closing:
        case connection_state_t::last_ack:
        case connection_state_t::time_wait:
            return;
        default:
            panic("transmission_control_protocol::handle_segment_arrival_in_other_states");
        }
    }
}

auto transmission_control_protocol_t::delete_transmission_control_block(
    transmission_control_block_t &transmission_control_block, request_status_t request_status) -> void {
    if (transmission_control_block.open_request_address != nullptr) {
        transmission_control_block.open_request_address->lock.acquire();
        transmission_control_block.open_request_address->status = request_status;
        process::thread_scheduler::get().wake(transmission_control_block.open_request_address);
        transmission_control_block.open_request_address->lock.release();
    }
    if (transmission_control_block.close_request_address != nullptr) {
        transmission_control_block.close_request_address->lock.acquire();
        transmission_control_block.close_request_address->status = request_status;
        process::thread_scheduler::get().wake(transmission_control_block.close_request_address);
        transmission_control_block.close_request_address->lock.release();
    }
    transmission_control_block.receive_request_addresses.clear(request_status);
    transmission_control_block.transmit_request_addresses.clear(request_status);
    transmission_control_block.transmitted_request_addresses.clear(request_status);
    auto *packet_buffer_address = transmission_control_block.received_data_queue.dequeue();
    while (packet_buffer_address != nullptr) {
        packet_buffer_t::deallocate(packet_buffer_address);
        packet_buffer_address = transmission_control_block.received_data_queue.dequeue();
    }
    packet_buffer_address = transmission_control_block.transmitted_data_queue.dequeue();
    while (packet_buffer_address != nullptr) {
        packet_buffer_t::deallocate(packet_buffer_address);
        packet_buffer_address = transmission_control_block.transmitted_data_queue.dequeue();
    }
    transmission_control_block = {};
    // device::pl011::printf("??? -> closed\n");
}

auto transmission_control_protocol_t::get_transmission_control_block_index_by_address(
    uint16_t source_port_number, uint32_t destination_internet_protocol_address, uint16_t destination_port_number,
    bool should_ignore_destination) -> size_t {
    for (size_t i = 0; i < transmission_control_protocol_constants::maximum_number_of_connections; i++) {
        auto &transmission_control_block = this->transmission_control_blocks[i];
        if ((should_ignore_destination && transmission_control_block.source_port_number == source_port_number) ||
            (!should_ignore_destination && transmission_control_block.source_port_number == source_port_number &&
             transmission_control_block.destination_internet_protocol_address ==
                 destination_internet_protocol_address &&
             transmission_control_block.destination_port_number == destination_port_number)) {
            return i;
        }
    }
    return SIZE_MAX;
}

auto transmission_control_protocol_t::request(request_t *request_address) -> void {
    request_address->lock.acquire();
    if (request_address->type != request_type_t::open && request_address->control_block_index == SIZE_MAX) {
        request_address->status = request_status_t::invalid_arguments_error;
        process::thread_scheduler::get().wake(request_address);
        request_address->lock.release();
    } else {
        request_address->lock.release();
    }
    switch (request_address->type) {
    case request_type_t::open: {
        transmission_control_protocol_t::get().open_connection(request_address);
        return;
    }
    case request_type_t::close: {
        transmission_control_protocol_t::get().close_connection(request_address);
        return;
    }
    case request_type_t::receive: {
        transmission_control_protocol_t::get().receive_data(request_address);
        return;
    }
    case request_type_t::transmit: {
        transmission_control_protocol_t::get().transmit_data(request_address);
        return;
    }
    }
}

auto transmission_control_protocol_t::handle_transmit_requests() -> void {
    for (size_t transmission_control_block_index = 0;
         transmission_control_block_index < transmission_control_protocol_constants::maximum_number_of_connections;
         transmission_control_block_index += 1) {
        auto &transmission_control_block =
            transmission_control_protocol_t::get().transmission_control_blocks[transmission_control_block_index];
        auto *request_address = transmission_control_block.transmit_request_addresses.dequeue();
        while (request_address != nullptr) {
            request_address->lock.acquire();
            while (request_address->number_of_bytes_to_transfer > 0) {
                auto number_of_bytes_to_transfer = request_address->number_of_bytes_to_transfer;
                if (number_of_bytes_to_transfer > transmission_control_protocol_constants::maximum_payload_size) {
                    number_of_bytes_to_transfer = transmission_control_protocol_constants::maximum_payload_size;
                }
                auto *packet_buffer_address = packet_buffer_t::allocate();
                packet_buffer_address->push_back(
                    span_t(&request_address->buffer[request_address->number_of_bytes_transferred],
                           number_of_bytes_to_transfer));
                request_address->number_of_bytes_transferred += number_of_bytes_to_transfer;
                request_address->number_of_bytes_to_transfer -= number_of_bytes_to_transfer;
                transmission_control_protocol_packet_configuration_t packet_configuration = {
                    .sequence_number = transmission_control_block.next_uint32_to_transmit,
                    .acknowledgement_number = transmission_control_block.next_uint32_to_receive,
                    .ack = true,
                    .rst = false,
                    .syn = false,
                    .fin = false};
                transmit(packet_buffer_address, transmission_control_block, packet_configuration);
                transmission_control_block.next_uint32_to_transmit += number_of_bytes_to_transfer;
            }
            request_address->acknowledgement_sequence_number = transmission_control_block.next_uint32_to_transmit - 1;
            request_address->lock.release();
            transmission_control_block.transmitted_request_addresses.enqueue(request_address);
            request_address = transmission_control_block.transmit_request_addresses.dequeue();
        }
    }
}

} // namespace networking

#ifndef TRANSMISSION_CONTROL_PROTOCOL_HPP
#define TRANSMISSION_CONTROL_PROTOCOL_HPP

#include "socket_interface.hpp"
#include "spin_lock.hpp"

namespace networking {

struct transmission_control_protocol_packet_configuration_t {
    uint32_t sequence_number{};
    uint32_t acknowledgement_number{};
    bool ack{};
    bool rst{};
    bool syn{};
    bool fin{};
};

enum class connection_state_t {
    closed,
    listen,
    syn_sent,
    syn_received,
    established,
    fin_wait_1,
    fin_wait_2,
    close_wait,
    closing,
    last_ack,
    time_wait,
};

enum class fin_state_t { no_fin, unacknowledged, acknowledged };

struct transmission_control_block_t {
    synchronization::spin_lock lock;

    connection_state_t state = connection_state_t::closed;
    bool active_opened = false;
    networking::port_number_t source_port_number = {};
    networking::internet_protocol_address_t destination_internet_protocol_address = {};
    networking::port_number_t destination_port_number = {};

    request_t *open_request_address = nullptr;
    request_t *close_request_address = nullptr;
    request_queue_t receive_request_addresses;
    request_queue_t transmit_request_addresses;
    request_queue_t transmitted_request_addresses;

    packet_buffer_queue_t received_data_queue = {};
    packet_buffer_queue_t transmitted_data_queue = {};

    uint32_t next_uint32_to_receive{};
    uint16_t receive_window_size = transmission_control_protocol_constants::initial_window_size;
    uint32_t initial_receive_sequence_number{};

    uint32_t oldest_unacknowledged_sequence_number{};
    uint32_t next_uint32_to_transmit{};
    uint16_t transmit_window_size = transmission_control_protocol_constants::initial_window_size;
    uint32_t last_window_update_sequence_number{};
    uint32_t last_window_update_acknowledgement_number{};
    uint32_t initial_send_sequence_number{};

    fin_state_t fin_state = fin_state_t::no_fin;
    uint32_t sequence_number_of_fin{};
};

class transmission_control_protocol_t {
public:
    static auto receive(packet_buffer_t *packet_buffer_address,
                        internet_protocol_packet_header_t internet_protocol_header) -> void;
    static auto transmit(packet_buffer_t *packet_buffer_address,
                         transmission_control_block_t &transmission_control_block,
                         transmission_control_protocol_packet_configuration_t packet_configuration) -> void;
    static auto request(request_t *request_address) -> void;
    static auto handle_transmit_requests() -> void;
    static auto timeout() -> void;
    static auto sleep_until_established(size_t transmission_control_block_index) -> bool;

    transmission_control_protocol_t(const transmission_control_protocol_t &) = delete;
    auto operator=(const transmission_control_protocol_t &) -> transmission_control_protocol_t & = delete;
    transmission_control_protocol_t(transmission_control_protocol_t &&) = delete;
    auto operator=(transmission_control_protocol_t &&) -> transmission_control_protocol_t & = delete;

private:
    array_t<transmission_control_block_t, transmission_control_protocol_constants::maximum_number_of_connections>
        transmission_control_blocks;

    static auto get() -> transmission_control_protocol_t & {
        static transmission_control_protocol_t instance;
        return instance;
    }

    auto open_connection(request_t *request_address) -> void;
    auto close_connection(request_t *request_address) -> void;
    auto receive_data(request_t *request_address) -> void;
    auto transmit_data(request_t *request_address) -> void;

    auto handle_segment_arrival(size_t transmission_control_block_index,
                                transmission_control_protocol_header_t transmission_control_protocol_header,
                                internet_protocol_packet_header_t internet_protocol_header,
                                packet_buffer_t *packet_buffer_address) -> void;
    auto
    handle_segment_arrival_in_closed_state(size_t transmission_control_block_index,
                                           transmission_control_protocol_header_t transmission_control_protocol_header,
                                           packet_buffer_t *packet_buffer_address) -> void;
    auto
    handle_segment_arrival_in_listen_state(size_t transmission_control_block_index,
                                           transmission_control_protocol_header_t transmission_control_protocol_header,
                                           internet_protocol_packet_header_t internet_protocol_header,
                                           packet_buffer_t *packet_buffer_address) -> void;
    auto handle_segment_arrival_in_syn_sent_state(
        size_t transmission_control_block_index,
        transmission_control_protocol_header_t transmission_control_protocol_header,
        internet_protocol_packet_header_t internet_protocol_header, packet_buffer_t *packet_buffer_address) -> void;
    auto
    handle_segment_arrival_in_other_states(size_t transmission_control_block_index,
                                           transmission_control_protocol_header_t transmission_control_protocol_header,
                                           internet_protocol_packet_header_t internet_protocol_header,
                                           packet_buffer_t *packet_buffer_address) -> void;

    static auto delete_transmission_control_block(transmission_control_block_t &transmission_control_block,
                                                  request_status_t request_status) -> void;
    auto get_transmission_control_block_index_by_address(uint16_t source_port_number,
                                                         uint32_t destination_internet_protocol_address,
                                                         uint16_t destination_port_number,
                                                         bool should_ignore_destination) -> size_t;

    transmission_control_protocol_t() = default;
    ~transmission_control_protocol_t() = default;
};

} // namespace networking

#endif

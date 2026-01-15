#ifndef PACKET_BUFFER_HPP
#define PACKET_BUFFER_HPP

#include "../lib/array.hpp"
#include "../lib/span.hpp"
#include "buddy_allocator.hpp"
#include "integer.hpp"
#include "memory.hpp"
#include "networking.hpp"
#include "spin_lock.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>

namespace networking {

class packet_buffer_t {
public:
    static auto allocate() -> packet_buffer_t * {
        auto *packet_buffer = memory::buddy_allocator::get().allocate<packet_buffer_t>(1);
        for (size_t offset = 0; offset < packet_buffer_constants::packet_buffer_size; offset++) {
            packet_buffer->buffer[offset].set_value(0);
        }
        packet_buffer->offset = packet_buffer_constants::packet_buffer_initial_offset;
        packet_buffer->length = 0;
        packet_buffer->next = nullptr;
        packet_buffer->source_internet_protocol_address = 0;
        packet_buffer->source_port_number = 0;
        packet_buffer->destination_internet_protocol_address = 0;
        packet_buffer->destination_port_number = 0;
        packet_buffer->number_of_retransmissions = 0;
        return packet_buffer;
    }

    static auto deallocate(packet_buffer_t *packet_buffer_address) -> void {
        memory::buddy_allocator::get().deallocate(packet_buffer_address);
    }

    auto get_packet() -> byte_t * {
        return &this->buffer[offset];
    }

    auto push_front(span_t<byte_t> buffer) -> bool {
        if (buffer.size() > this->offset) {
            return false;
        }
        this->offset -= buffer.size();
        this->length += buffer.size();
        for (size_t i = 0; i < buffer.size(); i++) {
            this->buffer[this->offset + i] = buffer[i];
        }
        return true;
    }

    auto pop_front(span_t<byte_t> buffer) -> bool {
        if (buffer.size() > this->length) {
            return false;
        }
        for (size_t i = 0; i < buffer.size(); i++) {
            buffer[i] = this->buffer[offset + i];
        }
        this->offset += buffer.size();
        this->length -= buffer.size();
        return true;
    }

    auto push_back(span_t<byte_t> buffer) -> bool {
        if (this->offset + this->length + buffer.size() > packet_buffer_constants::packet_buffer_size) {
            return false;
        }
        for (size_t i = 0; i < buffer.size(); i++) {
            this->buffer[this->offset + this->length + i] = buffer[i];
        }
        this->length += buffer.size();
        return true;
    }

    auto pop_back(span_t<byte_t> buffer) -> bool {
        if (buffer.size() > this->length) {
            return false;
        }
        this->length -= buffer.size();
        for (size_t i = 0; i < buffer.size(); i++) {
            buffer[i] = this->buffer[this->offset + this->length + i];
        }
        return true;
    }

    [[nodiscard]] auto get_length() const -> size_t {
        return this->length;
    }

    auto set_length(size_t length) -> void {
        this->length = length;
    }

    auto get_next() -> packet_buffer_t * {
        return this->next;
    }

    auto set_next(packet_buffer_t *packet_buffer_address) -> void {
        this->next = packet_buffer_address;
    }

    auto checksum() -> uint16_t {
        bool padded = false;
        byte_t zero{};
        if (this->length % 2 != 0) {
            padded = true;
            this->push_back(span_t(&zero, 1));
        }
        uint32_t sum = 0;
        for (size_t i = 0; i < this->length / 2; i++) {
            auto value = buffer[offset + 2 * i].get_value() | (buffer[offset + 2 * i + 1].get_value() << uint8_width);
            sum += value;
        }
        while ((sum >> uint16_width) != 0) {
            sum = (sum & UINT16_MAX) + (sum >> uint16_width);
        }
        sum = ~sum;
        if (padded) {
            this->pop_back(span_t(&zero, 1));
        }
        return sum;
    }

    [[nodiscard]] auto get_number_of_retransmissions() const -> int {
        return this->number_of_retransmissions;
    }

    auto set_number_of_retransmissions(int number_of_retransmissions) -> void {
        this->number_of_retransmissions = number_of_retransmissions;
    }

private:
    array_t<byte_t, packet_buffer_constants::packet_buffer_size> buffer = {};
    size_t offset = packet_buffer_constants::packet_buffer_initial_offset;
    size_t length = 0;
    packet_buffer_t *next = nullptr;

    uint32_t source_internet_protocol_address = 0;
    uint16_t source_port_number = 0;
    uint32_t destination_internet_protocol_address = 0;
    uint16_t destination_port_number = 0;

    int number_of_retransmissions = 0;
};
static_assert(sizeof(packet_buffer_t) <= 2 * memory::page_size);

class packet_buffer_queue_t {
public:
    auto enqueue(packet_buffer_t *packet_buffer_address) -> void {
        this->lock.acquire();
        if (this->head == nullptr && this->tail == nullptr) {
            this->head = packet_buffer_address;
            this->tail = packet_buffer_address;
            this->number_of_queued_packet_buffers += 1;
            this->lock.release();
            return;
        }
        this->tail->set_next(packet_buffer_address);
        this->tail = packet_buffer_address;
        this->number_of_queued_packet_buffers += 1;
        this->lock.release();
    }

    auto dequeue() -> packet_buffer_t * {
        this->lock.acquire();
        if (this->head == nullptr && this->tail == nullptr) {
            this->lock.release();
            return {};
        }
        if (this->head == this->tail) {
            auto *packet_buffer_address = this->head;
            this->head = {};
            this->tail = {};
            this->number_of_queued_packet_buffers -= 1;
            this->lock.release();
            return packet_buffer_address;
        }
        auto *packet_buffer_address = this->head;
        this->head = head->get_next();
        this->number_of_queued_packet_buffers -= 1;
        this->lock.release();
        return packet_buffer_address;
    }

    auto clear() -> void {
        auto *packet_buffer_address = this->dequeue();
        while (packet_buffer_address != nullptr) {
            packet_buffer_t::deallocate(packet_buffer_address);
            packet_buffer_address = this->dequeue();
        }
    }

    [[nodiscard]] auto length() const -> int {
        return this->number_of_queued_packet_buffers;
    }

    auto front() -> packet_buffer_t * {
        return this->head;
    }

private:
    synchronization::spin_lock lock;
    packet_buffer_t *head = {};
    packet_buffer_t *tail = {};
    int number_of_queued_packet_buffers = 0;
};

} // namespace networking

#endif

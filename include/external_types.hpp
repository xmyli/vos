#ifndef EXTERNEL_TYPES_HPP
#define EXTERNEL_TYPES_HPP

#include "../lib/array.hpp"
#include "device.hpp"
#include "memory.hpp"
#include "networking.hpp"
#include "path_name.hpp"
#include "pl011.hpp"
#include "reinterpretable.hpp"
#include "virtual_memory.hpp"

#include <cstddef>
#include <cstdint>

constexpr uint64_t elr_value = 0x0000000000400000;
constexpr uint64_t spsr_value = 0x0000000000000300;
constexpr uint64_t sp_value = 0x0001000000000000;
class exception_frame_t {
private:
    uint64_t x0{};
    uint64_t x1{};
    uint64_t x2{};
    uint64_t x3{};
    uint64_t x4{};
    uint64_t x5{};
    uint64_t x6{};
    uint64_t x7{};
    uint64_t x8{};
    uint64_t x9{};
    uint64_t x10{};
    uint64_t x11{};
    uint64_t x12{};
    uint64_t x13{};
    uint64_t x14{};
    uint64_t x15{};
    uint64_t x16{};
    uint64_t x17{};
    uint64_t x18{};
    uint64_t x19{};
    uint64_t x20{};
    uint64_t x21{};
    uint64_t x22{};
    uint64_t x23{};
    uint64_t x24{};
    uint64_t x25{};
    uint64_t x26{};
    uint64_t x27{};
    uint64_t x28{};
    uint64_t x29{};
    uint64_t x30{};
    uint64_t elr{elr_value};
    uint64_t spsr{spsr_value};
    uint64_t sp{sp_value};

public:
    [[nodiscard]] auto get_x0_field() const -> uint64_t {
        return this->x0;
    }
    auto set_x0_field(uint64_t value) -> void {
        this->x0 = value;
    }
    [[nodiscard]] auto get_x1_field() const -> uint64_t {
        return this->x1;
    }
    auto set_x1_field(uint64_t value) -> void {
        this->x1 = value;
    }
    [[nodiscard]] auto get_x2_field() const -> uint64_t {
        return this->x2;
    }
    auto set_x2_field(uint64_t value) -> void {
        this->x2 = value;
    }
    [[nodiscard]] auto get_x3_field() const -> uint64_t {
        return this->x3;
    }
    auto set_x3_field(uint64_t value) -> void {
        this->x3 = value;
    }
    [[nodiscard]] auto get_x4_field() const -> uint64_t {
        return this->x4;
    }
    auto set_x4_field(uint64_t value) -> void {
        this->x4 = value;
    }
    [[nodiscard]] auto get_x8_field() const -> uint64_t {
        return this->x8;
    }
    auto set_x8_field(uint64_t value) -> void {
        this->x8 = value;
    }
    auto set_elr_field(uint64_t value) -> void {
        this->elr = value;
    }
    auto reset_spsr_field() -> void {
        this->spsr = spsr_value;
    }
    auto set_sp_field(uint64_t value) -> void {
        this->sp = value;
    }
};
constexpr size_t exception_frame_size = 272;
static_assert(sizeof(exception_frame_t) == exception_frame_size);

constexpr size_t ident_length = 12;
class elf_header_t {
private:
    uint32_t magic_number;
    array_t<uint8_t, ident_length> ident;
    uint16_t type;
    uint16_t machine;
    uint32_t version;
    uint64_t entry;
    uint64_t phoff;
    uint64_t shoff;
    uint32_t flags;
    uint16_t ehsize;
    uint16_t phentsize;
    uint16_t phnum;
    uint16_t shentsize;
    uint16_t shnum;
    uint16_t shstrndx;

public:
    [[nodiscard]] auto is_elf() const -> bool {
        constexpr uint32_t elf_magic_number = 0x464c457f;
        return this->magic_number == elf_magic_number;
    }
    [[nodiscard]] auto get_entry_field() const -> size_t {
        return this->entry;
    }
    [[nodiscard]] auto get_phoff_field() const -> size_t {
        return this->phoff;
    }
    [[nodiscard]] auto get_phnum_field() const -> size_t {
        return this->phnum;
    }
};
constexpr size_t elf_header_size = 64;
static_assert(sizeof(elf_header_t) == elf_header_size);

class elf_section_header_t {
private:
    uint32_t type;
    uint32_t flags;
    uint64_t off;
    uint64_t vaddr;
    uint64_t paddr;
    uint64_t filesz;
    uint64_t memsz;
    uint64_t align;

public:
    [[nodiscard]] auto is_loadable() const -> bool {
        return this->type == 1;
    }
    [[nodiscard]] auto get_off_field() const -> size_t {
        return this->off;
    }
    [[nodiscard]] auto get_vaddr_field() const -> uintptr_t {
        return this->vaddr;
    }
    [[nodiscard]] auto get_paddr_field() const -> uintptr_t {
        return this->paddr;
    }
    [[nodiscard]] auto get_filesz_field() const -> size_t {
        return this->filesz;
    }
    [[nodiscard]] auto get_memsz_field() const -> size_t {
        return this->memsz;
    }
};
constexpr size_t elf_section_header_size = 56;
static_assert(sizeof(elf_section_header_t) == elf_section_header_size);

class context {
private:
    void *sp{};
    uint64_t x18{};
    uint64_t x19{};
    uint64_t x20{};
    uint64_t x21{};
    uint64_t x22{};
    uint64_t x23{};
    uint64_t x24{};
    uint64_t x25{};
    uint64_t x26{};
    uint64_t x27{};
    uint64_t x28{};
    uint64_t x29{};
    void (*x30)(){};

public:
    auto set_stack_pointer(void *value) -> void {
        this->sp = value;
    }
    auto set_link_pointer(void (*value)()) -> void {
        this->x30 = value;
    }
};
constexpr size_t context_size = 112;
static_assert(sizeof(context) == context_size);

class virtqueue_descriptor {
private:
    uint64_t address;
    uint32_t length;
    uint16_t flags;
    uint16_t next;

public:
    auto set_address_field(void *value) -> void {
        this->address = reinterpretable_t<void *>(value).to_integer() -
                        memory::kernel_address_space_constants::virtual_address_begin;
    }
    auto set_length_field(size_t value) -> void {
        this->length = value;
    }
    auto set_flags_field(device::virtqueue_descriptor_flag value) -> void {
        switch (value) {
        case device::virtqueue_descriptor_flag::none:
            this->flags = 0;
            break;
        case device::virtqueue_descriptor_flag::next:
            this->flags = 1;
            break;
        case device::virtqueue_descriptor_flag::write:
            this->flags = 2;
            break;
        case device::virtqueue_descriptor_flag::read:
            this->flags = 3;
            break;
        case device::virtqueue_descriptor_flag::indirect:
            this->flags = 4;
            break;
        }
    }
    auto set_next_field(size_t value) -> void {
        this->next = value;
    }
};
constexpr size_t virtqueue_descriptor_size = 16;
static_assert(sizeof(virtqueue_descriptor) == virtqueue_descriptor_size);

class virtqueue_available_ring {
private:
    uint16_t flags;
    uint16_t index;
    array_t<uint16_t, device::virtio_blk_virtqueue_ring_size> ring;
    uint16_t unused;

public:
    [[nodiscard]] auto get_index_field() const -> size_t {
        return this->index;
    }
    auto set_index_field(size_t value) -> void {
        this->index = value;
    }
    auto get_ring_element_at_index(size_t index) -> size_t {
        return this->ring[index];
    }
    auto set_ring_element_at_index(size_t index, size_t value) -> void {
        this->ring[index] = value;
    }
};
constexpr size_t virtqueue_available_ring_size = 22;
static_assert(sizeof(virtqueue_available_ring) == virtqueue_available_ring_size);

class virtqueue_used_ring_element {
private:
    uint32_t id{};
    uint32_t length{};

public:
    [[nodiscard]] auto get_id_field() const -> size_t {
        return this->id;
    }
};
constexpr size_t virtqueue_used_ring_element_size = 8;
static_assert(sizeof(virtqueue_used_ring_element) == virtqueue_used_ring_element_size);

class virtqueue_used_ring {
private:
    uint16_t flags{};
    uint16_t index{};
    array_t<virtqueue_used_ring_element, device::virtio_blk_virtqueue_ring_size> ring{};

public:
    [[nodiscard]] auto get_index_field() const -> size_t {
        return this->index;
    }
    auto get_ring_element_at_index(size_t index) -> virtqueue_used_ring_element {
        return ring[index];
    }
};
constexpr size_t virtqueue_used_ring_size = 68;
static_assert(sizeof(virtqueue_used_ring) == virtqueue_used_ring_size);

class virtio_block_request {
private:
    uint32_t type{};
    uint32_t reserved{};
    uint64_t sector{};

public:
    auto set_type_field(device::virtio_request_type value) -> void {
        switch (value) {
        case device::virtio_request_type::read:
            this->type = 0;
            break;
        case device::virtio_request_type::write:
            this->type = 1;
            break;
        }
    }
    auto set_sector_field(size_t value) {
        this->sector = value;
    }
};
constexpr size_t virtio_block_request_size = 16;
static_assert(sizeof(virtio_block_request) == virtio_block_request_size);

enum class status_t : uint8_t { descriptor_not_done = 0x0, descriptor_done = 0x1, end_of_packet = 0x2 };

class receive_descriptor_t {
private:
    uint64_t buffer_address;
    uint16_t length;
    uint16_t packet_checksum;
    uint8_t status;
    uint8_t errors;
    uint16_t special;

public:
    [[nodiscard]] auto get_buffer_address_field() const -> uint64_t {
        return buffer_address;
    }
    auto set_buffer_address_field(void *value) -> void {
        this->buffer_address = reinterpretable_t<void *>(value).to_integer() -
                               memory::kernel_address_space_constants::virtual_address_begin;
    }
    [[nodiscard]] auto get_length_field() const -> size_t {
        return this->length;
    }
    auto set_length_field(size_t value) -> void {
        this->length = value;
    }
    [[nodiscard]] auto get_descriptor_done_status_field() const -> bool {
        return (this->status & 1) == 1;
    }
    auto set_descriptor_done_status_field(bool value) {
        if (value) {
            this->status |= 1;
        } else {
            this->status &= ~1;
        }
    }
};
constexpr size_t receive_descriptor_size = 16;
static_assert(sizeof(receive_descriptor_t) == receive_descriptor_size);

class transmit_descriptor_t {
private:
    uint64_t buffer_address;
    uint16_t length;
    uint8_t checksum_offset;
    uint8_t command;
    uint8_t status;
    uint8_t checksum_start;
    uint16_t special;

public:
    [[nodiscard]] auto get_buffer_address_field() const -> uint64_t {
        return buffer_address;
    }
    auto set_buffer_address_field(void *value) -> void {
        this->buffer_address = reinterpretable_t<void *>(value).to_integer() -
                               memory::kernel_address_space_constants::virtual_address_begin;
    }
    [[nodiscard]] auto get_length_field() const -> size_t {
        return this->length;
    }
    auto set_length_field(size_t value) -> void {
        this->length = value;
    }
    [[nodiscard]] auto get_end_of_packet_command_field() const -> bool {
        return (this->command & 1) == 1;
    }
    auto set_end_of_packet_command_field(bool value) -> void {
        if (value) {
            this->command |= 1;
        } else {
            this->command &= ~1;
        }
    }
    [[nodiscard]] auto get_report_status_command_field() const -> bool {
        return (this->command & (1 << 3)) != 0;
    }
    auto set_report_status_command_field(bool value) -> void {
        if (value) {
            this->command |= (1 << 3);
        } else {
            this->command &= ~(1 << 3);
        }
    }
    [[nodiscard]] auto get_descriptor_done_status_field() const -> bool {
        return (this->status & 1) == 1;
    }
    auto set_descriptor_done_status_field(bool value) {
        if (value) {
            this->status |= 1;
        } else {
            this->status &= ~1;
        }
    }
};
constexpr size_t transmit_descriptor_size = 16;
static_assert(sizeof(transmit_descriptor_t) == transmit_descriptor_size);

inline auto reverse_byte_order(span_t<byte_t> data) {
    byte_t temporary{};
    for (size_t i = 0; i < data.size() / 2; i++) {
        temporary = data[i];
        data[i] = data[data.size() - 1 - i];
        data[data.size() - 1 - i] = temporary;
    }
}

class ethernet_packet_header_t {
private:
    static constexpr uint16_t internet_protocol_ethertype = 2048;
    static constexpr uint16_t address_resolution_protocol_ethertype = 2054;
    uint64_t destination_address : 48;
    uint64_t source_address : 48;
    uint16_t packet_type;

public:
    [[nodiscard]] auto get_destination_address_field() const -> networking::ethernet_address_t {
        return networking::ethernet_address_t(this->destination_address);
    }
    auto set_destination_address_field(networking::ethernet_address_t value) -> void {
        this->destination_address = value;
    }
    [[nodiscard]] auto get_source_address_field() const -> networking::ethernet_address_t {
        return networking::ethernet_address_t(this->source_address);
    }
    auto set_source_address_field(networking::ethernet_address_t value) -> void {
        this->source_address = value;
    }
    [[nodiscard]] auto get_packet_type_field() const -> networking::protocol_type_t {
        auto value = this->packet_type;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        if (value == internet_protocol_ethertype) {
            return networking::protocol_type_t::internet_protocol;
        }
        if (value == address_resolution_protocol_ethertype) {
            return networking::protocol_type_t::address_resolution_protocol;
        }
        return networking::protocol_type_t::undefined_protocol;
    }
    auto set_packet_type_field(networking::protocol_type_t protocol_type) -> void {
        uint16_t value = 0;
        switch (protocol_type) {
        case networking::protocol_type_t::internet_protocol:
            value = internet_protocol_ethertype;
            break;
        case networking::protocol_type_t::address_resolution_protocol:
            value = address_resolution_protocol_ethertype;
            break;
        default:
            break;
        }
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->packet_type = value;
    }
} __attribute__((packed));
constexpr size_t ethernet_protocol_header_size = 14;
static_assert(sizeof(ethernet_packet_header_t) == ethernet_protocol_header_size);

enum address_resolution_protocol_operation_code : uint16_t { undefined = 0, request = 1, reply = 2 };
class address_resolution_protocol_packet_header_t {
private:
    static constexpr uint16_t ethernet_protocol_hardware_address_space = 1;
    static constexpr uint16_t internet_protocol_protocol_address_space = 2048;
    static constexpr uint8_t ethernet_protocol_hardware_address_length = 6;
    static constexpr uint8_t internet_protocol_protocol_address_length = 4;

    uint16_t hardware_address_space{ethernet_protocol_hardware_address_space};
    uint16_t protocol_address_space{internet_protocol_protocol_address_space};
    uint8_t hardware_address_length{ethernet_protocol_hardware_address_length};
    uint8_t protocol_address_length{internet_protocol_protocol_address_length};
    uint16_t operation_code{};
    uint64_t hardware_address_of_sender : 48;
    uint32_t protocol_address_of_sender{};
    uint64_t hardware_address_of_target : 48;
    uint32_t protocol_address_of_target{};

public:
    address_resolution_protocol_packet_header_t() : hardware_address_of_sender(0), hardware_address_of_target(0) {}
    [[nodiscard]] auto is_ethernet_protocol() const -> bool {
        auto hardware_address_space = this->hardware_address_space;
        reverse_byte_order(as_writable_bytes(span_t(&hardware_address_space, 1)));
        return hardware_address_space == ethernet_protocol_hardware_address_space &&
               this->hardware_address_length == ethernet_protocol_hardware_address_length;
    }
    [[nodiscard]] auto is_internet_protocol() const -> bool {
        auto protocol_address_space = this->protocol_address_space;
        reverse_byte_order(as_writable_bytes(span_t(&protocol_address_space, 1)));
        return protocol_address_space == internet_protocol_protocol_address_space &&
               this->protocol_address_length == internet_protocol_protocol_address_length;
    }
    [[nodiscard]] auto get_operation_code_field() const -> networking::address_resolution_protocol_operation_type_t {
        auto value = this->operation_code;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        if (value == address_resolution_protocol_operation_code::request) {
            return networking::address_resolution_protocol_operation_type_t::request_operation;
        }
        if (value == address_resolution_protocol_operation_code::reply) {
            return networking::address_resolution_protocol_operation_type_t::reply_operation;
        }
        return networking::address_resolution_protocol_operation_type_t::undefined_operation;
    }
    auto set_operation_code_field(networking::address_resolution_protocol_operation_type_t operation_type) -> void {
        auto value = address_resolution_protocol_operation_code::undefined;
        switch (operation_type) {
        case networking::address_resolution_protocol_operation_type_t::undefined_operation:
            break;
        case networking::address_resolution_protocol_operation_type_t::request_operation:
            value = address_resolution_protocol_operation_code::request;
            break;
        case networking::address_resolution_protocol_operation_type_t::reply_operation:
            value = address_resolution_protocol_operation_code::reply;
            break;
        }
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->operation_code = value;
    }
    [[nodiscard]] auto get_hardware_address_of_sender_field() const -> networking::ethernet_address_t {
        return networking::ethernet_address_t(this->hardware_address_of_sender);
    }
    auto set_hardware_address_of_sender_field(networking::ethernet_address_t value) -> void {
        this->hardware_address_of_sender = value;
    }
    [[nodiscard]] auto get_protocol_address_of_sender_field() const -> networking::internet_protocol_address_t {
        auto value = this->protocol_address_of_sender;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return networking::internet_protocol_address_t(value);
    }
    auto set_protocol_address_of_sender_field(networking::internet_protocol_address_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->protocol_address_of_sender = value;
    }
    [[nodiscard]] auto get_hardware_address_of_target_field() const -> networking::ethernet_address_t {
        return networking::ethernet_address_t(this->hardware_address_of_target);
    }
    auto set_hardware_address_of_target_field(networking::ethernet_address_t value) -> void {
        this->hardware_address_of_target = value;
    }
    [[nodiscard]] auto get_protocol_address_of_target_field() const -> networking::internet_protocol_address_t {
        auto value = this->protocol_address_of_target;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return networking::internet_protocol_address_t(value);
    }
    auto set_protocol_address_of_target_field(networking::internet_protocol_address_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->protocol_address_of_target = value;
    }
} __attribute__((packed));
constexpr size_t address_resolution_protocol_packet_header_size = 28;
static_assert(sizeof(address_resolution_protocol_packet_header_t) == address_resolution_protocol_packet_header_size);

enum protocol_number : uint8_t {
    undefined_protocol = 0,
    transmission_control_protocol = 6,
    user_datagram_protocol = 17
};
class internet_protocol_packet_header_t {
private:
    uint8_t version_and_internet_header_length{};
    uint8_t type_of_service{};
    uint16_t total_length{};
    uint16_t identification{};
    uint16_t fragment_offset{};
    uint8_t time_to_live{};
    uint8_t protocol{};
    uint16_t header_checksum{};
    uint32_t source_address{};
    uint32_t destination_address{};

public:
    [[nodiscard]] auto get_version_and_internet_header_length_field() const -> byte_t {
        byte_t value{};
        value.set_value(this->version_and_internet_header_length);
        return value;
    }
    auto set_version_and_internet_header_length_field(byte_t value) -> void {
        this->version_and_internet_header_length = value.get_value();
    }
    [[nodiscard]] auto get_total_length_field() const -> size_t {
        auto value = this->total_length;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return value;
    }
    auto set_total_length_field(uint16_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->total_length = value;
    }
    [[nodiscard]] auto is_fragment_offset_zero() const -> bool {
        auto value = this->fragment_offset;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return value == 0;
    }
    [[nodiscard]] auto get_time_to_live_field() const -> size_t {
        return this->time_to_live;
    }
    auto set_time_to_live_field(size_t value) -> void {
        this->time_to_live = value;
    }
    [[nodiscard]] auto get_protocol_field() const -> networking::protocol_type_t {
        if (this->protocol == protocol_number::transmission_control_protocol) {
            return networking::protocol_type_t::transmission_control_protocol;
        }
        if (this->protocol == protocol_number::user_datagram_protocol) {
            return networking::protocol_type_t::user_datagram_protocol;
        }
        return networking::protocol_type_t::undefined_protocol;
    }
    auto set_protocol_field(networking::protocol_type_t protocol_type) -> void {
        switch (protocol_type) {
        case networking::protocol_type_t::transmission_control_protocol:
            this->protocol = protocol_number::transmission_control_protocol;
            break;
        case networking::protocol_type_t::user_datagram_protocol:
            this->protocol = protocol_number::user_datagram_protocol;
            break;
        default:
            this->protocol = 0;
            break;
        }
    }
    [[nodiscard]] auto get_header_checksum_field() const -> size_t {
        return this->header_checksum;
    }
    auto set_header_checksum_field(size_t value) -> void {
        this->header_checksum = value;
    }
    [[nodiscard]] auto get_source_address_field() const -> networking::internet_protocol_address_t {
        auto value = this->source_address;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return networking::internet_protocol_address_t(value);
    }
    auto set_source_address_field(networking::internet_protocol_address_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->source_address = value;
    }
    [[nodiscard]] auto get_destination_address_field() const -> networking::internet_protocol_address_t {
        auto value = this->destination_address;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return networking::internet_protocol_address_t(value);
    }
    auto set_destination_address_field(networking::internet_protocol_address_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->destination_address = value;
    }
} __attribute__((packed));
constexpr size_t internet_protocol_header_size = 20;
static_assert(sizeof(internet_protocol_packet_header_t) == internet_protocol_header_size);

class pseudo_header_t {
private:
    uint32_t source_address;
    uint32_t destination_address;
    uint8_t reserved;
    uint8_t protocol_number;
    uint16_t tcp_length;

public:
    auto set_source_address_field(networking::internet_protocol_address_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->source_address = value;
    }
    auto set_destination_address_field(networking::internet_protocol_address_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->destination_address = value;
    }
    auto set_protocol_field(networking::protocol_type_t protocol_type) -> void {
        auto value = protocol_number::undefined_protocol;
        switch (protocol_type) {
        case networking::protocol_type_t::transmission_control_protocol:
            value = protocol_number::transmission_control_protocol;
            break;
        case networking::protocol_type_t::user_datagram_protocol:
            value = protocol_number::user_datagram_protocol;
            break;
        default:
            break;
        }
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->protocol_number = value;
    }
    auto set_tcp_length_field(uint16_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->tcp_length = value;
    }
} __attribute__((packed));
constexpr size_t pseudo_header_size = 12;
static_assert(sizeof(pseudo_header_t) == pseudo_header_size);

class transmission_control_protocol_header_t {
private:
    uint16_t source_port{};
    uint16_t destination_port{};
    uint32_t sequence_number{};
    uint32_t acknowledgement_number{};
    uint8_t data_offset{};
    uint8_t control_bits{};
    uint16_t window{};
    uint16_t checksum{};
    uint16_t urgent_pointer{};

public:
    [[nodiscard]] auto get_source_port_field() const -> networking::port_number_t {
        auto value = this->source_port;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return networking::port_number_t(value);
    }
    auto set_source_port_field(networking::port_number_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->source_port = value;
    }
    [[nodiscard]] auto get_destination_port_field() const -> networking::port_number_t {
        auto value = this->destination_port;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return networking::port_number_t(value);
    }
    auto set_destination_port_field(networking::port_number_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->destination_port = value;
    }
    [[nodiscard]] auto get_sequence_number_field() const -> uint32_t {
        auto value = this->sequence_number;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return value;
    }
    auto set_sequence_number_field(uint32_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->sequence_number = value;
    }
    [[nodiscard]] auto get_data_offset_field() const -> size_t {
        return this->data_offset;
    }
    auto set_data_offset_field(size_t value) -> void {
        this->data_offset = value;
    }
    [[nodiscard]] auto get_acknowledgement_number_field() const -> uint32_t {
        auto value = this->acknowledgement_number;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return value;
    }
    auto set_acknowledgement_number_field(uint32_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->acknowledgement_number = value;
    }
    [[nodiscard]] auto get_acknowledgement_flag() const -> bool {
        return (this->control_bits & 1 << 4) != 0;
    }
    auto set_acknowledgement_flag(bool value) -> void {
        if (value) {
            this->control_bits |= 1 << 4;
        } else {
            this->control_bits &= ~(1 << 4);
        }
    }
    [[nodiscard]] auto get_reset_flag() const -> bool {
        return (this->control_bits & 1 << 2) != 0;
    }
    auto set_reset_flag(bool value) -> void {
        if (value) {
            this->control_bits |= 1 << 2;
        } else {
            this->control_bits &= ~(1 << 2);
        }
    }
    [[nodiscard]] auto get_synchronization_flag() const -> bool {
        return (this->control_bits & 1 << 1) != 0;
    }
    auto set_synchronization_flag(bool value) -> void {
        if (value) {
            this->control_bits |= 1 << 1;
        } else {
            this->control_bits &= ~(1 << 1);
        }
    }
    [[nodiscard]] auto get_finish_flag() const -> bool {
        return (this->control_bits & 1) != 0;
    }
    auto set_finish_flag(bool value) -> void {
        if (value) {
            this->control_bits |= 1;
        } else {
            this->control_bits &= ~1;
        }
    }
    [[nodiscard]] auto get_window_field() const -> size_t {
        auto value = this->window;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return value;
    }
    auto set_window_field(uint16_t value) {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->window = value;
    }

    [[nodiscard]] auto get_checksum_field() const -> size_t {
        return this->checksum;
    }
    auto set_checksum_field(size_t value) {
        this->checksum = value;
    }
} __attribute__((packed));
constexpr size_t transmission_control_protocol_header_size = 20;
static_assert(sizeof(transmission_control_protocol_header_t) == transmission_control_protocol_header_size);

class user_datagram_protocol_header_t {
private:
    uint16_t source_port{};
    uint16_t destination_port{};
    uint16_t length{};
    uint16_t checksum{};

public:
    [[nodiscard]] auto get_source_port_field() const -> networking::port_number_t {
        auto value = this->source_port;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return networking::port_number_t(value);
    }
    auto set_source_port_field(networking::port_number_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->source_port = value;
    }
    [[nodiscard]] auto get_destination_port_field() const -> networking::port_number_t {
        auto value = this->destination_port;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return networking::port_number_t(value);
    }
    auto set_destination_port_field(networking::port_number_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->destination_port = value;
    }
    [[nodiscard]] auto get_length_field() const -> size_t {
        auto value = this->length;
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        return value;
    }
    auto set_length_field(uint16_t value) -> void {
        reverse_byte_order(as_writable_bytes(span_t(&value, 1)));
        this->length = value;
    }
} __attribute__((packed));
constexpr size_t user_datagram_protocol_header_size = 8;
static_assert(sizeof(user_datagram_protocol_header_t) == user_datagram_protocol_header_size);

#endif

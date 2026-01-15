#ifndef PCIE_CONFIGURATION_SPACE_HPP
#define PCIE_CONFIGURATION_SPACE_HPP

#include "../lib/array.hpp"
#include "integer.hpp"

#include <cstdint>

struct pcie_configuration_space_function_t {
    class vendor_id_t {
    public:
        [[nodiscard]] auto get_vendor_id_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_vendor_id_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint16_t value;
    } __attribute__((packed));

    class device_id_t {
    public:
        [[nodiscard]] auto get_device_id_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_device_id_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint16_t value;
    } __attribute__((packed));

    class command_t {
    public:
        [[nodiscard]] auto get_io_space_enable_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_io_space_enable_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_memory_space_enable_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_memory_space_enable_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_bus_master_enable_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_bus_master_enable_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_parity_error_response_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_parity_error_response_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_serr_enable_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_serr_enable_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_interrupt_disable_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_interrupt_disable_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint16_t value;
    } __attribute__((packed));

    class status_t {
    public:
        [[nodiscard]] auto get_immediate_readiness_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_immediate_readiness_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_interrupt_status_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_interrupt_status_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_capabilities_list_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_capabilities_list_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_master_data_parity_error_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_master_data_parity_error_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_signaled_target_abort_bit() const -> bool {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_signaled_target_abort_bit(bool value) -> void {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_received_target_abort_bit() const -> bool {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_received_target_abort_bit(bool value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_received_master_abort_bit() const -> bool {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_received_master_abort_bit(bool value) -> void {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_signaled_system_error_bit() const -> bool {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_signaled_system_error_bit(bool value) -> void {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_detected_parity_error_bit() const -> bool {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_detected_parity_error_bit(bool value) -> void {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint16_t value;
    } __attribute__((packed));

    class revision_id_and_class_code_t {
    public:
        [[nodiscard]] auto get_revision_id_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_revision_id_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_programming_interface_bits() const -> uint8_t {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_programming_interface_bits(uint8_t value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_sub_class_code_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_sub_class_code_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_base_class_code_bits() const -> uint8_t {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_base_class_code_bits(uint8_t value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class cache_line_size_t {
    public:
        [[nodiscard]] auto get_cache_line_size_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_cache_line_size_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint8_t value;
    } __attribute__((packed));

    class header_type_t {
    public:
        [[nodiscard]] auto get_header_layout_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_header_layout_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_multi_function_device_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_multi_function_device_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint8_t value;
    } __attribute__((packed));

    class bist_t {
    public:
        [[nodiscard]] auto get_completion_code_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_completion_code_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_start_bist_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_start_bist_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_bist_capable_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_bist_capable_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint8_t value;
    } __attribute__((packed));

    class base_address_t {
    public:
        [[nodiscard]] auto get_base_address_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_base_address_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class subsystem_vendor_id_t {
    public:
        [[nodiscard]] auto get_subsystem_vendor_id_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_subsystem_vendor_id_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint16_t value;
    } __attribute__((packed));

    class subsystem_id_t {
    public:
        [[nodiscard]] auto get_subsystem_id_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_subsystem_id_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint16_t value;
    } __attribute__((packed));

    class expansion_rom_base_address_t {
    public:
        [[nodiscard]] auto get_expansion_rom_enable_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_expansion_rom_enable_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_expansion_rom_validation_status_bits() const -> uint8_t {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_expansion_rom_validation_status_bits(uint8_t value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_expansion_rom_validation_details_bits() const -> uint8_t {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_expansion_rom_validation_details_bits(uint8_t value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_expansion_rom_base_address_bits() const -> uint32_t {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_expansion_rom_base_address_bits(uint32_t value) -> void {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class capabilities_pointer_t {
    public:
        [[nodiscard]] auto get_capabilities_pointer_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_capabilities_pointer_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint8_t value;
    } __attribute__((packed));

    class interrupt_line_t {
    public:
        [[nodiscard]] auto get_interrupt_line_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_interrupt_line_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint8_t value;
    } __attribute__((packed));

    class interrupt_pin_t {
    public:
        [[nodiscard]] auto get_interrupt_pin_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_interrupt_pin_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint8_t value;
    } __attribute__((packed));

    static constexpr auto base_address_length = 6;
    static constexpr auto rsv_1_length = 4;
    static constexpr auto rsv_3_length = 1986;

    vendor_id_t vendor_id;
    device_id_t device_id;
    command_t command;
    status_t status;
    revision_id_and_class_code_t revision_id_and_class_code;
    cache_line_size_t cache_line_size;
    packed_byte_t _rsv_0_;
    header_type_t header_type;
    bist_t bist;
    packed_array_t<base_address_t, base_address_length> base_address;
    packed_array_t<packed_byte_t, rsv_1_length> _rsv_1_;
    subsystem_vendor_id_t subsystem_vendor_id;
    subsystem_id_t subsystem_id;
    expansion_rom_base_address_t expansion_rom_base_address;
    capabilities_pointer_t capabilities_pointer;
    uint64_t _rsv_2_ : 56;
    interrupt_line_t interrupt_line;
    interrupt_pin_t interrupt_pin;
    packed_array_t<packed_byte_t, rsv_3_length> _rsv_3_;
} __attribute__((packed));

struct pcie_configuration_space_t {
    static constexpr auto maximum_number_of_functions = 32;
    packed_array_t<pcie_configuration_space_function_t, maximum_number_of_functions> functions;
} __attribute__((packed));

// NOLINTBEGIN
static_assert(offsetof(pcie_configuration_space_function_t, command) == 1 * 4);
static_assert(offsetof(pcie_configuration_space_function_t, base_address) == 4 * 4);
static_assert(offsetof(pcie_configuration_space_function_t, interrupt_line) == 0x3c);
static_assert(sizeof(pcie_configuration_space_function_t) == 2048);
// NOLINTEND

#endif

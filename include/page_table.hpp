#ifndef PAGE_TABLE_HPP
#define PAGE_TABLE_HPP

#include "../lib/array.hpp"
#include "memory.hpp"

#include <cstddef>
#include <cstdint>

namespace memory {

class page_table_t;

class page_table_descriptor_t {
public:
    page_table_descriptor_t();
    page_table_descriptor_t(page_table_t *table_address);
    page_table_descriptor_t(uintptr_t table_address);
    page_table_descriptor_t(uintptr_t page_address, bool is_device_memory, bool is_read_only, bool is_privileged_only,
                            bool is_privileged_executable, bool is_unprivileged_executable);
    [[nodiscard]] auto is_valid() const -> bool;
    [[nodiscard]] auto get_next_level_table_address() const -> page_table_t *;
    [[nodiscard]] auto get_output_address_upper_bits() const -> uintptr_t;

private:
    uint64_t value;

    [[nodiscard]] auto get_next_level_table_address_bits() const -> uintptr_t;
    auto set_next_level_table_address_bits(uintptr_t value) -> void;
    [[nodiscard]] auto get_pxntable_bit() const -> bool;
    auto set_pxntable_bit(bool value) -> void;
    [[nodiscard]] auto get_uxntable_bit() const -> bool;
    auto set_uxntable_bit(bool value) -> void;
    [[nodiscard]] auto get_aptable_bits() const -> uint8_t;
    auto set_aptable_bits(uint8_t value) -> void;
    [[nodiscard]] auto get_nstable_bit() const -> bool;
    auto set_nstable_bit(bool value) -> void;
    [[nodiscard]] auto get_attrindx_bits() const -> uint8_t;
    auto set_attrindx_bits(uint8_t value) -> void;
    [[nodiscard]] auto get_ns_bit() const -> bool;
    auto set_ns_bit(bool value) -> void;
    [[nodiscard]] auto get_ap_bits() const -> uint8_t;
    auto set_ap_bits(uint8_t value) -> void;
    [[nodiscard]] auto get_sh_bits() const -> uint8_t;
    auto set_sh_bits(uint8_t value) -> void;
    [[nodiscard]] auto get_af_bit() const -> bool;
    auto set_af_bit(bool value) -> void;
    [[nodiscard]] auto get_ng_bit() const -> bool;
    auto set_ng_bit(bool value) -> void;
    [[nodiscard]] auto get_output_address_bits() const -> uintptr_t;
    auto set_output_address_bits(uintptr_t value) -> void;
    [[nodiscard]] auto get_dbm_bit() const -> bool;
    auto set_dbm_bit(bool value) -> void;
    [[nodiscard]] auto get_contiguous_bit() const -> bool;
    auto set_contiguous_bit(bool value) -> void;
    [[nodiscard]] auto get_pxn_bit() const -> bool;
    auto set_pxn_bit(bool value) -> void;
    [[nodiscard]] auto get_uxn_bit() const -> bool;
    auto set_uxn_bit(bool value) -> void;
};
static_assert(sizeof(page_table_descriptor_t) == sizeof(uint64_t));

class page_table_t {
public:
    enum class type_t { device, text, data, user };
    enum class mode_t { create_el1_mapping, create_el0_mapping, do_not_create };

    auto get_descriptor_at_index(size_t index) -> page_table_descriptor_t &;
    void set_descriptor_at_index(size_t index, page_table_descriptor_t value);
    auto get_address_of_descriptor_at_index(size_t index) -> page_table_descriptor_t *;
    auto translate(uintptr_t virtual_address) -> uintptr_t;
    auto map(uintptr_t virtual_address, type_t type, uintptr_t physical_address, size_t size) -> void;
    auto map(uintptr_t virtual_address, type_t type, void *physical_address, size_t size) -> void;
    auto map(uintptr_t virtual_address, type_t type, void (*physical_address)(), size_t size) -> void;
    auto unmap(uintptr_t virtual_address, size_t size) -> void;
    auto clear() -> void;

private:
    auto walk(uintptr_t value, mode_t mode) -> page_table_descriptor_t *;

    array_t<page_table_descriptor_t, page_size / sizeof(page_table_descriptor_t)> data;
};
static_assert(sizeof(page_table_t) == page_size);

} // namespace memory
#endif

#include "../include/page_table.hpp"
#include "../include/buddy_allocator.hpp"
#include "../include/panic.hpp"
#include "../include/virtual_memory.hpp"

namespace memory {

page_table_descriptor_t::page_table_descriptor_t() : value{0b00} {}

page_table_descriptor_t::page_table_descriptor_t(page_table_t *table_address) : value{0b11} {
    this->set_next_level_table_address_bits(reinterpretable_t<void *>(table_address).to_integer());
    this->set_pxntable_bit(false);
    this->set_uxntable_bit(false);
    this->set_aptable_bits(0b00);
    this->set_nstable_bit(false);
}

page_table_descriptor_t::page_table_descriptor_t(uintptr_t table_address) : value{0b11} {
    this->set_next_level_table_address_bits(table_address);
    this->set_pxntable_bit(false);
    this->set_uxntable_bit(false);
    this->set_aptable_bits(0b00);
    this->set_nstable_bit(false);
}

page_table_descriptor_t::page_table_descriptor_t(uintptr_t page_address, bool is_device_memory, bool is_read_only,
                                                 bool is_privileged_only, bool is_privileged_executable,
                                                 bool is_unprivileged_executable)
    : value{0b11} {
    if (is_device_memory) {
        this->set_attrindx_bits(0b000);
    } else {
        this->set_attrindx_bits(0b001);
    }
    this->set_ns_bit(false);
    if (!is_read_only) {
        if (is_privileged_only) {
            this->set_ap_bits(0b00);
        } else {
            this->set_ap_bits(0b01);
        }
    } else {
        if (is_privileged_only) {
            this->set_ap_bits(0b10);
        } else {
            this->set_ap_bits(0b11);
        }
    }
    this->set_sh_bits(0b00);
    this->set_af_bit(true);
    this->set_ng_bit(false);
    this->set_output_address_bits(page_address);
    this->set_dbm_bit(false);
    this->set_contiguous_bit(false);
    if (is_privileged_executable) {
        this->set_pxn_bit(false);
    } else {
        this->set_pxn_bit(true);
    }
    if (is_unprivileged_executable) {
        this->set_uxn_bit(false);
    } else {
        this->set_uxn_bit(true);
    }
}

[[nodiscard]] auto page_table_descriptor_t::is_valid() const -> bool {
    return (this->value & 1) == 1;
}

[[nodiscard]] auto page_table_descriptor_t::get_next_level_table_address() const -> page_table_t * {
    return reinterpret_cast<page_table_t *>(memory::kernel_address_space_constants::virtual_address_begin |
                                            this->get_next_level_table_address_bits());
}

[[nodiscard]] auto page_table_descriptor_t::get_output_address_upper_bits() const -> uintptr_t {
    return this->get_output_address_bits();
}

[[nodiscard]] auto page_table_descriptor_t::get_next_level_table_address_bits() const -> uintptr_t {
    constexpr auto offset = 12;
    constexpr uint64_t mask = 0b111111111111111111111111111111111111;
    return this->value & (mask << offset);
}

auto page_table_descriptor_t::set_next_level_table_address_bits(uintptr_t value) -> void {
    constexpr auto offset = 12;
    constexpr uint64_t mask = 0b111111111111111111111111111111111111;
    this->value = (this->value & ~(mask << offset)) | (value & (mask << offset));
}

[[nodiscard]] auto page_table_descriptor_t::get_pxntable_bit() const -> bool {
    constexpr auto offset = 59;
    constexpr uint64_t mask = 0b1;
    return (this->value & (mask << offset)) != 0;
}

auto page_table_descriptor_t::set_pxntable_bit(bool value) -> void {
    constexpr auto offset = 59;
    constexpr uint64_t mask = 0b1;
    value ? this->value |= mask << offset : this->value &= ~(mask << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_uxntable_bit() const -> bool {
    constexpr auto offset = 60;
    constexpr uint64_t mask = 0b1;
    return (this->value & (mask << offset)) != 0;
}

auto page_table_descriptor_t::set_uxntable_bit(bool value) -> void {
    constexpr auto offset = 60;
    constexpr uint64_t mask = 0b1;
    value ? this->value |= mask << offset : this->value &= ~(mask << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_aptable_bits() const -> uint8_t {
    constexpr auto offset = 61;
    constexpr uint64_t mask = 0b11;
    return (this->value & (mask << offset)) >> offset;
}

auto page_table_descriptor_t::set_aptable_bits(uint8_t value) -> void {
    constexpr auto offset = 61;
    constexpr uint64_t mask = 0b11;
    this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_nstable_bit() const -> bool {
    constexpr auto offset = 63;
    constexpr uint64_t mask = 0b1;
    return (this->value & (mask << offset)) != 0;
}

auto page_table_descriptor_t::set_nstable_bit(bool value) -> void {
    constexpr auto offset = 63;
    constexpr uint64_t mask = 0b1;
    value ? this->value |= mask << offset : this->value &= ~(mask << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_attrindx_bits() const -> uint8_t {
    constexpr auto offset = 2;
    constexpr uint64_t mask = 0b111;
    return (this->value & (mask << offset)) >> offset;
}

auto page_table_descriptor_t::set_attrindx_bits(uint8_t value) -> void {
    constexpr auto offset = 2;
    constexpr uint64_t mask = 0b111;
    this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_ns_bit() const -> bool {
    constexpr auto offset = 5;
    constexpr uint64_t mask = 0b1;
    return (this->value & (mask << offset)) != 0;
}

auto page_table_descriptor_t::set_ns_bit(bool value) -> void {
    constexpr auto offset = 5;
    constexpr uint64_t mask = 0b1;
    value ? this->value |= mask << offset : this->value &= ~(mask << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_ap_bits() const -> uint8_t {
    constexpr auto offset = 6;
    constexpr uint64_t mask = 0b11;
    return (this->value & (mask << offset)) >> offset;
}

auto page_table_descriptor_t::set_ap_bits(uint8_t value) -> void {
    constexpr auto offset = 6;
    constexpr uint64_t mask = 0b11;
    this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_sh_bits() const -> uint8_t {
    constexpr auto offset = 8;
    constexpr uint64_t mask = 0b11;
    return (this->value & (mask << offset)) >> offset;
}

auto page_table_descriptor_t::set_sh_bits(uint8_t value) -> void {
    constexpr auto offset = 8;
    constexpr uint64_t mask = 0b11;
    this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_af_bit() const -> bool {
    constexpr auto offset = 10;
    constexpr uint64_t mask = 0b1;
    return (this->value & (mask << offset)) != 0;
}

auto page_table_descriptor_t::set_af_bit(bool value) -> void {
    constexpr auto offset = 10;
    constexpr uint64_t mask = 0b1;
    value ? this->value |= mask << offset : this->value &= ~(mask << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_ng_bit() const -> bool {
    constexpr auto offset = 11;
    constexpr uint64_t mask = 0b1;
    return (this->value & (mask << offset)) != 0;
}

auto page_table_descriptor_t::set_ng_bit(bool value) -> void {
    constexpr auto offset = 11;
    constexpr uint64_t mask = 0b1;
    value ? this->value |= mask << offset : this->value &= ~(mask << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_output_address_bits() const -> uintptr_t {
    constexpr auto offset = 12;
    constexpr uint64_t mask = 0b111111111111111111111111111111111111;
    return this->value & (mask << offset);
}

auto page_table_descriptor_t::set_output_address_bits(uintptr_t value) -> void {
    constexpr auto offset = 12;
    constexpr uint64_t mask = 0b111111111111111111111111111111111111;
    this->value = (this->value & ~(mask << offset)) | (value & (mask << offset));
}

[[nodiscard]] auto page_table_descriptor_t::get_dbm_bit() const -> bool {
    constexpr auto offset = 51;
    constexpr uint64_t mask = 0b1;
    return (this->value & (mask << offset)) != 0;
}

auto page_table_descriptor_t::set_dbm_bit(bool value) -> void {
    constexpr auto offset = 51;
    constexpr uint64_t mask = 0b1;
    value ? this->value |= mask << offset : this->value &= ~(mask << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_contiguous_bit() const -> bool {
    constexpr auto offset = 52;
    constexpr uint64_t mask = 0b1;
    return (this->value & (mask << offset)) != 0;
}

auto page_table_descriptor_t::set_contiguous_bit(bool value) -> void {
    constexpr auto offset = 52;
    constexpr uint64_t mask = 0b1;
    value ? this->value |= mask << offset : this->value &= ~(mask << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_pxn_bit() const -> bool {
    constexpr auto offset = 53;
    constexpr uint64_t mask = 0b1;
    return (this->value & (mask << offset)) != 0;
}

auto page_table_descriptor_t::set_pxn_bit(bool value) -> void {
    constexpr auto offset = 53;
    constexpr uint64_t mask = 0b1;
    value ? this->value |= mask << offset : this->value &= ~(mask << offset);
}

[[nodiscard]] auto page_table_descriptor_t::get_uxn_bit() const -> bool {
    constexpr auto offset = 54;
    constexpr uint64_t mask = 0b1;
    return (this->value & (mask << offset)) != 0;
}

auto page_table_descriptor_t::set_uxn_bit(bool value) -> void {
    constexpr auto offset = 54;
    constexpr uint64_t mask = 0b1;
    value ? this->value |= mask << offset : this->value &= ~(mask << offset);
}

auto get_level_0_page_table_index(uintptr_t value) -> size_t {
    return (value & (memory::virtual_memory_constants::virtual_address_field_mask::level_0_page_table_index
                     << memory::virtual_memory_constants::virtual_address_field_offset::level_0_page_table_index)) >>
           memory::virtual_memory_constants::virtual_address_field_offset::level_0_page_table_index;
}

auto get_level_1_page_table_index(uintptr_t value) -> size_t {
    return (value & (memory::virtual_memory_constants::virtual_address_field_mask::level_1_page_table_index
                     << memory::virtual_memory_constants::virtual_address_field_offset::level_1_page_table_index)) >>
           memory::virtual_memory_constants::virtual_address_field_offset::level_1_page_table_index;
}

auto get_level_2_page_table_index(uintptr_t value) -> size_t {
    return (value & (memory::virtual_memory_constants::virtual_address_field_mask::level_2_page_table_index
                     << memory::virtual_memory_constants::virtual_address_field_offset::level_2_page_table_index)) >>
           memory::virtual_memory_constants::virtual_address_field_offset::level_2_page_table_index;
}

auto get_level_3_page_table_index(uintptr_t value) -> size_t {
    return (value & (memory::virtual_memory_constants::virtual_address_field_mask::level_3_page_table_index
                     << memory::virtual_memory_constants::virtual_address_field_offset::level_3_page_table_index)) >>
           memory::virtual_memory_constants::virtual_address_field_offset::level_3_page_table_index;
}

auto get_output_address_lower_bits(uintptr_t value) -> uintptr_t {
    return value & memory::virtual_memory_constants::virtual_address_field_mask::physical_address_lower_bits;
}

auto page_table_t::get_descriptor_at_index(size_t index) -> page_table_descriptor_t & {
    return data[index];
}

void page_table_t::set_descriptor_at_index(size_t index, page_table_descriptor_t value) {
    data[index] = value;
}

auto page_table_t::get_address_of_descriptor_at_index(size_t index) -> page_table_descriptor_t * {
    return &data[index];
}

auto page_table_t::translate(uintptr_t virtual_address) -> uintptr_t {
    auto *page_descriptor = this->walk(virtual_address, mode_t::do_not_create);
    if (page_descriptor == nullptr) {
        return 0;
    }
    return page_descriptor->get_output_address_upper_bits() | get_output_address_lower_bits(virtual_address);
}

auto page_table_t::map(uintptr_t virtual_address, type_t type, uintptr_t physical_address, std::size_t size) -> void {
    for (size_t offset = 0; offset < size; offset += page_size) {
        page_table_descriptor_t *page_descriptor = nullptr;
        switch (type) {
        case page_table_t::type_t::device:
        case page_table_t::type_t::text:
        case page_table_t::type_t::data:
            page_descriptor = this->walk(virtual_address + offset, mode_t::create_el1_mapping);
            break;
        case page_table_t::type_t::user:
            page_descriptor = this->walk(virtual_address + offset, mode_t::create_el0_mapping);
            break;
        }
        if (page_descriptor == nullptr) {
            panic("page_table::map");
        }
        switch (type) {
        case type_t::device:
            *page_descriptor = page_table_descriptor_t(physical_address + offset, true, false, true, true, true);
            break;
        case type_t::text:
            *page_descriptor = page_table_descriptor_t(physical_address + offset, false, true, true, true, false);
            break;
        case type_t::data:
            *page_descriptor = page_table_descriptor_t(physical_address + offset, false, false, true, false, false);
            break;
        case type_t::user:
            *page_descriptor = page_table_descriptor_t(physical_address + offset, false, false, false, true, true);
            break;
        }
    }
}

auto page_table_t::map(uintptr_t virtual_address, type_t type, void *physical_address, size_t size) -> void {
    this->map(virtual_address, type, reinterpretable_t<void *>(physical_address).to_integer(), size);
}

auto page_table_t::map(uintptr_t virtual_address, type_t type, void (*physical_address)(), size_t size) -> void {
    this->map(virtual_address, type, reinterpretable_t<void (*)()>(physical_address).to_integer(), size);
}

auto page_table_t::unmap(uintptr_t virtual_address, size_t size) -> void {
    for (size_t offset = 0; offset < size; offset += page_size) {
        auto *page_descriptor = this->walk(virtual_address + offset, mode_t::do_not_create);
        if (page_descriptor == nullptr) {
            panic("page_table::unmap");
        }
        *page_descriptor = page_table_descriptor_t();
    }
}

auto page_table_t::walk(uintptr_t value, mode_t mode) -> page_table_descriptor_t * {
    auto level_0_page_table_index = get_level_0_page_table_index(value);
    auto level_0_page_table_descriptor = this->get_descriptor_at_index(level_0_page_table_index);
    if (!level_0_page_table_descriptor.is_valid()) {
        switch (mode) {
        case mode_t::create_el1_mapping: {
            auto &new_page_table = virtual_memory::get().allocate_new_exception_level_1_page_table();
            for (size_t i = 0; i < sizeof(page_table_t) / sizeof(page_table_descriptor_t); i++) {
                new_page_table.set_descriptor_at_index(i, {});
            }
            level_0_page_table_descriptor = page_table_descriptor_t(&new_page_table);
            this->set_descriptor_at_index(level_0_page_table_index, level_0_page_table_descriptor);
            break;
        }
        case mode_t::create_el0_mapping: {
            auto *new_page_table = buddy_allocator::get().allocate<page_table_t>(0);
            for (size_t i = 0; i < sizeof(page_table_t) / sizeof(page_table_descriptor_t); i++) {
                new_page_table->set_descriptor_at_index(i, {});
            }
            level_0_page_table_descriptor = page_table_descriptor_t(new_page_table);
            this->set_descriptor_at_index(level_0_page_table_index, level_0_page_table_descriptor);
            break;
        }
        case mode_t::do_not_create: {
            return nullptr;
        }
        }
    }

    auto *level_1_page_table_address = level_0_page_table_descriptor.get_next_level_table_address();
    auto level_1_page_table_index = get_level_1_page_table_index(value);
    auto level_1_page_table_descriptor = level_1_page_table_address->get_descriptor_at_index(level_1_page_table_index);
    if (!level_1_page_table_descriptor.is_valid()) {
        switch (mode) {
        case mode_t::create_el1_mapping: {
            auto &new_page_table = virtual_memory::get().allocate_new_exception_level_1_page_table();
            for (size_t i = 0; i < sizeof(page_table_t) / sizeof(page_table_descriptor_t); i++) {
                new_page_table.set_descriptor_at_index(i, {});
            }
            level_1_page_table_descriptor = page_table_descriptor_t(&new_page_table);
            level_1_page_table_address->set_descriptor_at_index(level_1_page_table_index,
                                                                level_1_page_table_descriptor);
            break;
        }
        case mode_t::create_el0_mapping: {
            auto *new_page_table = buddy_allocator::get().allocate<page_table_t>(0);
            for (size_t i = 0; i < sizeof(page_table_t) / sizeof(page_table_descriptor_t); i++) {
                new_page_table->set_descriptor_at_index(i, {});
            }
            level_1_page_table_descriptor = page_table_descriptor_t(new_page_table);
            level_1_page_table_address->set_descriptor_at_index(level_1_page_table_index,
                                                                level_1_page_table_descriptor);
            break;
        }
        case mode_t::do_not_create: {
            return nullptr;
        }
        }
    }

    auto *level_2_page_table_address = level_1_page_table_descriptor.get_next_level_table_address();
    auto level_2_page_table_index = get_level_2_page_table_index(value);
    auto level_2_page_table_descriptor = level_2_page_table_address->get_descriptor_at_index(level_2_page_table_index);
    if (!level_2_page_table_descriptor.is_valid()) {
        switch (mode) {
        case mode_t::create_el1_mapping: {
            auto &new_page_table = virtual_memory::get().allocate_new_exception_level_1_page_table();
            for (size_t i = 0; i < sizeof(page_table_t) / sizeof(page_table_descriptor_t); i++) {
                new_page_table.set_descriptor_at_index(i, {});
            }
            level_2_page_table_descriptor = page_table_descriptor_t(&new_page_table);
            level_2_page_table_address->set_descriptor_at_index(level_2_page_table_index,
                                                                level_2_page_table_descriptor);
            break;
        }
        case mode_t::create_el0_mapping: {
            auto *new_page_table = buddy_allocator::get().allocate<page_table_t>(0);
            for (size_t i = 0; i < sizeof(page_table_t) / sizeof(page_table_descriptor_t); i++) {
                new_page_table->set_descriptor_at_index(i, {});
            }
            level_2_page_table_descriptor = page_table_descriptor_t(new_page_table);
            level_2_page_table_address->set_descriptor_at_index(level_2_page_table_index,
                                                                level_2_page_table_descriptor);
            break;
        }
        case mode_t::do_not_create: {
            return nullptr;
        }
        }
    }

    auto *level_3_page_table_address = level_2_page_table_descriptor.get_next_level_table_address();
    auto level_3_page_table_index = get_level_3_page_table_index(value);
    return &level_3_page_table_address->get_descriptor_at_index(level_3_page_table_index);
}

auto clear_level_3_page_table(page_table_t *level_3_page_table_address) -> void {
    for (size_t level_3_page_table_index = 0;
         level_3_page_table_index < sizeof(page_table_t) / sizeof(page_table_descriptor_t);
         level_3_page_table_index++) {
        auto *level_3_page_table_descriptor_address =
            level_3_page_table_address->get_address_of_descriptor_at_index(level_3_page_table_index);
        if (level_3_page_table_descriptor_address->is_valid()) {
            auto page_physical_address = level_3_page_table_descriptor_address->get_output_address_upper_bits();
            buddy_allocator::get().deallocate(reinterpret_cast<void *>(
                kernel_address_space_constants::virtual_address_begin + page_physical_address));
        }
    }
};

auto clear_level_2_page_table(page_table_t *level_2_page_table_address) -> void {
    for (size_t level_2_page_table_index = 0;
         level_2_page_table_index < sizeof(page_table_t) / sizeof(page_table_descriptor_t);
         level_2_page_table_index++) {
        auto *level_2_page_table_descriptor_address =
            level_2_page_table_address->get_address_of_descriptor_at_index(level_2_page_table_index);
        if (level_2_page_table_descriptor_address->is_valid()) {
            auto *level_3_page_table_address = level_2_page_table_descriptor_address->get_next_level_table_address();
            if (level_3_page_table_address != nullptr) {
                clear_level_3_page_table(level_3_page_table_address);
                buddy_allocator::get().deallocate(level_3_page_table_address);
            }
        }
    }
}

auto clear_level_1_page_table(page_table_t *level_1_page_table_address) -> void {
    for (size_t level_1_page_table_index = 0;
         level_1_page_table_index < sizeof(page_table_t) / sizeof(page_table_descriptor_t);
         level_1_page_table_index++) {
        auto *level_1_page_table_descriptor_address =
            level_1_page_table_address->get_address_of_descriptor_at_index(level_1_page_table_index);
        if (level_1_page_table_descriptor_address->is_valid()) {
            auto *level_2_page_table_address = level_1_page_table_descriptor_address->get_next_level_table_address();
            if (level_2_page_table_address != nullptr) {
                clear_level_2_page_table(level_2_page_table_address);
                buddy_allocator::get().deallocate(level_2_page_table_address);
            }
        }
    }
}

auto page_table_t::clear() -> void {
    for (size_t level_0_page_table_index = 0;
         level_0_page_table_index < sizeof(page_table_t) / sizeof(page_table_descriptor_t);
         level_0_page_table_index++) {
        auto level_0_page_table_descriptor = this->get_descriptor_at_index(level_0_page_table_index);
        if (level_0_page_table_descriptor.is_valid()) {
            auto *level_1_page_table_address = level_0_page_table_descriptor.get_next_level_table_address();
            if (level_1_page_table_address != nullptr) {
                clear_level_1_page_table(level_1_page_table_address);
                buddy_allocator::get().deallocate(level_1_page_table_address);
            }
        }
    }
}

} // namespace memory

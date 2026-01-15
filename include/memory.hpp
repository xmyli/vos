#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstddef>
#include <cstdint>

namespace memory {

constexpr size_t page_size = 0x1000ULL;
constexpr size_t section_size = 0x200000ULL;

constexpr uintptr_t virtual_address_mask = 0xffff'0000'0000'0000;
constexpr uintptr_t physical_address_mask = 0x0000'ffff'ffff'ffff;

namespace kernel_address_space_constants {
    constexpr uintptr_t virtual_address_begin = 0xffff000000000000ULL;
    constexpr size_t virtual_address_space_size = 1ULL << 38;
    constexpr uintptr_t physical_address_begin = 0x40000000ULL;
    constexpr size_t physical_address_space_size = 1ULL << 26;
    constexpr uintptr_t link_address = virtual_address_begin + physical_address_begin;
    constexpr uintptr_t gicv3_distributor_begin = virtual_address_begin + 0x08000000ULL;
    constexpr size_t gicv3_distributor_size = 0x10000;
    constexpr uintptr_t gicv3_redistributor_begin = virtual_address_begin + 0x080a0000ULL;
    constexpr size_t gicv3_redistributor_size = 0x20000;
    constexpr uintptr_t pl011_begin = virtual_address_begin + 0x09000000ULL;
    constexpr size_t pl011_size = page_size;
    constexpr uintptr_t virtio_begin = virtual_address_begin + 0x0a000000ULL;
    constexpr size_t virtio_size = page_size;
    constexpr uintptr_t e1000_begin = virtual_address_begin + 0x20000000ULL;
    constexpr size_t e1000_size = 0x20000;
    constexpr uintptr_t pcie_ecam_begin = virtual_address_begin + 0x3f000000ULL;
    constexpr size_t pcie_ecam_size = 0x10000000;
    constexpr int stack_size_order = 3;
    constexpr size_t address_space_size = physical_address_space_size + gicv3_distributor_size +
                                          gicv3_redistributor_size + pl011_size + virtio_size + e1000_size +
                                          pcie_ecam_size;
    constexpr size_t stack_size = page_size * (0x1 << stack_size_order);
} // namespace kernel_address_space_constants

namespace user_address_space_constants {
    constexpr uintptr_t image_begin = 0x400000;
    constexpr int stack_size_order = 3;
    constexpr size_t stack_size = (1 << stack_size_order) * page_size;
    constexpr uintptr_t stack_top = 0x0001'0000'0000'0000;
    constexpr uintptr_t stack_begin = stack_top - stack_size;
    constexpr uintptr_t stack_end = stack_top;
} // namespace user_address_space_constants

// TODO: Relocate these to constants in the new virtual_address_t and physical_address_t classes
namespace virtual_memory_constants {
    namespace virtual_address_field_offset {
        constexpr uint64_t level_0_page_table_index = 39;
        constexpr uint64_t level_1_page_table_index = 30;
        constexpr uint64_t level_2_page_table_index = 21;
        constexpr uint64_t level_3_page_table_index = 12;
    } // namespace virtual_address_field_offset
    namespace virtual_address_field_mask {
        constexpr uint64_t level_0_page_table_index = 0b111'111'111;
        constexpr uint64_t level_1_page_table_index = 0b111'111'111;
        constexpr uint64_t level_2_page_table_index = 0b111'111'111;
        constexpr uint64_t level_3_page_table_index = 0b111'111'111;
        constexpr uint64_t physical_address_lower_bits = 0b111'111'111'111;
    } // namespace virtual_address_field_mask
} // namespace virtual_memory_constants

namespace buddy_allocator_constants {
    constexpr int maximum_order = 64;
}

namespace slab_allocator_constants {
    constexpr int number_of_partially_allocated_slab_lists = 8;
} // namespace slab_allocator_constants

template <typename T> struct object_t;
template <typename T> struct slab_t;

template <typename T> struct object_metadata_t {
    slab_t<T> *pointer_to_slab_containing_this_object;
    object_t<T> *address_of_previous_object;
    object_t<T> *address_of_this_object;
    object_t<T> *address_of_next_object;
    bool is_allocated;
};

template <typename T> struct slab_metadata_t {
    slab_t<T> *pointer_to_previous_slab;
    slab_t<T> *pointer_to_next_slab;
    object_t<T> *unallocated_objects_list_head;
    int number_of_allocated_objects;
};

} // namespace memory

#endif

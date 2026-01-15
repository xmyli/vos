#include "../include/virtual_memory.hpp"
#include "../include/architecture.hpp"
#include "../include/buddy_allocator.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/thread_scheduler.hpp"

namespace memory {

void virtual_memory::initialize() {
    if (architecture::get_core_number() == 0) {
        auto &level_0_page_table = virtual_memory::get().page_tables[0];

        auto gicv3_virtual_address = kernel_address_space_constants::gicv3_distributor_begin;
        auto gicv3_physical_address = gicv3_virtual_address - kernel_address_space_constants::virtual_address_begin;
        auto gicv3_size_in_bytes = kernel_address_space_constants::gicv3_distributor_size;
        level_0_page_table.map(gicv3_virtual_address, page_table_t::type_t::device, gicv3_physical_address,
                               gicv3_size_in_bytes);

        auto gicv3_redist_virtual_address = kernel_address_space_constants::gicv3_redistributor_begin;
        auto gicv3_redist_physical_address =
            gicv3_redist_virtual_address - kernel_address_space_constants::virtual_address_begin;
        auto gicv3_redist_size_in_bytes =
            kernel_address_space_constants::gicv3_redistributor_size * architecture::number_of_cores;
        level_0_page_table.map(gicv3_redist_virtual_address, page_table_t::type_t::device,
                               gicv3_redist_physical_address, gicv3_redist_size_in_bytes);

        auto pl011_virtual_address = kernel_address_space_constants::pl011_begin;
        auto pl011_physical_address = pl011_virtual_address - kernel_address_space_constants::virtual_address_begin;
        auto pl011_size_in_bytes = kernel_address_space_constants::pl011_size;
        level_0_page_table.map(pl011_virtual_address, page_table_t::type_t::device, pl011_physical_address,
                               pl011_size_in_bytes);

        auto virtio_virtual_address = kernel_address_space_constants::virtio_begin;
        auto virtio_physical_address = virtio_virtual_address - kernel_address_space_constants::virtual_address_begin;
        auto virtio_size_in_bytes = kernel_address_space_constants::virtio_size;
        level_0_page_table.map(virtio_virtual_address, page_table_t::type_t::device, virtio_physical_address,
                               virtio_size_in_bytes);

        auto e1000_virtual_address = kernel_address_space_constants::e1000_begin;
        auto e1000_physical_address = e1000_virtual_address - kernel_address_space_constants::virtual_address_begin;
        auto e1000_size_in_bytes = kernel_address_space_constants::e1000_size;
        level_0_page_table.map(e1000_virtual_address, page_table_t::type_t::device, e1000_physical_address,
                               e1000_size_in_bytes);

        auto pcie_virtual_address = kernel_address_space_constants::pcie_ecam_begin;
        auto pcie_physical_address = pcie_virtual_address - kernel_address_space_constants::virtual_address_begin;
        auto pcie_size_in_bytes = kernel_address_space_constants::pcie_ecam_size;
        level_0_page_table.map(pcie_virtual_address, page_table_t::type_t::device, pcie_physical_address,
                               pcie_size_in_bytes);

        auto text_end = reinterpretable_t<void *>(&_text_end_[0]).to_integer();

        auto text_virtual_address = kernel_address_space_constants::link_address;
        auto text_physical_address = text_virtual_address - kernel_address_space_constants::virtual_address_begin;
        auto text_size_in_bytes = text_end - kernel_address_space_constants::link_address;
        level_0_page_table.map(text_virtual_address, page_table_t::type_t::text, text_physical_address,
                               text_size_in_bytes);

        auto data_virtual_address = text_end;
        auto data_physical_address = data_virtual_address - kernel_address_space_constants::virtual_address_begin;
        auto data_size_in_bytes = kernel_address_space_constants::virtual_address_begin +
                                  kernel_address_space_constants::physical_address_begin +
                                  kernel_address_space_constants::physical_address_space_size - text_end;
        level_0_page_table.map(data_virtual_address, page_table_t::type_t::data, data_physical_address,
                               data_size_in_bytes);
    }
    virtual_memory::set_translation_table_base_1_register(&virtual_memory::get().page_tables[0]);
    virtual_memory::flush_translation_lookaside_buffer();
}

auto virtual_memory::get_address_of_kernel_page_table() -> page_table_t * {
    return &this->page_tables[0];
}

auto virtual_memory::allocate_new_exception_level_1_page_table() -> page_table_t & {
    auto &temp = this->page_tables[this->index];
    this->index += 1;
    return temp;
}

void virtual_memory::set_translation_table_base_1_register(page_table_t *level_0_page_table_address) {
    asm volatile("msr ttbr1_el1, %0" ::"r"(level_0_page_table_address));
}

void virtual_memory::set_translation_table_base_0_register(page_table_t *level_0_page_table_address) {
    asm volatile("msr ttbr0_el1, %0" ::"r"(level_0_page_table_address));
}

void virtual_memory::flush_translation_lookaside_buffer() {
    asm volatile("dsb ishst");
    asm volatile("tlbi vmalle1is");
    asm volatile("dsb ish");
    asm volatile("isb");
}

} // namespace memory

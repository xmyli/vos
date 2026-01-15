#ifndef VIRTUAL_MEMORY_HPP
#define VIRTUAL_MEMORY_HPP

#include "../lib/array.hpp"
#include "integer.hpp"
#include "memory.hpp"
#include "page_table.hpp"
#include "symbols.hpp"

namespace memory {

class virtual_memory {
public:
    static auto get() -> virtual_memory & {
        static virtual_memory instance;
        return instance;
    }

    static auto initialize() -> void;

    auto get_address_of_kernel_page_table() -> page_table_t *;
    auto allocate_new_exception_level_1_page_table() -> page_table_t &;

    static void set_translation_table_base_0_register(page_table_t *level_0_page_table_address);
    static void set_translation_table_base_1_register(page_table_t *level_0_page_table_address);
    static void flush_translation_lookaside_buffer();

    virtual_memory(const virtual_memory &) = delete;
    auto operator=(const virtual_memory &) -> virtual_memory & = delete;
    virtual_memory(virtual_memory &&) = delete;
    auto operator=(virtual_memory &&) -> virtual_memory & = delete;

private:
    __attribute__((aligned(page_size)))
    array_t<page_table_t, 2 * kernel_address_space_constants::address_space_size /
                              (sizeof(page_table_t) / sizeof(page_table_descriptor_t) * page_size)>
        page_tables;
    int index = 1;

    virtual_memory() = default;
    ~virtual_memory() = default;
};

} // namespace memory

#endif

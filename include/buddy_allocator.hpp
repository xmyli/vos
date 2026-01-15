#ifndef BUDDY_ALLOCATOR_HPP
#define BUDDY_ALLOCATOR_HPP

#include "../lib/array.hpp"
#include "../lib/span.hpp"
#include "integer.hpp"
#include "memory.hpp"
#include "reinterpretable.hpp"
#include "spin_lock.hpp"
#include "symbols.hpp"

namespace memory {

enum class page_state_t { unallocated, allocated, subordinate };

struct page_metadata_t {
    page_state_t state;
    int order;
    uint64_t previous;
    uint64_t next;
};

using page_t = array_t<byte_t, page_size>;

class buddy_allocator {
public:
    static auto get() -> buddy_allocator & {
        static buddy_allocator instance;
        return instance;
    }

    static auto initialize() -> void;
    static auto print_state() -> void;

    auto allocate(int order) -> span_t<byte_t>;
    auto deallocate(void *address) -> void;

    template <typename T> auto allocate(int order) -> T * {
        return reinterpretable_t<span_t<byte_t>>(this->allocate(order)).to<T>();
    }

    buddy_allocator(const buddy_allocator &) = delete;
    auto operator=(const buddy_allocator &) -> buddy_allocator & = delete;
    buddy_allocator(buddy_allocator &&) = delete;
    auto operator=(buddy_allocator &&) -> buddy_allocator & = delete;

private:
    static constexpr auto hardware_maximum_number_of_pages =
        kernel_address_space_constants::physical_address_space_size / (page_size + sizeof(page_metadata_t));

    synchronization::spin_lock lock;
    size_t number_of_pages = 0;
    array_t<page_metadata_t, hardware_maximum_number_of_pages> *page_metadata_list = nullptr;
    array_t<page_t, hardware_maximum_number_of_pages> *pages_base_address = nullptr;
    array_t<uint64_t, buddy_allocator_constants::maximum_order> free_lists = {};

    void set_page_state(uint64_t index, page_state_t state);
    void set_page_order(uint64_t index, int order);
    void set_page_previous(uint64_t index, uint64_t previous);
    void set_page_next(uint64_t index, uint64_t next);
    void remove_from_free_list(uint64_t index, int order);
    void insert_into_free_list(uint64_t index, int order);

    buddy_allocator() = default;
    ~buddy_allocator() = default;
};

} // namespace memory

#endif

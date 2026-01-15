#include "../include/buddy_allocator.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/panic.hpp"
#include "../include/reinterpretable.hpp"
#include "../include/thread_scheduler.hpp"
#include "../include/virtual_memory.hpp"

namespace memory {

auto buddy_allocator::initialize() -> void {
    if (architecture::get_core_number() == 0) {
        buddy_allocator::get().number_of_pages = (kernel_address_space_constants::physical_address_begin +
                                                  kernel_address_space_constants::physical_address_space_size +
                                                  kernel_address_space_constants::virtual_address_begin -
                                                  reinterpretable_t<void *>(&_kernel_end_[0]).to_integer()) /
                                                 (page_size + sizeof(page_metadata_t));
        buddy_allocator::get().page_metadata_list =
            reinterpret_cast<array_t<page_metadata_t, hardware_maximum_number_of_pages> *>(
                reinterpretable_t<void *>(&_kernel_end_[0]).to_integer());
        buddy_allocator::get().pages_base_address =
            reinterpret_cast<array_t<page_t, hardware_maximum_number_of_pages> *>(
                ((reinterpretable_t<void *>(&_kernel_end_[0]).to_integer() +
                  buddy_allocator::get().number_of_pages * sizeof(page_metadata_t)) |
                 (page_size - 1)) +
                1);
        for (auto &free_list : buddy_allocator::get().free_lists) {
            free_list = UINT64_MAX;
        }
        int current_page_index = 0;
        while (buddy_allocator::get().number_of_pages - current_page_index > 0) {
            auto order =
                uint64_width - 1 - __builtin_clzll(buddy_allocator::get().number_of_pages - current_page_index);
            auto number_of_pages = 0x1ULL << order;
            for (size_t i = 0; i < number_of_pages; i++) {
                if (i == 0) {
                    buddy_allocator::get().free_lists[order] = current_page_index;
                    (*buddy_allocator::get().page_metadata_list)[current_page_index] = {page_state_t::unallocated,
                                                                                        order, UINT64_MAX, UINT64_MAX};
                } else {
                    (*buddy_allocator::get().page_metadata_list)[current_page_index] = {page_state_t::subordinate, -1,
                                                                                        UINT64_MAX, UINT64_MAX};
                }
                current_page_index += 1;
            }
        }
    }
}

void buddy_allocator::set_page_state(uint64_t index, page_state_t state) {
    /*
    auto page = page_metadata_list.offset_by_index(index).read();
    page.state = state;
    page_metadata_list.offset_by_index(index).write(page);
    */
    (*page_metadata_list)[index].state = state;
}

void buddy_allocator::set_page_order(uint64_t index, int order) {
    /*
    auto page = page_metadata_list.offset_by_index(index).read();
    page.order = order;
    page_metadata_list.offset_by_index(index).write(page);
    */
    (*page_metadata_list)[index].order = order;
}

void buddy_allocator::set_page_previous(uint64_t index, uint64_t previous) {
    /*
    auto page = page_metadata_list.offset_by_index(index).read();
    page.previous = previous;
    page_metadata_list.offset_by_index(index).write(page);
    */
    (*page_metadata_list)[index].previous = previous;
}

void buddy_allocator::set_page_next(uint64_t index, uint64_t next) {
    /*
    auto page = page_metadata_list.offset_by_index(index).read();
    page.next = next;
    page_metadata_list.offset_by_index(index).write(page);
    */
    (*page_metadata_list)[index].next = next;
}

void buddy_allocator::remove_from_free_list(uint64_t index, int order) {
    if ((*page_metadata_list)[index].previous != UINT64_MAX) {
        set_page_next((*page_metadata_list)[index].previous, (*page_metadata_list)[index].next);
    } else {
        free_lists[order] = (*page_metadata_list)[index].next;
    }
    if ((*page_metadata_list)[index].next != UINT64_MAX) {
        set_page_previous((*page_metadata_list)[index].next, (*page_metadata_list)[index].previous);
    }
    set_page_previous(index, UINT64_MAX);
    set_page_next(index, UINT64_MAX);
}

void buddy_allocator::insert_into_free_list(uint64_t index, int order) {
    if (free_lists[order] != UINT64_MAX) {
        set_page_previous(free_lists[order], index);
    }
    set_page_previous(index, UINT64_MAX);
    set_page_next(index, free_lists[order]);
    free_lists[order] = index;
}

auto buddy_allocator::allocate(int order) -> span_t<byte_t> {
    this->lock.acquire();
    auto requested_order = order;
    auto queried_order = order;
    while (queried_order < buddy_allocator_constants::maximum_order) {
        if (requested_order == queried_order) {
            if (this->free_lists[queried_order] != UINT64_MAX) {
                auto index_of_pages_to_allocate = this->free_lists[queried_order];
                remove_from_free_list(index_of_pages_to_allocate, queried_order);
                set_page_state(index_of_pages_to_allocate, page_state_t::allocated);
                this->lock.release();
                return {&(*pages_base_address)[index_of_pages_to_allocate][0], page_size << order};
            }
            queried_order += 1;
        }
        if (requested_order < queried_order) {
            if (this->free_lists[queried_order] != UINT64_MAX) {
                auto number_of_pages_for_queried_order = 0x1 << queried_order;
                auto index_of_pages_to_split = this->free_lists[queried_order];
                auto first_half_index = this->free_lists[queried_order];
                auto second_half_index = this->free_lists[queried_order] + number_of_pages_for_queried_order / 2;
                remove_from_free_list(index_of_pages_to_split, queried_order);
                insert_into_free_list(second_half_index, queried_order - 1);
                insert_into_free_list(first_half_index, queried_order - 1);
                set_page_state(first_half_index, page_state_t::unallocated);
                set_page_order(first_half_index, queried_order - 1);
                set_page_state(second_half_index, page_state_t::unallocated);
                set_page_order(second_half_index, queried_order - 1);
                queried_order -= 1;
            } else {
                queried_order += 1;
            }
        }
    }
    panic("buddy_allocator::allocate");
    return {nullptr, 0};
}

auto buddy_allocator::deallocate(void *address) -> void {
    this->lock.acquire();
    auto index = (reinterpretable_t<void *>(address).to_integer() -
                  reinterpretable_t<void *>(this->pages_base_address).to_integer()) /
                 page_size;
    if ((*this->page_metadata_list)[index].state != page_state_t::allocated) {
        panic("buddy_allocator::deallocate");
    }
    while (true) {
        auto order = (*this->page_metadata_list)[index].order;
        size_t buddy_index = 0;
        if (index % (0x1 << (order + 1)) == 0) {
            buddy_index = index + (0x1 << order);
        } else {
            buddy_index = index - (0x1 << order);
        }
        if (buddy_index < this->number_of_pages &&
            (*this->page_metadata_list)[buddy_index].state == page_state_t::unallocated &&
            (*this->page_metadata_list)[buddy_index].order == order) {
            if (buddy_index > index) {
                set_page_state(index, page_state_t::allocated);
                set_page_order(index, order + 1);
                set_page_state(buddy_index, page_state_t::subordinate);
                set_page_order(buddy_index, -1);
                remove_from_free_list(buddy_index, order);
            } else {
                set_page_state(index, page_state_t::subordinate);
                set_page_order(index, -1);
                set_page_state(buddy_index, page_state_t::allocated);
                set_page_order(buddy_index, order + 1);
                remove_from_free_list(buddy_index, order);
                index = buddy_index;
            }
        } else {
            set_page_state(index, page_state_t::unallocated);
            insert_into_free_list(index, order);
            this->lock.release();
            return;
        }
    }
}

} // namespace memory

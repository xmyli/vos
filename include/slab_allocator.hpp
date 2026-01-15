#ifndef SLAB_ALLOCATOR_HPP
#define SLAB_ALLOCATOR_HPP

#include "../lib/array.hpp"
#include "buddy_allocator.hpp"
#include "integer.hpp"
#include "memory.hpp"
#include "page_table.hpp"
#include "panic.hpp"
#include "pl011.hpp"
#include "reinterpretable.hpp"
#include "virtual_memory.hpp"

namespace memory {

template <typename T> class object_t {
public:
    using object_data_t = array_t<byte_t, sizeof(T)>;
    auto get_address_of_data() -> T * {
        return reinterpretable_t<object_data_t *>(&this->data).template to<T>();
    }
    auto get_pointer_to_slab() -> slab_t<T> * {
        return this->metadata.pointer_to_slab_containing_this_object;
    }
    auto set_pointer_to_slab(slab_t<T> *value) -> void {
        this->metadata.pointer_to_slab_containing_this_object = value;
    }
    auto get_address_of_previous_object() -> object_t<T> * {
        return this->metadata.address_of_previous_object;
    }
    auto set_address_of_previous_object(object_t<T> *value) -> void {
        this->metadata.address_of_previous_object = value;
    }
    auto get_address_of_this_object() -> object_t<T> * {
        return this->metadata.address_of_this_object;
    }
    auto set_address_of_this_object(object_t<T> *value) -> void {
        this->metadata.address_of_this_object = value;
    }
    auto get_address_of_next_object() -> object_t<T> * {
        return this->metadata.address_of_next_object;
    }
    auto set_address_of_next_object(object_t<T> *value) -> void {
        this->metadata.address_of_next_object = value;
    }
    auto get_allocation_state() -> bool {
        return this->metadata.is_allocated;
    }
    auto set_allocation_state(bool value) -> void {
        this->metadata.is_allocated = value;
    }

private:
    object_data_t data;
    object_metadata_t<T> metadata;
};

template <typename T> class slab_t {
public:
    using object_data_t = typename object_t<T>::object_data_t;
    static constexpr int maximum_number_of_objects_per_slab =
        (page_size - sizeof(slab_metadata_t<T>)) / sizeof(object_t<T>) - 1;

    auto initialize() -> void {
        for (auto index = 0; index < maximum_number_of_objects_per_slab; index += 1) {
            auto &object = this->objects[index];
            object.set_pointer_to_slab(this);
            if (index > 0) {
                object.set_address_of_previous_object(&this->objects[index - 1]);
            } else {
                object.set_address_of_previous_object(nullptr);
            }
            object.set_address_of_this_object(&object);
            if (index < maximum_number_of_objects_per_slab - 1) {
                object.set_address_of_next_object(&this->objects[index + 1]);
            } else {
                object.set_address_of_next_object(nullptr);
            }
            object.set_allocation_state(false);
        }
        this->metadata.pointer_to_previous_slab = nullptr;
        this->metadata.pointer_to_next_slab = nullptr;
        this->metadata.unallocated_objects_list_head = &this->objects[0];
        this->metadata.number_of_allocated_objects = 0;
    }

    auto get_address_of_previous_slab() -> slab_t<T> * {
        return this->metadata.pointer_to_previous_slab;
    }

    auto set_address_of_previous_slab(slab_t<T> *value) -> void {
        this->metadata.pointer_to_previous_slab = value;
    }

    auto get_address_of_next_slab() -> slab_t<T> * {
        return this->metadata.pointer_to_next_slab;
    }

    auto set_address_of_next_slab(slab_t<T> *value) -> void {
        this->metadata.pointer_to_next_slab = value;
    }

    auto get_address_of_next_unallocated_object() -> object_t<T> * {
        return this->metadata.unallocated_objects_list_head;
    }

    auto get_number_of_unallocated_objects() -> int {
        return maximum_number_of_objects_per_slab - this->metadata.number_of_allocated_objects;
    }

    auto get_number_of_allocated_objects() -> int {
        return this->metadata.number_of_allocated_objects;
    }

    auto remove_object_from_unallocated_list(object_t<T> *object_address) -> void {
        auto address_of_previous_object = object_address->get_address_of_previous_object();
        auto address_of_next_object = object_address->get_address_of_next_object();
        if (address_of_previous_object) {
            address_of_previous_object->set_address_of_next_object(address_of_next_object);
        }
        if (address_of_next_object) {
            address_of_next_object->set_address_of_previous_object(address_of_previous_object);
        }
        if (this->metadata.unallocated_objects_list_head == object_address) {
            this->metadata.unallocated_objects_list_head = object_address->get_address_of_next_object();
        }
        object_address->set_address_of_previous_object(nullptr);
        object_address->set_address_of_next_object(nullptr);
    }

    auto insert_object_into_unallocated_list(object_t<T> *object_address) -> void {
        auto address_of_next_object = this->metadata.unallocated_objects_list_head;
        if (address_of_next_object) {
            address_of_next_object->set_address_of_previous_object(object_address);
        }
        object_address->set_address_of_next_object(address_of_next_object);
        this->metadata.unallocated_objects_list_head = object_address;
    }

    auto increment_number_of_allocated_objects() -> void {
        this->metadata.number_of_allocated_objects += 1;
    }

    auto decrement_number_of_allocated_objects() -> void {
        this->metadata.number_of_allocated_objects -= 1;
    }

private:
    array_t<object_t<T>, (page_size - sizeof(slab_metadata_t<T>)) / sizeof(object_t<T>) - 1> objects;
    slab_metadata_t<T> metadata;
};

template <typename T> class slab_allocator {
    static_assert(sizeof(slab_metadata_t<T>) < (page_size - sizeof(T)));
    static_assert(sizeof(slab_t<T>) < page_size);

public:
    static auto get() -> slab_allocator & {
        static slab_allocator instance;
        return instance;
    }

    auto allocate() -> T * {
        this->lock.acquire();
        slab_t<T> *slab_address{};
        auto has_slab_with_unallocated_objects = false;
        for (auto &slab : this->partially_allocated_slabs) {
            if (slab) {
                has_slab_with_unallocated_objects = true;
                break;
            }
        }
        if (has_slab_with_unallocated_objects) {
            for (auto index = slab_allocator_constants::number_of_partially_allocated_slab_lists - 1; index >= 0;
                 index -= 1) {
                if (this->partially_allocated_slabs[index]) {
                    slab_address = this->partially_allocated_slabs[index];
                    break;
                }
            }
        } else {
            slab_address = buddy_allocator::get().allocate<slab_t<T>>(0);
            slab_address->initialize();
        }
        if (!slab_address) {
            panic("slab_allocator::allocate");
        }
        auto object_address = slab_address->get_address_of_next_unallocated_object();
        slab_address->remove_object_from_unallocated_list(object_address);
        object_address->set_allocation_state(true);
        slab_address->increment_number_of_allocated_objects();
        if (slab_address->get_number_of_allocated_objects() != 1) {
            this->remove_slab_from_slab_list(slab_address);
        }
        this->insert_slab_into_slab_list(slab_address);
        this->lock.release();
        return object_address->get_address_of_data();
    }

    auto deallocate(T *value) -> void {
        this->lock.acquire();
        auto object_address = reinterpret_cast<object_t<T> *>(value);
        if (object_address->get_address_of_this_object() != object_address) {
            panic("slab_allocator::deallocate");
        }
        if (!object_address->get_allocation_state()) {
            panic("slab_allocator::deallocate");
        }
        auto slab_address = object_address->get_pointer_to_slab();
        object_address->set_allocation_state(false);
        slab_address->insert_object_into_unallocated_list(object_address);
        slab_address->decrement_number_of_allocated_objects();
        this->remove_slab_from_slab_list(slab_address);
        if (slab_address->get_number_of_allocated_objects() == 0) {
            buddy_allocator::get().deallocate(slab_address);
        } else {
            this->insert_slab_into_slab_list(slab_address);
        }
        this->lock.release();
    }

    slab_allocator(const slab_allocator &) = delete;
    auto operator=(const slab_allocator &) -> slab_allocator & = delete;
    slab_allocator(slab_allocator &&) = delete;
    auto operator=(slab_allocator &&) -> slab_allocator & = delete;

private:
    synchronization::spin_lock lock;
    array_t<slab_t<T> *, slab_allocator_constants::number_of_partially_allocated_slab_lists>
        partially_allocated_slabs{};
    slab_t<T> *fully_allocated_slabs{};

    auto remove_slab_from_slab_list(slab_t<T> *slab_address) -> void {
        auto previous_slab_address = slab_address->get_address_of_previous_slab();
        auto next_slab_address = slab_address->get_address_of_next_slab();
        if (previous_slab_address) {
            previous_slab_address->set_address_of_next_slab(next_slab_address);
        }
        if (next_slab_address) {
            next_slab_address->set_address_of_previous_slab(previous_slab_address);
        }
        for (auto &slab : this->partially_allocated_slabs) {
            if (slab_address == slab) {
                slab = next_slab_address;
            }
        }
        if (slab_address == this->fully_allocated_slabs) {
            this->fully_allocated_slabs = next_slab_address;
        }
        slab_address->set_address_of_previous_slab(nullptr);
        slab_address->set_address_of_next_slab(nullptr);
    }

    auto insert_slab_into_slab_list(slab_t<T> *slab_address) -> void {
        if (slab_address->get_number_of_unallocated_objects() == 0) {
            auto next_slab_address = this->fully_allocated_slabs;
            if (next_slab_address) {
                next_slab_address->set_address_of_previous_slab(slab_address);
            }
            slab_address->set_address_of_next_slab(next_slab_address);
            this->fully_allocated_slabs = slab_address;
        } else {
            auto index = (slab_address->get_number_of_allocated_objects() *
                          slab_allocator_constants::number_of_partially_allocated_slab_lists) /
                         slab_t<T>::maximum_number_of_objects_per_slab;
            auto next_slab_address = this->partially_allocated_slabs[index];
            if (next_slab_address) {
                next_slab_address->set_address_of_previous_slab(slab_address);
            }
            slab_address->set_address_of_next_slab(next_slab_address);
            this->partially_allocated_slabs[index] = slab_address;
        }
    }

    slab_allocator() = default;
    ~slab_allocator() = default;
};

} // namespace memory

#endif

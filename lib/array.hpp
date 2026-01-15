#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "iterator.hpp"

#include <cstddef>
#include <type_traits>

template <typename value_t, size_t size> class array_t {
public:
    auto at(size_t index) -> value_t & {
        if (index >= size) {
            for (;;) {
                asm volatile("nop");
            }
        }
        return _data[index];
    }
    auto at(size_t index) const -> const value_t & {
        if (index >= size) {
            for (;;) {
                asm volatile("nop");
            }
        }
        return _data[index];
    }
    auto operator[](size_t index) -> value_t & {
        return _data[index];
    }
    auto operator[](size_t index) const -> const value_t & {
        return _data[index];
    }
    auto begin() -> iterator_t<array_t, value_t> {
        return iterator_t<array_t, value_t>(*this, 0);
    }
    auto end() -> iterator_t<array_t, value_t> {
        return iterator_t<array_t, value_t>(*this, size);
    }

private:
    value_t _data[size];
};

template <typename value_t, size_t size> class packed_array_t {
    static_assert(std::is_standard_layout<value_t>::value && std::is_trivial<value_t>::value);

public:
    auto operator[](size_t index) -> value_t & {
        if (index >= size) {
            for (;;) {
                asm volatile("nop");
            }
        }
        return _data[index];
    }
    auto operator[](size_t index) const -> const value_t & {
        if (index >= size) {
            for (;;) {
                asm volatile("nop");
            }
        }
        return _data[index];
    }

private:
    value_t _data[size];
} __attribute__((packed));

#endif

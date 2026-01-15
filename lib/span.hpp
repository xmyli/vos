#ifndef SPAN_HPP
#define SPAN_HPP

#include "../include/integer.hpp"
#include "iterator.hpp"

#include <cstddef>

template <typename T> class span_t;

template <typename T> auto as_bytes(span_t<T> span) -> span_t<byte_t>;

template <typename T> auto as_writable_bytes(span_t<T> span) -> span_t<byte_t>;

template <typename value_t> class span_t {
    friend auto as_bytes<value_t>(span_t<value_t> span) -> span_t<byte_t>;
    friend auto as_writable_bytes<value_t>(span_t<value_t> span) -> span_t<byte_t>;

public:
    span_t(value_t *data, size_t size) : _data(data), _size(size) {}

    auto begin() -> iterator_t<span_t, value_t> {
        return iterator_t<span_t, value_t>(*this, 0);
    }

    auto end() -> iterator_t<span_t, value_t> {
        return iterator_t<span_t, value_t>(*this, this->_size);
    }

    auto operator[](size_t index) -> value_t & {
        return *(_data + index);
    }

    auto operator[](size_t index) const -> const value_t & {
        return *(_data + index);
    }

    [[nodiscard]] auto data() const -> value_t * {
        return this->_data;
    }

    [[nodiscard]] auto size() const -> size_t {
        return this->_size;
    }

private:
    value_t *_data;
    size_t _size;
};

template <typename value_t> auto as_bytes(span_t<value_t> span) -> span_t<byte_t> {
    return span_t<byte_t>(reinterpret_cast<const byte_t *>(span._data), span._size * sizeof(value_t));
}

template <typename value_t> auto as_writable_bytes(span_t<value_t> span) -> span_t<byte_t> {
    return span_t<byte_t>(reinterpret_cast<byte_t *>(span._data), span._size * sizeof(value_t));
}

#endif

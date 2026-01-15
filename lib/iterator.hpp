#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

template <typename container_t, typename value_t> class iterator_t {
    friend container_t;

public:
    auto operator==(iterator_t iterator) -> bool {
        return this->_index == iterator._index;
    }
    auto operator!=(iterator_t iterator) -> bool {
        return this->_index != iterator._index;
    }
    auto operator*() -> value_t & {
        return this->_container[_index];
    }
    auto operator++() -> void {
        ++this->_index;
    }
    auto operator--() -> void {
        --this->_index;
    }

private:
    container_t &_container;
    size_t _index;

    iterator_t(container_t &container, size_t index) : _container(container), _index(index) {}
};

#endif

#ifndef OPTIONAL_HPP
#define OPTIONAL_HPP

#include <cstdint>

template <typename value_t> class optional_t {
public:
    optional_t() = default;
    optional_t(value_t value) : _has_value(true), _value(value) {}
    auto value() -> value_t {
        return _value;
    }
    auto has_value() -> bool {
        return _has_value;
    }

private:
    struct empty_t {};
    union {
        value_t _value;
        empty_t _empty;
    };
    bool _has_value = false;
};

#endif

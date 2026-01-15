#ifndef PAIR_HPP
#define PAIR_HPP

template <typename first_value_t, typename second_value_t> class pair_t {
public:
    pair_t(const first_value_t first_value, const second_value_t second_value)
        : _first_value(first_value), _second_value(second_value) {}

    auto get_first_value() -> first_value_t {
        return this->_first_value;
    }

    auto set_first_value(const first_value_t value) -> void {
        this->_first_value = value;
    }

    auto get_second_value() -> second_value_t {
        return this->_second_value;
    }

    auto set_second_value(const second_value_t value) -> void {
        this->_second_value = value;
    }

private:
    first_value_t _first_value;
    second_value_t _second_value;
};

#endif

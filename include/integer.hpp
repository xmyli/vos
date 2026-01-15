#ifndef INTEGER_HPP
#define INTEGER_HPP

#include <cstdint>
#include <sys/cdefs.h>

constexpr int uint8_width = 8;
constexpr int uint16_width = 16;
constexpr int uint32_width = 32;
constexpr int uint64_width = 64;

class packed_byte_t {
private:
    uint8_t value;

public:
    [[nodiscard]] auto get_value() const -> uint8_t {
        return this->value;
    }
    auto set_value(uint8_t value) -> void {
        this->value = value;
    }
    [[nodiscard]] auto is_zero() const -> bool {
        return this->value == 0;
    }
    friend auto operator==(packed_byte_t left, packed_byte_t right) -> bool {
        return left.value == right.value;
    }
    friend auto operator!=(packed_byte_t left, packed_byte_t right) -> bool {
        return left.value != right.value;
    }
} __attribute__((packed));
static_assert(sizeof(packed_byte_t) == 1);

class byte_t {
private:
    uint8_t value;

public:
    [[nodiscard]] auto get_value() const -> uint8_t {
        return this->value;
    }
    auto set_value(uint8_t value) -> void {
        this->value = value;
    }
    [[nodiscard]] auto is_zero() const -> bool {
        return this->value == 0;
    }
    friend auto operator==(byte_t left, byte_t right) -> bool {
        return left.value == right.value;
    }
    friend auto operator!=(byte_t left, byte_t right) -> bool {
        return left.value != right.value;
    }
};
static_assert(sizeof(byte_t) == 1);

#endif

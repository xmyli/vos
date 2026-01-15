#ifndef PRINTF_HPP
#define PRINTF_HPP

#include "../include/integer.hpp"
#include "array.hpp"

#include <cstddef>
#include <cstdint>

namespace lib {

using get_char_t = char (*)();
using put_char_t = void (*)(char);

constexpr int number_of_hexadecimal_digits = 16;
constexpr int number_of_decimal_digits = 10;
constexpr int buffer_size = 32;

inline auto get_digit(uint64_t index) -> char {
    if (index > number_of_hexadecimal_digits - 1) {
        return ' ';
    }
    if (index < number_of_decimal_digits) {
        return index + '0';
    }
    return index + 'a' - number_of_decimal_digits;
}

inline void printint(put_char_t put_char, uint64_t value, uint64_t base) {
    array_t<char, buffer_size> buffer = {};
    int index = 0;

    index = 0;
    buffer[index++] = get_digit(value % base);
    while ((value /= base) != 0) {
        buffer[index++] = get_digit(value % base);
    }

    while (--index >= 0) {
        put_char(buffer[index]);
    }
}

inline void printptr(put_char_t put_char, const void *value) {
    auto bits = reinterpret_cast<uintptr_t>(value);
    for (size_t i = 0; i < (sizeof(uint64_t) * 2); i++, bits <<= 4) {
        put_char(get_digit(bits >> (uint64_width - 4)));
    }
}

inline void printchar(put_char_t put_char, const char value) {
    put_char(value);
}

inline void printstr(put_char_t put_char, const char *str) {
    while (*str != '\0') {
        put_char(*str);
        str++;
    }
}

// ========== //

inline void printarg(put_char_t put_char, const uint64_t value, char specifier) {
    if (specifier == 'b') {
        printint(put_char, value, 2);
    } else if (specifier == 'd') {
        printint(put_char, value, number_of_decimal_digits);
    } else if (specifier == 'x') {
        printint(put_char, value, number_of_hexadecimal_digits);
    } else if (specifier == 'c') {
        printchar(put_char, value);
    } else {
        printstr(put_char, "\nprintf type mismatch\n");
    }
}

inline void printarg(put_char_t put_char, const char *value, char specifier) {
    if (specifier == 's') {
        printstr(put_char, value);
    } else if (specifier == 'p') {
        printptr(put_char, value);
    } else {
        printstr(put_char, "\nprintf type mismatch\n");
    }
}

inline void printarg(put_char_t put_char, const void *value, char specifier) {
    if (specifier == 'p') {
        printptr(put_char, value);
    } else {
        printstr(put_char, "\nprintf type mismatch\n");
    }
}

// =========== //

inline void printf(put_char_t put_char, const char *str) {
    bool specified = false;
    while (*str != '\0') {
        if (specified) {
            if (*str == '%') {
                printchar(put_char, '%');
                specified = false;
            } else {
                printstr(put_char, "\nprintf error: not enough arguments\n");
                break;
            }
        } else {
            if (*str == '%') {
                specified = true;
            } else {
                printchar(put_char, *str);
            }
        }
        str++;
    }
}

template <typename T, typename... Args>
inline void printf(put_char_t put_char, const char *str, T value, Args... args) {
    bool terminated = false;
    bool specified = false;
    while (!terminated) {
        char val = *str;
        if (specified) {
            switch (val) {
            case '%':
                printchar(put_char, '%');
                specified = false;
                break;
            case 'b':
            case 'd':
            case 'x':
            case 'c':
            case 's':
            case 'p':
                printarg(put_char, value, val);
                printf(put_char, str + 1, args...);
                terminated = true;
                break;
            default:
                printstr(put_char, "\nprintf error: invalid format specifier\n");
                terminated = true;
                break;
            }
        } else {
            if (val == '\0') {
                printstr(put_char, "\nprintf error: too many arguments\n");
                break;
            }
            if (val == '%') {
                specified = true;
            } else {
                printchar(put_char, val);
            }
        }
        str++;
    }
}

} // namespace lib

#endif

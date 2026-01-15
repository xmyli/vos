#ifndef PATH_NAME_HPP
#define PATH_NAME_HPP

#include "../include/pl011.hpp"
#include "../lib/array.hpp"
#include "../lib/span.hpp"
#include "file.hpp"

namespace file {

class path_name_t {
public:
    explicit path_name_t() = default;

    explicit path_name_t(const char *const string) : _data({}), _length(0) {
        auto value = span_t(string, maximum_path_length);
        int index = 0;
        if (value[0] != '/') {
            this->_data[index] = '/';
            index += 1;
        }
        for (size_t offset = 0; value[offset] != '\0' && offset + index < maximum_path_length - 1; offset += 1) {
            this->_data[index] = value[offset];
            index += 1;
        }
        _length = index;
        while (index < maximum_path_length) {
            this->_data[index] = '\0';
            index += 1;
        }
    }

    auto operator==(const path_name_t &path) const -> bool {
        for (int i = 0; i < maximum_path_length; i++) {
            if (this->_data[i] != path._data[i]) {
                return false;
            }
        }
        return true;
    }

    auto operator!=(const path_name_t &path) const -> bool {
        return !(*this == path);
    }

    explicit operator bool() const noexcept {
        return this->_data[0] == '/' && this->_data[maximum_path_length - 1] == '\0';
    }

    auto operator[](int index) -> char & {
        return this->_data[index];
    }

    [[nodiscard]] auto front() const -> path_name_t {
        if (!(*this)) {
            return path_name_t{};
        }
        auto path = path_name_t{};
        path._data[0] = '/';
        path._length = 1;
        for (int index = 1; this->_data[index] != '/' && this->_data[index] != '\0'; index += 1) {
            path._data[path._length] = this->_data[index];
            path._length += 1;
        }
        return path;
    }

    [[nodiscard]] auto pop_front() -> bool {
        if (!(*this)) {
            return false;
        }
        int index = 1;
        while (this->_data[index] != '/' && this->_data[index] != '\0') {
            index += 1;
        }
        int length = index;
        while (index < maximum_path_length) {
            this->_data[index - length] = this->_data[index];
            index += 1;
        }
        for (int index = 0; index < length; index += 1) {
            this->_data[maximum_path_length - 1 - index] = '\0';
        }
        if (this->_data[0] == '\0') {
            this->_data[0] = '/';
            this->_length += 1;
        }
        this->_length -= length;
        return true;
    }

    [[nodiscard]] auto back() const -> path_name_t {
        if (!(*this)) {
            return path_name_t{};
        }
        int index = maximum_path_length - 1;
        while (this->_data[index] != '/') {
            index -= 1;
        }
        auto path = path_name_t{};
        while (this->_data[index] != '\0') {
            path._data[path._length] = this->_data[index];
            path._length += 1;
            index += 1;
        }
        return path;
    }

    [[nodiscard]] auto pop_back() -> bool {
        if (!(*this)) {
            return false;
        }
        int index = maximum_path_length - 1;
        size_t length = 1;
        while (this->_data[index] != '/') {
            if (this->_data[index] != '\0') {
                length += 1;
            }
            index -= 1;
        }
        while (index < maximum_path_length) {
            this->_data[index] = '\0';
            index += 1;
        }
        if (this->_data[0] != '/') {
            this->_data[0] = '/';
            length += 1;
        }
        this->_length -= length;
        return true;
    }

    [[nodiscard]] auto length() const -> size_t {
        return this->_length;
    }

private:
    array_t<char, maximum_path_length> _data;
    size_t _length;
};

} // namespace file

#endif

#ifndef EXCEPTION_HANDLER_HPP
#define EXCEPTION_HANDLER_HPP

#include "external_types.hpp"

#include <cstdint>

namespace process {

class exception_handler {
public:
    static auto get() -> exception_handler & {
        static exception_handler instance;
        return instance;
    }

    static auto initialize() -> void;

    exception_handler(const exception_handler &) = delete;
    auto operator=(const exception_handler &) -> exception_handler & = delete;
    exception_handler(exception_handler &&) = delete;
    auto operator=(exception_handler &&) -> exception_handler & = delete;

private:
    exception_handler() = default;
    ~exception_handler() = default;
};

} // namespace process

#endif

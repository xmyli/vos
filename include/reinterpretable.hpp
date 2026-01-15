#ifndef REINTERPRETABLE_HPP
#define REINTERPRETABLE_HPP

#include "../lib/array.hpp"
#include "../lib/span.hpp"
#include "e1000_registers.hpp"
#include "gicv3_registers.hpp"
#include "integer.hpp"
#include "memory.hpp"
#include "page_table.hpp"
#include "pcie_configuration_space.hpp"
#include "pl011_registers.hpp"
#include "virtio_blk_registers.hpp"

#include <cstdint>
#include <type_traits>

template <typename T = void> class reinterpretable_t {
public:
    gicv3_distributor_registers_t *gicv3_distributor_registers = reinterpret_cast<gicv3_distributor_registers_t *>(
        memory::kernel_address_space_constants::gicv3_distributor_begin);
    gicv3_redistributor_registers_t *gicv3_redistributor_registers =
        reinterpret_cast<gicv3_redistributor_registers_t *>(
            memory::kernel_address_space_constants::gicv3_redistributor_begin);
    pl011_registers_t *pl011_registers =
        reinterpret_cast<pl011_registers_t *>(memory::kernel_address_space_constants::pl011_begin);
    pcie_configuration_space_t *pcie_configuration_space =
        reinterpret_cast<pcie_configuration_space_t *>(memory::kernel_address_space_constants::pcie_ecam_begin);
    e1000_registers_t *e1000_registers =
        reinterpret_cast<e1000_registers_t *>(memory::kernel_address_space_constants::e1000_begin);
    virtio_blk_registers_t *virtio_blk_registers =
        reinterpret_cast<virtio_blk_registers_t *>(memory::kernel_address_space_constants::virtio_begin);
};

template <> class reinterpretable_t<void *> {
public:
    reinterpretable_t(const void *value) : _value(value) {}
    [[nodiscard]] auto to_integer() const -> uintptr_t {
        return reinterpret_cast<uintptr_t>(this->_value);
    }

private:
    const void *_value = nullptr;
};

template <> class reinterpretable_t<void (*)()> {
public:
    reinterpretable_t(void (*value)()) : _value(value) {}
    [[nodiscard]] auto to_integer() const -> uintptr_t {
        return reinterpret_cast<uintptr_t>(this->_value);
    }

private:
    void (*_value)() = nullptr;
};

template <size_t S> class reinterpretable_t<array_t<byte_t, S> *> {
public:
    reinterpretable_t(array_t<byte_t, S> *value) : _value(value) {}
    template <typename T> auto to() const -> T * {
        static_assert(S >= sizeof(T));
        return reinterpret_cast<T *>(this->_value);
    }

private:
    array_t<byte_t, S> *_value = nullptr;
};

template <> class reinterpretable_t<span_t<byte_t>> {
public:
    reinterpretable_t(span_t<byte_t> value) : _value(value) {}
    template <typename T> auto to() const -> T * {
        if constexpr (!std::is_same_v<T, void>) {
            if (sizeof(T) > this->_value.size()) {
                // error
                return nullptr;
            }
        }
        return reinterpret_cast<T *>(this->_value.data());
    }

private:
    span_t<byte_t> _value = {nullptr, 0};
};

template <> class reinterpretable_t<uintptr_t> {
public:
    reinterpretable_t(memory::page_table_t *page_table, uintptr_t value) : _page_table(page_table), _value(value) {}
    template <typename T> auto to() const -> T * {
        if (this->_page_table == nullptr) {
            return nullptr;
        }
        auto physical_address = this->_page_table->translate(this->_value);
        if (physical_address == 0) {
            return nullptr;
        }
        return reinterpret_cast<T *>(memory::kernel_address_space_constants::virtual_address_begin + physical_address);
    }

private:
    memory::page_table_t *_page_table = nullptr;
    uintptr_t _value = 0;
};

#endif

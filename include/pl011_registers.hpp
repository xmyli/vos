#ifndef PL011_REGISTERS_HPP
#define PL011_REGISTERS_HPP

#include "../lib/array.hpp"
#include "integer.hpp"

#include <cstdint>

struct pl011_registers_t {
    class uartdr_t {
    public:
        [[nodiscard]] auto get_data_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_data_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_fe_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_fe_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_pe_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_pe_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_be_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_be_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_oe_bit() const -> bool {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_oe_bit(bool value) -> void {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartrsr_and_uartesr_t {
    public:
        [[nodiscard]] auto get_fe_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_fe_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_pe_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_pe_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_be_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_be_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_oe_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_oe_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartfr_t {
    public:
        [[nodiscard]] auto get_cts_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_cts_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dsr_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dsr_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dcd_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dcd_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_busy_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_busy_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxfe_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxfe_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txff_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txff_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxff_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxff_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txfe_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txfe_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ri_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ri_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartilpr_t {
    public:
        [[nodiscard]] auto get_ilpdvsr_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_ilpdvsr_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartibrd_t {
    public:
        [[nodiscard]] auto get_baud_divint_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_baud_divint_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartfbrd_t {
    public:
        [[nodiscard]] auto get_baud_divfrac_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_baud_divfrac_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartlcr_h_t {
    public:
        [[nodiscard]] auto get_brk_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_brk_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_pen_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_pen_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_eps_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_eps_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_stp2_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_stp2_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_fen_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_fen_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_wlen_bits() const -> uint8_t {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_wlen_bits(uint8_t value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_sps_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sps_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartcr_t {
    public:
        [[nodiscard]] auto get_uarten_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_uarten_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_siren_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_siren_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_sirlp_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sirlp_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_lbe_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_lbe_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txe_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txe_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxe_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxe_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dtr_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dtr_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rts_bit() const -> bool {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rts_bit(bool value) -> void {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_out1_bit() const -> bool {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_out1_bit(bool value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_out2_bit() const -> bool {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_out2_bit(bool value) -> void {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rtsen_bit() const -> bool {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rtsen_bit(bool value) -> void {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ctsen_bit() const -> bool {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ctsen_bit(bool value) -> void {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartifls_t {
    public:
        [[nodiscard]] auto get_txiflsel_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_txiflsel_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_rxiflsel_bits() const -> uint8_t {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_rxiflsel_bits(uint8_t value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartimsc_t {
    public:
        [[nodiscard]] auto get_rimim_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rimim_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ctsmim_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ctsmim_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dcdmim_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dcdmim_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dsrmim_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dsrmim_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxim_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxim_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txim_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txim_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rtim_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rtim_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_feim_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_feim_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_peim_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_peim_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_beim_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_beim_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_oeim_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_oeim_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartris_t {
    public:
        [[nodiscard]] auto get_rirmis_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rirmis_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ctsrmis_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ctsrmis_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dcdrmis_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dcdrmis_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dsrrmis_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dsrrmis_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxris_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxris_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txris_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txris_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rtris_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rtris_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_feris_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_feris_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_peris_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_peris_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_beris_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_beris_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_oeris_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_oeris_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartmis_t {
    public:
        [[nodiscard]] auto get_rimmis_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rimmis_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ctsmmis_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ctsmmis_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dcdmmis_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dcdmmis_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dsrmmis_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dsrmmis_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxmis_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxmis_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txmis_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txmis_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rtmis_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rtmis_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_femis_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_femis_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_pemis_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_pemis_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_bemis_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_bemis_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_oemis_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_oemis_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uarticr_t {
    public:
        [[nodiscard]] auto get_rimic_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rimic_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ctsmic_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ctsmic_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dcdmic_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dcdmic_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dsrmic_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dsrmic_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxic_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxic_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txic_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txic_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rtic_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rtic_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_feic_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_feic_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_peic_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_peic_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_beic_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_beic_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_oeic_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_oeic_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class uartdmacr_t {
    public:
        [[nodiscard]] auto get_rxdmae_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxdmae_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txdmae_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txdmae_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dmaonerr_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dmaonerr_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    static constexpr auto rsv_0_length = 16;
    static constexpr auto rsv_1_length = 4;

    uartdr_t uartdr;
    uartrsr_and_uartesr_t uartrsr_and_uartesr;
    packed_array_t<packed_byte_t, rsv_0_length> _rsv_0_;
    uartfr_t uartfr;
    packed_array_t<packed_byte_t, rsv_1_length> _rsv_1_;
    uartilpr_t uartilpr;
    uartibrd_t uartibrd;
    uartfbrd_t uartfbrd;
    uartlcr_h_t uartlcr_h;
    uartcr_t uartcr;
    uartifls_t uartifls;
    uartimsc_t uartimsc;
    uartris_t uartris;
    uartmis_t uartmis;
    uarticr_t uarticr;
    uartdmacr_t uartdmacr;
} __attribute__((packed));

// NOLINTBEGIN
static_assert(offsetof(pl011_registers_t, uartdr) == 0x0);
static_assert(offsetof(pl011_registers_t, uartrsr_and_uartesr) == 0x4);
static_assert(offsetof(pl011_registers_t, uartfr) == 0x18);
static_assert(offsetof(pl011_registers_t, uartilpr) == 0x20);
static_assert(offsetof(pl011_registers_t, uartibrd) == 0x24);
static_assert(offsetof(pl011_registers_t, uartfbrd) == 0x28);
static_assert(offsetof(pl011_registers_t, uartlcr_h) == 0x2c);
static_assert(offsetof(pl011_registers_t, uartcr) == 0x30);
static_assert(offsetof(pl011_registers_t, uartifls) == 0x34);
static_assert(offsetof(pl011_registers_t, uartimsc) == 0x38);
static_assert(offsetof(pl011_registers_t, uartris) == 0x3c);
static_assert(offsetof(pl011_registers_t, uartmis) == 0x40);
static_assert(offsetof(pl011_registers_t, uarticr) == 0x44);
static_assert(offsetof(pl011_registers_t, uartdmacr) == 0x48);
// NOLINTEND

#endif

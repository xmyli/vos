#ifndef GICV3_REGISTERS_HPP
#define GICV3_REGISTERS_HPP

#include "../lib/array.hpp"
#include "integer.hpp"

#include <cstddef>
#include <cstdint>

struct gicv3_system_registers_t {
    static auto get_icc_pmr_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_PMR_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_pmr_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_PMR_EL1, %0" : : "r"(value));
    }
    static auto get_icc_iar0_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_IAR0_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_eoir0_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_EOIR0_EL1, %0" : : "r"(value));
    }
    static auto get_icc_hppir0_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_HPPIR0_EL1" : "=r"(value));
        return value;
    }
    static auto get_icc_bpr0_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_BPR0_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_bpr0_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_BPR0_EL1, %0" : : "r"(value));
    }
    static auto get_icc_ap0r0_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_AP0R0_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_ap0r0_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_AP0R0_EL1, %0" : : "r"(value));
    }
    static auto get_icc_ap0r1_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_AP0R1_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_ap0r1_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_AP0R1_EL1, %0" : : "r"(value));
    }
    static auto get_icc_ap0r2_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_AP0R2_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_ap0r2_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_AP0R2_EL1, %0" : : "r"(value));
    }
    static auto get_icc_ap0r3_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_AP0R3_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_ap0r3_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_AP0R3_EL1, %0" : : "r"(value));
    }
    static auto get_icc_ap1r0_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_AP1R0_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_ap1r0_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_AP1R0_EL1, %0" : : "r"(value));
    }
    static auto get_icc_ap1r1_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_AP1R1_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_ap1r1_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_AP1R1_EL1, %0" : : "r"(value));
    }
    static auto get_icc_ap1r2_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_AP1R2_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_ap1r2_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_AP1R2_EL1, %0" : : "r"(value));
    }
    static auto get_icc_ap1r3_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_AP1R3_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_ap1r3_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_AP1R3_EL1, %0" : : "r"(value));
    }
    static auto set_icc_dir_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_DIR_EL1, %0" : : "r"(value));
    }
    static auto get_icc_rpr_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_RPR_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_sgi1r_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_SGI1R_EL1, %0" : : "r"(value));
    }
    static auto set_icc_asgi1r_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_ASGI1R_EL1, %0" : : "r"(value));
    }
    static auto set_icc_sgi0r_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_SGI0R_EL1, %0" : : "r"(value));
    }
    static auto get_icc_iar1_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_IAR1_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_eoir1_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_EOIR1_EL1, %0" : : "r"(value));
    }
    static auto get_icc_hppir1_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_HPPIR1_EL1" : "=r"(value));
        return value;
    }
    static auto get_icc_bpr1_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_BPR1_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_bpr1_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_BPR1_EL1, %0" : : "r"(value));
    }
    static auto get_icc_ctlr_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_CTLR_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_ctlr_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_CTLR_EL1, %0" : : "r"(value));
    }
    static auto get_icc_sre_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_SRE_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_sre_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_SRE_EL1, %0" : : "r"(value));
    }
    static auto get_icc_igrpen0_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_IGRPEN0_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_igrpen0_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_IGRPEN0_EL1, %0" : : "r"(value));
    }
    static auto get_icc_igrpen1_el1_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_IGRPEN1_EL1" : "=r"(value));
        return value;
    }
    static auto set_icc_igrpen1_el1_bits(uint64_t value) -> void {
        asm volatile("msr ICC_IGRPEN1_EL1, %0" : : "r"(value));
    }
    static auto get_icc_sre_el2_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_SRE_EL2" : "=r"(value));
        return value;
    }
    static auto set_icc_sre_el2_bits(uint64_t value) -> void {
        asm volatile("msr ICC_SRE_EL2, %0" : : "r"(value));
    }
    static auto get_icc_ctlr_el3_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_CTLR_EL3" : "=r"(value));
        return value;
    }
    static auto set_icc_ctlr_el3_bits(uint64_t value) -> void {
        asm volatile("msr ICC_CTLR_EL3, %0" : : "r"(value));
    }
    static auto get_icc_sre_el3_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_SRE_EL3" : "=r"(value));
        return value;
    }
    static auto set_icc_sre_el3_bits(uint64_t value) -> void {
        asm volatile("msr ICC_SRE_EL3, %0" : : "r"(value));
    }
    static auto get_icc_igrpen1_el3_bits() -> uint64_t {
        uint64_t value = 0;
        asm volatile("mrs %0, ICC_IGRPEN1_EL3" : "=r"(value));
        return value;
    }
    static auto set_icc_igrpen1_el3_bits(uint64_t value) -> void {
        asm volatile("msr ICC_IGRPEN1_EL3, %0" : : "r"(value));
    }
};

struct gicv3_distributor_registers_t {
    class ctlr_t {
    public:
        [[nodiscard]] auto get_enablegrp0_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_enablegrp0_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_enablegrp1ns_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_enablegrp1ns_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_enablegrp1s_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_enablegrp1s_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_are_s_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_are_s_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_are_ns_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_are_ns_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ds_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ds_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_e1nwf_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_e1nwf_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rwp_bit() const -> bool {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rwp_bit(bool value) -> void {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class typer_t {
    public:
        [[nodiscard]] auto get_itlinesnumber_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_itlinesnumber_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_cpunumber_bits() const -> uint8_t {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_cpunumber_bits(uint8_t value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_espi_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_espi_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_securityextn_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_securityextn_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_num_lpis_bits() const -> uint8_t {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b11111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_num_lpis_bits(uint8_t value) -> void {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b11111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_mbis_bit() const -> bool {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_mbis_bit(bool value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_lpis_bit() const -> bool {
            constexpr auto offset = 17;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_lpis_bit(bool value) -> void {
            constexpr auto offset = 17;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dvis_bit() const -> bool {
            constexpr auto offset = 18;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dvis_bit(bool value) -> void {
            constexpr auto offset = 18;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_idbits_bits() const -> uint8_t {
            constexpr auto offset = 19;
            constexpr uint64_t mask = 0b11111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_idbits_bits(uint8_t value) -> void {
            constexpr auto offset = 19;
            constexpr uint64_t mask = 0b11111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_a3v_bit() const -> bool {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_a3v_bit(bool value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_no1n_bit() const -> bool {
            constexpr auto offset = 25;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_no1n_bit(bool value) -> void {
            constexpr auto offset = 25;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rss_bit() const -> bool {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rss_bit(bool value) -> void {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_espi_range_bits() const -> uint8_t {
            constexpr auto offset = 27;
            constexpr uint64_t mask = 0b11111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_espi_range_bits(uint8_t value) -> void {
            constexpr auto offset = 27;
            constexpr uint64_t mask = 0b11111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class iidr_t {
    public:
        [[nodiscard]] auto get_implementer_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_implementer_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_revision_bits() const -> uint8_t {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_revision_bits(uint8_t value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_variant_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_variant_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_productid_bits() const -> uint8_t {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_productid_bits(uint8_t value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class typer2_t {
    public:
        [[nodiscard]] auto get_vid_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_vid_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_vil_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_vil_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_nassgicap_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_nassgicap_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class statusr_t {
    public:
        [[nodiscard]] auto get_rrd_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rrd_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_wrd_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_wrd_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rwod_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rwod_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_wrod_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_wrod_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class setspi_nsr_t {
    public:
        [[nodiscard]] auto get_intid_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_intid_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class clrspi_nsr_t {
    public:
        [[nodiscard]] auto get_intid_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_intid_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class setspi_sr_t {
    public:
        [[nodiscard]] auto get_intid_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_intid_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class clrspi_sr_t {
    public:
        [[nodiscard]] auto get_intid_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_intid_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class igroupr_t {
        class group_status_bits_t {
        public:
            group_status_bits_t(igroupr_t *igroupr, size_t index) : igroupr(igroupr), index(index) {}
            [[nodiscard]] auto get_group_status_bits() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->igroupr->value & (mask << offset)) != 0;
            }
            auto set_group_status_bits(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->igroupr->value |= mask << offset : this->igroupr->value &= ~(mask << offset);
            }

        private:
            igroupr_t *igroupr;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> group_status_bits_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class isenabler_t {
        class set_enable_bits_t {
        public:
            set_enable_bits_t(isenabler_t *isenabler, size_t index) : isenabler(isenabler), index(index) {}
            [[nodiscard]] auto get_set_enable_bits() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->isenabler->value & (mask << offset)) != 0;
            }
            auto set_set_enable_bits(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->isenabler->value |= mask << offset : this->isenabler->value &= ~(mask << offset);
            }

        private:
            isenabler_t *isenabler;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> set_enable_bits_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class icenabler_t {
        class clear_enable_bits_t {
        public:
            clear_enable_bits_t(icenabler_t *icenabler, size_t index) : icenabler(icenabler), index(index) {}
            [[nodiscard]] auto get_clear_enable_bits() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->icenabler->value & (mask << offset)) != 0;
            }
            auto set_clear_enable_bits(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->icenabler->value |= mask << offset : this->icenabler->value &= ~(mask << offset);
            }

        private:
            icenabler_t *icenabler;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> clear_enable_bits_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class ispendr_t {
        class set_pending_bits_t {
        public:
            set_pending_bits_t(ispendr_t *ispendr, size_t index) : ispendr(ispendr), index(index) {}
            [[nodiscard]] auto get_set_pending_bits() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->ispendr->value & (mask << offset)) != 0;
            }
            auto set_set_pending_bits(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->ispendr->value |= mask << offset : this->ispendr->value &= ~(mask << offset);
            }

        private:
            ispendr_t *ispendr;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> set_pending_bits_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class icpendr_t {
        class clear_pending_bits_t {
        public:
            clear_pending_bits_t(icpendr_t *icpendr, size_t index) : icpendr(icpendr), index(index) {}
            [[nodiscard]] auto get_clear_pending_bits() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->icpendr->value & (mask << offset)) != 0;
            }
            auto set_clear_pending_bits(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->icpendr->value |= mask << offset : this->icpendr->value &= ~(mask << offset);
            }

        private:
            icpendr_t *icpendr;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> clear_pending_bits_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class isactiver_t {
        class set_active_bits_t {
        public:
            set_active_bits_t(isactiver_t *isactiver, size_t index) : isactiver(isactiver), index(index) {}
            [[nodiscard]] auto get_set_active_bits() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->isactiver->value & (mask << offset)) != 0;
            }
            auto set_set_active_bits(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->isactiver->value |= mask << offset : this->isactiver->value &= ~(mask << offset);
            }

        private:
            isactiver_t *isactiver;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> set_active_bits_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class icactiver_t {
        class clear_active_bits_t {
        public:
            clear_active_bits_t(icactiver_t *icactiver, size_t index) : icactiver(icactiver), index(index) {}
            [[nodiscard]] auto get_clear_active_bits() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->icactiver->value & (mask << offset)) != 0;
            }
            auto set_clear_active_bits(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->icactiver->value |= mask << offset : this->icactiver->value &= ~(mask << offset);
            }

        private:
            icactiver_t *icactiver;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> clear_active_bits_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class ipriorityr_t {
        class priority_offset_bits_t {
        public:
            priority_offset_bits_t(ipriorityr_t *ipriorityr, size_t index) : ipriorityr(ipriorityr), index(index) {}
            [[nodiscard]] auto get_priority_offset_bits() const -> uint8_t {
                const auto offset = 8 * this->index;
                constexpr uint64_t mask = 0b11111111;
                return (this->ipriorityr->value & (mask << offset)) >> offset;
            }
            auto set_priority_offset_bits(uint8_t value) -> void {
                const auto offset = 8 * this->index;
                constexpr uint64_t mask = 0b11111111;
                this->ipriorityr->value = (this->ipriorityr->value & ~(mask << offset)) | ((value & mask) << offset);
            }

        private:
            ipriorityr_t *ipriorityr;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> priority_offset_bits_t {
            return {this, index};
        }
        static constexpr auto length = 4;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class itargetsr_t {
        class cpu_targets_offset_bits_t {
        public:
            cpu_targets_offset_bits_t(itargetsr_t *itargetsr, size_t index) : itargetsr(itargetsr), index(index) {}
            [[nodiscard]] auto get_cpu_targets_offset_bits() const -> uint8_t {
                const auto offset = 8 * this->index;
                constexpr uint64_t mask = 0b11111111;
                return (this->itargetsr->value & (mask << offset)) >> offset;
            }
            auto set_cpu_targets_offset_bits(uint8_t value) -> void {
                const auto offset = 8 * this->index;
                constexpr uint64_t mask = 0b11111111;
                this->itargetsr->value = (this->itargetsr->value & ~(mask << offset)) | ((value & mask) << offset);
            }

        private:
            itargetsr_t *itargetsr;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> cpu_targets_offset_bits_t {
            return {this, index};
        }
        static constexpr auto length = 4;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class icfgr_t {
        class int_config_bits_t {
        public:
            int_config_bits_t(icfgr_t *icfgr, size_t index) : icfgr(icfgr), index(index) {}
            [[nodiscard]] auto get_int_config_bits() const -> uint8_t {
                const auto offset = 2 * this->index;
                constexpr uint64_t mask = 0b11;
                return (this->icfgr->value & (mask << offset)) >> offset;
            }
            auto set_int_config_bits(uint8_t value) -> void {
                const auto offset = 2 * this->index;
                constexpr uint64_t mask = 0b11;
                this->icfgr->value = (this->icfgr->value & ~(mask << offset)) | ((value & mask) << offset);
            }

        private:
            icfgr_t *icfgr;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> int_config_bits_t {
            return {this, index};
        }
        static constexpr auto length = 16;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class igrpmodr_t {
        class group_modifier_bits_t {
        public:
            group_modifier_bits_t(igrpmodr_t *igrpmodr, size_t index) : igrpmodr(igrpmodr), index(index) {}
            [[nodiscard]] auto get_group_modifier_bits() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->igrpmodr->value & (mask << offset)) != 0;
            }
            auto set_group_modifier_bits(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->igrpmodr->value |= mask << offset : this->igrpmodr->value &= ~(mask << offset);
            }

        private:
            igrpmodr_t *igrpmodr;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> group_modifier_bits_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class nsacr_t {
        class ns_access_t {
        public:
            ns_access_t(nsacr_t *nsacr, size_t index) : nsacr(nsacr), index(index) {}
            [[nodiscard]] auto get_ns_access() const -> uint8_t {
                const auto offset = 2 * this->index;
                constexpr uint64_t mask = 0b11;
                return (this->nsacr->value & (mask << offset)) >> offset;
            }
            auto set_ns_access(uint8_t value) -> void {
                const auto offset = 2 * this->index;
                constexpr uint64_t mask = 0b11;
                this->nsacr->value = (this->nsacr->value & ~(mask << offset)) | ((value & mask) << offset);
            }

        private:
            nsacr_t *nsacr;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> ns_access_t {
            return {this, index};
        }
        static constexpr auto length = 16;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class sgir_t {
    public:
        [[nodiscard]] auto get_intid_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_intid_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_nsatt_bit() const -> bool {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_nsatt_bit(bool value) -> void {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_cputargetlist_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_cputargetlist_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_targetlistfilter_bits() const -> uint8_t {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_targetlistfilter_bits(uint8_t value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class cpendsgir_t {
        class sgi_clear_pending_bits_t {
        public:
            sgi_clear_pending_bits_t(cpendsgir_t *cpendsgir, size_t index) : cpendsgir(cpendsgir), index(index) {}
            [[nodiscard]] auto get_sgi_clear_pending_bits() const -> uint8_t {
                const auto offset = 8 * this->index;
                constexpr uint64_t mask = 0b11111111;
                return (this->cpendsgir->value & (mask << offset)) >> offset;
            }
            auto set_sgi_clear_pending_bits(uint8_t value) -> void {
                const auto offset = 8 * this->index;
                constexpr uint64_t mask = 0b11111111;
                this->cpendsgir->value = (this->cpendsgir->value & ~(mask << offset)) | ((value & mask) << offset);
            }

        private:
            cpendsgir_t *cpendsgir;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> sgi_clear_pending_bits_t {
            return {this, index};
        }
        static constexpr auto length = 4;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class spendsgir_t {
        class sgi_set_pending_bits_t {
        public:
            sgi_set_pending_bits_t(spendsgir_t *spendsgir, size_t index) : spendsgir(spendsgir), index(index) {}
            [[nodiscard]] auto get_sgi_set_pending_bits() const -> uint8_t {
                const auto offset = 8 * this->index;
                constexpr uint64_t mask = 0b11111111;
                return (this->spendsgir->value & (mask << offset)) >> offset;
            }
            auto set_sgi_set_pending_bits(uint8_t value) -> void {
                const auto offset = 8 * this->index;
                constexpr uint64_t mask = 0b11111111;
                this->spendsgir->value = (this->spendsgir->value & ~(mask << offset)) | ((value & mask) << offset);
            }

        private:
            spendsgir_t *spendsgir;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> sgi_set_pending_bits_t {
            return {this, index};
        }
        static constexpr auto length = 4;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    static constexpr auto igroupr_length = 32;
    static constexpr auto isenabler_length = 32;
    static constexpr auto icenabler_length = 32;
    static constexpr auto ispendr_length = 32;
    static constexpr auto icpendr_length = 32;
    static constexpr auto isactiver_length = 32;
    static constexpr auto icactiver_length = 32;
    static constexpr auto ipriorityr_length = 256;
    static constexpr auto itargetsr_length = 256;
    static constexpr auto icfgr_length = 64;
    static constexpr auto igrpmodr_length = 64;
    static constexpr auto nsacr_length = 64;
    static constexpr auto cpendsgir_length = 4;
    static constexpr auto spendsgir_length = 4;
    static constexpr auto rsv_0_length = 44;
    static constexpr auto rsv_1_length = 4;
    static constexpr auto rsv_2_length = 4;
    static constexpr auto rsv_3_length = 4;
    static constexpr auto rsv_4_length = 36;
    static constexpr auto rsv_5_length = 12;

    ctlr_t ctlr;
    typer_t typer;
    iidr_t iidr;
    typer2_t typer2;
    statusr_t statusr;
    packed_array_t<packed_byte_t, rsv_0_length> _rsv_0_;
    setspi_nsr_t setspi_nsr;
    packed_array_t<packed_byte_t, rsv_1_length> _rsv_1_;
    clrspi_nsr_t clrspi_nsr;
    packed_array_t<packed_byte_t, rsv_2_length> _rsv_2_;
    setspi_sr_t setspi_sr;
    packed_array_t<packed_byte_t, rsv_3_length> _rsv_3_;
    clrspi_sr_t clrspi_sr;
    packed_array_t<packed_byte_t, rsv_4_length> _rsv_4_;
    packed_array_t<igroupr_t, igroupr_length> igroupr;
    packed_array_t<isenabler_t, isenabler_length> isenabler;
    packed_array_t<icenabler_t, icenabler_length> icenabler;
    packed_array_t<ispendr_t, ispendr_length> ispendr;
    packed_array_t<icpendr_t, icpendr_length> icpendr;
    packed_array_t<isactiver_t, isactiver_length> isactiver;
    packed_array_t<icactiver_t, icactiver_length> icactiver;
    packed_array_t<ipriorityr_t, ipriorityr_length> ipriorityr;
    packed_array_t<itargetsr_t, itargetsr_length> itargetsr;
    packed_array_t<icfgr_t, icfgr_length> icfgr;
    packed_array_t<igrpmodr_t, igrpmodr_length> igrpmodr;
    packed_array_t<nsacr_t, nsacr_length> nsacr;
    sgir_t sgir;
    packed_array_t<packed_byte_t, rsv_5_length> _rsv_5_;
    packed_array_t<cpendsgir_t, cpendsgir_length> cpendsgir;
    packed_array_t<spendsgir_t, spendsgir_length> spendsgir;

} __attribute__((packed));

// NOLINTBEGIN
static_assert(offsetof(gicv3_distributor_registers_t, ctlr) == 0x0);
static_assert(offsetof(gicv3_distributor_registers_t, typer) == 0x4);
static_assert(offsetof(gicv3_distributor_registers_t, igroupr) == 0x80);
static_assert(offsetof(gicv3_distributor_registers_t, isenabler) == 0x100);
static_assert(offsetof(gicv3_distributor_registers_t, icpendr) == 0x280);
static_assert(offsetof(gicv3_distributor_registers_t, ipriorityr) == 0x400);
static_assert(offsetof(gicv3_distributor_registers_t, itargetsr) == 0x800);
static_assert(offsetof(gicv3_distributor_registers_t, icfgr) == 0xc00);
static_assert(offsetof(gicv3_distributor_registers_t, igrpmodr) == 0xd00);
static_assert(offsetof(gicv3_distributor_registers_t, nsacr) == 0xe00);
static_assert(offsetof(gicv3_distributor_registers_t, sgir) == 0xf00);
static_assert(offsetof(gicv3_distributor_registers_t, cpendsgir) == 0xf10);
static_assert(offsetof(gicv3_distributor_registers_t, spendsgir) == 0xf20);
// NOLINTEND

struct gicv3_redistributor_registers_t {
    class ctlr_t {
    public:
        [[nodiscard]] auto get_enablelpis_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_enablelpis_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ces_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ces_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ir_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ir_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rwp_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rwp_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dpg0_bit() const -> bool {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dpg0_bit(bool value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dpg1ns_bit() const -> bool {
            constexpr auto offset = 25;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dpg1ns_bit(bool value) -> void {
            constexpr auto offset = 25;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dpg1s_bit() const -> bool {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dpg1s_bit(bool value) -> void {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_uwp_bit() const -> bool {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_uwp_bit(bool value) -> void {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class iidr_t {
    public:
        [[nodiscard]] auto get_implementer_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_implementer_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_revision_bits() const -> uint8_t {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_revision_bits(uint8_t value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_variant_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_variant_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_productid_bits() const -> uint8_t {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_productid_bits(uint8_t value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class typer_t {
    public:
        [[nodiscard]] auto get_plpis_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_plpis_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_vlpis_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_vlpis_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dirty_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dirty_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_directlpi_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_directlpi_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_last_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_last_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dpgs_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dpgs_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_mpam_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_mpam_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rvpeid_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rvpeid_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_processor_number_bits() const -> uint16_t {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_processor_number_bits(uint16_t value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_commonlpiaff_bits() const -> uint8_t {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_commonlpiaff_bits(uint8_t value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_vsgi_bit() const -> bool {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_vsgi_bit(bool value) -> void {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ppinum_bits() const -> uint8_t {
            constexpr auto offset = 27;
            constexpr uint64_t mask = 0b11111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_ppinum_bits(uint8_t value) -> void {
            constexpr auto offset = 27;
            constexpr uint64_t mask = 0b11111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_aff0_bits() const -> uint8_t {
            constexpr auto offset = 32;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_aff0_bits(uint8_t value) -> void {
            constexpr auto offset = 32;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_aff1_bits() const -> uint8_t {
            constexpr auto offset = 40;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_aff1_bits(uint8_t value) -> void {
            constexpr auto offset = 40;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_aff2_bits() const -> uint8_t {
            constexpr auto offset = 48;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_aff2_bits(uint8_t value) -> void {
            constexpr auto offset = 48;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_aff3_bits() const -> uint8_t {
            constexpr auto offset = 56;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_aff3_bits(uint8_t value) -> void {
            constexpr auto offset = 56;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint64_t value;
    } __attribute__((packed));

    class statusr_t {
    public:
        [[nodiscard]] auto get_rrd_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rrd_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_wrd_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_wrd_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rwod_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rwod_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_wrod_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_wrod_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class waker_t {
    public:
        [[nodiscard]] auto get_processorsleep_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_processorsleep_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_childrenasleep_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_childrenasleep_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class mpamidr_t {
    public:
        [[nodiscard]] auto get_partidmax_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_partidmax_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_pmgmax_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_pmgmax_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class partidr_t {
    public:
        [[nodiscard]] auto get_partid_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_partid_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_pmg_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_pmg_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class setlpir_t {
    public:
        [[nodiscard]] auto get_pintid_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_pintid_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint64_t value;
    } __attribute__((packed));

    class clrlpir_t {
    public:
        [[nodiscard]] auto get_pintid_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_pintid_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint64_t value;
    } __attribute__((packed));

    class propbaser_t {
    public:
        [[nodiscard]] auto get_idbits_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_idbits_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_innercache_bits() const -> uint8_t {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_innercache_bits(uint8_t value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_shareability_bits() const -> uint8_t {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_shareability_bits(uint8_t value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_physical_address_bits() const -> uint64_t {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1111111111111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_physical_address_bits(uint64_t value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1111111111111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_outercache_bits() const -> uint8_t {
            constexpr auto offset = 56;
            constexpr uint64_t mask = 0b111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_outercache_bits(uint8_t value) -> void {
            constexpr auto offset = 56;
            constexpr uint64_t mask = 0b111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint64_t value;
    } __attribute__((packed));

    class pendbaser_t {
    public:
        [[nodiscard]] auto get_innercache_bits() const -> uint8_t {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_innercache_bits(uint8_t value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_shareability_bits() const -> uint8_t {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_shareability_bits(uint8_t value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_physical_address_bits() const -> uint64_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b111111111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_physical_address_bits(uint64_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b111111111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_outercache_bits() const -> uint8_t {
            constexpr auto offset = 56;
            constexpr uint64_t mask = 0b111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_outercache_bits(uint8_t value) -> void {
            constexpr auto offset = 56;
            constexpr uint64_t mask = 0b111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_ptz_bit() const -> bool {
            constexpr auto offset = 62;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ptz_bit(bool value) -> void {
            constexpr auto offset = 62;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint64_t value;
    } __attribute__((packed));

    class invlpir_t {
    public:
        [[nodiscard]] auto get_intid_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_intid_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_vpeid_bits() const -> uint16_t {
            constexpr auto offset = 32;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_vpeid_bits(uint16_t value) -> void {
            constexpr auto offset = 32;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_v_bit() const -> bool {
            constexpr auto offset = 63;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_v_bit(bool value) -> void {
            constexpr auto offset = 63;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint64_t value;
    } __attribute__((packed));

    class invallr_t {
    public:
        [[nodiscard]] auto get_vpeid_bits() const -> uint16_t {
            constexpr auto offset = 32;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_vpeid_bits(uint16_t value) -> void {
            constexpr auto offset = 32;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_v_bit() const -> bool {
            constexpr auto offset = 63;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_v_bit(bool value) -> void {
            constexpr auto offset = 63;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint64_t value;
    } __attribute__((packed));

    class syncr_t {
    public:
        [[nodiscard]] auto get_busy_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_busy_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class igroupr0_t {
        class redistributor_group_status_bit_t {
        public:
            redistributor_group_status_bit_t(igroupr0_t *igroupr0, size_t index) : igroupr0(igroupr0), index(index) {}
            [[nodiscard]] auto get_redistributor_group_status_bit() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->igroupr0->value & (mask << offset)) != 0;
            }
            auto set_redistributor_group_status_bit(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->igroupr0->value |= mask << offset : this->igroupr0->value &= ~(mask << offset);
            }

        private:
            igroupr0_t *igroupr0;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> redistributor_group_status_bit_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class isenabler0_t {
        class set_enable_bit_t {
        public:
            set_enable_bit_t(isenabler0_t *isenabler0, size_t index) : isenabler0(isenabler0), index(index) {}
            [[nodiscard]] auto get_set_enable_bit() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->isenabler0->value & (mask << offset)) != 0;
            }
            auto set_set_enable_bit(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->isenabler0->value |= mask << offset : this->isenabler0->value &= ~(mask << offset);
            }

        private:
            isenabler0_t *isenabler0;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> set_enable_bit_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class icenabler0_t {
        class clear_enable_bit_t {
        public:
            clear_enable_bit_t(icenabler0_t *icenabler0, size_t index) : icenabler0(icenabler0), index(index) {}
            [[nodiscard]] auto get_clear_enable_bit() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->icenabler0->value & (mask << offset)) != 0;
            }
            auto set_clear_enable_bit(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->icenabler0->value |= mask << offset : this->icenabler0->value &= ~(mask << offset);
            }

        private:
            icenabler0_t *icenabler0;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> clear_enable_bit_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class ispendr0_t {
        class set_pending_bit_t {
        public:
            set_pending_bit_t(ispendr0_t *ispendr0, size_t index) : ispendr0(ispendr0), index(index) {}
            [[nodiscard]] auto get_set_pending_bit() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->ispendr0->value & (mask << offset)) != 0;
            }
            auto set_set_pending_bit(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->ispendr0->value |= mask << offset : this->ispendr0->value &= ~(mask << offset);
            }

        private:
            ispendr0_t *ispendr0;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> set_pending_bit_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class icpendr0_t {
        class clear_pending_bit_t {
        public:
            clear_pending_bit_t(icpendr0_t *icpendr0, size_t index) : icpendr0(icpendr0), index(index) {}
            [[nodiscard]] auto get_clear_pending_bit() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->icpendr0->value & (mask << offset)) != 0;
            }
            auto set_clear_pending_bit(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->icpendr0->value |= mask << offset : this->icpendr0->value &= ~(mask << offset);
            }

        private:
            icpendr0_t *icpendr0;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> clear_pending_bit_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class isactiver0_t {
        class set_active_bit_t {
        public:
            set_active_bit_t(isactiver0_t *isactiver0, size_t index) : isactiver0(isactiver0), index(index) {}
            [[nodiscard]] auto get_set_active_bit() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->isactiver0->value & (mask << offset)) != 0;
            }
            auto set_set_active_bit(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->isactiver0->value |= mask << offset : this->isactiver0->value &= ~(mask << offset);
            }

        private:
            isactiver0_t *isactiver0;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> set_active_bit_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class icactiver0_t {
        class clear_active_bit_t {
        public:
            clear_active_bit_t(icactiver0_t *icactiver0, size_t index) : icactiver0(icactiver0), index(index) {}
            [[nodiscard]] auto get_clear_active_bit() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->icactiver0->value & (mask << offset)) != 0;
            }
            auto set_clear_active_bit(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->icactiver0->value |= mask << offset : this->icactiver0->value &= ~(mask << offset);
            }

        private:
            icactiver0_t *icactiver0;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> clear_active_bit_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class ipriorityr_t {
        class priority_offset_bits_t {
        public:
            priority_offset_bits_t(ipriorityr_t *ipriorityr, size_t index) : ipriorityr(ipriorityr), index(index) {}
            [[nodiscard]] auto get_priority_offset_bits() const -> uint8_t {
                const auto offset = 8 * this->index;
                constexpr uint64_t mask = 0b11111111;
                return (this->ipriorityr->value & (mask << offset)) >> offset;
            }
            auto set_priority_offset_bits(uint8_t value) -> void {
                const auto offset = 8 * this->index;
                constexpr uint64_t mask = 0b11111111;
                this->ipriorityr->value = (this->ipriorityr->value & ~(mask << offset)) | ((value & mask) << offset);
            }

        private:
            ipriorityr_t *ipriorityr;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> priority_offset_bits_t {
            return {this, index};
        }
        static constexpr auto length = 4;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class icfgr0_t {
        class int_config_bits_t {
        public:
            int_config_bits_t(icfgr0_t *icfgr0, size_t index) : icfgr0(icfgr0), index(index) {}
            [[nodiscard]] auto get_int_config_bits() const -> uint8_t {
                const auto offset = 2 * this->index;
                constexpr uint64_t mask = 0b11;
                return (this->icfgr0->value & (mask << offset)) >> offset;
            }
            auto set_int_config_bits(uint8_t value) -> void {
                const auto offset = 2 * this->index;
                constexpr uint64_t mask = 0b11;
                this->icfgr0->value = (this->icfgr0->value & ~(mask << offset)) | ((value & mask) << offset);
            }

        private:
            icfgr0_t *icfgr0;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> int_config_bits_t {
            return {this, index};
        }
        static constexpr auto length = 16;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class icfgr1_t {
        class int_config_bits_t {
        public:
            int_config_bits_t(icfgr1_t *icfgr1, size_t index) : icfgr1(icfgr1), index(index) {}
            [[nodiscard]] auto get_int_config_bits() const -> uint8_t {
                const auto offset = 2 * this->index;
                constexpr uint64_t mask = 0b11;
                return (this->icfgr1->value & (mask << offset)) >> offset;
            }
            auto set_int_config_bits(uint8_t value) -> void {
                const auto offset = 2 * this->index;
                constexpr uint64_t mask = 0b11;
                this->icfgr1->value = (this->icfgr1->value & ~(mask << offset)) | ((value & mask) << offset);
            }

        private:
            icfgr1_t *icfgr1;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> int_config_bits_t {
            return {this, index};
        }
        static constexpr auto length = 16;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class igrpmodr0_t {
        class group_modifier_bit_t {
        public:
            group_modifier_bit_t(igrpmodr0_t *igrpmodr0, size_t index) : igrpmodr0(igrpmodr0), index(index) {}
            [[nodiscard]] auto get_group_modifier_bit() const -> bool {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                return (this->igrpmodr0->value & (mask << offset)) != 0;
            }
            auto set_group_modifier_bit(bool value) -> void {
                const auto offset = this->index;
                constexpr uint64_t mask = 0b1;
                value ? this->igrpmodr0->value |= mask << offset : this->igrpmodr0->value &= ~(mask << offset);
            }

        private:
            igrpmodr0_t *igrpmodr0;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> group_modifier_bit_t {
            return {this, index};
        }
        static constexpr auto length = 32;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class nsacr_t {
        class ns_access_bits_t {
        public:
            ns_access_bits_t(nsacr_t *nsacr, size_t index) : nsacr(nsacr), index(index) {}
            [[nodiscard]] auto get_ns_access_bits() const -> uint8_t {
                const auto offset = 2 * this->index;
                constexpr uint64_t mask = 0b11;
                return (this->nsacr->value & (mask << offset)) >> offset;
            }
            auto set_ns_access_bits(uint8_t value) -> void {
                const auto offset = 2 * this->index;
                constexpr uint64_t mask = 0b11;
                this->nsacr->value = (this->nsacr->value & ~(mask << offset)) | ((value & mask) << offset);
            }

        private:
            nsacr_t *nsacr;
            size_t index;
        };

    public:
        auto operator[](size_t index) -> ns_access_bits_t {
            return {this, index};
        }
        static constexpr auto length = 16;

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    static constexpr auto ipriorityr_length = 8;
    static constexpr auto rsv_0_length = 32;
    static constexpr auto rsv_1_length = 32;
    static constexpr auto rsv_2_length = 32;
    static constexpr auto rsv_3_length = 8;
    static constexpr auto rsv_4_length = 8;
    static constexpr auto rsv_5_length = 65468;
    static constexpr auto rsv_6_length = 124;
    static constexpr auto rsv_7_length = 124;
    static constexpr auto rsv_8_length = 124;
    static constexpr auto rsv_9_length = 124;
    static constexpr auto rsv_10_length = 124;
    static constexpr auto rsv_11_length = 124;
    static constexpr auto rsv_12_length = 124;
    static constexpr auto rsv_13_length = 2016;
    static constexpr auto rsv_14_length = 248;
    static constexpr auto rsv_15_length = 252;

    ctlr_t ctlr;
    iidr_t iidr;
    typer_t typer;
    statusr_t statusr;
    waker_t waker;
    mpamidr_t mpamidr;
    partidr_t partidr;
    packed_array_t<packed_byte_t, rsv_0_length> _rsv_0_;
    setlpir_t setlpir;
    clrlpir_t clrlpir;
    packed_array_t<packed_byte_t, rsv_1_length> _rsv_1_;
    propbaser_t propbaser;
    pendbaser_t pendbaser;
    packed_array_t<packed_byte_t, rsv_2_length> _rsv_2_;
    invlpir_t invlpir;
    packed_array_t<packed_byte_t, rsv_3_length> _rsv_3_;
    invallr_t invallr;
    packed_array_t<packed_byte_t, rsv_4_length> _rsv_4_;
    syncr_t syncr;
    packed_array_t<packed_byte_t, rsv_5_length> _rsv_5_;
    igroupr0_t igroupr0;
    packed_array_t<packed_byte_t, rsv_6_length> _rsv_6_;
    isenabler0_t isenabler0;
    packed_array_t<packed_byte_t, rsv_7_length> _rsv_7_;
    icenabler0_t icenabler0;
    packed_array_t<packed_byte_t, rsv_8_length> _rsv_8_;
    ispendr0_t ispendr0;
    packed_array_t<packed_byte_t, rsv_9_length> _rsv_9_;
    icpendr0_t icpendr0;
    packed_array_t<packed_byte_t, rsv_10_length> _rsv_10_;
    isactiver0_t isactiver0;
    packed_array_t<packed_byte_t, rsv_11_length> _rsv_11_;
    icactiver0_t icactiver0;
    packed_array_t<packed_byte_t, rsv_12_length> _rsv_12_;
    packed_array_t<ipriorityr_t, ipriorityr_length> ipriorityr;
    packed_array_t<packed_byte_t, rsv_13_length> _rsv_13_;
    icfgr0_t icfgr0;
    icfgr1_t icfgr1;
    packed_array_t<packed_byte_t, rsv_14_length> _rsv_14_;
    igrpmodr0_t igrpmodr0;
    packed_array_t<packed_byte_t, rsv_15_length> _rsv_15_;
    nsacr_t nsacr;
} __attribute__((packed));

// NOLINTBEGIN
static_assert(offsetof(gicv3_redistributor_registers_t, ctlr) == 0x0);
static_assert(offsetof(gicv3_redistributor_registers_t, waker) == 0x14);
static_assert(offsetof(gicv3_redistributor_registers_t, setlpir) == 0x40);
static_assert(offsetof(gicv3_redistributor_registers_t, clrlpir) == 0x48);
static_assert(offsetof(gicv3_redistributor_registers_t, syncr) == 0xc0);
static_assert(offsetof(gicv3_redistributor_registers_t, igroupr0) == 0x10000 + 0x80);
static_assert(offsetof(gicv3_redistributor_registers_t, isenabler0) == 0x10000 + 0x100);
static_assert(offsetof(gicv3_redistributor_registers_t, icpendr0) == 0x10000 + 0x280);
static_assert(offsetof(gicv3_redistributor_registers_t, ipriorityr) == 0x10000 + 0x400);
static_assert(offsetof(gicv3_redistributor_registers_t, igrpmodr0) == 0x10000 + 0xd00);
static_assert(offsetof(gicv3_redistributor_registers_t, nsacr) == 0x10000 + 0xe00);
// NOLINTEND

#endif

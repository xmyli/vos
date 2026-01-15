#ifndef E1000_REGISTERS_HPP
#define E1000_REGISTERS_HPP

#include "../lib/array.hpp"
#include "integer.hpp"

#include <cstdint>

struct e1000_registers_t {
    class ctrl_t {
    public:
        [[nodiscard]] auto get_fd_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_fd_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_lrst_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_lrst_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_asde_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_asde_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_slu_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_slu_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ilos_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ilos_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_speed_bits() const -> uint8_t {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_speed_bits(uint8_t value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_frcspd_bit() const -> bool {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_frcspd_bit(bool value) -> void {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_frcdplx_bit() const -> bool {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_frcdplx_bit(bool value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_sdp0_data_bit() const -> bool {
            constexpr auto offset = 18;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sdp0_data_bit(bool value) -> void {
            constexpr auto offset = 18;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_sdp1_data_bit() const -> bool {
            constexpr auto offset = 19;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sdp1_data_bit(bool value) -> void {
            constexpr auto offset = 19;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_advd3wuc_bit() const -> bool {
            constexpr auto offset = 20;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_advd3wuc_bit(bool value) -> void {
            constexpr auto offset = 20;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_en_phy_pwr_mgmt_bit() const -> bool {
            constexpr auto offset = 21;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_en_phy_pwr_mgmt_bit(bool value) -> void {
            constexpr auto offset = 21;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_sdp0_iodir_bit() const -> bool {
            constexpr auto offset = 22;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sdp0_iodir_bit(bool value) -> void {
            constexpr auto offset = 22;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_sdp1_iodir_bit() const -> bool {
            constexpr auto offset = 23;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sdp1_iodir_bit(bool value) -> void {
            constexpr auto offset = 23;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rst_bit() const -> bool {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rst_bit(bool value) -> void {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rfce_bit() const -> bool {
            constexpr auto offset = 27;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rfce_bit(bool value) -> void {
            constexpr auto offset = 27;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_tfce_bit() const -> bool {
            constexpr auto offset = 28;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_tfce_bit(bool value) -> void {
            constexpr auto offset = 28;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_vme_bit() const -> bool {
            constexpr auto offset = 30;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_vme_bit(bool value) -> void {
            constexpr auto offset = 30;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_phy_rst_bit() const -> bool {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_phy_rst_bit(bool value) -> void {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class status_t {
    public:
        [[nodiscard]] auto get_fd_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_fd_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_lu_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_lu_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_function_id_bits() const -> uint8_t {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_function_id_bits(uint8_t value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_txoff_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txoff_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_tbimode_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_tbimode_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_speed_bits() const -> uint8_t {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_speed_bits(uint8_t value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_asdv_bits() const -> uint8_t {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_asdv_bits(uint8_t value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_pci66_bit() const -> bool {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_pci66_bit(bool value) -> void {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_bus64_bit() const -> bool {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_bus64_bit(bool value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_pcix_mode_bit() const -> bool {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_pcix_mode_bit(bool value) -> void {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_pcixspd_bits() const -> uint8_t {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_pcixspd_bits(uint8_t value) -> void {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class eecd_t {
    public:
        [[nodiscard]] auto get_sk_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sk_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_cs_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_cs_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_di_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_di_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_do_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_do_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_fwe_bits() const -> uint8_t {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_fwe_bits(uint8_t value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_req_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_req_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_gnt_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_gnt_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_pres_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_pres_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_size_bits() const -> uint8_t {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_size_bits(uint8_t value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_type_bit() const -> bool {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_type_bit(bool value) -> void {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class eerd_t {
    public:
        [[nodiscard]] auto get_start_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_start_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_done_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_done_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_addr_bits() const -> uint8_t {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_addr_bits(uint8_t value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_data_bits() const -> uint16_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_data_bits(uint16_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class ctrl_ext_t {
    public:
        [[nodiscard]] auto get_gpi_en_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_gpi_en_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_phyint_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_phyint_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_sdp6_data_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sdp6_data_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_sdp7_data_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sdp7_data_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_sdp6_iodir_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sdp6_iodir_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_sdp7_iodir_bit() const -> bool {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sdp7_iodir_bit(bool value) -> void {
            constexpr auto offset = 11;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_asdchk_bit() const -> bool {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_asdchk_bit(bool value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ee_rst_bit() const -> bool {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ee_rst_bit(bool value) -> void {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_spd_byps_bit() const -> bool {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_spd_byps_bit(bool value) -> void {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ro_dis_bit() const -> bool {
            constexpr auto offset = 17;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ro_dis_bit(bool value) -> void {
            constexpr auto offset = 17;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_link_mode_bits() const -> uint8_t {
            constexpr auto offset = 22;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_link_mode_bits(uint8_t value) -> void {
            constexpr auto offset = 22;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class mdic_t {
    public:
        [[nodiscard]] auto get_data_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_data_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_regadd_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_regadd_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_phyadd_bits() const -> uint8_t {
            constexpr auto offset = 21;
            constexpr uint64_t mask = 0b11111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_phyadd_bits(uint8_t value) -> void {
            constexpr auto offset = 21;
            constexpr uint64_t mask = 0b11111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_op_bits() const -> uint8_t {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_op_bits(uint8_t value) -> void {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_r_bit() const -> bool {
            constexpr auto offset = 28;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_r_bit(bool value) -> void {
            constexpr auto offset = 28;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_i_bit() const -> bool {
            constexpr auto offset = 29;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_i_bit(bool value) -> void {
            constexpr auto offset = 29;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_e_bit() const -> bool {
            constexpr auto offset = 30;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_e_bit(bool value) -> void {
            constexpr auto offset = 30;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class fcal_t {
    public:
        [[nodiscard]] auto get_fcal_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_fcal_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class fcah_t {
    public:
        [[nodiscard]] auto get_fcah_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_fcah_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class fct_t {
    public:
        [[nodiscard]] auto get_fct_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_fct_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class vet_t {
    public:
        [[nodiscard]] auto get_vet_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_vet_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class icr_t {
    public:
        [[nodiscard]] auto get_txdw_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txdw_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txqe_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txqe_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_lsc_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_lsc_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxseq_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxseq_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxdmt0_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxdmt0_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxo_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxo_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxt0_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxt0_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_mdac_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_mdac_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxcfg_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxcfg_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_phyint_bit() const -> bool {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_phyint_bit(bool value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_gpi_sdp6_bit() const -> bool {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_gpi_sdp6_bit(bool value) -> void {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_gpi_sdp7_bit() const -> bool {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_gpi_sdp7_bit(bool value) -> void {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txd_low_bit() const -> bool {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txd_low_bit(bool value) -> void {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_srpd_bit() const -> bool {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_srpd_bit(bool value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class itr_t {
    public:
        [[nodiscard]] auto get_interval_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_interval_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class ics_t {
    public:
        [[nodiscard]] auto get_txdw_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txdw_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txqe_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txqe_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_lsc_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_lsc_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxseq_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxseq_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxdmt0_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxdmt0_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxo_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxo_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxt0_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxt0_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_mdac_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_mdac_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxcfg_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxcfg_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_phyint_bit() const -> bool {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_phyint_bit(bool value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_gpi_bits() const -> uint8_t {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_gpi_bits(uint8_t value) -> void {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_txd_low_bit() const -> bool {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txd_low_bit(bool value) -> void {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_srpd_bit() const -> bool {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_srpd_bit(bool value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class ims_t {
    public:
        [[nodiscard]] auto get_txdw_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txdw_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txqe_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txqe_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_lsc_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_lsc_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxseq_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxseq_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxdmt0_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxdmt0_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxo_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxo_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxt0_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxt0_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_mdac_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_mdac_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxcfg_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxcfg_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_phyint_bit() const -> bool {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_phyint_bit(bool value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_gpi_bits() const -> uint8_t {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_gpi_bits(uint8_t value) -> void {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_txd_low_bit() const -> bool {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txd_low_bit(bool value) -> void {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_srpd_bit() const -> bool {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_srpd_bit(bool value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class imc_t {
    public:
        [[nodiscard]] auto get_txdw_bit() const -> bool {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txdw_bit(bool value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_txqe_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txqe_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_lsc_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_lsc_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxseq_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxseq_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxdmt0_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxdmt0_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxo_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxo_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxt0_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxt0_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_mdac_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_mdac_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxcfg_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxcfg_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_phyint_bit() const -> bool {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_phyint_bit(bool value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_gpi_bits() const -> uint8_t {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_gpi_bits(uint8_t value) -> void {
            constexpr auto offset = 13;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_txd_low_bit() const -> bool {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txd_low_bit(bool value) -> void {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_srpd_bit() const -> bool {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_srpd_bit(bool value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rctl_t {
    public:
        [[nodiscard]] auto get_en_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_en_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_sbp_bit() const -> bool {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_sbp_bit(bool value) -> void {
            constexpr auto offset = 2;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_upe_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_upe_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_mpe_bit() const -> bool {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_mpe_bit(bool value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_lpe_bit() const -> bool {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_lpe_bit(bool value) -> void {
            constexpr auto offset = 5;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_lbm_bits() const -> uint8_t {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_lbm_bits(uint8_t value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_rdmts_bits() const -> uint8_t {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_rdmts_bits(uint8_t value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_mo_bits() const -> uint8_t {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_mo_bits(uint8_t value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_bam_bit() const -> bool {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_bam_bit(bool value) -> void {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_bsize_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_bsize_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_vfe_bit() const -> bool {
            constexpr auto offset = 18;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_vfe_bit(bool value) -> void {
            constexpr auto offset = 18;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_cfien_bit() const -> bool {
            constexpr auto offset = 19;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_cfien_bit(bool value) -> void {
            constexpr auto offset = 19;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_cfi_bit() const -> bool {
            constexpr auto offset = 20;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_cfi_bit(bool value) -> void {
            constexpr auto offset = 20;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_dpf_bit() const -> bool {
            constexpr auto offset = 22;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_dpf_bit(bool value) -> void {
            constexpr auto offset = 22;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_pmcf_bit() const -> bool {
            constexpr auto offset = 23;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_pmcf_bit(bool value) -> void {
            constexpr auto offset = 23;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_bsex_bit() const -> bool {
            constexpr auto offset = 25;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_bsex_bit(bool value) -> void {
            constexpr auto offset = 25;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_secrc_bit() const -> bool {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_secrc_bit(bool value) -> void {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class fcttv_t {
    public:
        [[nodiscard]] auto get_ttv_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_ttv_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class txcw_t {
    public:
        [[nodiscard]] auto get_txconfigword_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_txconfigword_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_txconfig_bit() const -> bool {
            constexpr auto offset = 30;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_txconfig_bit(bool value) -> void {
            constexpr auto offset = 30;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ane_bit() const -> bool {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ane_bit(bool value) -> void {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rxcw_t {
    public:
        [[nodiscard]] auto get_rxconfigword_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_rxconfigword_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_rxconfignocarrier_bit() const -> bool {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxconfignocarrier_bit(bool value) -> void {
            constexpr auto offset = 26;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxconfiginvalid_bit() const -> bool {
            constexpr auto offset = 27;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxconfiginvalid_bit(bool value) -> void {
            constexpr auto offset = 27;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxconfigchange_bit() const -> bool {
            constexpr auto offset = 28;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxconfigchange_bit(bool value) -> void {
            constexpr auto offset = 28;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxconfig_bit() const -> bool {
            constexpr auto offset = 29;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxconfig_bit(bool value) -> void {
            constexpr auto offset = 29;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rxsynchronize_bit() const -> bool {
            constexpr auto offset = 30;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rxsynchronize_bit(bool value) -> void {
            constexpr auto offset = 30;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_anc_bit() const -> bool {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_anc_bit(bool value) -> void {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class tctl_t {
    public:
        [[nodiscard]] auto get_en_bit() const -> bool {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_en_bit(bool value) -> void {
            constexpr auto offset = 1;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_psp_bit() const -> bool {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_psp_bit(bool value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ct_bits() const -> uint8_t {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_ct_bits(uint8_t value) -> void {
            constexpr auto offset = 4;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_cold_bits() const -> uint16_t {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_cold_bits(uint16_t value) -> void {
            constexpr auto offset = 12;
            constexpr uint64_t mask = 0b1111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_swxoff_bit() const -> bool {
            constexpr auto offset = 22;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_swxoff_bit(bool value) -> void {
            constexpr auto offset = 22;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_rtlc_bit() const -> bool {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_rtlc_bit(bool value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class tipg_t {
    public:
        [[nodiscard]] auto get_ipgt_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_ipgt_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_ipgr1_bits() const -> uint16_t {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_ipgr1_bits(uint16_t value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_ipgr2_bits() const -> uint16_t {
            constexpr auto offset = 20;
            constexpr uint64_t mask = 0b1111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_ipgr2_bits(uint16_t value) -> void {
            constexpr auto offset = 20;
            constexpr uint64_t mask = 0b1111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class aifs_t {
    public:
        [[nodiscard]] auto get_aifs_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_aifs_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class ledctl_t {
    public:
        [[nodiscard]] auto get_led0_mode_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_led0_mode_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_led0_ivrt_bit() const -> bool {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_led0_ivrt_bit(bool value) -> void {
            constexpr auto offset = 6;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_led0_blink_bit() const -> bool {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_led0_blink_bit(bool value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_led1_mode_bits() const -> uint8_t {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_led1_mode_bits(uint8_t value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_led1_ivrt_bit() const -> bool {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_led1_ivrt_bit(bool value) -> void {
            constexpr auto offset = 14;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_led1_blink_bit() const -> bool {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_led1_blink_bit(bool value) -> void {
            constexpr auto offset = 15;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_led2_mode_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_led2_mode_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_led2_ivrt_bit() const -> bool {
            constexpr auto offset = 22;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_led2_ivrt_bit(bool value) -> void {
            constexpr auto offset = 22;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_led2_blink_bit() const -> bool {
            constexpr auto offset = 23;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_led2_blink_bit(bool value) -> void {
            constexpr auto offset = 23;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_led3_mode_bits() const -> uint8_t {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_led3_mode_bits(uint8_t value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_led3_ivrt_bit() const -> bool {
            constexpr auto offset = 30;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_led3_ivrt_bit(bool value) -> void {
            constexpr auto offset = 30;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_led3_blink_bit() const -> bool {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_led3_blink_bit(bool value) -> void {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class fcrtl_t {
    public:
        [[nodiscard]] auto get_rtl_bits() const -> uint16_t {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_rtl_bits(uint16_t value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class fcrth_t {
    public:
        [[nodiscard]] auto get_rth_bits() const -> uint16_t {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_rth_bits(uint16_t value) -> void {
            constexpr auto offset = 3;
            constexpr uint64_t mask = 0b1111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rdbal_t {
    public:
        [[nodiscard]] auto get_rdbal_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_rdbal_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rdbah_t {
    public:
        [[nodiscard]] auto get_rdbah_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_rdbah_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rdlen_t {
    public:
        [[nodiscard]] auto get_len_bits() const -> uint16_t {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_len_bits(uint16_t value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rdh_t {
    public:
        [[nodiscard]] auto get_rdh_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_rdh_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rdt_t {
    public:
        [[nodiscard]] auto get_rdt_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_rdt_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rdtr_t {
    public:
        [[nodiscard]] auto get_delay_timer_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_delay_timer_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_fpd_bit() const -> bool {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_fpd_bit(bool value) -> void {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rxdctl_t {
    public:
        [[nodiscard]] auto get_pthresh_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_pthresh_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_hthresh_bits() const -> uint8_t {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_hthresh_bits(uint8_t value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_wthresh_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_wthresh_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_gran_bit() const -> bool {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_gran_bit(bool value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class radv_t {
    public:
        [[nodiscard]] auto get_delay_timer_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_delay_timer_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rsrpd_t {
    public:
        [[nodiscard]] auto get_size_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_size_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class tdbal_t {
    public:
        [[nodiscard]] auto get_tdbal_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_tdbal_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class tdbah_t {
    public:
        [[nodiscard]] auto get_tdbah_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_tdbah_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class tdlen_t {
    public:
        [[nodiscard]] auto get_len_bits() const -> uint16_t {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_len_bits(uint16_t value) -> void {
            constexpr auto offset = 7;
            constexpr uint64_t mask = 0b1111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class tdh_t {
    public:
        [[nodiscard]] auto get_tdh_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_tdh_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class tdt_t {
    public:
        [[nodiscard]] auto get_tdt_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_tdt_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class tidv_t {
    public:
        [[nodiscard]] auto get_idv_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_idv_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class txdctl_t {
    public:
        [[nodiscard]] auto get_pthresh_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_pthresh_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_hthresh_bits() const -> uint8_t {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_hthresh_bits(uint8_t value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_wthresh_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_wthresh_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_gran_bit() const -> bool {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_gran_bit(bool value) -> void {
            constexpr auto offset = 24;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_lwthresh_bits() const -> uint8_t {
            constexpr auto offset = 25;
            constexpr uint64_t mask = 0b1111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_lwthresh_bits(uint8_t value) -> void {
            constexpr auto offset = 25;
            constexpr uint64_t mask = 0b1111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class tadv_t {
    public:
        [[nodiscard]] auto get_idv_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_idv_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class tspmt_t {
    public:
        [[nodiscard]] auto get_tsmt_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_tsmt_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_tspbp_bits() const -> uint16_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_tspbp_bits(uint16_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rxcsum_t {
    public:
        [[nodiscard]] auto get_pcss_bits() const -> uint8_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_pcss_bits(uint8_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_ipofld_bit() const -> bool {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ipofld_bit(bool value) -> void {
            constexpr auto offset = 8;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_tuofld_bit() const -> bool {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_tuofld_bit(bool value) -> void {
            constexpr auto offset = 9;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }
        [[nodiscard]] auto get_ipv6ofl_bit() const -> bool {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_ipv6ofl_bit(bool value) -> void {
            constexpr auto offset = 10;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class mta_t {
    public:
        [[nodiscard]] auto get_mc_bit_vector_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_mc_bit_vector_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class ral_t {
    public:
        [[nodiscard]] auto get_ral_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_ral_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class rah_t {
    public:
        [[nodiscard]] auto get_rah_bits() const -> uint16_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_rah_bits(uint16_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b1111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_as_bits() const -> uint8_t {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_as_bits(uint8_t value) -> void {
            constexpr auto offset = 16;
            constexpr uint64_t mask = 0b11;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }
        [[nodiscard]] auto get_av_bit() const -> bool {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            return (this->value & (mask << offset)) != 0;
        }
        auto set_av_bit(bool value) -> void {
            constexpr auto offset = 31;
            constexpr uint64_t mask = 0b1;
            value ? this->value |= mask << offset : this->value &= ~(mask << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    class vfta_t {
    public:
        [[nodiscard]] auto get_bit_vector_bits() const -> uint32_t {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            return (this->value & (mask << offset)) >> offset;
        }
        auto set_bit_vector_bits(uint32_t value) -> void {
            constexpr auto offset = 0;
            constexpr uint64_t mask = 0b11111111111111111111111111111111;
            this->value = (this->value & ~(mask << offset)) | ((value & mask) << offset);
        }

    private:
        volatile uint32_t value;
    } __attribute__((packed));

    static constexpr auto mta_length = 128;
    static constexpr auto vfta_length = 128;
    static constexpr auto rsv_0_length = 4;
    static constexpr auto rsv_1_length = 4;
    static constexpr auto rsv_2_length = 4;
    static constexpr auto rsv_3_length = 4;
    static constexpr auto rsv_4_length = 4;
    static constexpr auto rsv_5_length = 132;
    static constexpr auto rsv_6_length = 4;
    static constexpr auto rsv_7_length = 4;
    static constexpr auto rsv_8_length = 36;
    static constexpr auto rsv_9_length = 108;
    static constexpr auto rsv_10_length = 4;
    static constexpr auto rsv_11_length = 4;
    static constexpr auto rsv_12_length = 636;
    static constexpr auto rsv_13_length = 12;
    static constexpr auto rsv_14_length = 68;
    static constexpr auto rsv_15_length = 2468;
    static constexpr auto rsv_16_length = 4956;
    static constexpr auto rsv_17_length = 4;
    static constexpr auto rsv_18_length = 1684;
    static constexpr auto rsv_19_length = 4;
    static constexpr auto rsv_20_length = 4;
    static constexpr auto rsv_21_length = 4;
    static constexpr auto rsv_22_length = 4;
    static constexpr auto rsv_23_length = 976;
    static constexpr auto rsv_24_length = 3068;
    static constexpr auto rsv_25_length = 4;
    static constexpr auto rsv_26_length = 4;
    static constexpr auto rsv_27_length = 4;
    static constexpr auto rsv_28_length = 4;
    static constexpr auto rsv_29_length = 6092;
    static constexpr auto rsv_30_length = 508;
    static constexpr auto rsv_31_length = 504;

    ctrl_t ctrl;
    packed_array_t<packed_byte_t, rsv_0_length> _rsv_0_;
    status_t status;
    packed_array_t<packed_byte_t, rsv_1_length> _rsv_1_;
    eecd_t eecd;
    eerd_t eerd;
    ctrl_ext_t ctrl_ext;
    packed_array_t<packed_byte_t, rsv_2_length> _rsv_2_;
    mdic_t mdic;
    packed_array_t<packed_byte_t, rsv_3_length> _rsv_3_;
    fcal_t fcal;
    fcah_t fcah;
    fct_t fct;
    packed_array_t<packed_byte_t, rsv_4_length> _rsv_4_;
    vet_t vet;
    packed_array_t<packed_byte_t, rsv_5_length> _rsv_5_;
    icr_t icr;
    itr_t itr;
    ics_t ics;
    packed_array_t<packed_byte_t, rsv_6_length> _rsv_6_;
    ims_t ims;
    packed_array_t<packed_byte_t, rsv_7_length> _rsv_7_;
    imc_t imc;
    packed_array_t<packed_byte_t, rsv_8_length> _rsv_8_;
    rctl_t rctl;
    packed_array_t<packed_byte_t, rsv_9_length> _rsv_9_;
    fcttv_t fcttv;
    packed_array_t<packed_byte_t, rsv_10_length> _rsv_10_;
    txcw_t txcw;
    packed_array_t<packed_byte_t, rsv_11_length> _rsv_11_;
    rxcw_t rxcw;
    packed_array_t<packed_byte_t, rsv_12_length> _rsv_12_;
    tctl_t tctl;
    packed_array_t<packed_byte_t, rsv_13_length> _rsv_13_;
    tipg_t tipg;
    packed_array_t<packed_byte_t, rsv_14_length> _rsv_14_;
    aifs_t aifs;
    packed_array_t<packed_byte_t, rsv_15_length> _rsv_15_;
    ledctl_t ledctl;
    packed_array_t<packed_byte_t, rsv_16_length> _rsv_16_;
    fcrtl_t fcrtl;
    packed_array_t<packed_byte_t, rsv_17_length> _rsv_17_;
    fcrth_t fcrth;
    packed_array_t<packed_byte_t, rsv_18_length> _rsv_18_;
    rdbal_t rdbal;
    rdbah_t rdbah;
    rdlen_t rdlen;
    packed_array_t<packed_byte_t, rsv_19_length> _rsv_19_;
    rdh_t rdh;
    packed_array_t<packed_byte_t, rsv_20_length> _rsv_20_;
    rdt_t rdt;
    packed_array_t<packed_byte_t, rsv_21_length> _rsv_21_;
    rdtr_t rdtr;
    packed_array_t<packed_byte_t, rsv_22_length> _rsv_22_;
    rxdctl_t rxdctl;
    radv_t radv;
    packed_array_t<packed_byte_t, rsv_23_length> _rsv_23_;
    rsrpd_t rsrpd;
    packed_array_t<packed_byte_t, rsv_24_length> _rsv_24_;
    tdbal_t tdbal;
    tdbah_t tdbah;
    tdlen_t tdlen;
    packed_array_t<packed_byte_t, rsv_25_length> _rsv_25_;
    tdh_t tdh;
    packed_array_t<packed_byte_t, rsv_26_length> _rsv_26_;
    tdt_t tdt;
    packed_array_t<packed_byte_t, rsv_27_length> _rsv_27_;
    tidv_t tidv;
    packed_array_t<packed_byte_t, rsv_28_length> _rsv_28_;
    txdctl_t txdctl;
    tadv_t tadv;
    tspmt_t tspmt;
    packed_array_t<packed_byte_t, rsv_29_length> _rsv_29_;
    rxcsum_t rxcsum;
    packed_array_t<packed_byte_t, rsv_30_length> _rsv_30_;
    packed_array_t<mta_t, mta_length> mta;
    ral_t ral;
    rah_t rah;
    packed_array_t<packed_byte_t, rsv_31_length> _rsv_31_;
    packed_array_t<vfta_t, vfta_length> vfta;
} __attribute__((packed));

// NOLINTBEGIN
static_assert(offsetof(e1000_registers_t, ctrl) == 0x000);
static_assert(offsetof(e1000_registers_t, icr) == 0x0c0);
static_assert(offsetof(e1000_registers_t, ims) == 0x0d0);
static_assert(offsetof(e1000_registers_t, rctl) == 0x100);
static_assert(offsetof(e1000_registers_t, tctl) == 0x400);
static_assert(offsetof(e1000_registers_t, tipg) == 0x410);
static_assert(offsetof(e1000_registers_t, rdbal) == 0x2800);
static_assert(offsetof(e1000_registers_t, rdlen) == 0x2808);
static_assert(offsetof(e1000_registers_t, rdh) == 0x2810);
static_assert(offsetof(e1000_registers_t, rdt) == 0x2818);
static_assert(offsetof(e1000_registers_t, tdbal) == 0x3800);
static_assert(offsetof(e1000_registers_t, tdlen) == 0x3808);
static_assert(offsetof(e1000_registers_t, tdh) == 0x3810);
static_assert(offsetof(e1000_registers_t, tdt) == 0x3818);
static_assert(offsetof(e1000_registers_t, mta) == 0x5200);
static_assert(offsetof(e1000_registers_t, ral) == 0x5400);
static_assert(offsetof(e1000_registers_t, rah) == 0x5404);
// NOLINTEND

#endif

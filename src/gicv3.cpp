#include "../include/gicv3.hpp"
#include "../include/architecture.hpp"
#include "../include/device.hpp"
#include "../include/multiprocessing.hpp"
#include "../include/reinterpretable.hpp"

namespace device {

void set_up_distributor() {
    auto itlinesnumber = reinterpretable_t<>().gicv3_distributor_registers->typer.get_itlinesnumber_bits();
    for (int i = 0; i < itlinesnumber; i++) {
        for (int j = 0; j < gicv3_distributor_registers_t::igroupr_t::length; j++) {
            reinterpretable_t<>().gicv3_distributor_registers->igroupr[i][j].set_group_status_bits(true);
        }
    }
}

void set_up_redistributor() {
    gicv3_system_registers_t::set_icc_sre_el1_bits((gicv3_system_registers_t::get_icc_sre_el1_bits() | 1));
    for (int i = 0; i < gicv3_redistributor_registers_t::igroupr0_t::length; i++) {
        reinterpretable_t<>().gicv3_redistributor_registers->igroupr0[i].set_redistributor_group_status_bit(true);
    }
    for (int i = 0; i < gicv3_redistributor_registers_t::igrpmodr0_t::length; i++) {
        reinterpretable_t<>().gicv3_redistributor_registers->igrpmodr0[i].set_group_modifier_bit(true);
    }
    reinterpretable_t<>().gicv3_redistributor_registers->waker.set_processorsleep_bit(false);
    while (reinterpretable_t<>().gicv3_redistributor_registers->waker.get_childrenasleep_bit()) {
        ;
    }
}

void set_up_cpu_interface() {
    gicv3_system_registers_t::set_icc_pmr_el1_bits(~0);
    gicv3_system_registers_t::set_icc_igrpen1_el1_bits(0);
}

void set_up_shared_peripheral_interrupt(uint16_t interrupt_number) {
    reinterpretable_t<>()
        .gicv3_distributor_registers
        ->itargetsr[interrupt_number / gicv3_distributor_registers_t::itargetsr_t::length]
                   [interrupt_number % gicv3_distributor_registers_t::itargetsr_t::length]
        .set_cpu_targets_offset_bits(1);
    reinterpretable_t<>()
        .gicv3_distributor_registers
        ->ipriorityr[interrupt_number / gicv3_distributor_registers_t::ipriorityr_t::length]
                    [interrupt_number % gicv3_distributor_registers_t::ipriorityr_t::length]
        .set_priority_offset_bits(0);
    reinterpretable_t<>()
        .gicv3_distributor_registers
        ->icpendr[interrupt_number / gicv3_distributor_registers_t::icpendr_t::length]
                 [interrupt_number % gicv3_distributor_registers_t::icpendr_t::length]
        .set_clear_pending_bits(true);
    reinterpretable_t<>()
        .gicv3_distributor_registers
        ->isenabler[interrupt_number / gicv3_distributor_registers_t::isenabler_t::length]
                   [interrupt_number % gicv3_distributor_registers_t::isenabler_t::length]
        .set_set_enable_bits(true);
}

void set_up_private_peripheral_interrupt(uint16_t interrupt_number) {
    reinterpretable_t<>()
        .gicv3_redistributor_registers
        ->ipriorityr[interrupt_number / gicv3_redistributor_registers_t::ipriorityr_t::length]
                    [interrupt_number % gicv3_redistributor_registers_t::ipriorityr_t::length]
        .set_priority_offset_bits(0);
    reinterpretable_t<>()
        .gicv3_redistributor_registers->icpendr0[interrupt_number % gicv3_redistributor_registers_t::icpendr0_t::length]
        .set_clear_pending_bit(true);
    reinterpretable_t<>()
        .gicv3_redistributor_registers
        ->isenabler0[interrupt_number % gicv3_redistributor_registers_t::isenabler0_t::length]
        .set_set_enable_bit(true);
}

void enable_interrupt_controller() {
    reinterpretable_t<>().gicv3_distributor_registers->ctlr.set_enablegrp1ns_bit(true);
    gicv3_system_registers_t::set_icc_igrpen1_el1_bits(1);
}

auto gicv3::initialize() -> void {
    if (architecture::get_core_number() == 0) {
        set_up_distributor();
        set_up_shared_peripheral_interrupt(gicv3_pl011_intid);
        set_up_shared_peripheral_interrupt(gicv3_pcie_intid);
        set_up_shared_peripheral_interrupt(gicv3_virtio_intid);
    }
    set_up_redistributor();
    set_up_cpu_interface();
    set_up_private_peripheral_interrupt(gicv3_timer_intid);
    enable_interrupt_controller();
}

auto gicv3::get_interrupt_number() -> uint64_t {
    return gicv3_system_registers_t::get_icc_iar1_el1_bits();
}

void gicv3::set_interrupt_number(uint64_t interrupt_number) {
    gicv3_system_registers_t::set_icc_eoir1_el1_bits(interrupt_number);
}

} // namespace device

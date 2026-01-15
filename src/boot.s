.section ".text"

.global _start
_start:
        mrs x1, mpidr_el1
        and x1, x1, #0x3
        cbz x1, primary
        b secondary

primary:
        adrp x1, _bss_begin_
        ldr w2, =_bss_size_

1:
        cbz w2, 2f
        str xzr, [x1], #0x8
        sub w2, w2, #0x1
        b 1b

        .macro create_linear_mapping, level_0_page_table, level_1_page_table, level_2_page_table, offset
        adrp x0, \level_2_page_table
        mov x1, #0x40000000
        ldr x2, =(_kernel_end_-0xffff000000000000)-0x1
        mov x3, \offset
        add x4, x1, x3
        add x5, x2, x3
        lsr x6, x4, #0x15
        and x6, x6, #0x1ff
        lsr x7, x5, #0x15
        and x7, x7, #0x1ff
        mov x8, #0x405
        orr x9, x1, x8
999:
        str x9, [x0, x6, lsl #0x3]
        add x6, x6, #0x1
        add x9, x9, #0x200000
        cmp x6, x7
        b.ls 999b
        adrp x0, \level_1_page_table
        lsr x5, x4, #0x1e
        and x5, x5, #0x1ff
        mov x6, #0x3
        adrp x7, \level_2_page_table
        orr x8, x6, x7
        str x8, [x0, x5, lsl #0x3]
        adrp x0, \level_0_page_table
        lsr x5, x4, #0x27
        and x5, x5, #0x1ff
        mov x6, #0x3
        adrp x7, \level_1_page_table
        orr x8, x6, x7
        str x8, [x0, x5, lsl #0x3]
        .endm

2:
        create_linear_mapping _identity_level_0_page_table_, _identity_level_1_page_table_, _identity_level_2_page_table_, 0x0
        create_linear_mapping _linear_level_0_page_table_, _linear_level_1_page_table_, _linear_level_2_page_table_, #0xffff000000000000

secondary:
        adrp x0, _identity_level_0_page_table_
        adrp x1, _linear_level_0_page_table_
        msr ttbr0_el1, x0
        msr ttbr1_el1, x1
        ldr x0, =0x5b5103510
        msr tcr_el1, x0
        ldr x1, =0x4400
        msr mair_el1, x1
        isb
        ldr x1, =_setup
        mrs x0, sctlr_el1
        orr x0, x0, #0x1
        msr sctlr_el1, x0
        br x1

_setup:
        ldr x0, =_stack_begin_
        mov x1, #0x1000
        mrs x2, mpidr_el1
        and x2, x2, #0x3
        add x2, x2, #0x1
        mul x1, x1, x2
        add x0, x0, x1
        mov sp, x0
        b main
        b .


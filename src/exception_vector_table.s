.section ".text"

.macro kernel_save_registers
        sub sp, sp, #272

        stp x0, x1, [sp, #16 * 0]
        stp x2, x3, [sp, #16 * 1]
        stp x4, x5, [sp, #16 * 2]
        stp x6, x7, [sp, #16 * 3]
        stp x8, x9, [sp, #16 * 4]
        stp x10, x11, [sp, #16 * 5]
        stp x12, x13, [sp, #16 * 6]
        stp x14, x15, [sp, #16 * 7]
        stp x16, x17, [sp, #16 * 8]
        stp x18, x19, [sp, #16 * 9]
        stp x20, x21, [sp, #16 * 10]
        stp x22, x23, [sp, #16 * 11]
        stp x24, x25, [sp, #16 * 12]
        stp x26, x27, [sp, #16 * 13]
        stp x28, x29, [sp, #16 * 14]
        
        mrs x9, elr_el1
        mrs x10, spsr_el1
        
        add x11, sp, #272
        
        stp x30, x9, [sp, #16 * 15]
        stp x10, x11, [sp, #16 * 16]
.endm

.macro kernel_restore_registers
        ldp x30, x9, [sp, #16 * 15]
        ldp x10, x11, [sp, #16 * 16]

        msr elr_el1, x9
        msr spsr_el1, x10

        ldp x0, x1, [sp, #16 * 0]
        ldp x2, x3, [sp, #16 * 1]
        ldp x4, x5, [sp, #16 * 2]
        ldp x6, x7, [sp, #16 * 3]
        ldp x8, x9, [sp, #16 * 4]
        ldp x10, x11, [sp, #16 * 5]
        ldp x12, x13, [sp, #16 * 6]
        ldp x14, x15, [sp, #16 * 7]
        ldp x16, x17, [sp, #16 * 8]
        ldp x18, x19, [sp, #16 * 9]
        ldp x20, x21, [sp, #16 * 10]
        ldp x22, x23, [sp, #16 * 11]
        ldp x24, x25, [sp, #16 * 12]
        ldp x26, x27, [sp, #16 * 13]
        ldp x28, x29, [sp, #16 * 14]
        
        add sp, sp, #272
.endm

.macro user_save_registers
        sub sp, sp, #272

        stp x0, x1, [sp, #16 * 0]
        stp x2, x3, [sp, #16 * 1]
        stp x4, x5, [sp, #16 * 2]
        stp x6, x7, [sp, #16 * 3]
        stp x8, x9, [sp, #16 * 4]
        stp x10, x11, [sp, #16 * 5]
        stp x12, x13, [sp, #16 * 6]
        stp x14, x15, [sp, #16 * 7]
        stp x16, x17, [sp, #16 * 8]
        stp x18, x19, [sp, #16 * 9]
        stp x20, x21, [sp, #16 * 10]
        stp x22, x23, [sp, #16 * 11]
        stp x24, x25, [sp, #16 * 12]
        stp x26, x27, [sp, #16 * 13]
        stp x28, x29, [sp, #16 * 14]

        mrs x9, elr_el1
        mrs x10, spsr_el1
        mrs x11, sp_el0

        stp x30, x9, [sp, #16 * 15]
        stp x10, x11, [sp, #16 * 16]
.endm

.macro user_restore_registers
        ldp x30, x9, [sp, #16 * 15]
        ldp x10, x11, [sp, #16 * 16]

        msr elr_el1, x9
        msr spsr_el1, x10
        msr sp_el0, x11

        ldp x0, x1, [sp, #16 * 0]
        ldp x2, x3, [sp, #16 * 1]
        ldp x4, x5, [sp, #16 * 2]
        ldp x6, x7, [sp, #16 * 3]
        ldp x8, x9, [sp, #16 * 4]
        ldp x10, x11, [sp, #16 * 5]
        ldp x12, x13, [sp, #16 * 6]
        ldp x14, x15, [sp, #16 * 7]
        ldp x16, x17, [sp, #16 * 8]
        ldp x18, x19, [sp, #16 * 9]
        ldp x20, x21, [sp, #16 * 10]
        ldp x22, x23, [sp, #16 * 11]
        ldp x24, x25, [sp, #16 * 12]
        ldp x26, x27, [sp, #16 * 13]
        ldp x28, x29, [sp, #16 * 14]

        add sp, sp, #272
.endm

.global exception_vector_table
    .balign 0x800
exception_vector_table:
        b .
    .balign 0x80
        b .
    .balign 0x80
        b .
    .balign 0x80
        b .
    .balign 0x80
        b handle_synchronous_exception_from_kernel
    .balign 0x80
        b handle_interrupt_request_from_kernel
    .balign 0x80
        b .
    .balign 0x80
        b .
    .balign 0x80
        b handle_synchronous_exception_from_user
    .balign 0x80
        b handle_interrupt_request_from_user
    .balign 0x80
        b .
    .balign 0x80
        b .
    .balign 0x80
        b .
    .balign 0x80
        b .
    .balign 0x80
        b .
    .balign 0x80
        b .

handle_synchronous_exception_from_kernel:
        kernel_save_registers
        
        mov x0, sp
        bl handle_exception_level_1_exception 
      
        kernel_restore_registers
      
        eret

handle_interrupt_request_from_kernel:
        kernel_save_registers
        
        mov x0, sp
        bl handle_exception_level_1_interrupt
      
        kernel_restore_registers
      
        eret
      
handle_synchronous_exception_from_user:
        user_save_registers
      
        mov x0, sp
        bl handle_exception_level_0_exception
      
        user_restore_registers
      
        eret

handle_interrupt_request_from_user:
        user_save_registers
      
        mov x0, sp
        bl handle_exception_level_0_interrupt

        user_restore_registers

        eret

.global return_from_exception
return_from_exception:
        mov sp, x0
        user_restore_registers
        eret

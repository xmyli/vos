.global init
    .balign 0x1000
init:
        sub sp, sp, 64

        // write "init" to stack
        mov x0, 105
        str x0, [sp]
        mov x0, 110
        str x0, [sp, 1]
        mov x0, 105
        str x0, [sp, 2]
        mov x0, 116
        str x0, [sp, 3]
        mov x0, 10
        str x0, [sp, 4]

        // set up write system call
        mov x0, 1
        mov x1, sp
        mov x2, 5

        // call write system call
        mov x8, 3
        svc 0

        // call fork system call
        mov x8, 5
        svc 0

        // check fork return value
        cmp x0, 0
        b.eq exec
        b wait

    exec:
        // write "echo" to stack
        mov x0, 47
        str x0, [sp]
        mov x0, 115
        str x0, [sp, 1]
        mov x0, 104
        str x0, [sp, 2]
        mov x0, 101
        str x0, [sp, 3]
        mov x0, 108
        str x0, [sp, 4]
        mov x0, 108
        str x0, [sp, 5]
        mov x0, 0
        str x0, [sp, 6]
        mov x3, sp // x3 stores pointer to "shell"

        sub sp, sp, 64

        mov x0, 104
        str x0, [sp]
        mov x0, 101
        str x0, [sp, 1]
        mov x0, 108
        str x0, [sp, 2]
        mov x0, 108
        str x0, [sp, 3]
        mov x0, 111
        str x0, [sp, 4]
        mov x0, 0
        str x0, [sp, 5]
        mov x4, sp // x4 stores pointer to "hello"

        sub sp, sp, 64

        mov x0, 119
        str x0, [sp]
        mov x0, 111
        str x0, [sp, 1]
        mov x0, 114
        str x0, [sp, 2]
        mov x0, 108
        str x0, [sp, 3]
        mov x0, 100
        str x0, [sp, 4]
        mov x0, 0
        str x0, [sp, 5]
        mov x5, sp // x5 stores pointer to "world"

        sub sp, sp, 64

        // write memory addresses of "hello" and "world" to stack
        mov x6, 0
        str x6, [sp, 16]
        str x5, [sp, 8]
        str x4, [sp]
        // sp is address to argument list

        // set up exec system call
        mov x0, x3
        mov x1, sp

        // do exec system call
        mov x8, 4
        svc 0

    wait:
        mov x8, 8
        svc 0
        b wait
    .balign 0x1000

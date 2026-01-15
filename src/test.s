.global test
    .balign 0x1000
test:
        mov x8, 7
        svc 0
        b test
    .balign 0x1000

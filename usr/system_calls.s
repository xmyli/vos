.global exit
exit:
    mov x8, 1
    svc 0
    ret

.global read
read:
    mov x8, 2
    svc 0
    ret

.global write
write:
    mov x8, 3
    svc 0
    ret

.global fork
fork:
    mov x8, 5
    svc 0
    ret

.global exec
exec:
    mov x8, 4
    svc 0
    ret

.global pipe
pipe:
    mov x8, 6
    svc 0
    ret

.global wait
wait:
    mov x8, 8
    svc 0
    ret

.global open
open:
    mov x8, 9
    svc 0
    ret

.global close
close:
    mov x8, 10
    svc 0
    ret

.global copy
copy:
    mov x8, 11
    svc 0
    ret

.global socket
socket:
    mov x8, 12
    svc 0
    ret

.global bind
bind:
    mov x8, 13
    svc 0
    ret

.global connect
connect:
    mov x8, 14
    svc 0
    ret

.global listen
listen:
    mov x8, 15
    svc 0
    ret

.global accept
accept:
    mov x8, 16
    svc 0
    ret

.global receive
receive:
    mov x8, 17
    svc 0
    ret

.global transmit
transmit:
    mov x8, 18
    svc 0
    ret


usr/cat:     file format elf64-littleaarch64


Disassembly of section .text:

0000000000400000 <.text>:
  400000:	a9ba7bfd 	stp	x29, x30, [sp, #-96]!
  400004:	910003fd 	mov	x29, sp
  400008:	7100041f 	cmp	w0, #0x1
  40000c:	f9000bf3 	str	x19, [sp, #16]
  400010:	540000cc 	b.gt	0x400028
  400014:	90000000 	adrp	x0, 0x400000
  400018:	9106b000 	add	x0, x0, #0x1ac
  40001c:	94000058 	bl	0x40017c
  400020:	52800000 	mov	w0, #0x0                   	// #0
  400024:	9400001a 	bl	0x40008c
  400028:	aa0103e4 	mov	x4, x1
  40002c:	52800003 	mov	w3, #0x0                   	// #0
  400030:	f9400480 	ldr	x0, [x4, #8]
  400034:	52800002 	mov	w2, #0x0                   	// #0
  400038:	52800021 	mov	w1, #0x1                   	// #1
  40003c:	94000029 	bl	0x4000e0
  400040:	3100041f 	cmn	w0, #0x1
  400044:	2a0003f3 	mov	w19, w0
  400048:	54000101 	b.ne	0x400068  // b.any
  40004c:	90000000 	adrp	x0, 0x400000
  400050:	9106ec00 	add	x0, x0, #0x1bb
  400054:	17fffff2 	b	0x40001c
  400058:	93407c02 	sxtw	x2, w0
  40005c:	910083e1 	add	x1, sp, #0x20
  400060:	52800020 	mov	w0, #0x1                   	// #1
  400064:	94000010 	bl	0x4000a4
  400068:	d2800802 	mov	x2, #0x40                  	// #64
  40006c:	910083e1 	add	x1, sp, #0x20
  400070:	2a1303e0 	mov	w0, w19
  400074:	94000009 	bl	0x400098
  400078:	35ffff00 	cbnz	w0, 0x400058
  40007c:	90000000 	adrp	x0, 0x400000
  400080:	9106e400 	add	x0, x0, #0x1b9
  400084:	17ffffe6 	b	0x40001c
  400088:	97ffffde 	bl	0x400000
  40008c:	d2800028 	mov	x8, #0x1                   	// #1
  400090:	d4000001 	svc	#0x0
  400094:	d65f03c0 	ret
  400098:	d2800048 	mov	x8, #0x2                   	// #2
  40009c:	d4000001 	svc	#0x0
  4000a0:	d65f03c0 	ret
  4000a4:	d2800068 	mov	x8, #0x3                   	// #3
  4000a8:	d4000001 	svc	#0x0
  4000ac:	d65f03c0 	ret
  4000b0:	d28000a8 	mov	x8, #0x5                   	// #5
  4000b4:	d4000001 	svc	#0x0
  4000b8:	d65f03c0 	ret
  4000bc:	d2800088 	mov	x8, #0x4                   	// #4
  4000c0:	d4000001 	svc	#0x0
  4000c4:	d65f03c0 	ret
  4000c8:	d28000c8 	mov	x8, #0x6                   	// #6
  4000cc:	d4000001 	svc	#0x0
  4000d0:	d65f03c0 	ret
  4000d4:	d2800108 	mov	x8, #0x8                   	// #8
  4000d8:	d4000001 	svc	#0x0
  4000dc:	d65f03c0 	ret
  4000e0:	d2800128 	mov	x8, #0x9                   	// #9
  4000e4:	d4000001 	svc	#0x0
  4000e8:	d65f03c0 	ret
  4000ec:	d2800148 	mov	x8, #0xa                   	// #10
  4000f0:	d4000001 	svc	#0x0
  4000f4:	d65f03c0 	ret
  4000f8:	d2800168 	mov	x8, #0xb                   	// #11
  4000fc:	d4000001 	svc	#0x0
  400100:	d65f03c0 	ret
  400104:	d2800188 	mov	x8, #0xc                   	// #12
  400108:	d4000001 	svc	#0x0
  40010c:	d65f03c0 	ret
  400110:	d28001a8 	mov	x8, #0xd                   	// #13
  400114:	d4000001 	svc	#0x0
  400118:	d65f03c0 	ret
  40011c:	d28001c8 	mov	x8, #0xe                   	// #14
  400120:	d4000001 	svc	#0x0
  400124:	d65f03c0 	ret
  400128:	d28001e8 	mov	x8, #0xf                   	// #15
  40012c:	d4000001 	svc	#0x0
  400130:	d65f03c0 	ret
  400134:	d2800208 	mov	x8, #0x10                  	// #16
  400138:	d4000001 	svc	#0x0
  40013c:	d65f03c0 	ret
  400140:	d2800228 	mov	x8, #0x11                  	// #17
  400144:	d4000001 	svc	#0x0
  400148:	d65f03c0 	ret
  40014c:	d2800248 	mov	x8, #0x12                  	// #18
  400150:	d4000001 	svc	#0x0
  400154:	d65f03c0 	ret
  400158:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
  40015c:	d2800022 	mov	x2, #0x1                   	// #1
  400160:	910003fd 	mov	x29, sp
  400164:	91007fe1 	add	x1, sp, #0x1f
  400168:	39007fe0 	strb	w0, [sp, #31]
  40016c:	2a0203e0 	mov	w0, w2
  400170:	97ffffcd 	bl	0x4000a4
  400174:	a8c27bfd 	ldp	x29, x30, [sp], #32
  400178:	d65f03c0 	ret
  40017c:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
  400180:	910003fd 	mov	x29, sp
  400184:	f9000bf3 	str	x19, [sp, #16]
  400188:	aa0003f3 	mov	x19, x0
  40018c:	39400260 	ldrb	w0, [x19]
  400190:	35000080 	cbnz	w0, 0x4001a0
  400194:	f9400bf3 	ldr	x19, [sp, #16]
  400198:	a8c27bfd 	ldp	x29, x30, [sp], #32
  40019c:	d65f03c0 	ret
  4001a0:	91000673 	add	x19, x19, #0x1
  4001a4:	97ffffed 	bl	0x400158
  4001a8:	17fffff9 	b	0x40018c

Disassembly of section .rodata:

00000000004001ac <.rodata>:
  4001ac:	3a746163 	.inst	0x3a746163 ; undefined
  4001b0:	67726120 	.inst	0x67726120 ; undefined
  4001b4:	203c2063 	.inst	0x203c2063 ; undefined
  4001b8:	63000a32 	.inst	0x63000a32 ; undefined
  4001bc:	203a7461 	.inst	0x203a7461 ; undefined
  4001c0:	62616e75 	.inst	0x62616e75 ; undefined
  4001c4:	7420656c 	.inst	0x7420656c ; undefined
  4001c8:	706f206f 	adr	x15, 0x4de5d7
  4001cc:	66206e65 	.inst	0x66206e65 ; undefined
  4001d0:	0a656c69 	bic	w9, w3, w5, lsr #27
	...

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	3a434347 	ccmn	w26, w3, #0x7, mi	// mi = first
   4:	72412820 	.inst	0x72412820 ; undefined
   8:	4e47206d 	.inst	0x4e47206d ; undefined
   c:	6f542055 	umlal2	v21.4s, v2.8h, v4.h[1]
  10:	68636c6f 	.inst	0x68636c6f ; undefined
  14:	206e6961 	.inst	0x206e6961 ; undefined
  18:	332e3331 	.inst	0x332e3331 ; undefined
  1c:	6c65522e 	ldnp	d14, d20, [x17, #-432]
  20:	42282031 	.inst	0x42282031 ; undefined
  24:	646c6975 	.inst	0x646c6975 ; undefined
  28:	6d726120 	ldp	d0, d24, [x9, #-224]
  2c:	2e33312d 	usubw	v13.8h, v9.8h, v19.8b
  30:	29293432 	stp	w18, w13, [x1, #-184]
  34:	2e333120 	usubw	v0.8h, v9.8h, v19.8b
  38:	20312e33 	.inst	0x20312e33 ; undefined
  3c:	34323032 	cbz	w18, 0x64640
  40:	34313630 	cbz	w16, 0x62704
	...

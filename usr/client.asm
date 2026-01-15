
usr/client:     file format elf64-littleaarch64


Disassembly of section .text:

0000000000400000 <.text>:
  400000:	a9bd7bfd 	stp	x29, x30, [sp, #-48]!
  400004:	52800000 	mov	w0, #0x0                   	// #0
  400008:	910003fd 	mov	x29, sp
  40000c:	f9000bf3 	str	x19, [sp, #16]
  400010:	9400003f 	bl	0x40010c
  400014:	52804041 	mov	w1, #0x202                 	// #514
  400018:	72a14001 	movk	w1, #0xa00, lsl #16
  40001c:	5280fa22 	mov	w2, #0x7d1                 	// #2001
  400020:	2a0003f3 	mov	w19, w0
  400024:	94000040 	bl	0x400124
  400028:	34000240 	cbz	w0, 0x400070
  40002c:	90000000 	adrp	x0, 0x400000
  400030:	91067000 	add	x0, x0, #0x19c
  400034:	9400004b 	bl	0x400160
  400038:	90000001 	adrp	x1, 0x400000
  40003c:	9107b421 	add	x1, x1, #0x1ed
  400040:	f9400020 	ldr	x0, [x1]
  400044:	d28001a2 	mov	x2, #0xd                   	// #13
  400048:	f90013e0 	str	x0, [sp, #32]
  40004c:	f8405020 	ldur	x0, [x1, #5]
  400050:	910083e1 	add	x1, sp, #0x20
  400054:	f80253e0 	stur	x0, [sp, #37]
  400058:	2a1303e0 	mov	w0, w19
  40005c:	94000014 	bl	0x4000ac
  400060:	b4000120 	cbz	x0, 0x400084
  400064:	90000000 	adrp	x0, 0x400000
  400068:	91076c00 	add	x0, x0, #0x1db
  40006c:	14000003 	b	0x400078
  400070:	90000000 	adrp	x0, 0x400000
  400074:	9106a000 	add	x0, x0, #0x1a8
  400078:	9400003a 	bl	0x400160
  40007c:	52800000 	mov	w0, #0x0                   	// #0
  400080:	94000005 	bl	0x400094
  400084:	90000000 	adrp	x0, 0x400000
  400088:	91070400 	add	x0, x0, #0x1c1
  40008c:	17fffffb 	b	0x400078
  400090:	97ffffdc 	bl	0x400000
  400094:	d2800028 	mov	x8, #0x1                   	// #1
  400098:	d4000001 	svc	#0x0
  40009c:	d65f03c0 	ret
  4000a0:	d2800048 	mov	x8, #0x2                   	// #2
  4000a4:	d4000001 	svc	#0x0
  4000a8:	d65f03c0 	ret
  4000ac:	d2800068 	mov	x8, #0x3                   	// #3
  4000b0:	d4000001 	svc	#0x0
  4000b4:	d65f03c0 	ret
  4000b8:	d28000a8 	mov	x8, #0x5                   	// #5
  4000bc:	d4000001 	svc	#0x0
  4000c0:	d65f03c0 	ret
  4000c4:	d2800088 	mov	x8, #0x4                   	// #4
  4000c8:	d4000001 	svc	#0x0
  4000cc:	d65f03c0 	ret
  4000d0:	d28000c8 	mov	x8, #0x6                   	// #6
  4000d4:	d4000001 	svc	#0x0
  4000d8:	d65f03c0 	ret
  4000dc:	d2800108 	mov	x8, #0x8                   	// #8
  4000e0:	d4000001 	svc	#0x0
  4000e4:	d65f03c0 	ret
  4000e8:	d2800128 	mov	x8, #0x9                   	// #9
  4000ec:	d4000001 	svc	#0x0
  4000f0:	d65f03c0 	ret
  4000f4:	d2800148 	mov	x8, #0xa                   	// #10
  4000f8:	d4000001 	svc	#0x0
  4000fc:	d65f03c0 	ret
  400100:	d2800168 	mov	x8, #0xb                   	// #11
  400104:	d4000001 	svc	#0x0
  400108:	d65f03c0 	ret
  40010c:	d2800188 	mov	x8, #0xc                   	// #12
  400110:	d4000001 	svc	#0x0
  400114:	d65f03c0 	ret
  400118:	d28001a8 	mov	x8, #0xd                   	// #13
  40011c:	d4000001 	svc	#0x0
  400120:	d65f03c0 	ret
  400124:	d28001c8 	mov	x8, #0xe                   	// #14
  400128:	d4000001 	svc	#0x0
  40012c:	d65f03c0 	ret
  400130:	d28001e8 	mov	x8, #0xf                   	// #15
  400134:	d4000001 	svc	#0x0
  400138:	d65f03c0 	ret
  40013c:	d2800208 	mov	x8, #0x10                  	// #16
  400140:	d4000001 	svc	#0x0
  400144:	d65f03c0 	ret
  400148:	d2800228 	mov	x8, #0x11                  	// #17
  40014c:	d4000001 	svc	#0x0
  400150:	d65f03c0 	ret
  400154:	d2800248 	mov	x8, #0x12                  	// #18
  400158:	d4000001 	svc	#0x0
  40015c:	d65f03c0 	ret
  400160:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
  400164:	910003fd 	mov	x29, sp
  400168:	f9000bf3 	str	x19, [sp, #16]
  40016c:	aa0003f3 	mov	x19, x0
  400170:	39400260 	ldrb	w0, [x19]
  400174:	35000080 	cbnz	w0, 0x400184
  400178:	f9400bf3 	ldr	x19, [sp, #16]
  40017c:	a8c27bfd 	ldp	x29, x30, [sp], #32
  400180:	d65f03c0 	ret
  400184:	d2800022 	mov	x2, #0x1                   	// #1
  400188:	aa1303e1 	mov	x1, x19
  40018c:	2a0203e0 	mov	w0, w2
  400190:	91000673 	add	x19, x19, #0x1
  400194:	97ffffc6 	bl	0x4000ac
  400198:	17fffff6 	b	0x400170

Disassembly of section .rodata:

000000000040019c <.rodata>:
  40019c:	4e4e4f43 	.inst	0x4e4e4f43 ; undefined
  4001a0:	45544345 	saddwb	z5.h, z26.h, z20.b
  4001a4:	000a2e44 	.inst	0x000a2e44 ; undefined
  4001a8:	4f525245 	.inst	0x4f525245 ; undefined
  4001ac:	63203a52 	.inst	0x63203a52 ; undefined
  4001b0:	656e6e6f 	fnmls	z15.h, p3/m, z19.h, z14.h
  4001b4:	29287463 	stp	w3, w29, [x3, #-192]
  4001b8:	69616620 	ldpsw	x0, x25, [x17, #-248]
  4001bc:	0a64656c 	bic	w12, w11, w4, lsr #25
  4001c0:	52524500 	.inst	0x52524500 ; undefined
  4001c4:	203a524f 	.inst	0x203a524f ; undefined
  4001c8:	6e617274 	uabdl2	v20.4s, v19.8h, v1.8h
  4001cc:	74696d73 	.inst	0x74696d73 ; undefined
  4001d0:	66202928 	.inst	0x66202928 ; undefined
  4001d4:	656c6961 	fnmls	z1.h, p2/m, z11.h, z12.h
  4001d8:	44000a64 	.inst	0x44000a64 ; undefined
  4001dc:	20415441 	.inst	0x20415441 ; undefined
  4001e0:	4e415254 	.inst	0x4e415254 ; undefined
  4001e4:	54494d53 	bc.cc	0x492b8c  // bc.lo, bc.ul, bc.last
  4001e8:	0a444554 	and	w20, w10, w4, lsr #17
  4001ec:	6c654800 	ldnp	d0, d18, [x0, #-432]
  4001f0:	202c6f6c 	.inst	0x202c6f6c ; undefined
  4001f4:	6c726f57 	ldnp	d23, d27, [x26, #-224]
  4001f8:	Address 0x4001f8 is out of bounds.


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

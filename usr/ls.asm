
usr/ls:     file format elf64-littleaarch64


Disassembly of section .text:

0000000000400000 <.text>:
  400000:	a9b47bfd 	stp	x29, x30, [sp, #-192]!
  400004:	910003fd 	mov	x29, sp
  400008:	7100041f 	cmp	w0, #0x1
  40000c:	a90153f3 	stp	x19, x20, [sp, #16]
  400010:	a9025bf5 	stp	x21, x22, [sp, #32]
  400014:	5400026c 	b.gt	0x400060
  400018:	90000000 	adrp	x0, 0x400000
  40001c:	9107d000 	add	x0, x0, #0x1f4
  400020:	52800003 	mov	w3, #0x0                   	// #0
  400024:	52800002 	mov	w2, #0x0                   	// #0
  400028:	52800021 	mov	w1, #0x1                   	// #1
  40002c:	9400003f 	bl	0x400128
  400030:	3100041f 	cmn	w0, #0x1
  400034:	2a0003f3 	mov	w19, w0
  400038:	54000200 	b.eq	0x400078  // b.none
  40003c:	52800156 	mov	w22, #0xa                   	// #10
  400040:	d2801002 	mov	x2, #0x80                  	// #128
  400044:	910103e1 	add	x1, sp, #0x40
  400048:	2a1303e0 	mov	w0, w19
  40004c:	94000025 	bl	0x4000e0
  400050:	b40001a0 	cbz	x0, 0x400084
  400054:	910107f4 	add	x20, sp, #0x41
  400058:	d2800035 	mov	x21, #0x1                   	// #1
  40005c:	14000014 	b	0x4000ac
  400060:	aa0103e4 	mov	x4, x1
  400064:	52800003 	mov	w3, #0x0                   	// #0
  400068:	f9400480 	ldr	x0, [x4, #8]
  40006c:	52800002 	mov	w2, #0x0                   	// #0
  400070:	52800021 	mov	w1, #0x1                   	// #1
  400074:	17ffffee 	b	0x40002c
  400078:	90000000 	adrp	x0, 0x400000
  40007c:	9107d800 	add	x0, x0, #0x1f6
  400080:	94000051 	bl	0x4001c4
  400084:	52800000 	mov	w0, #0x0                   	// #0
  400088:	94000013 	bl	0x4000d4
  40008c:	39400280 	ldrb	w0, [x20]
  400090:	340000a0 	cbz	w0, 0x4000a4
  400094:	d2800022 	mov	x2, #0x1                   	// #1
  400098:	aa1403e1 	mov	x1, x20
  40009c:	2a0203e0 	mov	w0, w2
  4000a0:	94000013 	bl	0x4000ec
  4000a4:	910006b5 	add	x21, x21, #0x1
  4000a8:	91000694 	add	x20, x20, #0x1
  4000ac:	f9405be0 	ldr	x0, [sp, #176]
  4000b0:	eb15001f 	cmp	x0, x21
  4000b4:	54fffec8 	b.hi	0x40008c  // b.pmore
  4000b8:	d2800022 	mov	x2, #0x1                   	// #1
  4000bc:	9100ffe1 	add	x1, sp, #0x3f
  4000c0:	3900fff6 	strb	w22, [sp, #63]
  4000c4:	2a0203e0 	mov	w0, w2
  4000c8:	94000009 	bl	0x4000ec
  4000cc:	17ffffdd 	b	0x400040
  4000d0:	97ffffcc 	bl	0x400000
  4000d4:	d2800028 	mov	x8, #0x1                   	// #1
  4000d8:	d4000001 	svc	#0x0
  4000dc:	d65f03c0 	ret
  4000e0:	d2800048 	mov	x8, #0x2                   	// #2
  4000e4:	d4000001 	svc	#0x0
  4000e8:	d65f03c0 	ret
  4000ec:	d2800068 	mov	x8, #0x3                   	// #3
  4000f0:	d4000001 	svc	#0x0
  4000f4:	d65f03c0 	ret
  4000f8:	d28000a8 	mov	x8, #0x5                   	// #5
  4000fc:	d4000001 	svc	#0x0
  400100:	d65f03c0 	ret
  400104:	d2800088 	mov	x8, #0x4                   	// #4
  400108:	d4000001 	svc	#0x0
  40010c:	d65f03c0 	ret
  400110:	d28000c8 	mov	x8, #0x6                   	// #6
  400114:	d4000001 	svc	#0x0
  400118:	d65f03c0 	ret
  40011c:	d2800108 	mov	x8, #0x8                   	// #8
  400120:	d4000001 	svc	#0x0
  400124:	d65f03c0 	ret
  400128:	d2800128 	mov	x8, #0x9                   	// #9
  40012c:	d4000001 	svc	#0x0
  400130:	d65f03c0 	ret
  400134:	d2800148 	mov	x8, #0xa                   	// #10
  400138:	d4000001 	svc	#0x0
  40013c:	d65f03c0 	ret
  400140:	d2800168 	mov	x8, #0xb                   	// #11
  400144:	d4000001 	svc	#0x0
  400148:	d65f03c0 	ret
  40014c:	d2800188 	mov	x8, #0xc                   	// #12
  400150:	d4000001 	svc	#0x0
  400154:	d65f03c0 	ret
  400158:	d28001a8 	mov	x8, #0xd                   	// #13
  40015c:	d4000001 	svc	#0x0
  400160:	d65f03c0 	ret
  400164:	d28001c8 	mov	x8, #0xe                   	// #14
  400168:	d4000001 	svc	#0x0
  40016c:	d65f03c0 	ret
  400170:	d28001e8 	mov	x8, #0xf                   	// #15
  400174:	d4000001 	svc	#0x0
  400178:	d65f03c0 	ret
  40017c:	d2800208 	mov	x8, #0x10                  	// #16
  400180:	d4000001 	svc	#0x0
  400184:	d65f03c0 	ret
  400188:	d2800228 	mov	x8, #0x11                  	// #17
  40018c:	d4000001 	svc	#0x0
  400190:	d65f03c0 	ret
  400194:	d2800248 	mov	x8, #0x12                  	// #18
  400198:	d4000001 	svc	#0x0
  40019c:	d65f03c0 	ret
  4001a0:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
  4001a4:	d2800022 	mov	x2, #0x1                   	// #1
  4001a8:	910003fd 	mov	x29, sp
  4001ac:	91007fe1 	add	x1, sp, #0x1f
  4001b0:	39007fe0 	strb	w0, [sp, #31]
  4001b4:	2a0203e0 	mov	w0, w2
  4001b8:	97ffffcd 	bl	0x4000ec
  4001bc:	a8c27bfd 	ldp	x29, x30, [sp], #32
  4001c0:	d65f03c0 	ret
  4001c4:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
  4001c8:	910003fd 	mov	x29, sp
  4001cc:	f9000bf3 	str	x19, [sp, #16]
  4001d0:	aa0003f3 	mov	x19, x0
  4001d4:	39400260 	ldrb	w0, [x19]
  4001d8:	35000080 	cbnz	w0, 0x4001e8
  4001dc:	f9400bf3 	ldr	x19, [sp, #16]
  4001e0:	a8c27bfd 	ldp	x29, x30, [sp], #32
  4001e4:	d65f03c0 	ret
  4001e8:	91000673 	add	x19, x19, #0x1
  4001ec:	97ffffed 	bl	0x4001a0
  4001f0:	17fffff9 	b	0x4001d4

Disassembly of section .rodata:

00000000004001f4 <.rodata>:
  4001f4:	736c002f 	.inst	0x736c002f ; undefined
  4001f8:	6e75203a 	usubl2	v26.4s, v1.8h, v21.8h
  4001fc:	656c6261 	fnmls	z1.h, p0/m, z19.h, z12.h
  400200:	206f7420 	.inst	0x206f7420 ; undefined
  400204:	6e65706f 	uabdl2	v15.4s, v3.8h, v5.8h
  400208:	72696420 	.inst	0x72696420 ; undefined
  40020c:	6f746365 	umlsl2	v5.4s, v27.8h, v4.h[3]
  400210:	000a7972 	.inst	0x000a7972 ; undefined

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


usr/server:     file format elf64-littleaarch64


Disassembly of section .text:

0000000000400000 <.text>:
  400000:	a9b97bfd 	stp	x29, x30, [sp, #-112]!
  400004:	52800000 	mov	w0, #0x0                   	// #0
  400008:	910003fd 	mov	x29, sp
  40000c:	a90153f3 	stp	x19, x20, [sp, #16]
  400010:	a9025bf5 	stp	x21, x22, [sp, #32]
  400014:	94000057 	bl	0x400170
  400018:	5280fa01 	mov	w1, #0x7d0                 	// #2000
  40001c:	2a0003f4 	mov	w20, w0
  400020:	94000057 	bl	0x40017c
  400024:	350000c0 	cbnz	w0, 0x40003c
  400028:	90000000 	adrp	x0, 0x400000
  40002c:	91087000 	add	x0, x0, #0x21c
  400030:	9400006c 	bl	0x4001e0
  400034:	52800000 	mov	w0, #0x0                   	// #0
  400038:	94000030 	bl	0x4000f8
  40003c:	2a1403e0 	mov	w0, w20
  400040:	94000055 	bl	0x400194
  400044:	35000080 	cbnz	w0, 0x400054
  400048:	90000000 	adrp	x0, 0x400000
  40004c:	9108c800 	add	x0, x0, #0x232
  400050:	17fffff8 	b	0x400030
  400054:	90000000 	adrp	x0, 0x400000
  400058:	91092800 	add	x0, x0, #0x24a
  40005c:	94000061 	bl	0x4001e0
  400060:	2a1403e0 	mov	w0, w20
  400064:	90000015 	adrp	x21, 0x400000
  400068:	910962b5 	add	x21, x21, #0x258
  40006c:	90000016 	adrp	x22, 0x400000
  400070:	91095ad6 	add	x22, x22, #0x256
  400074:	9400004b 	bl	0x4001a0
  400078:	2a0003f3 	mov	w19, w0
  40007c:	3100067f 	cmn	w19, #0x1
  400080:	540000e1 	b.ne	0x40009c  // b.any
  400084:	90000000 	adrp	x0, 0x400000
  400088:	91097c00 	add	x0, x0, #0x25f
  40008c:	94000055 	bl	0x4001e0
  400090:	2a1403e0 	mov	w0, w20
  400094:	94000031 	bl	0x400158
  400098:	17ffffe7 	b	0x400034
  40009c:	d2800802 	mov	x2, #0x40                  	// #64
  4000a0:	52800001 	mov	w1, #0x0                   	// #0
  4000a4:	9100c3e0 	add	x0, sp, #0x30
  4000a8:	94000047 	bl	0x4001c4
  4000ac:	d2800802 	mov	x2, #0x40                  	// #64
  4000b0:	9100c3e1 	add	x1, sp, #0x30
  4000b4:	2a1303e0 	mov	w0, w19
  4000b8:	94000013 	bl	0x400104
  4000bc:	b4000100 	cbz	x0, 0x4000dc
  4000c0:	aa1503e0 	mov	x0, x21
  4000c4:	94000047 	bl	0x4001e0
  4000c8:	9100c3e0 	add	x0, sp, #0x30
  4000cc:	94000045 	bl	0x4001e0
  4000d0:	aa1603e0 	mov	x0, x22
  4000d4:	94000043 	bl	0x4001e0
  4000d8:	17fffff1 	b	0x40009c
  4000dc:	2a1303e0 	mov	w0, w19
  4000e0:	9400001e 	bl	0x400158
  4000e4:	2a1403e0 	mov	w0, w20
  4000e8:	9400002e 	bl	0x4001a0
  4000ec:	2a0003f3 	mov	w19, w0
  4000f0:	17ffffe3 	b	0x40007c
  4000f4:	97ffffc3 	bl	0x400000
  4000f8:	d2800028 	mov	x8, #0x1                   	// #1
  4000fc:	d4000001 	svc	#0x0
  400100:	d65f03c0 	ret
  400104:	d2800048 	mov	x8, #0x2                   	// #2
  400108:	d4000001 	svc	#0x0
  40010c:	d65f03c0 	ret
  400110:	d2800068 	mov	x8, #0x3                   	// #3
  400114:	d4000001 	svc	#0x0
  400118:	d65f03c0 	ret
  40011c:	d28000a8 	mov	x8, #0x5                   	// #5
  400120:	d4000001 	svc	#0x0
  400124:	d65f03c0 	ret
  400128:	d2800088 	mov	x8, #0x4                   	// #4
  40012c:	d4000001 	svc	#0x0
  400130:	d65f03c0 	ret
  400134:	d28000c8 	mov	x8, #0x6                   	// #6
  400138:	d4000001 	svc	#0x0
  40013c:	d65f03c0 	ret
  400140:	d2800108 	mov	x8, #0x8                   	// #8
  400144:	d4000001 	svc	#0x0
  400148:	d65f03c0 	ret
  40014c:	d2800128 	mov	x8, #0x9                   	// #9
  400150:	d4000001 	svc	#0x0
  400154:	d65f03c0 	ret
  400158:	d2800148 	mov	x8, #0xa                   	// #10
  40015c:	d4000001 	svc	#0x0
  400160:	d65f03c0 	ret
  400164:	d2800168 	mov	x8, #0xb                   	// #11
  400168:	d4000001 	svc	#0x0
  40016c:	d65f03c0 	ret
  400170:	d2800188 	mov	x8, #0xc                   	// #12
  400174:	d4000001 	svc	#0x0
  400178:	d65f03c0 	ret
  40017c:	d28001a8 	mov	x8, #0xd                   	// #13
  400180:	d4000001 	svc	#0x0
  400184:	d65f03c0 	ret
  400188:	d28001c8 	mov	x8, #0xe                   	// #14
  40018c:	d4000001 	svc	#0x0
  400190:	d65f03c0 	ret
  400194:	d28001e8 	mov	x8, #0xf                   	// #15
  400198:	d4000001 	svc	#0x0
  40019c:	d65f03c0 	ret
  4001a0:	d2800208 	mov	x8, #0x10                  	// #16
  4001a4:	d4000001 	svc	#0x0
  4001a8:	d65f03c0 	ret
  4001ac:	d2800228 	mov	x8, #0x11                  	// #17
  4001b0:	d4000001 	svc	#0x0
  4001b4:	d65f03c0 	ret
  4001b8:	d2800248 	mov	x8, #0x12                  	// #18
  4001bc:	d4000001 	svc	#0x0
  4001c0:	d65f03c0 	ret
  4001c4:	d2800003 	mov	x3, #0x0                   	// #0
  4001c8:	eb03005f 	cmp	x2, x3
  4001cc:	54000041 	b.ne	0x4001d4  // b.any
  4001d0:	d65f03c0 	ret
  4001d4:	38236801 	strb	w1, [x0, x3]
  4001d8:	91000463 	add	x3, x3, #0x1
  4001dc:	17fffffb 	b	0x4001c8
  4001e0:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
  4001e4:	910003fd 	mov	x29, sp
  4001e8:	f9000bf3 	str	x19, [sp, #16]
  4001ec:	aa0003f3 	mov	x19, x0
  4001f0:	39400260 	ldrb	w0, [x19]
  4001f4:	35000080 	cbnz	w0, 0x400204
  4001f8:	f9400bf3 	ldr	x19, [sp, #16]
  4001fc:	a8c27bfd 	ldp	x29, x30, [sp], #32
  400200:	d65f03c0 	ret
  400204:	d2800022 	mov	x2, #0x1                   	// #1
  400208:	aa1303e1 	mov	x1, x19
  40020c:	2a0203e0 	mov	w0, w2
  400210:	91000673 	add	x19, x19, #0x1
  400214:	97ffffbf 	bl	0x400110
  400218:	17fffff6 	b	0x4001f0

Disassembly of section .rodata:

000000000040021c <.rodata>:
  40021c:	4f525245 	.inst	0x4f525245 ; undefined
  400220:	62203a52 	.inst	0x62203a52 ; undefined
  400224:	28646e69 	ldnp	w9, w27, [x19, #-224]
  400228:	61662029 	.inst	0x61662029 ; undefined
  40022c:	64656c69 	.inst	0x64656c69 ; undefined
  400230:	5245000a 	.inst	0x5245000a ; undefined
  400234:	3a524f52 	.inst	0x3a524f52 ; undefined
  400238:	73696c20 	.inst	0x73696c20 ; undefined
  40023c:	286e6574 	ldnp	w20, w25, [x11, #-144]
  400240:	61662029 	.inst	0x61662029 ; undefined
  400244:	64656c69 	.inst	0x64656c69 ; undefined
  400248:	494c000a 	.inst	0x494c000a ; undefined
  40024c:	4e455453 	.inst	0x4e455453 ; undefined
  400250:	2e474e49 	.inst	0x2e474e49 ; undefined
  400254:	000a2e2e 	.inst	0x000a2e2e ; undefined
  400258:	41544144 	.inst	0x41544144 ; undefined
  40025c:	4500203a 	.inst	0x4500203a ; undefined
  400260:	524f5252 	.inst	0x524f5252 ; undefined
  400264:	6361203a 	.inst	0x6361203a ; undefined
  400268:	74706563 	.inst	0x74706563 ; undefined
  40026c:	66202928 	.inst	0x66202928 ; undefined
  400270:	656c6961 	fnmls	z1.h, p2/m, z11.h, z12.h
  400274:	Address 0x400274 is out of bounds.


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


usr/pong:     file format elf64-littleaarch64


Disassembly of section .text:

0000000000400000 <.text>:
  400000:	a9b87bfd 	stp	x29, x30, [sp, #-128]!
  400004:	90000000 	adrp	x0, 0x400000
  400008:	9108d000 	add	x0, x0, #0x234
  40000c:	910003fd 	mov	x29, sp
  400010:	a90153f3 	stp	x19, x20, [sp, #16]
  400014:	a9025bf5 	stp	x21, x22, [sp, #32]
  400018:	94000078 	bl	0x4001f8
  40001c:	52800020 	mov	w0, #0x1                   	// #1
  400020:	9400005a 	bl	0x400188
  400024:	5280fa01 	mov	w1, #0x7d0                 	// #2000
  400028:	2a0003f4 	mov	w20, w0
  40002c:	9400005a 	bl	0x400194
  400030:	350000c0 	cbnz	w0, 0x400048
  400034:	90000000 	adrp	x0, 0x400000
  400038:	9108e800 	add	x0, x0, #0x23a
  40003c:	9400006f 	bl	0x4001f8
  400040:	52800000 	mov	w0, #0x0                   	// #0
  400044:	94000033 	bl	0x400110
  400048:	90000000 	adrp	x0, 0x400000
  40004c:	91092000 	add	x0, x0, #0x248
  400050:	9400006a 	bl	0x4001f8
  400054:	d2800802 	mov	x2, #0x40                  	// #64
  400058:	52800001 	mov	w1, #0x0                   	// #0
  40005c:	8b2263e0 	add	x0, sp, x2
  400060:	90000015 	adrp	x21, 0x400000
  400064:	91095ab5 	add	x21, x21, #0x256
  400068:	90000016 	adrp	x22, 0x400000
  40006c:	9109e6d6 	add	x22, x22, #0x279
  400070:	9400005b 	bl	0x4001dc
  400074:	9100ebe4 	add	x4, sp, #0x3a
  400078:	9100f3e3 	add	x3, sp, #0x3c
  40007c:	790077ff 	strh	wzr, [sp, #58]
  400080:	d2800062 	mov	x2, #0x3                   	// #3
  400084:	910103e1 	add	x1, sp, #0x40
  400088:	b9003fff 	str	wzr, [sp, #60]
  40008c:	2a1403e0 	mov	w0, w20
  400090:	9400004d 	bl	0x4001c4
  400094:	aa0003f3 	mov	x19, x0
  400098:	b50000f3 	cbnz	x19, 0x4000b4
  40009c:	90000000 	adrp	x0, 0x400000
  4000a0:	910a2c00 	add	x0, x0, #0x28b
  4000a4:	94000055 	bl	0x4001f8
  4000a8:	2a1403e0 	mov	w0, w20
  4000ac:	94000031 	bl	0x400170
  4000b0:	17ffffe4 	b	0x400040
  4000b4:	aa1503e0 	mov	x0, x21
  4000b8:	94000050 	bl	0x4001f8
  4000bc:	794077e4 	ldrh	w4, [sp, #58]
  4000c0:	aa1303e2 	mov	x2, x19
  4000c4:	910103e1 	add	x1, sp, #0x40
  4000c8:	2a1403e0 	mov	w0, w20
  4000cc:	b9403fe3 	ldr	w3, [sp, #60]
  4000d0:	94000040 	bl	0x4001d0
  4000d4:	b5000080 	cbnz	x0, 0x4000e4
  4000d8:	90000000 	adrp	x0, 0x400000
  4000dc:	91099c00 	add	x0, x0, #0x267
  4000e0:	17ffffd7 	b	0x40003c
  4000e4:	aa1603e0 	mov	x0, x22
  4000e8:	94000044 	bl	0x4001f8
  4000ec:	9100ebe4 	add	x4, sp, #0x3a
  4000f0:	9100f3e3 	add	x3, sp, #0x3c
  4000f4:	d2800062 	mov	x2, #0x3                   	// #3
  4000f8:	910103e1 	add	x1, sp, #0x40
  4000fc:	2a1403e0 	mov	w0, w20
  400100:	94000031 	bl	0x4001c4
  400104:	aa0003f3 	mov	x19, x0
  400108:	17ffffe4 	b	0x400098
  40010c:	97ffffbd 	bl	0x400000
  400110:	d2800028 	mov	x8, #0x1                   	// #1
  400114:	d4000001 	svc	#0x0
  400118:	d65f03c0 	ret
  40011c:	d2800048 	mov	x8, #0x2                   	// #2
  400120:	d4000001 	svc	#0x0
  400124:	d65f03c0 	ret
  400128:	d2800068 	mov	x8, #0x3                   	// #3
  40012c:	d4000001 	svc	#0x0
  400130:	d65f03c0 	ret
  400134:	d28000a8 	mov	x8, #0x5                   	// #5
  400138:	d4000001 	svc	#0x0
  40013c:	d65f03c0 	ret
  400140:	d2800088 	mov	x8, #0x4                   	// #4
  400144:	d4000001 	svc	#0x0
  400148:	d65f03c0 	ret
  40014c:	d28000c8 	mov	x8, #0x6                   	// #6
  400150:	d4000001 	svc	#0x0
  400154:	d65f03c0 	ret
  400158:	d2800108 	mov	x8, #0x8                   	// #8
  40015c:	d4000001 	svc	#0x0
  400160:	d65f03c0 	ret
  400164:	d2800128 	mov	x8, #0x9                   	// #9
  400168:	d4000001 	svc	#0x0
  40016c:	d65f03c0 	ret
  400170:	d2800148 	mov	x8, #0xa                   	// #10
  400174:	d4000001 	svc	#0x0
  400178:	d65f03c0 	ret
  40017c:	d2800168 	mov	x8, #0xb                   	// #11
  400180:	d4000001 	svc	#0x0
  400184:	d65f03c0 	ret
  400188:	d2800188 	mov	x8, #0xc                   	// #12
  40018c:	d4000001 	svc	#0x0
  400190:	d65f03c0 	ret
  400194:	d28001a8 	mov	x8, #0xd                   	// #13
  400198:	d4000001 	svc	#0x0
  40019c:	d65f03c0 	ret
  4001a0:	d28001c8 	mov	x8, #0xe                   	// #14
  4001a4:	d4000001 	svc	#0x0
  4001a8:	d65f03c0 	ret
  4001ac:	d28001e8 	mov	x8, #0xf                   	// #15
  4001b0:	d4000001 	svc	#0x0
  4001b4:	d65f03c0 	ret
  4001b8:	d2800208 	mov	x8, #0x10                  	// #16
  4001bc:	d4000001 	svc	#0x0
  4001c0:	d65f03c0 	ret
  4001c4:	d2800228 	mov	x8, #0x11                  	// #17
  4001c8:	d4000001 	svc	#0x0
  4001cc:	d65f03c0 	ret
  4001d0:	d2800248 	mov	x8, #0x12                  	// #18
  4001d4:	d4000001 	svc	#0x0
  4001d8:	d65f03c0 	ret
  4001dc:	d2800003 	mov	x3, #0x0                   	// #0
  4001e0:	eb03005f 	cmp	x2, x3
  4001e4:	54000041 	b.ne	0x4001ec  // b.any
  4001e8:	d65f03c0 	ret
  4001ec:	38236801 	strb	w1, [x0, x3]
  4001f0:	91000463 	add	x3, x3, #0x1
  4001f4:	17fffffb 	b	0x4001e0
  4001f8:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
  4001fc:	910003fd 	mov	x29, sp
  400200:	f9000bf3 	str	x19, [sp, #16]
  400204:	aa0003f3 	mov	x19, x0
  400208:	39400260 	ldrb	w0, [x19]
  40020c:	35000080 	cbnz	w0, 0x40021c
  400210:	f9400bf3 	ldr	x19, [sp, #16]
  400214:	a8c27bfd 	ldp	x29, x30, [sp], #32
  400218:	d65f03c0 	ret
  40021c:	d2800022 	mov	x2, #0x1                   	// #1
  400220:	aa1303e1 	mov	x1, x19
  400224:	2a0203e0 	mov	w0, w2
  400228:	91000673 	add	x19, x19, #0x1
  40022c:	97ffffbf 	bl	0x400128
  400230:	17fffff6 	b	0x400208

Disassembly of section .rodata:

0000000000400234 <.rodata>:
  400234:	676e6f70 	.inst	0x676e6f70 ; undefined
  400238:	6962000a 	ldpsw	x10, x0, [x0, #-240]
  40023c:	6620646e 	.inst	0x6620646e ; undefined
  400240:	756c6961 	.inst	0x756c6961 ; undefined
  400244:	000a6572 	.inst	0x000a6572 ; undefined
  400248:	646e6962 	.inst	0x646e6962 ; undefined
  40024c:	63757320 	.inst	0x63757320 ; undefined
  400250:	73736563 	.inst	0x73736563 ; undefined
  400254:	6572000a 	fmla	z10.h, p0/m, z0.h, z18.h
  400258:	76696563 	.inst	0x76696563 ; undefined
  40025c:	75732065 	.inst	0x75732065 ; undefined
  400260:	73656363 	.inst	0x73656363 ; undefined
  400264:	74000a73 	.inst	0x74000a73 ; undefined
  400268:	736e6172 	.inst	0x736e6172 ; undefined
  40026c:	2074696d 	.inst	0x2074696d ; undefined
  400270:	6c696166 	ldnp	d6, d24, [x11, #-368]
  400274:	0a657275 	bic	w21, w19, w5, lsr #28
  400278:	61727400 	.inst	0x61727400 ; undefined
  40027c:	696d736e 	ldpsw	x14, x28, [x27, #-152]
  400280:	75732074 	.inst	0x75732074 ; undefined
  400284:	73656363 	.inst	0x73656363 ; undefined
  400288:	72000a73 	ands	w19, w19, #0x7
  40028c:	69656365 	ldpsw	x5, x24, [x27, #-216]
  400290:	66206576 	.inst	0x66206576 ; undefined
  400294:	756c6961 	.inst	0x756c6961 ; undefined
  400298:	000a6572 	.inst	0x000a6572 ; undefined

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

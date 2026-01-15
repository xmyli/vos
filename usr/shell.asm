
usr/shell:     file format elf64-littleaarch64


Disassembly of section .text:

0000000000400000 <.text>:
  400000:	a9ad7bfd 	stp	x29, x30, [sp, #-304]!
  400004:	910003fd 	mov	x29, sp
  400008:	a90153f3 	stp	x19, x20, [sp, #16]
  40000c:	9100c3f4 	add	x20, sp, #0x30
  400010:	f90013f5 	str	x21, [sp, #32]
  400014:	52800480 	mov	w0, #0x24                  	// #36
  400018:	52800013 	mov	w19, #0x0                   	// #0
  40001c:	94000074 	bl	0x4001ec
  400020:	52800400 	mov	w0, #0x20                  	// #32
  400024:	94000072 	bl	0x4001ec
  400028:	94000067 	bl	0x4001c4
  40002c:	12001c01 	and	w1, w0, #0xff
  400030:	7100343f 	cmp	w1, #0xd
  400034:	2a0103f5 	mov	w21, w1
  400038:	54000380 	b.eq	0x4000a8  // b.none
  40003c:	51008022 	sub	w2, w1, #0x20
  400040:	12001c42 	and	w2, w2, #0xff
  400044:	7101785f 	cmp	w2, #0x5e
  400048:	54000128 	b.hi	0x40006c  // b.pmore
  40004c:	7103fa7f 	cmp	w19, #0xfe
  400050:	54fffecc 	b.gt	0x400028
  400054:	94000066 	bl	0x4001ec
  400058:	52800000 	mov	w0, #0x0                   	// #0
  40005c:	94000064 	bl	0x4001ec
  400060:	3833ca95 	strb	w21, [x20, w19, sxtw]
  400064:	11000673 	add	w19, w19, #0x1
  400068:	17fffff0 	b	0x400028
  40006c:	7101fc3f 	cmp	w1, #0x7f
  400070:	54fffdc1 	b.ne	0x400028  // b.any
  400074:	7100027f 	cmp	w19, #0x0
  400078:	54fffd8d 	b.le	0x400028
  40007c:	52800100 	mov	w0, #0x8                   	// #8
  400080:	51000673 	sub	w19, w19, #0x1
  400084:	9400005a 	bl	0x4001ec
  400088:	52800400 	mov	w0, #0x20                  	// #32
  40008c:	94000058 	bl	0x4001ec
  400090:	52800100 	mov	w0, #0x8                   	// #8
  400094:	94000056 	bl	0x4001ec
  400098:	52800000 	mov	w0, #0x0                   	// #0
  40009c:	94000054 	bl	0x4001ec
  4000a0:	3833ca9f 	strb	wzr, [x20, w19, sxtw]
  4000a4:	17ffffe1 	b	0x400028
  4000a8:	52800140 	mov	w0, #0xa                   	// #10
  4000ac:	94000050 	bl	0x4001ec
  4000b0:	52800000 	mov	w0, #0x0                   	// #0
  4000b4:	9400004e 	bl	0x4001ec
  4000b8:	aa1403e0 	mov	x0, x20
  4000bc:	94000061 	bl	0x400240
  4000c0:	d2800000 	mov	x0, #0x0                   	// #0
  4000c4:	6b00027f 	cmp	w19, w0
  4000c8:	54fffa6d 	b.le	0x400014
  4000cc:	38206a9f 	strb	wzr, [x20, x0]
  4000d0:	91000400 	add	x0, x0, #0x1
  4000d4:	17fffffc 	b	0x4000c4
  4000d8:	97ffffca 	bl	0x400000
  4000dc:	d2800028 	mov	x8, #0x1                   	// #1
  4000e0:	d4000001 	svc	#0x0
  4000e4:	d65f03c0 	ret
  4000e8:	d2800048 	mov	x8, #0x2                   	// #2
  4000ec:	d4000001 	svc	#0x0
  4000f0:	d65f03c0 	ret
  4000f4:	d2800068 	mov	x8, #0x3                   	// #3
  4000f8:	d4000001 	svc	#0x0
  4000fc:	d65f03c0 	ret
  400100:	d28000a8 	mov	x8, #0x5                   	// #5
  400104:	d4000001 	svc	#0x0
  400108:	d65f03c0 	ret
  40010c:	d2800088 	mov	x8, #0x4                   	// #4
  400110:	d4000001 	svc	#0x0
  400114:	d65f03c0 	ret
  400118:	d28000c8 	mov	x8, #0x6                   	// #6
  40011c:	d4000001 	svc	#0x0
  400120:	d65f03c0 	ret
  400124:	d2800108 	mov	x8, #0x8                   	// #8
  400128:	d4000001 	svc	#0x0
  40012c:	d65f03c0 	ret
  400130:	d2800128 	mov	x8, #0x9                   	// #9
  400134:	d4000001 	svc	#0x0
  400138:	d65f03c0 	ret
  40013c:	d2800148 	mov	x8, #0xa                   	// #10
  400140:	d4000001 	svc	#0x0
  400144:	d65f03c0 	ret
  400148:	d2800168 	mov	x8, #0xb                   	// #11
  40014c:	d4000001 	svc	#0x0
  400150:	d65f03c0 	ret
  400154:	d2800188 	mov	x8, #0xc                   	// #12
  400158:	d4000001 	svc	#0x0
  40015c:	d65f03c0 	ret
  400160:	d28001a8 	mov	x8, #0xd                   	// #13
  400164:	d4000001 	svc	#0x0
  400168:	d65f03c0 	ret
  40016c:	d28001c8 	mov	x8, #0xe                   	// #14
  400170:	d4000001 	svc	#0x0
  400174:	d65f03c0 	ret
  400178:	d28001e8 	mov	x8, #0xf                   	// #15
  40017c:	d4000001 	svc	#0x0
  400180:	d65f03c0 	ret
  400184:	d2800208 	mov	x8, #0x10                  	// #16
  400188:	d4000001 	svc	#0x0
  40018c:	d65f03c0 	ret
  400190:	d2800228 	mov	x8, #0x11                  	// #17
  400194:	d4000001 	svc	#0x0
  400198:	d65f03c0 	ret
  40019c:	d2800248 	mov	x8, #0x12                  	// #18
  4001a0:	d4000001 	svc	#0x0
  4001a4:	d65f03c0 	ret
  4001a8:	d2800003 	mov	x3, #0x0                   	// #0
  4001ac:	eb03005f 	cmp	x2, x3
  4001b0:	54000041 	b.ne	0x4001b8  // b.any
  4001b4:	d65f03c0 	ret
  4001b8:	38236801 	strb	w1, [x0, x3]
  4001bc:	91000463 	add	x3, x3, #0x1
  4001c0:	17fffffb 	b	0x4001ac
  4001c4:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
  4001c8:	d2800022 	mov	x2, #0x1                   	// #1
  4001cc:	910003fd 	mov	x29, sp
  4001d0:	91007fe1 	add	x1, sp, #0x1f
  4001d4:	52800000 	mov	w0, #0x0                   	// #0
  4001d8:	39007fff 	strb	wzr, [sp, #31]
  4001dc:	97ffffc3 	bl	0x4000e8
  4001e0:	39407fe0 	ldrb	w0, [sp, #31]
  4001e4:	a8c27bfd 	ldp	x29, x30, [sp], #32
  4001e8:	d65f03c0 	ret
  4001ec:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
  4001f0:	d2800022 	mov	x2, #0x1                   	// #1
  4001f4:	910003fd 	mov	x29, sp
  4001f8:	91007fe1 	add	x1, sp, #0x1f
  4001fc:	39007fe0 	strb	w0, [sp, #31]
  400200:	2a0203e0 	mov	w0, w2
  400204:	97ffffbc 	bl	0x4000f4
  400208:	a8c27bfd 	ldp	x29, x30, [sp], #32
  40020c:	d65f03c0 	ret
  400210:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
  400214:	910003fd 	mov	x29, sp
  400218:	f9000bf3 	str	x19, [sp, #16]
  40021c:	aa0003f3 	mov	x19, x0
  400220:	39400260 	ldrb	w0, [x19]
  400224:	35000080 	cbnz	w0, 0x400234
  400228:	f9400bf3 	ldr	x19, [sp, #16]
  40022c:	a8c27bfd 	ldp	x29, x30, [sp], #32
  400230:	d65f03c0 	ret
  400234:	91000673 	add	x19, x19, #0x1
  400238:	97ffffed 	bl	0x4001ec
  40023c:	17fffff9 	b	0x400220
  400240:	d282480c 	mov	x12, #0x1240                	// #4672
  400244:	d2820002 	mov	x2, #0x1000                	// #4096
  400248:	cb2c63ff 	sub	sp, sp, x12
  40024c:	52800001 	mov	w1, #0x0                   	// #0
  400250:	a9007bfd 	stp	x29, x30, [sp]
  400254:	910003fd 	mov	x29, sp
  400258:	a90153f3 	stp	x19, x20, [sp, #16]
  40025c:	aa0003f4 	mov	x20, x0
  400260:	910903e0 	add	x0, sp, #0x240
  400264:	52800013 	mov	w19, #0x0                   	// #0
  400268:	97ffffd0 	bl	0x4001a8
  40026c:	d2800003 	mov	x3, #0x0                   	// #0
  400270:	52800002 	mov	w2, #0x0                   	// #0
  400274:	38636a80 	ldrb	w0, [x20, x3]
  400278:	121a7801 	and	w1, w0, #0xffffffdf
  40027c:	35000561 	cbnz	w1, 0x400328
  400280:	34000062 	cbz	w2, 0x40028c
  400284:	11000673 	add	w19, w19, #0x1
  400288:	52800002 	mov	w2, #0x0                   	// #0
  40028c:	91000463 	add	x3, x3, #0x1
  400290:	f104007f 	cmp	x3, #0x100
  400294:	54ffff01 	b.ne	0x400274  // b.any
  400298:	7100027f 	cmp	w19, #0x0
  40029c:	540006ad 	b.le	0x400370
  4002a0:	910103f4 	add	x20, sp, #0x40
  4002a4:	52800001 	mov	w1, #0x0                   	// #0
  4002a8:	d2804002 	mov	x2, #0x200                 	// #512
  4002ac:	aa1403e0 	mov	x0, x20
  4002b0:	97ffffbe 	bl	0x4001a8
  4002b4:	910903e1 	add	x1, sp, #0x240
  4002b8:	d2800000 	mov	x0, #0x0                   	// #0
  4002bc:	f8207a81 	str	x1, [x20, x0, lsl #3]
  4002c0:	91000400 	add	x0, x0, #0x1
  4002c4:	91010021 	add	x1, x1, #0x40
  4002c8:	6b00027f 	cmp	w19, w0
  4002cc:	54ffff8c 	b.gt	0x4002bc
  4002d0:	9100c3e0 	add	x0, sp, #0x30
  4002d4:	97ffff91 	bl	0x400118
  4002d8:	9100e3e0 	add	x0, sp, #0x38
  4002dc:	97ffff8f 	bl	0x400118
  4002e0:	97ffff88 	bl	0x400100
  4002e4:	35000340 	cbnz	w0, 0x40034c
  4002e8:	97ffff95 	bl	0x40013c
  4002ec:	52800020 	mov	w0, #0x1                   	// #1
  4002f0:	97ffff93 	bl	0x40013c
  4002f4:	b94037e0 	ldr	w0, [sp, #52]
  4002f8:	97ffff91 	bl	0x40013c
  4002fc:	b9403be0 	ldr	w0, [sp, #56]
  400300:	97ffff8f 	bl	0x40013c
  400304:	b94033e0 	ldr	w0, [sp, #48]
  400308:	97ffff90 	bl	0x400148
  40030c:	b9403fe0 	ldr	w0, [sp, #60]
  400310:	97ffff8e 	bl	0x400148
  400314:	aa1403e1 	mov	x1, x20
  400318:	910903e0 	add	x0, sp, #0x240
  40031c:	97ffff7c 	bl	0x40010c
  400320:	52800000 	mov	w0, #0x0                   	// #0
  400324:	97ffff6e 	bl	0x4000dc
  400328:	937a7e61 	sbfiz	x1, x19, #6, #32
  40032c:	d2824804 	mov	x4, #0x1240                	// #4672
  400330:	8b040021 	add	x1, x1, x4
  400334:	8b2163e1 	add	x1, sp, x1
  400338:	8b22c021 	add	x1, x1, w2, sxtw
  40033c:	d1400421 	sub	x1, x1, #0x1, lsl #12
  400340:	11000442 	add	w2, w2, #0x1
  400344:	39000020 	strb	w0, [x1]
  400348:	17ffffd1 	b	0x40028c
  40034c:	b94033e0 	ldr	w0, [sp, #48]
  400350:	97ffff7b 	bl	0x40013c
  400354:	b9403fe0 	ldr	w0, [sp, #60]
  400358:	97ffff79 	bl	0x40013c
  40035c:	52800020 	mov	w0, #0x1                   	// #1
  400360:	3900bfe0 	strb	w0, [sp, #47]
  400364:	3940bfe0 	ldrb	w0, [sp, #47]
  400368:	350000e0 	cbnz	w0, 0x400384
  40036c:	97ffff6e 	bl	0x400124
  400370:	d282480c 	mov	x12, #0x1240                	// #4672
  400374:	a9407bfd 	ldp	x29, x30, [sp]
  400378:	a94153f3 	ldp	x19, x20, [sp, #16]
  40037c:	8b2c63ff 	add	sp, sp, x12
  400380:	d65f03c0 	ret
  400384:	b9403be0 	ldr	w0, [sp, #56]
  400388:	d2800022 	mov	x2, #0x1                   	// #1
  40038c:	9100bfe1 	add	x1, sp, #0x2f
  400390:	97ffff56 	bl	0x4000e8
  400394:	b4fffe80 	cbz	x0, 0x400364
  400398:	d2800022 	mov	x2, #0x1                   	// #1
  40039c:	9100bfe1 	add	x1, sp, #0x2f
  4003a0:	2a0203e0 	mov	w0, w2
  4003a4:	97ffff54 	bl	0x4000f4
  4003a8:	17ffffef 	b	0x400364

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

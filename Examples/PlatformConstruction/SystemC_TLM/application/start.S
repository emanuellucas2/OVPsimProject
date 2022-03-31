/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

// Imperas

	.text
	.org 0x100

#define MAX_SPRS_PER_GRP_BITS 	(11)
#define SPR_GROUP_PIC 		(9 << MAX_SPRS_PER_GRP_BITS)
#define SPR_PICMR 		(SPR_GROUP_PIC + 0)

	.global _start
_start:
	l.addi	r1, r0, 0xfff0
	l.addi	r2, r1, 0x0

	l.mfspr	r3, r0, 17
	l.ori	r3, r3, 0x4
	l.mtspr	r0, r3, 17
// unmask all interrupts
	l.movhi	r4, hi(SPR_PICMR)
	l.addi	r4, r0, lo(SPR_PICMR)
	l.movhi	r5, 0xffff
	l.addi	r5, r5, 0xffff
	l.mtspr	r4, r5, 0
// Jump to main()
	l.jal	_main
	l.nop
// Jump to exit
	l.jal	_exit
	l.nop

// ------------------------------------------------------
// INT HANDLER
//
// NOTE: save 30 registers starting at sp-132 per ABI
// ------------------------------------------------------
    .org 0x800
    l.addi r1, r1, -252
    l.sw   116(r1), r31
    l.sw   112(r1), r30
    l.sw   108(r1), r29
    l.sw   104(r1), r28
    l.sw   100(r1), r27
    l.sw    96(r1), r26
    l.sw    92(r1), r25
    l.sw    88(r1), r24
    l.sw    84(r1), r23
    l.sw    80(r1), r22
    l.sw    76(r1), r21
    l.sw    72(r1), r20
    l.sw    68(r1), r19
    l.sw    64(r1), r18
    l.sw    60(r1), r17
    l.sw    56(r1), r16
    l.sw    52(r1), r15
    l.sw    48(r1), r14
    l.sw    44(r1), r13
    l.sw    40(r1), r12
    l.sw    36(r1), r11
    l.sw    32(r1), r10
    l.sw    28(r1), r9
    l.sw    24(r1), r8
    l.sw    20(r1), r7
    l.sw    16(r1), r6
    l.sw    12(r1), r5
    l.sw     8(r1), r4
    l.sw     4(r1), r3
    l.sw     0(r1), r2
    l.jal  _int_handler
    l.lwz  r31, 116(r1)
    l.lwz  r30, 112(r1)
    l.lwz  r29, 108(r1)
    l.lwz  r28, 104(r1)
    l.lwz  r27, 100(r1)
    l.lwz  r26, 96(r1)
    l.lwz  r25, 92(r1)
    l.lwz  r24, 88(r1)
    l.lwz  r23, 84(r1)
    l.lwz  r22, 80(r1)
    l.lwz  r21, 76(r1)
    l.lwz  r20, 72(r1)
    l.lwz  r19, 68(r1)
    l.lwz  r18, 64(r1)
    l.lwz  r17, 60(r1)
    l.lwz  r16, 56(r1)
    l.lwz  r15, 52(r1)
    l.lwz  r14, 48(r1)
    l.lwz  r13, 44(r1)
    l.lwz  r12, 40(r1)
    l.lwz  r11, 36(r1)
    l.lwz  r10, 32(r1)
    l.lwz  r9,  28(r1)
    l.lwz  r8,  24(r1)
    l.lwz  r7,  20(r1)
    l.lwz  r6,  16(r1)
    l.lwz  r5,  12(r1)
    l.lwz  r4,  8(r1)
    l.lwz  r3,  4(r1)
    l.lwz  r2,  0(r1)
    l.addi r1, r1, 252
    l.nop
    l.rfe

	.org 0xffc
	l.nop

// Loop forever at exit
// If default processor semihost library is loaded this will terminate simulation
	.global _exit
	.global __exit
_exit:
__exit:
	l.j	_exit
	l.nop


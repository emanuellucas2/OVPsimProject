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

// define new instructions not supported by the assembler

#define ldext   0xf7ff0ffc
#define svext   0xf7ff0ffd

        ////////////////////////////////////////////////////////////////////////
.global _start
_start:
        l.ori       r31,r0,0       // r31 = 0 (stack pointer)
        l.ori       r1,r0,0        // zero r1
        l.ori       r2,r0,0        // zero r2

        l.movhi     r1,hi(constData)
        l.ori       r1,r1,lo(constData)
        .word       ldext           // load ext regs with one instruction

        l.movhi     r1,0x8000       // r1 = 0x80000000
        l.movhi     r2,0x1234
        l.ori       r2,r2,0x5678    // r2 contains a new constant
        l.sw        0(r1),r2        // write to *0x80000000 (memory mapped ext reg[0])

        l.ori       r1,r0,0
        l.movhi     r1,0x9000
        .word       svext           // save ext regs to 0x90000000 with one instruction
        l.nop
        l.bf        exit

.global exit
exit:   l.nop
        l.bf        exit

.org 0xF00

constData:
        .word       0
        .word       7
        .word       14
        .word       21
        .word       28
        .word       35
        .word       42
        .word       49
        .word       56
        .word       63
        .word       70
        .word       77
        .word       84
        .word       91
        .word       98
        .word       105


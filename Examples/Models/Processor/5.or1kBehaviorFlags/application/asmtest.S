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

.global _start
_start:                             // TEST PROLOGUE
        l.addi      r1,r0,0         // r1 = 0
        l.addi      r2,r0,1         // r2 = 1
        l.addi      r3,r0,-1        // r3 = -1
        l.addi      r4,r0,0x800     // r4 = 0x00000800
        l.muli      r4,r4,0x800     // r4 = 0x00400000
        l.muli      r4,r4,0x200     // r4 = 0x80000000
        l.addi      r5,r4,-1        // r5 = 0x7fffffff

        l.addic     r20,r0,-1
        l.addic     r20,r0,0
        l.addic     r20,r0,1
        l.addic     r20,r1,-1
        l.addic     r20,r1,0
        l.addic     r20,r1,1
        l.addic     r20,r2,-1
        l.addic     r20,r2,0
        l.addic     r20,r2,1
        l.addic     r20,r3,-1
        l.addic     r20,r3,0
        l.addic     r20,r3,1
        l.addic     r20,r4,-1
        l.addic     r20,r4,0
        l.addic     r20,r4,1
        l.addic     r20,r5,-1
        l.addic     r20,r5,0
        l.addic     r20,r5,1

        l.addic     r0,r0,-1
        l.addic     r0,r0,0
        l.addic     r0,r0,1
        l.addic     r0,r1,-1
        l.addic     r0,r1,0
        l.addic     r0,r1,1
        l.addic     r0,r2,-1
        l.addic     r0,r2,0
        l.addic     r0,r2,1
        l.addic     r0,r3,-1
        l.addic     r0,r3,0
        l.addic     r0,r3,1
        l.addic     r0,r4,-1
        l.addic     r0,r4,0
        l.addic     r0,r4,1
        l.addic     r0,r5,-1
        l.addic     r0,r5,0
        l.addic     r0,r5,1

.global exit
exit:
		l.addi		r1,r2,0


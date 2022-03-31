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
        l.addi      r5,r0,0x55      // r5 = 0x55

        l.nop
        l.lwz       r3,0(r4)        // load 0x00400000 to r3
        l.nop
        l.sw        0(r4),r5        // store 0x55 to 0x00400000
        l.nop

        l.addi      r4,r4,0x100     // r4 = 0x00400100
        l.nop
        l.lwz       r3,0(r4)        // load 0x00400000 to r3
        l.nop
        l.sw        0(r4),r5        // store 0x55 to 0x00400000
        l.nop

        l.addi      r4,r4,0x100     // r4 = 0x00400200
        l.nop
        l.lwz       r3,0(r4)        // load 0x00400000 to r3
        l.nop
        l.sw        0(r4),r5        // store 0x55 to 0x00400000
        l.nop

// intercept with or1kNewlib semihost
.global __exit
__exit:
        l.addi      r1,r0,0


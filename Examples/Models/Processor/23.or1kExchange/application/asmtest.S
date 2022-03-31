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

        ////////////////////////////////////////////////////////////////////////
        // MAIN ROUTINE
        ////////////////////////////////////////////////////////////////////////
.global _start
_start:
        l.addi      r31,r0,0        // initialize stack pointer to 0
        l.addi      r1,r0,0x100     // r1 = 0x100
        l.sw        -4(r31),r1      // save r1 value on stack
        l.addi      r1,r0,0x200     // r1 = 0x200
        .word       0xf7ff0ffc      // exch r1,-4(r31)
        l.lwz       r2,-4(r31)      // get current value of -4(r31)
        l.addi      r1,r0,0x300     // r1 = 0x300
        .word       0xf7ff0ffc      // exch r1,-4(r31)
        l.lwz       r2,-4(r31)      // get current value of -4(r31)

        ////////////////////////////////////////////////////////////////////////
        // EXIT FROM POINT TEST
        ////////////////////////////////////////////////////////////////////////
.global exit
exit:
        l.nop

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

.org 0x100

        ////////////////////////////////////////////////////////////////////////
        // RESET HANDLER (AT 0x100)
        ////////////////////////////////////////////////////////////////////////
        l.j         _start          // jump to start address
        l.addi      r30,r30,1       // increment count of external exceptions

.org 0x800

        ////////////////////////////////////////////////////////////////////////
        // EXTERNAL INTERRUPT HANDLER (AT 0x800)
        ////////////////////////////////////////////////////////////////////////
        l.addi      r30,r30,1       // increment count of external exceptions
        l.rfe                       // return from exception

.org 0x10000

        ////////////////////////////////////////////////////////////////////////
        // APPLICATION CODE (AT 0x10000)
        ////////////////////////////////////////////////////////////////////////

.global _start
_start:
        l.ori       r30,r0,0        // r30 = 0 (counts timer exceptions)
        l.addi      r1,r0,-1        // r1 = -1
        l.mtspr     r0,r1,0x4800    // set picmr from r1 (enables interrupts)
        l.ori       r1,r0,6         // r1 = SR_IEE|SR_TEE, user mode
        l.mtspr     r0,r1,0x11      // set sr from r1 (enables interrupts)

        l.ori       r1,r0,4         // r1 = 4 (loop count)
loop1:
        l.addi      r1,r1,-1        // decrement r1
        l.sfeqi     r1,0            // r1==0?
        l.bnf       loop1           // go if not
        l.nop                       // (delay slot)

.global exit
exit:
        l.nop

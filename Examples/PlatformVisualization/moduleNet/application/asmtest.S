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

.global resetVector
.org 0x0
        ////////////////////////////////////////////////////////////////////////
        // RESET CODE (AT 0x0)
        ////////////////////////////////////////////////////////////////////////
resetVector:
        l.addi r2,r0,0x1000         // set r2 0x1000 (_start)
        l.jr r2                     // jump
        l.nop

.global interruptVector
.org 0x800
        ////////////////////////////////////////////////////////////////////////
        // EXTERNAL INTERRUPT HANDLER (AT 0x800)
        ////////////////////////////////////////////////////////////////////////
interruptVector:
        l.movhi    r3,hi(25000000)  // this is the loop count - loop should take one simulated second (25M x 4 instructions)
    1:  l.addi     r3,r3,-1
        l.sfgesi   r3,0
        l.bf       1b
        l.nop
        //
        l.addi r30,r30,1            // increment count of external exceptions
        l.addi r2,r0,0xe000         // set r2
        l.slli r2,r2,16             // shift to 0xe0000000
        l.sw   0(r2),r30            // write interrupt Achnowledge register
        l.rfe                       // return from exception

.org 0x1000
        ////////////////////////////////////////////////////////////////////////
        // APPLICATION CODE (AT 0x10000)
        ////////////////////////////////////////////////////////////////////////
.global _start
_start:
        l.ori       r30,r0,0        // r30 = 0 (counts timer exceptions)
        l.ori       r1,r0,7         // r1 = 7 (SR_IEE | SR_TEE | SR_SM)
        l.mtspr     r0,r1,0x11      // set sr from r1 (enables interrupts)
        l.addi      r1,r0,-1        // r1 = -1
        l.mtspr     r0,r1,0x4800    // set picmr from r1 (enables interrupts)

        l.ori       r1,r0,8         // r1 = 8 (loop count)
loop1:
        l.sfeq      r1,r30          // r1==r30?
        l.bnf       loop1           // go if not
        l.nop                       // (delay slot)
        l.addi r2,r0,0x1000         // set r2 0x1000 (_start)
        l.jr r2                     // jump
        l.nop

.global __exit
__exit:
        l.nop

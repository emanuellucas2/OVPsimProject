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
        // KERNEL START CODE (AT 0x0)
        ////////////////////////////////////////////////////////////////////////
.global _start
_start:
        l.ori       r31,r0,0        // r31 = 0 (stack pointer)

        // prepare to copy application to user space 
        l.movhi     r1,0x8000       // r1 = 0x80000000
        l.movhi     r2,hi(appStart) // r2 = appStart
        l.ori       r2,r2,lo(appStart)
        l.movhi     r3,hi(appEnd)   // r3 = appEnd
        l.ori       r3,r3,lo(appEnd)

        // copy application to user space
loop:   l.lwz       r4,0(r2)        // r4 = word of application code
        l.sw        0(r1),r4        // copy to 0x80000000
        l.addi      r2,r2,4         // increment src pointer
        l.addi      r1,r1,4         // increment dst pointer
        l.sfne      r2,r3           // r2!=r3?
        l.bf        loop            // go if true
        l.nop                       // (delay slot instruction)

        // run user code
        l.mtspr     r0,r0,0x40      // clear esr
        l.mtspr     r0,r0,0x20      // clear epc (resume address in user space)
        l.rfe                       // return from exception (runs user code)

.org 0x300
        ////////////////////////////////////////////////////////////////////////
        // DATA PRIVILEGE EXCEPTION VECTOR (AT 0x300) - SKIP INSTRUCTION
        ////////////////////////////////////////////////////////////////////////
        l.mfspr     r1,r0,0x20      // get epc in r1
        l.addi      r1,r1,4         // increment address to skip faulting insn
        l.mtspr     r0,r1,0x20      // set epc
        l.rfe                       // return from exception

.org 0x400
        ////////////////////////////////////////////////////////////////////////
        // CODE PRIVILEGE EXCEPTION VECTOR (AT 0x400) - RESUME AT LINK ADDRESS
        ////////////////////////////////////////////////////////////////////////
        l.mtspr     r0,r9,0x20      // set epc from link register (r9)
        l.rfe                       // return from exception

.org 0xc00
        ////////////////////////////////////////////////////////////////////////
        // SYSCALL VECTOR (AT 0xc00) - TERMINATE PROGRAM
        ////////////////////////////////////////////////////////////////////////
        l.movhi     r1,0x9000       // r1 = 0x90000000
        l.lwz       r3,0(r1)        // load r3 from address 0x90000000
.global exit
exit:   l.nop

        ////////////////////////////////////////////////////////////////////////
        // USER APPLICATION (IN KERNEL MEMORY)
        ////////////////////////////////////////////////////////////////////////
appStart:
        l.movhi     r1,0xf000       // r1 = 0xf0000000
        l.ori       r2,r0,0x1234    // r2 = 0x00001234
        l.sw        0(r1),r2        // legal store to 0xf0000000
        l.sw        0(r0),r2        // attempt ILLEGAL store to 0x00000000
        l.movhi     r1,0xf000       // r1 = 0xf0000000
        l.jalr      r1              // attempt ILLEGAL jump to 0xf0000000
        l.nop                       // (delay slot instruction)
        l.sys       0               // exit program
appEnd:


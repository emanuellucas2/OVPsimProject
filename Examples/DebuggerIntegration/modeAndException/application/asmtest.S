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

.org 0x700
        ////////////////////////////////////////////////////////////////////////
        // ILLEGAL INSTRUCTION EXCEPTION HANDLER (AT 0x700)
        ////////////////////////////////////////////////////////////////////////
        l.addi      r30,r30,1       // increment count of illegal instructions
        l.sw        -4(r31),r1      // save value in r1
        l.mfspr     r1,r0,0x20      // get epc in r1
        l.addi      r1,r1,4         // move epc past faulting instruction
        l.mtspr     r0,r1,0x20      // set epc from r1
        l.lwz       r1,-4(r31)      // restore original r1
        l.rfe                       // return from exception

.org 0x10000
        ////////////////////////////////////////////////////////////////////////
        // APPLICATION CODE (AT 0x10000)
        ////////////////////////////////////////////////////////////////////////
.global _start
_start:
        l.ori       r30,r0,0        // r30 = 0 (counts illegal instructions)
        l.ori       r31,r0,0        // r31 = 0 (stack pointer)
        l.mtspr     r0,r0,0x20      // clear epc

        ////////////////////////////////////////////////////////////////////////
        // SUPERVISOR MODE LOOP TEST
        ////////////////////////////////////////////////////////////////////////
        l.ori       r1,r0,2         // r1 = 2 (loop count)
loop1:
        l.mfspr     r2,r0,0x20      // get epc in r2
        l.addi      r2,r2,1         // increment r2
        l.mtspr     r0,r2,0x20      // set epc from r2
        l.addi      r1,r1,-1        // decrement r1
        l.sfeqi     r1,0            // r1==0?
        l.bnf       loop1           // go if not
        l.nop                       // (delay slot)

        ////////////////////////////////////////////////////////////////////////
        // SUPERVISOR MODE FUNCTION CALL TEST
        ////////////////////////////////////////////////////////////////////////
        l.jal       incEPC          // incEPC (in supervisor mode)
        l.nop                       // (delay slot)
        l.mtspr     r0,r0,0x11      // clear supervisor mode

        ////////////////////////////////////////////////////////////////////////
        // USER MODE FUNCTION CALL TEST
        ////////////////////////////////////////////////////////////////////////
        l.jal       incEPC          // incEPC (in user mode)
        l.nop                       // (delay slot)
        l.rfe                       // *ILLEGAL* return from exception

.global exit    // imperasExit semihost library intercepts exit
exit:
.global __exit  // or1k semihost library intercepts __exit
__exit:
        l.nop

        ////////////////////////////////////////////////////////////////////////
        // FUNCTION CALLED IN BOTH USER AND SUPERVISOR MODE
        ////////////////////////////////////////////////////////////////////////
incEPC:
        l.mfspr     r2,r0,0x20      // get epc in r2
        l.addi      r2,r2,1         // increment r2
        l.mtspr     r0,r2,0x20      // set epc from r2
        l.jr        r9              // return
        l.nop                       // (delay slot)

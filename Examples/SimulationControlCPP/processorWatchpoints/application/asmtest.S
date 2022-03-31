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

.org 0x200
        ////////////////////////////////////////////////////////////////////////
        // ALIGNMENT EXCEPTION HANDLER (AT 0x200)
        ////////////////////////////////////////////////////////////////////////
        l.addi      r30,r30,1       // increment count of alignment exceptions
        l.addi      r1,r1,1         // increment store address
        l.rfe                       // return from exception

.org 0x10000
        ////////////////////////////////////////////////////////////////////////
        // APPLICATION CODE (AT 0x10000)
        ////////////////////////////////////////////////////////////////////////
.global _start
_start:
        l.ori       r30,r0,0        // r30 = 0 (counts alignment exceptions)
        l.movhi     r1,0x8000       // r1 = 0x80000000
        l.ori       r1,r1,0x0001    // r1 = 0x80000001
        l.movhi     r2,0x1234       // r2 = 0x12340000
        l.ori       r2,r2,0x5678    // r2 = 0x12345678

        ////////////////////////////////////////////////////////////////////////
        // Memory exception
        ////////////////////////////////////////////////////////////////////////
        l.sh        0(r1),r2	    // do two-byte store
        
        ////////////////////////////////////////////////////////////////////////
        // Arithmetic exception
        ////////////////////////////////////////////////////////////////////////
        l.div       r30,r30,r0      // divide by zero

        l.ori       r30,r0,0        // r30 = 0
        l.ori       r31,r0,0        // r31 = 0 (stack pointer)
        l.mtspr     r0,r0,0x20      // clear epc
        
        ////////////////////////////////////////////////////////////////////////
        // SUPERVISOR MODE
        ////////////////////////////////////////////////////////////////////////
        l.mtspr     r0,r0,0x11      // clear supervisor mode

        ////////////////////////////////////////////////////////////////////////
        // Register change
        ////////////////////////////////////////////////////////////////////////
        l.movhi     r8,0x8000       // r8 = 0x80000000
        l.nop

        ////////////////////////////////////////////////////////////////////////
        // Register change
        ////////////////////////////////////////////////////////////////////////
        l.movhi     r8,0x0000       // r8 = 0x00000000
        l.nop

.global exit
exit:

        l.j exit
        l.nop



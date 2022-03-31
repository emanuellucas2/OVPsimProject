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
        l.jal       fib             // calculate fib(15)
        l.addi      r1,r0,15        // r1 = 15 (delay slot)

        ////////////////////////////////////////////////////////////////////////
        // EXIT FROM POINT TEST
        ////////////////////////////////////////////////////////////////////////
.global exit
exit:
        l.nop

        ////////////////////////////////////////////////////////////////////////
        // FUNCTION fib - calculate fibonnacci number of N, passed in r1.
        //                result is returned in r1, r2 is destroyed
        ////////////////////////////////////////////////////////////////////////
fib:    l.sflesi    r1,1            // r1<=1? (signed)
        l.bf        done            // done if so, result is r1
        l.nop                       // (delay slot)

        l.addi      r31,r31,-12     // create stack frame
        l.sw        0(r31),r9       // save link register
        l.sw        4(r31),r1       // save input r1

        l.jal       fib             // calculate fib(N-1)
        l.addi      r1,r1,-1        // r1 = N-1 (delay slot)
        l.sw        8(r31),r1       // save fib(N-1)

        l.lwz       r1,4(r31)       // restore initial N
        l.jal       fib             // calculate fib(N-2)
        l.addi      r1,r1,-2        // r1 = N-2 (delay slot)

        l.lwz       r2,8(r31)       // restore fib(N-1)
        l.add       r1,r1,r2        // r1 = fib(N-2) + fib(N-1)

        l.lwz       r9,0(r31)       // restore link register
        l.addi      r31,r31,12      // destroy stack frame

done:   l.jr        r9              // return, result in r1
        l.nop                       // (delay slot instruction)

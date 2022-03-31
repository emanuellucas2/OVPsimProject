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
        l.addi      r1,r0,0         // r1 = 0 (counts taken jumps)
        l.addi      r2,r0,0         // r2 = 0 (counts untaken jumps)
        l.jal       func1           // call func1
        l.addi      r1,r1,1         // increment r1 (delay slot instruction)
        l.jalr      r10             // call indirect using r10 (i.e. r10_addr)
        l.addi      r1,r1,1         // increment r1 (delay slot instruction)

        ////////////////////////////////////////////////////////////////////////
        // EXIT FROM POINT TEST
        ////////////////////////////////////////////////////////////////////////
.global exit
exit:
        l.addi      r1,r1,0

        ////////////////////////////////////////////////////////////////////////
        // FUNCTION func1
        ////////////////////////////////////////////////////////////////////////
func1:
        l.j         forward         // jump forward in this function
        l.addi      r1,r1,1         // increment r1 (delay slot instruction)
        l.addi      r2,r2,1         // ** not executed **
forward:
        l.addi      r8,r9,0         // save return address in r8
        l.jal       func2           // call func2
        l.addi      r1,r1,1         // increment r1 (delay slot instruction)
        l.addi      r9,r8,0         // restore return address from r8
r10_addr:
        l.jr        r9              // return from function
        l.addi      r1,r1,1         // increment r1 (delay slot instruction)
        l.addi      r2,r2,1         // ** not executed **

        ////////////////////////////////////////////////////////////////////////
        // FUNCTION func2
        ////////////////////////////////////////////////////////////////////////
func2:
        l.addi      r10,r9,4        // save return address+4 in r10
        l.jr        r9              // return from function
        l.addi      r1,r1,1         // increment r1 (delay slot instruction)
        l.addi      r2,r2,1         // ** not executed **

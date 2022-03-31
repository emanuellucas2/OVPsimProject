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
        // test1: r1=3, r2=2
        l.addi      r1,r0,3         // r1=3
        l.addi      r2,r0,2         // r2=2
        l.jal       test            // call test
        l.nop                       // (delay slot instruction)
        l.addi      r3,r29,0        // move bf taken mask to r3
        l.addi      r4,r30,0        // move bnf taken mask to r4

        // test2: r1=3, r2=3
        l.addi      r1,r0,3         // r1=3
        l.addi      r2,r0,3         // r2=3
        l.jal       test            // call test
        l.nop                       // (delay slot instruction)
        l.addi      r5,r29,0        // move bf taken mask to r5
        l.addi      r6,r30,0        // move bnf taken mask to r6

        // test3: r1=3, r2=4
        l.addi      r1,r0,3         // r1=3
        l.addi      r2,r0,4         // r2=4
        l.jal       test            // call test
        l.nop                       // (delay slot instruction)
        l.addi      r7,r29,0        // move bf taken mask to r7
        l.addi      r8,r30,0        // move bnf taken mask to r8

        // test4: r1=-3, r2=-2
        l.addi      r1,r0,-3        // r1=-3
        l.addi      r2,r0,-2        // r2=-2
        l.jal       test            // call test
        l.nop                       // (delay slot instruction)
        l.addi      r10,r29,0       // move bf taken mask to r10
        l.addi      r11,r30,0       // move bnf taken mask to r11

        // test5: r1=-3, r2=-3
        l.addi      r1,r0,-3        // r1=-3
        l.addi      r2,r0,-3        // r2=-3
        l.jal       test            // call test
        l.nop                       // (delay slot instruction)
        l.addi      r12,r29,0       // move bf taken mask to r12
        l.addi      r13,r30,0       // move bnf taken mask to r13

        // test6: r1=-3, r2=-4
        l.addi      r1,r0,-3        // r1=-3
        l.addi      r2,r0,-4        // r2=-4
        l.jal       test            // call test
        l.nop                       // (delay slot instruction)
        l.addi      r14,r29,0       // move bf taken mask to r14
        l.addi      r15,r30,0       // move bnf taken mask to r15

        ////////////////////////////////////////////////////////////////////////
        // EXIT FROM POINT TEST
        ////////////////////////////////////////////////////////////////////////
.global exit
exit:
        l.nop

        ////////////////////////////////////////////////////////////////////////
        // FUNCTION test
        ////////////////////////////////////////////////////////////////////////
test:   l.addi      r29,r0,0        // clear output mask r29 (bf taken)
        l.addi      r30,r0,1        // clear output mask r30 (bnf taken)
        l.addi      r31,r0,1        // initialize bitmask

        // test for sfeq
        l.sfeq      r1,r2           // r1==r2?
        l.bf        sfeqF           // go if true
        l.xor       r29,r29,r31     // add mask (delay slot instruction)
        l.xor       r29,r29,r31     // remove mask
sfeqF:  l.bnf       sfeqNF          // go if false
        l.xor       r30,r30,r31     // add mask (delay slot instruction)
        l.xor       r30,r30,r31     // remove mask
sfeqNF: l.add       r31,r31,r31     // shift mask

        // test for sfne
        l.sfne      r1,r2           // r1!=r2?
        l.bf        sfneF           // go if true
        l.xor       r29,r29,r31     // add mask (delay slot instruction)
        l.xor       r29,r29,r31     // remove mask
sfneF:  l.bnf       sfneNF          // go if false
        l.xor       r30,r30,r31     // add mask (delay slot instruction)
        l.xor       r30,r30,r31     // remove mask
sfneNF: l.add       r31,r31,r31     // shift mask

        // test for sfgtu
        l.sfgtu     r1,r2           // r1>r2? (unsigned)
        l.bf        sfgtuF          // go if true
        l.xor       r29,r29,r31     // add mask (delay slot instruction)
        l.xor       r29,r29,r31     // remove mask
sfgtuF: l.bnf       sfgtuNF         // go if false
        l.xor       r30,r30,r31     // add mask (delay slot instruction)
        l.xor       r30,r30,r31     // remove mask
sfgtuNF:l.add       r31,r31,r31     // shift mask

        // test for sfgeu
        l.sfgeu     r1,r2           // r1>=r2? (unsigned)
        l.bf        sfgeuF          // go if true
        l.xor       r29,r29,r31     // add mask (delay slot instruction)
        l.xor       r29,r29,r31     // remove mask
sfgeuF: l.bnf       sfgeuNF         // go if false
        l.xor       r30,r30,r31     // add mask (delay slot instruction)
        l.xor       r30,r30,r31     // remove mask
sfgeuNF:l.add       r31,r31,r31     // shift mask

        // test for sfltu
        l.sfltu     r1,r2           // r1<r2? (unsigned)
        l.bf        sfltuF          // go if true
        l.xor       r29,r29,r31     // add mask (delay slot instruction)
        l.xor       r29,r29,r31     // remove mask
sfltuF: l.bnf       sfltuNF         // go if false
        l.xor       r30,r30,r31     // add mask (delay slot instruction)
        l.xor       r30,r30,r31     // remove mask
sfltuNF:l.add       r31,r31,r31     // shift mask

        // test for sfleu
        l.sfleu     r1,r2           // r1<=r2? (unsigned)
        l.bf        sfleuF          // go if true
        l.xor       r29,r29,r31     // add mask (delay slot instruction)
        l.xor       r29,r29,r31     // remove mask
sfleuF: l.bnf       sfleuNF         // go if false
        l.xor       r30,r30,r31     // add mask (delay slot instruction)
        l.xor       r30,r30,r31     // remove mask
sfleuNF:l.add       r31,r31,r31     // shift mask

        // test for sfgts
        l.sfgts     r1,r2           // r1>r2? (signed)
        l.bf        sfgtsF          // go if true
        l.xor       r29,r29,r31     // add mask (delay slot instruction)
        l.xor       r29,r29,r31     // remove mask
sfgtsF: l.bnf       sfgtsNF         // go if false
        l.xor       r30,r30,r31     // add mask (delay slot instruction)
        l.xor       r30,r30,r31     // remove mask
sfgtsNF:l.add       r31,r31,r31     // shift mask

        // test for sfges
        l.sfges     r1,r2           // r1>=r2? (signed)
        l.bf        sfgesF          // go if true
        l.xor       r29,r29,r31     // add mask (delay slot instruction)
        l.xor       r29,r29,r31     // remove mask
sfgesF: l.bnf       sfgesNF         // go if false
        l.xor       r30,r30,r31     // add mask (delay slot instruction)
        l.xor       r30,r30,r31     // remove mask
sfgesNF:l.add       r31,r31,r31     // shift mask

        // test for sflts
        l.sflts     r1,r2           // r1<r2? (signed)
        l.bf        sfltsF          // go if true
        l.xor       r29,r29,r31     // add mask (delay slot instruction)
        l.xor       r29,r29,r31     // remove mask
sfltsF: l.bnf       sfltsNF         // go if false
        l.xor       r30,r30,r31     // add mask (delay slot instruction)
        l.xor       r30,r30,r31     // remove mask
sfltsNF:l.add       r31,r31,r31     // shift mask

        // test for sfles
        l.sfles     r1,r2           // r1<=r2? (signed)
        l.bf        sflesF          // go if true
        l.xor       r29,r29,r31     // add mask (delay slot instruction)
        l.xor       r29,r29,r31     // remove mask
sflesF: l.bnf       sflesNF         // go if false
        l.xor       r30,r30,r31     // add mask (delay slot instruction)
        l.xor       r30,r30,r31     // remove mask
sflesNF:l.add       r31,r31,r31     // shift mask

        l.jr        r9              // return, results in r29 and r30
        l.nop                       // (delay slot instruction)


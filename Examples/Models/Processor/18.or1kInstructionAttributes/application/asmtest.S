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

.org 0xc00

        ////////////////////////////////////////////////////////////////////////
        // SYS HANDLER (AT 0xc00)
        ////////////////////////////////////////////////////////////////////////

        l.rfe                       // return from exception

.org 0x10000
.global _start
_start:

        ////////////////////////////////////////////////////////////////////////
        // MOVHI INSTRUCTION TEST
        ////////////////////////////////////////////////////////////////////////

        l.movhi     r1,0x1234

        ////////////////////////////////////////////////////////////////////////
        // ARITHMETIC INSTRUCTION TESTS (SECOND ARGUMENT CONSTANT)
        ////////////////////////////////////////////////////////////////////////

        l.addi      r1,r2,1
        l.addic     r3,r4,2
        l.andi      r5,r6,1
        l.ori       r7,r8,1
        l.xori      r9,r10,1
        l.muli      r11,r12,1

        ////////////////////////////////////////////////////////////////////////
        // ARITHMETIC INSTRUCTION TESTS (SECOND ARGUMENT REGISTER)
        ////////////////////////////////////////////////////////////////////////

        l.add       r1,r2,r3
        l.addc      r3,r4,r5
        l.sub       r13,r14,r15
        l.and       r5,r6,r7
        l.or        r7,r8,r9
        l.xor       r9,r10,r11
        l.mul       r11,r12,r13
        l.addi      r1,r0,5
        l.addi      r2,r0,-7
        l.div       r3,r2,r1
        l.divu      r3,r2,r1

        ////////////////////////////////////////////////////////////////////////
        // SHIFT/ROTATE INSTRUCTION TESTS (SECOND ARGUMENT CONSTANT)
        ////////////////////////////////////////////////////////////////////////

        l.slli      r1,r2,1
        l.srli      r3,r4,2
        l.srai      r5,r6,3
        l.rori      r7,r8,4

        ////////////////////////////////////////////////////////////////////////
        // SHIFT/ROTATE INSTRUCTION TESTS (SECOND ARGUMENT REGISTER)
        ////////////////////////////////////////////////////////////////////////

        l.sll       r1,r2,r3
        l.srl       r3,r4,r5
        l.sra       r5,r6,r7
        l.ror       r7,r8,r7

        ////////////////////////////////////////////////////////////////////////
        // BRANCH INSTRUCTION TESTS
        ////////////////////////////////////////////////////////////////////////

        l.sfeqi     r1,0            // r1==0?
        l.bnf       1f              // go if condition false
        l.addi      r1,r1,0x12      // (delay slot)
        l.nop                       // (not executed)
1:      l.bf        1f              // go if condition true
        l.addi      r1,r1,0x12      // (delay slot)
        l.nop
1:      l.j         1f
        l.addi      r1,r1,0x12      // (delay slot)
        l.nop                       // (not executed)
1:      l.jal       1f
        l.addi      r1,r1,0x12      // (delay slot)
        l.nop                       // (not executed)
1:      l.movhi     r1,   hi(fwd1)  // r1 = fwd1 (high)
        l.ori       r1,r1,lo(fwd1)  // r1 = fwd1
        l.jr        r1
        l.addi      r1,r1,0x12      // (delay slot)
        l.nop                       // (not executed)
fwd1:   l.movhi     r1,   hi(fwd2)  // r1 = fwd2 (high)
        l.ori       r1,r1,lo(fwd2)  // r1 = fwd2
        l.jalr      r1
        l.addi      r1,r1,0x12      // (delay slot)
        l.nop                       // (not executed)
fwd2:

        ////////////////////////////////////////////////////////////////////////
        // SYS AND RFE INSTRUCTION TESTS
        ////////////////////////////////////////////////////////////////////////

        l.sys       0x1234

        ////////////////////////////////////////////////////////////////////////
        // SYSTEM REGISTER INSTRUCTION TESTS
        ////////////////////////////////////////////////////////////////////////

        l.mfspr     r2,r0,0x20      // get epc in r2
        l.addi      r2,r0,-1        // r2 = -1
        l.mtspr     r0,r2,0x20      // set epc from r2

        ////////////////////////////////////////////////////////////////////////
        // LOAD/STORE INSTRUCTION TESTS
        ////////////////////////////////////////////////////////////////////////

        l.movhi     r1,   hi(data)  // r1 = data (high)
        l.ori       r1,r1,lo(data)  // r1 = data
        l.lwz       r3,4(r1)
        l.lhz       r3,6(r1)
        l.lbz       r3,7(r1)
        l.lws       r3,4(r1)
        l.lhs       r3,6(r1)
        l.lbs       r3,7(r1)
        l.sw        0(r1),r3
        l.sh        2(r1),r3
        l.sb        3(r1),r3

        ////////////////////////////////////////////////////////////////////////
        // COMPARISON INSTRUCTION TESTS
        ////////////////////////////////////////////////////////////////////////

        l.sfeqi     r1,0
        l.sfeq      r1,r2

        ////////////////////////////////////////////////////////////////////////
        // NOP INSTRUCTION TEST
        ////////////////////////////////////////////////////////////////////////

        l.nop

.global exit
exit:
        l.nop

data:
        .word 0x12345678
        .word 0x89abcdef

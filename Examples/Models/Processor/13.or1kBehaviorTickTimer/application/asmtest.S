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

.org 0x500
        ////////////////////////////////////////////////////////////////////////
        // TICK TIMER EXCEPTION HANDLER (AT 0x500)
        ////////////////////////////////////////////////////////////////////////
        l.addi      r30,r30,1       // increment count of timer exceptions
        l.sw        -4(r31),r1      // save value in r1
        l.sw        -8(r31),r2      // save value in r2
        l.mfspr     r1,r0,0x5000    // get ttmr in r1
        l.movhi     r2,0xefff       // r2 hi = ~TTMR_IP mask
        l.ori       r2,r2,0xffff    // r1 lo = ~TTMR_IP mask
        l.and       r1,r1,r2        // clear TTMR_IP
        l.mtspr     r0,r1,0x5000    // set ttmr from r1
        l.lwz       r1,-4(r31)      // restore original r1
        l.lwz       r2,-8(r31)      // restore original r2
        l.sfeqi     r30,3           // r30==3?
        l.bf        noReset         // go if so
        l.nop                       // (delay slot)
        l.mtspr     r0,r0,0x5100    // clear ttcr (restarts counter)
noReset:l.rfe                       // return from exception

.org 0xc00
        ////////////////////////////////////////////////////////////////////////
        // SYSCALL VECTOR (AT 0xc00)
        ////////////////////////////////////////////////////////////////////////
        l.mtspr     r0,r1,0x5000    // set ttmr from r1
        l.rfe                       // return from exception

.org 0x10000
        ////////////////////////////////////////////////////////////////////////
        // APPLICATION CODE (AT 0x10000)
        ////////////////////////////////////////////////////////////////////////
.global _start
_start:
        l.ori       r30,r0,0        // r30 = 0 (counts timer exceptions)
        l.ori       r31,r0,0        // r31 = 0 (stack pointer)

        l.ori       r1,r0,7         // r1 = 7 (SR_IEE | SR_TEE | SR_SM)
        l.mtspr     r0,r1,0x11      // set sr from r1 (enables interrupts)
        l.movhi     r1,0xa000       // M=ONCE,IE=True
        l.ori       r1,r1,8         // TP=8 (count to match)
        l.sys       0
        l.mtspr     r0,r0,0x5100    // clear ttcr (starts counter)

        ////////////////////////////////////////////////////////////////////////
        // TEST INTERRUPT WITH MODE ONCE
        ////////////////////////////////////////////////////////////////////////
        l.ori       r1,r0,8         // r1 = 8 (loop count)
loop1:
        l.addi      r1,r1,-1        // decrement r1
        l.sfeqi     r1,0            // r1==0?
        l.bnf       loop1           // go if not
        l.nop                       // (delay slot)

.global exit
exit:
        l.nop

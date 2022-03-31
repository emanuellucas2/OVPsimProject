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

#define TLB_SIZE  4
#define PAGE_SIZE 4096

        ////////////////////////////////////////////////////////////////////////
        // KERNEL START CODE (AT 0x0)
        ////////////////////////////////////////////////////////////////////////
.global _start
_start:
        l.ori       r31,r0,0        // r31 = 0 (stack pointer)
        l.ori       r30,r0,0        // r30 = 0 (TLB miss count)

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
        // DATA PRIVILEGE EXCEPTION VECTOR (AT 0x300) - UPDATE TLB
        ////////////////////////////////////////////////////////////////////////
        l.sw        -4(r31),r1      // save r1
        l.sw        -8(r31),r2      // save r2
        l.sw        -12(r31),r3     // save r3
        l.sw        -16(r31),r4     // save r4
        l.sw        -20(r31),r5     // save r5
        l.sw        -24(r31),r6     // save r6
        l.sw        -28(r31),r7     // save r7

        l.addi      r30,r30,1       // increment TLB miss count

        l.mfspr     r2,r0,0x30      // r2 = eear
        l.addi      r1,r0,-PAGE_SIZE// r1 = page mask
        l.and       r2,r2,r1        // mask faulting va to page size
        l.movhi     r4,0x0001       // r4 = 0x10000 (page table address)
        l.lwz       r5,0(r4)        // r5 = table size
        l.addi      r7,r4,8         // r7 = current page table entry
        l.addi      r6,r0,0         // r6 = 0 (current entry index)

try:    l.sfeq      r6,r5           // last entry?
        l.bf        miss            // go if so (a miss)
        l.nop                       // (delay slot instruction)
        l.lwz       r1,0(r7)        // r1 = current entry va
        l.sfeq      r1,r2           // does va match entry?
        l.bf        hit             // go if so (a hit)
        l.nop                       // (delay slot instruction)
        l.addi      r7,r7,4         // r7 = next page table entry
        l.j         try             // try next entry
        l.addi      r6,r6,1         // r6 = next entry index (delay slot)

miss:   l.sw        0(r7),r2        // save va into page table
        l.addi      r5,r5,1         // increment table size
        l.sw        0(r4),r5        // save new table size

hit:    l.muli      r3,r6,PAGE_SIZE // r3 = current entry index * page size
        l.movhi     r5,0x1000       // r5 = heap base (0x10000000)
        l.add       r3,r3,r5        // r3 = pa
        l.lwz       r1,4(r4)        // r1 = tlbIndex
        l.nop       99              // set TLB entry
        l.addi      r1,r1,1         // increment tlbIndex
        l.andi      r1,r1,TLB_SIZE-1// clip to TLB size
        l.sw        4(r4),r1        // save tlbIndex for next call

        l.lwz       r1,-4(r31)      // restore r1
        l.lwz       r2,-8(r31)      // restore r2
        l.lwz       r3,-12(r31)     // restore r3
        l.lwz       r4,-16(r31)     // restore r4
        l.lwz       r5,-20(r31)     // restore r5
        l.lwz       r6,-24(r31)     // restore r6
        l.lwz       r7,-28(r31)     // restore r7
        l.rfe                       // return from exception

.org 0xc00
        ////////////////////////////////////////////////////////////////////////
        // SYSCALL VECTOR (AT 0xc00) - TERMINATE PROGRAM
        ////////////////////////////////////////////////////////////////////////
.global exit
exit:   l.nop

        ////////////////////////////////////////////////////////////////////////
        // USER APPLICATION (IN KERNEL MEMORY)
        ////////////////////////////////////////////////////////////////////////
appStart:
        l.jal       fib             // calculate fib(15)
        l.addi      r1,r0,15        // r1 = 15 (delay slot)
        l.sys       0               // exit the application

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

        l.nop       98              // whats in r1?
        l.muli      r2,r1,PAGE_SIZE // r2 = fib * page size
        l.movhi     r3,0x8000       // r3 = user heap base (0x80000000)
        l.add       r2,r2,r3        // r2 = fib page
        l.lwz       r3,0(r2)        // r3 = old fib count
        l.addi      r3,r3,1         // increment count
        l.sw        0(r2),r3        // save new count

done:   l.jr        r9              // return, result in r1
        l.nop                       // (delay slot instruction)
appEnd:



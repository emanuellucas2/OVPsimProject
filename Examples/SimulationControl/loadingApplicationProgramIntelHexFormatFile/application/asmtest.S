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

.global _start
_start:                          // TEST PROLOGUE
        addi      x1,x0,0        // x1 = 0
        addi      x2,x0,1        // x2 = 1
        addi      x3,x0,-1       // x3 = -1
        addi      x4,x0,0x80     // x4 = 0x00000080

        lw        x5,0(x4)
        addi      x5,x3,-1
        addi      x5,x4,0
        addi      x5,x5,1
        sw        x5, 0(x4)

.global _exit
_exit:
.global exit
exit:
        nop
        wfi
        nop
        j _exit

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

        .text
        .globl  _reset_vector
        .globl  _start
        .global exit
        .syntax unified
	.org 0x0000
_start:
_reset_vector:
	b main
	.org 0x0004
_und_vector:
	movs pc, lr
	.org 0x0008
_swi_vector:
	movs pc, lr
	.org 0x000C
_pabt_vector:
	movs pc, lr
	.org 0x0010
_dabt_vector:
	b do_dabt
	.org 0x0014
_rsvd_vector:
	movs pc, lr
	.org 0x0018
_irq_vector:
	movs pc, lr
	.org 0x001C
_fiq_vector:
	movs pc, lr
	.org 0x0020
_mon_reset_vector:
	b main
	.org 0x0024
_mon_und_vector:
	movs pc, lr
	.org 0x0028
_mon_swi_vector:
        b do_smc
	.org 0x002C
_mon_pabt_vector:
	movs pc, lr
	.org 0x0030
_mon_dabt_vector:
	b do_dabt
	.org 0x0034
_mon_rsvd_vector:
	movs pc, lr
	.org 0x0038
_mon_irq_vector:
	movs pc, lr
	.org 0x003C
_mon_fiq_vector:
	movs pc, lr

do_dabt:
        mrc     p15, 0, r3, c5, c0, 0       /* read DFSR */
        mrc     p15, 0, r3, c6, c0, 0       /* read DFAR */
	subs    pc, lr, 4

do_smc:

	movs    pc, r2

main:

        mov     r0, #0x20
        mcr     p15, 0, r0, c12, c0, 1      /* write MVBAR */
        mrc     p15, 0, r0, c12, c0, 1      /* read MVBAR */

        #####################################################################
        # set all TTBCR bits except PD0, PD1
        #####################################################################

        mrc     p15,0,r0,c2,c0,2            /* read TTBCR */
        mov     r0,#0xffffffcf
        mcr     p15,0,r0,c2,c0,2            /* write TTBCR */

        #####################################################################
        # enter Monitor mode
        #####################################################################

        mrs     r0,cpsr
        bic     r0,#0x1f
        orr     r0,#0x16
        msr     cpsr_cx,r0

        #####################################################################
        # set up secure TLB
        #####################################################################

        mov     r0, #SecureTranslationTable
        bl      setUpTLB

        #####################################################################
        # validate secure PL1 mode accesses, TLB enabled
        #####################################################################

        bl      testAccesses

        #####################################################################
        # enter insecure Supervisor mode
        #####################################################################

        mrc     p15,0,r0,c1,c1,0            /* read SCR */
        orr     r0,#0x01                    /* set SCR.NS */
        mcr     p15,0,r0,c1,c1,0            /* write SCR */

        mrs     r0,cpsr
        bic     r0,#0x1f
        orr     r0,#0x13
        msr     cpsr_cx,r0

        #####################################################################
        # validate insecure PL1 mode accesses, TLB disabled
        #####################################################################

        bl      testAccesses

        #####################################################################
        # enter Monitor mode
        #####################################################################

        mrs     r0,cpsr
        bic     r0,#0x1f
        orr     r0,#0x16
        msr     cpsr_cx,r0

        #####################################################################
        # toggle SCR.NS
        #####################################################################

        mrc     p15,0,r0,c1,c1,0            /* read SCR */
        orr     r0,#0x01                    /* set SCR.NS */
        mcr     p15,0,r0,c1,c1,0            /* write SCR */

        #####################################################################
        # set up insecure TLB
        #####################################################################

        mov     r2, lr
        mov     r0, #InsecureTranslationTable
        bl      setUpTLB

        #####################################################################
        # enter insecure Supervisor mode
        #####################################################################

        mrs     r0,cpsr
        bic     r0,#0x1f
        orr     r0,#0x13
        msr     cpsr_cx,r0

        #####################################################################
        # validate insecure PL1 mode accesses, TLB enabled
        #####################################################################

        bl      testAccesses

        #####################################################################
        # enter insecure User mode
        #####################################################################

        mrs     r0,cpsr
        bic     r0,#0x1f
        orr     r0,#0x10
        msr     cpsr_cx,r0

        #####################################################################
        # validate insecure PL0 mode accesses
        #####################################################################

        bl      testAccesses

exit:   b       exit

testAccesses:

        mov     r5, lr

        mov     r4, #0x00100000
        add     r2, r4, #0x0000 ; bl      testAccess
        add     r2, r4, #0x0400 ; bl      testAccess
        add     r2, r4, #0x0800 ; bl      testAccess
        add     r2, r4, #0x0c00 ; bl      testAccess
        add     r2, r4, #0x1000 ; bl      testAccess
        add     r2, r4, #0x1400 ; bl      testAccess
        add     r2, r4, #0x1800 ; bl      testAccess
        add     r2, r4, #0x1c00 ; bl      testAccess
        add     r2, r4, #0x2000 ; bl      testAccess
        add     r2, r4, #0x2400 ; bl      testAccess
        add     r2, r4, #0x2800 ; bl      testAccess
        add     r2, r4, #0x2c00 ; bl      testAccess
        add     r2, r4, #0x3000 ; bl      testAccess
        add     r2, r4, #0x3400 ; bl      testAccess
        add     r2, r4, #0x3800 ; bl      testAccess
        add     r2, r4, #0x3c00 ; bl      testAccess

        mov     r4, #0x00200000
        add     r2, r4, #0x0000 ; bl      testAccess
        add     r2, r4, #0x0400 ; bl      testAccess
        add     r2, r4, #0x0800 ; bl      testAccess
        add     r2, r4, #0x0c00 ; bl      testAccess
        add     r2, r4, #0x1000 ; bl      testAccess
        add     r2, r4, #0x1400 ; bl      testAccess
        add     r2, r4, #0x1800 ; bl      testAccess
        add     r2, r4, #0x1c00 ; bl      testAccess
        add     r2, r4, #0x2000 ; bl      testAccess
        add     r2, r4, #0x2400 ; bl      testAccess
        add     r2, r4, #0x2800 ; bl      testAccess
        add     r2, r4, #0x2c00 ; bl      testAccess
        add     r2, r4, #0x3000 ; bl      testAccess
        add     r2, r4, #0x3400 ; bl      testAccess
        add     r2, r4, #0x3800 ; bl      testAccess
        add     r2, r4, #0x3c00 ; bl      testAccess

        mov     r4, #0x00300000
        add     r2, r4, #0x0000 ; bl      testAccess
        add     r2, r4, #0x0400 ; bl      testAccess
        add     r2, r4, #0x0800 ; bl      testAccess
        add     r2, r4, #0x0c00 ; bl      testAccess
        add     r2, r4, #0x1000 ; bl      testAccess
        add     r2, r4, #0x1400 ; bl      testAccess
        add     r2, r4, #0x1800 ; bl      testAccess
        add     r2, r4, #0x1c00 ; bl      testAccess
        add     r2, r4, #0x2000 ; bl      testAccess
        add     r2, r4, #0x2400 ; bl      testAccess
        add     r2, r4, #0x2800 ; bl      testAccess
        add     r2, r4, #0x2c00 ; bl      testAccess
        add     r2, r4, #0x3000 ; bl      testAccess
        add     r2, r4, #0x3400 ; bl      testAccess
        add     r2, r4, #0x3800 ; bl      testAccess
        add     r2, r4, #0x3c00 ; bl      testAccess

        mov     r4, #0x00400000
        add     r2, r4, #0x0000 ; bl      testAccess
        add     r2, r4, #0x0400 ; bl      testAccess
        add     r2, r4, #0x0800 ; bl      testAccess
        add     r2, r4, #0x0c00 ; bl      testAccess
        add     r2, r4, #0x1000 ; bl      testAccess
        add     r2, r4, #0x1400 ; bl      testAccess
        add     r2, r4, #0x1800 ; bl      testAccess
        add     r2, r4, #0x1c00 ; bl      testAccess
        add     r2, r4, #0x2000 ; bl      testAccess
        add     r2, r4, #0x2400 ; bl      testAccess
        add     r2, r4, #0x2800 ; bl      testAccess
        add     r2, r4, #0x2c00 ; bl      testAccess
        add     r2, r4, #0x3000 ; bl      testAccess
        add     r2, r4, #0x3400 ; bl      testAccess
        add     r2, r4, #0x3800 ; bl      testAccess
        add     r2, r4, #0x3c00 ; bl      testAccess

        bx      r5

testAccess:

        ldr     r0, [r2]
        str     r0, [r2]
        ldrt    r0, [r2]
        strt    r0, [r2]

        bx      lr

setUpTLB:

        #####################################################################
        # set up translation table base
        #####################################################################

        mrc     p15, 0, r1, c2, c0, 0
        mcr     p15, 0, r0, c2, c0, 0
        mrc     p15, 0, r0, c2, c0, 0

        #####################################################################
        # set up domain 0 with client permissions
        #####################################################################

        mrc     p15, 0, r0, c3, c0, 0
        mov     r0, #1
        mcr     p15, 0, r0, c3, c0, 0

        #####################################################################
        # enable MMU
        #####################################################################

        mrc     p15, 0, r0, c1, c0, 0
        orr     r0, r0, #1
        mcr     p15, 0, r0, c1, c0, 0

        bx      lr

################################################################################
# TLB MACROS
################################################################################

        .macro  TABLE PA,Domain,NS,PXN
        .word   \PA+(\Domain<<5)+(\NS<<3)+(\PXN<<2)+1
        .endm

        .macro  SMALL_PAGE_V5 PA,AP3,AP2,AP1,AP0,C,B
        .word   \PA+(\AP3<<10)+(\AP2<<8)+(\AP1<<6)+(\AP0<<4)+(\C<<3)+(\B<<2)+2
        .endm

################################################################################
# SECURE TABLE
################################################################################

        .org 0x4000

SecureTranslationTable:

                                    /* -------- */
                                    /* lowVA    */
                                    /* -------- */
TABLE 1f,0,0,0                      /* 00000000 */
TABLE 2f,0,0,0                      /* 00100000 */
TABLE 3f,0,0,1                      /* 00200000 */
TABLE 2f,0,1,0                      /* 00300000 */
TABLE 3f,0,1,1                      /* 00400000 */

        .org 0x5000

1:
                                    /* -------- -------- -------- ---- ---- */
                                    /* lowVA    highVA   lowPA    priv user */
                                    /* -------- -------- -------- ---- ---- */
SMALL_PAGE_V5 0x00000000,3,3,3,3,0,0/* 00100000 00100fff 00000000 rwx  rwx  */
                                    /* -------- -------- -------- ---- ---- */

        .org 0x5400

2:
                                    /* -------- -------- -------- ---- ---- */
                                    /* lowVA    highVA   lowPA    priv user */
                                    /* -------- -------- -------- ---- ---- */
SMALL_PAGE_V5 0x08000000,3,2,1,0,0,0/* 00100000 00100fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,3,2,1,0,0,1/* 00101000 00101fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,3,2,1,0,1,0/* 00102000 00102fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,3,2,1,0,1,1/* 00103000 00103fff 08000000 ---  ---  */
                                    /* -------- -------- -------- ---- ---- */

        .org 0x5800

3:
                                    /* -------- -------- -------- ---- ---- */
                                    /* lowVA    highVA   lowPA    priv user */
                                    /* -------- -------- -------- ---- ---- */
SMALL_PAGE_V5 0x08000000,0,1,2,3,0,0/* 00200000 00200fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,0,1,2,3,0,1/* 00201000 00201fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,0,1,2,3,1,0/* 00202000 00202fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,0,1,2,3,1,1/* 00203000 00203fff 08000000 ---  ---  */
                                    /* -------- -------- -------- ---- ---- */

################################################################################
# INSECURE TABLE
################################################################################

        .org 0x8000

InsecureTranslationTable:

                                    /* -------- */
                                    /* lowVA    */
                                    /* -------- */
TABLE 1f,0,0,0                      /* 00000000 */
TABLE 2f,0,0,0                      /* 00100000 */
TABLE 3f,0,0,1                      /* 00200000 */
TABLE 2f,0,1,0                      /* 00300000 */
TABLE 3f,0,1,1                      /* 00400000 */

        .org 0x9000

1:
                                    /* -------- -------- -------- ---- ---- */
                                    /* lowVA    highVA   lowPA    priv user */
                                    /* -------- -------- -------- ---- ---- */
SMALL_PAGE_V5 0x00000000,3,3,3,3,0,0/* 00100000 00100fff 00000000 rwx  rwx  */
                                    /* -------- -------- -------- ---- ---- */

        .org 0x9400

2:
                                    /* -------- -------- -------- ---- ---- */
                                    /* lowVA    highVA   lowPA    priv user */
                                    /* -------- -------- -------- ---- ---- */
SMALL_PAGE_V5 0x08000000,3,2,1,0,0,0/* 00100000 00100fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,3,2,1,0,0,1/* 00101000 00101fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,3,2,1,0,1,0/* 00102000 00102fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,3,2,1,0,1,1/* 00103000 00103fff 08000000 ---  ---  */
                                    /* -------- -------- -------- ---- ---- */

        .org 0x9800

3:
                                    /* -------- -------- -------- ---- ---- */
                                    /* lowVA    highVA   lowPA    priv user */
                                    /* -------- -------- -------- ---- ---- */
SMALL_PAGE_V5 0x08000000,0,1,2,3,0,0/* 00200000 00200fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,0,1,2,3,0,1/* 00201000 00201fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,0,1,2,3,1,0/* 00202000 00202fff 08000000 ---  ---  */
SMALL_PAGE_V5 0x08000000,0,1,2,3,1,1/* 00203000 00203fff 08000000 ---  ---  */
                                    /* -------- -------- -------- ---- ---- */

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


////////////////////////////////////////////////////////////////////////////////
// CODE
////////////////////////////////////////////////////////////////////////////////

        .text
        .globl  _reset_vector
        .globl  _start

        .org 0x0000
_start:
        b           testMain

bodgeStartup:

        // initialize vpidr_el2 from midr_el1 (Foundation Model does not seem
        // to reset to this state, which is incorrect)
        mrs         x0, midr_el1
        msr         vpidr_el2, x0

        // force SCTLR_EL3 state
        mrs         x0, sctlr_el3
        bic         x0, x0, #0x40000    // nTWE=0
        bic         x0, x0, #0x10000    // nTWI=0
        bic         x0, x0, #0x00038    // SA=0, SA0=0, CP15BEN=0
        msr         sctlr_el3, x0

        // force SCTLR_EL2 state
        mrs         x0, sctlr_el2
        bic         x0, x0, #0x00008    // SA=0
        msr         sctlr_el2, x0

        // force SCTLR_EL1 state
        mrs         x0, sctlr_el1
        bic         x0, x0, #0x40000    // nTWE=0
        bic         x0, x0, #0x10000    // nTWI=0
        bic         x0, x0, #0x00038    // SA=0, SA0=0, CP15BEN=0
        msr         sctlr_el1, x0

        // force CSSELR_EL1 state
        mov         x0, #1
        msr         csselr_el1, x0

        // force MAIR_EL1 and MAIR_EL3 state
        mov         x0, #0
        msr         mair_el1, x0
        msr         mair_el3, x0

        // force CNTHCTL_EL2 state
        mov         x0, #0
        msr         cnthctl_el2, x0

        ret
/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd. All Rights Reserved.
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

////////////////////////////////////////////////////////////////////////////////
// MACROS
////////////////////////////////////////////////////////////////////////////////

        // This is required so '&' can be used to signal end of macro parameter
        .altmacro

        // define register name label
        .macro DEFINE_REG_LABEL _L
        \_L : .string "\_L"
        .endm

        // write string (destroys X0, X1)
        .macro WRITE_S _L
#ifndef SYS_QUIET
        adr         x1, \_L
        mov         x0, #0x04       // Code for SYS_WRITE0
        hlt         #0xf000
#endif
        .endm

       // write newline (destroys X0, X1)
        .macro WRITE_NL
        WRITE_S     newlineL
        .endm

        // write log message (destroys X0, X1)
        .macro WRITE_LOG_N _M
        WRITE_S     logM
        WRITE_S     \_M
        .endm

        // write log message (destroys X0, X1)
        .macro WRITE_LOG _M
        WRITE_LOG_N \_M
        WRITE_NL
        .endm

        // write raw register (destroys X0, X1, X2, X3, LR)
        .macro WRITE_RAW _R
#ifndef SYS_QUIET
        mov         x1, \_R
        bl          writeX1
#endif
        .endm

        // write GPR (destroys X0, X1, X2, X3, LR)
        .macro WRITE_GPR _GPR
        mov         x3, \_GPR
        WRITE_S     logM
        WRITE_S     \_GPR
        WRITE_S     equalsXL
        WRITE_RAW   x3
        WRITE_NL
        .endm

        // write SIMD V reg val (destroys X0, X1, X2, X3, LR)
        .macro WRITE_SIMD _V
        WRITE_S     logM
        WRITE_S     \_V
        WRITE_S     equalsXL
        WRITE_RAW   \_V&.d[1]
        WRITE_RAW   \_V&.d[0]
        WRITE_NL
        .endm

        // MRS (destroys X0, X1, X2, X3, LR)
        .macro MRS_LOG _GPR, _SYS
        mrs         \_GPR, \_SYS
        WRITE_S     logM
        WRITE_S     \_SYS
        WRITE_S     rarrowXL
        WRITE_RAW   \_GPR
        WRITE_NL
        .endm

        // MSR (destroys X0, X1, X2, X3, LR)
        .macro MSR_LOG _SYS, _GPR
        msr         \_SYS, \_GPR
#ifndef SYS_QUIET
        mov         x2, #-1
        movk        x2, #0xdead,  lsl #0
        movk        x2, #0xdead,  lsl #16
        movk        x2, #0xdead,  lsl #32
        movk        x2, #0xdead,  lsl #48
        mrs         x2, \_SYS
#endif
        WRITE_S     logM
        WRITE_S     \_SYS
        WRITE_S     larrowXL
        WRITE_RAW   x2
        WRITE_NL
        .endm

        // exit test
        .macro EXIT
        WRITE_LOG   exitM
        mov         x0, #0x18       // Angel SWIreason_ReportException(0x18)
        ldr         x1, =0x20026    // report ADP_Stopped_ApplicationEXIT
        hlt         #0xf000
        .endm

        // branch if core has the given id (destroys X0)
        .macro BRANCH_IF_CORE _ID, _ADDRESS
        mrs         x0, mpidr_el1
        and         x0, x0, 0xff
        cmp         x0, \_ID
        b.eq        \_ADDRESS
        .endm

        // branch if core dies not have the given id (destroys X0)
        .macro BRANCH_IF_NOT_CORE _ID, _ADDRESS
        mrs         x0, mpidr_el1
        and         x0, x0, 0xff
        cmp         x0, \_ID
        b.ne        \_ADDRESS
        .endm

        // stop cpu if it has the passed core id (destroys X0)
        .macro STOP_CORE, _ID
        BRANCH_IF_NOT_CORE \_ID, 2f
1:      wfe
        b           1b
2:
        .endm

        // stop cpu unless it has the passed core id (destroys X0)
        .macro STOP_UNLESS_CORE, _ID
        BRANCH_IF_CORE \_ID, 2f
1:      wfe
        b           1b
2:
        .endm

        // wait-for-interrupt cpu if it has the passed core id (destroys X0)
        .macro WFI_CORE, _ID
        BRANCH_IF_NOT_CORE \_ID, 2f
1:      wfi
        b           1b
2:
        .endm

        // wait-for-interrupt cpu unless it has the passed core id (destroys X0)
        .macro WFI_UNLESS_CORE, _ID
        BRANCH_IF_CORE \_ID, 2f
1:      wfi
        b           1b
2:
        .endm

writeX1:
#ifndef SYS_QUIET
        // write register X1 (destroys X0, X1, X2, X3)
        mov         x2, x1
        mov         x3, 16

        // write character
1:      ror         x2, x2, #60
        and         x0, x2, #0xf
        adr         x1, chars
        add         x1, x1, x0, lsl #1
        mov         x0, #0x04       // Code for SYS_WRITE0
        hlt         #0xf000

        // loop
        subs        x3, x3, #1
        b.ne        1b
#endif

        ret

////////////////////////////////////////////////////////////////////////////////
// STRINGS
////////////////////////////////////////////////////////////////////////////////

chars:
        .string "0"
        .string "1"
        .string "2"
        .string "3"
        .string "4"
        .string "5"
        .string "6"
        .string "7"
        .string "8"
        .string "9"
        .string "a"
        .string "b"
        .string "c"
        .string "d"
        .string "e"
        .string "f"

newlineL:
        .string "\n"

equalsXL:
        .string " = 0x"

rarrowXL:
        .string " => 0x"

larrowXL:
        .string " <= 0x"
logM:
        .string "LOG: "
exitM:
        .string "TEST ENDED"

// GPR labels
DEFINE_REG_LABEL x0
DEFINE_REG_LABEL x1
DEFINE_REG_LABEL x2
DEFINE_REG_LABEL x3
DEFINE_REG_LABEL x4
DEFINE_REG_LABEL x5
DEFINE_REG_LABEL x6
DEFINE_REG_LABEL x7
DEFINE_REG_LABEL x8
DEFINE_REG_LABEL x9
DEFINE_REG_LABEL x10
DEFINE_REG_LABEL x11
DEFINE_REG_LABEL x12
DEFINE_REG_LABEL x13
DEFINE_REG_LABEL x14
DEFINE_REG_LABEL x15
DEFINE_REG_LABEL x16
DEFINE_REG_LABEL x17
DEFINE_REG_LABEL x18
DEFINE_REG_LABEL x19
DEFINE_REG_LABEL x20
DEFINE_REG_LABEL x21
DEFINE_REG_LABEL x22
DEFINE_REG_LABEL x23
DEFINE_REG_LABEL x24
DEFINE_REG_LABEL x25
DEFINE_REG_LABEL x26
DEFINE_REG_LABEL x27
DEFINE_REG_LABEL x28
DEFINE_REG_LABEL x29
DEFINE_REG_LABEL x30
DEFINE_REG_LABEL x31
DEFINE_REG_LABEL xzr
DEFINE_REG_LABEL sp

// SIMD labels
DEFINE_REG_LABEL v0
DEFINE_REG_LABEL v1
DEFINE_REG_LABEL v2
DEFINE_REG_LABEL v3
DEFINE_REG_LABEL v4
DEFINE_REG_LABEL v5
DEFINE_REG_LABEL v6
DEFINE_REG_LABEL v7
DEFINE_REG_LABEL v8
DEFINE_REG_LABEL v9
DEFINE_REG_LABEL v10
DEFINE_REG_LABEL v11
DEFINE_REG_LABEL v12
DEFINE_REG_LABEL v13
DEFINE_REG_LABEL v14
DEFINE_REG_LABEL v15
DEFINE_REG_LABEL v16
DEFINE_REG_LABEL v17
DEFINE_REG_LABEL v18
DEFINE_REG_LABEL v19
DEFINE_REG_LABEL v20
DEFINE_REG_LABEL v21
DEFINE_REG_LABEL v22
DEFINE_REG_LABEL v23
DEFINE_REG_LABEL v24
DEFINE_REG_LABEL v25
DEFINE_REG_LABEL v26
DEFINE_REG_LABEL v27
DEFINE_REG_LABEL v28
DEFINE_REG_LABEL v29
DEFINE_REG_LABEL v30
DEFINE_REG_LABEL v31

// mrs/msr, crn=0, op1=0
DEFINE_REG_LABEL midr_el1
DEFINE_REG_LABEL mpidr_el1
DEFINE_REG_LABEL revidr_el1
DEFINE_REG_LABEL id_pfr0_el1
DEFINE_REG_LABEL id_pfr1_el1
DEFINE_REG_LABEL id_dfr0_el1
DEFINE_REG_LABEL id_afr0_el1
DEFINE_REG_LABEL id_mmfr0_el1
DEFINE_REG_LABEL id_mmfr1_el1
DEFINE_REG_LABEL id_mmfr2_el1
DEFINE_REG_LABEL id_mmfr3_el1
DEFINE_REG_LABEL id_isar0_el1
DEFINE_REG_LABEL id_isar1_el1
DEFINE_REG_LABEL id_isar2_el1
DEFINE_REG_LABEL id_isar3_el1
DEFINE_REG_LABEL id_isar4_el1
DEFINE_REG_LABEL id_isar5_el1
DEFINE_REG_LABEL mvfr0_el1
DEFINE_REG_LABEL mvfr1_el1
DEFINE_REG_LABEL mvfr2_el1
DEFINE_REG_LABEL id_aa64pfr0_el1
DEFINE_REG_LABEL id_aa64pfr1_el1
DEFINE_REG_LABEL id_aa64dfr0_el1
DEFINE_REG_LABEL id_aa64dfr1_el1
DEFINE_REG_LABEL id_aa64afr0_el1
DEFINE_REG_LABEL id_aa64afr1_el1
DEFINE_REG_LABEL id_aa64isar0_el1
DEFINE_REG_LABEL id_aa64isar1_el1
DEFINE_REG_LABEL id_aa64mmfr0_el1
DEFINE_REG_LABEL id_aa64mmfr1_el1

// mrs/msr, crn=0, op1!=0
DEFINE_REG_LABEL ccsidr_el1
DEFINE_REG_LABEL clidr_el1
DEFINE_REG_LABEL aidr_el1
DEFINE_REG_LABEL csselr_el1
DEFINE_REG_LABEL ctr_el0
DEFINE_REG_LABEL dczid_el0
DEFINE_REG_LABEL vpidr_el2
DEFINE_REG_LABEL vmpidr_el2

// mrs/msr, crn=1
DEFINE_REG_LABEL sctlr_el1
DEFINE_REG_LABEL actlr_el1
DEFINE_REG_LABEL cpacr_el1
DEFINE_REG_LABEL sctlr_el2
DEFINE_REG_LABEL actlr_el2
DEFINE_REG_LABEL hcr_el2
DEFINE_REG_LABEL mdcr_el2
DEFINE_REG_LABEL cptr_el2
DEFINE_REG_LABEL hstr_el2
DEFINE_REG_LABEL hacr_el2
DEFINE_REG_LABEL sctlr_el3
DEFINE_REG_LABEL actlr_el3
DEFINE_REG_LABEL scr_el3
DEFINE_REG_LABEL sder32_el3
DEFINE_REG_LABEL cptr_el3
DEFINE_REG_LABEL mdcr_el3

// mrs/msr, crn=2
DEFINE_REG_LABEL ttbr0_el1
DEFINE_REG_LABEL ttbr1_el1
DEFINE_REG_LABEL tcr_el1
DEFINE_REG_LABEL ttbr0_el2
DEFINE_REG_LABEL tcr_el2
DEFINE_REG_LABEL vttbr_el2
DEFINE_REG_LABEL vtcr_el2
DEFINE_REG_LABEL ttbr0_el3
DEFINE_REG_LABEL tcr_el3

// mrs/msr, crn=3
DEFINE_REG_LABEL dacr32_el2

// mrs/msr, crn=4
DEFINE_REG_LABEL spsr_el1
DEFINE_REG_LABEL elr_el1
DEFINE_REG_LABEL sp_el0
DEFINE_REG_LABEL spsel,
DEFINE_REG_LABEL currentel,
DEFINE_REG_LABEL daif,
DEFINE_REG_LABEL nzcv,
DEFINE_REG_LABEL fpcr,
DEFINE_REG_LABEL fpsr,
DEFINE_REG_LABEL dspsr_el0
DEFINE_REG_LABEL dlr_el0
DEFINE_REG_LABEL spsr_el2
DEFINE_REG_LABEL elr_el2
DEFINE_REG_LABEL sp_el1
DEFINE_REG_LABEL spsr_irq,
DEFINE_REG_LABEL spsr_abt,
DEFINE_REG_LABEL spsr_und,
DEFINE_REG_LABEL spsr_fiq,
DEFINE_REG_LABEL spsr_el3
DEFINE_REG_LABEL elr_el3
DEFINE_REG_LABEL sp_el2

// mrs/msr, crn=5
DEFINE_REG_LABEL afsr0_el1
DEFINE_REG_LABEL afsr1_el1
DEFINE_REG_LABEL esr_el1
DEFINE_REG_LABEL ifsr32_el2
DEFINE_REG_LABEL afsr0_el2
DEFINE_REG_LABEL afsr1_el2
DEFINE_REG_LABEL esr_el2
DEFINE_REG_LABEL fpexc32_el2
DEFINE_REG_LABEL afsr0_el3
DEFINE_REG_LABEL afsr1_el3
DEFINE_REG_LABEL esr_el3

// mrs/msr, crn=6
DEFINE_REG_LABEL far_el1
DEFINE_REG_LABEL far_el2
DEFINE_REG_LABEL hpfar_el2
DEFINE_REG_LABEL far_el3

// mrs/msr, crn=7
DEFINE_REG_LABEL par_el1

// mrs/msr, crn=9
DEFINE_REG_LABEL pmintenset_el1
DEFINE_REG_LABEL pmintenclr_el1
DEFINE_REG_LABEL pmcr_el0
DEFINE_REG_LABEL pmcntenset_el0
DEFINE_REG_LABEL pmcntenclr_el0
DEFINE_REG_LABEL pmovsclr_el0
DEFINE_REG_LABEL pmswinc_el0
DEFINE_REG_LABEL pmselr_el0
DEFINE_REG_LABEL pmceid0_el0
DEFINE_REG_LABEL pmceid1_el0
DEFINE_REG_LABEL pmccntr_el0
DEFINE_REG_LABEL pmxevtyper_el0
DEFINE_REG_LABEL pmxevcntr_el0
DEFINE_REG_LABEL pmuserenr_el0
DEFINE_REG_LABEL pmovsset_el0

// mrs/msr, crn=10
DEFINE_REG_LABEL mair_el1
DEFINE_REG_LABEL amair_el1
DEFINE_REG_LABEL mair_el2
DEFINE_REG_LABEL amair_el2
DEFINE_REG_LABEL mair_el3
DEFINE_REG_LABEL amair_el3

// mrs/msr, crn=12
DEFINE_REG_LABEL vbar_el1
DEFINE_REG_LABEL rvbar_el1
DEFINE_REG_LABEL rmr_el1
DEFINE_REG_LABEL isr_el1
DEFINE_REG_LABEL vbar_el2
DEFINE_REG_LABEL rvbar_el2
DEFINE_REG_LABEL rmr_el2
DEFINE_REG_LABEL vbar_el3
DEFINE_REG_LABEL rvbar_el3
DEFINE_REG_LABEL rmr_el3

// mrs/msr, crn=13
DEFINE_REG_LABEL contextidr_el1
DEFINE_REG_LABEL tpidr_el1
DEFINE_REG_LABEL tpidr_el0
DEFINE_REG_LABEL tpidrro_el0
DEFINE_REG_LABEL tpidr_el2
DEFINE_REG_LABEL tpidr_el3

// mrs/msr, crn=14 (timer registers)
DEFINE_REG_LABEL cntkctl_el1
DEFINE_REG_LABEL cntfrq_el0
DEFINE_REG_LABEL cntpct_el0
DEFINE_REG_LABEL cntvct_el0
DEFINE_REG_LABEL cntp_tval_el0
DEFINE_REG_LABEL cntp_ctl_el0
DEFINE_REG_LABEL cntp_cval_el0
DEFINE_REG_LABEL cntv_tval_el0
DEFINE_REG_LABEL cntv_ctl_el0
DEFINE_REG_LABEL cntv_cval_el0
DEFINE_REG_LABEL cntvoff_el2
DEFINE_REG_LABEL cnthctl_el2
DEFINE_REG_LABEL cnthp_tval_el2
DEFINE_REG_LABEL cnthp_ctl_el2
DEFINE_REG_LABEL cnthp_cval_el2
DEFINE_REG_LABEL cntps_tval_el1
DEFINE_REG_LABEL cntps_ctl_el1
DEFINE_REG_LABEL cntps_cval_el1

// mrs/msr, crn=14 (performance monitor registers)
DEFINE_REG_LABEL pmevcntr0_el0
DEFINE_REG_LABEL pmevcntr1_el0
DEFINE_REG_LABEL pmevcntr2_el0
DEFINE_REG_LABEL pmevcntr3_el0
DEFINE_REG_LABEL pmevcntr4_el0
DEFINE_REG_LABEL pmevcntr5_el0
DEFINE_REG_LABEL pmevcntr6_el0
DEFINE_REG_LABEL pmevcntr7_el0
DEFINE_REG_LABEL pmevcntr8_el0
DEFINE_REG_LABEL pmevcntr9_el0
DEFINE_REG_LABEL pmevcntr10_el0
DEFINE_REG_LABEL pmevcntr11_el0
DEFINE_REG_LABEL pmevcntr12_el0
DEFINE_REG_LABEL pmevcntr13_el0
DEFINE_REG_LABEL pmevcntr14_el0
DEFINE_REG_LABEL pmevcntr15_el0
DEFINE_REG_LABEL pmevcntr16_el0
DEFINE_REG_LABEL pmevcntr17_el0
DEFINE_REG_LABEL pmevcntr18_el0
DEFINE_REG_LABEL pmevcntr19_el0
DEFINE_REG_LABEL pmevcntr20_el0
DEFINE_REG_LABEL pmevcntr21_el0
DEFINE_REG_LABEL pmevcntr22_el0
DEFINE_REG_LABEL pmevcntr23_el0
DEFINE_REG_LABEL pmevcntr24_el0
DEFINE_REG_LABEL pmevcntr25_el0
DEFINE_REG_LABEL pmevcntr26_el0
DEFINE_REG_LABEL pmevcntr27_el0
DEFINE_REG_LABEL pmevcntr28_el0
DEFINE_REG_LABEL pmevcntr29_el0
DEFINE_REG_LABEL pmevcntr30_el0
DEFINE_REG_LABEL pmevtyper0_el0
DEFINE_REG_LABEL pmevtyper1_el0
DEFINE_REG_LABEL pmevtyper2_el0
DEFINE_REG_LABEL pmevtyper3_el0
DEFINE_REG_LABEL pmevtyper4_el0
DEFINE_REG_LABEL pmevtyper5_el0
DEFINE_REG_LABEL pmevtyper6_el0
DEFINE_REG_LABEL pmevtyper7_el0
DEFINE_REG_LABEL pmevtyper8_el0
DEFINE_REG_LABEL pmevtyper9_el0
DEFINE_REG_LABEL pmevtyper10_el0
DEFINE_REG_LABEL pmevtyper11_el0
DEFINE_REG_LABEL pmevtyper12_el0
DEFINE_REG_LABEL pmevtyper13_el0
DEFINE_REG_LABEL pmevtyper14_el0
DEFINE_REG_LABEL pmevtyper15_el0
DEFINE_REG_LABEL pmevtyper16_el0
DEFINE_REG_LABEL pmevtyper17_el0
DEFINE_REG_LABEL pmevtyper18_el0
DEFINE_REG_LABEL pmevtyper19_el0
DEFINE_REG_LABEL pmevtyper20_el0
DEFINE_REG_LABEL pmevtyper21_el0
DEFINE_REG_LABEL pmevtyper22_el0
DEFINE_REG_LABEL pmevtyper23_el0
DEFINE_REG_LABEL pmevtyper24_el0
DEFINE_REG_LABEL pmevtyper25_el0
DEFINE_REG_LABEL pmevtyper26_el0
DEFINE_REG_LABEL pmevtyper27_el0
DEFINE_REG_LABEL pmevtyper28_el0
DEFINE_REG_LABEL pmevtyper29_el0
DEFINE_REG_LABEL pmevtyper30_el0
DEFINE_REG_LABEL pmccfiltr_el0

// debug registers
DEFINE_REG_LABEL mdccint_el1
DEFINE_REG_LABEL mdscr_el1
DEFINE_REG_LABEL dbgclaimset_el1
DEFINE_REG_LABEL dbgclaimclr_el1
DEFINE_REG_LABEL dbgauthstatus_el1
DEFINE_REG_LABEL dbgdtr_el0
DEFINE_REG_LABEL dbgdtrtx_el0
DEFINE_REG_LABEL dbgdtrrx_el0
DEFINE_REG_LABEL dbgprcr_el1
DEFINE_REG_LABEL dbgvcr32_el2
DEFINE_REG_LABEL mdccsr_el0
DEFINE_REG_LABEL osdlr_el1
DEFINE_REG_LABEL osdtrrx_el1
DEFINE_REG_LABEL osdtrtx_el1
DEFINE_REG_LABEL oseccr_el1
DEFINE_REG_LABEL oslar_el1
DEFINE_REG_LABEL oslsr_el1
DEFINE_REG_LABEL mdrar_el1

// debug register arrays
DEFINE_REG_LABEL dbgbvr0_el1
DEFINE_REG_LABEL dbgbvr1_el1
DEFINE_REG_LABEL dbgbvr2_el1
DEFINE_REG_LABEL dbgbvr3_el1
DEFINE_REG_LABEL dbgbvr4_el1
DEFINE_REG_LABEL dbgbvr5_el1
DEFINE_REG_LABEL dbgbvr6_el1
DEFINE_REG_LABEL dbgbvr7_el1
DEFINE_REG_LABEL dbgbvr8_el1
DEFINE_REG_LABEL dbgbvr9_el1
DEFINE_REG_LABEL dbgbvr10_el1
DEFINE_REG_LABEL dbgbvr11_el1
DEFINE_REG_LABEL dbgbvr12_el1
DEFINE_REG_LABEL dbgbvr13_el1
DEFINE_REG_LABEL dbgbvr14_el1
DEFINE_REG_LABEL dbgbvr15_el1
DEFINE_REG_LABEL dbgbcr0_el1
DEFINE_REG_LABEL dbgbcr1_el1
DEFINE_REG_LABEL dbgbcr2_el1
DEFINE_REG_LABEL dbgbcr3_el1
DEFINE_REG_LABEL dbgbcr4_el1
DEFINE_REG_LABEL dbgbcr5_el1
DEFINE_REG_LABEL dbgbcr6_el1
DEFINE_REG_LABEL dbgbcr7_el1
DEFINE_REG_LABEL dbgbcr8_el1
DEFINE_REG_LABEL dbgbcr9_el1
DEFINE_REG_LABEL dbgbcr10_el1
DEFINE_REG_LABEL dbgbcr11_el1
DEFINE_REG_LABEL dbgbcr12_el1
DEFINE_REG_LABEL dbgbcr13_el1
DEFINE_REG_LABEL dbgbcr14_el1
DEFINE_REG_LABEL dbgbcr15_el1
DEFINE_REG_LABEL dbgwcr0_el1
DEFINE_REG_LABEL dbgwcr1_el1
DEFINE_REG_LABEL dbgwcr2_el1
DEFINE_REG_LABEL dbgwcr3_el1
DEFINE_REG_LABEL dbgwcr4_el1
DEFINE_REG_LABEL dbgwcr5_el1
DEFINE_REG_LABEL dbgwcr6_el1
DEFINE_REG_LABEL dbgwcr7_el1
DEFINE_REG_LABEL dbgwcr8_el1
DEFINE_REG_LABEL dbgwcr9_el1
DEFINE_REG_LABEL dbgwcr10_el1
DEFINE_REG_LABEL dbgwcr11_el1
DEFINE_REG_LABEL dbgwcr12_el1
DEFINE_REG_LABEL dbgwcr13_el1
DEFINE_REG_LABEL dbgwcr14_el1
DEFINE_REG_LABEL dbgwcr15_el1
DEFINE_REG_LABEL dbgwvr0_el1
DEFINE_REG_LABEL dbgwvr1_el1
DEFINE_REG_LABEL dbgwvr2_el1
DEFINE_REG_LABEL dbgwvr3_el1
DEFINE_REG_LABEL dbgwvr4_el1
DEFINE_REG_LABEL dbgwvr5_el1
DEFINE_REG_LABEL dbgwvr6_el1
DEFINE_REG_LABEL dbgwvr7_el1
DEFINE_REG_LABEL dbgwvr8_el1
DEFINE_REG_LABEL dbgwvr9_el1
DEFINE_REG_LABEL dbgwvr10_el1
DEFINE_REG_LABEL dbgwvr11_el1
DEFINE_REG_LABEL dbgwvr12_el1
DEFINE_REG_LABEL dbgwvr13_el1
DEFINE_REG_LABEL dbgwvr14_el1
DEFINE_REG_LABEL dbgwvr15_el1

        .align 4
/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd. All Rights Reserved.
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

////////////////////////////////////////////////////////////////////////////////
// UTILITY MACROS
////////////////////////////////////////////////////////////////////////////////

        // emit exception prologue
        .macro EXCPT_PRLG _REPORT
1:
        sub         sp, sp, #64
        str         x0,  [sp, 0]
        str         x1,  [sp, 8]
        str         x2,  [sp, 16]
        str         x3,  [sp, 24]
        str         x4,  [sp, 32]
        str         x5,  [sp, 40]
        str         x30, [sp, 48]
        adr         x5,  1b
#ifndef SYS_QUIET
        bl          \_REPORT
#endif
        .endm

        // emit exception epilogue
        .macro EXCPT_EPLG
        ldr         x0,  [sp, 0]
        ldr         x1,  [sp, 8]
        ldr         x2,  [sp, 16]
        ldr         x3,  [sp, 24]
        ldr         x4,  [sp, 32]
        ldr         x5,  [sp, 40]
        ldr         x30, [sp, 48]
        add         sp, sp, #64
        .endm

        // define exception handler
        .macro EXCPT _ELR, _REPORT, _VECTORS, _OFFSET
        EXCPT_PRLG  \_REPORT
        adr         x0, \_VECTORS
        ldr         x0, [x0, #\_OFFSET]
        blr         x0
        EXCPT_EPLG
        eret
        .endm

        // define set of exception handlers
        .macro EXCPT_SET _ELR, _REPORT, _VECTORS
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (0*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (1*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (2*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (3*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (4*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (5*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (6*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (7*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (8*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (9*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (10*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (11*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (12*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (13*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (14*8)
        .align  7
        EXCPT       \_ELR, \_REPORT, \_VECTORS, (15*8)
        .endm

        // define set of 4 exception vectors (Synchonous, IRQ, FIQ, SError)
        .macro VECTOR_SETx4 _TARGET, _IRQ_HANDLER=0, _FIQ_HANDLER=0
        // Synchonous
        .quad       \_TARGET
        // IRQ or vIRQ
        .if         \_IRQ_HANDLER!=0
        .quad       \_IRQ_HANDLER
        .else
        .quad       \_TARGET
        .endif
        // FIQ or vFIQ
        .if         \_FIQ_HANDLER!=0
        .quad       \_FIQ_HANDLER
        .else
        .quad       \_TARGET
        .endif
        // SError or vSError
        .quad       \_TARGET
        .endm

        // define set of 16 exception vectors (4x4)
        .macro VECTOR_SET _TARGET, _IRQ_HANDLER=0, _FIQ_HANDLER=0
        VECTOR_SETx4 \_TARGET, \_IRQ_HANDLER, \_FIQ_HANDLER
        VECTOR_SETx4 \_TARGET, \_IRQ_HANDLER, \_FIQ_HANDLER
        VECTOR_SETx4 \_TARGET, \_IRQ_HANDLER, \_FIQ_HANDLER
        VECTOR_SETx4 \_TARGET, \_IRQ_HANDLER, \_FIQ_HANDLER
        .endm

        // set up exception handlers
        .macro SETUP_VECTORS
        WRITE_NL
        WRITE_LOG   installHandlers
        adr         x4, VBAR3
        MSR_LOG     vbar_el3, x4
        mov         x4, 0x100000000
        MSR_LOG     sp_el0, x4
        mov         x4, 0xf0000000
        MSR_LOG     sp_el1, x4
        mov         x4, 0xe0000000
        MSR_LOG     sp_el2, x4
        mov         x4, 0xd0000000
        mov         sp, x4
        WRITE_GPR   sp
        .endm

        // set up exception handlers
        .macro REPORT_EXCEPT _STARTM, _ENDM, _SPSR, _ESR, _ELR, _FAR
        str         x30, [sp, #-16]!
        WRITE_NL
        WRITE_LOG   \_STARTM
        WRITE_LOG_N exceptAddress
        mov         x1, x5
        bl          writeX1
        WRITE_NL
        MRS_LOG     x4, \_SPSR
        MRS_LOG     x4, \_ESR
        MRS_LOG     x4, \_ELR
        MRS_LOG     x4, \_FAR
        WRITE_LOG   \_ENDM
        WRITE_NL
        ldr         x30, [sp], #16
        ret
        .endm

        // define handler tables
        .macro DEFINE_HANDLERS, _IRQ_HANDLER=0, _FIQ_HANDLER=0, _TARGET_EL1=defaultHandlerEL1, _TARGET_EL2=defaultHandlerEL2, _TARGET_EL3=defaultHandlerEL3
        .align 11
VBAR1:  EXCPT_SET elr_el1, reportExceptEL1, VECTOR1
        .align 11
VBAR2:  EXCPT_SET elr_el2, reportExceptEL2, VECTOR2
        .align 11
VBAR3:  EXCPT_SET elr_el3, reportExceptEL3, VECTOR3
        .align  3
VECTOR1:VECTOR_SET \_TARGET_EL1, \_IRQ_HANDLER, \_FIQ_HANDLER
        .align  3
VECTOR2:VECTOR_SET \_TARGET_EL2, \_IRQ_HANDLER, \_FIQ_HANDLER
        .align  3
VECTOR3:VECTOR_SET \_TARGET_EL3, \_IRQ_HANDLER, \_FIQ_HANDLER
        .endm

////////////////////////////////////////////////////////////////////////////////
// HANDLER MACROS
////////////////////////////////////////////////////////////////////////////////

        // define default exception handler that skips faulting instruction
        .macro DEFAULT_HANDLER _SPSR, _ESR, _ELR, _FAR

        // save link register
        str         x30, [sp, #-16]!

        // get syndrome, EC field and ELR
        mrs         x0, \_ESR
        lsr         x1, x0, 26
        mrs         x2, \_ELR

        // interpret AArch32 SVC #0xff as request to return to EL1
        cmp         x1, #0x11
        b.ne        1f
        and         x3, x0, #0xffff
        cmp         x3, #0xff
        b.eq        4f

        // interpret AArch64 SVC #0xff as request to return to EL1
1:      cmp         x1, #0x15
        b.ne        1f
        and         x3, x0, #0xffff
        cmp         x3, #0xff
        b.eq        3f

        // interpret AArch32 HVC #0xff as request to return to EL2
1:      cmp         x1, #0x12
        b.ne        1f
        and         x3, x0, #0xffff
        cmp         x3, #0xff
        b.eq        4f

        // interpret AArch64 HVC #0xff as request to return to EL2
1:      cmp         x1, #0x16
        b.ne        1f
        and         x3, x0, #0xffff
        cmp         x3, #0xff
        b.eq        3f

        // interpret AArch32 SMC with r7==0xff as request to return to EL3
        // NOTE: AArch32 SMC instruction does not provide code in syndrome!
1:      cmp         x1, #0x13
        b.ne        1f
        cmp         x7, #0xff
        b.eq        4f

        // interpret AArch64 SMC #0xff as request to return to EL3
1:      cmp         x1, #0x17
        b.ne        1f
        and         x3, x0, #0xffff
        cmp         x3, #0xff
        b.eq        3f

        // handle tagged address by clearing tag
1:      cmp         x1, #0x20
        b.ne        1f
        lsr         x3, x2, #56
        cmp         x3, #0x55
        b.ne        1f
        lsl         x3, x3, #56
        bic         x2, x2, x3
        b           5f

        // handle tagged address by clearing tag
1:      cmp         x1, #0x21
        b.ne        1f
        lsr         x3, x2, #56
        cmp         x3, #0x55
        b.ne        1f
        lsl         x3, x3, #56
        bic         x2, x2, x3
        b           5f

        // handle misaligned PC by rounding address down
1:      cmp         x1, #0x22
        b.ne        1f
        and         x2, x2, #-4
        msr         \_ELR, x2
        b           2f

        // handle IL state by clearing it (and skipping the instruction)
1:      cmp         x1, #0x0e
        b.ne        1f
        mrs         x4, \_SPSR
        bic         x4, x4, #(1<<20)
        msr         \_SPSR, x4

        // adjust ELR to skip faulting instruction based on IL field in
        // syndrome
1:      tst         x0, #(1<<25)
        b.eq        1f
        add         x2, x2, #2
1:      add         x2, x2, #2
5:      msr         \_ELR, x2

        // restore link register
2:      ldr         x30, [sp], #16

        // return from exception
        ret

        ////////////////////////////////////////////////////////////////////
        // here if a request has been made to stay at AArch64 exception
        // level when executing at AArch64
        ////////////////////////////////////////////////////////////////////

3:      mrs         x0, currentel
        cmp         x0, (1<<2)
        b.ne        1f
        WRITE_LOG   STAY_AT_LEVEL_1
        b           2f
1:      cmp         x0, (2<<2)
        b.ne        1f
        WRITE_LOG   STAY_AT_LEVEL_2
        b           2f
1:      WRITE_LOG   STAY_AT_LEVEL_3
2:      WRITE_NL
        add         sp, sp, #16
        EXCPT_EPLG
        mrs         x30, \_ELR
        br          x30

        ////////////////////////////////////////////////////////////////////
        // here if a request has been made to stay at AArch64 exception
        // level when executing at AArch32
        ////////////////////////////////////////////////////////////////////

4:      mrs         x0, currentel
        cmp         x0, (1<<2)
        b.ne        1f
        WRITE_LOG   STAY_AT_LEVEL_1
        b           2f
1:      cmp         x0, (2<<2)
        b.ne        1f
        WRITE_LOG   STAY_AT_LEVEL_2
        b           2f
1:      WRITE_LOG   STAY_AT_LEVEL_3
2:      WRITE_NL
        add         sp, sp, #16
        EXCPT_EPLG
        br          x12

        .endm

////////////////////////////////////////////////////////////////////////////////
// CONTEXT SWITCH MACROS
////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // EL3 -> EL2 context switch (target AArch64)
        ////////////////////////////////////////////////////////////////////////

        .macro EL3_TO_EL2_AA64 _ADDRESS _HANDLER _VBAR=VBAR2

        // log message
        WRITE_NL
        WRITE_LOG   EL3_TO_EL2

        // set vector base address
        adr         x4, \_VBAR
        MSR_LOG     vbar_el2, x4

        // set NS and RW bits in scr_el3
        mrs         x0, scr_el3
        orr         x0, x0, #0x001
        orr         x0, x0, #0x400
        msr         scr_el3, x0
        isb

        // seed spsr_el3 with target mode
        mrs         x0, spsr_el3
        bic         x0, x0, #0x1f
        orr         x0, x0, #(2<<2)
        .if         \_HANDLER!=0
        orr         x0, x0, \_HANDLER
        .endif
        msr         spsr_el3, x0

        // seed elr_el3 with target address
        adr         x0, \_ADDRESS
        msr         elr_el3, x0

        // switch mode
        eret

        .endm

        ////////////////////////////////////////////////////////////////////////
        // EL3 -> secure EL1 context switch (target AArch64)
        ////////////////////////////////////////////////////////////////////////

        .macro EL3_TO_EL1_AA64_S _ADDRESS _HANDLER _VBAR=VBAR1

        // log message
        WRITE_NL
        WRITE_LOG   EL3_TO_EL1_AA64_S

        // set vector base address
        adr         x4, \_VBAR
        MSR_LOG     vbar_el1, x4

        // clear NS and set RW bits in scr_el3
        mrs         x0, scr_el3
        bic         x0, x0, #0x001
        orr         x0, x0, #0x400
        msr         scr_el3, x0
        isb

        // clear RW bit in hcr_el2
        // (should have no effect at secure EL1)
        mrs         x0, hcr_el2
        bic         x0, x0, #0x80000000
        msr         hcr_el2, x0

        // seed spsr_el3 with target mode
        mrs         x0, spsr_el3
        bic         x0, x0, #0x1f
        orr         x0, x0, #(1<<2)
        .if         \_HANDLER!=0
        orr         x0, x0, \_HANDLER
        .endif
        msr         spsr_el3, x0

        // seed elr_el3 with target address
        adr         x0, \_ADDRESS
        msr         elr_el3, x0

        // switch mode
        eret

        .endm

        ////////////////////////////////////////////////////////////////////////
        // EL3 -> non-secure EL1 context switch (target AArch64)
        ////////////////////////////////////////////////////////////////////////

        .macro EL3_TO_EL1_AA64_NS _ADDRESS _HANDLER _VBAR=VBAR1

        // log message
        WRITE_NL
        WRITE_LOG   EL3_TO_EL1_AA64_NS

        // set vector base address
        adr         x4, \_VBAR
        MSR_LOG     vbar_el1, x4

        // set NS and set RW bits in scr_el3
        mrs         x0, scr_el3
        orr         x0, x0, #0x001
        orr         x0, x0, #0x400
        msr         scr_el3, x0
        isb

        // set RW bit in hcr_el2
        mrs         x0, hcr_el2
        orr         x0, x0, #0x80000000
        msr         hcr_el2, x0

        // seed spsr_el3 with target mode
        mrs         x0, spsr_el3
        bic         x0, x0, #0x1f
        orr         x0, x0, #(1<<2)
        .if         \_HANDLER!=0
        orr         x0, x0, \_HANDLER
        .endif
        msr         spsr_el3, x0

        // seed elr_el3 with target address
        adr         x0, \_ADDRESS
        msr         elr_el3, x0

        // switch mode
        eret

        .endm

        ////////////////////////////////////////////////////////////////////////
        // EL2 -> EL1 context switch (target AArch64)
        ////////////////////////////////////////////////////////////////////////

        .macro EL2_TO_EL1_AA64 _ADDRESS _HANDLER _VBAR=VBAR1

        // log message
        WRITE_NL
        WRITE_LOG   EL2_TO_EL1

        // set vector base address
        adr         x4, \_VBAR
        MSR_LOG     vbar_el1, x4

        // set RW bit in hcr_el2
        mrs         x0, hcr_el2
        orr         x0, x0, #0x80000000
        msr         hcr_el2, x0

        // seed spsr_el2 with target mode
        mrs         x0, spsr_el2
        bic         x0, x0, #0x1f
        orr         x0, x0, #(1<<2)
        .if         \_HANDLER!=0
        orr         x0, x0, \_HANDLER
        .endif
        msr         spsr_el2, x0

        // seed elr_el2 with target address
        adr         x0, \_ADDRESS
        msr         elr_el2, x0

        // switch mode
        eret

        .endm

        ////////////////////////////////////////////////////////////////////////
        // EL1 -> EL0 context switch (target AArch64)
        ////////////////////////////////////////////////////////////////////////

        .macro EL1_TO_EL0_AA64 _ADDRESS _HANDLER

        // log message
        WRITE_NL
        WRITE_LOG   EL1_TO_EL0

        // seed spsr_el1 with target mode
        mrs         x0, spsr_el1
        bic         x0, x0, #0x1f
        msr         spsr_el1, x0

        // seed elr_el1 with target address
        adr         x0, \_ADDRESS
        msr         elr_el1, x0

        // switch mode
        eret

        .endm

        ////////////////////////////////////////////////////////////////////////
        // EL3 -> EL2 context switch (target AArch32)
        ////////////////////////////////////////////////////////////////////////

        .macro EL3_TO_EL2_AA32 _ADDRESS _HANDLER _AA32_ADDRESS

        // log message
        WRITE_NL
        WRITE_LOG   EL3_TO_EL2_AA32

        // set NS and clear RW bits in scr_el3
        mrs         x0, scr_el3
        orr         x0, x0, #0x001
        bic         x0, x0, #0x400
        msr         scr_el3, x0
        isb

        // set RW bit in hcr_el2
        // (should have no effect at AArch32 EL2)
        mrs         x0, hcr_el2
        bic         x0, x0, #0x80000000
        msr         hcr_el2, x0

        // seed spsr_el3 with target mode
        mrs         x0, spsr_el3
        bic         x0, x0, #0x1f
        mov         x1, #0x1a
        orr         x0, x0, x1
        msr         spsr_el3, x0

        // seed elr_el3 with target address
        mov         x0, #\_AA32_ADDRESS
        msr         elr_el3, x0

        // save AArch64 resume address in x12
        adr         x12, \_ADDRESS

        // switch mode
        eret

        .endm

        ////////////////////////////////////////////////////////////////////////
        // EL3 -> secure EL1 context switch (target AArch32)
        ////////////////////////////////////////////////////////////////////////

        .macro EL3_TO_EL1_AA32_S _ADDRESS _HANDLER _AA32_ADDRESS _AA32_MODE

        // log message
        WRITE_NL
        WRITE_LOG   EL3_TO_EL1_AA32_S

        // clear NS and clear RW bits in scr_el3
        mrs         x0, scr_el3
        bic         x0, x0, #0x001
        bic         x0, x0, #0x400
        msr         scr_el3, x0
        isb

        // set RW bit in hcr_el2
        // (should have no effect at secure EL1)
        mrs         x0, hcr_el2
        bic         x0, x0, #0x80000000
        msr         hcr_el2, x0

        // seed spsr_el3 with target mode
        mrs         x0, spsr_el3
        bic         x0, x0, #0x1f
        mov         x1, #\_AA32_MODE
        orr         x0, x0, x1
        msr         spsr_el3, x0

        // seed elr_el3 with target address
        mov         x0, #\_AA32_ADDRESS
        msr         elr_el3, x0

        // save AArch64 resume address in x12
        adr         x12, \_ADDRESS

        // switch mode
        eret

        .endm

        ////////////////////////////////////////////////////////////////////////
        // EL3 -> non-secure EL1 context switch (target AArch32)
        ////////////////////////////////////////////////////////////////////////

        .macro EL3_TO_EL1_AA32_NS _ADDRESS _HANDLER _AA32_ADDRESS _AA32_MODE

        // log message
        WRITE_NL
        WRITE_LOG   EL3_TO_EL1_AA32_NS

        // set NS and clear RW bits in scr_el3
        mrs         x0, scr_el3
        orr         x0, x0, #0x001
        bic         x0, x0, #0x400
        msr         scr_el3, x0
        isb

        // clear RW bit in hcr_el2
        mrs         x0, hcr_el2
        bic         x0, x0, #0x80000000
        msr         hcr_el2, x0

        // seed spsr_el3 with target mode
        mrs         x0, spsr_el3
        bic         x0, x0, #0x1f
        mov         x1, #\_AA32_MODE
        orr         x0, x0, x1
        msr         spsr_el3, x0

        // seed elr_el3 with target address
        mov         x0, #\_AA32_ADDRESS
        msr         elr_el3, x0

        // save AArch64 resume address in x12
        adr         x12, \_ADDRESS

        // switch mode
        eret

        .endm

        ////////////////////////////////////////////////////////////////////////
        // EL2 -> EL1 context switch (target AArch32)
        ////////////////////////////////////////////////////////////////////////

        .macro EL2_TO_EL1_AA32 _ADDRESS _HANDLER _AA32_ADDRESS _AA32_MODE

        // log message
        WRITE_NL
        WRITE_LOG   EL2_TO_EL1_AA32

        // clear RW bit in hcr_el2
        mrs         x0, hcr_el2
        bic         x0, x0, #0x80000000
        msr         hcr_el2, x0

        // seed spsr_el2 with target mode
        mrs         x0, spsr_el2
        bic         x0, x0, #0x1f
        mov         x1, #\_AA32_MODE
        orr         x0, x0, x1
        msr         spsr_el2, x0

        // seed elr_el2 with target address
        mov         x0, #\_AA32_ADDRESS
        msr         elr_el2, x0

        // save AArch64 resume address in x12
        adr         x12, \_ADDRESS

        // switch mode
        eret

        .endm

        ////////////////////////////////////////////////////////////////////////
        // EL1 -> EL0 context switch (target AArch32)
        ////////////////////////////////////////////////////////////////////////

        .macro EL1_TO_EL0_AA32 _ADDRESS _HANDLER _AA32_ADDRESS

        // log message
        WRITE_NL
        WRITE_LOG   EL1_TO_EL0_AA32

        // seed spsr_el1 with target mode
        mrs         x0, spsr_el1
        bic         x0, x0, #0x1f
        orr         x0, x0, #0x10
        msr         spsr_el1, x0

        // seed elr_el1 with target address
        mov         x0, #\_AA32_ADDRESS
        msr         elr_el1, x0

        // save AArch64 resume address in x12
        adr         x12, \_ADDRESS

        // switch mode
        eret

        .endm

        ////////////////////////////////////////////////////////////////////////
        // EL3 -> EL3 context switch, SCR.NS=1
        ////////////////////////////////////////////////////////////////////////

        .macro EL3_TO_EL3_NS1

        // log message
        WRITE_NL
        WRITE_LOG   EL3_NS1

        // set SCR.NS=1
        mrs         x0, scr_el3
        orr         x0, x0, #0x001
        msr         scr_el3, x0
        isb

        .endm

        ////////////////////////////////////////////////////////////////////////
        // EL3 -> EL3 context switch, SCR.NS=0
        ////////////////////////////////////////////////////////////////////////

        .macro EL3_TO_EL3_NS0

        // log message
        WRITE_NL
        WRITE_LOG   EL3_NS0

        // set SCR.NS=1
        mrs         x0, scr_el3
        bic         x0, x0, #0x001
        msr         scr_el3, x0
        isb

        .endm

////////////////////////////////////////////////////////////////////////////////
// HIERARCHY DESCENT MACROS
////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // call function at non-secure EL0
        ////////////////////////////////////////////////////////////////////////

        .macro APPLY_NS_EL0 _TESTCB

        // switch to EL2
        EL3_TO_EL2_AA64 1f 0

        // switch to non-secure EL1
1:      EL2_TO_EL1_AA64 1f 0

        // switch to non-secure EL0
1:      EL1_TO_EL0_AA64 1f 0

        // do tests at non-secure EL0
1:      bl          \_TESTCB

        // switch back to EL1
        svc         #0xff

        // switch back to EL3
        smc         #0xff

        .endm

        ////////////////////////////////////////////////////////////////////////
        // call function at non-secure EL1
        ////////////////////////////////////////////////////////////////////////

        .macro APPLY_NS_EL1 _TESTCB

        // switch to EL2
        EL3_TO_EL2_AA64 1f 0

        // switch to non-secure EL1
1:      EL2_TO_EL1_AA64 1f 0

        // do tests at non-secure EL1
1:      bl          \_TESTCB

        // switch back to EL3
        smc         #0xff

        .endm

        ////////////////////////////////////////////////////////////////////////
        // call function at non-secure EL1 and EL0
        ////////////////////////////////////////////////////////////////////////

        .macro APPLY_NS_EL1_EL0 _TESTCB

        // switch to EL2
        EL3_TO_EL2_AA64 1f 0

        // switch to non-secure EL1
1:      EL2_TO_EL1_AA64 1f 0

        // do tests at non-secure EL1
1:      bl          \_TESTCB

        // switch to non-secure EL0
        EL1_TO_EL0_AA64 1f 0

        // do tests at non-secure EL0
1:      bl          \_TESTCB

        // switch back to EL1
        svc         #0xff

        // switch back to EL3
        smc         #0xff

        .endm

        ////////////////////////////////////////////////////////////////////////
        // call function at non-secure EL2, EL1 and EL0
        ////////////////////////////////////////////////////////////////////////

        .macro APPLY_NS_EL2_EL1_EL0 _TESTCB

        // switch to EL2
        EL3_TO_EL2_AA64 1f 0

        // do tests at EL2
1:      bl          \_TESTCB

        // switch to non-secure EL1
        EL2_TO_EL1_AA64 1f 0

        // do tests at non-secure EL1
1:      bl          \_TESTCB

        // switch to non-secure EL0
        EL1_TO_EL0_AA64 1f 0

        // do tests at non-secure EL0
1:      bl          \_TESTCB

        // switch back to EL1
        svc         #0xff

        // switch back to EL2
        hvc         #0xff

        // switch back to EL3
        smc         #0xff

        .endm

        ////////////////////////////////////////////////////////////////////////
        // call function at non-secure EL2 and EL1
        ////////////////////////////////////////////////////////////////////////

        .macro APPLY_NS_EL2_EL1 _TESTCB

        // switch to EL2
        EL3_TO_EL2_AA64 1f 0

        // do tests at EL2
1:      bl          \_TESTCB

        // switch to non-secure EL1
        EL2_TO_EL1_AA64 1f 0

        // do tests at non-secure EL1
1:      bl          \_TESTCB

        // switch back to EL2
        hvc         #0xff

        // switch back to EL3
        smc         #0xff

        .endm

        ////////////////////////////////////////////////////////////////////////
        // call function at secure EL3, EL1 and EL0 (EL3 is tested twice, first
        // with SCR.NS=1 and then with SCR.NS=0
        ////////////////////////////////////////////////////////////////////////

        .macro APPLY_S_EL3_EL1_EL0 _TESTCB

        // switch to EL3 with SCR.NS=1
        EL3_TO_EL3_NS1

        // do tests at EL3 with SCR.NS=1
        bl          \_TESTCB

        // switch to EL3 with SCR.NS=0
        EL3_TO_EL3_NS0

        // do tests at EL3 with SCR.NS=0
        bl          \_TESTCB

        // switch to secure EL1
        EL3_TO_EL1_AA64_S 1f 0

        // do tests at secure EL1
1:      bl          \_TESTCB

        // switch to secure EL0
        EL1_TO_EL0_AA64 1f 0

        // do tests at secure EL0
1:      bl          \_TESTCB

        // switch back to EL1
        svc         #0xff

        // switch back to EL3
        smc         #0xff

        .endm

        ////////////////////////////////////////////////////////////////////////
        // call function at secure EL3, EL1 and EL0 (EL3 is with SCR.NS=1 only)
        ////////////////////////////////////////////////////////////////////////

        .macro APPLY_S_EL3_EL1_EL0_NS1 _TESTCB

        // switch to EL3 with SCR.NS=1
        EL3_TO_EL3_NS1

        // do tests at EL3 with SCR.NS=1
        bl          \_TESTCB

        // switch to secure EL1
        EL3_TO_EL1_AA64_S 1f 0

        // do tests at secure EL1
1:      bl          \_TESTCB

        // switch to secure EL0
        EL1_TO_EL0_AA64 1f 0

        // do tests at secure EL0
1:      bl          \_TESTCB

        // switch back to EL1
        svc         #0xff

        // switch back to EL3
        smc         #0xff

        .endm

        ////////////////////////////////////////////////////////////////////////
        // call function at secure EL1
        ////////////////////////////////////////////////////////////////////////

        .macro APPLY_S_EL1 _TESTCB

        // switch to EL3 with SCR.NS=0
        EL3_TO_EL3_NS0

        // switch to secure EL1
        EL3_TO_EL1_AA64_S 1f 0

        // do tests at secure EL1
1:      bl          \_TESTCB

        // switch back to EL3
        smc         #0xff

        .endm

        ////////////////////////////////////////////////////////////////////////
        // call function at non-secure EL1 in AArch32 state
        ////////////////////////////////////////////////////////////////////////

        .macro APPLY_NS_EL1_AA32 _TESTCB

        // do tests at non-secure EL1 in AArch32 state
        EL3_TO_EL1_AA32_NS 1f 0 \_TESTCB 0x11

1:      // switch back to EL3
        smc         #0xff

        .endm

////////////////////////////////////////////////////////////////////////////////
// STRINGS
////////////////////////////////////////////////////////////////////////////////

installHandlers :
        .string "INSTALL HANDLERS:"
exceptAddress:
        .string "HANDLER ADDRESS: "
exceptStartEL1:
        .string "------------ START EXCEPTION (EL1) ------------"
exceptEndEL1:
        .string "------------ END EXCEPTION (EL1)   ------------"
exceptStartEL2:
        .string "------------ START EXCEPTION (EL2) ------------"
exceptEndEL2:
        .string "------------ END EXCEPTION (EL2)   ------------"
exceptStartEL3:
        .string "------------ START EXCEPTION (EL3) ------------"
exceptEndEL3:
        .string "------------ END EXCEPTION (EL3)   ------------"
EL3_TO_EL2:
        .string "------------ SWITCH MODE EL3 -> EL2 -----------"
EL3_TO_EL1_AA64_S:
        .string "------------ SWITCH MODE EL3 -> EL1 (S) -------"
EL3_TO_EL1_AA64_NS:
        .string "------------ SWITCH MODE EL3 -> EL1 (NS) ------"
EL2_TO_EL1:
        .string "------------ SWITCH MODE EL2 -> EL1 -----------"
EL1_TO_EL0:
        .string "------------ SWITCH MODE EL1 -> EL0 -----------"
EL3_TO_EL2_AA32:
        .string "------------ SWITCH MODE EL3 -> EL2 (AA32) ----"
EL1_TO_EL0_AA32:
        .string "------------ SWITCH MODE EL1 -> EL0 (AA32) ----"
EL3_TO_EL1_AA32_S:
        .string "------------ SWITCH MODE EL3 -> EL1 (AA32,S) --"
EL3_TO_EL1_AA32_NS:
        .string "------------ SWITCH MODE EL3 -> EL1 (AA32,NS) -"
EL2_TO_EL1_AA32:
        .string "------------ SWITCH MODE EL2 -> EL1 (AA32) ----"
EL3_NS1:
        .string "------------ AT EL3 WITH SCR.NS=1 -------------"
EL3_NS0:
        .string "------------ AT EL3 WITH SCR.NS=0 -------------"
STAY_AT_LEVEL_1:
        .string "--------- RETURN TO EXCEPTION LEVEL 1 ---------"
STAY_AT_LEVEL_2:
        .string "--------- RETURN TO EXCEPTION LEVEL 2 ---------"
STAY_AT_LEVEL_3:
        .string "--------- RETURN TO EXCEPTION LEVEL 3 ---------"
LINES:
        .string "-----------------------------------------------"

////////////////////////////////////////////////////////////////////////////////
// CODE
////////////////////////////////////////////////////////////////////////////////

        .align 4

defaultHandlerEL1:
        DEFAULT_HANDLER spsr_el1, esr_el1, elr_el1, far_el1

defaultHandlerEL2:
        DEFAULT_HANDLER spsr_el2, esr_el2, elr_el2, far_el2

defaultHandlerEL3:
        DEFAULT_HANDLER spsr_el3, esr_el3, elr_el3, far_el3

reportExceptEL1:
        REPORT_EXCEPT exceptStartEL1, exceptEndEL1, spsr_el1, esr_el1, elr_el1, far_el1

reportExceptEL2:
        REPORT_EXCEPT exceptStartEL2, exceptEndEL2, spsr_el2, esr_el2, elr_el2, far_el2

reportExceptEL3:
        REPORT_EXCEPT exceptStartEL3, exceptEndEL3, spsr_el3, esr_el3, elr_el3, far_el3

/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd. All Rights Reserved.
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

        // define exception handlers
        DEFINE_HANDLERS

        .org 0x8000

testMain:

        // stop cores 1, 2 and 3 (leave 0 running)
        STOP_CORE   1
        STOP_CORE   2
        STOP_CORE   3

        // bodge initial state where Foundation Model looks wrong
        bl          bodgeStartup

        // enable HVC instruction (SCR.HCE)
        mrs         x4, scr_el3
        orr         x4, x4, 0x100
        MSR_LOG     scr_el3, x4

        // set up exception handlers
        SETUP_VECTORS

        // switch to secure EL1
        EL3_TO_EL1_AA64_S 1f 0
1:      nop

        // WFE that doesn't wait followed by one that does
        wfe
        wfe

        // WFI
        wfi

        // SEV (triggers reset)
        sev

        EXIT

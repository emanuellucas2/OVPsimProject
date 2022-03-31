/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "hostapi/impAlloc.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"
#include "ppc32Structure.h"
#include "ppc32MorphFP.h"
#include "ppc32Utils.h"
#include "ppc32VM.h"
#include "ppc32SPR_400.h"

//
// Trace SPR Accesses
//
#define TRACE_SPR 0


// HV PR
//  0  0    Privileged
//  0  1    Problem (user)
//  1  0    Privileged and Hypervisor
//  1  1    Problem (user)

Bool ppc32IsUserMode_400 (ppc32P ppc32) {
    return (ppc32->SPR->MSR.bits.PR==1);
}
Bool ppc32IsPrivMode_400 (ppc32P ppc32) {
    return (ppc32->SPR->MSR.bits.PR==0);
}
Bool ppc32IsHypvMode_400 (ppc32P ppc32) {
    return False;
}

//
// Special Handling for the dec counter
//
static void vmic_update_dec(ppc32P ppc32) {
    Uns64 now = vmirtGetICount((vmiProcessorP)ppc32);
    Uns64 diff = now - ppc32->SPR->DEC_tmr;
    ppc32->SPR->DEC -= diff;
    ppc32->SPR->DEC_tmr = now;
    //
    // TODO: post an event for a callback, this generates an interrupt
    // at count == 0
    //
}

//
// Special Handling for the tb counter
//
static void vmic_update_tb(ppc32P ppc32) {
    ppc32->SPR->TB.reg = vmirtGetICount((vmiProcessorP)ppc32);
}
//
// Special handling is required for mtspr
//
static void vmic_mtspr(ppc32P ppc32, Uns32 spr, Uns32 rs, Uns32 *wvalue) {
    Uns32 value;

    if (wvalue) {
        value = *wvalue;
    } else {
        value = ppc32->GPR[rs];
    }

    //
    // HV PR
    //  0  0  Privileged
    //  0  1  Problem (user)
    //  1  0  Privileged and Hypervisor
    //  1  1  Problem (user)
    //
    Bool user_ok = (SPR_ACCESS[spr].mtspr == NO);
    Bool priv_ok = (SPR_ACCESS[spr].mtspr == YES)  && ppc32IsPrivMode_400(ppc32);
    Bool hypv_ok = (SPR_ACCESS[spr].mtspr == HYPV) && ppc32IsHypvMode_400(ppc32);

    Bool ok = user_ok || priv_ok || hypv_ok;
    if (ok) {
        switch (spr) {
        case XER:
            ppc32->XER.reg = value & ppc32->XER_wmask.reg;
            ppc32UnpackXER(ppc32);
            break;
        case DEC:
            ppc32->SPR->DEC_tmr = vmirtGetICount((vmiProcessorP)ppc32);
            ppc32->SPR->DEC = value;
            break;
        case PID:
            ppc32->SPR->PID0.bits.PID = value;
            break;
        case SRR0:
            ppc32->SPR->SRR0.reg = value & ppc32->SPR->SRR0_wmask.reg;
            break;
        case SRR1:
            ppc32->SPR->SRR1.reg = value & ppc32->SPR->SRR1_wmask.reg;
            break;
        case SPRG0:
            ppc32->SPR->SPRG0 = value;
            break;
        case SPRG1:
            ppc32->SPR->SPRG1 = value;
            break;
        case SPRG2:
            ppc32->SPR->SPRG2 = value;
            break;
        case SPRG3_2:
            ppc32->SPR->SPRG3 = value;
            break;
        case TBL_2:
            ppc32->SPR->TB.bits.TBL = value;
            break;
        case TBU_2:
            ppc32->SPR->TB.bits.TBU = value;
            break;
        case CCR0:
            ppc32->SPR->CCR0.reg = value;
            break;

        case IVPR:
            // Instruction Register Prefix
            ppc32->SPR->IVPR.reg = value;
            ppc32->SPR->IVPR.bits.RSV0 = 0;
            break;
        case IVOR0:
            // Critical Input
            ppc32->SPR->IVOR0 = value & 0x0000fff0;
            break;
        case IVOR1:
            // Machine Check
            ppc32->SPR->IVOR1 = value & 0x0000fff0;
            break;
        case IVOR2:
            // Data Storage
            ppc32->SPR->IVOR2 = value & 0x0000fff0;
            break;
        case IVOR3:
            // Instruction Storage
            ppc32->SPR->IVOR3 = value & 0x0000fff0;
            break;
        case IVOR4:
            // External
            ppc32->SPR->IVOR4 = value & 0x0000fff0;
            break;
        case IVOR5:
            // Alignment
            ppc32->SPR->IVOR5 = value & 0x0000fff0;
            break;
        case IVOR6:
            // Program
            ppc32->SPR->IVOR6 = value & 0x0000fff0;
            break;
        case IVOR7:
            // Floating point unavailable
            ppc32->SPR->IVOR7 = value & 0x0000fff0;
            break;
        case IVOR8:
            // System Call
            ppc32->SPR->IVOR8 = value & 0x0000fff0;
            break;
        case IVOR9:
            // Auxilliary Processor unavailable
            ppc32->SPR->IVOR9 = value & 0x0000fff0;
            break;
        case IVOR10:
            // Decrementer
            ppc32->SPR->IVOR10 = value & 0x0000fff0;
            break;
        case IVOR11:
            // Fixed-Interval Timer Imterrupt
            ppc32->SPR->IVOR11 = value & 0x0000fff0;
            break;
        case IVOR12:
            // Watchdog Timer Interrupt
            ppc32->SPR->IVOR12 = value & 0x0000fff0;
            break;
        case IVOR13:
            // Data TLB Error
            ppc32->SPR->IVOR13 = value & 0x0000fff0;
            break;
        case IVOR14:
            // Instruction TLB Error
            ppc32->SPR->IVOR14 = value & 0x0000fff0;
            break;
        case IVOR15:
            // Debug
            ppc32->SPR->IVOR15 = value & 0x0000fff0;
            break;

        case DEAR:
            ppc32->SPR->DEAR = value;
            break;
        case ESR:
            ppc32->SPR->ESR.reg = value;
            break;

        case DECAR:
        case CSRR0:
        case CSRR1:
        case SPRG3_1:
        case SPRG4_1:
        case SPRG5_1:
        case SPRG6_1:
        case SPRG7_1:
        case TBL_1:
        case TBU_1:
        case SPRG4_2:
        case SPRG5_2:
        case SPRG6_2:
        case SPRG7_2:
        case PIR:
        case PVR:
        case DBSR:
        case DBCR0:
        case DBCR1:
        case DBCR2:
        case IAC1:
        case IAC2:
        case IAC3:
        case IAC4:
        case DAC1:
        case DAC2:
        case DVC1:
        case DVC2:
        case TSR:
        case TCR:
        case MCSRR0:
        case MCSRR1:
        case MCSR:
        case SPRG8:
        case DCDBTRL:
        case DCDBTRH:
        case ICDBTRL:
        case ICDBTRH:
        default:
            vmiMessage("W", "MTSPR-UNDEF", "mtspr spr[%d(%s)], r%d=0x%08x", spr, SPR_ACCESS[spr].name, rs, ppc32->GPR[rs]);
            break;
        }
    } else {
        vmiMessage("W", "MTSPR-PRIV", "mtspr spr[%d(%s)], r%d=0x%08x", spr, SPR_ACCESS[spr].name, rs, ppc32->GPR[rs]);
    }

#if (TRACE_SPR==1)
    vmiMessage("I", "TRACE-MTSPR", "mtspr spr[%d(%s)], r%d=0x%08x", spr, SPR_ACCESS[spr].name, rs, ppc32->GPR[rs]);
#endif
}

//
// Special handling is required for mfspr
//
static void vmic_mfspr(ppc32P ppc32, Uns32 rt, Uns32 spr, Uns32 *rvalue) {
    Uns32 value = 0xdeadbeef;

    //
    // HV PR
    //  0  0  Privileged
    //  0  1  Problem (user)
    //  1  0  Privileged and Hypervisor
    //  1  1  Problem (user)
    //
    Bool user_ok = (SPR_ACCESS[spr].mfspr == NO);
    Bool priv_ok = (SPR_ACCESS[spr].mfspr == YES)  && ppc32IsPrivMode_400(ppc32);
    Bool hypv_ok = (SPR_ACCESS[spr].mfspr == HYPV) && ppc32IsHypvMode_400(ppc32);

    Bool ok = user_ok || priv_ok || hypv_ok;
    if (ok) {
        switch (spr) {
        case XER:
            ppc32PackXER(ppc32);
            value = ppc32->XER.reg & ppc32->XER_rmask.reg;
            break;
        case DEC:
            vmic_update_dec(ppc32);
            value = ppc32->SPR->DEC;
            break;
        case SRR0:
            value = ppc32->SPR->SRR0.reg & ppc32->SPR->SRR0_rmask.reg;
            break;
        case SRR1:
            value = ppc32->SPR->SRR1.reg & ppc32->SPR->SRR1_rmask.reg;
            break;
        case SPRG0:
            value = ppc32->SPR->SPRG0;
            break;
        case SPRG1:
            value = ppc32->SPR->SPRG1;
            break;
        case SPRG2:
            value = ppc32->SPR->SPRG2;
            break;
        case SPRG3_2:
            value = ppc32->SPR->SPRG3;
            break;
        case PID:
            value = ppc32->SPR->PID0.reg & ppc32->SPR->PID0_rmask.reg;
            break;
        case TBL_1:
            vmic_update_tb(ppc32);
            value = ppc32->SPR->TB.bits.TBL;
            break;
        case TBU_1:
            vmic_update_tb(ppc32);
            value = ppc32->SPR->TB.bits.TBU;
            break;
        case PVR:
            value = ppc32->SPR->PVR.reg;
            break;
        case CCR0:
            value = ppc32->SPR->CCR0.reg;
            break;

        case IVPR:
            // Instruction Register Prefix
            value = ppc32->SPR->IVPR.reg;
            break;
        case IVOR0:
            // Critical Input
            value = ppc32->SPR->IVOR0;
            break;
        case IVOR1:
            // Machine Check
            value = ppc32->SPR->IVOR1;
            break;
        case IVOR2:
            // Data Storage
            value = ppc32->SPR->IVOR2;
            break;
        case IVOR3:
            // Instruction Storage
            value = ppc32->SPR->IVOR3;
            break;
        case IVOR4:
            // External
            value = ppc32->SPR->IVOR4;
            break;
        case IVOR5:
            // Alignment
            value = ppc32->SPR->IVOR5;
            break;
        case IVOR6:
            // Program
            value = ppc32->SPR->IVOR6;
            break;
        case IVOR7:
            // Floating point unavailable
            value = ppc32->SPR->IVOR7;
            break;
        case IVOR8:
            // System Call
            value = ppc32->SPR->IVOR8;
            break;
        case IVOR9:
            // Auxilliary Processor unavailable
            value = ppc32->SPR->IVOR9;
            break;
        case IVOR10:
            // Decrementer
            value = ppc32->SPR->IVOR10;
            break;
        case IVOR11:
            // Fixed-Interval Timer Imterrupt
            value = ppc32->SPR->IVOR11;
            break;
        case IVOR12:
            // Watchdog Timer Interrupt
            value = ppc32->SPR->IVOR12;
            break;
        case IVOR13:
            // Data TLB Error
            value = ppc32->SPR->IVOR13;
            break;
        case IVOR14:
            // Instruction TLB Error
            value = ppc32->SPR->IVOR14;
            break;
        case IVOR15:
            // Debug
            value = ppc32->SPR->IVOR15;
            break;

        case DEAR:
            value = ppc32->SPR->DEAR;
            break;

        case ESR:
            value = ppc32->SPR->ESR.reg;
            break;

        case DECAR:
        case CSRR0:
        case CSRR1:
        case SPRG3_1:
        case SPRG4_1:
        case SPRG5_1:
        case SPRG6_1:
        case SPRG7_1:
        case SPRG4_2:
        case SPRG5_2:
        case SPRG6_2:
        case SPRG7_2:
        case TBL_2:
        case TBU_2:
        case PIR:
        case DBSR:
        case DBCR0:
        case DBCR1:
        case DBCR2:
        case IAC1:
        case IAC2:
        case IAC3:
        case IAC4:
        case DAC1:
        case DAC2:
        case DVC1:
        case DVC2:
        case TSR:
        case TCR:
        case MCSRR0:
        case MCSRR1:
        case MCSR:
        case SPRG8:
        case DCDBTRL:
        case DCDBTRH:
        case ICDBTRL:
        case ICDBTRH:
        default:
            vmiMessage("W", "MFSPR-UNDEF", "mfspr r%d, spr[%d(%s)]", rt, spr, SPR_ACCESS[spr].name);
            break;
        }
    } else {
        vmiMessage("W", "MFSPR-PRIV", "mfspr r%d, spr[%d(%s)]", rt, spr, SPR_ACCESS[spr].name);
    }

    if (rvalue) {
        *rvalue = value;
    } else {
        ppc32->GPR[rt] = value;
#if (TRACE_SPR==1)
        vmiMessage("I", "TRACE-MFSPR", "mfspr r%d=0x%08x, spr[%d(%s)]", rt, ppc32->GPR[rt], spr, SPR_ACCESS[spr].name);
#endif
    }

}

static void refreshBlockMask(ppc32P ppc32) {

    ppc32BlockMask blockMask = BM_NONE;

    //
    // FPU Availability
    //
    if (ppc32->SPR->MSR.bits.FP) {
        blockMask |= BM_FP_AVAIL;
    }

    if (blockMask != ppc32->blockMask) {
        ppc32->blockMask = blockMask;
        vmirtSetBlockMask((vmiProcessorP)ppc32, blockMask);
    }
}

static void vmic_mtmsr(ppc32P ppc32, Uns32 l, Uns32 rs) {
    TYPE_MSR msr_rs;
    msr_rs.reg = ppc32->GPR[rs];

    //
    // Special or'ing, this seems to conflict with the programming note
    //
    TYPE_MSR MSR = ppc32->SPR->MSR;
    if (l==0) {
        ppc32->SPR->MSR.reg = msr_rs.reg & ppc32->SPR->MSR_wmask.reg;

        //
        // Special Handling of other bits
        //
        ppc32->SPR->MSR.bits.EE |= ppc32->SPR->MSR.bits.PR;   // bit 48
        ppc32->SPR->MSR.bits.IS |= ppc32->SPR->MSR.bits.PR;   // bit 58
        ppc32->SPR->MSR.bits.DS |= ppc32->SPR->MSR.bits.PR;   // bit 59
      //ppc32->SPR->MSR.bits.LE  = MSR.bits.LE;         // Restore bit 63
        ppc32->SPR->MSR.bits.ME  = MSR.bits.ME;         // Restore bit 51

    } else {

      //ppc32->SPR->MSR.bits.RI = msr_rs.bits.RI;
        ppc32->SPR->MSR.bits.EE = msr_rs.bits.EE;
    }

    ppc32UpdateFPControlWord(ppc32);
    refreshBlockMask(ppc32);
    vmirtSetMode((vmiProcessorP)ppc32, ppc32GetVMMode(ppc32));
}

void ppc32AllocSPR_400(ppc32P ppc32) {
    //
    // Allocate the SPRs
    //
    ppc32->SPR = STYPE_CALLOC(ppc32spr);
}

void ppc32InitSPR_400(ppc32P ppc32) {
    Int32 iter;
    for (iter=0; iter<32; iter++) {
        ppc32->GPR[iter] = 0;
    }
    for (iter=0; iter<32; iter++) {
        ppc32->FPR[iter] = 0;
    }
    for (iter=0; iter<32; iter++) {
        ppc32->VR[iter] = 0;
    }
    ppc32->CR.reg = 0x0; // readonly=0
    ppc32->CR_wmask.reg = ~0;
    ppc32->CR_rmask.reg = ~0;
    ppc32->XER.reg = 0x0; // readonly=0
    ppc32->XER_wmask.reg = ~0;
    ppc32->XER_rmask.reg = ~0;
    ppc32->XER_SO = 0; // readonly=0
    ppc32->XER_OV = 0; // readonly=0
    ppc32->XER_CA = 0; // readonly=0
    for (iter=0; iter<8; iter++) {
        ppc32->LT[iter] = 0;
    }
    for (iter=0; iter<8; iter++) {
        ppc32->GT[iter] = 0;
    }
    for (iter=0; iter<8; iter++) {
        ppc32->EQ[iter] = 0;
    }
    for (iter=0; iter<8; iter++) {
        ppc32->SO[iter] = 0;
    }
    for (iter=0; iter<4; iter++) {
        ppc32->TEMP[iter] = 0;
    }
    ppc32->LR = 0x0; // readonly=0
    ppc32->CTR = 0x0; // readonly=0
    ppc32->SPR->DEC = 0; // readonly=0
    ppc32->SPR->DEC_tmr = 0; // readonly=0
    ppc32->SPR->SRR0.reg = 0x0; // readonly=0
    ppc32->SPR->SRR0_wmask.reg = ~0;
    ppc32->SPR->SRR0_rmask.reg = ~0;
    ppc32->SPR->SRR1.reg = 0x0; // readonly=0
    ppc32->SPR->SRR1_wmask.reg = ~0;
    ppc32->SPR->SRR1_rmask.reg = ~0;
    ppc32->SPR->PID0.reg = 0x0; // readonly=0
    ppc32->SPR->PID0_wmask.reg = ~0;
    ppc32->SPR->PID0_rmask.reg = ~0;
    ppc32->SPR->DECAR = 0x0; // readonly=0
    ppc32->SPR->CSRR0 = 0x0; // readonly=0
    ppc32->SPR->CSRR1 = 0x0; // readonly=0
    ppc32->SPR->DEAR = 0x0; // readonly=0
    ppc32->SPR->ESR.reg = 0x0; // readonly=0
    ppc32->SPR->ESR_wmask.reg = ~0;
    ppc32->SPR->ESR_rmask.reg = ~0;
    ppc32->SPR->IVPR.reg = 0x0; // readonly=0
    ppc32->SPR->IVPR_wmask.reg = ~0;
    ppc32->SPR->IVPR_rmask.reg = ~0;
    ppc32->SPR->SPRG0 = 0x0; // readonly=0
    ppc32->SPR->SPRG1 = 0x0; // readonly=0
    ppc32->SPR->SPRG2 = 0x0; // readonly=0
    ppc32->SPR->SPRG3 = 0x0; // readonly=0
    ppc32->SPR->SPRG4 = 0x0; // readonly=0
    ppc32->SPR->SPRG5 = 0x0; // readonly=0
    ppc32->SPR->SPRG6 = 0x0; // readonly=0
    ppc32->SPR->SPRG7 = 0x0; // readonly=0
    ppc32->SPR->TB.reg = 0x0; // readonly=0
    ppc32->SPR->TB_wmask.reg = ~0;
    ppc32->SPR->TB_rmask.reg = ~0;
    ppc32->SPR->TBU.reg = 0x0; // readonly=0
    ppc32->SPR->TBU_wmask.reg = ~0;
    ppc32->SPR->TBU_rmask.reg = ~0;
    ppc32->SPR->PIR.reg = 0x0; // readonly=0
    ppc32->SPR->PIR_wmask.reg = ~0;
    ppc32->SPR->PIR_rmask.reg = ~0;
    ppc32->SPR->PVR.reg = 0x0; // readonly=0
    ppc32->SPR->PVR_wmask.reg = ~0;
    ppc32->SPR->PVR_rmask.reg = ~0;
    ppc32->SPR->DBSR.reg = 0x0; // readonly=0
    ppc32->SPR->DBSR_wmask.reg = ~0;
    ppc32->SPR->DBSR_rmask.reg = ~0;
    ppc32->SPR->DBCR0.reg = 0x0; // readonly=0
    ppc32->SPR->DBCR0_wmask.reg = ~0;
    ppc32->SPR->DBCR0_rmask.reg = ~0;
    ppc32->SPR->DBCR1.reg = 0x0; // readonly=0
    ppc32->SPR->DBCR1_wmask.reg = ~0;
    ppc32->SPR->DBCR1_rmask.reg = ~0;
    ppc32->SPR->DBCR2.reg = 0x0; // readonly=0
    ppc32->SPR->DBCR2_wmask.reg = ~0;
    ppc32->SPR->DBCR2_rmask.reg = ~0;
    ppc32->SPR->IAC1 = 0x0; // readonly=0
    ppc32->SPR->IAC2 = 0x0; // readonly=0
    ppc32->SPR->IAC3 = 0x0; // readonly=0
    ppc32->SPR->IAC4 = 0x0; // readonly=0
    ppc32->SPR->DAC1 = 0x0; // readonly=0
    ppc32->SPR->DAC2 = 0x0; // readonly=0
    ppc32->SPR->DVC1 = 0x0; // readonly=0
    ppc32->SPR->DVC2 = 0x0; // readonly=0
    ppc32->SPR->TSR.reg = 0x0; // readonly=0
    ppc32->SPR->TSR_wmask.reg = ~0;
    ppc32->SPR->TSR_rmask.reg = ~0;
    ppc32->SPR->TCR.reg = 0x0; // readonly=0
    ppc32->SPR->TCR_wmask.reg = ~0;
    ppc32->SPR->TCR_rmask.reg = ~0;
    ppc32->SPR->IVOR0 = 0x0; // readonly=0
    ppc32->SPR->IVOR1 = 0x0; // readonly=0
    ppc32->SPR->IVOR2 = 0x0; // readonly=0
    ppc32->SPR->IVOR3 = 0x0; // readonly=0
    ppc32->SPR->IVOR4 = 0x0; // readonly=0
    ppc32->SPR->IVOR5 = 0x0; // readonly=0
    ppc32->SPR->IVOR6 = 0x0; // readonly=0
    ppc32->SPR->IVOR7 = 0x0; // readonly=0
    ppc32->SPR->IVOR8 = 0x0; // readonly=0
    ppc32->SPR->IVOR9 = 0x0; // readonly=0
    ppc32->SPR->IVOR10 = 0x0; // readonly=0
    ppc32->SPR->IVOR11 = 0x0; // readonly=0
    ppc32->SPR->IVOR12 = 0x0; // readonly=0
    ppc32->SPR->IVOR13 = 0x0; // readonly=0
    ppc32->SPR->IVOR14 = 0x0; // readonly=0
    ppc32->SPR->IVOR15 = 0x0; // readonly=0
    ppc32->SPEFSCR.reg = 0; // readonly=0
    ppc32->SPEFSCR_wmask.reg = ~0;
    ppc32->SPEFSCR_rmask.reg = ~0;
    ppc32->SPR->MCSRR0 = 0x0; // readonly=0
    ppc32->SPR->MCSRR1 = 0x0; // readonly=0
    ppc32->SPR->MCSR.reg = 0x0; // readonly=0
    ppc32->SPR->SPRG8 = 0x0; // readonly=0
    ppc32->SPR->DCDBTRL = 0x0; // readonly=0
    ppc32->SPR->DCDBTRH = 0x0; // readonly=0
    ppc32->SPR->ICDBTRL = 0x0; // readonly=0
    ppc32->SPR->ICDBTRH = 0x0; // readonly=0
    ppc32->SPR->MSR.reg = 0x0; // readonly=0
    ppc32->SPR->MSR_wmask.reg = ~0;
    ppc32->SPR->MSR_rmask.reg = ~0;

    //
    // FPSCR
    //
    ppc32->FPSCR.reg = 0x0; // readonly=0
    ppc32->FPSCR_wmask.reg = ~0;
    ppc32->FPSCR_wmask.bits.FEX = 0;
    ppc32->FPSCR_wmask.bits.VX = 0;
    ppc32->FPSCR_wmask.bits.RSV1 = 0;
    ppc32->FPSCR_wmask.bits.NI = 0;
    ppc32->FPSCR_rmask.reg = ~0;

    //
    // Reservations
    //
    ppc32->RESERVE      = 0;
    ppc32->RESERVE_ADDR = 0;

    //
    // MSR
    //
    ppc32->SPR->MSR.reg = 0;
    ppc32MaskEnable64(&ppc32->SPR->MSR_rmask.reg, True, 0, 63);
    ppc32MaskEnable64(&ppc32->SPR->MSR_wmask.reg, True, 0, 63);
    ppc32->SPR->MSR_wmask.bits.RSV0 = 0;
    ppc32->SPR->MSR_wmask.bits.RSV1 = 0;
    ppc32->SPR->MSR_wmask.bits.RSV2 = 0;
    ppc32->SPR->MSR_wmask.bits.RSV3 = 0;
    ppc32->SPR->MSR_wmask.bits.RSV4 = 0;
    //
    // Enable FPU at startup if set by parameter
    //
    ppc32->SPR->MSR.bits.FP = ppc32->params.ENABLE_FPU;
    refreshBlockMask(ppc32);

    //
    // XER
    //
    ppc32->XER.reg = 0;
    ppc32MaskEnable64(&ppc32->XER_rmask.reg, True,  0, 63);
    ppc32MaskEnable64(&ppc32->XER_wmask.reg, True, 32, 63);
    ppc32->XER_wmask.bits.RSV0 = 0;
    ppc32->XER_wmask.bits.RSV1 = 0;

    //
    // DEC
    //
    ppc32->SPR->DEC_tmr = ~(0ULL);
    ppc32->SPR->DEC = 0;

    //
    // PVR
    //
    ppc32->SPR->PVR.reg = ppc32->configInfo.pvr;

}

void ppc32mtspr_400(ppc32P ppc32, Uns16 spr, vmiReg gpr_rs, Uns8 rs) {
    //
    // Optimize for some registers
    // LR
    //
    switch (spr) {
    case LR:
        vmimtMoveRR(PPC32_GPR_BITS, PPC32_LR_WR, gpr_rs);
        break;
    case CTR:
        vmimtMoveRR(PPC32_GPR_BITS, PPC32_CTR_WR, gpr_rs);
        break;

    default:
        vmimtArgProcessor();
        vmimtArgUns32(spr);
        vmimtArgUns32(rs);
        vmimtArgUns32(0);
        vmimtCall((vmiCallFn)vmic_mtspr);
        break;
    }
}

//
// Some of this work can be done at Morph time,
// but some of this needs top be done at runtime using a runtime call back
//
void ppc32mfspr_400(ppc32P ppc32, Uns8 rt, vmiReg gpr_rt, Uns16 spr) {
    //
    // Optimize for some registers
    // LR
    //
    switch (spr) {
    case LR:
        vmimtMoveRR(PPC32_GPR_BITS, gpr_rt, PPC32_LR_RD);
        break;
    case CTR:
        vmimtMoveRR(PPC32_GPR_BITS, gpr_rt, PPC32_CTR_RD);
        break;

    default:
        vmimtArgProcessor();
        vmimtArgUns32(rt);
        vmimtArgUns32(spr);
        vmimtArgUns32(0);
        vmimtCall((vmiCallFn)vmic_mfspr);
        break;
    }
}

void ppc32mtmsr_400(ppc32P ppc32, Uns8 L, vmiReg GPR_RS, Uns8 RS) {
    vmimtArgProcessor();
    vmimtArgUns32(L);
    vmimtArgUns32(RS);
    vmimtCall((vmiCallFn)vmic_mtmsr);
}

void ppc32mfmsr_400(ppc32P ppc32, vmiReg GPR_RT, Uns8 RT) {
//    vmiReg MSR = VMI_CPU_REG_DELTA(ppc32sprP, MSR, state->ppc32->SPRdelta);
//    vmimtMoveRR(PPC32_GPR_BITS, GPR_RT, MSR);
    vmimtMoveRR(PPC32_GPR_BITS, GPR_RT, PPC32_MSR_RD(ppc32));
}

static void vmic_wrteei(ppc32P ppc32, Uns32 e) {
    //
    // Set the EE Bit
    //
    ppc32->SPR->MSR.bits.EE = e;
}

void ppc32wrteei_400(ppc32P ppc32, Uns8 e) {
    vmimtArgProcessor();
    vmimtArgUns32(e);
    vmimtCall((vmiCallFn)vmic_wrteei);
}

static void vmic_wrtee(ppc32P ppc32, Uns32 rs) {
    TYPE_MSR msr_rs;
    msr_rs.reg = ppc32->GPR[rs];

    //
    // Set the EE Bit
    //
    ppc32->SPR->MSR.bits.EE = msr_rs.bits.EE;
}

void ppc32wrtee_400(ppc32P ppc32, vmiReg GPR_RS, Uns8 RS) {
    vmimtArgProcessor();
    vmimtArgUns32(RS);
    vmimtCall((vmiCallFn)vmic_wrtee);
}

Uns32 ppc32ReadSPR_400 (ppc32P ppc32, Uns32 index) {
    Uns32 rvalue;

    switch(index) {
    case LR:
        rvalue = ppc32->LR;
        break;
    case CTR:
        rvalue = ppc32->CTR;
        break;
    default:
        vmic_mfspr(ppc32, -1, index, &rvalue);
        break;
    }
    return rvalue;
}

void ppc32WriteSPR_400 (ppc32P ppc32, Uns32 index, Uns32 value) {
    switch(index) {
    case XER:
        ppc32UnpackXER(ppc32);
        break;
    default:
        vmic_mtspr(ppc32, index, -1, &value);
        break;
    }
}

Uns32 ppc32ReadMSR_400 (ppc32P ppc32) {
    ppc32PackMSR(ppc32);
    return ppc32->SPR->MSR.reg;
}

void ppc32WriteMSR_400 (ppc32P ppc32, Uns32 value) {
    ppc32->SPR->MSR.reg = value;
    ppc32UnpackMSR(ppc32);
}

Uns8 ppc32ReadMSR_VMMode_400 (ppc32P ppc32) {
    Uns8 IR = ppc32->SPR->MSR.bits.IS;
    Uns8 DR = ppc32->SPR->MSR.bits.DS;
    Uns8 HV = 0;
    Uns8 PR = ppc32->SPR->MSR.bits.PR;

    Uns8 MODE = (IR<<3) | (DR<<2) | (HV<<1) | (PR<<0);

    return MODE;
}

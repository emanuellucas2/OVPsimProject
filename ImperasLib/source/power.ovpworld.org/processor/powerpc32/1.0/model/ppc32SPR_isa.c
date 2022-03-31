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
#include "ppc32Utils.h"
#include "ppc32VM.h"
#include "ppc32SPR_isa.h"

//
// Trace SPR Accesses
//
#define TRACE_SPR 0


// HV PR
//  0  0    Privileged
//  0  1    Problem (user)
//  1  0    Privileged and Hypervisor
//  1  1    Problem (user)

Bool ppc32IsUserMode_isa (ppc32P ppc32) {
    return (ppc32->SPR->MSR.bits.PR==1);
}
Bool ppc32IsPrivMode_isa (ppc32P ppc32) {
    return (ppc32->SPR->MSR.bits.PR==0);
}
Bool ppc32IsHypvMode_isa (ppc32P ppc32) {
    return (ppc32->SPR->MSR.bits.PR==0 && ppc32->SPR->MSR.bits.HV==1);
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
static void vmic_mtspr(ppc32P ppc32, Uns32 spr, Uns32 rs) {
    //
    // HV PR
    //  0  0  Privileged
    //  0  1  Problem (user)
    //  1  0  Privileged and Hypervisor
    //  1  1  Problem (user)
    //
    Bool user_ok = (SPR_ACCESS[spr].mtspr == NO);
    Bool priv_ok = (SPR_ACCESS[spr].mtspr == YES)  && ppc32IsPrivMode_isa(ppc32);
    Bool hypv_ok = (SPR_ACCESS[spr].mtspr == HYPV) && ppc32IsHypvMode_isa(ppc32);

    Bool ok = user_ok || priv_ok || hypv_ok;
    if (ok) {
        switch (spr) {
        case XER:
            ppc32->XER.reg = ppc32->GPR[rs] & ppc32->XER_wmask.reg;
            ppc32UnpackXER(ppc32);
            break;
        case DEC:
            ppc32->SPR->DEC_tmr = vmirtGetICount((vmiProcessorP)ppc32);
            ppc32->SPR->DEC = ppc32->GPR[rs];
            break;
        case PID:
            ppc32->SPR->PID0.bits.PID = ppc32->GPR[rs];
            break;
        case DSISR:
            ppc32->SPR->DSISR = ppc32->GPR[rs];
            break;
        case DAR:
            ppc32->SPR->DAR = ppc32->GPR[rs];
            break;
        case SRR0:
            ppc32->SPR->SRR0.reg = ppc32->GPR[rs] & ppc32->SPR->SRR0_wmask.reg;
            break;
        case SRR1:
            ppc32->SPR->SRR1.reg = ppc32->GPR[rs] & ppc32->SPR->SRR1_wmask.reg;
            break;
        case SPRG0:
            ppc32->SPR->SPRG0 = ppc32->GPR[rs];
            break;
        case SPRG1:
            ppc32->SPR->SPRG1 = ppc32->GPR[rs];
            break;
        case SPRG2:
            ppc32->SPR->SPRG2 = ppc32->GPR[rs];
            break;
        case SPRG3_2:
            ppc32->SPR->SPRG3 = ppc32->GPR[rs];
            break;
        case TBL_2:
            ppc32->SPR->TB.bits.TBL = ppc32->GPR[rs];
            break;
        case TBU_2:
            ppc32->SPR->TB.bits.TBU = ppc32->GPR[rs];
            break;

        case DSCR:
        case CFAR:
        case AMR:
        case DECAR:
        case CSRR0:
        case CSRR1:
        case DEAR:
        case ESR:
        case IVPR:
        case VRSAVE:
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
        case EAR:
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
        case IVOR0:
        case IVOR1:
        case IVOR2:
        case IVOR3:
        case IVOR4:
        case IVOR5:
        case IVOR6:
        case IVOR7:
        case IVOR8:
        case IVOR9:
        case IVOR10:
        case IVOR11:
        case IVOR12:
        case IVOR13:
        case IVOR14:
        case IVOR15:
//      case SPEFSCR:
        case ATBL:
        case ATBU:
        case IVOR32:
        case IVOR33:
        case IVOR34:
        case IVOR35:
        case IVOR36:
        case IVOR37:
        case MCSSR0:
        case MCSSR1:
        case MCSSR:
        case DSSR0:
        case DSSR1:
        case SPRG8:
        case SPRG9:
        case MAS0:
        case MAS1:
        case MAS2:
        case MAS3:
        case MAS4:
        case MAS6:
        case PID1:
        case PID2:
        case TLB0CFG:
        case TLB1CFG:
        case TLB2CFG:
        case TLB3CFG:
        case EPR:
        case DCDBTRL:
        case DCDBTRH:
        case ICDBTRL:
        case ICDBTRH:
        case MAS7:
        case EPLC:
        case EPSC:
        case ICDBDR:
        case MMUCSR0:
        case MMUCFG:
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
    Bool priv_ok = (SPR_ACCESS[spr].mfspr == YES)  && ppc32IsPrivMode_isa(ppc32);
    Bool hypv_ok = (SPR_ACCESS[spr].mfspr == HYPV) && ppc32IsHypvMode_isa(ppc32);

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
        case DSISR:
            value = ppc32->SPR->DSISR;
            break;
        case DAR:
            value = ppc32->SPR->DAR;
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

        case DSCR:
        case CFAR:
        case AMR:
        case DECAR:
        case CSRR0:
        case CSRR1:
        case DEAR:
        case ESR:
        case IVPR:
        case VRSAVE:
        case SPRG3_1:
        case SPRG4_1:
        case SPRG5_1:
        case SPRG6_1:
        case SPRG7_1:
        case SPRG4_2:
        case SPRG5_2:
        case SPRG6_2:
        case SPRG7_2:
        case EAR:
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
        case IVOR0:
        case IVOR1:
        case IVOR2:
        case IVOR3:
        case IVOR4:
        case IVOR5:
        case IVOR6:
        case IVOR7:
        case IVOR8:
        case IVOR9:
        case IVOR10:
        case IVOR11:
        case IVOR12:
        case IVOR13:
        case IVOR14:
        case IVOR15:
//      case SPEFSCR:
        case ATBL:
        case ATBU:
        case IVOR32:
        case IVOR33:
        case IVOR34:
        case IVOR35:
        case IVOR36:
        case IVOR37:
        case MCSSR0:
        case MCSSR1:
        case MCSSR:
        case DSSR0:
        case DSSR1:
        case SPRG8:
        case SPRG9:
        case MAS0:
        case MAS1:
        case MAS2:
        case MAS3:
        case MAS4:
        case MAS6:
        case PID1:
        case PID2:
        case TLB0CFG:
        case TLB1CFG:
        case TLB2CFG:
        case TLB3CFG:
        case EPR:
        case DCDBTRL:
        case DCDBTRH:
        case ICDBTRL:
        case ICDBTRH:
        case MAS7:
        case EPLC:
        case EPSC:
        case ICDBDR:
        case MMUCSR0:
        case MMUCFG:
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

static void vmic_mtmsr(ppc32P ppc32, Uns32 l, Uns32 rs) {
    TYPE_MSR msr_rs;
    msr_rs.reg = ppc32->GPR[rs];

    //
    // Special or'ing, this seems to conflict with the programming note
    //
    TYPE_MSR msr1 = ppc32->SPR->MSR;
    if (l==0) {
        ppc32->SPR->MSR.reg = msr_rs.reg & ppc32->SPR->MSR_wmask.reg;

        //
        // Special Handling of other bits
        //
        ppc32->SPR->MSR.bits.EE |= ppc32->SPR->MSR.bits.PR;   // bit 48
        ppc32->SPR->MSR.bits.IR |= ppc32->SPR->MSR.bits.PR;   // bit 58
        ppc32->SPR->MSR.bits.DR |= ppc32->SPR->MSR.bits.PR;   // bit 59
        ppc32->SPR->MSR.bits.LE  = msr1.bits.LE;         // Restore bit 63
        ppc32->SPR->MSR.bits.ME  = msr1.bits.ME;         // Restore bit 51

    } else {

        ppc32->SPR->MSR.bits.RI = msr_rs.bits.RI;
        ppc32->SPR->MSR.bits.EE = msr_rs.bits.EE;
    }

    vmirtSetMode((vmiProcessorP)ppc32, ppc32GetVMMode(ppc32));
}

void ppc32AllocSPR_isa(ppc32P ppc32) {
    //
    // Allocate the SPRs
    //
    ppc32->SPR = STYPE_CALLOC(ppc32spr);
}

void ppc32InitSPR_isa(ppc32P ppc32) {
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
    ppc32->SPR->DSCR.reg = 0x0; // readonly=0
    ppc32->SPR->DSCR_wmask.reg = ~0;
    ppc32->SPR->DSCR_rmask.reg = ~0;
    ppc32->SPR->DSISR = 0x0; // readonly=0
    ppc32->SPR->DAR = 0x0; // readonly=0
    ppc32->SPR->DEC = 0; // readonly=0
    ppc32->SPR->DEC_tmr = 0; // readonly=0
    ppc32->SPR->SDR1.reg = 0x0; // readonly=0
    ppc32->SPR->SDR1_wmask.reg = ~0;
    ppc32->SPR->SDR1_rmask.reg = ~0;
    ppc32->SPR->SRR0.reg = 0x0; // readonly=0
    ppc32->SPR->SRR0_wmask.reg = ~0;
    ppc32->SPR->SRR0_rmask.reg = ~0;
    ppc32->SPR->SRR1.reg = 0x0; // readonly=0
    ppc32->SPR->SRR1_wmask.reg = ~0;
    ppc32->SPR->SRR1_rmask.reg = ~0;
    ppc32->SPR->CFAR.reg = 0x0; // readonly=0
    ppc32->SPR->CFAR_wmask.reg = ~0;
    ppc32->SPR->CFAR_rmask.reg = ~0;
    ppc32->SPR->AMR.reg = 0x0; // readonly=0
    ppc32->SPR->AMR_wmask.reg = ~0;
    ppc32->SPR->AMR_rmask.reg = ~0;
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
    ppc32->SPR->CTRL.reg = 0x0; // readonly=0
    ppc32->SPR->CTRL_wmask.reg = ~0;
    ppc32->SPR->CTRL_rmask.reg = ~0;
    ppc32->SPR->VRSAVE = 0; // readonly=0
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
    ppc32->SPR->EAR.reg = 0x0; // readonly=0
    ppc32->SPR->EAR_wmask.reg = ~0;
    ppc32->SPR->EAR_rmask.reg = ~0;
    ppc32->SPR->PIR.reg = 0x0; // readonly=0
    ppc32->SPR->PIR_wmask.reg = ~0;
    ppc32->SPR->PIR_rmask.reg = ~0;
    ppc32->SPR->PVR.reg = 0x0; // readonly=0
    ppc32->SPR->PVR_wmask.reg = ~0;
    ppc32->SPR->PVR_rmask.reg = ~0;
    for (iter=0; iter<2; iter++) {
        ppc32->SPR->HSPRG[iter] = 0;
    }
    ppc32->SPR->DBSR.reg = 0x0; // readonly=0
    ppc32->SPR->DBSR_wmask.reg = ~0;
    ppc32->SPR->DBSR_rmask.reg = ~0;
    ppc32->SPR->HDSISR = 0x0; // readonly=0
    ppc32->SPR->HDAR = 0x0; // readonly=0
    ppc32->SPR->DBCR0.reg = 0x0; // readonly=0
    ppc32->SPR->DBCR0_wmask.reg = ~0;
    ppc32->SPR->DBCR0_rmask.reg = ~0;
    ppc32->SPR->SPURR = 0x0; // readonly=0
    ppc32->SPR->PURR = 0x0; // readonly=0
    ppc32->SPR->DBCR1.reg = 0x0; // readonly=0
    ppc32->SPR->DBCR1_wmask.reg = ~0;
    ppc32->SPR->DBCR1_rmask.reg = ~0;
    ppc32->SPR->HDEC = 0x0; // readonly=0
    ppc32->SPR->DBCR2.reg = 0x0; // readonly=0
    ppc32->SPR->DBCR2_wmask.reg = ~0;
    ppc32->SPR->DBCR2_rmask.reg = ~0;
    ppc32->SPR->RMOR.reg = 0x0; // readonly=0
    ppc32->SPR->RMOR_wmask.reg = ~0;
    ppc32->SPR->RMOR_rmask.reg = ~0;
    ppc32->SPR->IAC1 = 0x0; // readonly=0
    ppc32->SPR->IAC2 = 0x0; // readonly=0
    ppc32->SPR->IAC3 = 0x0; // readonly=0
    ppc32->SPR->IAC4 = 0x0; // readonly=0
    ppc32->SPR->HRMOR.reg = 0x0; // readonly=0
    ppc32->SPR->HRMOR_wmask.reg = ~0;
    ppc32->SPR->HRMOR_rmask.reg = ~0;
    ppc32->SPR->HSRR0.reg = 0x0; // readonly=0
    ppc32->SPR->HSRR0_wmask.reg = ~0;
    ppc32->SPR->HSRR0_rmask.reg = ~0;
    ppc32->SPR->HSRR1 = 0x0; // readonly=0
    ppc32->SPR->DAC1 = 0x0; // readonly=0
    ppc32->SPR->DAC2 = 0x0; // readonly=0
    ppc32->SPR->LPCR.reg = 0x0; // readonly=0
    ppc32->SPR->LPCR_wmask.reg = ~0;
    ppc32->SPR->LPCR_rmask.reg = ~0;
    ppc32->SPR->DVC1 = 0x0; // readonly=0
    ppc32->SPR->DVC2 = 0x0; // readonly=0
    ppc32->SPR->LPIDR.reg = 0x0; // readonly=0
    ppc32->SPR->LPIDR_wmask.reg = ~0;
    ppc32->SPR->LPIDR_rmask.reg = ~0;
    ppc32->SPR->TSR.reg = 0x0; // readonly=0
    ppc32->SPR->TSR_wmask.reg = ~0;
    ppc32->SPR->TSR_rmask.reg = ~0;
    ppc32->SPR->HMER = 0x0; // readonly=0
    ppc32->SPR->HMEER = 0x0; // readonly=0
    ppc32->SPR->PCR.reg = 0x0; // readonly=0
    ppc32->SPR->PCR_wmask.reg = ~0;
    ppc32->SPR->PCR_rmask.reg = ~0;
    ppc32->SPR->HEIR = 0x0; // readonly=0
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
    ppc32->SPR->ATB.reg = 0x0; // readonly=0
    ppc32->SPR->ATB_wmask.reg = ~0;
    ppc32->SPR->ATB_rmask.reg = ~0;
    ppc32->SPR->IVOR32 = 0x0; // readonly=0
    ppc32->SPR->IVOR33 = 0x0; // readonly=0
    ppc32->SPR->IVOR34 = 0x0; // readonly=0
    ppc32->SPR->IVOR35 = 0x0; // readonly=0
    ppc32->SPR->IVOR36 = 0x0; // readonly=0
    ppc32->SPR->IVOR37 = 0x0; // readonly=0
    ppc32->SPR->MCSRR0 = 0x0; // readonly=0
    ppc32->SPR->MCSRR1 = 0x0; // readonly=0
    ppc32->SPR->MCSR = 0x0; // readonly=0
    ppc32->SPR->DSRR0 = 0x0; // readonly=0
    ppc32->SPR->DSRR1 = 0x0; // readonly=0
    ppc32->SPR->SPRG8 = 0x0; // readonly=0
    ppc32->SPR->SPRG9 = 0x0; // readonly=0
    ppc32->SPR->MAS0.reg = 0x0; // readonly=0
    ppc32->SPR->MAS0_wmask.reg = ~0;
    ppc32->SPR->MAS0_rmask.reg = ~0;
    ppc32->SPR->MAS1.reg = 0x0; // readonly=0
    ppc32->SPR->MAS1_wmask.reg = ~0;
    ppc32->SPR->MAS1_rmask.reg = ~0;
    ppc32->SPR->MAS2.reg = 0x0; // readonly=0
    ppc32->SPR->MAS2_wmask.reg = ~0;
    ppc32->SPR->MAS2_rmask.reg = ~0;
    ppc32->SPR->MAS3.reg = 0x0; // readonly=0
    ppc32->SPR->MAS3_wmask.reg = ~0;
    ppc32->SPR->MAS3_rmask.reg = ~0;
    ppc32->SPR->MAS4.reg = 0x0; // readonly=0
    ppc32->SPR->MAS4_wmask.reg = ~0;
    ppc32->SPR->MAS4_rmask.reg = ~0;
    ppc32->SPR->MAS6.reg = 0x0; // readonly=0
    ppc32->SPR->MAS6_wmask.reg = ~0;
    ppc32->SPR->MAS6_rmask.reg = ~0;
    ppc32->SPR->MAS7.reg = 0x0; // readonly=0
    ppc32->SPR->MAS7_wmask.reg = ~0;
    ppc32->SPR->MAS7_rmask.reg = ~0;
    ppc32->SPR->PID1.reg = 0x0; // readonly=0
    ppc32->SPR->PID1_wmask.reg = ~0;
    ppc32->SPR->PID1_rmask.reg = ~0;
    ppc32->SPR->PID2.reg = 0x0; // readonly=0
    ppc32->SPR->PID2_wmask.reg = ~0;
    ppc32->SPR->PID2_rmask.reg = ~0;
    ppc32->SPR->TLB0CFG.reg = 0x0; // readonly=0
    ppc32->SPR->TLB0CFG_wmask.reg = ~0;
    ppc32->SPR->TLB0CFG_rmask.reg = ~0;
    ppc32->SPR->TLB1CFG.reg = 0x0; // readonly=0
    ppc32->SPR->TLB1CFG_wmask.reg = ~0;
    ppc32->SPR->TLB1CFG_rmask.reg = ~0;
    ppc32->SPR->TLB2CFG.reg = 0x0; // readonly=0
    ppc32->SPR->TLB2CFG_wmask.reg = ~0;
    ppc32->SPR->TLB2CFG_rmask.reg = ~0;
    ppc32->SPR->TLB3CFG.reg = 0x0; // readonly=0
    ppc32->SPR->TLB3CFG_wmask.reg = ~0;
    ppc32->SPR->TLB3CFG_rmask.reg = ~0;
    ppc32->SPR->EPR = 0x0; // readonly=0
    for (iter=0; iter<16; iter++) {
        ppc32->SPR->perf_mon[iter] = 0x0;
    }
    ppc32->SPR->PPR.reg = 0x0; // readonly=0
    ppc32->SPR->PPR_wmask.reg = ~0;
    ppc32->SPR->PPR_rmask.reg = ~0;
    ppc32->SPR->DCDBTRL = 0x0; // readonly=0
    ppc32->SPR->DCDBTRH = 0x0; // readonly=0
    ppc32->SPR->ICDBTRL = 0x0; // readonly=0
    ppc32->SPR->ICDBTRH = 0x0; // readonly=0
    ppc32->SPR->EPLC.reg = 0x0; // readonly=0
    ppc32->SPR->EPLC_wmask.reg = ~0;
    ppc32->SPR->EPLC_rmask.reg = ~0;
    ppc32->SPR->EPSC.reg = 0x0; // readonly=0
    ppc32->SPR->EPSC_wmask.reg = ~0;
    ppc32->SPR->EPSC_rmask.reg = ~0;
    ppc32->SPR->ICDBDR = 0x0; // readonly=0
    ppc32->SPR->MMUCSR0.reg = 0x0; // readonly=0
    ppc32->SPR->MMUCSR0_wmask.reg = ~0;
    ppc32->SPR->MMUCSR0_rmask.reg = ~0;
    ppc32->SPR->DABR.reg = 0x0; // readonly=0
    ppc32->SPR->DABR_wmask.reg = ~0;
    ppc32->SPR->DABR_rmask.reg = ~0;
    ppc32->SPR->DABRX.reg = 0x0; // readonly=0
    ppc32->SPR->DABRX_wmask.reg = ~0;
    ppc32->SPR->DABRX_rmask.reg = ~0;
    ppc32->SPR->MMUCFG.reg = 0x0; // readonly=0
    ppc32->SPR->MMUCFG_wmask.reg = ~0;
    ppc32->SPR->MMUCFG_rmask.reg = ~0;
    ppc32->FPSCR.reg = 0x0; // readonly=0
    ppc32->FPSCR_wmask.reg = ~0;
    ppc32->FPSCR_rmask.reg = ~0;
    ppc32->SPR->VSCR.reg = 0; // readonly=0
    ppc32->SPR->VSCR_wmask.reg = ~0;
    ppc32->SPR->VSCR_rmask.reg = ~0;
    ppc32->SPR->Accumulator = 0; // readonly=0
    ppc32->SPR->MSR.reg = 0x0; // readonly=0
    ppc32->SPR->MSR_wmask.reg = ~0;
    ppc32->SPR->MSR_rmask.reg = ~0;

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
    ppc32->SPR->MSR_wmask.bits.RSV5 = 0;

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

void ppc32mtspr_isa(ppc32P ppc32, Uns16 spr, vmiReg gpr_rs, Uns8 rs) {
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
        vmimtCall((vmiCallFn)vmic_mtspr);
        break;
    }
}

//
// Some of this work can be done at Morph time,
// but some of this needs top be done at runtime using a runtime call back
//
void ppc32mfspr_isa(ppc32P ppc32, Uns8 rt, vmiReg gpr_rt, Uns16 spr) {
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

void ppc32mtmsr_isa(ppc32P ppc32, Uns8 L, vmiReg GPR_RS, Uns8 RS) {
    vmimtArgProcessor();
    vmimtArgUns32(L);
    vmimtArgUns32(RS);
    vmimtCall((vmiCallFn)vmic_mtmsr);
}

void ppc32mfmsr_isa(ppc32P ppc32, vmiReg GPR_RT, Uns8 RT) {
    vmimtMoveRR(PPC32_GPR_BITS, GPR_RT, PPC32_MSR_RD(ppc32));
}

static void vmic_wrteei(ppc32P ppc32, Uns32 e) {
    //
    // Set the EE Bit
    //
    ppc32->SPR->MSR.bits.EE = e;
}

void ppc32wrteei_isa(ppc32P ppc32, Uns8 E) {
    vmimtArgProcessor();
    vmimtArgUns32(E);
    vmimtCall((vmiCallFn)vmic_wrteei);
}

static void vmic_wrtee(ppc32P ppc32, Uns8 rs) {
    TYPE_MSR msr_rs;
    msr_rs.reg = ppc32->GPR[rs];

    //
    // Set the EE Bit
    //
    ppc32->SPR->MSR.bits.EE = msr_rs.bits.EE;
}

void ppc32wrtee_isa(ppc32P ppc32, vmiReg GPR_RS, Uns8 RS) {
    vmimtArgProcessor();
    vmimtArgUns32(RS);
    vmimtCall((vmiCallFn)vmic_wrtee);
}

Uns32 ppc32ReadSPR_isa (ppc32P ppc32, Uns32 index) {
    Uns32 rvalue;

    switch(index) {
//    case XER:
//        ppc32PackXER(ppc32);
//        return ppc32->XER.reg;
//        break;
    case LR:
        rvalue = ppc32->LR;
        break;
    case CTR:
        rvalue = ppc32->CTR;
        break;
//    case SRR0:
//        return ppc32->SPR->SRR0.reg;
//        break;
//    case SRR1:
//        return ppc32->SPR->SRR1.reg;
//        break;
    default:
        vmic_mfspr(ppc32, -1, index, &rvalue);
        break;
    }
    return rvalue;
}

void ppc32WriteSPR_isa (ppc32P ppc32, Uns32 index, Uns32 value) {
    switch(index) {
    case XER:
        ppc32UnpackXER(ppc32);
        break;
    }

    vmiMessage("F", "NOTIMP", "ppc32WriteSPR_isa Index %d", index);
}

Uns32 ppc32ReadMSR_isa (ppc32P ppc32) {
    ppc32PackMSR(ppc32);
    return ppc32->SPR->MSR.reg;
}

void ppc32WriteMSR_isa (ppc32P ppc32, Uns32 value) {
    ppc32UnpackMSR(ppc32);
}

Uns8 ppc32ReadMSR_VMMode_isa (ppc32P ppc32) {
    Uns8 IR = ppc32->SPR->MSR.bits.IR;
    Uns8 DR = ppc32->SPR->MSR.bits.DR;
    Uns8 HV = ppc32->SPR->MSR.bits.HV;
    Uns8 PR = ppc32->SPR->MSR.bits.PR;

    Uns8 MODE = (IR<<3) | (DR<<2) | (HV<<1) | (PR<<0);

    return MODE;
}

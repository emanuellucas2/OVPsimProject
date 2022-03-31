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

#include "vmi/vmiCxt.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "v850Exceptions.h"
#include "v850Functions.h"
#include "v850Decode.h"
#include "v850Utils.h"

VMI_ENDIAN_FN(v850GetEndian) {
    v850P v850 = (v850P)processor;
    if (isFetch) {
        return v850->iendian;
    } else {
        return v850->dendian;
    }
}

VMI_NEXT_PC_FN(v850nextPC) {
    v850InstructionInfo info = {0};
    v850Decode((v850P)processor, thisPC, &info);
    v850Addr nextAddress = info.nextPC;
    return nextAddress;
}

////////////////////////////////////////////////////////////////////////////////
// PROCESSOR RUN STATE TRANSITION HANDLING
////////////////////////////////////////////////////////////////////////////////

static void v850AbortExclusiveAccess(v850P v850);

//
// If this memory access callback is triggered, abort any active load linked
//
static VMI_MEM_WATCH_FN(abortEA) {
    if(processor) {
        v850AbortExclusiveAccess((v850P)userData);
    }
}

//
// Install or remove the exclusive access monitor callback
//
static void updateExclusiveAccessCallback(v850P v850, Bool install) {

    memDomainP domain  = vmirtGetProcessorDataDomain((vmiProcessorP)v850);
    Uns32      simLow  = v850->REG_LL & ~(V850_LLSIZE-1);
    Uns32      simHigh = simLow + (V850_LLSIZE-1);

    // install or remove a watchpoint on the current exclusive access address
    if(install) {
        vmirtAddWriteCallback(domain, 0, simLow, simHigh, abortEA, v850);
    } else {
        vmirtRemoveWriteCallback(domain, 0, simLow, simHigh, abortEA, v850);
    }
}

//
// Abort any active exclusive access
//
static void v850AbortExclusiveAccess(v850P v850) {

    if(v850->FLG_LL == True) {
        // remove callback on exclusive access monitor region
        updateExclusiveAccessCallback(v850, False);

        // clear exclusive tag (AFTER updateExclusiveAccessCallback)
        v850->FLG_LL = False;
    }
}

//
// Install or remove the exclusive access monitor callback if required
//
void v850UpdateExclusiveAccessCallback(v850P v850, Bool install) {
    if(v850->FLG_LL == True) {
        updateExclusiveAccessCallback(v850, install);
    }
}

VMI_IASSWITCH_FN(v850Switch) {
    v850P v850 = (v850P) processor;
    v850UpdateExclusiveAccessCallback(v850, state==RS_SUSPEND);
}

static const vmiModeInfo modes[] = {
    { "SUPERVISOR",     RH850_M_SUPERVISOR,     "Supervisor mode" },
    { "USER",           RH850_M_USER,           "User mode" },
    { "SUPERVISOR_MPU", RH850_M_SUPERVISOR_MPU, "Supervisor mode MPU" },
    { "USER_MPU",       RH850_M_USER_MPU,       "User mode MPU" },
    { 0, 0, 0 }
};

static Bool variantHasModes(v850P v850) {
    if (v850->configInfo.arch == RH850G3M) {
        return True;
    } else {
        return False;
    }
}

VMI_GET_MODE_FN(v850GetMode) {
    return &modes[v850GetVMMode((v850P)processor)];
}

VMI_MODE_INFO_FN(v850ModeInfo) {
    v850P v850 = (v850P)processor;

    //
    // Does this variant have modes ?
    //
    if (variantHasModes(v850) == 0) {
        return 0;
    }

    // on the first call, start with the first member of the table
    if(!prev) {
        prev = modes-1;
    }

    // get the next member
    vmiModeInfoCP this = prev+1;

    // return the next member, or NULL if at the end of the list
    return (this->name) ? this : 0;
}

void v850UnPackPSW(v850P v850) {

    v850SetVMMode(v850);

    v850->FLG_PSW_ZR  = v850->SPR_PSW.Z;
    v850->FLG_PSW_SI  = v850->SPR_PSW.S;
    v850->FLG_PSW_OV  = v850->SPR_PSW.OV;
    v850->FLG_PSW_CO  = v850->SPR_PSW.CY;
    v850->FLG_PSW_SAT = v850->SPR_PSW.SAT;
    v850->FLG_PSW_ID  = v850->SPR_PSW.ID;
    v850->FLG_PSW_EP  = v850->SPR_PSW.EP;
    v850->FLG_PSW_NP  = v850->SPR_PSW.NP;

    //
    // Execution levels determined by
    // NPV, DMP, IMP
    //   0    0    0    Exception Handler, OS Kernel etc
    //   0    1    0
    //   0    0    1
    //   0    1    1    OS Kernel Protected
    //   1    0    0    Common Library
    //   1    1    0
    //   1    0    1
    //   1    1    1    User Tasks
    //
}

Uns32 v850PackPSW(v850P v850) {
    v850->SPR_PSW.Z   = v850->FLG_PSW_ZR;
    v850->SPR_PSW.S   = v850->FLG_PSW_SI;
    v850->SPR_PSW.OV  = v850->FLG_PSW_OV;
    v850->SPR_PSW.CY  = v850->FLG_PSW_CO;
    v850->SPR_PSW.SAT = v850->FLG_PSW_SAT;
    v850->SPR_PSW.ID  = v850->FLG_PSW_ID;
    v850->SPR_PSW.EP  = v850->FLG_PSW_EP;
    v850->SPR_PSW.NP  = v850->FLG_PSW_NP;

    return v850->SPR_PSW.reg;
}

void v850UnPackEFG(v850P v850) {
    Uns32 efg = 0;
    v850->FLG_EFG_FPZ         = v850->SPR_EFG.Z;
    v850->FLG_EFG_FPS         = v850->SPR_EFG.S;
    v850->FLG_EFG_FPOV        = v850->SPR_EFG.OV;
    v850->FLG_FPF_STICKY  = v850->SPR_EFG.TR;

    efg |= v850->SPR_EFG.IV << 0;
    efg |= v850->SPR_EFG.RO << 1;
    efg |= v850->SPR_EFG.ZD << 2;
    efg |= v850->SPR_EFG.VF << 3;
    efg |= v850->SPR_EFG.UD << 4;
    efg |= v850->SPR_EFG.PR << 5;

    v850->FLG_FPF = efg;

    /*
    vmiFPFlags flags;
    flags.bits = 0;
    flags.f.I = v850->SPR_EFG.IV;
    flags.f.D = v850->SPR_EFG.RO;
    flags.f.Z = v850->SPR_EFG.ZD;
    flags.f.O = v850->SPR_EFG.VF;
    flags.f.U = v850->SPR_EFG.UD;
    flags.f.P = v850->SPR_EFG.PR;
    v850->FLG_FPF = flags;
    */
}

Uns32 v850PackEFG(v850P v850) {
    v850->SPR_EFG.Z  = v850->FLG_EFG_FPZ;
    v850->SPR_EFG.S  = v850->FLG_EFG_FPS;
    v850->SPR_EFG.OV = v850->FLG_EFG_FPOV;
    v850->SPR_EFG.TR = (v850->FLG_FPF_STICKY != 0) ? 1 : 0;   // Sticky TR Bit

    v850->SPR_EFG.IV = (v850->FLG_FPF & 0x01)      ? 1 : 0;   // Invalid Operation Bit
    v850->SPR_EFG.RO = (v850->FLG_FPF & 0x02)      ? 1 : 0;   // Reserved Operand Bit
    v850->SPR_EFG.ZD = (v850->FLG_FPF & 0x04)      ? 1 : 0;   // Divide-By-Zero Bit
    v850->SPR_EFG.VF = (v850->FLG_FPF & 0x08)      ? 1 : 0;   // Overflow Bit
    v850->SPR_EFG.UD = (v850->FLG_FPF & 0x10)      ? 1 : 0;   // Underflow Bit
    v850->SPR_EFG.PR = (v850->FLG_FPF & 0x20)      ? 1 : 0;   // Precision Bit

    return v850->SPR_EFG.reg;
}

//
// The master registers are
// v850->SPR_EIIC.reg
// v850->SPR_FEIC.reg
//
Uns32 v850PackECR(v850P v850) {
    v850->SPR_ECR.EICC = v850->SPR_EIIC.ECC;
    v850->SPR_ECR.FECC = v850->SPR_FEIC.ECC;

    return v850->SPR_ECR.reg;
}

void v850UnPackECR(v850P v850) {
    v850->SPR_EIIC.ECC = v850->SPR_ECR.EICC;
    v850->SPR_FEIC.ECC = v850->SPR_ECR.FECC;
}

//
// Preservation bits
//
#define UNPACK_XP(SREG) {                        \
    vmiFPFlags flagsSticky = { 0 };              \
    flagsSticky.f.P = v850->SPR_ ## SREG .XP_I;  \
    flagsSticky.f.U = v850->SPR_ ## SREG .XP_U;  \
    flagsSticky.f.O = v850->SPR_ ## SREG .XP_O;  \
    flagsSticky.f.Z = v850->SPR_ ## SREG .XP_Z;  \
    flagsSticky.f.I = v850->SPR_ ## SREG .XP_V;  \
    v850->FLG_FPF_STICKY = flagsSticky.bits;     \
}
#define PACK_XP(SREG) {                                   \
    vmiFPFlags flagsSticky = {bits:v850->FLG_FPF_STICKY}; \
    v850->SPR_ ## SREG .XP_I = flagsSticky.f.P;           \
    v850->SPR_ ## SREG .XP_U = flagsSticky.f.U;           \
    v850->SPR_ ## SREG .XP_O = flagsSticky.f.O;           \
    v850->SPR_ ## SREG .XP_Z = flagsSticky.f.Z;           \
    v850->SPR_ ## SREG .XP_V = flagsSticky.f.I;           \
}

//
// Cause bits (need to add XC_E bit)
//
#define UNPACK_XC(SREG) {                  \
    vmiFPFlags flags = { 0 };              \
    flags.f.P = v850->SPR_ ## SREG .XC_I;  \
    flags.f.U = v850->SPR_ ## SREG .XC_U;  \
    flags.f.O = v850->SPR_ ## SREG .XC_O;  \
    flags.f.Z = v850->SPR_ ## SREG .XC_Z;  \
    flags.f.I = v850->SPR_ ## SREG .XC_V;  \
    v850->FLG_FPF = flags.bits;            \
}
#define PACK_XC(SREG) {                      \
    vmiFPFlags flags = {bits:v850->FLG_FPF}; \
    v850->SPR_ ## SREG .XC_I = flags.f.P;    \
    v850->SPR_ ## SREG .XC_U = flags.f.U;    \
    v850->SPR_ ## SREG .XC_O = flags.f.O;    \
    v850->SPR_ ## SREG .XC_Z = flags.f.Z;    \
    v850->SPR_ ## SREG .XC_V = flags.f.I;    \
}

//
// CondCode bits
//
#define UNPACK_CC(SREG) {                        \
    v850->FLG_FPSR_CC[0] = v850->SPR_ ## SREG .CC0;  \
    v850->FLG_FPSR_CC[1] = v850->SPR_ ## SREG .CC1;  \
    v850->FLG_FPSR_CC[2] = v850->SPR_ ## SREG .CC2;  \
    v850->FLG_FPSR_CC[3] = v850->SPR_ ## SREG .CC3;  \
    v850->FLG_FPSR_CC[4] = v850->SPR_ ## SREG .CC4;  \
    v850->FLG_FPSR_CC[5] = v850->SPR_ ## SREG .CC5;  \
    v850->FLG_FPSR_CC[6] = v850->SPR_ ## SREG .CC6;  \
    v850->FLG_FPSR_CC[7] = v850->SPR_ ## SREG .CC7;  \
}

#define PACK_CC(SREG) {                           \
    v850->SPR_ ## SREG .CC0  = v850->FLG_FPSR_CC[0];  \
    v850->SPR_ ## SREG .CC1  = v850->FLG_FPSR_CC[1];  \
    v850->SPR_ ## SREG .CC2  = v850->FLG_FPSR_CC[2];  \
    v850->SPR_ ## SREG .CC3  = v850->FLG_FPSR_CC[3];  \
    v850->SPR_ ## SREG .CC4  = v850->FLG_FPSR_CC[4];  \
    v850->SPR_ ## SREG .CC5  = v850->FLG_FPSR_CC[5];  \
    v850->SPR_ ## SREG .CC6  = v850->FLG_FPSR_CC[6];  \
    v850->SPR_ ## SREG .CC7  = v850->FLG_FPSR_CC[7];  \
}


void v850UnPackFPSR(v850P v850) {

    //
    // Preservation Bits
    //
    UNPACK_XP(FPSR);

    //
    // Cause Bits
    //
    UNPACK_XC(FPSR);

    //
    // CC Bits
    //
    UNPACK_CC(FPSR);
}

Uns32 v850PackFPSR(v850P v850) {

    //
    // Preservation Bits
    //
    PACK_XP(FPSR);

    //
    // Cause Bits
    //
    PACK_XC(FPSR)

    //
    // CC Bits
    //
    PACK_CC(FPSR);

    return v850->SPR_FPSR.reg;
}

void v850UnPackFPST(v850P v850) {

    //
    // Preservation Bits
    //
    UNPACK_XP(FPST);

    //
    // Cause Bits
    //
    UNPACK_XC(FPST);
}

Uns32 v850PackFPST(v850P v850) {
    //
    // Preservation Bits
    //
    PACK_XP(FPST);

    //
    // Cause Bits
    //
    PACK_XC(FPST);

    //
    // PR bit on V850
    //
    v850->SPR_FPST.PR = v850->SPR_FPSR.PR;

    return v850->SPR_FPST.reg;
}

void v850UnPackFPCC(v850P v850) {

    //
    // CC Bits
    //
    UNPACK_CC(FPCC);
}

Uns32 v850PackFPCC(v850P v850) {

    //
    // CC Bits
    //
    PACK_CC(FPCC);

    return v850->SPR_FPCC.reg;
}

Uns32 v850PackFPCFG(v850P v850) {

    //
    // Copy FPSR.XE -> FPCFG.XE
    //
    v850->SPR_FPCFG.XE_I = v850->SPR_FPSR.XE_I;
    v850->SPR_FPCFG.XE_U = v850->SPR_FPSR.XE_U;
    v850->SPR_FPCFG.XE_O = v850->SPR_FPSR.XE_O;
    v850->SPR_FPCFG.XE_Z = v850->SPR_FPSR.XE_Z;
    v850->SPR_FPCFG.XE_V = v850->SPR_FPSR.XE_V;

    v850->SPR_FPCFG.RM   = v850->SPR_FPSR.RM;

    return v850->SPR_FPCFG.reg;
}

void v850UnPackFPCFG(v850P v850) {

    //
    // Copy FPCFG.XE -> FPSR.XE
    //
    v850->SPR_FPSR.XE_I = v850->SPR_FPCFG.XE_I;
    v850->SPR_FPSR.XE_U = v850->SPR_FPCFG.XE_U;
    v850->SPR_FPSR.XE_O = v850->SPR_FPCFG.XE_O;
    v850->SPR_FPSR.XE_Z = v850->SPR_FPCFG.XE_Z;
    v850->SPR_FPSR.XE_V = v850->SPR_FPCFG.XE_V;

    v850->SPR_FPSR.RM   = v850->SPR_FPCFG.RM;
}


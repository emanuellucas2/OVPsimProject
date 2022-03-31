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

#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "v850Exceptions.h"
#include "v850Decode.h"
#include "v850Morph.h"
#include "v850Functions.h"
#include "v850MorphFP.h"
#include "v850MPU.h"
#include "v850Instructions.h"
#include "v850Structure.h"
#include "v850Utils.h"

typedef union {
    Uns32 reg;
    struct {
        Uns32   NUM : 16;
        Uns32   PRI :  8;
        Uns32   PAD :  7;
        Uns32  MODE :  1;
    };
} RH850_EEINT;


//
// Return processor mode
//
v850Mode v850GetVMMode(v850P v850) {
    return v850->mode;
}

//
// Check SPR_PSW.UM and update v850 mode if changed
//
void v850SetVMMode(v850P v850) {
    //
    // Possible Modes
    //    RH850_M_SUPERVISOR,     0
    //    RH850_M_USER,           1
    //    RH850_M_SUPERVISOR_MPU, 2
    //    RH850_M_USER_MPU,       3
    //
    Bool mpe = v850->SPR_MPM.MPE;   // MPU Enabled
    Bool svp = v850->SPR_MPM.SVP;   // SuperVisor Protection Enabled
    Bool um  = v850->SPR_PSW.UM;    // User Mode

    // RH850_M_SUPERVISOR     =           um==0 && svp==0
    // RH850_M_USER           = mpe==0 && um==1
    // RH850_M_SUPERVISOR_MPU = mpe==1 && um==0 && svp==1
    // RH850_M_USER_MPU       = mpe==1 && um==1

    v850Mode mode  = RH850_M_SUPERVISOR;
    char *nextMode = "RH850_M_SUPERVISOR";

    if (!um && !svp) {
        mode     = RH850_M_SUPERVISOR;
        nextMode = "RH850_M_SUPERVISOR";
    } else if (!mpe && um) {
        mode     = RH850_M_USER;
        nextMode = "RH850_M_USER";

    } else if (mpe && !um && svp) {
        mode     = RH850_M_SUPERVISOR_MPU;
        nextMode = "RH850_M_SUPERVISOR_MPU";

    } else if (mpe && um) {
        mode     = RH850_M_USER_MPU;
        nextMode = "RH850_M_USER_MPU";
    }

    //
    // Mode change ?
    //
    if(v850->mode != mode) {
        if (V850_DEBUG_MPU(v850)) {
            char *currMode = "RH850_M_SUPERVISOR";

            if (v850->mode == RH850_M_SUPERVISOR) {
                currMode = "RH850_M_SUPERVISOR";

            } else if (v850->mode == RH850_M_USER) {
                currMode = "RH850_M_USER";

            } else if (v850->mode == RH850_M_SUPERVISOR_MPU) {
                currMode = "RH850_M_SUPERVISOR_MPU";

            } else if (v850->mode == RH850_M_USER_MPU) {
                currMode = "RH850_M_USER_MPU";
            }

            vmiPrintf("Change CPU Mode %s -> %s\n", currMode, nextMode);
        }

        v850->mode = mode;
        vmirtSetMode((vmiProcessorP)v850, v850->mode);
    }
}

//
// mask is a pointer to the mask register in the structure
// left and right are the indices 0..31, so reverse format
// similar to the PPC
//
void v850MaskEnable(Uns32 *mask, Bool Enable, Uns32 left, Uns32 right) {
    //
    // set bits left downto right (inclusive) to be the value '1' in the mask
    //
    Uns32 l = 31 - left;
    Uns32 r = 31 - right;
    Uns32 addmask = 0xffffffff;

    if (Enable) {
        *mask |= VECINDEX(addmask, l, r, r);
    } else {
        *mask &= ~(VECINDEX(addmask, l, r, r));
    }
}

inline static Bool isHalted(v850P v850) {
    return vmirtIsHalted((vmiProcessorP)v850);
}

//
// Is NMI interrupt pending and enabled?
//
inline static Bool nmiPendingAndEnabled(v850P v850) {
    Bool enabled = False;

    if (v850->FLG_RSTPEND) {
        // Held in reset
        return False;
    }

    if (v850->FLG_NMIPEND) {
        if (v850->FLG_PSW_NP) {
            //
            // NMI Interrupt Pending
            //
        } else {
            //
            // Begin Interrupt Service
            //
            enabled = True;
        }
    }
    return enabled;
}

//
// Is INTP interrupt pending and enabled?
//
inline static Bool intpPendingAndEnabled(v850P v850) {
    Bool enabled = False;

    if (v850->FLG_RSTPEND) {
        // Held in reset
        return False;
    }

    //
    // Check Maskable interrupt
    //
    if (v850->FLG_INTPEND) {
        if (v850->FLG_PSW_NP) {
            //
            // NMI Interrupt Pending
            //
        } else {
            if (v850->configInfo.arch == RH850G3M) {
                Uns32 int_net = v850->netValue.intp;
                Uns32 int_pri = (int_net & 0x00FF0000) >> 16;
                Uns32 int_msk = (1 << (int_pri + 1)) - 1;       // equal or higher priority bit than this interrupt

                if (v850->FLG_PSW_ID == 1) {
                    //
                    // INTP Disabled
                    //
                } else if (int_msk & v850->SPR_ISPR.reg) {
                    //
                    // ISPR Masked
                    //
                } else if (int_msk & v850->SPR_PMR.reg) {
                    //
                    // PMR Masked
                    //

                    // RH850G3M UM 3.3.1 (4) ICSR - Interrupt control status
                    // ICSR.PMEI
                    // This bit indicates that an interrupt (EIINTn) with the priority level masked by the PMR register exists.
                    v850->SPR_ICSR.PMEI = 1;

                } else {
                    //
                    // Begin Interrupt Service
                    //
                    enabled = True;
                }
            } else {
                if (v850->FLG_PSW_ID == 1) {
                    //
                    // INTP Disabled
                    //
                } else {
                    //
                    // Begin Interrupt Service
                    //
                    enabled = True;
                }
            }
        }
    }
    return enabled;
}

Bool v850InterruptPending(v850P v850) {
    if(isHalted(v850)) {
        return ((v850->FLG_INTPEND != 0) || (v850->FLG_NMIPEND != 0));
    } else {
        return nmiPendingAndEnabled(v850) || intpPendingAndEnabled(v850);
    }
}

void v850TestInterrupt(v850P v850) {
    if(v850InterruptPending(v850)) {
        if(isHalted(v850)) {
            vmirtRestartNow((vmiProcessorP)v850);
        }
        v850ProcessException((vmiProcessorP)v850);
    }
}

//
// Process NON Maskable Interrupt
//
static void doNonMaskableInterrupt(v850P v850) {
    Uns32 nmiHandler = 0;

    // FEPC <- PC
    v850->SPR_FEPC.reg = vmirtGetPC((vmiProcessorP)v850);

    // FEPSW <- PSW
    v850->SPR_FEPSW.reg = v850PackPSW(v850);

    // Which NMI is active ?
    // According to v850e2r
    //    the priority is 0x20, 0x30, 0x10
    //
    if (v850->netValue.nmi1) {
        v850->exception = (v850Exception) v850_E_nmi1;
    } else if (v850->netValue.nmi2) {
        v850->exception = (v850Exception) v850_E_nmi2;
    } else if (v850->netValue.nmi0) {
        v850->exception = (v850Exception) v850_E_nmi0;
    } else {
        vmiMessage("F", "NMI_INACTIVE", "Call to NMI handler, no nmi lines active");
    }
    nmiHandler = v850GetExceptionVector(v850, v850->exception);

    v850->SPR_FEIC.ECC = nmiHandler;

    // PSW.UM <- 0 (this is a null action on old architectures, so no need for test
    v850->SPR_PSW.UM = 0;

    // PSW.ID
    v850->FLG_PSW_ID = 1;

    // PSW.NP <- 1
    v850->FLG_PSW_NP = 1;

    // PSE.EP
    v850->FLG_PSW_EP = 0;

    // update processor mode
    v850SetVMMode(v850);

    // PC
    vmirtSetPCException((vmiProcessorP)v850, nmiHandler);

    // Send interrupt Acknowledge
    vmirtWriteNetPort((vmiProcessorP)v850, v850->netValue.intack, 1);
}

#define RH850_EEINT_CODE_BASE    0x1000

//
// Process Maskable Interrupt
//
static void doMaskableInterrupt(v850P v850) {
    // EIPC <- PC
    v850->SPR_EIPC.reg = vmirtGetPC((vmiProcessorP)v850);

    // EIPSW
    v850->SPR_EIPSW.reg = v850PackPSW(v850);

    // ECR.EICC (mask in lower 16 bits of Handler)
    Uns32 vector = 0;

    if (v850->configInfo.arch == RH850G3M) {
        vector = v850GetExceptionVector(v850, rh850_E_eiint);
        v850->exception=(v850Exception) rh850_E_eiint;    // exception info
    } else {
        vector = v850GetExceptionVector(v850, v850_E_intp);
        v850->exception=(v850Exception) v850_E_intp;    // exception info
    }

    if (v850->configInfo.arch == RH850G3M) {
        RH850_EEINT eeint  = {.reg = v850->netValue.intp};
        v850->SPR_EIIC.reg = eeint.NUM;               // "Exception Source Code"

    } else {
        v850->SPR_EIIC.reg = v850->netValue.intp;
    }

    // PSW.UM <- 0 (this is a null action on old architectures, so no need for test
    v850->SPR_PSW.UM = 0;

    // PSW.ID
    v850->FLG_PSW_ID = 1;

    // PSE.EP
    v850->FLG_PSW_EP = 0;

    // PC (based on RINT)
    Uns32 VPC = 0;

    // update processor mode
    v850SetVMMode(v850);

    if (v850->configInfo.arch == RH850G3M) {
        // TODO: No definition of selection between Vector and Direct Table method
        //       can be found in available user manuals.
        //       This method configures the intp input from the interrupt controller
        RH850_EEINT eeint  = {.reg = v850->netValue.intp};

        // INTCFG.ISPC 0:The ISPR register is automatically updated.
        if (v850->SPR_INTCFG.ISPC == 0) {
            v850->SPR_ISPR.reg |= (1 << eeint.PRI);
        }
        //
        // PSW.EBV==0 && RBASE.RINT==1 -OR-
        // PSW.EBV==1 && EBASE.RINT==1 -OR-
        // Table Reference Method - Whatever that is ?
        //
        Bool TableReferenceMethod =
            (v850->SPR_PSW.EBV==0 && v850->SPR_RBASE.RINT==1) ||
            (v850->SPR_PSW.EBV==1 && v850->SPR_EBASE.RINT==1) ||
            eeint.MODE;

        if (TableReferenceMethod) {
            // Table Reference Method
            memDomainP domain = vmirtGetProcessorDataDomain((vmiProcessorP) v850);
            Uns32 adr_tbl = v850->SPR_INTBP.reg + (4 * (eeint.NUM - RH850_EEINT_CODE_BASE));

            VPC = vmirtRead4ByteDomain(
                domain,             //    memDomainP     domain,
                adr_tbl,            //    Addr           simAddress,
                MEM_ENDIAN_LITTLE,  //    memEndian      endian,
                MEM_AA_TRUE);       //    memAccessAttrs attrs

        } else {
            // Direct Vector Method
            Uns32 adr_BASE = ((v850->SPR_PSW.EBV == 0) ? v850->SPR_RBASE.RBASE : v850->SPR_EBASE.EBASE) << 9;
            Uns32 int_RINT = (v850->SPR_PSW.EBV == 0)  ? v850->SPR_RBASE.RINT  : v850->SPR_EBASE.RINT;

            // on maskable (EIINT) exception, vector must be 100h
            if (int_RINT == 0) {
                VPC = adr_BASE + vector + (16 * eeint.PRI);
            } else {
                VPC = adr_BASE + vector;
            }
        }

    } else {
        Uns32 IntP0 = 0x0;
        if (v850->configInfo.arch == V850E2R) {
            IntP0 = 0x80;
        } else {
            IntP0 = 0x80;
        }
        if (v850->SPR_EH_CFG.RINT) {
            VPC = vector + IntP0;
        } else {
            VPC = vector + v850->netValue.intp - IntP0;
        }
    }

    vmirtSetPCException((vmiProcessorP)v850, VPC);

    // Send interrupt Acknowledge
    vmirtWriteNetPort((vmiProcessorP)v850, v850->netValue.intack, 1);
}

VMI_RD_PRIV_EXCEPT_FN(v850RdPrivExcept) {
    v850P v850 = (v850P)processor;
    Uns32 VA   = (Uns32)address;

    if (v850HasMPU(v850)) {
        if (!v850MPUMiss(v850, MEM_PRIV_R, VA, attrs)) {
            *action = VMI_LOAD_STORE_CONTINUE;
        }
    }
}

VMI_WR_PRIV_EXCEPT_FN(v850WrPrivExcept) {
    v850P v850 = (v850P)processor;
    Uns32 VA   = (Uns32)address;

    if (v850HasMPU(v850)) {
        if (!v850MPUMiss(v850, MEM_PRIV_W, VA, attrs)) {
            *action = VMI_LOAD_STORE_CONTINUE;
        }
    }
}

VMI_RD_ALIGN_EXCEPT_FN(v850RdAlignExcept) {
    return 0;
}

VMI_WR_ALIGN_EXCEPT_FN(v850WrAlignExcept) {
    return 0;
}

VMI_RD_ABORT_EXCEPT_FN(v850RdAbortExcept) {
}

VMI_WR_ABORT_EXCEPT_FN(v850WrAbortExcept) {
}

VMI_ARITH_EXCEPT_FN(v850ArithExcept) {
    v850P v850 = (v850P)processor;

    switch(exceptionType) {
        // integer divide-by-zero and overflow should not generate exceptions
        // but instead set the overflow flag
        case VMI_INTEGER_OVERFLOW:
            v850->FLG_PSW_SI = 1;
            v850->FLG_PSW_ZR = 0;
            /* no break */

        case VMI_INTEGER_DIVIDE_BY_ZERO:
            v850->FLG_PSW_OV = 1;
            return True;

        // not expecting any other arithmetic exception types
        default:
            return False;
    }
}

VMI_FP_ARITH_EXCEPT_FN(v850E1FPArithExcept) {

    //
    // Test Flags structure
    //
    // Denormal, tested after instruction completion
    if (flags->f.D) {
        flags->f.O = 0;
        flags->f.U = 0;
        flags->f.P = 0;
    }

    return VMI_FLOAT_CONTINUE;
}

VMI_FP_IND32_RESULT_FN(v850E2ConvertInd32) {
    Uns32 result = 0;
    VMI_ABORT("TODO: implement v850E2ConvertInd32 = %08x", value.u32);
    return result;
}

Uns64 clampDouble(
        vmiFPArg value,
        vmiFType type,
        Uns64 CLAMP_MIN,
        Uns64 CLAMP_MAX,
        Flt64 FCOMP_MIN,
        Flt64 FCOMP_MAX
) {
    Uns64 result = 0;

    if (value.type == vmi_FT_64_IEEE_754) {
        //
        // 64 bit Float -> 64/32 bit Signed/Unsigned CLAMP
        //
        if (IS_V850_FP64_INF(value.u64) && !IS_V850_FP64_NEG(value.u64)) {
            result = CLAMP_MAX;

        } else if (IS_V850_FP64_INF(value.u64) && IS_V850_FP64_NEG(value.u64)) {
            result = CLAMP_MIN;

        } else if (IS_V850_FP64_NAN(value.u64)) {
            result = CLAMP_MIN;

        } else if (value.f64 >= FCOMP_MAX) {
            result = CLAMP_MAX;

        } else if (value.f64 <= FCOMP_MIN) {
            result = CLAMP_MIN;

        } else {
            vmiMessage("F", "IND DBL->INT", "value.u64=" FMT_64x " %s:%d", value.u64, __FILE__, __LINE__);
        }

    } else if (value.type == vmi_FT_32_IEEE_754) {
        //
        // 32 bit Float -> 64/32 bit Signed/Unsigned CLAMP
        //
        if (IS_V850_FP32_INF(value.u32) && !IS_V850_FP32_NEG(value.u32)) {
            result = CLAMP_MAX;

        } else if (IS_V850_FP32_INF(value.u32) && IS_V850_FP32_NEG(value.u32)) {
            result = CLAMP_MIN;

        } else if (IS_V850_FP32_NAN(value.u32)) {
            result = CLAMP_MIN;

        } else if (value.f32 >= FCOMP_MAX) {
            result = CLAMP_MAX;

        } else if (value.f32 <= FCOMP_MIN) {
            result = CLAMP_MIN;

        } else {
            vmiMessage("F", "IND FLT->INT", "value.u32=0x%08x %s:%d", value.u32, __FILE__, __LINE__);
        }

    } else {
        vmiMessage("F", "IND DBL/FLT->INT", "value.u64=" FMT_64x " %s:%d", value.u64, __FILE__, __LINE__);
    }

    return result;
}

VMI_FP_IND32_RESULT_FN(v850E2Ind64_ds32) {
    Uns32 result = 0;

    result = (Uns32)
        clampDouble(value, vmi_FT_32_INT,
            (Int64)(Int32)V850_INT32_MIN, (Int64)(Int32)V850_INT32_MAX,
            (Flt64)(Int32)V850_INT32_MIN, (Flt64)(Int32)V850_INT32_MAX
        );
    return result;
}

VMI_FP_IND64_RESULT_FN(v850E2Ind64_ds64) {
    Uns64 result = 0;

    result = (Uns64)
        clampDouble(value, vmi_FT_64_INT,
            (Int64)V850_INT64_MIN, (Int64)V850_INT64_MAX,
            (Flt64)V850_INT64_MIN, (Flt64)V850_INT64_MAX
        );
    return result;
}

VMI_FP_IND32_RESULT_FN(v850E2Ind32_du32) {
    Uns32 result = 0;

    result = (Uns32)
        clampDouble(value, vmi_FT_32_UNS,
            (Uns64)(Uns32)V850_UNS32_MIN, (Uns64)(Uns32)V850_UNS32_MAX,
            (Flt64)(Uns32)V850_UNS32_MIN, (Flt64)(Uns32)V850_UNS32_MAX
        );
    return result;
}

VMI_FP_IND64_RESULT_FN(v850E2Ind64_du64) {
    Uns64 result = 0;

    result = (Uns64)
        clampDouble(value, vmi_FT_64_UNS,
            (Uns64)V850_UNS64_MIN, (Uns64)V850_UNS64_MAX,
            (Flt64)V850_UNS64_MIN, (Flt64)V850_UNS64_MAX
        );
    return result;
}

VMI_FP_64_RESULT_FN(v850E2ConvertResult64) {
    vmiPrintf("v850E2ConvertResult64\n");
    vmiPrintf("  argNum=%d\n", argNum);
    vmiPrintf("  result64=" FMT_64x "\n", result64);
    return result64;
}

VMI_FP_32_RESULT_FN(v850E2ConvertResult32) {
    vmiPrintf("v850E2ConvertResult32\n");
    vmiPrintf("  argNum=%d\n", argNum);
    vmiPrintf("  result32=0x%08x\n", result32);
    return result32;
}

VMI_FP_ARITH_EXCEPT_FN(v850E2FPArithExcept) {
    v850P v850 = (v850P)processor;
    //
    // copy flags across
    //
    v850->FLG_FPF |= (flags->f.I) ? FPFLAGS_I : 0;
    v850->FLG_FPF |= (flags->f.D) ? FPFLAGS_D : 0;
    v850->FLG_FPF |= (flags->f.Z) ? FPFLAGS_Z : 0;
    v850->FLG_FPF |= (flags->f.O) ? FPFLAGS_O : 0;
    v850->FLG_FPF |= (flags->f.U) ? FPFLAGS_U : 0;
    v850->FLG_FPF |= (flags->f.P) ? FPFLAGS_P : 0;

    if ((v850->configInfo.arch == RH850G3M) && (v850->SPR_FPSR.PEM)) {
        //
        // only RH850 generates precise exceptions
        //
        v850ProcessFPP(v850);
    } else {
        v850ProcessFPI(v850);
    }

    return VMI_FLOAT_CONTINUE;
}

//
// Validate that the passed address is a mapped fetch address
//
static Bool validateFetchAddress(v850P v850, Uns32 simPC, Bool complete) {

    memAccessAttrs attrs = complete ? MEM_AA_TRUE : MEM_AA_FALSE;

    if(vmirtIsExecutable((vmiProcessorP)v850, simPC)) {
        // no exception pending
        return True;
    }

    if (0 /* v850HasMMU(v850) */ ) {
        //
        // Handling for an MMU Present
        //

    } else if (v850HasMPU(v850)) {
        //
        // Handling for an MPU Present
        //
        if (v850MPUMiss(v850, MEM_PRIV_X, simPC, attrs)) {
            // MPU miss exception of some kind, handled by MPUMiss, so no
            // further action required here.
            return False;
        } else {
            // no exception pending
            return True;
        }
        return False;
    }

    // no exception pending
    return True;
}

VMI_IFETCH_FN(v850IfetchExcept) {
    v850P v850    = (v850P)processor;
    Uns32 thisPC  = (Uns32)address;

    Bool  fetchOK = False;

    if (nmiPendingAndEnabled(v850)) {
        fetchOK = False;

        if(complete) {
            doNonMaskableInterrupt(v850);
        }

    } else if (intpPendingAndEnabled(v850)) {
        fetchOK = False;

        if(complete) {
            doMaskableInterrupt(v850);
        }

    } else if (!validateFetchAddress(v850, thisPC, complete)) {
        //
        // mapping error - (handled in validateFetchAddress)
        //

    } else {
        //
        // no exception pending
        //
        fetchOK = True;
    }

    if(fetchOK) {
        return VMI_FETCH_NONE;
    } else if(complete) {
        return VMI_FETCH_EXCEPTION_COMPLETE;
    } else {
        return VMI_FETCH_EXCEPTION_PENDING;
    }
}

VMI_ICOUNT_FN(v850IcountExcept) {
}

VMI_EXCEPTION_INFO_FN(v850ExceptionInfo) {
    v850P v850 = (v850P)processor;

    //
    // Exception lists are variant specific
    //
    v850ExceptionInfoCP v850Info, v850prev, this, end;

    v850prev = (v850ExceptionInfoCP)prev;

    if (v850->configInfo.arch == RH850G3M) {
        v850Info = RH850_Exceptions;
        end = v850Info+rh850_E_LAST;
    } else {
        v850Info = V850_Exceptions;
        end = v850Info+v850_E_LAST;
    }

    // on the first call, start with the first member of the table
    if(!v850prev) {
        v850prev = v850Info-1;
    }

    // search for the next member
    for(this=v850prev+1; this!=end; this++) {
        return &this->info;
    }

    // no more exceptions
    return 0;
}

VMI_GET_EXCEPTION_FN(v850GetException) {
    v850P v850 = (v850P)processor;
    v850ExceptionInfoCP v850Info;

    if (v850->configInfo.arch == RH850G3M) {
        v850Info = RH850_Exceptions;
    } else {
        v850Info = V850_Exceptions;
    }
    return &v850Info[v850->exception].info;
}

void v850ProcessException(vmiProcessorP processor) {
    vmirtDoSynchronousInterrupt(processor);
}

static void v850RegisterInit (v850P v850) {
    v850->SPR_PSW.reg = 0x0;
    v850->SPR_PSW.ID  = 1;
    v850UnPackPSW(v850);

    v850->SPR_EIIC.reg  = 0x0;
    v850->SPR_FEIC.reg  = 0x0;
    v850->SPR_EIPC.reg  = 0x0;
    v850->SPR_FEPC.reg  = 0x0;
    v850->SPR_EIPSW.reg = 0x0;
    v850->SPR_FEPSW.reg = 0x0;
    v850->SPR_EIWR.reg  = 0x0;
    v850->SPR_FEWR.reg  = 0x0;
    v850->SPR_DBWR.reg  = 0x0;
    v850->SPR_BSEL.reg  = 0x0;

    v850->SPR_FPSR.reg  = 0x0;
    v850->SPR_FPSR.FS   = 1;

    if (v850->params.GDBSIMMODE) {
        v850->FLG_PSW_ID = 0;
        v850PackPSW(v850);
        v850->SPR_FPSR.FS = 0;
    }

    if (v850->configInfo.arch == V850E2R) {
        v850->SPR_EH_RESET.BITS_28_TO_13 = 0;
        v850->SPR_EH_BASE.BITS_28_TO_13  = 0;
    }

    if (v850->configInfo.arch == RH850G3M) {
        v850->SPR_EIPSW = v850->SPR_PSW;
        v850->SPR_FEPSW = v850->SPR_PSW;

        v850->SPR_HTCFG0.BIT1   = 0x1;
        v850->SPR_MCFG0.BIT1    = 0x1;
        v850->SPR_MCTL.BIT1     = 0x1;

        v850->SPR_ICCTRL.ICHEN  = 0x1;
        v850->SPR_ICCTRL.ICHEMK = 0x1;
        v850->SPR_ICCTRL.BIT16  = 0x1; // bit16=1

        v850->SPR_ICCFG.BIT16   = 0x1; // bit16=1

        v850->SPR_CDBCR.CDBEN   = 0x1;
    }

    v850->FLG_LL = 0;
}

//
// Status for either EI or FE
//
static void commonExceptFEEI (v850P v850, Uns32 VPC, Uns32 CC, Uns32 EXC, Uns32 *PC, Uns32 *PSW, Uns32 *IC) {
    Addr  thisPC = vmirtGetPC((vmiProcessorP)v850);
    Uns32 nextPC = (Uns32)v850nextPC((vmiProcessorP)v850, thisPC);

    Uns32 retPC = nextPC;
    v850ExceptionType type = v850GetExceptionType(v850, EXC);

    //
    // Terminating/Resumable Exception *PC = thisPC
    // Pending               Exception *PC = nextPC
    //
    if  ((type==EXC_TERMINATING) || (type==EXC_RESUMABLE)) {
        retPC = thisPC;
    } else if (type == EXC_PENDING) {
        retPC = nextPC;
    }

    v850->exception = (v850Exception)EXC;

    // xxPC <- PC
    *PC = retPC;

    // xxPSW <- PSW
    v850PackPSW(v850);
    *PSW = v850->SPR_PSW.reg;

    // ECR.xxCC/alias(xxIC (E2R)) <- CC
    // Keep upper 16 bits
    Uns32 CurrIC = (*IC & 0xFFFF0000) | (CC & 0x0000FFFF);
    *IC = CurrIC;

    // PSW.UM <- 0 (this is a null action on old architectures, so no need for test
    v850->SPR_PSW.UM = 0;

    // PSW.ID <- 1
    v850->SPR_PSW.ID = 1;

    // PSW.NP <- 1
    v850->SPR_PSW.NP = 1;

    // PSW.EP <- 1
    v850->SPR_PSW.EP = 1;

    //
    // Output to individual flags (update mode)
    //
    v850UnPackPSW(v850);

    //
    // Clear FLG_LL
    //
    v850->FLG_LL = 0;

    // PC <- Vector PC
    vmirtSetPCException((vmiProcessorP)v850, VPC);
}

static void exceptFE (v850P v850, Uns32 VPC, Uns32 CC, Uns32 EXC) {
    v850->exception=(v850Exception)EXC;    // exception info
    commonExceptFEEI (v850, VPC, CC, EXC, &(v850->SPR_FEPC.reg), &(v850->SPR_FEPSW.reg), &(v850->SPR_FEIC.reg));
}

static void exceptEI (v850P v850, Uns32 VPC, Uns32 CC, Uns32 EXC) {
    v850->exception=(v850Exception)EXC;    // exception info
    commonExceptFEEI (v850, VPC, CC, EXC, &(v850->SPR_EIPC.reg), &(v850->SPR_EIPSW.reg), &(v850->SPR_EIIC.reg));
}

void v850ProcessRESET(v850P v850) {
    Uns32 VPC = v850GetExceptionVector(v850, v850_E_reset);
    Uns32 CC  = v850GetExceptionCode(v850, v850_E_reset);

    exceptFE(v850, VPC, CC, v850_E_reset);

    //
    // Additional reset conditions
    //
    v850RegisterInit(v850);
}

void v850ProcessFENMI(v850P v850) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_fenmi);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_fenmi);
    exceptFE(v850, VPC, CC, rh850_E_fenmi);
}

void v850ProcessSYSERR(v850P v850, Uns32 uimm) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_syserr);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_syserr);
    exceptFE(v850, VPC, CC, rh850_E_syserr);
}

void v850ProcessFEINT(v850P v850) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_feint);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_feint);
    exceptFE(v850, VPC, CC, rh850_E_feint);
}

void v850ProcessFPI(v850P v850) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_fpi);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_fpi);
    exceptEI(v850, VPC, CC, rh850_E_fpi);
}

void v850ProcessEIINT(v850P v850, Uns32 uimm) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_eiint);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_eiint);
    exceptEI(v850, VPC, CC, rh850_E_eiint);
}

void v850ProcessMIP(v850P v850) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_mip);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_mip);
    exceptFE(v850, VPC, CC, rh850_E_mip);
}

void v850ProcessRIE(v850P v850) {
    Uns32         VPC;
    v850Exception EXC;
    Uns32         CC;

    if (v850->configInfo.arch == RH850G3M) {
        EXC = rh850_E_rie;
        VPC = v850GetExceptionVector(v850, EXC);
        CC  = v850GetExceptionCode(v850, EXC);
    } else {
        EXC = v850_E_rie;
        VPC = v850GetExceptionVector(v850, EXC);
        CC  = VPC | 0x100;
    }
    exceptFE(v850, VPC, CC, EXC);
}

void v850ProcessUCPOP(v850P v850, Uns32 uimm) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_ucpop);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_ucpop);
    exceptFE(v850, VPC, CC, rh850_E_ucpop);
}

void v850ProcessPIE(v850P v850) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_pie);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_pie);
    exceptFE(v850, VPC, CC, rh850_E_pie);
}

void v850ProcessMAE(v850P v850) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_mae);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_mae);
    exceptFE(v850, VPC, CC, rh850_E_mae);
}

void v850ProcessMDP(v850P v850) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_mdp);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_mdp);
    exceptFE(v850, VPC, CC, rh850_E_mdp);
}

void v850ProcessFPP(v850P v850) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_fpp);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_fpp);
    exceptEI(v850, VPC, CC, rh850_E_fpp);
}

void v850ProcessSYSCALL(v850P v850) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_syscall);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_syscall);
    exceptEI(v850, VPC, CC, rh850_E_syscall);
}

void v850ProcessFETRAP(v850P v850, Uns32 uimm) {
    v850Exception EXC;
    if (v850->configInfo.arch == RH850G3M) {
        EXC = rh850_E_fetrap;
    } else {
        EXC = v850_E_fetrap;
    }
    Uns32 VPC = v850GetExceptionVector(v850, EXC);
    Uns32 CC  = v850GetExceptionCode(v850, EXC) | uimm;
    exceptFE(v850, VPC, CC, EXC);
}

void v850ProcessTRAP0(v850P v850, Uns32 uimm) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_trap0);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_trap0) | uimm;
    exceptEI(v850, VPC, CC, rh850_E_trap0);
}

void v850ProcessTRAP1(v850P v850, Uns32 uimm) {
    Uns32 VPC = v850GetExceptionVector(v850, rh850_E_trap1);
    Uns32 CC  = v850GetExceptionCode(v850, rh850_E_trap1) | uimm;
    exceptEI(v850, VPC, CC, rh850_E_trap1);
}

//
// Halt the processor for the specified reason if it is running
//
void v850Halt(v850P v850, v850Disable reason) {
    v850->disable |= reason;
    vmirtHalt((vmiProcessorP)v850);
}

//
// Restart the processor for the specified reason if it is halted
//
void v850Restart(v850P v850, v850Disable reason) {
    v850->disable &= ~(reason);
    if (v850->disable == V850_ACTIVE) vmirtRestartNext((vmiProcessorP)v850);
}

Uns32 v850GetExceptionVector(v850P v850, Uns32 exception) {
    const Uns32 *vectors;
    if (v850->configInfo.arch == RH850G3M) {
        vectors = RH850_Vectors;
    } else {
        vectors = V850_Vectors;
    }

    Uns32 VPC = vectors[exception];

    //
    // Adjust from Base Offset ?
    //
    Uns32 Offset = 0;
    if (v850->configInfo.arch == RH850G3M) {
        if (exception == rh850_E_eiint) {
            ; // eiint may be vector or table
        } else if((exception == rh850_E_reset) || (v850->SPR_PSW.EBV == 0)) {
            // reset always uses RBASE
            Offset = v850->SPR_RBASE.RBASE << 9;
        } else {
            Offset = v850->SPR_EBASE.EBASE << 9;
        }

    } else if (v850->configInfo.arch == V850E2R) {
        if (VPC == 0) {
            Offset = v850->SPR_EH_RESET.BITS_28_TO_13 << 13;
        } else {
            Offset = v850->SPR_EH_BASE.BITS_28_TO_13 << 13;
        }

    } else {
        Offset = 0;

    }

    VPC += Offset;

    return VPC;
}

Uns32 v850GetExceptionCode(v850P v850, Uns32 exception) {
    v850ExceptionInfoCP v850Info;
    if (v850->configInfo.arch == RH850G3M) {
        v850Info = RH850_Exceptions;
    } else {
        v850Info = V850_Exceptions;
    }
    return v850Info[exception].info.code;
}

v850ExceptionType v850GetExceptionType(v850P v850, Uns32 exception) {
    v850ExceptionInfoCP v850Info;
    if (v850->configInfo.arch == RH850G3M) {
        v850Info = RH850_Exceptions;
    } else {
        v850Info = V850_Exceptions;
    }
    return v850Info[exception].type;
}

//
// TODO : need to handle RMW, BL, MS
//
void v850MPUMissException(v850P v850, memPriv action, Uns32 VA) {
    //
    // Decode the instruction at this PC
    //
    v850MorphState state;
    v850Decode(v850, vmirtGetPC((vmiProcessorP)v850), &state.info);

    v850Mode mode = v850GetVMMode(v850);
    if (action==MEM_PRIV_X) {
        if        (mode == RH850_M_SUPERVISOR_MPU) {
            v850->SPR_FEIC.SX = 1;
        } else if (mode == RH850_M_USER_MPU) {
            v850->SPR_FEIC.UX = 1;
        }
        v850ProcessMIP(v850);

    } else if (action==MEM_PRIV_R) {
        if        (mode == RH850_M_SUPERVISOR_MPU) {
            v850->SPR_FEIC.SR = 1;
        } else if (mode == RH850_M_USER_MPU) {
            v850->SPR_FEIC.UR = 1;
        }
        v850ProcessMDP(v850);
        v850->SPR_MEI = state.info.mei;

    } else if (action==MEM_PRIV_W) {
        if        (mode == RH850_M_SUPERVISOR_MPU) {
            v850->SPR_FEIC.SW = 1;
        } else if (mode == RH850_M_USER_MPU) {
            v850->SPR_FEIC.UW = 1;
        }
        v850ProcessMDP(v850);
        v850->SPR_MEI = state.info.mei;
    }

    //
    // Update the MEA Register, address of instruction, or LD/ST
    //
    v850->SPR_MEA.reg = VA;
}

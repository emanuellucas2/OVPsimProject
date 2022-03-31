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
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"
#include "ppc32Functions.h"
#include "ppc32Exceptions.h"
#include "ppc32Instructions.h"
#include "ppc32Morph.h"
#include "ppc32MorphFP.h"
#include "ppc32Utils.h"
#include "ppc32SPR.h"
#include "ppc32VM.h"

#define TRC 0

static Uns8 getMSR_FE(ppc32P ppc32) {
    Uns32 MSR = ppc32ReadMSR(ppc32);
    //          FE0                        FE1
    Uns8   FE = VECINDEX(MSR, 12, 12, 1) | VECINDEX(MSR, 9, 9, 0);

    return FE;
}

static Bool isSNaN(vmiFPArgP arg) {
    if (arg->type==vmi_FT_32_IEEE_754) {
        if (IS_PPC32_SFP_SNAN(arg->u32)) {
            return True;
        }
    } else if (arg->type==vmi_FT_64_IEEE_754) {
        if (IS_PPC32_DFP_SNAN(arg->u64)) {
            return True;
        }
    }
    return False;
}

static VMI_FP_QNAN32_RESULT_FN(QNaN32ResultCB) {

    ppc32P ppc32 = (ppc32P) processor;
    Uns32 result = 0;
    Uns32 argc;

    ppc32->QNAN_FLG = True;

#if (TRC==1)
    vmiPrintf("VMI_FP_QNAN32_RESULT_FN\n");
#endif

//  vmiFBinop       fbinOp = (ppc32->FPU_OP >>  8) & 0xff;
//  vmiFUnop         funOp = (ppc32->FPU_OP >>  8) & 0xff;
//  ppc32fpuOpTypeE  fpuOp = (ppc32->FPU_OP >>  0) & 0xff;

    //
    // If input NaN's exist
    //
    if (NaNArgNum) {
        for (argc=0; argc<NaNArgNum; argc++) {
            vmiFPArgP arg = &NaNArgs[argc];
            //
            // Is this an SNaN
            //
            if (isSNaN(arg)) {
                ppc32->FLG_FPSCR_VXSNAN = 1;
            }
        }
        result = QNaN32;
    }

    return result;
}

static VMI_FP_QNAN64_RESULT_FN(QNaN64ResultCB) {
    ppc32P ppc32 = (ppc32P) processor;
    Uns64 result = 0;
    Uns32 argc;

    ppc32->QNAN_FLG = True;

#if (TRC==1)
    vmiPrintf("VMI_FP_QNAN64_RESULT_FN\n");
#endif

    vmiFBinop       fbinOp = (ppc32->FPU_OP >> 8) & 0xff;
//  vmiFUnop         funOp = (ppc32->FPU_OP >> 8) & 0xff;
//  ppc32fpuOpTypeE  fpuOp = (ppc32->FPU_OP >> 0) & 0xff;

    //
    // If input NaN's exist
    //
    if (NaNArgNum) {
//        vmiPrintf("NaNArgNum=%d\n", NaNArgNum);
        for (argc=0; argc<NaNArgNum; argc++) {
            vmiFPArgP arg = &NaNArgs[argc];
            //
            // Is this an SNaN
            //
            if (isSNaN(arg)) {
                ppc32->FLG_FPSCR_VXSNAN = 1;
            }
        }


        if(NaNArgs[0].type==vmi_FT_32_IEEE_754) {
            //
            // Conversion
            //
            result = QNaN64;
        } else {
            //
            // If this is a 2 input Instruction, it could be
            // FRA, FRB
            // FRA, FRC
            // in which case the result is ALWAYS the first NAN
            //
            // If this is a 3 input Instruction, it will be
            // FRA, FRC, FRB
            // in which case FRB, takes precedence over FRC if it is a NAN
            //
            // In all cases allArgNum==3
            //
            // FRA FRB FRC  Nan Idx Sel
            //   .   .   .    0   .   .
            //   .   .   N    1   0   C
            //   .   N   .    1   0   B    ####
            //   .   N   N    2   1   B    ####
            //   N   .   .    1   0   A
            //   N   .   N    2   0   A
            //   N   N   .    2   0   A
            //   N   N   N    3   0   A
            //
            if (allArgNum == 3) {
                Uns8 sel = 0;
                if (IS_PPC32_DFP_NAN(allArgs[0].u64)) {
                    sel = 0;
                } else if (IS_PPC32_DFP_NAN(allArgs[2].u64)) {
                    sel = 2;
                } else if (IS_PPC32_DFP_NAN(allArgs[1].u64)) {
                    sel = 1;
                }
                result = allArgs[sel].u64 | PPC32_DFP_QUIET_MASK;
            } else {
                result = NaNArgs[0].u64 | PPC32_DFP_QUIET_MASK;
            }
        }

    } else {
        //
        // No Input Nans
        //
        vmiFPArgP arg0 = &allArgs[0];
        vmiFPArgP arg1 = &allArgs[1];

        if (allArgNum == 1) {
            //
            // Unary Op
            //
        } else if (allArgNum == 2) {
            //
            // Binary Op
            //
            result = QNaN64 & ~PPC32_DFP_SIGN_MASK;
            if (fbinOp == vmi_FDIV) {
                if (IS_PPC32_DFP_INF(arg0->u64)) {
                    ppc32->FLG_FPSCR_VXIDI = 1;
                } else {
                    ppc32->FLG_FPSCR_VXZDZ = 1;
                }

            } else {
                if (IS_PPC32_DFP_INF(arg0->u64) && IS_PPC32_DFP_INF(arg1->u64)) {
                    ppc32->FLG_FPSCR_VXISI = 1;
                } else {
                    ppc32->FLG_FPSCR_VXIMZ = 1;
                }
            }

        } else if (allArgNum == 3) {
            //
            // Ternary Op
            //
            result = QNaN64 & ~PPC32_DFP_SIGN_MASK;
            if (IS_PPC32_DFP_INF(arg0->u64) && IS_PPC32_DFP_ZERO(arg1->u64)) {
                ppc32->FLG_FPSCR_VXIMZ = 1;

            } else if (IS_PPC32_DFP_ZERO(arg0->u64) && IS_PPC32_DFP_INF(arg1->u64)) {
                ppc32->FLG_FPSCR_VXIMZ = 1;

            } else {
                ppc32->FLG_FPSCR_VXISI = 1;
            }
        }
    }

    //    //
    //    // Special case handling is required for Exceptions being enabled
    //    //
    //    InvalidOperationEnabledAction(ppc32);

    return result;
}

static VMI_FP_IND32_RESULT_FN(handleIndeterminate32) {
#if (TRC==1)
    vmiPrintf("VMI_FP_IND32_RESULT_FN\n");
#endif
    ppc32P ppc32 = (ppc32P) processor;
    Uns32 result;

    //
    // Set flag, do not generate FPU_REL
    //
    ppc32->FLG_FPSCR_VXCVI  = 1;
    ppc32->FPU_REL_GEN      = 0;

    //
    // X87 never generates a Signalling nan
    // so we need to refer to the input argument
    // held in PPC32_TEMP(0)
    //
    if (IS_PPC32_DFP_SNAN(ppc32->FPU_TEMP[1])) {
        ppc32->FLG_FPSCR_VXSNAN = 1;
    }

    if (IS_PPC32_DFP_SNAN(ppc32->FPU_TEMP[1]) || IS_PPC32_DFP_QNAN(ppc32->FPU_TEMP[1])) {
        result = PPC32_MIN_INT32;

    } else {
        Bool isPos = IS_PPC32_DFP_POS(ppc32->FPU_TEMP[1]);
        result = isPos ? PPC32_MAX_INT32 : PPC32_MIN_INT32;
    }

    return result;
}

static VMI_FP_IND64_RESULT_FN(handleIndeterminate64) {
#if (TRC==1)
    vmiPrintf("VMI_FP_IND64_RESULT_FN\n");
#endif
    ppc32P ppc32 = (ppc32P) processor;
    Uns64 result;

    //
    // Set flag, do not generate FPU_REL
    //
    ppc32->FLG_FPSCR_VXCVI  = 1;
    ppc32->FPU_REL_GEN      = 0;

    //
    // X87 never generates a Signalling nan
    // so we need to refer to the input argument
    // held in PPC32_TEMP(0)
    //
    if (IS_PPC32_DFP_SNAN(ppc32->FPU_TEMP[1])) {
        ppc32->FLG_FPSCR_VXSNAN = 1;
    }

    if (IS_PPC32_DFP_SNAN(ppc32->FPU_TEMP[1]) || IS_PPC32_DFP_QNAN(ppc32->FPU_TEMP[1])) {
        result = PPC32_MIN_INT64;

    } else {
        Bool isPos = IS_PPC32_DFP_POS(ppc32->FPU_TEMP[1]);
        result = isPos ? PPC32_MAX_INT64 : PPC32_MIN_INT64;
    }

    return result;
}

void ppc32ConfigureFPU(ppc32P ppc32) {

    // FPU configuration
    const static vmiFPConfig config = {
        .QNaN32                  = PPC32_SFP_QNAN_MASK,
        .QNaN64                  = PPC32_DFP_QNAN_MASK,
        .QNaN32ResultCB          = QNaN32ResultCB,
        .QNaN64ResultCB          = QNaN64ResultCB,
        .indeterminate32ResultCB = handleIndeterminate32,
        .indeterminate64ResultCB = handleIndeterminate64,
        .fpArithExceptCB         = ppc32FPArithExcept
    };

    // set up QNaN values and handlers
    vmirtConfigureFPU((vmiProcessorP)ppc32, &config);

    // initialize floating point control word
    ppc32UpdateFPControlWord(ppc32);
}

//
// The FPU Operation can be altered by a write to the
// MSR[FE0, FE1]
// or FPSCR[VE, ZE, OE, UE, XE]
//
void ppc32UpdateFPControlWord(ppc32P ppc32) {
    //
    // Set the new control word bits
    //
    vmiFPControlWord cw = {0};

    //
    // Interrupt Masks (register bits are enables, invert sense)
    //
    Uns8 FE = getMSR_FE(ppc32);

    if (FE == 0) {
        cw.IM = 1;  // Invalid Operation mask
        cw.ZM = 1;  // Divide by Zero mask
        cw.OM = 1;  // Overflow mask
        cw.UM = 1;  // Underflow mask
        cw.PM = 1;  // Precision mask
    } else {
        cw.IM = ~(ppc32->FPSCR.bits.VE);  // Invalid Operation mask
        cw.ZM = ~(ppc32->FPSCR.bits.ZE);  // Divide by Zero mask
        cw.OM = ~(ppc32->FPSCR.bits.OE);  // Overflow mask
        cw.UM = ~(ppc32->FPSCR.bits.UE);  // Underflow mask
        cw.PM = ~(ppc32->FPSCR.bits.XE);  // Precision mask
    }
    cw.DM = 1; // TODO: Denormal mask - define when not masked

    //
    // Rounding and precision
    //
    switch (ppc32->FPSCR.bits.RN) {
    case 0:
        cw.RC = vmi_FPR_NEAREST;
        break;
    case 1:
        cw.RC = vmi_FPR_ZERO;
        break;
    case 2:
        cw.RC = vmi_FPR_POS_INF;
        break;
    case 3:
        cw.RC = vmi_FPR_NEG_INF;
        break;
    }

    //
    //  TODO: Flush to zero
    //
    cw.FZ = 0;

    //
    //  TODO: Denormals are zeros
    //
    cw.DAZ = 0;

    //
    // Assign Control Word
    //
    vmirtSetFPControlWord((vmiProcessorP)ppc32, cw);
}

//
// Functions for special Rounding control on frsp
//
static void FPRSP_RoundSingle(ppc32P ppc32, Int8 *sign, Int32 *exp, Uns64 *frac_0_52, Uns8 G, Uns8 R, Uns8 X) {
    //
    // Frac is 0:52, which is 52:0
    // bit 23 is 52-23
    Uns8  inc  = 0;
    Uns8  lsb  = VECINDEX(*frac_0_52,(52-23),(52-23),0); // frac/23
    Uns8  gbit = VECINDEX(*frac_0_52,(52-24),(52-24),0); // frac/24
    Uns8  rbit = VECINDEX(*frac_0_52,(52-25),(52-25),0); // frac/25
    Uns8  xbit = 0;

    if ((VECINDEX(*frac_0_52,(52-26),(52-52),3) | SHIFTL(G,2) | SHIFTL(R,1) | SHIFTL(X,0)) > 0) {
        xbit = 1;
    }

    switch (ppc32->FPSCR.bits.RN) {
    case 0: // Round to Nearest
        if (lsb==1 && gbit==1) inc = 1;
        if (lsb==0 && gbit==1 && rbit==1) inc = 1;
        if (lsb==0 && gbit==1 && xbit==1) inc = 1;
        break;
    case 2: // Round to +Infinity
        if (*sign==0 && gbit==1) inc = 1;
        if (*sign==0 && rbit==1) inc = 1;
        if (*sign==0 && xbit==1) inc = 1;
        break;
    case 3: // Round to -Infinity
        if (*sign==1 && gbit==1) inc = 1;
        if (*sign==1 && rbit==1) inc = 1;
        if (*sign==1 && xbit==1) inc = 1;
        break;
    }

    Uns64 frac_0_23 = VECINDEX(*frac_0_52,(52-0),(52-23),0);
    frac_0_23 += inc;
    Uns8  carry_out = VECINDEX(frac_0_23,24,24,0);
    if (carry_out) {
        frac_0_23 = SHIFTL(0x1,23) | SHIFTR(frac_0_23,1);
        *exp = *exp + 1;
    }
    *frac_0_52 = SHIFTL(frac_0_23,(52-23));

    ppc32->FPSCR.bits.FR = inc;
    ppc32->FPSCR.bits.FI = gbit | rbit | xbit;

    // TBD
    return;
}
static void FPRSP_PosZero(ppc32P ppc32) {
    ppc32->FPSCR.bits.FE = 1;
}
static void FPRSP_NegZero(ppc32P ppc32) {
    //ppc32->FPSCR.bits.C  = 1;
    //ppc32->FLG_FP_SI = 1;
    ppc32->FPSCR.bits.FE = 1;
}
static void FPRSP_PosInfinity(ppc32P ppc32) {
    ppc32->FPSCR.bits.FU = 1;
    ppc32->FPSCR.bits.FG = 1;
}
static void FPRSP_NegInfinity(ppc32P ppc32) {
    ppc32->FPSCR.bits.FU = 1;
    ppc32->FPSCR.bits.FL = 1;
}
static void FPRSP_PosNormal(ppc32P ppc32) {
    ppc32->FPSCR.bits.FG = 1;
}
static void FPRSP_NegNormal(ppc32P ppc32) {
    ppc32->FPSCR.bits.FL = 1;
}
static void FPRSP_PosDenormal(ppc32P ppc32) {
    ppc32->CMP_FLG |= FPFLAGS_D;
    ppc32->FPSCR.bits.FG = 1;
}
static void FPRSP_NegDenormal(ppc32P ppc32) {
    ppc32->CMP_FLG |= FPFLAGS_D;
    ppc32->FPSCR.bits.FL = 1;
}
static void FPRSP_QNaN(ppc32P ppc32) {
    ppc32->FPU_REL |= FPUREL_UN;
    ppc32->FPSCR.bits.FU  = 1;
}
static void FPRSP_DisabledExponentUnderflow (ppc32P ppc32, Uns32 FRTi, doubleT FRB) {
    doubleT FRT;

    Int8  sign = FRB.bits.sign;
    Int32 exp  = 0;
    Uns64 frac_0_52 = 0;

    if (FRB.bits.exp == 0) {
        exp  = -1022;
        frac_0_52 = FRB.bits.frac;
    }
    if (FRB.bits.exp > 0) {
        exp  = FRB.bits.exp - 1023;
        frac_0_52 = FRB.bits.frac | SHIFTL(0x1,52);
    }

    //
    // Denormalize the operand (shifting right)
    //
    Uns8 G=0, R=0, X=0;
    while (exp < -126) {
        exp += 1;

        // frac,G,R,X = 0,frac,G,(R|X)
        X = (R | X);
        R = G;
        G = VECINDEX(frac_0_52,0,0,0);
        frac_0_52 = SHIFTR(frac_0_52,1);

    }

    if ((VECINDEX(frac_0_52,(52-24),(52-52),3) | SHIFTL(G,2) | SHIFTL(R,1) | SHIFTL(X,0)) > 0) {
        ppc32->FPSCR.bits.UX = 1;
    }

    FPRSP_RoundSingle(ppc32, &sign, &exp, &frac_0_52, G, R, X);

    if (frac_0_52 == 0) {
        FRT.bits.sign = sign;
        FRT.bits.exp  = 0;
        FRT.bits.frac = 0;
        if (sign==0) {
            FPRSP_PosZero(ppc32);
        } else {
            FPRSP_NegZero(ppc32);
        }
    }
    if (frac_0_52 > 0) {
        Uns8 frac0 = VECINDEX(frac_0_52,52,52,0);
        if (frac0==1) {
            if (sign==0) {
                FPRSP_PosNormal(ppc32);
            } else {
                FPRSP_NegNormal(ppc32);
            }
        } else {
            if (sign==0) {
                FPRSP_PosDenormal(ppc32);
            } else {
                FPRSP_NegDenormal(ppc32);
            }
        }
        //
        // Normalize the operand (shifting left)
        //
        while (frac0==0) {
            exp = exp - 1;
            frac_0_52 = VECINDEX(frac_0_52,51,0,1);
            frac0 = VECINDEX(frac_0_52,52,52,0);
        }
        FRT.bits.sign = sign;
        FRT.bits.exp  = exp + 1023;
        FRT.bits.frac = VECINDEX(frac_0_52,51,0,0);

    }

    ppc32->FPR[FRTi] = FRT.r64;
    return;
}
static void FPRSP_EnabledExponentUnderflow (ppc32P ppc32, Uns32 FRTi, doubleT FRB) {
    // TBD
    vmiMessage("F", "FPRSP_EnabledExponentUnderflow", "Not Implemented");
}
static void FPRSP_DisabledExponentOverflow (ppc32P ppc32, Uns32 FRTi, doubleT FRB) {
    ppc32->FPSCR.bits.OX = 1;

    switch (ppc32->FPSCR.bits.RN) {
    case 0: // Round to Nearest
        if (FRB.bits.sign == 0) {
            ppc32->FPR[FRTi] = PPC32_DFP_POS_INF;
            FPRSP_PosInfinity(ppc32);
        } else {
            ppc32->FPR[FRTi] = PPC32_DFP_NEG_INF;
            FPRSP_NegInfinity(ppc32);
        }
        break;
    case 1: // Round to Zero
        if (FRB.bits.sign == 0) {
            ppc32->FPR[FRTi] = 0x47EFFFFFE0000000ULL;
            FPRSP_PosNormal(ppc32);
        } else {
            ppc32->FPR[FRTi] = 0xC7EFFFFFE0000000ULL;
            FPRSP_NegNormal(ppc32);
        }
        break;
    case 2: // Round to +Infinity
        if (FRB.bits.sign == 0) {
            ppc32->FPR[FRTi] = 0x7FF0000000000000ULL;
            FPRSP_PosInfinity(ppc32);
        } else {
            ppc32->FPR[FRTi] = 0xC7EFFFFFE0000000ULL;
            FPRSP_NegNormal(ppc32);
        }
        break;
    case 3: // Round to -Infinity
        if (FRB.bits.sign == 0) {
            ppc32->FPR[FRTi] = 0x47EFFFFFE0000000ULL;
            FPRSP_PosNormal(ppc32);
        } else {
            ppc32->FPR[FRTi] = 0xFFF0000000000000ULL;
            FPRSP_NegInfinity(ppc32);
        }
        break;
    }
    ppc32->FPSCR.bits.FI = 1;

    return;
}
static void FPRSP_EnabledExponentOverflow (ppc32P ppc32, Uns32 FRTi, doubleT db) {
    vmiMessage("F", "FPRSP_EnabledExponentOverflow", "Not Implemented");
}
static void FPRSP_ZeroOperand (ppc32P ppc32, Uns32 FRTi, doubleT FRB) {
    ppc32->FPR[FRTi] = FRB.r64;

    if (FRB.bits.sign == 0) {
        FPRSP_PosZero(ppc32);
    } else {
        FPRSP_NegZero(ppc32);
    }

    return;
}
static void FPRSP_InfOperand (ppc32P ppc32, Uns32 FRTi, doubleT FRB) {
    ppc32->FPR[FRTi] = FRB.r64;
    if (FRB.bits.sign == 0) {
        FPRSP_PosInfinity(ppc32);
    } else {
        FPRSP_NegInfinity(ppc32);
    }

    return;
}
static void FPRSP_QnanOperand (ppc32P ppc32, Uns32 FRTi, doubleT FRB) {
    ppc32->FPR[FRTi] = VECINDEX(FRB.r64, 63, 29, 29);

    FPRSP_QNaN(ppc32);

    return;
}
static void FPRSP_SnanOperand (ppc32P ppc32, Uns32 FRTi, doubleT FRB) {
    ppc32->FPSCR.bits.VXSNAN = 1;

    if (ppc32->FPSCR.bits.VE == 0) {
        ppc32->FPR[FRTi]  = VECINDEX(FRB.r64, 63, 29, 29);
        ppc32->FPR[FRTi] |= PPC32_DFP_QUIET_MASK;

        FPRSP_QNaN(ppc32);
    }

    return;
}
Uns8 ppc32RoundingDFP_TO_SFP(ppc32P ppc32, Uns32 FRTi, Uns32 FRBi) {

    doubleT FRB = { .r64 = ppc32->FPR[FRBi] };
    ppc32->FPR[FRTi] = FRB.r64;

    // Clear Flags
    ppc32->FPSCR.bits.C  = 0;
    ppc32->FPSCR.bits.FL = 0;
    ppc32->FPSCR.bits.FG = 0;
    ppc32->FPSCR.bits.FE = 0;
    ppc32->FPSCR.bits.FU = 0;

    ppc32->FPSCR.bits.FR = 0;
    ppc32->FPSCR.bits.FI = 0;

    ppc32->CMP_FLG       = 0;

    Int64 FRB_1_11 = VECINDEX(FRB.r64,(63-1),(63-11),0);
    Int64 FRB_1_63 = VECINDEX(FRB.r64,(63-1),(63-63),0);

    //
    // Indicate that the morph time conversion does not need to be done
    //
    Bool doMorph = False;

    //
    // Underflow test
    //
    if ((FRB_1_11 < 897) && (FRB_1_63 > 0)) {
        if (ppc32->FPSCR.bits.UE == 0) {
            //
            // Disabled Exponent Underflow
            //
            FPRSP_DisabledExponentUnderflow (ppc32, FRTi, FRB);
        } else {
            //
            // Enabled Exponent Underflow
            //
            FPRSP_EnabledExponentUnderflow (ppc32, FRTi, FRB);
        }
    }

    //
    // Overflow test
    //
    if ((FRB_1_11 > 1150) && (FRB_1_11 < 2047)) {
        if (ppc32->FPSCR.bits.UE == 0) {
            //
            // Disabled Exponent Overflow
            //
            FPRSP_DisabledExponentOverflow (ppc32, FRTi, FRB);
        } else {
            //
            // Enabled Exponent Overflow
            //
            FPRSP_EnabledExponentOverflow (ppc32, FRTi, FRB);
        }
    }

    //
    // Normal test
    //
    if ((FRB_1_11 > 896) && (FRB_1_11 < 1151)) {
        //
        // Normal Operand
        //
        //
        // Indicate that the morph time conversion does need to be done
        //
        doMorph = True;
    }

    //
    // Zero test
    //
    if (FRB_1_63 == 0) {
        //
        // Zero Operand
        //
        FPRSP_ZeroOperand (ppc32, FRTi, FRB);
    }

    //
    // SNaN QNaN INF test
    //
    if (FRB_1_11 == 2047) {
        if (IS_PPC32_DFP_INF(FRB.r64)) {
            //
            // INF Operand
            //
            FPRSP_InfOperand (ppc32, FRTi, FRB);
        }
        if (IS_PPC32_DFP_QNAN(FRB.r64)) {
            //
            // QNaN Operand
            //
            FPRSP_QnanOperand (ppc32, FRTi, FRB);
        }
        if (IS_PPC32_DFP_SNAN(FRB.r64)) {
            //
            // SNaN Operand
            //
            FPRSP_SnanOperand (ppc32, FRTi, FRB);
        }
    }

    ppc32UnpackFPSCR(ppc32);
    ppc32->FPU_RES   = ppc32->FPR[FRTi];
    ppc32->FLG_FP_SI = (ppc32->FPU_RES & PPC32_DFP_SIGN_MASK) ? 1 : 0;

    return doMorph;
}


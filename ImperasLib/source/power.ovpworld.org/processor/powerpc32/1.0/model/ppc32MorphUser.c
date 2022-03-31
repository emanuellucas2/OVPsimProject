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

static const vmiFlags flags_ZrSi = {
    VMI_NOFLAG_CONST,
    {
        VMI_NOFLAG_CONST,
        VMI_NOFLAG_CONST,
        PPC32_FLG_ZR_CONST,
        PPC32_FLG_SI_CONST,
        VMI_NOFLAG_CONST
    }
};

static const vmiFlags flags_CoZrSiOv = {
    VMI_NOFLAG_CONST,
    {
        PPC32_FLG_CO_CONST,
        VMI_NOFLAG_CONST,
        PPC32_FLG_ZR_CONST,
        PPC32_FLG_SI_CONST,
        PPC32_FLG_OV_CONST
    }
};

static const vmiFlags flagsfp_Si = {
    VMI_NOFLAG_CONST,
    {
        VMI_NOFLAG_CONST,
        VMI_NOFLAG_CONST,
        VMI_NOFLAG_CONST,
        PPC32_FLG_FP_SI_CONST,
        VMI_NOFLAG_CONST
    }
};

//
// Perform an exit on a privileged exception in problem/user mode
//
static void vmic_privexit(ppc32P ppc32) {
    vmiMessage("F", "PRIV", "Privileged Instruction Exception");
    vmirtSetPCException((vmiProcessorP)ppc32, 0x0);
}

//
// Generate Privelege Exception if in user mode (error for time being)
//
#define CHECK_PRIV(state)                    \
    if (ppc32IsUserMode(state->ppc32)) {     \
        vmimtArgProcessor();                 \
        vmimtCall((vmiCallFn)vmic_privexit); \
        return;                              \
    }

//
// EQ = Zero Flag
// LT = Sign Flag
// GT = !(EQ | LT)
//
static void postOE () {
    //
    // Set latching XER[SO], requires FLG_OV
    //
    vmimtBinopRR(8, vmi_OR, PPC32_XER_SO_WR, PPC32_XER_OV_RD, 0);
}
static void postRC () {
    //
    // Set CR0[SO], CR0[GT]
    //
    vmimtMoveRR(8, PPC32_SO_WR(0), PPC32_XER_SO_RD);

    //
    // The GT flag is a nor of LT and EQ
    //
    vmimtBinopRRR(8, vmi_NOR, PPC32_GT_WR(0), PPC32_LT_RD(0), PPC32_EQ_RD(0), 0);
    vmimtBinopRC(8, vmi_AND, PPC32_GT_WR(0), 0x1, 0);
}

//
// These are the only functions which can read write fpscr directly
//
static Uns32 read_fpscr(ppc32P ppc32) {
    ppc32PackFPSCR(ppc32);
    return ppc32->FPSCR.reg;
}
static void write_fpscr(ppc32P ppc32, Uns32 value) {
    ppc32->FPSCR.reg = value;

    //
    // Unpack to flags
    //
    ppc32UnpackFPSCR(ppc32);

    //
    // Generate derived bits
    //
    ppc32PackFPSCR(ppc32);
}

//
// This can set
//      XER[OV] XER[CA]
//      CR0[EQ] CR0[LT]
//
inline static vmiFlagsCP ppc32FlagGen(Bool oe, Bool rc, Bool co, Bool ci, Bool cneg) {
    static       vmiFlags   flags;
    static       vmiFlagsCP pFlags  = &flags;
    static const vmiFlags   noFlags = VMI_NOFLAGS;

    flags = noFlags;

    if (rc) {
        flags.f[vmi_ZF] = PPC32_EQ_WR(0);
        flags.f[vmi_SF] = PPC32_LT_WR(0);
    }
    if (oe) {
        flags.f[vmi_OF] = PPC32_XER_OV_WR;
    }
    if (ci) {
        flags.cin       = PPC32_XER_CA_RD;
    }
    if (co) {
        flags.f[vmi_CF] = PPC32_XER_CA_WR;
    }
    if (cneg) {
        flags.negate    = vmi_FN_CF_IN | vmi_FN_CF_OUT;
    }
    return pFlags;
}

static vmiReg getCRbit (Uns8 bi) {
    // bi = xxxyy
    // xxx = CR   index
    // yy  = FLAG index
    Uns8 CRi = (bi >> 2) & 0x7;
    Uns8 FLi = (~bi) & 0x3;
    vmiReg CRbit = VMI_NOREG;
    switch (FLi) {
    case 0: // SO
        CRbit = PPC32_SO_WR(CRi);
        break;
    case 1: // EQ
        CRbit = PPC32_EQ_WR(CRi);
        break;
    case 2: // GT
        CRbit = PPC32_GT_WR(CRi);
        break;
    case 3: // LT
        CRbit = PPC32_LT_WR(CRi);
        break;
    }
    return CRbit;
}

static void emitFPSCR_to_CR1() {
    //
    // TODO: This needs to refresh the FPSCR
    // TEMP(0) = FPSCR >> 28
    // CR1[SO] = OX
    // CR1[EQ] = VX
    // CR1[GT] = FEX
    // CR1[LT] = FX
    //

    //
    // Firstly refresh the FPSCR register
    //
    vmimtArgProcessor();
    vmimtCall((vmiCallFn)ppc32PackFPSCR);

    vmimtBinopRRC(PPC32_FPR_BITS, vmi_SHR, PPC32_TEMP(0), PPC32_FPSCR_RD, 28, 0);
    vmimtBinopRRC(8, vmi_AND, PPC32_TEMP(1), PPC32_TEMP(0), 0x1, 0);    // PPC32_TEMP(1) = FPSCR[28/OX]
    vmimtMoveRR(PPC32_SO_BITS, PPC32_SO_WR(1), PPC32_TEMP(1));          // CR[CR1[SO]] = FPSCR[OX]

    vmimtBinopRC(PPC32_FPR_BITS, vmi_SHR, PPC32_TEMP(0), 1, 0);         // TEMP(0) >> 1
    vmimtBinopRRC(8, vmi_AND, PPC32_TEMP(1), PPC32_TEMP(0), 0x1, 0);    // PPC32_TEMP(1) = FPSCR[29/VX]
    vmimtMoveRR(PPC32_EQ_BITS, PPC32_EQ_WR(1), PPC32_TEMP(1));          // CR[CR1[EQ]] = FPSCR[VX]

    vmimtBinopRC(PPC32_FPR_BITS, vmi_SHR, PPC32_TEMP(0), 1, 0);         // TEMP(0) >> 1
    vmimtBinopRRC(8, vmi_AND, PPC32_TEMP(1), PPC32_TEMP(0), 0x1, 0);    // PPC32_TEMP(1) = FPSCR[30/FEX]
    vmimtMoveRR(PPC32_GT_BITS, PPC32_GT_WR(1), PPC32_TEMP(1));          // CR[CR1[GT]] = FPSCR[FEX]

    vmimtBinopRC(PPC32_FPR_BITS, vmi_SHR, PPC32_TEMP(0), 1, 0);         // TEMP(0) >> 1
    vmimtBinopRRC(8, vmi_AND, PPC32_TEMP(1), PPC32_TEMP(0), 0x1, 0);    // PPC32_TEMP(1) = FPSCR[31/FX]
    vmimtMoveRR(PPC32_LT_BITS, PPC32_LT_WR(1), PPC32_TEMP(1));          // CR[CR1[LT]] = FPSCR[FX]
}

static void ppc32BinopRRR(vmiBinop op, vmiReg rt, vmiReg ra, vmiReg rb, Bool oe, Bool rc, Bool co, Bool ci, Bool cneg) {
    //
    // Select the correct flags structure
    //
    vmiFlagsCP flags = ppc32FlagGen(oe, rc, co, ci, cneg);

    vmimtSetShiftMask(63);
    vmimtBinopRRR(PPC32_GPR_BITS, op, rt, ra, rb, flags);

    if (oe) postOE();
    if (rc) postRC();
}

//
// The FPPostOps will save the result
// Generate a Sign flag
// Generate the result relation to Zero
// and set the sticky flags ZX, UX, OX, XX
// The VXxxx flags are set in the callbacks
//
static void ppc32FPpostBinopRRR(vmiReg rt, vmiFType targetFtype) {
    //
    // Set the sticky flags from the operations, FPU_FLG_STICKY
    //
    // ZX // Divide-By-Zero flag
    // UX // Underflow
    // OX // Overflow
    // XX // precision
    vmimtBinopRR(PPC32_FLAG_BITS, vmi_OR, PPC32_FPU_FLG_STICKY, PPC32_FPU_FLG, 0);

    //
    // Obtain NaN(output), EQ, LT, GT in FPU_REL
    // and SIGN in FLG_FP_SI
    // This is only valid if FPU_REL_GEN is true
    // If this is a 64 bit op the result is in PPC32_FPU_TEMP(0)
    // If this is a 32 bit op the intermediate result is in PPC32_FPU_TEMP(1)
//    vmiLabelP NO_FPU_REL_GEN = vmimtNewLabel();
//    vmimtCondJumpLabel(PPC32_FPU_REL_GEN, False, NO_FPU_REL_GEN);
    vmimtMoveRR(PPC32_FPR_BITS, rt, PPC32_FPU_TEMP(0));  // Save Result
    vmimtMoveRC(PPC32_FPR_BITS, PPC32_TEMP(0), 0);

    //
    // Test the result(64 bit), or the intermediate result(32-bit)
    // need some careful handling if the 64 bit value was NaN
    //
    vmiLabelP COMPARE_64  = vmimtNewLabel();
    vmiLabelP COMPARE_32  = vmimtNewLabel();
    vmiLabelP COMPARE_END = vmimtNewLabel();

    switch (targetFtype) {
    case vmi_FT_32_IEEE_754:
        vmimtCondJumpLabel(PPC32_QNAN_FLG, True, COMPARE_64);
        vmimtUncondJumpLabel(COMPARE_32);
        break;

    case vmi_FT_64_IEEE_754:
        vmimtUncondJumpLabel(COMPARE_64);
        break;

    default:
        VMI_ABORT("Unhandled targetFtype");
        break;
    }

    vmimtInsertLabel(COMPARE_32);
    vmimtFCompareRR(vmi_FT_32_IEEE_754, PPC32_FPU_REL, PPC32_FPU_TEMP(1), PPC32_TEMP(0), PPC32_CMP_FLG, True, 0);
    vmimtUncondJumpLabel(COMPARE_END);

    vmimtInsertLabel(COMPARE_64);
    vmimtFCompareRR(vmi_FT_64_IEEE_754, PPC32_FPU_REL, PPC32_FPU_TEMP(0), PPC32_TEMP(0), PPC32_CMP_FLG, True, 0);
    vmimtUncondJumpLabel(COMPARE_END);

    vmimtInsertLabel(COMPARE_END);

    //
    // Store the result for future reference of UNORDERED (infinity)
    // and generate the SIGN flag
    //
    vmimtUnopRR(PPC32_FPR_BITS, vmi_MOV, PPC32_FPU_RES, rt, &flagsfp_Si);

    // Label to skip above instructions
//    vmimtInsertLabel(NO_FPU_REL_GEN);
}

static void ppc32FPTernopRRRR(
        vmiFType targetFtype,
        vmiFTernop op,
        Bool negate,
        Uns8 rti, vmiReg rt,
        Uns8 rai, vmiReg ra,
        Uns8 rbi, vmiReg rb,
        Uns8 rci, vmiReg rc,
        Bool roundInt
        ) {
    //
    // Indicate we have performed a BinopRRR, and save the inputs
    // Save the op in the upper part of the word
    //
    // FPU_OP = OP(8), BINOP(8)
    vmimtMoveRC(PPC32_FPU_OP_BITS, PPC32_FPU_OP, (op << 8) | FPUOP_TernopRRRR);

    //
    // Perform the operation (and any callbacks which ensue)
    //
//    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FPU_REL_GEN, 1);
    // Detect if we generate a QNAN, because we will need to skip the 32/64 conversion below
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_QNAN_FLG, 0);
    vmimtFTernopRRRR(vmi_FT_64_IEEE_754, op, PPC32_FPU_TEMP(0), ra, rb, rc, PPC32_FPU_FLG, roundInt, 0); // Save result to a temporary

    //
    // only convert if the number is not a NaN
    //
    vmiLabelP CONVERT_END = vmimtNewLabel();
    vmimtCondJumpLabel(PPC32_QNAN_FLG, True, CONVERT_END);

    //
    // perform final negation (rounding is done on the un-negated result)
    //
    if (negate) {
        vmimtFUnopRR(
            vmi_FT_64_IEEE_754, vmi_FQNEG, PPC32_FPU_TEMP(0), PPC32_FPU_TEMP(0), VMI_NOREG, 0
        );
    }

    //
    // if 32-bit operation, Cast into 32-bit representable value
    //
    if (targetFtype == vmi_FT_32_IEEE_754) {

        //
        // Convert to 32-bit FP, also or the flags into result flags
        //
        vmimtFConvertRR(vmi_FT_32_IEEE_754, PPC32_FPU_TEMP(1), vmi_FT_64_IEEE_754, PPC32_FPU_TEMP(0), vmi_FPR_CURRENT, PPC32_CNV32_FLG, 0);
        vmimtBinopRR(PPC32_FLAG_BITS, vmi_OR, PPC32_FPU_FLG, PPC32_CNV32_FLG, 0);

        //
        // Convert back to 64-bit FP
        //
        vmimtFConvertRR(vmi_FT_64_IEEE_754, PPC32_FPU_TEMP(0), vmi_FT_32_IEEE_754, PPC32_FPU_TEMP(1), vmi_FPR_CURRENT, PPC32_CNV64_FLG, 0);
    }

    //
    // here if result was a NaN
    //
    vmimtInsertLabel(CONVERT_END);

    //
    // Now generate and store the flag information, and save the result
    //
    ppc32FPpostBinopRRR(rt, targetFtype);
}

static void ppc32FPBinopRRR(vmiFType targetFtype, vmiFBinop op, Uns8 rti, vmiReg rt, Uns8 rai, vmiReg ra, Uns8 rbi, vmiReg rb) {
    //
    // Indicate we have performed a BinopRRR, and save the inputs
    // Save the op in the upper part of the word
    //
    // FPU_OP = OP(8), BINOP(8)
    vmimtMoveRC(PPC32_FPU_OP_BITS, PPC32_FPU_OP, (op << 8) | FPUOP_BinopRRR);


    //
    // Perform the operation (and any callbacks which ensue)
    //
//    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FPU_REL_GEN, 1);
    // Detect if we generate a QNAN, because we will need to skip the 32/64 conversion below
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_QNAN_FLG, 0);
    vmimtFBinopRRR(vmi_FT_64_IEEE_754, op, PPC32_FPU_TEMP(0), ra, rb, PPC32_FPU_FLG, 0); // Save result to a temporary

    //
    // if 32-bit operation, Cast into 32-bit representable value
    //
    if (targetFtype == vmi_FT_32_IEEE_754) {
        //
        // only convert if the number is not a NaN
        //
        vmiLabelP CONVERT_END = vmimtNewLabel();
        vmimtCondJumpLabel(PPC32_QNAN_FLG, True, CONVERT_END);

        //
        // Convert to 32-bit FP, also or the flags into result flags
        //
        vmimtFConvertRR(vmi_FT_32_IEEE_754, PPC32_FPU_TEMP(1), vmi_FT_64_IEEE_754, PPC32_FPU_TEMP(0), vmi_FPR_CURRENT, PPC32_CNV32_FLG, 0);
        vmimtBinopRR(PPC32_FLAG_BITS, vmi_OR, PPC32_FPU_FLG, PPC32_CNV32_FLG, 0);

        //
        // Convert back to 64-bit FP
        //
        vmimtFConvertRR(vmi_FT_64_IEEE_754, PPC32_FPU_TEMP(0), vmi_FT_32_IEEE_754, PPC32_FPU_TEMP(1), vmi_FPR_CURRENT, PPC32_CNV64_FLG, 0);

        vmimtInsertLabel(CONVERT_END);
    }

    //
    // Now generate and store the flag information, and save the result
    //
    ppc32FPpostBinopRRR(rt, targetFtype);
}

static void ppc32FPUnopRR(vmiFType targetFtype, vmiFUnop op, Uns8 rti, vmiReg rt, Uns8 rai, vmiReg ra) {
    //
    // Indicate we have performed a BinopRRR, and save the inputs
    // Save the op in the upper part of the word
    //
    // FPU_OP = OP(8), BINOP(8)
    vmimtMoveRC(PPC32_FPU_OP_BITS, PPC32_FPU_OP, (op << 8) | FPUOP_UnopRR);

    //
    // Perform the operation (and any callbacks which ensue)
    //
//    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FPU_REL_GEN, 1);
    // Detect if we generate a QNAN, because we will need to skip the 32/64 conversion below
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_QNAN_FLG, 0);
    vmimtFUnopRR(vmi_FT_64_IEEE_754, op, PPC32_FPU_TEMP(0), ra, PPC32_FPU_FLG, 0); // Save result to a temporary

//    //
//    // if 32-bit operation, Cast into 32-bit representable value
//    //
//    if (targetFtype == vmi_FT_32_IEEE_754) {
//        //
//        // only convert if the number is not a NaN
//        //
//        vmiLabelP CONVERT_END = vmimtNewLabel();
//        vmimtCondJumpLabel(PPC32_QNAN_FLG, True, CONVERT_END);
//
//        //
//        // Convert to 32-bit FP, also or the flags into result flags
//        //
//        vmimtFConvertRR(vmi_FT_32_IEEE_754, PPC32_FPU_TEMP(1), vmi_FT_64_IEEE_754, PPC32_FPU_TEMP(0), vmi_FPR_CURRENT, PPC32_CNV32_FLG);
//        vmimtBinopRR(PPC32_FLAG_BITS, vmi_OR, PPC32_FPU_FLG, PPC32_CNV32_FLG, 0);
//
//        //
//        // Convert back to 64-bit FP
//        //
//        vmimtFConvertRR(vmi_FT_64_IEEE_754, PPC32_FPU_TEMP(0), vmi_FT_32_IEEE_754, PPC32_FPU_TEMP(1), vmi_FPR_CURRENT, PPC32_CNV64_FLG);
//
//        vmimtInsertLabel(CONVERT_END);
//    }

    //
    // Now generate and store the flag information, and save the result
    //
    ppc32FPpostBinopRRR(rt, targetFtype);
}

//
// The ppc32FPpostConvertRR will save the result
// Generate required flags
//
static void ppc32FPpostConvertRR(vmiReg rt, vmiFType targetFtype, vmiReg rs, vmiFType sourceFtype) {
    //
    // Set the sticky flags from the operations, FPU_FLG_STICKY
    //
    // ZX // Divide-By-Zero flag
    // UX // Underflow
    // OX // Overflow
    // XX // precision
    vmimtBinopRR(PPC32_FLAG_BITS, vmi_OR, PPC32_FPU_FLG_STICKY, PPC32_FPU_FLG, 0);

    //
    // Obtain NaN(output), EQ, LT, GT in FPU_REL
    // and SIGN in FLG_FP_SI
    // This is only valid if FPU_REL_GEN is true
    // If this is a 64 bit op the result is in PPC32_FPU_TEMP(0)
    // If this is a 32 bit op the intermediate result is in PPC32_FPU_TEMP(1)
    Uns8 targetSize = 0;
    switch (targetFtype) {
    case vmi_FT_32_IEEE_754:
    case vmi_FT_32_INT:
        //
        // By observation the upper (undefined) bits of the FPR are 0x7fffffff
        //
        vmimtMoveRC(PPC32_FPR_BITS, rt, PPC32_MAX_INT64);
        targetSize = PPC32_GPR_BITS;
        break;
    case vmi_FT_64_IEEE_754:
    case vmi_FT_64_INT:
        targetSize = PPC32_FPR_BITS;
        break;
    default:
        VMI_ABORT("Unhandled targetFtype");
        break;
    }
    vmimtMoveRR(targetSize, rt, PPC32_FPU_TEMP(0));  // Save Result
    vmimtMoveRC(PPC32_FPR_BITS, PPC32_TEMP(0), 0);

    //
    // Test the result(64 bit), or the intermediate result(32-bit)
    // need some careful handling if the 64 bit value was NaN
    //
    vmiLabelP COMPARE_64_OUT = vmimtNewLabel();
    vmiLabelP COMPARE_32_OUT = vmimtNewLabel();
    vmiLabelP COMPARE_64_IN  = vmimtNewLabel();
    vmiLabelP COMPARE_32_IN  = vmimtNewLabel();
    vmiLabelP TEST_REL_GEN   = vmimtNewLabel();
    vmiLabelP ASSIGN_FPU_RES = vmimtNewLabel();
    vmiLabelP COMPARE_END    = vmimtNewLabel();

    switch (targetFtype) {
    case vmi_FT_32_IEEE_754:
        vmimtCondJumpLabel(PPC32_QNAN_FLG, True, COMPARE_64_OUT);
        vmimtUncondJumpLabel(COMPARE_32_OUT);
        break;

    case vmi_FT_64_IEEE_754:
        vmimtUncondJumpLabel(COMPARE_64_OUT);
        break;

    case vmi_FT_32_INT:
    case vmi_FT_64_INT:
        // Test the input
        switch (sourceFtype) {
        case vmi_FT_32_IEEE_754:
            vmimtUncondJumpLabel(COMPARE_32_IN);
            break;

        case vmi_FT_64_IEEE_754:
            vmimtUncondJumpLabel(COMPARE_64_IN);
            break;

        default:
            VMI_ABORT("Unhandled sourceFtype");
            break;
        }
        break;

    default:
        VMI_ABORT("Unhandled targetFtype");
        break;
    }

    //
    // Generate the UNordered flag for FP32
    //
    vmimtInsertLabel(COMPARE_32_IN);
    vmimtFCompareRR(vmi_FT_32_IEEE_754, PPC32_FPU_REL, rs, PPC32_TEMP(0), PPC32_CMP_FLG, True, 0);
    vmimtBinopRC(PPC32_FLAG_BITS, vmi_AND, PPC32_FPU_REL, FPUREL_UN, 0);
    vmimtUncondJumpLabel(TEST_REL_GEN);

    //
    // Generate the UNordered flag for FP64
    //
    vmimtInsertLabel(COMPARE_64_IN);
    vmimtFCompareRR(vmi_FT_64_IEEE_754, PPC32_FPU_REL, rs, PPC32_TEMP(0), PPC32_CMP_FLG, True, 0);
    vmimtBinopRC(PPC32_FLAG_BITS, vmi_AND, PPC32_FPU_REL, FPUREL_UN, 0);
    vmimtUncondJumpLabel(TEST_REL_GEN);

    vmimtInsertLabel(TEST_REL_GEN);
    // if FPU_REL_GEN == 0 clear FPU_REL
    vmimtCondJumpLabel(PPC32_FPU_REL_GEN, True, COMPARE_END);
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FPU_REL, 0);
    vmimtUncondJumpLabel(COMPARE_END);


    vmimtInsertLabel(COMPARE_32_OUT);
    vmimtFCompareRR(vmi_FT_32_IEEE_754, PPC32_FPU_REL, PPC32_FPU_TEMP(1), PPC32_TEMP(0), PPC32_CMP_FLG, True, 0);
    vmimtUncondJumpLabel(ASSIGN_FPU_RES);

    vmimtInsertLabel(COMPARE_64_OUT);
    vmimtFCompareRR(vmi_FT_64_IEEE_754, PPC32_FPU_REL, PPC32_FPU_TEMP(0), PPC32_TEMP(0), PPC32_CMP_FLG, True, 0);
    vmimtUncondJumpLabel(ASSIGN_FPU_RES);

    //
    // Store the result for future reference of UNORDERED (infinity)
    // and generate the SIGN flag - only for conversion to FP types
    //
    vmimtInsertLabel(ASSIGN_FPU_RES);
    vmimtUnopRR(PPC32_FPR_BITS, vmi_MOV, PPC32_FPU_RES, rt, &flagsfp_Si);

    vmimtInsertLabel(COMPARE_END);

}

static void ppc32FPConvertRR(vmiFType targetFtype, vmiReg rt, vmiFType sourceFtype, vmiReg rs, vmiFPRC roundMode, vmiReg flags) {
    // FPU_OP = BINOP(8)
    vmimtMoveRC(PPC32_FPU_OP_BITS, PPC32_FPU_OP, FPUOP_ConvertRR);
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FPU_REL_GEN, 1);

    //
    // Save rs in case we need to check that it is SNaN
    //
    vmimtMoveRR(PPC32_FPR_BITS, PPC32_FPU_TEMP(1), rs);
    vmimtFConvertRR(targetFtype, PPC32_FPU_TEMP(0), sourceFtype, rs, roundMode, flags, 0);

    //
    // Now generate and store the flag information, and save the result
    //
    ppc32FPpostConvertRR(rt, targetFtype, rs, sourceFtype);
}

static void vmic_checkSNaN (ppc32P ppc32, Uns32 size, Uns32 isordered, Uns32 rai, Uns32 rbi) {
    TYPE_FPSCR FPSCR;
    FPSCR.reg = read_fpscr(ppc32);

    //
    // Remove the sign bit
    //
    Uns64 ra = ppc32->FPR[rai] & ~PPC32_DFP_SIGN_MASK;
    Uns64 rb = ppc32->FPR[rbi] & ~PPC32_DFP_SIGN_MASK;

    //
    // Could be an SNaN or QNaN ?
    //
    Bool raSNaN = ((ra <= PPC32_DFP_SNAN_MAX) && (ra >= PPC32_DFP_SNAN_MIN)) ? 1 : 0;
    Bool rbSNaN = ((rb <= PPC32_DFP_SNAN_MAX) && (rb >= PPC32_DFP_SNAN_MIN)) ? 1 : 0;
    Bool raQNaN = ((ra <= PPC32_DFP_QNAN_MAX) && (ra >= PPC32_DFP_QNAN_MIN)) ? 1 : 0;
    Bool rbQNaN = ((rb <= PPC32_DFP_QNAN_MAX) && (rb >= PPC32_DFP_QNAN_MIN)) ? 1 : 0;

    if (raSNaN || rbSNaN) {
        FPSCR.bits.VXSNAN = 1;
        if (isordered && (FPSCR.bits.VE == 0)) {
            FPSCR.bits.VXVC = 1;
        }
    }
    if (isordered && (raQNaN || rbQNaN)) {
        FPSCR.bits.VXVC = 1;
    }
    write_fpscr(ppc32, FPSCR.reg);
}

static void vmic_REL_CR (ppc32P ppc32, Uns32 bf) {
    // Now copy FPU_REL into the CR[BF]
    // REL   = [GT, LT, EQ, UN]
    // swap (GT, LT)
    // FPSCR = [FL, FG, FE, FU]
    // CR    = [LT, GT, EQ, SO]

    Uns8 REL = ppc32->FPU_REL;
    ppc32->SO[bf] = (REL >> 0) & 0x1;
    ppc32->EQ[bf] = (REL >> 1) & 0x1;
    ppc32->LT[bf] = (REL >> 2) & 0x1;
    ppc32->GT[bf] = (REL >> 3) & 0x1;
}

static void ppc32FPCompareRR(vmiFType targetFtype, Uns8 bf, Uns8 rai, vmiReg ra, Uns8 rbi, vmiReg rb, Bool isordered) {

    //
    // If either input is SNaN, set VXSNAN = 1;
    //
    Uns8 compareSize  = 0;
    Uns64 compareMask = 0;
    if        (targetFtype == vmi_FT_32_IEEE_754) {
        compareSize = 32;
        compareMask = PPC32_SFP_SNAN_MASK;

        // Abort for now
        VMI_ABORT("Unimplemented");
    } else if (targetFtype == vmi_FT_64_IEEE_754) {
        compareSize = 64;
        compareMask = PPC32_DFP_SNAN_MASK;

    } else {
        VMI_ABORT("Unhandled targetFtype");
    }
    //
    // Test both inputs for SNaN
    // If ra or rb contain the PPC32_DFP_SNAN_MASK mask, call vmic_checkSNaN
    //
    vmiLabelP L_CALL_VMIC   = vmimtNewLabel();
    vmiLabelP L_NOCALL_VMIC = vmimtNewLabel();
    vmimtBinopRRC(compareSize, vmi_AND, PPC32_FPU_TEMP(0), ra, compareMask, 0);
    vmimtCompareRC(compareSize, vmi_COND_EQ, PPC32_FPU_TEMP(0), compareMask, PPC32_FLG_TEMP);
    vmimtCondJumpLabel(PPC32_FLG_TEMP, True, L_CALL_VMIC);

    vmimtBinopRRC(compareSize, vmi_AND, PPC32_FPU_TEMP(1), rb, compareMask, 0);
    vmimtCompareRC(compareSize, vmi_COND_EQ, PPC32_FPU_TEMP(1), compareMask, PPC32_FLG_TEMP);
    vmimtCondJumpLabel(PPC32_FLG_TEMP, True, L_CALL_VMIC);

    vmimtUncondJumpLabel(L_NOCALL_VMIC);

    vmimtInsertLabel(L_CALL_VMIC);
    vmimtArgProcessor();
    vmimtArgUns32(compareSize);
    vmimtArgUns32(isordered);
    vmimtArgUns32(rai);
    vmimtArgUns32(rbi);
    vmimtCall((vmiCallFn)vmic_checkSNaN);

    vmimtInsertLabel(L_NOCALL_VMIC);

    //
    // FPU_OP = BINOP(8)
    vmimtMoveRC(PPC32_FPU_OP_BITS, PPC32_FPU_OP, FPUOP_CompareRR);
    //
    // Do not allow a stale FPU result to set the FU Flag
    //
    vmimtUnopRC(PPC32_FPR_BITS, vmi_MOV, PPC32_FPU_RES, 0, 0);
    //
    // Perform the operation (and any callbacks which ensue)
    //
    vmimtFCompareRR(targetFtype, PPC32_FPU_REL, ra, rb, PPC32_FPU_FLG, True, 0);

    //
    // Now copy FPU_REL into the CR[BF]
    // REL   = [GT, LT, EQ, UN]
    // swap (GT, LT)
    // FPSCR = [FL, FG, FE, FU]
    // CR    = [LT, GT, EQ, SO]
    //
    vmimtArgProcessor();
    vmimtArgUns32(bf);
    vmimtCall((vmiCallFn)vmic_REL_CR);
}

static void ppc32BinopRRC(vmiBinop op, vmiReg rt, vmiReg ra, Uns64 c, Bool oe, Bool rc, Bool co, Bool ci, Bool cneg) {
    //
    // Select the correct flags structure
    //
    vmiFlagsCP flags = ppc32FlagGen(oe, rc, co, ci, cneg);

    vmimtBinopRRC(PPC32_GPR_BITS, op, rt, ra, c, flags);

    if (oe) postOE();
    if (rc) postRC();
}

static void ppc32BinopRR(vmiBinop op, vmiReg rt, vmiReg ra, Bool oe, Bool rc, Bool co, Bool ci, Bool cneg) {
    //
    // Select the correct flags structure
    //
    vmiFlagsCP flags = ppc32FlagGen(oe, rc, co, ci, cneg);

    vmimtBinopRR(PPC32_GPR_BITS, op, rt, ra, flags);

    if (oe) postOE();
    if (rc) postRC();
}

static void ppc32BinopRC(vmiBinop op, vmiReg rt, Uns64 c, Bool oe, Bool rc, Bool co, Bool ci, Bool cneg) {
    //
    // Select the correct flags structure
    //
    vmiFlagsCP flags = ppc32FlagGen(oe, rc, co, ci, cneg);

    vmimtBinopRC(PPC32_GPR_BITS, op, rt, c, flags);

    if (oe) postOE();
    if (rc) postRC();
}

static void ppc32UnopRR(vmiBinop op, vmiReg rt, vmiReg ra, Bool oe, Bool rc, Bool co, Bool ci, Bool cneg) {
    //
    // Select the correct flags structure
    //
    vmiFlagsCP flags = ppc32FlagGen(oe, rc, co, ci, cneg);

    vmimtUnopRR(PPC32_GPR_BITS, op, rt, ra, flags);

    if (oe) postOE();
    if (rc) postRC();
}

//
// MAC High Cross/Half word Multiply
//
typedef enum macOpTypeS {
    MULOP_CROSS,
    MULOP_HIGH,
    MULOP_LOW
} macOpType;
static void ppc32MulOp(vmiReg rt, vmiReg ra, vmiReg rb, Bool sign, macOpType select) {
    //
    // Signed or unsigned ?
    // TEMP(0) <- ra[high/low]
    // TEMP(1) <- rb[high/low]
    // TEMP(2) <- TESMP(0) op TEMP(1)
    //
    if (sign) {
        //
        // Signed operation
        //
        switch (select) {
        case MULOP_CROSS:
            vmimtMoveExtendRR(PPC32_GPR_BITS, PPC32_TEMP(0), PPC32_GPR_BITS/2, ra, 1);
            vmimtBinopRRC(PPC32_GPR_BITS, vmi_SAR, PPC32_TEMP(1), rb, 16, 0);
            break;
        case MULOP_HIGH:
            vmimtBinopRRC(PPC32_GPR_BITS, vmi_SAR, PPC32_TEMP(0), ra, 16, 0);
            vmimtBinopRRC(PPC32_GPR_BITS, vmi_SAR, PPC32_TEMP(1), rb, 16, 0);
            break;
        case MULOP_LOW:
            vmimtMoveExtendRR(PPC32_GPR_BITS, PPC32_TEMP(0), PPC32_GPR_BITS/2, ra, 1);
            vmimtMoveExtendRR(PPC32_GPR_BITS, PPC32_TEMP(1), PPC32_GPR_BITS/2, rb, 1);
            break;
        }
        vmimtBinopRRR(PPC32_GPR_BITS, vmi_IMUL, rt, PPC32_TEMP(1), PPC32_TEMP(0), &flags_ZrSi);
    } else {
        //
        // Unsigned operation
        //
        switch (select) {
        case MULOP_CROSS:
            vmimtMoveExtendRR(PPC32_GPR_BITS, PPC32_TEMP(0), PPC32_GPR_BITS/2, ra, 0);
            vmimtBinopRRC(PPC32_GPR_BITS, vmi_SHR, PPC32_TEMP(1), rb, 16, 0);
            break;
        case MULOP_HIGH:
            vmimtBinopRRC(PPC32_GPR_BITS, vmi_SHR, PPC32_TEMP(0), ra, 16, 0);
            vmimtBinopRRC(PPC32_GPR_BITS, vmi_SHR, PPC32_TEMP(1), rb, 16, 0);
            break;
        case MULOP_LOW:
            vmimtMoveExtendRR(PPC32_GPR_BITS, PPC32_TEMP(0), PPC32_GPR_BITS/2, ra, 0);
            vmimtMoveExtendRR(PPC32_GPR_BITS, PPC32_TEMP(1), PPC32_GPR_BITS/2, rb, 0);
            break;
        }
        vmimtBinopRRR(PPC32_GPR_BITS, vmi_MUL, rt, PPC32_TEMP(1), PPC32_TEMP(0), &flags_ZrSi);
    }
}

typedef enum macAccTypeS {
    ACCOP_ADD,
    ACCOP_SUB
} macAccType;
static void ppc32AccOp(vmiReg rt, Bool sign, Bool saturate, macAccType acc) {
    //
    // Accumulate operation
    //
    vmiBinop vmiOp;
    if (saturate) {
        if (sign) {
            vmiOp = (acc==ACCOP_ADD) ? vmi_ADDSQ : vmi_SUBSQ;
            vmimtBinopRR(PPC32_GPR_BITS, vmiOp, rt, PPC32_TEMP(2), &flags_CoZrSiOv);
        } else {
            vmiOp = (acc==ACCOP_ADD) ? vmi_ADDUQ : vmi_SUBUQ;
            vmimtBinopRR(PPC32_GPR_BITS, vmiOp, rt, PPC32_TEMP(2), &flags_CoZrSiOv);
        }
        //
        // Generate SIGN and ZERO flags for saturated operation, from result
        //
        vmimtUnopRR(PPC32_GPR_BITS, vmi_MOV, VMI_NOREG, rt, &flags_ZrSi);
    } else {
        vmiOp = (acc==ACCOP_ADD) ? vmi_ADD : vmi_SUB;
        vmimtBinopRR(PPC32_GPR_BITS, vmiOp, rt, PPC32_TEMP(2), &flags_CoZrSiOv);
    }
}

static void ppc32FlgOp(Bool oe, Bool rc, Bool sign) {
    //
    // Flag generation
    //
    if (oe) {
        // This is a special because of the carry
        // PPC32_XER_OV_WR  = (sign) ? FLG_OV : FLG_CA
        // PPC32_XER_SO_WR |= PPC32_XER_OV_WR
        //
        if (sign) {
            vmimtMoveRR(8, PPC32_XER_OV_WR, PPC32_FLG_OV);
        } else {
            vmimtMoveRR(8, PPC32_XER_OV_WR, PPC32_FLG_CO);
        }
        vmimtBinopRR(8, vmi_OR, PPC32_XER_SO_WR, PPC32_XER_OV_WR, 0);
    }
    if (rc) {
        //
        // Set CR0[SO], CR0[GT]
        //
        vmimtMoveRR(8, PPC32_SO_WR(0), PPC32_XER_SO_RD);

        // PPC32_LT_WR(0) = FLG_SI
        // PPC32_EQ_WR(0) = FLG_ZR
        vmimtMoveRR(8, PPC32_LT_WR(0), PPC32_FLG_SI);
        vmimtMoveRR(8, PPC32_EQ_WR(0), PPC32_FLG_ZR);

        // The PPC32_GT_WR(0) flag is a nor of PPC32_LT_WR(0) and PPC32_EQ_WR(0)
        vmimtBinopRRR(8, vmi_NOR, PPC32_GT_WR(0), PPC32_LT_RD(0), PPC32_EQ_RD(0), 0);
        vmimtBinopRC(8, vmi_AND, PPC32_GT_WR(0), 0x1, 0);
    }
}

static void ppc32macc(vmiReg rt, vmiReg ra, vmiReg rb, Bool oe, Bool rc, Bool sign, Bool saturate) {
    ppc32MulOp(PPC32_TEMP(2), ra, rb, sign, MULOP_CROSS);
    ppc32AccOp(rt, sign, saturate, ACCOP_ADD);
    ppc32FlgOp(oe, rc, sign);
}

static void ppc32nmacc(vmiReg rt, vmiReg ra, vmiReg rb, Bool oe, Bool rc, Bool sign, Bool saturate) {
    ppc32MulOp(PPC32_TEMP(2), ra, rb, sign, MULOP_CROSS);
    ppc32AccOp(rt, sign, saturate, ACCOP_SUB);
    ppc32FlgOp(oe, rc, sign);
}

static void ppc32mach(vmiReg rt, vmiReg ra, vmiReg rb, Bool oe, Bool rc, Bool sign, Bool saturate) {
    ppc32MulOp(PPC32_TEMP(2), ra, rb, sign, MULOP_HIGH);
    ppc32AccOp(rt, sign, saturate, ACCOP_ADD);
    ppc32FlgOp(oe, rc, sign);
}

static void ppc32nmach(vmiReg rt, vmiReg ra, vmiReg rb, Bool oe, Bool rc, Bool sign, Bool saturate) {
    ppc32MulOp(PPC32_TEMP(2), ra, rb, sign, MULOP_HIGH);
    ppc32AccOp(rt, sign, saturate, ACCOP_SUB);
    ppc32FlgOp(oe, rc, sign);
}

static void ppc32macl(vmiReg rt, vmiReg ra, vmiReg rb, Bool oe, Bool rc, Bool sign, Bool saturate) {
    ppc32MulOp(PPC32_TEMP(2), ra, rb, sign, MULOP_LOW);
    ppc32AccOp(rt, sign, saturate, ACCOP_ADD);
    ppc32FlgOp(oe, rc, sign);
}

static void ppc32nmacl(vmiReg rt, vmiReg ra, vmiReg rb, Bool oe, Bool rc, Bool sign, Bool saturate) {
    ppc32MulOp(PPC32_TEMP(2), ra, rb, sign, MULOP_LOW);
    ppc32AccOp(rt, sign, saturate, ACCOP_SUB);
    ppc32FlgOp(oe, rc, sign);
}

static void ppc32mulc(vmiReg rt, vmiReg ra, vmiReg rb, Bool rc, Bool sign) {
    ppc32MulOp(rt, ra, rb, sign, MULOP_CROSS);
    ppc32FlgOp(0, rc, sign);
}

static void ppc32mulh(vmiReg rt, vmiReg ra, vmiReg rb, Bool rc, Bool sign) {
    ppc32MulOp(rt, ra, rb, sign, MULOP_HIGH);
    ppc32FlgOp(0, rc, sign);
}

static void ppc32mull(vmiReg rt, vmiReg ra, vmiReg rb, Bool rc, Bool sign) {
    ppc32MulOp(rt, ra, rb, sign, MULOP_LOW);
    ppc32FlgOp(0, rc, sign);
}

static void ppc32Extend(vmiReg rt, vmiReg ra, Uns8 size, Bool sign, Bool rc) {
    //
    // Select the correct flags structure
    //
    vmiFlagsCP flags = ppc32FlagGen(0, rc, 0, 0, 0);

    vmimtMoveExtendRR(PPC32_GPR_BITS, rt, size, ra, sign);

    //
    // Generate flags if required
    //
    if (flags) {
        vmimtBinopRRC(PPC32_GPR_BITS, vmi_OR, VMI_NOREG, rt, 0, flags);
    }

    if (rc) postRC();
}

static Uns32 createMask (Uns8 mb, Uns8 me) {
    Uns32 mask, m1, m2;

    //
    // generate Mask field
    //
    if (me >= mb) {
        m1 = 0xffffffff >> mb;
        m2 = 0xffffffff << (PPC32_GPR_BITS - me - 1);
        mask = m1 & m2;
    } else {
        m1 = 0xffffffff >> (me + 1);
        m2 = 0xffffffff << (PPC32_GPR_BITS - mb);
        mask = ~(m1 & m2);
    }
    return mask;
}

static void ppc32rlwimi(vmiReg ra, vmiReg rs, Uns8 sh, Uns8 mb, Uns8 me, Bool rc) {
    Uns32 mask = createMask(mb, me);

    //
    // First perform rotate r <- ROT(rS, sh)
    //
    vmimtBinopRRC(PPC32_GPR_BITS, vmi_ROL, PPC32_TEMP(0), rs, sh, 0);

    //
    // Now mask the results r & (mb .. me)
    //
    vmimtBinopRC(PPC32_GPR_BITS, vmi_AND, PPC32_TEMP(0), mask, 0);

    //
    // mask the current result Register
    //
    vmimtBinopRC(PPC32_GPR_BITS, vmi_ANDN, ra, mask, 0);

    //
    // finally or the results Register
    //
    ppc32BinopRR(vmi_OR, ra, PPC32_TEMP(0), 0, rc, 0, 0, 0);
}

static void ppc32rlwinm(vmiReg ra, vmiReg rs, Uns8 sh, Uns8 mb, Uns8 me, Bool rc) {
    Uns32 mask = createMask(mb, me);

    //
    // First perform rotate r <- ROT(rS, sh)
    //
    vmimtBinopRRC(PPC32_GPR_BITS, vmi_ROL, PPC32_TEMP(0), rs, sh, 0);

    //
    // Now mask the results r & (mb .. me)
    //
    vmimtBinopRRC(PPC32_GPR_BITS, vmi_AND, ra, PPC32_TEMP(0), mask, 0);

    //
    // finally or the results Register
    //
    ppc32BinopRC(vmi_OR, ra, 0, 0, rc, 0, 0, 0);
}

static void ppc32rlwnm(vmiReg ra, vmiReg rs, vmiReg rb, Uns8 mb, Uns8 me, Bool rc) {
    Uns32 mask = createMask(mb, me);

    //
    // First perform rotate r <- ROT(rS, sh)
    //
    vmimtBinopRRR(PPC32_GPR_BITS, vmi_ROL, PPC32_TEMP(0), rs, rb, 0);

    //
    // Now mask the results r & (mb .. me)
    //
    vmimtBinopRRC(PPC32_GPR_BITS, vmi_AND, ra, PPC32_TEMP(0), mask, 0);

    //
    // finally or the results Register
    //
    ppc32BinopRC(vmi_OR, ra, 0, 0, rc, 0, 0, 0);
}

static void ppc32sraw(vmiReg rs, vmiReg ra, vmiReg rb, Bool rc) {
    //
    // will we generate a carry ?
    // create a bit mask of the bits which will be shifted
    //  POWERPC32_TEMPL_REG = rS & ~(-1 << rB);
    // This can then be tested for non zero to see if 1's will be shifted
    //
    vmimtSetShiftMask(63);
    vmimtBinopRCR(PPC32_GPR_BITS, vmi_SHL,  PPC32_TEMP(0), -1, rb, 0);
    vmimtBinopRRR(PPC32_GPR_BITS, vmi_ANDN, PPC32_TEMP(0), rs, PPC32_TEMP(0), 0);
    vmimtCompareRC(PPC32_GPR_BITS, vmi_COND_NE, PPC32_TEMP(0), 0, PPC32_TEMP(1));

    // Perform shift operation
    vmimtSetShiftMask(63);
    vmimtBinopRRR(PPC32_GPR_BITS, vmi_SAR, ra, rs, rb, 0);

    //
    // The Carry out is quite complicated
    // if the result is -ve, and ANY bits were shifted, the carry is true
    //
    // if the result is negative and shift1 then carry out is true
    vmimtCompareRC(PPC32_GPR_BITS, vmi_COND_S, ra, 0, PPC32_TEMP(2));

    //
    // if result is -ve AND we shifted out any bits, set the carry
    //
    vmimtBinopRRR(8, vmi_AND, PPC32_XER_CA_WR, PPC32_TEMP(1), PPC32_TEMP(2), 0);

    //
    // finally or the results Register
    //
    ppc32BinopRC(vmi_OR, ra, 0, 0, rc, 0, 0, 0);
}

static void ppc32srawi(vmiReg rs, vmiReg ra, Uns8 sh, Bool rc) {
    //
    // will we generate a carry ?
    // create a bit mask of the bits which will be shifted
    //  POWERPC32_TEMPL_REG = rS & ~(-1 << sh);
    // This can then be tested for non zero to see if 1's will be shifted
    //
    if (sh) {
        Uns32 v = -1 << sh;
        vmimtBinopRRC(PPC32_GPR_BITS, vmi_ANDN, PPC32_TEMP(0), rs, v, 0);
        vmimtCompareRC(PPC32_GPR_BITS, vmi_COND_NE, PPC32_TEMP(0), 0, PPC32_TEMP(1));
    }

    // Perform shift operation
    vmimtBinopRRC(PPC32_GPR_BITS, vmi_SAR, ra, rs, sh, 0);

    if (sh) {
        //
        // The Carry out is quite complicated
        // if the result is -ve, and ANY bits were shifted, the carry is true
        //
        // if the result is negative and shift1 then carry out is true
        vmimtCompareRC(PPC32_GPR_BITS, vmi_COND_S, ra, 0, PPC32_TEMP(2));
        //
        // if result is -ve AND we shifted out any bits, set the carry
        //
        vmimtBinopRRR(8, vmi_AND, PPC32_XER_CA_WR, PPC32_TEMP(1), PPC32_TEMP(2), 0);
    } else {
        vmimtMoveRC(8, PPC32_XER_CA_WR, 0);
    }

    //
    // finally or the results Register
    //
    ppc32BinopRC(vmi_OR, ra, 0, 0, rc, 0, 0, 0);
}

static void ppc32compare(Uns8 cmpSize, vmiReg ra, vmiReg rb, Uns8 crfd, Uns32 imm, Bool immInsn, vmiCondition ltcomp) {
    static       vmiFlags   flags;
    static       vmiFlagsCP pFlags  = &flags;
    static const vmiFlags   noFlags = VMI_NOFLAGS;
    flags = noFlags;

    // if ltcomp == vmi_COND_L (SF!=OF) :: comparison is signed
    // if ltcomp == vmi_COND_B (CF==1)  :: comparison is unsigned
    if (ltcomp == vmi_COND_L) {
        // SF != OF
        flags.f[vmi_SF] = PPC32_TEMP(0);
        flags.f[vmi_OF] = PPC32_TEMP(1);
    } else if (ltcomp == vmi_COND_B) {
        // CF == 1
        flags.f[vmi_CF] = PPC32_LT_WR(crfd);
    } else {
        // Unexpected
        vmiMessage("F", "BAD_COND", "Bad condition for ppc32compare");
    }
    flags.f[vmi_ZF] = PPC32_EQ_WR(crfd);

    vmimtMoveRR(8, PPC32_SO_WR(crfd), PPC32_XER_SO_RD);

    //
    // Generate flags by Comparison
    // if      A<B LT
    // else if A>B GT
    // else        EQ
    //
    if (immInsn) {
        if (cmpSize==32) {
            vmimtBinopRRC(cmpSize, vmi_SUB, VMI_NOREG, ra, (Uns32)imm, pFlags);
        } else if (cmpSize==16) {
            vmimtBinopRRC(cmpSize, vmi_SUB, VMI_NOREG, ra, (Uns16)imm, pFlags);
        } else {
            vmiMessage("F", "BAD_SIZE", "Bad size for immediate value");
        }
    } else {
        vmimtBinopRRR(cmpSize, vmi_SUB, VMI_NOREG, ra, rb, pFlags);
    }

    if (ltcomp == vmi_COND_L) {
        // SF != OF
        vmimtBinopRRR(8, vmi_XOR, PPC32_LT_WR(crfd), PPC32_TEMP(0), PPC32_TEMP(1), 0);
    }

    //
    // ppcGT is !(ppcLT|ppcEQ)
    //
    vmimtBinopRRR(8, vmi_OR, PPC32_GT_WR(crfd), PPC32_LT_RD(crfd), PPC32_EQ_RD(crfd), 0);
    vmimtBinopRC(8, vmi_XOR, PPC32_GT_WR(crfd), 1, 0);
}

static void ppc32loadGPR(vmiReg rd, vmiReg ra, vmiReg rb, ppc32MorphStateP state, Uns32 d, Uns8 size, Bool sext, Bool align, Bool upd, Bool rev) {
    Addr thisPC = state->info.thisPC;

    vmiReg updReg;
    memEndian dataEndian = ppc32GetEndian((vmiProcessorP)state->ppc32, False);

    align = True; // ignore incoming setting

    //
    // Are we performing a byte reverse ?
    //
    if (rev) {
        dataEndian = !dataEndian;
    }

    //
    // Sanity checks
    //
    VMI_ASSERT(!upd || !VMI_REG_EQUAL(ra, rd),              "load Register TargetReg==IndexReg PC=0x" FMT_6408x, thisPC);
    VMI_ASSERT(!upd || !VMI_REG_EQUAL(ra, PPC32_GPR_RD(0)), "load Register IndexReg==r0 PC=0x" FMT_6408x, thisPC);

    if (!VMI_REG_EQUAL(rb, VMI_NOREG)) {
        //
        // EA = (ra|0) + rB
        // if ra = 0, Address = rB
        //
        if (VMI_REG_EQUAL(ra, PPC32_GPR_RD(0))) {
            vmimtLoadRRO(PPC32_GPR_BITS, size, 0, rd, rb, dataEndian, sext, align);
            updReg = rb;
        } else {
            vmimtBinopRRR(PPC32_GPR_BITS, vmi_ADD, PPC32_TEMP(0), ra, rb, 0);
            vmimtLoadRRO(PPC32_GPR_BITS, size, 0, rd, PPC32_TEMP(0), dataEndian, sext, align);
            updReg = PPC32_TEMP(0);
        }
        if (upd) {
            vmimtMoveRR(PPC32_GPR_BITS, ra, updReg);
        }

    } else {
        //
        // Address = (ra|0) + d
        // if ra = 0, Address = d
        //
        vmiReg addrReg = VMI_REG_EQUAL(ra, PPC32_GPR_RD(0)) ? VMI_NOREG : ra;
        vmimtLoadRRO(PPC32_GPR_BITS, size, d, rd, addrReg, dataEndian, sext, align);
        if (upd) {
            vmimtBinopRC(PPC32_GPR_BITS, vmi_ADD, ra, d, 0);
        }
    }
}

static void ppc32loadGPR_se(vmiReg rd, vmiReg ra, vmiReg rb, ppc32MorphStateP state, Uns32 d, Uns8 size, Bool sext, Bool align, Bool upd, Bool rev) {
    Addr thisPC = state->info.thisPC;

    vmiReg updReg;
    memEndian dataEndian = ppc32GetEndian((vmiProcessorP)state->ppc32, False);

    align = True; // ignore incoming setting

    //
    // Are we performing a byte reverse ?
    //
    if (rev) {
        dataEndian = !dataEndian;
    }

    //
    // Sanity checks
    //
    VMI_ASSERT(!upd || !VMI_REG_EQUAL(ra, rd),              "load Register TargetReg==IndexReg PC=0x" FMT_6408x, thisPC);
    VMI_ASSERT(!upd || !VMI_REG_EQUAL(ra, PPC32_GPR_RD(0)), "load Register IndexReg==r0 PC=0x" FMT_6408x, thisPC);

    if (!VMI_REG_EQUAL(rb, VMI_NOREG)) {
        //
        // EA = ra + rb
        //
        vmimtBinopRRR(PPC32_GPR_BITS, vmi_ADD, PPC32_TEMP(0), ra, rb, 0);
        vmimtLoadRRO(PPC32_GPR_BITS, size, 0, rd, PPC32_TEMP(0), dataEndian, sext, align);
        updReg = PPC32_TEMP(0);
        if (upd) {
            vmimtMoveRR(PPC32_GPR_BITS, ra, updReg);
        }
    } else {
        //
        // Address = ra + d
        //
        vmimtLoadRRO(PPC32_GPR_BITS, size, d, rd, ra, dataEndian, sext, align);
        if (upd) {
            vmimtBinopRC(PPC32_GPR_BITS, vmi_ADD, ra, d, 0);
        }
    }
}

//
// return whether the bit of the mask has altered to be true
//
static Bool validateBlockMaskMT(ppc32P ppc32, ppc32BlockMask blockMask) {

    vmimtValidateBlockMask(blockMask);

    return (ppc32->blockMask & blockMask);
}

//
// Macro To test and Call FPU Exception Handler
//
#define FPU_AVAILABLE_TEST {                                \
    if (!validateBlockMaskMT(state->ppc32, BM_FP_AVAIL)) {  \
        vmimtArgProcessor();                                \
        vmimtArgUns64(state->info.thisPC);                  \
        vmimtArgUns32(EXC_FLOATING_POINT_UNAVAILABLE);      \
        vmimtCall((vmiCallFn)ppc32ProcessException);        \
        return;                                             \
    }                                                       \
}

static void ppc32loadDFPR(vmiReg rd, vmiReg ra, vmiReg rb, ppc32MorphStateP state, Uns32 d, Uns8 size, Bool upd) {
    FPU_AVAILABLE_TEST

    Addr thisPC = state->info.thisPC;

    vmiReg updReg;
    memEndian dataEndian = ppc32GetEndian((vmiProcessorP)state->ppc32, False);

    //
    // Sanity checks
    //
    VMI_ASSERT(!upd || !VMI_REG_EQUAL(ra, rd),              "load Register TargetReg==IndexReg PC=0x" FMT_6408x, thisPC);
    VMI_ASSERT(!upd || !VMI_REG_EQUAL(ra, PPC32_GPR_RD(0)), "load Register IndexReg==r0 PC=0x" FMT_6408x, thisPC);

    //
    // Set flag for Alignment test
    //
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FLG_FP_LDST, 1);

    if (!VMI_REG_EQUAL(rb, VMI_NOREG)) {
        //
        // EA = (ra|0) + rB
        // if ra = 0, Address = rB
        //
        if (VMI_REG_EQUAL(ra, PPC32_GPR_RD(0))) {
            vmimtLoadRRO(PPC32_FPR_BITS, size, 0, rd, rb, dataEndian, True, True);
            updReg = rb;
        } else {
            vmimtBinopRRR(PPC32_GPR_BITS, vmi_ADD, PPC32_TEMP(0), ra, rb, 0);
            vmimtLoadRRO(PPC32_FPR_BITS, size, 0, rd, PPC32_TEMP(0), dataEndian, True, True);
            updReg = PPC32_TEMP(0);
        }
        if (upd) {
            vmimtMoveRR(PPC32_GPR_BITS, ra, updReg);
        }

    } else {
        //
        // Address = (ra|0) + d
        // if ra = 0, Address = d
        //
        vmiReg addrReg = VMI_REG_EQUAL(ra, PPC32_GPR_RD(0)) ? VMI_NOREG : ra;
        vmimtLoadRRO(PPC32_FPR_BITS, size, d, rd, addrReg, dataEndian, True, True);
        if (upd) {
            vmimtBinopRC(PPC32_GPR_BITS, vmi_ADD, ra, d, 0);
        }
    }

    //
    // Clear flag for Alignment test
    //
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FLG_FP_LDST, 0);
}

#define VECINDEXREV(_VEC,_SIZE1,_SIZE2,_HI,_LO,_OFF) VECINDEX(_VEC,(_SIZE1-1-_HI),(_SIZE1-1-_LO),(_SIZE2-1-_OFF))

static Uns64 vmic_ConvSingleToDouble(ppc32P ppc32, Uns32 ip) {
    doubleT FRT  = { .r64 = 0  };

    //
    // Normalized Operand
    //
    Uns32 WORD_1_8  = VECINDEXREV(ip,32,32,1,8,31);
    Uns32 WORD_9_31 = VECINDEXREV(ip,32,32,9,31,31);
    Uns32 WORD_1_31 = VECINDEXREV(ip,32,32,1,31,31);
    if ((WORD_1_8 > 0) && (WORD_1_8 < 255)) {
        //
        // Normalized Operand
        //
        Uns64 op = 0;
        op |= VECINDEXREV(ip,32,64,0,1,1); // 0:1 = 0:1
        // Test for bit[1] == 0 -> // [2:4] = '111'
        if (VECINDEX(ip,30,30,0)) {
            // Value = 1
        } else {
            // Value = 0
            op |= SHIFTL(0x7,59);
        }
        op |= VECINDEXREV(ip,32,64,2,31,34); // [5:63] = [2:31]
        FRT.r64 = op;

    } else if ((WORD_1_8 == 0) && (WORD_9_31 != 0)) {
        //
        // Denormalized Operand
        //
        Int32 sign      = VECINDEX(ip,31,31,0);
        Int32 exp       = -126;
        Uns64 frac_0_52 = SHIFTL(WORD_9_31,29); // VECINDEXREV(ip,32,64,9,31,30);
        Uns8  frac0     = VECINDEX(frac_0_52,52,52,0);
        while (frac0==0) {
            frac_0_52 = VECINDEX(frac_0_52,51,0,1);
            exp = exp - 1;
            frac0 = VECINDEX(frac_0_52,52,52,0);
        }
        FRT.bits.sign = sign;
        FRT.bits.exp  = exp + 1023;
        FRT.bits.frac = VECINDEX(frac_0_52,51,0,0);

    } else if ((WORD_1_8 == 255) || (WORD_1_31 == 0)) {
        //
        // Zero/Inf/NaN Operand
        //
        Uns64 op = 0;
        op |= VECINDEXREV(ip,32,64,0,1,1); // 0:1 = 0:1
        // Test for bit[1] == 1 -> // [2:4] = '111'
        if (VECINDEX(ip,30,30,0)) {
            // Value = 1
            op |= SHIFTL(0x7,59);
        }
        op |= VECINDEXREV(ip,32,64,2,31,34); // [5:63] = [2:31]
        FRT.r64 = op;

    } else {
        vmiMessage("F", "Unreachable", "Something bad happened");
    }

    return FRT.r64;
}
static void ppc32loadSFPR(vmiReg rd, vmiReg ra, vmiReg rb, ppc32MorphStateP state, Uns32 d, Uns8 size, Bool upd) {
    FPU_AVAILABLE_TEST

    //
    // Set flag for Alignment test
    //
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FLG_FP_LDST, 1);

    //
    // Call a load word, placing into a temporary
    // Perform the conversion to the Destination
    // SFPR will use TEMP(0), so do not use this
    //
    vmiReg sfp = PPC32_TEMP(2);
    ppc32loadGPR(sfp, ra, rb, state, d, PPC32_GPR_BITS, False, True, upd, False);

    //
    // Now Convert from SFP -> DFP
    //
    // FPU_OP = BINOP(8)
if(1) {
    vmimtArgProcessor();
    vmimtArgReg(VPRRAT_32, sfp);
    vmimtCallResult((vmiCallFn)vmic_ConvSingleToDouble, 64, rd);
} else {
    vmimtMoveRC(PPC32_FPU_OP_BITS, PPC32_FPU_OP, FPUOP_Load);
    vmimtFConvertRR(vmi_FT_64_IEEE_754, rd, vmi_FT_32_IEEE_754, sfp, vmi_FPR_CURRENT, VMI_NOREG, 0);
}

    //
    // Clear flag for Alignment test
    //
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FLG_FP_LDST, 0);
}

//
// TODO: Need to handle page alignment crossing ???
// NOTE: There is apparently a CCR0[DLSTM] bit which can control exception generation
//       But does it exist ?
//
static void ppc32loadAll(Uns8 rtNum, vmiReg ra, ppc32MorphStateP state, Uns32 d) {
    Uns8 rtidx;
    memEndian dataEndian = ppc32GetEndian((vmiProcessorP)state->ppc32, False);

    //
    // Address = (ra|0) + d
    // if ra = 0, Address = d
    //
    vmiReg addrReg = VMI_REG_EQUAL(ra, PPC32_GPR_RD(0)) ? VMI_NOREG : ra;
    for (rtidx = rtNum; rtidx <= 31; rtidx++) {
        vmimtLoadRRO(PPC32_GPR_BITS, 32, d, PPC32_GPR_WR(rtidx), addrReg, dataEndian, False, True);
        d+=4;
    }
}

//
// TODO: Need to handle page alignment crossing
//
static void vmic_loadString(ppc32P ppc32, Uns32 rt, Uns32 ra, Uns32 rb, Uns32 nb, Uns32 idx) {
    vmiProcessorP  processor = (vmiProcessorP)ppc32;
    memDomainP     domain    = vmirtGetProcessorDataDomain(processor);

    Uns32 buffer[32];   // Max size of buffer requirement XER/7 bits
    Uns32 EA;
    Uns8 n, words, bytes;

    //
    // Read nb bytes, or XER[25::31] bytes
    //

    Uns32 ra_value = (ra==0) ? 0 : ppc32->GPR[ra];

    if (idx) {
        Uns32 rb_value = ppc32->GPR[rb];
        n = ppc32->XER.bits.BYTES;
        words = n / 4;
        bytes = n % 4;
        if (bytes) words++;
        EA = ra_value + rb_value;
    } else {
        n = (nb==0) ? 32 : nb;
        words = n / 4;
        bytes = n % 4;
        if (bytes) words++;
        EA = ra_value;
    }

    if (n) {
        vmirtReadNByteDomain(domain, EA, buffer, n, 0, True);

        Uns8 word;
        Uns8 r = rt;
        for(word = 0; word < words; word++) {
            r = (rt + word) % 32;
            VMI_ASSERT((ra != r), "lswi attempting to write to source register ra=r%d", ra);
            VMI_ASSERT((idx == 0) || (rb != r), "lswi attempting to write to source register rb=r%d", rb);
            ppc32->GPR[r] = SWAP_4_BYTE(buffer[word]);
        }

        //
        // Mask bits in last word
        //
        switch (bytes) {
            case 0:
                break;

            case 1:
                ppc32->GPR[r] &= 0xff000000;
                break;

            case 2:
                ppc32->GPR[r] &= 0xffff0000;
                break;

            case 3:
                ppc32->GPR[r] &= 0xffffff00;
                break;
        }
    }
}

static void ppc32loadString(Uns8 rt, Uns8 ra, Uns8 rb, Uns8 nb, Uns8 idx) {
    vmimtArgProcessor();
    vmimtArgUns32(rt);
    vmimtArgUns32(ra);
    vmimtArgUns32(rb);
    vmimtArgUns32(nb);
    vmimtArgUns32(idx);
    vmimtCall((vmiCallFn)vmic_loadString);
}

//
// TODO: Need to handle page alignment crossing
//
static void vmic_storeString(ppc32P ppc32, Uns32 rs, Uns32 ra, Uns32 rb, Uns32 nb, Uns32 idx) {
    vmiProcessorP  processor = (vmiProcessorP)ppc32;
    memDomainP     domain    = vmirtGetProcessorDataDomain(processor);

    Uns32 EA;
    Int8  n;

    //
    // Read nb bytes, or XER[25::31] bytes
    //
    Uns32 ra_value = (ra==0) ? 0 : ppc32->GPR[ra];

    if (idx) {
        Uns32 rb_value = ppc32->GPR[rb];
        n = ppc32->XER.bits.BYTES;
        EA = ra_value + rb_value;
    } else {
        n = (nb==0) ? 32 : nb;
        EA = ra_value;
    }

    Uns32 memValue;
    Uns8 i = 0;
    Uns8 r = rs - 1;
    while (n>0) {
        if (i == 0) {
            r = (r + 1) % 32;
        }
        memValue = ppc32->GPR[r];
        switch (i) {
            case 0:
                memValue = (memValue >> 24) & 0xff;
                break;

            case 8:
                memValue = (memValue >> 16) & 0xff;
                break;

            case 16:
                memValue = (memValue >> 8) & 0xff;
                break;

            case 24:
                memValue = (memValue >> 0) & 0xff;
                break;
        }
        vmirtWrite1ByteDomain(domain, EA, memValue, True);

        EA = EA + 1;
        i = (i + 8) % 32;
        n = n - 1;
    }
}

static void ppc32storeString(Uns8 rs, Uns8 ra, Uns8 rb, Uns8 nb, Uns8 idx) {
    vmimtArgProcessor();
    vmimtArgUns32(rs);
    vmimtArgUns32(ra);
    vmimtArgUns32(rb);
    vmimtArgUns32(nb);
    vmimtArgUns32(idx);
    vmimtCall((vmiCallFn)vmic_storeString);
}

//
// TODO: Need to handle page alignment crossing
//
static void ppc32storeAll(Uns8 rsNum, vmiReg ra, ppc32MorphStateP state, Uns32 d) {
    Uns8 rsidx;
    memEndian dataEndian = ppc32GetEndian((vmiProcessorP)state->ppc32, False);

    //
    // Address = (rA|0) + d
    // if rA = 0, Address = d
    //
    vmiReg addrReg = VMI_REG_EQUAL(ra, PPC32_GPR_RD(0)) ? VMI_NOREG : ra;
    for (rsidx = rsNum; rsidx <= 31; rsidx++) {
        vmimtStoreRRO(32, d, addrReg, PPC32_GPR_RD(rsidx), dataEndian, True);
        d+=4;
    }
}

static void ppc32StoreGPR(vmiReg rs, vmiReg ra, vmiReg rb, ppc32MorphStateP state, Uns32 d, Uns8 size, Bool align, Bool upd, Bool rev) {
    vmiReg updReg;
    memEndian dataEndian = ppc32GetEndian((vmiProcessorP)state->ppc32, False);

    align = True; // ignore incoming setting

    //
    // Are we performing a byte reverse ?
    //
    if (rev) {
        dataEndian = !dataEndian;
    }

    if (!VMI_REG_EQUAL(rb, VMI_NOREG)) {
        //
        // EA = (ra|0) + rb
        // if ra = 0, Address = rb
        //
        if (VMI_REG_EQUAL(ra, PPC32_GPR_RD(0))) {
            vmimtStoreRRO(size, 0, rb, rs, dataEndian, align);
            updReg = rb;
        } else {
            vmimtBinopRRR(PPC32_GPR_BITS, vmi_ADD, PPC32_TEMP(0), ra, rb, 0);
            vmimtStoreRRO(size, 0, PPC32_TEMP(0), rs, dataEndian, align);
            updReg = PPC32_TEMP(0);
        }
        if (upd) {
            vmimtMoveRR(PPC32_GPR_BITS, ra, updReg);
        }

    } else {
        //
        // Address = (ra|0) + d
        // if ra = 0, Address = d
        //
        vmiReg addrReg = VMI_REG_EQUAL(ra, PPC32_GPR_RD(0)) ? VMI_NOREG : ra;
        vmimtStoreRRO(size, d, addrReg, rs, dataEndian, align);
        if (upd) {
            vmimtBinopRC(PPC32_GPR_BITS, vmi_ADD, ra, d, 0);
        }
    }
}

static void ppc32StoreGPR_se(vmiReg rs, vmiReg ra, vmiReg rb, ppc32MorphStateP state, Uns32 d, Uns8 size, Bool align, Bool upd, Bool rev) {
    vmiReg updReg;
    memEndian dataEndian = ppc32GetEndian((vmiProcessorP)state->ppc32, False);

    align = True; // ignore incoming setting

    //
    // Are we performing a byte reverse ?
    //
    if (rev) {
        dataEndian = !dataEndian;
    }

    if (!VMI_REG_EQUAL(rb, VMI_NOREG)) {
        //
        // EA = ra + rb
        //
        vmimtBinopRRR(PPC32_GPR_BITS, vmi_ADD, PPC32_TEMP(0), ra, rb, 0);
        vmimtStoreRRO(size, 0, PPC32_TEMP(0), rs, dataEndian, align);
        updReg = PPC32_TEMP(0);
        if (upd) {
            vmimtMoveRR(PPC32_GPR_BITS, ra, updReg);
        }

    } else {
        //
        // Address = ra + d
        //
        vmimtStoreRRO(size, d, ra, rs, dataEndian, align);
        if (upd) {
            vmimtBinopRC(PPC32_GPR_BITS, vmi_ADD, ra, d, 0);
        }
    }
}

static void ppc32storeDFPR(vmiReg rs, vmiReg ra, vmiReg rb, ppc32MorphStateP state, Uns32 d, Uns8 size, Bool upd) {
    FPU_AVAILABLE_TEST

    vmiReg updReg;
    memEndian dataEndian = ppc32GetEndian((vmiProcessorP)state->ppc32, False);

    //
    // Set flag for Alignment test
    //
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FLG_FP_LDST, 1);

    if (!VMI_REG_EQUAL(rb, VMI_NOREG)) {
        //
        // EA = (ra|0) + rb
        // if ra = 0, Address = rb
        //
        if (VMI_REG_EQUAL(ra, PPC32_GPR_RD(0))) {
            vmimtStoreRRO(size, 0, rb, rs, dataEndian, True);
            updReg = rb;
        } else {
            vmimtBinopRRR(PPC32_GPR_BITS, vmi_ADD, PPC32_TEMP(0), ra, rb, 0);
            vmimtStoreRRO(size, 0, PPC32_TEMP(0), rs, dataEndian, True);
            updReg = PPC32_TEMP(0);
        }
        if (upd) {
            vmimtMoveRR(PPC32_GPR_BITS, ra, updReg);
        }

    } else {
        //
        // Address = (ra|0) + d
        // if ra = 0, Address = d
        //
        vmiReg addrReg = VMI_REG_EQUAL(ra, PPC32_GPR_RD(0)) ? VMI_NOREG : ra;
        vmimtStoreRRO(size, d, addrReg, rs, dataEndian, True);
        if (upd) {
            vmimtBinopRC(PPC32_GPR_BITS, vmi_ADD, ra, d, 0);
        }
    }

    //
    // Clear flag for Alignment test
    //
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FLG_FP_LDST, 0);
}

static Uns32 vmic_ConvDoubleToSingle(ppc32P ppc32, Uns64 value) {

    doubleT FRS = { .r64 = value };
    singleT WORD;

    vmirtRestoreFPState((vmiProcessorP)ppc32);

    WORD.f32 = FRS.f64;

    return WORD.r32;
}

static void ppc32storeSFPR(vmiReg rs, vmiReg ra, vmiReg rb, ppc32MorphStateP state, Uns32 d, Bool upd) {
    FPU_AVAILABLE_TEST

    //
    // Set flag for Alignment test
    //
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FLG_FP_LDST, 1);

    //
    // Now Convert fron DFP -> SFP
    //
    vmiReg sfp = PPC32_TEMP(2);
if(1) {
    vmimtArgProcessor();
    vmimtArgReg(VPRRAT_64, rs);
    vmimtCallResult((vmiCallFn)vmic_ConvDoubleToSingle, 32, sfp);
} else {
    // FPU_OP = BINOP(8)
    vmimtMoveRC(PPC32_FPU_OP_BITS, PPC32_FPU_OP, FPUOP_Store);
    vmimtFConvertRR(vmi_FT_32_IEEE_754, sfp, vmi_FT_64_IEEE_754, rs, vmi_FPR_CURRENT, VMI_NOREG, 0);
}

    //
    // Store SFP value
    //
    ppc32StoreGPR(sfp, ra, rb, state, d, PPC32_GPR_BITS, True, upd, False);

    //
    // Clear flag for Alignment test
    //
    vmimtMoveRC(PPC32_FLAG_BITS, PPC32_FLG_FP_LDST, 0);
}

static void ppc32loadReserve (ppc32MorphStateP state, Uns8 rt, Uns8 ra, Uns8 rb, Uns8 length) {
    memEndian endian = ppc32GetEndian((vmiProcessorP)state->ppc32, False);

    vmimtAtomic();

    if (ra == 0) {
        // EA = 0 + rb
        vmimtMoveRR(PPC32_GPR_BITS, PPC32_TEMP(0), PPC32_GPR_RD(rb));
    } else {
        // EA = ra + rb
        vmimtBinopRRR(PPC32_GPR_BITS, vmi_ADD, PPC32_TEMP(0), PPC32_GPR_RD(ra), PPC32_GPR_RD(rb), 0);
    }
    // rt = MEM(EA, 4)
    vmimtLoadRRO(PPC32_GPR_BITS, 32, 0, PPC32_GPR_WR(rt), PPC32_TEMP(0), endian, 0, 0);
    //
    // RESERVE=1. RESERVE_ADDR=EA, RESERVE_LENGTH=length
    //
    vmimtMoveRC(PPC32_RESERVE_BITS,        PPC32_RESERVE_WR,        1);
    vmimtMoveRR(PPC32_RESERVE_ADDR_BITS,   PPC32_RESERVE_ADDR_WR,   PPC32_TEMP(0));
    vmimtMoveRC(PPC32_RESERVE_LENGTH_BITS, PPC32_RESERVE_LENGTH_WR, length);
}

static void ppc32storeConditional (ppc32MorphStateP state, Uns8 rs, Uns8 ra, Uns8 rb, Uns8 length) {

    memEndian endian = ppc32GetEndian((vmiProcessorP)state->ppc32, False);

    vmimtAtomic();

    vmiLabelP SKIPSTORE = vmimtNewLabel();
    vmiLabelP DOSTORE   = vmimtNewLabel();
    vmiLabelP END       = vmimtNewLabel();

    //
    // If no RESERVE - this is a FAIL
    //
    vmimtCompareRCJumpLabel(PPC32_RESERVE_BITS, vmi_COND_NE, PPC32_RESERVE_RD, 1, SKIPSTORE);

    //
    // If LENGTH mismatch - this is a FAIL
    //
    vmimtCompareRCJumpLabel(PPC32_RESERVE_LENGTH_BITS, vmi_COND_NE, PPC32_RESERVE_LENGTH_RD, length, SKIPSTORE);

    //
    // If ADDRESS mismatch - this is a FAIL
    //
    if (ra == 0) {
        // EA = 0 + rb
        vmimtMoveRR(PPC32_GPR_BITS, PPC32_TEMP(2), PPC32_GPR_RD(rb));
    } else {
        // EA = ra + rb
        vmimtBinopRRR(PPC32_GPR_BITS, vmi_ADD, PPC32_TEMP(2), PPC32_GPR_RD(ra), PPC32_GPR_RD(rb), 0);
    }
    vmimtCompareRR(PPC32_RESERVE_BITS, vmi_COND_NE, PPC32_RESERVE_ADDR_RD, PPC32_TEMP(2), PPC32_FLG_TEMP);
    vmimtCondJumpLabel(PPC32_FLG_TEMP, True, SKIPSTORE);

    vmimtInsertLabel(DOSTORE);
        vmimtStoreRRO(PPC32_GPR_BITS, 0, PPC32_TEMP(2), PPC32_GPR_WR(rs), endian, 0);
        vmimtMoveRC(PPC32_EQ_BITS, PPC32_EQ_WR(0), 1);
        vmimtUncondJumpLabel(END);

    vmimtInsertLabel(SKIPSTORE);
        vmimtMoveRC(PPC32_EQ_BITS, PPC32_EQ_WR(0), 0);
        vmimtUncondJumpLabel(END);

    vmimtInsertLabel(END);
        vmimtMoveRC(PPC32_RESERVE_BITS, PPC32_RESERVE_WR, 0);
        vmimtMoveRC(PPC32_LT_BITS, PPC32_LT_WR(0), 0);
        vmimtMoveRC(PPC32_GT_BITS, PPC32_GT_WR(0), 0);
        vmimtMoveRR(PPC32_SO_BITS, PPC32_SO_WR(0), PPC32_XER_SO_RD);

}

//
// CR[BT] = CR[BA] op CR[BB]
//
static void ppc32crBinOpRRR (Uns8 BT, Uns8 BA, Uns8 BB, vmiBinop op) {
    vmimtBinopRRR(8, op, getCRbit(BT), getCRbit(BA), getCRbit(BB), 0);
}

static void ppc32branch(Addr thisPC, Addr nextPC, Int32 LI, Uns8 AA, Uns8 LK) {
    Addr        branchPC;
    vmiReg      LR;
    vmiJumpHint HINT;

    if (AA) {
        branchPC = LI;
    } else {
        branchPC = thisPC + LI;
    }

    if (LK) {
        LR = PPC32_LR_WR;
        HINT = vmi_JH_CALL;
    } else {
        LR = VMI_NOREG;
        HINT = vmi_JH_NONE;
    }

    vmimtUncondJump(nextPC, branchPC, LR, HINT);
}

typedef enum {
    BC=0,
    BCCTR=1,
    BCLR=2
} condType;

static void ppc32branchc(Addr thisPC, Addr nextPC, condType bcond, Uns8 BO, Uns8 BI, Int32 BD, Uns8 AA, Uns8 LK) {
    Addr        branchPC;
    vmiReg      branchReg = VMI_NOREG;
    vmiJumpHint HINT      = vmi_JH_NONE;

    if (AA) {
        branchPC = BD;
    } else {
        branchPC = thisPC + BD;
    }

    //
    // if lk add a hint
    //
    if (LK) {
        HINT = vmi_JH_CALL;
        //
        // Copy the current Link register off to a temporary
        // So that we can use this as our target reg
        //
        vmimtMoveRR(PPC32_GPR_BITS, PPC32_TEMP(0), PPC32_LR_WR);
        vmimtMoveRC(PPC32_GPR_BITS, PPC32_LR_WR, nextPC);
    }

    //
    // Is the branch constant or by a Reg ?
    //
    switch (bcond) {
        case BC:
            break;
        case BCCTR:
            branchReg = PPC32_CTR_RD;
            break;
        case BCLR:
            if (LK) {
                branchReg = PPC32_TEMP(0);
            } else {
                HINT = vmi_JH_RETURN;
                branchReg = PPC32_LR_RD;
            }
            break;
        default:
            VMI_ABORT("Illegal bcond=%d\n", bcond);
            break;
    }

    Uns8 boEncoding = (BO >> 1) & 0xf;
    //
    // if this is bcctr[l] - enable bit b0[2], and disable bo[1]
    // The test should never compare the eqZ eqNZ
    if (bcond == BCCTR) {
        boEncoding &= 0xe;
        boEncoding |= 0x2;
    }

    //
    // Get the Condition bit Register pointer from the CR
    //
    vmiReg crbit = getCRbit(BI);

    //
    // Decrement and test the CTR Register if required
    // The decrement is invalid for bcctr and bcctrl
    //
    Bool    decCTR = ((~BO) >> 2) & 0x1;
    vmiReg  ctreqZ  = PPC32_TEMP(1);
    vmiReg  ctreqNZ = PPC32_TEMP(2);
    static       vmiFlags   flags;
    static       vmiFlagsCP pFlags  = &flags;
    static const vmiFlags   noFlags = VMI_NOFLAGS;
    flags = noFlags;
    flags.f[vmi_ZF] = ctreqZ;

    switch (boEncoding) {
        case 1:     // 0001y :: !(ctreqNZ || crbit)
        case 4:     // 0100y :: ctreqNZ && crbit
        case 8:     // 1z00y :: ctreqNZ
            flags.f[vmi_ZF] = ctreqNZ;
            flags.negate = vmi_FN_ZF;
            break;

        case 0:     // 0000y :: !(ctreqZ || crbit)
        case 5:     // 0101y :: ctreqZ && crbit
        case 9:     // 1z01y :: ctreqZ
            flags.f[vmi_ZF] = ctreqZ;
            flags.negate = vmi_FN_NONE;
            break;

        case 2:     // 001zy :: !crbit
        case 6:     // 011zy :: crbit
        case 10:    // 1z1zz
        default:
            break;
    }

    if (decCTR) {
        //
        // Decrement the CTR reg before test and condition check ?
        // This is not valid when the instruction is a bcctr[l]
        // Ensure that bcond != 2 :: (2=CondCTR)
        // bcx or bclrx
        //VMI_ASSERT((bcond!=2), "Error: invalid form of Instruction Address=0x%08llx\n", thisPC);
        if ((bcond == BC) || (bcond == BCLR)) {
            vmimtBinopRC(PPC32_GPR_BITS, vmi_SUB, PPC32_CTR_WR, 1, pFlags);
        }
    }

    vmiReg testF = PPC32_TEMP(2);
    //
    // boEncoding is only 4 bits, bit 0 is ignored
    //
    switch (boEncoding) {
    case 0:     // 0000 z :: !(ctreqZ || crbit)
        vmimtBinopRRR(8, vmi_OR, testF, ctreqZ, crbit, 0);
        if (bcond == BC) {
            vmimtCondJump(testF, False, nextPC, branchPC, VMI_NOREG, HINT);
        } else {
            vmimtCondJumpReg(testF, False, nextPC, branchReg, VMI_NOREG, HINT);
        }
        break;

    case 1:     // 0001 z :: !(ctreqNZ || crbit)
        vmimtBinopRRR(8, vmi_OR, testF, ctreqNZ, crbit, 0);
        if (bcond == BC) {
            vmimtCondJump(testF, False, nextPC, branchPC, VMI_NOREG, HINT);
        } else {
            vmimtCondJumpReg(testF, False, nextPC, branchReg, VMI_NOREG, HINT);
        }
        break;

    case 2:     // 001a t :: !crbit
    case 3:     // 001A t :: !crbit (hint condition)
        if (bcond == BC) {
            vmimtCondJump(crbit, False, nextPC, branchPC, VMI_NOREG, HINT);
        } else {
            vmimtCondJumpReg(crbit, False, nextPC, branchReg, VMI_NOREG, HINT);
        }
        break;

    case 4:     // 0100 z :: ctreqNZ && crbit
        vmimtBinopRRR(8, vmi_AND, testF, ctreqNZ, crbit, 0);
        if (bcond == BC) {
            vmimtCondJump(testF, True, nextPC, branchPC, VMI_NOREG, HINT);
        } else {
            vmimtCondJumpReg(testF, True, nextPC, branchReg, VMI_NOREG, HINT);
        }
        break;

    case 5:     // 0101 y :: ctreqZ && crbit
        vmimtBinopRRR(8, vmi_AND, testF, ctreqZ, crbit, 0);
        if (bcond == BC) {
            vmimtCondJump(testF, True, nextPC, branchPC, VMI_NOREG, HINT);
        } else {
            vmimtCondJumpReg(testF, True, nextPC, branchReg, VMI_NOREG, HINT);
        }
        break;

    case 6:     // 011z y :: crbit
    case 7:     // 011Z y :: crbit (hint condition)
        if (bcond == BC) {
            vmimtCondJump(crbit, True, nextPC, branchPC, VMI_NOREG, HINT);
        } else {
            vmimtCondJumpReg(crbit, True, nextPC, branchReg, VMI_NOREG, HINT);
        }
        break;

    case 8:     // 1z00 y :: ctreqNZ
    case 12:    // 1Z00 y :: ctreqNZ (hint condition)
        if (bcond == BC) {
            vmimtCondJump(ctreqNZ, True, nextPC, branchPC, VMI_NOREG, HINT);
        } else {
            vmimtCondJumpReg(ctreqNZ, True, nextPC, branchReg, VMI_NOREG, HINT);
        }
        break;

    case 9:     // 1z01 y :: ctreqZ
    case 13:    // 1Z01 y :: ctreqZ  (hint condition)
        if (bcond == BC) {
            vmimtCondJump(ctreqZ, True, nextPC, branchPC, VMI_NOREG, HINT);
        } else {
            vmimtCondJumpReg(ctreqZ, True, nextPC, branchReg, VMI_NOREG, HINT);
        }
        break;

    case 10:    // 1z1z z
    case 11:    // 1z1Z z
    case 14:    // 1Z1z z
    case 15:    // 1Z1Z z
        if (bcond == BC) {
            vmimtUncondJump(nextPC, branchPC, VMI_NOREG, HINT);
        } else {
            vmimtUncondJumpReg(nextPC, branchReg, VMI_NOREG, HINT);
        }
        break;

    default:
        VMI_ABORT("PC=0x%08x, Illegal bc bo=%d boEncoding=%d\n", (Uns32)thisPC, BO, boEncoding);
        break;
    }
}

typedef enum ppc32FlagUpdateE {
    FLAGUPDATE_NONE,
    FLAGUPDATE_OE,
    FLAGUPDATE_RC,
    FLAGUPDATE_OERC
} ppc32FlagUpdate;

static void ppc32intDivOpRRR(vmiReg rt, vmiReg ra, vmiReg rb, vmiBinop op, Bool oe, Bool rc) {

    vmiFlagsCP flags = ppc32FlagGen(oe, rc, 0, 0, 0);

    //
    // setup information about flags to be generated in Exception Handler
    // clear and retrieve DIV OVERFLOW in TEMP(0)
    // store FLAGUPDATE in TEMP(1)
    //
    vmimtMoveRC(8, PPC32_TEMP(0), 0);
    if (rc && oe) {
        vmimtMoveRC(8, PPC32_XER_OV_WR, 0);
        vmimtMoveRC(PPC32_GPR_BITS, PPC32_TEMP(1), FLAGUPDATE_OERC);
    } else if (rc) {
        vmimtMoveRC(PPC32_GPR_BITS, PPC32_TEMP(1), FLAGUPDATE_RC);
    } else if (oe) {
        vmimtMoveRC(8, PPC32_XER_OV_WR, 0);
        vmimtMoveRC(PPC32_GPR_BITS, PPC32_TEMP(1), FLAGUPDATE_OE);
    } else {
        vmimtMoveRC(PPC32_GPR_BITS, PPC32_TEMP(1), FLAGUPDATE_NONE);
    }

    vmimtBinopRRR(PPC32_GPR_BITS, op, rt, ra, rb, 0);

    // Following from Div instruction
    //      Divide by Zero   -> VMI_INTEGER_ABORT
    //      Integer overflow -> VMI_INTEGER_CONTINUE (sets excOverflowFlag)

    //
    // Check Integer Overflow exception, this is set in PPC32_TEMP(0)
    //
    vmimtCondMoveRCR(PPC32_GPR_BITS, PPC32_TEMP(0), 1, rt, 0x80000000, rt);

    //
    // Regenerate Flags in case Integer Overflow occured
    //
    if (rc) {
        vmimtBinopRR(PPC32_GPR_BITS, vmi_OR, rt, rt, flags);
    }

    if (oe) postOE();
    if (rc) postRC();
}

static void warnNopMapping(const char *name) {
    vmiMessage("W", "MORPH_NOP", "Instruction %s mapped to NOP", name);
}

static void morphWarnNopMapping(ppc32MorphStateP state, const char *name) {
    if (state->ppc32->params.WARN_NOP) {
        //
        // Warn on cache ops mapped to NOP
        //
        vmimtArgNatAddress(name);
        vmimtCall((vmiCallFn)warnNopMapping);
    }
}

static void unimplemented(const char *name) {
    vmiMessage("E", "MORPH_UNIMP", "Instruction %s unimplemented", name);
}

static void morphUnimplemented(ppc32MorphStateP state, const char *name) {
    if (state->ppc32->params.UNIMP_TO_NOP) {
        //
        // NOP out the unimplemented instructions
        //
        if (state->ppc32->params.WARN_NOP) {
            //
            // Warn on cache ops mapped to NOP
            //
            vmimtArgNatAddress(name);
            vmimtCall((vmiCallFn)warnNopMapping);
        }
    } else {
        vmimtArgNatAddress(name);
        vmimtCall((vmiCallFn)unimplemented);
        vmimtExit();
    }
}

//
// Write Default Morpher stub Functions
//
PPC32_MORPH_FN(morphFMADD_A1) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRC = state->info.FRC;
    vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPTernopRRRR(
            vmi_FT_64_IEEE_754, vmi_FMADD,
            False,
            FRT, FPR_FRT,
            FRA, FPR_FRA,
            FRC, FPR_FRC,
            FRB, FPR_FRB,
            False
            );
}

PPC32_MORPH_FN(morphFMADDRC_A1) {
    //
    // Supported Architecture=I_FP
    //
    morphFMADD_A1(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFMADDS_A1) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRC = state->info.FRC;
    vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPTernopRRRR(
            vmi_FT_32_IEEE_754, vmi_FMADD,
            False,
            FRT, FPR_FRT,
            FRA, FPR_FRA,
            FRC, FPR_FRC,
            FRB, FPR_FRB,
            False
            );
}

PPC32_MORPH_FN(morphFMADDSRC_A1) {
    //
    // Supported Architecture=I_FP
    //
    morphFMADDS_A1(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFMSUB_A1) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRC = state->info.FRC;
    vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPTernopRRRR(
            vmi_FT_64_IEEE_754, vmi_FMSUB,
            False,
            FRT, FPR_FRT,
            FRA, FPR_FRA,
            FRC, FPR_FRC,
            FRB, FPR_FRB,
            False
            );
}

PPC32_MORPH_FN(morphFMSUBRC_A1) {
    //
    // Supported Architecture=I_FP
    //
    morphFMSUB_A1(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFMSUBS_A1) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRC = state->info.FRC;
    vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPTernopRRRR(
            vmi_FT_32_IEEE_754, vmi_FMSUB,
            False,
            FRT, FPR_FRT,
            FRA, FPR_FRA,
            FRC, FPR_FRC,
            FRB, FPR_FRB,
            False
            );
}

PPC32_MORPH_FN(morphFMSUBSRC_A1) {
    //
    // Supported Architecture=I_FP
    //
    morphFMSUBS_A1(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFNMADD_A1) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRC = state->info.FRC;
    vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPTernopRRRR(
            vmi_FT_64_IEEE_754, vmi_FMADD,
            True,
            FRT, FPR_FRT,
            FRA, FPR_FRA,
            FRC, FPR_FRC,
            FRB, FPR_FRB,
            False
            );
}

PPC32_MORPH_FN(morphFNMADDRC_A1) {
    //
    // Supported Architecture=I_FP
    //
    morphFNMADD_A1(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFNMADDS_A1) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRC = state->info.FRC;
    vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPTernopRRRR(
            vmi_FT_32_IEEE_754, vmi_FMADD,
            True,
            FRT, FPR_FRT,
            FRA, FPR_FRA,
            FRC, FPR_FRC,
            FRB, FPR_FRB,
            False
            );
}

PPC32_MORPH_FN(morphFNMADDSRC_A1) {
    //
    // Supported Architecture=I_FP
    //
    morphFNMADDS_A1(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFNMSUB_A1) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRC = state->info.FRC;
    vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPTernopRRRR(
            vmi_FT_64_IEEE_754, vmi_FMSUB,
            True,
            FRT, FPR_FRT,
            FRA, FPR_FRA,
            FRC, FPR_FRC,
            FRB, FPR_FRB,
            False
            );
}

PPC32_MORPH_FN(morphFNMSUBRC_A1) {
    //
    // Supported Architecture=I_FP
    //
    morphFNMSUB_A1(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFNMSUBS_A1) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRC = state->info.FRC;
    // vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    // vmiReg FPR_FRC = PPC32_FPR_WR(FRC);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "FNMSUBS_A1");
}

PPC32_MORPH_FN(morphFNMSUBSRC_A1) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRC = state->info.FRC;
    // vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    // vmiReg FPR_FRC = PPC32_FPR_WR(FRC);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "FNMSUBSRC_A1");
}

PPC32_MORPH_FN(morphFSEL_A1) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRC = state->info.FRC;
    vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    //
    // FRT = (FRA>=0) ? FRB : FRC;
    // -0 == +0
    //
    vmimtMoveRC(PPC32_FPR_BITS, PPC32_TEMP(0), 0x0000000000000000ULL);
    vmimtFCompareRR(vmi_FT_64_IEEE_754, PPC32_TEMP_REL, FPR_FRA, PPC32_TEMP(0), VMI_NOREG, False, 0);

    // test Result
    // if LT or NAN, FRT = FRB
    // if GT or EQ,  FRT = FRC
    vmimtBinopRRC(PPC32_GPR_BITS, vmi_AND, PPC32_TEMP(2), PPC32_TEMP_REL, (vmi_FPRL_GREATER | vmi_FPRL_EQUAL), 0);
    vmimtCondMoveRRR(PPC32_FPR_BITS, PPC32_TEMP(2), True, FPR_FRT, FPR_FRC, FPR_FRB);
}

PPC32_MORPH_FN(morphFSELRC_A1) {
    //
    // Supported Architecture=I_FP
    //
    morphFSEL_A1(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFADD_A2) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_RD(FRT);

    ppc32FPBinopRRR(vmi_FT_64_IEEE_754, vmi_FADD, FRT, FPR_FRT, FRA, FPR_FRA, FRB, FPR_FRB);
}

PPC32_MORPH_FN(morphFADDRC_A2) {
    //
    // Supported Architecture=I_FP
    //
    morphFADD_A2(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFADDS_A2) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_RD(FRT);

    ppc32FPBinopRRR(vmi_FT_32_IEEE_754, vmi_FADD, FRT, FPR_FRT, FRA, FPR_FRA, FRB, FPR_FRB);
}

PPC32_MORPH_FN(morphFADDSRC_A2) {
    //
    // Supported Architecture=I_FP
    //
    morphFADDS_A2(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFDIV_A2) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_RD(FRT);

    ppc32FPBinopRRR(vmi_FT_64_IEEE_754, vmi_FDIV, FRT, FPR_FRT, FRA, FPR_FRA, FRB, FPR_FRB);
}

PPC32_MORPH_FN(morphFDIVRC_A2) {
    //
    // Supported Architecture=I_FP
    //
    morphFDIV_A2(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFDIVS_A2) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_RD(FRT);

    ppc32FPBinopRRR(vmi_FT_32_IEEE_754, vmi_FDIV, FRT, FPR_FRT, FRA, FPR_FRA, FRB, FPR_FRB);
}

PPC32_MORPH_FN(morphFDIVSRC_A2) {
    //
    // Supported Architecture=I_FP
    //
    morphFDIVS_A2(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFSUB_A2) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_RD(FRT);

    ppc32FPBinopRRR(vmi_FT_64_IEEE_754, vmi_FSUB, FRT, FPR_FRT, FRA, FPR_FRA, FRB, FPR_FRB);
}

PPC32_MORPH_FN(morphFSUBRC_A2) {
    //
    // Supported Architecture=I_FP
    //
    morphFSUB_A2(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFSUBS_A2) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_RD(FRT);

    ppc32FPBinopRRR(vmi_FT_32_IEEE_754, vmi_FSUB, FRT, FPR_FRT, FRA, FPR_FRA, FRB, FPR_FRB);
}

PPC32_MORPH_FN(morphFSUBSRC_A2) {
    //
    // Supported Architecture=I_FP
    //
    morphFSUBS_A2(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFMUL_A3) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRC = state->info.FRC;
    vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_RD(FRT);

    ppc32FPBinopRRR(vmi_FT_64_IEEE_754, vmi_FMUL, FRT, FPR_FRT, FRA, FPR_FRA, FRC, FPR_FRC);
}

PPC32_MORPH_FN(morphFMULRC_A3) {
    //
    // Supported Architecture=I_FP
    //
    morphFMUL_A3(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFMULS_A3) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRC = state->info.FRC;
    vmiReg FPR_FRC = PPC32_FPR_RD(FRC);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_RD(FRT);

    ppc32FPBinopRRR(vmi_FT_32_IEEE_754, vmi_FMUL, FRT, FPR_FRT, FRA, FPR_FRA, FRC, FPR_FRC);
}

PPC32_MORPH_FN(morphFMULSRC_A3) {
    //
    // Supported Architecture=I_FP
    //
    morphFMULS_A3(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFSQRT_A4) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPUnopRR(vmi_FT_64_IEEE_754, vmi_FSQRT, FRT, FPR_FRT, FRB, FPR_FRB);
}

PPC32_MORPH_FN(morphFSQRTRC_A4) {
    //
    // Supported Architecture=I_FP
    //
    morphFSQRT_A4(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFSQRTS_A4) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FSQRTS_A4");
}

PPC32_MORPH_FN(morphFSQRTSRC_A4) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FSQRTSRC_A4");
}

PPC32_MORPH_FN(morphFRE_A5) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPUnopRR(vmi_FT_64_IEEE_754, vmi_FRECIP, FRT, FPR_FRT, FRB, FPR_FRB);
}

PPC32_MORPH_FN(morphFRERC_A5) {
    //
    // Supported Architecture=I_FP
    //
    morphFRE_A5(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFRES_A5) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRES_A5");
}

PPC32_MORPH_FN(morphFRESRC_A5) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRESRC_A5");
}

PPC32_MORPH_FN(morphFRSQRTE_A5) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPUnopRR(vmi_FT_64_IEEE_754, vmi_FRSQRT, FRT, FPR_FRT, FRB, FPR_FRB);
}

PPC32_MORPH_FN(morphFRSQRTERC_A5) {
    //
    // Supported Architecture=I_FP
    //
    morphFRSQRTE_A5(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFRSQRTES_A5) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRSQRTES_A5");
}

PPC32_MORPH_FN(morphFRSQRTESRC_A5) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRSQRTESRC_A5");
}

PPC32_MORPH_FN(morphISEL_A6) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BC = state->info.BC;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    // RT = CR[BC]==1 ? RA : RB
    vmiReg crbit = getCRbit(BC);
    vmimtCondMoveRRR(PPC32_GPR_BITS, crbit, True, GPR_RT, GPR_RA, GPR_RB);
}

PPC32_MORPH_FN(morphBC_B1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 AA = state->info.AA;
    Int16 BD = state->info.BD;
    Uns8 BI = state->info.BI;
    Uns8 BO = state->info.BO;
    Uns8 LK = state->info.LK;

    ppc32branchc(state->info.thisPC, state->info.nextPC, BC, BO, BI, BD, AA, LK);
}

PPC32_MORPH_FN(morphE_BC_BD15) {
    //
    // Supported Architecture=I_VLE
    //
    // Int16 BD = state->info.BD;
    // Uns8 BI32 = state->info.BI32;
    // Uns8 BO32 = state->info.BO32;
    // Uns8 LK = state->info.LK;

    state->info.AA = 0;
    state->info.BI = state->info.BI32;
    //
    // B0=0|01.. BO32=00 False
    // B0=0|11.. BO32=01 True
    // B0=1|.00. BO32=10 DecCTR Ctr!=0
    // B0=1|.01. BO32=11 DecCTR Ctr==0
    //
    switch (state->info.BO32) {
    case 0:
        state->info.BO = 0x04;
        break;
    case 1:
        state->info.BO = 0x0c;
        break;
    case 2:
        state->info.BO = 0x10;
        break;
    case 3:
        state->info.BO = 0x12;
        break;
    }
    morphBC_B1(state);
}

PPC32_MORPH_FN(morphE_B_BD24) {
    //
    // Supported Architecture=I_VLE
    //
    // Int32 BD24 = state->info.BD24;
    // Uns8 LK = state->info.LK;

    state->info.AA = 0;
    state->info.LI = state->info.BD24;
    morphB_I1(state);
}

PPC32_MORPH_FN(morphSE_BC_BD81) {
    //
    // Supported Architecture=I_VLE
    //
    // Int16 BD8 = state->info.BD8;
    // Uns8 BI16 = state->info.BI16;
    // Uns8 BO16 = state->info.BO16;

    state->info.AA = 0;
    state->info.LK = 0;
    state->info.BD = state->info.BD8;
    state->info.BI = state->info.BI16;
    //
    // B0=0|01.. BO16=0 False
    // B0=0|11.. BO16=1 True
    //
    switch (state->info.BO16) {
    case 0:
        state->info.BO = 0x04;
        break;
    case 1:
        state->info.BO = 0x0c;
        break;
    }
    morphBC_B1(state);
}

PPC32_MORPH_FN(morphSE_B_BD82) {
    //
    // Supported Architecture=I_VLE
    //
    // Int16 BD8 = state->info.BD8;
    // Uns8 LK = state->info.LK;

    state->info.AA = 0;
    state->info.LI = state->info.BD8;
    morphB_I1(state);
}

PPC32_MORPH_FN(morphSE_ILLEGAL_C_0) {
    //
    // Supported Architecture=I_VLE
    //
    morphUnimplemented(state, "SE_ILLEGAL_C_0");
}

PPC32_MORPH_FN(morphSE_ISYNC_C_0) {
    //
    // Supported Architecture=I_VLE
    //
    morphWarnNopMapping(state, "SE_ISYNC");
}

PPC32_MORPH_FN(morphSE_RFCI_C_0) {
    //
    // Supported Architecture=I_VLE
    //
    CHECK_PRIV(state);

    morphUnimplemented(state, "SE_RFCI_C_0");
}

PPC32_MORPH_FN(morphSE_RFDI_C_0) {
    //
    // Supported Architecture=I_VLE
    //
    CHECK_PRIV(state);

    morphUnimplemented(state, "SE_RFDI_C_0");
}

PPC32_MORPH_FN(morphSE_RFI_C_0) {
    //
    // Supported Architecture=I_VLE
    //
    CHECK_PRIV(state);

    morphUnimplemented(state, "SE_RFI_C_0");
}

PPC32_MORPH_FN(morphSE_RFMCI_C_0) {
    //
    // Supported Architecture=I_VLE
    //
    CHECK_PRIV(state);

    morphUnimplemented(state, "SE_RFMCI_C_0");
}

PPC32_MORPH_FN(morphSE_SC_C_0) {
    //
    // Supported Architecture=I_VLE
    //
    state->info.LEV = 0;
    morphSC_SC1(state);
}

PPC32_MORPH_FN(morphSE_BCTR_C_1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 LK = state->info.LK;

    ppc32branchc(state->info.thisPC, state->info.nextPC, BCCTR, 0x1f, 0, 0, 0, LK);
}

PPC32_MORPH_FN(morphSE_BLR_C_1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 LK = state->info.LK;

    ppc32branchc(state->info.thisPC, state->info.nextPC, BCLR, 0x1f, 0, 0, 0, LK);
}

PPC32_MORPH_FN(morphE_LBZ_D1) {
    //
    // Supported Architecture=I_VLE
    //
    // Int16 D = state->info.D;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);

    morphLBZ_D1(state);
}

PPC32_MORPH_FN(morphE_LHA_D1) {
    //
    // Supported Architecture=I_VLE
    //
    // Int16 D = state->info.D;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);

    morphLHA_D1(state);
}

PPC32_MORPH_FN(morphE_LHZ_D1) {
    //
    // Supported Architecture=I_VLE
    //
    // Int16 D = state->info.D;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);

    morphLHZ_D1(state);
}

PPC32_MORPH_FN(morphE_LWZ_D1) {
    //
    // Supported Architecture=I_VLE
    //
    // Int16 D = state->info.D;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);

    morphLWZ_D1(state);
}

PPC32_MORPH_FN(morphLBZ_D1) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, VMI_NOREG, state, D, 8, 0, 0, 0, 0);

}

PPC32_MORPH_FN(morphLBZU_D1) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, VMI_NOREG, state, D, 8, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphLHA_D1) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, VMI_NOREG, state, D, 16, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphLHAU_D1) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, VMI_NOREG, state, D, 16, 1, 0, 1, 0);
}

PPC32_MORPH_FN(morphLHZ_D1) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, VMI_NOREG, state, D, 16, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphLHZU_D1) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, VMI_NOREG, state, D, 16, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphLMW_D1) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;

    ppc32loadAll(RT, GPR_RA, state, D);
}

PPC32_MORPH_FN(morphLWZ_D1) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, VMI_NOREG, state, D, 32, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphLWZU_D1) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, VMI_NOREG, state, D, 32, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphE_ADD16I_D2) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Int16 SI = state->info.SI;

    morphADDI_D2_0(state);
}

PPC32_MORPH_FN(morphADDI_D2_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_RD(RT);
    Int16 SI = state->info.SI;

    ppc32BinopRRC(vmi_ADD, GPR_RT, GPR_RA, SI, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphADDIC_D2_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_RD(RT);
    Int16 SI = state->info.SI;

    ppc32BinopRRC(vmi_ADD, GPR_RT, GPR_RA, SI, 0, 0, 1, 0, 0);
}

PPC32_MORPH_FN(morphADDICRC_D2_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_RD(RT);
    Int16 SI = state->info.SI;

    ppc32BinopRRC(vmi_ADD, GPR_RT, GPR_RA, SI, 0, 1, 1, 0, 0);
}

PPC32_MORPH_FN(morphADDIS_D2_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_RD(RT);
    Int16 SI = state->info.SI;

    ppc32BinopRRC(vmi_ADD, GPR_RT, GPR_RA, (SI<<16), 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphMULLI_D2_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Int16 SI = state->info.SI;

    ppc32BinopRRC(vmi_IMUL, GPR_RT, GPR_RA, SI, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSUBFIC_D2_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Int16 SI = state->info.SI;

    ppc32BinopRRC(vmi_RSUB, GPR_RT, GPR_RA, SI, 0, 0, 1, 0, 1);
}

PPC32_MORPH_FN(morphLI_D2_1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Int16 SI = state->info.SI;

    vmimtUnopRC(PPC32_GPR_BITS, vmi_ADD, GPR_RT, SI, 0);
}

PPC32_MORPH_FN(morphLIS_D2_1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Int16 SI = state->info.SI;

    vmimtUnopRC(PPC32_GPR_BITS, vmi_ADD, GPR_RT, (SI << 16), 0);
}

PPC32_MORPH_FN(morphE_STB_D3) {
    //
    // Supported Architecture=I_VLE
    //
    // Int16 D = state->info.D;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);

    morphSTB_D3(state);
}

PPC32_MORPH_FN(morphE_STH_D3) {
    //
    // Supported Architecture=I_VLE
    //
    // Int16 D = state->info.D;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);

    morphSTH_D3(state);
}

PPC32_MORPH_FN(morphE_STW_D3) {
    //
    // Supported Architecture=I_VLE
    //
    // Int16 D = state->info.D;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);

    morphSTW_D3(state);
}

PPC32_MORPH_FN(morphSTB_D3) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, VMI_NOREG, state, D, 8, 0, 0, 0);
}

PPC32_MORPH_FN(morphSTBU_D3) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, VMI_NOREG, state, D, 8, 0, 1, 0);
}

PPC32_MORPH_FN(morphSTH_D3) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, VMI_NOREG, state, D, 16, 0, 0, 0);
}

PPC32_MORPH_FN(morphSTHU_D3) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, VMI_NOREG, state, D, 16, 0, 1, 0);
}

PPC32_MORPH_FN(morphSTMW_D3) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RS = state->info.RS;

    ppc32storeAll(RS, GPR_RA, state, D);
}

PPC32_MORPH_FN(morphSTW_D3) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, VMI_NOREG, state, D, 32, 0, 0, 0);
}

PPC32_MORPH_FN(morphSTWU_D3) {
    //
    // Supported Architecture=I_B
    //
    Int16 D = state->info.D;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, VMI_NOREG, state, D, 32, 0, 1, 0);
}

PPC32_MORPH_FN(morphANDIRC_D4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns16 UI = state->info.UI;

    ppc32BinopRRC(vmi_AND, GPR_RA, GPR_RS, UI, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphANDISRC_D4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns16 UI = state->info.UI;

    ppc32BinopRRC(vmi_AND, GPR_RA, GPR_RS, (UI<<16), 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphORI_D4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns16 UI = state->info.UI;

    ppc32BinopRRC(vmi_OR, GPR_RA, GPR_RS, UI, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphORIS_D4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns16 UI = state->info.UI;

    ppc32BinopRRC(vmi_OR, GPR_RA, GPR_RS, (UI<<16), 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphXORI_D4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns16 UI = state->info.UI;

    ppc32BinopRRC(vmi_XOR, GPR_RA, GPR_RS, UI, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphXORIS_D4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns16 UI = state->info.UI;

    ppc32BinopRRC(vmi_XOR, GPR_RA, GPR_RS, (UI<<16), 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphCMPWI_D5_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BF = state->info.BF;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Int16 SI = state->info.SI;

    ppc32compare(PPC32_GPR_BITS, GPR_RA, VMI_NOREG, BF, SI, 1, vmi_COND_L);
}

PPC32_MORPH_FN(morphCMPI_D5_1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BF = state->info.BF;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Int16 SI = state->info.SI;

    ppc32compare(PPC32_GPR_BITS, GPR_RA, VMI_NOREG, BF, SI, 1, vmi_COND_L);
}

PPC32_MORPH_FN(morphCMPLWI_D6_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BF = state->info.BF;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns16 UI = state->info.UI;

    ppc32compare(PPC32_GPR_BITS, GPR_RA, VMI_NOREG, BF, UI, 1, vmi_COND_B);
}

PPC32_MORPH_FN(morphCMPLI_D6_1) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns16 UI = state->info.UI;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "CMPLI_D6_1");
}



static void vmic_trap(ppc32P ppc32, Uns32 to, Uns32 ra, Int32 si) {
    Int32 sa = ppc32->GPR[ra];
    Uns32 ua = sa;
    Uns32 ui = si;

    vmiPrintf("vmic_trap: to=0x%02x\n", to);
    vmiPrintf("vmic_trap: r%d = (signed)%d (unsigned)%u\n", ra, sa, ua);
    vmiPrintf("vmic_trap: si = (signed)%d (unsigned)%d\n", si, ui);

    Bool takeException = False;

    // b0 *ra < si
    if (to & 0x01) if (sa < si)  takeException = True;
    if (to & 0x02) if (sa > si)  takeException = True;
    if (to & 0x04) if (sa == si) takeException = True;
    if (to & 0x08) if (ua < ui)  takeException = True;
    if (to & 0x10) if (ua > ui)  takeException = True;

    vmiPrintf("TRAP %s\n", (takeException) ? "Take" : "Ignore");

    vmiMessage("F", "FATAL", "nomsg");

    // Next Instruction Address SRR0;
    if (takeException) {
        vmirtSetPC((vmiProcessorP)ppc32, (Addr)EXC_PROGRAM);
    }
}

PPC32_MORPH_FN(morphTWI_D7) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    Int16 SI = state->info.SI;
    Uns8 TO = state->info.TO;

    vmimtArgProcessor();
    vmimtArgUns32(TO);
    vmimtArgUns32(RA);
    vmimtArgUns32(SI);
    vmimtCall((vmiCallFn)vmic_trap);
}

PPC32_MORPH_FN(morphLFD_D8) {
    //
    // Supported Architecture=I_FP
    //
    Int16 D = state->info.D;
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);

    ppc32loadDFPR(FPR_FRT, GPR_RA, VMI_NOREG, state, D, PPC32_FPR_BITS, False);
}

PPC32_MORPH_FN(morphLFDU_D8) {
    //
    // Supported Architecture=I_FP
    //
    Int16 D = state->info.D;
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);

    ppc32loadDFPR(FPR_FRT, GPR_RA, VMI_NOREG, state, D, PPC32_FPR_BITS, True);
}

PPC32_MORPH_FN(morphLFS_D8) {
    //
    // Supported Architecture=I_FP
    //
    Int16 D = state->info.D;
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);

    ppc32loadSFPR(FPR_FRT, GPR_RA, VMI_NOREG, state, D, PPC32_FPR_BITS/2, False);
}

PPC32_MORPH_FN(morphLFSU_D8) {
    //
    // Supported Architecture=I_FP
    //
    Int16 D = state->info.D;
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);

    ppc32loadSFPR(FPR_FRT, GPR_RA, VMI_NOREG, state, D, PPC32_FPR_BITS/2, True);
}

PPC32_MORPH_FN(morphE_LBZU_D8_0) {
    //
    // Supported Architecture=I_VLE
    //
    // Int8 D8 = state->info.D8;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg PR_RT = PPC32_PR_RD(RT);
    // vmiReg PR_RT = PPC32_PR_WR(RT);

    state->info.D = state->info.D8;
    morphLBZU_D1(state);
}

PPC32_MORPH_FN(morphE_LHAU_D8_0) {
    //
    // Supported Architecture=I_VLE
    //
    // Int8 D8 = state->info.D8;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg PR_RT = PPC32_PR_RD(RT);
    // vmiReg PR_RT = PPC32_PR_WR(RT);

    state->info.D = state->info.D8;
    morphLHAU_D1(state);
}

PPC32_MORPH_FN(morphE_LHZU_D8_0) {
    //
    // Supported Architecture=I_VLE
    //
    // Int8 D8 = state->info.D8;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg PR_RT = PPC32_PR_RD(RT);
    // vmiReg PR_RT = PPC32_PR_WR(RT);

    state->info.D = state->info.D8;
    morphLHZU_D1(state);
}

PPC32_MORPH_FN(morphE_LMW_D8_0) {
    //
    // Supported Architecture=I_VLE
    //
    // Int8 D8 = state->info.D8;
    // Uns8 RA = state->info.RA;
    // Uns8 RT = state->info.RT;

    state->info.D = state->info.D8;
    morphLMW_D1(state);
}

PPC32_MORPH_FN(morphE_LWZU_D8_0) {
    //
    // Supported Architecture=I_VLE
    //
    // Int8 D8 = state->info.D8;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg PR_RT = PPC32_PR_RD(RT);
    // vmiReg PR_RT = PPC32_PR_WR(RT);

    state->info.D = state->info.D8;
    morphLWZU_D1(state);
}

PPC32_MORPH_FN(morphE_STBU_D8_1) {
    //
    // Supported Architecture=I_VLE
    //
    // Int8 D8 = state->info.D8;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg PR_RS = PPC32_PR_RD(RS);
    // vmiReg PR_RS = PPC32_PR_WR(RS);

    state->info.D = state->info.D8;
    morphSTBU_D3(state);
}

PPC32_MORPH_FN(morphE_STHU_D8_1) {
    //
    // Supported Architecture=I_VLE
    //
    // Int8 D8 = state->info.D8;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg PR_RS = PPC32_PR_RD(RS);
    // vmiReg PR_RS = PPC32_PR_WR(RS);

    state->info.D = state->info.D8;
    morphSTHU_D3(state);
}

PPC32_MORPH_FN(morphE_STMW_D8_1) {
    //
    // Supported Architecture=I_VLE
    //
    // Int8 D8 = state->info.D8;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg PR_RS = PPC32_PR_RD(RS);
    // vmiReg PR_RS = PPC32_PR_WR(RS);

    state->info.D = state->info.D8;
    morphSTMW_D3(state);
}

PPC32_MORPH_FN(morphE_STWU_D8_1) {
    //
    // Supported Architecture=I_VLE
    //
    // Int8 D8 = state->info.D8;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg PR_RS = PPC32_PR_RD(RS);
    // vmiReg PR_RS = PPC32_PR_WR(RS);

    state->info.D = state->info.D8;
    morphSTWU_D3(state);
}

PPC32_MORPH_FN(morphSTFD_D9) {
    //
    // Supported Architecture=I_FP
    //
    Int16 D = state->info.D;
    Uns8 FRS = state->info.FRS;
    vmiReg FPR_FRS = PPC32_FPR_RD(FRS);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);

    ppc32storeDFPR(FPR_FRS, GPR_RA, VMI_NOREG, state, D, PPC32_FPR_BITS, False);
}

PPC32_MORPH_FN(morphSTFDU_D9) {
    //
    // Supported Architecture=I_FP
    //
    Int16 D = state->info.D;
    Uns8 FRS = state->info.FRS;
    vmiReg FPR_FRS = PPC32_FPR_RD(FRS);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);

    ppc32storeDFPR(FPR_FRS, GPR_RA, VMI_NOREG, state, D, PPC32_FPR_BITS, True);
}

PPC32_MORPH_FN(morphSTFS_D9) {
    //
    // Supported Architecture=I_FP
    //
    Int16 D = state->info.D;
    Uns8 FRS = state->info.FRS;
    vmiReg FPR_FRS = PPC32_FPR_RD(FRS);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);

    ppc32storeSFPR(FPR_FRS, GPR_RA, VMI_NOREG, state, D, False);
}

PPC32_MORPH_FN(morphSTFSU_D9) {
    //
    // Supported Architecture=I_FP
    //
    Int16 D = state->info.D;
    Uns8 FRS = state->info.FRS;
    vmiReg FPR_FRS = PPC32_FPR_RD(FRS);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);

    ppc32storeSFPR(FPR_FRS, GPR_RA, VMI_NOREG, state, D, True);
}

PPC32_MORPH_FN(morphLQ_DQ1) {
    //
    // Supported Architecture=I_LMA
    //
    // Int16 DQ = state->info.DQ;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RTp = state->info.RTp;
    // vmiReg GPR_RTp = PPC32_GPR_RD(RTp);
    // vmiReg GPR_RTp = PPC32_GPR_WR(RTp);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "LQ_DQ1");
}

PPC32_MORPH_FN(morphSTQ_DS3) {
    //
    // Supported Architecture=I_LMA
    //
    // Int16 DS = state->info.DS;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RSp = state->info.RSp;
    // vmiReg GPR_RSp = PPC32_GPR_RD(RSp);
    // vmiReg GPR_RSp = PPC32_GPR_WR(RSp);
    CHECK_PRIV(state);

    morphUnimplemented(state, "STQ_DS3");
}

PPC32_MORPH_FN(morphEVSEL_EVS) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BFA = state->info.BFA;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVSEL_EVS");
}

PPC32_MORPH_FN(morphBRINC_EVX1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    morphUnimplemented(state, "BRINC_EVX1");
}

PPC32_MORPH_FN(morphEVSTDDX_EVX1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    morphUnimplemented(state, "EVSTDDX_EVX1");
}

PPC32_MORPH_FN(morphEVSTDHX_EVX1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    morphUnimplemented(state, "EVSTDHX_EVX1");
}

PPC32_MORPH_FN(morphEVSTDWX_EVX1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    morphUnimplemented(state, "EVSTDWX_EVX1");
}

PPC32_MORPH_FN(morphEVSTWHEX_EVX1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    morphUnimplemented(state, "EVSTWHEX_EVX1");
}

PPC32_MORPH_FN(morphEVSTWHOX_EVX1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    morphUnimplemented(state, "EVSTWHOX_EVX1");
}

PPC32_MORPH_FN(morphEVSTWWEX_EVX1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    morphUnimplemented(state, "EVSTWWEX_EVX1");
}

PPC32_MORPH_FN(morphEVSTWWOX_EVX1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    morphUnimplemented(state, "EVSTWWOX_EVX1");
}

PPC32_MORPH_FN(morphEVSTWHE_EVX2_2) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVSTWHE_EVX2_2");
}

PPC32_MORPH_FN(morphEVSTWHO_EVX2_2) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVSTWHO_EVX2_2");
}

PPC32_MORPH_FN(morphEVSTWWE_EVX2_2) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVSTWWE_EVX2_2");
}

PPC32_MORPH_FN(morphEVSTWWO_EVX2_2) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVSTWWO_EVX2_2");
}

PPC32_MORPH_FN(morphEVSTDD_EVX2_3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVSTDD_EVX2_3");
}

PPC32_MORPH_FN(morphEVSTDH_EVX2_3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVSTDH_EVX2_3");
}

PPC32_MORPH_FN(morphEVSTDW_EVX2_3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVSTDW_EVX2_3");
}

PPC32_MORPH_FN(morphEFDCFS_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCFS_EVX3");
}

PPC32_MORPH_FN(morphEFDCFSF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCFSF_EVX3");
}

PPC32_MORPH_FN(morphEFDCFSI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCFSI_EVX3");
}

PPC32_MORPH_FN(morphEFDCFSID_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCFSID_EVX3");
}

PPC32_MORPH_FN(morphEFDCFUF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCFUF_EVX3");
}

PPC32_MORPH_FN(morphEFDCFUI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCFUI_EVX3");
}

PPC32_MORPH_FN(morphEFDCFUID_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCFUID_EVX3");
}

PPC32_MORPH_FN(morphEFDCTSF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCTSF_EVX3");
}

PPC32_MORPH_FN(morphEFDCTSI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCTSI_EVX3");
}

PPC32_MORPH_FN(morphEFDCTSIDZ_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCTSIDZ_EVX3");
}

PPC32_MORPH_FN(morphEFDCTSIZ_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCTSIZ_EVX3");
}

PPC32_MORPH_FN(morphEFDCTUF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCTUF_EVX3");
}

PPC32_MORPH_FN(morphEFDCTUI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCTUI_EVX3");
}

PPC32_MORPH_FN(morphEFDCTUIDZ_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCTUIDZ_EVX3");
}

PPC32_MORPH_FN(morphEFDCTUIZ_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCTUIZ_EVX3");
}

PPC32_MORPH_FN(morphEFSCFD_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCFD_EVX3");
}

PPC32_MORPH_FN(morphEFSCFSF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCFSF_EVX3");
}

PPC32_MORPH_FN(morphEFSCFSI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCFSI_EVX3");
}

PPC32_MORPH_FN(morphEFSCFUF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCFUF_EVX3");
}

PPC32_MORPH_FN(morphEFSCFUI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCFUI_EVX3");
}

PPC32_MORPH_FN(morphEFSCTSF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCTSF_EVX3");
}

PPC32_MORPH_FN(morphEFSCTSI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCTSI_EVX3");
}

PPC32_MORPH_FN(morphEFSCTSIZ_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCTSIZ_EVX3");
}

PPC32_MORPH_FN(morphEFSCTUF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCTUF_EVX3");
}

PPC32_MORPH_FN(morphEFSCTUI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCTUI_EVX3");
}

PPC32_MORPH_FN(morphEFSCTUIZ_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCTUIZ_EVX3");
}

PPC32_MORPH_FN(morphEVFSCFSF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCFSF_EVX3");
}

PPC32_MORPH_FN(morphEVFSCFSI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCFSI_EVX3");
}

PPC32_MORPH_FN(morphEVFSCFUF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCFUF_EVX3");
}

PPC32_MORPH_FN(morphEVFSCFUI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCFUI_EVX3");
}

PPC32_MORPH_FN(morphEVFSCTSF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCTSF_EVX3");
}

PPC32_MORPH_FN(morphEVFSCTSI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCTSI_EVX3");
}

PPC32_MORPH_FN(morphEVFSCTSIZ_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCTSIZ_EVX3");
}

PPC32_MORPH_FN(morphEVFSCTUF_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCTUF_EVX3");
}

PPC32_MORPH_FN(morphEVFSCTUI_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCTUI_EVX3");
}

PPC32_MORPH_FN(morphEVFSCTUIZ_EVX3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCTUIZ_EVX3");
}

PPC32_MORPH_FN(morphEFDADD_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EFDADD_EVX4");
}

PPC32_MORPH_FN(morphEFDDIV_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EFDDIV_EVX4");
}

PPC32_MORPH_FN(morphEFDMUL_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EFDMUL_EVX4");
}

PPC32_MORPH_FN(morphEFDSUB_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EFDSUB_EVX4");
}

PPC32_MORPH_FN(morphEFSADD_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EFSADD_EVX4");
}

PPC32_MORPH_FN(morphEFSDIV_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EFSDIV_EVX4");
}

PPC32_MORPH_FN(morphEFSMUL_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EFSMUL_EVX4");
}

PPC32_MORPH_FN(morphEFSSUB_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EFSSUB_EVX4");
}

PPC32_MORPH_FN(morphEVADDW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVADDW_EVX4");
}

PPC32_MORPH_FN(morphEVAND_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVAND_EVX4");
}

PPC32_MORPH_FN(morphEVANDC_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVANDC_EVX4");
}

PPC32_MORPH_FN(morphEVDIVWS_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVDIVWS_EVX4");
}

PPC32_MORPH_FN(morphEVDIVWU_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVDIVWU_EVX4");
}

PPC32_MORPH_FN(morphEVEQV_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVEQV_EVX4");
}

PPC32_MORPH_FN(morphEVFSADD_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVFSADD_EVX4");
}

PPC32_MORPH_FN(morphEVFSDIV_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVFSDIV_EVX4");
}

PPC32_MORPH_FN(morphEVFSMUL_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVFSMUL_EVX4");
}

PPC32_MORPH_FN(morphEVFSSUB_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVFSSUB_EVX4");
}

PPC32_MORPH_FN(morphEVLDDX_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVLDDX_EVX4");
}

PPC32_MORPH_FN(morphEVLDHX_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVLDHX_EVX4");
}

PPC32_MORPH_FN(morphEVLDWX_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVLDWX_EVX4");
}

PPC32_MORPH_FN(morphEVLHHESPLATX_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVLHHESPLATX_EVX4");
}

PPC32_MORPH_FN(morphEVLHHOSSPLATX_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVLHHOSSPLATX_EVX4");
}

PPC32_MORPH_FN(morphEVLHHOUSPLATX_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVLHHOUSPLATX_EVX4");
}

PPC32_MORPH_FN(morphEVLWHEX_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVLWHEX_EVX4");
}

PPC32_MORPH_FN(morphEVLWHOSX_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVLWHOSX_EVX4");
}

PPC32_MORPH_FN(morphEVLWHOUX_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVLWHOUX_EVX4");
}

PPC32_MORPH_FN(morphEVLWHSPLATX_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVLWHSPLATX_EVX4");
}

PPC32_MORPH_FN(morphEVLWWSPLATX_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVLWWSPLATX_EVX4");
}

PPC32_MORPH_FN(morphEVMERGEHI_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMERGEHI_EVX4");
}

PPC32_MORPH_FN(morphEVMERGEHILO_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMERGEHILO_EVX4");
}

PPC32_MORPH_FN(morphEVMERGELO_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMERGELO_EVX4");
}

PPC32_MORPH_FN(morphEVMERGELOHI_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMERGELOHI_EVX4");
}

PPC32_MORPH_FN(morphEVMHEGSMFAA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEGSMFAA_EVX4");
}

PPC32_MORPH_FN(morphEVMHEGSMFAN_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEGSMFAN_EVX4");
}

PPC32_MORPH_FN(morphEVMHEGSMIAA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEGSMIAA_EVX4");
}

PPC32_MORPH_FN(morphEVMHEGSMIAN_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEGSMIAN_EVX4");
}

PPC32_MORPH_FN(morphEVMHEGUMIAA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEGUMIAA_EVX4");
}

PPC32_MORPH_FN(morphEVMHEGUMIAN_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEGUMIAN_EVX4");
}

PPC32_MORPH_FN(morphEVMHESMF_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESMF_EVX4");
}

PPC32_MORPH_FN(morphEVMHESMFA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESMFA_EVX4");
}

PPC32_MORPH_FN(morphEVMHESMFAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESMFAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHESMFANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESMFANW_EVX4");
}

PPC32_MORPH_FN(morphEVMHESMI_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESMI_EVX4");
}

PPC32_MORPH_FN(morphEVMHESMIA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESMIA_EVX4");
}

PPC32_MORPH_FN(morphEVMHESMIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESMIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHESMIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESMIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMHESSF_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESSF_EVX4");
}

PPC32_MORPH_FN(morphEVMHESSFA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESSFA_EVX4");
}

PPC32_MORPH_FN(morphEVMHESSFAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESSFAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHESSFANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESSFANW_EVX4");
}

PPC32_MORPH_FN(morphEVMHESSIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESSIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHESSIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHESSIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMHEUMI_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEUMI_EVX4");
}

PPC32_MORPH_FN(morphEVMHEUMIA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEUMIA_EVX4");
}

PPC32_MORPH_FN(morphEVMHEUMIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEUMIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHEUMIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEUMIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMHEUSIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEUSIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHEUSIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHEUSIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOGSMFAA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOGSMFAA_EVX4");
}

PPC32_MORPH_FN(morphEVMHOGSMFAN_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOGSMFAN_EVX4");
}

PPC32_MORPH_FN(morphEVMHOGSMIAA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOGSMIAA_EVX4");
}

PPC32_MORPH_FN(morphEVMHOGSMIAN_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOGSMIAN_EVX4");
}

PPC32_MORPH_FN(morphEVMHOGUMIAA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOGUMIAA_EVX4");
}

PPC32_MORPH_FN(morphEVMHOGUMIAN_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOGUMIAN_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSMF_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSMF_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSMFA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSMFA_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSMFAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSMFAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSMFANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSMFANW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSMI_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSMI_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSMIA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSMIA_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSMIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSMIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSMIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSMIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSSF_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSSF_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSSFA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSSFA_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSSFAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSSFAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSSFANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSSFANW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSSIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSSIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOSSIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOSSIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOUMI_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOUMI_EVX4");
}

PPC32_MORPH_FN(morphEVMHOUMIA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOUMIA_EVX4");
}

PPC32_MORPH_FN(morphEVMHOUMIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOUMIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOUMIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOUMIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOUSIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOUSIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMHOUSIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMHOUSIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMWHSMF_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWHSMF_EVX4");
}

PPC32_MORPH_FN(morphEVMWHSMFA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWHSMFA_EVX4");
}

PPC32_MORPH_FN(morphEVMWHSMI_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWHSMI_EVX4");
}

PPC32_MORPH_FN(morphEVMWHSMIA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWHSMIA_EVX4");
}

PPC32_MORPH_FN(morphEVMWHSSF_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWHSSF_EVX4");
}

PPC32_MORPH_FN(morphEVMWHSSFA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWHSSFA_EVX4");
}

PPC32_MORPH_FN(morphEVMWHUMI_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWHUMI_EVX4");
}

PPC32_MORPH_FN(morphEVMWHUMIA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWHUMIA_EVX4");
}

PPC32_MORPH_FN(morphEVMWLSMIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWLSMIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMWLSMIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWLSMIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMWLSSIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWLSSIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMWLSSIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWLSSIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMWLUMI_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWLUMI_EVX4");
}

PPC32_MORPH_FN(morphEVMWLUMIA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWLUMIA_EVX4");
}

PPC32_MORPH_FN(morphEVMWLUMIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWLUMIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMWLUMIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWLUMIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMWLUSIAAW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWLUSIAAW_EVX4");
}

PPC32_MORPH_FN(morphEVMWLUSIANW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWLUSIANW_EVX4");
}

PPC32_MORPH_FN(morphEVMWSMF_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSMF_EVX4");
}

PPC32_MORPH_FN(morphEVMWSMFA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSMFA_EVX4");
}

PPC32_MORPH_FN(morphEVMWSMFAA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSMFAA_EVX4");
}

PPC32_MORPH_FN(morphEVMWSMFAN_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSMFAN_EVX4");
}

PPC32_MORPH_FN(morphEVMWSMI_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSMI_EVX4");
}

PPC32_MORPH_FN(morphEVMWSMIA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSMIA_EVX4");
}

PPC32_MORPH_FN(morphEVMWSMIAA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSMIAA_EVX4");
}

PPC32_MORPH_FN(morphEVMWSMIAN_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSMIAN_EVX4");
}

PPC32_MORPH_FN(morphEVMWSSF_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSSF_EVX4");
}

PPC32_MORPH_FN(morphEVMWSSFA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSSFA_EVX4");
}

PPC32_MORPH_FN(morphEVMWSSFAA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSSFAA_EVX4");
}

PPC32_MORPH_FN(morphEVMWSSFAN_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWSSFAN_EVX4");
}

PPC32_MORPH_FN(morphEVMWUMI_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWUMI_EVX4");
}

PPC32_MORPH_FN(morphEVMWUMIA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWUMIA_EVX4");
}

PPC32_MORPH_FN(morphEVMWUMIAA_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWUMIAA_EVX4");
}

PPC32_MORPH_FN(morphEVMWUMIAN_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVMWUMIAN_EVX4");
}

PPC32_MORPH_FN(morphEVNAND_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVNAND_EVX4");
}

PPC32_MORPH_FN(morphEVNOR_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVNOR_EVX4");
}

PPC32_MORPH_FN(morphEVOR_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVOR_EVX4");
}

PPC32_MORPH_FN(morphEVORC_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVORC_EVX4");
}

PPC32_MORPH_FN(morphEVRLW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVRLW_EVX4");
}

PPC32_MORPH_FN(morphEVSLW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVSLW_EVX4");
}

PPC32_MORPH_FN(morphEVSRWS_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVSRWS_EVX4");
}

PPC32_MORPH_FN(morphEVSRWU_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVSRWU_EVX4");
}

PPC32_MORPH_FN(morphEVSUBFW_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVSUBFW_EVX4");
}

PPC32_MORPH_FN(morphEVXOR_EVX4) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    morphUnimplemented(state, "EVXOR_EVX4");
}

PPC32_MORPH_FN(morphEFDABS_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDABS_EVX5");
}

PPC32_MORPH_FN(morphEFDNABS_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDNABS_EVX5");
}

PPC32_MORPH_FN(morphEFDNEG_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDNEG_EVX5");
}

PPC32_MORPH_FN(morphEFSABS_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSABS_EVX5");
}

PPC32_MORPH_FN(morphEFSNABS_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSNABS_EVX5");
}

PPC32_MORPH_FN(morphEFSNEG_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSNEG_EVX5");
}

PPC32_MORPH_FN(morphEVABS_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVABS_EVX5");
}

PPC32_MORPH_FN(morphEVADDSMIAAW_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVADDSMIAAW_EVX5");
}

PPC32_MORPH_FN(morphEVADDSSIAAW_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVADDSSIAAW_EVX5");
}

PPC32_MORPH_FN(morphEVADDUMIAAW_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVADDUMIAAW_EVX5");
}

PPC32_MORPH_FN(morphEVADDUSIAAW_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVADDUSIAAW_EVX5");
}

PPC32_MORPH_FN(morphEVCNTLSW_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVCNTLSW_EVX5");
}

PPC32_MORPH_FN(morphEVCNTLZW_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVCNTLZW_EVX5");
}

PPC32_MORPH_FN(morphEVEXTSB_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVEXTSB_EVX5");
}

PPC32_MORPH_FN(morphEVEXTSH_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVEXTSH_EVX5");
}

PPC32_MORPH_FN(morphEVFSABS_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSABS_EVX5");
}

PPC32_MORPH_FN(morphEVFSNABS_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSNABS_EVX5");
}

PPC32_MORPH_FN(morphEVFSNEG_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSNEG_EVX5");
}

PPC32_MORPH_FN(morphEVMRA_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVMRA_EVX5");
}

PPC32_MORPH_FN(morphEVNEG_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVNEG_EVX5");
}

PPC32_MORPH_FN(morphEVRNDW_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVRNDW_EVX5");
}

PPC32_MORPH_FN(morphEVSUBFSMIAAW_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVSUBFSMIAAW_EVX5");
}

PPC32_MORPH_FN(morphEVSUBFSSIAAW_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVSUBFSSIAAW_EVX5");
}

PPC32_MORPH_FN(morphEVSUBFUMIAAW_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVSUBFUMIAAW_EVX5");
}

PPC32_MORPH_FN(morphEVSUBFUSIAAW_EVX5) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVSUBFUSIAAW_EVX5");
}

PPC32_MORPH_FN(morphEVADDIW_EVX6_1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVADDIW_EVX6_1");
}

PPC32_MORPH_FN(morphEVSUBIFW_EVX6_2) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVSUBIFW_EVX6_2");
}

PPC32_MORPH_FN(morphEFDCMPEQ_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCMPEQ_EVX7");
}

PPC32_MORPH_FN(morphEFDCMPGT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCMPGT_EVX7");
}

PPC32_MORPH_FN(morphEFDCMPLT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDCMPLT_EVX7");
}

PPC32_MORPH_FN(morphEFDTSTEQ_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDTSTEQ_EVX7");
}

PPC32_MORPH_FN(morphEFDTSTGT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDTSTGT_EVX7");
}

PPC32_MORPH_FN(morphEFDTSTLT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFDTSTLT_EVX7");
}

PPC32_MORPH_FN(morphEFSCMPEQ_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCMPEQ_EVX7");
}

PPC32_MORPH_FN(morphEFSCMPGT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCMPGT_EVX7");
}

PPC32_MORPH_FN(morphEFSCMPLT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSCMPLT_EVX7");
}

PPC32_MORPH_FN(morphEFSTSTEQ_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSTSTEQ_EVX7");
}

PPC32_MORPH_FN(morphEFSTSTGT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSTSTGT_EVX7");
}

PPC32_MORPH_FN(morphEFSTSTLT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EFSTSTLT_EVX7");
}

PPC32_MORPH_FN(morphEVCMPEQ_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVCMPEQ_EVX7");
}

PPC32_MORPH_FN(morphEVCMPGTS_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVCMPGTS_EVX7");
}

PPC32_MORPH_FN(morphEVCMPGTU_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVCMPGTU_EVX7");
}

PPC32_MORPH_FN(morphEVCMPLTS_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVCMPLTS_EVX7");
}

PPC32_MORPH_FN(morphEVCMPLTU_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVCMPLTU_EVX7");
}

PPC32_MORPH_FN(morphEVFSCMPEQ_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCMPEQ_EVX7");
}

PPC32_MORPH_FN(morphEVFSCMPGT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCMPGT_EVX7");
}

PPC32_MORPH_FN(morphEVFSCMPLT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSCMPLT_EVX7");
}

PPC32_MORPH_FN(morphEVFSTSTEQ_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSTSTEQ_EVX7");
}

PPC32_MORPH_FN(morphEVFSTSTGT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSTSTGT_EVX7");
}

PPC32_MORPH_FN(morphEVFSTSTLT_EVX7) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVFSTSTLT_EVX7");
}

PPC32_MORPH_FN(morphEVRLWI_EVX8) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVRLWI_EVX8");
}

PPC32_MORPH_FN(morphEVSLWI_EVX8) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVSLWI_EVX8");
}

PPC32_MORPH_FN(morphEVSRWIS_EVX8) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVSRWIS_EVX8");
}

PPC32_MORPH_FN(morphEVSRWIU_EVX8) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVSRWIU_EVX8");
}

PPC32_MORPH_FN(morphEVLHHESPLAT_EVX8_1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVLHHESPLAT_EVX8_1");
}

PPC32_MORPH_FN(morphEVLHHOSSPLAT_EVX8_1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVLHHOSSPLAT_EVX8_1");
}

PPC32_MORPH_FN(morphEVLHHOUSPLAT_EVX8_1) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVLHHOUSPLAT_EVX8_1");
}

PPC32_MORPH_FN(morphEVLWHE_EVX8_2) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVLWHE_EVX8_2");
}

PPC32_MORPH_FN(morphEVLWHOS_EVX8_2) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVLWHOS_EVX8_2");
}

PPC32_MORPH_FN(morphEVLWHOU_EVX8_2) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVLWHOU_EVX8_2");
}

PPC32_MORPH_FN(morphEVLWHSPLAT_EVX8_2) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVLWHSPLAT_EVX8_2");
}

PPC32_MORPH_FN(morphEVLWWSPLAT_EVX8_2) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVLWWSPLAT_EVX8_2");
}

PPC32_MORPH_FN(morphEVLDD_EVX8_3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVLDD_EVX8_3");
}

PPC32_MORPH_FN(morphEVLDH_EVX8_3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVLDH_EVX8_3");
}

PPC32_MORPH_FN(morphEVLDW_EVX8_3) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;
    morphUnimplemented(state, "EVLDW_EVX8_3");
}

PPC32_MORPH_FN(morphEVSPLATFI_EVX9) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Int16 SI = state->info.SI;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVSPLATFI_EVX9");
}

PPC32_MORPH_FN(morphEVSPLATI_EVX9) {
    //
    // Supported Architecture=I_SP
    //
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Int16 SI = state->info.SI;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "EVSPLATI_EVX9");
}

PPC32_MORPH_FN(morphB_I1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 AA = state->info.AA;
    Int32 LI = state->info.LI;
    Uns8 LK = state->info.LK;

    ppc32branch(state->info.thisPC, state->info.nextPC, LI, AA, LK);
}

PPC32_MORPH_FN(morphE_ADD2IRC_I16A1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Int16 SI = state->info.SI;

    ppc32BinopRC(vmi_ADD, GPR_RA, SI, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_ADD2IS_I16A1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Int16 SI = state->info.SI;

    ppc32BinopRC(vmi_ADD, GPR_RA, (SI<<16), 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_CMP16I_I16A1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // Int16 SI = state->info.SI;

    state->info.BF = 0;
    morphCMPI_D5_1(state);
}

PPC32_MORPH_FN(morphE_CMPH16I_I16A1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Int16 SI = state->info.SI;

    ppc32compare(PPC32_GPR_BITS/2, GPR_RA, VMI_NOREG, 0, SI, True, vmi_COND_L);
}

PPC32_MORPH_FN(morphE_MULL2I_I16A1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Int16 SI = state->info.SI;

    ppc32BinopRC(vmi_IMUL, GPR_RA, SI, 0, 0, 0, 0, 0);
}

/*
 * Documentation must be wrong, this instruction is reported as treating the
 * numbers as signed, but the instruction E_CMPH16I already does that
 * ignoring manual and treating as unsigned
 */
PPC32_MORPH_FN(morphE_CMPHL16I_I16A2) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns16 UI = state->info.UI;

    ppc32compare(PPC32_GPR_BITS/2, GPR_RA, VMI_NOREG, 0, UI, True, vmi_COND_B);
}

PPC32_MORPH_FN(morphE_CMPL16I_I16A2) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns16 UI = state->info.UI;

    state->info.BF = 0;
    morphCMPLWI_D6_0(state);
}

PPC32_MORPH_FN(morphE_AND2IRC_I16L) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns16 UI = state->info.UI;

    ppc32BinopRC(vmi_AND, GPR_RT, UI, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_AND2ISRC_I16L) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns16 UI = state->info.UI;

    ppc32BinopRC(vmi_AND, GPR_RT, (UI<<16), 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_LIS_I16L) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns16 UI = state->info.UI;

    state->info.SI = state->info.UI;
    morphLIS_D2_1(state);
}

PPC32_MORPH_FN(morphE_OR2I_I16L) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns16 UI = state->info.UI;

    ppc32BinopRC(vmi_OR, GPR_RT, UI, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_OR2IS_I16L) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns16 UI = state->info.UI;

    ppc32BinopRC(vmi_OR, GPR_RT, (UI<<16), 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_ANDI_IM5) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);
    Uns8 UI5 = state->info.UI5;

    vmimtBinopRC(PPC32_GPR_BITS, vmi_AND, GPR_RX, UI5, 0);
}

PPC32_MORPH_FN(morphSE_BMASKI_IM5) {
    //
    // Supported Architecture=I_VLE
    //
     Uns8 RX = state->info.RX;
     vmiReg GPR_RX = PPC32_GPR_WR(RX);
     Uns8 UI5 = state->info.UI5;

     Uns32 value = 0xFFFFFFFF >> UI5;
     vmimtMoveRC(PPC32_GPR_BITS, GPR_RX, value);
}

PPC32_MORPH_FN(morphSE_CMPI_IM5) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 UI5 = state->info.UI5;

    state->info.BF = 0;
    state->info.RA = state->info.RX;
    state->info.SI = state->info.UI5;
    morphCMPI_D5_1(state);
}

PPC32_MORPH_FN(morphSE_LI_IM7) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 UI7 = state->info.UI7;

    state->info.RT = state->info.RX;
    state->info.SI = state->info.UI7;
    morphLI_D2_1(state);
}

PPC32_MORPH_FN(morphE_LI_LI20) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Int32 li20 = state->info.li20;

    vmimtMoveRC(PPC32_GPR_BITS, GPR_RT, li20);
}

PPC32_MORPH_FN(morphRLWNM_M1_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 MB = state->info.MB;
    Uns8 ME = state->info.ME;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32rlwnm(GPR_RA, GPR_RS, GPR_RB, MB, ME, 0);
}

PPC32_MORPH_FN(morphRLWNMRC_M1_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 MB = state->info.MB;
    Uns8 ME = state->info.ME;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32rlwnm(GPR_RA, GPR_RS, GPR_RB, MB, ME, 1);
}

PPC32_MORPH_FN(morphRLWNMRC_0_M1_1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32rlwnm(GPR_RA, GPR_RS, GPR_RB, 0, 31, 1);
}

PPC32_MORPH_FN(morphRLWNM_0_M1_1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32rlwnm(GPR_RA, GPR_RS, GPR_RB, 0, 31, 0);
}

PPC32_MORPH_FN(morphE_RLWIMI_M2_0) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 MB = state->info.MB;
    // Uns8 ME = state->info.ME;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Uns8 SH = state->info.SH;

    morphRLWIMI_M2_0(state);
}

PPC32_MORPH_FN(morphE_RLWINM_M2_0) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 MB = state->info.MB;
    // Uns8 ME = state->info.ME;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Uns8 SH = state->info.SH;

    morphRLWINM_M2_0(state);
}

PPC32_MORPH_FN(morphRLWIMI_M2_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 MB = state->info.MB;
    Uns8 ME = state->info.ME;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32rlwimi(GPR_RA, GPR_RS, SH, MB, ME, 0);
}

PPC32_MORPH_FN(morphRLWIMIRC_M2_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 MB = state->info.MB;
    Uns8 ME = state->info.ME;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32rlwimi(GPR_RA, GPR_RS, SH, MB, ME, 1);
}

PPC32_MORPH_FN(morphRLWINM_M2_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 MB = state->info.MB;
    Uns8 ME = state->info.ME;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32rlwinm(GPR_RA, GPR_RS, SH, MB, ME, 0);
}

PPC32_MORPH_FN(morphRLWINMRC_M2_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 MB = state->info.MB;
    Uns8 ME = state->info.ME;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32rlwinm(GPR_RA, GPR_RS, SH, MB, ME, 1);
}

PPC32_MORPH_FN(morphRLWINMRC_0_M2_1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32rlwinm(GPR_RA, GPR_RS, SH, 0, 31, 1);
}

PPC32_MORPH_FN(morphRLWINM_0_M2_1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32rlwinm(GPR_RA, GPR_RS, SH, 0, 31, 0);
}

PPC32_MORPH_FN(morphSE_BCLRI_OIM51_0) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 OIM5 = state->info.OIM5;
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);

    Uns32 value = ~(0x1 << (31 - OIM5));
    ppc32BinopRC(vmi_AND, GPR_RX, value, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_BGENI_OIM51_0) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 OIM5 = state->info.OIM5;
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);

    Uns32 value = 0x1 << (31 - OIM5);
    vmimtMoveRC(PPC32_GPR_BITS, GPR_RX, value);
}

PPC32_MORPH_FN(morphSE_BSETI_OIM51_0) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 OIM5 = state->info.OIM5;
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);

    Uns32 value = 0x1 << (31 - OIM5);
    ppc32BinopRC(vmi_OR, GPR_RX, value, 0, 0, 0, 0, 0);
}

static void btsti_vmic(ppc32P ppc32, Uns32 rx, Uns32 value) {
    Uns32 result = ppc32->GPR[rx] & value;

    // CR0 = LT,GT,EQ,SO
    if (result==0) {
        // CR0 = b'0010;
        ppc32->LT[0] = 0;
        ppc32->GT[0] = 0;
        ppc32->EQ[0] = 1;
        ppc32->SO[0] = 0;
    } else {
        // CR0 = b'0010;
        ppc32->LT[0] = 0;
        ppc32->GT[0] = 1;
        ppc32->EQ[0] = 0;
        ppc32->SO[0] = 0;
    }
}

PPC32_MORPH_FN(morphSE_BTSTI_OIM51_0) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 OIM5 = state->info.OIM5;
    Uns8 RX = state->info.RX;
//    vmiReg GPR_RX = PPC32_GPR_RD(RX);

    Uns32 value = 0x1 << (31 - OIM5);

    // Callback
    vmimtArgProcessor();
    vmimtArgUns32(RX);
    vmimtArgUns32(value);
    vmimtCall((vmiCallFn)btsti_vmic);
}

PPC32_MORPH_FN(morphSE_SLWI_OIM51_0) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 OIM5 = state->info.OIM5;
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    state->info.SH = state->info.OIM5;
    morphE_SLWI_X14(state);
}

PPC32_MORPH_FN(morphSE_SRAWI_OIM51_0) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 OIM5 = state->info.OIM5;
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    state->info.SH = state->info.OIM5;
    morphSRAWI_X14(state);
}

PPC32_MORPH_FN(morphSE_SRWI_OIM51_0) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 OIM5 = state->info.OIM5;
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    state->info.SH = state->info.OIM5;
    morphE_SRWI_X14(state);
}

PPC32_MORPH_FN(morphSE_ADDI_OIM51_1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 OIM5 = state->info.OIM5;
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);

    Uns8 OIM5 = state->info.OIM5;
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);

    ppc32BinopRC(vmi_ADD, GPR_RX, OIM5, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_CMPLI_OIM51_1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 OIM5 = state->info.OIM5;
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);

    state->info.BF = 0;
    state->info.RA = state->info.RX;
    state->info.SI = state->info.OIM5;
    morphCMPI_D5_1(state);
}

PPC32_MORPH_FN(morphSE_SUBI_OIM52_0) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 OIM5 = state->info.OIM5;
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);

    ppc32BinopRC(vmi_SUB, GPR_RX, OIM5, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_SUBIRC_OIM52_0) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 OIM5 = state->info.OIM5;
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);

    ppc32BinopRC(vmi_SUB, GPR_RX, OIM5, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_EXTSB_R1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    morphEXTSB_X15(state);
}

PPC32_MORPH_FN(morphSE_EXTSH_R1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    morphEXTSH_X15(state);
}

PPC32_MORPH_FN(morphSE_EXTZB_R1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);

    vmimtMoveExtendRR(PPC32_GPR_BITS, GPR_RX, 8, GPR_RX, 0);
}

PPC32_MORPH_FN(morphSE_EXTZH_R1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);

    vmimtMoveExtendRR(PPC32_GPR_BITS, GPR_RX, 16, GPR_RX, 0);
}

PPC32_MORPH_FN(morphSE_MFCTR_R1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);

    state->info.RT = state->info.RX;
    morphMFCTR_XFX1D(state);
}

PPC32_MORPH_FN(morphSE_MFLR_R1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);

    state->info.RT = state->info.RX;
    morphMFLR_XFX1D(state);
}

PPC32_MORPH_FN(morphSE_MTCTR_R1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);

    state->info.RS = state->info.RX;
    morphMTCTR_XFX10D(state);
}

PPC32_MORPH_FN(morphSE_MTLR_R1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);

    state->info.RS = state->info.RX;
    morphMTLR_XFX10D(state);
}

PPC32_MORPH_FN(morphSE_NEG_R1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);

    vmimtUnopR(PPC32_GPR_BITS, vmi_NEG, GPR_RX, 0);
}

PPC32_MORPH_FN(morphSE_NOT_R1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);

    vmimtUnopR(PPC32_GPR_BITS, vmi_NOT, GPR_RX, 0);
}

PPC32_MORPH_FN(morphSE_ADD_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 RY = state->info.RY;
    // vmiReg GPR_RY = PPC32_GPR_RD(RY);

    state->info.RT = state->info.RX;
    state->info.RA = state->info.RX;
    state->info.RB = state->info.RY;
    morphADD_XO1(state);
}

PPC32_MORPH_FN(morphSE_ANDC_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 RY = state->info.RY;
    // vmiReg GPR_RY = PPC32_GPR_RD(RY);

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    state->info.RB = state->info.RY;
    morphANDC_X9(state);
}

PPC32_MORPH_FN(morphSE_CMP_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 RY = state->info.RY;
    // vmiReg GPR_RY = PPC32_GPR_RD(RY);
    // vmiReg GPR_RY = PPC32_GPR_WR(RY);

    state->info.BF = 0; // CR0
    state->info.RA = state->info.RX;
    state->info.RB = state->info.RY;

    morphCMPW_X22_0(state);
}

PPC32_MORPH_FN(morphSE_CMPH_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_RD(RX);
    Uns8 RY = state->info.RY;
    vmiReg GPR_RY = PPC32_GPR_RD(RY);

    ppc32compare(PPC32_GPR_BITS/2, GPR_RX, GPR_RY, 0, 0, 0, vmi_COND_L);
}

PPC32_MORPH_FN(morphSE_CMPHL_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_RD(RX);
    Uns8 RY = state->info.RY;
    vmiReg GPR_RY = PPC32_GPR_RD(RY);

    ppc32compare(PPC32_GPR_BITS/2, GPR_RX, GPR_RY, 0, 0, 0, vmi_COND_B);
}

PPC32_MORPH_FN(morphSE_CMPL_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 RY = state->info.RY;
    // vmiReg GPR_RY = PPC32_GPR_RD(RY);
    // vmiReg GPR_RY = PPC32_GPR_WR(RY);

    state->info.BF = 0; // CR0
    state->info.RA = state->info.RX;
    state->info.RB = state->info.RY;

    morphCMPLW_X22_0(state);
}

PPC32_MORPH_FN(morphSE_MR_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);
    Uns8 RY = state->info.RY;
    vmiReg GPR_RY = PPC32_GPR_RD(RY);

    vmimtMoveRR(PPC32_GPR_BITS, GPR_RX, GPR_RY);
}

PPC32_MORPH_FN(morphSE_MULLW_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 RY = state->info.RY;
    // vmiReg GPR_RY = PPC32_GPR_RD(RY);
    // vmiReg GPR_RY = PPC32_GPR_WR(RY);

    state->info.RT = state->info.RX;
    state->info.RA = state->info.RX;
    state->info.RB = state->info.RY;
    morphMULLW_XO1(state);
}

PPC32_MORPH_FN(morphSE_OR_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // Uns8 RY = state->info.RY;
    // vmiReg GPR_RY = PPC32_GPR_RD(RY);

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    state->info.RB = state->info.RY;
    morphOR_X9(state);
}

PPC32_MORPH_FN(morphSE_SLW_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 RY = state->info.RY;
    // vmiReg GPR_RY = PPC32_GPR_RD(RY);
    // vmiReg GPR_RY = PPC32_GPR_WR(RY);
    // morphUnimplemented(state, "SE_SLW_RR1");

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    state->info.RB = state->info.RY;
    morphSLW_X9(state);
}

PPC32_MORPH_FN(morphSE_SRAW_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 RY = state->info.RY;
    // vmiReg GPR_RY = PPC32_GPR_RD(RY);
    // vmiReg GPR_RY = PPC32_GPR_WR(RY);

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    state->info.RB = state->info.RY;

    morphSRAW_X9(state);
}

PPC32_MORPH_FN(morphSE_SRW_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_RD(RX);
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 RY = state->info.RY;
    // vmiReg GPR_RY = PPC32_GPR_RD(RY);
    // vmiReg GPR_RY = PPC32_GPR_WR(RY);

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    state->info.RB = state->info.RY;
    morphSRW_X9(state);
}

PPC32_MORPH_FN(morphSE_SUB_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);
    Uns8 RY = state->info.RY;
    vmiReg GPR_RY = PPC32_GPR_RD(RY);

    // RX = RX - RY
    ppc32BinopRR(vmi_SUB, GPR_RX, GPR_RY, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_SUBF_RR1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);
    Uns8 RY = state->info.RY;
    vmiReg GPR_RY = PPC32_GPR_RD(RY);

    // RX = RY - RX
    ppc32BinopRR(vmi_RSUB, GPR_RX, GPR_RY, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_AND_RR2) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 RY = state->info.RY;
    // vmiReg GPR_RY = PPC32_GPR_RD(RY);

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    state->info.RB = state->info.RY;
    morphAND_X9(state);
}

PPC32_MORPH_FN(morphSE_ANDRC_RR2) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 RX = state->info.RX;
    // vmiReg GPR_RX = PPC32_GPR_WR(RX);
    // Uns8 RY = state->info.RY;
    // vmiReg GPR_RY = PPC32_GPR_RD(RY);

    state->info.RA = state->info.RX;
    state->info.RS = state->info.RX;
    state->info.RB = state->info.RY;
    morphANDRC_X9(state);
}

PPC32_MORPH_FN(morphSE_MFAR_RR3) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 ARY = state->info.ARY;
    vmiReg GPR_ARY = PPC32_GPR_RD(ARY);
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_WR(RX);

    vmimtMoveRR(PPC32_GPR_BITS, GPR_RX, GPR_ARY);
}

PPC32_MORPH_FN(morphSE_MTAR_RR4) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 ARX = state->info.ARX;
    vmiReg GPR_ARX = PPC32_GPR_WR(ARX);
    Uns8 RY = state->info.RY;
    vmiReg GPR_RY = PPC32_GPR_RD(RY);

    vmimtMoveRR(PPC32_GPR_BITS, GPR_ARX, GPR_RY);
}

//
// system call is the same as an exception
//
static void vmic_sc(ppc32P ppc32, Uns32 lev) {
    vmiProcessorP processor = (vmiProcessorP)ppc32;

    if (lev) {
        vmiMessage("F", "SYSCALL", "LEV=%d Nonzero unsupported\n", lev);
    }

    ppc32ProcessException(processor, vmirtGetPC(processor), EXC_SYSTEM_CALL);
}

PPC32_MORPH_FN(morphSC_SC1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 LEV = state->info.LEV;

    vmimtArgProcessor();
    vmimtArgUns32(LEV);
    vmimtCall((vmiCallFn)vmic_sc);
}

static Int32 genScaled8(Uns8 F, Uns8 SCL, Uns8 U8) {

    Int32 sci8 = 0;
    if (F==1) {
        //
        // Default 1's
        //
        sci8 = ~0;
        switch (SCL) {
        case 0:
            sci8 = 0xFFFFFF00;
            break;
        case 1:
            sci8 = 0xFFFF00FF;
            break;
        case 2:
            sci8 = 0xFF00FFFF;
            break;
        case 3:
            sci8 = 0x00FFFFFF;
            break;
        }
    }

    sci8 |= ((U8 & 0xFF) << (SCL * 8));

    return sci8;
}

PPC32_MORPH_FN(morphE_ADDI_SCI8_1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_ADD, GPR_RT, GPR_RA, sci8, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_ADDIC_SCI8_1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_ADD, GPR_RT, GPR_RA, sci8, 0, 0, 1, 0, 0);
}

PPC32_MORPH_FN(morphE_ADDICRC_SCI8_1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_ADD, GPR_RT, GPR_RA, sci8, 0, 1, 1, 0, 0);
}

PPC32_MORPH_FN(morphE_ADDIRC_SCI8_1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_ADD, GPR_RT, GPR_RA, sci8, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_SUBFIC_SCI8_1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_RSUB, GPR_RT, GPR_RA, sci8, 0, 0, 1, 0, 1);
}

PPC32_MORPH_FN(morphE_SUBFICRC_SCI8_1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_RSUB, GPR_RT, GPR_RA, sci8, 0, 1, 1, 0, 1);
}

PPC32_MORPH_FN(morphE_MULLI_SCI8_2) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_IMUL, GPR_RT, GPR_RA, sci8, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_ANDI_SCI8_3) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_AND, GPR_RA, GPR_RS, sci8, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_ANDIRC_SCI8_3) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_AND, GPR_RA, GPR_RS, sci8, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_ORI_SCI8_3) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_OR, GPR_RA, GPR_RS, sci8, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_ORIRC_SCI8_3) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_OR, GPR_RA, GPR_RS, sci8, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_XORI_SCI8_3) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_XOR, GPR_RA, GPR_RS, sci8, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_XORIRC_SCI8_3) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SCL = state->info.SCL;
    Uns8 U8 = state->info.U8;

    Int32 sci8 = genScaled8(F, SCL, U8);
    ppc32BinopRRC(vmi_XOR, GPR_RA, GPR_RS, sci8, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_CMPI_SCI8_5) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 BF32 = state->info.BF32;
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Int8 S8 = state->info.S8;
    Uns8 SCL = state->info.SCL;

    Int32 sci8  = genScaled8(F, SCL, S8);
    ppc32compare(PPC32_GPR_BITS, GPR_RA, VMI_NOREG, BF32, sci8, 1, vmi_COND_L);
}

PPC32_MORPH_FN(morphE_CMPLI_SCI8_6) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 BF32 = state->info.BF32;
    Uns8 F = state->info.F;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Int8 S8 = state->info.S8;
    Uns8 SCL = state->info.SCL;

    Int32 sci8  = genScaled8(F, SCL, S8);
    ppc32compare(PPC32_GPR_BITS, GPR_RA, VMI_NOREG, BF32, sci8, 1, vmi_COND_B);
}


PPC32_MORPH_FN(morphSE_LBZ_SD4_0) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_RD(RX);
    Uns8 RZ = state->info.RZ;
    vmiReg GPR_RZ = PPC32_GPR_WR(RZ);
    Uns8 SD4 = state->info.SD4;

    ppc32loadGPR_se(GPR_RZ, GPR_RX, VMI_NOREG, state, SD4, 8, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_STB_SD4_0) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_RD(RX);
    Uns8 RZ = state->info.RZ;
    vmiReg GPR_RZ = PPC32_GPR_RD(RZ);
    Uns8 SD4 = state->info.SD4;

    ppc32StoreGPR_se(GPR_RZ, GPR_RX, VMI_NOREG, state, SD4, 8, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_LHZ_SD4_1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_RD(RX);
    Uns8 RZ = state->info.RZ;
    vmiReg GPR_RZ = PPC32_GPR_WR(RZ);
    Uns8 SD4 = state->info.SD4;

    ppc32loadGPR_se(GPR_RZ, GPR_RX, VMI_NOREG, state, SD4, 16, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_STH_SD4_1) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_RD(RX);
    Uns8 RZ = state->info.RZ;
    vmiReg GPR_RZ = PPC32_GPR_RD(RZ);
    Uns8 SD4 = state->info.SD4;

    ppc32StoreGPR_se(GPR_RZ, GPR_RX, VMI_NOREG, state, SD4, 16, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_LWZ_SD4_2) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_RD(RX);
    Uns8 RZ = state->info.RZ;
    vmiReg GPR_RZ = PPC32_GPR_WR(RZ);
    Uns8 SD4 = state->info.SD4;

    ppc32loadGPR_se(GPR_RZ, GPR_RX, VMI_NOREG, state, SD4, 32, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSE_STW_SD4_2) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RX = state->info.RX;
    vmiReg GPR_RX = PPC32_GPR_RD(RX);
    Uns8 RZ = state->info.RZ;
    vmiReg GPR_RZ = PPC32_GPR_RD(RZ);
    Uns8 SD4 = state->info.SD4;

    ppc32StoreGPR_se(GPR_RZ, GPR_RX, VMI_NOREG, state, SD4, 32, 0, 0, 0);
}

PPC32_MORPH_FN(morphVMHADDSHS_VA1_0) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMHADDSHS_VA1_0");
}

PPC32_MORPH_FN(morphVMHRADDSHS_VA1_0) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMHRADDSHS_VA1_0");
}

PPC32_MORPH_FN(morphVMLADDUHM_VA1_0) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMLADDUHM_VA1_0");
}

PPC32_MORPH_FN(morphVMSUMMBM_VA1_0) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMSUMMBM_VA1_0");
}

PPC32_MORPH_FN(morphVMSUMSHM_VA1_0) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMSUMSHM_VA1_0");
}

PPC32_MORPH_FN(morphVMSUMSHS_VA1_0) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMSUMSHS_VA1_0");
}

PPC32_MORPH_FN(morphVMSUMUBM_VA1_0) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMSUMUBM_VA1_0");
}

PPC32_MORPH_FN(morphVMSUMUHM_VA1_0) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMSUMUHM_VA1_0");
}

PPC32_MORPH_FN(morphVMSUMUHS_VA1_0) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMSUMUHS_VA1_0");
}

PPC32_MORPH_FN(morphVPERM_VA1_0) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VPERM_VA1_0");
}

PPC32_MORPH_FN(morphVSEL_VA1_0) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSEL_VA1_0");
}

PPC32_MORPH_FN(morphVMADDFP_VA1_1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMADDFP_VA1_1");
}

PPC32_MORPH_FN(morphVMSUBFP_VA1_1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRC = state->info.VRC;
    // vmiReg VR_VRC = PPC32_VR_RD(VRC);
    // vmiReg VR_VRC = PPC32_VR_WR(VRC);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMSUBFP_VA1_1");
}

PPC32_MORPH_FN(morphVSLDOI_VA2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 SHB = state->info.SHB;
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VSLDOI_VA2");
}

PPC32_MORPH_FN(morphVCMPBFP_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPBFP_VC1");
}

PPC32_MORPH_FN(morphVCMPBFPRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPBFPRC_VC1");
}

PPC32_MORPH_FN(morphVCMPEQFP_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPEQFP_VC1");
}

PPC32_MORPH_FN(morphVCMPEQFPRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPEQFPRC_VC1");
}

PPC32_MORPH_FN(morphVCMPEQUB_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPEQUB_VC1");
}

PPC32_MORPH_FN(morphVCMPEQUBRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPEQUBRC_VC1");
}

PPC32_MORPH_FN(morphVCMPEQUH_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPEQUH_VC1");
}

PPC32_MORPH_FN(morphVCMPEQUHRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPEQUHRC_VC1");
}

PPC32_MORPH_FN(morphVCMPEQUW_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPEQUW_VC1");
}

PPC32_MORPH_FN(morphVCMPEQUWRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPEQUWRC_VC1");
}

PPC32_MORPH_FN(morphVCMPGEFP_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGEFP_VC1");
}

PPC32_MORPH_FN(morphVCMPGEFPRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGEFPRC_VC1");
}

PPC32_MORPH_FN(morphVCMPGTFP_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTFP_VC1");
}

PPC32_MORPH_FN(morphVCMPGTFPRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTFPRC_VC1");
}

PPC32_MORPH_FN(morphVCMPGTSB_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTSB_VC1");
}

PPC32_MORPH_FN(morphVCMPGTSBRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTSBRC_VC1");
}

PPC32_MORPH_FN(morphVCMPGTSH_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTSH_VC1");
}

PPC32_MORPH_FN(morphVCMPGTSHRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTSHRC_VC1");
}

PPC32_MORPH_FN(morphVCMPGTSW_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTSW_VC1");
}

PPC32_MORPH_FN(morphVCMPGTSWRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTSWRC_VC1");
}

PPC32_MORPH_FN(morphVCMPGTUB_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTUB_VC1");
}

PPC32_MORPH_FN(morphVCMPGTUBRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTUBRC_VC1");
}

PPC32_MORPH_FN(morphVCMPGTUH_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTUH_VC1");
}

PPC32_MORPH_FN(morphVCMPGTUHRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTUHRC_VC1");
}

PPC32_MORPH_FN(morphVCMPGTUW_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTUW_VC1");
}

PPC32_MORPH_FN(morphVCMPGTUWRC_VC1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCMPGTUWRC_VC1");
}

PPC32_MORPH_FN(morphVADDCUW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VADDCUW_VX1");
}

PPC32_MORPH_FN(morphVADDFP_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VADDFP_VX1");
}

PPC32_MORPH_FN(morphVADDSBS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VADDSBS_VX1");
}

PPC32_MORPH_FN(morphVADDSHS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VADDSHS_VX1");
}

PPC32_MORPH_FN(morphVADDSWS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VADDSWS_VX1");
}

PPC32_MORPH_FN(morphVADDUBM_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VADDUBM_VX1");
}

PPC32_MORPH_FN(morphVADDUBS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VADDUBS_VX1");
}

PPC32_MORPH_FN(morphVADDUHM_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VADDUHM_VX1");
}

PPC32_MORPH_FN(morphVADDUHS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VADDUHS_VX1");
}

PPC32_MORPH_FN(morphVADDUWM_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VADDUWM_VX1");
}

PPC32_MORPH_FN(morphVADDUWS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VADDUWS_VX1");
}

PPC32_MORPH_FN(morphVAND_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VAND_VX1");
}

PPC32_MORPH_FN(morphVANDC_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VANDC_VX1");
}

PPC32_MORPH_FN(morphVAVGSB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VAVGSB_VX1");
}

PPC32_MORPH_FN(morphVAVGSH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VAVGSH_VX1");
}

PPC32_MORPH_FN(morphVAVGSW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VAVGSW_VX1");
}

PPC32_MORPH_FN(morphVAVGUB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VAVGUB_VX1");
}

PPC32_MORPH_FN(morphVAVGUH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VAVGUH_VX1");
}

PPC32_MORPH_FN(morphVAVGUW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VAVGUW_VX1");
}

PPC32_MORPH_FN(morphVKPPX_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VKPPX_VX1");
}

PPC32_MORPH_FN(morphVKPSHSS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VKPSHSS_VX1");
}

PPC32_MORPH_FN(morphVKPSHUS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VKPSHUS_VX1");
}

PPC32_MORPH_FN(morphVKPSWSS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VKPSWSS_VX1");
}

PPC32_MORPH_FN(morphVKPSWUS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VKPSWUS_VX1");
}

PPC32_MORPH_FN(morphVKPUHUM_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VKPUHUM_VX1");
}

PPC32_MORPH_FN(morphVKPUHUS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VKPUHUS_VX1");
}

PPC32_MORPH_FN(morphVKPUWUM_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VKPUWUM_VX1");
}

PPC32_MORPH_FN(morphVKPUWUS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VKPUWUS_VX1");
}

PPC32_MORPH_FN(morphVMAXFP_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMAXFP_VX1");
}

PPC32_MORPH_FN(morphVMAXSB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMAXSB_VX1");
}

PPC32_MORPH_FN(morphVMAXSH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMAXSH_VX1");
}

PPC32_MORPH_FN(morphVMAXSW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMAXSW_VX1");
}

PPC32_MORPH_FN(morphVMAXUB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMAXUB_VX1");
}

PPC32_MORPH_FN(morphVMAXUH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMAXUH_VX1");
}

PPC32_MORPH_FN(morphVMAXUW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMAXUW_VX1");
}

PPC32_MORPH_FN(morphVMINFP_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMINFP_VX1");
}

PPC32_MORPH_FN(morphVMINSB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMINSB_VX1");
}

PPC32_MORPH_FN(morphVMINSH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMINSH_VX1");
}

PPC32_MORPH_FN(morphVMINSW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMINSW_VX1");
}

PPC32_MORPH_FN(morphVMINUB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMINUB_VX1");
}

PPC32_MORPH_FN(morphVMINUH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMINUH_VX1");
}

PPC32_MORPH_FN(morphVMINUW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMINUW_VX1");
}

PPC32_MORPH_FN(morphVMRGHB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMRGHB_VX1");
}

PPC32_MORPH_FN(morphVMRGHH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMRGHH_VX1");
}

PPC32_MORPH_FN(morphVMRGHW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMRGHW_VX1");
}

PPC32_MORPH_FN(morphVMRGLB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMRGLB_VX1");
}

PPC32_MORPH_FN(morphVMRGLH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMRGLH_VX1");
}

PPC32_MORPH_FN(morphVMRGLW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMRGLW_VX1");
}

PPC32_MORPH_FN(morphVMULESB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMULESB_VX1");
}

PPC32_MORPH_FN(morphVMULESH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMULESH_VX1");
}

PPC32_MORPH_FN(morphVMULEUB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMULEUB_VX1");
}

PPC32_MORPH_FN(morphVMULEUH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMULEUH_VX1");
}

PPC32_MORPH_FN(morphVMULOSB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMULOSB_VX1");
}

PPC32_MORPH_FN(morphVMULOSH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMULOSH_VX1");
}

PPC32_MORPH_FN(morphVMULOUB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMULOUB_VX1");
}

PPC32_MORPH_FN(morphVMULOUH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VMULOUH_VX1");
}

PPC32_MORPH_FN(morphVNOR_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VNOR_VX1");
}

PPC32_MORPH_FN(morphVOR_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VOR_VX1");
}

PPC32_MORPH_FN(morphVRLB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VRLB_VX1");
}

PPC32_MORPH_FN(morphVRLH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VRLH_VX1");
}

PPC32_MORPH_FN(morphVRLW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VRLW_VX1");
}

PPC32_MORPH_FN(morphVSL_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSL_VX1");
}

PPC32_MORPH_FN(morphVSLB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSLB_VX1");
}

PPC32_MORPH_FN(morphVSLH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSLH_VX1");
}

PPC32_MORPH_FN(morphVSLO_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSLO_VX1");
}

PPC32_MORPH_FN(morphVSLW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSLW_VX1");
}

PPC32_MORPH_FN(morphVSR_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSR_VX1");
}

PPC32_MORPH_FN(morphVSRAB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSRAB_VX1");
}

PPC32_MORPH_FN(morphVSRAH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSRAH_VX1");
}

PPC32_MORPH_FN(morphVSRAW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSRAW_VX1");
}

PPC32_MORPH_FN(morphVSRB_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSRB_VX1");
}

PPC32_MORPH_FN(morphVSRH_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSRH_VX1");
}

PPC32_MORPH_FN(morphVSRO_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSRO_VX1");
}

PPC32_MORPH_FN(morphVSRW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSRW_VX1");
}

PPC32_MORPH_FN(morphVSUBCUW_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUBCUW_VX1");
}

PPC32_MORPH_FN(morphVSUBFP_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUBFP_VX1");
}

PPC32_MORPH_FN(morphVSUBSBS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUBSBS_VX1");
}

PPC32_MORPH_FN(morphVSUBSHS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUBSHS_VX1");
}

PPC32_MORPH_FN(morphVSUBSWS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUBSWS_VX1");
}

PPC32_MORPH_FN(morphVSUBUBM_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUBUBM_VX1");
}

PPC32_MORPH_FN(morphVSUBUBS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUBUBS_VX1");
}

PPC32_MORPH_FN(morphVSUBUHM_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUBUHM_VX1");
}

PPC32_MORPH_FN(morphVSUBUHS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUBUHS_VX1");
}

PPC32_MORPH_FN(morphVSUBUWM_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUBUWM_VX1");
}

PPC32_MORPH_FN(morphVSUBUWS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUBUWS_VX1");
}

PPC32_MORPH_FN(morphVSUM2SWS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUM2SWS_VX1");
}

PPC32_MORPH_FN(morphVSUM4SBS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUM4SBS_VX1");
}

PPC32_MORPH_FN(morphVSUM4SHS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUM4SHS_VX1");
}

PPC32_MORPH_FN(morphVSUM4UBS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUM4UBS_VX1");
}

PPC32_MORPH_FN(morphVSUMSWS_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VSUMSWS_VX1");
}

PPC32_MORPH_FN(morphVXOR_VX1) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRA = state->info.VRA;
    // vmiReg VR_VRA = PPC32_VR_RD(VRA);
    // vmiReg VR_VRA = PPC32_VR_WR(VRA);
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VXOR_VX1");
}

PPC32_MORPH_FN(morphVEXPTEFP_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VEXPTEFP_VX2");
}

PPC32_MORPH_FN(morphVLOGEFP_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VLOGEFP_VX2");
}

PPC32_MORPH_FN(morphVREFP_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VREFP_VX2");
}

PPC32_MORPH_FN(morphVRFIM_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VRFIM_VX2");
}

PPC32_MORPH_FN(morphVRFIN_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VRFIN_VX2");
}

PPC32_MORPH_FN(morphVRFIP_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VRFIP_VX2");
}

PPC32_MORPH_FN(morphVRFIZ_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VRFIZ_VX2");
}

PPC32_MORPH_FN(morphVRSQRTEFP_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VRSQRTEFP_VX2");
}

PPC32_MORPH_FN(morphVUPKHPX_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VUPKHPX_VX2");
}

PPC32_MORPH_FN(morphVUPKHSB_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VUPKHSB_VX2");
}

PPC32_MORPH_FN(morphVUPKHSH_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VUPKHSH_VX2");
}

PPC32_MORPH_FN(morphVUPKLPX_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VUPKLPX_VX2");
}

PPC32_MORPH_FN(morphVUPKLSB_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VUPKLSB_VX2");
}

PPC32_MORPH_FN(morphVUPKLSH_VX2) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VUPKLSH_VX2");
}

PPC32_MORPH_FN(morphVCFSX_VX3) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 UIM = state->info.UIM;
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCFSX_VX3");
}

PPC32_MORPH_FN(morphVCFUX_VX3) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 UIM = state->info.UIM;
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCFUX_VX3");
}

PPC32_MORPH_FN(morphVCTSXS_VX3) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 UIM = state->info.UIM;
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCTSXS_VX3");
}

PPC32_MORPH_FN(morphVCTUXS_VX3) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 UIM = state->info.UIM;
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    morphUnimplemented(state, "VCTUXS_VX3");
}

PPC32_MORPH_FN(morphVSPLTB_VX4) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 UIM = state->info.UIM;
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VSPLTB_VX4");
}

PPC32_MORPH_FN(morphVSPLTH_VX5) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 UIM = state->info.UIM;
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VSPLTH_VX5");
}

PPC32_MORPH_FN(morphVSPLTW_VX6) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 UIM = state->info.UIM;
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VSPLTW_VX6");
}

PPC32_MORPH_FN(morphVSPLTISB_VX7) {
    //
    // Supported Architecture=I_V
    //
    // Int8 SIM = state->info.SIM;
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VSPLTISB_VX7");
}

PPC32_MORPH_FN(morphVSPLTISH_VX7) {
    //
    // Supported Architecture=I_V
    //
    // Int8 SIM = state->info.SIM;
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VSPLTISH_VX7");
}

PPC32_MORPH_FN(morphVSPLTISW_VX7) {
    //
    // Supported Architecture=I_V
    //
    // Int8 SIM = state->info.SIM;
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "VSPLTISW_VX7");
}

PPC32_MORPH_FN(morphMFVSCR_VX8) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "MFVSCR_VX8");
}

PPC32_MORPH_FN(morphMTVSCR_VX9) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 VRB = state->info.VRB;
    // vmiReg VR_VRB = PPC32_VR_RD(VRB);
    // vmiReg VR_VRB = PPC32_VR_WR(VRB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "MTVSCR_VX9");
}

PPC32_MORPH_FN(morphMFAPIDI_X1) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "MFAPIDI_X1");
}

PPC32_MORPH_FN(morphMFDCRUX_X1) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "MFDCRUX_X1");
}

PPC32_MORPH_FN(morphMFDCRX_X1) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "MFDCRX_X1");
}

PPC32_MORPH_FN(morphMULCHW_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mulc(GPR_RT, GPR_RA, GPR_RB, 0, 1);
}

PPC32_MORPH_FN(morphMULCHWRC_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mulc(GPR_RT, GPR_RA, GPR_RB, 1, 1);
}

PPC32_MORPH_FN(morphMULCHWU_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mulc(GPR_RT, GPR_RA, GPR_RB, 0, 0);
}

PPC32_MORPH_FN(morphMULCHWURC_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mulc(GPR_RT, GPR_RA, GPR_RB, 1, 0);
}

PPC32_MORPH_FN(morphMULHHW_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mulh(GPR_RT, GPR_RA, GPR_RB, 0, 1);
}

PPC32_MORPH_FN(morphMULHHWRC_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mulh(GPR_RT, GPR_RA, GPR_RB, 1, 1);
}

PPC32_MORPH_FN(morphMULHHWU_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mulh(GPR_RT, GPR_RA, GPR_RB, 0, 0);
}

PPC32_MORPH_FN(morphMULHHWURC_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mulh(GPR_RT, GPR_RA, GPR_RB, 1, 0);
}

PPC32_MORPH_FN(morphMULLHW_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mull(GPR_RT, GPR_RA, GPR_RB, 0, 1);
}

PPC32_MORPH_FN(morphMULLHWRC_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mull(GPR_RT, GPR_RA, GPR_RB, 1, 1);
}

PPC32_MORPH_FN(morphMULLHWU_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mull(GPR_RT, GPR_RA, GPR_RB, 0, 0);
}

PPC32_MORPH_FN(morphMULLHWURC_X10) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mull(GPR_RT, GPR_RA, GPR_RB, 1, 0);
}

PPC32_MORPH_FN(morphSTWCXRC_X11) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    Uns8 RB = state->info.RB;
    Uns8 RS = state->info.RS;

    ppc32storeConditional(state, RS, RA, RB, 4);
}

PPC32_MORPH_FN(morphCMPB_X12) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "CMPB_X12");
}

PPC32_MORPH_FN(morphSTBCIX_X12) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "STBCIX_X12");
}

PPC32_MORPH_FN(morphSTBEPX_X12) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "STBEPX_X12");
}

PPC32_MORPH_FN(morphSTBUX_X12) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, GPR_RB, state, 0, 8, 0, 1, 0);
}

PPC32_MORPH_FN(morphSTBX_X12) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, GPR_RB, state, 0, 8, 0, 0, 0);
}

PPC32_MORPH_FN(morphSTDCIX_X12) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "STDCIX_X12");
}

PPC32_MORPH_FN(morphSTDEPX_X12) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "STDEPX_X12");
}

PPC32_MORPH_FN(morphSTHBRX_X12) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, GPR_RB, state, 0, 16, 0, 0, 1);
}

PPC32_MORPH_FN(morphSTHCIX_X12) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "STHCIX_X12");
}

PPC32_MORPH_FN(morphSTHEPX_X12) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "STHEPX_X12");
}

PPC32_MORPH_FN(morphSTHUX_X12) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, GPR_RB, state, 0, 16, 0, 1, 0);
}

PPC32_MORPH_FN(morphSTHX_X12) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, GPR_RB, state, 0, 16, 0, 0, 0);
}

PPC32_MORPH_FN(morphSTSWX_X12) {
    //
    // Supported Architecture=I_MA
    //
    Uns8 RA = state->info.RA;
    Uns8 RB = state->info.RB;
    Uns8 RS = state->info.RS;

    ppc32storeString(RS, RA, RB, 0, 1);
}

PPC32_MORPH_FN(morphSTWBRX_X12) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, GPR_RB, state, 0, 32, 0, 0, 1);
}

PPC32_MORPH_FN(morphSTWCIX_X12) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "STWCIX_X12");
}

PPC32_MORPH_FN(morphSTWEPX_X12) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "STWEPX_X12");
}

PPC32_MORPH_FN(morphSTWUX_X12) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    // morphUnimplemented(state, "STWUX_X12");

    ppc32StoreGPR(GPR_RS, GPR_RA, GPR_RB, state, 0, 32, 0, 1, 0);
}

PPC32_MORPH_FN(morphSTWX_X12) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32StoreGPR(GPR_RS, GPR_RA, GPR_RB, state, 0, 32, 0, 0, 0);
}

PPC32_MORPH_FN(morphSTSWI_X13) {
    //
    // Supported Architecture=I_MA
    //
    Uns8 NB = state->info.NB;
    Uns8 RA = state->info.RA;
    Uns8 RS = state->info.RS;

    ppc32storeString(RS, RA, 0, NB, 0);
}

PPC32_MORPH_FN(morphE_RLWI_X14) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32BinopRRC(vmi_ROL, GPR_RA, GPR_RS, SH, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_RLWIRC_X14) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32BinopRRC(vmi_ROL, GPR_RA, GPR_RS, SH, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_SLWI_X14) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32BinopRRC(vmi_SHL, GPR_RA, GPR_RS, SH, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_SLWIRC_X14) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32BinopRRC(vmi_SHL, GPR_RA, GPR_RS, SH, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_SRWI_X14) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32BinopRRC(vmi_SHR, GPR_RA, GPR_RS, SH, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_SRWIRC_X14) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32BinopRRC(vmi_SHR, GPR_RA, GPR_RS, SH, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphSRAWI_X14) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32srawi(GPR_RS, GPR_RA, SH, 0);
}

PPC32_MORPH_FN(morphSRAWIRC_X14) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns8 SH = state->info.SH;

    ppc32srawi(GPR_RS, GPR_RA, SH, 1);
}

PPC32_MORPH_FN(morphCNTLZW_X15) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32UnopRR(vmi_CLZ, GPR_RA, GPR_RS, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphCNTLZWRC_X15) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32UnopRR(vmi_CLZ, GPR_RA, GPR_RS, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphEXTSB_X15) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32Extend(GPR_RA, GPR_RS, 8, 1, 0);
}

PPC32_MORPH_FN(morphEXTSBRC_X15) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32Extend(GPR_RA, GPR_RS, 8, 1, 1);
}

PPC32_MORPH_FN(morphEXTSH_X15) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32Extend(GPR_RA, GPR_RS, 16, 1, 0);
}

PPC32_MORPH_FN(morphEXTSHRC_X15) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32Extend(GPR_RA, GPR_RS, 16, 1, 1);
}

PPC32_MORPH_FN(morphCBCDTD_X16) {
    //
    // Supported Architecture=I_BCDA
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "CBCDTD_X16");
}

PPC32_MORPH_FN(morphCDTBCD_X16) {
    //
    // Supported Architecture=I_BCDA
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "CDTBCD_X16");
}

PPC32_MORPH_FN(morphMTDCRUX_X16) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "MTDCRUX_X16");
}

PPC32_MORPH_FN(morphMTDCRX_X16) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "MTDCRX_X16");
}

static void popcntb_vmic(ppc32P ppc32, Uns32 ra, Uns32 value) {
    Int8 byteI, bitI;
    Uns32 v = value;
    Uns32 r = 0;
    for(byteI=0; byteI<=4; byteI++) {
        Uns8 cnt = 0;
        for(bitI=0; bitI<=7; bitI++) {
            if (v & 0x1) {
                cnt++;
            }
            v >>= 1;
        }
        r |= (cnt << (8*byteI));
    }
    ppc32->GPR[ra] = r;
}

PPC32_MORPH_FN(morphPOPCNTB_X16) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    // Count bytes into RA
    vmimtArgProcessor();
    vmimtArgUns32(RA);
    vmimtArgReg(PPC32_GPR_BITS, GPR_RS);
    vmimtCall((vmiCallFn)popcntb_vmic);
}

static void prtyw_vmic(ppc32P ppc32, Uns32 ra, Uns32 value) {

    //
    // Xor the 4 bytes of value and use bottom bit
    //
    Uns8 parity =
            ((value>>24) & 0xff) ^
            ((value>>16) & 0xff) ^
            ((value>> 8) & 0xff) ^
            ((value>> 0) & 0xff);

    parity &= 0x1;

    ppc32->GPR[ra] = parity;
}

PPC32_MORPH_FN(morphPRTYW_X16) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    // Parity generation
    vmimtArgProcessor();
    vmimtArgUns32(RA);
    vmimtArgReg(PPC32_GPR_BITS, GPR_RS);
    vmimtCall((vmiCallFn)prtyw_vmic);
}

PPC32_MORPH_FN(morphMTSR_X17) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Uns8 SR = state->info.SR;
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "MTSR_X17");
}

PPC32_MORPH_FN(morphMTSRIN_X18) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "MTSRIN_X18");
}

PPC32_MORPH_FN(morphSLBMTE_X18) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);
    morphUnimplemented(state, "SLBMTE_X18");
}

PPC32_MORPH_FN(morphMTMSR_X19_0) {
    //
    // Supported Architecture=I_E
    //
    CHECK_PRIV(state);

    Uns8 L = state->info.L;
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32mtmsr(state->ppc32, L, GPR_RS, RS);
}

PPC32_MORPH_FN(morphWRTEE_X19_1) {
    //
    // Supported Architecture=I_E
    //
    CHECK_PRIV(state);

    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32wrtee(state->ppc32, GPR_RS, RS);
}

PPC32_MORPH_FN(morphDCREAD_X2) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCREAD_X2");
}

PPC32_MORPH_FN(morphECIWX_X2) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "ECIWX_X2");
}

PPC32_MORPH_FN(morphECOWX_X2) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "ECOWX_X2");
}

PPC32_MORPH_FN(morphLBEPX_X2) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "LBEPX_X2");
}

PPC32_MORPH_FN(morphLBZCIX_X2) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "LBZCIX_X2");
}

PPC32_MORPH_FN(morphLBZUX_X2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_RD(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, GPR_RB, state, 0, 8, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphLBZX_X2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, GPR_RB, state, 0, 8, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphLDCIX_X2) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "LDCIX_X2");
}

PPC32_MORPH_FN(morphLDEPX_X2) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "LDEPX_X2");
}

PPC32_MORPH_FN(morphLHAUX_X2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, GPR_RB, state, 0, 16, 1, 0, 1, 0);
}

PPC32_MORPH_FN(morphLHAX_X2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, GPR_RB, state, 0, 16, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphLHBRX_X2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, GPR_RB, state, 0, 16, 0, 0, 0, 1);
}

PPC32_MORPH_FN(morphLHEPX_X2) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "LHEPX_X2");
}

PPC32_MORPH_FN(morphLHZCIX_X2) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "LHZCIX_X2");
}

PPC32_MORPH_FN(morphLHZUX_X2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, GPR_RB, state, 0, 16, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphLHZX_X2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, GPR_RB, state, 0, 16, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphLSWX_X2) {
    //
    // Supported Architecture=I_MA
    //
    Uns8 RA = state->info.RA;
    Uns8 RB = state->info.RB;
    Uns8 RT = state->info.RT;

    ppc32loadString(RT, RA, RB, 0, 1);
}

PPC32_MORPH_FN(morphLWBRX_X2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, GPR_RB, state, 0, 32, 0, 0, 0, 1);
}

PPC32_MORPH_FN(morphLWEPX_X2) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "LWEPX_X2");
}

PPC32_MORPH_FN(morphLWZCIX_X2) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "LWZCIX_X2");
}

PPC32_MORPH_FN(morphLWZUX_X2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, GPR_RB, state, 0, 32, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphLWZX_X2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32loadGPR(GPR_RT, GPR_RA, GPR_RB, state, 0, 32, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphMTMSRD_X20) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 L = state->info.L;
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);
    morphUnimplemented(state, "MTMSRD_X20");
}

PPC32_MORPH_FN(morphCMPLW_X22_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BF = state->info.BF;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32compare(PPC32_GPR_BITS, GPR_RA, GPR_RB, BF, 0, 0, vmi_COND_B);
}

PPC32_MORPH_FN(morphCMPW_X22_0) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BF = state->info.BF;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32compare(PPC32_GPR_BITS, GPR_RA, GPR_RB, BF, 0, 0, vmi_COND_L);
}

//
// This instruction is actually illegal in 32 bit mode
// But behaves like morphCMPW_X22_0
//
PPC32_MORPH_FN(morphCMP_X22_1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BF = state->info.BF;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32compare(PPC32_GPR_BITS, GPR_RA, GPR_RB, BF, 0, 0, vmi_COND_L);
}

PPC32_MORPH_FN(morphCMPL_X22_1) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 BF = state->info.BF;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "CMPL_X22_1");
}

PPC32_MORPH_FN(morphE_CMPH_X22_2) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 BF = state->info.BF;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32compare(PPC32_GPR_BITS/2, GPR_RA, GPR_RB, BF, 0, 0, vmi_COND_L);
}

PPC32_MORPH_FN(morphE_CMPHL_X22_2) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 BF = state->info.BF;
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32compare(PPC32_GPR_BITS/2, GPR_RA, GPR_RB, BF, 0, 0, vmi_COND_B);
}

PPC32_MORPH_FN(morphDCMPO_X23) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCMPO_X23");
}

PPC32_MORPH_FN(morphDCMPU_X23) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCMPU_X23");
}

PPC32_MORPH_FN(morphDTSTEX_X23) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DTSTEX_X23");
}

PPC32_MORPH_FN(morphDTSTSF_X23) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DTSTSF_X23");
}

PPC32_MORPH_FN(morphFCMPO_X23) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BF = state->info.BF;
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);

    ppc32FPCompareRR(vmi_FT_64_IEEE_754, BF, FRA, FPR_FRA, FRB, FPR_FRB, True);
}

PPC32_MORPH_FN(morphFCMPU_X23) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BF = state->info.BF;
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);

    ppc32FPCompareRR(vmi_FT_64_IEEE_754, BF, FRA, FPR_FRA, FRB, FPR_FRB, False);
}

static void vmic_mcrfs(ppc32P ppc32, Uns32 BF, Uns32 BFA) {
    //
    // CR[BF] = FPSCR[BFA]
    //
    TYPE_FPSCR FPSCR;
    FPSCR.reg = read_fpscr(ppc32);

    Uns8 CRF = (FPSCR.reg >> ((7 - BFA) * 4)) & 0xf;

    //
    // Copy to CR
    //
    ppc32->LT[BF] = ((CRF >> 3) & 0x1);
    ppc32->GT[BF] = ((CRF >> 2) & 0x1);
    ppc32->EQ[BF] = ((CRF >> 1) & 0x1);
    ppc32->SO[BF] = ((CRF >> 0) & 0x1);

    //
    // Clear Flags in FPSCR
    //
    switch (BFA) {
    case 0:
        FPSCR.bits.FX = 0;
        FPSCR.bits.OX = 0;
        break;
    case 1:
        FPSCR.bits.UX = 0;
        FPSCR.bits.ZX = 0;
        FPSCR.bits.XX = 0;
        FPSCR.bits.VXSNAN = 0;
        break;
    case 2:
        FPSCR.bits.VXISI = 0;
        FPSCR.bits.VXIDI = 0;
        FPSCR.bits.VXZDZ = 0;
        FPSCR.bits.VXIMZ = 0;
        break;
    case 3:
        FPSCR.bits.VXVC = 0;
        break;
    case 5:
        FPSCR.bits.VXSOFT = 0;
        FPSCR.bits.VXSQRT = 0;
        FPSCR.bits.VXCVI = 0;
        break;
    }
    write_fpscr(ppc32, FPSCR.reg);
}

PPC32_MORPH_FN(morphMCRFS_X24) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BF = state->info.BF;
    Uns8 BFA = state->info.BFA;

    // CR[BF] = FPSCR[BFA]
    vmimtArgProcessor();
    vmimtArgUns32(BF);
    vmimtArgUns32(BFA);
    vmimtCall((vmiCallFn)vmic_mcrfs);
}

static void vmic_fpscr_to_cr1(ppc32P ppc32) {
    // LT (bit 0) = Floating point exception bit
    // GT (bit 1) = Common-point enable exception  bit
    // EQ (bit 2) = Floating point invalid exception bit
    // SO (bit 3) = Floating point overflow exception bit

    TYPE_FPSCR FPSCR;
    FPSCR.reg = read_fpscr(ppc32);

    ppc32->LT[1] = FPSCR.bits.FX;
    ppc32->GT[1] = FPSCR.bits.FEX;
    ppc32->EQ[1] = FPSCR.bits.VX;
    ppc32->SO[1] = FPSCR.bits.OX;
}

static void vmic_set_imm_fpscr(ppc32P ppc32, Uns32 BFU, Uns32 U, Uns32 RC) {
    //
    // Calculate new value
    //
    Uns8  shift = (28 - (4*BFU));
    Uns32 value = U << shift;
    Uns32  mask = ~(0xf << shift);

    TYPE_FPSCR FPSCR;
    FPSCR.reg  = read_fpscr(ppc32) & mask;
    FPSCR.reg |= (value & ppc32->FPSCR_wmask.reg);

    write_fpscr(ppc32, FPSCR.reg);

    if (RC==1) {
        vmic_fpscr_to_cr1(ppc32);
    }
}

#define FPSCRMASK(_value, _reg, _mask) _value = (_value & ~_mask) | (_reg & _mask)
static void vmic_set_reg_fpscr(ppc32P ppc32, Uns32 BL, Uns32 BW, Uns32 FLM, Uns32 FRB, Uns32 RC) {

    TYPE_FPSCR FPSCR;

    if (BL) {
        //
        // Take entire register, ignoring Mask
        //
        FPSCR.reg = ppc32->FPR[FRB];
    } else {
        //
        // Each nibble of the FRB is independantly enabled by a bit in the FLM
        //
        FPSCR.reg = read_fpscr(ppc32);
        if (FLM & 0x01) FPSCRMASK(FPSCR.reg, ppc32->FPR[FRB], 0x0000000f);
        if (FLM & 0x02) FPSCRMASK(FPSCR.reg, ppc32->FPR[FRB], 0x000000f0);
        if (FLM & 0x04) FPSCRMASK(FPSCR.reg, ppc32->FPR[FRB], 0x00000f00);
        if (FLM & 0x08) FPSCRMASK(FPSCR.reg, ppc32->FPR[FRB], 0x0000f000);
        if (FLM & 0x10) FPSCRMASK(FPSCR.reg, ppc32->FPR[FRB], 0x000f0000);
        if (FLM & 0x20) FPSCRMASK(FPSCR.reg, ppc32->FPR[FRB], 0x00f00000);
        if (FLM & 0x40) FPSCRMASK(FPSCR.reg, ppc32->FPR[FRB], 0x0f000000);
        if (FLM & 0x80) FPSCRMASK(FPSCR.reg, ppc32->FPR[FRB], 0xf0000000);
    }

    FPSCR.reg &= ppc32->FPSCR_wmask.reg;
    write_fpscr(ppc32, FPSCR.reg);

    if (RC==1) {
        vmic_fpscr_to_cr1(ppc32);
    }
}

static void vmic_set_bit_fpscr(ppc32P ppc32, Uns32 BT, Uns32 VAL, Uns32 RC) {

    Uns32 mask  = 0x1 << (31-BT);
    TYPE_FPSCR FPSCR;
    FPSCR.reg = read_fpscr(ppc32);

    if (mask & ~ppc32->FPSCR_wmask.reg) {
        //
        // Attempting to set a bit present in the write mask
        //
    } else {
        //
        // Insert a 0 or 1 ?
        //
        if (VAL) {
            FPSCR.reg |= mask;
        } else {
            FPSCR.reg &= ~mask;
        }
    }

    write_fpscr(ppc32, FPSCR.reg);

    if (RC==1) {
        vmic_fpscr_to_cr1(ppc32);
    }
}

PPC32_MORPH_FN(morphMTFSFIZ_X25_0) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BFU = state->info.BFU;
    Uns8 U   = state->info.U;

    vmimtArgProcessor();
    vmimtArgUns32(BFU);
    vmimtArgUns32(U);
    vmimtArgUns32(0);   // RC=0
    vmimtCall((vmiCallFn)vmic_set_imm_fpscr);
}

PPC32_MORPH_FN(morphMTFSFIZRC_X25_0) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BFU = state->info.BFU;
    Uns8 U   = state->info.U;

    vmimtArgProcessor();
    vmimtArgUns32(BFU);
    vmimtArgUns32(U);
    vmimtArgUns32(1);   // RC=1
    vmimtCall((vmiCallFn)vmic_set_imm_fpscr);
}

PPC32_MORPH_FN(morphMTFSFI_X25_1) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 BFU = state->info.BFU;
    // Uns8 U = state->info.U;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "MTFSFI_X25_1");
}

PPC32_MORPH_FN(morphMTFSFIRC_X25_1) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 BFU = state->info.BFU;
    // Uns8 U = state->info.U;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "MTFSFIRC_X25_1");
}

PPC32_MORPH_FN(morphMCRXR_X26) {
    //
    // Supported Architecture=I_E
    //
    Uns8 BF = state->info.BF;

    //
    // Load the contents of CR[crfd]
    // PPC32_SO_WR(BF)
    vmimtMoveRR(8, PPC32_LT_WR(BF), PPC32_XER_SO_RD);
    vmimtMoveRR(8, PPC32_GT_WR(BF), PPC32_XER_OV_RD);
    vmimtMoveRR(8, PPC32_EQ_WR(BF), PPC32_XER_CA_RD);
    vmimtMoveRC(8, PPC32_SO_WR(BF), 0);

    //
    // Now Clear the contents of XER
    //
    vmimtMoveRC(8, PPC32_XER_SO_RD, 0);
    vmimtMoveRC(8, PPC32_XER_OV_RD, 0);
    vmimtMoveRC(8, PPC32_XER_CA_RD, 0);
}

PPC32_MORPH_FN(morphDCBT_X27_0) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 TH = state->info.TH;
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBT_X27_0");
}

PPC32_MORPH_FN(morphDCBTST_X27_0) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 TH = state->info.TH;
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBTST_X27_0");
}

PPC32_MORPH_FN(morphDCBTST_1_X27_1) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBTST_1_X27_1");
}

PPC32_MORPH_FN(morphDCBT_1_X27_1) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBT_1_X27_1");
}

PPC32_MORPH_FN(morphDCBTEP_X27_2) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 TH = state->info.TH;
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBTEP_X27_2");
}

PPC32_MORPH_FN(morphDCBTSTEP_X27_2) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 TH = state->info.TH;
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBTSTEP_X27_2");
}

PPC32_MORPH_FN(morphDCI_0_X28_0) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 CT = state->info.CT;
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCI_0_X28_0");
}

PPC32_MORPH_FN(morphICI_0_X28_0) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 CT = state->info.CT;
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "ICI_0_X28_0");
}

PPC32_MORPH_FN(morphDCI_X28_1) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 CT = state->info.CT;
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCI_X28_1");
}

PPC32_MORPH_FN(morphICI_X28_1) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 CT = state->info.CT;
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "ICI_X28_1");
}

PPC32_MORPH_FN(morphDCBLC_0_X29_0) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCBLC_0_X29_0");
}

PPC32_MORPH_FN(morphDCBTLS_0_X29_0) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCBTLS_0_X29_0");
}

PPC32_MORPH_FN(morphDCBTSTLS_0_X29_0) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCBTSTLS_0_X29_0");
}

PPC32_MORPH_FN(morphICBLC_0_X29_0) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "ICBLC_0_X29_0");
}

PPC32_MORPH_FN(morphICBTLS_0_X29_0) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "ICBTLS_0_X29_0");
}

PPC32_MORPH_FN(morphICBT_CT0_X29_0) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "ICBT_CT0_X29_0");
}

PPC32_MORPH_FN(morphDCBLC_1_X29_1) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCBLC_1_X29_1");
}

PPC32_MORPH_FN(morphDCBTLS_1_X29_1) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCBTLS_1_X29_1");
}

PPC32_MORPH_FN(morphDCBTSTLS_1_X29_1) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCBTSTLS_1_X29_1");
}

PPC32_MORPH_FN(morphICBLC_1_X29_1) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "ICBLC_1_X29_1");
}

PPC32_MORPH_FN(morphICBT_X29_1) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "ICBT_X29_1");
}

PPC32_MORPH_FN(morphICBTLS_1_X29_1) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 CT = state->info.CT;
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "ICBTLS_1_X29_1");
}

PPC32_MORPH_FN(morphLWARX_X3) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 EH = state->info.EH;
    Uns8 RA = state->info.RA;
    Uns8 RB = state->info.RB;
    Uns8 RT = state->info.RT;

    ppc32loadReserve(state, RT, RA, RB, 4);
}

PPC32_MORPH_FN(morphDCBF_X30) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBF_X30");
}

PPC32_MORPH_FN(morphDCBF_L_X30) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBF_L_X30");
}

PPC32_MORPH_FN(morphDCBF_LP_X30) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBF_LP_X30");
}

PPC32_MORPH_FN(morphTLBIEL_0_X31_0) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "TLBIEL_0_X31_0");
}

PPC32_MORPH_FN(morphTLBIE_0_X31_0) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    vmiMessage("W", "UNIMP", "TLBIE L=0 RB=%d\n", state->info.RB);
//    morphUnimplemented(state, "TLBIE_0_X31_0");
}

PPC32_MORPH_FN(morphTLBIEL_1_X31_1) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "TLBIEL_1_X31_1");
}

PPC32_MORPH_FN(morphTLBIE_1_X31_1) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    vmiMessage("W", "UNIMP", "TLBIE L=1 RB=%d\n", state->info.RB);
//    morphUnimplemented(state, "TLBIE_1_X31_1");
}

PPC32_MORPH_FN(morphLWSYNC_X32) {
    //
    // Supported Architecture=I_B
    //
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "LWSYNC_X32");
}

PPC32_MORPH_FN(morphPTESYNC_X32) {
    //
    // Supported Architecture=I_B
    //
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "PTESYNC_X32");
}

PPC32_MORPH_FN(morphSYNC_X32) {
    //
    // Supported Architecture=I_B
    //
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "SYNC_X32");
}

PPC32_MORPH_FN(morphTW_X33) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 TO = state->info.TO;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "TW_X33");
}

PPC32_MORPH_FN(morphLFDEPX_X34) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "LFDEPX_X34");
}

PPC32_MORPH_FN(morphLFDUX_X34) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32loadDFPR(FPR_FRT, GPR_RA, GPR_RB, state, 0, PPC32_FPR_BITS, True);
}

PPC32_MORPH_FN(morphLFDX_X34) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32loadDFPR(FPR_FRT, GPR_RA, GPR_RB, state, 0, PPC32_FPR_BITS, False);
}

PPC32_MORPH_FN(morphLFIWAX_X34) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32loadDFPR(FPR_FRT, GPR_RA, GPR_RB, state, 0, PPC32_FPR_BITS/2, False);
}

PPC32_MORPH_FN(morphLFSUX_X34) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32loadSFPR(FPR_FRT, GPR_RA, GPR_RB, state, 0, PPC32_FPR_BITS/2, True);
}

PPC32_MORPH_FN(morphLFSX_X34) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32loadSFPR(FPR_FRT, GPR_RA, GPR_RB, state, 0, PPC32_FPR_BITS/2, False);
}

PPC32_MORPH_FN(morphSTFDEPX_X34) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "STFDEPX_X34");
}

PPC32_MORPH_FN(morphDADD_X35RC) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "DADD_X35RC");
}

PPC32_MORPH_FN(morphDADDRC_X35RC) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "DADDRC_X35RC");
}

PPC32_MORPH_FN(morphDDIV_X35RC) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "DDIV_X35RC");
}

PPC32_MORPH_FN(morphDDIVRC_X35RC) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "DDIVRC_X35RC");
}

PPC32_MORPH_FN(morphDIEX_X35RC) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "DIEX_X35RC");
}

PPC32_MORPH_FN(morphDIEXRC_X35RC) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "DIEXRC_X35RC");
}

PPC32_MORPH_FN(morphDMUL_X35RC) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "DMUL_X35RC");
}

PPC32_MORPH_FN(morphDMULRC_X35RC) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "DMULRC_X35RC");
}

PPC32_MORPH_FN(morphDSUB_X35RC) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "DSUB_X35RC");
}

PPC32_MORPH_FN(morphDSUBRC_X35RC) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    morphUnimplemented(state, "DSUBRC_X35RC");
}

PPC32_MORPH_FN(morphFCPSGN_X35RC) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRA = state->info.FRA;
    vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    // Mask bit 0
    vmimtBinopRRC(PPC32_FPR_BITS, vmi_AND, FPR_FRT,       FPR_FRB, 0x7FFFFFFFFFFFFFFFULL, 0);
    // Mask bit 1:31
    vmimtBinopRRC(PPC32_FPR_BITS, vmi_AND, PPC32_TEMP(0), FPR_FRA, 0x8000000000000000ULL, 0);
    // Or to result
    vmimtBinopRR(PPC32_FPR_BITS, vmi_OR, FPR_FRT, PPC32_TEMP(0), 0);

}

PPC32_MORPH_FN(morphFCPSGNRC_X35RC) {
    //
    // Supported Architecture=I_FP
    //
    morphFCPSGN_X35RC(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphDCTDP_X37) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCTDP_X37");
}

PPC32_MORPH_FN(morphDCTDPRC_X37) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCTDPRC_X37");
}

PPC32_MORPH_FN(morphDCTFIX_X37) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCTFIX_X37");
}

PPC32_MORPH_FN(morphDCTFIXRC_X37) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCTFIXRC_X37");
}

PPC32_MORPH_FN(morphDRSP_X37) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRSP_X37");
}

PPC32_MORPH_FN(morphDRSPRC_X37) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRSPRC_X37");
}

PPC32_MORPH_FN(morphDXEX_X37) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DXEX_X37");
}

PPC32_MORPH_FN(morphDXEXRC_X37) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DXEXRC_X37");
}

PPC32_MORPH_FN(morphFABS_X37) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    //
    // Simply mask the sign bit - not really FP ABS
    //
    vmimtMoveRR(PPC32_FPR_BITS, FPR_FRT, FPR_FRB);
    vmimtBinopRC(PPC32_FPR_BITS, vmi_AND, FPR_FRT, 0x7FFFFFFFFFFFFFFFULL, 0);
}

PPC32_MORPH_FN(morphFABSRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    morphFABS_X37(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFCFID_X37) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPConvertRR(vmi_FT_64_IEEE_754, FPR_FRT, vmi_FT_64_INT, FPR_FRB, vmi_FPR_CURRENT, PPC32_FPU_FLG);
}

PPC32_MORPH_FN(morphFCFIDRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    morphFCFID_X37(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFCTID_X37) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPConvertRR(vmi_FT_64_INT, FPR_FRT, vmi_FT_64_IEEE_754, FPR_FRB, vmi_FPR_CURRENT, PPC32_FPU_FLG);
}

PPC32_MORPH_FN(morphFCTIDRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    morphFCTID_X37(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFCTIDZ_X37) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPConvertRR(vmi_FT_64_INT, FPR_FRT, vmi_FT_64_IEEE_754, FPR_FRB, vmi_FPR_ZERO, PPC32_FPU_FLG);
}

PPC32_MORPH_FN(morphFCTIDZRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    morphFCTIDZ_X37(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFCTIW_X37) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPConvertRR(vmi_FT_32_INT, FPR_FRT, vmi_FT_64_IEEE_754, FPR_FRB, vmi_FPR_CURRENT, PPC32_FPU_FLG);
}

PPC32_MORPH_FN(morphFCTIWRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    morphFCTIW_X37(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFCTIWZ_X37) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    ppc32FPConvertRR(vmi_FT_32_INT, FPR_FRT, vmi_FT_64_IEEE_754, FPR_FRB, vmi_FPR_ZERO, PPC32_FPU_FLG);
}

PPC32_MORPH_FN(morphFCTIWZRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    morphFCTIWZ_X37(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFMR_X37) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_RD(FRT);

    vmimtMoveRR(PPC32_FPR_BITS, FPR_FRT, FPR_FRB);
}

PPC32_MORPH_FN(morphFMRRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    morphFMR_X37(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFNABS_X37) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    //
    // Simply set the sign bit - not really FP NABS
    //
    vmimtMoveRR(PPC32_FPR_BITS, FPR_FRT, FPR_FRB);
    vmimtBinopRC(PPC32_FPR_BITS, vmi_OR, FPR_FRT, 0x8000000000000000ULL, 0);
}

PPC32_MORPH_FN(morphFNABSRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    morphFNABS_X37(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFNEG_X37) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    //
    // Toggle sign bit
    //
    vmimtMoveRR(PPC32_FPR_BITS, FPR_FRT, FPR_FRB);
    vmimtBinopRC(PPC32_FPR_BITS, vmi_XOR, FPR_FRT, 0x8000000000000000ULL, 0);
}

PPC32_MORPH_FN(morphFNEGRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    morphFNEG_X37(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphFRIM_X37) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRIM_X37");
}

PPC32_MORPH_FN(morphFRIMRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRIMRC_X37");
}

PPC32_MORPH_FN(morphFRIN_X37) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRIN_X37");
}

PPC32_MORPH_FN(morphFRINRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRINRC_X37");
}

PPC32_MORPH_FN(morphFRIP_X37) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRIP_X37");
}

PPC32_MORPH_FN(morphFRIPRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRIPRC_X37");
}

PPC32_MORPH_FN(morphFRIZ_X37) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRIZ_X37");
}

PPC32_MORPH_FN(morphFRIZRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "FRIZRC_X37");
}

PPC32_MORPH_FN(morphFRSP_X37) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRB = state->info.FRB;
    vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    vmiLabelP L1 = vmimtNewLabel();

    //
    // This function needs special handling of the input argument
    //
    vmimtArgProcessor();
    vmimtArgUns32(FRT);
    vmimtArgUns32(FRB);
    vmimtCallResult((vmiCallFn)ppc32RoundingDFP_TO_SFP, 8, PPC32_FLG_TEMP);

    //
    // if PPC32_FLG_TEMP == 0, skip morph conversion
    //
    vmimtCondJumpLabel(PPC32_FLG_TEMP, False, L1);

    ppc32FPConvertRR(vmi_FT_32_IEEE_754, FPR_FRT, vmi_FT_64_IEEE_754, FPR_FRB, vmi_FPR_CURRENT, PPC32_FPU_FLG);
    ppc32FPConvertRR(vmi_FT_64_IEEE_754, FPR_FRT, vmi_FT_32_IEEE_754, FPR_FRT, vmi_FPR_CURRENT, VMI_NOREG);

    vmimtInsertLabel(L1);
    //
    // Generate the FPSCR.C bit
    //
    // FPU_OP = BINOP(8)
    vmimtMoveRC(PPC32_FPU_OP_BITS, PPC32_FPU_OP, FPUOP_FRSP);
}

PPC32_MORPH_FN(morphFRSPRC_X37) {
    //
    // Supported Architecture=I_FP
    //
    morphFRSP_X37(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphDCTFIXQ_X38) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCTFIXQ_X38");
}

PPC32_MORPH_FN(morphDCTFIXQRC_X38) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCTFIXQRC_X38");
}

PPC32_MORPH_FN(morphDXEX_X38) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DXEX_X38");
}

PPC32_MORPH_FN(morphDXEXRC_X38) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DXEXRC_X38");
}

PPC32_MORPH_FN(morphMFFS_X39) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRT = state->info.FRT;
    vmiReg FPR_FRT = PPC32_FPR_WR(FRT);

    vmimtMoveRC(PPC32_FPR_BITS, FPR_FRT, 0);
    vmimtMoveRR(PPC32_GPR_BITS, FPR_FRT, PPC32_FPSCR_RD);
}

PPC32_MORPH_FN(morphMFFSRC_X39) {
    //
    // Supported Architecture=I_FP
    //
    morphMFFS_X39(state);
    emitFPSCR_to_CR1();
}

PPC32_MORPH_FN(morphLSWI_X4) {
    //
    // Supported Architecture=I_MA
    //
    Uns8 NB = state->info.NB;
    // vmiReg GPR_NB = PPC32_GPR_RD(NB);
    // vmiReg GPR_NB = PPC32_GPR_WR(NB);
    Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    // morphUnimplemented(state, "LSWI_X4");

    ppc32loadString(RT, RA, 0, NB, 0);
}

PPC32_MORPH_FN(morphDCFFIXQ_X40) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCFFIXQ_X40");
}

PPC32_MORPH_FN(morphDCFFIXQRC_X40) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCFFIXQRC_X40");
}

PPC32_MORPH_FN(morphDCTQPQ_X40) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCTQPQ_X40");
}

PPC32_MORPH_FN(morphDCTQPQRC_X40) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCTQPQRC_X40");
}

PPC32_MORPH_FN(morphDRDPQ_X41) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRDPQ_X41");
}

PPC32_MORPH_FN(morphDRDPQRC_X41) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRDPQRC_X41");
}

PPC32_MORPH_FN(morphDADDQ_X43) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    morphUnimplemented(state, "DADDQ_X43");
}

PPC32_MORPH_FN(morphDADDQRC_X43) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    morphUnimplemented(state, "DADDQRC_X43");
}

PPC32_MORPH_FN(morphDDIVQ_X43) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    morphUnimplemented(state, "DDIVQ_X43");
}

PPC32_MORPH_FN(morphDDIVQRC_X43) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    morphUnimplemented(state, "DDIVQRC_X43");
}

PPC32_MORPH_FN(morphDIEXQ_X43) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    morphUnimplemented(state, "DIEXQ_X43");
}

PPC32_MORPH_FN(morphDIEXQRC_X43) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    morphUnimplemented(state, "DIEXQRC_X43");
}

PPC32_MORPH_FN(morphDMULQ_X43) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    morphUnimplemented(state, "DMULQ_X43");
}

PPC32_MORPH_FN(morphDMULQRC_X43) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    morphUnimplemented(state, "DMULQRC_X43");
}

PPC32_MORPH_FN(morphDSUBQ_X43) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    morphUnimplemented(state, "DSUBQ_X43");
}

PPC32_MORPH_FN(morphDSUBQRC_X43) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    morphUnimplemented(state, "DSUBQRC_X43");
}

PPC32_MORPH_FN(morphDCMPOQ_X45) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCMPOQ_X45");
}

PPC32_MORPH_FN(morphDCMPUQ_X45) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DCMPUQ_X45");
}

PPC32_MORPH_FN(morphDTSTEXQ_X45) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DTSTEXQ_X45");
}

PPC32_MORPH_FN(morphDTSTSFQ_X45) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DTSTSFQ_X45");
}

PPC32_MORPH_FN(morphDDEDPD_X46_0) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 SP = state->info.SP;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DDEDPD_X46_0");
}

PPC32_MORPH_FN(morphDDEDPDRC_X46_0) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 SP = state->info.SP;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DDEDPDRC_X46_0");
}

PPC32_MORPH_FN(morphDENBCD_X46_1) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 S = state->info.S;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DENBCD_X46_1");
}

PPC32_MORPH_FN(morphDENBCDRC_X46_1) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 S = state->info.S;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DENBCDRC_X46_1");
}

PPC32_MORPH_FN(morphDDEDPDQ_X47_0) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 SP = state->info.SP;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DDEDPDQ_X47_0");
}

PPC32_MORPH_FN(morphDDEDPDQRC_X47_0) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 SP = state->info.SP;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DDEDPDQRC_X47_0");
}

PPC32_MORPH_FN(morphDENBCDQ_X47_1) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 S = state->info.S;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DENBCDQ_X47_1");
}

PPC32_MORPH_FN(morphDENBCDQRC_X47_1) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 S = state->info.S;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DENBCDQRC_X47_1");
}

PPC32_MORPH_FN(morphSTFDUX_X48) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRS = state->info.FRS;
    vmiReg FPR_FRS = PPC32_FPR_RD(FRS);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32storeDFPR(FPR_FRS, GPR_RA, GPR_RB, state, 0, PPC32_FPR_BITS, True);
}

PPC32_MORPH_FN(morphSTFDX_X48) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRS = state->info.FRS;
    vmiReg FPR_FRS = PPC32_FPR_RD(FRS);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32storeDFPR(FPR_FRS, GPR_RA, GPR_RB, state, 0, PPC32_FPR_BITS, False);
}

PPC32_MORPH_FN(morphSTFIWX_X48) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRS = state->info.FRS;
    vmiReg FPR_FRS = PPC32_FPR_RD(FRS);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32storeDFPR(FPR_FRS, GPR_RA, GPR_RB, state, 0, PPC32_FPR_BITS/2, False);
}

PPC32_MORPH_FN(morphSTFSUX_X48) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRS = state->info.FRS;
    vmiReg FPR_FRS = PPC32_FPR_RD(FRS);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32storeSFPR(FPR_FRS, GPR_RA, GPR_RB, state, 0, True);
}

PPC32_MORPH_FN(morphSTFSX_X48) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 FRS = state->info.FRS;
    vmiReg FPR_FRS = PPC32_FPR_RD(FRS);
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);

    ppc32storeSFPR(FPR_FRS, GPR_RA, GPR_RB, state, 0, False);
}

PPC32_MORPH_FN(morphMFSR_X5) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Uns8 SR = state->info.SR;
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "MFSR_X5");
}

static void emit_vmic_set_bit_fpscr(Uns8 BT, Uns8 VAL, Uns8 RC) {
    vmimtArgProcessor();
    vmimtArgUns32(BT);
    vmimtArgUns32(VAL);
    vmimtArgUns32(RC);
    vmimtCall((vmiCallFn)vmic_set_bit_fpscr);
}

PPC32_MORPH_FN(morphMTFSSB0_X50) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BT = state->info.BT;
    emit_vmic_set_bit_fpscr(BT, 0, 0);
}

PPC32_MORPH_FN(morphMTFSSB0RC_X50) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BT = state->info.BT;
    emit_vmic_set_bit_fpscr(BT, 0, 1);
}

PPC32_MORPH_FN(morphMTFSSB1_X50) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BT = state->info.BT;
    emit_vmic_set_bit_fpscr(BT, 1, 0);
}

PPC32_MORPH_FN(morphMTFSSB1RC_X50) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BT = state->info.BT;
    emit_vmic_set_bit_fpscr(BT, 1, 1);
}

PPC32_MORPH_FN(morphDCBA_X51) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBA_X51");
}

PPC32_MORPH_FN(morphDCBFEP_X51) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCBFEP_X51");
}

PPC32_MORPH_FN(morphDCBI_X51) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCBI_X51");
}

PPC32_MORPH_FN(morphDCBST_X51) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBST_X51");
}

PPC32_MORPH_FN(morphDCBSTEP_X51) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCBSTEP_X51");
}

PPC32_MORPH_FN(morphDCBZ_X51) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "DCBZ_X51");
}

PPC32_MORPH_FN(morphDCBZEP_X51) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "DCBZEP_X51");
}

PPC32_MORPH_FN(morphICBI_X51) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "ICBI_X51");
}

PPC32_MORPH_FN(morphICBIEP_X51) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "ICBIEP_X51");
}

PPC32_MORPH_FN(morphICREAD_X51) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphWarnNopMapping(state, "ICREAD_X51");
}

PPC32_MORPH_FN(morphTLBIVAX_X51) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "TLBIVAX_X51");
}

PPC32_MORPH_FN(morphTLBSX_X51) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "TLBSX_X51");
}

PPC32_MORPH_FN(morphMSGCLR_X52) {
    //
    // Supported Architecture=I_E_PC
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "MSGCLR_X52");
}

PPC32_MORPH_FN(morphMSGSND_X52) {
    //
    // Supported Architecture=I_E_PC
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "MSGSND_X52");
}

PPC32_MORPH_FN(morphSLBIE_X52) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "SLBIE_X52");
}

PPC32_MORPH_FN(morphEIEIO_X53_0) {
    //
    // Supported Architecture=I_S
    //
    morphUnimplemented(state, "EIEIO_X53_0");
}

PPC32_MORPH_FN(morphTLBIA_X53_1) {
    //
    // Supported Architecture=I_S
    //
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "TLBIA_X53_1");
}

PPC32_MORPH_FN(morphTLBRE_X53_1) {
    //
    // Supported Architecture=I_E
    //
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "TLBRE_X53_1");
}

PPC32_MORPH_FN(morphTLBSYNC_X53_1) {
    //
    // Supported Architecture=I_B
    //
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "TLBSYNC_X53_1");
}

PPC32_MORPH_FN(morphTLBWE_X53_1) {
    //
    // Supported Architecture=I_E
    //
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "TLBWE_X53_1");
}

PPC32_MORPH_FN(morphWAIT_X53_1) {
    //
    // Supported Architecture=I_WT
    //
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "WAIT_X53_1");
}

PPC32_MORPH_FN(morphWRTEEI_X54) {
    //
    // Supported Architecture=I_E
    //
    CHECK_PRIV(state);

    Uns8 E = state->info.E;
    ppc32wrteei(state->ppc32, E);
}

PPC32_MORPH_FN(morphSLBIA_0_X55_0) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 IH = state->info.IH;
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "SLBIA_0_X55_0");
}

PPC32_MORPH_FN(morphSLBIA_1_X55_1) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 IH = state->info.IH;
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "SLBIA_1_X55_1");
}

PPC32_MORPH_FN(morphLVEBX_X58) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "LVEBX_X58");
}

PPC32_MORPH_FN(morphLVEHX_X58) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "LVEHX_X58");
}

PPC32_MORPH_FN(morphLVEWX_X58) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "LVEWX_X58");
}

PPC32_MORPH_FN(morphLVSL_X58) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "LVSL_X58");
}

PPC32_MORPH_FN(morphLVSR_X58) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "LVSR_X58");
}

PPC32_MORPH_FN(morphLVX_X58) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "LVX_X58");
}

PPC32_MORPH_FN(morphLVXL_X58) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRT = state->info.VRT;
    // vmiReg VR_VRT = PPC32_VR_RD(VRT);
    // vmiReg VR_VRT = PPC32_VR_WR(VRT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "LVXL_X58");
}

PPC32_MORPH_FN(morphSTVEBX_X59) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRS = state->info.VRS;
    // vmiReg VR_VRS = PPC32_VR_RD(VRS);
    // vmiReg VR_VRS = PPC32_VR_WR(VRS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "STVEBX_X59");
}

PPC32_MORPH_FN(morphSTVEHX_X59) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRS = state->info.VRS;
    // vmiReg VR_VRS = PPC32_VR_RD(VRS);
    // vmiReg VR_VRS = PPC32_VR_WR(VRS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "STVEHX_X59");
}

PPC32_MORPH_FN(morphSTVEWX_X59) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRS = state->info.VRS;
    // vmiReg VR_VRS = PPC32_VR_RD(VRS);
    // vmiReg VR_VRS = PPC32_VR_WR(VRS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "STVEWX_X59");
}

PPC32_MORPH_FN(morphSTVX_X59) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRS = state->info.VRS;
    // vmiReg VR_VRS = PPC32_VR_RD(VRS);
    // vmiReg VR_VRS = PPC32_VR_WR(VRS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "STVX_X59");
}

PPC32_MORPH_FN(morphSTVXL_X59) {
    //
    // Supported Architecture=I_V
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 VRS = state->info.VRS;
    // vmiReg VR_VRS = PPC32_VR_RD(VRS);
    // vmiReg VR_VRS = PPC32_VR_WR(VRS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "STVXL_X59");
}

PPC32_MORPH_FN(morphMFSRIN_X6) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "MFSRIN_X6");
}

PPC32_MORPH_FN(morphSLBMFEE_X6) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "SLBMFEE_X6");
}

PPC32_MORPH_FN(morphSLBMFEV_X6) {
    //
    // Supported Architecture=I_S
    //
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "SLBMFEV_X6");
}

PPC32_MORPH_FN(morphMBAR_X60) {
    //
    // Supported Architecture=I_E
    //
    // Uns8 MO = state->info.MO;
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "MBAR_X60");
}

PPC32_MORPH_FN(morphMFMSR_X8) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    // morphUnimplemented(state, "MFMSR_X8");
    CHECK_PRIV(state);

    ppc32mfmsr(state->ppc32, GPR_RT, RT);
}

PPC32_MORPH_FN(morphAND_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_AND, GPR_RA, GPR_RS, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphANDC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_ANDN, GPR_RA, GPR_RS, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphANDCRC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_ANDN, GPR_RA, GPR_RS, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphANDRC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_AND, GPR_RA, GPR_RS, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphDLMZB_X9) {
    //
    // Supported Architecture=I_LMA
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    morphUnimplemented(state, "DLMZB_X9");
}

PPC32_MORPH_FN(morphDLMZBRC_X9) {
    //
    // Supported Architecture=I_LMA
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    morphUnimplemented(state, "DLMZBRC_X9");
}

PPC32_MORPH_FN(morphEQV_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_XNOR, GPR_RA, GPR_RS, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphEQVRC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_XNOR, GPR_RA, GPR_RS, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_RLW_X9) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_ROL, GPR_RA, GPR_RS, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphE_RLWRC_X9) {
    //
    // Supported Architecture=I_VLE
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_ROL, GPR_RA, GPR_RS, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphNAND_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_NAND, GPR_RA, GPR_RS, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphNANDRC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_NAND, GPR_RA, GPR_RS, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphNOR_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_NOR, GPR_RA, GPR_RS, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphNORRC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_NOR, GPR_RA, GPR_RS, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphOR_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_OR, GPR_RA, GPR_RS, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphORC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_ORN, GPR_RA, GPR_RS, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphORCRC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_ORN, GPR_RA, GPR_RS, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphORRC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_OR, GPR_RA, GPR_RS, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphSLW_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_SHL, GPR_RA, GPR_RS, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSLWRC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_SHL, GPR_RA, GPR_RS, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphSRAW_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32sraw(GPR_RS, GPR_RA, GPR_RB, 0);
}

PPC32_MORPH_FN(morphSRAWRC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32sraw(GPR_RS, GPR_RA, GPR_RB, 1);
}

PPC32_MORPH_FN(morphSRW_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    ppc32BinopRRR(vmi_SHR, GPR_RA, GPR_RS, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSRWRC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_SHR, GPR_RA, GPR_RS, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphXOR_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_XOR, GPR_RA, GPR_RS, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphXORRC_X9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_WR(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32BinopRRR(vmi_XOR, GPR_RA, GPR_RS, GPR_RB, 0, 1, 0, 0, 0);
}

static void emit_vmic_set_reg_fpscr(Uns8 BL, Uns8 BW, Uns8 FLM, Uns8 FRB, Uns8 RC) {
    vmimtArgProcessor();
    vmimtArgUns32(BL);
    vmimtArgUns32(BW);
    vmimtArgUns32(FLM);
    vmimtArgUns32(FRB);
    vmimtArgUns32(RC);
    vmimtCall((vmiCallFn)vmic_set_reg_fpscr);
}

PPC32_MORPH_FN(morphMTFSF_XFL) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BL = state->info.BL;
    Uns8 BW = state->info.BW;
    Uns8 FLM = state->info.FLM;
    Uns8 FRB = state->info.FRB;

    emit_vmic_set_reg_fpscr(BL, BW, FLM, FRB, 0);
}

PPC32_MORPH_FN(morphMTFSFRC_XFL) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BL = state->info.BL;
    Uns8 BW = state->info.BW;
    Uns8 FLM = state->info.FLM;
    Uns8 FRB = state->info.FRB;

    emit_vmic_set_reg_fpscr(BL, BW, FLM, FRB, 1);
}

PPC32_MORPH_FN(morphMTFSFZ_XFLZ) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BL = state->info.BL;
    Uns8 BW = state->info.BW;
    Uns8 FLM = state->info.FLM;
    Uns8 FRB = state->info.FRB;

    emit_vmic_set_reg_fpscr(BL, BW, FLM, FRB, 0);
}

PPC32_MORPH_FN(morphMTFSFZRC_XFLZ) {
    //
    // Supported Architecture=I_FP
    //
    Uns8 BL = state->info.BL;
    Uns8 BW = state->info.BW;
    Uns8 FLM = state->info.FLM;
    Uns8 FRB = state->info.FRB;

    emit_vmic_set_reg_fpscr(BL, BW, FLM, FRB, 1);
}

PPC32_MORPH_FN(morphMFSPR_XFX1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns16 SPR = state->info.SPR;

    ppc32mfspr(state->ppc32, RT, GPR_RT, SPR);
}

PPC32_MORPH_FN(morphMFTB_XFX1) {
    //
    // Supported Architecture=I_S
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);
    Uns16 SPR = state->info.SPR;

    ppc32mfspr(state->ppc32, RT, GPR_RT, SPR);
}

PPC32_MORPH_FN(morphMTSPR_XFX10) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);
    Uns16 SPR = state->info.SPR;

    ppc32mtspr(state->ppc32, SPR, GPR_RS, RS);
}

PPC32_MORPH_FN(morphMTCTR_XFX10D) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32mtspr(state->ppc32, 9, GPR_RS, RS);
}

PPC32_MORPH_FN(morphMTLR_XFX10D) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32mtspr(state->ppc32, 8, GPR_RS, RS);
}

PPC32_MORPH_FN(morphMTXER_XFX10D) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    ppc32mtspr(state->ppc32, 1, GPR_RS, RS);
}

PPC32_MORPH_FN(morphMTDCR_XFX11) {
    //
    // Supported Architecture=I_E
    //
    // Uns16 DCR = state->info.DCR;
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "MTDCR_XFX11");
}

PPC32_MORPH_FN(morphMTPMR_XFX12) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns16 PMRN = state->info.PMRN;
    // Uns8 RS = state->info.RS;
    // vmiReg GPR_RS = PPC32_GPR_RD(RS);
    // vmiReg GPR_RS = PPC32_GPR_WR(RS);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "MTPMR_XFX12");
}

PPC32_MORPH_FN(morphMFCTR_XFX1D) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mfspr(state->ppc32, RT, GPR_RT, 9);
}

PPC32_MORPH_FN(morphMFLR_XFX1D) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mfspr(state->ppc32, RT, GPR_RT, 8);
}

PPC32_MORPH_FN(morphMFXER_XFX1D) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mfspr(state->ppc32, RT, GPR_RT, 1);
}

PPC32_MORPH_FN(morphMFCR_XFX3) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    vmimtArgProcessor();
    vmimtCall((vmiCallFn)ppc32PackCR);
    vmimtMoveRR(PPC32_GPR_BITS, GPR_RT, PPC32_CR_RD);
}

//
// Note other bits of target register are undefined - in fact
// it seems to copy into all fields of the target register. so
// copy behavior
//
PPC32_MORPH_FN(morphMFOCRF_XFX4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 FXM = state->info.FXM;
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    //
    // If FXM has more than one bit set - this is illegal
    //
    Int32 i;
    Uns8  v = FXM;
    Uns8  cnt = 0;
    for(i=0; i<=7; i++) {
        if (v & 0x1) {
            cnt++;
        }
        v >>= 1;
    }
    if (cnt>1) {
        vmiMessage("W", "ILL_MFOCRF", "Illegal value for FXM=0x%02x", FXM);
    }

    vmimtArgProcessor();
    vmimtCall((vmiCallFn)ppc32PackCR);
    vmimtMoveRR(PPC32_GPR_BITS, GPR_RT, PPC32_CR_RD);

}

PPC32_MORPH_FN(morphMFDCR_XFX5) {
    //
    // Supported Architecture=I_E
    //
    // Uns16 DCR = state->info.DCR;
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "MFDCR_XFX5");
}

PPC32_MORPH_FN(morphMFPMR_XFX6) {
    //
    // Supported Architecture=I_E_PD
    //
    // Uns16 PMRN = state->info.PMRN;
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "MFPMR_XFX6");
}

static void mtcrf_expand(vmiReg rs, Uns8 CRi, Uns8 RSi) {
    vmimtBinopRRC(PPC32_GPR_BITS, vmi_SHR, PPC32_TEMP(0), rs, RSi+3, 0);
    vmimtBinopRRC(8, vmi_AND, PPC32_LT_WR(CRi), PPC32_TEMP(0), 0x1, 0);

    vmimtBinopRRC(PPC32_GPR_BITS, vmi_SHR, PPC32_TEMP(0), rs, RSi+2, 0);
    vmimtBinopRRC(8, vmi_AND, PPC32_GT_WR(CRi), PPC32_TEMP(0), 0x1, 0);

    vmimtBinopRRC(PPC32_GPR_BITS, vmi_SHR, PPC32_TEMP(0), rs, RSi+1, 0);
    vmimtBinopRRC(8, vmi_AND, PPC32_EQ_WR(CRi), PPC32_TEMP(0), 0x1, 0);

    vmimtBinopRRC(PPC32_GPR_BITS, vmi_SHR, PPC32_TEMP(0), rs, RSi+0, 0);
    vmimtBinopRRC(8, vmi_AND, PPC32_SO_WR(CRi), PPC32_TEMP(0), 0x1, 0);
}

static void mtcrf(Uns8 mask, vmiReg rs) {
    if (mask & 0x80) mtcrf_expand(rs, 0, 28);
    if (mask & 0x40) mtcrf_expand(rs, 1, 24);
    if (mask & 0x20) mtcrf_expand(rs, 2, 20);
    if (mask & 0x10) mtcrf_expand(rs, 3, 16);
    if (mask & 0x08) mtcrf_expand(rs, 4, 12);
    if (mask & 0x04) mtcrf_expand(rs, 5, 8);
    if (mask & 0x02) mtcrf_expand(rs, 6, 4);
    if (mask & 0x01) mtcrf_expand(rs, 7, 0);
}

PPC32_MORPH_FN(morphMTCRF_XFX8) {
    //
    // Supported Architecture=I_B
    //
    Uns8 FXM = state->info.FXM;
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    // Set CR0
    //
    // LT[0] = CR0[LT] = RS[31]
    // GT[0] = CR0[GT] = RS[30]
    // EQ[0] = CR0[EQ] = RS[29]
    // SO[0] = CR0[SO] = RS[28]
    //
    mtcrf(FXM, GPR_RS);
}

PPC32_MORPH_FN(morphMTCR_XFX8D) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    mtcrf(0xff, GPR_RS);
}

PPC32_MORPH_FN(morphMTOCRF_XFX9) {
    //
    // Supported Architecture=I_B
    //
    Uns8 FXM = state->info.FXM;
    Uns8 RS = state->info.RS;
    vmiReg GPR_RS = PPC32_GPR_RD(RS);

    //
    // If FXM has more than one bit set - this is illegal
    //
    Int32 i;
    Uns8  v = FXM;
    Uns8  cnt = 0;
    for(i=0; i<=7; i++) {
        if (v & 0x1) {
            cnt++;
        }
        v >>= 1;
    }
    if (cnt>1) {
        vmiMessage("W", "ILL_MTOCRF", "Illegal value for FXM=0x%02x", FXM);
    }
    mtcrf(FXM, GPR_RS);
}

PPC32_MORPH_FN(morphCRAND_XL1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BA = state->info.BA;
    Uns8 BB = state->info.BB;
    Uns8 BT = state->info.BT;

    ppc32crBinOpRRR(BT, BA, BB, vmi_AND);
}

PPC32_MORPH_FN(morphCRANDC_XL1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BA = state->info.BA;
    Uns8 BB = state->info.BB;
    Uns8 BT = state->info.BT;

    ppc32crBinOpRRR(BT, BA, BB, vmi_ANDN);
}

PPC32_MORPH_FN(morphCREQV_XL1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BA = state->info.BA;
    Uns8 BB = state->info.BB;
    Uns8 BT = state->info.BT;

    ppc32crBinOpRRR(BT, BA, BB, vmi_XNOR);
}

PPC32_MORPH_FN(morphCRNAND_XL1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BA = state->info.BA;
    Uns8 BB = state->info.BB;
    Uns8 BT = state->info.BT;

    ppc32crBinOpRRR(BT, BA, BB, vmi_NAND);
}

PPC32_MORPH_FN(morphCRNOR_XL1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BA = state->info.BA;
    Uns8 BB = state->info.BB;
    Uns8 BT = state->info.BT;

    ppc32crBinOpRRR(BT, BA, BB, vmi_NOR);
}

PPC32_MORPH_FN(morphCROR_XL1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BA = state->info.BA;
    Uns8 BB = state->info.BB;
    Uns8 BT = state->info.BT;

    ppc32crBinOpRRR(BT, BA, BB, vmi_OR);
}

PPC32_MORPH_FN(morphCRORC_XL1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BA = state->info.BA;
    Uns8 BB = state->info.BB;
    Uns8 BT = state->info.BT;

    ppc32crBinOpRRR(BT, BA, BB, vmi_ORN);
}

PPC32_MORPH_FN(morphCRXOR_XL1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BA = state->info.BA;
    Uns8 BB = state->info.BB;
    Uns8 BT = state->info.BT;

    ppc32crBinOpRRR(BT, BA, BB, vmi_XOR);
}

PPC32_MORPH_FN(morphE_CRAND_XL1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 BA = state->info.BA;
    // Uns8 BB = state->info.BB;
    // Uns8 BT = state->info.BT;
    // Dontcare32 X = state->info.X;

    morphCRAND_XL1(state);
}

PPC32_MORPH_FN(morphE_CRANDC_XL1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 BA = state->info.BA;
    // Uns8 BB = state->info.BB;
    // Uns8 BT = state->info.BT;
    // Dontcare32 X = state->info.X;

    morphCRANDC_XL1(state);
}

PPC32_MORPH_FN(morphE_CREQV_XL1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 BA = state->info.BA;
    // Uns8 BB = state->info.BB;
    // Uns8 BT = state->info.BT;
    // Dontcare32 X = state->info.X;

    morphCREQV_XL1(state);
}

PPC32_MORPH_FN(morphE_CRNAND_XL1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 BA = state->info.BA;
    // Uns8 BB = state->info.BB;
    // Uns8 BT = state->info.BT;
    // Dontcare32 X = state->info.X;

    morphCRNAND_XL1(state);
}

PPC32_MORPH_FN(morphE_CRNOR_XL1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 BA = state->info.BA;
    // Uns8 BB = state->info.BB;
    // Uns8 BT = state->info.BT;
    // Dontcare32 X = state->info.X;

    morphCRNOR_XL1(state);
}

PPC32_MORPH_FN(morphE_CROR_XL1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 BA = state->info.BA;
    // Uns8 BB = state->info.BB;
    // Uns8 BT = state->info.BT;
    // Dontcare32 X = state->info.X;

    morphCROR_XL1(state);
}

PPC32_MORPH_FN(morphE_CRORC_XL1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 BA = state->info.BA;
    // Uns8 BB = state->info.BB;
    // Uns8 BT = state->info.BT;
    // Dontcare32 X = state->info.X;

    morphCRORC_XL1(state);
}

PPC32_MORPH_FN(morphE_CRXOR_XL1) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 BA = state->info.BA;
    // Uns8 BB = state->info.BB;
    // Uns8 BT = state->info.BT;
    // Dontcare32 X = state->info.X;

    morphCRXOR_XL1(state);
}

PPC32_MORPH_FN(morphBCCTR_XL2) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 BH = state->info.BH;
    Uns8 BI = state->info.BI;
    Uns8 BO = state->info.BO;
    Uns8 LK = state->info.LK;

    ppc32branchc(state->info.thisPC, state->info.nextPC, BCCTR, BO, BI, 0, 0, LK);
}

PPC32_MORPH_FN(morphBCLR_XL2) {
    //
    // Supported Architecture=I_B
    //
    // Uns8 BH = state->info.BH;
    Uns8 BI = state->info.BI;
    Uns8 BO = state->info.BO;
    Uns8 LK = state->info.LK;

    ppc32branchc(state->info.thisPC, state->info.nextPC, BCLR, BO, BI, 0, 0, LK);
}

PPC32_MORPH_FN(morphE_MCRF_XL3) {
    //
    // Supported Architecture=I_VLE
    //
    // Uns8 BF = state->info.BF;
    // Uns8 BFA = state->info.BFA;
    // Dontcare32 X = state->info.X;

    morphMCRF_XL3(state);
}

PPC32_MORPH_FN(morphMCRF_XL3) {
    //
    // Supported Architecture=I_B
    //
    Uns8 BF = state->info.BF;
    Uns8 BFA = state->info.BFA;

    vmimtMoveRR(8, PPC32_LT_WR(BF), PPC32_LT_RD(BFA));
    vmimtMoveRR(8, PPC32_GT_WR(BF), PPC32_GT_RD(BFA));
    vmimtMoveRR(8, PPC32_EQ_WR(BF), PPC32_EQ_RD(BFA));
    vmimtMoveRR(8, PPC32_SO_WR(BF), PPC32_SO_RD(BFA));
}

PPC32_MORPH_FN(morphDOZE_XL4) {
    //
    // Supported Architecture=I_S
    //
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DOZE_XL4");
}

PPC32_MORPH_FN(morphHRFID_XL4) {
    //
    // Supported Architecture=I_S
    //
    CHECK_PRIV(state);

    morphUnimplemented(state, "HRFID_XL4");
}

PPC32_MORPH_FN(morphISYNC_XL4) {
    //
    // Supported Architecture=I_B
    //
    // Dontcare32 X = state->info.X;
    morphWarnNopMapping(state, "ISYNC_XL4");
}

PPC32_MORPH_FN(morphNAP_XL4) {
    //
    // Supported Architecture=I_S
    //
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "NAP_XL4");
}

PPC32_MORPH_FN(morphRFCI_XL4) {
    //
    // Supported Architecture=I_E
    //
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "RFCI_XL4");
}

static void vmic_rfi(ppc32P ppc32) {
    //
    // get SRR1 and store in MSR
    //
    Uns32 SRR1 = ppc32ReadSPR(ppc32, 27);
    ppc32WriteMSR(ppc32, SRR1);

    // Next Instruction Address SRR0;
    Addr SRR0 = ppc32ReadSPR(ppc32, 26);
    vmirtSetPC((vmiProcessorP)ppc32, SRR0);
}

PPC32_MORPH_FN(morphRFI_XL4) {
    //
    // Supported Architecture=I_E
    //
    CHECK_PRIV(state);

    vmimtArgProcessor();
    vmimtCall((vmiCallFn)vmic_rfi);
}

PPC32_MORPH_FN(morphRFID_XL4) {
    //
    // Supported Architecture=I_S
    //
    CHECK_PRIV(state);

    morphUnimplemented(state, "RFID_XL4");
}

PPC32_MORPH_FN(morphRFMCI_XL4) {
    //
    // Supported Architecture=I_E
    //
    // Dontcare32 X = state->info.X;
    CHECK_PRIV(state);

    morphUnimplemented(state, "RFMCI_XL4");
}

PPC32_MORPH_FN(morphRVWINKLE_XL4) {
    //
    // Supported Architecture=I_S
    //
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "RVWINKLE_XL4");
}

PPC32_MORPH_FN(morphSLEEP_XL4) {
    //
    // Supported Architecture=I_S
    //
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "SLEEP_XL4");
}

PPC32_MORPH_FN(morphADD_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADD, GPR_RT, GPR_RA, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphADDC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADD, GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 0, 0);
}

PPC32_MORPH_FN(morphADDCOE_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADD, GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 0, 0);
}

PPC32_MORPH_FN(morphADDCOERC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADD, GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 0, 0);
}

PPC32_MORPH_FN(morphADDCRC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADD, GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 0, 0);
}

PPC32_MORPH_FN(morphADDE_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADC, GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 1, 0);
}

PPC32_MORPH_FN(morphADDEOE_XO1) {
    //
    // Supported Architecture=I_B
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADC, GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 1, 0);
}

PPC32_MORPH_FN(morphADDEOERC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADC, GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphADDERC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADC, GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphADDOE_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADD, GPR_RT, GPR_RA, GPR_RB, 1, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphADDOERC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADD, GPR_RT, GPR_RA, GPR_RB, 1, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphADDRC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_ADD, GPR_RT, GPR_RA, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphDIVW_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32intDivOpRRR(GPR_RT, GPR_RA, GPR_RB, vmi_IDIV, 0, 0);
}

PPC32_MORPH_FN(morphDIVWOE_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32intDivOpRRR(GPR_RT, GPR_RA, GPR_RB, vmi_IDIV, 1, 0);

}

PPC32_MORPH_FN(morphDIVWOERC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32intDivOpRRR(GPR_RT, GPR_RA, GPR_RB, vmi_IDIV, 1, 1);
}

PPC32_MORPH_FN(morphDIVWRC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32intDivOpRRR(GPR_RT, GPR_RA, GPR_RB, vmi_IDIV, 0, 1);
}

PPC32_MORPH_FN(morphDIVWU_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32intDivOpRRR(GPR_RT, GPR_RA, GPR_RB, vmi_DIV, 0, 0);
}

PPC32_MORPH_FN(morphDIVWUOE_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32intDivOpRRR(GPR_RT, GPR_RA, GPR_RB, vmi_DIV, 1, 0);
}

PPC32_MORPH_FN(morphDIVWUOERC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32intDivOpRRR(GPR_RT, GPR_RA, GPR_RB, vmi_DIV, 1, 1);
}

PPC32_MORPH_FN(morphDIVWURC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32intDivOpRRR(GPR_RT, GPR_RA, GPR_RB, vmi_DIV, 0, 1);
}

PPC32_MORPH_FN(morphMACCHW_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphMACCHWOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 0);
}

PPC32_MORPH_FN(morphMACCHWOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphMACCHWRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 0);
}

PPC32_MORPH_FN(morphMACCHWS_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 1);
}

PPC32_MORPH_FN(morphMACCHWSOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 1);
}

PPC32_MORPH_FN(morphMACCHWSOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphMACCHWSRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphMACCHWSU_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 0, 0, 0, 1);
}

PPC32_MORPH_FN(morphMACCHWSUOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 1, 0, 0, 1);
}

PPC32_MORPH_FN(morphMACCHWSUOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 1, 1, 0, 1);
}

PPC32_MORPH_FN(morphMACCHWSURC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 0, 1, 0, 1);
}

PPC32_MORPH_FN(morphMACCHWU_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphMACCHWUOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphMACCHWUOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 1, 1, 0, 0);
}

PPC32_MORPH_FN(morphMACCHWURC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macc(GPR_RT, GPR_RA, GPR_RB, 0, 1, 0, 0);
}

PPC32_MORPH_FN(morphMACHHW_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphMACHHWOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 0);
}

PPC32_MORPH_FN(morphMACHHWOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphMACHHWRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 0);
}

PPC32_MORPH_FN(morphMACHHWS_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 1);
}

PPC32_MORPH_FN(morphMACHHWSOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 1);
}

PPC32_MORPH_FN(morphMACHHWSOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphMACHHWSRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphMACHHWSU_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 0, 0, 0, 1);
}

PPC32_MORPH_FN(morphMACHHWSUOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 1, 0, 0, 1);
}

PPC32_MORPH_FN(morphMACHHWSUOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 1, 1, 0, 1);
}

PPC32_MORPH_FN(morphMACHHWSURC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 0, 1, 0, 1);
}

PPC32_MORPH_FN(morphMACHHWU_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphMACHHWUOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphMACHHWUOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 1, 1, 0, 0);
}

PPC32_MORPH_FN(morphMACHHWURC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32mach(GPR_RT, GPR_RA, GPR_RB, 0, 1, 0, 0);
}

PPC32_MORPH_FN(morphMACLHW_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphMACLHWOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 0);
}

PPC32_MORPH_FN(morphMACLHWOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphMACLHWRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 0);
}

PPC32_MORPH_FN(morphMACLHWS_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 1);
}

PPC32_MORPH_FN(morphMACLHWSOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 1);
}

PPC32_MORPH_FN(morphMACLHWSOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphMACLHWSRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphMACLHWSU_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 0, 0, 0, 1);
}

PPC32_MORPH_FN(morphMACLHWSUOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 1, 0, 0, 1);
}

PPC32_MORPH_FN(morphMACLHWSUOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 1, 1, 0, 1);
}

PPC32_MORPH_FN(morphMACLHWSURC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 0, 1, 0, 1);
}

PPC32_MORPH_FN(morphMACLHWU_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphMACLHWUOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphMACLHWUOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 1, 1, 0, 0);
}

PPC32_MORPH_FN(morphMACLHWURC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32macl(GPR_RT, GPR_RA, GPR_RB, 0, 1, 0, 0);
}

PPC32_MORPH_FN(morphMULLW_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_IMUL, GPR_RT, GPR_RA, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphMULLWOE_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_IMUL, GPR_RT, GPR_RA, GPR_RB, 1, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphMULLWOERC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_IMUL, GPR_RT, GPR_RA, GPR_RB, 1, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphMULLWRC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_IMUL, GPR_RT, GPR_RA, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphNMACCHW_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacc(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphNMACCHWOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacc(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 0);
}

PPC32_MORPH_FN(morphNMACCHWOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacc(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphNMACCHWRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacc(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 0);
}

PPC32_MORPH_FN(morphNMACCHWS_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacc(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 1);
}

PPC32_MORPH_FN(morphNMACCHWSOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacc(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 1);
}

PPC32_MORPH_FN(morphNMACCHWSOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacc(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphNMACCHWSRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacc(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphNMACHHW_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmach(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphNMACHHWOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmach(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 0);
}

PPC32_MORPH_FN(morphNMACHHWOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmach(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphNMACHHWRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmach(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 0);
}

PPC32_MORPH_FN(morphNMACHHWS_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmach(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 1);
}

PPC32_MORPH_FN(morphNMACHHWSOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmach(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 1);
}

PPC32_MORPH_FN(morphNMACHHWSOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmach(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphNMACHHWSRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmach(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphNMACLHW_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacl(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 0);
}

PPC32_MORPH_FN(morphNMACLHWOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacl(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 0);
}

PPC32_MORPH_FN(morphNMACLHWOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacl(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphNMACLHWRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacl(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 0);
}

PPC32_MORPH_FN(morphNMACLHWS_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacl(GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 1);
}

PPC32_MORPH_FN(morphNMACLHWSOE_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacl(GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 1);
}

PPC32_MORPH_FN(morphNMACLHWSOERC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacl(GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphNMACLHWSRC_XO1) {
    //
    // Supported Architecture=I_LMA
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32nmacl(GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBF_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSUB, GPR_RT, GPR_RA, GPR_RB, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSUBFC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSUB, GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFCOE_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSUB, GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFCOERC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSUB, GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFCRC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSUB, GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFE_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSBB, GPR_RT, GPR_RA, GPR_RB, 0, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFEOE_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSBB, GPR_RT, GPR_RA, GPR_RB, 1, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFEOERC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSBB, GPR_RT, GPR_RA, GPR_RB, 1, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFERC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSBB, GPR_RT, GPR_RA, GPR_RB, 0, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFOE_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSUB, GPR_RT, GPR_RA, GPR_RB, 1, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphSUBFOERC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSUB, GPR_RT, GPR_RA, GPR_RB, 1, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphSUBFRC_XO1) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRR(vmi_RSUB, GPR_RT, GPR_RA, GPR_RB, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphMULHW_XO2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    // Ignore flags, this is based upon 64 bit result
    vmimtMulopRRR(PPC32_GPR_BITS, vmi_IMUL, GPR_RT, VMI_NOREG, GPR_RA, GPR_RB, 0);
}

PPC32_MORPH_FN(morphMULHWRC_XO2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    // Ignore flags, this is based upon 64 bit result
    vmimtMulopRRR(PPC32_GPR_BITS, vmi_IMUL, GPR_RT, VMI_NOREG, GPR_RA, GPR_RB, 0);

    // Generate flags for upper 32 bit result
    ppc32BinopRRC(vmi_OR, VMI_NOREG, GPR_RT, 0, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphMULHWU_XO2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    // Ignore flags, this is based upon 64 bit result
    vmimtMulopRRR(PPC32_GPR_BITS, vmi_MUL, GPR_RT, VMI_NOREG, GPR_RA, GPR_RB, 0);
}

PPC32_MORPH_FN(morphMULHWURC_XO2) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RB = state->info.RB;
    vmiReg GPR_RB = PPC32_GPR_RD(RB);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    // Ignore flags, this is based upon 64 bit result
    vmimtMulopRRR(PPC32_GPR_BITS, vmi_MUL, GPR_RT, VMI_NOREG, GPR_RA, GPR_RB, 0);

    // Generate flags for upper 32 bit result
    ppc32BinopRRC(vmi_OR, VMI_NOREG, GPR_RT, 0, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphADDG6S_XO3) {
    //
    // Supported Architecture=I_BCDA
    //
    // Uns8 RA = state->info.RA;
    // vmiReg GPR_RA = PPC32_GPR_RD(RA);
    // vmiReg GPR_RA = PPC32_GPR_WR(RA);
    // Uns8 RB = state->info.RB;
    // vmiReg GPR_RB = PPC32_GPR_RD(RB);
    // vmiReg GPR_RB = PPC32_GPR_WR(RB);
    // Uns8 RT = state->info.RT;
    // vmiReg GPR_RT = PPC32_GPR_RD(RT);
    // vmiReg GPR_RT = PPC32_GPR_WR(RT);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "ADDG6S_XO3");
}

PPC32_MORPH_FN(morphADDME_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_ADC, GPR_RT, GPR_RA, -1, 0, 0, 1, 1, 0);

}

PPC32_MORPH_FN(morphADDMEOE_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_ADC, GPR_RT, GPR_RA, -1, 1, 0, 1, 1, 0);
}

PPC32_MORPH_FN(morphADDMEOERC_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_ADC, GPR_RT, GPR_RA, -1, 1, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphADDMERC_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_ADC, GPR_RT, GPR_RA, -1, 0, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphADDZE_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_ADC, GPR_RT, GPR_RA, 0, 0, 0, 1, 1, 0);
}

PPC32_MORPH_FN(morphADDZEOE_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_ADC, GPR_RT, GPR_RA, 0, 1, 0, 1, 1, 0);
}

PPC32_MORPH_FN(morphADDZEOERC_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_ADC, GPR_RT, GPR_RA, 0, 1, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphADDZERC_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_ADC, GPR_RT, GPR_RA, 0, 0, 1, 1, 1, 0);
}

PPC32_MORPH_FN(morphNEG_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32UnopRR(vmi_NEG, GPR_RT, GPR_RA, 0, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphNEGOE_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32UnopRR(vmi_NEG, GPR_RT, GPR_RA, 1, 0, 0, 0, 0);
}

PPC32_MORPH_FN(morphNEGOERC_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32UnopRR(vmi_NEG, GPR_RT, GPR_RA, 1, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphNEGRC_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32UnopRR(vmi_NEG, GPR_RT, GPR_RA, 0, 1, 0, 0, 0);
}

PPC32_MORPH_FN(morphSUBFME_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_RSBB, GPR_RT, GPR_RA, -1, 0, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFMEOE_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_RSBB, GPR_RT, GPR_RA, -1, 1, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFMEOERC_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_RSBB, GPR_RT, GPR_RA, -1, 1, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFMERC_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_RSBB, GPR_RT, GPR_RA, -1, 0, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFZE_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_RSBB, GPR_RT, GPR_RA, 0, 0, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFZEOE_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_RSBB, GPR_RT, GPR_RA, 0, 1, 0, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFZEOERC_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_RSBB, GPR_RT, GPR_RA, 0, 1, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphSUBFZERC_XO4) {
    //
    // Supported Architecture=I_B
    //
    Uns8 RA = state->info.RA;
    vmiReg GPR_RA = PPC32_GPR_RD(RA);
    Uns8 RT = state->info.RT;
    vmiReg GPR_RT = PPC32_GPR_WR(RT);

    ppc32BinopRRC(vmi_RSBB, GPR_RT, GPR_RA, 0, 0, 1, 1, 1, 1);
}

PPC32_MORPH_FN(morphDTSTDC_Z22_1) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 DCM = state->info.DCM;
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DTSTDC_Z22_1");
}

PPC32_MORPH_FN(morphDTSTDG_Z22_1) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 DCM = state->info.DCM;
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DTSTDG_Z22_1");
}

PPC32_MORPH_FN(morphDTSTDCQ_Z22_2) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 DCM = state->info.DCM;
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DTSTDCQ_Z22_2");
}

PPC32_MORPH_FN(morphDTSTDGQ_Z22_2) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 BF = state->info.BF;
    // Uns8 DCM = state->info.DCM;
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DTSTDGQ_Z22_2");
}

PPC32_MORPH_FN(morphDSCLI_Z22_5) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 SH = state->info.SH;
    morphUnimplemented(state, "DSCLI_Z22_5");
}

PPC32_MORPH_FN(morphDSCLIRC_Z22_5) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 SH = state->info.SH;
    morphUnimplemented(state, "DSCLIRC_Z22_5");
}

PPC32_MORPH_FN(morphDSCRI_Z22_5) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 SH = state->info.SH;
    morphUnimplemented(state, "DSCRI_Z22_5");
}

PPC32_MORPH_FN(morphDSCRIRC_Z22_5) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 SH = state->info.SH;
    morphUnimplemented(state, "DSCRIRC_Z22_5");
}

PPC32_MORPH_FN(morphDSCLIQ_Z22_6) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 SH = state->info.SH;
    morphUnimplemented(state, "DSCLIQ_Z22_6");
}

PPC32_MORPH_FN(morphDSCLIQRC_Z22_6) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 SH = state->info.SH;
    morphUnimplemented(state, "DSCLIQRC_Z22_6");
}

PPC32_MORPH_FN(morphDSCRIQ_Z22_6) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 SH = state->info.SH;
    morphUnimplemented(state, "DSCRIQ_Z22_6");
}

PPC32_MORPH_FN(morphDSCRIQRC_Z22_6) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRAp = state->info.FRAp;
    // vmiReg FPR_FRAp = PPC32_FPR_RD(FRAp);
    // vmiReg FPR_FRAp = PPC32_FPR_WR(FRAp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 SH = state->info.SH;
    morphUnimplemented(state, "DSCRIQRC_Z22_6");
}

PPC32_MORPH_FN(morphDQUAI_Z23_1) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RMC = state->info.RMC;
    // Int8 TE = state->info.TE;
    morphUnimplemented(state, "DQUAI_Z23_1");
}

PPC32_MORPH_FN(morphDQUAIRC_Z23_1) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RMC = state->info.RMC;
    // Int8 TE = state->info.TE;
    morphUnimplemented(state, "DQUAIRC_Z23_1");
}

PPC32_MORPH_FN(morphDQUAIQ_Z23_2) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 RMC = state->info.RMC;
    // Int8 TE = state->info.TE;
    morphUnimplemented(state, "DQUAIQ_Z23_2");
}

PPC32_MORPH_FN(morphDQUAIQRC_Z23_2) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 RMC = state->info.RMC;
    // Int8 TE = state->info.TE;
    morphUnimplemented(state, "DQUAIQRC_Z23_2");
}

PPC32_MORPH_FN(morphDQUA_Z23_3) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RMC = state->info.RMC;
    morphUnimplemented(state, "DQUA_Z23_3");
}

PPC32_MORPH_FN(morphDQUAQ_Z23_3) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RMC = state->info.RMC;
    morphUnimplemented(state, "DQUAQ_Z23_3");
}

PPC32_MORPH_FN(morphDQUAQRC_Z23_3) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RMC = state->info.RMC;
    morphUnimplemented(state, "DQUAQRC_Z23_3");
}

PPC32_MORPH_FN(morphDQUARC_Z23_3) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RMC = state->info.RMC;
    morphUnimplemented(state, "DQUARC_Z23_3");
}

PPC32_MORPH_FN(morphDRRND_Z23_3) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RMC = state->info.RMC;
    morphUnimplemented(state, "DRRND_Z23_3");
}

PPC32_MORPH_FN(morphDRRNDQ_Z23_3) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RMC = state->info.RMC;
    morphUnimplemented(state, "DRRNDQ_Z23_3");
}

PPC32_MORPH_FN(morphDRRNDQRC_Z23_3) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RMC = state->info.RMC;
    morphUnimplemented(state, "DRRNDQRC_Z23_3");
}

PPC32_MORPH_FN(morphDRRNDRC_Z23_3) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRA = state->info.FRA;
    // vmiReg FPR_FRA = PPC32_FPR_RD(FRA);
    // vmiReg FPR_FRA = PPC32_FPR_WR(FRA);
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 RMC = state->info.RMC;
    morphUnimplemented(state, "DRRNDRC_Z23_3");
}

PPC32_MORPH_FN(morphDRINTN_Z23_6) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 R = state->info.R;
    // Uns8 RMC = state->info.RMC;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRINTN_Z23_6");
}

PPC32_MORPH_FN(morphDRINTNRC_Z23_6) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 R = state->info.R;
    // Uns8 RMC = state->info.RMC;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRINTNRC_Z23_6");
}

PPC32_MORPH_FN(morphDRINTX_Z23_6) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 R = state->info.R;
    // Uns8 RMC = state->info.RMC;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRINTX_Z23_6");
}

PPC32_MORPH_FN(morphDRINTXRC_Z23_6) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRB = state->info.FRB;
    // vmiReg FPR_FRB = PPC32_FPR_RD(FRB);
    // vmiReg FPR_FRB = PPC32_FPR_WR(FRB);
    // Uns8 FRT = state->info.FRT;
    // vmiReg FPR_FRT = PPC32_FPR_RD(FRT);
    // vmiReg FPR_FRT = PPC32_FPR_WR(FRT);
    // Uns8 R = state->info.R;
    // Uns8 RMC = state->info.RMC;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRINTXRC_Z23_6");
}

PPC32_MORPH_FN(morphDRINTNQ_Z23_7) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 R = state->info.R;
    // Uns8 RMC = state->info.RMC;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRINTNQ_Z23_7");
}

PPC32_MORPH_FN(morphDRINTNQRC_Z23_7) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 R = state->info.R;
    // Uns8 RMC = state->info.RMC;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRINTNQRC_Z23_7");
}

PPC32_MORPH_FN(morphDRINTXQ_Z23_7) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 R = state->info.R;
    // Uns8 RMC = state->info.RMC;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRINTXQ_Z23_7");
}

PPC32_MORPH_FN(morphDRINTXQRC_Z23_7) {
    //
    // Supported Architecture=I_DFP
    //
    // Uns8 FRBp = state->info.FRBp;
    // vmiReg FPR_FRBp = PPC32_FPR_RD(FRBp);
    // vmiReg FPR_FRBp = PPC32_FPR_WR(FRBp);
    // Uns8 FRTp = state->info.FRTp;
    // vmiReg FPR_FRTp = PPC32_FPR_RD(FRTp);
    // vmiReg FPR_FRTp = PPC32_FPR_WR(FRTp);
    // Uns8 R = state->info.R;
    // Uns8 RMC = state->info.RMC;
    // Dontcare32 X = state->info.X;
    morphUnimplemented(state, "DRINTXQRC_Z23_7");
}


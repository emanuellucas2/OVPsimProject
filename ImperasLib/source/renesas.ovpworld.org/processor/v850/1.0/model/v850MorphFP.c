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
#include "v850Functions.h"
#include "v850Instructions.h"
#include "v850Morph.h"
#include "v850MorphFP.h"
#include "v850Utils.h"

static void unimplemented(const char *name) {
    vmiMessage("F", "MORPH_UNIMP", "Instruction %s unimplemented", name);
}

static __attribute__((unused)) void morphUnimplemented(const char *name) {
    vmimtArgNatAddress(name);
    vmimtCall((vmiCallFn)unimplemented);
    vmimtExit();
}

//
// Emit code to set the sticky flags
//
inline static void emitSetSticky(vmiReg flags) {
    //
    // FP_STICKY |= flags
    // TR generated on demand in v850PackEFG
    vmimtBinopRR(V850_FLG_FPF_STICKY_BITS, vmi_OR, V850_FLG_FPF_STICKY_WR, flags, 0);
}

//
// Emit code for generic FPU (single) unop
//
static void emitFPUnopE1(v850MorphStateP state, vmiReg rB, vmiReg rD, vmiFBinop op) {

    // do the binary operation - following actions may not be done if there is
    // a floating-point exception
    vmimtFUnopRR(vmi_FT_32_IEEE_754, op, rD, rB, V850_FLG_FPF_WR, 0);

    //
    // If Denormal flag is set, overwrite the target register with V850_QNAN_32
    //
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(0), V850_FLG_FPF_RD, FPFLAGS_D, 0);
    vmimtCondMoveRCR(V850_GPR_BITS, V850_TMP_RD(0), FPFLAGS_D, rD, V850E1_FP32_QNAN, rD);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);
}

static void vmic_emitFPConvE1(v850P v850, Uns32 rB, Uns32 rD) {
    Uns32 arg = v850->gpr[rB];

    if        (v850->FLG_FPF & FPFLAGS_P) {
        //
        // Do nothing
        //
    } else if (v850->FLG_FPF & FPFLAGS_I) {
        // Note - do not write to gpr[rD] if rD == 0
        if (IS_V850_FP32_NAN(arg)) {
            if (rD) v850->gpr[rD] = V850_FP32_MINUS_ZERO;
            v850->FLG_FPF |= FPFLAGS_D;

        } else if (IS_V850_FP32_INF(arg)) {
            if (V850_FP32_SIGN(arg)) {
                if (rD) v850->gpr[rD] = V850_INT32_MIN;
            } else {
                if (rD) v850->gpr[rD] = V850_INT32_MAX;
            }
            v850->FLG_EFG_FPOV = 1;
            v850->FLG_FPF |= FPFLAGS_D;

        } else {
            if (V850_FP32_SIGN(arg)) {
                if (rD) v850->gpr[rD] = V850_INT32_MIN;
            } else {
                if (rD) v850->gpr[rD] = V850_INT32_MAX;
                v850->FLG_EFG_FPOV = 1;
            }
        }

    } else if (v850->FLG_FPF & FPFLAGS_D) {
        if (rD) v850->gpr[rD] = V850_FP32_MINUS_ZERO;

    } else {
        vmiMessage("F", "vmic_emitFPConvE1", "Flag ?");
    }
}

//
// Emit code for generic FPU Convert
//
static void emitFPConvE1(v850MorphStateP state, vmiReg rB, Uns32 rBi, vmiFType tB, vmiReg rD, Uns32 rDi, vmiFType tD, vmiFPRC rc) {

    vmiLabelP normalOperands = vmimtNewLabel();

    // Clear The overflow to allow it to be set by the callback
    vmimtMoveRC(V850_FLG_EFG_FPOV_BITS, V850_FLG_EFG_FPOV_WR, 0);

    // do the binary operation - following actions may not be done if there is
    // a floating-point exception
    vmimtFConvertRR(tD, rD, tB, rB, rc, V850_FLG_FPF_WR, 0);

    //
    // If flags are zero jump to normalOperands
    //
    vmimtCondJumpLabel(V850_FLG_FPF_RD, False, normalOperands);
    vmimtArgProcessor();
    vmimtArgUns32(rBi);
    vmimtArgUns32(rDi);
    vmimtCall((vmiCallFn)vmic_emitFPConvE1);

    //  set sticky flags from fpuFlag value
    vmimtInsertLabel(normalOperands);
    emitSetSticky(V850_FLG_FPF_RD);
}

//
// Emit code for generic FPU binop (single)
//
static void emitFPBinopE1(v850MorphStateP state, vmiReg rA, vmiReg rB, vmiReg rD, vmiFBinop op) {

    // do the binary operation - following actions may not be done if there is
    // a floating-point exception
    vmimtFBinopRRR(vmi_FT_32_IEEE_754, op, rD, rB, rA, V850_FLG_FPF_WR, 0);

    //
    // If Denormal flag is set, overwrite the target register with V850_QNAN_32
    //
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(0), V850_FLG_FPF_RD, FPFLAGS_D, 0);
    vmimtCondMoveRCR(V850_GPR_BITS, V850_TMP_RD(0), FPFLAGS_D, rD, V850E1_FP32_QNAN, rD);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);
}

//
// Emit code for generic FPU compare
//
static void emitFPCompareE1(v850MorphStateP state, vmiReg rA, vmiReg rB, vmiReg rD, vmiFPRelation relation) {
    // do the compare operation - result held in V850_TMP_WR
    vmimtFCompareRR(vmi_FT_32_IEEE_754, V850_TMP_WR(0), rA, rB, V850_FLG_FPF_WR, True, 0);

    // if gpr1 cond gpr2 => gpr3 = gpr1
    // else              gpr3 = gpr2
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(1), V850_TMP_RD(0), relation, 0);
    vmimtCondMoveRRR(V850_GPR_BITS, V850_TMP_RD(1), relation, rD, rA, rB);

    // if Result is UNORDERED, set to V850_QNAN_32
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(1), V850_TMP_RD(0), vmi_FPRL_UNORDERED, 0);
    vmimtCondMoveRCR(V850_GPR_BITS, V850_TMP_RD(1), vmi_FPRL_UNORDERED, rD, V850E1_FP32_QNAN, rD);

    //
    // If Denormal flag is set, overwrite the target register with V850_QNAN_32
    //
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(2), V850_FLG_FPF_RD, FPFLAGS_D, 0);
    vmimtCondMoveRCR(V850_GPR_BITS, V850_TMP_RD(2), FPFLAGS_D, rD, V850E1_FP32_QNAN, rD);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);

}

static void emitFPFlagsE1(v850MorphStateP state, vmiReg rD, Bool Z, Bool S) {
    if (Z) {
        //
        // If -ve Zero or +ve Zero, set the Z flag
        // ignore MSB sign = 0x80000000 0x00000000
        //
        vmimtTestRC(32, vmi_COND_Z, rD, 0x7fffffff, V850_FLG_EFG_FPZ_WR);
    }
    if (S) {
        //
        // If -ve, set the S flag
        //
        vmimtTestRC(32, vmi_COND_NZ, rD, 0x80000000, V850_FLG_EFG_FPS_WR);
    }
}

//
// Emit code for generic FPU (single/double) unop
//
static void emitFPUnopE2(v850MorphStateP state, vmiFType ftype, vmiReg rB, vmiReg rD, vmiFBinop op, vmiFPConfigCP config) {

    // do the binary operation - following actions may not be done if there is
    // a floating-point exception
    vmimtFUnopRR(ftype, op, rD, rB, V850_FLG_FPF_WR, config);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);
}

//
// Emit code for generic FPU (single/double) binop
//
static void emitFPBinopE2(v850MorphStateP state, vmiFType ftype, vmiReg rA, vmiReg rB, vmiReg rD, vmiFBinop op, vmiFPConfigCP config) {

    // do the binary operation - following actions may not be done if there is
    // a floating-point exception
    vmimtFBinopRRR(ftype, op, rD, rB, rA, V850_FLG_FPF_WR, config);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);
}

//
// Emit code for FPU Convert (single/double)
//
static void emitFPConvE2(vmiFType tA, vmiReg rA, vmiFType tD, vmiReg rD, vmiFPRC rc, vmiFPConfigCP config) {
    vmimtFConvertRR(tD, rD, tA, rA, rc, V850_FLG_FPF_WR, config);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);
}

//
// Special handling for Unsigned
//
static void emitFPConvE2uns(vmiFType tA, vmiReg rA, vmiFType tD, vmiReg rD, vmiFPRC rc, vmiFPConfigCP config) {
    Uns8 rAsize = 0;
    Uns64 CONDVAR1 = 0;
    Uns64 CONDVAR2 = 0;

    if (tA == vmi_FT_32_IEEE_754) {
        rAsize = V850_GPR_BITS;
        CONDVAR1 = V850_FP32_MINUS_ZERO;
        CONDVAR2 = V850_UNS32_MIN;

    } else if (tA == vmi_FT_64_IEEE_754) {
        rAsize = V850_GPR_BITS*2;
        CONDVAR1 = V850_FP64_MINUS_ZERO;
        CONDVAR2 = V850_UNS64_MIN;

    } else {
        vmiMessage("F", "CEILF_DU", "Unsupported type %d", tA);
    }

    //
    // Single/Double to Unsigned
    //
    vmimtMoveRR(rAsize, V850_TMP_WR(0), rA);
    emitFPConvE2(tA, rA, tD, rD, rc, config);

    //
    // If reg2 was -ve but not -0,
    // then
    //   set the [V] flag [inValid]
    //   (Unset Precision [I] Inexact
    //
    vmiLabelP skip = vmimtNewLabel();
    vmimtCompareRCJumpLabel(rAsize, vmi_COND_EQ, V850_TMP_RD(0), CONDVAR1, skip); // == -0 -> skip
    vmimtCompareRCJumpLabel(rAsize, vmi_COND_NS, V850_TMP_RD(0), CONDVAR2, skip); // !signed -> skip

    vmimtBinopRC(8, vmi_OR,  V850_FLG_FPF_WR, FPFLAGS_I,    0);
    vmimtBinopRC(8, vmi_AND, V850_FLG_FPF_WR, ~(FPFLAGS_P), 0);
    emitSetSticky(V850_FLG_FPF_RD);

    vmimtInsertLabel(skip);
}

static vmiReg emitTargetReg(vmiReg rD) {
    if (VMI_ISNOREG(rD)) {
        rD = V850_TMP_WR(1);
        vmimtMoveRC(V850_GPR_BITS, rD, 0);
    }
    return rD;
}

//
// Single Precision E1F format
//

V850_MORPH_FN(morphADDF_S_FI) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmiReg rD = emitTargetReg(gpr_reg3);

    emitFPBinopE1(state, gpr_reg1, gpr_reg2, rD, vmi_FADD);
    emitFPFlagsE1(state, rD, True, True);
}

V850_MORPH_FN(morphDIVF_S_FI) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    //
    // Supported Architecture=V850E1_SP_FPU
    // reg3 = reg2 / reg1
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmiReg rD = emitTargetReg(gpr_reg3);

    emitFPBinopE1(state, gpr_reg1, gpr_reg2, rD, vmi_FDIV);
    emitFPFlagsE1(state, rD, True, True);
}

V850_MORPH_FN(morphMAXF_S_FI) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmiLabelP label1 = vmimtNewLabel();
    vmiLabelP label2 = vmimtNewLabel();
    vmiLabelP label3 = vmimtNewLabel();

    //
    // Need to handle special case of max(-0(0x80000000),+0(0x00000000)) = +0
    // Need to handle special case of max(-0(0x80000000),-0(0x80000000)) = -0
    //  r1            r2              r1            r2
    // (0x80000000 && 0x80000000) || (0x80000000 && 0x800000000) = -0
    // (0x80000000 && 0x00000000) || (0x00000000 && 0x800000000) = +0
    //
    //   tmp(0) = (rA | rB) & ~(V850_FP32_MINUS_ZERO)
    //   tmp(1) = (rA & rB)
    //   if tmp(0) != 0
    //     rD = emitFPCompareE1()
    //   else
    //L1:   if tmp(1) != 0
    //       rD = V850_FP32_MINUS_ZERO
    //     else
    //L2:     rD = V850_FP32_PLUS_ZERO
    //     fi
    //   fi
    //L3:

    vmimtBinopRRR(V850_GPR_BITS, vmi_OR, V850_TMP_WR(0), gpr_reg1, gpr_reg2, 0);
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(0), V850_TMP_RD(0), ~(V850_FP32_MINUS_ZERO), 0);

    // if tmp(0) != 0
    vmimtCompareRC(V850_GPR_BITS, vmi_COND_EQ, V850_TMP_RD(0), 0, V850_FLG_TMP_WR);
    vmimtCondJumpLabel(V850_FLG_TMP_RD, True, label1);
    emitFPCompareE1(state, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FPRL_GREATER);
    vmimtUncondJumpLabel(label3);

    //L1:   if tmp(1) != 0
    vmimtInsertLabel(label1);
    vmimtBinopRRR(V850_GPR_BITS, vmi_AND, V850_TMP_WR(0), gpr_reg1, gpr_reg2, 0);
    vmimtCompareRC(V850_GPR_BITS, vmi_COND_EQ, V850_TMP_RD(0), 0, V850_FLG_TMP_WR);
    vmimtCondJumpLabel(V850_FLG_TMP_RD, True, label2);
    vmimtMoveRC(V850_GPR_BITS, gpr_reg3, V850_FP32_MINUS_ZERO);
    vmimtUncondJumpLabel(label3);

    //     else
    vmimtInsertLabel(label2);
    vmimtMoveRC(V850_GPR_BITS, gpr_reg3, V850_FP32_PLUS_ZERO);

    // end
    vmimtInsertLabel(label3);
    emitFPFlagsE1(state, gpr_reg3, True, True);
}

V850_MORPH_FN(morphMINF_S_FI) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmiLabelP label1 = vmimtNewLabel();
    vmiLabelP label2 = vmimtNewLabel();

    //
    // Need to handle special case of min(-0(0x80000000),+0(0x00000000)) => -0
    // tmp = rA | rB
    // if (tmp == V850_FP32_MINUS_ZERO)
    //   rD = V850_FP32_MINUS_ZERO
    // else
    //   rD = emitFPCompareE1()
    //
    vmimtBinopRRR(V850_GPR_BITS, vmi_OR, V850_TMP_WR(0), gpr_reg1, gpr_reg2, 0);
    vmimtCompareRC(V850_GPR_BITS, vmi_COND_EQ, V850_TMP_RD(0), V850_FP32_MINUS_ZERO, V850_FLG_TMP_WR);
    vmimtCondJumpLabel(V850_FLG_TMP_RD, True, label1);

    // Calculate the result
    emitFPCompareE1(state, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FPRL_LESS);
    vmimtUncondJumpLabel(label2);

    // commit the result
    vmimtInsertLabel(label1);
    vmimtMoveRC(V850_GPR_BITS, gpr_reg3, V850_FP32_MINUS_ZERO);

    vmimtInsertLabel(label2);
    emitFPFlagsE1(state, gpr_reg3, True, True);
}

V850_MORPH_FN(morphMULF_S_FI) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmiReg rD = emitTargetReg(gpr_reg3);

    emitFPBinopE1(state, gpr_reg1, gpr_reg2, rD, vmi_FMUL);
    emitFPFlagsE1(state, rD, True, True);
}


V850_MORPH_FN(morphSUBF_S_FI) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmiReg rD = emitTargetReg(gpr_reg3);

    emitFPBinopE1(state, gpr_reg1, gpr_reg2, rD, vmi_FSUB);
    emitFPFlagsE1(state, rD, True, True);
}

//
// Double Precision E1F format
//

V850_MORPH_FN(morphADDF_D_FID) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_64_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FADD, 0);
}

/*
 * TODO:
 * Condition query
 * divf.d   r20, r16, r22
 * R20=7fefffffffffffff
 * R16=43d0000000000000
 *
 * Result=03d0000000000001
 * Exp   =03d0000000000000
 */
V850_MORPH_FN(morphDIVF_D_FID) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_64_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FDIV, 0);
}

V850_MORPH_FN(morphMAXF_D_FID) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_64_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FMAX, 0);
}

V850_MORPH_FN(morphMINF_D_FID) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_64_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FMIN, 0);
}

V850_MORPH_FN(morphMULF_D_FID) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_64_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FMUL, 0);
}

V850_MORPH_FN(morphSUBF_D_FID) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_64_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FSUB, 0);
}

V850_MORPH_FN(morphCEILF_DW_FIDSR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_32_INT, gpr_reg3, vmi_FPR_POS_INF, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphCVTF_DS_FIDSR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_32_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}

V850_MORPH_FN(morphCVTF_DUW_FIDSR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_32_UNS, gpr_reg3, vmi_FPR_CURRENT, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphCVTF_DW_FIDSR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    //
    // Refer to conditions on P210
    //
    emitFPConvE2(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_32_INT, gpr_reg3, vmi_FPR_CURRENT, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphCVTF_LS_FIDSR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    //
    // Refer to conditions on P210
    //
    emitFPConvE2(vmi_FT_64_INT, gpr_reg2, vmi_FT_32_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}

V850_MORPH_FN(morphCVTF_ULS_FIDSR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    //
    // Refer to conditions on P210
    //
    emitFPConvE2(vmi_FT_64_UNS, gpr_reg2, vmi_FT_32_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}

static void CMOVF(Uns8 fff, vmiReg r1, vmiReg r2, vmiReg r3, Uns8 size) {
    //
    // Test V850_FLG_FPSR_CC_WR(fff)
    // if (cc==1) r3 <- r1
    // else       r3 <- r2
    //
    vmiLabelP E1 = vmimtNewLabel();
    vmiLabelP F1 = vmimtNewLabel();
    vmimtCompareRCJumpLabel(8, vmi_COND_EQ, V850_FLG_FPSR_CC_WR(fff), 0, F1);
    vmimtMoveRR(size, r3, r1);
    vmimtUncondJumpLabel(E1);

    vmimtInsertLabel(F1);
    vmimtMoveRR(size, r3, r2);

    vmimtInsertLabel(E1);
}

V850_MORPH_FN(morphCMOVF_D_FIDFFF) {
    //
    // Supported Architecture=ISA_E2_DPFP
    //
    Uns8 fff = state->info.fff;
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    CMOVF(fff, gpr_reg1, gpr_reg2, gpr_reg3, V850_GPR_BITS*2);
}

V850_MORPH_FN(morphFLOORF_DW_FIDSR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_32_INT, gpr_reg3, vmi_FPR_NEG_INF, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphTRNCF_DW_FIDSR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_32_INT, gpr_reg3, vmi_FPR_ZERO, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

static void cmpf(v850MorphStateP state, vmiFType ftype) {
    Uns8 cond = state->info.cond;
    Uns8 fff  = state->info.fff;
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);

    Bool allowQNaN  = (cond & 0x8) ? 0 : 1;
    Uns8 condvar    = cond & 0x7;

    // Generate the relation/cond
    // RELOP(VMI) = GT, LT, EQ, UN
    // COND(V850) = IV, LT, EQ, UN
    // IV indicates Signalling
    vmimtFCompareRR(ftype, V850_FLG_FCMP_WR, gpr_reg2, gpr_reg1, V850_FLG_FPF_WR, allowQNaN, 0);

    //
    // If a NAN was propagated, this remaining code is not executed, and the signal
    // handler is called
    //

    // set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);

    // FLG_FPSR_CC[fff] = (V850_FLG_FCMP_WR & cond) ? 1 : 0;
    // update field of FPSR/CC Temporary
    vmimtTestRC(8, vmi_COND_NZ, V850_FLG_FCMP_RD, condvar, V850_FLG_FPSR_CC_WR(fff));
}

V850_MORPH_FN(morphCMPF_D_FIDCOND) {
    //
    // Supported Architecture=ISA_E2_DPFP
    //
    cmpf(state, vmi_FT_64_IEEE_754);
}

//
// If the operand is S-NaN, an IEEE754-defined invalid operation exception (V)
// S-NaN converted to Q-NaN and [V] generated
//
V850_MORPH_FN(morphABSF_D_FIDR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPUnopE2(state, vmi_FT_64_IEEE_754, gpr_reg2, gpr_reg3, vmi_FABS, 0);
}

V850_MORPH_FN(morphCEILF_DL_FIDR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    //
    // Refer to conditions on P210
    //
    emitFPConvE2(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_64_INT, gpr_reg3, vmi_FPR_POS_INF, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphCEILF_DUL_FIDR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    //
    // Refer to conditions on P211
    //
    emitFPConvE2uns(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_64_UNS, gpr_reg3, vmi_FPR_POS_INF, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphCEILF_DUW_FIDR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    //
    // Refer to conditions on P212
    //
    emitFPConvE2uns(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_32_UNS, gpr_reg3, vmi_FPR_POS_INF, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphCVTF_DL_FIDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_64_INT, gpr_reg3, vmi_FPR_CURRENT, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphCVTF_DUL_FIDR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_64_UNS, gpr_reg3, vmi_FPR_CURRENT, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphCVTF_ULD_FIDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_64_UNS, gpr_reg2, vmi_FT_64_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}

V850_MORPH_FN(morphFLOORF_DL_FIDR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_64_INT, gpr_reg3, vmi_FPR_NEG_INF, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphFLOORF_DUL_FIDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_64_UNS, gpr_reg3, vmi_FPR_NEG_INF, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphFLOORF_DUW_FIDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_32_UNS, gpr_reg3, vmi_FPR_NEG_INF, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphNEGF_D_FIDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPUnopE2(state, vmi_FT_64_IEEE_754, gpr_reg2, gpr_reg3, vmi_FNEG, 0);
}

V850_MORPH_FN(morphRECIPF_D_FIDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPUnopE2(state, vmi_FT_64_IEEE_754, gpr_reg2, gpr_reg3, vmi_FRECIP, 0);
}

/*
 * TODO:
 * Condition query
 * sqrtf.d  r20, r16
 * R20=7fefffffffffffff
 *
 * Result=5fefffffffffffff
 * Exp   =5ff0000000000000
 */
V850_MORPH_FN(morphRSQRTF_D_FIDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPUnopE2(state, vmi_FT_64_IEEE_754, gpr_reg2, gpr_reg3, vmi_FRSQRT, 0);
}

V850_MORPH_FN(morphSQRTF_D_FIDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPUnopE2(state, vmi_FT_64_IEEE_754, gpr_reg2, gpr_reg3, vmi_FSQRT, 0);
}

V850_MORPH_FN(morphTRNCF_DL_FIDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_64_INT, gpr_reg3, vmi_FPR_ZERO, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphTRNCF_DUL_FIDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_64_UNS, gpr_reg3, vmi_FPR_ZERO, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphTRNCF_DUW_FIDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_64_IEEE_754, gpr_reg2, vmi_FT_32_UNS, gpr_reg3, vmi_FPR_ZERO, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphABSF_S_FII) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPUnopE1(state, gpr_reg2, gpr_reg3, vmi_FABS);
    emitFPFlagsE1(state, gpr_reg3, True, True);
}

V850_MORPH_FN(morphCVT_SW_FII) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE1(state, gpr_reg2, reg2, vmi_FT_32_IEEE_754, gpr_reg3, reg3, vmi_FT_32_INT, vmi_FPR_NEAREST);
    emitFPFlagsE1(state, gpr_reg3, True, True);
}

V850_MORPH_FN(morphCVT_WS_FII) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE1(state, gpr_reg2, reg2, vmi_FT_32_INT, gpr_reg3, reg3, vmi_FT_32_IEEE_754, vmi_FPR_NEAREST);
    emitFPFlagsE1(state, gpr_reg3, True, True);
}

V850_MORPH_FN(morphNEGF_S_FII) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
     Uns8 reg2 = state->info.reg2;
     vmiReg gpr_reg2 = V850_GPR_RD(reg2);
     Uns8 reg3 = state->info.reg3;
     vmiReg gpr_reg3 = V850_GPR_WR(reg3);

     emitFPUnopE1(state, gpr_reg2, gpr_reg3, vmi_FNEG);
     emitFPFlagsE1(state, gpr_reg3, True, True);
}

V850_MORPH_FN(morphTRNC_SW_FII) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE1(state, gpr_reg2, reg2, vmi_FT_32_IEEE_754, gpr_reg3, reg3, vmi_FT_32_INT, vmi_FPR_ZERO);
    emitFPFlagsE1(state, gpr_reg3, True, True);
}

V850_MORPH_FN(morphADDF_S_FIS) {
    //
    // Supported Architecture=V850E2_SP_FPU
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_32_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FADD, 0);
}

V850_MORPH_FN(morphDIVF_S_FIS) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_32_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FDIV, 0);
}

V850_MORPH_FN(morphMAXF_S_FIS) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_32_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FMAX, 0);
}

V850_MORPH_FN(morphMINF_S_FIS) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_32_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FMIN, 0);
}

V850_MORPH_FN(morphMULF_S_FIS) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_32_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FMUL, 0);
}

V850_MORPH_FN(morphSUBF_S_FIS) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPBinopE2(state, vmi_FT_32_IEEE_754, gpr_reg1, gpr_reg2, gpr_reg3, vmi_FSUB, 0);
}

V850_MORPH_FN(morphCEILF_SL_FISDR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_64_INT, gpr_reg3, vmi_FPR_POS_INF, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphCEILF_SUL_FISDR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_64_UNS, gpr_reg3, vmi_FPR_POS_INF, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphCVTF_SD_FISDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_64_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}

V850_MORPH_FN(morphCVTF_SL_FISDR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_64_INT, gpr_reg3, vmi_FPR_CURRENT, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphCVTF_SUL_FISDR2R3) {
    //
    // Supported Architecture=V850E2_DP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_64_UNS, gpr_reg3, vmi_FPR_CURRENT, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphCVTF_UWD_FISDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_UNS, gpr_reg2, vmi_FT_64_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}

V850_MORPH_FN(morphCVTF_WD_FISDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_INT, gpr_reg2, vmi_FT_64_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}

V850_MORPH_FN(morphFLOORF_SL_FISDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_64_INT, gpr_reg3, vmi_FPR_NEG_INF, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphFLOORF_SUL_FISDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_64_UNS, gpr_reg3, vmi_FPR_NEG_INF, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphTRNCF_SL_FISDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_64_INT, gpr_reg3, vmi_FPR_ZERO, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphTRNCF_SUL_FISDR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_64_UNS, gpr_reg3, vmi_FPR_ZERO, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphMADDF_S_FISA) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_RD(reg3);
    Uns8 reg4 = state->info.reg4;
    vmiReg gpr_reg4 = V850_GPR_WR(reg4);

    //
    // r4 = (reg2 * reg1) + reg3
    // Do not round intermediate result
    //
    vmimtFTernopRRRR(vmi_FT_32_IEEE_754, vmi_FMADD, gpr_reg4, gpr_reg2, gpr_reg1, gpr_reg3, V850_FLG_FPF_WR, False, 0);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);
}

V850_MORPH_FN(morphMSUBF_S_FISA) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_RD(reg3);
    Uns8 reg4 = state->info.reg4;
    vmiReg gpr_reg4 = V850_GPR_WR(reg4);

    //
    // r4 = neg((reg2 * reg1) - reg3)
    // Do not round intermediate result
    //
    vmimtFTernopRRRR(vmi_FT_32_IEEE_754, vmi_FMSUB, gpr_reg4, gpr_reg2, gpr_reg1, gpr_reg3, V850_FLG_FPF_WR, False, 0);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);
}

V850_MORPH_FN(morphNMADDF_S_FISA) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_RD(reg3);
    Uns8 reg4 = state->info.reg4;
    vmiReg gpr_reg4 = V850_GPR_WR(reg4);

    //
    // r4 = neg((reg2 * reg1) + reg3)
    // Do not round intermediate result
    //
    vmimtFTernopRRRR(vmi_FT_32_IEEE_754, vmi_FNMADD, gpr_reg4, gpr_reg2, gpr_reg1, gpr_reg3, V850_FLG_FPF_WR, False, 0);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);
}

V850_MORPH_FN(morphNMSUBF_S_FISA) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_RD(reg3);
    Uns8 reg4 = state->info.reg4;
    vmiReg gpr_reg4 = V850_GPR_WR(reg4);

    //
    // r4 = neg((reg2 * reg1) - reg3)
    // Do not round intermediate result
    //
    vmimtFTernopRRRR(vmi_FT_32_IEEE_754, vmi_FNMSUB, gpr_reg4, gpr_reg2, gpr_reg1, gpr_reg3, V850_FLG_FPF_WR, False, 0);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);
}

V850_MORPH_FN(morphCMPF_S_FISCOND) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    cmpf(state, vmi_FT_32_IEEE_754);
}

V850_MORPH_FN(morphCMOVF_S_FISFFF) {
    //
    // Supported Architecture=ISA_E2_SPFP
    //
    Uns8 fff = state->info.fff;
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    CMOVF(fff, gpr_reg1, gpr_reg2, gpr_reg3, V850_GPR_BITS);
}

V850_MORPH_FN(morphABSF_S_FISR2R3) {
    //
    // Supported Architecture=V850E2_SP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPUnopE2(state, vmi_FT_32_IEEE_754, gpr_reg2, gpr_reg3, vmi_FABS, 0);
}

V850_MORPH_FN(morphCEILF_SUW_FISR2R3) {
    //
    // Supported Architecture=V850E2_SP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_32_UNS, gpr_reg3, vmi_FPR_POS_INF, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphCEILF_SW_FISR2R3) {
    //
    // Supported Architecture=V850E2_SP_FPU
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_32_INT, gpr_reg3, vmi_FPR_POS_INF, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphCVTF_LD_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_64_INT, gpr_reg2, vmi_FT_64_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}

V850_MORPH_FN(morphCVTF_SUW_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_32_UNS, gpr_reg3, vmi_FPR_CURRENT, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphCVTF_SW_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_32_INT, gpr_reg3, vmi_FPR_CURRENT, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphCVTF_UWS_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_UNS, gpr_reg2, vmi_FT_32_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}

V850_MORPH_FN(morphCVTF_WS_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_INT, gpr_reg2, vmi_FT_32_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}

V850_MORPH_FN(morphFLOORF_SUW_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_32_UNS, gpr_reg3, vmi_FPR_NEG_INF, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphFLOORF_SW_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_32_INT, gpr_reg3, vmi_FPR_NEG_INF, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphNEGF_S_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPUnopE2(state, vmi_FT_32_IEEE_754, gpr_reg2, gpr_reg3, vmi_FNEG, 0);
}

V850_MORPH_FN(morphRECIPF_S_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPUnopE2(state, vmi_FT_32_IEEE_754, gpr_reg2, gpr_reg3, vmi_FRECIP, 0);
}

V850_MORPH_FN(morphRSQRTF_S_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPUnopE2(state, vmi_FT_32_IEEE_754, gpr_reg2, gpr_reg3, vmi_FRSQRT, 0);
}

V850_MORPH_FN(morphSQRTF_S_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPUnopE2(state, vmi_FT_32_IEEE_754, gpr_reg2, gpr_reg3, vmi_FSQRT, 0);
}

V850_MORPH_FN(morphTRNCF_SUW_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2uns(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_32_UNS, gpr_reg3, vmi_FPR_ZERO, v850GetFPconfig(V850_FP_FLT_TO_UNS));
}

V850_MORPH_FN(morphTRNCF_SW_FISR2R3) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_32_INT, gpr_reg3, vmi_FPR_ZERO, v850GetFPconfig(V850_FP_FLT_TO_INT));
}

V850_MORPH_FN(morphTRFF_FIV) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    //    FLG_PSW_CO = (FLG_FPF_STICKY != 0)
    //    FLG_PSW_OV = FLG_EFG_FPOV
    //    FLG_PSW_SI = FLG_EFG_FPS
    //    FLG_PSW_ZR = FLG_EFG_FPZ
    vmimtCondMoveRCC(V850_FLG_PSW_CO_BITS, V850_FLG_FPF_STICKY_RD, False, V850_FLG_PSW_CO_WR, 0, 1);
    vmimtMoveRR(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, V850_FLG_EFG_FPOV_RD);
    vmimtMoveRR(V850_FLG_PSW_SI_BITS, V850_FLG_PSW_SI_WR, V850_FLG_EFG_FPS_RD);
    vmimtMoveRR(V850_FLG_PSW_ZR_BITS, V850_FLG_PSW_ZR_WR, V850_FLG_EFG_FPZ_RD);
}

V850_MORPH_FN(morphLDFF_FIVR2A) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    MT_MTSREG(SPR_EFG, V850_GPR_RD(state->info.reg2));
    vmimtArgProcessor();
    vmimtCall((vmiCallFn)v850UnPackEFG);
}

V850_MORPH_FN(morphLDFC_FIVR2B) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    MT_MTSREG(SPR_ECT, V850_GPR_RD(state->info.reg2));
}

V850_MORPH_FN(morphSTFF_FIVR3A) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    vmimtArgProcessor();
    vmimtCall((vmiCallFn)v850PackEFG);
    MT_MFSREG(V850_GPR_WR(state->info.reg3), SPR_EFG);
}

V850_MORPH_FN(morphSTFC_FIVR3B) {
    //
    // Supported Architecture=V850E1_SP_FPU
    //
    vmimtMoveRR(V850_GPR_BITS, V850_GPR_WR(state->info.reg3), V850_SPR_ECT_RD);
}

V850_MORPH_FN(morphTRFSR_FIFFF) {
    //
    // Supported Architecture=ISA_E2_FP
    //
    Uns8 fff = state->info.fff;
    vmimtUnopRR(8, vmi_MOV, V850_FLG_PSW_ZR_WR, V850_FLG_FPSR_CC_RD(fff), 0);
}

//
// RH850
//
V850_MORPH_FN(morphCVTF_HS_FI) {
    //
    // Supported Architecture=ISA_E3_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_16_IEEE_754, gpr_reg2, vmi_FT_32_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}

V850_MORPH_FN(morphCVTF_SH_FI) {
    //
    // Supported Architecture=ISA_E3_FP
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    emitFPConvE2(vmi_FT_32_IEEE_754, gpr_reg2, vmi_FT_16_IEEE_754, gpr_reg3, vmi_FPR_CURRENT, 0);
}


// r3 = (r2+r1) + r3
V850_MORPH_FN(morphFMAF_S_FI) {
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    //
    // r3 = (r2 * r1) + r3
    // Do not round intermediate result
    //
    vmimtFTernopRRRR(vmi_FT_32_IEEE_754, vmi_FMADD, gpr_reg3, gpr_reg2, gpr_reg1, gpr_reg3, V850_FLG_FPF_WR, False, 0);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);
}

V850_MORPH_FN(morphFMSF_S_FI) {
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

     //
     // r3 = (r1 * r2) - r3
     // Do not round intermediate result
     //
     vmimtFTernopRRRR(vmi_FT_32_IEEE_754, vmi_FMSUB, gpr_reg3, gpr_reg2, gpr_reg1, gpr_reg3, V850_FLG_FPF_WR, False, 0);

     //  set sticky flags from fpuFlag value
     emitSetSticky(V850_FLG_FPF_RD);
}

V850_MORPH_FN(morphFNMAF_S_FI) {
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    //
    // r3 = neg((r2 * r1) + r3)
    // Do not round intermediate result
    //
    vmimtFTernopRRRR(vmi_FT_32_IEEE_754, vmi_FNMADD, gpr_reg3, gpr_reg2, gpr_reg1, gpr_reg3, V850_FLG_FPF_WR, False, 0);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);}

V850_MORPH_FN(morphFNMSF_S_FI) {
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    //
    // r3 = neg((r1 * r2) - r3)
    // Do not round intermediate result
    //
    vmimtFTernopRRRR(vmi_FT_32_IEEE_754, vmi_FNMSUB, gpr_reg3, gpr_reg2, gpr_reg1, gpr_reg3, V850_FLG_FPF_WR, False, 0);

    //  set sticky flags from fpuFlag value
    emitSetSticky(V850_FLG_FPF_RD);}

//
// This is specifically for the non-IEEE SFPU for E1F
// This fixed value pattern is returned for any QNAN result
//
static VMI_FP_QNAN32_RESULT_FN(QNaN32ResultCB) {
    return V850E1_FP32_QNAN;
}

//
// These contain FP80 tiny values to use as results
//
static vmiFP80Arg fp80QNaN;

//
// Initialize the FP80 format tiny value with the 32-bit FP value
//
static void initfp80QNaN() {
    union {Uns32 u32; Flt32 f32;} u;
    u.u32 = V850E1_FP32_QNAN;
    fp80QNaN.f80 = u.f32;
}

//static VMI_FP_TINY_ARGUMENT_FN(tinyArgumentCB) {
//    return fp80QNaN;
//}

//
// Set simulator floating point control word
//
void v850UpdateFPControlWord(v850P v850) {
    vmiFPControlWord fpcw = { 0 };

    if (v850->configInfo.arch & ISA_E1_FP) {
        // V850e1f mode
        vmiFPControlWord cwNoExceptions = {
                .IM  = 0,
                .DM  = 0,
                .ZM  = 1,
                .OM  = 1,
                .UM  = 1,
                .PM  = 1,

                //
                // Rounding Control
                //
                .RC  = vmi_FPR_NEAREST,
                .FZ  = 0,
                .DAZ = 0
        };
        fpcw = cwNoExceptions;

    } else if (v850->configInfo.arch & ISA_E2_FP){

        fpcw.IM = !v850->SPR_FPSR.XE_V;
        fpcw.DM = 1;
        fpcw.ZM = !v850->SPR_FPSR.XE_Z;
        fpcw.OM = !v850->SPR_FPSR.XE_O;
        fpcw.UM = !v850->SPR_FPSR.XE_U;
        fpcw.PM = !v850->SPR_FPSR.XE_I;

        //
        // Rounding Control
        //
        fpcw.RC  = v850->SPR_FPSR.RM; // Always vmi_FPR_NEAREST;
        fpcw.FZ  = v850->SPR_FPSR.FS; // Always True
        fpcw.DAZ = 1;   // Email from Nishiumi-san 29/1/15
                        // Denormalized inputs are flushed to zero
    }

    vmirtSetFPControlWord((vmiProcessorP)v850, fpcw);
}

//
// Configure FPU, if implemented
//
void v850ConfigureFPU(v850P v850) {

    v850FPCtrl ctrl = V850_FP_DEFAULT;

    initfp80QNaN();

    if (v850->configInfo.arch & ISA_E1_FP) {
        ctrl = V850_FP_E1;
    } else if (v850->configInfo.arch & ISA_E2_FP) {
        ctrl = V850_FP_E2;
    }

    if (ctrl != V850_FP_DEFAULT) {
        vmirtConfigureFPU((vmiProcessorP)v850, v850GetFPconfig(ctrl));

        // initialize floating point control word
        v850UpdateFPControlWord(v850);
    }
}

vmiFPConfigCP v850GetFPconfig(v850FPCtrl ctrl) {
    if (ctrl==V850_FP_DEFAULT) {
        return 0;
    } else {
        static const vmiFPConfig configs[V850_FP_LAST] = {
            [V850_FP_E1] = {
                .QNaN32                  = V850E1_FP32_QNAN,
                .QNaN32ResultCB          = QNaN32ResultCB,
                .fpArithExceptCB         = v850E1FPArithExcept
            },
            [V850_FP_E2] = {
                .QNaN32                  = V850E2_FP32_QNAN,
                .QNaN64                  = V850E2_FP64_QNAN,
                .fpArithExceptCB         = v850E2FPArithExcept,
                .suppressFlags           = {.f = {.D = 1} },
            },
            [V850_FP_FLT_TO_INT] = {
                .QNaN32                  = V850E2_FP32_QNAN,
                .QNaN64                  = V850E2_FP64_QNAN,
                .indeterminate32ResultCB = v850E2Ind64_ds32,
                .indeterminate64ResultCB = v850E2Ind64_ds64,
                .fpArithExceptCB         = v850E2FPArithExcept,
                .suppressFlags           = {.f = {.D = 1} },
            },
            [V850_FP_FLT_TO_UNS] = {
                .QNaN32                  = V850E2_FP32_QNAN,
                .QNaN64                  = V850E2_FP64_QNAN,
                .indeterminate32ResultCB = v850E2Ind32_du32,
                .indeterminate64ResultCB = v850E2Ind64_du64,
                .fpArithExceptCB         = v850E2FPArithExcept,
                .suppressFlags           = {.f = {.D = 1} },
            },
        };
        return &configs[ctrl];
    }
}

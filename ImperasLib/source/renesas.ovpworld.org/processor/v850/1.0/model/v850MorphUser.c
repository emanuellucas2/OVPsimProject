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
#include "v850BlockState.h"
#include "v850Instructions.h"
#include "v850Exceptions.h"
#include "v850Morph.h"
#include "v850MorphFP.h"
#include "v850Utils.h"


#define IMMTSREG(SREG, VALUE) { \
    Uns32 mask    = v850->SPR_ ## SREG ## _wmask.reg; \
    Uns32 prevREG = v850->SPR_ ## SREG .reg & ~mask;  \
    Uns32 nextREG = VALUE                   &  mask;  \
    v850->SPR_ ## SREG .reg = prevREG | nextREG;      \
}

//
// Write Flag Const structures
//
static const vmiFlags flags_Si = {
    VMI_NOFLAG_CONST,
    {
        VMI_NOFLAG_CONST,
        VMI_NOFLAG_CONST,
        VMI_NOFLAG_CONST,
        V850_FLG_PSW_SI_CONST,
        VMI_NOFLAG_CONST
    }
};
static const vmiFlags flags_Zr = {
    VMI_NOFLAG_CONST,
    {
        VMI_NOFLAG_CONST,
        VMI_NOFLAG_CONST,
        V850_FLG_PSW_ZR_CONST,
        VMI_NOFLAG_CONST,
        VMI_NOFLAG_CONST
    }
};
static const vmiFlags flags_ZrSi = {
    VMI_NOFLAG_CONST,
    {
        VMI_NOFLAG_CONST,
        VMI_NOFLAG_CONST,
        V850_FLG_PSW_ZR_CONST,
        V850_FLG_PSW_SI_CONST,
        VMI_NOFLAG_CONST
    }
};
static const vmiFlags flags_ZrSiOv = {
    VMI_NOFLAG_CONST,
    {
        VMI_NOFLAG_CONST,
        VMI_NOFLAG_CONST,
        V850_FLG_PSW_ZR_CONST,
        V850_FLG_PSW_SI_CONST,
        V850_FLG_PSW_OV_CONST
    }
};
static const vmiFlags flags_CoZrSi = {
    VMI_NOFLAG_CONST,
    {
        V850_FLG_PSW_CO_CONST,
        VMI_NOFLAG_CONST,
        V850_FLG_PSW_ZR_CONST,
        V850_FLG_PSW_SI_CONST,
        VMI_NOFLAG_CONST
    }
};
static const vmiFlags flags_CoZrSiOv = {
    VMI_NOFLAG_CONST,
    {
        V850_FLG_PSW_CO_CONST,
        VMI_NOFLAG_CONST,
        V850_FLG_PSW_ZR_CONST,
        V850_FLG_PSW_SI_CONST,
        V850_FLG_PSW_OV_CONST
    }
};

//
// Update carry
//
static const vmiFlags flags_CoFromZr = {
    VMI_NOFLAG_CONST,           // offset to carry in flag (unused)
    {
        VMI_NOFLAG_CONST,       // offset to carry flag (unused)
        VMI_NOFLAG_CONST,       // offset to parity flag (unused)
        V850_FLG_PSW_CO_CONST,  // offset to carry flag (writing zero value)
        VMI_NOFLAG_CONST,       // offset to sign flag(unused)
        VMI_NOFLAG_CONST        // offset to overflow flag (unused)
    }
};

static const vmiFlags flags_TmpFromZr = {
    VMI_NOFLAG_CONST,           // offset to carry in flag (unused)
    {
        VMI_NOFLAG_CONST,       // offset to carry flag (unused)
        VMI_NOFLAG_CONST,       // offset to parity flag (unused)
        V850_TMP_CONST(0),      // offset to Temporary flag - zero
        VMI_NOFLAG_CONST,       // offset to sign flag (unused)
        VMI_NOFLAG_CONST        // offset to overflow flag (unused)
    }
};

// LCOV_EXCL_START
static void unimplemented(const char *name) {
    vmiMessage("F", "MORPH_UNIMP", "Instruction %s unimplemented", name);
}

static void morphUnimplemented(const char *name) {
    vmimtArgNatAddress(name);
    vmimtCall((vmiCallFn)unimplemented);
    vmimtExit();
}
// LCOV_EXCL_STOP

static Bool UM_PrivException(v850MorphStateP state) {
    Bool UserMode = (state->v850->mode==RH850_M_USER) || (state->v850->mode==RH850_M_USER_MPU);
    if (UserMode) {
        // Supervisor instruction Exception
        vmimtArgProcessor();
        vmimtCall((vmiCallFn)v850ProcessPIE);
        return True;
    }
    return False;
}

////////////////////////////////////////////////////////////////////////////////
// CONDITIONAL INSTRUCTION EXECUTION
////////////////////////////////////////////////////////////////////////////////

//
// For conditions, this enumeration describes the circumstances under which the
// condition is satisfied
//
typedef enum v850CondOpE {
    ACO_ALWAYS, // condition always True
    ACO_FALSE,  // condition satisfied if flag unset
    ACO_TRUE,   // condition satisfied if flag set
} v850CondOp;

//
// Condition Codes
//
typedef enum v850CondE {
    FLAG_V,
    FLAG_C,
    FLAG_Z,
    FLAG_NH,
    FLAG_S,
    FLAG_T,
    FLAG_LT,
    FLAG_LE,
    FLAG_NV,
    FLAG_NC,
    FLAG_NZ,
    FLAG_H,
    FLAG_NS,
    FLAG_SA,
    FLAG_GE,
    FLAG_GT,
    FLAG_LAST             // KEEP LAST: for sizing
} v850Cond;

//
// For conditions, this structure describes a flag and a value for a match
//
typedef struct v850CondActionS {
    vmiReg     flag;
    v850CondOp op;
} v850CondAction, *v850CondActionP;

//
// Emit code to prepare a conditional operation and return an v850Cond structure
// giving the offset of a flag to compare against
//
static v850CondAction emitPrepareCondition(v850Cond cond) {

    const static v850CondAction condTable[FLAG_LAST] = {
        [FLAG_V]  = {V850_FLG_PSW_OV_CONST,  ACO_TRUE  },      // OF==1
        [FLAG_C]  = {V850_FLG_PSW_CO_CONST,  ACO_TRUE  },      // CF==1
        [FLAG_Z]  = {V850_FLG_PSW_ZR_CONST,  ACO_TRUE  },      // ZF==1
        [FLAG_NH] = {V850_FLG_TMP_CONST, ACO_TRUE  },      // (CF==1) || (ZF==1)
        [FLAG_S]  = {V850_FLG_PSW_SI_CONST,  ACO_TRUE  },      // SF==1
        [FLAG_T]  = {VMI_NOREG,          ACO_ALWAYS},      // always true
        [FLAG_LT] = {V850_FLG_TMP_CONST, ACO_TRUE  },      // NF!=VF
        [FLAG_LE] = {V850_FLG_TMP_CONST, ACO_TRUE  },      // (ZF==1) || (NF!=VF)
        [FLAG_NV] = {V850_FLG_PSW_OV_CONST,  ACO_FALSE },      // OF==0
        [FLAG_NC] = {V850_FLG_PSW_CO_CONST,  ACO_FALSE },      // CF==0
        [FLAG_NZ] = {V850_FLG_PSW_ZR_CONST,  ACO_FALSE },      // ZF==0
        [FLAG_H]  = {V850_FLG_TMP_CONST, ACO_FALSE },      // (CF==0) && (ZF==0)
        [FLAG_NS] = {V850_FLG_PSW_SI_CONST,  ACO_FALSE },      // SF==0
        [FLAG_SA] = {V850_FLG_PSW_SAT_CONST, ACO_TRUE  },      // SAT=1
        [FLAG_GE] = {V850_FLG_TMP_CONST, ACO_FALSE },      // (S xor OV) = 0
        [FLAG_GT] = {V850_FLG_TMP_CONST, ACO_FALSE },      // ((S xor OV) or Z) = 0
    };

    // get the table entry corresponding to the instruction condition
    v850CondAction entry = condTable[cond];
    vmiReg         tf    = entry.flag;

    switch(cond) {

        case FLAG_T:
             // unconditional execution
             break;

        case FLAG_V:
        case FLAG_C:
        case FLAG_Z:
        case FLAG_S:
        case FLAG_NV:
        case FLAG_NC:
        case FLAG_NZ:
        case FLAG_NS:
        case FLAG_SA:
            // basic flags, always valid
            break;

        case FLAG_H:
        case FLAG_NH:
            // (Carry or Zero) = 1
            vmimtBinopRRR(8, vmi_OR, tf, V850_FLG_PSW_CO_WR, V850_FLG_PSW_ZR_RD, 0);
            break;

        case FLAG_LT:
        case FLAG_GE:
            // (Sign ^ Overflow) = 1
            vmimtBinopRRR(8, vmi_XOR, tf, V850_FLG_PSW_SI_WR, V850_FLG_PSW_OV_RD, 0);
            break;

        case FLAG_LE:
        case FLAG_GT:
            vmimtBinopRRR(8, vmi_XOR, tf, V850_FLG_PSW_SI_WR, V850_FLG_PSW_OV_RD, 0);
            vmimtBinopRR (8, vmi_OR, tf, V850_FLG_PSW_ZR_WR, 0);
            break;

        default:
            VMI_ABORT("%s: unimplemented condition", FUNC_NAME);    // LCOV_EXCL_LINE
            /* no break */
    }

    // return the condition description
    return entry;
}

static void binopRRRCCCC(vmiBinop op, Uns8 cccc, vmiReg gpr_reg3, vmiReg gpr_reg2, vmiReg gpr_reg1) {

    v850CondAction action = emitPrepareCondition(cccc);

    if(action.op==ACO_ALWAYS) {
        vmimtMoveRC(8, V850_TMP_WR(0), 1);
        action.flag = V850_TMP_RD(0);
    } else if(action.op==ACO_FALSE) {
        vmimtBinopRRC(8, vmi_XOR, V850_TMP_WR(0), action.flag, 1, 0);
        action.flag = V850_TMP_RD(0);
    }

    vmiFlags tmpFlags = {
        cin:action.flag,
        .f = {
            V850_FLG_PSW_CO_CONST,
            VMI_NOFLAG_CONST,
            V850_FLG_PSW_ZR_CONST,
            V850_FLG_PSW_SI_CONST,
            V850_FLG_PSW_OV_CONST
        }
    };

    vmimtBinopRRR(V850_GPR_BITS, op, gpr_reg3, gpr_reg2, gpr_reg1, &tmpFlags);
}

#define BINOPRRR(_OP,_FLAGS) \
    vmimtBinopRRR(V850_GPR_BITS, _OP, gpr_reg3, gpr_reg2, gpr_reg1, _FLAGS)

#define BINOPRR(_OP,_FLAGS) \
    vmimtBinopRR(V850_GPR_BITS, _OP, gpr_reg2, gpr_reg1, _FLAGS)

#define BINOPRRC(_OP,_CONST,_FLAGS) \
        vmimtBinopRRC(V850_GPR_BITS, _OP, gpr_reg2, gpr_reg1, _CONST, _FLAGS)

#define BINOPRC(_OP,_CONST,_FLAGS) \
    vmimtBinopRRC(V850_GPR_BITS, _OP, gpr_reg2, gpr_reg2, _CONST, _FLAGS)

#define UNOPRR(_OP,_FLAGS) \
        vmimtUnopRR(V850_GPR_BITS, _OP, gpr_reg2, gpr_reg1, _FLAGS);

static void emitSaturateCheck(vmiReg result) {
    // generate sign and zero flags from the (possibly saturated) result
    vmimtUnopRR(V850_GPR_BITS, vmi_MOV, VMI_NOREG, result, &flags_ZrSi);

    // set sticky saturation flag if there was an overflow
    vmimtBinopRR(8, vmi_OR, V850_FLG_PSW_SAT_WR, V850_FLG_PSW_OV_RD, 0);
}

static memEndian getEndian(void) {
    return MEM_ENDIAN_LITTLE;
}

static void load (
    vmiReg           reg2,
    vmiReg           reg1,
    Int32            imm,
    Uns8             size,
    Bool             sign,
    v850Architecture arch) {

    memEndian endian = getEndian();

    //
    // Need to check state of alignment
    // V850   misaligned access masked
    // V850E1/ES misaligned access OK
    // V850E2/E2R programmable from IFMAEN
    //
    Bool snap = False;
    if (arch == V850) {
        snap = True;
    } else if (arch == V850E1) {
        snap = False;  // Actually dependant upon pin IFMAEN
    } else if (arch == V850ES) {
        snap = False;  // Actually dependant upon pin IFMAEN
    } else if (arch == V850E2) {
        snap = False;  // Actually dependant upon pin IFMAEN
    } else if (arch == V850E2R) {
        snap = False;  // Actually dependant upon pin IFMAEN
    } else if (arch == RH850G3M) {
        snap = False;  // Actually dependant upon pin IFMAEN
    }
    Uns8 destBits = (size <= 32) ? V850_GPR_BITS : (2*V850_GPR_BITS);
    vmimtLoadRRO(destBits, size, imm, reg2, reg1, endian, sign, snap);
}

static void store (
    vmiReg           reg2,
    vmiReg           reg1,
    Int32            imm,
    Uns8             size,
    Bool             sign,
    v850Architecture arch) {

    memEndian endian = getEndian();

    //
    // Need to check state of alignment
    // V850   misaligned access masked
    // V850E1/ES misaligned access OK
    // V850E2/E2R programmable from IFMAEN
    //
    Bool snap = False;
    if (arch == V850) {
        snap = True;
    } else if (arch == V850E1) {
        snap = False;  // Actually dependant upon pin IFMAEN
    } else if (arch == V850ES) {
        snap = False;  // Actually dependant upon pin IFMAEN
    } else if (arch == V850E2) {
        snap = False;  // Actually dependant upon pin IFMAEN
    } else if (arch == V850E2R) {
        snap = False;  // Actually dependant upon pin IFMAEN
    } else if (arch == RH850G3M) {
        snap = False;  // Actually dependant upon pin IFMAEN
    }
    vmimtStoreRRO(size, imm, reg1, reg2, endian, snap);
}

static void divFmt11 (
        vmiReg     reg1,
        vmiReg     reg2,
        vmiReg     reg3,
        vmiBinop   op,
        Uns8       size,
        vmiFlagsCP flags
    ) {

    Bool sign = (op == vmi_IDIV) ? True : False;

    //
    // Clear the overflow flag, this can be set if necessary
    // by the exception handler on a divide by zero
    //
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);

    if (size == 32) {
            // Extend reg2 to a 64 bit
            vmimtMoveExtendRR(V850_GPR_BITS*2, V850_TMP_WR(0), V850_GPR_BITS, reg2, sign);
            vmimtDivopRRR(V850_GPR_BITS, op, reg2, reg3, V850_TMP_RD(1), V850_TMP_RD(0), reg1, flags);

    } else if (size == 16) {
        // Extend reg1(15:0] to a 32 bit
        vmimtMoveExtendRR(V850_GPR_BITS, V850_TMP_WR(0), V850_GPR_BITS/2, reg1, sign);
        vmimtDivopRRR(V850_GPR_BITS, op, reg2, reg3, VMI_NOREG, reg2, V850_TMP_RD(0), flags);

    } else {
        VMI_ABORT("%s: unimplemented size %d", FUNC_NAME, size);    // LCOV_EXCL_LINE
    }
}

static void vmic_Value_to_PSW(v850P v850, Uns32 value) {
    IMMTSREG(PSW, value);
    v850UnPackPSW(v850);

    //
    // Check for pending interrupts
    //
    v850TestInterrupt(v850);
}

static void bitOP (Uns8 bit, vmiReg gpr_reg1, Int32 sdisp, vmiBinop op) {
    memEndian   endian  = getEndian();

    // First perform a byte read
    vmimtLoadRRO(8, 8, sdisp, V850_TMP_WR(0), gpr_reg1, endian, False, False);

    // Test the bit for Zero to set the Z flag
    Uns8 setBit = 0x1 << bit;
    vmimtBinopRRC(8, vmi_AND, VMI_NOREG, V850_TMP_RD(0), setBit, &flags_Zr);

    // UNSet the bit in the TEMPREG
    vmimtBinopRC(8, op, V850_TMP_WR(0), setBit, 0);

    // Write back the TEMPREG to byte
    vmimtStoreRRO(8, sdisp, gpr_reg1, V850_TMP_RD(0), endian, False);
}

//
// Write Default Morpher stub Functions
//
V850_MORPH_FN(morphADD_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    BINOPRR(vmi_ADD, &flags_CoZrSiOv);
}

V850_MORPH_FN(morphAND_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    BINOPRR(vmi_AND, &flags_ZrSiOv);
}

V850_MORPH_FN(morphCMP_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    BINOPRR(vmi_CMP, &flags_CoZrSiOv);
}

V850_MORPH_FN(morphDIVH_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);

    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);
    vmimtMoveExtendRR(V850_GPR_BITS, V850_TMP_WR(0), V850_GPR_BITS/2, gpr_reg1, True);
    vmimtBinopRR(V850_GPR_BITS, vmi_IDIV, gpr_reg2, V850_TMP_RD(0), &flags_ZrSi);
}

V850_MORPH_FN(morphMOV_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    vmimtMoveRR(V850_GPR_BITS, gpr_reg2, gpr_reg1);
}

V850_MORPH_FN(morphMULH_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);

    vmiReg gpr_reg2H = VMI_REG_DELTA(gpr_reg2, 2);
    vmimtMulopRRR(V850_GPR_BITS/2, vmi_IMUL, gpr_reg2H, gpr_reg2, gpr_reg2, gpr_reg1, 0);
}

V850_MORPH_FN(morphNOT_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    UNOPRR(vmi_NOT, &flags_ZrSi);

    // Special clear Overflow
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);
}

V850_MORPH_FN(morphOR_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    BINOPRR(vmi_OR, &flags_ZrSiOv);
}

V850_MORPH_FN(morphSATADD_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    BINOPRR(vmi_ADDSQ, &flags_CoZrSiOv);
    emitSaturateCheck(gpr_reg2);
}

V850_MORPH_FN(morphSATSUB_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);

    BINOPRR(vmi_SUBSQ, &flags_CoZrSiOv);
    emitSaturateCheck(gpr_reg2);
}

V850_MORPH_FN(morphSATSUBR_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);

    BINOPRR(vmi_RSUBSQ, &flags_CoZrSiOv);
    emitSaturateCheck(gpr_reg2);
}

V850_MORPH_FN(morphSUB_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    BINOPRR(vmi_SUB, &flags_CoZrSiOv);
}

V850_MORPH_FN(morphSUBR_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    BINOPRR(vmi_RSUB, &flags_CoZrSiOv);
}

V850_MORPH_FN(morphTST_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);

    vmimtBinopRRR(V850_GPR_BITS, vmi_AND, VMI_NOREG, gpr_reg2, gpr_reg1, &flags_ZrSiOv);
}

V850_MORPH_FN(morphXOR_F01) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    BINOPRR(vmi_XOR, &flags_ZrSiOv);
}

V850_MORPH_FN(morphDBTRAP_F01A) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    morphUnimplemented("DBTRAP_F01A");
}

V850_MORPH_FN(morphNOP_F01A) {
    //
    // Supported Architecture=V850_ISA_E0
    //
}

static void common_RIE(v850MorphStateP state) {
    vmimtArgProcessor();
    vmimtCall((vmiCallFn)v850ProcessRIE);
}

V850_MORPH_FN(morphRIE_F01A) {
    //
    // Supported Architecture=ISA_E2
    //
    common_RIE(state);
}

V850_MORPH_FN(morphRIE_F06X) {
    //
    // Supported Architecture=ISA_E2
    //
    common_RIE(state);
}

#define V850_ADDRESS_MASK 0x00fffffe
#define V850E_ADDRESS_MASK 0xfffffffe
V850_MORPH_FN(morphSWITCH_F01D) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);

    memEndian   endian   = getEndian();
    Int32       pc       = state->info.thisPC;
    //
    // adr <- (PC+2) + (gpr_reg1 << 1)
    // PC  <- (PC+2) + ((signed(mem(adr,HW)) << 1)
    //

    // tmpl = gpr_reg1 << 1
    vmimtBinopRRC(V850_GPR_BITS, vmi_SHL, V850_TMP_WR(0), gpr_reg1, 1, 0);
    // tmph = mem((tmp1 + (thisPC + 2)),HW)
    vmimtLoadRRO(V850_GPR_BITS, V850_GPR_BITS/2, (pc + 2), V850_TMP_WR(1), V850_TMP_RD(0), endian, True, True);
    // tmph = tmph << 1
    vmimtBinopRRC(V850_GPR_BITS, vmi_SHL, V850_TMP_WR(1), V850_TMP_RD(1), 1, 0);
    // tmph = tmph + (pc + 2)
    vmimtBinopRC(V850_GPR_BITS, vmi_ADD, V850_TMP_WR(1), (pc + 2), 0);

    //
    // the Next PC is now held in V850_TEMPH_REG
    //
    vmimtSetAddressMask(V850_ADDRESS_MASK);
    vmimtUncondJumpReg(0, V850_TMP_RD(1), VMI_NOREG, vmi_JH_NONE);
}

V850_MORPH_FN(morphSXB_F01C) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_WR(reg1);

    vmimtMoveExtendRR(V850_GPR_BITS, gpr_reg1, 8, gpr_reg1, True);
}

V850_MORPH_FN(morphSXH_F01C) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_WR(reg1);

    vmimtMoveExtendRR(V850_GPR_BITS, gpr_reg1, 16, gpr_reg1, True);
}

V850_MORPH_FN(morphZXB_F01C) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_WR(reg1);

    vmimtMoveExtendRR(V850_GPR_BITS, gpr_reg1, 8, gpr_reg1, False);
}

V850_MORPH_FN(morphZXH_F01C) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_WR(reg1);

    vmimtMoveExtendRR(V850_GPR_BITS, gpr_reg1, 16, gpr_reg1, False);
}

V850_MORPH_FN(morphFETRAP_F01E) {
    //
    // Supported Architecture=ISA_E2
    //
    Uns32 uimm = state->info.uimm;
    vmimtArgProcessor();
    vmimtArgUns32(uimm);
    vmimtCall((vmiCallFn)v850ProcessFETRAP);
}

V850_MORPH_FN(morphCALLT_F02B) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns32 uimm = state->info.uimm;

    Int32       pc       = state->info.thisPC;
    memEndian   endian   = getEndian();

    // CTPSW <- PSW
    vmimtRegReadImpl("PSW");
    vmimtArgProcessor();
    vmimtCallResult((vmiCallFn)v850PackPSW, V850_GPR_BITS, V850_SPR_CTPSW_WR);

    // Calculate Jump Address
    // calculate adr (CTBP + uimm), get the value into V850_TEMPL_REG
    // Jumpaddress = V850_CTBP_REG + mem(LoHalf, V850_CTBP_REG+uimm)
    // The immediate value is left shifted by 1
    //
    vmimtLoadRRO(V850_GPR_BITS, V850_GPR_BITS/2, uimm<<1, V850_TMP_WR(0), V850_SPR_CTBP_RD, endian, False, True);
    vmimtBinopRR(V850_GPR_BITS, vmi_ADD, V850_TMP_WR(0), V850_SPR_CTBP_RD, 0);

    //
    // Jump and link through callt
    // CTPC <- PC + 2 (Return PC)
    //
    vmimtUncondJumpReg(pc+2, V850_TMP_RD(0), V850_SPR_CTPC_RD, vmi_JH_NONE);
}

V850_MORPH_FN(morphRMTRAP_F01A) {
    //
    // Supported Architecture=ISA_E2
    //
    /* LCOV_EXCL_LINE */ morphUnimplemented("RMTRAP_F01A");
}

V850_MORPH_FN(morphSYNCM_F01A) {
    //
    // Supported Architecture=ISA_E2
    //
    // NOP
}

V850_MORPH_FN(morphSYNCP_F01A) {
    //
    // Supported Architecture=ISA_E2
    //
    // NOP
}

//
// CALL, RETURNE, or NONE
//
static void jmp (v850MorphStateP state, Uns8 reg1, Int32 sdisp) {
    vmiReg  gpr_reg1 = V850_GPR_WR(reg1);

    if (sdisp) {

        vmimtBinopRRC(V850_GPR_BITS, vmi_ADD, V850_TMP_WR(0), gpr_reg1, sdisp, 0);
        vmimtUncondJumpReg(0, V850_TMP_WR(0), VMI_NOREG, vmi_JH_NONE);

    } else {

        vmiJumpHint jump_hint;

        //
        // If the preceding instruction manufactures a link address save, then
        // assume this is a call; otherwise, if the register is one that has
        // previously been used as a link register, assume it is a return;
        // otherwise, assume an indirect jump.
        //
        if (state->blockState->jmpIsCall) {
            jump_hint = vmi_JH_CALL;
            state->blockState->jmpIsCall = False;
        } else if (state->v850->REG_RETMASK & (1<<reg1)) {
            jump_hint = vmi_JH_RETURN;
        } else {
            jump_hint = vmi_JH_NONE;
        }

        vmimtUncondJumpReg(0, gpr_reg1, VMI_NOREG, jump_hint);
    }
}

V850_MORPH_FN(morphJMP_F01B) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;

    jmp(state, reg1, 0);
}

V850_MORPH_FN(morphADD_F02S) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int16 simm = state->info.simm;
    BINOPRC(vmi_ADD, simm, &flags_CoZrSiOv);
}

V850_MORPH_FN(morphCMP_F02S) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int16 simm = state->info.simm;
    BINOPRC(vmi_CMP, simm, &flags_CoZrSiOv);
}

V850_MORPH_FN(morphMOV_F02S) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int16 simm = state->info.simm;
    vmimtMoveRC(V850_GPR_BITS, gpr_reg2, simm);
}

V850_MORPH_FN(morphMULH_F02S) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int16 simm = state->info.simm;
    vmiReg gpr_reg2H = VMI_REG_DELTA(gpr_reg2, 2);

    vmimtMoveRC(V850_GPR_BITS/2, V850_TMP_WR(0), simm);
    vmimtMulopRRR(V850_GPR_BITS/2, vmi_IMUL, gpr_reg2H, gpr_reg2, gpr_reg2, V850_TMP_RD(0), 0);
}

V850_MORPH_FN(morphSATADD_F02S) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int16 simm = state->info.simm;

    BINOPRC(vmi_ADDSQ, simm, &flags_CoZrSiOv);
    emitSaturateCheck(gpr_reg2);
}

V850_MORPH_FN(morphSAR_F02U) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns16 uimm = state->info.uimm;
    BINOPRC(vmi_SAR, uimm, &flags_CoZrSi);
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);
}

V850_MORPH_FN(morphSHL_F02U) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns16 uimm = state->info.uimm;
    BINOPRC(vmi_SHL, uimm, &flags_CoZrSi);
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);
}

V850_MORPH_FN(morphSHR_F02U) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns16 uimm = state->info.uimm;
    BINOPRC(vmi_SHR, uimm, &flags_CoZrSi);
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);
}

static void bcond(v850MorphStateP state) {

    Uns8     cond     = state->info.cond;
    v850Addr targetPC = state->info.targetPC;

    v850CondAction action = emitPrepareCondition(cond);

    if(action.op==ACO_ALWAYS) {
        vmimtUncondJump(0, targetPC, VMI_NOREG, vmi_JH_NONE);
    } else {
        vmimtCondJump(action.flag, action.op==ACO_TRUE, 0, targetPC, VMI_NOREG, vmi_JH_NONE);
    }
}

V850_MORPH_FN(morphBCOND_F03) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    bcond(state);
}

V850_MORPH_FN(morphSLD_BU_F04DB) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 udisp = state->info.udisp;

    vmiReg gpr_ep = V850_GPR_RD(30);
    load(gpr_reg2, gpr_ep, udisp, 8, False, state->info.arch);
}

V850_MORPH_FN(morphSLD_HU_F04DH) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 udisp = state->info.udisp;

    vmiReg gpr_ep = V850_GPR_RD(30);
    load(gpr_reg2, gpr_ep, udisp, 16, False, state->info.arch);
}

V850_MORPH_FN(morphSLD_B_F04LA) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 udisp = state->info.udisp;

    vmiReg gpr_ep = V850_GPR_RD(30);
    load(gpr_reg2, gpr_ep, udisp, 8, True, state->info.arch);
}

V850_MORPH_FN(morphSLD_H_F04LB) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 udisp = state->info.udisp;

    vmiReg gpr_ep = V850_GPR_WR(30);
    load(gpr_reg2, gpr_ep, udisp, 16, True, state->info.arch);
}

V850_MORPH_FN(morphSLD_W_F04LC) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 udisp = state->info.udisp;

    vmiReg gpr_ep = V850_GPR_WR(30);
    load(gpr_reg2, gpr_ep, udisp, 32, True, state->info.arch);
}

V850_MORPH_FN(morphSST_B_F04SA) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 udisp = state->info.udisp;

    vmiReg gpr_ep = V850_GPR_WR(30);
    store(gpr_reg2, gpr_ep, udisp, 8, True, state->info.arch);
}

V850_MORPH_FN(morphSST_H_F04SB) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 udisp = state->info.udisp;

    vmiReg gpr_ep = V850_GPR_WR(30);
    store(gpr_reg2, gpr_ep, udisp, 16, True, state->info.arch);
}

V850_MORPH_FN(morphSST_W_F04SC) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 udisp = state->info.udisp;

    vmiReg gpr_ep = V850_GPR_WR(30);
    store(gpr_reg2, gpr_ep, udisp, 32, True, state->info.arch);
}

//
// CALL or NONE
//
static void jarl1 (v850MorphStateP state, Uns8 lr, Int32 sdisp) {
    v850Addr pc       = state->info.thisPC;
    v850Addr isize    = state->info.instrsize;
    vmiReg   gpr_lr   = V850_GPR_WR(lr);
    v850Addr targetPC = state->info.targetPC;
    vmiJumpHint jump_hint;

    if (sdisp == isize) {
        //
        // This indicates a manufactured jump and link in a strange idiom
        //
        jump_hint = vmi_JH_NONE;
        state->blockState->jmpIsCall = True;
    } else {
        //
        // indicate that this register may contain a link address
        //
        jump_hint = vmi_JH_CALL;
        state->v850->REG_RETMASK |= (1<<lr);
    }

    vmimtUncondJump(pc+isize, targetPC, gpr_lr, jump_hint);
}

V850_MORPH_FN(morphJARL_F05A) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8  reg2  = state->info.reg2;
    Int32 sdisp = state->info.sdisp;

    jarl1(state, reg2, sdisp);
}

static void jr (v850MorphStateP state, Int32 sdisp) {
    v850Addr targetPC = state->info.targetPC;
    vmimtUncondJump(0, targetPC, VMI_NOREG, vmi_JH_NONE);
}

V850_MORPH_FN(morphJR_F05B) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Int32 sdisp = state->info.sdisp;

    jr(state, sdisp);
}

V850_MORPH_FN(morphADDI_F06S) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int16 simm = state->info.simm;
    BINOPRRC(vmi_ADD, simm, &flags_CoZrSiOv);
}

V850_MORPH_FN(morphMOVEA_F06S) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int16 simm = state->info.simm;
    BINOPRRC(vmi_ADD, simm, 0);
}

V850_MORPH_FN(morphMULHI_F06S) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int16 simm = state->info.simm;
    vmiReg gpr_reg2H = VMI_REG_DELTA(gpr_reg2, 2);

    vmimtMoveRC(V850_GPR_BITS/2, V850_TMP_WR(0), simm);
    vmimtMulopRRR(V850_GPR_BITS/2, vmi_IMUL, gpr_reg2H, gpr_reg2, gpr_reg1, V850_TMP_RD(0), 0);
}

V850_MORPH_FN(morphSATSUBI_F06S) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int16 simm = state->info.simm;

    BINOPRRC(vmi_SUBSQ, simm, &flags_CoZrSiOv);
    emitSaturateCheck(gpr_reg2);
}

V850_MORPH_FN(morphJARL_F06SA) {
    //
    // Supported Architecture=ISA_E2
    //
    Uns8  reg1  = state->info.reg1;
    Int32 sdisp = state->info.sdisp;

    jarl1(state, reg1, sdisp);
}

V850_MORPH_FN(morphJMP_F06SB) {
    //
    // Supported Architecture=ISA_E2
    //
    Uns8  reg1  = state->info.reg1;
    Int32 sdisp = state->info.sdisp;

    jmp(state, reg1, sdisp);
}

V850_MORPH_FN(morphJR_F06SC) {
    //
    // Supported Architecture=ISA_E2
    //
    Int32 sdisp = state->info.sdisp;

    jr(state, sdisp);
}

V850_MORPH_FN(morphANDI_F06U) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns16 uimm = state->info.uimm;
    BINOPRRC(vmi_AND, uimm, &flags_ZrSiOv);
}

V850_MORPH_FN(morphMOVHI_F06S) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns16 simm = state->info.simm;
    BINOPRRC(vmi_ADD, SHIFTL(simm,16), 0);
}

V850_MORPH_FN(morphORI_F06U) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns16 uimm = state->info.uimm;
    BINOPRRC(vmi_OR, uimm, &flags_ZrSiOv);
}

V850_MORPH_FN(morphXORI_F06U) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns16 uimm = state->info.uimm;
    BINOPRRC(vmi_XOR, uimm, &flags_ZrSiOv);
}

V850_MORPH_FN(morphMOV_F06UA) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_WR(reg1);
    Uns32 uimm = state->info.uimm;

    if (VMI_REG_EQUAL(gpr_reg1, VMI_NOREG)) {
        VMI_ABORT("%s: Attempt mov imm32, r0", FUNC_NAME);  // LCOV_EXCL_LINE
    } else {
        vmimtMoveRC(V850_GPR_BITS, gpr_reg1, uimm);
    }
}

V850_MORPH_FN(morphLD_BU_F07C) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int32 sdisp = state->info.sdisp;

    load(gpr_reg2, gpr_reg1, sdisp, 8, False, state->info.arch);
}

V850_MORPH_FN(morphLD_B_F07LA) {
    //
    // Supported Architecture=V850_ISA_E0
    //

    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int32 sdisp = state->info.sdisp;

    load(gpr_reg2, gpr_reg1, sdisp, 8, True, state->info.arch);
}

V850_MORPH_FN(morphLD_H_F07LB) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int32 sdisp = state->info.sdisp;

    load(gpr_reg2, gpr_reg1, sdisp, 16, True, state->info.arch);
}

V850_MORPH_FN(morphLD_HU_F07LB) {
    //
    // Supported Architecture=V850_ISA_E1
    //

    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int32 sdisp = state->info.sdisp;

    load(gpr_reg2, gpr_reg1, sdisp, 16, False, state->info.arch);
}

V850_MORPH_FN(morphLD_W_F07LB) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int32 sdisp = state->info.sdisp;

    load(gpr_reg2, gpr_reg1, sdisp, 32, True, state->info.arch);
}

V850_MORPH_FN(morphST_B_F07SA) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int32 sdisp = state->info.sdisp;

    store(gpr_reg2, gpr_reg1, sdisp, 8, True, state->info.arch);
}

V850_MORPH_FN(morphST_H_F07SB) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int32 sdisp = state->info.sdisp;

    store(gpr_reg2, gpr_reg1, sdisp, 16, True, state->info.arch);
}

V850_MORPH_FN(morphST_W_F07SB) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Int32 sdisp = state->info.sdisp;

    store(gpr_reg2, gpr_reg1, sdisp, 32, True, state->info.arch);
}


V850_MORPH_FN(morphCLR1_F08) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 bit = state->info.bit;
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Int32 sdisp = state->info.sdisp;

    bitOP(bit, gpr_reg1, sdisp, vmi_ANDN);
}

V850_MORPH_FN(morphNOT1_F08) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 bit = state->info.bit;
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Int32 sdisp = state->info.sdisp;

    bitOP(bit, gpr_reg1, sdisp, vmi_XOR);
}

V850_MORPH_FN(morphSET1_F08) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 bit = state->info.bit;
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Int32 sdisp = state->info.sdisp;

    bitOP(bit, gpr_reg1, sdisp, vmi_OR);
}

V850_MORPH_FN(morphTST1_F08) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 bit = state->info.bit;
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Int32 sdisp = state->info.sdisp;

    memEndian   endian  = getEndian();

    // First perform a byte read
    vmimtLoadRRO(8, 8, sdisp, V850_TMP_WR(0), gpr_reg1, endian, False, False);

    // Test the bit for Zero to set the Z flag
    Uns8 setBit = 0x1 << bit;
    vmimtBinopRRC(8, vmi_AND, VMI_NOREG, V850_TMP_RD(0), setBit, &flags_Zr);
}

V850_MORPH_FN(morphSASF_F09) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 cccc = state->info.cccc;
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);

//    vmiReg      reg2    = getuRd1(&state->info);
//    Int32       cond    = state->info.cond;

    v850CondAction action = emitPrepareCondition(cccc);

    // Firstly always shift left reg2
    vmimtBinopRC(V850_GPR_BITS, vmi_SHL, gpr_reg2, 1, 0);

    // if test is true then perform logical OR with 0x1
    // V850_TEMPL_REG
    if(action.op==ACO_ALWAYS) {
        vmimtBinopRC(V850_GPR_BITS, vmi_OR, gpr_reg2, 0x1, 0);
    } else {
        vmimtBinopRRC(V850_GPR_BITS, vmi_OR, V850_TMP_WR(0), gpr_reg2, 0x1, 0);
        vmimtCondMoveRRR(V850_GPR_BITS, action.flag, action.op==ACO_TRUE, gpr_reg2, V850_TMP_RD(0), gpr_reg2);
    }
}

V850_MORPH_FN(morphSETF_F09) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 cccc = state->info.cccc;
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);

    v850CondAction action = emitPrepareCondition(cccc);
    if(action.op==ACO_ALWAYS) {
        vmimtMoveRC(V850_GPR_BITS, gpr_reg2, 1);
    } else {
        vmimtCondMoveRCC(V850_GPR_BITS, action.flag, action.op==ACO_TRUE, gpr_reg2, 1, 0);
    }
}

V850_MORPH_FN(morphSAR_F09RR) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);

    BINOPRR(vmi_SAR, &flags_CoZrSi);
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);
}

V850_MORPH_FN(morphSHL_F09RR) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    BINOPRR(vmi_SHL, &flags_CoZrSi);
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);
}

V850_MORPH_FN(morphSHR_F09RR) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    BINOPRR(vmi_SHR, &flags_CoZrSi);
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);
}

V850_MORPH_FN(morphCLR1_F09RS2) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    Uns8 reg2 = state->info.reg2;

    vmiReg rs1 = V850_GPR_RD(reg2);
    vmiReg rs2 = V850_GPR_WR(reg1);

    memEndian   endian  = getEndian();

    // Generate the shift value in a register V850_TEMPH_REG
    vmimtMoveRC(V850_GPR_BITS, V850_TMP_WR(1), 0x1);
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(0), rs1, 0x7, 0);
    vmimtBinopRR(V850_GPR_BITS, vmi_SHL, V850_TMP_WR(1), V850_TMP_RD(0), 0);

    // First perform a byte read
    vmimtLoadRRO(8, 8, 0, V850_TMP_WR(0), rs2, endian, False, False);

    // Test the bit for Zero to set the Z flag
    vmimtBinopRRR(8, vmi_AND, VMI_NOREG, V850_TMP_RD(0), V850_TMP_RD(1), &flags_Zr);

    // UNSet the bit in the TEMPREG
    vmimtBinopRR(8, vmi_ANDN, V850_TMP_WR(0), V850_TMP_RD(1), 0);

    // Write back the TEMPREG to byte
    vmimtStoreRRO(8, 0, rs2, V850_TMP_RD(0), endian, False);
}



V850_MORPH_FN(morphNOT1_F09RS2) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    Uns8 reg2 = state->info.reg2;

    vmiReg rs1 = V850_GPR_RD(reg2);
    vmiReg rs2 = V850_GPR_WR(reg1);

    memEndian   endian  = getEndian();

    // Generate the shift value in a register V850_TEMPH_REG
    vmimtMoveRC(V850_GPR_BITS, V850_TMP_WR(1), 0x1);
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(0), rs1, 0x7, 0);
    vmimtBinopRR(V850_GPR_BITS, vmi_SHL, V850_TMP_WR(1), V850_TMP_RD(0), 0);

    // First perform a byte read
    vmimtLoadRRO(8, 8, 0, V850_TMP_WR(0), rs2, endian, False, False);

    // Test the bit for Zero to set the Z flag
    vmimtBinopRRR(8, vmi_AND, VMI_NOREG, V850_TMP_RD(0), V850_TMP_RD(1), &flags_Zr);

    // UNSet the bit in the TEMPREG
    vmimtBinopRR(8, vmi_XOR, V850_TMP_WR(0), V850_TMP_RD(1), 0);

    // Write back the TEMPREG to byte
    vmimtStoreRRO(8, 0, rs2, V850_TMP_RD(0), endian, False);
}

V850_MORPH_FN(morphSET1_F09RS2) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    Uns8 reg2 = state->info.reg2;

    vmiReg rs1 = V850_GPR_RD(reg2);
    vmiReg rs2 = V850_GPR_WR(reg1);

    memEndian   endian  = getEndian();

    // Generate the shift value in a register V850_TEMPH_REG
    vmimtMoveRC(V850_GPR_BITS, V850_TMP_WR(1), 0x1);
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(0), rs1, 0x7, 0);
    vmimtBinopRR(V850_GPR_BITS, vmi_SHL, V850_TMP_WR(1), V850_TMP_RD(0), 0);

    // First perform a byte read
    vmimtLoadRRO(8, 8, 0, V850_TMP_WR(0), rs2, endian, False, False);

    // Test the bit for Zero to set the Z flag
    vmimtBinopRRR(8, vmi_AND, VMI_NOREG, V850_TMP_RD(0), V850_TMP_RD(1), &flags_Zr);

    // Set the bit in the TEMPREG
    vmimtBinopRR(8, vmi_OR, V850_TMP_WR(0), V850_TMP_RD(1), 0);

    // Write back the TEMPREG to byte
    vmimtStoreRRO(8, 0, rs2, V850_TMP_RD(0), endian, False);
}

V850_MORPH_FN(morphTST1_F09RS2) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    Uns8 reg2 = state->info.reg2;

    vmiReg rs1 = V850_GPR_RD(reg2);
    vmiReg rs2 = V850_GPR_WR(reg1);

    memEndian   endian  = getEndian();

    // Generate the shift value in a register V850_TEMPH_REG
    vmimtMoveRC(V850_GPR_BITS, V850_TMP_WR(1), 0x1);
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(0), rs1, 0x7, 0);
    vmimtBinopRR(V850_GPR_BITS, vmi_SHL, V850_TMP_WR(1), V850_TMP_RD(0), 0);

    // First perform a byte read
    vmimtLoadRRO(8, 8, 0, V850_TMP_WR(0), rs2, endian, False, False);

    // Test the bit for Zero to set the Z flag
    vmimtBinopRRR(8, vmi_AND, VMI_NOREG, V850_TMP_WR(0), V850_TMP_RD(1), &flags_Zr);
}

static void searchInRegister(vmiReg tgt, vmiReg src, vmiUnop op, Uns32 CYMask) {
    vmiLabelP setflags = vmimtNewLabel();
    //
    // bitpos 31=1, bitpos 0=32
    //

    //
    // Init (temp) result to 0, and ZR=1
    //
    vmimtMoveRC(V850_GPR_BITS, V850_TMP_WR(0), 0);

    //
    // Special cases
    // SCH0 && reg2==0xFFFFFFFF
    // SCH1 && reg2==0x00000000
    //
    Uns32 special = (op==vmi_CLO || op==vmi_CTO) ? 0xFFFFFFFF : 0x00000000;
    vmimtCompareRCJumpLabel(V850_GPR_BITS, vmi_COND_EQ, src, special, setflags);

    //
    // else calculate and adjust +1
    //
    vmimtUnopRR(V850_GPR_BITS, op, V850_TMP_WR(0), src, 0);
    vmimtBinopRC(V850_GPR_BITS, vmi_ADD, V850_TMP_WR(0), 1, 0);

    //
    // Set remaining flags
    //
    vmimtInsertLabel(setflags);
    //  Z = (gpr_reg3==0) ? 1 : 0
    vmimtBinopRC(V850_GPR_BITS, vmi_OR, V850_TMP_WR(0), 0, &flags_Zr);

    // CY = (src == CYMask)
    vmimtCompareRC(V850_GPR_BITS, vmi_COND_EQ, src, CYMask, V850_FLG_PSW_CO_WR);

    // OV == S == 0
    vmimtMoveRC(V850_GPR_BITS/4, V850_FLG_PSW_OV_WR, 0);
    vmimtMoveRC(V850_GPR_BITS/4, V850_FLG_PSW_SI_WR, 0);

    // copy to target register
    vmimtMoveRR(V850_GPR_BITS, tgt, V850_TMP_RD(0));
}

V850_MORPH_FN(morphSCH0L_F09RR2) {
    //
    // Supported Architecture=ISA_E2
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    searchInRegister(gpr_reg3, gpr_reg2, vmi_CLO, 0xFFFFFFFE);
}

V850_MORPH_FN(morphSCH0R_F09RR2) {
    //
    // Supported Architecture=ISA_E2
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    searchInRegister(gpr_reg3, gpr_reg2, vmi_CTO, 0x7FFFFFFF);
}

V850_MORPH_FN(morphSCH1L_F09RR2) {
    //
    // Supported Architecture=ISA_E2
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    searchInRegister(gpr_reg3, gpr_reg2, vmi_CLZ, 0x00000001);
}

V850_MORPH_FN(morphSCH1R_F09RR2) {
    //
    // Supported Architecture=ISA_E2
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    searchInRegister(gpr_reg3, gpr_reg2, vmi_CTZ, 0x80000000);
}

V850_MORPH_FN(morphCTRET_F10A) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    //  PSW <- CTPSW
    vmimtRegWriteImpl("PSW");
    vmimtArgProcessor();
    vmimtArgReg(V850_GPR_BITS, V850_SPR_CTPSW_RD);
    vmimtCall((vmiCallFn)vmic_Value_to_PSW);

    //
    // return to CTPC
    //
    vmimtUncondJumpReg(0, V850_SPR_CTPC_RD, VMI_NOREG, vmi_JH_NONE);
}

V850_MORPH_FN(morphDBRET_F10A) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    // Uns8 b16 = state->info.b16;
    morphUnimplemented("DBRET_F10A");
}

V850_MORPH_FN(morphDI_F10A) {
    //
    // Supported Architecture=V850_ISA_E0
    //

    // RH850G3M UM page 216.
    // If the MCTL.UIC bit has been cleared to 0, this instruction is a supervisor-level instruction.
    // If the MCTL.UIC bit has been set to 1, this instruction can always be executed.

    // @@@shinbo: UM_PrivException or checking state->v850->mode might be called in execution time, not in morph time ?

    vmiLabelP UIC_1 = vmimtNewLabel();
    vmiLabelP END   = vmimtNewLabel();

    Bool UserMode = (state->v850->mode==RH850_M_USER) || (state->v850->mode==RH850_M_USER_MPU);

    if (UserMode) {
        vmimtBinopRRC          (V850_GPR_BITS, vmi_AND    , V850_TMP_WR(0), V850_SPR_MCTL_RD, 0x00000001, 0);
        vmimtCompareRCJumpLabel(V850_GPR_BITS, vmi_COND_EQ, V850_TMP_RD(0),                   0x00000001, UIC_1);

        // UIC=0
        // Supervisor instruction Exception
        vmimtArgProcessor();
        vmimtCall((vmiCallFn) v850ProcessPIE);
        vmimtUncondJumpLabel(END);
    }

    vmimtInsertLabel(UIC_1);
    vmimtMoveRC(8, V850_FLG_PSW_ID_WR, 1);

    vmimtInsertLabel(END);
}

static void vmic_evaluate_pending_interrupts (v850P v850) {
    v850TestInterrupt(v850);
}

V850_MORPH_FN(morphEI_F10A) {
    //
    // Supported Architecture=V850_ISA_E0
    //

    vmiLabelP UIC_1 = vmimtNewLabel();
    vmiLabelP END   = vmimtNewLabel();

    Bool UserMode = (state->v850->mode==RH850_M_USER) || (state->v850->mode==RH850_M_USER_MPU);

    if (UserMode) {
        vmimtBinopRRC          (V850_GPR_BITS, vmi_AND    , V850_TMP_WR(0), V850_SPR_MCTL_RD, 0x00000001, 0);
        vmimtCompareRCJumpLabel(V850_GPR_BITS, vmi_COND_EQ, V850_TMP_RD(0),                   0x00000001, UIC_1);

        // UIC=0
        // Supervisor instruction Exception
        vmimtArgProcessor();
        vmimtCall((vmiCallFn) v850ProcessPIE);
        vmimtUncondJumpLabel(END);
    }

    vmimtInsertLabel(UIC_1);
    vmimtMoveRC(8, V850_FLG_PSW_ID_WR, 0);

    //
    // We need to check if any Interrupts are pending, and if so
    // make a call to evaluate the pending interrupt
    //
    vmimtArgProcessor();
    vmimtCall((vmiCallFn)vmic_evaluate_pending_interrupts);

    vmimtInsertLabel(END);

}

static void vmic_WriteNetPort_mireti(v850P v850) {
    vmirtWriteNetPort((vmiProcessorP)v850, v850->netValue.mireti, 1);

}

static void vmic_updateISPR(v850P v850) {

    // RH850G3M UM 4.2.1 (1) EP bit of PSW register
    // Depending on the EP bit setting, the operation changes when the EIRET or FERET instruction is executed. If the
    // EP bit is cleared to 0, the bit with the highest priority (0 is the highest) among the bits set to 1 in ISPR.ISP15 to
    // ISPR.ISP0 is cleared to 0. Also, the end of the exception handling routine is reported to the external interrupt
    // controller.

    // RH850G3M UM 3.3.1 (5) INTCFG - Interrupt function setting
    // INTCFG.ISPC :
    // If this bit is set to 1, the bits of the ISPR register are not updated by the
    // acknowledgment of an interrupt (EIINTn) or by execution of the EIRET
    // instruction. In this case, the bits can be updated by an LDSR instruction
    // executed by the program.

    if (v850->configInfo.arch == RH850G3M) {
        if (v850->FLG_PSW_EP == 0) {                // 17/03/06 esol trinity shinbo
            if (v850->SPR_INTCFG.ISPC == 0) {
                // When doing EIRET instruction, clear to 0 smallest bit set to 1.
                v850->SPR_ISPR.reg &= (v850->SPR_ISPR.reg - 1);
            }
        }
    }
}

static void updateISPR() {
    vmimtArgProcessor();
    vmimtCall((vmiCallFn) vmic_updateISPR);
}

static void restorePSW (vmiReg psw) {
    vmimtRegWriteImpl("PSW");
    vmimtArgProcessor();
    vmimtArgReg(V850_GPR_BITS, psw);
    vmimtCall((vmiCallFn)vmic_Value_to_PSW);
}

static void notifyRETI () {
    vmiLabelP ep = vmimtNewLabel();
    vmimtCondJumpLabel(V850_FLG_PSW_EP_RD, True, ep);
    vmimtArgProcessor();
    vmimtCall((vmiCallFn)vmic_WriteNetPort_mireti);

    vmimtInsertLabel(ep);
}

V850_MORPH_FN(morphEIRET_F10A) {
    //
    // Supported Architecture=ISA_E2
    //
    if (UM_PrivException(state)) {
    } else {

        //
        updateISPR();

        // PSW = V850_EIPSW_REG
        restorePSW(V850_SPR_EIPSW_RD);

        // need to send event on mireti signal
        notifyRETI();

        // PC = V850_EIPC_REG
        vmimtUncondJumpReg(0, V850_SPR_EIPC_RD, VMI_NOREG, vmi_JH_NONE);
    }
}

V850_MORPH_FN(morphFERET_F10A) {
    //
    // Supported Architecture=ISA_E2
    //
    if (UM_PrivException(state)) {
    } else {
        // PSW = V850_EIPSW_REG
        restorePSW(V850_SPR_FEPSW_RD);

        // need to send event on mireti signal
        notifyRETI();

        // PC = V850_EIPC_REG
        vmimtUncondJumpReg(0, V850_SPR_FEPC_RD, VMI_NOREG, vmi_JH_NONE);
    }
}

V850_MORPH_FN(morphHALT_F10A) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    // Uns8 b16 = state->info.b16;
    if (UM_PrivException(state)) {
    } else {
        vmimtHalt();
    }
}

V850_MORPH_FN(morphRETI_F10A) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    vmiLabelP noep       = vmimtNewLabel();
    vmiLabelP nonmi      = vmimtNewLabel();

    // if      PSW.EP { PC = EIPC; PSW = EIPSW } {
    // else if PSW.NP { PC = FEPC; PSW = FEPSW } {
    // else           { PC = EIPC; PSW = EIPSW }

    vmimtCondJumpLabel(V850_FLG_PSW_EP_RD, False, noep);
    // if PSW.EP == True
    // PSW = V850_EIPSW_REG
    restorePSW(V850_SPR_EIPSW_RD);
    // PC = V850_EIPC_REG
    vmimtUncondJumpReg(0, V850_SPR_EIPC_RD, VMI_NOREG, vmi_JH_NONE);

    vmimtInsertLabel(noep);
    vmimtCondJumpLabel(V850_FLG_PSW_NP_RD, False, nonmi);
    // else if PSW.NP == True
    // PSW = V850_FEPSW_REG
    restorePSW(V850_SPR_FEPSW_RD);
    // PC = V850_FEPC_REG
    vmimtUncondJumpReg(0, V850_SPR_FEPC_RD, VMI_NOREG, vmi_JH_NONE);

    vmimtInsertLabel(nonmi);
    // else if PSW.NP == False && PSW.EP == False
    // PSW = V850_EIPSW_REG
    restorePSW(V850_SPR_EIPSW_RD);
    // need to send event on mireti signal
    notifyRETI();
    // PC = V850_EIPC_REG
    vmimtUncondJumpReg(0, V850_SPR_EIPC_RD, VMI_NOREG, vmi_JH_NONE);
}

V850_MORPH_FN(morphTRAP_F10B) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns16 uimm = state->info.uimm;

    Uns32 RETPC = state->info.thisPC + state->info.instrsize;
    Int32 VPC   = 0x40 | (uimm & 0x10);
    Uns32 CC    = VPC  | uimm;

    // EIPC <- PC
    vmimtMoveRC(V850_GPR_BITS, V850_SPR_EIPC_WR, RETPC);

    // EIPSW <- PSW
    vmimtRegReadImpl("PSW");
    vmimtArgProcessor();
    vmimtCallResult((vmiCallFn)v850PackPSW, V850_GPR_BITS, V850_SPR_EIPSW_WR);

    // ECR.EICC = alias(EIIC(E2R))
    vmimtMoveRC(V850_GPR_BITS, V850_SPR_EIIC_WR, CC);

    // PSW.EP <- 1
    vmimtMoveRC(8, V850_FLG_PSW_EP_WR, 1);

    // PSW.ID <- 1
    vmimtMoveRC(8, V850_FLG_PSW_ID_WR, 1);

    // PC <- Vector PC
    vmimtUncondJump(0, VPC, VMI_NOREG, vmi_JH_NONE);
}

V850_MORPH_FN(morphDIV_F11) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    divFmt11(gpr_reg1, gpr_reg2, gpr_reg3, vmi_IDIV, 32, &flags_ZrSi);
}

V850_MORPH_FN(morphDIVH_F11) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    divFmt11(gpr_reg1, gpr_reg2, gpr_reg3, vmi_IDIV, 16, &flags_ZrSi);
}

V850_MORPH_FN(morphDIVHU_F11) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    divFmt11(gpr_reg1, gpr_reg2, gpr_reg3, vmi_DIV, 16, &flags_ZrSi);
}

V850_MORPH_FN(morphDIVQ_F11) {
    //
    // Supported Architecture=ISA_E2
    //
    morphDIV_F11(state);
}

V850_MORPH_FN(morphDIVQU_F11) {
    //
    // Supported Architecture=ISA_E2
    //
    morphDIVU_F11(state);
}

V850_MORPH_FN(morphDIVU_F11) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    divFmt11(gpr_reg1, gpr_reg2, gpr_reg3, vmi_DIV, 32, &flags_ZrSi);
}

V850_MORPH_FN(morphMUL_F11) {
     Uns8 reg1 = state->info.reg1;
     Uns8 reg2 = state->info.reg2;
     Uns8 reg3 = state->info.reg3;

    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmimtMulopRRR(V850_GPR_BITS, vmi_IMUL, gpr_reg3, gpr_reg2, gpr_reg2, gpr_reg1, 0);
}

V850_MORPH_FN(morphMULU_F11) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg1 = state->info.reg1;
    Uns8 reg2 = state->info.reg2;
    Uns8 reg3 = state->info.reg3;

   vmiReg gpr_reg1 = V850_GPR_RD(reg1);
   vmiReg gpr_reg2 = V850_GPR_WR(reg2);
   vmiReg gpr_reg3 = V850_GPR_WR(reg3);

   vmimtMulopRRR(V850_GPR_BITS, vmi_MUL, gpr_reg3, gpr_reg2, gpr_reg2, gpr_reg1, 0);
}

V850_MORPH_FN(morphSAR_F11) {
    //
    // Supported Architecture=V850_ISA_E2
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    BINOPRRR(vmi_SAR, &flags_CoZrSi);
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);
}

V850_MORPH_FN(morphSATADD_F11) {
    //
    // Supported Architecture=V850_ISA_E2
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    BINOPRRR(vmi_ADDSQ, &flags_CoZrSiOv);
    emitSaturateCheck(gpr_reg3);
}

V850_MORPH_FN(morphSATSUB_F11) {
    //
    // Supported Architecture=V850_ISA_E2
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    BINOPRRR(vmi_SUBSQ, &flags_CoZrSiOv);
    emitSaturateCheck(gpr_reg3);
}

V850_MORPH_FN(morphSHL_F11) {
    //
    // Supported Architecture=V850_ISA_E2
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    BINOPRRR(vmi_SHL, &flags_CoZrSi);
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);
}

V850_MORPH_FN(morphSHR_F11) {
    //
    // Supported Architecture=V850_ISA_E2
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    BINOPRRR(vmi_SHR, &flags_CoZrSi);
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);
}

V850_MORPH_FN(morphMAC_F11A) {
    //
    // Supported Architecture=V850_ISA_E2
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
    // r4(64) = (r2(32) * r1(32)) + r3(64)
    //
    vmimtMulopRRR(V850_GPR_BITS,   vmi_IMUL, V850_TMP_WR(1), V850_TMP_WR(0), gpr_reg2, gpr_reg1, 0);
    vmimtBinopRRR(V850_GPR_BITS*2, vmi_ADD, gpr_reg4, V850_TMP_RD(0), gpr_reg3, 0);
}

V850_MORPH_FN(morphMACU_F11A) {
    //
    // Supported Architecture=V850_ISA_E2
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
    // r4(64) = (r2(32) * r1(32)) + r3(64)
    //
    vmimtMulopRRR(V850_GPR_BITS,   vmi_MUL, V850_TMP_WR(1), V850_TMP_WR(0), gpr_reg2, gpr_reg1, 0);
    vmimtBinopRRR(V850_GPR_BITS*2, vmi_ADD, gpr_reg4, V850_TMP_RD(0), gpr_reg3, 0);
}

V850_MORPH_FN(morphADF_F11B) {
    //
    // Supported Architecture=V850_ISA_E2
    //
    Uns8 cccc = state->info.cccc;
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    binopRRRCCCC(vmi_ADC, cccc, gpr_reg3, gpr_reg2, gpr_reg1);
}

V850_MORPH_FN(morphCMOV_F11B) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 cccc = state->info.cccc;
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    v850CondAction action = emitPrepareCondition(cccc);

    if(action.op==ACO_ALWAYS) {
        vmimtMoveRR(V850_GPR_BITS, gpr_reg3, gpr_reg1);
    } else {
        vmimtCondMoveRRR(V850_GPR_BITS, action.flag, action.op==ACO_TRUE, gpr_reg3, gpr_reg1, gpr_reg2);
    }

}

V850_MORPH_FN(morphSBF_F11B) {
    //
    // Supported Architecture=V850_ISA_E2
    //
    Uns8 cccc = state->info.cccc;
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    binopRRRCCCC(vmi_SBB, cccc, gpr_reg3, gpr_reg2, gpr_reg1);
}

V850_MORPH_FN(morphMUL_F12S) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg2 = state->info.reg2;
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int16 simm = state->info.simm;

    //
    // TODO - require a vmimtMulopRRC();
    //
    // Move constant into temporary register
    vmimtMoveRC(V850_GPR_BITS, V850_TMP_WR(0), simm);

    vmimtMulopRRR(V850_GPR_BITS, vmi_IMUL, gpr_reg3, gpr_reg2, gpr_reg2, V850_TMP_RD(0), 0);
}

V850_MORPH_FN(morphMULU_F12U) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg2 = state->info.reg2;
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Uns16 uimm = state->info.uimm;

    //
    // TODO - require a vmimtMulopRRC();
    //
    // Move constant into temporary register
    vmimtMoveRC(V850_GPR_BITS, V850_TMP_WR(0), uimm);

    vmimtMulopRRR(V850_GPR_BITS, vmi_MUL, gpr_reg3, gpr_reg2, gpr_reg2, V850_TMP_RD(0), 0);
}

V850_MORPH_FN(morphCAXI_F11C) {
    //
    // Supported Architecture=ISA_E2
    //
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmiLabelP nostore = vmimtNewLabel();
    vmimtAtomic();

    // TMP[0] = MEM[reg1]
    load(V850_TMP_WR(0), gpr_reg1, 0, 32, True, state->info.arch);

    // TMP[1] = reg2 - TMP[0]
    vmimtBinopRRR(V850_GPR_BITS, vmi_SUB, V850_TMP_WR(1), gpr_reg2, V850_TMP_RD(0), &flags_CoZrSiOv);

    // if (TMP[1]==0) {
    //     MEM[reg1] = reg3;
    // }
    vmimtCompareRCJumpLabel(V850_GPR_BITS, vmi_COND_NE, V850_TMP_RD(1), 0, nostore);
    store(gpr_reg3, gpr_reg1, 0, 32, True, state->info.arch);

    vmimtInsertLabel(nostore);
    // reg3 = TMP[0];
    vmimtMoveRR(V850_GPR_BITS, gpr_reg3, V850_TMP_RD(0));
}

static void jarl2 (v850MorphStateP state, Uns8 lr, Uns8 tr) {
    v850Addr pc    = state->info.thisPC;
    v850Addr isize = state->info.instrsize;
    vmiReg  gpr_lr = V850_GPR_WR(lr);
    vmiReg  gpr_tr = V850_GPR_WR(tr);
    vmiJumpHint jump_hint = vmi_JH_NONE;

    //
    // indicate that this register may contain a link address
    //
    if (lr) {
        jump_hint = vmi_JH_CALL;
        state->v850->REG_RETMASK |= (1<<lr);
    }

    vmimtUncondJumpReg(pc+isize, gpr_tr, gpr_lr, jump_hint);
}

V850_MORPH_FN(morphCMOV_F12A) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    // Uns8 b16 = state->info.b16;
    Uns8 cccc = state->info.cccc;
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int16 simm = state->info.simm;

    v850CondAction action = emitPrepareCondition(cccc);

    if(action.op==ACO_ALWAYS) {
        vmimtMoveRC(V850_GPR_BITS, gpr_reg3, simm);
    } else {
        vmimtCondMoveRCR(V850_GPR_BITS, action.flag, action.op==ACO_TRUE, gpr_reg3, simm, gpr_reg2);
    }
}

V850_MORPH_FN(morphBSH_F12B) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmiReg reg2L  = gpr_reg2;
    vmiReg reg3L  = gpr_reg3;
    vmiReg reg2H  = VMI_REG_DELTA(reg2L, 2);
    vmiReg reg3H  = VMI_REG_DELTA(reg3L, 2);

    vmiReg reg3B0 = reg3L;
    vmiReg reg3B1 = VMI_REG_DELTA(reg3L, 1);

    // 16 bit byte swap
    vmimtUnopRR(V850_GPR_BITS/2, vmi_SWP, reg3L, reg2L, &flags_Zr);
    vmimtUnopRR(V850_GPR_BITS/2, vmi_SWP, reg3H, reg2H, &flags_Si);

    // if reg3[7:0]==0 or reg3[15:8]==0 CY=1 - flagsZtoC
    vmimtBinopRRC(V850_GPR_BITS/4, vmi_AND, VMI_NOREG, reg3B0, 0xff, &flags_CoFromZr);
    vmimtBinopRRC(V850_GPR_BITS/4, vmi_AND, VMI_NOREG, reg3B1, 0xff, &flags_TmpFromZr);
    vmimtBinopRR(V850_GPR_BITS/4, vmi_OR, V850_FLG_PSW_CO_WR, V850_TMP_RD(0), 0);
}

V850_MORPH_FN(morphBSW_F12B) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmiReg reg3B0 = gpr_reg3;
    vmiReg reg3B1 = VMI_REG_DELTA(gpr_reg3, 1);
    vmiReg reg3B2 = VMI_REG_DELTA(gpr_reg3, 2);
    vmiReg reg3B3 = VMI_REG_DELTA(gpr_reg3, 3);

    // This operation affects the Z and S flags
    vmimtUnopRR(V850_GPR_BITS, vmi_SWP, gpr_reg3, gpr_reg2, &flags_ZrSi);

    // Generate the carry flag by looking at the individual byte lanes
    vmimtBinopRRC(V850_GPR_BITS/4, vmi_AND, VMI_NOREG, reg3B0, 0xff, &flags_CoFromZr);
    vmimtBinopRRC(V850_GPR_BITS/4, vmi_AND, VMI_NOREG, reg3B1, 0xff, &flags_TmpFromZr);
    vmimtBinopRR(V850_GPR_BITS/4, vmi_OR, V850_FLG_PSW_CO_WR, V850_TMP_RD(0), 0);

    vmimtBinopRRC(V850_GPR_BITS/4, vmi_AND, VMI_NOREG, reg3B2, 0xff, &flags_TmpFromZr);
    vmimtBinopRR(V850_GPR_BITS/4, vmi_OR, V850_FLG_PSW_CO_WR, V850_TMP_RD(0), 0);

    vmimtBinopRRC(V850_GPR_BITS/4, vmi_AND, VMI_NOREG, reg3B3, 0xff, &flags_TmpFromZr);
    vmimtBinopRR(V850_GPR_BITS/4, vmi_OR, V850_FLG_PSW_CO_WR, V850_TMP_RD(0), 0);
}

V850_MORPH_FN(morphHSH_F12B) {
    //
    // Supported Architecture=V850_ISA_E2
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    // reg3 <= reg2
    //  S   <= (reg3[31]==1) ? 1 : 0
    vmimtBinopRRC(V850_GPR_BITS, vmi_ADD, gpr_reg3, gpr_reg2, 0, &flags_Si);

    // CY   <= (reg3[15:0]==0) ? 1 : 0
    //  Z   <= (reg3[15:0]==0) ? 1 : 0
    vmimtBinopRRC(V850_GPR_BITS/2, vmi_AND, VMI_NOREG, gpr_reg2, 0xffff, &flags_Zr);
    vmimtMoveRR(V850_GPR_BITS/4, V850_FLG_PSW_CO_WR, V850_FLG_PSW_ZR_RD);

    // OV   <= 0
    vmimtMoveRC(V850_GPR_BITS/4, V850_FLG_PSW_OV_WR, 0);
}

V850_MORPH_FN(morphHSW_F12B) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 reg2 = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8 reg3 = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmiReg reg2H = VMI_REG_DELTA(gpr_reg2, 2);

    // Shift 2 bytes left
    vmimtBinopRRC(V850_GPR_BITS, vmi_SHL, gpr_reg3, gpr_reg2, V850_GPR_BITS/2, 0);

    // OR the two halfwords together
    vmimtBinopRR(V850_GPR_BITS, vmi_OR, gpr_reg3, reg2H, &flags_ZrSi);

    // if reg3[15:0]==0 or reg3[31:16]==0 CY=1 - flagsZtoC
    vmimtBinopRRC(V850_GPR_BITS/2, vmi_AND, VMI_NOREG, gpr_reg2, 0xffff, &flags_CoFromZr);
    vmimtBinopRRC(V850_GPR_BITS/2, vmi_AND, VMI_NOREG, reg2H,    0xffff, &flags_TmpFromZr);
    vmimtBinopRR(V850_GPR_BITS/4, vmi_OR, V850_FLG_PSW_CO_WR, V850_TMP_RD(0), 0);
}

static void common_DISPOSE(Uns16 list12, Uns8 uimm5) {
    memEndian   endian   = getEndian();
    Int32       list12Iter;
    Int32       spOffset = uimm5 * 4;

//    vmiPrintf("common_DISPOSE list12=%08x uimm5=%02x\n", list12, uimm5);
    // iterate over the bits in list12 inputting regs
    // in [r31..r20]
    for(list12Iter=31; list12Iter>=20; list12Iter--) {
        if ((list12>>(list12Iter-20)) & 0x1) {
            vmimtLoadRRO(V850_GPR_BITS, V850_GPR_BITS, spOffset, V850_GPR_WR(list12Iter), V850_GPR_RD(V850_GPR_SP), endian, False, True);
            spOffset+=4;
        }
    }
    vmimtBinopRC(V850_GPR_BITS, vmi_ADD, V850_GPR_WR(V850_GPR_SP), spOffset, 0);
}

V850_MORPH_FN(morphDISPOSE_F13IL1) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns16 list12 = state->info.list12;
    Uns8 uimm5 = state->info.uimm5;

    common_DISPOSE(list12, uimm5);
}

V850_MORPH_FN(morphDISPOSE_F13IL2) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns16 list12 = state->info.list12;
    Uns8 reg1 = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8 uimm5 = state->info.uimm5;

    common_DISPOSE(list12, uimm5);

    vmimtUncondJumpReg(0, gpr_reg1, VMI_NOREG, vmi_JH_RETURN);
}

static void common_PREPARE(Uns16 list12, Uns8 uimm5) {
    memEndian   endian   = getEndian();
    Int32       list12Iter;
    Int32       spOffset = 0;

//    vmiPrintf("common_PREPARE list12=%03x uimm5=%02x\n", list12, uimm5);

    // iterate over the bits in list12 outputing regs
    // in [r31..r20]
    for(list12Iter=20; list12Iter<=31; list12Iter++) {
        if (list12 & 0x1) {
            spOffset-=4;
            vmimtStoreRRO(V850_GPR_BITS, spOffset, V850_GPR_RD(V850_GPR_SP), V850_GPR_RD(list12Iter), endian, True);
        }
        list12 >>= 1;
    }
    vmimtBinopRC(V850_GPR_BITS, vmi_ADD, V850_GPR_WR(V850_GPR_SP), (spOffset - (uimm5 * 4)), 0);
}


V850_MORPH_FN(morphPREPARE_F13LI) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns8 uimm5 = state->info.uimm5;
    Uns16 list12 = state->info.list12;

    common_PREPARE(list12, uimm5);
}

V850_MORPH_FN(morphPREPARE_F13LI00) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns16 list12 = state->info.list12;
    Uns8 uimm5 = state->info.uimm5;

    common_PREPARE(list12, uimm5);

    vmimtMoveRR(V850_GPR_BITS, V850_GPR_WR(V850_GPR_EP), V850_GPR_RD(V850_GPR_SP));
}

V850_MORPH_FN(morphPREPARE_F13LI01) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns16 list12 = state->info.list12;
    Int32 simm = state->info.simm;
    Uns8 uimm5 = state->info.uimm5;

    common_PREPARE(list12, uimm5);

    vmimtMoveRC(V850_GPR_BITS, V850_GPR_WR(V850_GPR_EP), simm);
}

V850_MORPH_FN(morphPREPARE_F13LI10) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns16 list12 = state->info.list12;
    Int32 simm = state->info.simm;
    Uns8 uimm5 = state->info.uimm5;

    common_PREPARE(list12, uimm5);

    vmimtMoveRC(V850_GPR_BITS, V850_GPR_WR(V850_GPR_EP), simm);

}

V850_MORPH_FN(morphPREPARE_F13LI11) {
    //
    // Supported Architecture=V850_ISA_E1
    //
    Uns16 list12 = state->info.list12;
    Int32 simm = state->info.simm;
    Uns8 uimm5 = state->info.uimm5;

    common_PREPARE(list12, uimm5);

    vmimtMoveRC(V850_GPR_BITS, V850_GPR_WR(V850_GPR_EP), simm);
}

//
// New for RH850
//
V850_MORPH_FN(morphLDL_W_F07D) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmimtAtomic();

    //
    // Set the reservation bit, addr & length
    // This must be cleared on interrupt / exception
    //
    vmimtMoveRC(V850_FLG_LL_BITS, V850_FLG_LL, 1);
    vmimtMoveRR(V850_REG_LL_BITS, V850_REG_LL, gpr_reg1);

    load(gpr_reg3, gpr_reg1, 0, 32, True, state->info.arch);
}

V850_MORPH_FN(morphSTC_W_F07D) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmimtAtomic();

    vmiLabelP FAIL = vmimtNewLabel();
    vmiLabelP END  = vmimtNewLabel();

    //
    // Test the state of the LL bit, before attempting the store
    //
    //    if (FLG_LL) {
    ///* OK */
    //        MEM[ADDR] = Data;
    //        reg3 <= 1;
    //    } else {
    ///* FAIL */
    //        reg3 <= 0;
    //    }
    ///* END */
    //    FLG_LL <= 0
    vmimtCompareRC(V850_FLG_TMP_BITS, vmi_COND_EQ, V850_FLG_LL, 0, V850_FLG_TMP_WR);
    vmimtCondJumpLabel(V850_FLG_TMP_RD, True, FAIL);

    //
    // Perform Store - OK
    //
    store(gpr_reg3, gpr_reg1, 0, 32, True, state->info.arch);
    vmimtMoveRC(V850_GPR_BITS, gpr_reg3, 1);
    vmimtUncondJumpLabel(END);

    //
    // No Store - FAIL
    //
    vmimtInsertLabel(FAIL);
    vmimtMoveRC(V850_GPR_BITS, gpr_reg3, 0);

    vmimtInsertLabel(END);
    vmimtMoveRC(V850_FLG_LL_BITS, V850_FLG_LL, 0);

}

static void common_BINS(v850MorphStateP state) {

    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg2     = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_WR(reg2);

    Uns8 lsb  = state->info.lsb;
    Uns8 msb  = state->info.msb;

    Uns32 ones   = 0xFFFFFFFF;
    Uns32 maskr1 = VECINDEX(ones, (msb-lsb), 0, 0);
    Uns32 maskr2 = ~(maskr1 << lsb);

    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(0), gpr_reg1, maskr1, 0);
    vmimtBinopRC( V850_GPR_BITS, vmi_SHL, V850_TMP_WR(0), lsb, 0);

    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, V850_TMP_WR(1), gpr_reg2, maskr2, 0);
    vmimtBinopRRR(V850_GPR_BITS, vmi_OR,  gpr_reg2, V850_TMP_RD(0), V850_TMP_RD(1), &flags_ZrSiOv);

}

V850_MORPH_FN(morphBINS_F09RPWR_0) {
    //
    // Supported Architecture=ISA_E3
    //
    common_BINS(state);
}

V850_MORPH_FN(morphBINS_F09RPWR_1) {
    //
    // Supported Architecture=ISA_E3
    //
    common_BINS(state);
}

V850_MORPH_FN(morphBINS_F09RPWR_2) {
    //
    // Supported Architecture=ISA_E3
    //
    common_BINS(state);
}

V850_MORPH_FN(morphCLL_F10) {
    //
    // Supported Architecture=ISA_E3
    //
    vmimtMoveRC(8, V850_FLG_LL, 0);
}

V850_MORPH_FN(morphSNOOZE_F10) {
    //
    // Supported Architecture=ISA_E3
    //
    // NOP
}

V850_MORPH_FN(morphCACHE_F10) {
    //
    // Supported Architecture=ISA_E3
    //
    UM_PrivException(state);
}

V850_MORPH_FN(morphCACHE_CHBII) {
    //
    // Supported Architecture=ISA_E3
    //
    // NOP Operation in Supv & User Mode
}

V850_MORPH_FN(morphCACHE_CIBII) {
    //
    // Supported Architecture=ISA_E3
    //
    UM_PrivException(state);
}

V850_MORPH_FN(morphCACHE_CFALI) {
    //
    // Supported Architecture=ISA_E3
    //
    UM_PrivException(state);
}

V850_MORPH_FN(morphCACHE_CISTI) {
    //
    // Supported Architecture=ISA_E3
    //
    UM_PrivException(state);
}

V850_MORPH_FN(morphCACHE_CILDI) {
    //
    // Supported Architecture=ISA_E3
    //
    UM_PrivException(state);
}

V850_MORPH_FN(morphPREF_F10) {
    //
    // Supported Architecture=ISA_E3
    //
    UM_PrivException(state);
}

V850_MORPH_FN(morphPREFI_F10) {
    //
    // Supported Architecture=ISA_E3
    //
    UM_PrivException(state);
}

V850_MORPH_FN(morphPUSHSP_F11) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8 rh = state->info.reg1;
    Uns8 rt = state->info.reg3;

    memEndian   endian   = getEndian();
    Int32       spOffset = 0;

    if (rh <= rt) {
        Uns8 cur = rh;
        Uns8 end = rt;
        while (cur <= end) {
            spOffset-=4;
            vmimtStoreRRO(V850_GPR_BITS, spOffset, V850_GPR_RD(V850_GPR_SP), V850_GPR_RD(cur), endian, True);
            cur = cur+1;
        }
        vmimtBinopRC(V850_GPR_BITS, vmi_ADD, V850_GPR_WR(V850_GPR_SP), spOffset, 0);
    }
}

V850_MORPH_FN(morphPOPSP_F11) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8 rh = state->info.reg1;
    Uns8 rt = state->info.reg3;

    memEndian   endian   = getEndian();
    Int32       spOffset = 0;

    if (rh <= rt) {
        Uns8 cur = rt;
        Uns8 end = rh;
        while (cur >= end) {
            vmimtLoadRRO(V850_GPR_BITS, V850_GPR_BITS, spOffset, V850_GPR_WR(cur), V850_GPR_RD(V850_GPR_SP), endian, False, True);
            spOffset+=4;
            cur = cur-1;
        }
        vmimtBinopRC(V850_GPR_BITS, vmi_ADD, V850_GPR_WR(V850_GPR_SP), spOffset, 0);
    }
}

static void commonFlags_ROTL(v850MorphStateP state) {
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    // OV <= 0
    vmimtMoveRC(V850_FLG_PSW_OV_BITS, V850_FLG_PSW_OV_WR, 0);

    // CY = !(RESULT[0])
    vmimtUnopRR( V850_FLG_PSW_CO_BITS, vmi_NOT, V850_FLG_PSW_CO_WR, gpr_reg3, 0);
    vmimtBinopRC(V850_FLG_PSW_CO_BITS, vmi_AND, V850_FLG_PSW_CO_WR, 0x1, 0);
}

V850_MORPH_FN(morphROTL_F07RRR) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg2     = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);

    vmimtBinopRRR(V850_GPR_BITS, vmi_ROL, gpr_reg3, gpr_reg2, gpr_reg1, &flags_CoZrSi);

    commonFlags_ROTL(state);
}

V850_MORPH_FN(morphROTL_F07IRR) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg2     = state->info.reg2;
    vmiReg gpr_reg2 = V850_GPR_RD(reg2);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Uns8 uimm5      = state->info.uimm5;

    vmimtBinopRRC(V850_GPR_BITS, vmi_ROL, gpr_reg3, gpr_reg2, uimm5, &flags_CoZrSi);

    commonFlags_ROTL(state);
}

V850_MORPH_FN(morphLD_DW_F14) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int32  sdisp    = state->info.sdisp;

    load(gpr_reg3, gpr_reg1, sdisp, 64, True, state->info.arch);
}

V850_MORPH_FN(morphST_DW_F14) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int32  sdisp    = state->info.sdisp;

    store(gpr_reg3, gpr_reg1, sdisp, 64, True, state->info.arch);
}

V850_MORPH_FN(morphBCOND_F07CC) {
    //
    // Supported Architecture=V850_ISA_E3
    //
    bcond(state);
}

V850_MORPH_FN(morphJARL_F11D) {
    //
    // Supported Architecture=V850_ISA_E3
    //
    // PC=GR[reg1]
    // GR[reg3]=PC+4
    Uns8 reg1 = state->info.reg1;
    Uns8 reg3 = state->info.reg3;

    jarl2(state, reg3, reg1);
}


// reg1 = reg1 - 1;
// if reg1 != 0
//     PC = PC - udisp
V850_MORPH_FN(morphLOOP_F07RI) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8     reg1     = state->info.reg1;
    vmiReg   gpr_reg1 = V850_GPR_RD(reg1);
    v850Addr targetPC = state->info.targetPC;

    vmimtBinopRC(V850_GPR_BITS, vmi_SUB, gpr_reg1, 1, &flags_CoZrSiOv);

    vmimtCondJump(V850_FLG_PSW_ZR_RD, False, 0, targetPC, VMI_NOREG, vmi_JH_RELATIVE);
}

V850_MORPH_FN(morphLD_BU_F14) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int32  sdisp    = state->info.sdisp;

    load(gpr_reg3, gpr_reg1, sdisp, 8, False, state->info.arch);
}

V850_MORPH_FN(morphLD_B_F14) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int32  sdisp    = state->info.sdisp;

    load(gpr_reg3, gpr_reg1, sdisp, 8, True, state->info.arch);
}

V850_MORPH_FN(morphLD_H_F14) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int32  sdisp    = state->info.sdisp;

    load(gpr_reg3, gpr_reg1, sdisp, 16, True, state->info.arch);
}

V850_MORPH_FN(morphLD_HU_F14) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int32  sdisp    = state->info.sdisp;

    load(gpr_reg3, gpr_reg1, sdisp, 16, False, state->info.arch);
}

V850_MORPH_FN(morphLD_W_F14) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int32  sdisp    = state->info.sdisp;

    load(gpr_reg3, gpr_reg1, sdisp, 32, True, state->info.arch);
}

V850_MORPH_FN(morphST_B_F14) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int32  sdisp    = state->info.sdisp;

    store(gpr_reg3, gpr_reg1, sdisp, 8, True, state->info.arch);
}

V850_MORPH_FN(morphST_H_F14) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int32  sdisp    = state->info.sdisp;

    store(gpr_reg3, gpr_reg1, sdisp, 16, True, state->info.arch);
}

V850_MORPH_FN(morphST_W_F14) {
    //
    // Supported Architecture=ISA_E3
    //
    Uns8   reg1     = state->info.reg1;
    vmiReg gpr_reg1 = V850_GPR_RD(reg1);
    Uns8   reg3     = state->info.reg3;
    vmiReg gpr_reg3 = V850_GPR_WR(reg3);
    Int32  sdisp    = state->info.sdisp;

    store(gpr_reg3, gpr_reg1, sdisp, 32, True, state->info.arch);
}

//
// Fix to 14606, correct VMMode during a syscall
//
static void vmicSYSCALL(v850P v850, Uns32 vector8) {
    vmiProcessorP processor = (vmiProcessorP)v850;
    Uns32         RETPC     = vmirtGetPC(processor);

    // EIPC <- PC
    v850->SPR_EIPC.reg = RETPC + 4;

    // EIPSW <- PSW
    v850PackPSW(v850);
    v850->SPR_EIPSW = v850->SPR_PSW;

    // EIIC <- exception code
    v850->SPR_EIIC.ECC = 0x8000 + vector8;

    // PSW settings
    v850->SPR_PSW.UM = 0;
    v850->SPR_PSW.EP = 1;
    v850->SPR_PSW.ID = 1;
    v850UnPackPSW(v850);

    // Set Mode
    v850SetVMMode(v850);

    Uns32 adr;
    if (vector8 <= v850->SPR_SCCFG.SIZE) {
        adr = v850->SPR_SCBP.reg + (vector8 << 2);
    } else {
        adr = v850->SPR_SCBP.reg;
    }

    // PC <- SCBP + mem(adr,Word)
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    Uns32      adrVal = vmirtRead4ByteDomain(domain, adr, getEndian(), MEM_AA_TRUE);
    Uns32      PC     = v850->SPR_SCBP.reg + adrVal;
    vmirtSetPCException(processor, PC);
}

V850_MORPH_FN(morphSYSCALL_F10C) {
    //
    // Supported Architecture=ISA_E3
    //

    Uns8 vector8 = state->info.uimm;

    vmimtArgProcessor();
    vmimtArgUns32(vector8);
    vmimtCallAttrs((vmiCallFn) vmicSYSCALL, VMCA_EXCEPTION);
}

V850_MORPH_FN(morphSYNCE_F01A) {
    //
    // Supported Architecture=ISA_E3
    //
    // NOP
}


V850_MORPH_FN(morphSYNCI_F01A) {
    //
    // Supported Architecture=ISA_E3
    //
    // NOP
}

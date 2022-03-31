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

// VMI header files
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"

// model header files
#include "andesACE.h"
#include "andesCSR.h"
#include "andesCustomPhases.h"
#include "andesDecode.h"
#include "andesDecodeTypes.h"
#include "andesExceptions.h"
#include "andesFunctions.h"
#include "andesMessage.h"
#include "andesMode.h"
#include "andesMorph.h"
#include "andesStructure.h"
#include "andesTypeRefs.h"
#include "andesUtils.h"
#include "andesVariant.h"

// base model header files
#include "riscvRegisters.h"
#include "riscvStructure.h"
#include "riscvTypes.h"


////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

//
// Floating point control
//
typedef enum andesFPCtrlE {
    ANFP_FLHW,      // special for FLHW
    ANFP_FSHW,      // special for FSHW
    ANFP_LAST       // KEEP LAST
} andesFPCtrl;

//
// Generic JIT code emission callback
//
#define ANDES_MORPH_FN(_NAME) void _NAME(andesMorphStateP state)
typedef ANDES_MORPH_FN((*andesMorphFn));

typedef enum findTypeE {
    FT_M,       // search for match
    FT_ZMISM,   // search for mismatch or zero
    FT_MISM,    // search for mismatch
} findType;

//
// Attributes controlling JIT code translation
//
typedef struct andesMorphAttrS {
    andesMorphFn          morph;        // function to translate one instruction
    octiaInstructionClass iClass;       // supplemental instruction class
    andesVariant          variant;      // required variant
    vmiBinop              binop    : 8; // integer binary operation
    andesFPCtrl           fpConfig : 4; // floating point configuration
    vmiCondition          cond     : 4; // comparison condition
    findType              findType : 2; // type of search (ffm etc)
    Bool                  findFirst: 1; // find first match (ffm etc)
} andesMorphAttr;

//
// Context for JIT code translation (decoded instruction information and
// translation attributes)
//
typedef struct andesMorphStateS {
    andesInstrInfo       info;          // decoded instruction information
    andesMorphAttrCP     attrs;         // instruction attributes
    riscvP               riscv;         // current processor
    vmiosObjectP         object;        // current extension object
} andesMorphState;


////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Return current program counter
//
inline static Uns64 getPC(riscvP riscv) {
    return vmirtGetPC((vmiProcessorP)riscv);
}

//
// Return endian for data accesses
//
inline static memEndian getDataEndian(riscvP riscv) {
    return riscv->cb.getDataEndianMt(riscv);
}

//
// Disable instruction translation (test mode)
//
inline static Bool disableMorph(andesMorphStateP state) {
    return RISCV_DISASSEMBLE(state->riscv);
}


////////////////////////////////////////////////////////////////////////////////
// REGISTER ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Return riscvRegDesc for the indexed register
//
inline static riscvRegDesc getRVReg(andesMorphStateP state, Uns32 argNum) {
    return state->info.r[argNum];
}

//
// Return vmiReg for the indexed extension temporary
//
inline static vmiReg getTmp(andesMorphStateP state, Uns32 index) {

    Uns64 *tmpP = &state->object->tmp[index];

    return vmimtGetExtTemp((vmiProcessorP)state->riscv, tmpP);
}


////////////////////////////////////////////////////////////////////////////////
// BASE MODEL UTILITY FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// This holds an Illegal Instruction description
//
typedef struct illegalDescS {
    const char *id;     // message ID
    const char *detail; // detailed description
} illegalDesc, *illegalDescP;

//
// Macro used to define illegalDesc structure and emit an Illegal Instruction
// using it
//
#define ILLEGAL_INSTRUCTION_MESSAGE(_RISCV, _ID, _DETAIL) { \
    static illegalDesc _DESC = { .id=CPU_PREFIX"_"_ID, .detail=_DETAIL};    \
    emitIllegalInstructionMessageDesc(_RISCV, &_DESC);                      \
}

//
// Emit call to take Illegal Instruction exception
//
static void emitIllegalInstruction(void) {
    vmimtArgProcessor();
    vmimtCallAttrs((vmiCallFn)andesIllegalInstruction, VMCA_EXCEPTION);
}

//
// Emit Illegal Instruction description message
//
static void illegalInstructionMessageDesc(riscvP riscv, illegalDescP desc) {
    vmiMessage("W", desc->id,
        SRCREF_FMT "%s",
        SRCREF_ARGS(riscv, getPC(riscv)),
        desc->detail
    );
}

//
// Emit Illegal Instruction message and take Illegal Instruction exception
//
static void emitIllegalInstructionMessageDesc(riscvP riscv, illegalDescP desc) {

    // emit message in verbose mode
    if(riscv->verbose) {
        vmimtArgProcessor();
        vmimtArgNatAddress(desc);
        vmimtCall((vmiCallFn)illegalInstructionMessageDesc);
    }

    // take Illegal Instruction exception
    emitIllegalInstruction();
}

//
// Validate instruction support by feature bit in mmsc_cfg
//
#define VALIDATE_ANDES_MMSC_CFG(_RISCV, _OBJECT, _FEATURE) \
    if(!RD_XCSR_FIELD(_OBJECT, mmsc_cfg, _FEATURE)) {                   \
        ILLEGAL_INSTRUCTION_MESSAGE(                                    \
            _RISCV, #_FEATURE, "Illegal when mmsc_cfg."#_FEATURE"=0"    \
        );                                                              \
        return False;                                                   \
    }

//
// Validate that the instruction is supported and enabled and take an Illegal
// Instruction exception if not
//
static Bool instructionEnabled(
    vmiosObjectP      object,
    riscvP            riscv,
    riscvArchitecture requiredVariant,
    andesMorphAttrCP  attrs
) {
    vmiReg       mode      = andesObjectReg(object, EXT_REG(mode));
    andesVariant anVariant = attrs->variant;

    // validate base model constraints
    if(!riscv->cb.instructionEnabled(riscv, requiredVariant)) {
        return False;
    }

    // validate Andes feature set
    if(anVariant==ANV_ECD) {
        VALIDATE_ANDES_MMSC_CFG(riscv, object, ECD);
    } else if(anVariant==ANV_EV5MPE) {
        VALIDATE_ANDES_MMSC_CFG(riscv, object, EV5MPE);
    } else if(anVariant==ANV_EFHW) {
        VALIDATE_ANDES_MMSC_CFG(riscv, object, EFHW);
    } else if(anVariant==ANV_BF16CVT) {
        VALIDATE_ANDES_MMSC_CFG(riscv, object, BF16CVT);
    } else if(anVariant==ANV_VL4) {
        VALIDATE_ANDES_MMSC_CFG(riscv, object, VL4);
    } else if(anVariant==ANV_VPFH) {
        VALIDATE_ANDES_MMSC_CFG(riscv, object, VPFH);
    } else {
        VMI_ABORT("Unexpected Andes variant 0x%x", anVariant); // LCOV_EXCL_LINE
    }

    // validate mmisc_ctl.RVCOMPM value
    vmimtValidateBlockMaskR(32, mode, ANM_RVCOMPM);

    // handle illegal instruction when mmisc_ctl.RVCOMPM=1
    if(object->mode & ANM_RVCOMPM) {
        ILLEGAL_INSTRUCTION_MESSAGE(riscv, "RVCOMPM", "Illegal when mmisc_ctl.RVCOMPM=1");
        return False;
    } else {
        return True;
    }
}

//
// Return VMI register for the given abstract register
//
inline static vmiReg getVMIReg(riscvP riscv, riscvRegDesc r) {
    return riscv->cb.getVMIReg(riscv, r);
}

//
// Return VMI register for the given abstract register which may require a NaN
// box test if it is floating point
//
inline static vmiReg getVMIRegFS(riscvP riscv, riscvRegDesc r, vmiReg tmp) {
    return riscv->cb.getVMIRegFS(riscv, r, tmp);
}

//
// Do actions when a register is written (sign extending or NaN boxing, if
// required) using the derived register size
//
inline static void writeReg(riscvP riscv, riscvRegDesc r) {
    riscv->cb.writeReg(riscv, r, True);
}

//
// Return VMI register for floating point status flags when written
//
inline static vmiReg riscvGetFPFlagsMT(riscvP riscv) {
    return riscv->cb.getFPFlagsMt(riscv);
}

//
// Validate the given rounding mode is legal and emit an Illegal Instruction
// exception call if not
//
inline static Bool emitCheckLegalRM(riscvP riscv, riscvRMDesc rm) {
    return riscv->cb.checkLegalRMMt(riscv, rm);
}

//
// Return floating point type for the given abstract register
//
static vmiFType getRegFType(riscvRegDesc r) {

    Uns32 bits = getRBits(r);

    if(isFReg(r)) {
        return VMI_FT_IEEE_754 | bits;
    } else if(isUReg(r)) {
        return VMI_FT_UNS | bits;
    } else {
        return VMI_FT_INT | bits;
    }
}


////////////////////////////////////////////////////////////////////////////////
// LOAD/STORE UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Load value from memory
//
static void emitLoadCommon(
    andesMorphStateP state,
    vmiReg           rd,
    Uns32            rdBits,
    vmiReg           ra,
    memConstraint    constraint
) {
    riscvP riscv   = state->riscv;
    Uns32  memBits = state->info.memBits;
    Uns64  offset  = state->info.c1;

    riscvExtLdStAttrs attrs = {
        constraint : constraint,
        sExtend    : !state->info.unsExt
    };

    riscv->cb.loadMt(riscv, rd, rdBits, ra, memBits, offset, attrs);
}

//
// Store value to memory
//
static void emitStoreCommon(
    andesMorphStateP state,
    vmiReg           rs,
    vmiReg           ra,
    memConstraint    constraint
) {
    riscvP riscv   = state->riscv;
    Uns32  memBits = state->info.memBits;
    Uns64  offset  = state->info.c1;

    riscvExtLdStAttrs attrs = {constraint : constraint};

    riscv->cb.storeMt(riscv, rs, ra, memBits, offset, attrs);
}


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Implement generic Binop (two registers and constant)
//
static ANDES_MORPH_FN(emitBinopRRC) {

    riscvP       riscv = state->riscv;
    riscvRegDesc rdA   = getRVReg(state, 0);
    riscvRegDesc rs1A  = getRVReg(state, 1);
    vmiReg       rd    = getVMIReg(riscv, rdA);
    vmiReg       rs1   = getVMIReg(riscv, rs1A);
    Uns32        bits  = getRBits(rdA);
    Uns64        c     = state->info.c1;

    vmimtBinopRRC(bits, state->attrs->binop, rd, rs1, c, 0);

    writeReg(riscv, rdA);
}

//
// Implement branch on bit set or clear
//
static ANDES_MORPH_FN(emitBranchRB) {

    riscvP       riscv = state->riscv;
    riscvRegDesc rs1A  = getRVReg(state, 0);
    vmiReg       rs1   = getVMIReg(riscv, rs1A);
    Uns32        bits  = getRBits(rs1A);
    Uns64        tgt   = state->info.c1;
    Uns64        mask  = (1ULL << state->info.c2);
    vmiReg       tmp   = getTmp(state, 0);

    vmimtTestRC(bits, state->attrs->cond, rs1, mask, tmp);
    vmimtCondJump(tmp, True, 0, tgt, VMI_NOREG, vmi_JH_RELATIVE);
}

//
// Implement branch on equal or unequal
//
static ANDES_MORPH_FN(emitBranchRC) {

    riscvP       riscv = state->riscv;
    riscvRegDesc rs1A  = getRVReg(state, 0);
    vmiReg       rs1   = getVMIReg(riscv, rs1A);
    Uns32        bits  = getRBits(rs1A);
    Uns64        tgt   = state->info.c1;
    Uns64        imm   = state->info.c2;
    vmiReg       tmp   = getTmp(state, 0);

    vmimtCompareRC(bits, state->attrs->cond, rs1, imm, tmp);
    vmimtCondJump(tmp, True, 0, tgt, VMI_NOREG, vmi_JH_RELATIVE);
}

//
// Implement bit field operation
//
static ANDES_MORPH_FN(emitBFO) {

    riscvP       riscv = state->riscv;
    riscvRegDesc rdA   = getRVReg(state, 0);
    riscvRegDesc rs1A  = getRVReg(state, 1);
    vmiReg       rd    = getVMIReg(riscv, rdA);
    vmiReg       rs1   = getVMIReg(riscv, rs1A);
    Uns32        bits  = getRBits(rdA);
    Uns32        msb   = state->info.c1;
    Uns32        lsb   = state->info.c2;
    vmiReg       tmp   = getTmp(state, 0);
    Uns32        shiftL;
    Uns32        shiftR;

    // determine left and right shifts
    if(!msb || (msb<lsb)) {
        Uns32 lenM1 = msb ? lsb-msb : 0;
        shiftL = bits-lenM1-1;
        shiftR = bits-lsb-1;
    } else {
        Uns32 lenM1 = msb-lsb;
        shiftL = bits-msb-1;
        shiftR = bits-lenM1-1;
    }

    // implement operation using two shifts
    vmimtBinopRRC(bits, vmi_SHL, tmp, rs1, shiftL, 0);
    vmimtBinopRRC(bits, state->attrs->binop, rd, tmp, shiftR, 0);

    writeReg(riscv, rdA);
}

//
// Implement load effective address operation
//
static ANDES_MORPH_FN(emitLEA) {

    riscvP       riscv   = state->riscv;
    riscvRegDesc rdA     = getRVReg(state, 0);
    riscvRegDesc rs1A    = getRVReg(state, 1);
    riscvRegDesc rs2A    = getRVReg(state, 2);
    vmiReg       rd      = getVMIReg(riscv, rdA);
    vmiReg       rs1     = getVMIReg(riscv, rs1A);
    vmiReg       rs2     = getVMIReg(riscv, rs2A);
    Uns32        bits    = getRBits(rdA);
    Uns32        srcBits = state->info.ze32 ? 32 : bits;
    vmiReg       tmp     = getTmp(state, 0);
    Uns32        shift   = 0;
    Uns32        i;

    // extract part of rs2 into temporary
    vmimtMoveExtendRR(bits, tmp, srcBits, rs2, False);

    // calculate scale shift
    for(i=8; i<state->info.memBits; i*=2) {shift++;}

    // scale up temporary
    vmimtBinopRC(bits, vmi_SHL, tmp, shift, 0);

    // get result
    vmimtBinopRRR(bits, state->attrs->binop, rd, rs1, tmp, 0);

    writeReg(riscv, rdA);
}

//
// Get alignment constraint for load/store operations
//
static memConstraint getLoadStoreConstraint(andesMorphStateP state) {

    Bool unaligned = state->riscv->configInfo.unaligned;

    return unaligned ? MEM_CONSTRAINT_NONE : MEM_CONSTRAINT_ALIGNED;
}

//
// Load value from memory
//
static ANDES_MORPH_FN(emitLoad) {

    riscvP        riscv      = state->riscv;
    riscvRegDesc  rdA        = getRVReg(state, 0);
    riscvRegDesc  raA        = getRVReg(state, 1);
    vmiReg        rd         = getVMIReg(riscv, rdA);
    vmiReg        ra         = getVMIReg(riscv, raA);
    Uns32         rdBits     = getRBits(rdA);
    memConstraint constraint = getLoadStoreConstraint(state);

    // call common code to perform load
    emitLoadCommon(state, rd, rdBits, ra, constraint);

    writeReg(riscv, rdA);
}

//
// Store value to memory
//
static ANDES_MORPH_FN(emitStore) {

    riscvP        riscv      = state->riscv;
    riscvRegDesc  rsA        = getRVReg(state, 0);
    riscvRegDesc  raA        = getRVReg(state, 1);
    vmiReg        rs         = getVMIReg(riscv, rsA);
    vmiReg        ra         = getVMIReg(riscv, raA);
    memConstraint constraint = getLoadStoreConstraint(state);

    // call common code to perform store
    emitStoreCommon(state, rs, ra, constraint);
}

//
// Emit find operation (FFB, FFZMISM, FFMISM or FLMISM)
//
static ANDES_MORPH_FN(emitFind) {

    riscvP       riscv = state->riscv;
    riscvRegDesc rdA   = getRVReg(state, 0);
    riscvRegDesc rs1A  = getRVReg(state, 1);
    riscvRegDesc rs2A  = getRVReg(state, 2);
    vmiReg       rd    = getVMIReg(riscv, rdA);
    vmiReg       rs1   = getVMIReg(riscv, rs1A);
    vmiReg       rs2   = getVMIReg(riscv, rs2A);
    Uns32        bits  = getRBits(rdA);
    vmiLabelP    loop  = vmimtNewLabel();
    vmiLabelP    done  = vmimtNewLabel();
    vmiReg       tmp1  = getTmp(state, 0);
    vmiReg       tmp2  = getTmp(state, 1);
    vmiReg       count = getTmp(state, 2);
    vmiReg       tf    = getTmp(state, 3);
    Bool         match = state->attrs->findType==FT_M;
    Bool         zero  = state->attrs->findType==FT_ZMISM;
    Bool         first = state->attrs->findFirst;
    Bool         swap  = getDataEndian(state->riscv) == first;
    vmiUnop      op    = swap ? vmi_SWP : vmi_MOV;
    Int32        elems = bits/8;

    // move value to compare to temporary (perhaps with byte swap)
    vmimtUnopRR(bits, op, tmp1, rs1, 0);

    // if corresponding byte comparison, move second value to temporary
    if(!match) {
        vmimtUnopRR(bits, op, tmp2, rs2, 0);
    } else {
        tmp2 = rs2;
    }

    // initialize repeat count
    vmimtMoveRC(bits, count, elems);

    // loop to here
    vmimtInsertLabel(loop);

    // do match/mismatch test
    vmimtCompareRR(8, vmi_COND_EQ, tmp1, tmp2, tf);
    vmimtCondJumpLabel(tf, match, done);

    // do zero test if required
    if(zero) {
        vmimtCompareRCJumpLabel(8, vmi_COND_EQ, tmp1, 0, done);
    }

    // get next byte in tmp1
    vmimtBinopRC(bits, vmi_SHR, tmp1, 8, 0);

    // if corresponding byte comparison, get next byte in tmp2
    if(!match) {
        vmimtBinopRC(bits, vmi_SHR, tmp2, 8, 0);
    }

    // do next iteration
    vmimtDJNZLabel(32, count, loop);

    // here when done
    vmimtInsertLabel(done);

    // extend count to operand size
    vmimtMoveExtendRR(bits, rd, 32, count, True);

    // get result from count, depending on whether first or last match is
    // required; for example, for 32-bit search, final count is mapped to the
    // following results:
    //
    //  count first last
    //  ----- ----- ----
    //    0     0     0
    //    1    -1    -4
    //    2    -2    -3
    //    3    -3    -2
    //    4    -4    -1
    //
    if(first) {

        vmimtUnopR(bits, vmi_NEG, rd, 0);

    } else {

        vmiLabelP noSub = vmimtNewLabel();

        vmimtCompareRCJumpLabel(bits, vmi_COND_EQ, rd, 0, noSub);
        vmimtBinopRRC(bits, vmi_SUB, rd, count, elems+1, 0);
        vmimtInsertLabel(noSub);
    }

    writeReg(riscv, rdA);
}

//
// Emit EXEC.IT indirect instruction
//
static ANDES_MORPH_FN(emitEXEC_IT) {

    memDomainP domain = vmirtGetProcessorCodeDomain((vmiProcessorP)state->riscv);
    Uns32      bits   = vmirtGetDomainAddressBits(domain);
    Uns32      offset = state->info.c1*4;
    Uns64      nextPC = state->info.thisPC+2;
    vmiReg     uitb   = andesObjectReg(state->object, XCSR_REG_MT(uitb));
    vmiReg     tmp    = getTmp(state, 0);

    // mask nextPC if required
    if(bits<64) {
        nextPC &= ((1ULL<<bits)-1);
    }

    // save instruction address
    vmimtMoveRSimPC(bits, RISCV_JUMP_BASE);

    // calculate target address
    vmimtBinopRRC(bits, vmi_ADD, tmp, uitb, offset, 0);

    // execute one instruction at the target address
    vmimtEnterDelaySlotR(1, tmp, nextPC, 0);
}


////////////////////////////////////////////////////////////////////////////////
// FLOATING POINT CONFIGURATION AND CONTROL
////////////////////////////////////////////////////////////////////////////////

//
// Flt16 macros
//
#define FP16_DEFAULT_QNAN   0x7e00

//
// Flt32 macros
//
#define FP32_DEFAULT_QNAN   0x7fc00000

//
// 16-bit QNaN result - return default QNaN
//
static VMI_FP_QNAN16_RESULT_FN(handleQNaN16) {
    return FP16_DEFAULT_QNAN;
}

//
// 32-bit QNaN result - return default QNaN
//
static VMI_FP_QNAN32_RESULT_FN(handleQNaN32) {
    return FP32_DEFAULT_QNAN;
}

//
// Define one vmiFPConfig
//
#define FPU_CONFIG(_R16, _R32, _STICKY) { \
    .QNaN16         = FP16_DEFAULT_QNAN,    \
    .QNaN32         = FP32_DEFAULT_QNAN,    \
    .QNaN16ResultCB = handleQNaN16,         \
    .QNaN32ResultCB = handleQNaN32,         \
    .fp16ResultCB   = _R16,                 \
    .fp32ResultCB   = _R32,                 \
    .suppressFlags  = {f:{D:1}},            \
    .stickyFlags    = _STICKY               \
}

//
// Table of floating point operation configurations
//
const static vmiFPConfig fpConfigs[ANFP_LAST] = {
    [ANFP_FLHW] = FPU_CONFIG(0, 0, 1),
    [ANFP_FSHW] = FPU_CONFIG(0, 0, 0),
};

//
// Return floating point control to use for the current instruction
//
static vmiFPConfigCP getFPControl(andesMorphStateP state) {
    return &fpConfigs[state->attrs->fpConfig];
}


////////////////////////////////////////////////////////////////////////////////
// FLOATING POINT OPERATIONS
////////////////////////////////////////////////////////////////////////////////

//
// Emit FLHW
//
static ANDES_MORPH_FN(emitFLHW) {

    riscvP        riscv      = state->riscv;
    riscvRegDesc  fdA        = getRVReg(state, 0);
    riscvRegDesc  raA        = getRVReg(state, 1);
    vmiReg        fd         = getVMIReg(riscv, fdA);
    vmiReg        ra         = getVMIReg(riscv, raA);
    memConstraint constraint = getLoadStoreConstraint(state);
    vmiFType      typeD      = getRegFType(fdA);
    vmiFType      typeS      = vmi_FT_16_IEEE_754;
    vmiFPConfigCP ctrl       = getFPControl(state);
    vmiReg        flags      = riscvGetFPFlagsMT(riscv);

    // call common code to perform load
    emitLoadCommon(state, fd, 16, ra, constraint);

    // convert to single-precision
    vmimtFConvertRR(typeD, fd, typeS, fd, vmi_FPR_ZERO, flags, ctrl);

    writeReg(riscv, fdA);
}

//
// Emit FSHW
//
static ANDES_MORPH_FN(emitFSHW) {

    riscvP        riscv      = state->riscv;
    riscvRegDesc  fsA        = getRVReg(state, 0);
    riscvRegDesc  raA        = getRVReg(state, 1);
    vmiReg        tmp        = getTmp(state, 1);
    vmiReg        tmpFlags   = getTmp(state, 2);
    vmiReg        fs         = getVMIRegFS(riscv, fsA, tmp);
    vmiReg        ra         = getVMIReg(riscv, raA);
    memConstraint constraint = getLoadStoreConstraint(state);
    vmiFType      typeD      = vmi_FT_16_IEEE_754;
    vmiFType      typeS      = getRegFType(fsA);
    vmiFPConfigCP ctrl       = getFPControl(state);
    vmiReg        flags      = riscvGetFPFlagsMT(riscv);

    // convert to half-precision, producing temporary flags
    vmimtFConvertRR(typeD, tmp, typeS, fs, vmi_FPR_ZERO, tmpFlags, ctrl);

    // call common code to perform store
    emitStoreCommon(state, tmp, ra, constraint);

    // merge temporary flags if store succeeds
    vmimtBinopRR(8, vmi_OR, flags, tmpFlags, 0);
}

//
// Return riscvRegDesc for the indexed register, forced to width 16
//
inline static riscvRegDesc getRVReg16(andesMorphStateP state, Uns32 argNum) {
    return (getRVReg(state, argNum) & ~RV_RD_BITS_MASK) | RV_RD_16;
}

//
// Emit code to validate the current SEW is the given value
//
static void emitValidateSEW(andesMorphStateP state, Uns32 SEW) {

    vmiReg    tmp = getTmp(state, 0);
    vmiLabelP ok  = vmimtNewLabel();

    // extract current SEW
    vmimtBinopRRC(8, vmi_AND, tmp, CSR_REG_MT(vtype), 7<<2, 0);

    // no exception if SEW=16
    vmimtCompareRCJumpLabel(8, vmi_COND_EQ, tmp, 1<<2, ok);

    // raise Illegal Instruction
    ILLEGAL_INSTRUCTION_MESSAGE(state->riscv, "RVSEW", "Illegal when SEW!=16");

    // here if ok
    vmimtInsertLabel(ok);
}

//
// Emit a vector operation using the given shape and callback
//
static void emitVectorOp(
    andesMorphStateP state,
    riscvVShape      shape,
    riscvVExternalFn externalCB
) {
    riscvP riscv = state->riscv;

    // implement as vector operation
    riscv->cb.morphVOp(
        riscv,
        state->info.thisPC,
        getRVReg(state, 0),
        getRVReg(state, 1),
        getRVReg(state, 2),
        state->info.mask,
        shape,
        externalCB,
        state
    );
}

//
// Per-element callback for int4 variant instructions
//
static RISCV_VEXTERNAL_FN(emitVLNVCB) {

    andesMorphStateP state      = userData;
    riscvRegDesc     rs1A       = getRVReg(state, 1);
    vmiReg           tmp        = getTmp(state, 0);
    vmiReg           ra         = tmp;
    Uns32            raBits     = getRBits(rs1A);
    vmiReg           vstart     = CSR_REG_MT(vstart);
    Uns32            shift      = 1;
    Uns32            fields     = 1<<shift;
    Uns32            fieldBits  = 8/fields;
    memConstraint    constraint = getLoadStoreConstraint(state);
    Bool             sExtend    = !state->info.unsExt;

    // calculate load offset
    vmimtBinopRRC(raBits, vmi_SHR, ra, vstart, shift, 0);

    // calculate load base
    vmimtBinopRR(raBits, vmi_ADD, ra, r[1], 0);

    // call common code to perform load (forced to one byte)
    state->info.memBits = 8;
    emitLoadCommon(state, r[0], 8, ra, constraint);

    // calculate field index
    vmimtBinopRRC(8, vmi_AND, tmp, vstart, fields-1, 0);

    // calculate field left shift (to top of byte)
    vmimtBinopRCR(8, vmi_SUB, tmp, fields-1, tmp, 0);

    // calculate field bit shift
    vmimtBinopRC(8, vmi_MUL, tmp, fieldBits, 0);

    // shift to align field with top of byte
    vmimtBinopRR(8, vmi_SHL, r[0], tmp, 0);

    // zero/sign extend field
    vmimtBinopRC(8, sExtend?vmi_SAR:vmi_SHR, r[0], 8-fieldBits, 0);

    // extend result to SEW if required
    vmimtMoveExtendRR(SEW, r[0], 8, r[0], sExtend);
}

//
// Emit int4 variant instructions
//
static ANDES_MORPH_FN(emitVLNV) {

    riscvVShape shape = state->info.elemBits==8 ? RVVW_V1I_V1I_V1I_SEW8 : RVVW_V1I_V1I_V1I;

    emitVectorOp(state, shape, emitVLNVCB);
}

//
// Per-element callback for VFPMADT.VF or VFPMADB.VF
//
static void emitVFPMADTCBInt(
    riscvP           riscv,
    andesMorphStateP state,
    vmiReg          *r,
    Uns32            SEW,
    Bool             T
) {
    vmiReg        vd    = r[0];
    vmiReg        rs1   = r[1];
    vmiReg        vs2   = r[2];
    vmiReg        mul   = VMI_REG_DELTA(rs1, T?2:0);
    vmiReg        add   = VMI_REG_DELTA(rs1, T?0:2);
    vmiFType      type  = vmi_FT_16_IEEE_754;
    vmiFPConfigCP ctrl  = getFPControl(state);
    vmiReg        flags = riscvGetFPFlagsMT(riscv);

    vmimtFTernopRRRR(type, vmi_FMADD, vd, vs2, mul, add, flags, False, ctrl);
}

//
// Per-element callback for VFPMADT.VF
//
static RISCV_VEXTERNAL_FN(emitVFPMADTCB) {
    emitVFPMADTCBInt(riscv, userData, r, SEW, True);
}

//
// Per-element callback for VFPMADB.VF
//
static RISCV_VEXTERNAL_FN(emitVFPMADBCB) {
    emitVFPMADTCBInt(riscv, userData, r, SEW, False);
}

//
// Emit VFPMADT.VF
//
static ANDES_MORPH_FN(emitVFPMADT_VF) {

    emitValidateSEW(state, 16);
    emitVectorOp(state, RVVW_V1F_S1F_V1F, emitVFPMADTCB);
}

//
// Emit VFPMADB.VF
//
static ANDES_MORPH_FN(emitVFPMADB_VF) {

    emitValidateSEW(state, 16);
    emitVectorOp(state, RVVW_V1F_S1F_V1F, emitVFPMADBCB);
}

//
// Emit FCVT.S.BF16
//
static ANDES_MORPH_FN(emitFCVT_S_BF16) {

    riscvP       riscv = state->riscv;
    riscvRegDesc fdA   = getRVReg(state, 0);
    riscvRegDesc fsA   = getRVReg16(state, 1);
    vmiReg       fd    = getVMIReg(riscv, fdA);
    vmiReg       fdH   = VMI_REG_DELTA(fd, 2);
    vmiReg       fs    = getVMIReg(riscv, fsA);

    // move result to high part of register
    vmimtMoveRR(16, fdH, fs);
    vmimtMoveRC(16, fd,  0);

    // write result
    writeReg(riscv, fdA);
}

//
// Emit FCVT.BF16.S
//
static ANDES_MORPH_FN(emitFCVT_BF16_S) {

    riscvP       riscv = state->riscv;
    riscvRegDesc fdA   = getRVReg16(state, 0);
    riscvRegDesc fsA   = getRVReg(state, 1);
    vmiReg       fd    = getVMIReg(riscv, fdA);
    vmiReg       fs    = getVMIReg(riscv, fsA);
    vmiFType     typeD = vmi_FT_BFLOAT16;
    vmiFType     typeS = vmi_FT_32_IEEE_754;

    if(emitCheckLegalRM(riscv, RV_RM_CURRENT)) {
        vmiReg flags = riscvGetFPFlagsMT(riscv);
        vmimtFConvertRR(typeD, fd, typeS, fs, vmi_FPR_CURRENT, flags, 0);
        writeReg(riscv, fdA);
    }
}

//
// Per-element callback for VFWCVT.S.BF16
//
static RISCV_VEXTERNAL_FN(emitVFWCVT_S_BF16CB) {

    vmiReg r0L = r[0];
    vmiReg r0H = VMI_REG_DELTA(r[0], 2);

    // move result to high part of register
    vmimtMoveRR(16, r0H, r[1]);
    vmimtMoveRC(16, r0L, 0);
}

//
// Per-element callback for VFWCVT.BF16.S
//
static RISCV_VEXTERNAL_FN(emitVFNCVT_BF16_SCB) {

    vmiFType typeD = vmi_FT_BFLOAT16;
    vmiFType typeS = vmi_FT_32_IEEE_754;

    if(emitCheckLegalRM(riscv, RV_RM_CURRENT)) {
        vmiReg flags = riscvGetFPFlagsMT(riscv);
        vmimtFConvertRR(typeD, r[0], typeS, r[1], vmi_FPR_CURRENT, flags, 0);
    }
}

//
// Emit VFWCVT.S.BF16
//
static ANDES_MORPH_FN(emitVFWCVT_S_BF16) {

    emitValidateSEW(state, 16);
    emitVectorOp(state, RVVW_V2F_V1I, emitVFWCVT_S_BF16CB);
}

//
// Emit VFWCVT.BF16.S
//
static ANDES_MORPH_FN(emitVFNCVT_BF16_S) {

    emitValidateSEW(state, 16);
    emitVectorOp(state, RVVW_V1I_V2F_IW, emitVFNCVT_BF16_SCB);
}


////////////////////////////////////////////////////////////////////////////////
// CUSTOM INSTRUCTIONS
////////////////////////////////////////////////////////////////////////////////

#if defined(CUSTOMFILE)
    #define ANDES_CUSTOM_PHASE ANDES_CUSTOM_MORPH_FUNCTIONS
    #include CUSTOMFILE
    #undef ANDES_CUSTOM_PHASE
#endif


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION TABLE
////////////////////////////////////////////////////////////////////////////////

//
// Dispatch table for instruction translation
//
const static andesMorphAttr dispatchTable[] = {

    // add immediate instruction
    [AN_IT_ADDI]          = {morph:emitBinopRRC,      variant:ANV_EV5MPE, binop:vmi_ADD, iClass:OCL_IC_INTEGER},

    // branch instructions
    [AN_IT_BBC]           = {morph:emitBranchRB,      variant:ANV_EV5MPE, cond:vmi_COND_Z },
    [AN_IT_BBS]           = {morph:emitBranchRB,      variant:ANV_EV5MPE, cond:vmi_COND_NZ},
    [AN_IT_BEQC]          = {morph:emitBranchRC,      variant:ANV_EV5MPE, cond:vmi_COND_Z },
    [AN_IT_BNEC]          = {morph:emitBranchRC,      variant:ANV_EV5MPE, cond:vmi_COND_NZ},

    // bit field instructions
    [AN_IT_BFOS]          = {morph:emitBFO,           variant:ANV_EV5MPE, binop:vmi_SAR, iClass:OCL_IC_INTEGER},
    [AN_IT_BFOZ]          = {morph:emitBFO,           variant:ANV_EV5MPE, binop:vmi_SHR, iClass:OCL_IC_INTEGER},

    // load effective address instruction
    [AN_IT_LEA]           = {morph:emitLEA,           variant:ANV_EV5MPE, binop:vmi_ADD, iClass:OCL_IC_INTEGER},

    // load and store instructions
    [AN_IT_L]             = {morph:emitLoad,          variant:ANV_EV5MPE},
    [AN_IT_S]             = {morph:emitStore,         variant:ANV_EV5MPE},

    // find instructions
    [AN_IT_FFB]           = {morph:emitFind,          variant:ANV_EV5MPE, findType:FT_M,     findFirst:True,  iClass:OCL_IC_INTEGER},
    [AN_IT_FFZMISM]       = {morph:emitFind,          variant:ANV_EV5MPE, findType:FT_ZMISM, findFirst:True,  iClass:OCL_IC_INTEGER},
    [AN_IT_FFMISM]        = {morph:emitFind,          variant:ANV_EV5MPE, findType:FT_MISM,  findFirst:True,  iClass:OCL_IC_INTEGER},
    [AN_IT_FLMISM]        = {morph:emitFind,          variant:ANV_EV5MPE, findType:FT_MISM,  findFirst:False, iClass:OCL_IC_INTEGER},

    // execute table instruction
    [AN_IT_EXEC_IT]       = {morph:emitEXEC_IT,       variant:ANV_ECD},

    // half-precision floating-point instructions
    [AN_IT_FLHW]          = {morph:emitFLHW,          variant:ANV_EFHW, fpConfig:ANFP_FLHW},
    [AN_IT_FSHW]          = {morph:emitFSHW,          variant:ANV_EFHW, fpConfig:ANFP_FSHW},

    // int4 vector load extension instructions
    [AN_IT_VLNV]          = {morph:emitVLNV,          variant:ANV_VL4},

    // bfloat16 extension instructions
    [AN_IT_VFWCVT_S_BF16] = {morph:emitVFWCVT_S_BF16, variant:ANV_BF16CVT},
    [AN_IT_VFNCVT_BF16_S] = {morph:emitVFNCVT_BF16_S, variant:ANV_BF16CVT},
    [AN_IT_FCVT_S_BF16]   = {morph:emitFCVT_S_BF16,   variant:ANV_BF16CVT},
    [AN_IT_FCVT_BF16_S]   = {morph:emitFCVT_BF16_S,   variant:ANV_BF16CVT},

    // vector packed FP16 extension
    [AN_IT_VFPMADT_VF]    = {morph:emitVFPMADT_VF,    variant:ANV_VPFH},
    [AN_IT_VFPMADB_VF]    = {morph:emitVFPMADB_VF,    variant:ANV_VPFH},

    // define custom instruction entries
    #if defined(CUSTOMFILE)
        #define ANDES_CUSTOM_PHASE ANDES_CUSTOM_MORPH_TABLE
        #include CUSTOMFILE
        #undef ANDES_CUSTOM_PHASE
    #endif

    // KEEP LAST
    [AN_IT_LAST]    = {0}
};

//
// Instruction Morpher
//
VMIOS_MORPH_FN(andesMorph) {

    riscvP          riscv = (riscvP)processor;
    andesMorphState state;

    // get instruction and instruction type
    andesDecode(riscv, object, thisPC, &state.info);

    // assume unaligned access is not allowed
    object->unaligned = False;

    if(state.info.type == AN_IT_MSA_UNA) {

        // base model instruction affected by alignment
        vmiReg mode = andesObjectReg(object, EXT_REG(mode));

        // validate mmisc_ctl.MSA_UNA value
        vmimtValidateBlockMaskR(32, mode, ANM_MSA_UNA);

        // unaligned access permitted if mmisc_ctl.MSA_UNA=1
        object->unaligned = RD_XCSR_FIELD(object, mmisc_ctl, MSA_UNA);

    } else if(state.info.type != AN_IT_LAST) {

        // indicate instruction is implemented here
        *opaque = True;

        andesMorphAttrCP attrs = &dispatchTable[state.info.type];
        state.attrs  = attrs;
        state.riscv  = riscv;
        state.object = object;

        if(disableMorph(&state)) {

            // no action if in disassembly mode

        } else if(!instructionEnabled(object, riscv, state.info.arch, attrs)) {

            // instruction not enabled

        } else if(state.attrs->morph) {

            // translate the instruction
            vmimtInstructionClassAdd(state.attrs->iClass);
            state.attrs->morph(&state);

        } else {

            // here if no morph callback specified
            vmiMessage("F", CPU_PREFIX "_UIMP", // LCOV_EXCL_LINE
                SRCREF_FMT "unimplemented",
                SRCREF_ARGS(riscv, thisPC)
            );
        }

    } else if(andesACEMorph(object, state.info.instruction)) {

        // indicate ACE instruction is implemented here
        *opaque = True;
    }

    // no callback function is required
    return 0;
}

//
// Function called before translation of an instruction
//
RISCV_DERIVED_MORPH_FN(andesPreMorph) {

    vmiosObjectP object = clientData;

    // handle hardware stack protection if required
    if(RD_XCSR_FIELD(object, mmsc_cfg, HSP)) {
        andesRecordSP(riscv, object);
    }

    // override default unaligned access behavior
    riscv->configInfo.unaligned = object->unaligned;
}

//
// Function called after translation of an instruction
//
RISCV_DERIVED_MORPH_FN(andesPostMorph) {

    vmiosObjectP object = clientData;

    // handle hardware stack protection if required
    if(RD_XCSR_FIELD(object, mmsc_cfg, HSP)) {
        andesCheckHSP(riscv, object);
    }

    // reset default unaligned access behavior (required for PMP updates to
    // be correctly handled)
    riscv->configInfo.unaligned = True;
}


/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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
#include "m16cMorph.h"
#include "m16cDecode.h"
#include "m16cExceptions.h"
#include "m16cFunctions.h"
#include "m16cStructure.h"
#include "m16cInstructions.h"
#include "m16cDisassemble.h"
#include "m16cUtils.h"





////////////////////////////////////////////////////////////////////////////////
// REGISTER ACCESS UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Return vmiReg structure for the passed GPR - note that register 0 is not
// writeable and always contains 0
//
inline static vmiReg getGPR(Uns32 r) {
    return r < M16C_REG_NONE ? M16C_REG(r) : VMI_NOREG;
}



//
// Return vmiReg structure for source register
//
inline static vmiReg getRs(m16cInstructionInfoP info) {
    return getGPR(info->rs1);
}


//
// Return vmiReg structure for destination register
//
inline static vmiReg getRd(m16cInstructionInfoP info) {
    return getGPR(info->rd1);
}


// Return Stack pointer.
inline static vmiReg getSp(m16cMorphState * state) {
    return (state->m16c->spSelectFlag) ? M16C_REG(M16C_REG_USP) : M16C_REG(M16C_REG_ISP);
}

inline static Uns8 getSize(m16cInstructionInfoP info) {
    if (info->sz == B)
        return 8;
    else if (info->sz == W)
        return 16;
    else if (info->sz == A)
        return 20;
    else if (info->sz == L)
        return 32;
    else if (info->sz == BIT)  // To perform bit operations, apply a mask against a 16-bit register
        return 16;
    vmiPrintf("Invalid Size\n");
    return 99;
}



//
// Return vmiReg structure for destination register
//
inline static vmiReg getFlgReg(m16cInstructionInfoP info) {
    switch (info->destMode)
    {
        case MODE_B:
            return M16C_REGBANKSELF_REG;
        case MODE_C:
            return M16C_CARRYF_REG;
        case MODE_D:
            return M16C_DEBUGF_REG;
        case MODE_I:
            return M16C_INTENABLE_REG;
        case MODE_O:
            return M16C_OVERFLOWF_REG;
        case MODE_S:
            return M16C_SIGNF_REG;
        case MODE_U:
            return M16C_SPSELECTF_REG;
        case MODE_Z:
            return M16C_ZEROF_REG;
        default:
            return VMI_NOREG;
    }

    return VMI_NOREG;
}



static void m16cSetFLG(m16cP m16c, Uns16 flg)
{
    m16c->carryFlag              =  (M16C_FLG_C & flg) ? True : False;
    m16c->debugFlag              =  (M16C_FLG_D & flg) ? True : False;
    m16c->zeroFlag               =  (M16C_FLG_Z & flg) ? True : False;
    m16c->signFlag               =  (M16C_FLG_S & flg) ? True : False;
    m16c->regBankSelectFlag      =  (M16C_FLG_B & flg) ? True : False;
    m16c->overflowFlag           =  (M16C_FLG_O & flg) ? True : False;
    m16c->intEnableFlag          =  (M16C_FLG_I & flg) ? True : False;
    m16c->spSelectFlag           =  (M16C_FLG_U & flg) ? True : False;
    m16c->intPriorityLevel = (flg >> 13) & 0x7;
}


#define M16C_SET_FLG() \
    vmimtArgProcessor(); \
    vmimtArgReg(16, M16C_REG(M16C_REG_FLG)); \
    vmimtCall((vmiCallFn)m16cSetFLG);

#define M16C_GET_FLG() \
    vmimtArgProcessor(); \
    vmimtCallResult((vmiCallFn)m16cGetFLG, 16, M16C_REG(M16C_REG_FLG));


inline static void vmimtLoadRRO16(Uns32 destBits, Uns32 memBits, Addr offset, vmiReg rd, vmiReg ra, memEndian endian, Bool signExtend, Bool checkAlign) {
    if (VMI_REG_EQUAL(ra, M16C_REG(M16C_REG_ISP)) || VMI_REG_EQUAL(ra, M16C_REG(M16C_REG_FB)) || VMI_REG_EQUAL(ra, M16C_REG(M16C_REG_A1))) {
        vmimtLoadRRO(destBits, memBits, offset, rd, ra, endian, signExtend, checkAlign);
    } else {
        vmimtMoveExtendRR(32, M16C_TEMPA_REG, 16, ra, False);
        vmimtLoadRRO(destBits, memBits, offset, rd, M16C_TEMPA_REG, endian, signExtend, checkAlign);
    }
}

inline static void vmimtStoreRRO16(Uns32 srcBits, Addr offset, vmiReg rd, vmiReg ra, memEndian endian, Bool checkAlign) {
    if (VMI_REG_EQUAL(rd, M16C_REG(M16C_REG_ISP)) || VMI_REG_EQUAL(rd, M16C_REG(M16C_REG_FB)) || VMI_REG_EQUAL(rd, M16C_REG(M16C_REG_A1)))
    {
        vmimtStoreRRO(srcBits, offset, rd, ra, endian, checkAlign);
    } else {
        vmimtMoveExtendRR(32, M16C_TEMPA_REG, 16, rd, False);
        vmimtStoreRRO(srcBits, offset, M16C_TEMPA_REG, ra, endian, checkAlign);
    }
}


inline static void vmimtStoreRCO16(Uns32 srcBits, Addr offset, vmiReg rd, Uns32 c, memEndian endian, Bool checkAlign) {
    if (VMI_REG_EQUAL(rd, M16C_REG(M16C_REG_ISP)) || VMI_REG_EQUAL(rd, M16C_REG(M16C_REG_FB)) || VMI_REG_EQUAL(rd, M16C_REG(M16C_REG_A1))) {
        vmimtStoreRCO(srcBits, offset, rd, c, endian, checkAlign);
    } else {
        vmimtMoveExtendRR(32, M16C_TEMPA_REG, 16, rd, False);
        vmimtStoreRCO(srcBits, offset, M16C_TEMPA_REG, c, endian, checkAlign);
    }
}

//
// Called for an undecoded instruction
//
static void undecoded(
    vmiProcessorP           processor,
    Uns32                   thisPC,
    Uns32                   instruction
) {
    m16cP m16c = (m16cP)processor;
    m16cInstructionInfo info;

    // get instruction and instruction type
    m16cDecode(m16c, thisPC, &info);

    // report that undecoded instruction was encountered
    vmiPrintf(
        "CPU '%s' Cannot Morph Instruction\n"
        "CPU '%s' 0x%08x:0x%08x : '%s' index=%d\n",
        vmirtProcessorName(processor),
        vmirtProcessorName(processor),
        thisPC,
        instruction,
        m16cDisassembleInfo(m16c, &info),
        info.morphindex
    );

    // exit the CPU
    vmirtExit(processor);
}


#define DEBUG_MORPH_FN(_NAME)  // vmiPrintf("MORPH_FN: %s (%d) for instr: %s, 0x%08x\n",_NAME, (int) state->info.optype,state->info.opcode,state->info.instruction);


//
// Emit code to implement a nop
//
static M16C_MORPH_FN(nopOp) {
    DEBUG_MORPH_FN("NOP");
}




static M16C_MORPH_FN(binOpRR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiBinop    op     = (state->info).optype;
    vmiFlagsCP  flags  = (state->info).flags;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("binOp RR");
    if (op == vmi_SBB) {  // SBB is dest <- dest - src - (inverted) Carry
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);
    }

    vmimtBinopRR(size, op, regD, regS, flags);

    if (op == vmi_CMP || op == vmi_SUB || op == vmi_SBB) {  // For these instructions Carry is set when unsigned operation is >= 0
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);
    }
}


static M16C_MORPH_FN(binOpRC) {
    Int32       imm    = (state->info).imm;
    vmiReg      regD    = getRd(&state->info);
    // vmiReg      temp    = M16C_TEMPS_REG;
    vmiBinop    op     = (state->info).optype;
    vmiFlagsCP  flags  = (state->info).flags;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("binOp RC");

    if (op == vmi_SBB) {
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);  // SBB is dest <- dest - src - (inverted) Carry
    }

    vmimtBinopRC(size, op, regD, imm, flags);

    if (op == vmi_CMP || op == vmi_SUB || op == vmi_SBB) {  // For these instructions Carry is set when unsigned operation is >= 0
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);
    }
}

static M16C_MORPH_FN(binOpRO) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    Int32       offset  = (state->info).offsetS;
    vmiReg      temp    = M16C_TEMPS_REG;
    vmiBinop    op     = (state->info).optype;
    vmiFlagsCP  flags  = (state->info).flags;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("binOp RO");

    vmimtLoadRRO16(size, size, offset, temp, regS, M16C_ENDIAN, False, False);

    if (op == vmi_SBB) {  // SBB is dest <- dest - src - (inverted) Carry
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);
    }

    vmimtBinopRR(size, op, regD, temp, flags);

    if (op == vmi_CMP || op == vmi_SUB || op == vmi_SBB) {  // For these instructions Carry is set when unsigned operation is >= 0
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);
    }
}


static M16C_MORPH_FN(binOpOR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPD_REG;
    Int32       offset  = (state->info).offsetD;
    vmiBinop    op     = (state->info).optype;
    vmiFlagsCP  flags  = (state->info).flags;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("binOp OR");
    vmimtLoadRRO16(size, size, offset, temp, regD, M16C_ENDIAN, False, False);

    if (op == vmi_SBB) {  // SBB is dest <- dest - src - (inverted) Carry
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);
    }

    vmimtBinopRR(size, op, temp, regS, flags);

    if (op == vmi_CMP || op == vmi_SUB || op == vmi_SBB) {  // For these instructions Carry is set when unsigned operation is >= 0
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);
    }

    vmimtStoreRRO16(size, offset, regD, temp, M16C_ENDIAN, False);
}

static M16C_MORPH_FN(binOpOC) {
    vmiReg      regD    = getRd(&state->info);
    vmiReg      tempS    = M16C_TEMPS_REG;
    Int32       offset  = (state->info).offsetD;
    Int32       imm    = (state->info).imm;
    vmiBinop    op     = (state->info).optype;
    vmiFlagsCP  flags  = (state->info).flags;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("binOp OC");

    vmimtLoadRRO16(16, 16, offset, tempS, regD, M16C_ENDIAN, False, False);

    if (op == vmi_SBB) {  // SBB is dest <- dest - src - (inverted) Carry
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);
    }

    vmimtBinopRC(size, op, tempS, imm, flags);

    if (op == vmi_CMP) {  // Don't store result for CMP operation
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);  // Carry is set when unsigned operation is >= 0
    } else {
        vmimtStoreRRO16(size, offset, regD, tempS, M16C_ENDIAN, False);
        if (op == vmi_SUB || op == vmi_SBB) {  // For these instructions Carry is set when unsigned operation is >= 0
            vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);
        }
    }
}

static M16C_MORPH_FN(binOpOO) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiReg      tempS    = M16C_TEMPS_REG;
    vmiReg      tempD    = M16C_TEMPD_REG;
    Int32       offsetS  = (state->info).offsetS;
    Int32       offsetD  = (state->info).offsetD;
    vmiBinop    op     = (state->info).optype;
    vmiFlagsCP  flags  = (state->info).flags;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("binOp OO");
    vmimtLoadRRO16(size, size, offsetS, tempS, regS, M16C_ENDIAN, False, False);
    vmimtLoadRRO16(size, size, offsetD, tempD, regD, M16C_ENDIAN, False, False);

    if (op == vmi_SBB) {  // SBB is dest <- dest - src - (inverted) Carry
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);
    }

    vmimtBinopRR(size, op, tempD, tempS, flags);

     if (op == vmi_CMP) {  // Don't store result for CMP operation
        vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);  // Carry is set when unsigned operation is >= 0
     } else {
        vmimtStoreRRO16(size, offsetD, regD, tempD, M16C_ENDIAN, False);
        if (op == vmi_SUB || op == vmi_SBB) {  // For these instructions Carry is set when unsigned operation is >= 0
            vmimtBinopRC(BOOL_BITS, vmi_XOR, M16C_CARRYF_REG, 1, 0);
        }
     }
}


static M16C_MORPH_FN(bitOpR) {
    Uns32       cons    = (state->info).cons;
    vmiReg      regD    = getRd(&state->info);
    vmiBinop    op     = (state->info).optype;
    // vmiFlagsCP  flags  = (state->info).flags;

    // TODO: Check that bit offsets and masks are computed correctly
    DEBUG_MORPH_FN("bitOp R");
    // vmiPrintf("Cons = %x,bytes=%d\n",cons,(state->info).bytes);
    vmimtBinopRC(16, op, regD, cons, 0);
}


static M16C_MORPH_FN(bitOpO) {
    Uns32       cons    = (state->info).cons;
    vmiReg      regD    = getRd(&state->info);
    vmiBinop    op     = (state->info).optype;
    vmiReg      tempD    = M16C_TEMPD_REG;
    Int32       offsetD  = (state->info).offsetD;

    // vmiFlagsCP  flags  = (state->info).flags;

    // TODO: Check that bit offsets and masks are computed correctly

    DEBUG_MORPH_FN("bitOp O");

    vmimtLoadRRO16(16, 16, offsetD, tempD, regD, M16C_ENDIAN, False, False);

    vmimtBinopRC(16, op, regD, cons, 0);

    vmimtStoreRRO16(16, offsetD, regD, tempD, M16C_ENDIAN, False);
}


static M16C_MORPH_FN(bitOpC) {
//  Uns32       cons    = (state->info).cons;
//  vmiReg      regD    = getRd(&state->info);
//  vmiBinop    op     = (state->info).optype;
    // vmiFlagsCP  flags  = (state->info).flags;

    // TODO: Check that bit offsets and masks are computed correctly

    DEBUG_MORPH_FN("bitOp C");
    // vmiPrintf("Cons = %x,bytes=%d\n",cons,(state->info).bytes);
  //  vmimtBinopRC(16, op,regD,cons,0);
}


static M16C_MORPH_FN(breakOp) {
    DEBUG_MORPH_FN("breakOp");
    m16cP m16c = state->m16c;

    if(m16c->compat!=COMPAT_NOPBRK) {
        // On hardware break instruction triggers interrupt at vector 0xFFFE4
        // For now just halt simulation
        vmimtFinish();
    }
}


static M16C_MORPH_FN(divOpR) {
    vmiReg      regS    = getRs(&state->info);
    Uns8        size   = getSize(&state->info);
    vmiBinop    op     = (state->info).optype;

    DEBUG_MORPH_FN("divOpR");

    if (size == 8)
        vmimtDivopRRR(size, op, M16C_REG(M16C_REG_R0L), M16C_REG(M16C_REG_R0H), M16C_REG(M16C_REG_R0H), M16C_REG(M16C_REG_R0L), regS, &flagsO);
    else
        vmimtDivopRRR(size, op, M16C_REG(M16C_REG_R0), M16C_REG(M16C_REG_R2), M16C_REG(M16C_REG_R2), M16C_REG(M16C_REG_R0), regS, &flagsO);
}

static M16C_MORPH_FN(divOpC) {
    Int32       imm    = (state->info).imm;
    vmiReg      tempS    = M16C_TEMPS_REG;
    Uns8        size   = getSize(&state->info);
    vmiBinop    op     = (state->info).optype;

    DEBUG_MORPH_FN("divOpC");

    vmimtMoveRC(size, tempS, imm);

    if (size == 8) {
        vmimtDivopRRR(size, op, M16C_REG(M16C_REG_R0L), M16C_REG(M16C_REG_R0H), M16C_REG(M16C_REG_R0H), M16C_REG(M16C_REG_R0L), tempS, &flagsO);
    } else {
        vmimtDivopRRR(size, op, M16C_REG(M16C_REG_R0), M16C_REG(M16C_REG_R2), M16C_REG(M16C_REG_R2), M16C_REG(M16C_REG_R0), tempS, &flagsO);
    }
}

static M16C_MORPH_FN(divOpO) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      tempS    = M16C_TEMPS_REG;
    Int32       offsetS  = (state->info).offsetS;
    Uns8        size   = getSize(&state->info);
    vmiBinop    op     = (state->info).optype;

    DEBUG_MORPH_FN("divOpO");

    vmimtLoadRRO16(size, size, offsetS, tempS, regS, M16C_ENDIAN, False, False);

    if (size == 8) {
        vmimtDivopRRR(size, op, M16C_REG(M16C_REG_R0L), M16C_REG(M16C_REG_R0H), M16C_REG(M16C_REG_R0H), M16C_REG(M16C_REG_R0L), tempS, &flagsO);
    } else {
        vmimtDivopRRR(size, op, M16C_REG(M16C_REG_R0), M16C_REG(M16C_REG_R2), M16C_REG(M16C_REG_R2), M16C_REG(M16C_REG_R0), tempS, &flagsO);
    }
}

static M16C_MORPH_FN(enterOp) {
    Int32       imm    = (state->info).imm;
    vmiReg      sp    = getSp(state);
    vmiReg      fb    = M16C_REG(M16C_REG_FB);


    DEBUG_MORPH_FN("enterOp");

    // Build stack frame
    // SP <- SP - 2
    // M(SP) <- FB
    // FB <- SP
    // SP <- SP - src

    vmimtStoreRRO16(16, -2, sp, fb, M16C_ENDIAN, False);  // M(SP-2) <- FB
    vmimtBinopRRC(16, vmi_SUB, fb, sp, 2, 0);  // FB <- SP - 2
    vmimtBinopRC(16, vmi_SUB, sp, imm+2, 0);  // SP <- SP - (src + 2)
}

static M16C_MORPH_FN(exitOp) {
    vmiReg      sp    = getSp(state);
    vmiReg      fb    = M16C_REG(M16C_REG_FB);
    vmiReg      temp    = M16C_TEMPD_REG;

    DEBUG_MORPH_FN("exitOp");

    // Deallocate stack frame

    // SP <- FB
    // FB <- M(SP)
    // SP <- SP + 2
    // PCml <- M(SP)
    // SP <- SP + 2
    // PCh <- M(SP)
    // SP <- SP + 1

    vmimtLoadRRO16(32, 32, 2, temp, fb, M16C_ENDIAN, False, False);  // tempPC <- M(SP+2)
    vmimtBinopRRC(16, vmi_ADD, sp, fb, 5, 0);  // SP <- SP + 2 + 2 + 1

    vmimtLoadRRO16(16, 16, 0, fb, fb, M16C_ENDIAN, False, False);  // FB <- M(SP)

    vmimtSetAddressMask(0x000FFFFF);
    vmimtUncondJumpReg(0, temp, VMI_NOREG, vmi_JH_RETURN);
}


// Extend sign.  If size B extend from 8 to 16 bits.  If size W, extend from 16 to 32 bits.
static M16C_MORPH_FN(extsOpR) {
    vmiReg      regS    = getRs(&state->info);
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("extsOpR");

    vmimtMoveExtendRR(size*2, regS, size, regS, True);

    if (size == 8) {  // Flags are not modified for size W
        vmimtBinopRC(16, vmi_CMP, regS, 0, &flagsZS);
    }
}

static M16C_MORPH_FN(extsOpO) {  // Should only be for size==B, Form 2 for size W only operates on R0
    vmiReg      regS    = getRs(&state->info);
    vmiReg      temp    = M16C_TEMPS_REG;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("extsOpO");

    vmimtLoadRRO16(size, size, 0, temp, regS, M16C_ENDIAN, False, False);
    vmimtMoveExtendRR(size*2, temp, size, temp, True);
    vmimtStoreRRO16(size*2, 0, regS, temp, M16C_ENDIAN, False);
    if (size == 8) {  // Flags are not modified for size W
        vmimtBinopRC(16, vmi_CMP, temp, 0, &flagsZS);
    }
}

static M16C_MORPH_FN(intOp) {
    Int32       imm    = (state->info).imm;
    vmiReg      sp     = (imm <= 31) ? M16C_REG(M16C_REG_ISP) : M16C_REG(M16C_REG_USP);
    vmiReg      temp    = M16C_TEMPD_REG;
    vmiReg      temp2   = M16C_TEMPS_REG;

    DEBUG_MORPH_FN("intOp");

    // Trigger interrupt

    // SP <- SP - 2
    // M(SP) <- (PC + 2)H, FLG
    // SP <- SP - 2
    // M(SP) <- (PC + 2)ML
    // PC <- M(IntBase +  src  * 4)

    M16C_GET_FLG();
    vmimtMoveRSimPC(32, temp);   // temp <- PC
    vmimtBinopRC(32, vmi_ADD, temp, 2, 0);

    vmimtBinopRRC(32, vmi_SHR, temp2, temp, 16, 0);  // Move upper bytes of PC to temp2
    vmimtBinopRR(16, vmi_OR, temp2, M16C_REG(M16C_REG_FLG), 0);  // Or PCH with FLG

    vmimtStoreRRO16(16, -2, sp, temp2, M16C_ENDIAN, False);  // M(SP) <- PCH | FLG
    vmimtStoreRRO16(16, -4, sp, temp, M16C_ENDIAN, False);   // M(SP) <- PCL

    vmimtBinopRC(16, vmi_SUB, sp, 4, 0);  // SP <- SP - 2 - 2

    vmimtLoadRRO16(32, 32, (imm*4), temp, M16C_REG(M16C_REG_INTB), M16C_ENDIAN, False, False);

    if (imm <= 31) {  // U Flag is cleared if INT number is equal or less than 31
        vmimtMoveRC(8, M16C_SPSELECTF_REG, 0);  // Clear U
    }

    vmimtMoveRC(8, M16C_INTENABLE_REG, 0);  // Clear I
    vmimtMoveRC(8, M16C_DEBUGF_REG, 0);  // Clear D

    vmimtUncondJumpReg(0, temp, VMI_NOREG, vmi_JH_CALLINT);
}

static M16C_MORPH_FN(intoOp) {
    vmiReg      sp    = getSp(state);
    vmiReg      temp    = M16C_TEMPD_REG;
    vmiReg      temp2   = M16C_TEMPS_REG;
    vmiLabelP   label_end  = vmimtNewLabel();

    DEBUG_MORPH_FN("intoOp");

    // Interrupt on overflow

    // SP <- SP - 2
    // M(SP) <- (PC + 1)H, FLG
    // SP <- SP - 2
    // M(SP) <- (PC + 1)ML
    // PC <- M(FFFE016)

    vmimtCondJumpLabel(M16C_OVERFLOWF_REG, False, label_end);

    M16C_GET_FLG();
    vmimtMoveRSimPC(32, temp);   // temp <- PC
    vmimtBinopRC(32, vmi_ADD, temp, 2, 0);

    vmimtBinopRRC(16, vmi_SHR, temp2, temp, 16, 0);  // Move upper bytes of PC to temp2
    vmimtBinopRR(16, vmi_OR, temp2, M16C_REG(M16C_REG_FLG), 0);  // Or PCH with FLG

    vmimtStoreRRO16(16, -2, sp, temp2, M16C_ENDIAN, False);  // M(SP) <- PCH | FLG
    vmimtStoreRRO16(16, -4, sp, temp, M16C_ENDIAN, False);   // M(SP) <- PCL

    vmimtBinopRC(16, vmi_SUB, sp, 4, 0);  // SP <- SP + 2 + 2 + 1


    vmimtMoveRC(8, M16C_SPSELECTF_REG, 0);  // Clear U
    vmimtMoveRC(8, M16C_INTENABLE_REG, 0);  // Clear I
    vmimtMoveRC(8, M16C_DEBUGF_REG, 0);  // Clear D

    vmimtUncondJump(0, 0xFFFE0, VMI_NOREG, vmi_JH_CALLINT);

    vmimtInsertLabel(label_end);
}

static M16C_MORPH_FN(jmpOp) {
    vmiReg      flg = VMI_NOREG;
    Bool     ifTrue = True;

    DEBUG_MORPH_FN("jmpOp");

    switch ((state->info).cond) {
        case GEU:
            flg = M16C_CARRYF_REG;
            ifTrue = True;
            break;
        case EQ:
            flg = M16C_ZEROF_REG;
            ifTrue = True;
            break;
        case PZ:
            flg = M16C_SIGNF_REG;
            ifTrue = False;
            break;
        case O:
            flg = M16C_OVERFLOWF_REG;
            ifTrue = True;
            break;
        case LTU:
            flg = M16C_CARRYF_REG;
            ifTrue = False;
            break;
        case NE:
            flg = M16C_ZEROF_REG;
            ifTrue = False;
            break;
        case N:
            flg = M16C_SIGNF_REG;
            ifTrue = True;
            break;
        case NO:
            flg = M16C_OVERFLOWF_REG;
            ifTrue = False;
            break;
        case GTU:
            vmimtBinopRRC(8, vmi_XOR, M16C_TEMPF_REG, M16C_ZEROF_REG, 1, 0);
            vmimtBinopRR(8, vmi_AND, M16C_TEMPF_REG, M16C_CARRYF_REG, 0);
            flg = M16C_TEMPF_REG;
            ifTrue = True;
            break;
        case GE:
            vmimtBinopRRR(8, vmi_XOR, M16C_TEMPF_REG, M16C_SIGNF_REG, M16C_OVERFLOWF_REG, 0);
            flg = M16C_TEMPF_REG;
            ifTrue = False;
            break;
        case GT:
            vmimtBinopRRR(8, vmi_XOR, M16C_TEMPF_REG, M16C_SIGNF_REG, M16C_OVERFLOWF_REG, 0);
            vmimtBinopRR(8, vmi_OR, M16C_TEMPF_REG, M16C_ZEROF_REG, 0);
            flg = M16C_TEMPF_REG;
            ifTrue = False;
            break;
        case LEU:
            vmimtBinopRRC(8, vmi_XOR, M16C_TEMPF_REG, M16C_ZEROF_REG, 1, 0);
            vmimtBinopRR(8, vmi_AND, M16C_TEMPF_REG, M16C_CARRYF_REG, 0);
            flg = M16C_TEMPF_REG;
            ifTrue = False;
            break;
        case LE:
            vmimtBinopRRR(8, vmi_XOR, M16C_TEMPF_REG, M16C_SIGNF_REG, M16C_OVERFLOWF_REG, 0);
            vmimtBinopRR(8, vmi_OR, M16C_TEMPF_REG, M16C_ZEROF_REG, 0);
            flg = M16C_TEMPF_REG;
            ifTrue = True;
            break;
        case LT:
            vmimtBinopRRR(8, vmi_XOR, M16C_TEMPF_REG, M16C_SIGNF_REG, M16C_OVERFLOWF_REG, 0);
            flg = M16C_TEMPF_REG;
            ifTrue = True;
            break;
        case COND_NA:        // instruction has no condition
        // Error
            return;
    };

    vmimtCondJump(flg, ifTrue, 0, state->info.branchPC, VMI_NOREG, vmi_JH_NONE);
}

static M16C_MORPH_FN(jmpOpU) {
    DEBUG_MORPH_FN("jmpOpU");

    vmimtUncondJump(0, state->info.branchPC, VMI_NOREG, vmi_JH_NONE);
}



static M16C_MORPH_FN(jmpiOpR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      tempD    = M16C_TEMPD_REG;
    vmiReg      tempS    = M16C_TEMPS_REG;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("jmpiOpR");

    // When jump distance specifier (.length) is (.W)
    // PC <- PC +/- src

    // When jump distance specifier (.length) is (.A)
    // PC <- src

    if (size == 16) {
        vmimtMoveExtendRR(32, tempS, size, regS, False);
        vmimtMoveRSimPC(32, tempD);
        vmimtBinopRR(32, vmi_ADD, tempD, tempS, 0);
    } else {
        vmimtMoveRR(size, tempD, regS);
    }
    vmimtUncondJumpReg(0, tempD, VMI_NOREG, vmi_JH_NONE);
}

static M16C_MORPH_FN(jmpiOpO) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      tempS    = M16C_TEMPS_REG;
    vmiReg      tempD    = M16C_TEMPD_REG;
    Int32       offset  = (state->info).offsetS;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("jmpiOpO");

    // When jump distance specifier (.length) is (.W)
    // PC <- PC +/- src

    // When jump distance specifier (.length) is (.A)
    // PC <- src

    if (size == 16) {
        vmimtLoadRRO16(size, size, offset, tempD, regS, M16C_ENDIAN, False, False);
        vmimtMoveExtendRR(32, tempS, size, tempD, True);
        vmimtMoveRSimPC(32, tempD);
        vmimtBinopRR(32, vmi_ADD, tempD, tempS, 0);

    } else {
        vmimtLoadRRO16(32, 32, offset, tempD, regS, M16C_ENDIAN, False, False);
        vmimtBinopRC(32, vmi_AND, tempD, 0xFFFFF, 0);
    }
    vmimtUncondJumpReg(0, tempD, VMI_NOREG, vmi_JH_NONE);
}

static M16C_MORPH_FN(jsrOp) {
    vmiReg      sp    = getSp(state);
    vmiReg      temp    = M16C_TEMPD_REG;
    vmiReg      temp2   = M16C_TEMPS_REG;

    DEBUG_MORPH_FN("jsrOp");

    // Jump Subroutine
    //
    // SP <- SP – 1
    // M(SP) <- (PC + n)H
    // SP <- SP – 2
    // M(SP) <- (PC + n)ML
    // PC <- label

    vmimtMoveRSimPC(32, temp);   // temp <- PC
    vmimtBinopRC(32, vmi_ADD, temp, state->info.bytes, 0);

    vmimtBinopRRC(32, vmi_SHR, temp2, temp, 16, 0);  // Move upper bytes of PC to temp2
    vmimtStoreRRO16(8, -1, sp, temp2, M16C_ENDIAN, False);  // M(SP) <- PCH

    vmimtStoreRRO16(16, -3, sp, temp, M16C_ENDIAN, False);   // M(SP) <- PCL

    vmimtBinopRC(16, vmi_SUB, sp, 3, 0);  // SP <- SP - 1 - 2

    vmimtUncondJump(0, state->info.branchPC, VMI_NOREG, vmi_JH_CALL);
}

static M16C_MORPH_FN(jsriOp) {
    vmiReg      sp    = getSp(state);
    vmiReg      temp    = M16C_TEMPD_REG;
    vmiReg      temp2   = M16C_TEMPS_REG;

    // TODO: JSRI code is same as JSR for src=abs16, needs to be changed when src is a register

    // When jump distance specifier (.length) is (.W)
    // SP <- SP - 1
    // M(SP) <- (PC + n)H
    // SP <- SP - 2
    // M(SP) <- (PC + n)ML
    // PC <- PC +/- src

    // When jump distance specifier (.length) is (.A)
    // SP <- SP - 1
    // M(SP) <- (PC + n)H
    // SP <- SP - 2
    // M(SP) <- (PC + n)ML
    // PC <- src

    DEBUG_MORPH_FN("jsriOpU");

    vmimtMoveRSimPC(32, temp);   // temp <- PC
    vmimtBinopRC(32, vmi_ADD, temp, state->info.bytes, 0);

    vmimtBinopRRC(32, vmi_SHR, temp2, temp, 16, 0);  // Move upper bytes of PC to temp2
    vmimtStoreRRO16(8, -1, sp, temp2, M16C_ENDIAN, False);  // M(SP) <- PCH

    vmimtStoreRRO16(16, -3, sp, temp, M16C_ENDIAN, False);   // M(SP) <- PCL

    vmimtBinopRC(16, vmi_SUB, sp, 3, 0);  // SP <- SP - 1 - 2

    vmimtUncondJump(0, state->info.branchPC, VMI_NOREG, vmi_JH_CALL);
}


static M16C_MORPH_FN(jsrsOp) {
    vmiReg      sp    = getSp(state);
    vmiReg      temp    = M16C_TEMPD_REG;
    vmiReg      temp2   = M16C_TEMPS_REG;


    DEBUG_MORPH_FN("jsrsOp");

    // Jump subroutine special page
    //
    // SP <- SP - 1
    // M(SP) <- (PC + 2)H
    // SP <- SP - 2
    // M(SP) <- (PC + 2)ML
    // PCH <- 0F
    // PCML <- M (FFFFE - src)


    vmimtMoveRSimPC(32, temp);   // temp <- PC
    vmimtBinopRC(32, vmi_ADD, temp, state->info.bytes, 0);

    vmimtBinopRRC(32, vmi_SHR, temp2, temp, 16, 0);  // Move upper bytes of PC to temp2
    vmimtStoreRRO16(8, -1, sp, temp2, M16C_ENDIAN, False);  // M(SP) <- PCH

    vmimtStoreRRO16(16, -3, sp, temp, M16C_ENDIAN, False);   // M(SP) <- PCL

    vmimtBinopRC(16, vmi_SUB, sp, 3, 0);  // SP <- SP - 1 - 2

    // TODO: Check that branchPC is computed correctly, and if so may be able to merge morph funtion with other jsr function

    vmimtUncondJump(0, state->info.branchPC, VMI_NOREG, vmi_JH_CALL);
}

static M16C_MORPH_FN(ldctxOp) {
    DEBUG_MORPH_FN("ldctxOp");
    // TODO: Implement ldctx instruction
}

static M16C_MORPH_FN(ldiplOp) {
    Int32       imm    = (state->info).imm;

    DEBUG_MORPH_FN("ldiplOp");

    vmimtMoveRC(8, M16C_IPL_REG, imm);
}

static M16C_MORPH_FN(moveOpRR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    Uns8        size   = getSize(&state->info);
    vmiFlagsCP  flags  = (state->info).flags;

    DEBUG_MORPH_FN("moveOp RR");

    if (VMI_REG_EQUAL(regS, M16C_REG(M16C_REG_FLG))) {
            M16C_GET_FLG();
    }
    vmimtMoveRR(size, regD, regS);
    if (flags != &flagsNONE)
        vmimtBinopRC(size, vmi_CMP, regD, 0, flags);
}


static M16C_MORPH_FN(moveOpRC) {
    Int32       imm    = (state->info).imm;
    vmiReg      regD    = getRd(&state->info);
    Uns8        size   = getSize(&state->info);
    vmiFlagsCP  flags  = (state->info).flags;

    DEBUG_MORPH_FN("moveOp RC");
    vmimtMoveRC(size, regD, imm);
    if (flags != &flagsNONE)
        vmimtBinopRC(size, vmi_CMP, regD, 0, flags);
}

static M16C_MORPH_FN(moveOpRO) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    Int32       offset  = (state->info).offsetS;
    Uns8        size   = getSize(&state->info);
    vmiFlagsCP  flags  = (state->info).flags;

    DEBUG_MORPH_FN("moveOp RO");

    vmimtLoadRRO16(size, size, offset, regD, regS, M16C_ENDIAN, False, False);
    if ((VMI_REG_EQUAL(regD, M16C_REG(M16C_REG_A0)) || VMI_REG_EQUAL(regD, M16C_REG(M16C_REG_A1))) && size == 8) {  // For .B move to Address register, zero-extend
        vmimtMoveExtendRR(16, M16C_REG(M16C_REG_A0), 8, M16C_REG(M16C_REG_A0), False);
    }

    if (flags != &flagsNONE) {
        vmimtBinopRC(size, vmi_CMP, regD, 0, flags);
    }
}

static M16C_MORPH_FN(moveOpOR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    Int32       offset  = (state->info).offsetD;
    // vmiReg      temp    = M16C_TEMPD_REG;
    Uns8        size   = getSize(&state->info);
    vmiFlagsCP  flags  = (state->info).flags;

    DEBUG_MORPH_FN("moveOp OR");

    if (VMI_REG_EQUAL(regS, M16C_REG(M16C_REG_FLG))) {
        M16C_GET_FLG();
    }

    vmimtStoreRRO16(size, offset, regD, regS, M16C_ENDIAN, False);
    if (flags != &flagsNONE)
        vmimtBinopRC(size, vmi_CMP, regS, 0, flags);
}

static M16C_MORPH_FN(moveOpOC) {
    Int32       imm    = (state->info).imm;
    vmiReg      regD    = getRd(&state->info);
    Int32       offset  = (state->info).offsetD;
    Uns8        size   = getSize(&state->info);
    // vmiFlagsCP  flags  = (state->info).flags;

    DEBUG_MORPH_FN("moveOp OC");

    vmimtStoreRCO16(size, offset, regD, imm, M16C_ENDIAN, False);
    // if (flags == &flagsZS)
    {
        vmimtMoveRC(size, M16C_ZEROF_REG, (imm == 0)? True : False);
        vmimtMoveRC(size, M16C_SIGNF_REG, (imm >> (size - 1)) ? True : False);
    }
}

static M16C_MORPH_FN(moveOpOO) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPS_REG;
    Int32       offsetS  = (state->info).offsetS;
    Int32       offsetD  = (state->info).offsetD;
    Uns8        size   = getSize(&state->info);
    vmiFlagsCP  flags  = (state->info).flags;

    DEBUG_MORPH_FN("moveOp OO");
    vmimtLoadRRO16(size, size, offsetS, temp, regS, M16C_ENDIAN, False, False);
    vmimtStoreRRO16(size, offsetD, regD, temp, M16C_ENDIAN, False);
    if (flags != &flagsNONE) {
        vmimtBinopRC(size, vmi_CMP, temp, 0, flags);
    }
}

static M16C_MORPH_FN(checkCond) {
    vmiLabelP   label_jump  = vmimtNewLabel();

    DEBUG_MORPH_FN("checkCond");

    if ((state->info).cond == EQ) {
        vmimtCondJumpLabel(M16C_ZEROF_REG, True, label_jump);
    } else if ((state->info).cond == NE) {
        vmimtCondJumpLabel(M16C_ZEROF_REG, False, label_jump);
    }

    return;

    vmimtInsertLabel(label_jump);
    state->attrs->condMorphCB(state);
}


static M16C_MORPH_FN(movefOp) {
    Int32       imm    = (state->info).imm;
    vmiReg      reg    = getFlgReg(&state->info);

    DEBUG_MORPH_FN("movefOp");
    vmimtMoveRC(8, reg, imm);
}

static M16C_MORPH_FN(moveaOp) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    Int32       offset  = (state->info).offsetS;

    DEBUG_MORPH_FN("moveaOp");
    if (VMI_REG_EQUAL(regS, VMI_NOREG)) {  // Abs16 addressing
        vmimtMoveRC(16, regD, offset);
    } else {
        vmimtBinopRRC(16, vmi_ADD, regD, regS, offset, 0);
    }
}

static M16C_MORPH_FN(popOpR) {
    vmiReg      sp    = getSp(state);
    vmiReg      regD    = getRd(&state->info);

    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("popOp R");

    vmimtLoadRRO16(size, size, 0, regD, sp, M16C_ENDIAN, False, False);

    if (VMI_REG_EQUAL(regD, M16C_REG(M16C_REG_FLG))) {
        M16C_SET_FLG();
    }

    if (size == 8) {
        vmimtBinopRC(16, vmi_ADD, sp, 1, 0);
    } else {
        vmimtBinopRC(16, vmi_ADD, sp, 2, 0);
    }
}

static M16C_MORPH_FN(popOpO) {
    vmiReg      sp      = getSp(state);
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPS_REG;
    Int32       offset  = (state->info).offsetD;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("popOp O");

    vmimtLoadRRO16(size, size, 0, temp, sp, M16C_ENDIAN, False, False);
    vmimtStoreRRO16(size, offset, regD, temp, M16C_ENDIAN, False);
    if (size == 8) {
        vmimtBinopRC(16, vmi_ADD, sp, 1, 0);
    } else {
        vmimtBinopRC(16, vmi_ADD, sp, 2, 0);
    }
}

static M16C_MORPH_FN(popOpM) {
    vmiReg      sp      = getSp(state);
    Int32       imm     = (state->info).imm;
    Int32       offset  = 0;

    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("popOpM");

    if (imm & 0x01) {
        vmimtLoadRRO16(size, size, offset, M16C_REG(M16C_REG_R0), sp, M16C_ENDIAN, False, False);
        offset = offset + 2;
    }
    if (imm & 0x02) {
        vmimtLoadRRO16(size, size, offset, M16C_REG(M16C_REG_R1), sp, M16C_ENDIAN, False, False);
        offset = offset + 2;
    }
    if (imm & 0x04) {
        vmimtLoadRRO16(size, size, offset, M16C_REG(M16C_REG_R2), sp, M16C_ENDIAN, False, False);
        offset = offset + 2;
    }
    if (imm & 0x08) {
        vmimtLoadRRO16(size, size, offset, M16C_REG(M16C_REG_R3), sp, M16C_ENDIAN, False, False);
        offset = offset + 2;
    }
    if (imm & 0x10) {
        vmimtLoadRRO16(size, size, offset, M16C_REG(M16C_REG_A0), sp, M16C_ENDIAN, False, False);
        offset = offset + 2;
    }
    if (imm & 0x20) {
        vmimtLoadRRO16(size, size, offset, M16C_REG(M16C_REG_A1), sp, M16C_ENDIAN, False, False);
        offset = offset + 2;
    }
    if (imm & 0x40) {
        vmimtLoadRRO16(size, size, offset, M16C_REG(M16C_REG_SB), sp, M16C_ENDIAN, False, False);
        offset = offset + 2;
    }
    if (imm & 0x80) {
        vmimtLoadRRO16(size, size, offset, M16C_REG(M16C_REG_FB), sp, M16C_ENDIAN, False, False);
        offset = offset + 2;
    }

    vmimtBinopRC(16, vmi_ADD, sp, offset, 0);
}

static M16C_MORPH_FN(pushOpR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      sp    = getSp(state);

    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("pushOp R");

    if (size == 8) {
        vmimtBinopRC(16, vmi_ADD, sp, -1, 0);
    } else {
        vmimtBinopRC(16, vmi_ADD, sp, -2, 0);
    }

    if (VMI_REG_EQUAL(regS, M16C_REG(M16C_REG_FLG))) {
        M16C_GET_FLG();
    }
    vmimtStoreRRO16(size, 0, sp, regS, M16C_ENDIAN, False);
}

static M16C_MORPH_FN(pushOpC) {
    Int32       imm    = (state->info).imm;
    vmiReg      sp    = getSp(state);

    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("pushOp C");

    if (size == 8)
        vmimtBinopRC(16, vmi_ADD, sp, -1, 0);
    else
        vmimtBinopRC(16, vmi_ADD, sp, -2, 0);
    vmimtStoreRCO(size, 0, sp, imm, M16C_ENDIAN, False);
}

static M16C_MORPH_FN(pushOpO) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      sp      = getSp(state);
    vmiReg      temp    = M16C_TEMPS_REG;
    Int32       offset  = (state->info).offsetS;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("pushOp O");

    if (size == 8) {
        vmimtBinopRC(16, vmi_ADD, sp, -1, 0);
    } else {
        vmimtBinopRC(16, vmi_ADD, sp, -2, 0);
    }
    vmimtLoadRRO16(size, size, offset, temp, regS, M16C_ENDIAN, False, False);
    vmimtStoreRRO16(size, 0, sp, temp, M16C_ENDIAN, False);
}

static M16C_MORPH_FN(pushOpM) {
    vmiReg      sp      = getSp(state);
    Int32       imm     = (state->info).imm;
    Int32       offset  = -2;

    Uns8        size   = 16;

    DEBUG_MORPH_FN("pushOpM");

    if (imm & 0x01) {
        vmimtStoreRRO16(size, offset, sp, M16C_REG(M16C_REG_FB), M16C_ENDIAN, False);
        offset = offset - 2;
    }
    if (imm & 0x02) {
        vmimtStoreRRO16(size, offset, sp, M16C_REG(M16C_REG_SB), M16C_ENDIAN, False);
        offset = offset - 2;
    }
    if (imm & 0x04) {
        vmimtStoreRRO16(size, offset, sp, M16C_REG(M16C_REG_A1), M16C_ENDIAN, False);
        offset = offset - 2;
    }
    if (imm & 0x08) {
        vmimtStoreRRO16(size, offset, sp, M16C_REG(M16C_REG_A0), M16C_ENDIAN, False);
        offset = offset - 2;
    }
    if (imm & 0x10) {
        vmimtStoreRRO16(size, offset, sp, M16C_REG(M16C_REG_R3), M16C_ENDIAN, False);
        offset = offset - 2;
    }
    if (imm & 0x20) {
        vmimtStoreRRO16(size, offset, sp, M16C_REG(M16C_REG_R2), M16C_ENDIAN, False);
        offset = offset - 2;
    }
    if (imm & 0x40) {
        vmimtStoreRRO16(size, offset, sp, M16C_REG(M16C_REG_R1), M16C_ENDIAN, False);
        offset = offset - 2;
    }
    if (imm & 0x80) {
        vmimtStoreRRO16(size, offset, sp, M16C_REG(M16C_REG_R0), M16C_ENDIAN, False);
        offset = offset - 2;
    }

    vmimtBinopRC(16, vmi_ADD, sp, offset+2, 0);
}

static M16C_MORPH_FN(reitOp) {
    vmiReg      sp    = getSp(state);
    vmiReg      temp    = M16C_TEMPD_REG;

    DEBUG_MORPH_FN("reitOp");

    // Return from Interrupt
    //
    // PCML <- M(SP)
    // SP <- SP + 2
    // PCH, FLG <- M(SP)
    // SP <- SP + 2

    vmimtLoadRRO16(16, 16, 2, temp, sp, M16C_ENDIAN, False, False);
    vmimtBinopRRC(16, vmi_AND, M16C_REG(M16C_REG_FLG), temp, 0x70FF, 0);

    vmimtLoadRRO16(32, 32, 0, temp, sp, M16C_ENDIAN, False, False);
    vmimtBinopRC(32, vmi_AND, temp, 0x000FFFFF, 0);

    vmimtBinopRC(16, vmi_ADD, sp, 4, 0);  // SP <- SP + 2 + 2


    vmimtUncondJumpReg(0, temp, VMI_NOREG, vmi_JH_RETURNINT);
}

static M16C_MORPH_FN(rmpaOp) {
    DEBUG_MORPH_FN("rmpaOp");
    // TODO: Implement rmpa
}


// Shift and rotate instructions can have a positive or negative value indicating right or left
static M16C_MORPH_FN(rotOpRR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPS_REG;
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);
    vmiFlagsCP  flags  = (state->info).flags;

    vmiLabelP   label_end  = vmimtNewLabel();
    vmiLabelP   label_shr  = vmimtNewLabel();
    vmiLabelP   label_sha  = vmimtNewLabel();
    vmiLabelP   label_ror  = vmimtNewLabel();
    vmiLabelP   label_rcr  = vmimtNewLabel();

    DEBUG_MORPH_FN("rotOp RR");

    vmimtMoveRR(8, temp, regS);

    if (op == vmi_SHL) {
        vmimtCompareRCJumpLabel(8, vmi_COND_L, temp, 0, label_shr);
        vmimtBinopRR(size, vmi_SHL, regD, temp, flags);
        vmimtUncondJumpLabel(label_end);

        vmimtInsertLabel(label_shr);
        vmimtUnopR(8, vmi_NEG, temp, 0);
        vmimtBinopRR(size, vmi_SHR, regD, temp, flags);
    } else if (op == vmi_SAR) {
        vmimtCompareRCJumpLabel(8, vmi_COND_L, temp, 0, label_sha);
        vmimtBinopRR(size, vmi_SHL, regD, temp, flags);
        vmimtUncondJumpLabel(label_end);

        vmimtInsertLabel(label_sha);
        vmimtUnopR(8, vmi_NEG, temp, 0);
        vmimtBinopRR(size, vmi_SAR, regD, temp, flags);
    } else if (op == vmi_ROL) {
        vmimtCompareRCJumpLabel(8, vmi_COND_L, temp, 0, label_ror);
        vmimtBinopRR(size, vmi_ROL, regD, temp, flags);
        vmimtUncondJumpLabel(label_end);

        vmimtInsertLabel(label_ror);
        vmimtUnopR(8, vmi_NEG, temp, 0);
        vmimtBinopRR(size, vmi_ROR, regD, temp, flags);
    } else if (op == vmi_RCL) {
        vmimtCompareRCJumpLabel(8, vmi_COND_L, temp, 0, label_rcr);
        vmimtBinopRR(size, vmi_RCL, regD, temp, flags);
        vmimtUncondJumpLabel(label_end);

        vmimtInsertLabel(label_rcr);
        vmimtUnopR(8, vmi_NEG, temp, 0);
        vmimtBinopRR(size, vmi_RCR, regD, temp, flags);
    }

    vmimtInsertLabel(label_end);
}


// Shift and rotate instructions can have a positive or negative constant indicating right or left
static M16C_MORPH_FN(rotOpRC) {
    Int32       imm    = (state->info).imm;
    vmiReg      regD    = getRd(&state->info);
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);
    vmiFlagsCP  flags  = (state->info).flags;

    DEBUG_MORPH_FN("rotOp RC");


    if (op == vmi_SHL && imm < 0) {
        op = vmi_SHR;
        imm = 0 - imm;
    } else if (op == vmi_SAR && imm > 0) {
        op = vmi_SHL;

    } else if (op == vmi_SAR && imm < 0) {
        imm = 0 - imm;
    } else if (op == vmi_ROL && imm < 0) {
        op = vmi_ROR;
        imm = 0 - imm;
    } else if (op == vmi_RCL && imm < 0) {
        op = vmi_RCR;
        imm = 0 - imm;
    }

    vmimtSetShiftMask(31);
    vmimtBinopRC(size, op, regD, imm, flags);
}


// Shift and rotate instructions can have a positive or negative value indicating right or left
static M16C_MORPH_FN(rotOpOR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPS_REG;
    vmiReg      tempd    = M16C_TEMPD_REG;
    Int32       offset  = (state->info).offsetD;
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);

    vmiFlagsCP  flags  = (state->info).flags;

    vmiLabelP   label_end  = vmimtNewLabel();
    vmiLabelP   label_shr  = vmimtNewLabel();
    vmiLabelP   label_sha  = vmimtNewLabel();

    vmiLabelP   label_ror  = vmimtNewLabel();
    vmiLabelP   label_rcr  = vmimtNewLabel();

    DEBUG_MORPH_FN("rotOp OR");

    vmimtMoveRR(8, temp, regS);
    vmimtLoadRRO16(size, size, offset, tempd, regD, M16C_ENDIAN, False, False);

    if (op == vmi_SHL) {
        vmimtCompareRCJumpLabel(8, vmi_COND_L, temp, 0, label_shr);
        vmimtBinopRR(size, vmi_SHL, tempd, temp, flags);
        vmimtUncondJumpLabel(label_end);

        vmimtInsertLabel(label_shr);
        vmimtUnopR(8, vmi_NEG, temp, 0);
        vmimtBinopRR(size, vmi_SHR, tempd, temp, flags);
    } else if (op == vmi_SAR) {
        vmimtCompareRCJumpLabel(8, vmi_COND_L, temp, 0, label_sha);
        vmimtBinopRR(size, vmi_SHL, tempd, temp, flags);
        vmimtUncondJumpLabel(label_end);

        vmimtInsertLabel(label_sha);
        vmimtUnopR(8, vmi_NEG, temp, 0);
        vmimtBinopRR(size, vmi_SAR, tempd, temp, flags);
    } else if (op == vmi_ROL) {
        vmimtCompareRCJumpLabel(8, vmi_COND_L, temp, 0, label_ror);
        vmimtBinopRR(size, vmi_ROL, tempd, temp, flags);
        vmimtUncondJumpLabel(label_end);

        vmimtInsertLabel(label_ror);
        vmimtUnopR(8, vmi_NEG, temp, 0);
        vmimtBinopRR(size, vmi_ROR, tempd, temp, flags);
    } else if (op == vmi_RCL) {
        vmimtCompareRCJumpLabel(8, vmi_COND_L, temp, 0, label_rcr);
        vmimtBinopRR(size, vmi_RCL, tempd, temp, flags);
        vmimtUncondJumpLabel(label_end);

        vmimtInsertLabel(label_rcr);
        vmimtUnopR(8, vmi_NEG, temp, 0);
        vmimtBinopRR(size, vmi_RCR, tempd, temp, flags);
    }

    vmimtInsertLabel(label_end);
    vmimtStoreRRO16(size, offset, regD, tempd, M16C_ENDIAN, False);
}


// Shift and rotate instructions can have a positive or negative value indicating right or left
static M16C_MORPH_FN(rotOpOC) {
    Int32       imm    = (state->info).imm;
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPD_REG;
    Int32       offset  = (state->info).offsetD;
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);
    vmiFlagsCP  flags  = (state->info).flags;

    DEBUG_MORPH_FN("rotOp OC");
    if (op == vmi_SHL && imm < 0) {
        op = vmi_SHR;
        imm = 0 - imm;
    } else if (op == vmi_SAR && imm < 0) {
        imm = 0 - imm;
    } else if (op == vmi_SAR && imm > 0) {
        op = vmi_SHL;
    } else if (op == vmi_ROL && imm < 0) {
        op = vmi_ROR;
        imm = 0 - imm;
    } else if (op == vmi_RCL && imm < 0) {
        op = vmi_RCR;
        imm = 0 - imm;
    }
    vmimtLoadRRO16(size, size, offset, temp, regD, M16C_ENDIAN, False, False);
    vmimtBinopRC(size, op, temp, imm, flags);
    vmimtStoreRRO16(size, offset, regD, temp, M16C_ENDIAN, False);
}

static M16C_MORPH_FN(rtsOp) {
    vmiReg      sp    = getSp(state);
    vmiReg      temp    = M16C_TEMPD_REG;

    DEBUG_MORPH_FN("rtsOp");

    // Return from subroutine
    //
    // PCML <- M(SP)
    // SP <- SP + 2
    // PCH <- M(SP)
    // SP <- SP + 1

    vmimtLoadRRO16(32, 32, 0, temp, sp, M16C_ENDIAN, False, False);
    vmimtBinopRC(32, vmi_AND, temp, 0x000FFFFF, 0);

    vmimtBinopRC(16, vmi_ADD, sp, 3, 0);  // SP <- SP + 2 + 2

    vmimtUncondJumpReg(0, temp, VMI_NOREG, vmi_JH_RETURN);
}

static M16C_MORPH_FN(sbjnzOpRC) {
    Int32       imm     = (state->info).imm;
    vmiReg      regD    = getRd(&state->info);
    Uns8        size   = getSize(&state->info);
    vmiLabelP   label_end  = vmimtNewLabel();
    vmiBinop    op     = (state->info).optype;

    DEBUG_MORPH_FN("sbjnzOp RC");

    vmimtBinopRC(size, op, regD, imm, 0);
    vmimtCompareRCJumpLabel(16, vmi_COND_Z, regD, 0, label_end);  // Instruction does not modify FLG, so use labels for conditional jump
    vmimtUncondJump(0, state->info.branchPC, VMI_NOREG, vmi_JH_NONE);

    vmimtInsertLabel(label_end);
}

static M16C_MORPH_FN(sbjnzOpOC) {
    Int32       imm     = (state->info).imm;
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPD_REG;
    Int32       offset  = (state->info).offsetS;
    Uns8        size   = getSize(&state->info);
    vmiLabelP   label_end  = vmimtNewLabel();
    vmiBinop    op     = (state->info).optype;

    DEBUG_MORPH_FN("sbjnzOp OC");
    vmimtLoadRRO16(size, size, offset, temp, regD, M16C_ENDIAN, False, False);
    vmimtBinopRC(size, op, temp, imm, 0);
    vmimtStoreRRO16(size, offset, regD, temp, M16C_ENDIAN, False);

    vmimtCompareRCJumpLabel(16, vmi_COND_Z, temp, 0, label_end);  // Instruction does not modify FLG, so use labels for conditional jump
    vmimtUncondJump(0, state->info.branchPC, VMI_NOREG, vmi_JH_NONE);

    vmimtInsertLabel(label_end);
}


static M16C_MORPH_FN(smovOp) {
    vmiReg      temps   = M16C_TEMPS_REG;
    vmiReg      temp    = M16C_TEMPD_REG;
    Uns32       step    = (&state->info)->cons;  // -1 for SMOVB.B, -2 for SMOVB.W, +1 for SMOVF.B, +2 for SMOVF.W
    Uns8        size   = getSize(&state->info);
    vmiLabelP   label_end  = vmimtNewLabel();
    vmiLabelP   label_repeat  = vmimtNewLabel();

    DEBUG_MORPH_FN("smovOp");

    // SMOVB - String Move Backward
    // When size specifier (.size) is (.B)
    // Repeat
    //      M(A1) <- M(2^16 * R1H + A0)
    //      A0 <- A0 - 1
    //      A1 <- A1 - 1
    //      R3 <- R3 - 1
    // Until R3 == 0
    // When size specifier (.size) is (.W)
    // Repeat
    //      M(A1) <- M(2^16 * R1H + A0)
    //      A0 <- A0 - 2
    //      A1 <- A1 - 2
    //      R3 <- R3 - 1
    // Until R3 == 0
    // * If A0 underflows, the content of R1H is decremented by 1.


    // SMOVF - String Move Forward
    // When size specifier (.size) is (.B)
    // Repeat
    //      M(A1) <- M(2^16 * R1H + A0)
    //      A0 <- A0 + 1
    //      A1 <- A1 + 1
    //      R3 <- R3 - 1
    // Until R3 == 0
    // When size specifier (.size) is (.W)
    // Repeat
    //      M(A1) <- M(2^16 * R1H + A0)
    //      A0 <- A0 + 2
    //      A1 <- A1 + 2
    //      R3 <- R3 - 1
    // Until R3 == 0
    // * If A0 overflows, the content of R1H is incremented by 1.

    vmimtCompareRCJumpLabel(16, vmi_COND_Z, M16C_REG(M16C_REG_R3), 0, label_end);


    vmimtInsertLabel(label_repeat);

    vmimtMoveExtendRR(32, temps, 8, M16C_REG(M16C_REG_R1H), False);
    vmimtMoveExtendRR(32, temp, 16, M16C_REG(M16C_REG_A0), False);

    vmimtBinopRC(32, vmi_SHL, temps, 16, 0);
    vmimtBinopRR(32, vmi_OR, temps, temp, 0);

    vmimtLoadRRO(size, size, 0, temp, temps, M16C_ENDIAN, False, False);
    vmimtStoreRRO16(size, 0, M16C_REG(M16C_REG_A1), temp, M16C_ENDIAN, False);


    vmimtBinopRC(16, vmi_ADD, M16C_REG(M16C_REG_A0), step, 0);
    vmimtBinopRC(16, vmi_ADD, M16C_REG(M16C_REG_A1), step, 0);

    // TODO: Check if A0 under/overflowed and increment R1H if it did

    vmimtBinopRC(16, vmi_SUB, M16C_REG(M16C_REG_R3), 1, 0);
    vmimtCompareRCJumpLabel(16, vmi_COND_NZ, M16C_REG(M16C_REG_R3), 0, label_repeat);

    vmimtInsertLabel(label_end);
}

static M16C_MORPH_FN(sstrOp) {
    Uns32       step    = 1;
    Uns8        size   = getSize(&state->info);
    vmiLabelP   label_end  = vmimtNewLabel();
    vmiLabelP   label_repeat  = vmimtNewLabel();

    if (size == 8)
        step = 1;
    else
        step = 2;

    DEBUG_MORPH_FN("sstrOp");

    vmimtCompareRCJumpLabel(16, vmi_COND_Z, M16C_REG(M16C_REG_R3), 0, label_end);


    vmimtInsertLabel(label_repeat);

    vmimtStoreRRO16(size, 0, M16C_REG(M16C_REG_A1), M16C_REG(M16C_REG_R0L), M16C_ENDIAN, False);

    vmimtBinopRC(16, vmi_ADD, M16C_REG(M16C_REG_A1), step, 0);

    // TODO: Check if A0 overflowed and increment R1H if it did

    vmimtBinopRC(16, vmi_SUB, M16C_REG(M16C_REG_R3), 1, 0);
    vmimtCompareRCJumpLabel(16, vmi_COND_NZ, M16C_REG(M16C_REG_R3), 0, label_repeat);


    vmimtInsertLabel(label_end);
}

static M16C_MORPH_FN(stctxOp) {
    DEBUG_MORPH_FN("stctxOp");
    // TODO: Implement stctx
}


static M16C_MORPH_FN(stzxOpR) {
    Int32       imm     = (state->info).imm;
    Int32       imm2     = (state->info).cons;
    vmiReg      regD    = getRd(&state->info);
    Uns8        size   = getSize(&state->info);


    DEBUG_MORPH_FN("stzxOp");

    vmimtCondMoveRCC(size, M16C_ZEROF_REG, True, regD, imm, imm2);
}

static M16C_MORPH_FN(stzxOpO) {
    Int32       imm     = (state->info).imm;
    Int32       imm2     = (state->info).cons;
    vmiReg      regD    = getRd(&state->info);
    Int32       offset  = (state->info).offsetS;
    vmiReg      temp    = M16C_TEMPD_REG;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("stzxOp");

    vmimtCondMoveRCC(size, M16C_ZEROF_REG, True, temp, imm, imm2);
    vmimtStoreRRO16(size, offset, regD, temp, M16C_ENDIAN, False);
}



static M16C_MORPH_FN(undOp) {
    vmiReg      sp    = getSp(state);
    vmiReg      temp    = M16C_TEMPD_REG;
    vmiReg      temp2   = M16C_TEMPS_REG;

    DEBUG_MORPH_FN("undOp");

    vmimtMoveRSimPC(32, temp);   // temp <- PC
    vmimtBinopRC(32, vmi_ADD, temp, 1, 0);

    vmimtBinopRRC(16, vmi_SHR, temp2, temp, 16, 0);  // Move upper bytes of PC to temp2
    vmimtBinopRR(16, vmi_OR, temp2, M16C_REG(M16C_REG_FLG), 0);  // Or PCH with FLG

    vmimtStoreRRO16(16, -2, sp, temp2, M16C_ENDIAN, False);  // M(SP) <- PCH | FLG
    vmimtStoreRRO16(16, -4, sp, temp, M16C_ENDIAN, False);   // M(SP) <- PCL

    vmimtBinopRC(16, vmi_SUB, sp, 4, 0);  // SP <- SP - 2 - 2

    vmimtMoveRC(BOOL_BITS, M16C_SPSELECTF_REG, 0);  // Clear U
    vmimtMoveRC(BOOL_BITS, M16C_INTENABLE_REG, 0);  // Clear I
    vmimtMoveRC(BOOL_BITS, M16C_DEBUGF_REG, 0);  // Clear D

    vmimtUncondJump(0, 0xFFFDC, VMI_NOREG, vmi_JH_CALLINT);
}

static M16C_MORPH_FN(unOpR) {
    vmiReg      regD    = getRd(&state->info);
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);
    vmiFlagsCP  flags  = (state->info).flags;

    DEBUG_MORPH_FN("unOp R");
    vmimtUnopR(size, op, regD, flags);
    vmimtBinopRC(8, vmi_XOR, M16C_CARRYF_REG, 1, 0);
}

static M16C_MORPH_FN(unOpO) {
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPS_REG;
    Int32       offset  = (state->info).offsetD;
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);
    vmiFlagsCP  flags  = (state->info).flags;

    DEBUG_MORPH_FN("unOp O");
    vmimtLoadRRO16(size, size, offset, temp, regD, M16C_ENDIAN, False, False);
    vmimtUnopR(size, op, temp, flags);
    vmimtBinopRC(8, vmi_XOR, M16C_CARRYF_REG, 1, 0);

    vmimtStoreRRO16(size, offset, regD, temp, M16C_ENDIAN, False);
}


static M16C_MORPH_FN(unOpRR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);
    DEBUG_MORPH_FN("unOp RR");
    vmimtUnopRR(size, op, regD, regS, 0);
}

static M16C_MORPH_FN(unOpRC) {
    Int32       imm    = (state->info).imm;
    vmiReg      regD    = getRd(&state->info);
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("unOp RC");
    vmimtUnopRC(size, op, regD, imm, 0);
}

static M16C_MORPH_FN(unOpRO) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPS_REG;
    Int32       offset  = (state->info).offsetS;
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("unOp RO");
    vmimtLoadRRO16(size, size, offset, temp, regS, M16C_ENDIAN, False, False);
    vmimtUnopRR(size, op, regD, temp, 0);
}


static M16C_MORPH_FN(unOpOR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPD_REG;
    Int32       offset  = (state->info).offsetD;
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("unOp OR");
    vmimtUnopRR(size, op, temp, regS, 0);
    vmimtStoreRRO16(size, offset, regD, temp, M16C_ENDIAN, False);
}

static M16C_MORPH_FN(unOpOC) {
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPD_REG;
    Int32       offset  = (state->info).offsetD;
    Int32       imm    = (state->info).imm;
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("unOp OC");
    vmimtUnopRC(size, op, temp, imm, 0);
    vmimtStoreRRO16(size, offset, regD, temp, M16C_ENDIAN, False);
}


static M16C_MORPH_FN(unOpOO) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiReg      tempS    = M16C_TEMPS_REG;
    vmiReg      tempD    = M16C_TEMPD_REG;
    Int32       offsetS  = (state->info).offsetS;
    Int32       offsetD  = (state->info).offsetD;
    vmiBinop    op     = (state->info).optype;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("unOp OO");
    vmimtLoadRRO16(size, size, offsetS, tempS, regS, M16C_ENDIAN, False, False);
    vmimtUnopRR(size, op, tempD, tempS, 0);
    vmimtStoreRRO16(size, offsetD, regD, tempD, M16C_ENDIAN, False);
}


static M16C_MORPH_FN(waitOp) {
    DEBUG_MORPH_FN("waitOp");
    vmimtHalt();
}

static M16C_MORPH_FN(xchgOpRR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPS_REG;
    Uns8        size   = getSize(&state->info);


    DEBUG_MORPH_FN("xchgOp RR");

    vmimtMoveRR(size, temp, regS);
    vmimtMoveRR(size, regS, regD);
    vmimtMoveRR(size, regD, temp);
}

static M16C_MORPH_FN(xchgOpOR) {
    vmiReg      regS    = getRs(&state->info);
    vmiReg      regD    = getRd(&state->info);
    vmiReg      temp    = M16C_TEMPS_REG;
    Int32       offset  = (state->info).offsetD;
    Uns8        size   = getSize(&state->info);

    DEBUG_MORPH_FN("xchgOp OR");
    vmimtMoveRR(size, temp, regS);
    vmimtLoadRRO16(size, size, offset, regS, regD, M16C_ENDIAN, False, False);
    vmimtStoreRRO16(size, offset, regD, temp, M16C_ENDIAN, False);
}

//
// Default morpher callback
//
static M16C_MORPH_FN(morphDefault) {
    // print message warning about the undecoded instruction
    vmimtArgProcessor();
    vmimtArgUns32(state->info.thisPC);
    vmimtArgUns32(state->info.instruction);
    vmimtCall((vmiCallFn)undecoded);
}


const static m16cMorphAttr dispatchTable[M16C_MT_LAST+1] = {
        [M16C_MT_BINOP_R_R]            = {morphCB:binOpRR},
        [M16C_MT_BINOP_R_C]            = {morphCB:binOpRC},
        [M16C_MT_BINOP_R_O]            = {morphCB:binOpRO},
        [M16C_MT_BINOP_O_R]            = {morphCB:binOpOR},
        [M16C_MT_BINOP_O_C]            = {morphCB:binOpOC},
        [M16C_MT_BINOP_O_O]            = {morphCB:binOpOO},
        [M16C_MT_BITOP_R]              = {morphCB:bitOpR},
        [M16C_MT_BITOP_O]              = {morphCB:bitOpO},
        [M16C_MT_BITOPC]               = {morphCB:bitOpC},
        [M16C_MT_DIV_R]                = {morphCB:divOpR},
        [M16C_MT_DIV_C]                = {morphCB:divOpC},
        [M16C_MT_DIV_O]                = {morphCB:divOpO},
        [M16C_MT_JMPI_R]               = {morphCB:jmpiOpR},
        [M16C_MT_JMPI_C]               = {},
        [M16C_MT_JMPI_O]               = {morphCB:jmpiOpO},
        [M16C_MT_UNOP_R]               = {morphCB:unOpR},
        [M16C_MT_UNOP_O]               = {morphCB:unOpO},
        [M16C_MT_UNOP_R_R]             = {morphCB:unOpRR},
        [M16C_MT_UNOP_R_C]             = {morphCB:unOpRC},
        [M16C_MT_UNOP_R_O]             = {morphCB:unOpRO},
        [M16C_MT_UNOP_O_R]             = {morphCB:unOpOR},
        [M16C_MT_UNOP_O_C]             = {morphCB:unOpOC},
        [M16C_MT_UNOP_O_O]             = {morphCB:unOpOO},
        [M16C_MT_BRK]                  = {morphCB:breakOp},
        [M16C_MT_ENTER]                = {morphCB:enterOp},
        [M16C_MT_EXIT]                 = {morphCB:exitOp},
        [M16C_MT_EXTS_R]               = {morphCB:extsOpR},
        [M16C_MT_EXTS_C]               = {},
        [M16C_MT_EXTS_O]               = {morphCB:extsOpO},
        [M16C_MT_INT]                  = {morphCB:intOp},
        [M16C_MT_INTO]                 = {morphCB:intoOp},
        [M16C_MT_JMP]                  = {morphCB:jmpOp},
        [M16C_MT_JMPU]                 = {morphCB:jmpOpU},
        [M16C_MT_JSR]                  = {morphCB:jsrOp},
        [M16C_MT_JSRI]                 = {morphCB:jsriOp},
        [M16C_MT_JSRS]                 = {morphCB:jsrsOp},
        [M16C_MT_LDCTX]                = {morphCB:ldctxOp},
        [M16C_MT_LDIPL]                = {morphCB:ldiplOp},
        [M16C_MT_POP_R]                = {morphCB:popOpR},
        [M16C_MT_POP_O]                = {morphCB:popOpO},
        [M16C_MT_POP_M]                = {morphCB:popOpM},
        [M16C_MT_PUSH_R]               = {morphCB:pushOpR},
        [M16C_MT_PUSH_C]               = {morphCB:pushOpC},
        [M16C_MT_PUSH_O]               = {morphCB:pushOpO},
        [M16C_MT_PUSH_M]               = {morphCB:pushOpM},
        [M16C_MT_REIT]                 = {morphCB:reitOp},
        [M16C_MT_RMPA]                 = {morphCB:rmpaOp},
        [M16C_MT_ROT_R_R]              = {morphCB:rotOpRR},
        [M16C_MT_ROT_R_C]              = {morphCB:rotOpRC},
        [M16C_MT_ROT_R_O]              = {},
        [M16C_MT_ROT_O_R]              = {morphCB:rotOpOR},
        [M16C_MT_ROT_O_C]              = {morphCB:rotOpOC},
        [M16C_MT_ROT_O_O]              = {},
        [M16C_MT_RTS]                  = {morphCB:rtsOp},
        [M16C_MT_SBJNZ_R_R]            = {},
        [M16C_MT_SBJNZ_R_C]            = {morphCB:sbjnzOpRC},
        [M16C_MT_SBJNZ_R_O]            = {},
        [M16C_MT_SBJNZ_O_R]            = {},
        [M16C_MT_SBJNZ_O_C]            = {morphCB:sbjnzOpOC},
        [M16C_MT_SBJNZ_O_O]            = {},
        [M16C_MT_SMOV]                 = {morphCB:smovOp},
        [M16C_MT_SSTR]                 = {morphCB:sstrOp},
        [M16C_MT_STCTX]                = {morphCB:stctxOp},
        [M16C_MT_STZX_R]               = {morphCB:stzxOpR},
        [M16C_MT_STZX_O]               = {morphCB:stzxOpO},
        [M16C_MT_MOVE_R_R]             = {morphCB:moveOpRR},
        [M16C_MT_MOVE_R_C]             = {morphCB:moveOpRC},
        [M16C_MT_MOVE_R_O]             = {morphCB:moveOpRO},
        [M16C_MT_MOVE_O_R]             = {morphCB:moveOpOR},
        [M16C_MT_MOVE_O_C]             = {morphCB:moveOpOC},
        [M16C_MT_MOVE_O_O]             = {morphCB:moveOpOO},
        [M16C_MT_MOVEC_R_R]            = {morphCB:checkCond, condMorphCB:moveOpRR},
        [M16C_MT_MOVEC_R_C]            = {morphCB:checkCond, condMorphCB:moveOpRC},
        [M16C_MT_MOVEC_R_O]            = {morphCB:checkCond, condMorphCB:moveOpRO},
        [M16C_MT_MOVEC_O_R]            = {morphCB:checkCond, condMorphCB:moveOpOR},
        [M16C_MT_MOVEC_O_C]            = {morphCB:checkCond, condMorphCB:moveOpOC},
        [M16C_MT_MOVEC_O_O]            = {morphCB:checkCond, condMorphCB:moveOpOO},
        [M16C_MT_MOVEF]                = {morphCB:movefOp},
        [M16C_MT_MOVEA]                = {morphCB:moveaOp},
        [M16C_MT_UND]                  = {morphCB:undOp},
        [M16C_MT_WAIT]                 = {morphCB:waitOp},
        [M16C_MT_XCHG_R_R]             = {morphCB:xchgOpRR},
        [M16C_MT_XCHG_R_C]             = {},
        [M16C_MT_XCHG_R_O]             = {},
        [M16C_MT_XCHG_O_R]             = {morphCB:xchgOpOR},
        [M16C_MT_XCHG_O_C]             = {},
        [M16C_MT_XCHG_O_O]             = {},
        [M16C_MT_NOP]                  = {morphCB:nopOp},
};



////////////////////////////////////////////////////////////////////////////////
// MORPHER MAIN ROUTINES
////////////////////////////////////////////////////////////////////////////////

//
// Default morpher callback for implemented instructions
//
static M16C_MORPH_FN(emitImplemented) {
    // generate instruction code
    state->attrs->morphCB(state);
}

//
// Should morphing be disabled? (disassembly test mode only)
//
static Bool disableMorph(m16cP m16c) {
    if (!M16C_CLI_DISASSEMBLE(m16c)) {
        return False;
    } else {
        return True;
    }
}
//
// Create code for the M16C instruction at the simulated address referenced
// by 'thisPC'.
//
VMI_MORPH_FN(m16cMorphInstruction) {
    m16cP          m16c = (m16cP)processor;
    m16cMorphState state;

    // get instruction and instruction type
    m16cDecode(m16c, thisPC, &state.info);

    if (disableMorph(m16c)) {
        //
        // Morphing is disabled, for disassembly
        //
    } else {
        // get morpher attributes for the decoded instruction and initialize other
        // state fields
        state.attrs    = &dispatchTable[state.info.morphindex];
        state.m16c     = m16c;

        m16cVariant instrVariant = state.attrs->variant;

        if (!state.attrs->morphCB) {
            // here if no morph callback specified
            morphDefault(&state);
        } else if (instrVariant == (instrVariant & m16c->variant)) {
            // translate the instruction
            emitImplemented(&state);
        } else {
            // here if no morph callback specified
            morphDefault(&state);
        }
    }
}

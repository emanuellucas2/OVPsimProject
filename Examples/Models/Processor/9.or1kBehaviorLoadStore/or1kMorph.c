/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


// VMI header files
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"

// model header files
#include "or1kDecode.h"
#include "or1kFunctions.h"
#include "or1kStructure.h"

//
// Define pointer to or1kMorphAttr type
//
typedef const struct or1kMorphAttrS *or1kMorphAttrCP;

//
// Define pointer to or1kMorphState type
//
typedef struct or1kMorphStateS *or1kMorphStateP;

//
// Morpher callback type
//
#define OR1K_MORPH_FN(_NAME) void _NAME(or1kMorphStateP state)
typedef OR1K_MORPH_FN((*or1kMorphFn));

//
// This structure provides supplementary information required to translate code
// for an instruction
//
typedef struct or1kMorphAttrS {
    or1kMorphFn morphCB;    // function to translate one instruction
    vmiBinop    binop;      // if a simple binary operation
    vmiFlagsCP  flags;      // flags used by the instruction
    Bool        jumpIfTrue; // whether to branch if condition flag is True
    Bool        link;       // whether to set link register
} or1kMorphAttr;

//
// This structure holds state for a single instruction as it is translated
//
typedef struct or1kMorphStateS {
    or1kInstructionInfo info;        // instruction description (from decoder)
    or1kMorphAttrCP     attrs;       // instruction attributes
    or1kP               or1k;        // current processor
    Bool                inDelaySlot; // true if instruction is in delay slot
} or1kMorphState;

//
// Update carry & overflow flags
//
static const vmiFlags flagsCO = {
    OR1K_CARRY_CONST,           // offset to carry in flag
    {
        OR1K_CARRY_CONST,       // offset to carry out flag
        VMI_NOFLAG_CONST,       // parity flag not used
        VMI_NOFLAG_CONST,       // zero flag not used
        VMI_NOFLAG_CONST,       // sign flag not used
        OR1K_OVERFLOW_CONST     // offset to overflow flag
    }
};

//
// Convert from register index to equivalent VMI register. Note that register
// r0 is always zero, so return VMI_NOREG for that index.
//
static vmiReg getGPR(Uns32 r) {
    return r ? OR1K_REG(r) : VMI_NOREG;
}

//
// Emit code for a movhi instruction
//
static OR1K_MORPH_FN(morphMOVHI) {

    vmiReg rd = getGPR(state->info.r1);
    Uns32  c  = state->info.c;

    vmimtMoveRC(OR1K_BITS, rd, c<<16);
}

//
// Emit code for a binary/literal instruction
//
static OR1K_MORPH_FN(morphBinopRRC) {

    vmiBinop   op    = state->attrs->binop;
    vmiReg     rd    = getGPR(state->info.r1);
    vmiReg     ra    = getGPR(state->info.r2);
    Uns32      c     = state->info.c;
    vmiFlagsCP flags = state->attrs->flags;

    vmimtBinopRRC(OR1K_BITS, op, rd, ra, c, flags);
}

//
// Emit code for a binary/register instruction
//
static OR1K_MORPH_FN(morphBinopRRR) {

    vmiBinop   op    = state->attrs->binop;
    vmiReg     rd    = getGPR(state->info.r1);
    vmiReg     ra    = getGPR(state->info.r2);
    vmiReg     rb    = getGPR(state->info.r3);
    vmiFlagsCP flags = state->attrs->flags;

    vmimtBinopRRR(OR1K_BITS, op, rd, ra, rb, flags);
}

//
// Emit code for a branch instruction.
//
static OR1K_MORPH_FN(morphBranch) {

    Uns32 toAddress   = state->info.c;
    Bool  jumpIfTrue  = state->attrs->jumpIfTrue;
    Bool  inDelaySlot = state->inDelaySlot;

    if(inDelaySlot) {
        // jump in the delay slot does nothing
    } else {
        vmimtCondJumpDelaySlot(
            1,                  // slotOps
            OR1K_BRANCH,        // flagReg
            jumpIfTrue,         // jumpIfTrue
            0,                  // linkPC
            toAddress,          // toAddress
            VMI_NOREG,          // linkReg
            vmi_JH_NONE,        // hint
            0                   // slotCB
        );
    }
}

//
// Emit code for a jump instruction
//
static OR1K_MORPH_FN(morphJump) {

    Uns32       toAddress   = state->info.c;
    Uns32       nextAddress = state->info.thisPC + 8;
    Bool        inDelaySlot = state->inDelaySlot;
    Bool        link        = state->attrs->link;
    vmiReg      linkReg     = link ? OR1K_LINKREG : VMI_NOREG;
    vmiJumpHint hint;

    // select an appropriate jump hint
    if(link) {
        hint = vmi_JH_CALL;
    } else {
        hint = vmi_JH_NONE;
    }

    if(inDelaySlot) {
        // jump in the delay slot does nothing
    } else {
        vmimtUncondJumpDelaySlot(
            1,                  // slotOps
            nextAddress,        // linkPC
            toAddress,          // toAddress
            linkReg,            // linkReg
            hint,               // hint
            0                   // slotCB
        );
    }
}

//
// Emit code for an indirect jump instruction
//
static OR1K_MORPH_FN(morphJumpReg) {

    Uns32       r1          = state->info.r1;
    vmiReg      toReg       = getGPR(r1);
    Uns32       nextAddress = state->info.thisPC + 8;
    Bool        inDelaySlot = state->inDelaySlot;
    Bool        link        = state->attrs->link;
    vmiReg      linkReg     = link ? OR1K_LINKREG : VMI_NOREG;
    vmiJumpHint hint;

    // select an appropriate jump hint
    if(link) {
        hint = vmi_JH_CALL;
    } else if(r1==OR1K_LINK) {
        hint = vmi_JH_RETURN;
    } else {
        hint = vmi_JH_NONE;
    }

    if(inDelaySlot) {
        // jump in the delay slot does nothing
    } else {
        vmimtUncondJumpRegDelaySlot(
            1,                  // slotOps
            nextAddress,        // linkPC
            toReg,              // toReg
            linkReg,            // linkReg
            hint,               // hint
            0                   // slotCB
        );
    }
}

//
// Return endianness of this model
//
static memEndian getEndian(void) {
    return MEM_ENDIAN_BIG;
}

//
// Emit code to load from an address
//
static OR1K_MORPH_FN(morphLoad) {

    vmiReg    rd         = getGPR(state->info.r1);
    vmiReg    ra         = getGPR(state->info.r2);
    Int32     offset     = state->info.c;
    Uns32     bytes      = state->info.bytes;
    Bool      signExtend = (state->info.extend==OR1K_EXTEND_S);
    memEndian endian     = getEndian();

    vmimtLoadRRO(
        OR1K_BITS,              // destBits
        bytes*8,                // memBits
        offset,                 // offset
        rd,                     // rd
        ra,                     // ra
        endian,                 // endian
        signExtend,             // signExtend
        MEM_CONSTRAINT_ALIGNED  // constraint
    );
}

//
// Emit code to store to an address
//
static OR1K_MORPH_FN(morphStore) {

    vmiReg    ra     = getGPR(state->info.r1);
    vmiReg    rb     = getGPR(state->info.r2);
    Int32     offset = state->info.c;
    Uns32     bytes  = state->info.bytes;
    memEndian endian = getEndian();

    vmimtStoreRRO(
        bytes*8,                // bits
        offset,                 // offset
        ra,                     // ra
        rb,                     // rb
        endian,                 // endian
        MEM_CONSTRAINT_ALIGNED  // constraint
    );
}

//
// Return vmiCondition for or1kCondition
//
static vmiCondition mapCondition(or1kCondition cond) {

    static const vmiCondition map[] = {
        [OR1K_COND_EQ]  = vmi_COND_Z,   // 0x0: a == b
        [OR1K_COND_NE]  = vmi_COND_NZ,  // 0x1: a != b
        [OR1K_COND_GTU] = vmi_COND_NBE, // 0x2: a >  b (unsigned)
        [OR1K_COND_GEU] = vmi_COND_NB,  // 0x3: a >= b (unsigned)
        [OR1K_COND_LTU] = vmi_COND_B,   // 0x4: a <  b (unsigned)
        [OR1K_COND_LEU] = vmi_COND_BE,  // 0x5: a <= b (unsigned)
        [OR1K_COND_GTS] = vmi_COND_NLE, // 0xa: a >  b (signed)
        [OR1K_COND_GES] = vmi_COND_NL,  // 0xb: a >= b (signed)
        [OR1K_COND_LTS] = vmi_COND_L,   // 0xc: a <  b (signed)
        [OR1K_COND_LES] = vmi_COND_LE,  // 0xd: a <= b (signed)
        [OR1K_COND_BAD] = -1,           // invalid condition
    };

    return map[cond];
}

//
// Emit code for a literal comparison instruction
//
static OR1K_MORPH_FN(morphCompareRC) {

    vmiReg       ra   = getGPR(state->info.r1);
    Uns32        c    = state->info.c;
    vmiCondition cond = mapCondition(state->info.cond);

    vmimtCompareRC(OR1K_BITS, cond, ra, c, OR1K_BRANCH);
}

//
// Emit code for a register comparison instruction
//
static OR1K_MORPH_FN(morphCompareRR) {

    vmiReg       ra   = getGPR(state->info.r1);
    vmiReg       rb   = getGPR(state->info.r2);
    vmiCondition cond = mapCondition(state->info.cond);

    vmimtCompareRR(OR1K_BITS, cond, ra, rb, OR1K_BRANCH);
}

//
// Emit code for a OR1K nop instruction
//
static OR1K_MORPH_FN(morphNOP) {

    // no action for a NOP
}


////////////////////////////////////////////////////////////////////////////////
// MORPHER DISPATCH TABLE
////////////////////////////////////////////////////////////////////////////////

//
// OR1K morpher dispatch table
//
const or1kMorphAttr or1kMorphTable[OR1K_IT_LAST+1] = {

    // handle movhi instruction
    [OR1K_IT_MOVHI] = {morphCB:morphMOVHI},

    // handle arithmetic instructions (second argument constant)
    [OR1K_IT_ADDI]  = {morphCB:morphBinopRRC, binop:vmi_ADD,  flags:&flagsCO},
    [OR1K_IT_ADDIC] = {morphCB:morphBinopRRC, binop:vmi_ADC,  flags:&flagsCO},
    [OR1K_IT_ANDI]  = {morphCB:morphBinopRRC, binop:vmi_AND,  flags:0       },
    [OR1K_IT_ORI]   = {morphCB:morphBinopRRC, binop:vmi_OR,   flags:0       },
    [OR1K_IT_XORI]  = {morphCB:morphBinopRRC, binop:vmi_XOR,  flags:0       },
    [OR1K_IT_MULI]  = {morphCB:morphBinopRRC, binop:vmi_IMUL, flags:&flagsCO},

    // handle arithmetic instructions (second argument register)
    [OR1K_IT_ADD]   = {morphCB:morphBinopRRR, binop:vmi_ADD,  flags:&flagsCO},
    [OR1K_IT_ADDC]  = {morphCB:morphBinopRRR, binop:vmi_ADC,  flags:&flagsCO},
    [OR1K_IT_SUB]   = {morphCB:morphBinopRRR, binop:vmi_SUB,  flags:&flagsCO},
    [OR1K_IT_AND]   = {morphCB:morphBinopRRR, binop:vmi_AND,  flags:0       },
    [OR1K_IT_OR]    = {morphCB:morphBinopRRR, binop:vmi_OR,   flags:0       },
    [OR1K_IT_XOR]   = {morphCB:morphBinopRRR, binop:vmi_XOR,  flags:0       },
    [OR1K_IT_MUL]   = {morphCB:morphBinopRRR, binop:vmi_IMUL, flags:&flagsCO},
    [OR1K_IT_DIV]   = {morphCB:morphBinopRRR, binop:vmi_IDIV, flags:0       },
    [OR1K_IT_DIVU]  = {morphCB:morphBinopRRR, binop:vmi_DIV,  flags:0       },

    // handle shift/rotate instructions (second argument constant)
    [OR1K_IT_SLLI]  = {morphCB:morphBinopRRC, binop:vmi_SHL},
    [OR1K_IT_SRLI]  = {morphCB:morphBinopRRC, binop:vmi_SHR},
    [OR1K_IT_SRAI]  = {morphCB:morphBinopRRC, binop:vmi_SAR},
    [OR1K_IT_RORI]  = {morphCB:morphBinopRRC, binop:vmi_ROR},

    // handle shift/rotate instructions (second argument register)
    [OR1K_IT_SLL]   = {morphCB:morphBinopRRR, binop:vmi_SHL},
    [OR1K_IT_SRL]   = {morphCB:morphBinopRRR, binop:vmi_SHR},
    [OR1K_IT_SRA]   = {morphCB:morphBinopRRR, binop:vmi_SAR},
    [OR1K_IT_ROR]   = {morphCB:morphBinopRRR, binop:vmi_ROR},

    // handle branch instructions
    [OR1K_IT_BF]    = {morphCB:morphBranch,  jumpIfTrue:True },
    [OR1K_IT_BNF]   = {morphCB:morphBranch,  jumpIfTrue:False},
    [OR1K_IT_J]     = {morphCB:morphJump,    link:      False},
    [OR1K_IT_JR]    = {morphCB:morphJumpReg, link:      False},
    [OR1K_IT_JAL]   = {morphCB:morphJump,    link:      True },
    [OR1K_IT_JALR]  = {morphCB:morphJumpReg, link:      True },

    // handle load instructions
    [OR1K_IT_LWZ]   = {morphCB:morphLoad},
    [OR1K_IT_LWS]   = {morphCB:morphLoad},
    [OR1K_IT_LBZ]   = {morphCB:morphLoad},
    [OR1K_IT_LBS]   = {morphCB:morphLoad},
    [OR1K_IT_LHZ]   = {morphCB:morphLoad},
    [OR1K_IT_LHS]   = {morphCB:morphLoad},

    // handle store instructions
    [OR1K_IT_SW]    = {morphCB:morphStore},
    [OR1K_IT_SB]    = {morphCB:morphStore},
    [OR1K_IT_SH]    = {morphCB:morphStore},

    // handle comparison instructions
    [OR1K_IT_SF]    = {morphCB:morphCompareRR},
    [OR1K_IT_SFI]   = {morphCB:morphCompareRC},

    // handle nop instruction
    [OR1K_IT_NOP]   = {morphCB:morphNOP}
};

//
// Called for an unimplemented instruction
//
static void unimplemented(
    vmiProcessorP processor,
    Uns32         thisPC,
    Uns32         instruction
) {
    // report that unimplemented instruction was encountered
    vmiPrintf(
        "CPU '%s' 0x%08x:0x%08x *** undecoded instruction: exiting ***\n",
        vmirtProcessorName(processor),
        thisPC,
        instruction
    );

    // exit the CPU
    vmirtExit(processor);
}

//
// Default morpher callback
//
static OR1K_MORPH_FN(emitUnimplemented) {

    vmimtArgProcessor();
    vmimtArgUns32((Uns32)state->info.thisPC);
    vmimtArgUns32(state->info.instruction);
    vmimtCall((vmiCallFn)unimplemented);
}

//
// Create code for the OR1K instruction at the simulated address referenced
// by 'thisPC'.
//
VMI_MORPH_FN(or1kMorphInstruction) {

    or1kP          or1k  = (or1kP)processor;
    or1kMorphState state = {{0}};

    // decode instruction
    or1kDecode(or1k, thisPC, &state.info);

    // get morpher attributes for the decoded instruction and initialize other
    // state fields
    state.attrs       = &or1kMorphTable[state.info.type];
    state.or1k        = or1k;
    state.inDelaySlot = inDelaySlot;

    if(state.attrs->morphCB) {
        // translate the instruction
        state.attrs->morphCB(&state);
    } else {
        // here if no translation callback specified
        emitUnimplemented(&state);
    }
}


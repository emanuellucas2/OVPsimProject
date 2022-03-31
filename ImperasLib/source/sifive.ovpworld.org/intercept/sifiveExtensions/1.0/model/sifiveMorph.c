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
#include "sifiveCSR.h"
#include "sifiveDecode.h"
#include "sifiveDecodeTypes.h"
#include "sifiveExceptions.h"
#include "sifiveFunctions.h"
#include "sifiveMessage.h"
#include "sifiveMorph.h"
#include "sifiveStructure.h"
#include "sifiveTypeRefs.h"
#include "sifiveUtils.h"
#include "sifiveVariant.h"

// base model header files
#include "riscvRegisters.h"
#include "riscvStructure.h"
#include "riscvTypes.h"


////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

//
// Generic JIT code emission callback
//
#define SIFIVE_MORPH_FN(_NAME) void _NAME(sifiveMorphStateP state)
typedef SIFIVE_MORPH_FN((*sifiveMorphFn));

//
// Attributes controlling JIT code translation
//
typedef struct sifiveMorphAttrS {
    sifiveMorphFn         morph;        // function to translate one instruction
    octiaInstructionClass iClass;       // supplemental instruction class
    sifiveVariant         variant;      // required variant
} sifiveMorphAttr;

//
// Context for JIT code translation (decoded instruction information and
// translation attributes)
//
typedef struct sifiveMorphStateS {
    sifiveInstrInfo      info;          // decoded instruction information
    sifiveMorphAttrCP    attrs;         // instruction attributes
    riscvP               riscv;         // current processor
    vmiosObjectP         object;        // current extension object
} sifiveMorphState;


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
// Disable instruction translation (test mode)
//
inline static Bool disableMorph(sifiveMorphStateP state) {
    return RISCV_DISASSEMBLE(state->riscv);
}


////////////////////////////////////////////////////////////////////////////////
// REGISTER ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Return riscvRegDesc for the indexed register
//
inline static riscvRegDesc getRVReg(sifiveMorphStateP state, Uns32 argNum) {
    return state->info.r[argNum];
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
    vmimtCallAttrs((vmiCallFn)sifiveIllegalInstruction, VMCA_EXCEPTION);
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
// Validate that the instruction is supported and enabled and take an Illegal
// Instruction exception if not
//
static Bool instructionEnabled(
    vmiosObjectP      object,
    riscvP            riscv,
    riscvArchitecture riscvVariants,
    sifiveVariant     siFiveVariants
) {
    sifiveVariant availableVariants = object->variant;

    // validate base model constraints
    if(!riscv->cb.instructionEnabled(riscv, riscvVariants)) {
        return False;
    }

    // validate SiFive feature set
    if((availableVariants & siFiveVariants) != siFiveVariants) {
        ILLEGAL_INSTRUCTION_MESSAGE(riscv, "SVUI", "Unimplemented on this variant");
        return False;
    }

    return True;
}

//
// Return VMI register for the given abstract register
//
inline static vmiReg getVMIReg(riscvP riscv, riscvRegDesc r) {
    return riscv->cb.getVMIReg(riscv, r);
}


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Morph-time check for M-mode
//
static Bool requireModeMMt(sifiveMorphStateP state) {
    riscvP riscv = state->riscv;
    return riscv->cb.requireModeMt(riscv, RISCV_MODE_M);
}

//
// Implement Cache Flush instruction
//
static SIFIVE_MORPH_FN(emitCFlush) {

    riscvP       riscv = state->riscv;
    riscvRegDesc rs1   = getRVReg(state, 0);
    vmiReg       rA    = getVMIReg(riscv, rs1);

    // Note that if the PMP scheme write-protects only part of a cache line,
    // then using a value for rs1 in the write-protected region will cause an
    // exception, whereas using a value for rs1 in the write-permitted region
    // will write back the entire cache line.
    if(!requireModeMMt(state)) {
        // require M-mode
    } else if(!VMI_ISNOREG(rA)) {
        vmimtTryStoreRC(8, 0, rA, MEM_CONSTRAINT_NONE);
    }
}

//
// Cease execution of the given hart until reset
//
static void ceaseHart(riscvP riscv) {
    riscv->cb.halt(riscv, RVD_RESET);
}

//
// Implement Cease instruction
//
static SIFIVE_MORPH_FN(emitCease) {

    if(requireModeMMt(state)) {
        vmimtArgProcessor();
        vmimtCall((vmiCallFn)ceaseHart);
    }
}


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION TABLE
////////////////////////////////////////////////////////////////////////////////

//
// Dispatch table for instruction translation
//
const static sifiveMorphAttr dispatchTable[] = {

    // SiFive custom instructions
    [S5_IT_CFLUSH]  = {morph:emitCFlush, variant:S5V_CFLUSH, iClass:OCL_IC_DCACHE},
    [S5_IT_CEASE]   = {morph:emitCease,  variant:S5V_CEASE,  iClass:OCL_IC_NONE  },

    // KEEP LAST
    [S5_IT_LAST]    = {0}
};

//
// Instruction Morpher
//
VMIOS_MORPH_FN(sifiveMorph) {

    riscvP          riscv = (riscvP)processor;
    sifiveMorphState state;

    // get instruction and instruction type
    sifiveDecode(riscv, object, thisPC, &state.info);

    // action is inly required if the instruction is implemented by this
    // extension
    if(state.info.type != S5_IT_LAST) {

        // indicate instruction is implemented here
        *opaque = True;

        sifiveMorphAttrCP attrs = &dispatchTable[state.info.type];
        state.attrs  = attrs;
        state.riscv  = riscv;
        state.object = object;

        if(disableMorph(&state)) {

            // no action if in disassembly mode

        } else if(!instructionEnabled(object, riscv, state.info.arch, attrs->variant)) {

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
    }

    // no callback function is required
    return 0;
}

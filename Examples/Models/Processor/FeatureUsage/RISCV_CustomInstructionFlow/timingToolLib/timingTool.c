/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., All Rights Reserved.
 *
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS
 * OF IMPERAS SOFTWARE LTD. USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED
 * EXCEPT AS MAY BE PROVIDED FOR IN A WRITTEN AGREEMENT WITH
 * IMPERAS SOFTWARE LTD.
 *
 */

// standard includes
#include <string.h>
#include <stdio.h>

// Imperas common includes
#include "hostapi/impAlloc.h"

// Imperas common library includes
#include "ocl/oclia.h"

// Imperas Support Library includes
#include "isl/cpuEstimator.h"

// VMI area includes
#include "vmi/vmiInstructionAttrs.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiDoc.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"


////////////////////////////////////////////////////////////////////////////////
// GENERAL DEFINITIONS
////////////////////////////////////////////////////////////////////////////////

#define CPU_PREFIX "RCE"


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION CLASSES
////////////////////////////////////////////////////////////////////////////////

//
// Instruction classes with different cycle estimation algorithms
//
typedef enum instrClassE {
    IC_default,
    IC_load,
    IC_loadhu,
    IC_branch,
    IC_trap,
    IC_mdu_mul,
    IC_mdu_div,
    IC_mdu_divu,
    IC_csr_r,
    IC_csr_w,
    IC_csr_rw,
} instrClass;

//
// Instruction class names
//
static const char *instrClassNames[] = {
    [IC_default]   = "IC_default",
    [IC_load]      = "IC_load",
    [IC_loadhu]    = "IC_loadhu",
    [IC_branch]    = "IC_branch",
    [IC_trap]      = "IC_trap",
    [IC_mdu_mul]   = "IC_mdu_mul",
    [IC_mdu_div]   = "IC_mdu_div",
    [IC_mdu_divu]  = "IC_mdu_divu",
    [IC_csr_r]     = "IC_csr_r",
    [IC_csr_w]     = "IC_csr_w",
    [IC_csr_rw]    = "IC_csr_rw",
};

//
// Mapping from instruction mnemonic to class
//
static ceInstTableEntry instructionClasses[] = {

    { IC_load,      "lw",     {2}},
    { IC_loadhu,    "lb",     {3}},
    { IC_loadhu,    "lh",     {3}},
    { IC_loadhu,    "lbu",    {3}},
    { IC_loadhu,    "lhu",    {3}},

    { IC_branch,    "jal",    {1}},
    { IC_branch,    "jalr",   {1}},
    { IC_branch,    "beq",    {1}},
    { IC_branch,    "bne",    {1}},
    { IC_branch,    "blt",    {1}},
    { IC_branch,    "bge",    {1}},
    { IC_branch,    "bltu",   {1}},
    { IC_branch,    "bgeu",   {1}},

    { IC_mdu_mul,   "mul",    {3}},
    { IC_mdu_mul,   "mulh",   {3}},
    { IC_mdu_mul,   "mulhu",  {3}},
    { IC_mdu_mul,   "mulhsu", {3}},

    { IC_mdu_div,   "div",    {16}},
    { IC_mdu_divu,  "divu",   {16}},
    { IC_mdu_div,   "rem",    {16}},
    { IC_mdu_divu,  "remu",   {16}},

    { IC_csr_r,     "csrr",   {3}},
    { IC_csr_rw,    "csrrc",  {8}},
    { IC_csr_rw,    "csrrs",  {8}},
    { IC_csr_rw,    "csrrw",  {8}},
    { IC_csr_w,     "csrc",   {5}},
    { IC_csr_w,     "csrs",   {5}},
    { IC_csr_w,     "csrw",   {5}},

    { IC_csr_rw,    "csrrci", {8}},
    { IC_csr_rw,    "csrrsi", {8}},
    { IC_csr_rw,    "csrrwi", {8}},
    { IC_csr_w,     "csrci",  {5}},
    { IC_csr_w,     "csrsi",  {5}},
    { IC_csr_w,     "csrwi",  {5}},

    // KEEP LAST: terminator

    { 0 },
};


////////////////////////////////////////////////////////////////////////////////
// ANALYSIS ALGORITHM
////////////////////////////////////////////////////////////////////////////////

//
// Assume additional 3 cycles pipeline penalty on estimator miss
//
#define PIPELINE_PENALTY 3

//
// Return string corresponding to vmiBranchReason
//
static const char *branchReasonString(vmiBranchReason reason) {

    static const char *map[] = {
        [VMIBR_UNCOND]         = "unconditional branch taken",
        [VMIBR_COND_TAKEN]     = "conditional branch taken",
        [VMIBR_COND_NOT_TAKEN] = "conditional branch not taken",
        [VMIBR_PC_SET]         = "PC set by non instruction route",
    };

    return map[reason];
}

//
// Branch notifier callback
// NOTE: this core has no branch prediction; all branches and jumps predict as
// NOT taken
//
static VMI_BRANCH_REASON_FN(riscvBranchNotifier) {

    vmiosObjectP object = userData;
    Uns32        cycles = 0;

    switch(reason) {

        case VMIBR_UNCOND:
            cycles = PIPELINE_PENALTY;
            break;

        case VMIBR_COND_TAKEN:
            cycles = PIPELINE_PENALTY;
            break;

        case VMIBR_COND_NOT_TAKEN:
            break;

        case VMIBR_PC_SET:
            cycles = PIPELINE_PENALTY;
            break;

        default: {
            VMI_ABORT("Invalid vmiBranchReason %u", reason);
            break;
        }
    }

    ceAddCycles(object, cycles);

    if(ceGetDiagnosticLevel(object)>1) {
        vmiMessage(
            "I", CPU_PREFIX "_BAV",
            "%s: PC: 0x"FMT_A08x": %s: New PC: 0x"FMT_Ax": %u penalty cycles added",
            vmirtProcessorName(processor),
            prevPC,
            branchReasonString(reason),
            thisPC,
            cycles
        );
    }
}

//
// Morph time cycle accumulation
//
static VMIOS_MORPH_FN(riscvMorph) {

    instrClass thisClass = ceGetThisInstructionClass(object);
    ceInstData data      = ceGetThisInstructionData(object);
    Uns32      cycles    = data.u32 ? data.u32 : 1;

    // add constant cycle delay
    ceEmitAddCycleCountC(
        object,
        thisPC,
        instrClassNames[thisClass],
        cycles
    );

    *opaque = False;
    return NULL;
}


////////////////////////////////////////////////////////////////////////////////
// ENABLE AND DISABLE
////////////////////////////////////////////////////////////////////////////////

//
// Called when estimator is enabled
//
static CE_OPERATION_FN(riscvEnable) {
    vmirtRegisterBranchNotifier(processor, riscvBranchNotifier, object);
}

//
// Called when estimator is disabled
//
static CE_OPERATION_FN(riscvDisable) {
    vmirtUnregisterBranchNotifier(processor, riscvBranchNotifier, object);
}


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static CE_CONSTRUCT_FN(riscvConstructor) {

    // fill table of instruction classes at root level
    if(!parent) {

        ceInstTableEntryP this;

        for(this=instructionClasses; this->mnemonic; this++) {
            ceInstTableEntryAdd(object, this);
        }
    }
}

//
// Destructor
//
static CE_CONSTRUCT_FN(riscvDestructor) {

    // no action
}


////////////////////////////////////////////////////////////////////////////////
// DOCUMENTATION
////////////////////////////////////////////////////////////////////////////////

//
// Documentation
//
static CE_DOC_FN(riscvDoc) {
    vmidocAddText(
        reference,
        "RISCV v2.0 Handbook"
    );
}


////////////////////////////////////////////////////////////////////////////////
// VARIANT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

static ceProcInfo infoRISCV = {
    .constructorCB = riscvConstructor,
    .destructorCB  = riscvDestructor,
    .docCB         = riscvDoc,
    .enableCB      = riscvEnable,
    .morphCB       = riscvMorph,
    .disableCB     = riscvDisable,
};

//
// Model-specific callback for supported processor variants
//
CE_GET_PROC_INFO_FN(ceGetProcInfo) {

    ceProcInfoP result = 0;

    if(strcmp(type, "riscv")) {
        // not a RISCV model variant
    } else if(!strncmp(variant, "RVB32I", 6) ||
              !strncmp(variant, "RV32I", 5)) {
        result = &infoRISCV;
    }

    return result;
}


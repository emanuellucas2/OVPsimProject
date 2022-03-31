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
#include "vmi/vmiCxt.h"
#include "vmi/vmiRt.h"

// model header files
#include "or1kExceptions.h"
#include "or1kFunctions.h"
#include "or1kStructure.h"
#include "or1kUtils.h"


////////////////////////////////////////////////////////////////////////////////
// REGISTER GROUPS
////////////////////////////////////////////////////////////////////////////////

//
// This describes the register groups in the OR1K
//
typedef enum or1kRegGroupIdE {
    OR1K_RG_GPR,            // GPR group
    OR1K_RG_SYSTEM,         // System register group
    OR1K_RG_INTEGRATION,    // System register group
    OR1K_RG_LAST            // KEEP LAST: for sizing
} or1kRegGroupId;

//
// This provides information about each group
//
static const vmiRegGroup groups[OR1K_RG_LAST+1] = {
    [OR1K_RG_GPR]         = {name: "GPR"                },
    [OR1K_RG_SYSTEM]      = {name: "System"             },
    [OR1K_RG_INTEGRATION] = {name: "Integration_Support"}
};

//
// Macro to specify a the group for a register
//
#define OR1K_GROUP(_G) &groups[OR1K_RG_##_G]

//
// Some registers are hidden in gdb, but we allow access to them
//
#define OR1K_GDB_HIDDEN_INDEX 100
#define IS_GDB_HIDDEN_REG(_I) ((_I)>=OR1K_GDB_HIDDEN_INDEX)


////////////////////////////////////////////////////////////////////////////////
// REGISTER ACCESS FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Macro to specify basic register attributes
//
#define OR1K_REG_INFO(_NAME, _INDEX, _USAGE, _BITS, _DETAIL, _DESC) { \
    name        : _NAME,    \
    description : _DESC,    \
    gdbIndex    : _INDEX,   \
    usage       : _USAGE,   \
    bits        : _BITS,    \
    _DETAIL                 \
}

//
// Macro to specify a register accessible raw for read/write
//
#define OR1K_RAW_REG_RW(_R, _G) \
    access   : vmi_RA_RW,           \
    raw      : OR1K_CPU_REG(_R),    \
    group    : _G

//
// Macro to specify a register accessible raw for read only
//
#define OR1K_RAW_REG_R(_R, _G) \
    access   : vmi_RA_R,            \
    raw      : OR1K_CPU_REG(_R),    \
    group    : _G

//
// Macro to specify a register accessible with callbacks for read/write
//
#define OR1K_CB_REG_RW(_R, _G) \
    access   : vmi_RA_RW,           \
    readCB   : read##_R,            \
    writeCB  : write##_R,           \
    group    : _G

//
// Macro to specify a register accessible raw for read and using callback
// for write
//
#define OR1K_CB_REG_W(_R, _G) \
    access   : vmi_RA_RW,           \
    raw      : OR1K_CPU_REG(_R),    \
    writeCB  : write##_R,           \
    group    : _G

//
// Macro to execute body code in artifact access state
//
#define OR1K_ARTIFACT_ACCESS(_OR1K, _B) \
    (_OR1K)->artifactAccess = True;     \
    _B;                                 \
    (_OR1K)->artifactAccess = False

//
// Read callback for PC
//
static VMI_REG_READ_FN(readPC) {
    or1kP or1k = (or1kP)processor;
    OR1K_ARTIFACT_ACCESS(or1k, *(Uns32*)buffer = (Uns32)vmirtGetPC(processor));
    return True;
}

//
// Write callback for PC
//
static VMI_REG_WRITE_FN(writePC) {
    or1kP or1k = (or1kP)processor;
    OR1K_ARTIFACT_ACCESS(or1k, vmirtSetPC(processor, *(Uns32*)buffer));
    return True;
}

//
// Read callback for SR
//
static VMI_REG_READ_FN(readSR) {
    or1kP or1k = (or1kP)processor;
    OR1K_ARTIFACT_ACCESS(or1k, *(Uns32*)buffer = or1kGetSR(or1k));
    return True;
}

//
// Write callback for SR
//
static VMI_REG_WRITE_FN(writeSR) {
    or1kP or1k = (or1kP)processor;
    OR1K_ARTIFACT_ACCESS(or1k, or1kSetSR(or1k, *(Uns32*)buffer));
    return True;
}

//
// Write callback for PICMR
//
static VMI_REG_WRITE_FN(writePICMR) {
    or1kP or1k = (or1kP)processor;
    OR1K_ARTIFACT_ACCESS(or1k, or1kSetPICMR(or1k, *(Uns32*)buffer));
    return True;
}

//
// Read callback for TTCR
//
static VMI_REG_READ_FN(readTTCR) {
    or1kP or1k = (or1kP)processor;
    OR1K_ARTIFACT_ACCESS(or1k, *(Uns32*)buffer = or1kGetTTCR(or1k));
    return True;
}

//
// Write callback for TTCR
//
static VMI_REG_WRITE_FN(writeTTCR) {
    or1kP or1k = (or1kP)processor;
    OR1K_ARTIFACT_ACCESS(or1k, or1kSetTTCR(or1k, *(Uns32*)buffer));
    return True;
}

//
// Write callback for TTMR
//
static VMI_REG_WRITE_FN(writeTTMR) {
    or1kP or1k = (or1kP)processor;
    OR1K_ARTIFACT_ACCESS(or1k, or1kSetTTMR(or1k, *(Uns32*)buffer));
    return True;
}

//
// Static array holding information about the registers in the OR1K
//
static const vmiRegInfo registers[] = {

    // registers visible in gdb
    OR1K_REG_INFO("R0",     0,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_R (regs[0],   OR1K_GROUP(GPR))   ,      "constant zero"),
    OR1K_REG_INFO("R1",     1,  vmi_REG_SP,   OR1K_BITS, OR1K_RAW_REG_RW(regs[1],   OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R2",     2,  vmi_REG_FP,   OR1K_BITS, OR1K_RAW_REG_RW(regs[2],   OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R3",     3,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[3],   OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R4",     4,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[4],   OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R5",     5,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[5],   OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R6",     6,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[6],   OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R7",     7,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[7],   OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R8",     8,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[8],   OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R9",     9,  vmi_REG_LR,   OR1K_BITS, OR1K_RAW_REG_RW(regs[9],   OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R10",   10,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[10],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R11",   11,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[11],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R12",   12,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[12],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R13",   13,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[13],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R14",   14,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[14],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R15",   15,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[15],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R16",   16,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[16],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R17",   17,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[17],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R18",   18,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[18],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R19",   19,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[19],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R20",   20,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[20],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R21",   21,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[21],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R22",   22,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[22],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R23",   23,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[23],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R24",   24,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[24],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R25",   25,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[25],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R26",   26,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[26],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R27",   27,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[27],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R28",   28,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[28],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R29",   29,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[29],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R30",   30,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[30],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("R31",   31,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(regs[31],  OR1K_GROUP(GPR))   ,      0),
    OR1K_REG_INFO("PC",    64,  vmi_REG_PC,   OR1K_BITS, OR1K_CB_REG_RW (PC,        OR1K_GROUP(SYSTEM)),      0),
    OR1K_REG_INFO("SR",    65,  vmi_REG_NONE, OR1K_BITS, OR1K_CB_REG_RW (SR,        OR1K_GROUP(SYSTEM)),      "status register"),
    OR1K_REG_INFO("EPCR",  66,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(EPC,       OR1K_GROUP(SYSTEM)),      "exception PC"),
    OR1K_REG_INFO("EEAR",  67,  vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(EEAR,      OR1K_GROUP(SYSTEM)),      "exception effective address "),

    // registers not visible in gdb
    OR1K_REG_INFO("ESR",   100, vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(ESR,       OR1K_GROUP(SYSTEM)),      "exception status register"),
    OR1K_REG_INFO("PICMR", 101, vmi_REG_NONE, OR1K_BITS, OR1K_CB_REG_W  (PICMR,     OR1K_GROUP(SYSTEM)),      "PIC mask register"),
    OR1K_REG_INFO("PICSR", 102, vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(PICSR,     OR1K_GROUP(SYSTEM)),      "PIC status register"),
    OR1K_REG_INFO("TTCR",  103, vmi_REG_NONE, OR1K_BITS, OR1K_CB_REG_RW (TTCR,      OR1K_GROUP(SYSTEM)),      "tick timer count register"),
    OR1K_REG_INFO("TTMR",  104, vmi_REG_NONE, OR1K_BITS, OR1K_CB_REG_W  (TTMR,      OR1K_GROUP(SYSTEM)),      "tick timer mode register"),
    OR1K_REG_INFO("EXCPT", 200, vmi_REG_NONE, OR1K_BITS, OR1K_RAW_REG_RW(exception, OR1K_GROUP(INTEGRATION)), "current exception"),

    {0},
};

//
// Is the passed register supported on this processor?
//
static Bool isRegSupported(or1kP or1k, vmiRegInfoCP reg, Bool gdbFrame) {

    if(gdbFrame && IS_GDB_HIDDEN_REG(reg->gdbIndex)) {

        // if this is a GDB frame request then registers that should be hidden
        // from GDB should be ignored
        return False;

    } else {

        // other registers are always supported
        return True;
    }
}

//
// Return next supported register on this processor
//
static vmiRegInfoCP getNextRegister(or1kP or1k, vmiRegInfoCP reg, Bool gdbFrame) {

    do {
        if(!reg) {
            reg = registers;
        } else if((reg+1)->name) {
            reg = reg+1;
        } else {
            reg = 0;
        }
    } while(reg && !isRegSupported(or1k, reg, gdbFrame));

    return reg;
}

//
// Register structure iterator
//
VMI_REG_INFO_FN(or1kRegInfo) {
    return getNextRegister((or1kP)processor, prev, gdbFrame);
}

//
// Register group iterator
//
VMI_REG_GROUP_FN(or1kRegGroup) {

    if(!prev) {
        return groups;
    } else if((prev+1)->name) {
        return prev+1;
    } else {
        return 0;
    }
}

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
#include "vmi/vmiCxt.h"
#include "vmi/vmiRt.h"

// model header files
#include "m16cFunctions.h"
#include "m16cUtils.h"
#include "m16cStructure.h"
#include "m16cTypeRefs.h"


////////////////////////////////////////////////////////////////////////////////
// REGISTER ACCESS FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Some registers are hidden in gdb
//
#define M16_GDB_HIDDEN_INDEX  7
#define IS_GDB_HIDDEN_REG(_I) ((_I)>=M16_GDB_HIDDEN_INDEX)

//
// Read callback for PC
//
static VMI_REG_READ_FN(readPC) {
    *(Uns32*)buffer = (Uns32)vmirtGetPC(processor);
    return True;
}

//
// Write callback for PC
//
static VMI_REG_WRITE_FN(writePC) {
    vmirtSetPC(processor, *(Uns32*)buffer);
    return True;
}

//
// Used to define a directly-accessible register
//
#define M16_REG_INFO_RAW(_NAME, _INDEX, _USAGE, _BITS, _ACCESS, _REG) { \
    name     : _NAME,           \
    gdbIndex : _INDEX,          \
    usage    : _USAGE,          \
    bits     : _BITS,           \
    access   : _ACCESS,         \
    raw      : M16C_REG(_REG)   \
}

//
// Used to define a callback-accessible register
//
#define M16_REG_INFO_CB(_NAME, _INDEX, _USAGE, _BITS, _ACCESS, _RCB, _WCB, _UD) { \
    name     : _NAME,           \
    gdbIndex : _INDEX,          \
    usage    : _USAGE,          \
    bits     : _BITS,           \
    access   : _ACCESS,         \
    readCB   : _RCB,            \
    writeCB  : _WCB,            \
    userData : _UD              \
}

//
// Static array holding information about the registers in the m16c frame
//
static const vmiRegInfo frameRegs[] = {

    /* General Purpose Registers */
    M16_REG_INFO_RAW("R0",   0x00, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R0),
    M16_REG_INFO_RAW("R0B",  0x01, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R0B),
    M16_REG_INFO_RAW("R1",   0x02, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R1),
    M16_REG_INFO_RAW("R1B",  0x03, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R1B),
    M16_REG_INFO_RAW("R2",   0x04, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R2),
    M16_REG_INFO_RAW("R2B",  0x05, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R2B),
    M16_REG_INFO_RAW("R3",   0x06, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R3),
    M16_REG_INFO_RAW("R3B",  0x07, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R3B),
    M16_REG_INFO_RAW("A0",   0x08, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_A0),
    M16_REG_INFO_RAW("A0B",  0x09, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_A0B),
    M16_REG_INFO_RAW("A1",   0x0a, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_A1),
    M16_REG_INFO_RAW("A1B",  0x0b, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_A1B),
    M16_REG_INFO_RAW("FB",   0x0c, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_FB),
    M16_REG_INFO_RAW("FBB",  0x0d, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_FBB),
    M16_REG_INFO_RAW("SB",   0x0e, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_SB),
// Cannot determine what this register is but layout of 'G' packet requires it
    M16_REG_INFO_RAW("SB",   0x0f, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_SB),

    M16_REG_INFO_RAW("USP",  0x10, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_USP),
    M16_REG_INFO_RAW("ISP",  0x11, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_ISP),
    M16_REG_INFO_RAW("INTB", 0x12, vmi_REG_NONE, 24, vmi_RA_RW, M16C_REG_INTB),

    M16_REG_INFO_CB ("PC",   0x13, vmi_REG_PC,   24, vmi_RA_RW, readPC, writePC, 0),
    M16_REG_INFO_RAW("FLG",  0x14, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_FLG),

    {0},
};

//
// Static array holding information about the registers in the m16c
//
static const vmiRegInfo normalRegs[] = {

    /* General Purpose Registers */
    M16_REG_INFO_RAW("R0",   0x00, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R0),
    M16_REG_INFO_RAW("R1",   0x02, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R1),
    M16_REG_INFO_RAW("R2",   0x04, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R2),
    M16_REG_INFO_RAW("R3",   0x06, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R3),
    M16_REG_INFO_RAW("A0",   0x08, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_A0),
    M16_REG_INFO_RAW("A1",   0x0a, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_A1),
    M16_REG_INFO_RAW("FB",   0x0c, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_FB),

    /* Shadow register to store alternate bank values */
    M16_REG_INFO_RAW("R0B",  0x01, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R0B),
    M16_REG_INFO_RAW("R1B",  0x03, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R1B),
    M16_REG_INFO_RAW("R2B",  0x05, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R2B),
    M16_REG_INFO_RAW("R3B",  0x07, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_R3B),
    M16_REG_INFO_RAW("A0B",  0x09, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_A0B),
    M16_REG_INFO_RAW("A1B",  0x0b, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_A1B),
    M16_REG_INFO_RAW("FBB",  0x0d, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_FBB),

    /* System Registers */
    M16_REG_INFO_RAW("SB",   0x0e, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_SB),

    M16_REG_INFO_RAW("USP",  0x10, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_USP),
    M16_REG_INFO_RAW("ISP",  0x11, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_ISP),
    M16_REG_INFO_RAW("INTB", 0x12, vmi_REG_NONE, 20, vmi_RA_RW, M16C_REG_INTB),
    M16_REG_INFO_CB ("PC",   0x13, vmi_REG_PC,   20, vmi_RA_RW, readPC, writePC, 0),
    M16_REG_INFO_RAW("FLG",  0x14, vmi_REG_NONE, 16, vmi_RA_RW, M16C_REG_FLG),

    {0},
};

//
// Register structure iterator
//
VMI_REG_INFO_FN(m16cRegInfo) {
    vmiRegInfoCP reg = prev ? prev+1 : gdbFrame ? frameRegs : normalRegs;
    return reg->name ? reg : 0;
}


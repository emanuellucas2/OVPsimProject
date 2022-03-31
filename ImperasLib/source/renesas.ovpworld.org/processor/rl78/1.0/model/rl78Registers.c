/*
 * Copyright (c)      2016 eSOL TRINITY, www.esol-trinity.co.jp
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
#include "rl78Functions.h"
#include "rl78Structure.h"
#include "rl78Utils.h"
#include "rl78Message.h"        // MY_ASSERT


////////////////////////////////////////////////////////////////////////////////
// REGISTER GROUPS
////////////////////////////////////////////////////////////////////////////////

//
// This describes the register groups in the RL78
//
typedef enum rl78RegGroupIdE {
    RL78_RG_GPR,    // GPR group
    RL78_RG_BANK1,    // GPR group
    RL78_RG_BANK2,    // GPR group
    RL78_RG_BANK3,    // GPR group
    RL78_RG_BANK4,    // GPR group
    RL78_RG_SYSTEM, // System register group
    RL78_RG_LAST    // KEEP LAST: for sizing
} rl78RegGroupId;

//
// This provides information about each group
//
static const vmiRegGroup groups[RL78_RG_LAST+1] = {
    [RL78_RG_GPR]    = {name: "GPR"   },
    [RL78_RG_BANK1]  = {name: "Bank1" },
    [RL78_RG_BANK2]  = {name: "Bank2" },
    [RL78_RG_BANK3]  = {name: "Bank3" },
    [RL78_RG_BANK4]  = {name: "Bank4" },
    [RL78_RG_SYSTEM] = {name: "System"}
};

//
// Some registers are hidden in gdb, but we allow access to them
//
#define RL78_GDB_HIDDEN_INDEX 100
#define IS_GDB_HIDDEN_REG(_I) ((_I)>=RL78_GDB_HIDDEN_INDEX)


////////////////////////////////////////////////////////////////////////////////
// REGISTER ACCESS FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Macro to specify basic register attributes
//
#define RL78_REG_INFO(_NAME, _INDEX, _USAGE, _BITS, _DETAIL, _DESC) { \
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
#define RL78_RAW_REG_RW(_R, _G) \
    access   : vmi_RA_RW,           \
    raw      : RL78_OFFSET(_R),     \
    group    : _G

//
// Macro to specify a register accessible raw for read only
//
#define RL78_RAW_REG_R(_R, _G) \
    access   : vmi_RA_R,            \
    raw      : RL78_OFFSET(_R),     \
    group    : _G

//
// Macro to specify a register accessible with callbacks for read/write
//
#define RL78_CB_REG_RW(_RCB, _WCB, _G) \
    access   : vmi_RA_RW,           \
    readCB   : _RCB,                \
    writeCB  : _WCB,                \
    group    : _G

//
// Macro to specify a register accessible with callbacks for read only
//
#define RL78_CB_REG_R(_RCB, _G) \
    access   : vmi_RA_R,            \
    readCB   : _RCB,                \
    group    : _G




//#define VMI_REG_READ_FN(_NAME) Bool _NAME( 
//    vmiProcessorP processor,    
//    vmiRegInfoCP  reg,          
//    void         *buffer        
//)
static VMI_REG_READ_FN(readPC) {
    rl78P rl78 = (rl78P) processor;
    MY_MESSAGE(rl78, "I", "readPC\n");
    *(Uns32*) buffer = (Uns32) vmirtGetPC(processor);
    return True;
}

//#define VMI_REG_WRITE_FN(_NAME) Bool _NAME( 
//    vmiProcessorP processor,    
//    vmiRegInfoCP  reg,          
//    const void   *buffer        
//)
static VMI_REG_WRITE_FN(writePC) {
    rl78P rl78 = (rl78P) processor;
    MY_MESSAGE(rl78, "I", "writePC\n");
    vmirtSetPC(processor, *(Uns32*)buffer);
    return True;
}


//#define VMI_REG_READ_FN(_NAME) Bool _NAME( 
//    vmiProcessorP processor,    
//    vmiRegInfoCP  reg,          
//    void         *buffer        
//)
static VMI_REG_READ_FN(readPSW) {
    rl78P rl78 = (rl78P) processor;
    MY_MESSAGE(rl78, "I", "readPSW\n");
    *(Uns8*) buffer = rl78GetPSW_REG(rl78);
    return True;
}


static VMI_REG_READ_FN(readGPR) {
    rl78P rl78 = (rl78P) processor;
    MY_MESSAGE(rl78, "I", "readGPR\n");

    Uns32 idx  = 8 * rl78->PSW_RBS + (reg->gdbIndex - 100);
    
    *(Uns8*) buffer = rl78->regs[idx];
    return True;
}


static VMI_REG_WRITE_FN(writeGPR) {
    rl78P rl78 = (rl78P) processor;
    MY_MESSAGE(rl78, "I", "writeGPR\n");

    Uns32 idx  = 8 * rl78->PSW_RBS + (reg->gdbIndex - 100);
    
    rl78->regs[idx] = *(Uns8*) buffer;
    return True;
}




//
// Static array holding information about the registers in the RL78
//
static const vmiRegInfo registers[] = {

    // registers visible in gdb
    // gdbIndex is according to gdb-7.10/gdb/rl78-tdep.c

    RL78_REG_INFO("X[RB0]",  0, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 0 + 0],  &groups[RL78_RG_BANK1 ]), "R00"),
    RL78_REG_INFO("A[RB0]",  1, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 0 + 1],  &groups[RL78_RG_BANK1 ]), "R01"),
    RL78_REG_INFO("C[RB0]",  2, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 0 + 2],  &groups[RL78_RG_BANK1 ]), "R02"),
    RL78_REG_INFO("B[RB0]",  3, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 0 + 3],  &groups[RL78_RG_BANK1 ]), "R03"),
    RL78_REG_INFO("E[RB0]",  4, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 0 + 4],  &groups[RL78_RG_BANK1 ]), "R04"),
    RL78_REG_INFO("D[RB0]",  5, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 0 + 5],  &groups[RL78_RG_BANK1 ]), "R05"),
    RL78_REG_INFO("L[RB0]",  6, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 0 + 6],  &groups[RL78_RG_BANK1 ]), "R06"),
    RL78_REG_INFO("H[RB0]",  7, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 0 + 7],  &groups[RL78_RG_BANK1 ]), "R07"),

    RL78_REG_INFO("X[RB1]",  8, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 1 + 0],  &groups[RL78_RG_BANK2 ]), "R08"),
    RL78_REG_INFO("A[RB1]",  9, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 1 + 1],  &groups[RL78_RG_BANK2 ]), "R09"),
    RL78_REG_INFO("C[RB1]", 10, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 1 + 2],  &groups[RL78_RG_BANK2 ]), "R10"),
    RL78_REG_INFO("B[RB1]", 11, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 1 + 3],  &groups[RL78_RG_BANK2 ]), "R11"),
    RL78_REG_INFO("E[RB1]", 12, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 1 + 4],  &groups[RL78_RG_BANK2 ]), "R12"),
    RL78_REG_INFO("D[RB1]", 13, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 1 + 5],  &groups[RL78_RG_BANK2 ]), "R13"),
    RL78_REG_INFO("L[RB1]", 14, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 1 + 6],  &groups[RL78_RG_BANK2 ]), "R14"),
    RL78_REG_INFO("H[RB1]", 15, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 1 + 7],  &groups[RL78_RG_BANK2 ]), "R15"),

    RL78_REG_INFO("X[RB2]", 16, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 2 + 0],  &groups[RL78_RG_BANK3 ]), "R16"),
    RL78_REG_INFO("A[RB2]", 17, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 2 + 1],  &groups[RL78_RG_BANK3 ]), "R17"),
    RL78_REG_INFO("C[RB2]", 18, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 2 + 2],  &groups[RL78_RG_BANK3 ]), "R18"),
    RL78_REG_INFO("B[RB2]", 19, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 2 + 3],  &groups[RL78_RG_BANK3 ]), "R19"),
    RL78_REG_INFO("E[RB2]", 20, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 2 + 4],  &groups[RL78_RG_BANK3 ]), "R20"),
    RL78_REG_INFO("D[RB2]", 21, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 2 + 5],  &groups[RL78_RG_BANK3 ]), "R21"),
    RL78_REG_INFO("L[RB2]", 22, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 2 + 6],  &groups[RL78_RG_BANK3 ]), "R22"),
    RL78_REG_INFO("H[RB2]", 23, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 2 + 7],  &groups[RL78_RG_BANK3 ]), "R23"),

    RL78_REG_INFO("X[RB3]", 24, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 3 + 0],  &groups[RL78_RG_BANK4 ]), "R24"),
    RL78_REG_INFO("A[RB3]", 25, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 3 + 1],  &groups[RL78_RG_BANK4 ]), "R25"),
    RL78_REG_INFO("C[RB3]", 26, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 3 + 2],  &groups[RL78_RG_BANK4 ]), "R26"),
    RL78_REG_INFO("B[RB3]", 27, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 3 + 3],  &groups[RL78_RG_BANK4 ]), "R27"),
    RL78_REG_INFO("E[RB3]", 28, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 3 + 4],  &groups[RL78_RG_BANK4 ]), "R28"),
    RL78_REG_INFO("D[RB3]", 29, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 3 + 5],  &groups[RL78_RG_BANK4 ]), "R29"),
    RL78_REG_INFO("L[RB3]", 30, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 3 + 6],  &groups[RL78_RG_BANK4 ]), "R30"),
    RL78_REG_INFO("H[RB3]", 31, vmi_REG_NONE,  8, RL78_RAW_REG_RW(regs[8 * 3 + 7],  &groups[RL78_RG_BANK4 ]), "R31"),

    RL78_REG_INFO("PSW"   , 32, vmi_REG_NONE,  8, RL78_CB_REG_R  (readPSW,          &groups[RL78_RG_SYSTEM]), "status register"),        // RL78_PSW_REGNUM
    RL78_REG_INFO("ES"    , 33, vmi_REG_NONE,  8, RL78_RAW_REG_RW(ES_Addr.ES,       &groups[RL78_RG_SYSTEM]), "ES"),                     // RL78_ES_REGNUM
    RL78_REG_INFO("CS"    , 34, vmi_REG_NONE,  8, RL78_RAW_REG_RW(CS_Addr.CS,       &groups[RL78_RG_SYSTEM]), "CS"),                     // RL78_CS_REGNUM
    RL78_REG_INFO("PC"    , 35, vmi_REG_PC  , 20, RL78_CB_REG_RW (readPC, writePC,  &groups[RL78_RG_SYSTEM]), "program counter"),        // RL78_RAW_PC_REGNUM

    // 36    RL78_SPL_REGNUM
    // 37    RL78_SPH_REGNUM
    RL78_REG_INFO("PMC"   , 38, vmi_REG_NONE,  8, RL78_RAW_REG_R (PMC,              &groups[RL78_RG_SYSTEM]), "processor mode control"), // RL78_PMC_REGNUM

    RL78_REG_INFO("MEM"   , 39, vmi_REG_NONE,  8, RL78_RAW_REG_R (MEM,              &groups[RL78_RG_SYSTEM]), "MEM"),                    // 39    RL78_MEM_REGNUM
    // 40    RL78_NUM_REGS

//    RL78_REG_INFO("PC"    , 41, vmi_REG_PC  , 20, RL78_CB_REG_RW (readPC, writePC,  &groups[RL78_RG_SYSTEM]), "program counter"),      // RL78_PC_REGNUM
    RL78_REG_INFO("SP"    , 42, vmi_REG_SP  , 16, RL78_RAW_REG_RW(SP,               &groups[RL78_RG_SYSTEM]), "stack pointer"),          // RL78_SP_REGNUM

    // registers not visible in gdb
//    RL78_REG_INFO("EXCPT", 100, vmi_REG_NONE,  8, RL78_RAW_REG_R (exception,       &groups[RL78_RG_SYSTEM]), 0),

    RL78_REG_INFO("X"    , 100, vmi_REG_LR,    8, RL78_CB_REG_RW(readGPR, writeGPR, &groups[RL78_RG_GPR   ]), "X"  ),
    RL78_REG_INFO("A"    , 101, vmi_REG_NONE,  8, RL78_CB_REG_RW(readGPR, writeGPR, &groups[RL78_RG_GPR   ]), "A"  ),
    RL78_REG_INFO("C"    , 102, vmi_REG_NONE,  8, RL78_CB_REG_RW(readGPR, writeGPR, &groups[RL78_RG_GPR   ]), "C"  ),
    RL78_REG_INFO("B"    , 103, vmi_REG_NONE,  8, RL78_CB_REG_RW(readGPR, writeGPR, &groups[RL78_RG_GPR   ]), "B"  ),
    RL78_REG_INFO("E"    , 104, vmi_REG_NONE,  8, RL78_CB_REG_RW(readGPR, writeGPR, &groups[RL78_RG_GPR   ]), "E"  ),
    RL78_REG_INFO("D"    , 105, vmi_REG_NONE,  8, RL78_CB_REG_RW(readGPR, writeGPR, &groups[RL78_RG_GPR   ]), "D"  ),
    RL78_REG_INFO("L"    , 106, vmi_REG_NONE,  8, RL78_CB_REG_RW(readGPR, writeGPR, &groups[RL78_RG_GPR   ]), "L"  ),
    RL78_REG_INFO("H"    , 107, vmi_REG_NONE,  8, RL78_CB_REG_RW(readGPR, writeGPR, &groups[RL78_RG_GPR   ]), "H"  ),

    {0},
};

//
// Is the passed register supported on this processor?
//
static Bool isRegSupported(rl78P rl78, vmiRegInfoCP reg, Bool gdbFrame) {

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
static vmiRegInfoCP getNextRegister(rl78P rl78, vmiRegInfoCP reg, Bool gdbFrame) {

    do {
        if(!reg) {
            reg = registers;
        } else if((reg+1)->name) {
            reg = reg+1;
        } else {
            reg = 0;
        }
    } while(reg && !isRegSupported(rl78, reg, gdbFrame));

    return reg;
}

//
// Register structure iterator
//
//#define VMI_REG_INFO_FN(_NAME) vmiRegInfoCP _NAME( 
//    vmiProcessorP processor,    
//    vmiRegInfoCP  prev,         
//    Bool          gdbFrame      
//)
VMI_REG_INFO_FN(rl78RegInfo) {
    return getNextRegister((rl78P)processor, prev, gdbFrame);
}

//
// Register group iterator
//
//#define VMI_REG_GROUP_FN(_NAME) vmiRegGroupCP _NAME( 
//    vmiProcessorP processor,    
//    vmiRegGroupCP prev          
//)
VMI_REG_GROUP_FN(rl78RegGroup) {

    if(!prev) {
        return groups;
    } else if((prev+1)->name) {
        return prev+1;
    } else {
        return 0;
    }
}


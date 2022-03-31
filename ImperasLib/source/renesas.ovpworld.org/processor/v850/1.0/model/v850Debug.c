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

#include "hostapi/impAlloc.h"

#include "vmi/vmiAttrs.h"
#include "vmi/vmiDbg.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "v850Structure.h"
#include "v850Exceptions.h"
#include "v850Functions.h"
#include "v850Utils.h"

//
// Macro to specify basic register attributes
//
#define V850_REGEXT_INFO(_SET, _NAME, _INDEX, _USAGE, _BITS, _GROUP, _DETAIL, _DESC) { \
    {\
        name        : _NAME,    \
        description : _DESC,    \
        gdbIndex    : _INDEX,   \
        usage       : _USAGE,   \
        bits        : _BITS,    \
        group       : _GROUP,   \
        _DETAIL                 \
    }, \
    _SET \
}
#define V850_REG_INFO(_NAME, _INDEX, _USAGE, _BITS, _GROUP, _DETAIL, _DESC) { \
    name        : _NAME,    \
    description : _DESC,    \
    gdbIndex    : _INDEX,   \
    usage       : _USAGE,   \
    bits        : _BITS,    \
    group       : _GROUP,   \
    _DETAIL                 \
}
#define V850_REG_INFO_QUIET(_NAME, _INDEX, _USAGE, _BITS, _GROUP, _DETAIL, _DESC) { \
    name         : _NAME,   \
    description  : _DESC,   \
    gdbIndex     : _INDEX,  \
    usage        : _USAGE,  \
    bits         : _BITS,   \
    group        : _GROUP,  \
    noTraceChange: True,    \
    noSaveRestore: True,    \
    _DETAIL                 \
}

//
// Macro to specify a register accessible raw for read/write
//
#define V850_REG_RAWRW(_R)      \
    access   : vmi_RA_RW,       \
    raw      : V850_CPU_REG(_R)

//
// Macro to specify a register accessible raw for read only
//
#define V850_REG_RAWR(_R)       \
    access   : vmi_RA_R,        \
    raw      : V850_CPU_REG(_R)

//
// Macro to specify a register accessible with callbacks for read/write
//
#define V850_REG_CBRW(_RCB, _WCB) \
    access   : vmi_RA_RW,         \
    readCB   : _RCB,              \
    writeCB  : _WCB

//
// Macro to specify a register accessible with callbacks for read/write
//
#define V850_REG_RAWR_CBW(_R, _WCB) \
    access   : vmi_RA_RW,           \
    raw      : V850_CPU_REG(_R),    \
    writeCB  : _WCB

//
// Macro to specify a register accessible with callbacks for read only
//
#define V850_REG_CBR(_RCB) \
    access   : vmi_RA_R,    \
    readCB   : _RCB

static VMI_REG_READ_FN(readPC) {
    *(v850Addr*)buffer = (Uns32)vmirtGetPC(processor);
    return True;
}

static VMI_REG_WRITE_FN(writePC) {
    vmirtSetPC(processor, *(v850Addr*)buffer);
    return True;
}

static VMI_REG_READ_FN(readECR) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = rECR(v850, 0);
    return True;
}

static VMI_REG_WRITE_FN(writeECR) {
    v850P v850 = (v850P)processor;
    Uns32 newv = *(Uns32*)buffer;
    wECR(v850, newv, 0);
    return True;
}

static VMI_REG_READ_FN(readPSW) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = rPSW(v850, 0);
    return True;
}

static VMI_REG_WRITE_FN(writePSW) {
    v850P v850 = (v850P)processor;
    Uns32 newv = *(Uns32*)buffer;
    wPSW(v850, newv, 0);
    return True;
}

static VMI_REG_READ_FN(readEFG) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = rEFG(v850, 0);
    return True;
}

static VMI_REG_WRITE_FN(writeEFG) {
    v850P v850 = (v850P)processor;
    Uns32 newv = *(Uns32*)buffer;

    Uns32 mask = v850->SPR_EFG_wmask.reg;
    v850->SPR_EFG_wmask.reg = ~0;
    wEFG(v850, newv, 0);
    v850->SPR_EFG_wmask.reg = mask;
    return True;
}

static VMI_REG_READ_FN(padZERO) {
    *(Uns32*)buffer = 0x00000000;
    return True;
}

static VMI_REG_READ_FN(readFPSR) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = rFPSR(v850, 0);
    return True;
}

static VMI_REG_WRITE_FN(writeFPSR) {
    v850P v850 = (v850P)processor;
    Uns32 newv = *(Uns32*)buffer;
    wFPSR(v850, newv, 0);

    return True;
}

static VMI_REG_READ_FN(readFPST) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = rFPST(v850, 0);
    return True;
}

static VMI_REG_WRITE_FN(writeFPST) {
    v850P v850 = (v850P)processor;
    Uns32 newv = *(Uns32*)buffer;
    wFPST(v850, newv, 0);
    return True;
}

static VMI_REG_READ_FN(readFPCC) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = rFPCC(v850, 0);
    return True;
}

static VMI_REG_WRITE_FN(writeFPCC) {
    v850P v850 = (v850P)processor;
    Uns32 newv = *(Uns32*)buffer;
    wFPCC(v850, newv, 0);
    return True;
}

static VMI_REG_READ_FN(readFPCFG) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = rFPCFG(v850, 0);
    return True;
}

static VMI_REG_WRITE_FN(writeFPCFG) {
    v850P v850 = (v850P)processor;
    Uns32 newv = *(Uns32*)buffer;
    wFPCFG(v850, newv, 0);
    return True;
}

static VMI_REG_READ_FN(readFPEC) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = v850->SPR_FPEC.reg & v850->SPR_FPEC_rmask.reg;
    return True;
}

static VMI_REG_WRITE_FN(writeFPEC) {
    v850P v850 = (v850P)processor;
    Uns32 mask = v850->SPR_FPEC_wmask.reg;
    Uns32 newv = *(Uns32*)buffer;
    Uns32 oldv = v850->SPR_FPEC.reg;
    v850->SPR_FPEC.reg = (oldv & ~mask) | (newv & mask);
    return True;
}

static VMI_REG_WRITE_FN(writeBSEL) {
    v850P v850 = (v850P)processor;
    Uns32 newv = *(Uns32*)buffer;
    wBSEL(v850, newv, 0);
    return True;
}

//
// MPU
//
static VMI_REG_WRITE_FN(writeMPL) {
    return True;
}
static VMI_REG_READ_FN(readStop) {
    v850P v850 = (v850P) processor;
    *(Uns32*)buffer = (v850->disable & V850_STOP) && True;
    return True;
}

static VMI_REG_WRITE_FN(writeStop) {
    v850P v850 = (v850P) processor;

    if(*(Uns32*)buffer) {
        v850Halt(v850, V850_STOP);
    } else {
        v850Restart(v850, V850_STOP);
    }
    return True;
}

static VMI_REG_READ_FN(readResultId) {
    v850P v850 = (v850P) processor;
    *(Uns8*)buffer = v850->ResultId;
    return True;
}
static VMI_REG_WRITE_FN(writeResultId) {
    v850P v850 = (v850P) processor;
    v850->ResultId = *(Uns8*)buffer;

    Uns8 size = v850->ResultSz;
    Uns8 base = v850->ResultId;

    //
    // Check to see if any exceptions are enabled for flags
    //

    if (base == 0) {
        // Do nothing if attempting to write to r0
    } else if (size==16 || size==32) {
        v850->gpr[base] = v850->ResultLo;

    } else if (size==64) {
        if ((base & 0x1) == 0) {
            v850->gpr[base+0] = v850->ResultLo;
            v850->gpr[base+1] = v850->ResultHi;
        } else {
            vmiMessage("F", "DPFP_OFF", "r%d is not a valid target for a DFP operation", base);
        }

    } else {
        vmiMessage("W", "FP_SIZE", "%d is not a valid size for a FP operation", size);

    }
    return True;
}

static VMI_REG_READ_FN(readResultCC) {
    v850P v850 = (v850P) processor;
    *(Uns32*)buffer = v850->ResultCC.reg;
    return True;
}
static VMI_REG_WRITE_FN(writeResultCC) {
    v850P v850 = (v850P) processor;
    v850->ResultCC.reg = *(Uns32*)buffer;

    //
    // Trigger update
    //
    return True;
}

//  static const char *v850_reg_names[] =
//  {
//    "r0",   "r1",     "r2",    "r3",    "r4",   "r5",   "r6",   "r7",
//    "r8",   "r9",     "r10",   "r11",   "r12",  "r13",  "r14",  "r15",
//    "r16",  "r17",    "r18",   "r19",   "r20",  "r21",  "r22",  "r23",
//    "r24",  "r25",    "r26",   "r27",   "r28",  "r29",  "r30",  "r31",
//
//
//    "eipc", "eipsw",  "fepc",  "fepsw", "ecr",  "psw",  "sr6",  "sr7",
//    "sr8",  "sr9",    "sr10",  "sr11",  "sr12", "sr13", "sr14", "sr15",
//    "sr16", "sr17",   "sr18",  "sr19",  "sr20", "sr21", "sr22", "sr23",
//    "sr24", "sr25",   "sr26",  "sr27",  "sr28", "sr29", "sr30", "sr31",
//    "pc",   "fp"
//  };

//  static const char *v850e_reg_names[] =
//  {
//    "r0",   "r1",    "r2",   "r3",    "r4",   "r5",   "r6",   "r7",
//    "r8",   "r9",    "r10",  "r11",   "r12",  "r13",  "r14",  "r15",
//    "r16",  "r17",   "r18",  "r19",   "r20",  "r21",  "r22",  "r23",
//    "r24",  "r25",   "r26",  "r27",   "r28",  "r29",  "r30",  "r31",
//
//    "eipc", "eipsw", "fepc", "fepsw", "ecr",  "psw",  "sr6",  "sr7",
//    "sr8",  "sr9",   "sr10", "sr11",  "sr12", "sr13", "sr14", "sr15",
//    "ctpc", "ctpsw", "dbpc", "dbpsw", "ctbp", "sr21", "sr22", "sr23",
//    "sr24", "sr25",  "sr26", "sr27",  "sr28", "sr29", "sr30", "sr31",
//    "pc",   "fp"
//  };


//  static const char *v850e2_reg_names[] =
//  {
//    /* General purpose registers.  */
//    "r0",   "r1", "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
//    "r8",   "r9", "r10", "r11", "r12", "r13", "r14", "r15",
//    "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
//    "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",
//
//    /* System registers - main banks.  */
//    "eipc", "eipsw", "fepc",  "fepsw", "ecr",  "psw",  "pid",  "cfg",
//    "",     "",      "",      "sccfg", "scbp", "eiic", "feic", "dbic",
//    "ctpc", "ctpsw", "dbpc",  "dbpsw", "ctbp", "dir",  "",     "",
//    "",     "",      "",      "",      "eiwr", "fewr", "dbwr", "bsel",
//
//
//    /* PC.  */
//    "pc", "",
//
//    /* System registers - MPV (PROT00) bank.  */
//    "vsecr", "vstid", "vsadr", "",     "vmecr", "vmtid", "vmadr", "",
//    "vpecr", "vptid", "vpadr", "",     "",      "",       "",     "",
//    "",      "",      "",      "",     "",      "",       "",     "",
//    "mca",   "mcs",   "mcc",   "mcr",
//
//    /* System registers - MPU (PROT01) bank.  */
//    "mpm",   "mpc",   "tid",   "",      "",      "",      "ipa0l", "ipa0u",
//    "ipa1l", "ipa1u", "ipa2l", "ipa2u", "ipa3l", "ipa3u", "ipa4l", "ipa4u",
//    "dpa0l", "dpa0u", "dpa1l", "dpa1u", "dpa2l", "dpa2u", "dpa3l", "dpa3u",
//    "dpa4l", "dpa4u", "dpa5l", "dpa5u",
//
//    /* FPU system registers.  */
//    "",     "",     "",      "",     "", "", "fpsr", "fpepc",
//    "fpst", "fpcc", "fpcfg", "fpec", "", "", "",     "",
//    "",     "",     "",      "",     "", "", "",     "",
//    "",     "",     "",      "fpspc"
//  };

//  static const char *v850e3v5_reg_names[] =
//  {
//    /* General purpose registers.  */
//0:  "r0",   "r1", "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
//    "r8",   "r9", "r10", "r11", "r12", "r13", "r14", "r15",
//    "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
//    "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",
//
//    /* selID 0, not including FPU registers.  The FPU registers are
//       listed later on.  32:63*/
//32: "eipc", "eipsw", "fepc", "fepsw", "",     "psw", "" /* fpsr */, "" /* fpepc */,
//    "" /* fpst */, "" /* fpcc */, "" /* fpcfg */, "" /* fpec */,
//    "sesr", "eiic", "feic", "",
//    "ctpc", "ctpsw", "", "", "ctbp", "", "", "",
//    "", "", "", "", "eiwr", "fewr", "", "bsel",
//
//
//    /* PC.  64,65 */
//64: "pc", "",
//
//    /* v850e2 MPV bank.  66:+=28*/
//66: "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "",
//
//    /* Skip v850e2 MPU bank.  It's tempting to reuse these, but we need
//       32 entries for this bank.  66:+=(2*28)*/
//94: "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "",
//
//    /* FPU system registers.  These are actually in selID 0, but
//       are placed here to preserve register numbering compatibility
//       with previous architectures.  66:+=(3*28) */
//122:"", "", "", "", "", "", "fpsr", "fpepc",
//    "fpst", "fpcc", "fpcfg", "fpec", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "",
//
//    /* selID 1.  */
//150:"mcfg0", "mcfg1", "rbase", "ebase", "intbp", "mctl", "pid", "fpipr",
//    "", "", "tcsel", "sccfg", "scbp", "hvccfg", "hvcbp", "vsel",
//    "vmprt0", "vmprt1", "vmprt2", "", "", "", "", "vmscctl",
//    "vmsctbl0", "vmsctbl1", "vmsctbl2", "vmsctbl3", "", "", "", "",
//
//    /* selID 2.  */
//182:"htcfg0", "", "", "", "", "htctl", "mea", "asid",
//    "mei", "ispr", "pmr", "icsr", "intcfg", "", "", "",
//    "tlbsch", "", "", "", "", "", "", "htscctl",
//    "htsctbl0", "htsctbl1", "htsctbl2", "htsctbl3",
//    "htsctbl4", "htsctbl5", "htsctbl6", "htsctbl7",
//
//    /* selID 3.  */
//214:"", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//
//    /* selID 4.  */
//246:"tlbidx", "", "", "", "telo0", "telo1", "tehi0", "tehi1",
//    "", "", "tlbcfg", "", "bwerrl", "bwerrh", "brerrl", "brerrh",
//    "ictagl", "ictagh", "icdatl", "icdath",
//    "dctagl", "dctagh", "dcdatl", "dcdath",
//    "icctrl", "dcctrl", "iccfg", "dccfg", "icerr", "dcerr", "", "",
//
//    /* selID 5.  */
//278:"mpm", "mprc", "", "", "mpbrgn", "mptrgn", "", "",
//    "mca", "mcs", "mcc", "mcr", "", "", "", "",
//    "", "", "", "", "mpprt0", "mpprt1", "mpprt2", "",
//    "", "", "", "", "", "", "", "",
//
//    /* selID 6.  */
//310:"mpla0", "mpua0", "mpat0", "", "mpla1", "mpua1", "mpat1", "",
//    "mpla2", "mpua2", "mpat2", "", "mpla3", "mpua3", "mpat3", "",
//    "mpla4", "mpua4", "mpat4", "", "mpla5", "mpua5", "mpat5", "",
//    "mpla6", "mpua6", "mpat6", "", "mpla7", "mpua7", "mpat7", "",
//
//    /* selID 7.  */
//342:"mpla8",  "mpua8",  "mpat8",  "", "mpla9",  "mpua9" , "mpat9",  "",
//    "mpla10", "mpua10", "mpat10", "", "mpla11", "mpua11", "mpat11", "",
//    "mpla12", "mpua12", "mpat12", "", "mpla13", "mpua13", "mpat13", "",
//    "mpla14", "mpua14", "mpat14", "", "mpla15", "mpua15", "mpat15", "",
//
//    /* Vector Registers */
//374:"vr0", "vr1", "vr2", "vr3", "vr4", "vr5", "vr6", "vr7",
//    "vr8", "vr9", "vr10", "vr11", "vr12", "vr13", "vr14", "vr15",
//    "vr16", "vr17", "vr18", "vr19", "vr20", "vr21", "vr22", "vr23",
//    "vr24", "vr25", "vr26", "vr27", "vr28", "vr29", "vr30", "vr31",
//  };


typedef enum v850RegGroupIdE {
    V850_RG_USER,
    V850_RG_SYSTEM,
    V850_RG_INTEGRATION,
    V850_RG_LAST
} v850RegGroupId;

static const vmiRegGroup groups[V850_RG_LAST+1] = {
    [V850_RG_USER]        = {name: "User"                },
    [V850_RG_SYSTEM]      = {name: "System"              },
    [V850_RG_INTEGRATION] = {name: "Integration_support" },
};

//
// Return next supported group on this processor
//
static vmiRegGroupCP getNextGroup(vmiRegGroupCP group) {
    if(!group) {
        group = groups;
    } else if((group+1)->name) {
        group = group+1;
    } else {
        group = 0;
    }
    return group;
}

#define SUPPORT_REGS 1000

static const vmiRegInfo gprRegisters[] = {
    /* General Purpose Registers = 32 */
    V850_REG_INFO("R0",   0, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWR (gpr[0]),  "Zero Register"),
    V850_REG_INFO("R1",   1, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[1]),  "Assembler-reserved register"),
    V850_REG_INFO("R2",   2, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[2]),  "Address/data variable register (when the real-time OS to be used is not using r2)"),
    V850_REG_INFO("R3",   3, vmi_REG_SP,   V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[3]),  "Stack pointer (SP)"),
    V850_REG_INFO("R4",   4, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[4]),  "Global pointer (GP)"),
    V850_REG_INFO("R5",   5, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[5]),  "Test pointer (TP)"),
    V850_REG_INFO("R6",   6, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[6]),  "Address/data variable registers"),
    V850_REG_INFO("R7",   7, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[7]),  "Address/data variable registers"),
    V850_REG_INFO("R8",   8, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[8]),  "Address/data variable registers"),
    V850_REG_INFO("R9",   9, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[9]),  "Address/data variable registers"),
    V850_REG_INFO("R10", 10, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[10]), "Address/data variable registers"),
    V850_REG_INFO("R11", 11, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[11]), "Address/data variable registers"),
    V850_REG_INFO("R12", 12, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[12]), "Address/data variable registers"),
    V850_REG_INFO("R13", 13, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[13]), "Address/data variable registers"),
    V850_REG_INFO("R14", 14, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[14]), "Address/data variable registers"),
    V850_REG_INFO("R15", 15, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[15]), "Address/data variable registers"),
    V850_REG_INFO("R16", 16, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[16]), "Address/data variable registers"),
    V850_REG_INFO("R17", 17, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[17]), "Address/data variable registers"),
    V850_REG_INFO("R18", 18, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[18]), "Address/data variable registers"),
    V850_REG_INFO("R19", 19, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[19]), "Address/data variable registers"),
    V850_REG_INFO("R20", 20, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[20]), "Address/data variable registers"),
    V850_REG_INFO("R21", 21, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[21]), "Address/data variable registers"),
    V850_REG_INFO("R22", 22, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[22]), "Address/data variable registers"),
    V850_REG_INFO("R23", 23, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[23]), "Address/data variable registers"),
    V850_REG_INFO("R24", 24, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[24]), "Address/data variable registers"),
    V850_REG_INFO("R25", 25, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[25]), "Address/data variable registers"),
    V850_REG_INFO("R26", 26, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[26]), "Address/data variable registers"),
    V850_REG_INFO("R27", 27, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[27]), "Address/data variable registers"),
    V850_REG_INFO("R28", 28, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[28]), "Address/data variable registers"),
    V850_REG_INFO("R29", 29, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[29]), "Address/data variable registers"),
    V850_REG_INFO("R30", 30, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[30]), "Element pointer (EP)"),
    V850_REG_INFO("R31", 31, vmi_REG_LR,   V850_GPR_BITS, &groups[V850_RG_USER], V850_REG_RAWRW(gpr[31]), "Link pointer (LP)"),

    // KEEP LAST: structure terminator
    {0}
};

static const vmiRegInfo null_sprRegisters[] = {
    V850_REG_INFO("_UNIMPLEMENTED_", 0, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), "_UNIMPLEMENTED_")
};

static const vmiRegInfo V850_sprRegisters[] = {
    /* V850  System Registers */
    V850_REG_INFO("EIPC",  32, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIPC),  "Interrupt status-saving register PC"),
    V850_REG_INFO("EIPSW", 33, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIPSW), "Interrupt status-saving register PSW"),
    V850_REG_INFO("FEPC",  34, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEPC),  "NMI status-saving register PC"),
    V850_REG_INFO("FEPSW", 35, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEPSW), "NMI status-saving register PSW"),
    V850_REG_INFO("ECR",   36, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readECR, writeECR), "Exception cause register"),
    V850_REG_INFO("PSW",   37, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readPSW, writePSW), "Program status word"),
    // gap
    V850_REG_INFO("PC",    64, vmi_REG_PC,   V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readPC, writePC), "Program Counter"),
    V850_REG_INFO("FP",    65, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(gpr[0]), 0),

    // KEEP LAST: structure terminator
    {0}
};

static const vmiRegInfo V850E1_sprRegisters[] = {
    /* V850E  System Registers */
    V850_REG_INFO("EIPC",  32, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIPC),  "Interrupt status-saving register PC"),
    V850_REG_INFO("EIPSW", 33, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIPSW), "Interrupt status-saving register PSW"),
    V850_REG_INFO("FEPC",  34, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEPC),  "NMI status-saving register PC"),
    V850_REG_INFO("FEPSW", 35, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEPSW), "NMI status-saving register PSW"),
    V850_REG_INFO("ECR",   36, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readECR, writeECR), "Exception cause register"),
    V850_REG_INFO("PSW",   37, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readPSW, writePSW), "Program status word"),
    // gap
    V850_REG_INFO("CTPC",  48, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTPC),  "CALLT status-saving register PC"),
    V850_REG_INFO("CTPSW", 49, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTPSW), "CALLT status-saving register PSW"),
    V850_REG_INFO("DBPC",  50, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_DBPC),  "Exception/Debug trap status-saving register PC"),
    V850_REG_INFO("DBPSW", 51, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_DBPSW), "Exception/Debug trap status-saving register PSW"),
    V850_REG_INFO("CTBP",  52, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTBP),  "CALLT base pointer"),
    V850_REG_INFO("DIR",   53, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_DIR),   "Debug Interface register"),
    // gap
    V850_REG_INFO("PC",    64, vmi_REG_PC,   V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readPC, writePC), "Program Counter"),
    V850_REG_INFO("FP",    65, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(gpr[0]), 0),

    // KEEP LAST: structure terminator
    {0}
};

static const vmiRegInfo V850E1F_sprRegisters[] = {
    /* V850E  System Registers */
    V850_REG_INFO("EIPC",  32, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIPC),  "Interrupt status-saving register PC"),
    V850_REG_INFO("EIPSW", 33, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIPSW), "Interrupt status-saving register PSW"),
    V850_REG_INFO("FEPC",  34, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEPC),  "NMI status-saving register PC"),
    V850_REG_INFO("FEPSW", 35, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEPSW), "NMI status-saving register PSW"),
    V850_REG_INFO("ECR",   36, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readECR, writeECR), "Exception cause register"),
    V850_REG_INFO("PSW",   37, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readPSW, writePSW), "Program status word"),
    // gap
    V850_REG_INFO("CTPC",  48, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTPC),  "CALLT status-saving register PC"),
    V850_REG_INFO("CTPSW", 49, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTPSW), "CALLT status-saving register PSW"),
    V850_REG_INFO("DBPC",  50, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_DBPC),  "Exception/Debug trap status-saving register PC"),
    V850_REG_INFO("DBPSW", 51, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_DBPSW), "Exception/Debug trap status-saving register PSW"),
    V850_REG_INFO("CTBP",  52, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTBP),  "CALLT base pointer"),
    V850_REG_INFO("DIR",   53, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_DIR),   "Debug Interface register"),
    // gap
    V850_REG_INFO("PC",    64, vmi_REG_PC,   V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readPC, writePC), "Program Counter"),
    V850_REG_INFO("FP",    65, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(gpr[0]), 0),

   // Not accessible from GDB, but required for SAVE/RESTORE
    V850_REG_INFO("EFG",  100, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readEFG, writeEFG), "EFG Register"),

    // KEEP LAST: structure terminator
    {0}
};

static const vmiRegInfo V850E2_sprRegisters[] = {
    /* V850E2  System Registers */
    V850_REG_INFO("EIPC",  32, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIPC),  "Interrupt status-saving register PC"),
    V850_REG_INFO("EIPSW", 33, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIPSW), "Interrupt status-saving register PSW"),
    V850_REG_INFO("FEPC",  34, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEPC),  "NMI status-saving register PC"),
    V850_REG_INFO("FEPSW", 35, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEPSW), "NMI status-saving register PSW"),
    V850_REG_INFO("ECR",   36, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readECR, writeECR), "Exception cause register"),
    V850_REG_INFO("PSW",   37, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readPSW, writePSW), "Program status word"),
    V850_REG_INFO("PID",   38, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO),    "_UNIMPLEMENTED_"),
    V850_REG_INFO("CFG",   39, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO),    "_UNIMPLEMENTED_"),
    // gap
    V850_REG_INFO("SCCFG", 43, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO("SCBP",  44, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO),   "_UNIMPLEMENTED_"),
//    V850_REG_INFO("EIIC",  45, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readEIIC, writeEIIC), "EI Cause Register"),
//    V850_REG_INFO("FEIC",  46, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readFEIC, writeFEIC), "FE Cause Register"),
    V850_REG_INFO("EIIC",  45, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIIC), "EI Cause Register"),
    V850_REG_INFO("FEIC",  46, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEIC), "FE Cause Register"),
    V850_REG_INFO("DBIC",  47, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_DBIC),  "DB Cause Register"),
    V850_REG_INFO("CTPC",  48, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTPC),  "CALLT status-saving register PC"),
    V850_REG_INFO("CTPSW", 49, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTPSW), "CALLT status-saving register PSW"),
    V850_REG_INFO("DBPC",  50, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_DBPC),  "Exception/Debug trap status-saving register PC"),
    V850_REG_INFO("DBPSW", 51, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_DBPSW), "Exception/Debug trap status-saving register PSW"),
    V850_REG_INFO("CTBP",  52, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTBP),  "CALLT base pointer"),
    V850_REG_INFO("DIR",   53, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_DIR),   "Debug Interface register"),
    // gap
    V850_REG_INFO("EIWR",  60, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIWR),  "EIWR"),
    V850_REG_INFO("FEWR",  61, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEWR),  "FEWR"),
    V850_REG_INFO("DBWR",  62, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_DBWR),  "DBWR"),
    V850_REG_INFO("BSEL",  63, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_BSEL, writeBSEL), "Bank Select Register"),
    V850_REG_INFO("PC",    64, vmi_REG_PC,   V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readPC, writePC), "Program Counter"),

    /* MP Violation */
    V850_REG_INFO("FPVIP",  66, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    // gap
    V850_REG_INFO("VMECR",  70, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("VMTID",  71, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("VMADR",  72, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    // gap
    V850_REG_INFO("VPECR",  74, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("VPTID",  75, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("VPADR",  76, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    // gap
    V850_REG_INFO("VDECR",  78, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("VDTID",  79, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    // gap

    /* MP Setting */
    V850_REG_INFO("MPM",    94, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("MPC",    95, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("TID",    96, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("PPA",    97, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("PPM",    98, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("PPC",    99, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("DCC",   100, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("DCV0",  101, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("DCV1",  102, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    // gap
    V850_REG_INFO("SPAL",  104, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("SPAU",  105, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("IPA0L", 106, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("IPA0U", 107, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("IPA1L", 108, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("IPA1U", 109, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("IPA2L", 110, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("IPA2U", 111, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("IPA3L", 112, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("IPA3U", 113, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("DPA0L", 114, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("DPA0U", 115, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("DPA1L", 116, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("DPA1U", 117, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("DPA2L", 118, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("DPA2U", 119, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("DPA3L", 120, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    V850_REG_INFO("DPA3U", 121, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR (padZERO), 0),
    // gap

    /* FPU system registers.  */
    // MPV 66+28 = 94
    // MPU 94+28 = 122
    V850_REG_INFO("FPSR",  122+6,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readFPSR,  writeFPSR),  "Floating-point configuration/status"),
    V850_REG_INFO("FPEPC", 122+7,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FPEPC),            "Floating-point exception program counter"),
    V850_REG_INFO("FPST",  122+8,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readFPST,  writeFPST),  "Floating-point status"),
    V850_REG_INFO("FPCC",  122+9,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readFPCC,  writeFPCC),  "Floating-point comparison result"),
    V850_REG_INFO("FPCFG", 122+10, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readFPCFG, writeFPCFG), "Floating-point configuration"),

    // gap

    // KEEP LAST: structure terminator
    {0}
};

static const vmiRegInfo RH850G3M_sprRegisters[] = {
    /* RH850G3M  System Registers */
    // SELID=0
    V850_REG_INFO("EIPC",  32+0,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIPC),  "Interrupt status-saving register PC"),
    V850_REG_INFO("EIPSW", 32+1,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIPSW), "Interrupt status-saving register PSW"),
    V850_REG_INFO("FEPC",  32+2,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEPC),  "NMI status-saving register PC"),
    V850_REG_INFO("FEPSW", 32+3,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEPSW), "NMI status-saving register PSW"),
    // gap
    V850_REG_INFO("PSW",   32+5,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readPSW, writePSW), "Program status word"),
    // gap
//    V850_REG_INFO("EIIC",  32+13, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readEIIC, writeEIIC),  "EI level Cause Register"),
//    V850_REG_INFO("FEIC",  32+14, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readFEIC, writeFEIC),  "FE level Cause Register"),
    V850_REG_INFO("EIIC",  32+13, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIIC),  "EI level Cause Register"),
    V850_REG_INFO("FEIC",  32+14, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEIC),  "FE level Cause Register"),
    // gap
    V850_REG_INFO("CTPC",  32+16, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTPC),  "CALLT status-saving register PC"),
    V850_REG_INFO("CTPSW", 32+17, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTPSW), "CALLT status-saving register PSW"),
    // gap
    V850_REG_INFO("CTBP",  32+20, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_CTBP),  "CALLT base pointer"),
    // gap
    V850_REG_INFO("EIWR",  32+28, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_EIWR),  "EI level exception working register"),
    V850_REG_INFO("FEWR",  32+29, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FEWR),  "FE level exception working register"),
    // gap
    V850_REG_INFO("BSEL",  32+31, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_BSEL, writeBSEL), "Bank Select Register (Backward compatibility)"),
    V850_REG_INFO("PC",    32+32, vmi_REG_PC,   V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readPC, writePC), "Program Counter"),
    // gap

    // MPV 66+28 = 94
    // MPU 94+28 = 122
    V850_REG_INFO("FPSR",  122+6,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readFPSR,  writeFPSR),  "Floating-point configuration/status"),
    V850_REG_INFO("FPEPC", 122+7,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_FPEPC),            "Floating-point exception program counter"),
    V850_REG_INFO("FPST",  122+8,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readFPST,  writeFPST),  "Floating-point status"),
    V850_REG_INFO("FPCC",  122+9,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readFPCC,  writeFPCC),  "Floating-point comparison result"),
    V850_REG_INFO("FPCFG", 122+10, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readFPCFG, writeFPCFG), "Floating-point configuration"),
    V850_REG_INFO("FPEC",  122+11, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBRW(readFPEC,  writeFPEC),  "Floating-point exception control"),


    // SELID=1 : 122+28 = 150
    V850_REG_INFO("MCFG0", 150+0,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_MCFG0), "Machine Configuration"),
    V850_REG_INFO("RBASE", 150+2,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_RBASE), "Reset vector base address"),
    V850_REG_INFO("EBASE", 150+3,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_EBASE), "Exception handler vector address"),
    V850_REG_INFO("INTBP", 150+4,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_INTBP), "Base address of the interrupt handler table"),
    V850_REG_INFO("MCTL",  150+5,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_MCTL),  "CPU control"),
    V850_REG_INFO("PID",   150+6,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_PID),   "Processor ID"),
    V850_REG_INFO("FPIPR", 150+7,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_FPIPR), "FPI exception interrupt priority setting"),
    V850_REG_INFO("SCCFG", 150+11, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_SCCFG), "SYSCALL operation setting"),
    V850_REG_INFO("SCBP",  150+12, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_SCBP),  "SYSCALL base pointer"),

    // SELID=2 : 150+32 = 182
    V850_REG_INFO("HTCFG0", 182+0,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_HTCFG0), "Thread configuration"),
    V850_REG_INFO("MEA",    182+6,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_MEA),    "Memory error address"),
    V850_REG_INFO("ASID",   182+7,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_ASID),   "Address space ID"),
    V850_REG_INFO("MEI",    182+8,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_MEI),    "Memory error information"),
    V850_REG_INFO("ISPR",   182+9,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_ISPR),   "Priority of interrupt being serviced"),
    V850_REG_INFO("PMR",    182+10, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_PMR),    "Interrupt priority masking"),
    V850_REG_INFO("ICSR",   182+11, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_ICSR),   "Interrupt control status"),
    V850_REG_INFO("INTCFG", 182+12, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR(SPR_INTCFG), "Interrupt function setting"),

    // SELID=3 182+32 = 214

    // SELID=4 : 214+32 = 246
    V850_REG_INFO("ICTAGL", 246+16, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_ICTAGL), "Instruction cache tag Lo access"),
    V850_REG_INFO("ICTAGH", 246+17, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_ICTAGH), "Instruction cache tag Hi access"),
    V850_REG_INFO("ICDATL", 246+18, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_ICDATL), "Instruction cache data Lo access"),
    V850_REG_INFO("ICDATH", 246+19, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_ICDATH), "Instruction cache data Hi access"),
    V850_REG_INFO("ICCTRL", 246+24, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_ICCTRL), "Instruction cache control"),
    V850_REG_INFO("ICCFG",  246+26, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_ICCFG),  "Instruction cache configuration"),
    V850_REG_INFO("ICERR",  246+28, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_ICERR),  "Instruction cache error"),

    // SELID=5 : 246+32 = 310
    V850_REG_INFO("MPM",    278+0,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_MPM),    "Memory protection operation mode setting"),
    V850_REG_INFO("MPRC",   278+1,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_MPRC),   "MPU region control"),
    V850_REG_INFO("MPBRGN", 278+4,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_MPBRGN), "MPU base region number"),
    V850_REG_INFO("MPTRGN", 278+5,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_MPTRGN), "MPU end region number"),
    V850_REG_INFO("MCA",    278+8,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_MCA),    "Memory protection setting check address"),
    V850_REG_INFO("MCS",    278+9,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_MCS),    "Memory protection setting check size"),
    V850_REG_INFO("MCC",    278+10, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_MCC),    "Memory protection setting check command"),
    V850_REG_INFO("MCR",    278+11, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWRW(SPR_MCR),    "Memory protection setting check result"),

    // SELID=6 : 278+32 = 310
    V850_REG_INFO("MPLA0",  310+0,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[0], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA0",  310+1,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[0], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT0",  310+2,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[0], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA1",  310+4,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[1], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA1",  310+5,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[1], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT1",  310+6,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[1], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA2",  310+8,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[2], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA2",  310+9,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[2], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT2",  310+10,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[2], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA3",  310+12,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[3], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA3",  310+13,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[3], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT3",  310+14,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[3], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA4",  310+16,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[4], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA4",  310+17,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[4], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT4",  310+18,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[4], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA5",  310+20,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[5], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA5",  310+21,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[5], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT5",  310+22,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[5], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA6",  310+24,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[6], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA6",  310+25,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[6], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT6",  310+26,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[6], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA7",  310+28,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[7], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA7",  310+29,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[7], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT7",  310+30,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[7], writeMPL), "Protection area attribute"),

    // SELID=7 : 310+32 = 342
    V850_REG_INFO("MPLA8",  342+0,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[8],  writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA8",  342+1,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[8],  writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT8",  342+2,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[8],  writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA9",  342+4,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[9],  writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA9",  342+5,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[9],  writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT9",  342+6,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[9],  writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA10", 342+8,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[10], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA10", 342+9,   vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[10], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT10", 342+10,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[10], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA11", 342+12,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[11], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA11", 342+13,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[11], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT11", 342+14,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[11], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA12", 342+16,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[12], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA12", 342+17,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[12], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT12", 342+18,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[12], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA13", 342+20,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[13], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA13", 342+21,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[13], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT13", 342+22,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[13], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA14", 342+24,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[14], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA14", 342+25,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[14], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT14", 342+26,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[14], writeMPL), "Protection area attribute"),
    V850_REG_INFO("MPLA15", 342+28,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPLA[15], writeMPL), "Protection area minimum address"),
    V850_REG_INFO("MPUA15", 342+29,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPUA[15], writeMPL), "Protection area maximum address"),
    V850_REG_INFO("MPAT15", 342+30,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_RAWR_CBW(SPR_MPAT[15], writeMPL), "Protection area attribute"),

    // SELID=13 :
    //V850_REG_INFO("CDBCR",  418+24,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_REG_CBR(padZERO), "Data buffer control register"),

    // KEEP LAST: structure terminator
    {0}
};

static const vmiRegInfo supportRegisters[] = {
    /* Support Registers */
    V850_REG_INFO_QUIET("stop",      SUPPORT_REGS+0, vmi_REG_NONE, 32, &groups[V850_RG_INTEGRATION], V850_REG_CBRW(readStop, writeStop),         "Support Register for Stopping Processor"),
    V850_REG_INFO_QUIET("ResultHi",  SUPPORT_REGS+1, vmi_REG_NONE, 32, &groups[V850_RG_INTEGRATION], V850_REG_RAWRW(ResultHi),                   "External ResultHi Register"),
    V850_REG_INFO_QUIET("ResultLo",  SUPPORT_REGS+2, vmi_REG_NONE, 32, &groups[V850_RG_INTEGRATION], V850_REG_RAWRW(ResultLo),                   "External ResultLo Register"),
    V850_REG_INFO_QUIET("ResultSz",  SUPPORT_REGS+3, vmi_REG_NONE,  8, &groups[V850_RG_INTEGRATION], V850_REG_RAWRW(ResultSz),                   "External ResultSz Register"),
    V850_REG_INFO_QUIET("ResultId",  SUPPORT_REGS+4, vmi_REG_NONE,  8, &groups[V850_RG_INTEGRATION], V850_REG_CBRW(readResultId, writeResultId), "External ResultId Register"),
    V850_REG_INFO_QUIET("ResultFlg", SUPPORT_REGS+5, vmi_REG_NONE, 32, &groups[V850_RG_INTEGRATION], V850_REG_RAWRW(ResultFlg),                  "External ResultFlg Register"),
    V850_REG_INFO_QUIET("ResultCC",  SUPPORT_REGS+6, vmi_REG_NONE, 32, &groups[V850_RG_INTEGRATION], V850_REG_CBRW(readResultCC, writeResultCC), "External ResultCC Register"),

    // Not archicturally visible
    V850_REG_INFO("FLG_LL",          SUPPORT_REGS+7, vmi_REG_NONE,  8, &groups[V850_RG_INTEGRATION], V850_REG_RAWRW(FLG_LL),                      "Load/Store Exclusive FLG_LL"),

    // KEEP LAST: structure terminator
    {0}
};

VMI_REG_GROUP_FN(v850RegGroup) {
    return getNextGroup(prev);
}

inline static void copyRegister(vmiRegInfoP dst, vmiRegInfoCP src) {
    *dst = *src;
}

//
// Is the passed register supported on this processor?
//
static Bool isRegSupported(v850P v850, vmiRegInfoCP reg) {
//    v850RegSet regset  = reg->set;
//    v850RegSet archset = getRegSet(v850->configInfo.arch);
//
//    if (regset & archset) {
//        return True;
//    } else {
//        return False;
//    }
    return True;
}

//
// Return next vmiRegInfoCP structure for a basic register

static vmiRegInfoCP getNextReg(v850P v850, vmiRegInfoCP prev, const vmiRegInfo *reglist) {
    vmiRegInfoCP reg = prev ? prev+1 : reglist;
    return reg->name ? reg : 0;
}

static Uns32 numRegisters(v850P v850, vmiRegInfoCP regList, Bool Frame) {
    vmiRegInfoCP reg   = 0;
    Uns32        num   = 0;
    Int32        first = -1;
    Int32        last  = 0;

    // count GPR registers
    while((reg=getNextReg(v850, reg, regList))) {
        last = reg->gdbIndex;
        if (num==0) {
            first = reg->gdbIndex;
        }
        num++;
    }

    //
    // Actual number of registers, or frame registers for gdb 'g' packet
    //
    Int32 total;
    if (Frame) {
        total = 1 + last - first;
    } else {
        total = num;
    }

    // vmiPrintf("GDB range %d -> %d = %d\n", first, last, total);
    return total;
}

//
// Return V850 register descriptions
//
static vmiRegInfoCP getRegisters(v850P v850) {
    if(!v850->regInfoVariant) {
        Uns32 rnum;
        rnum = numRegisters(v850, gprRegisters, 0);

        vmiRegInfoCP sysRegisters = 0;
        if (v850->configInfo.arch == V850) {
            sysRegisters = V850_sprRegisters;

        } else if (v850->configInfo.arch == V850E1) {
            sysRegisters = V850E1_sprRegisters;

        } else if (v850->configInfo.arch == V850E1F) {
            sysRegisters = V850E1F_sprRegisters; // NOTE Includes inaccessible registers (gdb) EFG, ECT

        } else if (v850->configInfo.arch == V850ES) {
            sysRegisters = V850E1_sprRegisters;

        } else if (v850->configInfo.arch == V850E2) {
            sysRegisters = V850E2_sprRegisters;

        } else if (v850->configInfo.arch == V850E2M) {
            sysRegisters = V850E2_sprRegisters;

        } else if (v850->configInfo.arch == V850E2R) {
            sysRegisters = V850E2_sprRegisters;

        } else if (v850->configInfo.arch == RH850G3M) {
            sysRegisters = RH850G3M_sprRegisters;
        }

        rnum += numRegisters(v850, sysRegisters,     0);
        rnum += numRegisters(v850, supportRegisters, 0);

        v850->regInfoVariant = STYPE_CALLOC_N(vmiRegInfo, rnum+1);

        //
        // Now assign registers
        //
        Uns32 i = 0;
        vmiRegInfoCP reg = 0;
        while((reg=getNextReg(v850, reg, gprRegisters))) {
            copyRegister(&v850->regInfoVariant[i++], reg);
        }
        reg = 0;
        while((reg=getNextReg(v850, reg, sysRegisters))) {
            copyRegister(&v850->regInfoVariant[i++], reg);
        }
        reg = 0;
        while((reg=getNextReg(v850, reg, supportRegisters))) {
            copyRegister(&v850->regInfoVariant[i++], reg);
        }
    }

    return v850->regInfoVariant;
}


static vmiRegInfoCP getFrameRegisters(v850P v850) {
    if(!v850->regInfoFrame) {
        Uns32 rnum;
        rnum = numRegisters(v850, gprRegisters, 1);

        vmiRegInfoCP sysRegisters = 0;
        if (v850->configInfo.arch == V850) {
            sysRegisters = V850_sprRegisters;

        } else if (v850->configInfo.arch == V850E1) {
            sysRegisters = V850E1_sprRegisters;

        } else if (v850->configInfo.arch == V850E1F) {
            sysRegisters = V850E1_sprRegisters;

        } else if (v850->configInfo.arch == V850ES) {
            sysRegisters = V850E1_sprRegisters;

        } else if (v850->configInfo.arch == V850E2) {
            sysRegisters = V850E2_sprRegisters;

        } else if (v850->configInfo.arch == V850E2M) {
            sysRegisters = V850E2_sprRegisters;

        } else if (v850->configInfo.arch == V850E2R) {
            sysRegisters = V850E2_sprRegisters;

        } else if (v850->configInfo.arch == RH850G3M) {
            sysRegisters = RH850G3M_sprRegisters;
        }

        rnum += numRegisters(v850, sysRegisters, 1);

        v850->regInfoFrame = STYPE_CALLOC_N(vmiRegInfo, rnum+1);

        //
        // Point to null register
        //
        Uns32 i;
        vmiRegInfoCP reg = 0;
        reg = getNextReg(v850, reg, null_sprRegisters);
        for(i=0; i<rnum; i++) {
            copyRegister(&v850->regInfoFrame[i], reg);
        }

        //
        // Now assign real gdb registers
        //
        reg = 0;
        while((reg=getNextReg(v850, reg, gprRegisters))) {
            Uns32 gdbIndex = reg->gdbIndex;
            copyRegister(&v850->regInfoFrame[gdbIndex], reg);
        }
        reg = 0;
        while((reg=getNextReg(v850, reg, sysRegisters))) {
            Uns32 gdbIndex = reg->gdbIndex;
            copyRegister(&v850->regInfoFrame[gdbIndex], reg);
        }
    }

    return v850->regInfoFrame;
}

static vmiRegInfoCP getNextRegister(v850P v850, vmiRegInfoCP reg) {
    do {
        if(!reg) {
            reg = getRegisters(v850);
        } else if((reg+1)->name) {
            reg = reg+1;
        } else {
            reg = 0;
        }
    } while (reg && !isRegSupported(v850, reg));

    return reg;
}

static vmiRegInfoCP getNextFrameRegister(v850P v850, vmiRegInfoCP reg) {
    if(!reg) {
        reg = getFrameRegisters(v850);
    } else if((reg+1)->name) {
        return reg+1;
    } else {
        return 0;
    }
    return reg;
}

VMI_REG_INFO_FN(v850RegInfo) {
    v850P v850 = (v850P)processor;

    if(gdbFrame==VMIRIT_GPACKET) {
        return getNextFrameRegister(v850, prev);
    }else {
        return getNextRegister(v850, prev);
    }
}

//
// Helper macro for defining register implementations
//
#define V850_REG_IMPL_RAW(_REG, _FIELD, _BITS) \
    vmirtRegImplRaw(processor, _REG, _FIELD, _BITS)

//
// Helper macro for defining field-to register mappings
//
#define V850_FIELD_IMPL_RAW(_REGINFO, _FIELD) { \
    Uns32 bits = sizeof(((v850P)0)->_FIELD) * 8;                \
    V850_REG_IMPL_RAW(_REGINFO, V850_CPU_REG(_FIELD), bits);    \
}

//
// Helper macro for defining field-to register mappings
//
#define V850_MASK_EXCLUDE(_REG) \
    V850_FIELD_IMPL_RAW(0, _REG##_rmask); \
    V850_FIELD_IMPL_RAW(0, _REG##_wmask)

//
// Specify vmiReg-to-vmiRegInfoCP correspondence for registers for which this
// cannot be automatically derived
//
VMI_REG_IMPL_FN(v850RegImpl) {

    ////////////////////////////////////////////////////////////////////////////
    // SPECIFY REGISTER IMPLEMENTATIONS THAT CANNOT BE AUTOMATICALLY INFERRED
    ////////////////////////////////////////////////////////////////////////////

    // specify flag registers in the PSW
    vmiRegInfoCP PSW = vmirtGetRegByName(processor, "PSW");
    V850_FIELD_IMPL_RAW(PSW, FLG_PSW_ZR);
    V850_FIELD_IMPL_RAW(PSW, FLG_PSW_SI);
    V850_FIELD_IMPL_RAW(PSW, FLG_PSW_OV);
    V850_FIELD_IMPL_RAW(PSW, FLG_PSW_CO);
    V850_FIELD_IMPL_RAW(PSW, FLG_PSW_SAT);
    V850_FIELD_IMPL_RAW(PSW, FLG_PSW_ID);
    V850_FIELD_IMPL_RAW(PSW, FLG_PSW_EP);
    V850_FIELD_IMPL_RAW(PSW, FLG_PSW_NP);

    // specify flag registers in the FPSR
    vmiRegInfoCP FPSR = vmirtGetRegByName(processor, "FPSR");
    V850_FIELD_IMPL_RAW(FPSR, FLG_FPSR_CC);
    V850_FIELD_IMPL_RAW(FPSR, FLG_FPF);
    V850_FIELD_IMPL_RAW(FPSR, FLG_FPF_STICKY);

    // specify fields in SPR_EFG
    // TODO: this register does not seem to exist!
    vmiRegInfoCP SPR_EFG = vmirtGetRegByName(processor, "SPR_EFG");
    V850_FIELD_IMPL_RAW(SPR_EFG, FLG_EFG_FPZ);
    V850_FIELD_IMPL_RAW(SPR_EFG, FLG_EFG_FPS);
    V850_FIELD_IMPL_RAW(SPR_EFG, FLG_EFG_FPOV);
    if(!SPR_EFG) {V850_FIELD_IMPL_RAW(0, SPR_EFG)}

    // specify fields in SPR_ECT
    // TODO: this register does not seem to exist!
    vmiRegInfoCP SPR_ECT = vmirtGetRegByName(processor, "SPR_ECT");
    V850_FIELD_IMPL_RAW(SPR_ECT, SPR_ECT);
    if(!SPR_ECT) {V850_FIELD_IMPL_RAW(0, SPR_ECT)}

    // specify fields in ECR
    vmiRegInfoCP ECR = vmirtGetRegByName(processor, "ECR");
    V850_FIELD_IMPL_RAW(ECR, SPR_EIIC);

    ////////////////////////////////////////////////////////////////////////////
    // SPECIFY EXCLUDED REGISTERS
    ////////////////////////////////////////////////////////////////////////////

    // ignore artifact mask registers
    V850_MASK_EXCLUDE(SPR_EFG);
    V850_MASK_EXCLUDE(SPR_ECT);
}

VMI_DEBUG_FN(v850Debug) {
    v850P v850 = (v850P)processor;
    Int32 iter;

    vmiPrintf("-----------------  -----------------  -----------------  -----------------\n");

    for (iter=0; iter<32; iter++) {
        vmiPrintf(" R%-5u: %08x", iter, v850->gpr[iter]);
        if(!((iter+1)&3)) {
            vmiPrintf("\n");
        } else {
            vmiPrintf("  ");
        }
    }

    // newline if required before derived registers
    if(iter&3) {
        vmiPrintf("\n");
    }

    vmiPrintf(" EIPC  : %08x  ", v850->SPR_EIPC.reg);
    vmiPrintf(" EIPSW : %08x  ", v850->SPR_EIPSW.reg);
    vmiPrintf(" FEPC  : %08x  ", v850->SPR_FEPC.reg);
    vmiPrintf(" FEPSW : %08x\n", v850->SPR_FEPSW.reg);

    v850PackECR(v850);
    vmiPrintf(" ECR   : %08x  ", v850->SPR_ECR.reg);

    v850PackPSW(v850);
    vmiPrintf(" PSW   : %08x",   v850->SPR_PSW.reg);

    if (v850->configInfo.arch == V850E1F) {
        vmiPrintf("  ");
        v850PackEFG(v850);
        vmiPrintf(" EFG   : %08x  ", v850->SPR_EFG.reg);
        vmiPrintf(" ECT   : %08x  ", v850->SPR_ECT.reg);
    }
    if (v850->configInfo.arch & ISA_E2) {
        v850PackFPSR(v850);
        v850PackFPST(v850);
        v850PackFPCC(v850);
        v850PackFPCFG(v850);
        vmiPrintf("  ");
        vmiPrintf(" FPSR  : %08x  ", v850->SPR_FPSR.reg);
        vmiPrintf(" FPST  : %08x  ", v850->SPR_FPST.reg);
        vmiPrintf("\n");
        vmiPrintf(" FPCC  : %08x  ", v850->SPR_FPCC.reg);
        vmiPrintf(" FPCFG : %08x  ", v850->SPR_FPCFG.reg);
        vmiPrintf(" BSEL  : %08x  ", v850->SPR_BSEL.reg);

    }

    vmiPrintf("\n");

    vmiPrintf(" PC    : %08x", (v850Addr)vmirtGetPC(processor));

    vmiPrintf("\n-----------------  -----------------  -----------------  -----------------\n\n");
}


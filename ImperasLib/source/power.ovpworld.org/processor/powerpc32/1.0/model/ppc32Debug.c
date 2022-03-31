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

#include "vmi/vmiAttrs.h"
#include "vmi/vmiDbg.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "ppc32Structure.h"
#include "ppc32Functions.h"
#include "ppc32Utils.h"
#include "ppc32SPR.h"

#define PPC32_RAW_REG_RW(_R) \
    VMI_REG_RAW_READ_CB, \
    VMI_REG_RAW_WRITE_CB, \
    (void *)PPC32_CPU_OFFSET(_R)

#define PPC32_RAW_REG_R(_R) \
    VMI_REG_RAW_READ_CB, \
    0, \
    (void *)PPC32_CPU_OFFSET(_R)

static VMI_REG_READ_FN(readPC) {
    *(ppc32Addr*)buffer = (Uns32)vmirtGetPC(processor);
    return True;
}
static VMI_REG_WRITE_FN(writePC) {
    vmirtSetPC(processor, *(ppc32Addr*)buffer);
    return True;
}

static VMI_REG_READ_FN(readMSR) {
    *(ppc32Addr*)buffer = (Uns32)ppc32ReadMSR((ppc32P)processor);
    return True;
}
static VMI_REG_WRITE_FN(writeMSR) {
    ppc32WriteMSR((ppc32P)processor, (Uns32)*(ppc32Addr*)buffer);
    return True;
}

static VMI_REG_READ_FN(readCR) {
    ppc32PackCR((ppc32P)processor);
    *(ppc32Addr*)buffer = ((ppc32P)processor)->CR.reg;
    return True;
}
static VMI_REG_WRITE_FN(writeCR) {
    ((ppc32P)processor)->CR.reg = (Uns32)*(ppc32Addr*)buffer;
    ppc32UnpackCR((ppc32P)processor);
    return True;
}

static VMI_REG_READ_FN(readLR) {
    *(ppc32Addr*)buffer = (Uns32)ppc32ReadSPR((ppc32P)processor, 8);
    return True;
}
static VMI_REG_WRITE_FN(writeLR) {
    ppc32WriteSPR((ppc32P)processor, 8, (Uns32)*(ppc32Addr*)buffer);
    return True;
}

static VMI_REG_READ_FN(readCTR) {
    *(ppc32Addr*)buffer = (Uns32)ppc32ReadSPR((ppc32P)processor, 9);
    return True;
}
static VMI_REG_WRITE_FN(writeCTR) {
    ppc32WriteSPR((ppc32P)processor, 9, (Uns32)*(ppc32Addr*)buffer);
    return True;
}

static VMI_REG_READ_FN(readXER) {
    *(ppc32Addr*)buffer = (Uns32)ppc32ReadSPR((ppc32P)processor, 1);
    return True;
}
static VMI_REG_WRITE_FN(writeXER) {
    ppc32WriteSPR((ppc32P)processor, 1, (Uns32)*(ppc32Addr*)buffer);
    return True;
}

static VMI_REG_READ_FN(readFPSCR) {
    ppc32PackFPSCR((ppc32P)processor);
    //
    // Need to mask out bit FR - unsupported
    //
    TYPE_FPSCR fpscr = ((ppc32P)processor)->FPSCR;
    fpscr.bits.FR = 0;
    *(ppc32Addr*)buffer = fpscr.reg;
    return True;
}
static VMI_REG_WRITE_FN(writeFPSCR) {
    ((ppc32P)processor)->FPSCR.reg = (Uns32)*(ppc32Addr*)buffer;
    ppc32UnpackFPSCR((ppc32P)processor);
    return True;
}

typedef enum ppc32RegGroupIdE {
    PPC32_RG_USER,
    PPC32_RG_FP,
    PPC32_RG_SYSTEM,
    PPC32_RG_LAST
} ppc32RegGroupId;

static const vmiRegGroup groups[PPC32_RG_LAST+1] = {
    [PPC32_RG_USER]   = {name: "User"           },
    [PPC32_RG_FP]     = {name: "FloatingPoint"  },
    [PPC32_RG_SYSTEM] = {name: "System"         },
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


static const vmiRegInfo registers[] = {
    {name:"GPR0",   gdbIndex:0,   usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[0])},
    {name:"GPR1",   gdbIndex:1,   usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[1])},
    {name:"GPR2",   gdbIndex:2,   usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[2])},
    {name:"GPR3",   gdbIndex:3,   usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[3])},
    {name:"GPR4",   gdbIndex:4,   usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[4])},
    {name:"GPR5",   gdbIndex:5,   usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[5])},
    {name:"GPR6",   gdbIndex:6,   usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[6])},
    {name:"GPR7",   gdbIndex:7,   usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[7])},
    {name:"GPR8",   gdbIndex:8,   usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[8])},
    {name:"GPR9",   gdbIndex:9,   usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[9])},
    {name:"GPR10",  gdbIndex:10,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[10])},
    {name:"GPR11",  gdbIndex:11,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[11])},
    {name:"GPR12",  gdbIndex:12,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[12])},
    {name:"GPR13",  gdbIndex:13,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[13])},
    {name:"GPR14",  gdbIndex:14,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[14])},
    {name:"GPR15",  gdbIndex:15,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[15])},
    {name:"GPR16",  gdbIndex:16,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[16])},
    {name:"GPR17",  gdbIndex:17,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[17])},
    {name:"GPR18",  gdbIndex:18,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[18])},
    {name:"GPR19",  gdbIndex:19,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[19])},
    {name:"GPR20",  gdbIndex:20,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[20])},
    {name:"GPR21",  gdbIndex:21,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[21])},
    {name:"GPR22",  gdbIndex:22,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[22])},
    {name:"GPR23",  gdbIndex:23,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[23])},
    {name:"GPR24",  gdbIndex:24,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[24])},
    {name:"GPR25",  gdbIndex:25,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[25])},
    {name:"GPR26",  gdbIndex:26,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[26])},
    {name:"GPR27",  gdbIndex:27,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[27])},
    {name:"GPR28",  gdbIndex:28,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[28])},
    {name:"GPR29",  gdbIndex:29,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[29])},
    {name:"GPR30",  gdbIndex:30,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[30])},
    {name:"GPR31",  gdbIndex:31,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_USER], raw:PPC32_CPU_REG(GPR[31])},

    {name:"FPR0",   gdbIndex:32,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[0])},
    {name:"FPR1",   gdbIndex:33,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[1])},
    {name:"FPR2",   gdbIndex:34,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[2])},
    {name:"FPR3",   gdbIndex:35,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[3])},
    {name:"FPR4",   gdbIndex:36,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[4])},
    {name:"FPR5",   gdbIndex:37,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[5])},
    {name:"FPR6",   gdbIndex:38,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[6])},
    {name:"FPR7",   gdbIndex:39,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[7])},
    {name:"FPR8",   gdbIndex:40,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[8])},
    {name:"FPR9",   gdbIndex:41,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[9])},
    {name:"FPR10",  gdbIndex:42,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[10])},
    {name:"FPR11",  gdbIndex:43,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[11])},
    {name:"FPR12",  gdbIndex:44,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[12])},
    {name:"FPR13",  gdbIndex:45,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[13])},
    {name:"FPR14",  gdbIndex:46,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[14])},
    {name:"FPR15",  gdbIndex:47,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[15])},
    {name:"FPR16",  gdbIndex:48,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[16])},
    {name:"FPR17",  gdbIndex:49,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[17])},
    {name:"FPR18",  gdbIndex:50,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[18])},
    {name:"FPR19",  gdbIndex:51,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[19])},
    {name:"FPR20",  gdbIndex:52,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[20])},
    {name:"FPR21",  gdbIndex:53,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[21])},
    {name:"FPR22",  gdbIndex:54,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[22])},
    {name:"FPR23",  gdbIndex:55,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[23])},
    {name:"FPR24",  gdbIndex:56,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[24])},
    {name:"FPR25",  gdbIndex:57,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[25])},
    {name:"FPR26",  gdbIndex:58,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[26])},
    {name:"FPR27",  gdbIndex:59,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[27])},
    {name:"FPR28",  gdbIndex:60,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[28])},
    {name:"FPR29",  gdbIndex:61,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[29])},
    {name:"FPR30",  gdbIndex:62,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[30])},
    {name:"FPR31",  gdbIndex:63,  usage:vmi_REG_NONE, bits:64, access:vmi_RA_RW, group:&groups[PPC32_RG_FP],   raw:PPC32_CPU_REG(FPR[31])},

    /* Special PC */
    {name:"PC", gdbIndex:64, usage:vmi_REG_PC, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_SYSTEM], readCB:readPC, writeCB:writePC},

    /* State and Condition */
    {name:"MSR",  gdbIndex:65,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_SYSTEM], readCB:readMSR, writeCB:writeMSR},
    {name:"CR",   gdbIndex:66,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_SYSTEM], readCB:readCR,  writeCB:writeCR},
    {name:"LR",   gdbIndex:67,  usage:vmi_REG_LR,   bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_SYSTEM], readCB:readLR,  writeCB:writeLR},
    {name:"CTR",  gdbIndex:68,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_SYSTEM], readCB:readCTR, writeCB:writeCTR},
    {name:"XER",  gdbIndex:69,  usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_SYSTEM], readCB:readXER, writeCB:writeXER},

    /* Floating Point Status Register */
    {name:"FPSCR", gdbIndex:70, usage:vmi_REG_NONE, bits:32, access:vmi_RA_RW, group:&groups[PPC32_RG_SYSTEM], readCB:readFPSCR, writeCB:writeFPSCR},

    {0}
};

VMI_REG_GROUP_FN(ppc32RegGroup) {
    return getNextGroup(prev);
}

VMI_REG_INFO_FN(ppc32RegInfo) {
    if(!prev) {
        return registers;
    } else if((prev+1)->name) {
        return prev+1;
    } else {
        return 0;
    }
}

//
// Dump POWERPC32 registers original
//
VMI_DEBUG_FN(ppc32Debug) {

    ppc32P ppc32 = (ppc32P)processor;
    Uns32 i    = 0;
    ppc32PackRegs(ppc32);

    vmiPrintf("-----------------  -----------------  -----------------  -----------------\n");

    // print general-purpose registers
    while(i<32) {
        vmiPrintf(" R%-5u: %08x", i, ppc32->GPR[i]);
        i++;
        if(!(i&3)) {
            vmiPrintf("\n");
        } else {
            vmiPrintf("  ");
        }
    }
    // newline if required before derived registers
    if(i&3) {
        vmiPrintf("\n");
    }

    //
    // If the FP is available lets print the FPR Regs
    //
    if (ppc32->configInfo.arch & FEATURE_I_FP) {
        // print general-purpose registers
        i = 0;
        while(i<32) {
            vmiPrintf(" FPR%-3u: " FMT_640Nx, i, ppc32->FPR[i]);
            i++;
            if(!(i&3)) {
                vmiPrintf("\n");
            } else {
                vmiPrintf("  ");
            }
        }
        // newline if required before derived registers
        if(i&3) {
            vmiPrintf("\n");
        }
    }

    // program counter
    vmiPrintf(" PC    : %08x", (Uns32)vmirtGetPC(processor)); vmiPrintf("  ");

    // Other registers for gdb
    vmiPrintf(" MSR   : %08x", ppc32ReadMSR(ppc32));    vmiPrintf("  ");
    vmiPrintf(" CR    : %08x", (Uns32)ppc32->CR.reg);   vmiPrintf("  ");
    vmiPrintf(" LR    : %08x", ppc32ReadSPR(ppc32, 8)); vmiPrintf("\n");
    vmiPrintf(" CTR   : %08x", ppc32ReadSPR(ppc32, 9)); vmiPrintf("  ");
    vmiPrintf(" XER   : %08x", ppc32ReadSPR(ppc32, 1));

    if (ppc32->configInfo.arch & FEATURE_I_FP) {
        TYPE_FPSCR fpscr = ppc32->FPSCR;
        fpscr.bits.FR = 0; // mask unused bit
        vmiPrintf("   FPSCR : %08x", fpscr.reg);
    }

#define EXTRA_DEBUG 0
#if(EXTRA_DEBUG==1)
    vmiPrintf("\n");
    vmiPrintf(" CR0_LT=%d CR0_GT=%d CR0_EQ=%d CR0_SO=%d", ppc32->CR0_LT, ppc32->CR0_GT, ppc32->CR0_EQ, ppc32->CR0_SO);
    vmiPrintf("\n");
    vmiPrintf(" XER_SO=%d XER_OV=%d XER_CA=%d",           ppc32->XER_SO, ppc32->XER_OV, ppc32->XER_CA);
#endif

    vmiPrintf("\n-----------------  -----------------  -----------------  -----------------\n\n");
}

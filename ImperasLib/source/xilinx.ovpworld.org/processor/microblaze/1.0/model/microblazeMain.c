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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Imperas header files
#include "hostapi/impAlloc.h"

#include "vmi/vmiAttrs.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "microblazeBus.h"
#include "microblazePorts.h"
#include "microblazeStructure.h"
#include "microblazeInstructions.h"
#include "microblazeConfig.h"
#include "microblazeDoc.h"
#include "microblazeExceptions.h"
#include "microblazeParameters.h"
#include "microblazeMorphFP.h"
#include "microblazeTLB.h"
#include "microblazeUser.h"

//
// Return number of members of an array
//
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))

static Uns32 mbLog2 (Uns32 val) {
    Uns32 r = 0;
    while (val>1) {
        val>>=1;
        r++;
    }
    return r;
}

////////////////////////////////////////////////////////////////////////////////
// FIFO PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Allocate FIFO port structure
//
static vmiFifoPortP allocFSLports(microblazeP microblaze) {

    Uns32 fsl = microblaze->SPR_PVR3.FSL;
    fsl = 16;   // Always allocate 16

    // allocate permanent port structure (including terminator)
    vmiFifoPortP result = STYPE_CALLOC_N(vmiFifoPort, (fsl * 2) + 1);

    // fill permanent port structure
    Uns32 i;
    vmiFifoPortP   fslPort = result;

    //
    // Iterate and create the Slave Fifo Ports
    //
    for(i=0; i<fsl; i++) {
       char name[32];
       sprintf(name, "SFSL%d", i);
       fslPort->name = strdup(name);

       fslPort->bits = MICROBLAZE_FSL_BITS;
       fslPort->type = vmi_FIFO_INPUT;
       fslPort->handle = (void *)&microblaze->SFSL[i];
       fslPort->description = "FSL Fifo Input port - Controlled by Parameter C_FSL_LINKS";
       fslPort++;
    }
    //
    // Iterate and create the Master Fifo Ports
    //
    for(i=0; i<fsl; i++) {
       char name[32];
       sprintf(name, "MFSL%d",i);
       fslPort->name = strdup(name);
       fslPort->bits = MICROBLAZE_FSL_BITS;
       fslPort->type = vmi_FIFO_OUTPUT;
       fslPort->handle = (void *)&microblaze->MFSL[i];
       fslPort->description = "FSL Fifo Output port - Controlled by Parameter C_FSL_LINKS";
       fslPort++;
    }

    // always blank the last
    *fslPort = (vmiFifoPort){0};

    return result;
}

//
// Free FIFO port structure
//
static void freeFSLports(microblazeP microblaze, vmiFifoPortP fslPorts) {

    Uns32 fsl = microblaze->SPR_PVR3.FSL;
    fsl = 16;   // Always de-allocate 16

    // fill permanent port structure
    Uns32 i;
    vmiFifoPortP fslPort = fslPorts;

    //
    // Iterate and delete the Slave Fifo Ports
    //
    for(i=0; i<fsl; i++) {
        STYPE_FREE(fslPort->name);
        fslPort++;
    }
    //
    // Iterate and delete the Master Fifo Ports
    //
    for(i=0; i<fsl; i++) {
        STYPE_FREE(fslPort->name);
        fslPort++;
    }
    STYPE_FREE(fslPorts);
}

//
// Get the next fsl port, if enabled
//
VMI_FIFO_PORT_SPECS_FN(microblazeFifoPortSpecs) {

    microblazeP microblaze = (microblazeP)processor;

    if(!prev) {
        return microblaze->fslPorts;
    }

    prev++;

    if(prev->name) {
        return prev;
    }

    return 0;
}

static VMIRT_COMMAND_PARSE_FN(dumpTLB) {
    microblazeP microblaze = (microblazeP)processor;
    microblazePrintTLB(microblaze, True);
    return "1";
}

VMI_CONSTRUCTOR_FN(microblazeConstructor) {
    microblazeP microblaze = (microblazeP)processor;
    microblazeParamValuesP params = (microblazeParamValuesP)parameterValues;

    microblaze->flags = vmirtProcessorFlags(processor);
    microblaze->configInfo = microblazeConfigTable[params->variant];

    Int32 iter;
    for (iter=0; iter<32; iter++) {
        microblaze->gpr[iter] = 0;
    }

    microblaze->SPR_PVR0.reg    = 0; // readonly=0
    microblaze->SPR_PVR1.reg    = 0; // readonly=0
    microblaze->SPR_PVR2.reg    = 0; // readonly=0
    microblaze->SPR_PVR3.reg    = 0; // readonly=0
    microblaze->SPR_PVR4.reg    = 0; // readonly=0
    microblaze->SPR_PVR5.reg    = 0; // readonly=0
    microblaze->SPR_PVR6.reg    = 0; // readonly=0
    microblaze->SPR_PVR7.reg    = 0; // readonly=0
    microblaze->SPR_PVR8.reg    = 0; // readonly=0
    microblaze->SPR_PVR9.reg    = 0; // readonly=0
    microblaze->SPR_PVR10.reg   = 0; // readonly=0
    microblaze->SPR_PVR11.reg   = 0; // readonly=0
    for (iter=0; iter<4; iter++) {
        microblaze->tmp[iter]   = 0;
    }
    microblaze->FLG_tmp         = 0; // readonly=0
    microblaze->FLG_FP.bits     = 0;
    microblaze->FLG_DO          = 0;
    microblaze->disable         = 0;
    microblaze->iendian         = MEM_ENDIAN_BIG;
    microblaze->dendian         = MEM_ENDIAN_BIG;
    microblaze->exception       = microblaze_E_RESET;

    //
    // LWX/SWX reservation
    //
    microblaze->reservation        = 0; // readonly=0
    microblaze->reservation_addr   = 0; // readonly=0
    microblaze->reservation_length = 0; // readonly=0

    //
    // Store the parameters for later retrievel
    //
    microblaze->params.C_FAMILY                     = params->C_FAMILY;
    microblaze->params.C_AREA_OPTIMIZED             = params->C_AREA_OPTIMIZED;
    microblaze->params.C_INTERCONNECT               = params->C_INTERCONNECT;


    //
    // Setup Checks for illegal conditions
    //
    if (microblaze->configInfo.arch & ISA_V9_50) {
        if (params->C_ENDIANNESS==0 && params->C_ENDIANNESS__set) {
            vmiMessage("E", "Unsupported", "ISA V9.5 does not support Big-Endian C_ENDIANNESS==0");
        } else {
            //
            // Force new default
            //
            params->C_ENDIANNESS = 1;
        }
    }
    microblaze->params.C_ENDIANNESS                 = params->C_ENDIANNESS;
    microblaze->params.C_FAULT_TOLERANT             = params->C_FAULT_TOLERANT;
    microblaze->params.C_ECC_USE_CE_EXCEPTION       = params->C_ECC_USE_CE_EXCEPTION;
    microblaze->params.C_PVR                        = params->C_PVR;
    microblaze->params.C_PVR_USER1                  = params->C_PVR_USER1;
    microblaze->params.C_PVR_USER2                  = params->C_PVR_USER2;
    microblaze->params.C_RESET_MSR                  = params->C_RESET_MSR;
    microblaze->params.C_BASE_VECTORS               = params->C_BASE_VECTORS;
    microblaze->params.C_D_PLB                      = params->C_D_PLB;
    microblaze->params.C_D_AXI                      = params->C_D_AXI;
    microblaze->params.C_D_LMB                      = params->C_D_LMB;
    microblaze->params.C_I_PLB                      = params->C_I_PLB;
    microblaze->params.C_I_AXI                      = params->C_I_AXI;
    microblaze->params.C_I_LMB                      = params->C_I_LMB;
    microblaze->params.C_M_AXI_DP_EXCLUSIVE_ACCESS  = params->C_M_AXI_DP_EXCLUSIVE_ACCESS;
    microblaze->params.C_M_AXI_DC_EXCLUSIVE_ACCESS  = params->C_M_AXI_DC_EXCLUSIVE_ACCESS;
    microblaze->params.C_USE_BARREL                 = params->C_USE_BARREL;
    microblaze->params.C_USE_DIV                    = params->C_USE_DIV;
    microblaze->params.C_USE_HW_MUL                 = params->C_USE_HW_MUL;
    microblaze->params.C_USE_FPU                    = params->C_USE_FPU;
    microblaze->params.C_USE_MSR_INSTR              = params->C_USE_MSR_INSTR;
    microblaze->params.C_USE_PCMP_INSTR             = params->C_USE_PCMP_INSTR;
    microblaze->params.C_USE_REORDER_INSTR          = params->C_USE_REORDER_INSTR;
    microblaze->params.C_UNALIGNED_EXCEPTIONS       = params->C_UNALIGNED_EXCEPTIONS;
    microblaze->params.C_ILL_OPCODE_EXCEPTION       = params->C_ILL_OPCODE_EXCEPTION;
    microblaze->params.C_IPLB_BUS_EXCEPTION         = params->C_IPLB_BUS_EXCEPTION;
    microblaze->params.C_DPLB_BUS_EXCEPTION         = params->C_DPLB_BUS_EXCEPTION;
    microblaze->params.C_M_AXI_I_BUS_EXCEPTION      = params->C_M_AXI_I_BUS_EXCEPTION;
    microblaze->params.C_M_AXI_D_BUS_EXCEPTION      = params->C_M_AXI_D_BUS_EXCEPTION;
    microblaze->params.C_DIV_ZERO_EXCEPTION         = params->C_DIV_ZERO_EXCEPTION;
    microblaze->params.C_FPU_EXCEPTION              = params->C_FPU_EXCEPTION;
    microblaze->params.C_OPCODE_0x0_ILLEGAL         = params->C_OPCODE_0x0_ILLEGAL;
    microblaze->params.C_FSL_EXCEPTION              = params->C_FSL_EXCEPTION;
    microblaze->params.C_USE_STACK_PROTECTION       = params->C_USE_STACK_PROTECTION;
    microblaze->params.C_DEBUG_ENABLED              = params->C_DEBUG_ENABLED;
    microblaze->params.C_NUMBER_OF_PC_BRK           = params->C_NUMBER_OF_PC_BRK;
    microblaze->params.C_NUMBER_OF_RD_ADDR_BRK      = params->C_NUMBER_OF_RD_ADDR_BRK;
    microblaze->params.C_NUMBER_OF_WR_ADDR_BRK      = params->C_NUMBER_OF_WR_ADDR_BRK;
    microblaze->params.C_INTERRUPT_IS_EDGE          = params->C_INTERRUPT_IS_EDGE;
    microblaze->params.C_EDGE_IS_POSITIVE           = params->C_EDGE_IS_POSITIVE;
    microblaze->params.C_FSL_LINKS                  = params->C_FSL_LINKS;
    microblaze->params.C_USE_EXTENDED_FSL_INSTR     = params->C_USE_EXTENDED_FSL_INSTR;
    microblaze->params.C_ICACHE_BASEADDR            = params->C_ICACHE_BASEADDR;
    microblaze->params.C_ICACHE_HIGHADDR            = params->C_ICACHE_HIGHADDR;
    microblaze->params.C_USE_ICACHE                 = params->C_USE_ICACHE;
    microblaze->params.C_ALLOW_ICACHE_WR            = params->C_ALLOW_ICACHE_WR;
    microblaze->params.C_ICACHE_LINE_LEN            = params->C_ICACHE_LINE_LEN;
    microblaze->params.C_ICACHE_ALWAYS_USED         = params->C_ICACHE_ALWAYS_USED;
    microblaze->params.C_ICACHE_INTERFACE           = params->C_ICACHE_INTERFACE;
    microblaze->params.C_ICACHE_FORCE_TAG_LUTRAM    = params->C_ICACHE_FORCE_TAG_LUTRAM;
    microblaze->params.C_ICACHE_STREAMS             = params->C_ICACHE_STREAMS;
    microblaze->params.C_ICACHE_VICTIMS             = params->C_ICACHE_VICTIMS;
    microblaze->params.C_ICACHE_DATA_WIDTH          = params->C_ICACHE_DATA_WIDTH;
    microblaze->params.C_ADDR_TAG_BITS              = params->C_ADDR_TAG_BITS;
    microblaze->params.C_CACHE_BYTE_SIZE            = params->C_CACHE_BYTE_SIZE;
    microblaze->params.C_ICACHE_USE_FSL             = params->C_ICACHE_USE_FSL;
    microblaze->params.C_DCACHE_BASEADDR            = params->C_DCACHE_BASEADDR;
    microblaze->params.C_DCACHE_HIGHADDR            = params->C_DCACHE_HIGHADDR;
    microblaze->params.C_USE_DCACHE                 = params->C_USE_DCACHE;
    microblaze->params.C_ALLOW_DCACHE_WR            = params->C_ALLOW_DCACHE_WR;
    microblaze->params.C_DCACHE_LINE_LEN            = params->C_DCACHE_LINE_LEN;
    microblaze->params.C_DCACHE_ALWAYS_USED         = params->C_DCACHE_ALWAYS_USED;
    microblaze->params.C_DCACHE_INTERFACE           = params->C_DCACHE_INTERFACE;
    microblaze->params.C_DCACHE_FORCE_TAG_LUTRAM    = params->C_DCACHE_FORCE_TAG_LUTRAM;
    microblaze->params.C_DCACHE_USE_WRITEBACK       = params->C_DCACHE_USE_WRITEBACK;
    microblaze->params.C_DCACHE_VICTIMS             = params->C_DCACHE_VICTIMS;
    microblaze->params.C_DCACHE_DATA_WIDTH          = params->C_DCACHE_DATA_WIDTH;
    microblaze->params.C_DCACHE_ADDR_TAG            = params->C_DCACHE_ADDR_TAG;
    microblaze->params.C_DCACHE_BYTE_SIZE           = params->C_DCACHE_BYTE_SIZE;
    microblaze->params.C_DCACHE_USE_FSL             = params->C_DCACHE_USE_FSL;
    microblaze->params.C_USE_MMU                    = params->C_USE_MMU;
    microblaze->params.C_MMU_DTLB_SIZE              = params->C_MMU_DTLB_SIZE;
    microblaze->params.C_MMU_ITLB_SIZE              = params->C_MMU_ITLB_SIZE;
    microblaze->params.C_MMU_TLB_ACCESS             = params->C_MMU_TLB_ACCESS;
    microblaze->params.C_MMU_ZONES                  = params->C_MMU_ZONES;
    microblaze->params.C_MMU_PRIVILEGED_INSTR       = params->C_MMU_PRIVILEGED_INSTR;
    microblaze->params.C_USE_INTERRUPT              = params->C_USE_INTERRUPT;
    microblaze->params.C_USE_EXT_BRK                = params->C_USE_EXT_BRK;
    microblaze->params.C_USE_EXT_NM_BRK             = params->C_USE_EXT_NM_BRK;
    microblaze->params.C_USE_BRANCH_TARGET_CACHE    = params->C_USE_BRANCH_TARGET_CACHE;
    microblaze->params.C_BRANCH_TARGET_CACHE_SIZE   = params->C_BRANCH_TARGET_CACHE_SIZE;
    microblaze->params.C_STREAM_INTERCONNECT        = params->C_STREAM_INTERCONNECT;

    //
    // Some compound Booleans
    //
    Bool ANY_EXCEPTION =    params->C_UNALIGNED_EXCEPTIONS  ||
                            params->C_ILL_OPCODE_EXCEPTION  ||
                            params->C_IPLB_BUS_EXCEPTION    ||
                            params->C_DPLB_BUS_EXCEPTION    ||
                            params->C_M_AXI_I_BUS_EXCEPTION ||
                            params->C_M_AXI_D_BUS_EXCEPTION ||
                            params->C_DIV_ZERO_EXCEPTION    ||
                            params->C_FPU_EXCEPTION         ||
                            params->C_USE_MMU;

    //
    // PVR0
    //
    microblazeMaskEnable(&microblaze->SPR_PVR0_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR0_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR0.CFG   = (params->C_PVR >> 1);
    microblaze->SPR_PVR0.BS    = params->C_USE_BARREL;
    microblaze->SPR_PVR0.DIV   = params->C_USE_DIV;
    microblaze->SPR_PVR0.MUL   = (params->C_USE_HW_MUL) ? 1 : 0;
    microblaze->SPR_PVR0.FPU   = (params->C_USE_FPU) ? 1 : 0;
    //
    // if any exception
    //
    if (ANY_EXCEPTION) {
        microblaze->SPR_PVR0.EXC = 1;
    }

    microblaze->SPR_PVR0.ICU   = params->C_USE_ICACHE;
    microblaze->SPR_PVR0.DCU   = params->C_USE_DCACHE;
    microblaze->SPR_PVR0.MMU   = (params->C_USE_MMU) ? 1 : 0;
    microblaze->SPR_PVR0.BTC   = params->C_USE_BRANCH_TARGET_CACHE;
    microblaze->SPR_PVR0.ENDI  = params->SETBIT(endian) ? ((params->endian == MEM_ENDIAN_BIG) ? 0 : 1) : params->C_ENDIANNESS;
    microblaze->SPR_PVR0.FT    = params->C_FAULT_TOLERANT;
    microblaze->SPR_PVR0.SPROT = params->C_USE_STACK_PROTECTION;
    microblaze->SPR_PVR0.REORD = params->C_USE_REORDER_INSTR;
    //
    // MBV is based upon the ISA Version
    // 0x15 = v8.2
    // 0x22 = v9.5
    //
    switch(microblaze->configInfo.arch) {
//    case V7_00:
//        microblaze->SPR_PVR0.MBV = 0x05;
//        break;
//    case V7_10:
//        microblaze->SPR_PVR0.MBV = 0x08;
//        break;
//    case V7_20:
//        microblaze->SPR_PVR0.MBV = 0x0c;
//        break;
//    case V7_30:
//        microblaze->SPR_PVR0.MBV = 0x10;
//        break;
//    case V8_00:
//        microblaze->SPR_PVR0.MBV = 0x12;
//        break;
//    case V8_10:
//        microblaze->SPR_PVR0.MBV = 0x14;
//        break;

    case V9_50:
        microblaze->SPR_PVR0.MBV = 0x22;
        break;

    case V8_20:
    default:
        microblaze->SPR_PVR0.MBV = 0x15;
        break;
    }
    microblaze->SPR_PVR0.USR1  = params->C_PVR_USER1;

    //
    // PVR1
    //
    microblazeMaskEnable(&microblaze->SPR_PVR1_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR1_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR1.USR2 = params->C_PVR_USER2;

    //
    // PVR2
    //
    microblazeMaskEnable(&microblaze->SPR_PVR2_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR2_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR2.DAXI      = params->C_D_AXI;
    microblaze->SPR_PVR2.DLMB      = params->C_D_LMB;
    microblaze->SPR_PVR2.IAXI      = params->C_I_AXI;
    microblaze->SPR_PVR2.ILMB      = params->C_I_LMB;
    microblaze->SPR_PVR2.IRQEDGE   = params->C_INTERRUPT_IS_EDGE;
    microblaze->SPR_PVR2.IRQPOS    = params->C_EDGE_IS_POSITIVE;
    microblaze->SPR_PVR2.DPLB      = params->C_D_PLB;
    microblaze->SPR_PVR2.IPLB      = params->C_I_PLB;
    microblaze->SPR_PVR2.INTERCON  = params->C_INTERCONNECT;
    microblaze->SPR_PVR2.STREAM    = params->C_STREAM_INTERCONNECT;
    microblaze->SPR_PVR2.AXI4DP    = params->C_M_AXI_DP_EXCLUSIVE_ACCESS;
    microblaze->SPR_PVR2.FSL       = params->C_USE_EXTENDED_FSL_INSTR;
    microblaze->SPR_PVR2.FSLEXC    = params->C_FSL_EXCEPTION;
    microblaze->SPR_PVR2.MSR       = params->C_USE_MSR_INSTR;
    microblaze->SPR_PVR2.PCMP      = params->C_USE_PCMP_INSTR;
    microblaze->SPR_PVR2.AREA      = params->C_AREA_OPTIMIZED;
    microblaze->SPR_PVR2.BS        = params->C_USE_BARREL;
    microblaze->SPR_PVR2.DIV       = params->C_USE_DIV;
    microblaze->SPR_PVR2.MUL       = params->C_USE_HW_MUL > 0;
    microblaze->SPR_PVR2.FPU       = params->C_USE_FPU > 0;
    microblaze->SPR_PVR2.MUL64     = params->C_USE_HW_MUL == 2;
    microblaze->SPR_PVR2.FPU2      = params->C_USE_FPU == 2;
    microblaze->SPR_PVR2.IPLBEXC   = params->C_IPLB_BUS_EXCEPTION;
    microblaze->SPR_PVR2.DPLBEXC   = params->C_DPLB_BUS_EXCEPTION;
    microblaze->SPR_PVR2.OP0EXC    = params->C_OPCODE_0x0_ILLEGAL;
    microblaze->SPR_PVR2.UNEXC     = params->C_UNALIGNED_EXCEPTIONS;
    microblaze->SPR_PVR2.OPEXC     = params->C_ILL_OPCODE_EXCEPTION;
    microblaze->SPR_PVR2.AXIIEXC   = params->C_M_AXI_I_BUS_EXCEPTION;
    microblaze->SPR_PVR2.AXIDEXC   = params->C_M_AXI_D_BUS_EXCEPTION;
    microblaze->SPR_PVR2.DIVEXC    = params->C_DIV_ZERO_EXCEPTION;
    microblaze->SPR_PVR2.FPUEXC    = params->C_FPU_EXCEPTION;

    //
    // PVR3
    //
    microblazeMaskEnable(&microblaze->SPR_PVR3_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR3_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR3.DEBUG_    = params->C_DEBUG_ENABLED;
    microblaze->SPR_PVR3.PCBRK     = params->C_NUMBER_OF_PC_BRK;
    microblaze->SPR_PVR3.RDADDR    = params->C_NUMBER_OF_RD_ADDR_BRK;
    microblaze->SPR_PVR3.WRADDR    = params->C_NUMBER_OF_WR_ADDR_BRK;
    microblaze->SPR_PVR3.FSL       = params->C_FSL_LINKS;
    microblaze->SPR_PVR3.BTC_SIZE  = params->C_BRANCH_TARGET_CACHE_SIZE;

    //
    // PVR4
    //
    microblazeMaskEnable(&microblaze->SPR_PVR4_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR4_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR4.ICU       = params->C_USE_ICACHE;
    microblaze->SPR_PVR4.ICTS      = params->C_ADDR_TAG_BITS;
    microblaze->SPR_PVR4.ICW       = params->C_ALLOW_ICACHE_WR;
    microblaze->SPR_PVR4.ICLL      = mbLog2(params->C_ICACHE_LINE_LEN);   // log2()
    microblaze->SPR_PVR4.ICBS      = mbLog2(params->C_CACHE_BYTE_SIZE);   // log2()
    microblaze->SPR_PVR4.IAU       = params->C_ICACHE_ALWAYS_USED;
    microblaze->SPR_PVR4.ICI       = params->C_ICACHE_INTERFACE;
    microblaze->SPR_PVR4.ICV       = params->C_ICACHE_VICTIMS;
    microblaze->SPR_PVR4.ICS       = params->C_ICACHE_STREAMS;
    microblaze->SPR_PVR4.IFTL      = params->C_ICACHE_FORCE_TAG_LUTRAM;
    microblaze->SPR_PVR4.ICDW      = params->C_ICACHE_DATA_WIDTH > 0;

    //
    // PVR5
    //
    microblazeMaskEnable(&microblaze->SPR_PVR5_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR5_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR5.DCU       = params->C_USE_DCACHE;
    microblaze->SPR_PVR5.DCTS      = params->C_DCACHE_ADDR_TAG;
    microblaze->SPR_PVR5.reserved2 = 1;
    microblaze->SPR_PVR5.DCW       = params->C_ALLOW_DCACHE_WR;
    microblaze->SPR_PVR5.DCLL      = mbLog2(params->C_DCACHE_LINE_LEN);     // log2()
    microblaze->SPR_PVR5.DCBS      = mbLog2(params->C_DCACHE_BYTE_SIZE);    // log2()
    microblaze->SPR_PVR5.DAU       = params->C_DCACHE_ALWAYS_USED;
    microblaze->SPR_PVR5.DWB       = params->C_DCACHE_USE_WRITEBACK;
    microblaze->SPR_PVR5.DCI       = params->C_DCACHE_INTERFACE;
    microblaze->SPR_PVR5.DCV       = params->C_DCACHE_VICTIMS;
    microblaze->SPR_PVR5.DFTL      = params->C_DCACHE_FORCE_TAG_LUTRAM;
    microblaze->SPR_PVR5.DCDW      = params->C_DCACHE_DATA_WIDTH > 0;
    microblaze->SPR_PVR5.AXI4DC    = params->C_M_AXI_DC_EXCLUSIVE_ACCESS;

    //
    // PVR6
    //
    microblazeMaskEnable(&microblaze->SPR_PVR6_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR6_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR6.ICBA      = params->C_ICACHE_BASEADDR;

    //
    // PVR7
    //
    microblazeMaskEnable(&microblaze->SPR_PVR7_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR7_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR7.ICHA      = params->C_ICACHE_HIGHADDR;

    //
    // PVR8
    //
    microblazeMaskEnable(&microblaze->SPR_PVR8_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR8_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR8.DCBA      = params->C_DCACHE_BASEADDR;

    //
    // PVR9
    //
    microblazeMaskEnable(&microblaze->SPR_PVR9_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR9_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR9.DCHA      = params->C_DCACHE_HIGHADDR;

    //
    // PVR10
    //
    microblazeMaskEnable(&microblaze->SPR_PVR10_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR10_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR10.ARCH     = params->C_FAMILY;

    //
    // PVR11
    //
    microblazeMaskEnable(&microblaze->SPR_PVR11_rmask.reg, True,  0, 31);
    microblazeMaskEnable(&microblaze->SPR_PVR11_wmask.reg, False, 0, 31);
    microblaze->SPR_PVR11.MMU      = params->C_USE_MMU;
    microblaze->SPR_PVR11.ITLB     = mbLog2(params->C_MMU_ITLB_SIZE);  // log2()
    microblaze->SPR_PVR11.DTLB     = mbLog2(params->C_MMU_DTLB_SIZE);  // log2()
    microblaze->SPR_PVR11.TLBACC   = params->C_MMU_TLB_ACCESS;
    microblaze->SPR_PVR11.ZONES    = params->C_MMU_ZONES;
    microblaze->SPR_PVR11.PRIVINS  = params->C_MMU_PRIVILEGED_INSTR;
    microblaze->SPR_PVR11.RSTMSR   = params->C_RESET_MSR;

    //
    // PVR12
    //
    if (microblaze->configInfo.arch & ISA_V9_50) {
        microblaze->SPR_PVR12.VECTORS = params->C_BASE_VECTORS;
    }

    //
    // Initialize the MMU (if present)
    //
    microblazeConstructMMU(microblaze);

    //
    // Initialize FPU (if present)
    //
    microblazeConfigureFPU(microblaze);

    //
    // Configure the Fast Serial Links
    //
    microblaze->fslPorts = allocFSLports(microblaze);

    //
    // Create bus port descriptions
    //
    microblazeNewBusPorts(microblaze);

    //
    // Create net port descriptions
    //
    microblazeNewNetPorts(microblaze);

    //
    // call the reset
    //
    microblazeRegisterInit(microblaze);

    microblazeDoc(processor, params);

    //
    // update processor state wrt SPR registers
    //
    microblazeEmptyRegisters(microblaze);

    //
    // Install Commands
    //
    vmirtAddCommandParse(processor, "dumpTLB", "Display the current contents of the TLB", dumpTLB, VMI_CT_QUERY|VMI_CO_TLB|VMI_CA_QUERY);
}

VMI_DESTRUCTOR_FN(microblazeDestructor) {
    microblazeP microblaze = (microblazeP)processor;
    freeFSLports(microblaze, microblaze->fslPorts);
    microblazeFreeBusPorts(microblaze);
    microblazeDestructMMU(microblaze);
}


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

#ifndef OR1K_STRUCTURE_H
#define OR1K_STRUCTURE_H

// VMI header files
#include "vmi/vmiTypes.h"

// model header files
#include "or1kExceptionTypes.h"

// prefix string (for error messages)
#define CPU_PREFIX "OR1K"

#define OR1K_REGS      32       // basic OR1K registers
#define OR1K_BITS      32       // register size in bits
#define OR1K_SP         1       // stack pointer (R1)
#define OR1K_A0         3       // first argument (R3)
#define OR1K_LINK       9       // link register index (R9)
#define OR1K_MRU_TEST   0       // enable MRU test mode
#define OR1K_NUM_TEMPS 16       // number of temporaries

// processor mode definitions
typedef enum or1kModeE {
    OR1K_MODE_SUPERVISOR,
    OR1K_MODE_USER,
    OR1K_MODE_LAST
} or1kMode;

// processor mode definitions
typedef enum or1kBlockStateE {
    OR1K_BS_NONE,               // not blocked
    OR1K_BS_INPUT,              // blocked on input connection
    OR1K_BS_OUTPUT              // blocked on output connection
} or1kBlockState;

// processor structure
typedef struct or1kS {

    Bool          carryFlag;        // carry flag
    Bool          overflowFlag;     // overflow flag
    Bool          branchFlag;       // branch flag

    Uns32         regs[OR1K_REGS];  // basic registers

    Uns32         SR;               // status register
    Uns32         ESR;              // exception status register
    Uns32         EPC;              // exception program counter register
    Uns32         EEAR;             // exception effective address register
    Uns32         PICMR;            // PIC mask register
    Uns32         PICSR;            // PIC status register
    Uns32         TTCR;             // tick timer count register
    Uns32         TTCRSetCount;     // cycle count when TTCR set
    Bool          timerRunning;     // whether the timer is running
    Bool          reset;            // whether the processor is being reset
    Bool          resetInput;       // external value of reset signal
    Bool          artifactAccess;   // whether artifact register read/write
    Bool          inSaveRestore;    // whether save/restore in progress
    or1kException exception;        // current exception

    union {                         // tick timer mode register
        Uns32 TTMR;
        struct {
            Uns32 TTMR_TP: 28;      // timeout count
            Uns32 TTMR_IP: 1;       // interrupt pending
            Uns32 TTMR_IE: 1;       // interrupt enable
            Uns32 TTMR_M : 2;       // timer mode
        };
    };

    Uns64          TMP[OR1K_NUM_TEMPS];// temporaries

    vmiNetPortP    netPorts;        // net port descriptions
    vmiBusPortP    busPorts;        // bus port descriptions
    vmiFifoPortP   fifoPorts;       // fifo port descriptions

                                    // FIFO CONNECTIONS
    vmiConnInputP  inputConn;       // input FIFO connection
    vmiConnOutputP outputConn;      // output FIFO connection
    Uns32          connValue;       // connection data value
    or1kBlockState blockState;      // whether blocked on connection event

    #if(OR1K_MRU_TEST)
        Uns32      currentState;
        memMRUSet  mruSet;
    #endif

} or1k, *or1kP;

// macros to specify target registers in VARIABLE expressions
#define OR1K_CPU_REG(_F)        VMI_CPU_REG(or1kP, _F)
#define OR1K_CPU_TEMP(_F)       VMI_CPU_TEMP(or1kP, _F)
#define OR1K_REG(_R)            OR1K_CPU_REG(regs[_R])
#define OR1K_CARRY              OR1K_CPU_REG(carryFlag)
#define OR1K_OVERFLOW           OR1K_CPU_REG(overflowFlag)
#define OR1K_BRANCH             OR1K_CPU_REG(branchFlag)
#define OR1K_LINKREG            OR1K_REG(OR1K_LINK)
#define OR1K_SR                 OR1K_CPU_REG(SR)
#define OR1K_ESR                OR1K_CPU_REG(ESR)
#define OR1K_EPC                OR1K_CPU_REG(EPC)
#define OR1K_EEAR               OR1K_CPU_REG(EEAR)
#define OR1K_TTMR               OR1K_CPU_REG(TTMR)
#define OR1K_PICMR              OR1K_CPU_REG(PICMR)
#define OR1K_PICSR              OR1K_CPU_REG(PICSR)
#define OR1K_TEMPREG            OR1K_CPU_TEMP(tempReg)
#define OR1K_BLOCK_STATE        OR1K_CPU_REG(blockState)

// macros to specify target registers in CONSTANT expressions
#define OR1K_CPU_REG_CONST(_F)  VMI_CPU_REG_CONST(or1kP, _F)
#define OR1K_CPU_TEMP_CONST(_F) VMI_CPU_TEMP_CONST(or1kP, _F)
#define OR1K_REG_CONST(_R)      OR1K_CPU_REG_CONST(regs[_R])
#define OR1K_CARRY_CONST        OR1K_CPU_REG_CONST(carryFlag)
#define OR1K_OVERFLOW_CONST     OR1K_CPU_REG_CONST(overflowFlag)

// Bit definitions for the SR register
#define SPR_SR_CID      0xf0000000  // Context ID
#define SPR_SR_SUMRA    0x00010000  // Supervisor SPR read access
#define SPR_SR_FO       0x00008000  // Fixed one
#define SPR_SR_EPH      0x00004000  // Exception Prefix High
#define SPR_SR_DSX      0x00002000  // Delay Slot Exception
#define SPR_SR_OVE      0x00001000  // Overflow flag Exception
#define SPR_SR_OV       0x00000800  // Overflow flag
#define SPR_SR_CY       0x00000400  // Carry flag
#define SPR_SR_F        0x00000200  // Condition Flag
#define SPR_SR_CE       0x00000100  // CID Enable
#define SPR_SR_LEE      0x00000080  // Little Endian Enable
#define SPR_SR_IME      0x00000040  // Instruction MMU Enable
#define SPR_SR_DME      0x00000020  // Data MMU Enable
#define SPR_SR_ICE      0x00000010  // Instruction Cache Enable
#define SPR_SR_DCE      0x00000008  // Data Cache Enable
#define SPR_SR_IEE      0x00000004  // Interrupt Exception Enable
#define SPR_SR_TEE      0x00000002  // Tick timer Exception Enable
#define SPR_SR_SM       0x00000001  // Supervisor Mode

// This specifies whether the processor is in supervisor mode
#define IN_SUPERVISOR_MODE(_OR1K) ((_OR1K)->SR & SPR_SR_SM)

// This specifies whether FIFOs are enabled
#define OR1K_FIFO             0x00000002
#define OR1K_ENABLE_FIFOS(_P) ((vmirtProcessorFlags(_P) & OR1K_FIFO) != 0)

#endif


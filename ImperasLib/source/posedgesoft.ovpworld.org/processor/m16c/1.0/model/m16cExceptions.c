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


// Imperas header files
#include "hostapi/impAlloc.h"

// VMI header files
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

// model header files
#include "m16cExceptions.h"
#include "m16cFunctions.h"
#include "m16cTypeRefs.h"
#include "m16cStructure.h"

//
// Exception levels
//
#define NMI0 0x1


#define M16C_FIXED_VECTOR   0xFFFDC
#define M16C_RESET_VECTOR   0xFFFFC

//
// Return number of members of an array
//
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))


//
// Is the processor halted?
//
inline static Bool isHalted(m16cP m16c) {
    return vmirtIsHalted((vmiProcessorP)m16c);
}




//
// Fill the full current value of the SR register, including bits normally
// maintained in separate flags fields
//
inline static void fillFLG(m16cP m16c) {
    Uns32 nextFLG = 0;
    if (m16c->carryFlag)                nextFLG |= M16C_FLG_C;
    if (m16c->debugFlag)                nextFLG |= M16C_FLG_D;
    if (m16c->zeroFlag)                 nextFLG |= M16C_FLG_Z;
    if (m16c->signFlag)                 nextFLG |= M16C_FLG_S;
    if (m16c->regBankSelectFlag)        nextFLG |= M16C_FLG_B;
    if (m16c->overflowFlag)             nextFLG |= M16C_FLG_O;
    if (m16c->intEnableFlag)            nextFLG |= M16C_FLG_I;
    if (m16c->spSelectFlag)             nextFLG |= M16C_FLG_U;
    nextFLG |= (m16c->intPriorityLevel << 13);
    m16c->regs[M16C_REG_FLG] = nextFLG;
}




//
// Is there a pending exception on this processor? Note that if the processor
// is halted
//
Bool m16cInterruptPending(m16cP m16c) {
    Bool enabled = False;

    if (isHalted(m16c)) {
        if (m16c->nmiPending) {
            enabled = True;
        } else {
            if (m16c->intpPending) {
                if (m16c->intEnableFlag &&  (m16c->intpLevel > m16c->intPriorityLevel)) {
                    enabled = True;
                }
            }
        }
    }
    return enabled;
}



//
// Process Interrupt
//

static void doInterrupt(m16cP m16c) {
    // EIPC
    // m16c->sregs[M16C_RPC] = vmirtGetPC((vmiProcessorP)m16c);

    // (1) CPU gets the interrupt information (the interrupt number and
    // interrupt request level) by reading address 0x00000.

    // stored in m16c->intpHandler by signalMI()

    // (2) Saves the content of the flag register (FLG) as it was immediately
    // before the start of interrupt sequence in the temporary register within
    // the CPU.

    fillFLG(m16c);



    // (3) Sets the interrupt enable flag (I flag), the debug flag (D flag), and
    // the stack pointer select flag (U flag) to “0” (the U flag, however does
    // not change if the INT instruction, in software interrupt numbers 32
    // through 63, is executed)

    m16c->debugFlag = 0;
    m16c->intEnableFlag = 0;
    if (m16c->nmiPending || m16c->intpHandler < 32)  // only set 'U' flag if int number is not 32 to 64 (for a SWI)
        m16c->spSelectFlag = 0;


    // (4) Saves the content of the temporary register (Note 1) within the CPU
    // in the stack area.

    // Use the new stack location 'U' flag, as determined in the next step

    Uns32 sp = (m16c->spSelectFlag == 0) ? GET_REG16(m16c,M16C_REG_ISP) : GET_REG16(m16c,M16C_REG_USP);


    // PC and FLG are packed in 4 bytes.  Bits 8-11 of FLG are unused and packed with PC bit 16-20.
    Uns32 tempPC = vmirtGetPC((vmiProcessorP)m16c);
    Uns32 value = ((tempPC & 0x000F0000) << 4) |
                  (((Uns32) GET_REG16(m16c,M16C_REG_FLG) & 0x000070FF) << 16) |
                  (tempPC & 0x0000FFFF);

    // (5) Saves the content of the program counter (PC) in the stack area.

    vmirtWrite4ByteDomain(vmirtGetProcessorCodeDomain((vmiProcessorP) m16c), sp, MEM_ENDIAN_LITTLE, value, MEM_AA_TRUE);



    if (m16c->nmiPending) {
        // (6) Sets the interrupt priority level of the accepted instruction in the
        // IPL.
        m16c->intPriorityLevel = 0;

        // Remove intpPending
        m16c->nmiPending = 0;

        // After the interrupt sequence is completed, the processor resumes
        // executing instructions from the first address of the interrupt routine.
        vmirtSetPCException((vmiProcessorP)m16c, M16C_FIXED_VECTOR  + m16c->nmiHandler);
    } else {
        // (6) Sets the interrupt priority level of the accepted instruction in the
        // IPL.


        m16c->intpPending = 0;

        // After the interrupt sequence is completed, the processor resumes
        // executing instructions from the first address of the interrupt routine.
        vmirtSetPCException((vmiProcessorP)m16c, ((Uns32) m16c->regs[M16C_REG_INTB]) + m16c->intpHandler);
        // Send interrupt Acknowledge, and remove intpPending
    }

    vmirtWriteNetPort((vmiProcessorP)m16c, m16c->intack, 1);
}








static void doException(vmiProcessorP processor) {
    vmirtRestartNext(processor);
    vmirtDoSynchronousInterrupt(processor);
}

//
// Do reset exception
// PC <= 0x0
// FECC <= 0x0, EICC <= 0x0 == ECR
// PSW <= 0x00000020
static void doReset(vmiProcessorP processor, Bool intMask) {
    m16cP  m16c = (m16cP)processor;
    //
    // Perform reset actions, then jump to reset vector
    //


    m16c->carryFlag = False;
    m16c->debugFlag = False;
    m16c->zeroFlag = False;
    m16c->signFlag = False;
    m16c->regBankSelectFlag = False;
    m16c->overflowFlag = False;
    //
    // In GDB mode this powers up as False
    // The Silicon however says it powers up as True
    //
    m16c->intEnableFlag =(m16c->compat == COMPAT_GDB) ? True : False;
    m16c->spSelectFlag = False;
    m16c->intPriorityLevel = 0;

    m16c->nmiPending = 0;
    m16c->intpPending = 0;


    //
    // Initialize the General Purpose Registers
    //
    int i;

    for (i = 1; i < M16C_REGS; i++) {
        m16c->regs[i] = 0x0;
    }

    m16c->exception             = m16c_E_Reset;

    // jump to reset vector
    vmirtSetPCException((vmiProcessorP)m16c, M16C_RESET_VECTOR);
}

//
//
//
VMI_ARITH_EXCEPT_FN(m16cArithExceptionCB) {
    m16cP m16c = (m16cP)processor;
    m16c->exception = m16c_E_Overflow;

    switch (exceptionType) {
        // integer divide-by-zero and overflow should not generate exceptions
        // but instead set the overflow flag
        case VMI_INTEGER_OVERFLOW:
            m16c->signFlag = 1;
            m16c->zeroFlag = 0;
        case VMI_INTEGER_DIVIDE_BY_ZERO:
            m16c->overflowFlag = 1;
            return True;

        // not expecting any other arithmetic exception types
        default:
            return False;
    }
}

//
// Read alignment exception handler - snap address to access size
//
VMI_RD_ALIGN_EXCEPT_FN(m16cRdAlignExceptionCB) {
    // Processor is Byte addressable, should not be Alignment Exceptions
    return 0;
}

//
// Write alignment exception handler - snap address to access size
//
VMI_WR_ALIGN_EXCEPT_FN(m16cWrAlignExceptionCB) {
    // Processor is Byte addressable, should not be Alignment Exceptions
    return 0;
}

//
// This is called by the simulator when fetching from an instruction address.
// It gives the model an opportunity to take an exception instead
//
VMI_IFETCH_FN(m16cIFetchExceptionCB) {
    m16cP       m16c   = (m16cP)processor;
    m16c->exception    = m16c_E_Fetch;
    // Uns32       thisPC = (Uns32)address;

    if        (m16cInterruptPending(m16c)) {
        doInterrupt(m16c);
        return VMI_FETCH_EXCEPTION_COMPLETE;

    // } else if (vmirtIsExecutable(processor, thisPC)) {
        // no exception pending
    //    return VMI_FETCH_NONE;

    } else {
        return VMI_FETCH_NONE;
    }
}

//
// Table of exception mode descriptors
//
static const vmiExceptionInfo exceptions[] = {
    { "Undefined",      m16c_E_Undefined },
    { "Overflow",       m16c_E_Overflow  },
    { "BRK",            m16c_E_BRK       },
    { "AddressMatch",  m16c_E_AdrMatch  },
    { "SingleStep",    m16c_E_SStep     },
    { "Watchdog",       m16c_E_Wdt       },
    { "DBC",            m16c_E_DBC       },
    { "NMI",            m16c_E_NMI       },
    { "Reset",          m16c_E_Reset     },
    { "Fetch",          m16c_E_Fetch     },
    { 0 }
};


//
// Return the current processor exception
//
VMI_GET_EXCEPTION_FN(m16cGetException) {
    m16cP m16c = (m16cP)processor;
    return &exceptions[m16c->exception];
}

//
// Exception mode iterator
//
VMI_EXCEPTION_INFO_FN(m16cExceptionInfo) {
    // on the first call, start with the first member of the table
    if (!prev) {
        return exceptions;
    }
    prev++;
    return prev->name ? prev : 0;
}


//
// Called by the simulator when an external NMIn is raised
//
static VMI_NET_CHANGE_FN(signalNMI) {
    m16cP  m16c = (m16cP)processor;

    m16c->nmiPending = 1;

    m16c->nmiHandler = m16c_E_NMI;
    m16c->exception  = m16c_E_NMI;


    // take nmi if it is pending and enabled
    if (m16cInterruptPending(m16c)) {
        doException(processor);
    }
}


//
// Called by the simulator when an external Maskable Interrupt is raised
//
static VMI_NET_CHANGE_FN(signalMI) {
    m16cP m16c = (m16cP)processor;

    // Send Interrupt Priority level as bits 8-10.  Is configureable per
    // interrupt in periph control registers.  Level 0 would be disabled
    m16c->intpPending = (newValue == 0) ? 0 : 1;
    m16c->intpHandler = newValue & 0x2F;
    m16c->intpLevel   = (newValue >> 8) & 0x7;

    // take interrupt if it is pending and enabled
    if (m16cInterruptPending(m16c)) {
        doException(processor);
    }
}

//
// Called by the simulator when an external reset is raised
//
static VMI_NET_CHANGE_FN(signalReset) {
    m16cP m16c = (m16cP)processor;

    if (m16c->reset == newValue) {
    } else {
        m16c->reset = newValue;
        if (!m16c->reset) {
            // reset the processor
            doReset(processor, True);

            // take reset
            doException(processor);
        }
    }
}

typedef struct m16cNetPortS {
    vmiNetPort desc;
    Bool       extended;
} m16cNetPort;

//
// Allocate net port structures
//
void m16cNewNetPorts(m16cP m16c) {

    // declare template port structure (including terminator)
    m16cNetPort template[] = {
        {{name : "reset",   type : vmi_NP_INPUT,  netChangeCB : signalReset},   1},
        {{name : "nmi",     type : vmi_NP_INPUT,  netChangeCB : signalNMI},     1},
        {{name : "int_per", type : vmi_NP_INPUT,  netChangeCB : signalMI},      1},
        {{name : "int_ack", type : vmi_NP_OUTPUT, handle      : &m16c->intack}, 1},
        {{0}}
    };

    // count members
    Uns32 numMembers = NUM_MEMBERS(template);
    Uns32 i;

    // allocate permanent port structure (including terminator)
    m16cNetPortP result = STYPE_CALLOC_N(m16cNetPort, numMembers);

    // fill permanent port structure
    for (i = 0; i < numMembers; i++) {
        result[i] = template[i];
    }

    // save ports on processor
    m16c->netPorts = result;
}

//
// Free net port structures
//
void m16cFreeNetPorts(m16cP m16c) {
    if (m16c->netPorts) {
        STYPE_FREE(m16c->netPorts);
    }
}

//
// Skip port descriptions not used on this variant
//
static void skipUnusedPorts(m16cNetPortPP p) {
    while ((*p)->desc.name && !(*p)->extended) {
        (*p)++;
    }
}

//
// Get the next net port
//
VMI_NET_PORT_SPECS_FN(m16cGetNetPortSpec) {
    m16cNetPortP c    = (m16cNetPortP)prev;
    m16cP        m16c = (m16cP)processor;
    // Bool         extd = m16c->variant & (VAR_V850_E1_SET | VAR_V850_E2_SET);

    if (!c) {
        c = m16c->netPorts;
    } else {
        c++;
    }

    // if (!extd) {
        skipUnusedPorts(&c);
    // }

    return (vmiNetPortP)((c->desc.name) ? c : 0);
}



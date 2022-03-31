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

// Imperas header files
#include "hostapi/impAlloc.h"

// VMI header files
#include "vmi/vmiRt.h"

// model header files
#include "openhwConfig.h"
#include "openhwExceptions.h"
#include "openhwStructure.h"
#include "openhwUtils.h"

// base model header files
#include "riscvStructure.h"


////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Does this variant implement custom bus faults?
//
static Bool hasBusFault(riscvP riscv) {

    openhwConfigCP config   = openhwExtConfig(riscv);
    openhwFeature  features = config->features;

    return (features&OHWF_BUS_FAULT);
}


////////////////////////////////////////////////////////////////////////////////
// NET PORT CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Test for pending NMI
//
static void handleNMI(
    vmiosObjectP object,
    Bool         new,
    openhwInt    ecode_nmi
) {
    riscvP riscv = object->riscv;
    Bool   old   = RD_CSR_FIELDC(riscv, dcsr, nmip);

    if(!old && new) {

        // save pending NMI error code
        riscv->configInfo.ecode_nmi = ecode_nmi;

        // immediately take interrupt when not in debug mode
        if(!inDebugMode(riscv)) {
            riscv->cb.restart(riscv, RVD_RESTART_NMI);
            vmirtDoSynchronousInterrupt((vmiProcessorP)riscv);
        }

        // save new pending value
        RD_CSR_FIELDC(riscv, dcsr, nmip) = new;
    }
}

//
// LoadBusFault NMI Interrupt
//
static VMI_NET_CHANGE_FN(loadBusFault) {
    handleNMI(userData, newValue, OHWI_LoadBusFault);
}

//
// StoreBusFault NMI Interrupt
//
static VMI_NET_CHANGE_FN(storeBusFault) {
    handleNMI(userData, newValue, OHWI_StoreBusFault);
}

//
// InstructionBusFault Exception
//
static VMI_NET_CHANGE_FN(instructionBusFault) {

    vmiosObjectP object = userData;
    riscvP       riscv  = object->riscv;
    Bool         old    = object->instructionBusFault;
    Bool         new    = newValue&1;

    // detect rising edge
    if(!old && new) {
        riscv->cb.restart(riscv, RVD_RESTART_NMI);
        riscv->cb.takeException(riscv, OHW_E_InstructionBusFault, 0);
    }

    object->instructionBusFault = new;
}

//
// Illegal Instruction Exception
//
static VMI_NET_CHANGE_FN(illegalInstruction) {

    vmiosObjectP object = userData;
    riscvP       riscv  = object->riscv;

    // detect rising edge
    if(newValue&1) {
        riscv->cb.takeException(riscv, riscv_E_IllegalInstruction, 0);
    }
}


////////////////////////////////////////////////////////////////////////////////
// NET PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Common fault template port list
//
static const vmiNetPort commonFaultTemplate[] = {
    {
        name        : "IllegalInstruction",
        type        : vmi_NP_INPUT,
        netChangeCB : illegalInstruction,
        description : "Illegal Instruction Exception"
    },
};

//
// Bus fault template port list
//
static const vmiNetPort busFaultTemplate[] = {
    {
        name        : "LoadBusFaultNMI",
        type        : vmi_NP_INPUT,
        netChangeCB : loadBusFault,
        description : "Load Bus Fault Interrupt"
    },
    {
        name        : "StoreBusFaultNMI",
        type        : vmi_NP_INPUT,
        netChangeCB : storeBusFault,
        description : "Store Bus Fault Interrupt"
    },
    {
        name        : "InstructionBusFault",
        type        : vmi_NP_INPUT,
        netChangeCB : instructionBusFault,
        description : "Instruction Bus Fault Exception"
    },
};

//
// Allocate ports for this extension
//
static void newPorts(vmiosObjectP object) {

    Uns32 numCommon = sizeof(commonFaultTemplate)/sizeof(commonFaultTemplate[0]);
    Uns32 numBus    = 0;

    if(hasBusFault(object->riscv)) {
        numBus = sizeof(busFaultTemplate)/sizeof(busFaultTemplate[0]);
    }

    vmiNetPortP ports = STYPE_CALLOC_N(vmiNetPort, numCommon+numBus+1);
    Uns32       i, j;

    for(i=0, j=0; i<numCommon; i++, j++) {
        ports[j] = commonFaultTemplate[i];
        ports[j].userData = object;
    }

    for(i=0; i<numBus; i++, j++) {
        ports[j] = busFaultTemplate[i];
        ports[j].userData = object;
    }

    object->ports = ports;
}

//
// Free ports for this extension
//
static void freePorts(vmiosObjectP object) {

    if(object->ports) {
        STYPE_FREE(object->ports);
    }
}

//
// Return net ports implemented by this extension
//
VMIOS_NET_PORT_SPECS_FN(openhwNetPorts) {

    vmiNetPortP next = !prev ? object->ports : prev+1;

    return next && next->name ? next : 0;
}


////////////////////////////////////////////////////////////////////////////////
// EXCEPTION DEFINITIONS
////////////////////////////////////////////////////////////////////////////////

//
// Fill one member of exceptions with an exception
//
#define OHW_EXCEPTION(_NAME, _DESC) { \
    name:#_NAME, code:OHW_E_##_NAME, description:_DESC, \
}

//
// Fill one member of exceptions with an interrupt
//
#define OHW_INTERRUPT(_NAME, _DESC) { \
    name:#_NAME, code:riscv_E_Interrupt+OHWI_##_NAME, description:_DESC, \
}

//
// Table of bust fault exception descriptions
//
static const vmiExceptionInfo busFaultExceptions[] = {

    ////////////////////////////////////////////////////////////////////
    // EXCEPTIONS
    ////////////////////////////////////////////////////////////////////

    OHW_EXCEPTION (InstructionBusFault,  "Instruction Bus Fault"),

    ////////////////////////////////////////////////////////////////////
    // INTERRUPTS
    ////////////////////////////////////////////////////////////////////

    OHW_INTERRUPT (LoadBusFault,  "Load Bus Fault NMI"),
    OHW_INTERRUPT (StoreBusFault, "Store Bus Fault NMI"),

    ////////////////////////////////////////////////////////////////////
    // TERMINATOR
    ////////////////////////////////////////////////////////////////////

    {0}
};

//
// Return the first exception implemented by the derived model
//
static RISCV_FIRST_EXCEPTION_FN(firstException) {
    return hasBusFault(riscv) ? busFaultExceptions : 0;
}


////////////////////////////////////////////////////////////////////////////////
// CUSTOM NMI
////////////////////////////////////////////////////////////////////////////////

//
// Implement custom NMI behavior
//
static RISCV_CUSTOM_NMI_FN(customNMI) {

    // update interrupt enable and interrupt enable stack
    WR_CSR_FIELDC(riscv, mstatus, MPIE, RD_CSR_FIELDC(riscv, mstatus, MIE));
    WR_CSR_FIELDC(riscv, mstatus, MIE, 0);

    // also do standard actions
    return False;
}


////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Initialize exception structures
//
void openhwExceptionInit(vmiosObjectP object) {

    // install OpenHW exceptions
    object->extCB.firstException = firstException;
    object->extCB.customNMI      = customNMI;

    // initialize port list for this instance
    newPorts(object);
}

//
// Free exception structures
//
void openhwExceptionFree(vmiosObjectP object) {

    // initialize port list for this instance
    freePorts(object);
}


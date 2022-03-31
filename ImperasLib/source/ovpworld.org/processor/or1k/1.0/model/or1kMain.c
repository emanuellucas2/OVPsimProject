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
#include "vmi/vmiAttrs.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"

// model header files
#include "or1kExceptions.h"
#include "or1kStructure.h"
#include "or1kFunctions.h"
#include "or1kParameters.h"

//
// Return number of members of an array
//
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))


////////////////////////////////////////////////////////////////////////////////
// NET PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Template net port list
//
const static vmiNetPort netPorts[] = {
    {name : "intr0", type : vmi_NP_INPUT, userData : (void*)1, netChangeCB : or1kExternalInterrupt},
    {name : "intr1", type : vmi_NP_INPUT, userData : (void*)2, netChangeCB : or1kExternalInterrupt},
    {name : "intr2", type : vmi_NP_INPUT, userData : (void*)4, netChangeCB : or1kExternalInterrupt},
    {name : "intr3", type : vmi_NP_INPUT, userData : (void*)8, netChangeCB : or1kExternalInterrupt},
    {name : "reset", type : vmi_NP_INPUT, userData : (void*)0, netChangeCB : or1kExternalReset    },
};

//
// Allocate net port specifications
//
static void newNetPorts(or1kP or1k) {

    Uns32 i;

    or1k->netPorts = STYPE_CALLOC_N(vmiNetPort, NUM_MEMBERS(netPorts));

    for(i=0; i<NUM_MEMBERS(netPorts); i++) {
        or1k->netPorts[i] = netPorts[i];
    }
}

//
// Free net port specifications
//
static void freeNetPorts(or1kP or1k) {

    if(or1k->netPorts) {
        STYPE_FREE(or1k->netPorts);
        or1k->netPorts = 0;
    }
}

//
// Get the next net port
//
VMI_NET_PORT_SPECS_FN(or1kGetNetPortSpec) {

    or1kP or1k = (or1kP)processor;

    if(!prev) {

        // first port
        return or1k->netPorts;

    } else {

        // port other than the first
        Uns32 prevIndex = (prev-or1k->netPorts);
        Uns32 thisIndex = prevIndex+1;

        return (thisIndex<NUM_MEMBERS(netPorts)) ? &or1k->netPorts[thisIndex] : 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
// BUS PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Template bus port list
//
const static vmiBusPort busPorts[] = {
    {"INSTRUCTION", vmi_BP_MASTER, vmi_DOM_CODE, {32,32}, 1, "Used to fetch code for execution"},
    {"DATA"       , vmi_BP_MASTER, vmi_DOM_DATA, {32,32}, 0, "Used to read & write data"       },
};

//
// Allocate bus port specifications
//
static void newBusPorts(or1kP or1k) {

    Uns32 i;

    or1k->busPorts = STYPE_CALLOC_N(vmiBusPort, NUM_MEMBERS(busPorts));

    for(i=0; i<NUM_MEMBERS(busPorts); i++) {
        or1k->busPorts[i] = busPorts[i];
    }
}

//
// Free bus port specifications
//
static void freeBusPorts(or1kP or1k) {

    if(or1k->busPorts) {
        STYPE_FREE(or1k->busPorts);
        or1k->busPorts = 0;
    }
}

//
// Get the next bus port
//
VMI_BUS_PORT_SPECS_FN(or1kGetBusPortSpec) {

    or1kP or1k = (or1kP)processor;

    if(!prev) {

        // first port
        return or1k->busPorts;

    } else {

        // port other than the first
        Uns32 prevIndex = (prev-or1k->busPorts);
        Uns32 thisIndex = prevIndex+1;

        return (thisIndex<NUM_MEMBERS(busPorts)) ? &or1k->busPorts[thisIndex] : 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
// FIFO PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Template FIFO port list
//
static vmiFifoPort fifoPorts[] = {
    {"fifoIn" , vmi_FIFO_INPUT,  32, (void *)VMI_CPU_OFFSET(or1kP, inputConn) },
    {"fifoOut", vmi_FIFO_OUTPUT, 32, (void *)VMI_CPU_OFFSET(or1kP, outputConn)}
};

//
// Allocate FIFO port structure
//
static void newFifoPorts(or1kP or1k) {

    Uns32 i;

    or1k->fifoPorts = STYPE_CALLOC_N(vmiFifoPort, NUM_MEMBERS(fifoPorts));

    for(i=0; i<NUM_MEMBERS(fifoPorts); i++) {

        or1k->fifoPorts[i] = fifoPorts[i];

        // correct FIFO port handles
        Uns8 *raw = (Uns8*)(or1k->fifoPorts[i].handle);
        or1k->fifoPorts[i].handle = (void **)(raw + (UnsPS)or1k);
    }
}

//
// Free FIFO port specifications
//
static void freeFifoPorts(or1kP or1k) {

    if(or1k->fifoPorts) {
        STYPE_FREE(or1k->fifoPorts);
        or1k->fifoPorts = 0;
    }
}

//
// Get the next fifo port, if enabled
//
VMI_FIFO_PORT_SPECS_FN(or1kGetFifoPortSpec) {

    or1kP or1k = (or1kP)processor;

    if(!prev) {

        // first port
        return or1k->fifoPorts;

    } else {

        // port other than the first
        Uns32 prevIndex = (prev-or1k->fifoPorts);
        Uns32 thisIndex = prevIndex+1;

        return (thisIndex<NUM_MEMBERS(fifoPorts)) ? &or1k->fifoPorts[thisIndex] : 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
// SAVE/RESTORE INTERFACE
////////////////////////////////////////////////////////////////////////////////

//
// OR1K processor state save
//
VMI_SAVE_STATE_FN(or1kSaveStateCB) {

    or1kP or1k = (or1kP)processor;

    switch(phase) {

        case SRT_BEGIN:
            // start of save/restore process
            or1k->inSaveRestore = True;
            break;

        case SRT_BEGIN_CORE:
            // start of individual core
            break;

        case SRT_END_CORE:
            // end of individual core: save fields not covered by debug register
            // interface
            VMIRT_SAVE_FIELD(cxt, or1k, TTCRSetCount);
            VMIRT_SAVE_FIELD(cxt, or1k, timerRunning);
            VMIRT_SAVE_FIELD(cxt, or1k, resetInput);
            VMIRT_SAVE_FIELD(cxt, or1k, reset);
            VMIRT_SAVE_FIELD(cxt, or1k, blockState);
            break;

        case SRT_END:
            // end of save/restore process
            or1k->inSaveRestore = False;
            break;

        default:
            // not reached
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }
}

//
// OR1K processor state restore
//
VMI_RESTORE_STATE_FN(or1kRestoreStateCB) {

    or1kP or1k = (or1kP)processor;

    switch(phase) {

        case SRT_BEGIN:
            // start of save/restore process
            or1k->inSaveRestore = True;
            break;

        case SRT_BEGIN_CORE:
            // start of individual core
            break;

        case SRT_END_CORE:
            // end of individual core: save fields not covered by debug register
            // interface
            VMIRT_RESTORE_FIELD(cxt, or1k, TTCRSetCount);
            VMIRT_RESTORE_FIELD(cxt, or1k, timerRunning);
            VMIRT_RESTORE_FIELD(cxt, or1k, resetInput);
            VMIRT_RESTORE_FIELD(cxt, or1k, reset);
            VMIRT_RESTORE_FIELD(cxt, or1k, blockState);
            // take any pending interrupt before the next instruction
            or1kInterruptNext(or1k);
            // restore blocked state if required
            if(or1k->blockState==OR1K_BS_INPUT) {
                vmirtConnNotifyPut(or1k->inputConn, 0, 0);
            } else if(or1k->blockState==OR1K_BS_OUTPUT) {
                vmirtConnNotifyGet(or1k->outputConn, 0, 0);
            }
            break;

        case SRT_END:
            // end of save/restore process
            or1k->inSaveRestore = False;
            break;

        default:
            // not reached
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// OR1K processor constructor
//
VMI_CONSTRUCTOR_FN(or1kConstructor) {

    or1kP            or1k   = (or1kP)processor;
    or1kParamValuesP params = (or1kParamValuesP)parameterValues;
    Uns32 i;

    // initialise general purpose registers
    for(i=2; i<OR1K_REGS; i++) {
        or1k->regs[i] = 0xdeadbeef;
    }

    // initialise status registers SR, ESR, EPCR and EEAR
    or1k->SR   = SPR_SR_FO | SPR_SR_SM;
    or1k->ESR  = 0xdeadbeef;
    or1k->EPC  = 0xdeadbeef;
    or1k->EEAR = 0xdeadbeef;

    // create FIFO port descriptions if enabled
    if(OR1K_ENABLE_FIFOS(processor) || params->fifos) {
        newFifoPorts(or1k);
    }

    // create net port specifications
    newNetPorts(or1k);

    // create bus port specifications
    newBusPorts(or1k);
}

//
// OR1K processor destructor
//
VMI_DESTRUCTOR_FN(or1kDestructor) {

    or1kP or1k = (or1kP)processor;

    // free FIFO port specifications
    freeFifoPorts(or1k);

    // free net port specifications
    freeNetPorts(or1k);

    // free bus port specifications
    freeBusPorts(or1k);
}

//
// OR1K virtual memory initialisation
//
VMI_VMINIT_FN(or1kVMInit) {

    #if(OR1K_MRU_TEST)

        or1kP      or1k           = (or1kP)processor;
        memDomainP physicalDomain = codeDomains[0];
        memDomainP virtualDomain  = vmirtNewDomain("virtual", 32);

        or1k->mruSet.nextState    = &or1k->currentState;
        or1k->mruSet.currentState = &or1k->currentState;

        vmirtAliasMemory(
            physicalDomain,
            virtualDomain,
            0x00000000,
            0xffffffff,
            0x00000000,
            &or1k->mruSet
        );

        codeDomains[0] = virtualDomain;
        dataDomains[0] = virtualDomain;
        codeDomains[1] = virtualDomain;
        dataDomains[1] = virtualDomain;

    #endif
}


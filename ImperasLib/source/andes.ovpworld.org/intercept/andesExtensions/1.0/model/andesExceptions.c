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
#include "andesExceptions.h"
#include "andesStructure.h"
#include "andesTypeRefs.h"

// base model header files
#include "riscvStructure.h"


////////////////////////////////////////////////////////////////////////////////
// BASE MODEL WRAPPER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Check for pending interrupts
//
void andesTestInterrupt(riscvP riscv) {
    riscv->cb.testInterrupt(riscv);
}

//
// Take Illegal Instruction exception
//
void andesIllegalInstruction(riscvP riscv) {
    riscv->cb.illegalInstruction(riscv);
}

//
// Take custom exception
//
void andesTakeException(riscvP riscv, andesException exception, Uns64 tval) {
    riscv->cb.takeException(riscv, exception, tval);
}


////////////////////////////////////////////////////////////////////////////////
// CUSTOM NET PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Type pointers
//
DEFINE_CS(vmiNetPort);

//
// Macro defining input port template
//
#define PORT_I(_ID, _CB, _CODE, _DESC) [ANP_##_ID] = { \
    type        : vmi_NP_INPUT,                     \
    name        : #_ID,                             \
    netChangeCB : _CB,                              \
    userData    : (void *)(_CODE),                  \
    description : _DESC                             \
}

//
// Macro defining output port template
//
#define PORT_O(_ID, _HANDLE, _CODE, _DESC) [ANP_##_ID] = { \
    type        : vmi_NP_OUTPUT,                    \
    name        : #_ID,                             \
    handle      : &(((vmiosObjectP)0)->_HANDLE),    \
    userData    : (void *)(_CODE),                  \
    description : _DESC                             \
}

//
// Port identifiers
//
typedef enum andesPortIdE {

    // interrupt acknowledgement ports
    ANP_UExternalInterruptACK,
    ANP_SExternalInterruptACK,
    ANP_MExternalInterruptACK,

} andesPortId;

//
// Port template list
//
static const vmiNetPort netPorts[] = {

    // interrupt acknowledgement ports
    PORT_O(UExternalInterruptACK, ueiackHandle, 0, "User mode external interrupt acknowledge"),
    PORT_O(SExternalInterruptACK, seiackHandle, 0, "Supervisor mode external interrupt acknowledge"),
    PORT_O(MExternalInterruptACK, meiackHandle, 0, "Machine mode external interrupt acknowledge"),
};

//
// Allocate a new port and append to the tail of the list
//
static riscvNetPortPP newNetPort(
    vmiosObjectP   object,
    riscvNetPortPP tail,
    const char    *name,
    vmiNetPortType type,
    vmiNetChangeFn portCB,
    const char    *desc,
    Uns32          code,
    Uns32         *handle
) {
    riscvNetPortP       this = STYPE_CALLOC(riscvNetPort);
    vmiNetPortP         info = &this->desc;
    riscvInterruptInfoP ii   = &this->ii;

    // fill port fields
    info->name        = name;
    info->type        = type;
    info->netChangeCB = portCB;
    info->handle      = handle;
    info->description = desc;
    info->userData    = ii;

    // initialize interrupt information structure to enable vectoring interrupt
    // to specific processor instance and use as userData on netChange callback
    ii->hart     = object->riscv;
    ii->userData = code;

    // append to list
    *tail = this;

    // return new tail
    return &this->next;
}

//
// Allocate a new input port based on the given template and append to the tail
// of the list
//
static riscvNetPortPP newNetPortTemplate(
    vmiosObjectP   object,
    riscvNetPortPP tail,
    andesPortId    id
) {
    vmiNetPortCP template = &netPorts[id];
    void        *handle   = template->handle;

    // rebase handle to the given object structure
    if(handle) {
        handle += (UnsPS)object;
    }

    return newNetPort(
        object,
        tail,
        template->name,
        template->type,
        template->netChangeCB,
        template->description,
        (UnsPS)template->userData,
        handle
    );
}

//
// Add ports required for exception state management
//
void andesNewExceptionPorts(vmiosObjectP object) {

    riscvP         riscv = object->riscv;
    riscvNetPortPP tail  = &object->netPorts;

    // always add MExternalInterruptACK port
    tail = newNetPortTemplate(object, tail, ANP_MExternalInterruptACK);

    // add SExternalInterruptACK port if Supervisor mode is present
    if(riscv->configInfo.arch&ISA_S) {
        tail = newNetPortTemplate(object, tail, ANP_SExternalInterruptACK);
    }

    // add UExternalInterruptACK port if N extension is present
    if(riscv->configInfo.arch&ISA_N) {
        tail = newNetPortTemplate(object, tail, ANP_UExternalInterruptACK);
    }
}

//
// Free ports required for exception state management
//
void andesFreeExceptionPorts(vmiosObjectP object) {

    riscvNetPortP this;

    while((this=object->netPorts)) {
        object->netPorts = this->next;
        STYPE_FREE(this);
    }
}

//
// Write a net port
//
inline static void writeNet(riscvP riscv, Uns32 handle, Uns32 value) {
    if(handle) {
        vmirtWriteNetPort((vmiProcessorP)riscv, handle, value);
    }
}

//
// Acknowledge interrupt if required
//
void andesAcknowledgeInterrupt(vmiosObjectP object) {

    riscvP riscv  = object->riscv;
    Uns32  handle = 0;

    switch(riscv->exception) {

        case riscv_E_UExternalInterrupt:
            handle = object->ueiackHandle;
            break;

        case riscv_E_SExternalInterrupt:
            handle = object->seiackHandle;
            break;

        case riscv_E_MExternalInterrupt:
            handle = object->meiackHandle;
            break;

        default:
            break;
    }

    // pulse acknowledge signal
    writeNet(riscv, handle, 1);
    writeNet(riscv, handle, 0);
}

//
// Return current data domain
//
inline static memDomainP getDataDomain(riscvP riscv) {
    return vmirtGetProcessorDataDomain((vmiProcessorP)riscv);
}

//
// Get interrupt/exception handler PC if Andes Vectored mode enabled
//
RISCV_GET_HANDLER_PC_FN(andesGetHandlerPC) {

    vmiosObjectP object = clientData;
    Bool         custom = RD_XCSR_FIELD(object, mmisc_ctl, VEC_PLIC);

    if(custom) {

        riscvMode      mode         = getCurrentMode5(riscv);
        memEndian      endian       = riscv->cb.getDataEndian(riscv, mode);
        memDomainP     domain       = getDataDomain(riscv);
        memAccessAttrs memAttrs     = MEM_AA_TRUE;
        riscvException oldException = riscv->exception;
        Uns32          offset       = 0;
        Uns64          handlerPC;

        // get table offset for this exception type
        switch(riscv->exception) {

            case riscv_E_UExternalInterrupt:
            case riscv_E_SExternalInterrupt:
            case riscv_E_MExternalInterrupt:
                offset = ecode*4;
                break;

            default:
                break;
        }

        // clear exception indication
        riscv->exception = 0;

        // read 4-byte table entry
        handlerPC = vmirtRead4ByteDomain(domain, tvec+offset, endian, memAttrs);

        // determine whether exception occurred on table load
        if(!riscv->exception) {

            // restore previous exception context
            riscv->exception = oldException;

            // mask off LSB from result
            *handlerPCP = handlerPC &= -2;
        }
    }

    return custom;
}


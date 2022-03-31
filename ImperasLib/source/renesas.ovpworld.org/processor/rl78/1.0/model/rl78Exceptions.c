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
#include "vmi/vmiRt.h"

// model header files
#include "rl78Functions.h"
#include "rl78Structure.h"
#include "rl78Utils.h"            // rl78TakeException
#include "rl78Message.h"        // MY_ASSERT


const vmiExceptionInfo exceptions[RL78_EXCPT_LAST] = {
    [RL78_EXCPT_RST] = { name : "RST", code : RST_ADDRESS },
    [RL78_EXCPT_TRP] = { name : "TRP", code : RST_ADDRESS },
    [RL78_EXCPT_IAW] = { name : "IAW", code : RST_ADDRESS },
    [RL78_EXCPT_BRK] = { name : "BRK", code : BRK_ADDRESS },
    [RL78_EXCPT_IRQ] = { name : "IRQ", code : IRQ_ADDRESS },
};




////////////////////////////////////////////////////////////////////////////////
// HANDLING PENDING EXCEPTIONS
////////////////////////////////////////////////////////////////////////////////


inline static Uns32 irqMustBeTaken(rl78P rl78) {
//    vmiPrintf("rl78->irq_vect=%d rl78->PSW_IE=%d rl78->PSW_ISP=%d rl78->irq_prio=%d\n", rl78->irq_vect, rl78->PSW_IE, rl78->PSW_ISP, rl78->irq_prio);

    return ((rl78->irq_vect != 0) && (rl78->PSW_IE != 0) && (rl78->irq_prio <= rl78->PSW_ISP));
}

// OVP Processor Modeling Guide p.130
// The callback function must not itself try to handle the interrupt (for example, by
// calling or1kTakeException, which we first saw in chapter 12). Instead, it must call
// vmirtDoSynchronousInterrupt to indicate that a exception is pending.
// The interrupt must be handled by the instruction fetch exception handler function,
// specified by the VMI_IFETCH_FN macro in vmiAttrs.h:

// The instruction fetch exception handler is called in two phases. In the first phase
// (indicated by complete argument False), the function should determine whether there is
// a pending exception on the processor that should prevent execution at the passed address
// and instead cause control to be transferred to an exception handler. If there is such an
// exception pending, the function should return VMI_FETCH_EXCEPTION_PENDING; otherwise,
// it should return VMI_FETCH_NONE. In this phase, the instruction fetch handler should not
// update the processor state.

// If the instruction fetch exception handler returns VMI_FETCH_EXCEPTION_PENDING, then it
// will subsequently be called again in a second phase (indicated by complete argument
// True). At this point, it should make any changes to the processor state required to handle
// the pending exception and return VMI_FETCH_EXCEPTION_COMPLETE to indicate that
// exception state has been updated.

//#define VMI_IFETCH_FN(_NAME) vmiFetchAction _NAME(
//    vmiProcessorP processor,
//    memDomainP    domain,
//    Addr          address,
//    Bool          complete,
//    Bool          annulled
//)
VMI_IFETCH_FN(rl78IFetchExceptionCB) {

    rl78P rl78 = (rl78P) processor;

    if (rl78->reset != 0) {
        if (complete) {
            rl78Reset(rl78);
            return VMI_FETCH_EXCEPTION_COMPLETE;
        } else {
            return VMI_FETCH_EXCEPTION_PENDING;
        }

    } else if (irqMustBeTaken(rl78)) {
        // external interrupt must be taken
        if (complete) {
            rl78TakeException(rl78, RL78_EXCPT_IRQ, 0);

            vmirtWriteNetPort((vmiProcessorP) rl78, rl78->netAck, 1);

            return VMI_FETCH_EXCEPTION_COMPLETE;
        } else {
            return VMI_FETCH_EXCEPTION_PENDING;
        }

    } else if (!vmirtIsExecutable(processor, address)) {
        // handle execute privilege exception
        if(complete) {
            rl78TakeException(rl78, RL78_EXCPT_IAW, 0);
            return VMI_FETCH_EXCEPTION_COMPLETE;
        } else {
            return VMI_FETCH_EXCEPTION_PENDING;
        }
    }
    return VMI_FETCH_NONE;
}


//#define VMI_NET_CHANGE_FN(_NAME) void _NAME(
//    vmiProcessorP processor,
//    void         *userData,
//    Uns32         newValue
//)
static VMI_NET_CHANGE_FN(externalInterrupt) {

    rl78P rl78 = (rl78P) processor;

       MY_MESSAGE(rl78, "I", "externalInterrupt newValue:%x\n", (Uns32)newValue);

    // Including a case of pending interrupt by CPU, save the interrupt number at this point.
    // It does not return an ACK to INTC, until this interrupt is accepted.
    rl78->irq_vect = newValue & 0xFFFF;
    rl78->irq_prio = newValue >> 16;

    if (irqMustBeTaken(rl78)) {
        if (vmirtIsHalted(processor)) {
            vmirtRestartNow(processor);
        }
        vmirtDoSynchronousInterrupt((vmiProcessorP) rl78);
    }
}

static VMI_NET_CHANGE_FN(resetIn) {

    rl78P rl78 = (rl78P) processor;

    rl78->reset = newValue;

    if (vmirtIsHalted(processor)) {
        vmirtRestartNext(processor);
    }
    vmirtDoSynchronousInterrupt((vmiProcessorP) rl78);
}

//
// Ensure any pending interrupt is taken before the next instruction
//
void rl78InterruptNext(vmiProcessorP processor) {
    rl78P rl78 = (rl78P) processor;
    if (irqMustBeTaken(rl78)) {
        if (vmirtIsHalted((vmiProcessorP) rl78)) {
            vmirtRestartNow((vmiProcessorP) rl78);
        }
        vmirtDoSynchronousInterrupt((vmiProcessorP) rl78);
    }
}


////////////////////////////////////////////////////////////////////////////////
// NET PORTS
////////////////////////////////////////////////////////////////////////////////
//typedef struct vmiNetPortS {
//    const char      *name;
//    vmiNetPortType   type;
//    void            *userData;
//    vmiNetChangeFn   netChangeCB;
//    Uns32           *handle;
//    const char      *description;
//    void            *descriptionDom;
//    Bool            mustBeConnected;
//} vmiNetPort;
static vmiNetPort netPorts[] = {
    {"reset" , vmi_NP_INPUT , (void*)1, resetIn           },
    {"extint", vmi_NP_INPUT , (void*)2, externalInterrupt },
    {"intAck", vmi_NP_OUTPUT, (void*)3, (void*)0          },
    {0                                                    }
};

//#define VMI_NET_PORT_SPECS_FN(_NAME) vmiNetPortP _NAME (
//    vmiProcessorP processor,
//    vmiNetPortP   prev
//)
VMI_NET_PORT_SPECS_FN(rl78GetNetPortSpec) {

    rl78P rl78 = (rl78P) processor;

    if (!prev) {
//        vmiMessage("I", "RL78", "net iterate:%s\n", netPorts[0].name);
        return netPorts;
    }
    prev++;
    if (prev->name) {
//        vmiMessage("I", "RL78", "net iterate:%s\n", prev->name);

        if (((UnsPS) prev->userData) == 3) {
            prev->handle = &rl78->netAck;
        }
        return prev;
    }
    return 0;
}

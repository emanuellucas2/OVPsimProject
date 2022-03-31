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
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

// Model header files
#include "Nios_IIStructure.h"
#include "Nios_IIExceptions.h"
#include "Nios_IIFunctions.h"
#include "Nios_IIPorts.h"

#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))

static Bool posedge(Uns32 old, Uns32 new) {
    if (old == 0 && new == 1) {
        return True;
    }
    return False;
}

static Bool negedge(Uns32 old, Uns32 new) {
    if (old == 1 && new == 0) {
        return True;
    }
    return False;
}

static VMI_NET_CHANGE_FN(signalReset) {

    Nios_IIP Nios_II = (Nios_IIP)processor;

    //
    // The reset is negative edge sensitive
    //
    if (negedge(Nios_II->reset_n, newValue)) {
        //
        // Enter Reset
        //
        Nios_II->ResetPending = True;

        // halt the processor while reset is active
        // vmirtHalt((vmiProcessorP)Nios_II);
        Nios_IIHalt(Nios_II, NIOS_II_RESET);

    } else if (posedge(Nios_II->reset_n, newValue)) {
        //
        // Exit Reset
        //
        Nios_II->ResetPending = False;

        Nios_IIProcessReset(Nios_II);

        Nios_IIRestart(Nios_II, NIOS_II_RESET);
        Nios_IIDoException(Nios_II);
    }

    Nios_II->reset_n = newValue;
}

static VMI_NET_CHANGE_FN(irq_event) {

    Nios_IIP Nios_II = (Nios_IIP)processor;
    Uns32 index = (Uns32)(UnsPS)userData;

    Uns32 mask = 0x1 << index;
    Uns32 irq  = (Nios_II->d_irq >> index) & 0x1;

    if (posedge(irq, newValue)) {
        //
        // Activated
        //
        Nios_II->d_irq |= mask;
    }
    if (negedge(irq, newValue)) {
        //
        // DeActivated
        //
        Nios_II->d_irq &= ~mask;
    }

    // process the interrupt
    Nios_IICheckExceptions(Nios_II);
}

typedef struct Nios_IINetPortS {
    vmiNetPort desc;
    Uns32      variantMask;
} Nios_IINetPort;

static Uns32 countPorts(Nios_IINetPortP template, Nios_IIP Nios_II) {
    Nios_IINetPortP p = template;
    Uns32 c = 0;
    Uns32 variant = Nios_II->configInfo.arch;

    while(p && p->desc.name) {
        if (p->variantMask & variant) {
            c++;
        }
        p++;
    }
    return c;
}

//
// Skip port descriptions not used on this variant
//
static void skipUnusedPorts(Nios_IINetPortPP p, Uns32 variant) {
    while(*p && (*p)->desc.name && !((*p)->variantMask & variant)) {
        (*p)++;
    }
}

//
// Get the next net port
//
VMI_NET_PORT_SPECS_FN(Nios_IINetPortSpecs) {
    Nios_IIP Nios_II = (Nios_IIP)processor;
    Nios_IINetPortP c = (Nios_IINetPortP)prev;
    Uns32 variant = Nios_II->configInfo.arch;

    if(!c) {
        c = Nios_II->netPorts;
    } else {
        c++;
    }
    skipUnusedPorts(&c, variant);

    return (vmiNetPortP)(c && (c->desc.name) ? c : 0);
}

//
// Called from constructor
//
void Nios_IINewNetPorts(Nios_IIP Nios_II) {
    Uns32 variant = Nios_II->configInfo.arch;
    Nios_IINetPort template[] = {
        { {name : "reset_n", type : vmi_NP_INPUT, userData : (void*)0,  netChangeCB : signalReset},   PORT_EXIST_RESET },
        { {name : "d_irq0",  type : vmi_NP_INPUT, userData : (void*)0,  netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq1",  type : vmi_NP_INPUT, userData : (void*)1,  netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq2",  type : vmi_NP_INPUT, userData : (void*)2,  netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq3",  type : vmi_NP_INPUT, userData : (void*)3,  netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq4",  type : vmi_NP_INPUT, userData : (void*)4,  netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq5",  type : vmi_NP_INPUT, userData : (void*)5,  netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq6",  type : vmi_NP_INPUT, userData : (void*)6,  netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq7",  type : vmi_NP_INPUT, userData : (void*)7,  netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq8",  type : vmi_NP_INPUT, userData : (void*)8,  netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq9",  type : vmi_NP_INPUT, userData : (void*)9,  netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq10", type : vmi_NP_INPUT, userData : (void*)10, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq11", type : vmi_NP_INPUT, userData : (void*)11, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq12", type : vmi_NP_INPUT, userData : (void*)12, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq13", type : vmi_NP_INPUT, userData : (void*)13, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq14", type : vmi_NP_INPUT, userData : (void*)14, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq15", type : vmi_NP_INPUT, userData : (void*)15, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq16", type : vmi_NP_INPUT, userData : (void*)16, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq17", type : vmi_NP_INPUT, userData : (void*)17, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq18", type : vmi_NP_INPUT, userData : (void*)18, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq19", type : vmi_NP_INPUT, userData : (void*)19, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq20", type : vmi_NP_INPUT, userData : (void*)20, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq21", type : vmi_NP_INPUT, userData : (void*)21, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq22", type : vmi_NP_INPUT, userData : (void*)22, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq23", type : vmi_NP_INPUT, userData : (void*)23, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq24", type : vmi_NP_INPUT, userData : (void*)24, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq25", type : vmi_NP_INPUT, userData : (void*)25, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq26", type : vmi_NP_INPUT, userData : (void*)26, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq27", type : vmi_NP_INPUT, userData : (void*)27, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq28", type : vmi_NP_INPUT, userData : (void*)28, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq29", type : vmi_NP_INPUT, userData : (void*)29, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq30", type : vmi_NP_INPUT, userData : (void*)30, netChangeCB : irq_event},     PORT_EXIST_IRQ   },
        { {name : "d_irq31", type : vmi_NP_INPUT, userData : (void*)31, netChangeCB : irq_event},     PORT_EXIST_IRQ   },

        { { 0 } }
    };

    // count members
    Uns32 numMembers = countPorts(template, Nios_II);
    Uns32 i, j;

    // allocate permanent port structure (including terminator)
    Nios_IINetPortP result = STYPE_CALLOC_N(Nios_IINetPort, numMembers+1);

    // fill permanent port structure
    for(i=0, j=0; i<NUM_MEMBERS(template); i++) {
        if(template[i].variantMask & variant) {
            result[j++] = template[i];
        }
    }

    // save ports on processor
    Nios_II->netPorts = result;

    // Default Stored net values for reset & irq
    Nios_II->reset_n = 1;
    Nios_II->d_irq   = 0;
}

//
// Free ports
//
void Nios_IIFreeNetPorts(Nios_IIP Nios_II) {
    if(Nios_II->netPorts) {
        STYPE_FREE(Nios_II->netPorts);
        Nios_II->netPorts = 0;
    }
}

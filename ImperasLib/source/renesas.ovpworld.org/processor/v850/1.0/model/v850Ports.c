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
#include "v850Structure.h"
#include "v850Exceptions.h"
#include "v850Functions.h"
#include "v850Utils.h"
#include "v850Ports.h"

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

static VMI_NET_CHANGE_FN(resetPortCB) {

    v850P v850 = (v850P)processor;

    //
    // The reset is negative edge sensitive
    //
    if (negedge(v850->netValue.reset, newValue)) {
        //
        // Enter Reset
        //
        v850->FLG_RSTPEND = True;

        // halt the processor while reset is active
        v850Halt(v850, V850_RESET);

    } else if (posedge(v850->netValue.reset, newValue)) {
        //
        // Exit Reset
        //
        v850->FLG_RSTPEND = False;

        v850ProcessRESET(v850);

        v850Restart(v850, V850_RESET);
        v850ProcessException(processor);
    }

    v850->netValue.reset = newValue;
}

static VMI_NET_CHANGE_FN(intpPortCB) {
    v850P v850 = (v850P)processor;
    v850->netValue.intp = newValue;
    v850->FLG_INTPEND = (newValue == 0) ? 0 : 1;

    // take interrupt if it is pending and enabled
    v850TestInterrupt(v850);
}

static VMI_NET_CHANGE_FN(nmi0PortCB) {
    v850P v850 = (v850P)processor;
    v850->netValue.nmi0 = newValue;
    v850->FLG_NMIPEND = (newValue == 0) ? 0 : 1;

    // take interrupt if it is pending and enabled
    v850TestInterrupt(v850);
}

static VMI_NET_CHANGE_FN(nmi1PortCB) {
    v850P v850 = (v850P)processor;
    v850->netValue.nmi1 = newValue;
    v850->FLG_NMIPEND = (newValue == 0) ? 0 : 1;

    // take interrupt if it is pending and enabled
    v850TestInterrupt(v850);
}

static VMI_NET_CHANGE_FN(nmi2PortCB) {
    v850P v850 = (v850P)processor;
    v850->netValue.nmi2 = newValue;
    v850->FLG_NMIPEND = (newValue == 0) ? 0 : 1;

    // take interrupt if it is pending and enabled
    v850TestInterrupt(v850);
}


typedef struct v850NetPortS {
    vmiNetPort desc;
    Uns32      variantMask;
} v850NetPort;

void v850NewNetPorts(v850P v850) {
    const char *intpText   = "Interrupt Port";
    const char *nmiXText   = "Non-Maskable Interrupt Port";
    const char *resetText  = "Reset Port";
    const char *miretiText = "Return from Interrupt Port";
    const char *intackText = "Interrupt Acknowledge Port";
    v850NetPort template[] = {
        { {"intp",   vmi_NP_INPUT,  (void*)0, intpPortCB,  (void*)0,               intpText },  ISA_E0 },
        { {"nmi0",   vmi_NP_INPUT,  (void*)0, nmi0PortCB,  (void*)0,               nmiXText },  ISA_E0 },
        { {"nmi1",   vmi_NP_INPUT,  (void*)0, nmi1PortCB,  (void*)0,               nmiXText },  ISA_E1 },
        { {"nmi2",   vmi_NP_INPUT,  (void*)0, nmi2PortCB,  (void*)0,               nmiXText },  ISA_E1 },
        { {"reset",  vmi_NP_INPUT,  (void*)0, resetPortCB, (void*)0,               resetText},  ISA_E0 },
        { {"mireti", vmi_NP_OUTPUT, (void*)0, (void*)0,    &v850->netValue.mireti, miretiText}, ISA_E0 },
        { {"intack", vmi_NP_OUTPUT, (void*)0, (void*)0,    &v850->netValue.intack, intackText}, ISA_E0 },
        { { 0 } }
    };

    // count members
    Uns32 numMembers = NUM_MEMBERS(template);
    Uns32 i;

    // allocate permanent port structure (including terminator)
    v850NetPortP result = STYPE_CALLOC_N(v850NetPort, numMembers);

    // fill permanent port structure
    for(i=0; i<numMembers; i++) {
        result[i] = template[i];
    }

    // save ports on processor
    v850->netPorts = result;
}

//
// Free ports
//
void v850FreeNetPorts(v850P v850) {
    if(v850->netPorts) {
        STYPE_FREE(v850->netPorts);
    }
}

//
// Skip port descriptions not used on this variant
//
static void skipUnusedPorts(v850NetPortPP p, Uns32 variant) {
    while(*p && (*p)->desc.name && !((*p)->variantMask & variant)) {
        (*p)++;
    }
}

//
// Get the next net port
//
VMI_NET_PORT_SPECS_FN(v850NetPortSpecs) {
    v850P v850 = (v850P)processor;
    v850NetPortP c = (v850NetPortP)prev;
    Uns32 variant = v850->configInfo.arch;

    if(!c) {
        c = v850->netPorts;
    } else {
        c++;
    }
    skipUnusedPorts(&c, variant);

    return (vmiNetPortP)(c && (c->desc.name) ? c : 0);
}

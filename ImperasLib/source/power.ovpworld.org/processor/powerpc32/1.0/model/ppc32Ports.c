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
#include "ppc32Structure.h"
#include "ppc32Functions.h"
#include "ppc32Exceptions.h"
#include "ppc32Ports.h"

//
// Called by the simulator when an external reset is raised
//
static VMI_NET_CHANGE_FN(signalReset) {

    ppc32P ppc32 = (ppc32P)processor;
    Uns32  reset = newValue;

    if (reset == 0) {
        // jump to reset vector
        vmirtSetPCException((vmiProcessorP)ppc32, RESET_VECTOR);

        // take reset
        vmirtRestartNext(processor);
        vmirtDoSynchronousInterrupt(processor);
    }
}

typedef struct ppc32NetPortS {
    vmiNetPort desc;
    Uns32      variantMask;
} ppc32NetPort;

static Uns32 countPorts(ppc32NetPortP template, ppc32P ppc32) {
    ppc32NetPortP p = template;
    Uns32 c = 0;
    Uns32 variant = ppc32->configInfo.arch;

    while(p && p->desc.name) {
        if (p->variantMask & variant) {
            c++;
        }
        p++;
    }
    return c;
}

void ppc32NewNetPorts(ppc32P ppc32) {
    Uns32 variant = ppc32->configInfo.arch;

    ppc32NetPort template[] = {
            { {name : "reset", type : vmi_NP_INPUT, netChangeCB : signalReset }, ~0 },
            { { 0 } }
    };

    // count members
    Uns32 numMembers = countPorts(template, ppc32);
    Uns32 i, j;

    // allocate permanent port structure (including terminator)
    ppc32NetPortP result = STYPE_CALLOC_N(ppc32NetPort, numMembers+1);

    // fill permanent port structure
    for(j=0, i=0; i<NUM_MEMBERS(template); i++) {
        if(template[i].variantMask & variant) {
            result[j++] = template[i];
        }
    }

    // save ports on processor
    ppc32->netPorts = result;
}

//
// Free ports
//
void ppc32FreeNetPorts(ppc32P ppc32) {
    if(ppc32->netPorts) {
        STYPE_FREE(ppc32->netPorts);
        ppc32->netPorts = 0;
    }
}

//
// Get the next net port
//
VMI_NET_PORT_SPECS_FN(ppc32NetPortSpecs) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32NetPortP c = (ppc32NetPortP)prev;

    if(!c) {
        c = ppc32->netPorts;
    } else {
        c++;
    }

    return (vmiNetPortP)(c && (c->desc.name) ? c : 0);
}

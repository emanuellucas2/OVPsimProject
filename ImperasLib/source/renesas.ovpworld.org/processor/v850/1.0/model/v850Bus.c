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
#include "v850Bus.h"
#include "v850Functions.h"
#include "v850Structure.h"

static vmiBusPort busPorts[] = {
    // MWH relaxed min bus bits to 28 to match '3441 platform
    {"INSTRUCTION", vmi_BP_MASTER, vmi_DOM_CODE, {28,32}, 1 },
    {"DATA"       , vmi_BP_MASTER, vmi_DOM_DATA, {28,32}, 0 }
};

// This gives the number of bus ports
#define NUM_BUS_PORTS (sizeof(busPorts)/sizeof(busPorts[0]))

// Allocate bus port specifications
void v850NewBusPorts(v850P v850) {
    Uns32 i;

    v850->busPorts = STYPE_CALLOC_N(vmiBusPort, NUM_BUS_PORTS);
    for(i=0; i<NUM_BUS_PORTS; i++) {
        v850->busPorts[i] = busPorts[i];
    }
}

// Free bus port specifications
void v850FreeBusPorts(v850P v850) {
    if(v850->busPorts) {
        STYPE_FREE(v850->busPorts);
        v850->busPorts = 0;
    }
}

// Get the next bus port
VMI_BUS_PORT_SPECS_FN(v850BusPortSpecs) {
    v850P v850 = (v850P)processor;

    if(!prev) {
        // first port
        return v850->busPorts;
    } else {
        // port other than the first
        Uns32 prevIndex = (prev-v850->busPorts);
        Uns32 thisIndex = prevIndex+1;
        return (thisIndex<NUM_BUS_PORTS) ? &v850->busPorts[thisIndex] : 0;
    }
}

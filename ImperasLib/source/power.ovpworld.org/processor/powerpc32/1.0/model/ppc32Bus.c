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
#include "ppc32Bus.h"
#include "ppc32Functions.h"
#include "ppc32Structure.h"

static vmiBusPort busPorts[] = {
    {"INSTRUCTION", vmi_BP_MASTER, vmi_DOM_CODE, {32,32}, 1 },
    {"DATA"       , vmi_BP_MASTER, vmi_DOM_DATA, {32,32}, 0 }
};

// This gives the number of bus ports
#define NUM_BUS_PORTS (sizeof(busPorts)/sizeof(busPorts[0]))

// Allocate bus port specifications
void ppc32NewBusPorts(ppc32P ppc32) {
    Uns32 i;

    ppc32->busPorts = STYPE_CALLOC_N(vmiBusPort, NUM_BUS_PORTS);
    for(i=0; i<NUM_BUS_PORTS; i++) {
        ppc32->busPorts[i] = busPorts[i];
    }
}

// Free bus port specifications
void ppc32FreeBusPorts(ppc32P ppc32) {
    if(ppc32->busPorts) {
        STYPE_FREE(ppc32->busPorts);
        ppc32->busPorts = 0;
    }
}

// Get the next bus port
VMI_BUS_PORT_SPECS_FN(ppc32BusPortSpecs) {
    ppc32P ppc32 = (ppc32P)processor;

    if(!prev) {
        // first port
        return ppc32->busPorts;
    } else {
        // port other than the first
        Uns32 prevIndex = (prev-ppc32->busPorts);
        Uns32 thisIndex = prevIndex+1;
        return (thisIndex<NUM_BUS_PORTS) ? &ppc32->busPorts[thisIndex] : 0;
    }
}

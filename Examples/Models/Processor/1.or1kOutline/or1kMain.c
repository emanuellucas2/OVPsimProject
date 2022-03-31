/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


// Imperas header files
#include "hostapi/impAlloc.h"

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiMessage.h"

// model header files
#include "or1kStructure.h"
#include "or1kFunctions.h"


//
// Return number of members of an array
//
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))


////////////////////////////////////////////////////////////////////////////////
// BUS PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Template bus port list
//
const static vmiBusPort busPorts[] = {
    {"INSTRUCTION", vmi_BP_MASTER, vmi_DOM_CODE, {32,32}, 1},
    {"DATA"       , vmi_BP_MASTER, vmi_DOM_DATA, {32,32}, 0},
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

//
// OR1K processor constructor
//
VMI_CONSTRUCTOR_FN(or1kConstructor) {

    or1kP or1k = (or1kP)processor;

    vmiPrintf("%s called\n", FUNC_NAME);

    // create bus port specifications
    newBusPorts(or1k);
}

//
// OR1K processor destructor
//
VMI_DESTRUCTOR_FN(or1kDestructor) {

    or1kP or1k = (or1kP)processor;

    vmiPrintf("%s called\n", FUNC_NAME);

    // free bus port specifications
    freeBusPorts(or1k);
}


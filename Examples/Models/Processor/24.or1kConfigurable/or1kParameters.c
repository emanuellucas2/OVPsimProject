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
#include "vmi/vmiParameters.h"

#include "or1kFunctions.h"
#include "or1kParameters.h"

//
// Table of parameter specs
//
static vmiParameter formals[] = {
    // Default is NOT verbose
    VMI_BOOL_PARAM_SPEC  (  or1kParamValues, verbose,       0,       "Verbose mode"),

    // 1 to 8 interrupts, default=1
    VMI_UNS32_PARAM_SPEC (  or1kParamValues, extinterrupts, 1, 1, 8, "Number of external interrupts" ),

    // Optional log file
    VMI_STRING_PARAM_SPEC(  or1kParamValues, extintlogfile, 0,       "Event log file" ),

    // End of list
    VMI_END_PARAM
};


//
// Function to iterate the parameter specs
//
VMI_PROC_PARAM_SPECS_FN(or1kGetParamSpec) {
    if(!prev) {
        return formals;
    } else {
        prev++;
        if (prev->name)
            return prev;
        else
            return 0;
    }
}

//
// Get the size of the parameter values table
//
VMI_PROC_PARAM_TABLE_SIZE_FN(or1kParamValueSize) {
    return sizeof(or1kParamValues);
}



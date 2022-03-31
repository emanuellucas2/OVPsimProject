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
#include "vmi/vmiParameters.h"
#include "vmi/vmiMessage.h"

#include "or1kFunctions.h"
#include "or1kParameters.h"
#include "or1kStructure.h"

//
// Define the Generic variant
//
vmiEnumParameter variantList[] = {
    // name      value  description
    { "generic", 0 ,    "Single default variant"},
    { 0 },
};

//
// Table of parameter specs
//
static vmiParameter formals[] = {
    VMI_BOOL_PARAM_SPEC  (  or1kParamValues, fifos,   0,           "Turn on FIFO feature" ),
    VMI_BOOL_PARAM_SPEC  (  or1kParamValues, verbose, 0,           "Turn on model messages" ),

    VMI_ENUM_PARAM_SPEC  (  or1kParamValues, variant, variantList, "Processor variant"),

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



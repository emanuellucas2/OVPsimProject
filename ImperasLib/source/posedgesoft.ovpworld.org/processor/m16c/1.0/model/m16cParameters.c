/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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

#include "m16cFunctions.h"
#include "m16cParameters.h"
#include "m16cStructure.h"
#include "m16cVariant.h"

static vmiEnumParameter variantValues[] = {
    {"m16c",   VAR_M16C   },
    {"r8c",    VAR_R8C    },
    {0}
};

static vmiEnumParameter compatTable[] = {
    {"isa",    COMPAT_ISA},
    {"gdb",    COMPAT_GDB},
    {"nopbrk", COMPAT_NOPBRK},
    { 0, 0 }
};

//
// Table of parameter specs
//
static vmiParameter formals[] = {
    VMI_ENUM_PARAM_SPEC(m16cParamValues, variant,          variantValues, "Selects variant (either a generic ISA or a specific model)"),
    VMI_ENUM_PARAM_SPEC(m16cParamValues, compatibility,    compatTable,   "Specify compatibility mode"),
    VMI_BOOL_PARAM_SPEC(m16cParamValues, verbose,          1,             "Specify verbose output messages"),
    VMI_END_PARAM
};


//
// Function to iterate the parameter specs
//
VMI_PROC_PARAM_SPECS_FN(m16cGetParamSpec) {
    if (!prev) {
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
VMI_PROC_PARAM_TABLE_SIZE_FN(m16cParamValueSize) {
    return sizeof(m16cParamValues);
}



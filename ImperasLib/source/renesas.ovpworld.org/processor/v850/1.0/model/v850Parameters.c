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

#include "hostapi/impAlloc.h"

#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"
#include "vmi/vmiMessage.h"

#include "v850Functions.h"
#include "v850Parameters.h"
#include "v850Structure.h"
#include "v850Variant.h"


//
// Table of parameter specs
//
static vmiParameter formals[] = {
    VMI_ENUM_PARAM_SPEC(v850ParamValues,  variant,    0,     "Selects variant (either a generic ISA or a specific model)"),
    VMI_BOOL_PARAM_SPEC(v850ParamValues,  verbose,    True,  "Specify verbose output messages"),
    VMI_BOOL_PARAM_SPEC(v850ParamValues,  GDBSIMMODE, False, "GDB Simulator Compatibility Mode"),
    VMI_BOOL_PARAM_SPEC(v850ParamValues,  nofpu,      False, "Disable Processor Internal FPU"),
    VMI_UNS32_PARAM_SPEC(v850ParamValues, RBASE,      0,     0x00000000, 0xFFFFFFFF, "RBASE register Reset vector Address"),
    VMI_BOOL_PARAM_SPEC(v850ParamValues,  ucbank,     False, "Enable the User Compatible Bank Registers (eg, VFOREST)"),
    VMI_UNS32_PARAM_SPEC(v850ParamValues, PEID,       1,     1, 3, "Processor element number"),
    VMI_UNS32_PARAM_SPEC(v850ParamValues, SPID,       0,     0x00, 0xFF, "System Protection Number"),
    VMI_END_PARAM
};

static Uns32 countVariants(void) {
    v850ConfigCP cfg = v850ConfigTable;
    Uns32 i = 0;
    while(cfg->name) {
        cfg++;
        i++;
    }
    return i;
}

//
// First time through, malloc and fill the variant list from the config table
//
static vmiEnumParameterP getVariantList() {
    static vmiEnumParameterP list = NULL;
    if (!list) {
        Uns32 v = 1 + countVariants();
        list = STYPE_CALLOC_N(vmiEnumParameter, v);
        vmiEnumParameterP prm;
        v850ConfigCP cfg;
        Uns32 i;
        for (i = 0, cfg = v850ConfigTable, prm = list;
             cfg->name;
             i++, cfg++, prm++) {
            prm->name = cfg->name;
            prm->value = i;
        }
    }
    return list;
}

//
// First time through, fill the formals table
//
static vmiParameterP getFormals(void) {
    static Bool first = True;
    if(first) {
        first = False;
        formals[0].u.enumParam.legalValues = getVariantList();
    }
    return formals;
}


//
// Function to iterate the parameter specs
//
VMI_PROC_PARAM_SPECS_FN(v850ParamSpecs) {
    if(!prev) {
        return getFormals();
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
VMI_PROC_PARAM_TABLE_SIZE_FN(v850ParamValueSize) {
    return sizeof(v850ParamValues);
}


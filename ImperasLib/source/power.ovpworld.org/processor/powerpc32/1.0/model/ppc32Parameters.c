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

#include "ppc32Functions.h"
#include "ppc32Parameters.h"
#include "ppc32Structure.h"
#include "ppc32Variant.h"


//
// Table of parameter specs
//
static vmiParameter formals[] = {
    VMI_ENUM_PARAM_SPEC(ppc32ParamValues, variant, 0, "Selects variant (either a generic UISA or a specific model)"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, verbose, True, "Specify verbose output messages"),
    VMI_ENDIAN_PARAM_SPEC(ppc32ParamValues, endian,   "Specify Model endian"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_B, False, "UISA Feature UISA_I_B"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_BCDA, False, "UISA Feature UISA_I_BCDA"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_S, False, "UISA Feature UISA_I_S"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_E, False, "UISA Feature UISA_I_E"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_E_PC, False, "UISA Feature UISA_I_E_PC"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_E_PD, False, "UISA Feature UISA_I_E_PD"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_EC, False, "UISA Feature UISA_I_EC"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_FP, False, "UISA Feature UISA_I_FP"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_DFP, False, "UISA Feature UISA_I_DFP"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_MA, False, "UISA Feature UISA_I_MA"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_SP, False, "UISA Feature UISA_I_SP"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_V, False, "UISA Feature UISA_I_V"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_LMA, False, "UISA Feature UISA_I_LMA"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_WT, False, "UISA Feature UISA_I_WT"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UISA_I_VLE, False, "UISA Feature UISA_I_VLE"),
    VMI_UNS32_PARAM_SPEC(ppc32ParamValues, ENABLE_FPU, 0, 0, 1, "Enable FPU At Startup"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, UNIMP_TO_NOP, False, "Map Unimplemented Instructions to NOP"),
    VMI_BOOL_PARAM_SPEC(ppc32ParamValues, WARN_NOP, False, "Warn when executing nop-mapped instructions"),
    VMI_END_PARAM
};

static Uns32 countVariants(void) {
    ppc32ConfigCP cfg = ppc32ConfigTable;
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
        ppc32ConfigCP cfg;
        Uns32 i;
        for (i = 0, cfg = ppc32ConfigTable, prm = list;
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
VMI_PROC_PARAM_SPECS_FN(ppc32ParamSpecs) {
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
VMI_PROC_PARAM_TABLE_SIZE_FN(ppc32ParamValueSize) {
    return sizeof(ppc32ParamValues);
}


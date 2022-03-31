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

// standard header files
#include <string.h>

// Imperas header files
#include "hostapi/impAlloc.h"

// VMI area includes
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiMessage.h"

// base model header files
#include "riscvConfig.h"
#include "riscvStructure.h"

// model header files
#include "sifiveConfig.h"
#include "sifiveCSR.h"
#include "sifiveDoc.h"
#include "sifiveFunctions.h"
#include "sifiveMessage.h"
#include "sifiveMorph.h"
#include "sifiveStructure.h"
#include "sifiveUtils.h"


////////////////////////////////////////////////////////////////////////////////
// PARAMETERS
////////////////////////////////////////////////////////////////////////////////

//
// Parameter value structure
//
typedef struct paramValuesS {

    // CSR configuration
    VMI_BOOL_PARAM(FeatureDisable_Present);         // Feature Disable CSR present
    VMI_BOOL_PARAM(BranchPredictionMode_Present);   // Branch Prediction Mode CSR present
    VMI_BOOL_PARAM(PowerDial_Present);              // PowerDial CSR present

    // ISA configuration
    VMI_BOOL_PARAM(CFLUSH_Present);                 // CFLUSH instruction present
    VMI_BOOL_PARAM(CEASE_Present);                  // CEASE instruction present

} paramValues, *paramValuesP;

//
// This function type is used to specify the default value for a parameter
//
#define SIFIVE_PDEFAULT_FN(_NAME) void _NAME( \
    riscvP         riscv,   \
    sifiveConfigCP cfg,     \
    vmiParameterP  param    \
)
typedef SIFIVE_PDEFAULT_FN((*sifivePDefaultFn));

//
// Parameter list including variant information
//
typedef struct riscvParameterS {
    sifivePDefaultFn defaultCB;
    vmiParameter     parameter;
} riscvParameter, *riscvParameterP;

//
// Validate parameter type
//
#define CHECK_PARAM_TYPE(_P, _T, _NAME) VMI_ASSERT( \
    _P->type==_T,                                   \
    "parameter %s is not of "_NAME" type",          \
    _P->name                                        \
)

//
// Set Bool parameter default
//
static void setBoolParamDefault(vmiParameterP param, Uns32 value) {
    CHECK_PARAM_TYPE(param, vmi_PT_BOOL, "Bool");
    param->u.boolParam.defaultValue = value;
}

//
// Macro to define a function to set a Boolean parameter from the SiFive variant
//
#define SIFIVE_BOOL_PDEFAULT_VAR_FN(_NAME, _MIMPID_MSB_MIN) SIFIVE_PDEFAULT_FN(default_##_NAME) { \
                                                            \
    Bool defValue = (                                       \
        (cfg->variant & S5V_##_NAME) &&                     \
        (RD_CSR(riscv, mimpid) >= ((_MIMPID_MSB_MIN)<<24))  \
    );                                                      \
                                                            \
    setBoolParamDefault(param, defValue);                   \
}

//
// Set default value of variant Booleans
//
static SIFIVE_BOOL_PDEFAULT_VAR_FN(FDCP,   0x00)
static SIFIVE_BOOL_PDEFAULT_VAR_FN(BPM,    0x00)
static SIFIVE_BOOL_PDEFAULT_VAR_FN(PWRD,   0x05)
static SIFIVE_BOOL_PDEFAULT_VAR_FN(CFLUSH, 0x00)
static SIFIVE_BOOL_PDEFAULT_VAR_FN(CEASE,  0x00)

//
// Table of formal parameter specifications
//
static riscvParameter formals[] = {

    // CSR configuration
    {default_FDCP,   VMI_BOOL_PARAM_SPEC (paramValues, FeatureDisable_Present,       0, "Specify whether Feature Disable CSR present")},
    {default_BPM,    VMI_BOOL_PARAM_SPEC (paramValues, BranchPredictionMode_Present, 0, "Specify whether Branch Prediction Mode CSR present")},
    {default_PWRD,   VMI_BOOL_PARAM_SPEC (paramValues, PowerDial_Present,            0, "Specify whether PowerDial CSR present")},

    // ISA configuration
    {default_CFLUSH, VMI_BOOL_PARAM_SPEC (paramValues, CFLUSH_Present,               0, "Specify whether CFLUSH.D.L1 and CDISCARD.D.L1 instructions present")},
    {default_CEASE,  VMI_BOOL_PARAM_SPEC (paramValues, CEASE_Present,                0, "Specify whether CEASE instruction present")},

    // KEEP LAST
    {0,              VMI_END_PARAM}
};

//
// Should this parameter be presented as a public one for the selected variant?
//
static Bool selectParameter(sifiveConfigCP cfg, riscvParameterP param) {
    return True;
}

//
// Count the number of visible parameters
//
static Uns32 countParameters(sifiveConfigCP cfg, riscvParameterP param) {

    Uns32 i = 0;

    while(param->parameter.name) {

        if(selectParameter(cfg, param)) {
            i++;
        }

        param++;
    }

    return i;
}

//
// Create parameter list applicable to the indicated variant
//
static vmiParameterP createParameterList(
    riscvP         riscv,
    vmiosObjectP   object,
    sifiveConfigCP cfg
) {
    riscvParameterP src = formals;
    vmiParameterP   dst;
    vmiParameterP   result;
    Uns32           i;

    // count the number of entries in the parameter list
    Uns32 entries = countParameters(cfg, src);

    // allocate the parameter list, including NULL terminator
    result = STYPE_CALLOC_N(vmiParameter, entries+1);

    // fill visible entries in the variant list
    for(i=0, dst=result; src->parameter.name; i++, src++) {

        if(selectParameter(cfg, src)) {

            *dst = src->parameter;

            // override default if required
            if(src->defaultCB) {
                src->defaultCB(riscv, cfg, dst);
            }

            dst++;
        }
    }

    // return resulting list
    return result;
}

//
// Is the processor a root level parameterisable object?
//
static Bool isRootParamCxt(riscvP riscv, vmiosObjectP parent) {

    if(sifiveIsCluster(riscv)) {

        // no parameters at cluster level
        return False;

    } else if(parent && sifiveIsCluster(parent->riscv)) {

        // root level beneath cluster
        return True;

    } else {

        // parameters at root level only
        return !parent;
    }
}

//
// Iterate formals
//
static VMIOS_PARAM_SPEC_FN(getParamSpecs) {

    riscvP riscv = (riscvP)processor;

    if(!isRootParamCxt(riscv, parent)) {

        // no child objects have parameters

    } else if(!object->parameters) {

        // create parameter definition list if required
        sifiveConfigCP cfg = sifiveExtConfig(riscv);

        object->parameters = createParameterList(riscv, object, cfg);
    }

    vmiParameterP this = prev ? prev+1 : object->parameters;

    return (this && this->name) ? this : 0;
}

//
// Return size of parameter structure
//
static VMIOS_PARAM_TABLE_SIZE_FN(getParamTableSize) {

    riscvP riscv = (riscvP)processor;

    return isRootParamCxt(riscv, parent) ? sizeof(paramValues) : 0;
}


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Update configured variant using parameter value
//
#define APPLY_BOOL_PDEFAULT_VAR(_O, _P, _VNAME, _PNAME) \
    if((_P)->_PNAME) {                  \
        (_O)->variant |= S5V_##_VNAME;  \
    }

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    riscvP riscv = (riscvP)processor;

    // save processor on object for later use
    object->riscv = riscv;

    // inherit variant from any non-cluster parent
    if(parent && !sifiveIsCluster(parent->riscv)) {
        object->variant = parent->variant;
    }

    // handle parameters if a parameter context
    if(isRootParamCxt(riscv, parent)) {

        paramValuesP params = parameterValues;

        // apply variant parameters
        APPLY_BOOL_PDEFAULT_VAR(object, params, FDCP,   FeatureDisable_Present);
        APPLY_BOOL_PDEFAULT_VAR(object, params, BPM,    BranchPredictionMode_Present);
        APPLY_BOOL_PDEFAULT_VAR(object, params, PWRD,   PowerDial_Present);
        APPLY_BOOL_PDEFAULT_VAR(object, params, CFLUSH, CFLUSH_Present);
        APPLY_BOOL_PDEFAULT_VAR(object, params, CEASE,  CEASE_Present);
    }

    // initialize state on leaf processors only
    if(sifiveIsLeaf(riscv)) {

        // prepare client data
        object->extCB.clientData = object;

        // initialize CSR state
        sifiveCSRInit(object);

        // register extension with base model
        riscv->cb.registerExtCB(riscv, &object->extCB, SIFIVE_OVP_CONFIG_ID);
    }
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {

    if(object->parameters) {
        STYPE_FREE(object->parameters);
    }
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,              // version string
    .modelType      = VMI_INTERCEPT_LIBRARY,    // type
    .packageName    = "sifiveExtensions",       // name
    .objectSize     = sizeof(vmiosObject),      // size in bytes of OSS object
    .allLevels      = True,                     // apply at all levels

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "sifive.ovpworld.org",
        .library = "intercept",
        .name    = "sifiveExtensions",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,          // object constructor
    .destructorCB   = destructor,           // object destructor
    .docCB          = sifiveDoc,            // doc constructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB = sifiveMorph,                 // morph override callback
    .disCB   = sifiveDisassemble,           // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,      // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,  // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        {0}
    }
};

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
#include "riscvExceptionDefinitions.h"
#include "riscvStructure.h"

// model header files
#include "andesACE.h"
#include "andesConfig.h"
#include "andesCustomPhases.h"
#include "andesCSR.h"
#include "andesDoc.h"
#include "andesExceptions.h"
#include "andesFunctions.h"
#include "andesMessage.h"
#include "andesMorph.h"
#include "andesStructure.h"
#include "andesUtils.h"


////////////////////////////////////////////////////////////////////////////////
// DUMMY IMPLEMENTATION CALLBACK
////////////////////////////////////////////////////////////////////////////////

//
// Helper macro for defining register implementations
//
#define ANDES_REG_IMPL_RAW(_REG, _FIELD, _BITS) \
    vmirtRegImplRaw(processor, _REG, _FIELD, _BITS)

//
// Helper macro for defining field-to register mappings
//
#define ANDES_FIELD_IMPL_RAW(_OBJECT, _REGINFO, _FIELD) { \
    Uns32  bits  = sizeof(object->_FIELD) * 8;                  \
    vmiReg field = andesObjectReg(object, EXT_REG(_FIELD));     \
    ANDES_REG_IMPL_RAW(_REGINFO, field, bits);                  \
}

//
// Helper macro for defining ignored fields
//
#define ANDES_FIELD_IMPL_IGNORE(_OBJECT, _FIELD) \
    ANDES_FIELD_IMPL_RAW(_OBJECT, 0, _FIELD)

//
// Specify vmiReg-to-vmiRegInfoCP correspondence for registers for which this
// cannot be automatically derived
//
static VMIOS_REG_IMPL_FN(andesRegImpl) {

    // exclude artifact registers
    ANDES_FIELD_IMPL_IGNORE(object, oldSP);
}


////////////////////////////////////////////////////////////////////////////////
// EXCEPTION DEFINITIONS
////////////////////////////////////////////////////////////////////////////////

//
// Fill one member of exceptions
//
#define ANDES_EXCEPTION(_NAME, _DESC) { \
    name:#_NAME, code:andes_E_##_NAME, description:_DESC,    \
}

//
// Table of exception descriptions
//
static const vmiExceptionInfo exceptions[] = {

    ////////////////////////////////////////////////////////////////////
    // EXCEPTIONS
    ////////////////////////////////////////////////////////////////////

    ANDES_EXCEPTION (HSP_OVF, "Stack overflow"),
    ANDES_EXCEPTION (HSP_UDF, "Stack underflow"),

    ////////////////////////////////////////////////////////////////////
    // TERMINATOR
    ////////////////////////////////////////////////////////////////////

    {0}
};


////////////////////////////////////////////////////////////////////////////////
// EXCEPTION ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Return the first exception implemented by the derived model
//
static RISCV_FIRST_EXCEPTION_FN(firstException) {
    return exceptions;
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CONFIGURATION ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Return Andes Ovpworld extension configuration for RISC-V processor
//
static andesConfigCP getAndesConfig(riscvP riscv) {
    riscvExtConfigCP cfg = riscv->cb.getExtConfig(riscv, ANDES_OVP_CONFIG_ID);
    VMI_ASSERT(cfg, "No Config with id 0x%x found", ANDES_OVP_CONFIG_ID);
    return cfg->userData;
}


////////////////////////////////////////////////////////////////////////////////
// PARAMETERS
////////////////////////////////////////////////////////////////////////////////

//
// Parameter value structure
//
typedef struct paramValuesS {

    // simulation controls
    VMI_UNS32_PARAM(PMA_grain);

    // ISA configuration
    VMI_UNS64_PARAM(milmb);
    VMI_UNS64_PARAM(mdlmb);
    VMI_UNS64_PARAM(mmsc_cfg);
    VMI_UNS64_PARAM(micm_cfg);
    VMI_UNS64_PARAM(mdcm_cfg);
    VMI_UNS32_PARAM(mvec_cfg);
    VMI_UNS64_PARAM(uitb);
    VMI_UNS64_PARAM(ml2c_ctl_base);
    VMI_UNS64_PARAM(milmbMask);
    VMI_UNS64_PARAM(mdlmbMask);

    // ACE extension
    VMI_STRING_PARAM(aceFile);

} paramValues, *paramValuesP;

//
// This function type is used to specify the default value for a parameter
//
#define ANDES_PDEFAULT_FN(_NAME) void _NAME(andesConfigCP cfg, vmiParameterP param)
typedef ANDES_PDEFAULT_FN((*andesPDefaultFn));

//
// Parameter list including variant information
//
typedef struct riscvParameterS {
    andesPDefaultFn defaultCB;
    vmiParameter    parameter;
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
// Set Uns32 parameter default
//
static void setUns32ParamDefault(vmiParameterP param, Uns32 value) {
    CHECK_PARAM_TYPE(param, vmi_PT_UNS32, "Uns32");
    param->u.uns32Param.defaultValue = value;
}

//
// Set Uns64 parameter default
//
static void setUns64ParamDefault(vmiParameterP param, Uns64 value) {
    CHECK_PARAM_TYPE(param, vmi_PT_UNS64, "Uns64");
    param->u.uns64Param.defaultValue = value;
}

//
// Macro to define a function to set an Uns64 CSR parameter value from the
// configuration
//
#define ANDES_UNS32_PDEFAULT_CFG_FN(_NAME) ANDES_PDEFAULT_FN(default_##_NAME) { \
    setUns32ParamDefault(param, cfg->_NAME);  \
}

//
// Macro to define a function to set an Uns64 CSR parameter value from the
// configuration
//
#define ANDES_CSR64_PDEFAULT_CFG_FN(_NAME) ANDES_PDEFAULT_FN(default_##_NAME) { \
    setUns64ParamDefault(param, cfg->csr._NAME.u64.bits);  \
}

//
// Macro to define a function to set an Uns32 CSR parameter value from the
// configuration
//
#define ANDES_CSR32_PDEFAULT_CFG_FN(_NAME) ANDES_PDEFAULT_FN(default_##_NAME) { \
    setUns32ParamDefault(param, cfg->csr._NAME.u32.bits);  \
}

//
// Macro to define a function to set an Uns64 CSR parameter mask value from the
// configuration
//
#define ANDES_CSRM_PDEFAULT_CFG_FN(_NAME) ANDES_PDEFAULT_FN(default_##_NAME##Mask) { \
    setUns64ParamDefault(param, cfg->csrMask._NAME.u64.bits);  \
}

//
// Set default value of raw Uns32 parameters
//
static ANDES_UNS32_PDEFAULT_CFG_FN(PMA_grain)

//
// Set default value of CSR parameters
//
static ANDES_CSR64_PDEFAULT_CFG_FN(milmb)
static ANDES_CSR64_PDEFAULT_CFG_FN(mdlmb)
static ANDES_CSR64_PDEFAULT_CFG_FN(mmsc_cfg)
static ANDES_CSR64_PDEFAULT_CFG_FN(micm_cfg)
static ANDES_CSR64_PDEFAULT_CFG_FN(mdcm_cfg)
static ANDES_CSR32_PDEFAULT_CFG_FN(mvec_cfg)
static ANDES_CSR64_PDEFAULT_CFG_FN(uitb)
static ANDES_CSR64_PDEFAULT_CFG_FN(ml2c_ctl_base)

//
// Set default value of CSR masks
//
static ANDES_CSRM_PDEFAULT_CFG_FN(milmb)
static ANDES_CSRM_PDEFAULT_CFG_FN(mdlmb)

//
// Table of formal parameter specifications
//
static riscvParameter formals[] = {

    // simulation controls
    {default_PMA_grain,     VMI_UNS32_PARAM_SPEC (paramValues, PMA_grain,     0, 0, 29, "Specify PMA region granularity, G (0 => 4 bytes, 1 => 8 bytes, etc)")},

    // ISA configuration
    {default_milmb,         VMI_UNS64_PARAM_SPEC (paramValues, milmb,         0, 0, -1, "Override milmb register")},
    {default_mdlmb,         VMI_UNS64_PARAM_SPEC (paramValues, mdlmb,         0, 0, -1, "Override mdlmb register")},
    {default_mmsc_cfg,      VMI_UNS64_PARAM_SPEC (paramValues, mmsc_cfg,      0, 0, -1, "Override mmsc_cfg register")},
    {default_micm_cfg,      VMI_UNS64_PARAM_SPEC (paramValues, micm_cfg,      0, 0, -1, "Override micm_cfg register")},
    {default_mdcm_cfg,      VMI_UNS64_PARAM_SPEC (paramValues, mdcm_cfg,      0, 0, -1, "Override mdcm_cfg register")},
    {default_mvec_cfg,      VMI_UNS32_PARAM_SPEC (paramValues, mvec_cfg,      0, 0, -1, "Override mvec_cfg register (ignored if mdcm_cfg.veccfg=0)")},
    {default_uitb,          VMI_UNS64_PARAM_SPEC (paramValues, uitb,          0, 0, -1, "Override uitb register")},
    {default_ml2c_ctl_base, VMI_UNS64_PARAM_SPEC (paramValues, ml2c_ctl_base, 0, 0, -1, "Override ml2c_ctl_base register (ignored if mmsc_cfg.L2CMP_CFG and .L2C are 0")},
    {default_milmbMask,     VMI_UNS64_PARAM_SPEC (paramValues, milmbMask,     0, 0, -1, "Override milmb register writable bit mask")},
    {default_mdlmbMask,     VMI_UNS64_PARAM_SPEC (paramValues, mdlmbMask,     0, 0, -1, "Override mdlmb register writable bit mask")},

    // ACE extension
    {0,                     VMI_STRING_PARAM_SPEC(paramValues, aceFile,       0,        "Specify ACE extension shared object")},

    // KEEP LAST
    {0,                     VMI_END_PARAM}
};

//
// Should this parameter be presented as a public one for the selected variant?
//
static Bool selectParameter(andesConfigCP cfg, riscvParameterP param) {
    return True;
}

//
// Count the number of visible parameters
//
static Uns32 countParameters(andesConfigCP cfg, riscvParameterP param) {

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
    riscvP        riscv,
    vmiosObjectP  object,
    andesConfigCP cfg
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
                src->defaultCB(cfg, dst);
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

    if(andesIsCluster(riscv)) {

        // no parameters at cluster level
        return False;

    } else if(parent && andesIsCluster(parent->riscv)) {

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
        andesConfigCP cfg = getAndesConfig(riscv);

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
// NET PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Get additional ports on this extension
//
static VMIOS_NET_PORT_SPECS_FN(getNetPorts) {

    riscvNetPortP this;

    if(!prev) {
        this = object->netPorts;
    } else {
        this = ((riscvNetPortP)prev)->next;
    }

    return this ? &this->desc : 0;
}


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    riscvP riscv = (riscvP)processor;

    // save processor on object for later use
    object->riscv = riscv;

    // inherit CSR defaults and ACE extension file from any non-cluster parent
    if(parent && !andesIsCluster(parent->riscv)) {
        object->csrDefaults = parent->csrDefaults;
        object->aceFile     = parent->aceFile;
    }

    // handle parameters if a parameter context
    if(isRootParamCxt(riscv, parent)) {

        paramValuesP params = parameterValues;

        // save simulation control defaults
        object->csrDefaults.PMA_grain = params->PMA_grain;

        // save CSR defaults
        object->csrDefaults.csr.milmb.u64.bits         = params->milmb;
        object->csrDefaults.csr.mdlmb.u64.bits         = params->mdlmb;
        object->csrDefaults.csr.mmsc_cfg.u64.bits      = params->mmsc_cfg;
        object->csrDefaults.csr.micm_cfg.u64.bits      = params->micm_cfg;
        object->csrDefaults.csr.mdcm_cfg.u64.bits      = params->mdcm_cfg;
        object->csrDefaults.csr.mvec_cfg.u32.bits      = params->mvec_cfg;
        object->csrDefaults.csr.uitb.u64.bits          = params->uitb;
        object->csrDefaults.csr.ml2c_ctl_base.u64.bits = params->ml2c_ctl_base;

        // save CSR mask defaults
        object->csrDefaults.csrMask.milmb.u64.bits = params->milmbMask;
        object->csrDefaults.csrMask.mdlmb.u64.bits = params->mdlmbMask;

        // save ACE extension file
        object->aceFile = params->aceFile;
    }

    // initialize state on leaf processors only
    if(andesIsLeaf(riscv)) {

        riscvConfigP   cfg = &riscv->configInfo;
        riscvVectorSet V   = cfg->vect_profile;

        // prepare client data
        object->extCB.clientData = object;

        // initialize base model callbacks
        object->extCB.firstException = firstException;
        object->extCB.getHandlerPC   = andesGetHandlerPC;
        object->extCB.preMorph       = andesPreMorph;
        object->extCB.postMorph      = andesPostMorph;
        object->extCB.installPhysMem = andesInstallPhysicalMem;
        object->extCB.PMAEnable      = andesPMAEnable;
        object->extCB.PMACheck       = andesPMACheck;

        // initialize CSR state
        andesCSRInit(object);

        // register extension with base model
        riscv->cb.registerExtCB(riscv, &object->extCB, ANDES_OVP_CONFIG_ID);

        // add HSP exceptions to the recognised set if required (after CSR reset)
        if(RD_XCSR_FIELD(object, mmsc_cfg, HSP)) {
            riscv->exceptionMask |= 1ULL<<andes_E_HSP_OVF;
            riscv->exceptionMask |= 1ULL<<andes_E_HSP_UDF;
        }

        // enable Flt16 support if mmsc_cfg.ZFH=1
        if(RD_XCSR_FIELD(object, mmsc_cfg, ZFH)) {
            cfg->fp16_version = RVFP16_IEEE754;
        }

        // include half-precision vector instructions if required
        if(cfg->fp16_version && (V&RVVS_F)) {
            V |= RVVS_H;
        }

        cfg->vect_profile = V;

        // initialize mvec_cfg.MISEW
        Uns32 MISEW = (V&RVVS_EEW64) ? 2 : 1;
        WR_XCSR_FIELD(object, mvec_cfg, MISEW, MISEW);

        // initialize mvec_cfg.MISEW
        Uns32 MFSEW = (V&RVVS_D) ? 2 : (V&RVVS_F) ? 1 : 0;
        WR_XCSR_FIELD(object, mvec_cfg, MFSEW, MFSEW);

        // add ports required for exception state management
        andesNewExceptionPorts(object);

        // initialize ACE extension state
        andesACEInit(object);

        // do custom initialization
        #if defined(CUSTOMFILE)
            #define ANDES_CUSTOM_PHASE ANDES_CUSTOM_INIT
            #include CUSTOMFILE
            #undef ANDES_CUSTOM_PHASE
        #endif
    }
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {

    // free ACE extension state
    andesACEFree(object);

    // free CSR state
    andesCSRFree(object);

    // free port state
    andesFreeExceptionPorts(object);

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
    .packageName    = "andesExtensions",        // name
    .objectSize     = sizeof(vmiosObject),      // size in bytes of OSS object
    .allLevels      = True,                     // apply at all levels

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "andes.ovpworld.org",
        .library = "intercept",
        .name    = "andesExtensions",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,          // object constructor
    .destructorCB   = destructor,           // object destructor
    .docCB          = andesDoc,             // doc constructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB = andesMorph,                  // morph override callback
    .disCB   = andesDisassemble,            // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // DEBUGGER INTEGRATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .regImplCB = andesRegImpl,              // vmiReg-to-vmiRegInfoCP callback

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,      // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,  // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // PORT ACCESS ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .netPortSpecsCB = getNetPorts,          // get net ports

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        {0}
    }
};

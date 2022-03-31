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

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"

// model header files
#include "openhwConfig.h"
#include "openhwExceptions.h"
#include "openhwMessage.h"
#include "openhwStructure.h"
#include "openhwUtils.h"

// base model header files
#include "riscvMessage.h"
#include "riscvStructure.h"
#include "riscvMode.h"
#include "riscvVMUtils.h"


////////////////////////////////////////////////////////////////////////////////
// EXTENSION PARAMETERS
////////////////////////////////////////////////////////////////////////////////

//
// Define parameter set for one PMA region
//
#define PMA_PARAM_SET(_N) \
    VMI_UNS32_PARAM(word_addr_low##_N);     \
    VMI_UNS32_PARAM(word_addr_high##_N);    \
    VMI_BOOL_PARAM(main##_N);               \
    VMI_BOOL_PARAM(bufferable##_N);         \
    VMI_BOOL_PARAM(cacheable##_N);          \
    VMI_BOOL_PARAM(atomic##_N);


typedef struct paramValuesS {

    // common parameters
    VMI_BOOL_PARAM(debug);

    // PMA region parameters
    VMI_UNS32_PARAM(PMA_NUM_REGIONS);
    PMA_PARAM_SET(0);
    PMA_PARAM_SET(1);
    PMA_PARAM_SET(2);
    PMA_PARAM_SET(3);
    PMA_PARAM_SET(4);
    PMA_PARAM_SET(5);
    PMA_PARAM_SET(6);
    PMA_PARAM_SET(7);
    PMA_PARAM_SET(8);
    PMA_PARAM_SET(9);
    PMA_PARAM_SET(10);
    PMA_PARAM_SET(11);
    PMA_PARAM_SET(12);
    PMA_PARAM_SET(13);
    PMA_PARAM_SET(14);
    PMA_PARAM_SET(15);

} paramValues, *paramValuesP;


////////////////////////////////////////////////////////////////////////////////
// PMA UPDATE
////////////////////////////////////////////////////////////////////////////////

//
// Initialise static PMA region
//
#define INIT_PMA(_N) initPMA( \
    object,                     \
    _N,                         \
    params->word_addr_low##_N,  \
    params->word_addr_high##_N, \
    params->main##_N,           \
    params->bufferable##_N,     \
    params->cacheable##_N,      \
    params->atomic##_N          \
)

//
// Initialise static PMA region
//
static void initPMA(
    vmiosObjectP object,
    Uns32        index,
    Uns64        word_addr_low,
    Uns64        word_addr_high,
    Bool         main,
    Bool         bufferable,
    Bool         cacheable,
    Bool         atomic
) {
    PMARegionP region = &object->PMARegions[index];

    region->word_addr_low  = word_addr_low<<2;
    region->word_addr_high = word_addr_high<<2;
    region->main           = main;
    region->bufferable     = bufferable;
    region->cacheable      = cacheable;
    region->atomic         = atomic;
}

//
// Indicate whether PMA protection is implemented
//
static RISCV_PMA_ENABLE_FN(openhwPMAEnable) {

    vmiosObjectP object = clientData;

    return object->PMA_NUM_REGIONS;
}

//
// Return privilege name for the given privilege
//
static const char *privName(memPriv priv) {

    static const char *map[2][2][8] = {
        {
            {"-----", "r----", "-w---", "rw---", "--x--", "r-x--", "-wx--", "rwx--"},
            {"----A", "r---A", "-w--A", "rw--A", "--x-A", "r-x-A", "-wx-A", "rwx-A"},
        },
        {
            {"---U-", "r--U-", "-w-U-", "rw-U-", "--xU-", "r-xU-", "-wxU-", "rwxU-"},
            {"---UA", "r--UA", "-w-UA", "rw-UA", "--xUA", "r-xUA", "-wxUA", "rwxUA"},
        }
    };

    Bool atomic    = !(priv&MEM_PRIV_USER1);
    Bool unaligned = !(priv&MEM_PRIV_ALIGN);

    // ignore atomic and alignment constraints
    priv &= ~(MEM_PRIV_ALIGN|MEM_PRIV_USER1);

    // sanity check given privilege
    VMI_ASSERT(priv<8, "unexpected privilege %u", priv);

    return map[unaligned][atomic][priv];
}

//
// Set privileges in the given domain set
//
static void setDomainPriv(
    riscvP            riscv,
    riscvDomainSetBMP domainSetB,
    Uns64             low,
    Uns64             high,
    memPriv           priv,
    const char       *name,
    Bool              verbose
) {
    riscvMode mode;

    // emit debug if required
    if(verbose && RISCV_DEBUG_MMU(riscv)) {
        vmiPrintf(
            "%s PRIV=%s 0x"FMT_6408x":0x"FMT_6408x"\n",
            name, privName(priv), low, high
        );
    }

    for(mode=RISCV_MODE_S; mode<RISCV_MODE_LAST_BASE; mode++) {

        memDomainP dataDomain = (*domainSetB)[mode][0];
        memDomainP codeDomain = (*domainSetB)[mode][1];

        if(mode==RISCV_MODE_H) {

            // ignore artifact mode

        } else if(dataDomain==codeDomain) {

            // set permissions in unified domain
            vmirtProtectMemory(dataDomain, low, high, priv, MEM_PRIV_SET);

        } else {

            // set permissions in data domain if required
            if((priv==MEM_PRIV_NONE) || (priv&MEM_PRIV_RW)) {
                vmirtProtectMemory(
                    dataDomain, low, high, priv&MEM_PRIV_RW, MEM_PRIV_SET
                );
            }

            // set permissions in code domain if required
            if((priv==MEM_PRIV_NONE) || (priv&MEM_PRIV_X)) {
                vmirtProtectMemory(
                    codeDomain, low, high, priv&MEM_PRIV_X, MEM_PRIV_SET
                );
            }
        }
    }
}

//
// Set privileges in PMA domain
//
static void setPMAPriv(
    riscvP  riscv,
    Uns64   low,
    Uns64   high,
    memPriv priv,
    Bool    verbose
) {
    setDomainPriv(riscv, &riscv->pmaDomains, low, high, priv, "PMA", verbose);
}

//
// Return main memory privileges
//
inline static memPriv getMainPriv(void) {
    return MEM_PRIV_RWX;
}

//
// Return I/O memory privileges
//
inline static memPriv getIOPriv(void) {
    return MEM_PRIV_RW|MEM_PRIV_ALIGN;
}

//
// Return non-atomic memory privileges
//
inline static memPriv getNonAtomicPriv(void) {
    return MEM_PRIV_USER1;
}

//
// Return default memory privileges
//
inline static memPriv getDefaultPriv(void) {
    return getIOPriv() | getNonAtomicPriv();
}

//
// Update the bounds in lowPAP/highPAP and privilege to reflect the effect of
// region i
//
static void refinePMARegionRange(
    vmiosObjectP object,
    Uns64       *lowPAP,
    Uns64       *highPAP,
    Uns64        PA,
    Uns32        index,
    memPriv     *privP
) {
    PMARegionP region      = &object->PMARegions[index];
    Uns64      lowPAEntry  = region->word_addr_low;
    Uns64      highPAEntry = region->word_addr_high;

    if((lowPAEntry<=PA) && (PA<highPAEntry)) {

        memPriv priv = region->main ? getMainPriv() : getIOPriv();

        // disallow atomic accesses if required
        if(!region->atomic) {
            priv |= getNonAtomicPriv();
        }

        // match in this region
        *lowPAP  = lowPAEntry;
        *highPAP = highPAEntry-1;
        *privP   = priv;

    } else if((lowPAEntry>PA) && (lowPAEntry<*highPAP)) {

        // remove part of region ABOVE matching address
        *highPAP = lowPAEntry-1;

    } else if((highPAEntry<=PA) && (highPAEntry>*lowPAP)) {

        // remove part of region BELOW matching address
        *lowPAP = highPAEntry;
    }
}

//
// Map region starting at lowPA, hopefully extending to highPA
//
static void mapPMAInt(
    riscvP       riscv,
    vmiosObjectP object,
    memPriv      requiredPriv,
    Uns64        lowPA,
    Uns64        highPA,
    Uns64       *lowMapP,
    Uns64       *highMapP
) {
    Uns64   PA   = *lowMapP;
    memPriv priv = getDefaultPriv();
    Int32 i;

    // set widest possible range initially
    *lowMapP = 0;

    // handle all regions in lowest-to-highest priority order
    for(i=object->PMA_NUM_REGIONS-1; i>=0; i--) {
        refinePMARegionRange(object, lowMapP, highMapP, PA, i, &priv);
    }

    // get PMA region range
    Uns64 lowMap  = *lowMapP;
    Uns64 highMap = *highMapP;

    // clamp physical range to maximum page size
    riscvClampPage(riscv, lowPA, highPA, &lowMap, &highMap);

    // update PMA privileges
    setPMAPriv(riscv, lowMap, highMap, priv, True);
}

//
// Refresh physical mappings for the given physical address range
//
static void mapPMA(
    riscvP       riscv,
    vmiosObjectP object,
    memPriv      requiredPriv,
    Uns64        lowPA,
    Uns64        highPA
) {
    Uns64 mask    = getAddressMask(riscv->extBits);
    Uns64 highMap = lowPA-1;
    Uns64 lowMap;

    // iterate while unprocessed regions remain
    do {

        // get next region bounds to try
        lowMap  = highMap+1;
        highMap = mask;

        // attempt PMA privilege change for regions in implemented range
        if(lowMap<=highMap) {
            mapPMAInt(riscv, object, requiredPriv, lowPA, highPA, &lowMap, &highMap);
        } else {
            highMap = highPA;
        }

    } while(highMap<highPA);
}

//
// Handle PMA initialization
//
static RISCV_IASSWITCH_FN(openhwPMAInit) {

    vmiosObjectP object = clientData;

    if(!object->PMAInit) {

        // remove all PMA permissions on first call
        setPMAPriv(riscv, 0, -1, MEM_PRIV_NONE, False);

        object->PMAInit = True;
    }
}

//
// Implement PMA check for the given address range
//
static RISCV_PMA_CHECK_FN(openhwPMACheck) {

    vmiosObjectP object = clientData;

    // apply PMA privileges
    mapPMA(riscv, object, requiredPriv, lowPA, highPA);
}

//
// When PMA is implemented, report alignment faults as access faults
//
static RISCV_RD_WR_FAULT_FN(openhwPMAAlign) {

    return True;
}


////////////////////////////////////////////////////////////////////////////////
// RESET NOTIFIER
////////////////////////////////////////////////////////////////////////////////

//
// Reset implementation-specific CSRs
//
static RISCV_RESET_NOTIFIER_FN(CSRReset) {

    // enable full write access to CSRs
    riscv->artifactAccess = True;

    // apply mcountinhibit reset
    riscv->cb.writeBaseCSR(riscv, CSR_ID(mcountinhibit), 0xd);

    // tdata1 initialization
    // https://core-v-docs-verif-strat.readthedocs.io/projects/cv32e40p_um/en/latest/control_status_registers.html
    //
    riscvTriggerP trigger = riscv->triggers;

    // initialise read-only fields
    if(trigger) {
        trigger->tdata1UP.type   = 2;       // Address/Data match trigger
        trigger->tdata1UP.dmode  = 1;       // Only debug mode can write tdata registers
        trigger->tdata1UP.action = 1;       // Enter debug mode on match
        trigger->tdata1UP.modes  = 1<<3;    // Match in M-Mode
    }

    // apply tdata1 reset
    riscv->cb.writeBaseCSR(riscv, CSR_ID(tdata1), 0x0);

    // disable full write access to CSRs
    riscv->artifactAccess = False;
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CSRS
////////////////////////////////////////////////////////////////////////////////

//
// CSR table
//
static const extCSRAttrs csrs[XCSR_ID(LAST)] = {

    //            name           num    arch         extension attrs    description           rCB rwCB wCB

    // Machine Mode CSRs
    XCSR_ATTR_P__(mtval,         0x343, 0,           0,        0,0,0,0, "Machine Trap Value", 0,  0,   0),
};

//
// Initialize CSR registers
//
static void addCSRsCSRInit(vmiosObjectP object) {

    riscvP   riscv = object->riscv;
    extCSRId id;

    // register each CSR with the base model using the newCSR interface function
    for(id=0; id<XCSR_ID(LAST); id++) {

        extCSRAttrsCP  src = &csrs[id];
        riscvCSRAttrs *dst = &object->csrs[id];

        riscv->cb.newCSR(dst, &src->baseAttrs, riscv, object);
    }

    //
    // DCSR
    //
    // mask out unimplemented bits in dcsr
    riscv->csrMask.dcsr.u32.fields.stopcount = 0;
    riscv->csrMask.dcsr.u32.fields.stoptime  = 0;
    riscv->csrMask.dcsr.u32.fields.mprven    = 0;
    riscv->csrMask.dcsr.u32.fields.nmip      = 0;

    // mask out readonly bits in dcsr where this differs from base model
    riscv->csrMask.dcsr.u32.fields.prv       = 0; // Changed in RTL from RW->RO
    riscv->csrMask.dcsr_RO.u32.fields.prv    = -1;

    // debug ver 4
    riscv->csr.dcsr.u32.fields.xdebugver     = 4;
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT PARAMETERS
////////////////////////////////////////////////////////////////////////////////

typedef struct openhwParameterS {
    vmiParameter  param;        // VMI parameter (must be first)
    openhwFeature features;     // any required features
} openhwParameter, *openhwParameterP;

//
// Define formals set for one PMA region
//
#define PMA_FORMAL_SET(_N) \
    {VMI_UNS32_PARAM_SPEC(paramValues, word_addr_low##_N,  0, 0, -1, "PMA region "#_N" low bound"),  OHWF_PMA16}, \
    {VMI_UNS32_PARAM_SPEC(paramValues, word_addr_high##_N, 0, 0, -1, "PMA region "#_N" high bound"), OHWF_PMA16}, \
    {VMI_BOOL_PARAM_SPEC (paramValues, main##_N,           0,        "PMA region "#_N" main"),       OHWF_PMA16}, \
    {VMI_BOOL_PARAM_SPEC (paramValues, bufferable##_N,     0,        "PMA region "#_N" bufferable"), OHWF_PMA16}, \
    {VMI_BOOL_PARAM_SPEC (paramValues, cacheable##_N,      0,        "PMA region "#_N" cacheable"),  OHWF_PMA16}, \
    {VMI_BOOL_PARAM_SPEC (paramValues, atomic##_N,         0,        "PMA region "#_N" atomic"),     OHWF_PMA16}

//
// Define formals
//
static openhwParameter formals[] = {

    // always-present parameters
    {VMI_BOOL_PARAM_SPEC(paramValues,  debug,            0,        "debug flags"),           OHWF_NA   },

    // PMA configuration parameters
    {VMI_UNS32_PARAM_SPEC(paramValues, PMA_NUM_REGIONS,  0, 0, 16, "number of PMA regions"), OHWF_PMA16},
    PMA_FORMAL_SET(0),
    PMA_FORMAL_SET(1),
    PMA_FORMAL_SET(2),
    PMA_FORMAL_SET(3),
    PMA_FORMAL_SET(4),
    PMA_FORMAL_SET(5),
    PMA_FORMAL_SET(6),
    PMA_FORMAL_SET(7),
    PMA_FORMAL_SET(8),
    PMA_FORMAL_SET(9),
    PMA_FORMAL_SET(10),
    PMA_FORMAL_SET(11),
    PMA_FORMAL_SET(12),
    PMA_FORMAL_SET(13),
    PMA_FORMAL_SET(14),
    PMA_FORMAL_SET(15),

    // KEEP LAST: terminator
    {VMI_END_PARAM, OHWF_NA},
};

//
// Is the feature set selected by the required set?
//
inline static Bool selectParam(openhwFeature this, openhwFeature required) {
    return (this&required) == required;
}

//
// Iterate formals
//
static VMIOS_PARAM_SPEC_FN(getParamSpecs) {

    riscvP           riscv    = (riscvP)processor;
    openhwConfigCP   config   = openhwExtConfig(riscv);
    openhwFeature    features = config->features;
    openhwParameterP prevOHW  = (openhwParameterP)prev;
    openhwParameterP thisOHW  = prevOHW ? prevOHW+1 : formals;

    // skip past parameter for absent features
    while(thisOHW->param.name && !selectParam(features, thisOHW->features)) {
        thisOHW++;
    }

    // return next parameter (if any)
    return thisOHW->param.name ? &thisOHW->param : 0;
}

//
// Return size of parameter structure
//
static VMIOS_PARAM_TABLE_SIZE_FN(getParamTableSize) {
    return sizeof(paramValues);
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(openhwConstructor) {

    riscvP riscv = (riscvP)processor;

    paramValuesP params = parameterValues;
    if(params->debug) {
        object->diagnostic = 1;
    }

    // initialize PMA regions
    object->PMA_NUM_REGIONS = params->PMA_NUM_REGIONS;
    INIT_PMA(0);
    INIT_PMA(1);
    INIT_PMA(2);
    INIT_PMA(3);
    INIT_PMA(4);
    INIT_PMA(5);
    INIT_PMA(6);
    INIT_PMA(7);
    INIT_PMA(8);
    INIT_PMA(9);
    INIT_PMA(10);
    INIT_PMA(11);
    INIT_PMA(12);
    INIT_PMA(13);
    INIT_PMA(14);
    INIT_PMA(15);

    object->riscv = riscv;

    // prepare client data
    object->extCB.clientData    = object;
    object->extCB.resetNotifier = CSRReset;

    // initialize base model PMA callbacks if required
    if(object->PMA_NUM_REGIONS) {
        object->extCB.rdFaultCB = openhwPMAAlign;
        object->extCB.wrFaultCB = openhwPMAAlign;
        object->extCB.switchCB  = openhwPMAInit;
        object->extCB.PMAEnable = openhwPMAEnable;
        object->extCB.PMACheck  = openhwPMACheck;
    }

    // register extension with base model using unique ID
    riscv->cb.registerExtCB(riscv, &object->extCB, 0);

    // initialize exception state
    openhwExceptionInit(object);

    // initialize CSRs
    addCSRsCSRInit(object);

    // perform initial CSR reset
    CSRReset(riscv, object);
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(openhwDestructor) {

    // free exception state
    openhwExceptionFree(object);
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,           // version string
    .modelType     = VMI_INTERCEPT_LIBRARY, // type
    .packageName   = "OpenHW",              // description
    .objectSize    = sizeof(vmiosObject),   // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = openhwConstructor,     // object constructor
    .destructorCB  = openhwDestructor,      // object destructor

    ////////////////////////////////////////////////////////////////////////
    // PORT ACCESS ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .netPortSpecsCB = openhwNetPorts,       // callback for next net port

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,      // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,  // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};


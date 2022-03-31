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



// VMI module includes
#include "vmi/vmiMmcAttrs.h"
#include "vmi/vmiMessage.h"

#define CPU_PREFIX "cacheNull"

//
// Define the attributes value structure
//
typedef struct paramValuesS {

    VMI_UNS32_PARAM(numSlavePorts);

} paramValues, *paramValuesP;

//
// Define formals
//
static vmiParameter formals[] = {
    VMI_UNS32_PARAM_SPEC(paramValues, numSlavePorts, 1,1, 8,"Number of slave ports"),
    VMI_END_PARAM
};

//
// Iterate formals
//
static VMIMMC_PARAM_SPEC_FN(getParamSpecs) {
    if(!prev) {
        return formals;
    } else {
        prev++;
        if (prev->name) {
            return prev;
        } else {
            return NULL;
        }
    }
}

//
// Return size of parameter structure
//
static VMIMMC_PARAM_TABLE_SIZE_FN(getParamTableSize) {
    return sizeof(paramValues);
}

//
// Cache object
//
typedef struct cacheObjectS {
    Uns32 numSlavePorts;
} cacheObject, *cacheObjectP;

//
// Cache object constructor
//
static VMIMMC_CONSTRUCTOR_FN(cacheConstructor) {

    paramValuesP params = parameterValues;
    cacheObjectP cache  = (cacheObjectP)component;

    // configure the number of slave ports
    cache->numSlavePorts = params->numSlavePorts;
}

//
// Cache object link
//
static VMIMMC_LINK_FN(cacheLink) {
}

//
// Cache object destructor
//
static VMIMMC_DESTRUCTOR_FN(cacheDestructor) {
}


////////////////////////////////////////////////////////////////////////////////
// MODEL REFRESH (AT START OF TIME SLICE)
////////////////////////////////////////////////////////////////////////////////

static VMIMMC_REFRESH_FN(cacheRefresh) {
}


////////////////////////////////////////////////////////////////////////////////
// FULL MODEL CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// N-byte read function
//
static VMI_MEM_READ_FN(readNFull) {
    VMI_ABORT("readNFull: unimplemented");
}

//
// N-byte write function
//
static VMI_MEM_WRITE_FN(writeNFull) {
    VMI_ABORT("writeNFull: unimplemented");
}


////////////////////////////////////////////////////////////////////////////////
// TRANSPARENT MODEL CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// N-byte read transparent
//
static VMI_MEM_WATCH_FN(readNTransparent) {
    // no action
}

//
// N-byte write transparent
//
static VMI_MEM_WATCH_FN(writeNTransparent) {
    // no action
}

//
// Get the next bus port
//
static VMIMMC_BUSPORT_FN(nextBusPortSpec) {

    // this model supports one master port and up to eight slave ports
    const static vmiBusPort busPorts[] = {
        { .name = "mp1", .type = vmi_BP_MASTER, .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp1", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp2", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp3", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp4", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp5", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp6", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp7", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp8", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
    };

    vmiBusPortP firstPort = (vmiBusPortP)&busPorts[0];

    if(!prev) {

        // first (master) port
        return firstPort;

    } else {

        // subsequent (slave) port
        cacheObjectP cache = (cacheObjectP)component;
        vmiBusPortP  this  = ++prev;
        Uns32        index = this-firstPort;

        return (index<=cache->numSlavePorts) ? this : NULL;
    }
}


vmimmcAttr caCacheAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    VMI_VERSION,                        // version string (THIS MUST BE FIRST)
    sizeof(cacheObject),                // size in bytes of MMC object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    cacheConstructor,                   // constructor
    cacheLink,                          // link component
    cacheDestructor,                    // destructor

    ////////////////////////////////////////////////////////////////////////
    // MODEL REFRESH (AT START OF TIME SLICE)
    ////////////////////////////////////////////////////////////////////////

    cacheRefresh,                       // refresh

    ////////////////////////////////////////////////////////////////////////
    // FULL MODEL CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    readNFull,                          // N-byte read callback
    writeNFull,                         // N-byte write callback

    ////////////////////////////////////////////////////////////////////////
    // TRANSPARENT MODEL CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    readNTransparent,                   // N-byte read callback
    writeNTransparent                   // N-byte write callback

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,          // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,      // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // BUS INTERFACE CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .busPortSpecsCB = nextBusPortSpec   // iterate ports
};


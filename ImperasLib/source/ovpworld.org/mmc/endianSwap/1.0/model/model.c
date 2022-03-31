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

//
// Endian swapper for 1, 2, 4 and 8 bytes access
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// VMI module includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiMmcAttrs.h"
#include "vmi/vmiMmc.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"

//
// Model prefix (used by vmiMessage interface)
//
#define CPU_PREFIX "endianSwap"

//
// Byte swap object
//
typedef struct swapObjectS {
    memDomainP nextDomain;      // next domain (FULL model)
    memRegionP lastRegion;      // last accessed (FULL model)
    Uns64      count;           // byte accesses
} swapObject, *swapObjectP;


////////////////////////////////////////////////////////////////////////////////
// STATISTICS
////////////////////////////////////////////////////////////////////////////////

#define BUF_SIZE 30

static char tmpCharBuffer[BUF_SIZE];

//
// Return a static temporary string that has the digits in the passed string
// separated into groups by a comma, e.g. "1234567" -> "1,234,567". The result
// is in a static buffer so it will be overwritten by the next call.
//
static const char *getCommaString(const char *string) {

    static char buffer2[BUF_SIZE];

    Uns32       length = strlen(string);
    Uns32       count  = 0;
    char       *dst    = buffer2+BUF_SIZE;
    const char *src    = string+length;

    // copy null terminator for comma string
    *--dst = *src--;

    // copy remaining characters in groups
    do {

        *--dst = *src--;

        // insert comma every three characters
        if((++count==3) && (src>=string)) {
            count = 0;
            *--dst = ',';
        }

    } while((src>=string) && (dst>=buffer2));

    return dst;
}

//
// Return a static temporary string that has the passed Uns64 value shown
// with digits separated by commas
//
static const char *uns64String(Uns64 value) {
    sprintf(tmpCharBuffer, FMT_64u, value);
    return getCommaString(tmpCharBuffer);
}

//
// Utility routine for statistics reporting
//
static void printStats(swapObjectP info) {
    vmiMessage("I", CPU_PREFIX,
        "TOTAL SWAPPED BYTES: %15s\n",
        uns64String(info->count)
    );
}


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR, LINK AND DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Byte swap object constructor
//
static VMIMMC_CONSTRUCTOR_FN(swapConstructor) {
    // no action
}

//
// Byte swap object link
//
static VMIMMC_LINK_FN(swapLink) {

    swapObjectP swap = (swapObjectP)component;

    // only a full model is supported (not transparent)
    if(vmimmcGetNextPort(component, "mp1")) {
        vmiMessage("F", CPU_PREFIX,
            "%s: only full model is supported.",
            vmimmcGetHierarchicalName(component)
        );
    }

    swap->nextDomain = vmimmcGetNextDomain(component, "mp1");
}

//
// Byte swap object destructor
//
static VMIMMC_DESTRUCTOR_FN(swapDestructor) {
    printStats((swapObjectP)component);
}


////////////////////////////////////////////////////////////////////////////////
// SAVE AND RESTORE
////////////////////////////////////////////////////////////////////////////////

//
// Save swap object state
//
static VMIMMC_SAVE_STATE_FN(swapSave) {

    swapObjectP swap = (swapObjectP)component;

    // both full and transparent have keys
    VMIRT_SAVE_FIELD(cxt, swap, count);
}

//
// Restore swap object state
//
static VMIMMC_RESTORE_STATE_FN(swapRestore) {

    swapObjectP swap = (swapObjectP)component;

    // both full and transparent have keys
    VMIRT_RESTORE_FIELD(cxt, swap, count);
}


////////////////////////////////////////////////////////////////////////////////
// FULL MODEL UTILITY FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

static void badAccess(const char *what, Addr address, Uns32 bytes) {
    vmiMessage("F", CPU_PREFIX,
        "Model supports 1-byte, 2-byte, 4-byte and 8-byte accesses."
        "Failed %s at 0x"FMT_64x" with %u-byte access",
        what, address, bytes
    );
}


////////////////////////////////////////////////////////////////////////////////
// FULL MODEL READ CALLBACK
////////////////////////////////////////////////////////////////////////////////

//
// N-byte read function
//
static VMI_MEM_READ_FN(readNFull) {

    vmimmcPortP port = userData;
    swapObjectP swap = (swapObjectP)port->component;

    // count true reads only
    if(MEM_AA_IS_TRUE_ACCESS(attrs)) {
        swap->count += bytes;
    }

    // read from next domain
    vmirtReadNByteDomain(
        swap->nextDomain,
        address,
        value,
        bytes,
        &swap->lastRegion,
        processor!=0
    );

    switch(bytes) {
        case 1:
            break;
        case 2:
            *(Uns16*)value = SWAP_2_BYTE(*(Uns16*)value);
            break;
        case 4:
            *(Uns32*)value = SWAP_4_BYTE(*(Uns32*)value);
            break;
        case 8:
            *(Uns64*)value = SWAP_8_BYTE(*(Uns64*)value);
            break;
        default:
            badAccess("read", address, bytes);
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
// FULL MODEL WRITE CALLBACK
////////////////////////////////////////////////////////////////////////////////

//
// N-byte write function
//
static VMI_MEM_WRITE_FN(writeNFull) {

    vmimmcPortP port         = userData;
    swapObjectP swap         = (swapObjectP)port->component;
    Uns64       swappedValue = 0;

    // count true writes only
    if(MEM_AA_IS_TRUE_ACCESS(attrs)) {
        swap->count += bytes;
    }

    switch(bytes) {
        case 1:
            swappedValue = *(Uns8*)value;
            break;
        case 2:
            swappedValue = SWAP_2_BYTE(*(Uns16*)value);
            break;
        case 4:
            swappedValue = SWAP_4_BYTE(*(Uns32*)value);
            break;
        case 8:
            swappedValue = SWAP_8_BYTE(*(Uns64*)value);
            break;
        default:
            badAccess("write", address, bytes);
            break;
    }

    // write to next domain
    vmirtWriteNByteDomain(
        swap->nextDomain,
        address,
        &swappedValue,
        bytes,
        &swap->lastRegion,
        processor!=0
    );
}

//
// Port descriptions
//
const static vmiBusPort busPorts[] = {
    {
        .name            = "mp1",
        .type            = vmi_BP_MASTER,
        .domainType      = vmi_DOM_DATA,
        .addrBits        = {1,64},
        .mustBeConnected = 1
    },
    {
        .name            = "sp1",
        .type            = vmi_BP_SLAVE,
        .domainType      = vmi_DOM_DATA,
        .addrBits        = {1,64},
        .mustBeConnected = 1
    },
    {0}
};

//
// Bus port iterator
//
VMIMMC_BUSPORT_FN(nextBusPortSpec) {

    if(!prev) {

        // first port
        return (vmiBusPortP)&busPorts[0];

    } else {

        vmiBusPortP next = ++prev;
        return next->name ? next : NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////
// MODEL ATTRIBUTES STRUCTURE
////////////////////////////////////////////////////////////////////////////////

vmimmcAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,           // version string
    .modelType     = VMI_MMC_MODEL,         // type
    .componentSize = sizeof(swapObject),    // size in bytes of MMC object

    ////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .saveCB    = swapSave,                  // model state save callback
    .restoreCB = swapRestore,               // model state restore callback
    .srVersion = 1,                         // model save/restore version

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = swapConstructor,       // constructor
    .linkCB        = swapLink,              // link component
    .destructorCB  = swapDestructor,        // destructor

    ////////////////////////////////////////////////////////////////////////
    // FULL MODEL CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .readNFullCB  = readNFull,              // N-byte read callback
    .writeNFullCB = writeNFull,             // N-byte write callback

    ////////////////////////////////////////////////////////////////////////
    // BUS INTERFACE CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .busPortSpecsCB = nextBusPortSpec,

    ////////////////////////////////////////////////////////////////////////
    // MODEL VLNV
    ////////////////////////////////////////////////////////////////////////

   .vlnv = {
        .vendor  = "ovpworld.org",
        .library = "mmc",
        .name    = "endianSwap",
        .version = "1.0"
    }
};



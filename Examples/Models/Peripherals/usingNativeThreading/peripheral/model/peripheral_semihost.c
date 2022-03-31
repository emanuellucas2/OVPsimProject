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


#include <string.h>
#include <stdlib.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiPSE.h"

#include "../application/dataSortRegisters.h"

// Prefix for messages from this module
#define PREFIX  "DATASORT_SEMI"
#define CPU_PREFIX PREFIX

typedef struct vmiosObjectS  {

    // Name of peripheral
    char *name;

    // Master port domain (passed to r/w callbacks accessing simulated memory)
    memDomainP portDomain;

    // memory region to work on
    Uns32 *memory;
    Uns32  memoryBase;
    Uns32  memorySize;
    Uns32  registerOnly;

    // LFSR used for pseudo-random number generation
    Uns32  lfsr;

} vmiosObject;

//
// Called to initialise
//
static void initSemiHost(
    vmiosObjectP object,
    Uns32        base,
    Uns32        size,
    Bool         registerOnly
) {
    object->registerOnly = registerOnly;
    object->memoryBase   = base;
    object->memorySize   = size;

    Uns32 bytes = size * sizeof(Uns32);
    Uns32 top   = base + bytes - 1;

    // Set up the data buffer
    object->memory = malloc(bytes);
    VMI_ASSERT(object->memory, "malloc error (allocating %d bytes)", bytes);

    // Copy any existing data from simulated memory
    vmirtReadNByteDomain(
        object->portDomain,
        base,
        object->memory,
        bytes,
        NULL,
        MEM_AA_FALSE
    );

    // Map the data buffer to the native memory
    vmirtMapNativeMemory(object->portDomain, base, top, object->memory);

    vmiMessage(
        "I", PREFIX,
        "%s: initSemiHost base = 0x%x size = 0x%x words\n",
        object->name, base, size
    );

}

//
// Generate new pseudo-random number
//
inline static Uns32 randomLocal(vmiosObjectP object) {
    object->lfsr =
        ((object->lfsr >> 1) ^ (-(Int32)(object->lfsr & 1) & 0x8000000bu));
    return object->lfsr;
}

//
// Fill data block of sort peripheral 'index' with new pseudo-random data set
//
void fillRandom(vmiosObjectP  object) {

    Uns32 i;
    Uns32 *base = object->memory;

    for(i = 0; i < object->memorySize; i++) {
        base[i] = randomLocal(object);
    }
}

//
// Callback for qsort
//
static int sortcb(const void *a, const void *b) {

    const Uns32 *ai = a;
    const Uns32 *bi = b;

    if(*ai < *bi ) return -1;
    if(*ai > *bi ) return 1;

    return 0;
}

//
// Native implementation of sort algorithm
//
static VMIOS_INTERCEPT_FN(runSort) {

    // don't do operation if register interface only
    if (object->registerOnly) {

        vmiMessage(
            "I", PREFIX,
            "%s: runSort: sort disabled in registerOnly mode\n",
            object->name
        );

    } else {

        Uns32 base   = object->memoryBase;
        Uns32 size   = object->memorySize;
        void *memory = object->memory;

        // fill data block with new pseudo-random data set if peripheral is in
        // control of this
        if(!(APPLICATIONGENERATESDATA)) {
            vmiMessage(
                "I", PREFIX,
                "%s, reseeding peripheral data buffer\n",
                object->name
            );
            fillRandom(object);
        }

        vmiMessage(
            "I", PREFIX,
            "%s: runSort: sort 0x%x words at 0x%x\n",
            object->name, size, base
        );

        // sort the data block
        qsort(memory, size, sizeof(Uns32), sortcb);
    }
}

//
// Get the memory domain connected to the master port
//
static memDomainP getPortDomain(vmiProcessorP processor) {

    Addr lo,  hi;
    Bool master, dynamic;

    memDomainP domain = vmipsePlatformPortAttributes(
        processor, "DATASORTMP", &lo, &hi, &master, &dynamic
    );

    if (!domain || !master) {
        vmiMessage(
            "E", PREFIX,
            "%s: Unable to open master port DATASORTMP\n",
            vmirtProcessorName(processor)
        );
    }

    return domain;

}

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    // store name of processor
    object->name = strdup(vmirtProcessorName(processor));

    // Get the master port's memory domain
    object->portDomain = getPortDomain(processor);

    // initialize LFSR pseudo-random number generation
    object->lfsr = 0x1234;

}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
    if (object->name) free(object->name);
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,            // version string
    .modelType     = VMI_INTERCEPT_LIBRARY,  // type
    .packageName   = PREFIX,                 // description
    .objectSize    = sizeof(vmiosObject),    // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = constructor,            // object constructor
    .destructorCB  = destructor,             // object destructor

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    =
    //   --------------- ----------- ------------------------ ------------
    //   Name            Address     Attributes               Callback
    //   --------------- ----------- ------------------------ ------------
    {
        {"initSemiHost", 0,          OSIA_OPAQUE,             VMIOS_ABI_INT(0, "o44b", initSemiHost)},
        {"runSort",      0,          OSIA_OPAQUE|OSIA_THREAD, runSort     },
        {0}
    }
};

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

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiPSE.h"
#include "vmi/vmiRt.h"

// model includes
#include "../pse/pse.igen.h"

//
// Prefix for messages from this module
//
#define PREFIX     "DMAC_NATIVE"
#define CPU_PREFIX PREFIX

// Define diagnostic levels
#define DIAG_LOW(_diag)        ((_diag & 3) > 0)
#define DIAG_MEDIUM(_diag)     ((_diag & 3) > 1)
#define DIAG_HIGH(_diag)       ((_diag & 3) > 2)

typedef struct vmiosObjectS  {

    // PSE data domain (passed to read and write callbacks)
    memDomainP pseDomain;

    memDomainP portReadDomain;
    memDomainP portWriteDomain;

    // diagnostics enabled
    Uns32 diag;

    // alias of internal channel structure of DMAC
    DMACSP_ab32_dataT channel;

    // record position of message sent
    Uns32 msgPtr;

} vmiosObject;

const char testString[] = "Native code test string";

static Uns32 transferDataNative(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         addressSrc,
    Uns32         addressDest,
    Uns32         bytes
) {
    if(DIAG_HIGH(object->diag)) {
        vmiMessage("I", PREFIX "_XFER", "Send native data 0x%08x to 0x%08x (%d bytes)",
                        addressSrc, addressDest, bytes);
    }

    if(!object->portReadDomain || !object->portWriteDomain) {
        vmiMessage("E", PREFIX "_XFER", "PSE Port Domains not available");
    }

    #define MAX_BYTES 256
    char tmp[MAX_BYTES];  // temporary buffer for transfer (allocation could be dynamic)

    if(bytes > MAX_BYTES) {
        if(DIAG_LOW(object->diag)) {
            vmiMessage("W", PREFIX "_XFER_SZ",
                       "Requested transfer size (%d bytes) limited to buffer allocated (%d)",
                        bytes, MAX_BYTES);
        }
        bytes = MAX_BYTES;    // limit transfer to max of tmp buffer
    }

    vmirtReadNByteDomain (object->portReadDomain,  addressSrc,  tmp, bytes , 0, False);
    vmirtWriteNByteDomain(object->portWriteDomain, addressDest, tmp, bytes , 0, False);

    // return bytes transferred as result
    return bytes;
}


//
// Called to initialise
//
static Uns32 initSemiHost(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Addr          base,
    Uns32         diag
) {
    // The names of the master ports to access
    const char *portWriteName = "MWRITE";
    const char *portReadName  = "MREAD";

    object->diag = diag;

    DMACSP_ab32_dataT *channel = &object->channel;
    Addr top                   = base+sizeof(DMACSP_ab32_dataT)-1;

    if(DIAG_LOW(object->diag))
        vmiMessage("I", PREFIX "_INIT", "Diag Level %d. "
                               "Channel Base 0x"FMT_A08x" Top 0x"FMT_A08x,
                               object->diag, base, top);

    // map the memory as native for the DMAchannel structure
    // same structure is now visible to PSE and native code
    if (!vmirtMapNativeMemory(object->pseDomain, base, top, channel)) {
        vmiMessage("E", PREFIX "_REG_MAP",
                               "Failed to map native memory for channel control");
    }

    // dummy variables (not used)
    Addr lo, hi;    // set to the low and high addresses of port
    Bool isMaster;  // set if the port is a master port
    Bool isDynamic; // set if the port is dynamic

    // Obtain information about the master write port
    object->portWriteDomain = vmipsePlatformPortAttributes(
        processor,
        portWriteName,
        &lo, &hi, &isMaster, &isDynamic
    );
    if(!object->portWriteDomain) {
        vmiMessage("E", PREFIX "_INIT_MWDOMAIN",
                               "Port domain information for '%s' not available"
                               " : Check port connected",
                        portWriteName);
    }
    if(DIAG_MEDIUM(object->diag))
        vmiMessage("I", PREFIX "_INIT_MWPORT", "'%s', "
                               "address range 0x"FMT_Ax " to 0x"FMT_Ax
                               " master %u dynamic %u",
                               portWriteName, lo, hi, isMaster, isDynamic);

    // Obtain information about the master read port
    object->portReadDomain = vmipsePlatformPortAttributes(
        processor,
        portReadName,
        &lo, &hi, &isMaster, &isDynamic
    );
    if(!object->portReadDomain) {
        vmiMessage("E", PREFIX "_INIT_MRDOMAIN",
                               "Port domain information for '%s' not available"
                               " : Check port connected",
                        portReadName);
    }

    if(DIAG_MEDIUM(object->diag))
        vmiMessage("I", PREFIX "_INIT_MRPORT", "'%s', "
                               "address range 0x"FMT_Ax " to 0x"FMT_Ax
                               " master %u dynamic %u",
                               portReadName, lo, hi, isMaster, isDynamic);


    return 1; // = ok
}


//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    // store the PSE data domain
    object->pseDomain = vmirtGetProcessorDataDomain(processor);
    if(!object->pseDomain) {
        vmiMessage("E", PREFIX "_PSEDOMAIN", "PSE Domain not available");
    }

    // Initialise variables
    object->msgPtr = 0;
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
    if(DIAG_LOW(object->diag)) {
        vmiMessage("I" ,PREFIX, "Shutting down");
    }
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
    //   --------------------    ------- ---------------------------------------
    //   Name                     Opaque Callback
    //   --------------------     ------ ---------------------------------------
    {
        {"transferDataNative", 0, True,  VMIOS_ABI_INT('4', "po444", transferDataNative)},
        {"initSemiHost",       0, True,  VMIOS_ABI_INT('4', "poa4",  initSemiHost)      },
        {0}
    }
};

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

#include <string.h>
#include <stdlib.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiPSE.h"
#include "vmi/vmiRt.h"

// model includes
#include "../pse/pse.igen.h"

#include "../pse/ucd9248.user.h"

//
// Prefix for messages from this module
//
#define PREFIX     "PMBUS_UCD9248_NATIVE"
#define CPU_PREFIX PREFIX

// include common power monitor defines
#include "ovpworld.org/modelSupport/powermonitor/1.0/model/powermonitor.native.h"

typedef struct vmiosObjectS  {

    // PSE data domain (passed to read and write callbacks)
    memDomainP pseDomain;

    // diagnostics enabled
    Uns32 diag;

    // name of the instance of this PSE
    const char *name;

    //
    // Power Monitor shared data handle
    //
    vmiSharedDataHandleP powerMonitorDataTransfer;

} vmiosObject;

// include common power monitor functions
#include "ovpworld.org/modelSupport/powermonitor/1.0/model/powermonitor.native.c.h"

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    object->name = vmirtProcessorName(processor);

    // store the PSE data domain
    object->pseDomain = vmirtGetProcessorDataDomain(processor);
    if(!object->pseDomain) {
        vmiMessage("E", PREFIX "_PSEDOMAIN", "%s: PSE Domain not available", object->name);
    }

    // check and open the shared data channel for the Power Monitor
    object->powerMonitorDataTransfer = openSharedPowerMonitor(object->name);

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

    .intercepts = {
        // -------------------   ----------- ------ -----------------
        // Name                  Address     Opaque Callback
        // -------------------   ----------- ------ -----------------
        POWERMONITOR_FUNCTION_INTERCEPTS,
        {0}
    }
};

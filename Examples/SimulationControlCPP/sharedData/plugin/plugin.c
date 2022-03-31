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
#include "vmi/vmiRt.h"
#include "vmi/vmiView.h"
#include "vmi/vmiVersion.h"

#include "sharedData.h"

#define PREFIX        "APP1"
#define KEY_NAME      "key1"
#define API_VERSION   "1.0.0"

//
// Data storage associated with an instance of this intercept
//
typedef struct vmiosObjectS {

    vmiSharedDataHandleP handle;
    sharedDataContainer  sdc;

} vmiosObject;

static VMI_SHARED_DATA_LISTENER_FN(listener1) {
    const char *uo = userObject;
    sharedDataContainerP scd = userData;
    *ret = *ret + 1;
    vmiMessage("I", "PLG", "Listener1 id:%d userObject=%s object1=%s   object2=%s", id, uo, scd->object1, scd->object2);
}

static VMI_SHARED_DATA_LISTENER_FN(listener2) {
    const char *uo = userObject;
    sharedDataContainerP scd = userData;

    *ret = *ret + 2;
    vmiMessage("I", "PLG", "Listener2 id:%d userObject=%s object1=%s   object2=%s", id, uo, scd->object1, scd->object2);
}

//
// Constructor. Called when an instance of this intercept is loaded.
//
static VMIOS_CONSTRUCTOR_FN(monitorConstructor)
{
    object->sdc.object1 = "object1";
    object->sdc.object1 = "object2";

    vmiMessage("I", "PLG", "%s: Create shared data object", vmiosGetExtensionName(object));
    
    char *instName = strdup(vmiosGetExtensionName(object));
    object->handle = vmirtFindAddSharedData(API_VERSION, KEY_NAME, (void*)instName);

    vmiMessage("I", "PLG", "Add listeners");
    vmirtRegisterListener(object->handle, listener1, (void*)object->sdc.object1);
    vmirtRegisterListener(object->handle, listener1, (void*)object->sdc.object2);
    vmirtRegisterListener(object->handle, listener2, (void*)object->sdc.object1);
    vmirtRegisterListener(object->handle, listener2, (void*)object->sdc.object2);

    vmiMessage("I", "PLG", "%s writes to shared data", instName);
    Int32 i = vmirtWriteListeners(object->handle, 1, &object->sdc);
    vmiMessage("I", "PLG", "%s write returned %d", vmiosGetExtensionName(object), i);
}

static VMIOS_POST_SIMULATE_FN(postSim) {
    vmiMessage("I", "PLG", "%s writes to shared data post-simulation", vmiosGetExtensionName(object));
    sharedDataContainer sdc;
    sdc.object1 = "ob1";
    sdc.object2 = "ob2";
    Int32 i = vmirtWriteListeners(object->handle, 2, &sdc);
    vmiMessage("I", "PLG", "%s write returned %d", vmiosGetExtensionName(object), i);
}

//
// Destructor. Called at the end of simulation for each instance.
//
static VMIOS_DESTRUCTOR_FN(monitorDestructor)
{
    vmiMessage("I", "PLG", "%s Destructor", vmiosGetExtensionName(object));
    
    vmiSharedDataHandleP h = vmirtFindSharedData(API_VERSION, KEY_NAME);
    if(h) {
        vmiMessage("I", "PLG", "%s monitorDestructor deleting shared data", vmiosGetExtensionName(object));

        vmirtUnregisterListener(h, listener1, (void*)object->sdc.object1);
        vmirtUnregisterListener(h, listener1, (void*)object->sdc.object2);
        vmirtUnregisterListener(h, listener2, (void*)object->sdc.object1);
        vmirtUnregisterListener(h, listener2, (void*)object->sdc.object2);
    
        vmirtRemoveSharedData(h);
    } else {
        vmiMessage("I", "PLG", "%s monitorDestructor NOT deleting shared data", vmiosGetExtensionName(object));
    }
    
    vmiMessage("I", "PLG", "%s Done", vmiosGetExtensionName(object));
}

////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,                // version string (THIS MUST BE FIRST)
    .modelType     = VMI_INTERCEPT_LIBRARY,      // type
    .packageName   = "UART Aplication monitor",  // description
    .objectSize    = sizeof(vmiosObject),        // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = monitorConstructor,         // object constructor
    .postSimulateCB = postSim,                    // object destructor
    .destructorCB   = monitorDestructor,          // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////
   
   .intercepts = {{0}}
};

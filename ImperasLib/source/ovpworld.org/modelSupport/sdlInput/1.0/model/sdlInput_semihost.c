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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiVersion.h"

// VGA module
#include "sdlInput.c.h"

//
// Get native endianness
//
#ifdef HOST_IS_BIG_ENDIAN
    #define ENDIAN_NATIVE MEM_ENDIAN_BIG
#else
    #define ENDIAN_NATIVE MEM_ENDIAN_LITTLE
#endif

#define DIAG_LOW(_obj)    ((_obj->diagLevel & 3) >= 1)
#define DIAG_MEDIUM(_obj) ((_obj->diagLevel & 3) >= 2)
#define DIAG_HIGH(_obj)   ((_obj->diagLevel & 3) == 3)

typedef struct vmiosObjectS  {

    Uns32  diagLevel;

} vmiosObject;

//
// Called to start the keyboard service.
//
static void inputInit(
    vmiosObjectP object,
    Uns32        diag,
    Uns32        grabDisable,
    Uns32        enableCursor
) {
    sdlInputInit(diag, grabDisable, enableCursor);
    object->diagLevel = diag;
}

//
// Called to end the keyboard service.
//
static void inputCleanUp(vmiosObjectP object)
{
    sdlInputCleanUp();
}

//
// Called to fetch the next event
//
static Bool inputPoll(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Addr          statep,
    Uns32         useMouse
) {
    static InputState native;

    Bool result = sdlInputPoll(&native, useMouse);

    if (result) {
        memDomainP domain = vmirtGetProcessorDataDomain(processor);
        vmirtWriteNByteDomain(domain, statep, &native, sizeof(native), 0, True);
    }

    return result;
}

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor)
{
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor)
{
    sdlInputCleanUp();
}

////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,                // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,      // type
    .packageName    = "sdlInput_semihost",        // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "ovpworld.org",
        .library = "modelSupport",
        .name    = "sdlInput",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,                // object constructor
    .destructorCB   = destructor,                 // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = 0,                          // morph callback
    .nextPCCB       = 0,                          // get next instruction address
    .disCB          = 0,                          // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////
    // -------------------   ----------- ------ -----------------
    // Name                  Address     Opaque Callback
    // -------------------   ----------- ------ -----------------
    .intercepts = {
        {"kbControlCleanUp",    0,       True,   VMIOS_ABI_INT(0,   "o",    inputCleanUp)},
        {"kbControlInit",       0,       True,   VMIOS_ABI_INT(0,   "o444", inputInit)},
        {"kbControlPoll",       0,       True,   VMIOS_ABI_INT('b', "poa4", inputPoll)},
        {0}
    }
};

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

#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <libgen.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

/*
 * Modified test mechanism to exit on execution of instruction at label write_tohost
 * may need to further enhance to se ewhat is written to host ?
 */

#define PREFIX "FUNCTIONS"

// Number of arguments passed in regs as defined by ABI
#define REG_ARG_NUM  3

#define UNUSED __attribute__((unused))
typedef struct vmiosObjectS {
    // first three argument registers (standard ABI)
    vmiRegInfoCP args[REG_ARG_NUM];

    // return register (standard ABI)
    vmiRegInfoCP resultReg;

} vmiosObject;

//
//
//
static UNUSED VMIOS_INTERCEPT_FN(myusleepCB) {
    vmiMessage("I", PREFIX, "Ignore function myusleep()");
}

static
VMIOS_CONSTRUCTOR_FN(constructor)
{
    // first three argument registers
    object->args[0] = vmiosGetRegDesc(processor, "r0");
    object->args[1] = vmiosGetRegDesc(processor, "r1");
    object->args[2] = vmiosGetRegDesc(processor, "r2");

    // return register (standard ABI)
    object->resultReg = vmiosGetRegDesc(processor, "r0");

}

static
VMIOS_DESTRUCTOR_FN(destructor)
{
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
    .packageName    = "functions",                // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "xilinx.ovpworld.org",
        .library = "intercept",
        .name    = "functions",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,                // object constructor
    .destructorCB   = destructor,                 // object destructor

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // -------------------   ----------- ------ -----------------
        // Name                  Address     Opaque Callback
        // -------------------   ----------- ------ -----------------
        { "myusleep",            0,          True,  myusleepCB    },
        {0}
    }
};

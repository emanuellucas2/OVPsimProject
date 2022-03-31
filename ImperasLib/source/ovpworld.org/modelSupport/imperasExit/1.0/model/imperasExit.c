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
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

//
// Intercept exit
//
static VMIOS_INTERCEPT_FN(exitInt) {

    vmiPrintf(
        "Processor '%s' terminated at '%s', address 0x" FMT_Ax "\n",
        vmirtProcessorName(processor),
        context,
        vmirtGetPC(processor)
    );

    vmirtExit(processor);
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,            // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,  // type
    .packageName    = "ImperasExit",          // description
    .objectSize     = 0,                      // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "ovpworld.org",
        .library = "modelSupport",
        .name    = "imperasExit",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = 0,                      // object constructor
    .destructorCB   = 0,                      // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = 0,                      // morph callback
    .nextPCCB       = 0,                      // get next instruction address
    .disCB          = 0,                      // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // ----------------- ------- ------ -----------------
        // Name              Address Opaque Callback
        // ----------------- ------- ------ -----------------
        {  "exit",           0,      False, exitInt          },
        {  0                                                 },
    }
};


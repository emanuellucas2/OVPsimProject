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


#pragma once

// Imperas header files
#include "hostapi/impTypes.h"

// VMI area includes
#include "vmi/vmiOSAttrs.h"

// model header files
#include "riscvModelCallbacks.h"
#include "riscvTypeRefs.h"


//
// OpenHW interrupts
//
typedef enum openhwIntE {
    OHWI_LoadBusFault  = 128,
    OHWI_StoreBusFault = 129,
} openhwInt;

//
// OpenHW exceptions
//
typedef enum openhwExceptionE {
    OHW_E_InstructionBusFault = 48,
} openhwException;


//
// Return net ports implemented by this extension
//
VMIOS_NET_PORT_SPECS_FN(openhwNetPorts);

//
// Initialize exception structures
//
void openhwExceptionInit(vmiosObjectP object);

//
// Free exception structures
//
void openhwExceptionFree(vmiosObjectP object);

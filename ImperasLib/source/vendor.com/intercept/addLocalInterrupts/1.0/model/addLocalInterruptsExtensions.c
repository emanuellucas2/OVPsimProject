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

// prefix for messages from this extension
#define CPU_PREFIX "ADD_LOCALINT"

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"

// processor model header files
#include "extensionConfig.h"

// base model header files
#include "riscvMessage.h"
#include "riscvStructure.h"


/*
DESCRIPTION
-----------
This example shows how to add local interrupts to a RISC-V model.

Each section below has further explanatory notes.
*/


////////////////////////////////////////////////////////////////////////////////
// CUSTOM INTERRUPT NUMBERS
////////////////////////////////////////////////////////////////////////////////

//
// Custom interrupts
//
typedef enum riscvExtIntE {
    EXT_I_INT21 = 21,
    EXT_I_INT22 = 22
} riscvExtInt;


////////////////////////////////////////////////////////////////////////////////
// EXTENSION OBJECT
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. This type holds all information added by an instance of this extension.
2. The extCB field holds function pointers and other data implementing
   communication between the base RISC-V model and the extension.
*/

typedef struct vmiosObjectS {

    // Info for associated processor
    riscvP           riscv;

    // extension callbacks
    riscvExtCB       extCB;

} vmiosObject;


////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Return current program counter
//
inline static Uns64 getPC(riscvP riscv) {
    return vmirtGetPC((vmiProcessorP)riscv);
}


////////////////////////////////////////////////////////////////////////////////
// LOCAL INTERRUPT PRIORITY
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. Local interrupts are enabled using the local_int_num and unimp_int_mask
   fields in the configuration list (see processor/riscv/model/riscvConfigList.c
   which has these lines:
        .local_int_num    = 7,         // enable local interrupts 16-22
        .unimp_int_mask   = 0x1f0000,  // int16-int20 absent
   This specifies that up to 7 local interrupts are available, but the first
   5 are unimplemented.
*/

//
// This function must return the relative priority of a custom interrupt, or
// 0 if the interrupt is not recognised by this extension
//
static RISCV_GET_INTERRUPT_PRI_FN(getInterruptPriority) {

    riscvExceptionPriority result = 0;

    if(intNum==EXT_I_INT21) {
        result = riscv_E_LocalPriority;
    } else if(intNum==EXT_I_INT22) {
        result = riscv_E_LocalPriority+1;
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
// TRAP NOTIFIER
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. This trap notifier is called whenever a trap occurs and gives the extension
   the opportunity to update state dependent on the trap. In this case, the
   notifier simple reports the trap without updating state.
*/

//
// Perform actions when an trap is taken
//
static RISCV_TRAP_NOTIFIER_FN(takeTrap) {

//  vmiosObjectP object = clientData;
    Uns64 pc    = getPC(riscv);
    Bool  isInt = RD_CSR_FIELD(riscv, mcause, Interrupt);

    if(isInt) {
        vmiMessage("I", CPU_PREFIX "_TRAP",
            SRCREF_FMT "TRAP:%u MODE:%u INTERRUPT:%u",
            SRCREF_ARGS(riscv, pc),
            RD_CSR_FIELD(riscv, mcause, ExceptionCode),
            mode,
            RD_CSR_FIELD(riscv, mcause, Interrupt)
        );
    }
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. For use with this extension infrastructure, these things must be done in the
   constructor:
   1.1. The clientData pointer in the extCB interface object must be set to
        the vmiosObject;
   1.2. The getInterruptPri pointer in the extCB interface object must be set to
        a function returning the relative priority of a custom interrupt;
   1.3. The trapNotifier field in the extCB interface object can optionally be
        set to a notifier called whenever an exception occurs;
   1.4. The extension interface must be registered with the base model using
        the registerExtCB interface function.
   Typically the constructor will also save a reference to the current
   processor and perform other initialisation, as shown below.
*/

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(addLocalInterruptsConstructor) {

    riscvP riscv = (riscvP)processor;

    object->riscv = riscv;

    // prepare client data
    object->extCB.clientData = object;

    // install notifier for suppression of memory exceptions
    object->extCB.getInterruptPri = getInterruptPriority;

    // install notifier when trap is taken
    object->extCB.trapNotifier = takeTrap;

    // register extension with base model using unique ID
    riscv->cb.registerExtCB(riscv, &object->extCB, EXTID_ADDLOCALINT);
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,           // version string
    .modelType     = VMI_INTERCEPT_LIBRARY, // type
    .packageName   = "addCSRs",             // description
    .objectSize    = sizeof(vmiosObject),   // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = addLocalInterruptsConstructor, // object constructor

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};


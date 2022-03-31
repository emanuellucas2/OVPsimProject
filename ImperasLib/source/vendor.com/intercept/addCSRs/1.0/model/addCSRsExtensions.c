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
#define CPU_PREFIX "ADD_CSRS"

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"

// extension header files
#include "addCSRsConfig.h"
#include "addCSRsCSR.h"

// processor model header files
#include "extensionConfig.h"

// base model header files
#include "riscvCSR.h"
#include "riscvCSRTypes.h"
#include "riscvMessage.h"
#include "riscvStructure.h"


/*
DESCRIPTION
-----------
This example shows how to add custom CSRs to a RISC-V model. Five CSRs are
added:

1. custom_rw1_32
----------------
This is a 32-bit M-mode CSR implemented as a plain register with a write mask
(some bits are not writeable). When accessed with XLEN 64, the value is zero
extended from 32 to 64 bits.

2. custom_rw2_64
----------------
This is a 64-bit M-mode CSR implemented as a plain register with a write mask
(some bits are not writeable). When accessed with XLEN 32, the most-significant
32 bits are zero.

3. custom_ro1
-------------
This is a 64-bit M-mode read-only CSR implemented as a plain register.

4. custom_rw3_32
----------------
This is a 32-bit M-mode CSR implemented using callback functions.

5. custom_rw4_64
----------------
This is a 64-bit M-mode CSR implemented using callback functions.

The accessibility of the CSR (access mode, and whether read/write or read-only)
is determined by its address, following standard conventions defined in the
Privileged Specification.

Each section below has further explanatory notes.
*/


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CSR IDENTIFIERS
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. This enumeration describes the CSRs implemented by the extension. Use the
   macro XCSR_ID to define each one for compatibility with standard utility
   macros.
*/

typedef enum extCSRIdE {

    // custom CSRs, plain registers
    XCSR_ID (custom_rw1_32),    // 0xBC0
    XCSR_ID (custom_rw2_64),    // 0xBC1
    XCSR_ID (custom_ro1),       // 0xFC0

    // custom CSRs, implemented by callbacks
    XCSR_ID (custom_rw3_32),    // 0xBC3
    XCSR_ID (custom_rw4_64),    // 0xBC4

    // base CSR with additional fields
    XCSR_ID (mstatus),          // 0x300

    // keep last (used to define size of the enumeration)
    XCSR_ID (LAST)

} extCSRId;


////////////////////////////////////////////////////////////////////////////////
// EXTENSION OBJECT
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. This type holds all information added by an instance of this extension.
2. The config field holds configuration-specific information (used, or example,
   to hold initial values for read-only CSR fields when these are configuration
   dependent.
3. The csr field holds values of each CSR defined by this extension.
4. The csrs field holds description information for each CSR defined by this
   extension.
5. The extCB field holds function pointers and other data implementing
   communication between the base RISC-V model and the extension.
*/

typedef struct vmiosObjectS {

    // Info for associated processor
    riscvP           riscv;

    // configuration (including CSR reset values)
    addCSRsConfig    config;

    // extension CSR info
    addCSRsCSRs      csr;                   // extension CSR values
    riscvCSRAttrs    csrs[XCSR_ID(LAST)];   // extension CSR definitions
    Bool             mstatus30;             // modified mstatus bit 30

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

//
// Return extension configuration using unique ID
//
static addCSRsConfigCP getExtConfig(riscvP riscv) {

    riscvExtConfigCP cfg = riscv->cb.getExtConfig(riscv, EXTID_ADDCSR);

    VMI_ASSERT(cfg, "ADDCSR config not found");

    return cfg->userData;
}


////////////////////////////////////////////////////////////////////////////////
// COMMANDS
////////////////////////////////////////////////////////////////////////////////

//
// Custom command to print extension CSRs
//
VMIOS_COMMAND_PARSE_FN(printCustomRegsCB) {

    riscvP riscv = object->riscv;
    Uns32  i;

    for(i=0xBC0; i<=0xBC3; i++) {
        vmiPrintf("CSR 0x%03x = 0x"FMT_Ax"\n", i, riscv->cb.readCSR(riscv, i));
    }

    return "";
}

//
// Add commands
//
static void addCommands(vmiosObjectP object) {
    vmiosAddCommandParse(
        object,
        "printCustomRegs",
        "Show values of all custom registers",
        printCustomRegsCB,
        VMI_CT_QUERY|VMI_CO_DIAG|VMI_CA_REPORT
    );
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CSRS
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. CSRs implemented as plain registers are useful if the CSR has no behavior
   associated with it but just a value.
2. For CSRs implemented using callbacks, use the macros RISCV_CSR_READFN and
   RISCV_CSR_WRITEFN to define read and write callbacks, respectively. The
   callbacks are passed an argument of type riscvCSRAttrsCP, which describes
   the CSR being accessed. Useful fields in this structure are:
       name : the CSR name
       object : the containing vmiosObject
3. Callbacks can refer to CSR fields in the containing vmiosObject using
   utility macros:
       RD_XCSR(_OBJ, _RNAME) : return the value of a CSR
       WR_XCSR(_OBJ, _RNAME, _VALUE) : update the value of a CSR
       RD_XCSR_FIELD(_OBJ, _RNAME, _FIELD) : return the value of a field
       WR_XCSR_FIELD(_OBJ, _RNAME, _FIELD, _VALUE) : set the value of a field
4. In the example callbacks below, register values are read and written without
   further action; typically some other actions would be performed as well
   (otherwise, the CSRs could be more-efficiently implemented as plain
   registers).
*/

//
// Read callback for CSR custom_rw3_32
//
static RISCV_CSR_READFN(custom_rw3_32R) {

    vmiosObjectP object = attrs->object;
    Int32        result = RD_XCSR(object, custom_rw3_32);

    return result;
}

//
// Write callback for CSR custom_rw3_32
//
static RISCV_CSR_WRITEFN(custom_rw3_32W) {

    vmiosObjectP object = attrs->object;

    WR_XCSR(object, custom_rw3_32, newValue);

    return newValue;
}

//
// Read callback for CSR custom_rw1_64
//
static RISCV_CSR_READFN(custom_rw4_64R) {

    vmiosObjectP object = attrs->object;
    Int64        result = RD_XCSR(object, custom_rw4_64);

    return result;
}

//
// Write callback for CSR custom_rw4_64
//
static RISCV_CSR_WRITEFN(custom_rw4_64W) {

    vmiosObjectP object = attrs->object;

    WR_XCSR(object, custom_rw4_64, newValue);

    return newValue;
}

//
// Enhanced mstatus type, with custom R/W field in bit 30
//
typedef union {
    Uns64 u64;
    struct {
        Uns64 standard1 : 30;
        Uns64 custom1   :  1;
        Uns64 standard2 : 33;
    } f;
} mstatusU;

//
// Read callback for mstatus CSR, with extra custom field
//
static RISCV_CSR_READFN(mstatusR) {

    vmiosObjectP object = attrs->object;

    // get value from base model
    mstatusU result = {u64 : riscv->cb.readBaseCSR(riscv, CSR_ID(mstatus))};

    // fill custom field from extension object
    result.f.custom1 = object->mstatus30;

    // return composed result
    return result.u64;
}

//
// Read callback for mstatus CSR, with extra custom field
//
static RISCV_CSR_WRITEFN(mstatusW) {

    vmiosObjectP object = attrs->object;

    // assign value to mstatusU for field extraction
    mstatusU result = {u64 : newValue};

    // extract custom field
    object->mstatus30 = result.f.custom1;

    // set value in base model
    result.u64 = riscv->cb.writeBaseCSR(riscv, CSR_ID(mstatus), newValue);

    // fill custom field from extension object
    result.f.custom1 = object->mstatus30;

    // return composed result
    return result.u64;
}

//
// CSR table
//
static const extCSRAttrs csrs[XCSR_ID(LAST)] = {

    //
    // -----------------------------------
    // CSRs IMPLEMENTED AS PLAIN REGISTERS
    // -----------------------------------
    //
    //            name           num    arch extension attrs    description               rCB rwCB wCB
    XCSR_ATTR_TC_(custom_rw1_32, 0xBC0, 0,   0,        0,0,0,0, "32-bit R/W CSR (plain)", 0,  0,   0),
    XCSR_ATTR_TC_(custom_rw2_64, 0xBC1, 0,   0,        0,0,0,0, "XLEN R/W CSR (plain)",   0,  0,   0),
    XCSR_ATTR_TC_(custom_ro1,    0xFC0, 0,   0,        0,0,0,0, "R/O CSR (plain)",        0,  0,   0),

    //
    // -------------------------------
    // CSRs IMPLEMENTED WITH CALLBACKS
    // -------------------------------
    //
    //            name           num    arch extension attrs    description            rCB             rwCB wCB
    XCSR_ATTR_TC_(custom_rw3_32, 0xBC2, 0,   0,        0,0,0,0, "32-bit R/W CSR (cb)", custom_rw3_32R, 0,   custom_rw3_32W),
    XCSR_ATTR_TC_(custom_rw4_64, 0xBC3, 0,   0,        0,0,0,0, "XLEN R/W CSR (cb)",   custom_rw4_64R, 0,   custom_rw4_64W),

    //
    // -----------------------------
    // MODIFIED BEHAVIOR OF BASE CSR
    // -----------------------------
    //
    //            name           num    arch extension attrs    description            rCB             rwCB wCB
    XCSR_ATTR_P__(mstatus,       0x300, 0,   0,        0,0,0,0, "Machine Status",      mstatusR,       0,   mstatusW      ),
};

//
// Reset implementation-specific CSRs
//
static RISCV_RESET_NOTIFIER_FN(CSRReset) {

    vmiosObjectP object = clientData;

    // reset custom mstatus field
    object->mstatus30 = 0;

    // reset custom CSRs by index
    riscv->cb.writeCSR(riscv, 0xBC0, 0);
    riscv->cb.writeCSR(riscv, 0xBC1, 0x1234);
    riscv->cb.writeCSR(riscv, 0xBC2, 0);
    riscv->cb.writeCSR(riscv, 0xBC3, 0);
}

//
// Initialize CSR registers
//
static void addCSRsCSRInit(vmiosObjectP object) {

    riscvP   riscv = object->riscv;
    extCSRId id;

    // initialise CSR values that have configuration values defined
    WR_XCSR(object, custom_ro1, object->config.csr.custom_ro1.u64.bits);

    // add commands
    addCommands(object);

    // register each CSR with the base model using the newCSR interface function
    for(id=0; id<XCSR_ID(LAST); id++) {

        extCSRAttrsCP  src = &csrs[id];
        riscvCSRAttrs *dst = &object->csrs[id];

        riscv->cb.newCSR(dst, &src->baseAttrs, riscv, object);
    }

    // perform initial CSR reset
    CSRReset(riscv, object);
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. For use with this extension infrastructure, two things must be done in the
   constructor:
   1.1. The clientData pointer in the extCB interface object must be set to
        the vmiosObject;
   1.2. The extension interface must be registered with the base model using
        the registerExtCB interface function;
   Typically the constructor will also save a reference to the current
   processor and perform other initialisation, as shown below.
*/

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(addCSRsConstructor) {

    riscvP riscv  = (riscvP)processor;

    object->riscv = riscv;

    // prepare client data
    object->extCB.clientData    = object;
    object->extCB.resetNotifier = CSRReset;

    // register extension with base model using unique ID
    riscv->cb.registerExtCB(riscv, &object->extCB, EXTID_ADDCSR);

    // copy configuration from template
    object->config = *getExtConfig(riscv);

    // initialize CSRs
    addCSRsCSRInit(object);
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

    .constructorCB = addCSRsConstructor,    // object constructor

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};


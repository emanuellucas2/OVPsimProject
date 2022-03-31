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

#include "vmi/vmiAttrs.h"
#include "v850BlockState.h"
#include "v850Structure.h"
#include "v850Functions.h"
#include "v850Doc.h"

static const char *dictNames[] = {
    [RH850_M_SUPERVISOR]     = "SUPERVISOR",
    [RH850_M_USER]           = "USER",
    [RH850_M_SUPERVISOR_MPU] = "SUPERVISOR_MPU",
    [RH850_M_USER_MPU]       = "USER_MPU",
    [RH850_M_LAST]           = 0
};

const vmiIASAttr modelAttrs = {
    ////////////////////////////////////////////////////////////////////////
    // VERSION & SIZE ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////

    .versionString      = VMI_VERSION,         // version string (THIS MUST BE 1ST)
    .modelType          = VMI_PROCESSOR_MODEL, // model type (THIS MUST BE 2ND)
    .releaseStatus      = VMI_OVP,
    .dictNames          = dictNames,           // null-terminated dictionary name list
    .cpuSize            = sizeof(v850),        // full size of CPU object
    .blockStateSize     = sizeof(v850BlockState),

    ////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .saveCB             = v850SaveState,
    .restoreCB          = v850RestoreState,

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB      = v850Constructor, // constructor
    .docCB              = v850Doc,         // doc constructor
    .vmInitCB           = v850VMInit,      // virtual memory initialization
    .destructorCB       = v850Destructor,  // destructor

    ////////////////////////////////////////////////////////////////////////
    // MORPHER CORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB            = v850Morph,     // morph callback
    .fetchSnapCB        = v850FetchSnap, // fetch address snap callback
    .rdSnapCB           = v850RdSnap,    // read address snap callback
    .wrSnapCB           = v850WrSnap,    // write address snap callback

    ////////////////////////////////////////////////////////////////////////
    // SIMULATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .getEndianCB        = v850GetEndian, // get processor endianness
    .nextPCCB           = v850nextPC,    // get next instruction address
    .disCB              = v850Dis,       // disassemble instruction
    .switchCB           = v850Switch,    // call on simulator context switch

    ////////////////////////////////////////////////////////////////////////
    // EXCEPTION ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .rdPrivExceptCB     = v850RdPrivExcept,  // read privilege exception
    .wrPrivExceptCB     = v850WrPrivExcept,  // write privilege exception
    .rdAlignExceptCB    = v850RdAlignExcept, // read alignment exception
    .wrAlignExceptCB    = v850WrAlignExcept, // write alignment exception
    .rdAbortExceptCB    = v850RdAbortExcept, // read abort exception
    .wrAbortExceptCB    = v850WrAbortExcept, // write abort exception
    .ifetchExceptCB     = v850IfetchExcept,  // execution privilege exception
    .arithExceptCB      = v850ArithExcept,   // arithmetic exception
    .icountExceptCB     = v850IcountExcept,  // instruction count exception

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = v850ParamSpecs,
    .paramValueSizeCB = v850ParamValueSize,

    ////////////////////////////////////////////////////////////////////////
    // PORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .busPortSpecsCB   = v850BusPortSpecs,
    .netPortSpecsCB   = v850NetPortSpecs,

    ////////////////////////////////////////////////////////////////////////
    // DEBUGGER INTEGRATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .regGroupCB         = v850RegGroup,      // regGroup callback
    .regInfoCB          = v850RegInfo,       // regInfo callback
    .regImplCB          = v850RegImpl,       // instruction attributes support
    .exceptionInfoCB    = v850ExceptionInfo, // exceptionInfo callback
    .modeInfoCB         = v850ModeInfo,      // modeInfo callback
    .getExceptionCB     = v850GetException,  // return current processor exception
    .getModeCB          = v850GetMode,       // return current processor mode
    .regReadCB          = 0,                 // default regRead callback
    .regWriteCB         = 0,                 // default regWrite callback
    .debugCB            = v850Debug,         // user-defined trace callback

    ////////////////////////////////////////////////////////////////////////
    // IMPERAS INTERCEPTED FUNCTION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .intReturnCB        = v850IntReturn, // morph return from opaque intercept
    .intResultCB        = v850IntResult, // set intercepted function result
    .intParCB           = v850IntPar,    // push function arguments

    ////////////////////////////////////////////////////////////////////////
    // PROCESSOR INFO ROUTINE
    ////////////////////////////////////////////////////////////////////////

    .procInfoCB  = v850ProcInfo

};

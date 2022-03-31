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
#include "ppc32Structure.h"
#include "ppc32Functions.h"

static const char *dictNames[] = {
    "REAL_PRIV",
    "REAL_USER",
    "REAL_HYPV",
    "VIRTUAL_PRIV_D",
    "VIRTUAL_PRIV_I",
    "VIRTUAL_PRIV_DI",
    "VIRTUAL_USER_D",
    "VIRTUAL_USER_I",
    "VIRTUAL_USER_DI",
    "VIRTUAL_HYPV_D",
    "VIRTUAL_HYPV_I",
    "VIRTUAL_HYPV_DI",
    0
};

const vmiIASAttr modelAttrs = {
    ////////////////////////////////////////////////////////////////////////
    // VERSION & SIZE ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////

    .versionString       = VMI_VERSION,         // version string (THIS MUST BE 1ST)
    .modelType           = VMI_PROCESSOR_MODEL, // model type (THIS MUST BE 2ND)
    .releaseStatus       = VMI_OVP,
    .dictNames           = dictNames,           // null-terminated dictionary name list
    .cpuSize             = sizeof(ppc32),       // full size of CPU object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB      = ppc32Constructor, // constructor
    .vmInitCB           = ppc32VMInit, // virtual memory initialization
    .destructorCB       = ppc32Destructor, // destructor

    ////////////////////////////////////////////////////////////////////////
    // MORPHER CORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB            = ppc32Morph,// morph callback
    .fetchSnapCB        = ppc32FetchSnap, // fetch address snap callback
    .rdSnapCB           = ppc32RdSnap, // read address snap callback
    .wrSnapCB           = ppc32WrSnap, // write address snap callback

    ////////////////////////////////////////////////////////////////////////
    // SIMULATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .getEndianCB        = ppc32GetEndian, // get processor endianness
    .nextPCCB           = ppc32nextPC, // get next instruction address
    .disCB              = ppc32Dis, // disassemble instruction
    .switchCB           = ppc32Switch, // call on simulator context switch

    ////////////////////////////////////////////////////////////////////////
    // EXCEPTION ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .rdPrivExceptCB     = ppc32RdPrivExcept, // read privilege exception
    .wrPrivExceptCB     = ppc32WrPrivExcept, // write privilege exception
    .rdAlignExceptCB    = ppc32RdAlignExcept, // read alignment exception
    .wrAlignExceptCB    = ppc32WrAlignExcept, // write alignment exception
    .rdAbortExceptCB    = ppc32RdAbortExcept, // read abort exception
    .wrAbortExceptCB    = ppc32WrAbortExcept, // write abort exception
    .ifetchExceptCB     = ppc32IfetchExcept, // execution privilege exception
    .arithExceptCB      = ppc32ArithExcept, // arithmetic exception
    .icountExceptCB     = ppc32IcountExcept, // instruction count exception

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = ppc32ParamSpecs,
    .paramValueSizeCB = ppc32ParamValueSize,

    ////////////////////////////////////////////////////////////////////////
    // PORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .busPortSpecsCB   = ppc32BusPortSpecs,
    .netPortSpecsCB   = ppc32NetPortSpecs,

    ////////////////////////////////////////////////////////////////////////
    // DEBUGGER INTEGRATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .regGroupCB         = ppc32RegGroup, // regGroup callback
    .regInfoCB          = ppc32RegInfo, // regInfo callback
    .exceptionInfoCB    = ppc32ExceptionInfo, // exceptionInfo callback
    .modeInfoCB         = ppc32ModeInfo, // modeInfo callback
    .getExceptionCB     = ppc32GetException, // return current processor exception
    .getModeCB          = ppc32GetMode, // return current processor mode
    .regReadCB          = 0, // default regRead callback
    .regWriteCB         = 0, // default regWrite callback
    .debugCB            = ppc32Debug, // user-defined trace callback

    ////////////////////////////////////////////////////////////////////////
    // IMPERAS INTERCEPTED FUNCTION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .intReturnCB        = ppc32IntReturn, // morph return from opaque intercept
    .intResultCB        = ppc32IntResult, // set intercepted function result
    .intParCB           = ppc32IntPar, // push function arguments

    ////////////////////////////////////////////////////////////////////////
    // PROCESSOR INFO ROUTINE
    ////////////////////////////////////////////////////////////////////////

    .procInfoCB  = ppc32ProcInfo

};

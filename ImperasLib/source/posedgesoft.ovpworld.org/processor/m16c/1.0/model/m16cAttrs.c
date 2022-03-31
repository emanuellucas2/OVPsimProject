/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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


// VMI header files
#include "vmi/vmiAttrs.h"

// model header files
#include "m16cStructure.h"
#include "m16cFunctions.h"

static const char *dictNames[] = {"NORMAL", 0};

//
// Configuration block for instruction-accurate modelling
//
const vmiIASAttr modelAttrs = {
    ////////////////////////////////////////////////////////////////////////
    // VERSION & SIZE ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,
    .modelType     = VMI_PROCESSOR_MODEL,
    .releaseStatus = VMI_OVP,
    .dictNames     = dictNames,
    .cpuSize       = sizeof(m16c),

    ////////////////////////////////////////////////////////////////////////
    // CREATE/DELETE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = m16cConstructor,
    .destructorCB  = m16cDestructor,

    ////////////////////////////////////////////////////////////////////////
    // MORPHER CORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB = m16cMorphInstruction,

    ////////////////////////////////////////////////////////////////////////
    // SIMULATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .getEndianCB = m16cGetEndian,
    .nextPCCB    = m16cNextInstruction,
    .disCB       = m16cDisassemble,

    ////////////////////////////////////////////////////////////////////////
    // EXCEPTION ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .rdAlignExceptCB = m16cRdAlignExceptionCB,
    .wrAlignExceptCB = m16cWrAlignExceptionCB,
    .ifetchExceptCB  = m16cIFetchExceptionCB,
    .arithExceptCB   = m16cArithExceptionCB,

    .exceptionInfoCB = m16cExceptionInfo,
    .getExceptionCB  = m16cGetException,

    ////////////////////////////////////////////////////////////////////////
    // REGISTER ACCESS SUPPORT ROUTINES (DEBUGGER & SEMIHOSTING)
    ////////////////////////////////////////////////////////////////////////

    .regInfoCB = m16cRegInfo,
    .debugCB   = m16cDumpRegisters,

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = m16cGetParamSpec,
    .paramValueSizeCB = m16cParamValueSize,

    ////////////////////////////////////////////////////////////////////////
    // PORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .busPortSpecsCB   = m16cGetBusPortSpec,
    .netPortSpecsCB   = m16cGetNetPortSpec,

    ////////////////////////////////////////////////////////////////////////
    // IMPERAS INTERCEPTED FUNCTION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .intReturnCB = m16cIntReturnCB,
    .intResultCB = m16cIntResultCB,
    .intParCB    = m16cIntParCB,

    ////////////////////////////////////////////////////////////////////////
    // PROCESSOR INFO ROUTINE
    ////////////////////////////////////////////////////////////////////////

    .procInfoCB  = m16cProcInfo
};




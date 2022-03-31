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


// VMI header files
#include "vmi/vmiAttrs.h"

// model header files
#include "or1kStructure.h"
#include "or1kFunctions.h"
#include "or1kDoc.h"

static const char *dictNames[] = {"SUPERVISOR", "USER", 0};

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
    .cpuSize       = sizeof(or1k),

    ////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .saveCB    = or1kSaveStateCB,
    .restoreCB = or1kRestoreStateCB,
    .srVersion = 1,

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = or1kConstructor,
    .docCB         = or1kDoc,
    .vmInitCB      = or1kVMInit,
    .destructorCB  = or1kDestructor,

    ////////////////////////////////////////////////////////////////////////
    // MORPHER CORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB = or1kMorphInstruction,

    ////////////////////////////////////////////////////////////////////////
    // SIMULATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .getEndianCB = or1kGetEndian,
    .nextPCCB    = or1kNextInstruction,
    .disCB       = or1kDisassemble,

    ////////////////////////////////////////////////////////////////////////
    // EXCEPTION ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .rdPrivExceptCB  = or1kRdPrivExceptionCB,
    .wrPrivExceptCB  = or1kWrPrivExceptionCB,
    .rdAlignExceptCB = or1kRdAlignExceptionCB,
    .wrAlignExceptCB = or1kWrAlignExceptionCB,
    .ifetchExceptCB  = or1kIFetchExceptionCB,
    .arithExceptCB   = or1kArithExceptionCB,
    .icountExceptCB  = or1kICountPendingCB,

    ////////////////////////////////////////////////////////////////////////
    // DEBUGGER INTEGRATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .regGroupCB      = or1kRegGroup,
    .regInfoCB       = or1kRegInfo,
    .regImplCB       = or1kRegImpl,
    .exceptionInfoCB = or1kExceptionInfo,
    .modeInfoCB      = or1kModeInfo,
    .getExceptionCB  = or1kGetException,
    .getModeCB       = or1kGetMode,
    .debugCB         = or1kDumpRegisters,

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = or1kGetParamSpec,
    .paramValueSizeCB = or1kParamValueSize,

    ////////////////////////////////////////////////////////////////////////
    // PORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .busPortSpecsCB     = or1kGetBusPortSpec,
    .fifoPortSpecsCB    = or1kGetFifoPortSpec,
    .netPortSpecsCB     = or1kGetNetPortSpec,

    ////////////////////////////////////////////////////////////////////////
    // IMPERAS INTERCEPTED FUNCTION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .intReturnCB = or1kIntReturnCB,
    .intResultCB = or1kIntResultCB,
    .intParCB    = or1kIntParCB,

    ////////////////////////////////////////////////////////////////////////
    // PROCESSOR INFO ROUTINE
    ////////////////////////////////////////////////////////////////////////

    .procInfoCB  = or1kProcInfo,
};

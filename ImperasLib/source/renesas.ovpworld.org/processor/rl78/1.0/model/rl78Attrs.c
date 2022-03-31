/*
 * Copyright (c)      2016 eSOL TRINITY, www.esol-trinity.co.jp
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

//#include "vmi/vmiAttrs.h"

// model header files
#include "rl78Structure.h"
#include "rl78Functions.h"
#include "rl78Parameters.h"
#include "rl78Doc.h"

static const char *dictNames[] = {"RB0", "RB1", "RB2", "RB3", 0};

//
// Configuration block for instruction-accurate modelling
//
const vmiIASAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION & SIZE ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////

    .versionString        = VMI_VERSION,
    .modelType            = VMI_PROCESSOR_MODEL,
    .releaseStatus        = VMI_OVP,

    ////////////////////////////////////////////////////////////////////////
    // SIZE ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////

    .dictNames            = dictNames,
    .cpuSize              = sizeof(rl78),

    ////////////////////////////////////////////////////////////////////////
    // CREATE/DELETE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB        = rl78Constructor,
    .docCB                = rl78Doc,
    .vmInitCB             = rl78VmInit,          // virtual memory initialization
    .destructorCB         = rl78Destructor,

    ////////////////////////////////////////////////////////////////////////
    // MORPHER CORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB              = rl78MorphInstruction,
    .rdSnapCB             = rl78RdSnapCB,
    .wrSnapCB             = rl78WrSnapCB,

    ////////////////////////////////////////////////////////////////////////
    // SIMULATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .getEndianCB          = rl78GetEndian,
    .nextPCCB             = rl78NextInstruction,
    .disCB                = rl78Disassemble,

    ////////////////////////////////////////////////////////////////////////
    // EXCEPTION ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .ifetchExceptCB       = rl78IFetchExceptionCB,

    ////////////////////////////////////////////////////////////////////////
    // DEBUGGER INTEGRATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .regGroupCB           = rl78RegGroup,
    .regInfoCB            = rl78RegInfo,
    .exceptionInfoCB      = rl78ExceptionInfo,
    .modeInfoCB           = rl78ModeInfo,
    .getExceptionCB       = rl78GetException,
    .getModeCB            = rl78GetMode,
    .debugCB              = rl78DumpRegisters,

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER SUPPORT ROUTINES iterator to find the parameters
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB         = rl78GetParamSpec,
    .paramValueSizeCB     = rl78ParamValueSize,

    ////////////////////////////////////////////////////////////////////////
    // PORT ACCESS ROUTINES iterators to find the bus and net ports
    ////////////////////////////////////////////////////////////////////////

    .busPortSpecsCB       = rl78GetBusPortSpec,
    .netPortSpecsCB       = rl78GetNetPortSpec,

    ////////////////////////////////////////////////////////////////////////
    // IMPERAS INTERCEPTED FUNCTION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .intReturnCB          = rl78IntReturnCB,
    .intResultCB          = rl78IntResultCB,
    .intParCB             = rl78IntParCB,

    ////////////////////////////////////////////////////////////////////////
    // SIMULATOR ENVIRONMENT SUPPORT
    ////////////////////////////////////////////////////////////////////////

    .procInfoCB           = rl78ProcInfo
};

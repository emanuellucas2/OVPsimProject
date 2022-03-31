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

// basic number types
#include "hostapi/impTypes.h"

// model header files
#include "andesCustomPhases.h"
#include "andesTypeRefs.h"

// base model header files
#include "riscvRegisterTypes.h"
#include "riscvTypes.h"
#include "riscvVariant.h"

//
// This enumerates generic instructions
//
typedef enum andesITypeE {

    // add immediate instruction
    AN_IT_ADDI,

    // branch instructions
    AN_IT_BBC,
    AN_IT_BBS,
    AN_IT_BEQC,
    AN_IT_BNEC,

    // bit field instructions
    AN_IT_BFOS,
    AN_IT_BFOZ,

    // load effective address instruction
    AN_IT_LEA,

    // load and store instructions
    AN_IT_L,
    AN_IT_S,

    // find instructions
    AN_IT_FFB,
    AN_IT_FFZMISM,
    AN_IT_FFMISM,
    AN_IT_FLMISM,

    // execute table instruction
    AN_IT_EXEC_IT,

    // half-precision floating-point instructions
    AN_IT_FLHW,
    AN_IT_FSHW,

    // int4 vector load extension instructions
    AN_IT_VLNV,

    // bfloat16 extension instructions
    AN_IT_VFWCVT_S_BF16,
    AN_IT_VFNCVT_BF16_S,
    AN_IT_FCVT_S_BF16,
    AN_IT_FCVT_BF16_S,

    // vector packed FP16 extension
    AN_IT_VFPMADT_VF,
    AN_IT_VFPMADB_VF,

    // base model instructions affected by alignment
    AN_IT_MSA_UNA,

    // define custom instructions
    #if defined(CUSTOMFILE)
        #define ANDES_CUSTOM_PHASE ANDES_CUSTOM_ITYPE
        #include CUSTOMFILE
        #undef ANDES_CUSTOM_PHASE
    #endif

    // KEEP LAST
    AN_IT_LAST

} andesIType;

//
// This defines the maximum number of argument registers
//
#define AN_MAX_AREGS 4

//
// This structure is filled with information extracted from the decoded
// instruction
//
typedef struct andesInstrInfoS {

    const char       *opcode;           // opcode name
    const char       *format;           // disassembly format string
    riscvAddr         thisPC;           // instruction address
    Uns32             instruction;      // instruction word
    Uns8              bytes;            // instruction size in bytes (2 or 4)
    andesIType        type;             // instruction type
    riscvArchitecture arch;             // architecture requirements
    Bool              unsExt;           // whether to extend unsigned
    Bool              unsExtQ;          // whether extend unsigned implicit
    Bool              ze32;             // whether to zero-extend 32-bit argument
    Bool              cvtF32;           // includes implicit F32 conversion?
    Uns32             memBits;          // load/store size
    Uns32             elemBits;         // element size
    Uns64             c1;               // constant value 1
    Uns64             c2;               // constant value 2
    riscvRegDesc      r[AN_MAX_AREGS];  // argument registers
    riscvRegDesc      mask;             // mask register
    riscvRegDesc      rImplicit;        // implicit register argument

} andesInstrInfo;


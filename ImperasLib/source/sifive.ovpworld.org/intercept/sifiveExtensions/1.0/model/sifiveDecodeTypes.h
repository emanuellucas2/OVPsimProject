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
#include "sifiveTypeRefs.h"

// base model header files
#include "riscvRegisterTypes.h"
#include "riscvTypes.h"
#include "riscvVariant.h"

//
// This enumerates generic instructions
//
typedef enum sifiveITypeE {

    // SiFive custom instructions
    S5_IT_CFLUSH,
    S5_IT_CEASE,

    // KEEP LAST
    S5_IT_LAST

} sifiveIType;

#define S5_MAX_AREGS 1

//
// This structure is filled with information extracted from the decoded
// instruction
//
typedef struct sifiveInstrInfoS {

    const char       *opcode;           // opcode name
    const char       *format;           // disassembly format string
    riscvAddr         thisPC;           // instruction address
    Uns32             instruction;      // instruction word
    Uns8              bytes;            // instruction size in bytes (2 or 4)
    sifiveIType       type;             // instruction type
    riscvArchitecture arch;             // architecture requirements
    riscvRegDesc      r[S5_MAX_AREGS];  // argument registers

} sifiveInstrInfo;


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


#ifndef M16C_MORPH_H
#define M16C_MORPH_H

// VMI header files
#include "vmi/vmiTypes.h"

// model header files
#include "m16cDecode.h"
#include "m16cMorphEntries.h"


//
// Dispatcher callback type
//
#define M16C_MORPH_FN(_NAME) void _NAME(m16cMorphStateP state)
typedef M16C_MORPH_FN((*m16cMorphFn));

//
// This structure provides information required to morph code for an instruction
//
typedef struct m16cMorphAttrS {
    m16cVariant     variant;        // required variant
    m16cMorphFn     morphCB;        // callback function to morph the instruction
    m16cMorphFn     condMorphCB;        // callback function to morph the instruction
    vmiBinop        binop     :8;   // if a simple binary operation
    vmiFlagsCP      flags;          // flags Constant pointer
    Uns8            dataSize;       // Size of data in bits for load store operations, 8, 16, 32
    Bool            sign;           // Signed result (or extended) is true
} m16cMorphAttr;


//
// This structure holds state for a single instruction as it is morphed
//
typedef struct m16cMorphStateS {
    m16cInstructionInfo info;        // instruction description (from decoder)
    m16cMorphAttrCP     attrs;       // instruction attributes
    m16cP               m16c;        // current processor
    Uns32               nextPC;      // next instruction address in sequence
} m16cMorphState;

#endif

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

// base model header files
#include "riscvCSR.h"


// -----------------------------------------------------------------------------
// tm_cfg     (id 0xFD0)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 tmPresent :  1;
    Uns32 _u1       : 31;
} CSR_REG_TYPE_32(tm_cfg);

// define 32 bit type
CSR_REG_STRUCT_DECL_32(tm_cfg);


////////////////////////////////////////////////////////////////////////////////
// SYSTEM REGISTER CONTAINER
////////////////////////////////////////////////////////////////////////////////

//
// This type defines the CSRs implemented as true registers in the processor
// structure
//
typedef struct tmCSRsS {
    CSR_REG_DECL(tm_cfg);       // 0xFD0
} tmCSRs;



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

// Imperas header files
#include "hostapi/impTypes.h"

// extension header files
#include "tmCSR.h"

//
// This enumerates extension configurable architecture features - allow
// transaction and WFE instructions to be separately configured
//
typedef enum tmVariantE {
    EXT_TM  = (1<<0),
    EXT_WFE = (1<<1),
    EXT_ALL = (EXT_TM|EXT_WFE),
} tmVariant;

//
// This is used to define extension configuration options
//
typedef struct tmConfigS {

    tmVariant variant;

    // TM extension CSR register values
    struct {
        CSR_REG_DECL(tm_cfg);
    } csr;

} tmConfig;

DEFINE_S (tmConfig);
DEFINE_CS(tmConfig);

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
#include "addCSRsCSR.h"

//
// This is used to define extension configuration options
//
typedef struct addCSRsConfigS {

    // extension CSR register values in configuration
    struct {
        CSR_REG_DECL(custom_ro1);
    } csr;

} addCSRsConfig;

DEFINE_S (addCSRsConfig);
DEFINE_CS(addCSRsConfig);

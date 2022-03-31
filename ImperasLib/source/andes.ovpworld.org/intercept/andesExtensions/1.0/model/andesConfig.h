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

// model header files
#include "andesCSR.h"
#include "andesTypeRefs.h"

// Unique ID for Andes OVPworld model extension
#define ANDES_OVP_CONFIG_ID (('A' << 8) + 'O')

//
// This is used to define a processor configuration option
//
typedef struct andesConfigS {

    // configuration not visible in CSR state
    Uns32 PMA_grain;        // PMA region grain size

    // CSR register values
    struct {
        CSR_REG_DECL(milmb);
        CSR_REG_DECL(mdlmb);
        CSR_REG_DECL(mmsc_cfg);
        CSR_REG_DECL(micm_cfg);
        CSR_REG_DECL(mdcm_cfg);
        CSR_REG_DECL(mvec_cfg);
        CSR_REG_DECL(ml2c_ctl_base);
        CSR_REG_DECL(uitb);
    } csr;

    // CSR register masks
    struct {
        CSR_REG_DECL(milmb);
        CSR_REG_DECL(mdlmb);
    } csrMask;

} andesConfig;

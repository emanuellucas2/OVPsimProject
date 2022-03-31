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

// VMI header files
#include "hostapi/typeMacros.h"

// VMI header files
#include "vmi/vmiTypes.h"

// base model header files
#include "riscvTypeRefs.h"

// base model header files
#include "riscvVariant.h"


//
// Is the processor a cluster container?
//
Bool sifiveIsCluster(riscvP riscv);

//
// Is the processor a leaf?
//
Bool sifiveIsLeaf(riscvP riscv);

//
// Return the current XLEN
//
Uns32 sifiveGetXlenMode(riscvP riscv);

//
// Return the configured XLEN (may not be the current XLEN if dynamic update
// of XLEN is allowed)
//
Uns32 sifiveGetXlenArch(riscvP riscv);

//
// Return the indexed X register name
//
const char *sifiveGetXRegName(riscvP riscv, Uns32 index);

//
// Return the indexed F register name
//
const char *sifiveGetFRegName(riscvP riscv, Uns32 index);

//
// Return the indexed V register name
//
const char *sifiveGetVRegName(riscvP riscv, Uns32 index);

//
// Return SiFive Ovpworld extension configuration for RISC-V processor
//
sifiveConfigCP sifiveExtConfig(riscvP riscv);

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

#ifndef PPC32_VM_H
#define PPC32_VM_H
#include "vmi/vmiTypes.h"
#include "vmi/vmiDbg.h"
#include "ppc32TypeRefs.h"
#include "ppc32Structure.h"

//
// Table of processor mode descriptions
//
static const vmiModeInfo modes[] = {
    { "REAL_PRIV",       VM_MODE_REAL_PRIV,       "Real Mode Privileged" },
    { "REAL_USER",       VM_MODE_REAL_USER,       "Real Mode User" },
    { "REAL_HYPV",       VM_MODE_REAL_HYPV,       "Real Mode Hypervisor" },
    { "VIRTUAL_PRIV_D",  VM_MODE_VIRTUAL_PRIV_D,  "Virtual Mode Privileged Data" },
    { "VIRTUAL_PRIV_I",  VM_MODE_VIRTUAL_PRIV_I,  "Virtual Mode Privileged Instruction" },
    { "VIRTUAL_PRIV_DI", VM_MODE_VIRTUAL_PRIV_DI, "Virtual Mode Privileged Data and Instruction" },
    { "VIRTUAL_USER_D",  VM_MODE_VIRTUAL_USER_D,  "Virtual Mode User Data" },
    { "VIRTUAL_USER_I",  VM_MODE_VIRTUAL_USER_I,  "Virtual Mode User Instruction" },
    { "VIRTUAL_USER_DI", VM_MODE_VIRTUAL_USER_DI, "Virtual Mode User Data and Instruction" },
    { "VIRTUAL_HYPV_D",  VM_MODE_VIRTUAL_HYPV_D,  "Virtual Mode Hypervisor Data" },
    { "VIRTUAL_HYPV_I",  VM_MODE_VIRTUAL_HYPV_I,  "Virtual Mode Hypervisor Instruction" },
    { "VIRTUAL_HYPV_DI", VM_MODE_VIRTUAL_HYPV_DI, "Virtual Mode Hypervisor Data and Instruction" },
    { 0, 0, 0 }
};

//
// Return processor mode
//
ppc32VMMode ppc32GetVMMode(ppc32P ppc32);

#endif // PPC32_VM_H

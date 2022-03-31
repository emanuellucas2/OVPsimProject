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

// Imperas header files
#include "hostapi/impTypes.h"

// VMI header files
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"

// model header files
#include "andesStructure.h"
#include "andesUtils.h"

// base model header files
#include "riscvStructure.h"


//
// Is the processor a cluster container?
//
Bool andesIsCluster(riscvP riscv) {
    return riscv->configInfo.members;
}

//
// Is the processor a leaf?
//
Bool andesIsLeaf(riscvP riscv) {
    return !vmirtGetSMPChild((vmiProcessorP)riscv);
}

//
// Return the current XLEN
//
Uns32 andesGetXlenMode(riscvP riscv) {
    return riscv->cb.getXlenMode(riscv);
}

//
// Return the configured XLEN (may not be the current XLEN if dynamic update
// of XLEN is allowed)
//
Uns32 andesGetXlenArch(riscvP riscv) {
    return riscv->cb.getXlenArch(riscv);
}

//
// Return the indexed X register name
//
const char *andesGetXRegName(riscvP riscv, Uns32 index) {
    return riscv->cb.getXRegName(riscv, index);
}

//
// Return the indexed F register name
//
const char *andesGetFRegName(riscvP riscv, Uns32 index) {
    return riscv->cb.getFRegName(riscv, index);
}

//
// Return the indexed V register name
//
const char *andesGetVRegName(riscvP riscv, Uns32 index) {
    return riscv->cb.getVRegName(riscv, index);
}

//
// Adjust the given vmiReg for a register in the extension object so that it
// can be accessed from the processor
//
vmiReg andesObjectReg(vmiosObjectP object, vmiReg reg) {

    riscvP riscv = object->riscv;
    UnsPS  delta = (UnsPS)object - (UnsPS)riscv;

    return VMI_REG_DELTA(reg, delta);
}

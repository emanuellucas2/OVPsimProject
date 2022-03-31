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

#include "vmi/vmiAttrs.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"
#include "ppc32VM.h"
#include "ppc32SPR.h"

VMI_VMINIT_FN(ppc32VMInit) {
}

//
// Return processor mode
//
ppc32VMMode ppc32GetVMMode(ppc32P ppc32) {

    // HV PR
    //  0  0    Privileged
    //  0  1    Problem (user)
    //  1  0    Privileged and Hypervisor
    //  1  1    Problem (user)

    // IR
    // 0        Instruction Address Translation Disabled
    // 1        Instruction Address Translation Enabled

    // DR
    // 0        Data Address Translation Disabled
    //          Effective Address Overflow does not occur
    // 1        Data Address Translation Enabled
    //          Effective Address Overflow causes Data Storage Interrupt

    ppc32VMMode mode = VM_MODE_REAL;

    Uns8 ModeBits = ppc32ReadMSR_VMMode (ppc32);

    switch (ModeBits) {
    case 0x0: // 0b0000:
        mode = VM_MODE_REAL_PRIV;
        break;
    case 0x4: // 0b0100:
        mode = VM_MODE_VIRTUAL_PRIV_D;
        break;
    case 0x8: // 0b1000:
        mode = VM_MODE_VIRTUAL_PRIV_I;
        break;
    case 0xc: // 0b1100:
        mode = VM_MODE_VIRTUAL_PRIV_DI;
        break;

    case 0x1: // 0b0001:
    case 0x3: // 0b0011:
        mode = VM_MODE_REAL_USER;
        break;
    case 0x5: // 0b0101:
    case 0x7: // 0b0111:
        mode = VM_MODE_VIRTUAL_USER_D;
        break;
    case 0x9: // 0b1001:
    case 0xb: // 0b1011:
        mode = VM_MODE_VIRTUAL_USER_I;
        break;
    case 0xd: // 0b1101:
    case 0xf: // 0b1111:
        mode = VM_MODE_VIRTUAL_USER_DI;
        break;

    case 0x2: // 0b0010:
        mode = VM_MODE_REAL_HYPV;
        break;
    case 0x6: // 0b0110:
        mode = VM_MODE_VIRTUAL_HYPV_D;
        break;
    case 0xa: // 0b1010:
        mode = VM_MODE_VIRTUAL_HYPV_I;
        break;
    case 0xe: // 0b1110:
        mode = VM_MODE_VIRTUAL_HYPV_DI;
        break;
    }

    return mode;
}

VMI_GET_MODE_FN(ppc32GetMode) {
    return &modes[ppc32GetVMMode((ppc32P)processor)];
}

VMI_MODE_INFO_FN(ppc32ModeInfo) {
    return 0;
}

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



// VMI header files
#include "vmi/vmiCxt.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

// model header files
#include "m16cFunctions.h"
#include "m16cDecode.h"

//
// This returns the endianness of the m16c processor
//
VMI_ENDIAN_FN(m16cGetEndian) {
    return MEM_ENDIAN_LITTLE;  // Little
}

//
// Return the next instruction address after 'thisPC'.
//
VMI_NEXT_PC_FN(m16cNextInstruction) {
    m16cInstructionInfo info;

    m16cDecode((m16cP)processor, thisPC, &info);

    Uns32 nextAddress = (Uns32)(thisPC + info.bytes);
    return nextAddress;
}

//
// Fill the full current value of the SR register, including bits normally
// maintained in separate flags fields
//
inline static void fillFLG(m16cP m16c) {
    Uns32 nextFLG = 0;
    if (m16c->carryFlag)                nextFLG |= M16C_FLG_C;
    if (m16c->debugFlag)                nextFLG |= M16C_FLG_D;
    if (m16c->zeroFlag)                 nextFLG |= M16C_FLG_Z;
    if (m16c->signFlag)                 nextFLG |= M16C_FLG_S;
    if (m16c->regBankSelectFlag)        nextFLG |= M16C_FLG_B;
    if (m16c->overflowFlag)             nextFLG |= M16C_FLG_O;
    if (m16c->intEnableFlag)            nextFLG |= M16C_FLG_I;
    if (m16c->spSelectFlag)             nextFLG |= M16C_FLG_U;
    nextFLG |= (m16c->intPriorityLevel << 13);
    m16c->regs[M16C_REG_FLG] = nextFLG;
}

//
// Return the current value of the FLG register
//
Uns32 m16cGetFLG(m16cP m16c) {
    fillFLG(m16c);
    return m16c->regs[M16C_REG_FLG];
}

//
// Dump M16C registers
//
VMI_DEBUG_FN(m16cDumpRegisters) {
    m16cP m16c = (m16cP)processor;
    // Uns32 i    = 0;
    fillFLG(m16c);

    vmiPrintf("----------   ---------   -------------  ----------\n");

    vmiPrintf(" Bank 0:     Bank 1:     PC:   %05x    U: %01x\n", (Uns32)vmirtGetPC(processor), m16c->spSelectFlag);
    Uns8 *tmpP=&m16c->regs[M16C_REG_R0]; // Windows64 compiler requires this hack to avoid strict aliasing rule! TODO: Add cleaner way of doing this
    vmiPrintf(" R0: %04x    R0: %04x    INTB: %05x    I: %01x\n", *((Uns16 *)tmpP), GET_REG16(m16c,M16C_REG_R0B), GET_REG16(m16c,M16C_REG_INTB), m16c->intEnableFlag);
    vmiPrintf(" R1: %04x    R1: %04x    USP:   %04x    O: %01x\n", GET_REG16(m16c,M16C_REG_R1), GET_REG16(m16c,M16C_REG_R1B), GET_REG16(m16c,M16C_REG_USP), m16c->overflowFlag);
    vmiPrintf(" R2: %04x    R2: %04x    ISP:   %04x    B: %01x\n", GET_REG16(m16c,M16C_REG_R2), GET_REG16(m16c,M16C_REG_R2B), GET_REG16(m16c,M16C_REG_ISP), m16c->regBankSelectFlag);
    vmiPrintf(" R3: %04x    R3: %04x    SB:    %04x    S: %01x\n", GET_REG16(m16c,M16C_REG_R3), GET_REG16(m16c,M16C_REG_R3B), GET_REG16(m16c,M16C_REG_SB), m16c->signFlag);
    vmiPrintf(" A0: %04x    A0: %04x    FLG:   %04x    Z: %01x\n", GET_REG16(m16c,M16C_REG_A0), GET_REG16(m16c,M16C_REG_A0B), GET_REG16(m16c,M16C_REG_FLG), m16c->zeroFlag);
    vmiPrintf(" A1: %04x    A1: %04x           %04x    D: %01x\n", GET_REG16(m16c,M16C_REG_A1), GET_REG16(m16c,M16C_REG_A1B), GET_REG16(m16c,38), m16c->debugFlag);
    vmiPrintf(" FB: %04x    FB: %04x    IPL:   %01x    C: %01x\n", GET_REG16(m16c,M16C_REG_FB), GET_REG16(m16c,M16C_REG_FBB), (GET_REG16(m16c,M16C_REG_FLG) &0x7000) >> 12, m16c->carryFlag);

    vmiPrintf("----------   ---------   -------------  ----------\n");
}


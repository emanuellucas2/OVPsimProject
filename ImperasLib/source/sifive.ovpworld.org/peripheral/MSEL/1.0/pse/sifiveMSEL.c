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

#include <string.h>

#include "pse.igen.h"

#define BPORT1 handles.bport1
#include "pse.macros.igen.h"

#define PREFIX "MSEL"

// Return appropriate instructions/jump addresses to model the power-on reset
// vector code described in SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf
// (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)

// RV64 Instructions to be read from CODE_RESET memory block
Uns32 rv64ResetCode[] = {
  0x00000297,    /* auipc   t0,0x0          */
  0xffc2a303,    /* lw      t1,-4(t0) # 0x0 */
  0x00331313,    /* slli    t1,t1,0x3       */
  0x006282b3,    /* add     t0,t0,t1        */
  0x0fc2a283,    /* lw      t0,252(t0)      */
  0x00028067,    /* jr      t0              */
};

// Jump targets to be read from TABLE_JUMPADDR memory block
Uns64 rv64JumpTargets[] = {
  0x00001004ULL,    // MSEL 0000: loops forever, waiting for debugger
  0x20000000ULL,    // MSEL 0001: memory-mapped QSPI0
  0x30000000ULL,    // MSEL 0010: memory-mapped QSPI1
  0x40000000ULL,    // MSEL 0011: uncached ChipLink
  0x60000000ULL,    // MSEL 0100: cached ChipLink
  0x00010000ULL,    // MSEL 0101: ZSBL
  0x00010000ULL,    // MSEL 0110: ZSBL
  0x00010000ULL,    // MSEL 0111: ZSBL
  0x00010000ULL,    // MSEL 1000: ZSBL
  0x00010000ULL,    // MSEL 1001: ZSBL
  0x00010000ULL,    // MSEL 1010: ZSBL
  0x00010000ULL,    // MSEL 1011: ZSBL
  0x00010000ULL,    // MSEL 1100: ZSBL
  0x00010000ULL,    // MSEL 1101: ZSBL
  0x00010000ULL,    // MSEL 1110: ZSBL
  0x00010000ULL,    // MSEL 1111: ZSBL
};

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    // Initialize MSEL register to MSEL parameter value
    bhmUns32ParamValue ("MSEL", &bport1_REG_data.MSEL.value);
    bport1_REG_data.MSEL.value &= 0xf;

    // copy rv64ResetCode[] into BPORT1_CODE_RESET
    if (sizeof(rv64ResetCode) > BPORT1_CODE_RESET_BYTES) {
        bhmMessage(
            "F", PREFIX"_RTS",
            "BPORT1_CODE_RESET too small: %d bytes, must be at least %d bytes\n",
            BPORT1_CODE_RESET_BYTES,
            (Uns32)sizeof(rv64ResetCode)
        );
    }
    memcpy(BPORT1_CODE_RESET, rv64ResetCode, sizeof(rv64ResetCode));

    // copy rv64JumpTargets[] into BPORT1_TABLE_JUMPADDR
    if (sizeof(rv64JumpTargets) > BPORT1_TABLE_JUMPADDR_BYTES) {
        bhmMessage(
            "F", PREFIX"_JTS",
            "BPORT1_TABLE_JUMPADDR too small: %d bytes, must be at least %d bytes\n",
            BPORT1_TABLE_JUMPADDR_BYTES,
            (Uns32)sizeof(rv64JumpTargets)
        );
    }
    memcpy(BPORT1_TABLE_JUMPADDR, rv64JumpTargets, sizeof(rv64JumpTargets));

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

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

#define init        bport1_ab_data.init.value
#define osc         bport1_ab_data.osc.value
#define auxosc      bport1_ab_data.auxosc.value
#define sdram       bport1_ab_data.sdram.value

static Bool         remapped = True;

static Uns8 spd[128] = {
   128, 8, 4, 11, 9, 1, 64, 0,  2, 0xa0, 0xa0, 0, 0, 8, 0, 1,
   0xe, 4, 0x1c, 1, 2, 0x20, 0xc0, 0, 0, 0, 0, 0x30, 0x28, 0x30, 0x28, 0x40
};

PPM_REG_READ_CB(readID) {
    // YOUR CODE HERE (readID)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readLock) {
    // YOUR CODE HERE (readLock)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readProc) {
    // YOUR CODE HERE (readProc)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readStat) {
    // YOUR CODE HERE (readStat)
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(writeCtrl) {
    if (data & 8) {
        bhmMessage("F", "CM_RST", "Board reset");
    }
    if ((init ^ data) & 4) {
        Bool remap = ((data & 4) == 0);
        if (remap != remapped) {
            remapped = remap;
            bhmMessage("W", "CM_RM", "Remap not supported (%d)", remap);
        }
    }
    if ((init ^ data) & 1) {
        bhmMessage("I", "CM_LED", "Green LED %s", (data & 1) ? "on" : "off");
    }
    init = (init & ~ 5) | (data ^ 5);
}

PPM_READ_CB(readSpd) {
    Uns32 offset = addr - (handles.bport1 + 0x100);
    if (offset >= 128)
        return 0;
    else
        return spd[offset];
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    ppmInstallReadCallback(readSpd, 0, handles.bport1+0x100, 0x100);

    Uns32 memsz = 128; // (Mb)

    osc    = 0x01000048;
    auxosc = 0x0007feff;
    sdram  = 0x00011122;

    if (memsz >= 256) {
        spd[31] = 64;
        sdram |= 0x10;
    } else if (memsz >= 128) {
        spd[31] = 32;
        sdram |= 0x0c;
    } else if (memsz >= 64) {
        spd[31] = 16;
        sdram |= 0x08;
    } else if (memsz >= 32) {
        spd[31] = 4;
        sdram |= 0x04;
    } else {
        spd[31] = 2;
    }
    memcpy(spd + 73, "IMPERAS-MEMORY", 15);
    init = 0x00000112;
}



PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


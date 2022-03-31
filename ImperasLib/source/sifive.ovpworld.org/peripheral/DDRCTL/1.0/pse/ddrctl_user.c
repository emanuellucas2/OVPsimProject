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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Development
//                          Tue Apr 20 21:20:45 2021
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
#include <string.h>

#define PREFIX "DDRCTL"

// Maximum mask size (must be power of 2)
// - masked writes are limited to this number of bytes
// - masks are always considered aligned to this value
#define MASK_SIZE 4

static void nByteWrite(
    Uns32        offset,
    const Uns8  *data,
    Uns32        bytes,
    Uns8        *writeMask,
    Uns8        *base
) {
    Uns32 i;

    if (writeMask) {
        if (bytes > MASK_SIZE) {
            bhmMessage("E", PREFIX"_WTB",
                "%d byte write at offset %d exceeds maximum write size "
                "of %d bytes for register with write mask - ignored",
                bytes, offset, MASK_SIZE
            );
        } else  {
            for (i = 0; i < bytes; i++) {
                Uns8 mask  = *(writeMask + (offset & (MASK_SIZE-1)) + i);

                *(base + offset + i) &= mask;
                *(base + offset + i) |= *(data + i) & mask;
            }
        }
    } else {
        for (i = 0; i < bytes; i++) {
            *(base + offset + i) = *(data + i);
        }
    }
}

static void nByteRead(
    Uns32  offset,
    Uns8  *data,
    Uns32  bytes,
    Uns8  *base
) {
    Uns32 i;

    for (i = 0; i < bytes; i++) {
        *(data + i) = *(base + offset + i);
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NBYTE_READ_CB(readControlMem) {
    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX"_CTL",
            "%d byte read at offset %d (0x%x)",
            bytes, offset, offset
        );
    }
    nByteRead(offset, data, bytes, handles.CONTROL);
}

PPM_NBYTE_WRITE_CB(writeControlMem) {
    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX"_CTL",
            "%d byte write at offset %d (0x%x)",
            bytes,  offset, offset
        );
    }
    nByteWrite(offset, data, bytes, NULL, handles.CONTROL);
}

PPM_NBYTE_READ_CB(readBlockerMem) {
    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX"_BLK",
            "%d byte read at offset %d (0x%x)",
            bytes, offset, offset
        );
    }
    nByteRead(offset, data, bytes, handles.BLOCKER);
}

PPM_NBYTE_WRITE_CB(writeBlockerMem) {
    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX"_BLK",
            "%d byte write at offset %d (0x%x)",
            bytes, offset, offset
        );
    }
    nByteWrite(offset, data, bytes, NULL, handles.BLOCKER);
}

PPM_NBYTE_WRITE_CB(writeMaskedControlReg) {
    nByteWrite(offset, data, bytes, (Uns8 *)&userData, handles.CONTROL);
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

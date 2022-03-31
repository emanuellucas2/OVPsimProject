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

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#define PREFIX "NCEPLMT100"

#include "CLINT.timer.h"

static Uns32 numharts;

static Bool hartidInRange(Uns32 hartid, const char *type) {
    if (hartid >= numharts) {
        bhmMessage("W", PREFIX,
                "mtimecmp %s ignored. hartid=%d exceeds number of harts implemented = %d",
                type, hartid, numharts);
        return False;
    }
    return True;
}

static Bool accessOk(Uns32 bytes, Uns32 offset, const char *name) {
    Uns32 offsetAlign = offset & (bytes-1);

    if ((bytes != 4) && (bytes != 8)) {
        bhmMessage("W", PREFIX,
            "%d byte access to %s ignored. Only size of 4 or 8 allowed.",
            bytes, name);
        return False;
    }

    if (offsetAlign) {
        bhmMessage("W", PREFIX,
            "%d byte access with alignment of %d bytes to %s ignored.",
            bytes, offsetAlign, name);
        return False;
    }

    return True;
}

//////////////////////////////// Callbacks ////////////////////////////////

PPM_NBYTE_READ_CB(defaultMemRead) {
    bhmMessage("I", "PPM_DFRD",
        "Read at offset 0x%x ignored - no register defined at this offset",
        offset
    );
    memset(data, 0, bytes);
}

PPM_NBYTE_WRITE_CB(defaultMemWrite) {
    bhmMessage("I", "PPM_DFWR",
        "Write at offset 0x%x ignored - no register defined at this offset",
        offset
    );
}

//
// Read the mtime register
// - compute value based on current simulated time, clock frequency,
//   most recent time mtime was written and the value written at that time
//
PPM_NBYTE_READ_CB(rdMTIME) {
    if (!accessOk(bytes, offset, "mtime")) {
        // Return 0 after warning for invalid access size/align
        memset(data,  0,  bytes);
    } else {
        Uns64 mtimeNow = mtimeCountValue(bhmGetLocalTime());

        memcpy(data, ((Uns8 *)&mtimeNow) + (offset & 0x7), bytes);
    }
}

//
// Write the mtime register
// - sets mtimeOffset based on current simulated time, clock frequency and the value written
//
PPM_NBYTE_WRITE_CB(wrMTIME) {
    if (accessOk(bytes, offset, "mtime")) {
        Uns64 oldMtime = mtimeCountValue(bhmGetLocalTime());
        Uns64 newMtime = oldMtime;

        memcpy(((Uns8 *)&newMtime) + (offset & 0x7), data, bytes);

        if (newMtime != oldMtime) {

            mtimeUpdate(newMtime);

            if (PSE_DIAG_LOW) {
                bhmMessage("I", PREFIX, "new mtime=%llu", newMtime);
            }

            updateAllTimerData();
        }
    }
}

PPM_NBYTE_VIEW_CB(viewMTIME) {
    Uns64 mtime = mtimeCountValue(bhmGetLocalTime());
    memcpy(data, &mtime, BPORT1_AB_MTIME_WIDTH/8);
}

//
// Write the mtimecmp registers
//
// Note: if the 64 bit value is written 32 bits at a time this can result in
//       extra interrupts, but that is how the hardware works. The RiscV
//       privilige spec suggests writing all 1's to the high 32 bits, then writing
//       the low word value, then the high word value
//
PPM_NBYTE_WRITE_CB(wrMTIMECMP) {
    Uns32 hartid = PTR_TO_UNS32(userData);

    if (!accessOk(bytes, offset, "mtimecmp")) {
        // Ignore invalid access size/align
    } else if (!hartidInRange(hartid, "write")) {
        // Ignore out of range accesses
    } else {
        timerDataP timer = getTimer(hartid);

        memcpy(((Uns8 *)&bport1_ab_data.mtimecmp[hartid].value) + (offset & 0x7), data, bytes);

        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX,
                "new mtimecmp[%d]=%llu",
                hartid, bport1_ab_data.mtimecmp[hartid].value);
        }

        // Spec states the timer interrupt is de-asserted when the mtimecmp
        // register is written.
        clearInterrupt(timer);

        updateTimerData(timer);

        // Recalculate next timer event which could be modified by this change
        scheduleTimer(NULL);
    }
}

PPM_NBYTE_READ_CB(rdMTIMECMP) {
    Uns32 hartid = PTR_TO_UNS32(userData);

    if (!accessOk(bytes, offset, "mtimecmp") ||
        !hartidInRange(hartid, "read")) {
        // Return 0 after warning for invalid size/align/hartid
        memset(data,  0,  bytes);
    } else {
        memcpy(data, ((Uns8 *)&bport1_ab_data.mtimecmp[hartid].value) + (offset & 0x7), bytes);
    }
}

///////////////
// RESET NET //
///////////////

PPM_NET_CB(resetCB) {
    if (PSE_DIAG_LOW) {
        bhmMessage(
            "I", PREFIX "_RNC",
            "Reset net set to %d",
            (Uns32)value
        );
    }

    if(value != 0) {
        // perform reset
        reset_reset(value, NULL);
        mtimeUpdate(0);
        updateAllTimerData();
    }
}


PPM_CONSTRUCTOR_CB(constructor) {
    double clockMHz;

    periphConstructor();

    bhmDoubleParamValue("clockMHz", &clockMHz);
    if (clockMHz == 0.0) {
        bhmMessage("E", PREFIX, "clockMHz = 0.0 is not legal");
        clockMHz = 1.0;
    }

    bhmUns32ParamValue("numharts", &numharts);
    if (numharts < 1 || numharts > MAXHARTS) {
        bhmMessage("E", PREFIX, "Invalid numharts=%d. Must be between 1 and %d", numharts, MAXHARTS);
        numharts = MAXHARTS;
    }

    initTimers(numharts, handles.intOut_, &bport1_ab_data.mtimecmp[0].value, clockMHz);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}



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
//                           Imperas/OVP Generated
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pse.igen.h"

#define PORT0 handles.port0
#include "pse.macros.igen.h"

#define PREFIX "CLINT"

#include "CLINT.timer.h"

struct {
    Uns32  harts;              // Number of harts supported
    double clockMHz;           // Counter frequency from parameter
    double mtime;              // Most recently read value for mtime register
} config;

// Pointers to dynamically allocated arrays - 1 entry per hart
ppmNetHandle *MTimerInterrupt, *MSWInterrupt;
Uns8         *MSIP;
Uns64        *mtimecmp;

static void initPort(ppmNetPortP port, char *name) {
    port->name            = strdup(name);
    port->type            = PPM_OUTPUT_PORT;
    port->mustBeConnected = 0;
    port->description     = 0;
}

//
// Get dynamic net port table - create on first call
//
static ppmNetPortP getNetPortsUser() {

    static ppmNetPort *netPortsUser = NULL;

    if (!netPortsUser) {

        Uns32 numHarts;

        if (bhmUns32ParamValue("num_harts", &numHarts) && (numHarts > 1)) {

            ppmNetPort *p;
            char        name[32];
            Uns32       hart;
            Uns32       numPortsUser = (2 * (numHarts-1));

            // Allocate ppmNetPort array with 2 entries for each of
            // harts 1..n plus a terminating entry.
            // Note: hart 0's ports are created by iGen code
            netPortsUser = calloc(numPortsUser+1, sizeof(ppmNetPort));

            for (p=netPortsUser, hart = 1; hart < numHarts; hart++) {
                snprintf(name, sizeof(name), "MTimerInterrupt%u", hart);
                initPort(p++, name);
                snprintf(name, sizeof(name), "MSWInterrupt%u", hart);
                initPort(p++, name);
            }

            // Set name to NULL on last entry to indicate end of list
            p->name = NULL;

        }
    }

    return netPortsUser;

}

PPM_NET_PORT_FN(nextNetPortUser) {
    if(!netPort) {
        netPort = getNetPortsUser();
    } else {
        netPort++;
    }
    return (netPort && netPort->name) ? netPort : 0;
}

#define READ_ACCESS True
#define WRITE_ACCESS False

static Bool checkAlignedAccess(
    Uns32 bytes,
    Uns32 offset,
    char *name,
    Bool  isRead,
    Bool  okay
) {
    if (!bytes || ((bytes&(bytes-1))!=0) || ((offset&(bytes-1)))!=0) {
        bhmMessage(
            "W", PREFIX,
            "Unaligned %u byte access at offset %u on %s %s",
            bytes, offset, name, isRead ? "read" : "write"
        );
        okay = False;
    }
    if (!okay) {
        if (isRead) {
            ppmReadAbort();
        } else {
            ppmWriteAbort();
        }
    }
    return okay;
}

static Bool checkAlignedDWordAccess(Uns32 bytes, Uns32 offset, char *name, Bool isRead) {
    Bool okay = True;

    if (bytes != 4 && bytes != 8) {
        bhmMessage(
            "W", PREFIX,
            "Unsupported size %u on %s %s",
            bytes, name, isRead ? "read" : "write"
        );
        okay = False;
    }

    okay = checkAlignedAccess(bytes, offset, name, isRead, okay);

    return okay;
}

static Bool checkAlignedWordAccess(Uns32 bytes, Uns32 offset, char *name, Bool isRead) {
    Bool okay = True;

    if (bytes != 4) {
        bhmMessage(
            "W", PREFIX,
            "Unsupported size %u on %s %s",
            bytes, name, isRead ? "read" : "write"
        );
        okay = False;
    }

    okay = checkAlignedAccess(bytes, offset, name, isRead, okay);

    return okay;
}

static Uns32 checkHartid(Uns32 hartid) {
    if (hartid >= config.harts) {
        bhmMessage("F", PREFIX, "Internal error: Invalid hartid %u", hartid);
        // Not reached
    }
    return hartid;
}

//////////////////////////////// Callbacks ////////////////////////////////

PPM_NBYTE_READ_CB(msipRead) {
    Uns32 hartid = checkHartid(PTR_TO_UNS32(userData));

    if (!checkAlignedWordAccess(bytes, offset, "msip", READ_ACCESS)) {
        // Return 0 after warning for invalid access size/align
        memset(data,  0,  bytes);
    } else {
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "msipRead[%u]=0x%x", hartid, MSIP[hartid]);
        }
        *(Uns32*)data = MSIP[hartid];
    }
}

PPM_NBYTE_WRITE_CB(msipWrite) {
    Uns32 hartid = checkHartid(PTR_TO_UNS32(userData));

    if (!checkAlignedWordAccess(bytes, offset, "msip", WRITE_ACCESS)) {
        // Ignore invalid access
    } else {
        MSIP[hartid]  = (MSIP[hartid] & PORT0_MSIP_MSIP0_WRNMASK)
                      | (*(Uns32*)data & PORT0_MSIP_MSIP0_WRMASK);

        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "msipWrite[%u]=0x%x", hartid, MSIP[hartid]);
        }
        ppmWriteNet(MSWInterrupt[hartid], MSIP[hartid] & 1);
    }
}

PPM_NBYTE_VIEW_CB(msipView) {
    Uns32 hartid = checkHartid(PTR_TO_UNS32(userData));
    *(Uns32 *)data = MSIP[hartid];
    memcpy(data, &MSIP[hartid], PORT0_MSIP_MSIP0_WIDTH/8);
}


PPM_NBYTE_READ_CB(mtimecmpRead) {
    Uns32 hartid = checkHartid(PTR_TO_UNS32(userData));

    if (!checkAlignedDWordAccess(bytes, offset, "mtimecmp", READ_ACCESS)) {
        // Return 0 after warning for invalid access size/align
        memset(data,  0,  bytes);
    } else {

        memcpy(data, ((Uns8 *)&mtimecmp[hartid]) + (offset & 0x7), bytes);

        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "mtimecmpRead[%u] %s (0x%08x_%08x)",
                    hartid,
                    (bytes == 8) ? "64" : offset&0x7 ? "HI/32" : "LO/32)",
                    (Uns32)(mtimecmp[hartid] >> 32),
                    (Uns32)(mtimecmp[hartid] & 0xffffffffULL));
        }
    }
}

//
// Write the mtimecmp registers
//
// Note: if the 64 bit value is written 32 bits at a time this can result in
//       extra interrupts, but that is how the hardware works. The RiscV
//       privilige spec suggests writing all 1's to the high 32 bits, then writing
//       the low word value, then the high word value
//
PPM_NBYTE_WRITE_CB(mtimecmpWrite) {
    Uns32 hartid   = checkHartid(PTR_TO_UNS32(userData));

    if (!checkAlignedDWordAccess(bytes, offset, "mtimecmp", WRITE_ACCESS)) {
        // Ignore invalid access
    } else {
        timerDataP timer = getTimer(hartid);

        memcpy(((Uns8 *)&mtimecmp[hartid]) + (offset & 0x7), data, bytes);

        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "mtimecmpWrite[%u] %s mtimecmp=0x%08x_%08x",
                    hartid,
                    (bytes == 8) ? "64" : offset&0x7 ? "HI/32" : "LO/32)",
                    (Uns32)(mtimecmp[hartid] >> 32),
                    (Uns32)(mtimecmp[hartid] & 0xffffffffULL));
        }

        // Spec states the timer interrupt is de-asserted when the mtimecmp
        // register is written.
        clearInterrupt(timer);

        updateTimerData(timer);

        // Recalculate next timer event which could be modified by this change
        scheduleTimer(NULL);
    }
}

PPM_NBYTE_VIEW_CB(mtimecmpView) {
    Uns32 hartid = checkHartid(PTR_TO_UNS32(userData));
    memcpy(data, &mtimecmp[hartid], PORT0_MTIME_MTIMECMP0_WIDTH/8);
}

PPM_NBYTE_READ_CB(mtimeRead) {
    if (!checkAlignedDWordAccess(bytes, offset, "mtime", READ_ACCESS)) {
    } else {
        Uns64 mtimeNow = mtimeCountValue(bhmGetLocalTime());

        memcpy(data, ((Uns8 *)&mtimeNow) + (offset & 0x7), bytes);

        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "mtimeRead %s = %llu (0x%08x_%08x)",
                    (bytes == 8) ? "64" : offset&0x7 ? "HI/32" : "LO/32)",
                            mtimeNow,
                    (Uns32)(mtimeNow>>32),
                    (Uns32)(mtimeNow&0xffffffff));
        }
    }
}

PPM_NBYTE_WRITE_CB(mtimeWrite) {
    if (!checkAlignedDWordAccess(bytes, offset, "mtime", WRITE_ACCESS)) {
        // Ignore invalid access
    } else {
        Uns64 oldMtime = mtimeCountValue(bhmGetLocalTime());
        Uns64 newMtime = oldMtime;

        memcpy(((Uns8 *)&newMtime) + (offset & 0x7), data, bytes);

        if (newMtime != oldMtime) {

            mtimeUpdate(newMtime);

            if (PSE_DIAG_LOW) {
                bhmMessage("I", PREFIX, "new mtime=%lld", newMtime);
            }

            updateAllTimerData();
        }
    }
}

PPM_NBYTE_VIEW_CB(mtimeView) {
    Uns64 mtime = mtimeCountValue(bhmGetLocalTime());
    memcpy(data, &mtime, PORT0_MTIME_MTIME_WIDTH/8);
}

//
// Trap Reserved Memory RD/Write
//
PPM_NBYTE_READ_CB(defaultMemRead) {

    (void) checkAlignedWordAccess(bytes, offset, "reserved", READ_ACCESS);

    if (PSE_DIAG_HIGH) {
        bhmMessage(
            "W", PREFIX,
            "Read from unallocated region at offset 0x%08x",
            offset
        );
    }
    memset(data, 0, bytes);
}

PPM_NBYTE_WRITE_CB(defaultMemWrite) {
    (void) checkAlignedWordAccess(bytes, offset, "reserved", WRITE_ACCESS);

    if (PSE_DIAG_HIGH) {
        bhmMessage(
            "W", PREFIX,
        "Write to unallocated region at offset 0x%08x",
            offset
        );
    }
}

static void openNetPorts() {
    MTimerInterrupt = (ppmNetHandle *) calloc(config.harts, sizeof(ppmNetHandle));
    MSWInterrupt    = (ppmNetHandle *) calloc(config.harts, sizeof(ppmNetHandle));

    Uns32 iter;
    char name[32];
    for (iter=0; iter<config.harts; iter++) {
        snprintf(name, sizeof(name), "MTimerInterrupt%u", iter);
        MTimerInterrupt[iter] = ppmOpenNetPort(name);
        snprintf(name, sizeof(name), "MSWInterrupt%u", iter);
        MSWInterrupt[iter] = ppmOpenNetPort(name);
    }
}

PPM_NET_CB(resetCB) {

    // Reset mtime counter to 0
    mtimeUpdate(0);

    // reset MSIP values (mtimecmp values are not affected by reset)
    if(value != 0) {
        int id;
        for (id=0; id<config.harts; id++) {
            MSIP[id] = 0;
        }
        updateAllTimerData();
    }
}

static void modelInit () {

    char name[32];
    char desc[128];

    bhmUns32ParamValue ("num_harts", &config.harts);
    bhmDoubleParamValue("clockMHz",  &config.clockMHz);

    MSIP     = (Uns8 *)     (Uns8  *) calloc(config.harts, sizeof(Uns8));
    mtimecmp = (Uns64 *)    (Uns64 *) calloc(config.harts, sizeof(Uns64));

    openNetPorts();

    // Create registers for harts 1..num_harts
    // Note: registers for hart0 were created by iGen
    int id;
    for (id=1; id<config.harts; id++) {
        Uns32 offset;

        offset = 4 * id;    // 4-byte aligned
        snprintf(name, sizeof(name), "msip_msip%u", id);
        snprintf(desc, sizeof(desc), "Hart %u Machine-Mode Software Interrupt", id);
        ppmCreateNByteRegister(
            name,
            desc,
            PORT0_MSIP_MSIP0,
            offset,
            4,
            msipRead,
            msipWrite,
            msipView,
            &(MSIP[id]),
            UNS32_TO_PTR(id),
            True,
            True,
            True,
            BHM_ENDIAN_LITTLE
        );

        offset = (8 * id); // 8-byte aligned
        snprintf(desc, sizeof(desc), "Hart %u Machine-Mode Timer Compare", id);
        snprintf(name, sizeof(name), "mtime_mtimecmp%u", id);
        ppmCreateNByteRegister(
            name,
            desc,
            PORT0_MTIME_MTIMECMP0,
            offset,
            8,
            mtimecmpRead,
            mtimecmpWrite,
            mtimecmpView,
            &(mtimecmp[id]),
            UNS32_TO_PTR(id),
            True,
            True,
            True,
            BHM_ENDIAN_LITTLE
        );
    }

    initTimers(config.harts, MTimerInterrupt, mtimecmp, config.clockMHz);
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
    modelInit();
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

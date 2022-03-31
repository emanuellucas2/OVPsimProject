/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#include <stdio.h>
#include <string.h>

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"

#include "pse.igen.h"

#include "../application/radar.h"

#define PREFIX "RADAR"

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
}

PPM_DESTRUCTOR_CB(destructor) {
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

static void redraw (bhmHTTPChannel ch) {
    Uns32 dataSize = sizeof(sharedDataT);
    Uns8  AppData[dataSize];

    sharedDataP data = (sharedDataP) AppData;
    ppmReadAddressSpace (handles.MPORT, RADAR_DATA, dataSize, AppData);

    bhmHTTPElementOpen(ch, "ovpelement");
    bhmHTTPKeyPrintf(ch, "track", "%d", data->track);

    int id;
    for (id=0; id< data->numAircraft; id++) {
        bhmHTTPKeyPrintf(ch, "icao",  "%d", data->p[id].icao);
        bhmHTTPKeyPrintf(ch, "xy",    "%d", data->p[id].xy);
        bhmHTTPKeyPrintf(ch, "x",     "%d", data->p[id].x);
        bhmHTTPKeyPrintf(ch, "y",     "%d", data->p[id].y);
        bhmHTTPKeyPrintf(ch, "z",     "%d", data->p[id].z);
        bhmHTTPKeyPrintf(ch, "kns",   "%d", data->p[id].kns);
        bhmHTTPKeyPrintf(ch, "trk",   "%d", data->p[id].trk);
        bhmHTTPKeyPrintf(ch, "climb", "%d", data->p[id].climb);
    }

    bhmHTTPElementClose(ch, "ovpelement");
    bhmHTTPSend(ch);
}

BHM_HTTP_GET_FN(peripheralHTTPGet) {
    redraw (ch);
}

BHM_HTTP_POST_FN(peripheralHTTPPost) {
    if (strstr(body, "exit=clicked")) {
        bhmMessage("I", PREFIX "_SW", "Exit Button pushed - terminating simulation.");
        bhmFinish();
    } else if (strstr(body, "reset=clicked")) {
        sharedDataP data = (sharedDataP) RADAR_DATA;
        Uns32 reset = 1;
        bhmMessage("I", PREFIX "_SW", "Reset Button pushed.");
        union {int *resetPtr; Uns64 resetAddr;} u = {&data->reset};
        ppmWriteAddressSpace (handles.MPORT, u.resetAddr, 4, &reset);
        redraw (ch);
    }
}

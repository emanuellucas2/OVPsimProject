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
//                          Wed Jan 12 17:58:14 2011
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"
#include "peripheral/bhmHttp.h"

#define PREFIX "SWITCH"

//////////////////////////////// Callback stubs ////////////////////////////////

Uns32 availableSwitches;    // number of Switches to include
Uns8 swReg = 0;

#define GET_SW_BIT(_B) ((swReg & (1<<(_B)))?1:0)

static void redraw (bhmHTTPChannel ch) {

    bhmHTTPElementOpen(ch, "ovpelement");

    Uns32 i;
    for (i=0;i<availableSwitches;i++) {
        char sw[8];
        sprintf(sw, "sw%d", i);
        bhmHTTPKeyPrintf(ch, sw, "%d", GET_SW_BIT(i));
    }

    bhmHTTPKeyPrintf(ch, "power0", "");

    bhmHTTPElementClose(ch, "ovpelement");
    bhmHTTPSend(ch);
}

//static inline void showSwitches() {
void showSwitches() {
    char buffer[64]; buffer[0]=0;
    Uns32 i;

    if (!PSE_DIAG_LOW || (availableSwitches==0))
        return;     // do not show as diagnostic message

    for (i=0;i<availableSwitches;i++) {
        char buff[8]; buff[0]=0;
        sprintf(buff, "%s ", GET_SW_BIT(i) ? "ON" : "--");
        strcat(buffer, buff);
    }
    bhmMessage("I", PREFIX, "%s at %f", buffer, bhmGetLocalTime()/1000000);
}

static BHM_HTTP_GET_FN(get) {
    redraw(ch);
}

static BHM_HTTP_POST_FN(post) {

    Uns32 i;
    Uns32 swOld = swReg;
    for (i=0;i<availableSwitches;i++) {
        char sw[16];
        sprintf(sw, "sw%d=clicked", i);
        if (strstr(body, sw) ) {
            Uns32 bit  = GET_SW_BIT(i) ? 0 : (1<<i);
            Uns32 mask = ~(1<<(i));
            swReg = ((swReg & mask) | bit );
        }
    }
    if(PSE_DIAG_MEDIUM && (swOld != swReg)) {
        bhmMessage("I", "SW", "Switch Changed %x -> %x", swOld, swReg);
    }

    if (strstr(body, "power0=clicked")) {
        bhmMessage("I", "SW", "Power Switch pushed - terminating simulation.");
        bhmFinish();
    }

    redraw(ch);
}

PPM_REG_READ_CB(readSwitch) {
    *(Uns32 *) user = swReg;
    showSwitches();
    return swReg;
}

#define BUFSIZE 128000
static char space[BUFSIZE];

PPM_CONSTRUCTOR_CB(config) {

    periphConstructor();

    // configure number of Switches
    bhmUns32ParamValue("availableSwitches", &availableSwitches);

    // visualization (enabled with global command line argument)
    bhmHTTPMethods m = { get, post, space, BUFSIZE, 0 };
    bhmHTTPOpen(&m, "httpvis");
}



PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


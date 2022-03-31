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

#define PREFIX "LED"

//////////////////////////////// Callback stubs ////////////////////////////////

Uns32 availableLEDS;    // number of LEDs to include
Uns8 ledReg = 0;


//static inline void showLEDs() {
void showLEDs() {
    char buffer[64]; buffer[0]=0;
    Uns32 i;

    if (!PSE_DIAG_LOW || (availableLEDS==0))
        return;     // do not show as diagnostic message

    for (i=availableLEDS; i ; i--) {
        char buff[8]; buff[0]=0;
        sprintf(buff, "%s ", (ledReg & (1<<(i-1))) ? "ON" : "--");
        strcat(buffer, buff);
    }
    bhmMessage("I", PREFIX, "%s at %f", buffer, bhmGetLocalTime()/1000000);
}

static BHM_HTTP_GET_FN(get) {

    bhmHTTPElementOpen(ch, "ovpelement");

    Uns32 i;
    for (i=0;i<availableLEDS;i++) {
        char led[8];
        sprintf(led, "led%d", i);
        bhmHTTPKeyPrintf(ch, led, "%d", (ledReg & (1<<i))?1:0);
    }

    bhmHTTPKeyPrintf(ch, "power0", "");

    bhmHTTPElementClose(ch, "ovpelement");
    bhmHTTPSend(ch);
}

static BHM_HTTP_POST_FN(post) {
    if (strstr(body, "power0=clicked")) {
        bhmMessage("I", PREFIX "_SW", "Power Switch pushed - terminating simulation.");
        bhmFinish();
    }
}

PPM_REG_READ_CB(readLed) {
    return ledReg;
}

PPM_REG_WRITE_CB(resetLed) {
    ledReg &= ~data;
    showLEDs();
    *(Uns8*)user = ledReg;
}

PPM_REG_WRITE_CB(setLed) {
    ledReg |= data;
    showLEDs();
    *(Uns8*)user = ledReg;
}

PPM_REG_WRITE_CB(writeLed) {
    ledReg = data;
    showLEDs();
    *(Uns8*)user = ledReg;
}

#define BUFSIZE 128000
static char space[BUFSIZE];

PPM_CONSTRUCTOR_CB(config) {

    periphConstructor();

    // configure number of LEDs
    bhmUns32ParamValue("availableLEDS", &availableLEDS);

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


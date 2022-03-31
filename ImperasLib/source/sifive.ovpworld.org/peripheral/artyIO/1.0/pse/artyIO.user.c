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
#include <string.h>

#include "pse.igen.h"

#define PREFIX "ARTY_IO"

// input/output bit values
Uns32 dataIn;         // current input
Uns32 dataInLast;     // previous before change
Uns32 dataOut;        // current output

#define FLIP_BIT(_d, _b) ((_d & (1<<_b)) ? (_d &= ~(1<<_b)) : (_d |= (1<<_b)))
#define GET_BIT(_d, _b)  ((_d & (1<<_b)) ? 1 : 0)

const char *switchInfo[] = {"SW0","SW1","SW2","SW3","BTN0","BTN1","BTN2","BTN3"};
const char *ledInfo[]    = {"LD0red","LD0green","LD0blue"};

// bits for dataIn
#define BIT_SW0  0
#define BIT_SW1  1
#define BIT_SW2  2
#define BIT_SW3  3
#define BIT_BTN0 4
#define BIT_BTN1 5
#define BIT_BTN2 6
#define BIT_BTN3 7

// bit for dataOut
#define BIT_LED0R 0
#define BIT_LED0G 1
#define BIT_LED0B 2

//
// Show current state
//
void showState() {
    Uns32 i;
    char  dataInString[18];
    char  dataOutString[18];
    for (i=0;i<16;i++) {
        dataInString[15-i]  = (char)(dataIn  & (1<<i)) ? 'O' : '-';
        dataOutString[15-i] = (char)(dataOut & (1<<i)) ? 'O' : '-';
    }
    // terminate
    dataInString[16]=0;
    dataOutString[16]=0;
    bhmMessage("I", PREFIX "_STATE", "IN 15: %s :0  OUT 15: %s :0", dataInString, dataOutString);
}

static void writeOutput(Uns32 switchState) {

    static Uns32 switchStateLast = 0;

    if(switchState != switchStateLast) {
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX"_SW","Switch State Last 0x%x New 0x%x", switchStateLast, switchState);
        }
        switchStateLast = switchState;

        // update switches state output
        Uns32 i;
        ppmNetHandle *baseHandle = &(handles.SW0);
        for (i=0;i<=BIT_BTN3;i++) {
            ppmNetHandle *switchHandle=(baseHandle + i);
            Uns32 current = (Uns32)ppmReadNet(*switchHandle);
            Uns32     new = (switchState >> i) & 1;
            if(new != current) {
                if (PSE_DIAG_HIGH) {
                    bhmMessage("I", PREFIX"_SW","Switch %s State %u->%u", switchInfo[i], current, new);
                }
                ppmWriteNet(*switchHandle, new);
            }
        }
    }
}

static BHM_HTTP_GET_FN(get) {

    bhmHTTPElementOpen(ch, "ovpelement");

    bhmHTTPKeyPrintf(ch, "switches", "0x%0x", (dataIn & (BIT_SW0|BIT_SW1|BIT_SW2|BIT_SW3)));

    bhmHTTPKeyPrintf(ch, "sw0", "%d", GET_BIT(dataIn, BIT_SW0));
    bhmHTTPKeyPrintf(ch, "sw1", "%d", GET_BIT(dataIn, BIT_SW1));
    bhmHTTPKeyPrintf(ch, "sw2", "%d", GET_BIT(dataIn, BIT_SW2));
    bhmHTTPKeyPrintf(ch, "sw3", "%d", GET_BIT(dataIn, BIT_SW3));

    bhmHTTPKeyPrintf(ch, "btn0", "%d", GET_BIT(dataIn, BIT_BTN0));
    bhmHTTPKeyPrintf(ch, "btn1", "%d", GET_BIT(dataIn, BIT_BTN1));
    bhmHTTPKeyPrintf(ch, "btn2", "%d", GET_BIT(dataIn, BIT_BTN2));
    bhmHTTPKeyPrintf(ch, "btn3", "%d", GET_BIT(dataIn, BIT_BTN3));

    bhmHTTPKeyPrintf(ch, "led0R", "%d", GET_BIT(dataOut, BIT_LED0R));
    bhmHTTPKeyPrintf(ch, "led0G", "%d", GET_BIT(dataOut, BIT_LED0G));
    bhmHTTPKeyPrintf(ch, "led0B", "%d", GET_BIT(dataOut, BIT_LED0B));

    bhmHTTPKeyPrintf(ch, "power0", "");

    bhmHTTPElementClose(ch, "ovpelement");
    bhmHTTPSend(ch);
}


static BHM_HTTP_POST_FN(post) {
    Uns32 dataInLast = dataIn;
    if        (strstr(body, "sw0=clicked")) {
        FLIP_BIT(dataIn, BIT_SW0);
    } else if (strstr(body, "sw1=clicked")) {
        FLIP_BIT(dataIn, BIT_SW1);
    } else if (strstr(body, "sw2=clicked")) {
        FLIP_BIT(dataIn, BIT_SW2);
    } else if (strstr(body, "sw3=clicked")) {
        FLIP_BIT(dataIn, BIT_SW3);
    } else if (strstr(body, "btn0=clicked")) {
        FLIP_BIT(dataIn, BIT_BTN0);
    } else if (strstr(body, "btn1=clicked")) {
        FLIP_BIT(dataIn, BIT_BTN1);
    } else if (strstr(body, "btn2=clicked")) {
        FLIP_BIT(dataIn, BIT_BTN2);
    } else if (strstr(body, "btn3=clicked")) {
        FLIP_BIT(dataIn, BIT_BTN3);
    } else if (strstr(body, "power0=clicked")) {
        bhmMessage("I", "BIT_SW_LED", "Power Switch pushed - terminating simulation.");
        bhmFinish();
    }
    if(dataInLast != dataIn) {
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX,"Switch Inputs Changed 0x%x -> 0x%x", dataInLast, dataIn);
        }

        if(PSE_DIAG_MEDIUM) showState();

        writeOutput(dataIn);
    }

}

//////////////////////////////// Callback stubs ////////////////////////////////

// update the output signals (LEDs)
PPM_NET_CB(ledCB) {

    Uns32 dataOutLast = dataOut;    // save so that we can determine how the pin changed
    Uns32 index       = PTR_TO_UNS32(userData);

    Uns32 ledBit = 1 << index;   // get bit to update 0->15
    Uns32 data   = (dataOut & ~ledBit) | (value ? ledBit : 0);    // mask in updated bit
    dataOut      = data;

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_LED", "Update %s LEDs 0x%04x->0x%04x",
                                ledInfo[index], dataOutLast, dataOut);

    if(PSE_DIAG_MEDIUM) showState();

}

PPM_NET_CB(resetCB) {
    // clear down variables
    dataIn     = 0;
    dataInLast = 0;
    dataOut    = 0;
}

#define BUFSIZE 128000
static char space[BUFSIZE];

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    bhmHTTPMethods m = { .get=get, .post=post, .message=space, .length=BUFSIZE, .userData=0 };

    bhmHTTPOpen(&m, "httpvis");

}

PPM_DESTRUCTOR_CB(destructor) {

}


PPM_SAVE_STATE_FN(peripheralSaveState) {

}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {

}


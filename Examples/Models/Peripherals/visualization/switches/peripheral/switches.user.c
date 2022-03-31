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


#include "peripheral/ppm.h"
#include "peripheral/bhm.h"
#include "peripheral/bhmHttp.h"

#include "pse.igen.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

static void redraw (bhmHTTPChannel ch) {

    Uns32 sw = bport_reg_data.sw.value;
    
    bhmHTTPElementOpen(ch, "ovpelement");
    
    bhmHTTPKeyPrintf(ch, "switches", "0x%0x", sw);
    bhmHTTPKeyPrintf(ch, "sw0", "%d", ((sw  & 0x1)?1:0));
    bhmHTTPKeyPrintf(ch, "sw1", "%d", ((sw  & 0x2)?1:0));
    bhmHTTPKeyPrintf(ch, "sw2", "%d", ((sw  & 0x4)?1:0));
    bhmHTTPKeyPrintf(ch, "sw3", "%d", ((sw  & 0x8)?1:0));
    
    bhmHTTPKeyPrintf(ch, "bled0", "%d", ((sw  & 0x1)?1:0));
    bhmHTTPKeyPrintf(ch, "bled1", "%d", ((sw  & 0x2)?1:0));
    bhmHTTPKeyPrintf(ch, "bled2", "%d", ((sw  & 0x4)?1:0));
    bhmHTTPKeyPrintf(ch, "bled3", "%d", ((sw  & 0x8)?1:0));
    
    bhmHTTPKeyPrintf(ch, "swt0", "%d", ((sw  & 0x1)?1:0));
    bhmHTTPKeyPrintf(ch, "swt1", "%d", ((sw  & 0x2)?1:0));
    bhmHTTPKeyPrintf(ch, "swt2", "%d", ((sw  & 0x4)?1:0));
    bhmHTTPKeyPrintf(ch, "swt3", "%d", ((sw  & 0x8)?1:0));
    
    bhmHTTPKeyPrintf(ch, "power0", "");
    
    bhmHTTPElementClose(ch, "ovpelement");
    bhmHTTPSend(ch);
}

static BHM_HTTP_GET_FN(get) {
    redraw (ch);
}

static BHM_HTTP_POST_FN(post) {
    if         (strstr(body, "sw0=clicked") || strstr(body, "bled0=clicked") || strstr(body, "swt0=clicked")) {
        bport_reg_data.sw.bits.SW0 = !bport_reg_data.sw.bits.SW0;

    } else if (strstr(body, "sw1=clicked") || strstr(body, "bled1=clicked") || strstr(body, "swt1=clicked")) {
        bport_reg_data.sw.bits.SW1 = !bport_reg_data.sw.bits.SW1;

    } else if (strstr(body, "sw2=clicked") || strstr(body, "bled2=clicked") || strstr(body, "swt2=clicked")) {
        bport_reg_data.sw.bits.SW2 = !bport_reg_data.sw.bits.SW2;

    } else if (strstr(body, "sw3=clicked") || strstr(body, "bled3=clicked") || strstr(body, "swt3=clicked")) {
        bport_reg_data.sw.bits.SW3 = !bport_reg_data.sw.bits.SW3;
        
    } else if (strstr(body, "power0=clicked")) {
        bhmMessage("I", "SW_LED", "Power Switch pushed - terminating simulation.");
        bhmFinish();
    }
    redraw (ch);
}

PPM_REG_READ_CB(ReadSwitch) {
    if(PSE_DIAG_LOW) bhmMessage("I", "SWITCHES", "Read sw %d", *(Uns32*)user);
    return *(Uns32*)user;
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
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}


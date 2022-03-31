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

#define PREFIX "LCD2x16"

static BHM_HTTP_GET_FN(get) {

    Uns8 *lcd = (Uns8 *)handles.bport;
    Uns8 str[33];
    Uns32 i;
    for (i=0; i<32; i++) {
       if(PSE_DIAG_LOW) bhmMessage("I", PREFIX "_STR", "index %d 0x%0x '%c'", i, lcd[i], lcd[i]);
        str[i] = lcd[i];
    }
    str[32] = 0;
    
    bhmHTTPElementOpen(ch, "ovpelement");
    
    bhmHTTPKeyPrintf(ch, "lcd2x16_0", "%s",  str); 
    
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

#define BUFSIZE 128000
static char space[BUFSIZE];

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    if(PSE_DIAG_LOW) bhmMessage("I", PREFIX , "Starting");

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


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

#define PREFIX "BARS"

static BHM_HTTP_GET_FN(get) {

    Uns32 util = bport_reg_data.util.value;
    
    bhmHTTPElementOpen(ch, "ovpelement");
    
    bhmHTTPKeyPrintf(ch, "bar0perc", "%d",  util);
    bhmHTTPKeyPrintf(ch, "bar0", "%d",  util);
    bhmHTTPKeyPrintf(ch, "bar1", "%d",  util);
    
    bhmHTTPKeyPrintf(ch, "power0", "0");
    
    bhmHTTPElementClose(ch, "ovpelement");
    bhmHTTPSend(ch);
}

static BHM_HTTP_POST_FN(post) {
    if (strstr(body, "power0=clicked")) {
        bhmMessage("I", PREFIX "_SW", "Power Switch pushed - terminating simulation.");
        bhmFinish();
    }
}

PPM_REG_WRITE_CB(WriteUtil) {
    if(PSE_DIAG_LOW) bhmMessage("I", PREFIX "_UTIL", "Write Utilization 0x%0x", data);
    *(Uns32*)user = data;
}

#define BUFSIZE 128000
static char space[BUFSIZE];

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    if(PSE_DIAG_LOW) bhmMessage("I", PREFIX, "Starting");

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


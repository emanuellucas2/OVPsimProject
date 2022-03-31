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
//                          Fri Jan  6 11:38:59 2012
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#define PREFIX "SPI"


//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NBYTE_READ_CB(defaultMemRead) {
    bhmMessage("I", "PPM_DFRD",
        "Default Read   bytes:%u  Offset:0x%x",
        bytes,
        offset
    );
    memset(data, 0, bytes);
}

PPM_NBYTE_WRITE_CB(defaultMemWrite) {
    bhmMessage("I", "PPM_DFWR",
        "Default Write   bytes:%u  Offset:0x%x",
        bytes,
        offset
    );
}

PPM_NET_CB(resetCB) {

    reset_resetNet(1,0);
}

PPM_REG_READ_CB(rdRx) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX, "%s: No Behaviour", __FUNCTION__);
    return *(Uns32*)user;
}

PPM_REG_READ_CB(rdTx) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX, "%s: No Behaviour", __FUNCTION__);
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(wrCsmode) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX, "%s: No Behaviour", __FUNCTION__);
    *(Uns32*)user = (*(Uns32*)user & 0xfffffffc) | (data & 0x3);
}

PPM_REG_WRITE_CB(wrRxMark) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX, "%s: No Behaviour", __FUNCTION__);
    *(Uns32*)user = (*(Uns32*)user & 0xfffffffc) | (data & 0x3);
}

PPM_REG_WRITE_CB(wrSckdiv) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX, "%s: No Behaviour", __FUNCTION__);
    *(Uns32*)user = (*(Uns32*)user & 0xfffff000) | (data & 0xfff);
}

PPM_REG_WRITE_CB(wrSckmode) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX, "%s: No Behaviour", __FUNCTION__);
    *(Uns32*)user = (*(Uns32*)user & 0xfffffffc) | (data & 0x3);
}

PPM_REG_WRITE_CB(wrTx) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX, "%s: No Behaviour", __FUNCTION__);
    *(Uns32*)user = (*(Uns32*)user & 0xffffff00) | (data & 0xff);
}

PPM_REG_WRITE_CB(wrTxMark) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX, "%s: No Behaviour", __FUNCTION__);
    *(Uns32*)user = (*(Uns32*)user & 0xfffffffc) | (data & 0x3);
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    bhmMessage("W", PREFIX, "** This is a register only model and has no behavior **");

}

PPM_DESTRUCTOR_CB(destructor) {

}


PPM_SAVE_STATE_FN(peripheralSaveState) {

}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {

}


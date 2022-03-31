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

////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#define PREFIX "DMAC"

static void checkSize1(Uns32 bytes) {
    if(bytes != 1) {
        bhmMessage("E", "DMAC_WE1", "Access must be 1 byte");
    }
}

static void checkSize4(Uns32 bytes) {
    if(bytes != 4) {
        bhmMessage("E", "DMAC_WE1", "Access must be 4 bytes");
    }
}


PPM_NBYTE_WRITE_CB(TCclearWr) {
    checkSize1(bytes);
    DMACSP_ab8_data.intTCstatus.value = *(Uns8*)data;
}

PPM_NBYTE_WRITE_CB(configChWr) {
    checkSize4(bytes);
    Uns32 ch = PTR_TO_UNS32(userData);
    DMACSP_ab32_data[ch].config.value =  *(Uns32*)data;
}

PPM_NBYTE_WRITE_CB(configWr) {
    checkSize1(bytes);
    DMACSP_ab8_data.config.value = *(Uns8*)data;
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}



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
//                             Version 20110906.3
//                          Tue Oct 18 10:54:11 2011
//
////////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "pse.igen.h"

//////////////////////////////// Callback stubs ////////////////////////////////

Uns64 flags_reg;
Uns32 procId0;
#define PROCID0 0x0c000191

PPM_REG_READ_CB(read100Hz) {

    // NOTE: Flt64 result must be *rounded* when converted to Uns64, not
    // *truncated* (the C default)
    Uns64 result = round(bhmGetCurrentTime()/1000);

    // return least-significant 32 bits
    return (Uns32)result;
}

PPM_REG_READ_CB(read24MHz) {

    // NOTE: Flt64 result must be *rounded* when converted to Uns64, not
    // *truncated* (the C default)
    Uns64 result = round(bhmGetCurrentTime()*24);

    // return least-significant 32 bits
    return (Uns32)result;
}

PPM_REG_READ_CB(readId) {
    // YOUR CODE HERE (readId)
    if (diagnosticLevel > 0) bhmMessage("I", "VexpressSysRegs", "ReadID");
    return 0x1190f500;

}

PPM_REG_READ_CB(readMci) {
    if (diagnosticLevel > 0) bhmMessage("I", "VexpressSysRegs", "ReadMci");
    //return 0x1;
    return (ppmReadNet(handles.cardin) & 0x01) | ((ppmReadNet(handles.wprot) & 0x01)<<1);
}

PPM_REG_READ_CB(readProcId0) {
    // YOUR CODE HERE (readProcId0)
    if (diagnosticLevel > 0) bhmMessage("I", "VexpressSysRegs", "ReadProcId0=0x%08x", procId0);
    return procId0;
}

PPM_REG_READ_CB(readProcId1) {
    // YOUR CODE HERE (readProcId1)
    if (diagnosticLevel > 0) bhmMessage("I", "VexpressSysRegs", "ReadProcId1");
    return 0;
}

PPM_REG_READ_CB(readSw) {
    // YOUR CODE HERE (readSw)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readFlags) {
    if (diagnosticLevel > 1) bhmMessage("I", "VexpressSysRegs", "ReadFlags =%x",(Uns32)flags_reg);
    return (Uns32)flags_reg;
}

PPM_REG_READ_CB(readMisc) {
    // YOUR CODE HERE (readSw)
    return 0x00002000;
    //return 0x00000000;
}

// Always return start (bit 31) = 0
PPM_REG_READ_CB(readCfgCtrl) {

    Uns32 ret    = 0;

    if (bytes == 4) {
        ret = *(Uns32 *)addr;
    }

    return ret & ~(1 << 31);

}

// Always return complete (bit 0) = 1
PPM_REG_READ_CB(readCfgStat) {
    return 0x00000001;
}

PPM_REG_WRITE_CB(writeLed) {
    // YOUR CODE HERE (writeLed)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeFlags) {
    flags_reg = (Uns32)data;
    if (diagnosticLevel > 1) bhmMessage("I", "VexpressSysRegs", "WriteFlags d=%x",(Uns32)flags_reg);

}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)

    flags_reg = 0;
    if(!bhmUns32ParamValue("SYS_PROCID0", &procId0)) {
        procId0 = PROCID0;
    }
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


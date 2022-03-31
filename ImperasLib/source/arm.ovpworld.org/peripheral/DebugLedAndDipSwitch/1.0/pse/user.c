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
//                                                                            //
//                W R I T T E N   B Y   I M P E R A S   I G E N               //
//                                                                            //
//                          Thu Jul 30 14:20:29 2009                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#define PREFIX "DebugLedAndDipSwitch"

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(writeAlpha) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Write Alpha Numeric Display 0x%x"
                                " 1: dp %s digit 0x%x"
                                " 2: dp %s digit 0x%x",
                                data,
                                data & 0x40000000 ? "on":"off", (data >> 16) & 0x7fff,
                                data & 0x40000000 ? "on":"off",  data        & 0x7fff);
    }
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeLED) {
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Write LED Lights %s %s %s %s",
                data & 0x08 ? "on" : "off",
                data & 0x04 ? "on" : "off",
                data & 0x02 ? "on" : "off",
                data & 0x01 ? "on" : "off");
    }
    *(Uns32*)user = data;
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


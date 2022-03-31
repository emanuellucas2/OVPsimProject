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

#define PREFIX "TESTSTATUS"

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_READ_CB(readStatus) {
    if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Read");
    return 0;
}

PPM_WRITE_CB(writeStatus) {
    if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Write value 0x%08x", data);

    Uns32 offset = addr - handles.bport1;

    if(offset == 0) {
        Uns32 status =  data        & 0xffff;
        Uns32 code   = (data >> 16) & 0xffff;
        if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Status 0x%04x Code 0x%04x", status, code);

        static Bool reportedOnce = False;
        if(!reportedOnce && ((status==0x5555) || (status==0x3333))) {
            reportedOnce = True;
            bhmMessage("I", PREFIX, "Test Status (%s)", code ? "FAIL" : "PASS");
        }
    } else {
        if(PSE_DIAG_LOW) bhmMessage("E", PREFIX, "Abort on write at offset address 0x%08x", offset);
        ppmWriteAbort();
    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

}

PPM_DESTRUCTOR_CB(destructor) {

}


PPM_SAVE_STATE_FN(peripheralSaveState) {

}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {

}


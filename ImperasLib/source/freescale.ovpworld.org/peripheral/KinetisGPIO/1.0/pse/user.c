/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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

#include "pse.igen.h"

#define PREFIX "GPIO"

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NET_CB(inputCB) {
    // YOUR CODE HERE (inputCB)
    
    bport1_ab_data.PDIR.value = ppmReadNet(handles.Input) & ~bport1_ab_data.PDDR.value;
    
}

PPM_NET_CB(resetCB) {
    // YOUR CODE HERE (resetCB)
    reset_Reset(1,0);
}


void update_output()
{
    Uns32 new_value = bport1_ab_data.PDOR.value & bport1_ab_data.PDDR.value;
    if (new_value != ppmReadNet(handles.Output)) {
        ppmWriteNet(handles.Output,new_value);
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "Write output net to 0x%x",new_value);
        }
    }
    
}


PPM_REG_WRITE_CB(writeCOR) {
    // YOUR CODE HERE (writeCOR)
    *(Uns32*)user = data;
    bport1_ab_data.PDOR.value &= ~data;
    update_output();
}

PPM_REG_WRITE_CB(writeDDR) {
    // YOUR CODE HERE (writeDDR)
    *(Uns32*)user = data;
    bport1_ab_data.PDIR.value = ppmReadNet(handles.Input) & ~data;
    ppmWriteNet(handles.OutputMask,data);
    update_output();
}

PPM_REG_WRITE_CB(writeDOR) {
    // YOUR CODE HERE (writeDOR)
    *(Uns32*)user = data;
    bport1_ab_data.PDOR.value = data;
    update_output();
}

PPM_REG_WRITE_CB(writeSOR) {
    // YOUR CODE HERE (writeSOR)
    *(Uns32*)user = data;
    bport1_ab_data.PDOR.value |= data;
    update_output();
}

PPM_REG_WRITE_CB(writeTOR) {
    // YOUR CODE HERE (writeTOR)
    *(Uns32*)user = data;
    bport1_ab_data.PDOR.value ^= data;
    update_output();
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)
}



// Save / restore callbacks

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


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

#include "pse.igen.h"

#define PREFIX "ANALOG"

// Word offsets fpr set/clear/toggle registers
// (See section 1.1.5.2 Register Macro Usage in i.MX6 Reference Manual)
// TODO: Currently updates register values only - must be enhanced if model must
//       respond to register value changes
#define SET_OFFSET     1
#define CLEAR_OFFSET   2
#define TOGGLE_OFFSET  3

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_READ_CB(regNoDefinitionRead) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Read Register Defined at offset 0x%04x", offset);
    return 0;
}

PPM_WRITE_CB(regNoDefinitionWrite) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Write Register Defined at offset 0x%04x", offset);
}

PPM_REG_READ_CB(ReadZero) {
    return 0;
}

// Clear bits in target register
PPM_REG_WRITE_CB(ClrBits) {
    *((Uns32*)user - CLEAR_OFFSET) &= ~data;
}

// Set bits in target register
PPM_REG_WRITE_CB(SetBits) {
    *((Uns32*)user - SET_OFFSET) |= data;
}

// Toggle bits in target register
PPM_REG_WRITE_CB(TogBits) {
    *((Uns32*)user - TOGGLE_OFFSET) ^= data;
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}


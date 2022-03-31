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

#include <string.h>

#include "pse.igen.h"

#define PREFIX "SD/SDIO"

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

//
// The 32-bit registers may in fact be accessed as bytes, shorts or words
//
#define BYTE3MASK 0xff000000
#define BYTE2MASK 0x00ff0000
#define BYTE1MASK 0x0000ff00
#define BYTE0MASK 0x000000ff
#define WORD1MASK 0xffff0000
#define WORD0MASK 0x0000ffff
#define BYTE3SHIFT 24
#define BYTE2SHIFT 16
#define BYTE1SHIFT  8
#define BYTE0SHIFT  0
#define WORD1SHIFT 16
#define WORD0SHIFT  0

void doAccess(const char *name, Uns32* reg, Uns32 byteSelect, Uns32 bytes, Uns32 data, Uns32 regMask, Uns32 updateMask) {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "%s: %d byte access offset %d", name, bytes, byteSelect);
    switch(bytes) {
    case 4:
        // 32-bit access
        *reg = (*reg & regMask) | (data & updateMask);
        break;
    case 2:
        // 16bit access
        if(byteSelect == 2) {
            // mask upper word
            *reg = (*reg & (regMask | WORD1MASK)) | ((data<<WORD1SHIFT) & (updateMask & WORD1MASK));
        } else if(byteSelect == 0) {
            // mask lower word
            *reg = (*reg & (regMask | WORD0MASK)) | ((data<<WORD0SHIFT) & (updateMask & WORD0MASK));
        } else {
            bhmMessage("W", PREFIX "_REG", "Access size %d but Address bits 1:0 %d", bytes, byteSelect);
        }
        break;
    case 1:
        // byte access
        if(byteSelect == 3) {
            // mask byte 3
            *reg = (*reg & (regMask | BYTE3MASK)) | ((data<<BYTE3SHIFT) & (updateMask & BYTE3MASK));
        } else if(byteSelect == 2) {
            // mask byte 2
            *reg = (*reg & (regMask | BYTE2MASK)) | ((data<<BYTE2SHIFT) & (updateMask & BYTE2MASK));
        } else if(byteSelect == 1) {
            // mask byte 1
            *reg = (*reg & (regMask | BYTE1MASK)) | ((data<<BYTE1SHIFT) & (updateMask & BYTE1MASK));
        } else if(byteSelect == 0) {
            // mask byte 0
            *reg = (*reg & (regMask | BYTE0MASK)) | ((data<<BYTE0SHIFT) & (updateMask & BYTE0MASK));
        } else {
            bhmMessage("W", PREFIX "_REG", "Access size %d but Address bits 1:0 %d", bytes, byteSelect);
        }
        break;
    default:
        bhmMessage("W", PREFIX "_REG", "Access size %d, not supported", bytes);
        break;
    }
}

PPM_REG_WRITE_CB(wrClkCtrl) {

    doAccess("wrClkCtrl", (Uns32*)user, (PTR_TO_UNS32(addr)) & 3, bytes, data, 0xf8f000f8, 0x70fff07);

    // If reset - report complete
    if(bport1_ab_data.Clock_Timeout_control_Software_reset.bits.SWRST_ALL) {
        if (PSE_DIAG_LOW)
            bhmMessage("I", PREFIX "_CLKCTRL", "Software reset");
        // clear to indicate complete
        bport1_ab_data.Clock_Timeout_control_Software_reset.bits.SWRST_ALL = 0;
    }

    // if Internal Clock is enabled - report stable
    bport1_ab_data.Clock_Timeout_control_Software_reset.bits.ICLKST = bport1_ab_data.Clock_Timeout_control_Software_reset.bits.ICLKEN;
    if (bport1_ab_data.Clock_Timeout_control_Software_reset.bits.ICLKST && PSE_DIAG_LOW)
        bhmMessage("I", PREFIX "_CLKCTRL", "Internal Clock Enabled, Report Stable");
}

PPM_REG_WRITE_CB(wrDebugSel) {
    if(PSE_DIAG_LOW)
        bhmMessage("W", PREFIX "_DBGSEL", "No Action");
}

PPM_REG_WRITE_CB(wrPwrCtrl) {
    doAccess("wrPwrCtrl", (Uns32*)user, (PTR_TO_UNS32(addr)) & 3, bytes, data, 0xf8f0f010, 0x70f0fef);

    // Report LED state
    if (PSE_DIAG_LOW)
        bhmMessage("I", PREFIX "_LED", "%s",
                bport1_ab_data.Host_Power_Block_Gap_Wakeup_control.bits.LED ? "on" : "off");
}

PPM_CONSTRUCTOR_CB(constructor) {
    if(PSE_DIAG_LOW)
        bhmMessage("W", PREFIX, "This model implements only the registers, LED indication and Internal Clock. There is no other behavior.");

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


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

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#define PREFIX "GPIO"

// GPIO pin values
Uns32 dataPinIn;         // current input
Uns32 dataPinInLast;     // previous before change
Uns32 dataPinOut;        // current output

//
// Show current state of GPIO
//
void showState() {
    Uns32 i;
    char  gpioString[18];
    for (i=0;i<16;i++) {
        gpioString[15-i] = (char)(dataPinIn & (1<<i)) ? 'O' : '-';
    }
    // terminate
    gpioString[16]=0;
    bhmMessage("I", PREFIX "_UGPIO", "15: %s :0", gpioString);
}

static void writeInterrupt(Uns32 intState) {

    static Uns32 intStateLast = 0;
    if(intState != intStateLast) {
        intStateLast = intState;
        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX"_INT","Write Interrupt %d", intState);
        }

        // update interrupts
        Uns32 i;
        for (i=0;i<16;i++) {
            ppmNetHandle intHandle=(ppmNetHandle)((&handles.intOut0+(i*sizeof(ppmNetHandle))));
            ppmNetValue current = ppmReadNet(intHandle);
            if((intState & (1<<i)) != current) {
                ppmWriteNet(intHandle, ~current & 1);
            }
        }
    }
}

static void updateInterrupts() {

    // work out if any are satisfied
    bport1_REG_data.RISE_IP.value = dataPinIn & ~dataPinInLast;
    bport1_REG_data.FALL_IP.value = dataPinIn & ~dataPinInLast;
    bport1_REG_data.LOW_IP.value  = ~dataPinIn;
    bport1_REG_data.HIGH_IP.value = dataPinIn;

    Uns32 intStatus = 0;

    intStatus |= bport1_REG_data.RISE_IE.value & bport1_REG_data.RISE_IP.value;
    intStatus |= bport1_REG_data.FALL_IE.value & bport1_REG_data.FALL_IP.value;
    intStatus |= bport1_REG_data.LOW_IE.value  & bport1_REG_data.RISE_IP.value;
    intStatus |= bport1_REG_data.HIGH_IE.value & bport1_REG_data.RISE_IP.value;

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_US", "Update Interrupt 0x%0x", intStatus);

    writeInterrupt(intStatus);
}

// update the output
static void updatePins () {

    // dataPin bitwise set from DATA if output enabled
    dataPinOut = (bport1_REG_data.PORT.value & bport1_REG_data.OUTPUT_EN.value);
    dataPinIn  = (dataPinIn & ~bport1_REG_data.OUTPUT_EN.value) | dataPinOut;

    Uns32 i;
    ppmNetHandle *baseHandle = &(handles.gpios0);
    for (i=0;i<16;i++) {
        Uns32 output = bport1_REG_data.OUTPUT_EN.value & (1<<i);
        if (output) {
            ppmNetHandle *gpioHandle = (baseHandle + i);
            Uns32 current = (Uns32)ppmReadNet(*gpioHandle);
            Uns32 new     = (dataPinOut >> i) & 1;
            if( new != current) {
                ppmWriteNet(*gpioHandle, new);  // change GPIO Net
            }
        }
    }

    // update the pin register
    bport1_REG_data.VALUE.value = dataPinIn;

    if(PSE_DIAG_MEDIUM) showState();

    updateInterrupts();
}

//////////////////////////////// Callback stubs ////////////////////////////////

// update the input GPIO
PPM_NET_CB(gpioInCB) {

    // update bits set as input (switches)
    Uns32 index = PTR_TO_UNS32(userData);
    // input is from pin or is the data output register if direction output and output enabled
    Uns32 dirm = bport1_REG_data.OUTPUT_EN.value;

    dataPinInLast = dataPinIn;    // save so that we can determine how the pin changed
    dataPinIn     = (value & ~dirm) | dataPinOut;

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_GPIO_IN", "Update input %u (GPIO Out 0x%04x dirm 0x%04x) GPIO In 0x%04x ",
                                            index, dataPinOut, dirm, dataPinIn);

    // update the pin register
    bport1_REG_data.VALUE.value = dataPinIn;

    if(PSE_DIAG_MEDIUM) showState();

    updateInterrupts();
}



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

PPM_REG_WRITE_CB(wrInputEn) {

    *(Uns32*)user = data;

    updatePins();
}

PPM_REG_WRITE_CB(wrOutputEn) {

    *(Uns32*)user = data;

    updatePins();
}

PPM_REG_WRITE_CB(wrPort) {

    *(Uns32*)user = data;

    updatePins();
}

PPM_REG_WRITE_CB(wrRIE) {

    *(Uns32*)user = data;

    updateInterrupts();
}

PPM_REG_WRITE_CB(wrFIE) {

    *(Uns32*)user = data;

    updateInterrupts();
}

PPM_REG_WRITE_CB(wrHIE) {

    *(Uns32*)user = data;

    updateInterrupts();
}

PPM_REG_WRITE_CB(wrLIE) {

    *(Uns32*)user = data;

    updateInterrupts();
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


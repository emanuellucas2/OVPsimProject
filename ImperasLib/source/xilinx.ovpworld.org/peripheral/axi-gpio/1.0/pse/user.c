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

/*************************************************************
 * Byte Swapping Function
 * PSE interface is always host (little) endian
 *************************************************************/

Bool byteSwap = False;

//
// convert a word for endian
//
static inline Uns32 BSWAP_UNS32(Uns32 p)
{
    return SWAP_4_BYTE_COND(p, byteSwap);
}


#define PREFIX "AXI_GPIO"

Bool dualChannel;

#define GPIO_DATA  *(Uns32 *)(handles.sp1 + SP1_REG_GPIO_DATA_OFFSET)
#define GPIO2_DATA *(Uns32 *)(handles.sp1 + SP1_REG_GPIO2_DATA_OFFSET)

//#define GPIO_DATA  sp1_reg_data.gpio_data.value
//#define GPIO2_DATA sp1_reg_data.gpio2_data.value

//////////////////////////////// Callback stubs ////////////////////////////////

// indicate the data register is being updated from the GPIO input (not processor write)
PPM_NET_CB(gpioInput) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_NET", "GPIO Change (0x%x)", (Uns32)value);
    }
    // only modify input bits (tri = 1)
    GPIO_DATA = (GPIO_DATA & ~sp1_reg_data.gpio_tri.value)
                   | (value & sp1_reg_data.gpio_tri.value);
}

PPM_NET_CB(gpio2Input) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_NET", "GPIO2 Change (0x%x)", (Uns32)value);
    }
    // only modify input bits (tri = 1)
    GPIO2_DATA = (GPIO2_DATA & ~sp1_reg_data.gpio2_tri.value)
                     | (value & sp1_reg_data.gpio2_tri.value);
}

PPM_WRITE_CB(writeData) {
    Uns32 gpioD = data & ~sp1_reg_data.gpio_tri.value;
    Uns32 gpioI = ppmReadNet(handles.gpio_out) & sp1_reg_data.gpio_tri.value;
    Uns32 gpio  = gpioD | gpioI;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Write DATA (0x%x/0x%x/0x%x/0x%x)",
                data, gpioD, gpioI, gpio);
    }
    ppmWriteNet(handles.gpio_out, gpio);
}

PPM_REG_WRITE_CB(writeTri) {
    // TODO: what happens when GPIO TRI changes
    *(Uns32*)user = data;
    // modify data register (holds input value)
    GPIO_DATA = GPIO_DATA & sp1_reg_data.gpio_tri.value;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Write TRI (0x%x)", data);
    }
}

PPM_WRITE_CB(writeData2) {
    if(dualChannel) {
        Uns32 gpioD = data & ~sp1_reg_data.gpio2_tri.value;
        Uns32 gpioI = ppmReadNet(handles.gpio2_out) & sp1_reg_data.gpio2_tri.value;
        Uns32 gpio  = gpioD | gpioI;
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_REG", "Write DATA2 (0x%x/0x%x/0x%x/0x%x)",
                    data, gpioD, gpioI, gpio);
        }
        ppmWriteNet(handles.gpio2_out, gpio);
    } else {
        bhmMessage("W", PREFIX "_REG", "Dual Channel not enabled : Ignore write DATA2 (0x%x)", data);
    }
}

PPM_REG_WRITE_CB(writeTri2) {
    if(dualChannel) {
        // TODO: what happens when GPIO TRI changes
        *(Uns32*)user = data;
        // modify data register (holds input value)
        GPIO2_DATA = GPIO2_DATA & sp1_reg_data.gpio2_tri.value;
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_REG", "Write TRI2 (0x%x)", data);
        }
    } else {
        bhmMessage("W", PREFIX "_REG", "Dual Channel not enabled : Ignore write TRI2 (0x%x)", data);
    }
}

PPM_REG_READ_CB(readGier) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Read GIER (%d)", *(Uns32*)user);
    }
    bhmMessage("W", PREFIX "_REG", "GIER Not Implemented");
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readIer) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Read IER (%d)", *(Uns32*)user);
    }
    bhmMessage("W", PREFIX "_REG", "IER Not Implemented");
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readIsr) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Read Data (%d)", *(Uns32*)user);
    }
    bhmMessage("W", PREFIX "_REG", "ISR Not Implemented");
    return *(Uns32*) user;
}

PPM_REG_WRITE_CB(writeGier) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Write GIER (0x%x)", data);
    }
    bhmMessage("W", PREFIX "_REG", "GIER Not Implemented");
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeIer) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Write IER (0x%x)", data);
    }
    bhmMessage("W", PREFIX "_REG", "IER Not Implemented");
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeIsr) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Write ISR (0x%x)", data);
    }
    bhmMessage("W", PREFIX "_REG", "ISR Not Implemented");
    *(Uns32*)user = data;
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    char endianString[8];
    // check for an endian attribute
    Bool setEndian = bhmStringParamValue("endian", endianString, sizeof(endianString));
    if(setEndian && !strcmp(endianString, "big")){
        byteSwap = True;
    }
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Interface Endian %s", byteSwap ? "BIG" : "LITTLE");
    }

    bhmBoolParamValue("dualchannel", &dualChannel);

    // default values
    bhmUns32ParamValue("initgpiotri",   &sp1_reg_data.gpio_tri.value);
    bhmUns32ParamValue("initgpiodata",  &GPIO_DATA);
    bhmUns32ParamValue("initgpio2tri",  &sp1_reg_data.gpio2_tri.value);
    bhmUns32ParamValue("initgpio2data", &GPIO2_DATA);
    Uns32 gpio  = GPIO_DATA  & ~sp1_reg_data.gpio_tri.value;
    Uns32 gpio2 = GPIO2_DATA & ~sp1_reg_data.gpio2_tri.value;
    if(PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX "_REG_INIT", "GPIO 0x%08x (0x%08x) "
                                            "GPIO2 0x%08x (0x%08x)",
                gpio, sp1_reg_data.gpio_tri.value,
                gpio2, sp1_reg_data.gpio2_tri.value);
    }
    ppmWriteNet(handles.gpio_out, gpio);
    ppmWriteNet(handles.gpio2_out, gpio2);
}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


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

#define PREFIX "GPIO"

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


Bool testGeneration = False;    // enable the user view of LEDs and Switches
bhmEventHandle startTest;       // event to start changing switches after software write to register
#define SWITCHDELAY 5000

Int32 channel;                  // serial channel

// ZC706 (4 user LEDs, 4 dip switch, 3 push switch)
// ZC702 (8 user LEDs, 2 dip switch)

#define ZC706_BASE_SWI  4
#define ZC706_WIDTH_SWI 7
#define ZC706_BASE_LED  0
#define ZC706_WIDTH_LED 4

#define ZC702_BASE_SWI  0
#define ZC702_WIDTH_SWI 2
#define ZC702_BASE_LED  2
#define ZC702_WIDTH_LED 8

// Default ZC702
Uns32 ledBase      = ZC702_BASE_LED;
Uns32 ledNumber    = ZC702_WIDTH_LED;
Uns32 ledMask      = ~(((1<<ZC702_WIDTH_LED)-1) << ZC702_BASE_LED);
Uns32 switchBase   = ZC702_BASE_SWI;
Uns32 switchNumber = ZC702_WIDTH_SWI;
Uns32 switchMask   = ~(((1<<ZC702_WIDTH_SWI)-1) << ZC702_BASE_SWI);

// datavalue on GPIO pin
Uns32 dataPinIn[4];
Uns32 dataPinInLast[4];     // previous before change
Uns32 dataPinOut[4];

//
// Update the Data RO registers
//
void updateDataRO(Uns32 bank) {
    switch(bank) {
        case 0:
            *(Uns32*)(handles.bport1 + BPORT1_REG_DATA_0_RO_OFFSET) = dataPinIn[0];
            break;
        case 1:
            *(Uns32*)(handles.bport1 + BPORT1_REG_DATA_1_RO_OFFSET) = dataPinIn[1];
            break;
        case 2:
            *(Uns32*)(handles.bport1 + BPORT1_REG_DATA_2_RO_OFFSET) = dataPinIn[2];
            break;
        case 3:
            *(Uns32*)(handles.bport1 + BPORT1_REG_DATA_3_RO_OFFSET) = dataPinIn[3];
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
}

void swTest(void *user) {

    Uns32 count = 0;
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_USW_TST", "Software Test Thread Starting");

    bhmWaitEvent(startTest);

    while(1) {

        // some test by setting switches
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_USW", "USER SW Test %d (0x%08x)", count, dataPinIn[2]);

        bhmWaitDelay(SWITCHDELAY);

        if (count == 4) {
            dataPinIn[2] &= switchMask;   // clear switch
            dataPinIn[2] |= 1<<(switchBase+0);
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX "_USW_TST", "USER SW SW0 set (0x%08x)", dataPinIn[2]);
        } else if (count == 6){
            dataPinIn[2] &= switchMask;   // clear switch
            dataPinIn[2] |= 1<<(switchBase+1);
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX "_USW_TST", "USER SW SW1 set (0x%08x)", dataPinIn[2]);
        } else if (count == 8){
            dataPinIn[2] &= switchMask;   // clear switch
            dataPinIn[2] |= 1<<(switchBase+2);
            count = 0;
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX "_USW_TST", "USER SW SW2 set (0x%08x)", dataPinIn[2]);
        }
        updateDataRO(2);     // update the read only registers
        count++;
    }
}

//
// Show current state of GPIO connected LEDs and Switches
//
void showState() {
    Uns32 i;
    char  ledString[(4*ledNumber)+1];
    ledString[0] = '\0';
    for (i=ledNumber;i>0;i--) {
        strcat(ledString, dataPinOut[2] & (1<<(ledBase+i-1)) ? " on " : "off ");
    }

    char  swString[(4*switchNumber)+1];
    swString[0] = '\0';
    for (i=switchNumber;i>0;i--) {
        strcat(swString, dataPinIn[2] & (1<<(switchBase+i-1)) ? " on " : "off ");
    }
    bhmMessage("I", PREFIX "_ULED", "USER LEDs %s USER SWs %s", ledString, swString);
}

static void writeInterrupt(Uns32 status, Uns32 mask) {

    Uns32 intState = status & ~mask;
    static Uns32 intStateLast = 0;

    if(intState != intStateLast) {
        intStateLast = intState;
        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX"_INT","Write Interrupt (status 0x%04x / mask 0x%04x)",
                                    status, mask);
        }
        if(intState) {
            // set
            ppmWriteNet(handles.intOut, 1);
        } else {
            // clear
            ppmWriteNet(handles.intOut, 0);
        }
    }
}

static void updateInterrupts(Uns32 bank) {

    Uns32 pinLast    = dataPinInLast[bank];
    Uns32 pinCurrent = dataPinIn[bank];
    Uns32 type, polarity, any, mask;
    (void) any; // Not used, so this is needed to avoid compiler warning
    switch(bank) {
        case 0:
            type     = bport1_REG_data.INT_TYPE_0.value;
            polarity = bport1_REG_data.INT_POLARITY_0.value;
            any      = bport1_REG_data.INT_ANY_0.value;
            mask     = bport1_REG_data.INT_MASK_0.value;
            break;
        case 1:
            type     = bport1_REG_data.INT_TYPE_1.value;
            polarity = bport1_REG_data.INT_POLARITY_1.value;
            any      = bport1_REG_data.INT_ANY_1.value;
            mask     = bport1_REG_data.INT_MASK_1.value;
            break;
        case 2:
            type     = bport1_REG_data.INT_TYPE_2.value;
            polarity = bport1_REG_data.INT_POLARITY_2.value;
            any      = bport1_REG_data.INT_ANY_2.value;
            mask     = bport1_REG_data.INT_MASK_2.value;
            break;
        case 3:
            type     = bport1_REG_data.INT_TYPE_3.value;
            polarity = bport1_REG_data.INT_POLARITY_3.value;
            any      = bport1_REG_data.INT_ANY_3.value;
            mask     = bport1_REG_data.INT_MASK_3.value;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            type     = 0;
            polarity = 0;
            any      = 0;
            mask     = 0;
            break;
    }

    // TODO: This should be cleaned up and optimized

    // generate interrupt, if
    //   type edge (1)
    //      polarity low->high (1)
    //         bit change 0->1
    //      polarity high->low (0)
    //         bit change 1->0
    //   type level (0)
    //      polarity low (0)
    //         bit is 0
    //      polarity high (1)
    //         bit is 1

    Uns32 status = 0;
    Uns32 bit;
    for (bit=0;bit<32;bit++) {
        Uns32 mask = (1<<bit);
        if(type & mask) {
            // edge sensitive
            if(polarity & mask) {
                // low to high
                if((pinCurrent & mask) && !(pinLast & mask)) {
                    status |= mask;
                }
            } else {
                // high->low
                if(!(pinCurrent & mask) && (pinCurrent & mask)) {
                    status |= mask;
                }
            }

        } else {
            // level sensitive
            if(polarity & mask) {
                // high
                if(pinCurrent & mask) {
                    status |= mask;
                }
            } else {
                // low
                if(!(pinCurrent & mask)) {
                    status |= mask;
                }
            }
        }
    }

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_US", "Update Interrupt Status(%d) 0x%0x", bank, status);

    switch(bank) {
        case 0:
            bport1_REG_data.INT_STAT_0.value |= status;
            break;
        case 1:
            bport1_REG_data.INT_STAT_1.value |= status;
            break;
        case 2:
            bport1_REG_data.INT_STAT_2.value |= status;
            break;
        case 3:
            bport1_REG_data.INT_STAT_3.value |= status;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }

    writeInterrupt(status, mask);
}

// update the output
PPM_NET_CB(gpio_in_change) {

    Uns32 bank = PTR_TO_UNS32(userData);

    // update bits set as input (switches)
    // input is from pin or is the data output register if direction output and output enabled
    Uns32 dirm;
    switch(bank) {
        case 0:
            dirm = bport1_REG_data.DIRM_0.value;
            break;
        case 1:
            dirm = bport1_REG_data.DIRM_1.value;
            break;
        case 2:
            dirm = bport1_REG_data.DIRM_2.value;
            break;
        case 3:
            dirm = bport1_REG_data.DIRM_3.value;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            dirm = 0;
            break;
    }

    dataPinInLast[bank] = dataPinIn[bank];    // save so that we can determine how the pin changed
    dataPinIn[bank]     = (value & ~dirm) | dataPinOut[bank];

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_GPIO_IN", "Update bank %d input 0x%x (GPIO Out 0x%08x dirm 0x%08x) GPIO In 0x%x ",
                                            bank, (Uns32)value, dataPinIn[bank], dirm, dataPinIn[bank]);

    updateDataRO(bank);     // update the read only registers

    if(PSE_DIAG_MEDIUM)
        showState();

    updateInterrupts(bank);
}

// update the output
static void updatePins (Uns32 bank) {

    // dataPin bitwise set from DATA if DIRM (output) and OEN (driver enabled)
    switch(bank) {
        case 0:
            dataPinOut[0] = (bport1_REG_data.DATA_0.value & bport1_REG_data.DIRM_0.value & bport1_REG_data.OEN_0.value);
            dataPinIn[0]  = (dataPinIn[0] & ~bport1_REG_data.DIRM_0.value) | dataPinOut[0];
            ppmWriteNet(handles.gpio_bank0_out, dataPinOut[0]);
            break;
        case 1:
            dataPinOut[1] = (bport1_REG_data.DATA_1.value & bport1_REG_data.DIRM_1.value & bport1_REG_data.OEN_1.value);
            dataPinIn[1]  = (dataPinIn[1] & ~bport1_REG_data.DIRM_1.value) | dataPinOut[1];
            ppmWriteNet(handles.gpio_bank1_out, dataPinOut[1]);
            break;
        case 2:
            dataPinOut[2] = (bport1_REG_data.DATA_2.value & bport1_REG_data.DIRM_2.value);
            dataPinIn[2]  = (dataPinIn[2] & ~bport1_REG_data.DIRM_2.value) | dataPinOut[2];
            ppmWriteNet(handles.gpio_bank2_out, dataPinOut[2]);
            ppmWriteNet(handles.gpio_bank2_oen_out, bport1_REG_data.DIRM_2.value & bport1_REG_data.OEN_2.value);
            break;
        case 3:
            dataPinOut[3] = (bport1_REG_data.DATA_3.value & bport1_REG_data.DIRM_3.value);
            dataPinIn[3]  = (dataPinIn[3] & ~bport1_REG_data.DIRM_3.value) | dataPinOut[3];
            ppmWriteNet(handles.gpio_bank3_out, dataPinOut[3]);
            ppmWriteNet(handles.gpio_bank3_oen_out, bport1_REG_data.DIRM_3.value & bport1_REG_data.OEN_3.value);
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }

    updateDataRO(bank);     // update the read only registers

    if(PSE_DIAG_MEDIUM)
        showState();

    if(testGeneration)
        bhmTriggerEvent(startTest);
}

PPM_REG_WRITE_CB(wDATA) {
    Uns32 bank = PTR_TO_UNS32(user);
    switch(bank) {
        case 0:
            bport1_REG_data.DATA_0.value = data;
            break;
        case 1:
            bport1_REG_data.DATA_1.value = data;
            break;
        case 2:
            bport1_REG_data.DATA_2.value = data;
            break;
        case 3:
            bport1_REG_data.DATA_3.value = data;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    updatePins(bank);
}

PPM_REG_WRITE_CB(wDIRM) {
    Uns32 bank = PTR_TO_UNS32(user);
    switch(bank) {
        case 0:
            bport1_REG_data.DIRM_0.value = data;
            break;
        case 1:
            bport1_REG_data.DIRM_1.value = data;
            break;
        case 2:
            bport1_REG_data.DIRM_2.value = data;
            break;
        case 3:
            bport1_REG_data.DIRM_3.value = data;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    updatePins(bank);
}
static Uns16 updateData(Uns16 data, Uns16 mask, Uns16 reg) {

    Uns16 regOut    = 0;
    Uns16 setBits   =  ( data & ~mask);   // provides a 1 in each bit position to be set
    Uns16 clearBits = ~(~data & ~mask);   // provides a 0 in each bit position to be cleared

    regOut = (reg & clearBits) | setBits;

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_UD", "data 0x%04x mask 0x%04x reg 0x%04x out 0x%04x"
                                      " (set/clr 0x%04x/0x%04x)",
                                     data, mask, reg, regOut,
                                     setBits, clearBits);
    }

    return regOut;
}

PPM_REG_WRITE_CB(wMASK) {
    Uns32 bank = PTR_TO_UNS32(user);

    switch(bank) {
        case 0:
            bport1_REG_data.MASK_DATA_0_LSW.value = data;
            bport1_REG_data.DATA_0.bits.LOW = updateData(bport1_REG_data.MASK_DATA_0_LSW.bits.DATA,
                                                         bport1_REG_data.MASK_DATA_0_LSW.bits.MASK,
                                                         bport1_REG_data.DATA_0.bits.LOW);
            break;
        case 1:
            bport1_REG_data.MASK_DATA_0_MSW.value = data;
            bport1_REG_data.DATA_0.bits.HIGH = updateData(bport1_REG_data.MASK_DATA_0_MSW.bits.DATA,
                                                          bport1_REG_data.MASK_DATA_0_MSW.bits.MASK,
                                                          bport1_REG_data.DATA_0.bits.HIGH);
            break;
        case 2:
            bport1_REG_data.MASK_DATA_1_LSW.value = data;
            bport1_REG_data.DATA_1.bits.LOW = updateData(bport1_REG_data.MASK_DATA_1_LSW.bits.DATA,
                                                         bport1_REG_data.MASK_DATA_1_LSW.bits.MASK,
                                                         bport1_REG_data.DATA_1.bits.LOW);
            break;
        case 3:
            bport1_REG_data.MASK_DATA_1_MSW.value = data;
            bport1_REG_data.DATA_1.bits.HIGH = updateData(bport1_REG_data.MASK_DATA_1_MSW.bits.DATA,
                                                          bport1_REG_data.MASK_DATA_1_MSW.bits.MASK,
                                                          bport1_REG_data.DATA_1.bits.HIGH);
            break;
        case 4:
            bport1_REG_data.MASK_DATA_2_LSW.value = data;
            bport1_REG_data.DATA_2.bits.LOW = updateData(bport1_REG_data.MASK_DATA_2_LSW.bits.DATA,
                                                         bport1_REG_data.MASK_DATA_2_LSW.bits.MASK,
                                                         bport1_REG_data.DATA_2.bits.LOW);
            break;
        case 5:
            bport1_REG_data.MASK_DATA_2_MSW.value = data;
            bport1_REG_data.DATA_2.bits.HIGH = updateData(bport1_REG_data.MASK_DATA_2_MSW.bits.DATA,
                                                          bport1_REG_data.MASK_DATA_2_MSW.bits.MASK,
                                                          bport1_REG_data.DATA_2.bits.HIGH);
            break;
        case 6:
            bport1_REG_data.MASK_DATA_3_LSW.value = data;
            bport1_REG_data.DATA_3.bits.LOW = updateData(bport1_REG_data.MASK_DATA_3_LSW.bits.DATA,
                                                         bport1_REG_data.MASK_DATA_3_LSW.bits.MASK,
                                                         bport1_REG_data.DATA_3.bits.LOW);
            break;
        case 7:
            bport1_REG_data.MASK_DATA_3_MSW.value = data;
            bport1_REG_data.DATA_3.bits.HIGH = updateData(bport1_REG_data.MASK_DATA_3_MSW.bits.DATA,
                                                          bport1_REG_data.MASK_DATA_3_MSW.bits.MASK,
                                                          bport1_REG_data.DATA_3.bits.HIGH);
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    updatePins(bank/2);
}

PPM_REG_WRITE_CB(wOEN) {
    Uns32 bank = PTR_TO_UNS32(user);
    switch(bank) {
        case 0:
            bport1_REG_data.OEN_0.value = data;
            break;
        case 1:
            bport1_REG_data.OEN_1.value = data;
            break;
        case 2:
            bport1_REG_data.OEN_2.value = data;
            break;
        case 3:
            bport1_REG_data.OEN_3.value = data;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    updatePins(bank);
}

PPM_REG_WRITE_CB(wINT_ANY) {
    if(PSE_DIAG_HIGH)
        bhmMessage("W", PREFIX "_NB", "No interrupt generation behaviour implemented");
    Uns32 bank = PTR_TO_UNS32(user);
    switch(bank) {
        case 0:
            bport1_REG_data.INT_ANY_0.value = data;
            break;
        case 1:
            bport1_REG_data.INT_ANY_1.value = data;
            break;
        case 2:
            bport1_REG_data.INT_ANY_2.value = data;
            break;
        case 3:
            bport1_REG_data.INT_ANY_3.value = data;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }

    updateInterrupts(bank);
}

PPM_REG_WRITE_CB(wINT_DIS) {
    if(PSE_DIAG_HIGH)
        bhmMessage("W", PREFIX "_NB", "No interrupt generation behaviour implemented");
    Uns32 bank = PTR_TO_UNS32(user);
    switch(bank) {
        case 0:
            bport1_REG_data.INT_DIS_0.value = data;
            bport1_REG_data.INT_MASK_0.value |= data;  // set mask bit
            break;
        case 1:
            bport1_REG_data.INT_DIS_1.value = data;
            bport1_REG_data.INT_MASK_1.value |= data;  // set mask bit
            break;
        case 2:
            bport1_REG_data.INT_DIS_2.value = data;
            bport1_REG_data.INT_MASK_2.value |= data;  // set mask bit
            break;
        case 3:
            bport1_REG_data.INT_DIS_3.value = data;
            bport1_REG_data.INT_MASK_3.value |= data;  // set mask bit
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
}

PPM_REG_WRITE_CB(wINT_EN) {
    if(PSE_DIAG_HIGH)
        bhmMessage("W", PREFIX "_NB", "No interrupt generation behaviour implemented");
    Uns32 bank = PTR_TO_UNS32(user);
    switch(bank) {
        case 0:
            bport1_REG_data.INT_EN_0.value = data;
            bport1_REG_data.INT_MASK_0.value &= ~data;  // clear mask bit
            break;
        case 1:
            bport1_REG_data.INT_EN_1.value = data;
            bport1_REG_data.INT_MASK_1.value &= ~data;  // clear mask bit
            break;
        case 2:
            bport1_REG_data.INT_EN_2.value = data;
            bport1_REG_data.INT_MASK_2.value &= ~data;  // clear mask bit
            break;
        case 3:
            bport1_REG_data.INT_EN_3.value = data;
            bport1_REG_data.INT_MASK_3.value &= ~data;  // clear mask bit
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
}

PPM_REG_WRITE_CB(wINT_POLARITY) {
    if(PSE_DIAG_HIGH)
        bhmMessage("W", PREFIX "_NB", "No interrupt generation behaviour implemented");
    Uns32 bank = PTR_TO_UNS32(user);
    switch(bank) {
        case 0:
            bport1_REG_data.INT_POLARITY_0.value = data;
            break;
        case 1:
            bport1_REG_data.INT_POLARITY_1.value = data;
            break;
        case 2:
            bport1_REG_data.INT_POLARITY_2.value = data;
            break;
        case 3:
            bport1_REG_data.INT_POLARITY_3.value = data;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }

    updateInterrupts(bank);
}

PPM_REG_WRITE_CB(wINT_STAT) {
    if(PSE_DIAG_HIGH)
        bhmMessage("W", PREFIX "_NB", "No interrupt generation behaviour implemented");
    Uns32 bank = PTR_TO_UNS32(user);
    switch(bank) {
        case 0:
            bport1_REG_data.INT_STAT_0.value &= ~data;
            break;
        case 1:
            bport1_REG_data.INT_STAT_1.value &= ~data;
            break;
        case 2:
            bport1_REG_data.INT_STAT_2.value &= ~data;
            break;
        case 3:
            bport1_REG_data.INT_STAT_3.value &= ~data;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
}

PPM_REG_WRITE_CB(wINT_TYPE) {
    if(PSE_DIAG_HIGH)
        bhmMessage("W", PREFIX "_NB", "No interrupt generation behaviour implemented");
    Uns32 bank = PTR_TO_UNS32(user);
    switch(bank) {
        case 0:
            bport1_REG_data.INT_TYPE_0.value = data;
            break;
        case 1:
            bport1_REG_data.INT_TYPE_1.value = data;
            break;
        case 2:
            bport1_REG_data.INT_TYPE_2.value = data;
            break;
        case 3:
            bport1_REG_data.INT_TYPE_3.value = data;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }

    updateInterrupts(bank);
}

PPM_REG_READ_CB(rDATA) {
    Uns32 bank = PTR_TO_UNS32(user);
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_NB", "DATA_%d", bank);
    Uns32 data = 0;
    switch(bank) {
        case 0:
            data = bport1_REG_data.DATA_0.value;
            break;
        case 1:
            data = bport1_REG_data.DATA_1.value;
            break;
        case 2:
            data = bport1_REG_data.DATA_2.value;
            break;
        case 3:
            data = bport1_REG_data.DATA_3.value;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    return data;
}

#if 0
// Implemented as memory for zero overhead
PPM_REG_READ_CB(rDATARO) {
    Uns32 bank = PTR_TO_UNS32(user);
    Uns32 data = 0;
    switch(bank) {
        case 0:
            data = dataPinIn[0];
            break;
        case 1:
            data = dataPinIn[1];
            break;
        case 2:
            data = dataPinIn[2];
            break;
        case 3:
            data = dataPinIn[3];
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_DRO", "DATA_RO%d 0x%08x", bank, data);
    return data;
}
#endif

PPM_REG_READ_CB(rDIRM) {
    Uns32 bank = PTR_TO_UNS32(user);
    Uns32 data = 0;
    switch(bank) {
        case 0:
            data = bport1_REG_data.DIRM_0.value;
            break;
        case 1:
            data = bport1_REG_data.DIRM_1.value;
            break;
        case 2:
            data = bport1_REG_data.DIRM_2.value;
            break;
        case 3:
            data = bport1_REG_data.DIRM_3.value;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    updatePins(bank);
    return data;
}

PPM_REG_READ_CB(rMASK) {
    Uns32 bank = PTR_TO_UNS32(user);
    Uns32 data = 0;
    switch(bank) {
        case 0:
            data = bport1_REG_data.DATA_0.bits.LOW;
            break;
        case 1:
            data = bport1_REG_data.DATA_0.bits.HIGH;
            break;
        case 2:
            data = bport1_REG_data.DATA_1.bits.LOW;
            break;
        case 3:
            data = bport1_REG_data.DATA_1.bits.HIGH;
            break;
        case 4:
            data = bport1_REG_data.DATA_2.bits.LOW;
            break;
        case 5:
            data = bport1_REG_data.DATA_2.bits.HIGH;
            break;
        case 6:
            data = bport1_REG_data.DATA_3.bits.LOW;
            break;
        case 7:
            data = bport1_REG_data.DATA_3.bits.HIGH;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    data = data & 0xff; // only bottom 16 bits can be read
    return data;
}

PPM_REG_READ_CB(rOEN) {
    Uns32 bank = PTR_TO_UNS32(user);
    Uns32 data = 0;
    switch(bank) {
        case 0:
            data = bport1_REG_data.OEN_0.value;
            break;
        case 1:
            data = bport1_REG_data.OEN_1.value;
            break;
        case 2:
            data = bport1_REG_data.OEN_2.value;
            break;
        case 3:
            data = bport1_REG_data.OEN_3.value;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    updatePins(bank);
    return data;
}

PPM_REG_READ_CB(rINT_ANY) {
    Uns32 bank = PTR_TO_UNS32(user);
    Uns32 data = 0;
    switch(bank) {
        case 0:
            data = bport1_REG_data.INT_ANY_0.value;
            break;
        case 1:
            data = bport1_REG_data.INT_ANY_1.value;
            break;
        case 2:
            data = bport1_REG_data.INT_ANY_2.value;
            break;
        case 3:
            data = bport1_REG_data.INT_ANY_3.value;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    return data;
}

PPM_REG_READ_CB(rINT_MASK) {
    Uns32 bank = PTR_TO_UNS32(user);
    Uns32 data = 0;
    switch(bank) {
        case 0:
            data = bport1_REG_data.INT_MASK_0.value;
            break;
        case 1:
            data = bport1_REG_data.INT_MASK_1.value;
            break;
        case 2:
            data = bport1_REG_data.INT_MASK_2.value;
            break;
        case 3:
            data = bport1_REG_data.INT_MASK_3.value;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    return data;
}

PPM_REG_READ_CB(rINT_POLARITY) {
    Uns32 bank = PTR_TO_UNS32(user);
    Uns32 data = 0;
    switch(bank) {
        case 0:
            data = bport1_REG_data.INT_POLARITY_0.value;
            break;
        case 1:
            data = bport1_REG_data.INT_POLARITY_1.value;
            break;
        case 2:
            data = bport1_REG_data.INT_POLARITY_2.value;
            break;
        case 3:
            data = bport1_REG_data.INT_POLARITY_3.value;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    return data;
}

PPM_REG_READ_CB(rINT_TYPE) {
    Uns32 bank = PTR_TO_UNS32(user);
    Uns32 data = 0;
    switch(bank) {
        case 0:
            data = bport1_REG_data.INT_TYPE_0.value;
            break;
        case 1:
            data = bport1_REG_data.INT_TYPE_1.value;
            break;
        case 2:
            data = bport1_REG_data.INT_TYPE_2.value;
            break;
        case 3:
            data = bport1_REG_data.INT_TYPE_3.value;
            break;
        default:
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_UB", "Bank %d not recognized", bank);
            break;
    }
    return data;
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    bhmBoolParamValue("swtest", &testGeneration);

    // The configuration is used only for test and debug
    configT config;
    if (bhmEnumParamValue("config", &config)) {
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX"_CFG", "Config '%s'",
                config == CONFIG_ZC706 ? "zc706" :
                config == CONFIG_ZC702 ? "zc702"
                                       : "???");
        if (config == CONFIG_ZC702) {
            // default initialisation
        } else if (config == CONFIG_ZC706) {
            ledBase      = ZC706_BASE_LED;
            ledNumber    = ZC706_WIDTH_LED;
            ledMask      = ~(((1<<ZC706_WIDTH_LED)-1) << ZC706_BASE_LED);
            switchBase   = ZC706_BASE_SWI;
            switchNumber = ZC706_WIDTH_SWI;
            switchMask   = ~(((1<<ZC706_WIDTH_SWI)-1) << ZC706_BASE_SWI);
        } else {
            bhmMessage("F", PREFIX"_CFG", "Invalid config %d", config);
        }
    }
    bhmMessage("I", PREFIX"_CFG_TST", "ledBase %d, ledNumber %d, ledMask 0x%08x "
                                      "swBase %d, swNumber %d, swMask 0x%08x",
                                      ledBase, ledNumber, ledMask,
                                      switchBase, switchNumber, switchMask);
    if(testGeneration) {

        startTest = bhmCreateEvent();
        // start periodic thread to stimulate switches
        bhmCreateThread(swTest, 0, "swTestThread", 0);
    } else {
        ppmInstallNetCallback(handles.gpio_bank0_in, gpio_in_change, (void *) 0);
        ppmInstallNetCallback(handles.gpio_bank1_in, gpio_in_change, (void *) 1);
        ppmInstallNetCallback(handles.gpio_bank2_in, gpio_in_change, (void *) 2);
        ppmInstallNetCallback(handles.gpio_bank3_in, gpio_in_change, (void *) 3);
    }

}

PPM_DESTRUCTOR_CB(destructor) {

}


PPM_SAVE_STATE_FN(peripheralSaveState) {

}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {

}


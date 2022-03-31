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
//                          Fri Sep 14 13:40:24 2012
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "pse.igen.h"
#include "stimulus.h"

#define UNUSED __attribute__((unused))

#define PREFIX "ADC"

typedef struct outputPinS {
    const char  *name;
    ppmNetHandle netP;
    Uns32        value;
} outputPin, *outputPinP;

typedef struct inputPinS {
    const char  *name;
    Uns32        value;
} inputPin, *inputPinP;

static Bool DMAEnabled = False;

static outputPin INTAD     = { "INTAD"   , 0, 0 };
static outputPin ADDMARQ   = { "ADDMARQ" , 0, 0 };
static inputPin  ADTRG     = { "ADTRG"   , 0 };
static inputPin  TS0ADT0   = { "TS0ADT0" , 0 };
static inputPin  TS0ADT1   = { "TS0ADT1" , 0 };
static inputPin  TS1ADT0   = { "TS1ADT0" , 0 };
static inputPin  TS1ADT1   = { "TS1ADT1" , 0 };
static inputPin  INTTS0OD  = { "INTTS0OD", 0 };
static inputPin  INTTS0CD  = { "INTTS0CD", 0 };
static inputPin  INTTS1OD  = { "INTTS1OD", 0 };
static inputPin  INTTS1CD  = { "INTTS1CD", 0 };

static double FRdelay = 10.5;

static Uns8 rising(inputPinP pin, Uns32 value) {
    Uns8 cond = 0;
    if (pin->value == 0 && value == 1) {
        cond = 1;
    } else {
        cond = 0;
    }
    return cond;
}

static Uns8 falling(inputPinP pin, Uns32 value) {
    Uns8 cond = 0;
    if (pin->value == 1 && value == 0) {
        cond = 1;
    } else {
        cond = 0;
    }
    return cond;
}
static void updatepin(inputPinP pin, Uns32 value) {
    pin->value = value;
}

//
// Only write when a value change occurs
//
static void doWriteNet(outputPinP pin, Uns32 value) {
    if (value != pin->value) {
        pin->value = value;
        ppmWriteNet(pin->netP, pin->value);
    }
}
static void posPulseNet(outputPinP pin) {
    if(DIAG_HIGH)
        bhmMessage("I", PREFIX"_NO", "Positive Pulse %s", pin->name);
    doWriteNet(pin, 1);
    doWriteNet(pin, 0);
}

static Uns32 PCLK1;

static bhmThreadHandle controllerThreadHandle = 0;
static bhmThreadHandle idleThreadHandle = 0;

static double sample;
static void idleThread(void *user) {
    while (1) {
        bhmWaitDelay(sample);
    }
}

//
// Latch sampled value and generate interrupt
//
bhmEventHandle triggerEvent;
bhmEventHandle adceEvent;

//
// Need to store 10 capture times for buffer/scan period
//
captureInfo cap[10] = { { 0 } };

static void controllerThread(void *user) {
    Int32 ch = 0;
    static int delay = 1;   // conversion time delays

    while (1) {
        //
        // If the A/D is disabled, wait for event causing enable
        //
        if (ADCP0_reg0_data.ADM0.bits.ADCE == 0) {
            if(DIAG_HIGH)
                bhmMessage("I", PREFIX"_EN", "Wait for Enable");
            bhmWaitEvent(adceEvent);
            ch = ADCP0_reg0_data.ADM2.bits.ANI;
        }

        //
        // Now wait for the trigger if we are in trigger mode
        // if we are in A/D mode, we bypass and wait for sample delay
        //
        if (ADCP0_reg0_data.ADM1.bits.TRG) {
            //
            // External or timer trigger mode
            // This is a retriggerable event
            //
            if(DIAG_HIGH)
                bhmMessage("I", PREFIX"_CT", "Wait for Trigger");
            bhmWaitEvent(triggerEvent);
            if(DIAG_HIGH)
                bhmMessage("I", PREFIX"_CT", "Triggered");
        }

        //
        // Detect scan/select mode and (1|4)-buffer operation
        //
        if (ADCP0_reg0_data.ADM0.bits.MS) {
            //
            // Select Mode, select a particular input
            //
            if (ADCP0_reg0_data.ADM0.bits.BS) {
                //
                // 4 buffer mode
                // AI0-AI3 ->  ADCR0-ADCR3
                // AI4-AI7 ->  ADCR4-ADCR7
                // AI8-AI9 ->  ADCR0-ADCR3
                //
                delay =  4;
            } else {
                //
                // 1 Buffer Mode, 1 sample to complete
                //
                delay = 1;
            }
        } else {
            //
            // Scan Mode, iterate across inputs 0 to ch
            //
            delay = (ch+1);
        }

        //
        // Calculate capture info and times
        //
        cap[0].time = bhmGetCurrentTime();
        cap[0].MS   = ADCP0_reg0_data.ADM0.bits.MS;
        cap[0].BS   = ADCP0_reg0_data.ADM0.bits.BS;
        cap[0].ANI  = ADCP0_reg0_data.ADM2.bits.ANI;
        Int32 ci;
        for (ci=0; ci <= cap[0].ANI; ci++) {
            cap[ci+1].time = cap[ci].time - FRdelay;
            cap[ci+1].MS   = cap[ci].MS;
            cap[ci+1].BS   = cap[ci].BS;
            cap[ci+1].ANI  = cap[ci].ANI;
        }


        //
        // Now generate an interrupt
        //
        if (!DMAEnabled) {
            // ADC Generating Interrupt after conversion(s) completed
            if(DIAG_HIGH)
                bhmMessage("I", PREFIX"_CTI", "Complete (delay %f)", (FRdelay * delay));
            bhmWaitDelay(FRdelay * delay);
            posPulseNet(&INTAD);
        } else {
            // DMA Generating Interrupt, Generate DMA Request after each conversion time
            int i;
            for (i=0; i<delay; i++) {
                if(DIAG_HIGH)
                    bhmMessage("I", PREFIX"_CTD", "Complete (delay %f)", (FRdelay));
                bhmWaitDelay(FRdelay);
                posPulseNet(&ADDMARQ);
            }
        }
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NET_CB(P_INTADEN) {
    // if DMA is enabled it will generate interrupt
    if(DIAG_HIGH)
        bhmMessage("I", PREFIX"_DMAEN", "Net Value %d", (Uns32)value);
    if (value) {
        DMAEnabled=True;
    } else {
        DMAEnabled=False;
    }
}

PPM_NET_CB(P_ADTRG) {
    switch (ADCP0_reg0_data.ADM1.bits.EGA) {
    case 0:
        // no action
        break;
    case 1:
        // falling edge
        if (falling(&ADTRG, value)) {
            bhmTriggerEvent(triggerEvent);
        }
        break;
    case 2:
        // rising edge
        if (rising(&ADTRG, value)) {
            bhmTriggerEvent(triggerEvent);
        }
        break;
    case 3:
        // edge
        if (rising(&ADTRG, value) || falling(&ADTRG, value)) {
            bhmTriggerEvent(triggerEvent);
        }
        break;
    default:
        break;
    }

    updatepin(&ADTRG, value);
}

PPM_NET_CB(P_TS0ADT0) {
    if (ADCP1_reg0_data.ADTRSEL.bits.TSEL == 1) {
        if (rising(&TS0ADT0, value)) {
            bhmTriggerEvent(triggerEvent);
        }
    }
    updatepin(&TS0ADT0, value);
}

PPM_NET_CB(P_TS0ADT1) {
    if (ADCP1_reg0_data.ADTRSEL.bits.TSEL == 2) {
        if (rising(&TS0ADT1, value)) {
            bhmTriggerEvent(triggerEvent);
        }
    }
    updatepin(&TS0ADT1, value);
}

PPM_NET_CB(P_TS1ADT0) {
    if (ADCP1_reg0_data.ADTRSEL.bits.TSEL == 3) {
        if (rising(&TS1ADT0, value)) {
            bhmTriggerEvent(triggerEvent);
        }
    }
    updatepin(&TS1ADT0, value);
}

PPM_NET_CB(P_TS1ADT1) {
    if (ADCP1_reg0_data.ADTRSEL.bits.TSEL == 4) {
        if (rising(&TS1ADT1, value)) {
            bhmTriggerEvent(triggerEvent);
        }
    }
    updatepin(&TS1ADT1, value);
}

PPM_NET_CB(P_INTTS0OD) {
    if (ADCP1_reg0_data.ADTRSEL.bits.TSEL == 5) {
        if (rising(&INTTS0OD, value)) {
            bhmTriggerEvent(triggerEvent);
        }
    }
    updatepin(&INTTS0OD, value);
}

PPM_NET_CB(P_INTTS0CD) {
    if (ADCP1_reg0_data.ADTRSEL.bits.TSEL == 6) {
        if (rising(&INTTS0CD, value)) {
            bhmTriggerEvent(triggerEvent);
        }
    }
    updatepin(&INTTS0CD, value);
}

PPM_NET_CB(P_INTTS1OD) {
    if (ADCP1_reg0_data.ADTRSEL.bits.TSEL == 7) {
        if (rising(&INTTS1OD, value)) {
            bhmTriggerEvent(triggerEvent);
        }
    }
    updatepin(&INTTS1OD, value);
}

PPM_NET_CB(P_INTTS1CD) {
    if (ADCP1_reg0_data.ADTRSEL.bits.TSEL == 8) {
        if (rising(&INTTS1CD, value)) {
            bhmTriggerEvent(triggerEvent);
        }
    }
    updatepin(&INTTS1CD, value);
}

Uns32 readSample(Uns32 addr, Uns32 bytes, Int32 idx) {
    Uns16 ADCR = 0;

    Uns8 MS  = cap[0].MS;
    Uns8 BS  = cap[0].BS;
    Uns8 ANI = cap[0].ANI;

    if (DIAG_HIGH) bhmMessage("I", PREFIX"_RS",
                "Info MS %d BS %d ANI %d idx %d bytes %d odd %d",
                         MS,   BS,   ANI,   idx,   bytes, addr&1);

    //
    // Detect scan/select mode and (1|4)-buffer operation - load adc[] accordingly
    //
    if (MS) {
        //
        // Select Mode, select a particular input
        //
        if (DIAG_HIGH) bhmMessage("I", PREFIX"_RS", "Select Mode");
        if (BS) {
            //
            // 4 Buffer Mode, 4 samples to complete -> reg 0-7
            // ANIx > ADRNx - ADRNy
            // capture is in reverse so latest is 3,2,1,0
            //
            if (DIAG_HIGH) bhmMessage("I", PREFIX"_RS", "4 Buffer Mode");
            Int8 slice = ~(idx%4) & 0x3;
            getAnalogValue(cap[slice]);
            ADCR = adcin[ANI].value;
        } else {
            //
            // 1 Buffer Mode, 1 sample to complete
            //
            if (DIAG_HIGH) bhmMessage("I", PREFIX"_RS", "1 Buffer Mode");
            getAnalogValue(cap[0]);
            ADCR = adcin[idx].value;
        }
    } else {
        //
        // Scan Mode, iterate across inputs 0 to ch, loading
        // ADCRn0 -> ADCRn0+ch
        //
        Int8 slice = ANI - idx;         // idx should never be more than ANI
        if (DIAG_HIGH) bhmMessage("I", PREFIX"_RS", "Scan Mode (idx %d slice %d)", idx, slice);
        if (slice < 0) {
            //
            // TODO
            // this is accessing an old register - not sure what to do here
            //
            getAnalogValue(cap[idx]);
            ADCR = adcin[idx].value;

        } else {
            getAnalogValue(cap[slice]);
            ADCR = adcin[idx].value;
        }
    }

    //
    // Calculate which part is being read
    //
    if ((PTR_TO_UNS32(addr)) & 0x1) {
        ADCR = ADCR >> 8;
    }
    if (bytes == 1) {
        ADCR &= 0xff;
    }
    if(DIAG_HIGH)
        bhmMessage("I", PREFIX"_RS", "Value 0x%04x (%d)", ADCR, ADCR);
    return ADCR;
}

PPM_REG_READ_CB(readADCR) {
    Int32 idx = PTR_TO_INT32(user);
    if(DIAG_HIGH)
        bhmMessage("I", PREFIX"_ADCR", "Channel Index %d", idx);
    return readSample(PTR_TO_UNS32(addr), bytes, idx);
}

PPM_REG_READ_CB(readADDMA) {
    static Uns32 index = 0;
    // Select mode index is current channel
    if (!ADCP0_reg0_data.ADM0.bits.MS) {
        index = ADCP0_reg0_data.ADM2.bits.ANI;
    }
    ADCP0_reg2_data.ADDMA.bits.ADDMA = readSample(0,2,index);
    if(DIAG_HIGH)
        bhmMessage("I", PREFIX"_ADDMA", "DMA Read index:%d  val:%d 0x%02x",
               index, ADCP0_reg2_data.ADDMA.bits.ADDMA, ADCP0_reg2_data.ADDMA.bits.ADDMA);
    // Scan mode iterate over scanned channels (setup for next channel)
    if (ADCP0_reg0_data.ADM0.bits.MS) {
        index = (index+1)%(ADCP0_reg0_data.ADM2.bits.ANI+1);
    }

    // TODO: Not modeling overflow
    ADCP0_reg2_data.ADDMA.bits.ODF = 0;

    return ADCP0_reg2_data.ADDMA.value;
}

PPM_REG_WRITE_CB(writeADM0) {
    //
    // Check legal values
    //
    if (data & 0x0f) {
        bhmMessage("W", PREFIX"_ADM0", "Register ADM0 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf) | (data & 0xf0);

    Uns8 ADCE = ADCP0_reg0_data.ADM0.bits.ADCE;

    if (ADCE==1) {
        //
        // This will kickstart the controller thread, and the idle thread
        //
        bhmTriggerEvent(adceEvent);
    } else {
        //
        // We do not need the idle thread
        //
//        bhmDeleteThread(idleThreadHandle);
    }
}

PPM_REG_WRITE_CB(writeADM1) {
    //
    // Check legal values
    //
    if (data & 0x0c) {
        bhmMessage("W", PREFIX"_ADM1", "Register ADM1 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xc) | (data & 0xf3);

    //
    // Edge specification
    //
    switch (ADCP0_reg0_data.ADM1.bits.EGA) {
    case 0: // No Edge detected
        break;

    default:// Unsupported Rising Falling Both
        bhmMessage("W", PREFIX"_ADM1", "Register ADM1[EGA] Unsupported value 0x%01x\n", ADCP0_reg0_data.ADM1.bits.EGA);
        break;
    }

    //
    // Trigger mode
    //
    switch (ADCP0_reg0_data.ADM1.bits.TRG) {
    case 0: // A/D Trigger Mode
    case 1: // Timer Trigger Mode
    case 2: // External Trigger Mode
        break;
    default:// Prohibited
        bhmMessage("W", PREFIX"_ADM1", "Register ADM1[TRG] Prohibited value 0x%01x\n", ADCP0_reg0_data.ADM1.bits.TRG);
        break;
    }

    //
    // Converter Mode FR - ignored
    //
    switch (ADCP0_reg0_data.ADM1.bits.FR) {
    case 0:
        FRdelay = 3;
        break;
    case 1:
        FRdelay = 6;
        break;
    case 2:
        FRdelay = 8.5;
        break;
    case 3:
    default:
        FRdelay = 10.5;
        break;
    }
}

PPM_REG_WRITE_CB(writeADM2) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", PREFIX"_ADM2", "Register ADM2 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);

    //
    // Analog pin selection
    //
    if (ADCP0_reg0_data.ADM2.bits.ANI > 9) {
        bhmMessage("W", PREFIX"_ADM2", "Register ADM2[ANI] Prohibited value 0x%01x\n", ADCP0_reg0_data.ADM2.bits.ANI);
    }
}

PPM_REG_WRITE_CB(writeADTRSEL) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", PREFIX, "Register ADTRSEL Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);

    if ((ADCP1_reg0_data.ADTRSEL.bits.TSEL == 0) || (ADCP1_reg0_data.ADTRSEL.bits.TSEL > 8)) {
        bhmMessage("W", PREFIX, "Register ADTRSEL[TSEL] Prohibited value 0x%01x\n", ADCP1_reg0_data.ADTRSEL.bits.TSEL);
    }
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    INTAD.netP = handles.INTAD;
    ADDMARQ.netP = handles.ADDMARQ;

    //
    // Trigger Events
    //
    triggerEvent = bhmCreateNamedEvent("Trigger", "Trigger event");
    adceEvent    = bhmCreateNamedEvent("ADCE",  "ADCE Enable event");
    //
    // Get the buffer file name
    //
    Int32 ch;
    char stimAttrName[64];
    for (ch=0; ch < ANIN; ch++) {
        sprintf(stimAttrName, "stimfile%d", ch);
        adcin[ch].fp     = NULL;
        adcin[ch].mode   = 0;
        adcin[ch].next   = -1;
        adcin[ch].now    = 0;
        adcin[ch].value  = 0;

        if (bhmStringParamValue(stimAttrName, buffer, sizeof(buffer))) {

            adcin[ch].fp = fopen(buffer, "r");
            if (adcin[ch].fp == NULL) {
                bhmMessage("F", "OPEN", "Cannot open stimfile%d=%s", ch, buffer);
            }

            //
            // initially assume we are SYNChronous unless we read a value indicating
            // otherwise
            //
            adcin[ch].mode = SYNC;
        }

        char plantAttrName[32];
        sprintf(plantAttrName, "plantmode%d", ch);

        if (bhmStringParamValue(plantAttrName, buffer, sizeof(buffer))) {

            if(strcmp(buffer, "voltage") == 0) {
                adcin[ch].plantMode = 0;

            } else if(strcmp(buffer, "current") == 0) {
                adcin[ch].plantMode = 1;

            } else {
                bhmMessage("F", "PLANT_INIT", "Channel %d: Do not recognize plant mode '%s', expecting 'voltage' or 'current' ", ch, buffer);
            }
            adcin[ch].plantEnable = True;
        }
    }

    //
    // PCLK1
    //
    bhmUns32ParamValue("PCLK1", &PCLK1);

    //
    // sample
    //
    bhmDoubleParamValue("sample", &sample);
    if (sample==0) {
        bhmMessage("E", PREFIX, "Parameter 'sample' must be non-zero");
    } else {

        //
        // Start the Controller loop
        //
        controllerThreadHandle = bhmCreateThread(controllerThread, 0, "controllerThread", 0);
        idleThreadHandle = bhmCreateThread(idleThread, 0, "idleThread", 0);
    }

}

PPM_DESTRUCTOR_CB(destructor) {
    Int32 ch;
    for (ch=0; ch<=9; ch++) {
        //
        // Read before close
        //
        if (adcin[ch].fp) {
            fclose(adcin[ch].fp);
        }
    }
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


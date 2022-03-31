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

// Section references in this file are to the
// K60 Sub-Family Reference Manual, Rev. 2, Dec 2011.

#include "stdio.h"
#include "pse.igen.h"
#define BPORT1 handles.bport1
#include "pse.macros.igen.h"
#include "stimulus.h"

#define PREFIX "ADC"

#define ADC_DISABLED 0x1F // Value of SC1A[ADCH] indicating module disabled
#define NOT_SAMPLING 0xFFFFFFFF

struct {
    Bool isRunningUnitTest;
    char  stimFile[NUM_CHANNELS][64];
    double       busClockPeriod;
    double       conversionDelay;
    ppmNetValue  lastAltClkValue;
    ppmNetValue  lastHwTrigValue;
    Uns32        divClkToAdckRemaining;
    Uns32        hwTrigSelValue;
    Uns32        convASamplesRemaining;
    Uns32        convBSamplesRemaining;
    ppmNetValue  currAdInIdValue;
    ppmNetValue  currInterruptValue;
    ppmNetValue  currDmaReqValue;
    double lastUpdateTime; // DGV TODO: Not used.  Can it be used to avoid issues
                           //           when triggering inputs change simultaneously?
} state = {
    .isRunningUnitTest     = False,
    .stimFile              = {{0}},
    .busClockPeriod        = -1,
    .conversionDelay       = -1,
    .lastAltClkValue       = -1,
    .lastHwTrigValue       = -1,
    .divClkToAdckRemaining = 0,
    .hwTrigSelValue        = 0,
    .convASamplesRemaining = NOT_SAMPLING,
    .convBSamplesRemaining = NOT_SAMPLING,
    .currAdInIdValue       = ADC_DISABLED,
    .currInterruptValue    = 0,
    .currDmaReqValue       = 0,
    .lastUpdateTime        = 0.0
};

//////////////////////////////// Internal Functions  ////////////////////////////

// Set AdInId line to value (if connected)
static void updateAdInIdOutput(Uns32 value) {

    // Only update if value changes from current  state
    if (state.currAdInIdValue != value) {
        state.currAdInIdValue = value;
        if (handles.AdInId) {
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisADC", "        setting adinid = %d", (Uns32)state.currAdInIdValue);
            }
            ppmWriteNet(handles.AdInId, state.currAdInIdValue);
        }
    }
}

// Set interrupt line to value (if connected)
static void updateInterruptOutput(Uns32 value) {

    // Only update if value changes from current  state
    if (state.currInterruptValue != value) {
        state.currInterruptValue = value;
        if (handles.Interrupt) {
            if (PSE_DIAG_HIGH) {
                bhmMessage(
                    "I", PREFIX "_SI",
                    "Setting Interrupt=%d @ %0.0fuS",
                    (Uns32)state.currInterruptValue, bhmGetCurrentTime()
                );
            }
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisADC", "        setting interrupt = %d", (Uns32)state.currInterruptValue);
            }
            ppmWriteNet(handles.Interrupt, state.currInterruptValue);
        }
    }
}

// Set DMA request line to value (if connected)
static void updateDmaReqOutput(Uns32 value) {

    // Only update if value changes from current  state
    if (state.currDmaReqValue != value) {
        state.currDmaReqValue = value;
        if (handles.DmaReq) {
            if (PSE_DIAG_HIGH) {
                bhmMessage(
                    "I", PREFIX "_SI",
                    "Setting DmaReq=%d @ %0.0fuS",
                    (Uns32)state.currDmaReqValue, bhmGetCurrentTime()
                );
            }
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisADC", "        setting dma request = %d", (Uns32)state.currDmaReqValue);
            }
            ppmWriteNet(handles.DmaReq, state.currDmaReqValue);
        }
    }
}

// See section 37.4.5.5
static Uns32 getConversionCycles()
{
    Uns32 retVal = 0;

    // DGV TODO: Add check for CFG1.ADLSMP, CFG2.ADLSTS, or CFG2.ADHSC changing
    //           during a conversion
    // DGV TODO: For continuous mode, when !CFG1.ADLSMP, the count is reduced by
    //           two for conversions after the first
    if (!bport1_ab_data.CFG1.bits.ADLSMP) {
        if (!bport1_ab_data.CFG2.bits.ADHSC) {
            retVal = 6;
        } else {
            retVal = 8;
        }
    } else {
        switch (bport1_ab_data.CFG2.bits.ADLSTS)
        {
            case 0:
                retVal = 24;
                break;
            case 1:
                retVal = 16;
                break;
            case 2:
                retVal = 10;
                break;
            case 3:
                retVal = 6;
                break;
            default:
                // DGV TODO: error condition
                break;
        }
        if (bport1_ab_data.CFG2.bits.ADHSC) {
            retVal += 2;
        }
    }
    return retVal;
}

// See section 37.3.4
static Uns32 getConvertedValue(Uns32 adin)
{
    Uns32 retVal = 0;
    Uns32 offset;
    Uns32 divisor = 0;
    ppmNetValue refHigh = ppmReadNet(handles.Vrefsh);
    ppmNetValue refLow = ppmReadNet(handles.Vrefsl);
    switch (bport1_ab_data.CFG1.bits.MODE) {
        case 0:
            divisor =  1 << 8;
            break;
        case 1:
            divisor =  1 << 12;
            break;
        case 2:
            divisor =  1 << 10;
            break;
        case 3:
            divisor =  1 << 16;
            break;
        default:
            break;
    }
    Uns32 delta = (refHigh - refLow) / divisor;
    if (adin < refLow) {
        offset = 0;
        retVal = 0;
    }
    else if (adin >= refHigh) {
        offset = refHigh;
        retVal = divisor - 1;
    } else {
        offset = adin - refLow;
        retVal = offset / delta;
    }
//  bhmMessage("I", "KinetisADC", "        adin=0x%08x (%u), refHigh=0x%08x (%u), refLow=0x%08x (%u), divisor=0x%08x (%u)",
//      adin, adin, refHigh, refHigh, refLow, refLow, divisor, divisor);
//  bhmMessage("I", "KinetisADC", "        offset=0x%08x (%u), delta=0x%08x (%u), result=0x%08x (%u)",
//      offset, offset, delta, delta, retVal, retVal);
    return retVal;
}

// Set conversion A result
static void updateConvAResult()
{
    bport1_ab_data.RA.bits.D = getConvertedValue(ppmReadNet(handles.AdIn));
    bport1_ab_data.SC2.bits.ADACT = 0; //DGV TODO: What about other channel.
    bport1_ab_data.SC1A.bits.COCO = 1;
    if (state.isRunningUnitTest) {
        bhmMessage("I", "KinetisADC", "        channel %s: conversion complete with value %u (ADACT=%d,COCO=%d)",
            "A", bport1_ab_data.RA.bits.D,
            bport1_ab_data.SC2.bits.ADACT, bport1_ab_data.SC1A.bits.COCO);
    }
    if (bport1_ab_data.SC1A.bits.AIEN) {
        updateInterruptOutput(1);
    }
    if (bport1_ab_data.SC2.bits.DMAEN) {
        updateDmaReqOutput(1);
    }
    if (!bport1_ab_data.SC3.bits.ADCO) {
        state.convASamplesRemaining = NOT_SAMPLING;
    } else {
        state.convASamplesRemaining = getConversionCycles();
        if (!bport1_ab_data.CFG1.bits.ADLSMP) {
          state.convASamplesRemaining -= 2;
        }
        bport1_ab_data.SC2.bits.ADACT = 1;
        if (state.isRunningUnitTest) {
            bhmMessage("I", "KinetisADC", "        channel %s: initiating continuous conversion over %d cycles (ADACT=%d,COCO=%d)",
                "A", state.convASamplesRemaining,
                bport1_ab_data.SC2.bits.ADACT, bport1_ab_data.SC1A.bits.COCO);
        }
    }
}

// Set conversion B result
static void updateConvBResult()
{
    bport1_ab_data.RB.bits.D = getConvertedValue(ppmReadNet(handles.AdIn));
    bport1_ab_data.SC2.bits.ADACT = 0; //DGV TODO: What about other channel.
    bport1_ab_data.SC1B.bits.COCO = 1;
    if (state.isRunningUnitTest) {
        bhmMessage("I", "KinetisADC", "        channel %s: conversion complete with value %u (ADACT=%d,COCO=%d)",
            "B", bport1_ab_data.RB.bits.D,
            bport1_ab_data.SC2.bits.ADACT, bport1_ab_data.SC1B.bits.COCO);
    }
    if (bport1_ab_data.SC1A.bits.AIEN) {
        updateInterruptOutput(1);
    }
    if (bport1_ab_data.SC2.bits.DMAEN) {
        updateDmaReqOutput(1);
    }
    if (!bport1_ab_data.SC3.bits.ADCO) {
        state.convBSamplesRemaining = NOT_SAMPLING;
    } else {
        state.convBSamplesRemaining = getConversionCycles();
        if (!bport1_ab_data.CFG1.bits.ADLSMP) {
          state.convBSamplesRemaining -= 2;
        }
        bport1_ab_data.SC2.bits.ADACT = 1;
        if (state.isRunningUnitTest) {
            bhmMessage("I", "KinetisADC", "        channel %s: initiating continuous conversion over %d cycles (ADACT=%d,COCO=%d)",
                "B", state.convASamplesRemaining,
                bport1_ab_data.SC2.bits.ADACT, bport1_ab_data.SC1B.bits.COCO);
        }
    }
}

static void setClkToAdckDivide()
{
    switch (bport1_ab_data.CFG1.bits.ADIV) {
        case 0:
            state.divClkToAdckRemaining =  1;
            break;
        case 1:
            state.divClkToAdckRemaining =  2;
            break;
        case 2:
            state.divClkToAdckRemaining =  4;
            break;
        case 3:
            state.divClkToAdckRemaining =  8;
            break;
        default:
            break;
    }
//    bhmMessage("I", "KinetisADC", "        just set state.divClkToAdckRemaining to %d",
//      state.divClkToAdckRemaining);
}

static Bool isAdckClock()
{
    Bool retVal = False;
    state.divClkToAdckRemaining--;
    if (0 >= state.divClkToAdckRemaining) {
        retVal = True;
        setClkToAdckDivide();
        //DGV TODO: Add check to make sure adin is not changing during sampling
        if (NOT_SAMPLING != state.convASamplesRemaining) {
            state.convASamplesRemaining--;
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisADC", "        channel %s: conversion clk, %d cycles remain (ADACT=%d,COCO=%d)",
                    "A", state.convASamplesRemaining,
                    bport1_ab_data.SC2.bits.ADACT, bport1_ab_data.SC1A.bits.COCO);
            }
            if (0 == state.convASamplesRemaining) {
                updateConvAResult();
            }
        }
        if (NOT_SAMPLING != state.convBSamplesRemaining) {
            state.convBSamplesRemaining--;
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisADC", "        channel %s: conversion clk, %d cycles remain (ADACT=%d,COCO=%d)",
                    "B", state.convBSamplesRemaining,
                    bport1_ab_data.SC2.bits.ADACT, bport1_ab_data.SC1B.bits.COCO);
            }
            if (0 == state.convBSamplesRemaining) {
                updateConvBResult();
            }
        }
    }
    return retVal;
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NET_CB(altClkCB) {
    if (bport1_ab_data.CFG1.bits.ADICLK) {
        if (value != state.lastAltClkValue) {
            state.lastAltClkValue = value;
            if (state.lastAltClkValue) { // Rising edge
                isAdckClock();
            }
        }
    }
}

#define HWTRIG_ADHWT    0x1
#define HWTRIG_ADHWTSA  0x2
#define HWTRIG_ADHWTSB  0x4
PPM_NET_CB(hwTrigCB) {
    // Proceed if hw trigger is enabled
    if (bport1_ab_data.SC2.bits.ADTRG) {
        if (value != state.lastHwTrigValue) {
            // Determine what has changed
            Uns32 changedBits = value ^ state.lastHwTrigValue;
            if (changedBits & HWTRIG_ADHWTSA) {
                if (value & HWTRIG_ADHWTSA) {
                    // note that selection has occurred
                    state.hwTrigSelValue |= HWTRIG_ADHWTSA;
                    if (state.isRunningUnitTest) {
                        bhmMessage("I", "KinetisADC", "        channel A: select event (ADACT=%d,COCO=%d)",
                            bport1_ab_data.SC2.bits.ADACT, bport1_ab_data.SC1A.bits.COCO);
                    }
                } else if (bport1_ab_data.SC2.bits.ADACT) {
                    // don't remember selection if conversion in progress
                    state.hwTrigSelValue &= ~HWTRIG_ADHWTSA;
                    if (state.isRunningUnitTest) {
                        bhmMessage("I", "KinetisADC", "        channel A: clearing select event");
                    }
                }
            }
            if (changedBits & HWTRIG_ADHWTSB) {
               //DGV TODO: same logic here as for A above
            }
            if ((changedBits & HWTRIG_ADHWT) & (value & HWTRIG_ADHWT)) {
                if (changedBits & HWTRIG_ADHWTSA) {
                    //DGV TODO: Error - trigger select must happen before trigger
                }
                if (changedBits & HWTRIG_ADHWTSB) {
                    //DGV TODO: Error - trigger select must happen before trigger
                }
                // Start conversion if one is not already in progress
                // and selection has occurred.
                if (!bport1_ab_data.SC2.bits.ADACT) {
                    if ((state.hwTrigSelValue & HWTRIG_ADHWTSA) &&
                        (state.hwTrigSelValue & HWTRIG_ADHWTSB))
                    {
                        //DGV TODO: Error - multiple trigger selects
                    } else if (state.hwTrigSelValue & HWTRIG_ADHWTSA){
                        state.convASamplesRemaining = getConversionCycles();
                        // DGV TODO: section 37.3.1 says COCO is cleared when respective SC1n is
                        //           written or respective Rn is read.  We are clearing it
                        //           automatically here.  Is this right?
                        bport1_ab_data.SC1A.bits.COCO = 0;
                        bport1_ab_data.SC2.bits.ADACT = 1;
                        if (state.isRunningUnitTest) {
                            bhmMessage("I", "KinetisADC", "        channel %s: initiating conversion over %d cycles (ADACT=%d,COCO=%d)",
                                "A", state.convASamplesRemaining,
                                bport1_ab_data.SC2.bits.ADACT, bport1_ab_data.SC1A.bits.COCO);
                        }
                    }
                    else if (state.hwTrigSelValue & HWTRIG_ADHWTSB){
                        // DGV TODO: section 37.3.1 says COCO is cleared when respective SC1n is
                        //           written or respective Rn is read.  We are clearing it
                        //           automatically here.  Is this right?
                        state.convBSamplesRemaining = getConversionCycles();
                        bport1_ab_data.SC1B.bits.COCO = 0;
                        bport1_ab_data.SC2.bits.ADACT = 1;
                        if (state.isRunningUnitTest) {
                            bhmMessage("I", "KinetisADC", "        channel %s: initiating conversion over %d cycles (ADACT=%d,COCO=%d)",
                                "B", state.convBSamplesRemaining,
                                bport1_ab_data.SC2.bits.ADACT, bport1_ab_data.SC1B.bits.COCO);
                        }
                    }
                }
            }
            state.lastHwTrigValue = value;
        }
    }
}

captureInfo cap = { 0 };

bhmEventHandle adcTriggerEvent;
bhmEventHandle adcEnableEvent;

static bhmThreadHandle controllerThreadHandle = 0;

static void syncControllerThread(void *user) {
    Int32 ch = 0;
    int i;

    if (state.isRunningUnitTest) {
    /*
        bhmMessage("I", "KinetisADC", "Enabled Capabilities: %s %s %s %s %s %s %s %s",
            bport1_ab_data.CR1.bits.EN ? "CMP" : "",
            bport1_ab_data.CR1.bits.SE ? "S" : "",
            bport1_ab_data.CR1.bits.WE ? "W" : "",
            bport1_ab_data.CR1.bits.OPE ? "OP" : "",
            bport1_ab_data.DACCR.bits.DACEN ? "DAC" : "",
            bport1_ab_data.SCR.bits.IER ? "IR" : "",
            bport1_ab_data.SCR.bits.IEF ? "IF" : "",
            bport1_ab_data.SCR.bits.DMAEN ? "DMA" : ""
        );
        */
    }

    cap.time = bhmGetCurrentTime();
    getValue(&cap); // Consume the first line of the file.  It isn't used

    for (i = 0; i < 100; i++) {

        // If the A/D is disabled, wait for event causing enable
        if (ADC_DISABLED == bport1_ab_data.SC1A.bits.ADCH) {
            bhmWaitEvent(adcEnableEvent);
        }

        // Wait for the trigger.  Per SC2[ADTRG], either the software or
        // hardware can trigger a conversion.
        bhmWaitEvent(adcTriggerEvent);

        // Wait for the conversion delay
        //DGV TODO: These calculation should happen automatically upon register writes.
        setClkToAdckDivide();
        switch (bport1_ab_data.CFG1.bits.ADICLK) {
        case 0:
            state.conversionDelay = (0 < state.busClockPeriod) ?
            state.busClockPeriod * state.divClkToAdckRemaining * getConversionCycles() : 0;
            break;
        case 1:
            state.conversionDelay = (0 < state.busClockPeriod) ?
            2 * state.busClockPeriod * state.divClkToAdckRemaining * getConversionCycles() : 0;
            break;
        default:
            break;
        }
        bhmWaitDelay(state.conversionDelay);

        // Read value from file.
        getValue(&cap);
        Uns32 adin = adc_in[ch].adin_value;

        if (state.isRunningUnitTest) {
            bhmMessage("I", "KinetisADC", "%6.2f: adin = 0x%-8x", bhmGetCurrentTime(), adin);
        }

        ppmWriteNet(handles.AdIn, adin);
        ppmWriteNet(handles.AdInId, bport1_ab_data.SC1A.bits.ADCH);
        updateConvAResult();
    }
}

static void asyncControllerThread(void *user) {
    Int32 ch = 0;
    static double delay = 0.0;
    int i;

    if (state.isRunningUnitTest) {
    /*
        bhmMessage("I", "KinetisADC", "Enabled Capabilities: %s %s %s %s %s %s %s %s",
            bport1_ab_data.CR1.bits.EN ? "CMP" : "",
            bport1_ab_data.CR1.bits.SE ? "S" : "",
            bport1_ab_data.CR1.bits.WE ? "W" : "",
            bport1_ab_data.CR1.bits.OPE ? "OP" : "",
            bport1_ab_data.DACCR.bits.DACEN ? "DAC" : "",
            bport1_ab_data.SCR.bits.IER ? "IR" : "",
            bport1_ab_data.SCR.bits.IEF ? "IF" : "",
            bport1_ab_data.SCR.bits.DMAEN ? "DMA" : ""
        );
        */
    }

    // DGV TODO: Need to add check that value is not a reserved one.  Also, what about SC1B?
    if (ADC_DISABLED != bport1_ab_data.SC1A.bits.ADCH) {
        cap.time = bhmGetCurrentTime();
        getValue(&cap); // Consume the first line of the file.  It isn't used
        for (i = 0; i < 100; i++) {
            // DGV TODO: incorporate gain and offset in the setting of adin
            Uns32 altclk = adc_in[ch].altclk_value & 1;
            Uns32 hwtrig = adc_in[ch].hwtrig_value & 0x7;
            Uns32 adin = adc_in[ch].adin_value;
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisADC", "%6.0f: altclk = %d, hwtrig = 0x%x, adin = 0x%-8x",
                    bhmGetCurrentTime(), altclk, hwtrig, adin);
            }

            ppmWriteNet(handles.AdIn, adin);
            ppmWriteNet(handles.AdInId, bport1_ab_data.SC1A.bits.ADCH);
            ppmWriteNet(handles.HwTrig, hwtrig);
            ppmWriteNet(handles.AltClk, altclk);

            delay = adc_in[ch].next;
            bhmWaitDelay(delay);
            getValue(&cap);
        }
    }
};

static bhmThreadHandle stimulusTriggerThreadHandle = 0;

// This emulates the software triggering that occur when
// the SC1A register is written (with ADCH bits not all 1's).
static void stimulusTriggerThread(void *user) {
    int i;

    for (i = 0; i < 50; i++) {
        bhmWaitDelay(3.0);
        bhmTriggerEvent(adcTriggerEvent);
    }
}

// Attributes for configuring ADC from command line
//   bus_clock_freq (in MHz)
//   configure_sc1a
//   configure_sc1b (placeholder; not currently used)
//   configure_cfg1
//   configure_cfg2
//   configure_cv1  (placeholder; not currently used)
//   configure_cv2  (placeholder; not currently used)
//   configure_sc2
//   configure_sc3
// For each of these the lower 8 bits (16 bits for configure_cv1 and
// configure_cvs2) correspond to those in the underlying ADC register.


PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)

    // Enabling and trigger Events
    adcEnableEvent   = bhmCreateNamedEvent("ADCE",  "ADCE Enable event");
    adcTriggerEvent = bhmCreateNamedEvent("Trigger", "Trigger event");


    // Setup the channel stimulus
    Int32 ch;
    char stimAttrName[64];
    for (ch=0; ch < NUM_CHANNELS; ch++) {
        sprintf(stimAttrName, "stimFile%d", ch);
        adc_in[ch].fp     = NULL;
        adc_in[ch].next   = -1;
        adc_in[ch].now    = 0;
        adc_in[ch].altclk_value  = 0;
        adc_in[ch].adin_value  = 0;
        if (bhmStringParamValue(stimAttrName, state.stimFile[ch], sizeof(state.stimFile[ch]))) {

            bhmMessage("I", "KinetisADC", "%s = %s", stimAttrName, state.stimFile[ch]);
            adc_in[ch].fp = fopen(state.stimFile[ch], "r");
            if (adc_in[ch].fp == NULL) {
                bhmMessage("F", "OPEN", "Cannot open stimFile%d=%s", ch, state.stimFile[ch]);
            }

            //
            // initially assume we are SYNChronous unless we read a value indicating
            // otherwise
            //
            //DGV adc_in[ch].mode = SYNC;
            adc_in[ch].mode = ASYNC;
        }
    }

    periphConstructor();

    // YOUR CODE HERE (post constructor)

    // Initialize the output nets
    updateAdInIdOutput(ADC_DISABLED);
    updateInterruptOutput(0);
    updateDmaReqOutput(0);

    // Configure the ADC from any given command line options
    Uns32 configBits;

    // Bus clock frequency in MHz
    if (bhmUns32ParamValue("bus_clock_freq", &configBits)) {
        if (0 < configBits) {
            state.busClockPeriod = 1.0 / configBits;
            bhmMessage("I", "KinetisADC", "bus clock freq = %d MHz => bus period = %6.2f us\n",
                configBits, state.busClockPeriod);
        } else {
            bhmMessage("I", "KinetisADC", "bus clock freq = <not specified>");
        }
    }

    // SC1A
    if (bhmUns32ParamValue("configure_sc1a", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.SC1A.bits.AIEN = 0 != (configBits & BPORT1_AB_SC1A_AIEN);
        bport1_ab_data.SC1A.bits.DIFF = 0 != (configBits & BPORT1_AB_SC1A_DIFF);
        bport1_ab_data.SC1A.bits.ADCH = configBits & BPORT1_AB_SC1A_ADCH;
        updateAdInIdOutput(bport1_ab_data.SC1A.bits.ADCH);
        bhmMessage("I", "KinetisADC", "configure_sc1a = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisADC", "      AIEN = 0x%x\n", bport1_ab_data.SC1A.bits.AIEN);
        bhmMessage("I", "KinetisADC", "      DIFF = 0x%x\n", bport1_ab_data.SC1A.bits.DIFF);
        bhmMessage("I", "KinetisADC", "      ADCH = 0x%x\n", bport1_ab_data.SC1A.bits.ADCH);
    }

    // SC1B
    if (bhmUns32ParamValue("configure_sc1b", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.SC1B.bits.AIEN = 0 != (configBits & BPORT1_AB_SC1B_AIEN);
        bport1_ab_data.SC1B.bits.DIFF = 0 != (configBits & BPORT1_AB_SC1B_DIFF);
        bport1_ab_data.SC1B.bits.ADCH = configBits & BPORT1_AB_SC1B_ADCH;
        updateAdInIdOutput(bport1_ab_data.SC1B.bits.ADCH);
        bhmMessage("I", "KinetisADC", "configure_sc1b = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisADC", "      AIEN = 0x%x\n", bport1_ab_data.SC1B.bits.AIEN);
        bhmMessage("I", "KinetisADC", "      DIFF = 0x%x\n", bport1_ab_data.SC1B.bits.DIFF);
        bhmMessage("I", "KinetisADC", "      ADCH = 0x%x\n", bport1_ab_data.SC1B.bits.ADCH);
    }

    // CFG1
    if (bhmUns32ParamValue("configure_cfg1", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.CFG1.bits.ADLPC =  0 != (configBits & BPORT1_AB_CFG1_ADLPC);
        bport1_ab_data.CFG1.bits.ADIV =  (configBits & BPORT1_AB_CFG1_ADIV) >> 5;
        bport1_ab_data.CFG1.bits.ADLSMP =  0 != (configBits & BPORT1_AB_CFG1_ADLSMP);
        bport1_ab_data.CFG1.bits.MODE =  (configBits & BPORT1_AB_CFG1_MODE) >> 2;
        bport1_ab_data.CFG1.bits.ADICLK =  (configBits & BPORT1_AB_CFG1_ADICLK) >> 0;
        bhmMessage("I", "KinetisADC", "configure_cfg1 = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisADC", "    ADLPC = 0x%x\n", bport1_ab_data.CFG1.bits.ADLPC);
        bhmMessage("I", "KinetisADC", "     ADIV = 0x%x\n", bport1_ab_data.CFG1.bits.ADIV);
        bhmMessage("I", "KinetisADC", "   ADLSMP = 0x%x\n", bport1_ab_data.CFG1.bits.ADLSMP);
        bhmMessage("I", "KinetisADC", "     MODE = 0x%x\n", bport1_ab_data.CFG1.bits.MODE);
        bhmMessage("I", "KinetisADC", "   ADICLK = 0x%x\n", bport1_ab_data.CFG1.bits.ADICLK);
        if ((0 == bport1_ab_data.CFG1.bits.ADICLK) || (1 == bport1_ab_data.CFG1.bits.ADICLK))
        {
            if (0 > state.busClockPeriod) {
                bhmMessage("F", "KinetisADC", "bus_clock_freq attribute must be > 0 when the bus clock is the input clock");
            }
        }
    }

    // CFG2
    if (bhmUns32ParamValue("configure_cfg2", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.CFG2.bits.MUXSEL =  0 != (configBits & BPORT1_AB_CFG2_MUXSEL);
        bport1_ab_data.CFG2.bits.ADACKEN = 0 != (configBits & BPORT1_AB_CFG2_ADACKEN);
        bport1_ab_data.CFG2.bits.ADHSC = 0 != (configBits & BPORT1_AB_CFG2_ADHSC);
        bport1_ab_data.CFG2.bits.ADLSTS = (configBits & BPORT1_AB_CFG2_ADLSTS) >> 0;
        bhmMessage("I", "KinetisADC", "configure_cfg2 = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisADC", "   MUXSEL = 0x%x\n", bport1_ab_data.CFG2.bits.MUXSEL);
        bhmMessage("I", "KinetisADC", "  ADACKEN = 0x%x\n", bport1_ab_data.CFG2.bits.ADACKEN);
        bhmMessage("I", "KinetisADC", "    ADHSC = 0x%x\n", bport1_ab_data.CFG2.bits.ADHSC);
        bhmMessage("I", "KinetisADC", "   ADLSTS = 0x%x\n", bport1_ab_data.CFG2.bits.ADLSTS);
    }

    // CV1
    if (bhmUns32ParamValue("configure_cv1", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.CV1.bits.CV = (configBits & BPORT1_AB_CV1_CV) >> 0;
        bhmMessage("I", "KinetisADC", "configure_cv1 = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisADC", "       CV = 0x%x\n", bport1_ab_data.CV1.bits.CV);
    }

    // CV2
    if (bhmUns32ParamValue("configure_cv2", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.CV2.bits.CV = (configBits & BPORT1_AB_CV2_CV) >> 0;
        bhmMessage("I", "KinetisADC", "configure_cv2 = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisADC", "       CV = 0x%x\n", bport1_ab_data.CV2.bits.CV);
    }

    // SC2
    if (bhmUns32ParamValue("configure_sc2", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.SC2.bits.ADTRG = 0 != (configBits & BPORT1_AB_SC2_ADTRG);
        bport1_ab_data.SC2.bits.ACFE = 0 != (configBits & BPORT1_AB_SC2_ACFE);
        bport1_ab_data.SC2.bits.ACFGT = 0 != (configBits & BPORT1_AB_SC2_ACFGT);
        bport1_ab_data.SC2.bits.ACREN = 0 != (configBits & BPORT1_AB_SC2_ACREN);
        bport1_ab_data.SC2.bits.DMAEN = 0 != (configBits & BPORT1_AB_SC2_DMAEN);
        bport1_ab_data.SC2.bits.REFSEL = (configBits & BPORT1_AB_SC2_REFSEL) >> 0;
        bhmMessage("I", "KinetisADC", "configure_sc2 = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisADC", "    ADTRG = 0x%x\n", bport1_ab_data.SC2.bits.ADTRG);
        bhmMessage("I", "KinetisADC", "     ACFE = 0x%x\n", bport1_ab_data.SC2.bits.ACFE);
        bhmMessage("I", "KinetisADC", "    ACFGT = 0x%x\n", bport1_ab_data.SC2.bits.ACFGT);
        bhmMessage("I", "KinetisADC", "    ACREN = 0x%x\n", bport1_ab_data.SC2.bits.ACREN);
        bhmMessage("I", "KinetisADC", "    DMAEN = 0x%x\n", bport1_ab_data.SC2.bits.DMAEN);
        bhmMessage("I", "KinetisADC", "   REFSEL = 0x%x\n", bport1_ab_data.SC2.bits.REFSEL);
    }

    // SC3
    if (bhmUns32ParamValue("configure_sc3", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.SC3.bits.CAL = 0 != (configBits & BPORT1_AB_SC3_CAL);
        bport1_ab_data.SC3.bits.CALF = 0 != (configBits & BPORT1_AB_SC3_CALF);
        bport1_ab_data.SC3.bits.ADCO = 0 != (configBits & BPORT1_AB_SC3_ADCO);
        bport1_ab_data.SC3.bits.AVGE = 0 != (configBits & BPORT1_AB_SC3_AVGE);
        bport1_ab_data.SC3.bits.AVGS = (configBits & BPORT1_AB_SC3_AVGS) >> 0;
        bhmMessage("I", "KinetisADC", "configure_sc3 = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisADC", "      CAL = 0x%x\n", bport1_ab_data.SC3.bits.CAL);
        bhmMessage("I", "KinetisADC", "     CALF = 0x%x\n", bport1_ab_data.SC3.bits.CALF);
        bhmMessage("I", "KinetisADC", "     ADCO = 0x%x\n", bport1_ab_data.SC3.bits.ADCO);
        bhmMessage("I", "KinetisADC", "     AVGE = 0x%x\n", bport1_ab_data.SC3.bits.AVGE);
        bhmMessage("I", "KinetisADC", "     AVGS = 0x%x\n", bport1_ab_data.SC3.bits.AVGS);
    }

    // Set ADC constant inputs from any given through command line options
    Uns32 inputBits;

    // Vrefh
    if (bhmUns32ParamValue("input_vrefh", &inputBits)) {
        state.isRunningUnitTest = True;
        ppmWriteNet(handles.Vrefsh, inputBits);
        bhmMessage("I", "KinetisADC", "Vrefsh = 0x%x (%u)\n", inputBits, inputBits);
    }

    // Vrefl
    if (bhmUns32ParamValue("input_vrefl", &inputBits)) {
        state.isRunningUnitTest = True;
        ppmWriteNet(handles.Vrefsl, inputBits);
        bhmMessage("I", "KinetisADC", "Vrefsl = 0x%x (%u)\n", inputBits, inputBits);
    }

    setClkToAdckDivide();

    // There are three parts to converting:
    //   1) Enabling the adc
    //   2) Triggering a conversion
    //   3) Completing the conversion over some number of clocks
    //
    // Enabling occurs by setting SC1A[ADCH] to a valid channel.  Disabling
    // occurs by setting to the value ADC_DISABLE (0x1f). Once disabled, the
    // subsequent enabling of the adc is indicated by the adcEnableEvent.
    //
    // Triggering can occur in hardware or software.  In either case this is
    // modeled as the setting of the event adcTriggerEvent.
    //
    // The number of ADCK clocks for conversion is determined through a few different
    // registers.  Upon triggering, these are examined to determine the amount of
    // time to delay before updating the RA register with the converted result and
    // asserting any configured interrupt or DMA request.
    //

    // Start the Controller loop based on the ADCK clock source.
    // When CFG1[ADICLK] is 0 or 1 the bus clock is the synchronous ADCK
    // clock source with the attribute bus_clock_freq giving the frequency.
    // When unit testing, trigger occurs automatically every 3 us and the
    // adin value for the selected input channel is in a stimulus file.
    //
    // When CFG1[ADICLK] is 2 or 3, an external clock
    // source is used that is potentially asynchronous to the bus clock.
    // When unit testing, the adc trigger and external clock are given
    // through a stimulus file.  The adin value for the selected input channel
    // is also in this stimulus file.
    if (adc_in[0].fp) {
        if ((0 == bport1_ab_data.CFG1.bits.ADICLK) || (1 == bport1_ab_data.CFG1.bits.ADICLK))
        {
            controllerThreadHandle = bhmCreateThread(syncControllerThread, 0, "syncControllerThread", 0);
            stimulusTriggerThreadHandle = bhmCreateThread(stimulusTriggerThread, 0, "stimulsTriggerThread", 0);
        } else {
            controllerThreadHandle = bhmCreateThread(asyncControllerThread, 0, "asyncControllerThread", 0);
        }
    }
}

PPM_DESTRUCTOR_CB(destructor) {
    Int32 ch;
    for (ch=0; ch<NUM_CHANNELS; ch++) {
        //
        // Read before close
        //
        if (adc_in[ch].fp) {
            fclose(adc_in[ch].fp);
        }
    }
}



// Save / restore callbacks

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


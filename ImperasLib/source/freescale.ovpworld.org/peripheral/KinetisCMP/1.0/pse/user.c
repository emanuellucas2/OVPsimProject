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
#include "string.h"
#include "pse.igen.h"
#define BPORT1 handles.bport1
#include "pse.macros.igen.h"
#include "stimulus.h"

#define PREFIX "CMP"

#define NUM_AMUX_INPUTS 8
#define NUM_VREF_INPUTS 2

Uns32 comparatorNumber = 0;

typedef struct {
    bhmThreadHandle thread;
    bhmEventHandle start;
} threadStateT, *threadStateP;

static threadStateT thState;

struct {
    Bool isRunningUnitTest;
    char  stimFile[64];
    ppmNetHandle amuxInputHandle[NUM_AMUX_INPUTS];
    ppmNetHandle vrefmuxInputHandle[NUM_VREF_INPUTS];
    ppmNetValue  lastExtSampleValue;
    ppmNetValue  lastInputValue[NUM_AMUX_INPUTS];
    Uns32        lastSampledCoutAValue;
    Uns32        numAgreeingCoutAValueSamples;
    Uns32        currCoutAValue;
    Uns32        currDacOutputValue;
    Uns32        currCoutSocValue;
    Uns32        currInterruptValue;
    Uns32        currDmaReqValue;
    Uns32        currCmpOPadValue;
    double       lastUpdateTime; // DGV TODO: Not used.  Can it be used to avoid issues
                           //           when triggering inputs change simultaneously?
} state = {
    .isRunningUnitTest  = False,
    .stimFile           = "",
    .amuxInputHandle     = {NULL},
    .vrefmuxInputHandle = {NULL},
    .lastExtSampleValue = -1,
    .lastInputValue     = {0},
    .lastSampledCoutAValue = 0,
    .numAgreeingCoutAValueSamples = 0,
    .currCoutAValue   = 0,
    .currDacOutputValue = 0,
    .currCoutSocValue   = 0,
    .currInterruptValue = 0,
    .currDmaReqValue    = 0,
    .currCmpOPadValue   = 0,
    .lastUpdateTime     = 0.0
};

//////////////////////////////////////////////////////////////////////////

// Set DAC Output to value if enabled (regardless if connected externally)
static void updateDacOutput() {
    // Only update if the DAC is enabled
    if (bport1_ab_data.DACCR.bits.DACEN) {
        Uns32 vinValue = ppmReadNet(state.vrefmuxInputHandle[bport1_ab_data.DACCR.bits.VRSEL]);
        Uns32 newDacOutputValue = vinValue * (bport1_ab_data.DACCR.bits.VOSEL + 1) / 64;

        // Only update if value changes from current  state
        if (state.currDacOutputValue != newDacOutputValue) {
            state.lastInputValue[7] = newDacOutputValue;
            state.currDacOutputValue = newDacOutputValue;
            if (PSE_DIAG_HIGH) {
                bhmMessage(
                    "I", PREFIX "_SI",
                    "Setting DAC Vin=%d, Output=%d @ %0.0fuS",
                    vinValue, state.currDacOutputValue, bhmGetCurrentTime()
                );
            }
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisCMP", "        setting DAC output = 0x%x", state.currDacOutputValue);
            }
            ppmWriteNet(state.amuxInputHandle[7], state.currDacOutputValue);
            ppmWriteNet(handles.DacOutput, state.currDacOutputValue);
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
                    state.currInterruptValue, bhmGetCurrentTime()
                );
            }
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisCMP", "        setting interrupt = %d", state.currInterruptValue);
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
                    state.currDmaReqValue, bhmGetCurrentTime()
                );
            }
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisCMP", "        setting dma request = %d", state.currDmaReqValue);
            }
            ppmWriteNet(handles.DmaReq, state.currDmaReqValue);
        }
    }
}

// Set CMPO at Pad to value (if connected)
static void updateCmpOPadOutput(Uns32 value) {

    // Only update if value changes from current  state
    if (state.currCmpOPadValue != value) {
        state.currCmpOPadValue = value;
        if (handles.CmpOPad) {
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisCMP", "        setting cmpo pad = %d", state.currCmpOPadValue);
            }
            ppmWriteNet(handles.CmpOPad, state.currCmpOPadValue);
        }
    }
}

// Set cout line to value (if connected)
static void updateCoutSocOutput(Uns32 value) {

    // Only update if value changes from current  state
    if (state.currCoutSocValue != value) {
        state.currCoutSocValue = value;
        bport1_ab_data.SCR.bits.COUT = value;
        // DGV TODO: Per section 38.9, implement interrupt deassertion:
        //             "by clearing either SCR[IER] or SCR[CFR] for a rising edge interrupt,
        //             or SCR[IEF] and SCR[CFF] for a falling edge interrupt."
        //           Is the rising edge clearing really an "or" condition and the falling
        //           edge really an "and" condition as the excerpt above indicates?
        if (bport1_ab_data.SCR.bits.COUT) {
            bport1_ab_data.SCR.bits.CFR = 1;
        } else {
            bport1_ab_data.SCR.bits.CFF = 1;
        }
        if (state.isRunningUnitTest) {
            bhmMessage("I", "KinetisCMP", "        SCR[COUT,CFF,CFR] = %d,%d,%d",
               bport1_ab_data.SCR.bits.COUT, bport1_ab_data.SCR.bits.CFF, bport1_ab_data.SCR.bits.CFR);
        }
        if (bport1_ab_data.SCR.bits.CFR && bport1_ab_data.SCR.bits.IER) {
            if (bport1_ab_data.SCR.bits.DMAEN) {
                updateDmaReqOutput(1);
            } else {
                updateInterruptOutput(1);
            }
        }
        if (bport1_ab_data.SCR.bits.CFF && bport1_ab_data.SCR.bits.IEF) {
            if (bport1_ab_data.SCR.bits.DMAEN) {
                updateDmaReqOutput(1);
            } else {
                updateInterruptOutput(1);
            }
        }
        if (!bport1_ab_data.CR1.bits.COS) {
            updateCmpOPadOutput(bport1_ab_data.SCR.bits.COUT);
        }
        if (handles.CoutSoc ) {
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisCMP", "        setting cout soc = %d", state.currCoutSocValue);
            }
            ppmWriteNet(handles.CoutSoc, state.currCoutSocValue);
        }
    }
}

static void updateComparatorOutput()
{
//    Uns32 lastCOUTValue = bport1_ab_data.SCR.bits.COUT;
    if (!bport1_ab_data.CR1.bits.EN) {
        state.currCoutAValue = 0;
        updateCoutSocOutput(state.currCoutAValue);
    } else {
        Uns32 minusValue = state.lastInputValue[bport1_ab_data.MUXCR.bits.MSEL];
        Uns32 plusValue = state.lastInputValue[bport1_ab_data.MUXCR.bits.PSEL];

         if (PSE_DIAG_HIGH) {
            bhmMessage("I", "KinetisCMP", "plus=%d, minus=%d, msel=%d", plusValue, minusValue,bport1_ab_data.MUXCR.bits.MSEL);
        }
        if (!bport1_ab_data.CR1.bits.INV) {
            // bport1_ab_data.SCR.bits.COUT = plusValue > minusValue;
            state.currCoutAValue = plusValue > minusValue;
        } else {
            // bport1_ab_data.SCR.bits.COUT = plusValue <= minusValue;
            state.currCoutAValue = plusValue <= minusValue;
        }
        if (state.isRunningUnitTest) {
            bhmMessage("I", "KinetisCMP", "        minus(%d) = 0x%x, plus(%d) = 0x%x => CoutA = %d",
               bport1_ab_data.MUXCR.bits.MSEL, minusValue,
               bport1_ab_data.MUXCR.bits.PSEL, plusValue,
               state.currCoutAValue);
        }
        if (!bport1_ab_data.CR1.bits.SE) {
            updateCoutSocOutput(state.currCoutAValue);
        }
        if (bport1_ab_data.CR1.bits.COS) {
            updateCmpOPadOutput(state.currCoutAValue);
        }
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(writeCR1) {
    // YOUR CODE HERE (writeCR1)
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", "KinetisCMP", "Write CR1 0x%x", data);
    }
    if (data & 0x01)
        bhmTriggerEvent(thState.start);

    *(Uns8*)user = (*(Uns8*)user & 0x28) | (data & 0xd7);
}

PPM_REG_WRITE_CB(writeMUX) {
    // YOUR CODE HERE (writeMUX)
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", "KinetisCMP", "Write MUX 0x%x", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xc0) | (data & 0x3f);
}

PPM_REG_WRITE_CB(writeSCR) {
    // YOUR CODE HERE (writeSCR)
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", "KinetisCMP", "Write SCR 0x%x", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xa1) | (data & 0x58);
    // Per section 38.7.4, implement clearing of SCR[CFR] and SCR[CFF] by
    //             "writing a logic one to the bit".
    if (data & 0x04) {
        *(Uns8*)user = *(Uns8*)user & ~0x04;
        updateDmaReqOutput(0);
    }
    if (data & 0x02) {
        *(Uns8*)user = *(Uns8*)user & ~0x02;
        updateDmaReqOutput(0);
    }
}

PPM_REG_WRITE_CB(writeDAC) {
    // YOUR CODE HERE (writeDAC)
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", "KinetisCMP", "Write DAC 0x%x", data);
    }
    *(Uns8*)user = data & 0xff;
    updateDacOutput();
}

PPM_NET_CB(extSampleCB) {
    if (bport1_ab_data.CR1.bits.SE) {
        if (value != state.lastExtSampleValue) {
            state.lastExtSampleValue = value;
            if (state.lastExtSampleValue) { // Rising edge
                if (!bport1_ab_data.CR0.bits.FILTER_CNT) {
                    updateCoutSocOutput(0);
                } else {
                    if (state.currCoutAValue == state.lastSampledCoutAValue) {
                        state.numAgreeingCoutAValueSamples++;
                    } else {
                        state.lastSampledCoutAValue = state.currCoutAValue;
                        state.numAgreeingCoutAValueSamples = 1;
                    }
                    if (state.isRunningUnitTest) {
                        bhmMessage("I", "KinetisCMP", "        %d of %d agreeing %d samples",
                            state.numAgreeingCoutAValueSamples, bport1_ab_data.CR0.bits.FILTER_CNT,
                            state.currCoutAValue);
                    }
                    if (state.numAgreeingCoutAValueSamples >= bport1_ab_data.CR0.bits.FILTER_CNT) {
                        updateCoutSocOutput(state.currCoutAValue);
                    }
                }
            }
        }
    }
}

// Macro for analog MUX input.
#define AMUX_INPUT_CB_BODY(_SELECT_BITS,_LAST_VALUE) \
        if (value != _LAST_VALUE) { \
            _LAST_VALUE = value; \
            if ((_SELECT_BITS == (bport1_ab_data.MUXCR.bits.MSEL)) || \
                (_SELECT_BITS == (bport1_ab_data.MUXCR.bits.PSEL))) \
            { \
                /* bhmMessage("I", "KinetisCMP", "%6.0f: input%dCB() reports value %d", \
                    bhmGetCurrentTime(), _SELECT_BITS, value); */ \
                updateComparatorOutput(); \
            } \
        }


PPM_NET_CB(input0CB) {
    if (PSE_DIAG_HIGH) {
   bhmMessage("I", "KinetisCMP", "%6.0f: input0CB() reports value %d",
      bhmGetCurrentTime(), (Uns32)value);
  }
    AMUX_INPUT_CB_BODY(0, state.lastInputValue[0])
}

PPM_NET_CB(input1CB) {
   //bhmMessage("I", "KinetisCMP", "%6.0f: input1CB() reports value %d",
      //bhmGetCurrentTime(), value);
    AMUX_INPUT_CB_BODY(1, state.lastInputValue[1])
}

PPM_NET_CB(input2CB) {
    AMUX_INPUT_CB_BODY(2, state.lastInputValue[2])
}

PPM_NET_CB(input3CB) {
    AMUX_INPUT_CB_BODY(3, state.lastInputValue[3])
}

PPM_NET_CB(input4CB) {
    AMUX_INPUT_CB_BODY(4, state.lastInputValue[4])
}

PPM_NET_CB(input5CB) {
    AMUX_INPUT_CB_BODY(5, state.lastInputValue[5])
}

PPM_NET_CB(input6CB) {
    AMUX_INPUT_CB_BODY(6, state.lastInputValue[6])
}

PPM_NET_CB(input7CB) {
    AMUX_INPUT_CB_BODY(7, state.lastInputValue[7])
}

captureInfo cap = { 0 };

static void controllerThread(void *user) {
    static double delay = 0.0;

    if (state.isRunningUnitTest) {
        bhmMessage("I", "KinetisCMP", "Enabled Capabilities: %s %s %s %s %s %s %s %s",
            bport1_ab_data.CR1.bits.EN ? "CMP" : "",
            bport1_ab_data.CR1.bits.SE ? "S" : "",
            bport1_ab_data.CR1.bits.WE ? "W" : "",
            bport1_ab_data.CR1.bits.OPE ? "OP" : "",
            bport1_ab_data.DACCR.bits.DACEN ? "DAC" : "",
            bport1_ab_data.SCR.bits.IER ? "IR" : "",
            bport1_ab_data.SCR.bits.IEF ? "IF" : "",
            bport1_ab_data.SCR.bits.DMAEN ? "DMA" : ""
        );
    }

    // Control thread, don't want it to end.
    for(;;){
        bhmWaitEvent(thState.start);
        cap.time = bhmGetCurrentTime();
        if (PSE_DIAG_LOW) {
            bhmMessage("I", "KinetasCMP", "Current time = %6.0f", cap.time);
        }
        getValue(&cap); // Consume the first line of the file.  It isn't used
        while ((cmp_in.next >= 0) && (bport1_ab_data.CR1.bits.EN)) {
            // DGV TODO: incorporate gain and offset in the setting of vin, a, and b
            Uns32 sample = cmp_in.extSample_value & 1;
            Uns32 vin = cmp_in.vin_value;
            Uns32 m = cmp_in.minus_value;
            Uns32 p = cmp_in.plus_value;
            if (state.isRunningUnitTest) {
                bhmMessage("I", "KinetisCMP", "%6.0f: sample = %d, vin = 0x%-8x, m = 0x%-8x, p = 0x%-8x",
                    bhmGetCurrentTime(), sample, vin, m, p);
            }

            ppmWriteNet(state.vrefmuxInputHandle[bport1_ab_data.DACCR.bits.VRSEL], vin);
            updateDacOutput();
            if (7 != bport1_ab_data.MUXCR.bits.MSEL) {
                ppmWriteNet(state.amuxInputHandle[bport1_ab_data.MUXCR.bits.MSEL], m);
            }
            if (7 != bport1_ab_data.MUXCR.bits.PSEL) {
                ppmWriteNet(state.amuxInputHandle[bport1_ab_data.MUXCR.bits.PSEL], p);
            }
            ppmWriteNet(handles.ExtSample, sample);

            delay = cmp_in.next;
            bhmWaitDelay(delay);
            getValue(&cap);
        }

        if (PSE_DIAG_LOW) {
            bhmMessage("I", "KinetisCMP", "Comparator %d out of stimulus", cmp_in.chNum);
        }
    }

};


// Attributes for configuring CMP from command line
//   configure_cr0
//   configure_cr1
//   configure_fpr
//   configure_scr
//   configure_muxcr
//   configure_daccr
// For each of these the lower 8-bits correspond to those in the underlying CMP
// register.


PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)

    bhmUns32ParamValue("cmpNumber", &(cmp_in.chNum));
    char stimAttrName[64];

    sprintf(stimAttrName, "stimFile");

    cmp_in.fp     = NULL;
    cmp_in.next   = -1;
    cmp_in.now    = 0;
    cmp_in.extSample_value  = 0;
    cmp_in.vin_value  = 0;
    cmp_in.minus_value  = 0;
    cmp_in.plus_value  = 0;

    if (bhmStringParamValue(stimAttrName, state.stimFile, sizeof(state.stimFile)) &&
        0 != strlen(state.stimFile))
    {
        if (PSE_DIAG_LOW) {
            bhmMessage("I", "KinetisCMP", "Using stimulus file = %s", state.stimFile);
        }
        cmp_in.fp = fopen(state.stimFile, "r");
        if (cmp_in.fp == NULL) {
            bhmMessage("F", "OPEN", "Cannot open stimFile%d=%s", cmp_in.chNum, state.stimFile);
        }

        //
        // initially assume we are SYNChronous unless we read a value indicating
        // otherwise
        //
        //DGV cmp_in.mode = SYNC;
        cmp_in.mode = ASYNC;
    } else {
        if (PSE_DIAG_LOW) {
            bhmMessage("I", "KinetisCMP", "No stimulus file specified");
        }
    }

    periphConstructor();

    // YOUR CODE HERE (post constructor)

    // Initialize the output nets
    updateDacOutput();
    updateCoutSocOutput(0);
    updateInterruptOutput(0);
    updateDmaReqOutput(0);
    updateCmpOPadOutput(0);

    // Setup indirection to handles to simplify code elsewhere
    state.amuxInputHandle[0] = handles.Input0;
    state.amuxInputHandle[1] = handles.Input1;
    state.amuxInputHandle[2] = handles.Input2;
    state.amuxInputHandle[3] = handles.Input3;
    state.amuxInputHandle[4] = handles.Input4;
    state.amuxInputHandle[5] = handles.Input5;
    state.amuxInputHandle[6] = handles.Input6;
    state.amuxInputHandle[7] = handles.Input7;

    state.vrefmuxInputHandle[0] = handles.Vin1;
    state.vrefmuxInputHandle[1] = handles.Vin2;

    // Configure the CMP from any given command line options
    Uns32 configBits;

    // CR0
    if (bhmUns32ParamValue("configure_cr0", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.CR0.bits.FILTER_CNT = (configBits & BPORT1_AB_CR0_FILTER_CNT) >> 4;
        bport1_ab_data.CR0.bits.HYSTCTR = configBits & BPORT1_AB_CR0_HYSTCTR;
        bhmMessage("I", "KinetisCMP", "configure_cr0 = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisCMP", "    FILTER_CNT = 0x%x\n", bport1_ab_data.CR0.bits.FILTER_CNT);
        bhmMessage("I", "KinetisCMP", "       HYSTCTR = 0x%x =>\n", bport1_ab_data.CR0.bits.HYSTCTR);
    }

    // CR1
    if (bhmUns32ParamValue("configure_cr1", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.CR1.bits.SE =  0 != (configBits & BPORT1_AB_CR1_SE);
        bport1_ab_data.CR1.bits.WE =  0 != (configBits & BPORT1_AB_CR1_WE);
        bport1_ab_data.CR1.bits.PMODE =  0 != (configBits & BPORT1_AB_CR1_PMODE);
        bport1_ab_data.CR1.bits.INV =  0 != (configBits & BPORT1_AB_CR1_INV);
        bport1_ab_data.CR1.bits.COS =  0 != (configBits & BPORT1_AB_CR1_COS);
        bport1_ab_data.CR1.bits.OPE =  0 != (configBits & BPORT1_AB_CR1_OPE);
        bport1_ab_data.CR1.bits.EN =  0 != (configBits & BPORT1_AB_CR1_EN);
        bhmMessage("I", "KinetisCMP", "configure_cr1 = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisCMP", "       SE = 0x%x\n", bport1_ab_data.CR1.bits.SE);
        bhmMessage("I", "KinetisCMP", "       WE = 0x%x\n", bport1_ab_data.CR1.bits.WE);
        bhmMessage("I", "KinetisCMP", "    PMODE = 0x%x\n", bport1_ab_data.CR1.bits.PMODE);
        bhmMessage("I", "KinetisCMP", "      INV = 0x%x\n", bport1_ab_data.CR1.bits.INV);
        bhmMessage("I", "KinetisCMP", "      COS = 0x%x\n", bport1_ab_data.CR1.bits.COS);
        bhmMessage("I", "KinetisCMP", "      OPE = 0x%x\n", bport1_ab_data.CR1.bits.OPE);
        bhmMessage("I", "KinetisCMP", "       EN = 0x%x\n", bport1_ab_data.CR1.bits.EN);
    }

    // FPR
    if (bhmUns32ParamValue("configure_fpr", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.FPR.bits.FILT_PER =  configBits & BPORT1_AB_FPR_FILT_PER;
        bhmMessage("I", "KinetisCMP", "configure_fpr = 0x%08x\n", configBits);
        bhmMessage("I", "KinetisCMP", "    FILT_PER = 0x%x\n", bport1_ab_data.FPR.bits.FILT_PER);
    }

    // SCR
    if (bhmUns32ParamValue("configure_scr", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.SCR.bits.DMAEN =  0 != (configBits & BPORT1_AB_SCR_DMAEN);
        bport1_ab_data.SCR.bits.IER =  0 != (configBits & BPORT1_AB_SCR_IER);
        bport1_ab_data.SCR.bits.IEF =  0 != (configBits & BPORT1_AB_SCR_IEF);
        bhmMessage("I", "KinetisCMP", "configure_scr = 0x%08x\n", configBits);
        bhmMessage("I", "KinetisCMP", "    DMAEN = 0x%x\n", bport1_ab_data.SCR.bits.DMAEN);
        bhmMessage("I", "KinetisCMP", "      IER = 0x%x\n", bport1_ab_data.SCR.bits.IER);
        bhmMessage("I", "KinetisCMP", "      IEF = 0x%x\n", bport1_ab_data.SCR.bits.IEF);
    }

    // DACCR
    if (bhmUns32ParamValue("configure_daccr", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.DACCR.bits.DACEN =  0 != (configBits & BPORT1_AB_DACCR_DACEN);
        bport1_ab_data.DACCR.bits.VRSEL =  0 != (configBits & BPORT1_AB_DACCR_VRSEL);
        bport1_ab_data.DACCR.bits.VOSEL =  configBits & BPORT1_AB_DACCR_VOSEL;
        bhmMessage("I", "KinetisCMP", "configure_daccr = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisCMP", "    DACEN = 0x%x\n", bport1_ab_data.DACCR.bits.DACEN);
        bhmMessage("I", "KinetisCMP", "    VRSEL = 0x%x\n", bport1_ab_data.DACCR.bits.VRSEL);
        bhmMessage("I", "KinetisCMP", "    VOSEL = 0x%x\n", bport1_ab_data.DACCR.bits.VOSEL);
    }

    // MUXCR
    if (bhmUns32ParamValue("configure_muxcr", &configBits)) {
        state.isRunningUnitTest = True;
        bport1_ab_data.MUXCR.bits.PSEL = (configBits & BPORT1_AB_MUXCR_PSEL) >> 3;
        bport1_ab_data.MUXCR.bits.MSEL = configBits & BPORT1_AB_MUXCR_MSEL;
        bhmMessage("I", "KinetisCMP", "configure_muxcr = 0x%08x =>\n", configBits);
        bhmMessage("I", "KinetisCMP", "    PSEL = 0x%x\n", bport1_ab_data.MUXCR.bits.PSEL);
        bhmMessage("I", "KinetisCMP", "    MSEL = 0x%x\n", bport1_ab_data.MUXCR.bits.MSEL);
    }

    // Start the Controller loop
    // At this point we don't need another thread of control.
    // controllerThreadHandle = bhmCreateThread(controllerThread, 0, "controllerThread", 0);
    char threadName[32];
    if (cmp_in.fp) {
        // Uncomment to get more debug output
        //state.isRunningUnitTest = True;
        sprintf(threadName, "cmp%dCtrl", cmp_in.chNum);
        thState.start = bhmCreateEvent();
        thState.thread = bhmCreateThread(controllerThread, (void *)0, threadName, 0);
        if (state.isRunningUnitTest && bport1_ab_data.CR1.bits.EN) {
           bhmWaitDelay(0);
           bhmTriggerEvent(thState.start);
        }
    }

}

PPM_DESTRUCTOR_CB(destructor) {
    if (cmp_in.fp) {
        fclose(cmp_in.fp);
    }
}



// Save / restore callbacks

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


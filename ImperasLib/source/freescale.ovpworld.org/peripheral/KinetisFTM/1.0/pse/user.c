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

#include "stdio.h"
#include "pse.igen.h"
#include "stimulus.h"

#define PREFIX "FTM"

struct {
    Bool isRunningUnitTest;
    char stimFile[NUM_CHANNELS][64];
    Bool readSetTOF;
    ppmNetValue currInterruptValue;
    Uns16       lastCount;
    ppmNetValue lastPhaseAValue;
    ppmNetValue lastPhaseBValue;
    double lastUpdateTime;
} state = {
    .isRunningUnitTest = False,
    .stimFile          = {{0}},
    .readSetTOF        = False,
    .currInterruptValue = 0,
    .lastCount         = 0,
    .lastPhaseAValue   = -1,
    .lastPhaseBValue   = -1,
    .lastUpdateTime    = 0.0
};

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
                bhmMessage("I", "Kinetis60FTM", "        setting interrupt = %d", (Uns32)state.currInterruptValue);
            }
            ppmWriteNet(handles.Interrupt, state.currInterruptValue);
        }
    }
}

static void updateCount(Int16 delta)
{
    Uns16 nextCount = bport1_ab_data.CNT.bits.COUNT + delta;
    if ( (bport1_ab_data.MOD.bits.MOD == bport1_ab_data.CNT.bits.COUNT) &&
         (state.lastCount != bport1_ab_data.CNT.bits.COUNT) &&  // don't overflow at startup
         (nextCount != state.lastCount) ) // Timer Overflow
    {
        bport1_ab_data.SC.bits.TOF = 1;
        state.readSetTOF = False;
        if (state.isRunningUnitTest) {
            bhmMessage("I", "Kinetis60FTM", "        setting TOF");
        }
        if (bport1_ab_data.SC.bits.TOIE) {
            updateInterruptOutput(1);
        }

       //DGV TODO: Should the setting on the next line only occur in Quadrature mode.
        bport1_ab_data.QDCTRL.bits.TOFDIR = delta > 0;
    }
    //DGV TODO: Should the setting on the next line only occur in Quadrature mode.
    bport1_ab_data.QDCTRL.bits.QUADIR = delta > 0;

    if (state.isRunningUnitTest) {
        bhmMessage("I", "Kinetis60FTM", "        count: %u->%u->%u, QUADIR=%d, TOF=%d, TOFDIR=%d",
            state.lastCount, bport1_ab_data.CNT.bits.COUNT, nextCount,
            bport1_ab_data.QDCTRL.bits.QUADIR,
            bport1_ab_data.SC.bits.TOF,
            bport1_ab_data.QDCTRL.bits.TOFDIR
        );
    }

    state.lastCount = bport1_ab_data.CNT.bits.COUNT;
    bport1_ab_data.CNT.bits.COUNT = nextCount;
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(readSC) {
    // YOUR CODE HERE (readSC)
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", "KinetisCMP", "Reading ...");
    }
    if (bport1_ab_data.SC.bits.TOF) {
        state.readSetTOF = True;
    }
    return bport1_ab_data.SC.value;
}

PPM_REG_WRITE_CB(writeSC) {
    // YOUR CODE HERE (writeSCR)
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", "KinetisCMP", "Write SC 0x%x", data);
    }
    *(Uns8*)user = data & 0x7f;
    if ((state.readSetTOF) && (0 == (data & 0x80))) {
        bport1_ab_data.SC.bits.TOF = 0;
    }
}


//DGV TODO: Per section 42.4.25 of K60 Sub-Family Reference Manual, Rev. 2, Dec 2011,
//          "Each one of input signals phase A and B has a filter that is equivalent
//          to the filter used in the channels input."  Looked briefly but couldn't
//          find a description of this filtering so ignoring filtering for now.
#define BPORT1_AB_FILTER_CH0FVAL   0xf
#define BPORT1_AB_FILTER_CH1FVAL   (0xf << 4)

// Per section 42.4.25 of K60 Sub-Family Reference Manual, Rev. 2, Dec 2011,
// "the FTM counter is cloked by the phase A and B input signals when quadrature
// decoder mode is selected.   Therefore it is expected that the quadrature decoder
// be used only with the FTM channels in input capture or output ompare models.
// DGV TODO:  Add a check for this.

static Bool isTriggerEdge(ppmNetValue phaseInput, Bool positivePolarity)
{
  return (1 & phaseInput) ? positivePolarity : !positivePolarity;
}

static Bool isIncrementingLevel(ppmNetValue phaseInput, Bool positivePolarity)
{
  return (1 & phaseInput) ? positivePolarity : !positivePolarity;
}


// The code below cannot handle simultaneous edges on phaseA and phaseB because the
// associated callback is activated at the moment the edge occurs.  Whichever
// transition happens to occur first is processed first.  The callback has no way of
// knowing that the signal for the other phase will also transition at the current
// time.  The behavior is NOT like a Verilog non-blocking assignment where all updates
// occur together at the end of the time step. Consequently, the stimulus should be
// crafted to avoid this situation.
// DGV TODO: Characterize how things will behave when there are simultaneous edges.

PPM_NET_CB(phaseACB) {
    double currentTime = bhmGetCurrentTime();
//    bhmMessage("I", "Kinetis60FTM", "%6.0f: phaseACB() reports value %d",
//      currentTime, value);
    if ((value != state.lastPhaseAValue) && (currentTime > state.lastUpdateTime)) {
        state.lastUpdateTime = currentTime;

        ppmNetValue phaseA_value = value;
        ppmNetValue phaseB_value = ppmReadNet(handles.PhaseB);
//        bhmMessage("I", "Kinetis60FTM", "%6.0f: phaseACB() detects value change to %d (was %d)",
//          currentTime, value, ppmReadNet(handles.PhaseA));
//      ppmNetValue phaseA_value = ppmReadNet(handles.PhaseA);
        // count and direction encoding mode
        if (1 == bport1_ab_data.QDCTRL.bits.QUADMODE) {
           if (isTriggerEdge(phaseA_value, 0 == bport1_ab_data.QDCTRL.bits.PHAPOL)) {
               bhmMessage("I", "Kinetis60FTM", "        phaseA %s, %s per phaseB",
                   (0 == bport1_ab_data.QDCTRL.bits.PHAPOL) ? "rising" : "falling",
                   isIncrementingLevel(phaseB_value, 0 == bport1_ab_data.QDCTRL.bits.PHBPOL) ?
                   "incrementing" : "decrementing");
               if (isIncrementingLevel(phaseB_value, 0 == bport1_ab_data.QDCTRL.bits.PHBPOL)) {
                  updateCount(+1);
               } else {
                  updateCount(-1);
               }
           }
        }

        // phase A and phase B encoding mode
        else {
            if (isTriggerEdge(phaseA_value, 0 == bport1_ab_data.QDCTRL.bits.PHAPOL)) {
               bhmMessage("I", "Kinetis60FTM", "        phaseA %s, %s per phaseB",
                   (0 == bport1_ab_data.QDCTRL.bits.PHAPOL) ? "rising" : "falling",
                   isIncrementingLevel(!phaseB_value, 0 == bport1_ab_data.QDCTRL.bits.PHBPOL) ?
                   "incrementing" : "decrementing");
               if (isIncrementingLevel(!phaseB_value, 0 == bport1_ab_data.QDCTRL.bits.PHBPOL)) {
                  updateCount(+1);
               } else {
                  updateCount(-1);
               }
            } else {
               bhmMessage("I", "Kinetis60FTM", " NT     phaseA %s, %s per phaseB",
                   (0 == bport1_ab_data.QDCTRL.bits.PHAPOL) ? "falling" : "rising",
                   isIncrementingLevel(phaseB_value, 0 == bport1_ab_data.QDCTRL.bits.PHBPOL) ?
                   "incrementing" : "decrementing");
               if (isIncrementingLevel(phaseB_value, 0 == bport1_ab_data.QDCTRL.bits.PHBPOL)) {
                  updateCount(+1);
               } else {
                  updateCount(-1);
               }
            }
        }
    } else {
//       bhmMessage("I", "Kinetis60FTM", "%4.0f: phaseACB() doing nothing; update already done",
//      currentTime);
    }
    state.lastPhaseAValue = value;
}

PPM_NET_CB(phaseBCB) {
    double currentTime = bhmGetCurrentTime();
//    bhmMessage("I", "Kinetis60FTM", "%6.0f: phaseBCB() reports value %d; phaseA is %d",
//      bhmGetCurrentTime(), value, ppmReadNet(handles.PhaseA));
    if ((value != state.lastPhaseBValue) && (currentTime > state.lastUpdateTime)) {
        state.lastUpdateTime = currentTime;

        ppmNetValue phaseA_value = ppmReadNet(handles.PhaseA);
        ppmNetValue phaseB_value = value;

        // count and direction encoding mode
        if (1 == bport1_ab_data.QDCTRL.bits.QUADMODE) {
            // phase B input cannot trigger counting so no need to
            // read the new value; it will be read when phase A transitions
        }

        // phase A and phase B encoding mode
        else {
            if (isTriggerEdge(phaseB_value, 0 == bport1_ab_data.QDCTRL.bits.PHBPOL)) {
               bhmMessage("I", "Kinetis60FTM", "        phaseB %s, %s per phaseA",
                   (0 == bport1_ab_data.QDCTRL.bits.PHBPOL) ? "rising" : "falling",
                   isIncrementingLevel(phaseA_value, 0 == bport1_ab_data.QDCTRL.bits.PHAPOL) ?
                   "incrementing" : "decrementing");
               if (isIncrementingLevel(phaseA_value, 0 == bport1_ab_data.QDCTRL.bits.PHAPOL)) {
                  updateCount(+1);
               } else {
                  updateCount(-1);
               }
            } else {
               bhmMessage("I", "Kinetis60FTM", " NT     phaseB %s, %s per phaseA",
                   (0 == bport1_ab_data.QDCTRL.bits.PHBPOL) ? "falling" : "rising",
                   isIncrementingLevel(!phaseA_value, 0 == bport1_ab_data.QDCTRL.bits.PHAPOL) ?
                   "incrementing" : "decrementing");
               if (isIncrementingLevel(!phaseA_value, 0 == bport1_ab_data.QDCTRL.bits.PHAPOL)) {
                  updateCount(+1);
               } else {
                  updateCount(-1);
               }
            }
        }
    } else {
//       bhmMessage("I", "Kinetis60FTM", "%4.0f: phaseBCB() doing nothing; update already done",
//      currentTime);
    }
    state.lastPhaseBValue = value;
}

captureInfo cap = { 0 };

static void controllerThread(void *user) {
    Int32 ch = 0;
    static double delay = 0.0;
    int i;

    bhmMessage("I", "Kinetis60FTM", "%s encoding mode.  Polarity (A,B)= (%d,%d)",
        (1 == bport1_ab_data.QDCTRL.bits.QUADMODE) ?
        "Count and Direction" : "PhaseA and PhaseB",
        bport1_ab_data.QDCTRL.bits.PHAPOL, bport1_ab_data.QDCTRL.bits.PHBPOL);

    cap.time = bhmGetCurrentTime();
    getValue(&cap); // Consume the first line of the file.  It isn't used
    // while (1) {
    for (i = 0; i < 32; i++) {
        Uns32 a = ftm_in[ch].phaseA_value & 1;
        Uns32 b = ftm_in[ch].phaseB_value & 1;
        bhmMessage("I", "Kinetis60FTM", "%6.0f: phaseA = %d, phaseB = %d, count = %d",
          bhmGetCurrentTime(), a, b, bport1_ab_data.CNT.bits.COUNT);
        ppmWriteNet(handles.PhaseA, a);
        ppmWriteNet(handles.PhaseB, b);
//        bhmMessage("I", "Kinetis60FTM", "%6.0f: (post write) phaseA = %d, phaseB = %d",
//        bhmGetCurrentTime(), ppmReadNet(handles.PhaseA), ppmReadNet(handles.PhaseB));
//        bhmWaitDelay(0);
//        bhmMessage("I", "Kinetis60FTM", "%6.0f: (post delay) phaseA = %d, phaseB = %d",
//        bhmGetCurrentTime(), ppmReadNet(handles.PhaseA), ppmReadNet(handles.PhaseB));
//      phaseACB(a, NULL);
//      phaseBCB(b, NULL);
        delay = ftm_in[ch].next;
        bhmWaitDelay(delay);
        getValue(&cap);
//        bhmMessage("I", "Kinetis60FTM", "%4.0f: phaseA = 0x%03x, phaseB = 0x%03x",
//            bhmGetCurrentTime(), ftm_in[ch].phaseA_value, ftm_in[ch].phaseB_value);
//        bhmMessage("I", "Kinetis60FTM", "%4.0f: phaseA = %d, phaseB = %d",
//            bhmGetCurrentTime(), ftm_in[ch].phaseA_value & 1, ftm_in[ch].phaseB_value & 1);
        // DGV TODO: Note that the ppmWriteNet() calls are not triggering the callbacks,
        //           so they are being explictly called for now.  Determine if there is a
        //           better way to handle this?
    }
};


// Bits for configuring FTM from command line

#define TIMER_OVERFLOW_IE   0x00000010
#define QUADRATURE_MODE     0x00000008
#define COUNT_DIRECTION_ENC 0x00000004  // Otherwise PhaseA and PhaseB Encoding
#define PHASEA_POLARITY     0x00000002  // Indicates inverted polarity of PhaseA
#define PHASEB_POLARITY     0x00000001  // Indicates inverted polarity of PhaseB

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)

    // Setup the channel stimulus
    Int32 ch;
    char stimAttrName[64];
    for (ch=0; ch < NUM_CHANNELS; ch++) {
        sprintf(stimAttrName, "stimFile%d", ch);
        ftm_in[ch].fp     = NULL;
        ftm_in[ch].next   = -1;
        ftm_in[ch].now    = 0;
        ftm_in[ch].phaseA_value  = 0;
        ftm_in[ch].phaseB_value  = 0;
        if (bhmStringParamValue(stimAttrName, state.stimFile[ch], sizeof(state.stimFile[ch]))) {

            bhmMessage("I", "Kinetis60FTM", "%s = %s", stimAttrName, state.stimFile[ch]);
            ftm_in[ch].fp = fopen(state.stimFile[ch], "r");
            if (ftm_in[ch].fp == NULL) {
                bhmMessage("F", "OPEN", "Cannot open stimFile%d=%s", ch, state.stimFile[ch]);
            }

            //
            // initially assume we are SYNChronous unless we read a value indicating
            // otherwise
            //
            //DGV ftm_in[ch].mode = SYNC;
            ftm_in[ch].mode = ASYNC;
        }
    }

    // Configure the FTM from a command line option if given
    Uns32 configBits;
    if (bhmUns32ParamValue("configure", &configBits)) {
        bhmMessage("I", "Kinetis60FTM", "configure = 0x%08x =>\n  %s, %s Encoding, PhaseA Polarity = %s, PhaseB Polarity = %s, TOIE = %d",
           configBits,
           (configBits & QUADRATURE_MODE) ? "Quadrature Mode" : "Other Mode",
           !(configBits & QUADRATURE_MODE) ? "NA" :
             (configBits & COUNT_DIRECTION_ENC) ?  "Count and Direction" : "PhaseA and PhaseB",
           configBits & PHASEA_POLARITY ? "Inverted" : "Normal",
           configBits & PHASEB_POLARITY ? "Inverted" : "Normal",
           configBits & TIMER_OVERFLOW_IE ? 1 : 0);
        state.isRunningUnitTest = True;
    }

    periphConstructor();
//  PSE seems to be a 32-bit environment
//  bhmMessage("I", "Kientis60FTM", "handles.PhaseA = 0x%016llX, handles.PhaseB = 0x%016llx",
//      (long long unsigned int) handles.PhaseA, (long long unsigned int) handles.PhaseB);
//  bhmMessage("I", "Kientis60FTM", "handles.PhaseA = 0x%08x, handles.PhaseB = 0x%08x",
//      (unsigned int) handles.PhaseA, (unsigned int) handles.PhaseB);
    // YOUR CODE HERE (post constructor)

    // Initialize the output nets
    updateInterruptOutput(0);

    if (configBits & QUADRATURE_MODE) {
        bport1_ab_data.QDCTRL.bits.QUADEN = 1;
        bport1_ab_data.MODE.bits.FTMEN = 1;
        if (configBits & COUNT_DIRECTION_ENC) {
            bport1_ab_data.QDCTRL.bits.QUADMODE = 1;
        } else {
            bport1_ab_data.QDCTRL.bits.QUADMODE = 0;
        }
        if (configBits & PHASEA_POLARITY) {
            bport1_ab_data.QDCTRL.bits.PHAPOL = 1;
        } else {
            bport1_ab_data.QDCTRL.bits.PHAPOL = 0;
        }
        if (configBits & PHASEB_POLARITY) {
            bport1_ab_data.QDCTRL.bits.PHBPOL = 1;
        } else {
            bport1_ab_data.QDCTRL.bits.PHBPOL = 0;
        }
    } else {
        bport1_ab_data.QDCTRL.bits.QUADEN = 0;
    }
    bport1_ab_data.SC.bits.TOIE = configBits & TIMER_OVERFLOW_IE ? 1 : 0;

    // Start the Controller loop
    // At this point we don't need another thread of control.
    // controllerThreadHandle = bhmCreateThread(controllerThread, 0, "controllerThread", 0);
    if (ftm_in[0].fp) {
        controllerThread(NULL);
    }
}

PPM_DESTRUCTOR_CB(destructor) {
    Int32 ch;
    for (ch=0; ch<NUM_CHANNELS; ch++) {
        //
        // Read before close
        //
        if (ftm_in[ch].fp) {
            fclose(ftm_in[ch].fp);
        }
    }
}



// Save / restore callbacks

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


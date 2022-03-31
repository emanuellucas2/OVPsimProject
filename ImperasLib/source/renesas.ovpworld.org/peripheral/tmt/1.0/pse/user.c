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
//                          Mon Sep 17 14:54:10 2012
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#ifndef PSE_DIAG_HIGH
#define PSE_DIAG_HIGH    (diagnosticLevel >= 3)
#define PSE_DIAG_MEDIUM  (diagnosticLevel >= 2)
#define PSE_DIAG_LOW     (diagnosticLevel >= 1)
#endif

#define PREFIX "TMT"

typedef struct outputPinS {
    const char  *name;
    ppmNetHandle netP;
    Uns32        value;
} outputPin, *outputPinP;

static outputPin TOT0     = { "TOT0"    , 0, 0 };
static outputPin TOT1     = { "TOT1"    , 0, 0 };

static outputPin TTTTO0   = { "TTTTO0"  , 0, 0 };
static outputPin TTTT01   = { "TTTT01"  , 0, 0 };
static outputPin TTTICC0  = { "TTTICC0" , 0, 0 };
static outputPin TTTICC1  = { "TTTICC1" , 0, 0 };
static outputPin TTTEQC0  = { "TTTEQC0" , 0, 0 };
static outputPin TTTEQC1  = { "TTTEQC1" , 0, 0 };

static outputPin INTTTCC0 = { "INTTTCC0", 0, 0 };
static outputPin INTTTCC1 = { "INTTTCC1", 0, 0 };
static outputPin INTTTOV  = { "INTTTOV" , 0, 0 };
static outputPin INTTTEC  = { "INTTTEC" , 0, 0 };

//static struct {
//    Uns32 TIT0;
//    Uns32 TIT1;
//    Uns32 TEVTT;
//    Uns32 TTRGT;
//    Uns32 TENCT0;
//    Uns32 TENCT1;
//    Uns32 TECRT;
//
//    Uns32 TTTTI0;
//    Uns32 TTTTI1;
//    Uns32 TTTENC0;
//    Uns32 TTTENC1;
//    Uns32 TTTTRG;
//    Uns32 TTTEVT;
//    Uns32 TTTECR;
//} inputPin;

// Indicate if we are running as plant model input
static Bool plantModelEnabled = False;
//
// Plant model duty and cycle update
//
FUNCTOHOST(void, interceptPlantModelDuty, Uns32 ccr0, Uns32 ccr1, Uns32 rate)

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
    doWriteNet(pin, 1);
    doWriteNet(pin, 0);
}
static void toggleNet(outputPinP pin) {
    doWriteNet(pin, !pin->value);
}

static Uns32  PCLK[10];
static double PCLKS;     // This is the selector clock
static double microSecCB; // Selected timer interval

static Uns32 CCR_Buffer[2];
struct {
    Uns32  value;   // Current Value of register
    double time;    // Time at which value was set
    Uns32  next;    // value of register at next calculated event
} cntInfo;

static double ticksToTime(Uns32 ticks) {
    return (microSecCB * ticks);
}
static Uns32 timeToTicks(double time) {
    return (time / microSecCB);
}

static bhmThreadHandle timerThreadHandle = 0;
static double microSecondDelay;

static void evaluateEvent();

static void timerThread(void *user) {
    while (1) {
        bhmWaitDelay(microSecondDelay);
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_EXP", "Timer Expired %f", bhmGetCurrentTime());

        //
        // OK, we have timed out, question is why ?
        //
        evaluateEvent();
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_RUN", "Re-Start Timer(%f) %f",  microSecondDelay, bhmGetCurrentTime());
    }
}

static void stopTimer() {
    if (timerThreadHandle) {
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_STP", "Stop Timer %f", bhmGetCurrentTime());
        bhmDeleteThread(timerThreadHandle);
        timerThreadHandle = 0;
    }
}

static void startTimer(double delay) {
    stopTimer();
    microSecondDelay = delay;
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_STRT", "Start Timer(%f) %f",  microSecondDelay, bhmGetCurrentTime());
    timerThreadHandle = bhmCreateThread(timerThread, 0, "timer", 0);
}

//
// Determine number of clocks to next event, or counter overflow
//
static Uns32 minOf (Uns32 a, Uns32 b) {
    Uns32 value;
    if (a > b) {
        value = b;
    } else {
        value = a;
    }
    return value;

}
static Uns32 calcDelay(Uns32 t0, Uns32 cnt) {
    Uns32 value;
    if (cnt >= t0) {
        value = (t0 + 0x10000) - cnt;
    } else {
        value = t0 - cnt;
    }
    return value;
}
static Uns32 updateCntInfo (Uns16 CNT) {

    cntInfo.value = CNT;
    cntInfo.time  = bhmGetCurrentTime();

    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_UCNTI", "updateCntInfo: CNT=0x%04x", cntInfo.value);
    //
    // Overflow count difference
    //
    Uns32 ticks = calcDelay(0xffff, (Uns32)cntInfo.value);

    //
    // CCR0..5
    //
    ticks = minOf(ticks, calcDelay(CCR_Buffer[0], (Uns32)cntInfo.value));
    ticks = minOf(ticks, calcDelay(CCR_Buffer[1], (Uns32)cntInfo.value));

    cntInfo.next = (cntInfo.value + ticks) & 0xffff;
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_UCNTI", "updateCntInfo: nextCNT=0x%04x", cntInfo.next);

    return ticks;
}

static void genSignalsFromCCR() {
    //
    // CCR0:1 match
    //
    if (cntInfo.next == CCR_Buffer[0]) {
        posPulseNet(&INTTTCC0);
        toggleNet(&TOT0);
    }
    if (cntInfo.next == CCR_Buffer[1]) {
        posPulseNet(&INTTTCC1);
        toggleNet(&TOT1);
    }
}
static void evaluateEvent () {
    //
    // Evaluate the current event based upon the Mode
    //
    switch (TMTP0_reg0_data.CTL1.bits.MD) {
    case 0:
        //
        // Interval Timer Mode
        // we must be here for one of the following reasons
        // 1. Counter matches CCR0 - (reset to 0)
        // 2. Counter matches CCR1:5 (generate interrupt)
        genSignalsFromCCR();
        if (cntInfo.next == CCR_Buffer[0]) {
            cntInfo.next = 0;
        }
        microSecondDelay = ticksToTime(updateCntInfo(cntInfo.next));
        break;

    case 1:
        //
        // External Event Count Mode
        //
        // If we are here we have had a rising edge on the TEVTS pin
        cntInfo.value = (cntInfo.value + 1) & 0xffff;
        genSignalsFromCCR();
        if (cntInfo.value == CCR_Buffer[0]) {
            cntInfo.value = 0;
        }
        break;

    case 2:
        //
        // External Trigger Pulse Output Mode
        //
        bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: External Trigger Pulse Output");
        break;
    case 3:
        //
        // One-Shot Pulse Mode
        //
        bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: One-Shot Pulse");
        break;
    case 4:
        //
        // PWM Mode
        //
        if(plantModelEnabled) {
            ; // do nothing we are only interested in values of CCR registers
        } else {
            bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: PWM");
        }
        break;
    case 5:
        //
        // Free-Running Mode
        // This mode generates an Overflow INTTSOV
        //
        genSignalsFromCCR();
        // Timer simply overflows in this mode
        if (cntInfo.next == 0xffff) {
            posPulseNet(&INTTTOV);
            TMTP0_reg0_data.OPT0.bits.OVF = 1;
            cntInfo.next = 0;
        }
        microSecondDelay = ticksToTime(updateCntInfo(cntInfo.next));
        break;
    case 6:
        //
        // Pulse Width Measurement Mode
        //
        bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Pulse Width Measurement");
        break;
    case 7:
        //
        // Triangular-Wave PWM Mode
        //
        bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Triangular-Wave PWM");
        break;
    case 8:
        //
        // Encoder Compare Mode
        //
        bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Encoder Compare Mode");
        break;
    case 9:
        //
        // Encoder Capture Mode
        //
        bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Encoder Capture Mode");
        break;
    case 10:
        //
        // Encoder Capture Compare Mode
        //
        bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Encoder Capture Compare Mode");
        break;
    case 11:
        //
        // Offset Trigger Generation Mode
        //
        bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Offset Trigger Generation Mode");
        break;
    default:
        //
        // all else ...
        //
        bhmMessage("W", PREFIX"_CTL1", "Illegal MODE CTL1/MD=0x%1x", TMTP0_reg0_data.CTL1.bits.MD);
        break;
    }
}

static void bufferReloadCCR() {
    CCR_Buffer[0] = TMTP0_reg1_data.CCR0.value;
    CCR_Buffer[1] = TMTP0_reg1_data.CCR1.value;
}

//
// Called whenever timer control changes
//
void update_timer () {
    Uns32 ticks;

    static Uns8 CEprev = 0;
    Uns8 CE = TMTP0_reg0_data.CTL0.bits.CE;

    //
    // Calculate the microSecCB
    //
    if (TMTP0_reg0_data.CTL1.bits.EEE) {
        //
        // External clock
        //
    } else {
        //
        // Internal Clock
        //
        PCLKS = PCLK[TMTP0_reg0_data.CTL0.bits.CKS];
        if (TMTP0_reg0_data.CTL0.bits.CKS == 6) PCLKS = PCLK[7];
        if (TMTP0_reg0_data.CTL0.bits.CKS == 7) PCLKS = PCLK[9];
        microSecCB = (1 / PCLKS) * 1000000;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_EVCB", "PCLKS=%f ClockInterval=%fus", PCLKS, microSecCB);
    }

    if (CE) {
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_EVCB", "Counter Enabled");

        //
        // The reloading of these differs it is dependent upon the mode
        // or initial loading CE 0->1
        //
        if (CEprev==0 && CE==1) {
            bufferReloadCCR();
        }

        //
        // Determine the mode of operation
        //
        switch (TMTP0_reg0_data.CTL1.bits.MD) {
        case 0:
            //
            // Interval Timer Mode
            // This mode performs a compare between the CNT register and the CCR0
            // An interrupt is also generated on a match between CCR1-CCR4
            //
            if (CEprev==0 && CE==1) {
                doWriteNet(&TOT0, 0);
                doWriteNet(&TOT1, 0);
            }
            bufferReloadCCR();
            ticks = updateCntInfo(0);
            if (PSE_DIAG_HIGH) bhmMessage("W", PREFIX"_EVCB", "Interval Timer Mode ticks=%d", ticks);
            startTimer(ticksToTime(ticks));
            break;
        case 1:
            //
            // External Event Count Mode
            // In order to implement this we need to propagate the top level
            // Pins in order to be driven
            //
            bufferReloadCCR();
            if (PSE_DIAG_HIGH) bhmMessage("W", PREFIX"_CTL1", "Untested MODE: External Event Count");
            break;
        case 2:
            //
            // External Trigger Pulse Output Mode
            //
            bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: External Trigger Pulse Output");
            break;
        case 3:
            //
            // One-Shot Pulse Mode
            //
            bufferReloadCCR();
            bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: One-Shot Pulse");
            break;
        case 4:
            //
            // PWM Mode
            //
            //
            // If we are operating as plant model control and counting is enabled
            //
            if (plantModelEnabled) {

        Uns32 nanoSecCB = microSecCB * 1000;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_TTDCCLOG", "CCR0.value:0x%04x CCR1.value:0x%04x  nanoSecCB:%dns",
                          TMTP0_reg1_data.CCR0.value, TMTP0_reg1_data.CCR1.value, nanoSecCB);
                interceptPlantModelDuty(TMTP0_reg1_data.CCR0.value,
                                        TMTP0_reg1_data.CCR1.value,
                                        nanoSecCB);
            } else {
                bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: PWM");
            }
            break;
        case 5:
            //
            // Free-Running Mode
            // This mode generates an Overflow INTTSOV
            // Also generates Compare interrupts and TOS outputs
            //
            if (CEprev==0 && CE==1) {
                doWriteNet(&TOT0, 0);
                doWriteNet(&TOT1, 0);
            }
            bufferReloadCCR();
            ticks = updateCntInfo(0);
            if (PSE_DIAG_HIGH) bhmMessage("W", PREFIX"_EVCB", "Free-Running Mode ticks=%d", ticks);
            startTimer(ticksToTime(ticks));
            break;
        case 6:
            //
            // Pulse Width Measurement Mode
            //
            bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Pulse Width Measurement");
            break;
        case 7:
            //
            // Triangular-Wave PWM Mode
            //
            bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Triangular-Wave PWM");
            break;
        case 8:
            //
            // Encoder Compare Mode
            //
            bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Encoder Compare Mode");
            break;
        case 9:
            //
            // Encoder Capture Mode
            //
            bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Encoder Capture Mode");
            break;
        case 10:
            //
            // Encoder Capture Compare Mode
            //
            bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Encoder Capture Compare Mode");
            break;
        case 11:
            //
            // Offset Trigger Generation Mode
            //
            bhmMessage("W", PREFIX"_CTL1", "Unsupported MODE: Offset Trigger Generation Mode");
            break;
        default:
            //
            // all else ...
            //
            bhmMessage("W", PREFIX"_CTL1", "Illegal MODE CTL1/MD=0x%1x", TMTP0_reg0_data.CTL1.bits.MD);
            break;
        }

    } else {
        //
        // This is the initialization bit
        //
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_EVCB", "Counter Disabled");

        //
        // Clear OVF flag and all Flags in OPT6
        // CCR0..5, PAT0,1, DTC0,1
        //
//        TMTP0_reg2_data.OPT0.bits.OVF = 0;
//        TMTP0_reg3_data.OPT6.value    = 0;
//        TMTP0_reg3_data.PAT0.value    = 0;
//        TMTP0_reg3_data.PAT1.value    = 0;
//        TMTP0_reg3_data.DTC0.value    = 0;
//        TMTP0_reg3_data.DTC1.value    = 0;
        cntInfo.value                 = 0;
        cntInfo.time                  = bhmGetCurrentTime();

        stopTimer();
    }

    CEprev = CE;
}

//
// Update the count register for reading
//
void update_count () {
    //
    // Get the current time, then work out how much further the counter
    // Would have progressed need to ensure it has been and remained enabled
    //
    Uns32 cnt = cntInfo.value;
    if (TMTP0_reg0_data.CTL0.bits.CE) {
        double time = bhmGetCurrentTime();
        double diff = time - cntInfo.time;
        Uns32 ticks = timeToTicks(diff);
        cnt = (cntInfo.value + ticks) & 0xffff;
    }
    TMTP0_reg1_data.CNT.value = cnt;
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NET_CB(P_TECRT) {
    // YOUR CODE HERE (P_TECRT)
}

PPM_NET_CB(P_TENCT0) {
    // YOUR CODE HERE (P_TENCT0)
}

PPM_NET_CB(P_TENCT1) {
    // YOUR CODE HERE (P_TENCT1)
}

PPM_NET_CB(P_TEVTT) {
    // YOUR CODE HERE (P_TEVTT)
}

PPM_NET_CB(P_TIT0) {
    // YOUR CODE HERE (P_TIT0)
}

PPM_NET_CB(P_TIT1) {
    // YOUR CODE HERE (P_TIT1)
}

PPM_NET_CB(P_TTRGT) {
    // YOUR CODE HERE (P_TTRGT)
}

PPM_NET_CB(P_TTTECR) {
    // YOUR CODE HERE (P_TTTECR)
}

PPM_NET_CB(P_TTTENC0) {
    // YOUR CODE HERE (P_TTTENC0)
}

PPM_NET_CB(P_TTTENC1) {
    // YOUR CODE HERE (P_TTTENC1)
}

PPM_NET_CB(P_TTTEVT) {
    // YOUR CODE HERE (P_TTTEVT)
}

PPM_NET_CB(P_TTTTI0) {
    // YOUR CODE HERE (P_TTTTI0)
}

PPM_NET_CB(P_TTTTI1) {
    // YOUR CODE HERE (P_TTTTI1)
}

PPM_NET_CB(P_TTTTRG) {
    // YOUR CODE HERE (P_TTTTRG)
}

PPM_REG_READ_CB(readCNT) {
    update_count();

    return *(Uns16*)user;
}

PPM_REG_WRITE_CB(writeCCR0) {
    *(Uns16*)user = (*(Uns16*)user & 0x0) | (data & 0xffff);

    //
    // Need to update timer in case a different event time is required
    //
    update_timer ();
}

PPM_REG_WRITE_CB(writeCCR1) {
    *(Uns16*)user = (*(Uns16*)user & 0x0) | (data & 0xffff);

    //
    // Need to update timer in case a different event time is required
    //
    update_timer ();
}

PPM_REG_WRITE_CB(writeCTL0) {
    //
    // Check legal values
    //
    if (data & 0x78) {
        bhmMessage("W", PREFIX"_WCTL0", "Register CTL0 Illegal value 0x%02x\n", data);
    }

    //
    // Get previous values of CE and CKS
    //
    Uns8 CE  = TMTP0_reg0_data.CTL0.bits.CE;
    Uns8 CKS = TMTP0_reg0_data.CTL0.bits.CKS;

    *(Uns8*)user = (*(Uns8*)user & 0x78) | (data & 0x87);

    //
    // Ensure the CE bit was zero if changing any other bits
    //
    if (CE==1 && (CKS != TMTP0_reg0_data.CTL0.bits.CKS)) {
        bhmMessage("W", PREFIX"_WCTL0", "Register CTL0 invalid to change CKS while CE==1, setting ignored\n");
        TMTP0_reg0_data.CTL0.bits.CKS = CKS;
    }

    update_timer();
}

PPM_REG_WRITE_CB(writeCTL1) {
    //
    // Check legal values
    //
    if (data & 0x90) {
        bhmMessage("W", PREFIX"_WCTL1", "Register CTL1 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0x90) | (data & 0x6f);

    update_timer();
}

PPM_REG_WRITE_CB(writeCTL2) {
    //
    // Check legal values
    //
    if (data & 0x60) {
        bhmMessage("W", PREFIX"_WCTL2", "Register CTL2 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0x60) | (data & 0x9f);
}

PPM_REG_WRITE_CB(writeIOC0) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", PREFIX"_WIOC0", "Register IOC0 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);
}

PPM_REG_WRITE_CB(writeIOC1) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", PREFIX"_WIOC1", "Register IOC1 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);
}

PPM_REG_WRITE_CB(writeIOC2) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", PREFIX"_WIOC2", "Register IOC2 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);
}

PPM_REG_WRITE_CB(writeIOC3) {
    *(Uns8*)user = (*(Uns8*)user & 0x0) | (data & 0xff);
}

PPM_REG_WRITE_CB(writeOPT0) {
    //
    // Check legal values
    //
    if (data & 0xce) {
        bhmMessage("W", PREFIX"_WOPT0", "Register OPT0 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xce) | (data & 0x31);
}

PPM_REG_WRITE_CB(writeOPT1) {
    //
    // Check legal values
    //
    if (data & 0xf8) {
        bhmMessage("W", PREFIX"_WOPT1", "Register OPT1 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf8) | (data & 0x7);
}

PPM_REG_WRITE_CB(writeOPT2) {
    //
    // Check legal values
    //
    if (data & 0xfe) {
        bhmMessage("W", PREFIX"_WOPT2", "Register OPT2 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xfe) | (data & 0x1);
}

PPM_REG_WRITE_CB(writeTCW) {
    *(Uns16*)user = (*(Uns16*)user & 0x0) | (data & 0xffff);
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    TOT0.netP     = handles.TOT0;
    TOT1.netP     = handles.TOT1;
    TTTTO0.netP   = handles.TTTTO0;
    TTTT01.netP   = handles.TTTT01;
    TTTICC0.netP  = handles.TTTICC0;
    TTTICC1.netP  = handles.TTTICC1;
    TTTEQC0.netP  = handles.TTTEQC0;
    TTTEQC1.netP  = handles.TTTEQC1;
    INTTTCC0.netP = handles.INTTTCC0;
    INTTTCC1.netP = handles.INTTTCC1;
    INTTTOV.netP  = handles.INTTTOV;
    INTTTEC.netP  = handles.INTTTEC;

    //
    // Get the PCLKx attributes
    //
    bhmUns32ParamValue("PCLK0", &PCLK[0]);
    bhmUns32ParamValue("PCLK1", &PCLK[1]);
    bhmUns32ParamValue("PCLK2", &PCLK[2]);
    bhmUns32ParamValue("PCLK3", &PCLK[3]);
    bhmUns32ParamValue("PCLK4", &PCLK[4]);
    bhmUns32ParamValue("PCLK5", &PCLK[5]);
    bhmUns32ParamValue("PCLK7", &PCLK[7]);
    bhmUns32ParamValue("PCLK9", &PCLK[9]);

    bhmBoolParamValue("PlantModelPWMMode", &plantModelEnabled);
    if (plantModelEnabled && PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_PE", "Plant Model PWM Mode Enabled");
    }

    update_timer();

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


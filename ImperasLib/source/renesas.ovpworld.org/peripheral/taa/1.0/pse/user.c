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
//                          Fri Sep 14 17:08:12 2012
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

// Is this model being used in PWM mode to control duty cycle?
Bool plantModelEnabled = False;

typedef struct outputPinS {
    const char  *name;
    ppmNetHandle netP;
    Uns32        value;
} outputPin, *outputPinP;

static outputPin TOAA0     = { "TOAA0"    , 0, 0 };
static outputPin TOAA1     = { "TOAA1"    , 0, 0 };
static outputPin INTTAAOV  = { "INTTAAOV" , 0, 0 };
static outputPin INTTAACC0 = { "INTTAACC0", 0, 0 };
static outputPin INTTAACC1 = { "INTTAACC1", 0, 0 };

static struct {
    Uns32 TIAA0;
    Uns32 TIAA1;
    Uns32 TTRGAA;
    Uns32 TEVTAA;
} inputPin;

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
        if (PSE_DIAG_HIGH) bhmMessage("I", "TAA", "Timer Expired %f", bhmGetCurrentTime());

        //
        // OK, we have timed out, question is why ?
        //
        evaluateEvent();
        if (PSE_DIAG_HIGH) bhmMessage("I", "TAA", "Re-Start Timer(%f) %f",  microSecondDelay, bhmGetCurrentTime());
    }
}

static void stopTimer() {
    if (timerThreadHandle) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "TAA", "Stop Timer %f", bhmGetCurrentTime());
        bhmDeleteThread(timerThreadHandle);
        timerThreadHandle = 0;
    }
}

static void startTimer(double delay) {
    stopTimer();
    microSecondDelay = delay;
    if (PSE_DIAG_HIGH) bhmMessage("I", "TAA", "Start Timer(%f) %f",  microSecondDelay, bhmGetCurrentTime());
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

    if (PSE_DIAG_HIGH) bhmMessage("I", "TAA", "updateCntInfo: CNT=0x%04x", cntInfo.value);
    //
    // Overflow count difference
    //
    Uns32 ticks = calcDelay(0xffff, (Uns32)cntInfo.value);

    //
    // CCR0/1
    //
    ticks = minOf(ticks, calcDelay(CCR_Buffer[0], (Uns32)cntInfo.value));
    ticks = minOf(ticks, calcDelay(CCR_Buffer[1], (Uns32)cntInfo.value));

    cntInfo.next = (cntInfo.value + ticks) & 0xffff;
    if (PSE_DIAG_HIGH) bhmMessage("I", "TAA", "updateCntInfo: nextCNT=0x%04x", cntInfo.next);

    return ticks;
}

static void evaluateEvent () {
    Uns8 CCS0, CCS1;

    //
    // Evaluate the current event based upon the Mode
    //
    switch (TAAP0_reg0_data.CTL1.bits.MD) {
    case 0:
        //
        // Interval Timer Mode
        // we must be here for one of the following reasons
        // 1. Counter matches CCR0 - (reset to 0)
        // 2. Counter matches CCR1:5 (generate interrupt)
        if (cntInfo.next == CCR_Buffer[0]) {
            posPulseNet(&INTTAACC0);
        }
        if (cntInfo.next == CCR_Buffer[1]) {
            posPulseNet(&INTTAACC1);
        }

        //
        // Next state
        //
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
        if (cntInfo.next == CCR_Buffer[0]) {
            posPulseNet(&INTTAACC0);
        }
        if (cntInfo.next == CCR_Buffer[1]) {
            posPulseNet(&INTTAACC1);
        }

        //
        // Next state
        //
        if (cntInfo.next == CCR_Buffer[0]) {
            cntInfo.next = 0;
        }
        break;
    case 2:
        //
        // External Trigger Pulse Output Mode
        //
        bhmMessage("W", "CTL1", "Unsupported MODE: External Trigger Pulse Output");
        break;
    case 3:
        //
        // One-Shot Pulse Mode
        //
        bhmMessage("W", "CTL1", "Unsupported MODE: One-Shot Pulse");
        break;
    case 4:
        //
        // PWM Mode
        //
        bhmMessage("W", "CTL1", "Unsupported MODE: PWM");
        break;
    case 5:
        //
        // Free-Running Mode
        //
        CCS0 =  TAAP0_reg0_data.OPT0.bits.CCS     & 0x1;
        CCS1 = (TAAP0_reg0_data.OPT0.bits.CCS>>1) & 0x1;

        if (cntInfo.next == CCR_Buffer[0]) {
            if (CCS0) {
                bhmMessage("W", "CTL1", "Unsupported MODE: Free-Running/Capture OPT0[CCS0]=1");
            } else {
                posPulseNet(&INTTAACC0);
                //
                // Toggle the output bit if enabled
                //
                if (TAAP0_reg2_data.IOC4.bits.OR0==0 && TAAP0_reg2_data.IOC4.bits.OS0==0) {
                    toggleNet(&TOAA0);
                }
            }
        }
        if (cntInfo.next == CCR_Buffer[1]) {
            if (CCS1) {
                bhmMessage("W", "CTL1", "Unsupported MODE: Free-Running/Capture OPT0[CCS1]=1");
            } else {
                posPulseNet(&INTTAACC1);
                //
                // Toggle the output bit if enabled
                //
                if (TAAP0_reg2_data.IOC4.bits.OR1==0 && TAAP0_reg2_data.IOC4.bits.OS1==0) {
                    toggleNet(&TOAA1);
                }
            }
        }

        //
        // Next state
        // Timer simply overflows in this mode
        //
        if (cntInfo.next == 0xffff) {
            posPulseNet(&INTTAAOV);
            TAAP0_reg0_data.OPT0.bits.OVF = 1;
            cntInfo.next = 0;
        }
        microSecondDelay = ticksToTime(updateCntInfo(cntInfo.next));
        break;
    case 6:
        //
        // Pulse width measurement Mode
        //
        bhmMessage("W", "CTL1", "Unsupported MODE: Pulse width measurement Mode");
        break;
    default:
        //
        // all else ...
        //
        bhmMessage("W", "CTL1", "Illegal MODE CTL1/MD=0x%1x", TAAP0_reg0_data.CTL1.bits.MD);
        break;
    }

}

//
// This function should be intercepted by the plant model
// The values passed for the duty and cycle are updated when CCR1 or CCR0 are updated and
// allow the PWM rate to be determined in the plant model
//
FUNCTOHOST(void, interceptPlantModelDutyRate, Uns32 cycle, Uns32 duty, Uns32 ticksPerSecond)


static void bufferReloadCCR() {
    CCR_Buffer[0] = TAAP0_reg1_data.CCR0.value;
    CCR_Buffer[1] = TAAP0_reg1_data.CCR1.value;
}

//
// Called whenever timer control changes
//
void update_timer () {
    Uns32 ticks;

    static Uns8 CEprev = 0;
    Uns8 CE = TAAP0_reg0_data.CTL0.bits.CE;

    //
    // Calculate the microSecCB
    //
    if (TAAP0_reg0_data.CTL1.bits.EEE) {
        //
        // External clock
        //
    } else {
        //
        // Internal Clock
        //
        PCLKS = PCLK[TAAP0_reg0_data.CTL0.bits.CKS];
        if (TAAP0_reg0_data.CTL0.bits.CKS == 6) PCLKS = PCLK[7];
        if (TAAP0_reg0_data.CTL0.bits.CKS == 7) PCLKS = PCLK[9];
        microSecCB = (1 / PCLKS) * 1000000;
        if (PSE_DIAG_HIGH) bhmMessage("W", "EVCB", "PCLKS=%f ClockInterval=%fus", PCLKS, microSecCB);
    }

    if (CE) {
        if (PSE_DIAG_HIGH) bhmMessage("W", "EVCB", "Counter Enabled");

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
        switch (TAAP0_reg0_data.CTL1.bits.MD) {
        case 0:
            //
            // Interval Timer Mode
            //
//            if (CEprev==0 && CE==1) {
//                doWriteNet(&TOS0, 0);
//                doWriteNet(&TOS1, 0);
//            }
            bufferReloadCCR();
            ticks = updateCntInfo(0);
            if (PSE_DIAG_HIGH) bhmMessage("W", "EVCB", "Interval Timer Mode ticks=%d", ticks);
            startTimer(ticksToTime(ticks));
            break;
        case 1:
            //
            // External Event Count Mode
            // In order to implement this we need to propagate the top level
            // Pins in order to be driven
            //
            bufferReloadCCR();
            if (PSE_DIAG_HIGH) bhmMessage("W", "CTL1", "Untested MODE: External Event Count");
            break;
        case 2:
            //
            // External Trigger Pulse Output Mode
            //
            bhmMessage("W", "CTL1", "Unsupported MODE: External Trigger Pulse Output");
            break;
        case 3:
            //
            // One-Shot Pulse Mode
            //
            bufferReloadCCR();
            bhmMessage("W", "CTL1", "Unsupported MODE: One-Shot Pulse");
            break;
        case 4:
            //
            // PWM Mode
            //
            bufferReloadCCR();
            if (plantModelEnabled) {
                // plant model mode
                // update plant model duty and cycle
                // TODO: these need to be converted to time from register values
                interceptPlantModelDutyRate(
                        CCR_Buffer[0],
                        CCR_Buffer[1],
                        microSecCB);
            } else {
                bhmMessage("W", "CTL1", "Unsupported MODE: PWM");
            }
            break;
        case 5:
            //
            // Free-Running Mode
            //
//            if (CEprev==0 && CE==1) {
//                doWriteNet(&TOS0, 0);
//                doWriteNet(&TOS1, 0);
//            }
            bufferReloadCCR();
            ticks = updateCntInfo(0);
            if (PSE_DIAG_HIGH) bhmMessage("W", "EVCB", "Free-Running Mode ticks=%d", ticks);
            startTimer(ticksToTime(ticks));
            break;
        case 6:
            //
            // Pulse width measurement Mode
            //
            bhmMessage("W", "CTL1", "Unsupported MODE: Pulse width measurement Mode");
            break;
        default:
            //
            // all else ...
            //
            bhmMessage("W", "CTL1", "Illegal MODE CTL1/MD=0x%1x", TAAP0_reg0_data.CTL1.bits.MD);
            break;
        }

    } else {
        if (PSE_DIAG_HIGH) bhmMessage("W", "EVCB", "Counter Disabled");

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
    if (TAAP0_reg0_data.CTL0.bits.CE) {
        double time = bhmGetCurrentTime();
        double diff = time - cntInfo.time;
        Uns32 ticks = timeToTicks(diff);
        cnt = (cntInfo.value + ticks) & 0xffff;
    }
    TAAP0_reg1_data.CNT.value = cnt;
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NET_CB(P_TEVTAA) {
    inputPin.TEVTAA = value;
}

PPM_NET_CB(P_TIAA0) {
    inputPin.TIAA0 = value;
}

PPM_NET_CB(P_TIAA1) {
    inputPin.TIAA1 = value;
}

PPM_NET_CB(P_TTRGAA) {
    inputPin.TTRGAA = value;
}

PPM_REG_READ_CB(readCNT) {
    update_count();

    return *(Uns16*)user;
}

PPM_REG_WRITE_CB(writeCCR0) {
    *(Uns16*)user = data;

    update_timer();
}

PPM_REG_WRITE_CB(writeCCR1) {
    *(Uns16*)user = data;

    update_timer();
}

PPM_REG_WRITE_CB(writeCTL0) {
    //
    // Check legal values
    //
    if (data & 0x78) {
        bhmMessage("W", "TAA", "Register CTL0 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0x78) | (data & 0x87);

    update_timer();
}

PPM_REG_WRITE_CB(writeCTL1) {
    //
    // Check legal values
    //
    if (data & 0x18) {
        bhmMessage("W", "TAA", "Register CTL1 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0x18) | (data & 0xe7);

    update_timer();
}

PPM_REG_WRITE_CB(writeIOC0) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", "TAA", "Register IOC0 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);
}

PPM_REG_WRITE_CB(writeIOC1) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", "TAA", "Register IOC1 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);
}

PPM_REG_WRITE_CB(writeIOC2) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", "TAA", "Register IOC2 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);
}

PPM_REG_WRITE_CB(writeIOC4) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", "TAA", "Register IOC4 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);
}

PPM_REG_WRITE_CB(writeOPT0) {
    //
    // Check legal values
    //
    if (data & 0xce) {
        bhmMessage("W", "TAA", "Register IOC4 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xce) | (data & 0x31);
}

PPM_REG_WRITE_CB(writeSVC) {
    // YOUR CODE HERE (writeSVC)
    *(Uns8*)user = data;
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    TOAA0.netP     = handles.TOAA0;
    TOAA1.netP     = handles.TOAA1;
    INTTAAOV.netP  = handles.INTTAAOV;
    INTTAACC0.netP = handles.INTTAACC0;
    INTTAACC1.netP = handles.INTTAACC1;

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

    bhmBoolParamValue("PlantModelPWM", &plantModelEnabled);

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


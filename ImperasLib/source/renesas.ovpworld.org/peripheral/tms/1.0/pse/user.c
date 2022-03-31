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
//                          Mon Sep 17 12:05:44 2012
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "pse.igen.h"

typedef struct outputPinS {
    const char  *name;
    ppmNetHandle netP;
    Uns32        value;
} outputPin, *outputPinP;

static outputPin TOS0     = { "TOS0",     0, 0 };
static outputPin TOS1     = { "TOS1",     0, 0 };
static outputPin TOS2     = { "TOS2",     0, 0 };
static outputPin TOS3     = { "TOS3",     0, 0 };
static outputPin TOS4     = { "TOS4",     0, 0 };
static outputPin TOS5     = { "TOS5",     0, 0 };
static outputPin TOS6     = { "TOS6",     0, 0 };
static outputPin TOS7     = { "TOS7",     0, 0 };
static outputPin INTTSCC0 = { "INTTSCC0", 0, 0 };
static outputPin INTTSCC1 = { "INTTSCC1", 0, 0 };
static outputPin INTTSCC2 = { "INTTSCC2", 0, 0 };
static outputPin INTTSCC3 = { "INTTSCC3", 0, 0 };
static outputPin INTTSCC4 = { "INTTSCC4", 0, 0 };
static outputPin INTTSCC5 = { "INTTSCC5", 0, 0 };
static outputPin INTTSCD0 = { "INTTSCD0", 0, 0 };
static outputPin INTTSOD  = { "INTTSOD",  0, 0 };
static outputPin INTTSOV  = { "INTTSOV",  0, 0 };
static outputPin INTTSER  = { "INTTSER",  0, 0 };
static outputPin INTTSWN  = { "INTTSWN",  0, 0 };
static outputPin TSADTRG0 = { "TSADTRG0", 0, 0 };
static outputPin TSADTRG1 = { "TSADTRG1", 0, 0 };
static outputPin TSAEDO   = { "TSAEDO",   0, 0 };
static outputPin TSESG    = { "TSESG",    0, 0 };
static outputPin TSTSF    = { "TSTSF",    0, 0 };

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

static Uns32 CCR_Buffer[6];
struct {
    Uns32  value;   // Current Value of register
    double time;    // Time at which value was set
    Uns32  next;    // value of register at next calculated event
} cntInfo;

#define BYTE_ACCESS(_addr,_user) *(Uns8*)(UnsPS)(PTR_TO_UNS32(_user) | (PTR_TO_UNS32(_addr) & 1))

static void writeByteOrShort(void *addr, Uns32 bytes, void *user, Uns32 data) {
    if (bytes == 1) {
        BYTE_ACCESS(addr,user) = data;
    } else {
        *(Uns16*)user = data;
    }
}

static Uns32 readByteOrShort(void *addr, Uns32 bytes, void *user) {
    if (bytes == 1) {
        return BYTE_ACCESS(addr,user);
    } else {
        return *(Uns16*)user;
    }
}

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
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "Timer Expired %f", bhmGetCurrentTime());

        //
        // OK, we have timed out, question is why ?
        //
        evaluateEvent();
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "Re-Start Timer(%f) %f",  microSecondDelay, bhmGetCurrentTime());
    }
}

static void stopTimer() {
    if (timerThreadHandle) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "Stop Timer %f", bhmGetCurrentTime());
        bhmDeleteThread(timerThreadHandle);
        timerThreadHandle = 0;
    }
}

static void startTimer(double delay) {
    stopTimer();
    microSecondDelay = delay;
    if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "Start Timer(%f) %f",  microSecondDelay, bhmGetCurrentTime());
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

    if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "updateCntInfo: CNT=0x%04x", cntInfo.value);
    //
    // Overflow count difference
    //
    Uns32 ticks = calcDelay(0xffff, (Uns32)cntInfo.value);

    //
    // CCR0..5
    //
    ticks = minOf(ticks, calcDelay(CCR_Buffer[0], (Uns32)cntInfo.value));
    ticks = minOf(ticks, calcDelay(CCR_Buffer[1], (Uns32)cntInfo.value));
    ticks = minOf(ticks, calcDelay(CCR_Buffer[2], (Uns32)cntInfo.value));
    ticks = minOf(ticks, calcDelay(CCR_Buffer[3], (Uns32)cntInfo.value));
    ticks = minOf(ticks, calcDelay(CCR_Buffer[4], (Uns32)cntInfo.value));
    ticks = minOf(ticks, calcDelay(CCR_Buffer[5], (Uns32)cntInfo.value));

    cntInfo.next = (cntInfo.value + ticks) & 0xffff;
    if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "updateCntInfo: nextCNT=0x%04x ticks=0x%04x", cntInfo.next, ticks);

    return ticks;
}

static void genSignalsFromCCR() {
    //
    // CCR0:5 match
    //
    if (cntInfo.next == CCR_Buffer[0]) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s:%d", __FUNCTION__, 1);
        posPulseNet(&INTTSCC0);
        toggleNet(&TOS0);
    }
    if (cntInfo.next == CCR_Buffer[1]) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s:%d", __FUNCTION__, 2);
        posPulseNet(&INTTSCC1);
        toggleNet(&TOS1);
    }
    if (cntInfo.next == CCR_Buffer[2]) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s:%d", __FUNCTION__, 3);
        posPulseNet(&INTTSCC2);
        toggleNet(&TOS2);
    }
    if (cntInfo.next == CCR_Buffer[3]) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s:%d", __FUNCTION__, 4);
        posPulseNet(&INTTSCC3);
        toggleNet(&TOS3);
    }
    if (cntInfo.next == CCR_Buffer[4]) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s:%d", __FUNCTION__, 5);
        posPulseNet(&INTTSCC4);
        if(TMSP0_reg3_data.OPT2.bits.AT04) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s_ADTRG0:%d", __FUNCTION__, 6);
            posPulseNet(&TSADTRG0);
        }
        if(TMSP0_reg3_data.OPT3.bits.AT04) {
            if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s_ADTRG1:%d", __FUNCTION__, 7);
            posPulseNet(&TSADTRG1);
        }
        toggleNet(&TOS4);
    }
    if (cntInfo.next == CCR_Buffer[5]) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s:%d", __FUNCTION__, 8);
        posPulseNet(&INTTSCC5);
        if(TMSP0_reg3_data.OPT2.bits.AT05) {
            if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s_ADTRG0:%d", __FUNCTION__, 9);
            posPulseNet(&TSADTRG0);
        }
        if(TMSP0_reg3_data.OPT3.bits.AT05) {
            if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s_ADTRG1:%d", __FUNCTION__, 10);
            posPulseNet(&TSADTRG1);
        }
        toggleNet(&TOS5);
    }
}

static void evaluateEvent () {
    //
    // Evaluate the current event based upon the Mode
    //
    switch (TMSP0_reg0_data.CTL1.bits.MD) {
    case 0:
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s:%d", __FUNCTION__, 1);
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
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s:%d", __FUNCTION__, 2);
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
        if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s:%d", __FUNCTION__, 3);
        //
        // Free-Running Mode
        // This mode generates an Overflow INTTSOV
        //
        genSignalsFromCCR();
        // Timer simply overflows in this mode
        if (cntInfo.next == 0xffff) {
            posPulseNet(&INTTSOV);
            TMSP0_reg2_data.OPT0.bits.OVF = 1;
            cntInfo.next = 0;
        }
        microSecondDelay = ticksToTime(updateCntInfo(cntInfo.next));
        break;
    case 7:
        //
        // Triangular-Wave PWM Mode
        //
        bhmMessage("W", "CTL1", "Unsupported MODE: Triangular-Wave PWM");
        break;
    case 8:
        //
        // High Accuracy T-PWM Mode
        //
        bhmMessage("W", "CTL1", "Unsupported MODE: High Accuracy T-PWM");
        break;
    case 9:
        //
        // PWM Mode with Dead Time
        //
        bhmMessage("W", "CTL1", "Unsupported MODE: PWM Mode with Dead Time");
        break;
    case 10:
        //
        // 120Deg Excitation Mode
        //
        bhmMessage("W", "CTL1", "Unsupported MODE: 120Deg Excitation Mode");
        break;
    case 11:
        //
        // Special 120Deg Excitation Mode
        //
        bhmMessage("W", "CTL1", "Unsupported MODE: Special 120Deg Excitation");
        break;
    case 12:
        //
        // Special Pattern Output Mode
        //
        bhmMessage("W", "CTL1", "Unsupported MODE: Special Pattern Output Mode");
        break;
    default:
        //
        // all else ...
        //
        bhmMessage("W", "CTL1", "Illegal MODE CTL1/MD=0x%1x", TMSP0_reg0_data.CTL1.bits.MD);
        break;
    }

}

static void bufferReloadCCR() {
    CCR_Buffer[0] = TMSP0_reg3_data.CCR0.value;
    CCR_Buffer[1] = TMSP0_reg3_data.CCR1.value;
    CCR_Buffer[2] = TMSP0_reg3_data.CCR2.value;
    CCR_Buffer[3] = TMSP0_reg3_data.CCR3.value;
    CCR_Buffer[4] = TMSP0_reg3_data.CCR4.value;
    CCR_Buffer[5] = TMSP0_reg3_data.CCR5.value;
    bhmMessage("I", "TMS", "%s 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x",  __FUNCTION__,
           CCR_Buffer[0], CCR_Buffer[1], CCR_Buffer[2], CCR_Buffer[3], CCR_Buffer[4], CCR_Buffer[5]);
}

//
// Called whenever timer control changes
//
void update_timer () {
    Uns32 ticks;

    static Uns8 CEprev = 0;
    Uns8 CE = TMSP0_reg0_data.CTL0.bits.CE;

    //
    // Calculate the microSecCB
    //
    if (TMSP0_reg0_data.CTL1.bits.EEE) {
        //
        // External clock
        //
    } else {
        //
        // Internal Clock
        //
        PCLKS = PCLK[TMSP0_reg0_data.CTL0.bits.CKS];
        if (TMSP0_reg0_data.CTL0.bits.CKS == 6) PCLKS = PCLK[7];
        if (TMSP0_reg0_data.CTL0.bits.CKS == 7) PCLKS = PCLK[9];
        microSecCB = (1 / PCLKS) * 1000000;
        if (PSE_DIAG_HIGH) bhmMessage("I", "EVCB", "PCLKS=%f ClockInterval=%fus", PCLKS, microSecCB);
    }

    if (CE) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "EVCB", "Counter Enabled");

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
        switch (TMSP0_reg0_data.CTL1.bits.MD) {
        case 0:
            if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s", __FUNCTION__);
            //
            // Interval Timer Mode
            // This mode performs a compare between the CNT register and the CCR0
            // An interrupt is also generated on a match between CCR1-CCR4
            //
            if (CEprev==0 && CE==1) {
                doWriteNet(&TOS0, 0);
                doWriteNet(&TOS1, 0);
                doWriteNet(&TOS2, 0);
                doWriteNet(&TOS3, 0);
                doWriteNet(&TOS4, 0);
                doWriteNet(&TOS5, 0);
            }
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
            bhmMessage("W", "CTL1", "Unsupported MODE: PWM");
            break;
        case 5:
            if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s", __FUNCTION__);
            //
            // Free-Running Mode
            // This mode generates an Overflow INTTSOV
            // Also generates Compare interrupts and TOS outputs
            //
            if (CEprev==0 && CE==1) {
                doWriteNet(&TOS0, 0);
                doWriteNet(&TOS1, 0);
                doWriteNet(&TOS2, 0);
                doWriteNet(&TOS3, 0);
                doWriteNet(&TOS4, 0);
                doWriteNet(&TOS5, 0);
            }
            bufferReloadCCR();
            ticks = updateCntInfo(0);
            if (PSE_DIAG_HIGH) bhmMessage("W", "EVCB", "Free-Running Mode ticks=%d", ticks);
            startTimer(ticksToTime(ticks));
            break;
        case 7:
            //
            // Triangular-Wave PWM Mode
            //
            bhmMessage("W", "CTL1", "Unsupported MODE: Triangular-Wave PWM");
            break;
        case 8:
            //
            // High Accuracy T-PWM Mode
            //
            bhmMessage("W", "CTL1", "Unsupported MODE: High Accuracy T-PWM");
            break;
        case 9:
            //
            // PWM Mode with Dead Time
            //
            bhmMessage("W", "CTL1", "Unsupported MODE: PWM Mode with Dead Time");
            break;
        case 10:
            //
            // 120Deg Excitation Mode
            //
            bhmMessage("W", "CTL1", "Unsupported MODE: 120Deg Excitation Mode");
            break;
        case 11:
            //
            // Special 120Deg Excitation Mode
            //
            bhmMessage("W", "CTL1", "Unsupported MODE: Special 120Deg Excitation");
            break;
        case 12:
            //
            // Special Pattern Output Mode
            //
            bhmMessage("W", "CTL1", "Unsupported MODE: Special Pattern Output Mode");
            break;
        default:
            //
            // all else ...
            //
            bhmMessage("W", "CTL1", "Illegal MODE CTL1/MD=0x%1x", TMSP0_reg0_data.CTL1.bits.MD);
            break;
        }

    } else {
        //
        // This is the initialization bit
        //
        if (PSE_DIAG_HIGH) bhmMessage("I", "EVCB", "Counter Disabled");

        //
        // Clear OVF flag and all Flags in OPT6
        // CCR0..5, PAT0,1, DTC0,1
        //
        TMSP0_reg2_data.OPT0.bits.OVF = 0;
        TMSP0_reg3_data.OPT6.value    = 0;
        TMSP0_reg3_data.PAT0.value    = 0;
        TMSP0_reg3_data.PAT1.value    = 0;
        TMSP0_reg3_data.DTC0.value    = 0;
        TMSP0_reg3_data.DTC1.value    = 0;
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
    if (TMSP0_reg0_data.CTL0.bits.CE) {
        double time = bhmGetCurrentTime();
        double diff = time - cntInfo.time;
        Uns32 ticks = timeToTicks(diff);
        cnt = (cntInfo.value + ticks) & 0xffff;
    }
    if (PSE_DIAG_HIGH) bhmMessage("I", "TMS", "%s %d %d %f", __FUNCTION__, cntInfo.value, cnt, cntInfo.time);
    TMSP0_reg3_data.CNT.value = cnt;
}

//////////////////////////////// Callback stubs ////////////////////////////////
PPM_NET_CB(P_ESO) {
    // YOUR CODE HERE (P_ESO)
}

PPM_NET_CB(P_TAPTS0) {
    // YOUR CODE HERE (P_TAPTS0)
}

PPM_NET_CB(P_TAPTS1) {
    // YOUR CODE HERE (P_TAPTS1)
}

PPM_NET_CB(P_TAPTS2) {
    // YOUR CODE HERE (P_TAPTS2)
}

PPM_NET_CB(P_TEVTS) {
    //
    // This is the count clock
    //
    static ppmNetValue prev = 0;

    //
    // Detect positive edge
    //
    if (prev==0 && value==1) {
        evaluateEvent();
    }
    prev = value;
}

PPM_NET_CB(P_TTRGS) {
    // YOUR CODE HERE (P_TTRGS)
}

PPM_REG_READ_CB(readCNT) {
    update_count();

    return *(Uns16*)user;
}

PPM_REG_READ_CB(readIOC0) {
    return readByteOrShort(addr, bytes, user);
}

PPM_REG_READ_CB(readOPT1) {
    return readByteOrShort(addr, bytes, user);
}

PPM_REG_READ_CB(readOPT2) {
    return readByteOrShort(addr, bytes, user);
}

PPM_REG_READ_CB(readOPT3) {
    return readByteOrShort(addr, bytes, user);
}

PPM_REG_READ_CB(readOPT6) {
    return readByteOrShort(addr, bytes, user);
}

PPM_REG_READ_CB(readSBC) {
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

PPM_REG_WRITE_CB(writeCCR2) {
    // YOUR CODE HERE (writeCCR2)
    *(Uns16*)user = (*(Uns16*)user & 0x0) | (data & 0xffff);

    //
    // Need to update timer in case a different event time is required
    //
    update_timer ();
}

PPM_REG_WRITE_CB(writeCCR3) {
    *(Uns16*)user = (*(Uns16*)user & 0x0) | (data & 0xffff);

    //
    // Need to update timer in case a different event time is required
    //
    update_timer ();
}

PPM_REG_WRITE_CB(writeCCR4) {
    *(Uns16*)user = (*(Uns16*)user & 0x0) | (data & 0xffff);

    //
    // Need to update timer in case a different event time is required
    //
    update_timer ();
}

PPM_REG_WRITE_CB(writeCCR5) {
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
        bhmMessage("W", "TMS", "Register CTL0 Illegal value 0x%02x\n", data);
    }

    //
    // Get previous values of CE and CKS
    //
    Uns8 CE  = TMSP0_reg0_data.CTL0.bits.CE;
    Uns8 CKS = TMSP0_reg0_data.CTL0.bits.CKS;

    *(Uns8*)user = (*(Uns8*)user & 0x78) | (data & 0x87);

    //
    // Ensure the CE bit was zero if changing any other bits
    //
    if (CE==1 && (CKS != TMSP0_reg0_data.CTL0.bits.CKS)) {
        bhmMessage("W", "TMS", "Register CTL0 invalid to change CKS while CE==1, setting ignored\n");
        TMSP0_reg0_data.CTL0.bits.CKS = CKS;
    }

    update_timer();
}

PPM_REG_WRITE_CB(writeCTL1) {
    //
    // Check legal values
    //
    if (data & 0x90) {
        bhmMessage("W", "TMS", "Register CTL1 Illegal value 0x%02x\n", data);
    }

    *(Uns8*)user = (*(Uns8*)user & 0x90) | (data & 0x6f);

    update_timer();
}

PPM_REG_WRITE_CB(writeDTC0) {
    //
    // Check legal values
    //
    if (data & 0xfc01) {
        bhmMessage("W", "TMS", "Register DTC0 Illegal value 0x%04x\n", data);
    }
    *(Uns16*)user = (*(Uns16*)user & 0xfc01) | (data & 0x3fe);
}

PPM_REG_WRITE_CB(writeDTC1) {
    //
    // Check legal values
    //
    if (data & 0xfc01) {
        bhmMessage("W", "TMS", "Register DTC0 Illegal value 0x%04x\n", data);
    }
    *(Uns16*)user = (*(Uns16*)user & 0xfc01) | (data & 0x3fe);
}

PPM_REG_WRITE_CB(writeIOC0) {
    writeByteOrShort(addr, bytes, user, data);
}

PPM_REG_WRITE_CB(writeIOC2) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", "TMS", "Register IOC2 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);
}

PPM_REG_WRITE_CB(writeIOC4) {
    //
    // Check legal values
    //
    if (data & 0x8a) {
        bhmMessage("W", "TMS", "Register IOC4 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0x8a) | (data & 0x75);
}

PPM_REG_WRITE_CB(writeOPT0) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", "TMS", "Register OPT0 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);
}

PPM_REG_WRITE_CB(writeOPT1) {
    Uns32 mask = 0x1fff;
    if (PTR_TO_UNS32(addr) & 0x1) {
        mask >>= 8;
    }
    //
    // Check legal values
    //
    if (data & ~mask) {
        bhmMessage("W", "TMS", "Register OPT1 Illegal value 0x%04x\n", data);
    }

    writeByteOrShort(addr, bytes, user, (data & mask));
}

PPM_REG_WRITE_CB(writeOPT2) {
    Uns32 mask = 0x03ff;
    if (PTR_TO_UNS32(addr) & 0x1) {
        mask >>= 8;
    }
    //
    // Check legal values
    //
    if (data & ~mask) {
        bhmMessage("W", "TMS", "Register OPT2 Illegal value 0x%04x\n", data);
    }
    writeByteOrShort(addr, bytes, user, (data & mask));
}

PPM_REG_WRITE_CB(writeOPT3) {
    Uns32 mask = 0x03ff;
    if (PTR_TO_UNS32(addr) & 0x1) {
        mask >>= 8;
    }
    //
    // Check legal values
    //
    if (data & ~mask) {
        bhmMessage("W", "TMS", "Register OPT3 Illegal value 0x%04x\n", data);
    }
    writeByteOrShort(addr, bytes, user, (data & mask));
}

PPM_REG_WRITE_CB(writeOPT4) {
    //
    // Check legal values
    //
    if (data & 0x70) {
        bhmMessage("W", "TMS", "Register OPT4 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0x70) | (data & 0x8f);
}

PPM_REG_WRITE_CB(writeOPT5) {
    // YOUR CODE HERE (writeOPT5)
    *(Uns8*)user = (*(Uns8*)user & 0x0) | (data & 0xff);
}

PPM_REG_WRITE_CB(writeOPT6) {
    Uns32 mask = 0x01ff;
    if (PTR_TO_UNS32(addr) & 0x1) {
        mask >>= 8;
    }
    //
    // Check legal values
    //
    if (data & ~mask) {
        bhmMessage("W", "TMS", "Register OPT6 Illegal value 0x%04x\n", data);
    }
    writeByteOrShort(addr, bytes, user, (data & mask));
}

PPM_REG_WRITE_CB(writeOPT7) {
    //
    // Check legal values
    //
    if (data & 0xc0) {
        bhmMessage("W", "TMS", "Register OPT7 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xc0) | (data & 0x3f);
}

PPM_REG_WRITE_CB(writePAT0) {
    *(Uns16*)user = (*(Uns16*)user & 0x0) | (data & 0xffff);
}

PPM_REG_WRITE_CB(writePAT1) {
    *(Uns16*)user = (*(Uns16*)user & 0x0) | (data & 0xffff);
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    TOS0.netP     = handles.TOS0;
    TOS1.netP     = handles.TOS1;
    TOS2.netP     = handles.TOS2;
    TOS3.netP     = handles.TOS3;
    TOS4.netP     = handles.TOS4;
    TOS5.netP     = handles.TOS5;
    TOS6.netP     = handles.TOS6;
    TOS7.netP     = handles.TOS7;
    INTTSCC0.netP = handles.INTTSCC0;
    INTTSCC1.netP = handles.INTTSCC1;
    INTTSCC2.netP = handles.INTTSCC2;
    INTTSCC3.netP = handles.INTTSCC3;
    INTTSCC4.netP = handles.INTTSCC4;
    INTTSCC5.netP = handles.INTTSCC5;
    INTTSCD0.netP = handles.INTTSCD0;
    INTTSOD.netP  = handles.INTTSOD;
    INTTSOV.netP  = handles.INTTSOV;
    INTTSER.netP  = handles.INTTSER;
    INTTSWN.netP  = handles.INTTSWN;
    TSADTRG0.netP = handles.TSADTRG0;
    TSADTRG1.netP = handles.TSADTRG1;
    TSAEDO.netP   = handles.TSAEDO;
    TSESG.netP    = handles.TSESG;
    TSTSF.netP    = handles.TSTSF;

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

    update_timer();
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


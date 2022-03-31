/*
 * MC148818 RTC Emulator.
 *
 * Copyright (c) 2003 Fabrice Bellard
 * Copyright (c) 2006 Openedhand Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
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

#include <string.h>

#include "pse.igen.h"

#include "rtc.h"

#define PREFIX "RTC"

void addressError(void *add, Uns32 attempt, Uns32 actual) {
    bhmMessage("E", PREFIX "_AE",
        "Attempting %u byte(s) access on a %u byte(s) register",
        attempt, actual
    );
}

//
// BusPort handles
//
static ppmLocalBusHandle rtc_handle;

//
// netPort handles
//
static ppmNetHandle intPortHandle;

//
// define the storage for the windows
//
Uns8 rtc_Window[2];             // This is the index register and the data register

RTCState rtc;                   // internal state of RTC

void genInterrupt() {
    if(intPortHandle) {
        ppmWriteNet(intPortHandle, 1);
        ppmWriteNet(intPortHandle, 0);
    }
}

//
// Dump the cmos_data fields to stdout
//
static void dump_cmos_data() {
    Uns32 i;
    bhmPrintf("Dumping rtc.cmos_data ...\n");

    for (i=0;i<RTC_NUM_REGS;i++) {
        bhmPrintf("Reg(%u) %s = %02x %p\n", i, regName[i], rtc.cmos_data[i], &rtc.cmos_data[i]);
    }
}

bhmEventHandle updateEnableEvent;       // when update is not enabled we wait for an event

Bool periodicTimerRunning = False;
Uns32 nextPeriod = 1000000;             // give a large value to minimise loop effect

bhmEventHandle startPTimer;

static void rtc_timer_update()
{
    Uns32 period_code, period;

    period_code = rtc.cmos_data[RTC_REG_A] & 0x0f;
    if (period_code != 0 &&
        (rtc.cmos_data[RTC_REG_B] & REG_B_PIE)) {
        if (period_code <= 2)
            period_code += 7;
        /* period in 32 Khz cycles */
        period = 1 << (period_code - 1);

        /* period for simulation delay */
        nextPeriod = period * 30517000;     // period times 30.517uS using bhmWaitDelay
        periodicTimerRunning = True;
        if (!bhmTriggerEvent(startPTimer))            // wake up periodic timer loop
        {
            bhmMessage("W", PREFIX,"Failed to Start periodic timer, period %d\n", nextPeriod);
        } else {
            if (BHM_DIAG_HIGH)
                bhmMessage("I", PREFIX,"Timer Update period code %d RTC_REG_B %08x REG_B_PIE %d\n", period_code, rtc.cmos_data[RTC_REG_B], rtc.cmos_data[RTC_REG_B] & REG_B_PIE);
        }
    } else {
        periodicTimerRunning = False;
    }

}

static inline Uns8 to_bcd(Uns32 a)
{
    if (rtc.cmos_data[RTC_REG_B] & 0x04) {
        return a;
    } else {
        return ((a / 10) << 4) | (a % 10);
    }
}

static inline Uns32 from_bcd(Uns8 a)
{
    if (rtc.cmos_data[RTC_REG_B] & 0x04) {
        return a;
    } else {
        return ((a >> 4) * 10) + (a & 0x0f);
    }
}

static void rtc_set_time()
{
    if (BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX,"rtc_set_time\n");
    rtc.current_tm.tm_sec = from_bcd(rtc.cmos_data[RTC_SECONDS]);
    rtc.current_tm.tm_min = from_bcd(rtc.cmos_data[RTC_MINUTES]);
    rtc.current_tm.tm_hour = from_bcd(rtc.cmos_data[RTC_HOURS] & 0x7f);
    if (!(rtc.cmos_data[RTC_REG_B] & 0x02) &&
        (rtc.cmos_data[RTC_HOURS] & 0x80)) {
        rtc.current_tm.tm_hour += 12;
    }
    rtc.current_tm.tm_wday = from_bcd(rtc.cmos_data[RTC_DAY_OF_WEEK]);
    rtc.current_tm.tm_mday = from_bcd(rtc.cmos_data[RTC_DATE_OF_MONTH]);
    rtc.current_tm.tm_mon = from_bcd(rtc.cmos_data[RTC_MONTH]) - 1;
    rtc.current_tm.tm_year = from_bcd(rtc.cmos_data[RTC_YEAR]) + 100;
}

static void rtc_copy_date()
{
    rtc.cmos_data[RTC_SECONDS] = to_bcd(rtc.current_tm.tm_sec);
    rtc.cmos_data[RTC_MINUTES] = to_bcd(rtc.current_tm.tm_min);
    if (rtc.cmos_data[RTC_REG_B] & 0x02) {
        /* 24 hour format */
        rtc.cmos_data[RTC_HOURS] = to_bcd(rtc.current_tm.tm_hour);
    } else {
        /* 12 hour format */
        rtc.cmos_data[RTC_HOURS] = to_bcd(rtc.current_tm.tm_hour % 12);
        if (rtc.current_tm.tm_hour >= 12)
            rtc.cmos_data[RTC_HOURS] |= 0x80;
    }
    rtc.cmos_data[RTC_DAY_OF_WEEK] = to_bcd(rtc.current_tm.tm_wday);
    rtc.cmos_data[RTC_DATE_OF_MONTH] = to_bcd(rtc.current_tm.tm_mday);
    rtc.cmos_data[RTC_MONTH] = to_bcd(rtc.current_tm.tm_mon + 1);
    rtc.cmos_data[RTC_YEAR] = to_bcd(rtc.current_tm.tm_year % 100);

    if (BHM_DIAG_MEDIUM)
        bhmMessage("I", PREFIX,"Update Date/Time %s %u/%u/%u %02u:%02u:%02u\n",
                            dayOfWeek[from_bcd(rtc.cmos_data[RTC_DAY_OF_WEEK])],
                            from_bcd(rtc.cmos_data[RTC_DATE_OF_MONTH]),
                            from_bcd(rtc.cmos_data[RTC_MONTH]),
                            from_bcd(rtc.cmos_data[RTC_YEAR])+2000,
                            from_bcd(rtc.cmos_data[RTC_HOURS]),
                            from_bcd(rtc.cmos_data[RTC_MINUTES]),
                            from_bcd(rtc.cmos_data[RTC_SECONDS]));


    if (BHM_DIAG_HIGH)
        dump_cmos_data();
}

/* month is between 0 and 11. */
static Uns32 get_days_in_month(Uns32 month, Uns32 year)
{
    static const Uns32 days_tab[12] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    Uns32 d;
    if ((Uns32)month >= 12)
        return 31;
    d = days_tab[month];
    if (month == 1) {
        if ((year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0))
            d++;
    }
    return d;
}


static inline void updateHours(struct tm *current_tm) {
    if ((unsigned)current_tm->tm_hour >= 24) {
        /* next day */
        current_tm->tm_wday+=current_tm->tm_hour/24;
        current_tm->tm_hour = 0;

        current_tm->tm_mday+=current_tm->tm_wday;
        if ((unsigned)current_tm->tm_wday >= 7) {
            current_tm->tm_wday = current_tm->tm_wday%7;
        }

        Uns32 days_in_month = get_days_in_month(current_tm->tm_mon,
                                          current_tm->tm_year + 1900);

        if (current_tm->tm_mday < 1) {
            current_tm->tm_mday = 1;
        } else if (current_tm->tm_mday > days_in_month) {
            // TODO: this will not work for large increments in time
            //       but if increase is less than a month should be Ok
            current_tm->tm_mday = current_tm->tm_mday%days_in_month;
            current_tm->tm_mon++;
            if (current_tm->tm_mon >= 12) {
                current_tm->tm_mon = 0;
                current_tm->tm_year++;
            }
        }
    }
}

/* update 'tm' to the current bhm time */
static void rtc_update_current_tm()
{
    // truncate the floating point value
    Uns32 thisTime = (Uns32)bhmGetCurrentTime();
    static Uns32 lastTime = 0;

    Uns32 changeInTime = thisTime - lastTime;
    Uns32 secondsUpdate = changeInTime/BHM_ONE_SECOND;

    if (BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX,"rtc_update_current_tm last %u this %u (change %u) seconds %u",
                            lastTime, thisTime, changeInTime, secondsUpdate);

    if(secondsUpdate!=0) {
        // if updating save the time at the update
        lastTime = thisTime;

        rtc.current_tm.tm_sec+= secondsUpdate;
        if ((unsigned)rtc.current_tm.tm_sec >= 60) {
            rtc.current_tm.tm_min+= rtc.current_tm.tm_sec/60;
            rtc.current_tm.tm_sec = 0;
            if ((unsigned)rtc.current_tm.tm_min >= 60) {
                rtc.current_tm.tm_hour+=rtc.current_tm.tm_min/60;
                rtc.current_tm.tm_min = 0;

                updateHours(&rtc.current_tm);
            }
        }
    }

    rtc_copy_date();
}

//
// Check to see if there should be an alarm trigger
// This is checked during the one second update period
static void checkAlarm() {

    if (BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX,"Check for Alarm Interrupt\n");

    if ((((rtc.cmos_data[RTC_SECONDS_ALARM] & 0xc0) == 0xc0 ) ||
          (rtc.cmos_data[RTC_SECONDS_ALARM] == rtc.cmos_data[RTC_SECONDS])) &&
        (((rtc.cmos_data[RTC_MINUTES_ALARM] & 0xc0) == 0xc0 ) ||
          (rtc.cmos_data[RTC_MINUTES_ALARM] == rtc.cmos_data[RTC_MINUTES])) &&
        (((rtc.cmos_data[RTC_HOURS_ALARM]   & 0xc0) == 0xc0 ) ||
          (rtc.cmos_data[RTC_HOURS_ALARM]   == rtc.cmos_data[RTC_HOURS]))) {

        if (rtc.cmos_data[RTC_REG_B] & REG_B_AIE) {
            rtc.cmos_data[RTC_REG_C] |= 0xa0;
            if (BHM_DIAG_HIGH)
                bhmMessage("I", PREFIX,"Alarm Interrupt\n");
            genInterrupt();
        }
    }
}

static inline Uns32 getIndex(void) {
    return rtc_Window[RTC_WINDOW_INDEX];
}

static void refreshData(void) {
    rtc_Window[RTC_WINDOW_DATA] = rtc.cmos_data[getIndex()];
}

static PPM_WRITE_CB(writeIndexCB) {

    if (BHM_DIAG_HIGH) {
        bhmMessage("I", PREFIX,"Write index %u\n", data);
    }

    refreshData();
}

static PPM_WRITE_CB(writeDataCB) {

    Uns32 index = getIndex();
    Uns8  dVal  = (Uns8)(data & 0xff);

    if (BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX,"Write %s index %d 0x%02x\n",
                    index < RTC_NUM_REGS ? regName[index] : "UNKNOWN",
                    index,
                    dVal);

    switch(index) {
        case RTC_SECONDS_ALARM:
        case RTC_MINUTES_ALARM:
        case RTC_HOURS_ALARM:
            rtc.cmos_data[index] = dVal;
            break;
        case RTC_SECONDS:
        case RTC_MINUTES:
        case RTC_HOURS:
        case RTC_DAY_OF_WEEK:
        case RTC_DATE_OF_MONTH:
        case RTC_MONTH:
        case RTC_YEAR:
            rtc.cmos_data[index] = dVal;
            /* if in set mode, do not update the time */
            if (!(rtc.cmos_data[RTC_REG_B] & REG_B_SET)) {
                rtc_set_time();
            }
            break;
        case RTC_REG_A:
            /* UIP bit is read only */
            rtc.cmos_data[RTC_REG_A] = (dVal & ~REG_A_UIP) |
                (rtc.cmos_data[RTC_REG_A] & REG_A_UIP);
            rtc_timer_update();
            // If osc mode changed to 0x20
            if (((dVal & 0x70) == 0x20) &&
                ((rtc.cmos_data[RTC_REG_A] & 0x70) != 0x20)) {
                if (!bhmTriggerEvent(updateEnableEvent))            // wake up one second timer
                {
                    bhmMessage("W", PREFIX,"OSC mode change to 0x20: Failed to Start One Second Update \n");
                }
            }
            break;
        case RTC_REG_B:
            if (dVal & REG_B_SET) {
                /* set mode: reset UIP mode */
                rtc.cmos_data[RTC_REG_A] &= ~REG_A_UIP;
                dVal &= ~REG_B_UIE;
            } else {
                /* if disabling set mode, update the time */
                if (rtc.cmos_data[RTC_REG_B] & REG_B_SET) {
                    rtc_set_time();
                    if (!bhmTriggerEvent(updateEnableEvent))            // wake up one second timer
                    {
                        bhmMessage("W", PREFIX,"REG_B SET cleared: Failed to Start One Second Update \n");
                    }
                }
            }
            rtc.cmos_data[RTC_REG_B] = dVal;
            rtc_timer_update();

            break;
        case RTC_REG_C:
        case RTC_REG_D:
            /* cannot write to them */
            bhmMessage("W", PREFIX,"Attempting to write to read only register %s\n",
                        regName[index]);
            break;
        default:
            if (index > MAX_REG_ACCESS)
                bhmMessage("F", PREFIX,"Index %d Out of range\n", index);
            rtc.cmos_data[index] = dVal;
            break;
    }

    if (BHM_DIAG_HIGH)
        dump_cmos_data();
}


/* PC cmos mappings */
#define REG_IBM_CENTURY_BYTE        0x32
#define REG_IBM_PS2_CENTURY_BYTE    0x37

void rtc_set_memory(int addr, int val)
{
    if (addr >= 0 && addr <= 127)
        rtc.cmos_data[addr] = val;
}

void rtc_set_date(const struct tm *tm)
{
    rtc.current_tm = *tm;
    rtc_copy_date();
}

static void rtc_set_date_from_host(Uns32 readTimeFromHost)
{
    struct tm tmt;
    struct tm *tm = &tmt;
    int val;

    if(readTimeFromHost) {
        // This attempts to read the time from the Host
        time_t ti;

        /* set the CMOS date */
        time(&ti);
        tm = gmtime(&ti);
        if(!tm->tm_isdst) {
// If we want to update the local time to current time
//            tm->tm_hour++;
//            updateHours(tm);
            if (BHM_DIAG_MEDIUM)
                bhmMessage("W", PREFIX,"Not Daylight Savings: local hour may be incorrect\n");
        }
    } else {
        // set a default time and date
        // 12:12.12 Friday, 25th April 2008
        tm->tm_sec   = 12;  // Seconds [0,60].
        tm->tm_min   = 12;  // Minutes [0,59].
        tm->tm_hour  = 12;  // Hour [0,23].
        tm->tm_mday  = 25;  // Day of month [1,31].
        tm->tm_mon   = 4;   // Month of year [0,11].
        tm->tm_year  = 108; // Years since 1900.
        tm->tm_wday  = 5;   // Day of week [0,6] (Sunday =0).
        tm->tm_yday  = 116; // Day of year [0,365].
        tm->tm_isdst = 0;   // Daylight Savings flag.
    }

    rtc_set_date(tm);

    val = to_bcd((tm->tm_year / 100) + 19);
    rtc_set_memory(REG_IBM_CENTURY_BYTE, val);
    rtc_set_memory(REG_IBM_PS2_CENTURY_BYTE, val);
}



//
// Connect bus ports
//
void busPortConnections(void) {

    rtc_handle = ppmOpenSlaveBusPort(
        PORT_NAME,
        &rtc_Window,
        2
    );

    ppmInstallChangeCallback(
        writeIndexCB,
        0,
        &rtc_Window[RTC_WINDOW_INDEX],
        1
    );

    ppmInstallWriteCallback(
        writeDataCB,
        0,
        &rtc_Window[RTC_WINDOW_DATA],
        1
    );
}

static void periodicTimerThread(void *user)
{
    for(;;) {

        if(periodicTimerRunning) {

            refreshData();
            bhmWaitDelay(nextPeriod);

            if (BHM_DIAG_HIGH)
                bhmMessage("I", PREFIX,"Periodic Timer Interrupt\n");

            rtc.cmos_data[RTC_REG_C] |= 0xc0;

            genInterrupt();

            if (BHM_DIAG_HIGH)
                dump_cmos_data();

        } else {
            if(bhmWaitEvent(startPTimer)) {      // wait for update
                bhmMessage("F", PREFIX,"periodic timer event not present\n");
            }
        }
    }
}

static void secondTimerThread(void *user)
{
    if (BHM_DIAG_MEDIUM)
        bhmMessage("I", PREFIX,"One Second Timer Thread Started\n");
    for(;;) {

        /* if the oscillator is not in normal operation, we do not update */
        if ((rtc.cmos_data[RTC_REG_A] & 0x70) == 0x20) {
            // if update enabled
            if (!(rtc.cmos_data[RTC_REG_B] & REG_B_SET)) {
                /* update in progress bit */
                rtc.cmos_data[RTC_REG_A] |= REG_A_UIP;
                if (BHM_DIAG_HIGH)
                    dump_cmos_data();

                refreshData();
                bhmWaitDelay(BHM_RTC_UPDATE_DELAY);

                rtc_update_current_tm();
                checkAlarm();

                // if update ended interrupt enabled
                if (rtc.cmos_data[RTC_REG_B] & REG_B_UIE) {
                    rtc.cmos_data[RTC_REG_C] |= 0x90;
                    if (BHM_DIAG_HIGH)
                        bhmMessage("I", PREFIX,"Update Ended Interrupt\n");
                    genInterrupt();
                }

                /* clear update in progress bit */
                rtc.cmos_data[RTC_REG_A] &= ~REG_A_UIP;
                if (BHM_DIAG_HIGH)
                    dump_cmos_data();

                refreshData();
                bhmWaitDelay(BHM_ONE_SECOND-BHM_RTC_UPDATE_DELAY);

            } else {
                bhmMessage("I", PREFIX,"waiting for enable. Current %u\n", rtc.cmos_data[RTC_REG_B] & REG_B_SET);
                if(bhmWaitEvent(updateEnableEvent)) {      // wait for update
                    bhmMessage("F", PREFIX,"waiting for enable: update enabled event not present\n");
                }
            }
        } else {
            bhmMessage("I", PREFIX,"waiting for osc mode. Current %u\n", rtc.cmos_data[RTC_REG_A] & 0x70);
            if(bhmWaitEvent(updateEnableEvent)) {      // wait for update
                bhmMessage("F", PREFIX,"waiting for osc mode: update enabled event not present\n");
            }
        }

        if (BHM_DIAG_HIGH)
            bhmMessage("I", PREFIX,"One Second Timer TICK %f\n", bhmGetCurrentTime());
    }
}

void userMainLoop(void)
{
    bhmEventHandle dummy;

    if (BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX,"User main\n");

    // create event and thread
    startPTimer = bhmCreateEvent();
    bhmCreateThread(
        periodicTimerThread,
        0,
        "periodicTimer",
        0
    );

    updateEnableEvent = bhmCreateEvent();
    bhmCreateThread(
        secondTimerThread,
        0,
        "secondTimer",
        0
    );

    // USER MAIN
    // Block forever. Behavior is triggered by register access
    dummy = bhmCreateEvent();
    bhmWaitEvent(dummy);
}


//
// reset
//
void userInit(void)
{
    if (BHM_DIAG_LOW)
        bhmMessage("I", PREFIX,"User initialization");
    if (BHM_DIAG_HIGH)
        bhmMessage("I", "MC146818RTC","Initialise Registers\n");

    // Set initial values on registers
    rtc.cmos_data[RTC_REG_A] = 0x26;
    rtc.cmos_data[RTC_REG_B] = 0x02;
    rtc.cmos_data[RTC_REG_C] = 0x00;
    rtc.cmos_data[RTC_REG_D] = 0x80;

    Bool readTimeFromHost;
    bhmBoolParamValue("timefromhost", &readTimeFromHost);

    rtc_set_date_from_host(readTimeFromHost);

    refreshData();
}

//
// Connect net ports
//
void netPortConnections(void) {
    intPortHandle = ppmOpenNetPort("timerInt");
    if(!intPortHandle)
        bhmMessage("W", "MC146818RTC","pin 'timerInt' should be connected\n");

}

//
// Main for rtc
//
PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    userInit();
    busPortConnections();
    netPortConnections();
    userMainLoop();
}


PPM_DESTRUCTOR_CB(destructor) {
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

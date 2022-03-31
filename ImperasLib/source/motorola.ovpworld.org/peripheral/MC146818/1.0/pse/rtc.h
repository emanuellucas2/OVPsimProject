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

#ifndef RTC_H_
#define RTC_H_

#include "time.h"

// register definitions and bits
#define RTC_SECONDS             0
#define RTC_SECONDS_ALARM       1
#define RTC_MINUTES             2
#define RTC_MINUTES_ALARM       3
#define RTC_HOURS               4
#define RTC_HOURS_ALARM         5
#define RTC_ALARM_DONT_CARE     0xC0

#define RTC_DAY_OF_WEEK         6
#define RTC_DATE_OF_MONTH       7
#define RTC_MONTH               8
#define RTC_YEAR                9

#define RTC_REG_A               10
#define RTC_REG_B               11
#define RTC_REG_C               12
#define RTC_REG_D               13

#define RTC_NUM_REGS            14

// The maximum register number that can be accessed
#define MAX_REG_ACCESS          63

const char *regName[RTC_REG_D+1] = {
    "RTC_SECONDS",
    "RTC_SECONDS_ALARM",
    "RTC_MINUTES",
    "RTC_MINUTES_ALARM",
    "RTC_HOURS",
    "RTC_HOURS_ALARM",
    "RTC_DAY_OF_WEEK",
    "RTC_DATE_OF_MONTH",
    "RTC_MONTH",
    "RTC_YEAR",
    "RTC_REG_A",
    "RTC_REG_B",
    "RTC_REG_C",
    "RTC_REG_D"
};

#define REG_A_UIP 0x80

#define REG_B_SET 0x80
#define REG_B_PIE 0x40
#define REG_B_AIE 0x20
#define REG_B_UIE 0x10

typedef struct  {
    Uns8 cmos_data[128];
    struct tm current_tm;
} RTCState, *RTCStateP;

const char *dayOfWeek[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; 

// These are Simulator delays used in bhmWaitDelay
// One second at a nominal 100MIPS rate
#define BHM_ONE_SECOND          1000000

// 244 micro seconds is the minimum update time for the RTC
#define BHM_RTC_UPDATE_DELAY    244

// offset to the index and data registers
#define RTC_WINDOW_INDEX        0
#define RTC_WINDOW_DATA         1

// the name of the port exposed
#define PORT_NAME               "busPort"

#endif /*RTC_H_*/

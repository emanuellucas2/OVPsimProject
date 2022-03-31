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

#pragma once

#include "peripheral/impTypes.h"

#ifndef PREFIX
#define PREFIX "CLINT"
#endif

#ifndef MAXHARTS
#define MAXHARTS 32
#endif


// Opaque timer handle
typedef struct timerDataS timerData, *timerDataP;

//
// Trigger a timer event
//  - call this to schedule an event for the timer's expiration
//  - call with timer == NULL after timer registers are modified to recalculate
//    and schedule the next timer expiration
//  - creates a timer event and/or thread if they do not exist
//
void scheduleTimer(timerDataP timer);

//
// Update the timer's data based on current mtime/mtimecmp[hartid] values
// - Call after change to mtimecmp for a single timer
// - Call after change to mtime for each timer
// The interrupt for the timer is updated based on the computed values
//
void updateTimerData(timerDataP timer);

//
// Update all timers
//
void updateAllTimerData();

//
// Compute the mtime counter value for the given time in microseconds
// - the value is adjusted based on any writes to the mtime register
//
Uns64 mtimeCountValue(double time);

//
// Update the mtime counter value
// - Save difference between counter value for current time and
//   the written mtime value, and use this offset to adjust the
//   counter value returned by mtimeCountValue()
//
void mtimeUpdate(Uns64 newMtime);

//
// Return timerData for given hartid
// - aborts on invalid hartid
//
timerDataP getTimer(Uns32 hartid);

//
// Clear interrupt output net if currently set
//
void clearInterrupt(timerDataP timer);

//
// Initialize timer structures
// - call from constructor
//
void initTimers(
    Uns32         numHartsIn,
    ppmNetHandle *timerInterruptsIn,
    Uns64        *mtimecmpValuesIn,
    double        clockMHzIn
);

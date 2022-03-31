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

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pse.igen.h"

#include "CLINT.timer.h"

// Timer clock duration in USEC
#define CLOCK_DURATION_USEC (1.0 / clockMHz)

// Use a rounding factor of 1/10th the counter clock duration to avoid jitter
#define ROUNDING_FACTOR_USEC (CLOCK_DURATION_USEC / 10)

// Convert a floating point time in microseconds to the corresponding
// number of ticks that will elapse in that time at the configured clock frequency
// NOTE: Add clockDelta before truncating double to integer to avoid jitter
//       for floating point calculations that round to just below an integer value
#define USECS_TO_TICKS(_U) ((Uns64)(((_U) * clockMHz) + clockDelta))

// Convert a number of ticks to the floating point time in microseconds
// at the configured clock frequency
#define TICKS_TO_USEC(_T) (((double)(_T)) / clockMHz)

// Convert a simulated time counter value to the mtime register
// counter value, taking into account most recent write to the mtime register
// (both the time of the write and the value written)
#define TIME_TO_MTIME(_T) ((_T) - mtimeOffset)

//
// State info for each timer
//
struct timerDataS {
    Uns32           hartid;             // this timer's hartid
    double          startTime;          // Time thread started in microseconds
    Uns64           startCount;         // Starting counter value
    Uns64           stopCount;          // Ending counter value
    double          threadDelay;        // Duration of timer in micro-seconds
    double          expirationTime;     // Time this event expires
    Bool            intSet;             // True when interrupt net is set
};

static Uns32           numharts;         // Number of timers
static double          clockMHz;         // Clock frequency in MHz from user parameter
static double          clockDelta;       // Delta to use to avoid rounding errors
static Uns64           mtimeOffset = 0;  // Offset to adjust for writes to mtime
static timerDataP      scheduledTimer;   // Currently scheduled timer
static bhmThreadHandle timerHandle;      // Handle for timer thread
static bhmEventHandle  timerEvent;       // Handle for triggering a timer event
static timerData      *timers;           // Array of timer data for each hart
static ppmNetHandle   *timerInterrupts;  // Array of interupt net handles for each hart
static Uns64          *mtimecmpValues;   // Array of current mtimecmp values for each hart

// Forward reference
static void timerThread(void *user);

//
// Workaround for PSE compiler bug when using printf %lld
// - buffer is only valid until next call (do not use multiple times on same
//   printf call)
//
static const char *uns64ToDecimal(Uns64 value) {
    static char buf[32];
    char *s = buf + sizeof(buf) - 1;

    // Zero terminate the string
    *s = '\0';

    do {
        *--s = '0' + (value % 10);
        value /= 10;
    } while (value != 0 && s != buf);

    return s;
}

//
// Set interrupt output net if not currently set
// - Issue diagnostic message if the current time does not match the
//   time that the timer was expected to expire, ehich can happen if
//   a timer is scheduled to expire before the end of the quantum it
//   was scheduled from.
//
static void setInterrupt(timerDataP timer) {

    if (!timer->intSet) {
        Uns32  hartid = timer->hartid;
        double now    = bhmGetLocalTime();
        double delta  = fabs(now - timer->expirationTime);
        Bool   error  = delta > (timer->threadDelay / 100.0);

        // Issue one time warning if more than 1% error due to quantum effects
        static Bool quantumWarningIssued = False;
        if (!quantumWarningIssued && error) {
            bhmMessage("W", PREFIX"_QTS",
                    "Quantum size is limiting timer accuracy. "
                    "Reduce quantum size if precise timer accuracy required.");
            quantumWarningIssued = True;
        }

        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX "_INTC",
                "timer[%d] @ %10.3fus: Timer expired - interrupt set",
                timer->hartid, now);
            if (error) {
                bhmMessage("I", PREFIX "_INTC",
                    "\t(Expected expiration time @ %10.3fus)",
                    timer->expirationTime);
            }
        }

        // trigger interrupt
        timer->intSet = True;
        ppmWriteNet(timerInterrupts[hartid], 1);
    }
}

//
// Timer loop:
// - Find the next timer that will expire
// - If a timer is found schedule an event to trigger at that time
// - Wait for an event:
//     - if scheduledTimer is not NULL then the event is that timer's expiration
// - Repeat loop
//
static void timerThread(void *user) {

    while (1) {
        timerDataP nextTimer = NULL;

        // Find next timer scheduled to expire
        Uns32 i;
        for (i = 0; i < numharts; i++) {
            timerDataP timer = getTimer(i);

            if (timer->expirationTime == DBL_MAX) {
                // Skip timers that have not been programmed yet or have been
                // set to the maximum value
            } else if (timer->intSet) {
                // Skip currently pending timers
            } else if (!nextTimer || nextTimer->expirationTime > timer->expirationTime) {
                // Earliest timer seen so far
                nextTimer = timer;
            }
        }

        if (nextTimer) {
            // schedule event for next timer expiration
            // - replaces any existing pending timer expiration
            scheduleTimer(nextTimer);
        }

        // Wait for a timer event
        bhmRestartReason reason = bhmWaitEvent(timerEvent);

        if (reason != BHM_RR_TRIGGERED) {
            bhmMessage("F", PREFIX, "Unexpected bhmRestartReason %d", reason);
        }

        // If this is a timer expiration event then trigger an interrupt
        if (scheduledTimer) {
            setInterrupt(scheduledTimer);

            // Clear currently scheduled timer after triggering
            scheduledTimer = NULL;
        }
    }
}

//
// Trigger a timer event
//  - call this to schedule an event for the timer's expiration
//  - call with timer == NULL after timer registers are modified to recalculate
//    and schedule the next timer expiration
//  - creates a timer event and/or thread if they do not exist
//
void scheduleTimer(timerDataP timer) {

    if (timerHandle == BHM_INVALID_HANDLE) {
        timerHandle = bhmCreateThread(timerThread, NULL, "Timer", 0);
    }

    if (timerEvent == BHM_INVALID_HANDLE) {
        timerEvent = bhmCreateNamedEvent("TimerEvent", "Event on timer thread");
    }

    if (timer) {
        double delay = timer->expirationTime - bhmGetLocalTime();

        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_SCHD",
                    "Next event scheduled: timer[%d] in %10.3fus @ %10.3fus",
                    timer->hartid, delay, timer->expirationTime);
        }

        if (delay < 0.0) {
            // This can happen because calling bhmGetLocalTime() from the thread
            // (i.e. non-processor) context can only give times at quantum
            // boundaries, and an event cannot be scheduled within a quantum
            // once that quantum has started. So just schedule event as early as
            // possible.
            delay = 0.0;
        }

        scheduledTimer = timer;
        bhmTriggerAfter(timerEvent, delay);

    } else {

        scheduledTimer = NULL;
        bhmTriggerEvent(timerEvent);

    }
}

//
// Update the timer's data based on current mtime/mtimecmp[hartid] values
// - Call after change to mtimecmp for a single timer
// - Call after change to mtime for each timer
// The interrupt for the timer is updated based on the computed values
//
void updateTimerData(timerDataP timer) {
    Uns32 hartid         = timer->hartid;
    Uns64 timecmp        = mtimecmpValues[hartid];
    Uns64 prevExpiration = timer->expirationTime;

    timer->startTime      = bhmGetLocalTime();
    timer->startCount     = mtimeCountValue(timer->startTime);
    timer->stopCount      = timecmp;

    if (timer->stopCount < timer->startCount) {
        // Don't allow negative delays - just trigger timer immediately
        timer->stopCount = timer->startCount;
    }

    if (timecmp == -1ULL) {

        // Disable timer when mtimecmp is at the max value for simulator
        // efficiency
        timer->threadDelay    = DBL_MAX;
        timer->expirationTime = DBL_MAX;

        if (PSE_DIAG_MEDIUM && prevExpiration != timer->expirationTime) {
            bhmMessage("I", PREFIX "_SCHD",
                    "timer[%d] @ %10.3fus disabled: mtimecmp=-1",
                    timer->hartid, timer->startTime);
        }

    } else {

        timer->threadDelay    = TICKS_TO_USEC(timer->stopCount - timer->startCount);
        timer->expirationTime = timer->startTime + timer->threadDelay;

        if (PSE_DIAG_MEDIUM && prevExpiration != timer->expirationTime) {
            bhmMessage("I", PREFIX "_SCHD", "timer[%d] @ %10.3fus", timer->hartid, timer->startTime);
            bhmMessage("I", PREFIX "_SCHD", "  mtime=%s", uns64ToDecimal(timer->startCount));
            bhmMessage("I", PREFIX "_SCHD", "  mtimecmp=%s", uns64ToDecimal(timecmp));
            bhmMessage("I", PREFIX "_SCHD", "  threadDelay=%10.3fus", timer->threadDelay);
            bhmMessage("I", PREFIX "_SCHD", "  expirationTime=%10.3fus", timer->expirationTime);
        }
    }

    // Update interrupt based on current mtime and mtimecmp values
    // - this is required to reflect changes due to writes to mtime register
    if (timer->stopCount <= timer->startCount) {
        // timecmp value has already been reached
        setInterrupt(timer);
    } else {
        clearInterrupt(timer);
    }
}

//
// Update all timers
//
void updateAllTimerData() {
    Uns32 hartid;

    for (hartid = 0; hartid < numharts; hartid++) {
        updateTimerData(getTimer(hartid));
    }

    // Recalulate next timer expiration
    scheduleTimer(NULL);
}

//
// Compute the mtime counter value for the given time in microseconds
// - the value is adjusted based on any writes to the mtime register
//
Uns64 mtimeCountValue(double time) {
    Uns64  ticks  = USECS_TO_TICKS(time);
    Uns64  mtime  = TIME_TO_MTIME(ticks);

    return mtime;
}

//
// Update the mtime counter value
// - Save difference between counter value for current time and
//   the written mtime value, and use this offset to adjust the
//   counter value returned by mtimeCountValue()
//
void mtimeUpdate(Uns64 newMtime) {
    Uns64 ticksNow  = USECS_TO_TICKS(bhmGetLocalTime());

    mtimeOffset = ticksNow - newMtime;
}

//
// Return timerData for given hartid
// - aborts on invalid hartid
//
timerDataP getTimer(Uns32 hartid) {
    if (hartid > numharts) {
        bhmMessage("F", PREFIX, "Invalid hartid %d", hartid);
    }
    return timers+hartid;
}

//
// Clear interrupt output net if currently set
//
void clearInterrupt(timerDataP timer) {

    if (timer->intSet) {
        Uns32 hartid = timer->hartid;

        if (PSE_DIAG_MEDIUM) {
            double now = bhmGetLocalTime();
            bhmMessage("I", PREFIX "_INTC",
                "timer[%d] @ %10.3fus: Interrupt cleared",
                timer->hartid, now);
        }

        // clear interrupt
        timer->intSet = False;
        ppmWriteNet(timerInterrupts[hartid], 0);
    }
}

//
// Initialize timer structures
// - call from constructor
//
void initTimers(
    Uns32         numHartsIn,
    ppmNetHandle *timerInterruptsIn,
    Uns64        *mtimecmpValuesIn,
    double        clockMHzIn
) {

    if (numHartsIn > MAXHARTS) {
        bhmMessage("F", PREFIX "_NHI",
            "numharts=%d exceeds maximum number allowed=%d",
            numHartsIn, MAXHARTS);
        // Not reached
    }

    numharts        = numHartsIn;
    timerInterrupts = timerInterruptsIn;
    mtimecmpValues  = mtimecmpValuesIn;
    clockMHz        = clockMHzIn;

    // Compute only once to improve performance
    clockDelta = ROUNDING_FACTOR_USEC;

    // Allocate timer structures
    timers = (timerDataP) calloc(numharts, sizeof(timerData));

    // Initialize hartid and expiration time for each timer
    Uns32 i;
    for (i = 0; i < numharts; i++) {
        timerDataP timer = getTimer(i);

        timer->hartid = i;
        timer->expirationTime = DBL_MAX;
    }

    timerHandle = BHM_INVALID_HANDLE;
    timerEvent  = BHM_INVALID_HANDLE;
}

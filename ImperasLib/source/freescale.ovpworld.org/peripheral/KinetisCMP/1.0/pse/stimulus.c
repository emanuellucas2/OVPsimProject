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


#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <errno.h>

#include "pse.igen.h"
#include "stimulus.h"

//
// Read a line from the file and write into the channel structure
// at EOF in the file, reset to 0
//
static void setNextStimLine(Uns32 ch) {
    if (cmp_in.fp != NULL) {

        char *rc = fgets(buffer, BUFFSIZE, cmp_in.fp);
        double now, next;
        Uns32  extSample_value;
        Uns32  vin_value;
        Uns32  minus_value;
        Uns32  plus_value;

        if (NULL==rc) {
            bhmMessage("I", "PARSE", "Stimulus reader Unrecoverable Error ch%d File Empty", cmp_in.chNum);
            return;
        }

        if (rc) {
            //
            // Read was OK
            //
            Int32 matches = sscanf(buffer, "%lf, 0x%08x, 0x%08x, 0x%08x, 0x%08x",
                &now, &extSample_value, &vin_value, &minus_value, &plus_value);
            if (matches != 5) {
                bhmMessage("F", "PARSE", "Stimulus reader cannot parse ch%d line:'%s'", cmp_in.chNum, buffer);
            }
//            cmp_in.now += now;
            cmp_in.now = now;
            cmp_in.extSample_value = extSample_value;
            cmp_in.vin_value = vin_value;
            cmp_in.minus_value = minus_value;
            cmp_in.plus_value = plus_value;

            /* if (-1 == cmp_in.next) {
              cmp_in.next = now;
            } else */{

                // Try to peek forward to the next line ?
                // Then undo
                Int64 fpos = ftell(cmp_in.fp);
                rc = fgets(buffer, BUFFSIZE, cmp_in.fp);
                fseek(cmp_in.fp, fpos, 0);

                if (rc==NULL) {
                    //
                    // reset to ZERO
                    //
                    fseek(cmp_in.fp, 0, 0);
                    rc = fgets(buffer, BUFFSIZE, cmp_in.fp);
                    fseek(cmp_in.fp, 0, 0);
                }

                if (rc) {
                    matches = sscanf(buffer, "%lf, 0x%08x, 0x%08x, 0x%08x, 0x%08x",
                        &next, &extSample_value, &vin_value, &minus_value, &plus_value);
                    if (matches != 5) {
                        bhmMessage("F", "PARSE", "Stimulus reader cannot parse ch%d line:'%s'", cmp_in.chNum, buffer);
                    }
//                    cmp_in.next = cmp_in.now + next;
                    cmp_in.next = next;
                } else {
                    cmp_in.next = 0;
                }

            }
        } else {
            bhmMessage("F", "PARSE", "Stimulus reader Unrecoverable error ch%d", ch);
        }

        //
        // Are we in ASYNC or SYNC mode
        //
//        if (cmp_in.now == -1) {
//            cmp_in.mode = ASYNC;
//        } else {
//            cmp_in.mode = SYNC;
//        }
    }
}

//
// Given a channel, get the value
// Synchronous Mode:    check the timestamps against current time
// Asynchronous Mode:   get the next value in the file
//
/*
void getAnalogValue(captureInfo cap) {
    //
    // Iterate all potential analog inputs
    //
    Int32 ani = cap.ANI;

    for (ani=0; ani<ANIN; ani++) {
        //
        // Check for the file descriptor, if it is not open then early return
        // Simply setting the datestamp
        //
        if (adcin[ani].fp == NULL) {
            adcin[ani].now = cap.time;
            return;
        }

        //
        // If the mode is ASYNChronous - just get next value
        //
        if (adcin[ani].mode == ASYNC) {
            setNextStimLine(ani);
        } else {
            //
            // If mode is SYNChronous align the timestamps
            // If the first read indicates ASYNChronous
            // Then this will drop out on the first iteration
            //
            if (adcin[ani].next == -1) setNextStimLine(ani); // Initialisation
            while (adcin[ani].next < cap.time) {
                setNextStimLine(ani);
            }
        }
    }

    return;
}
*/

void getValue(captureInfo* capP) {
    Uns32 ch = 0;
    if (cmp_in.fp == NULL) {
        cmp_in.now = capP->time;
    } else if (cmp_in.mode == ASYNC) {
//        bhmMessage("I", "KinetisCMP", "ASYNC:Calling setNextStimLine()");
        setNextStimLine(ch);
    } else { // SYNC
//        bhmMessage("I", "KinetisCMP", "SYNC:Calling setNextStimLine()");
        if (cmp_in.next == -1) setNextStimLine(ch); // Initialisation
        while (cmp_in.next < capP->time) {
            setNextStimLine(ch);
        }
    }
    return;
}

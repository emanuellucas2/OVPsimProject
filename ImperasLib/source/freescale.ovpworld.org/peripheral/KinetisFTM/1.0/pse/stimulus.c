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
    if (ftm_in[ch].fp != NULL) {

        char *rc = fgets(buffer, BUFFSIZE, ftm_in[ch].fp);
        double now, next;
        Uns32  phaseA_value;
        Uns32  phaseB_value;

        if (NULL==rc) {
            bhmMessage("F", "PARSE", "Stimulus reader Unrecoverable Error ch%d File Empty", ch);
        }

        if (rc) {
            //
            // Read was OK
            //
            Int32 matches = sscanf(buffer, "%lf, 0x%03x, 0x%03x", &now, &phaseA_value, &phaseB_value);
            if (matches != 3) {
                bhmMessage("F", "PARSE", "Stimulus reader cannot parse ch%d line:'%s'", ch, buffer);
            }
//            ftm_in[ch].now += now;
            ftm_in[ch].now = now;
//            ftm_in[ch].value = value; // value << 6;   // shift to upper bits of short
            ftm_in[ch].phaseA_value = phaseA_value;
            ftm_in[ch].phaseB_value = phaseB_value;

            /* if (-1 == ftm_in[ch].next) {
              ftm_in[ch].next = now;
            } else */{

                // Try to peek forward to the next line ?
                // Then undo
                Int64 fpos = ftell(ftm_in[ch].fp);
                rc = fgets(buffer, BUFFSIZE, ftm_in[ch].fp);
                fseek(ftm_in[ch].fp, fpos, 0);

                if (rc==NULL) {
                    //
                    // reset to ZERO
                    //
                    fseek(ftm_in[ch].fp, 0, 0);
                    rc = fgets(buffer, BUFFSIZE, ftm_in[ch].fp);
                    fseek(ftm_in[ch].fp, 0, 0);
                }

                if (rc) {
                    matches = sscanf(buffer, "%lf, 0x%03x, 0x%03x", &next, &phaseA_value, &phaseB_value);
                    if (matches != 3) {
                        bhmMessage("F", "PARSE", "Stimulus reader cannot parse ch%d line:'%s'", ch, buffer);
                    }
//                    ftm_in[ch].next = ftm_in[ch].now + next;
                    ftm_in[ch].next = next;
                } else {
                    ftm_in[ch].next = 0;
                }

            }
        } else {
            bhmMessage("F", "PARSE", "Stimulus reader Unrecoverable error ch%d", ch);
        }

        //
        // Are we in ASYNC or SYNC mode
        //
//        if (ftm_in[ch].now == -1) {
//            ftm_in[ch].mode = ASYNC;
//        } else {
//            ftm_in[ch].mode = SYNC;
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
    if (ftm_in[ch].fp == NULL) {
        ftm_in[ch].now = capP->time;
    } else if (ftm_in[ch].mode == ASYNC) {
//        bhmMessage("I", "Kinetis60FTM", "ASYNC:Calling setNextStimLine()");
        setNextStimLine(ch);
    } else { // SYNC
//        bhmMessage("I", "Kinetis60FTM", "SYNC:Calling setNextStimLine()");
        if (ftm_in[ch].next == -1) setNextStimLine(ch); // Initialisation
        while (ftm_in[ch].next < capP->time) {
            setNextStimLine(ch);
        }
    }
    return;
}

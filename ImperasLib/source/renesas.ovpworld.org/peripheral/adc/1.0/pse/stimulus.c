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
//                          Fri Sep 14 13:40:24 2012
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <errno.h>

#include "pse.igen.h"
#include "stimulus.h"

#define PREFIX "ADC_STIM"
//
// Read a line from the file and write into the channel structure
// at EOF in the file, reset to 0
//
static void setNextStimLine(Uns32 ch) {
    //
    // Only read a new value if the CHOK status is set
    //
    if (adcin[ch].fp != NULL) {

        char *rc = fgets(buffer, BUFFSIZE, adcin[ch].fp);
        double now, next;
        Uns32  value;

        if (rc==NULL) {
            bhmMessage("F", PREFIX"_PARSE", "Stimulus reader Unrecoverable Error ch%d File Empty", ch);
        }

        if (rc) {
            //
            // Read was OK
            //
            Int32 matches = sscanf(buffer, "%lf, 0x%03x", &now, &value);
            if (matches != 2) {
                bhmMessage("F", PREFIX"_PARSE", "Stimulus reader cannot parse ch%d line:'%s'", ch, buffer);
            }
            adcin[ch].now += now;
            adcin[ch].value = value << 6;   // shift to upper bits of short

            //
            // Try to peek forward to the next line ?
            // Then undo
            //
            Int64 fpos = ftell(adcin[ch].fp);
            rc = fgets(buffer, BUFFSIZE, adcin[ch].fp);
            fseek(adcin[ch].fp, fpos, 0);

            if (rc==NULL) {
                //
                // reset to ZERO
                //
                fseek(adcin[ch].fp, 0, 0);
                rc = fgets(buffer, BUFFSIZE, adcin[ch].fp);
                fseek(adcin[ch].fp, 0, 0);
            }

            if (rc) {
                matches = sscanf(buffer, "%lf, 0x%03x", &next, &value);
                if (matches != 2) {
                    bhmMessage("F", PREFIX"_PARSE", "Stimulus reader cannot parse ch%d line:'%s'", ch, buffer);
                }
                adcin[ch].next = adcin[ch].now + next;
            } else {
                adcin[ch].next = 0;
            }

        } else {
            bhmMessage("F", PREFIX"_PARSE", "Stimulus reader Unrecoverable error ch%d", ch);
        }

        //
        // Are we in ASYNC or SYNC mode
        //
        if (adcin[ch].now == -1) {
            adcin[ch].mode = ASYNC;
        } else {
            adcin[ch].mode = SYNC;
        }
    }
}

//
// These functions should be intercepted by a plant model
//
FUNCTOHOST(Uns32, interceptPlantReadVoltageResult, void)
FUNCTOHOST(Uns32, interceptPlantReadCurrentResult, void)

//
// Given a channel, get the value
// Synchronous Mode:    check the timestamps against current time
// Asynchronous Mode:   get the next value in the file
//
void getAnalogValue(captureInfo cap) {
    //
    // Iterate all potential analog inputs
    //
    Int32 ani = cap.ANI;

    for (ani=0; ani<ANIN; ani++) {
        //
        // Check for plant model enabled
        //
        if (adcin[ani].plantEnable) {
            switch (adcin[ani].plantMode) {
            case 0:
                //
                adcin[ani].value = interceptPlantReadVoltageResult();
                if (DIAG_HIGH) bhmMessage("I", PREFIX, "interceptPlantReadVoltageResult %d", adcin[ani].value);
                break;
            case 1:
                //
                adcin[ani].value = interceptPlantReadCurrentResult();
                if (DIAG_HIGH) bhmMessage("I", PREFIX, "interceptPlantReadCurrentResult %d", adcin[ani].value);
                break;
            default:
                adcin[ani].value = 0;
                if (DIAG_LOW) bhmMessage("W", PREFIX"_GET_ANALOGUE",
                        "Plant Mode Enabled but unknown mode %d",
                        adcin[ani].plantMode);
                break;
            }
        } else {

            //
            // Check for the file descriptor, if it is not open then early return
            // Simply setting the datestamp
            //
            if (adcin[ani].fp == NULL) {
                adcin[ani].now = cap.time;
                break;
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
    }

    return;
}

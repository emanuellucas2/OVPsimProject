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


#ifndef _KinetisFTM_STIMULUS_
#define _KinetisFTM_STIMULUS_

// #include "pse.igen.h"

// Stimulus file format
// <time>, <phaseA value>, <phaseB value>
// time  ::=  <abs-microseconds>   // | -1 (for modes other than quadrature
// value ::= 0xhhh

#define BUFFSIZE BHM_MAX_PATH
char buffer[BUFFSIZE];

// Channel Mode of operation Sync or async
#define SYNC  0
#define ASYNC 1

// Number of FTM channels
#define NUM_CHANNELS 1   // Only 1 for Quadrature; otherwise 8
typedef struct ftm_inS {
    FILE  *fp;          // This is the FILE pointer to the associated file stream, either NULL or non-NULL
    Int32  mode;        // Is the Channel ASYNC (just read values) or SYNC (bind values to time)
    double now, next;   // Time at which Value is valid (now), Time for next value
    ppmNetValue  phaseA_value;       // Value at Time
    ppmNetValue  phaseB_value;       // Value at Time
} ftm_inT, *ftm_inP;

ftm_inT ftm_in[NUM_CHANNELS];

// typedef struct captureInfoS {
//     double time;    // Time of capture
//     Uns8 BS;        // Buffer Mode
//     Uns8 MS;        // Select Mode
//     Uns8 ANI;       // Analog input
// } captureInfo, *captureInfoP;
typedef struct captureInfoS {
    double time;        // Time of capture
    ppmNetValue phaseA;
    ppmNetValue phaseB;
} captureInfo, *captureInfoP;

//
// Given a channel, get the value
// Synchronous Mode:    check the timestamps against current time
// Asynchronous Mode:   get the next value in the file
//
// void getAnalogValue(captureInfo cap);
void getValue(captureInfo* capP);

#endif

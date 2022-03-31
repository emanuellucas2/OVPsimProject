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


#ifndef _KinetisCMP_STIMULUS_
#define _KinetisCMP_STIMULUS_

// #include "pse.igen.h"

// Stimulus file format
// <time>, <extSample value>, <vin value>, <minus value>, <plus value>,
// time  ::=  <abs-microseconds>  
// value ::= 0xhhhhhhhh
// The specific inputs to which the <vin value>, <minus value>, and 
// <plus value> are applied are determined through the command line "configure"
// option bits:
#define BUFFSIZE BHM_MAX_PATH
char buffer[BUFFSIZE];

// Channel Mode of operation Sync or async
#define SYNC  0
#define ASYNC 1

// Number of FTM channels
typedef struct cmp_inS {
    Uns32  chNum;       // Comparator/Channel number for this instance of the comparator.
    FILE  *fp;          // This is the FILE pointer to the associated file stream, either NULL or non-NULL
    Int32  mode;        // Is the Channel ASYNC (just read values) or SYNC (bind values to time)
    double now, next;   // Time at which Value is valid (now), Time for next value
    ppmNetValue  extSample_value;    // external sample value at Time
    ppmNetValue  vin_value;          // Reference voltage value at Time
    ppmNetValue  minus_value;        // minus value at Time
    ppmNetValue  plus_value;         // plus value at Time
} cmp_inT, *cmp_inP;

cmp_inT cmp_in;

// typedef struct captureInfoS {
//     double time;    // Time of capture
//     Uns8 BS;        // Buffer Mode
//     Uns8 MS;        // Select Mode
//     Uns8 ANI;       // Analog input
// } captureInfo, *captureInfoP;
typedef struct captureInfoS {
    double time;        // Time of capture
    ppmNetValue extSample_value;
    ppmNetValue vin_value;
    ppmNetValue minus_value;
    ppmNetValue plus_value;
} captureInfo, *captureInfoP;

//
// Given a channel, get the value
// Synchronous Mode:    check the timestamps against current time
// Asynchronous Mode:   get the next value in the file
//
// void getAnalogValue(captureInfo cap);
void getValue(captureInfo* capP);

#endif

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

#ifndef _ADC_STIMULUS_
#define _ADC_STIMULUS_

#include "pse.igen.h"

#define DIAG_LOW  ((diagnosticLevel & 0x0f) >= 1)
#define DIAG_MED  ((diagnosticLevel & 0x0f) >= 2)
#define DIAG_HIGH ((diagnosticLevel & 0x0f) >= 3)

//
// Stimulus file format
// <time>, <value>
// time  ::= -1 | <abs-microseconds>
// value ::= 0xhhh
//
#define BUFFSIZE BHM_MAX_PATH
char buffer[BUFFSIZE];

//
// Channel Mode of operation Sync or async
//
#define SYNC  0
#define ASYNC 1

//
// Number of Analog inputs, and associated channels
//
#define ANIN 10
typedef struct adcinS {
    Bool   plantEnable; // True running in plant mode
    Uns32  plantMode;   // which of the plant model channels (0=Vo, 1=iL)
    FILE  *fp;          // This is the FILE pointer to the associated file stream, either NULL or non-NULL
    Int32  mode;        // Is the Channel ASYNC (just read values) or SYNC (bind values to time)
    double now, next;   // Time at which Value is valid (now), Time for next value
    Uns32  value;       // Value at Time
} adcinT, *adcinP;
adcinT adcin[ANIN];

typedef struct captureInfoS {
    double time;    // Time of capture
    Uns8 BS;        // Buffer Mode
    Uns8 MS;        // Select Mode
    Uns8 ANI;       // Analog input
} captureInfo, *captureInfoP;

//
// Given a channel, get the value
// Synchronous Mode:    check the timestamps against current time
// Asynchronous Mode:   get the next value in the file
//
void getAnalogValue(captureInfo cap);

#endif

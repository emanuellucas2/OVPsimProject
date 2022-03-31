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
//                          Wed Jan 12 17:58:14 2011
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"
#include "peripheral/bhmHttp.h"

#define PREFIX "TEMP_SENSOR"

#define MAXLINE    32
FILE   *dataFP = NULL;   // file for temperature configuration
double  rate;            // rate of change of temperature
double  temperature;     // current temperature
double  limitTemperature;  // max temperature when using rate change
typedef struct tempDataS {
    float time;
    float value;
} tempData;

#define MAX_FILE_INPUT 64
tempData tData[MAX_FILE_INPUT];

//////////////////////////////// Visualization ////////////////////////////////

static BHM_HTTP_GET_FN(get) {

    Uns32 value = (Uns32)temperature;

    bhmHTTPElementOpen(ch, "ovpelement");

    bhmHTTPKeyPrintf(ch, "gauge0", "%d",  value);

    bhmHTTPKeyPrintf(ch, "power0", "");

    bhmHTTPElementClose(ch, "ovpelement");
    bhmHTTPSend(ch);
}

static BHM_HTTP_POST_FN(post) {
    if (strstr(body, "power0=clicked")) {
        bhmMessage("I", PREFIX "_SW", "Power Switch pushed - terminating simulation.");
        bhmFinish();
    }
}

//////////////////////////////// User Functions ////////////////////////////////

// populate an internal array with the file values
// this is done for easier reference
void initTemperatureArray(char *dataFile) {

    if(!(dataFP = fopen(dataFile, "r"))) {
        bhmMessage("E", PREFIX "_NCF", "Could not open file '%s'", dataFile);
    } else {

        if(BHM_DIAG_LOW)
            bhmMessage("I", PREFIX "_FTI", "Initialize Temperature Data from file %s", dataFile);

        Uns32 index = 0;

        char line[MAXLINE];
        while (fgets(line, MAXLINE, dataFP) != NULL){
            if (line[0] == '#') {
                // Ignore comment line
            } else {
                Uns32 items;
                float ftime = 0;
                float ftemp = 0;

                // read data file line
                // contains <time in seconds> <temperature in oC>
                if ((items = sscanf(line, "%f %f", &ftime, &ftemp)) == 2) {
                    if(BHM_DIAG_LOW)
                        bhmMessage("I", PREFIX "_FT", "File: index %d time %4.2f temperature %f", index, ftime, ftemp);

                    if (index < MAX_FILE_INPUT) {
                        tData[index].time  = ftime;
                        tData[index].value = ftemp;
                        index++;
                    } else {
                        bhmMessage("W", PREFIX "_FTO", "Failed to read entry %d, max entries %d reached", index, MAX_FILE_INPUT);
                    }
                } else {
                    bhmMessage("W", PREFIX "_FW", "File: ignore line with incorrect entries '%s'", line);
                }
            }
        }
    }
}

//
// Calculate or read from file the current temperature
//
void getTemperature() {

    // get current time in seconds
    double now = bhmGetLocalTime()/1000000;

    if (dataFP) {
        Uns32 index = 0;
        // find the next entry
        while(index < MAX_FILE_INPUT+1) {
            // the current index is for future entry
            if ((double)tData[index+0].time > now) {
                break;
            }
            // current entry within time
            if((double)tData[index+1].time > now) {
                // next is future so use current
                temperature = tData[index].value;
                break;
            }
            index++;
        }
    } else {
        static double lastTime;

        // convert time in uS to time in seconds
        temperature += (rate * (now - lastTime));
        if(temperature > limitTemperature) {
            // fix at maximum
            temperature = limitTemperature;
        }
        lastTime     = now;
    }

    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX "_T", "Temperature %4.2f at %4.2f Seconds", temperature, now);
}

//////////////////////////////// Callback stubs ////////////////////////////////


PPM_REG_READ_CB(readData) {

    // conversion to register storage format
    // store value with 2 decimal places
    getTemperature();
    Bool negFlag = 0;
    float localTemp = temperature;
    if (temperature < 0) {
        localTemp = -temperature;
        negFlag = 1;
    }

    Uns32 tempReg = (Uns32)(localTemp*100);
    // set top bit to indicate negative
    if(negFlag) tempReg |= 0x80000000;

    // write value to register storage
    *(Uns32 *) user = tempReg;
    // return value
    return tempReg;
}

#define BUFSIZE 128000
static char space[BUFSIZE];

PPM_CONSTRUCTOR_CB(config) {

    periphConstructor();

    // temperature file not specified
    bhmDoubleParamValue("inittemp", &temperature);     // write initial value of temperature
    bhmDoubleParamValue("maxtemp", &limitTemperature); // maxium temperature when using rate
    bhmDoubleParamValue("ratechange", &rate);          // set rate

    // configure file to read temperature from
    char dataFile[BHM_MAX_PATH];
    if(bhmStringParamValue("datafile", dataFile, sizeof(dataFile))) {
        initTemperatureArray(dataFile);
    } else {
        if(BHM_DIAG_HIGH)
            bhmMessage("I", PREFIX "_INIT", "Temperature change Initial %4.2f oC Max %4.2f oC"
                                            " Rate of Change %4.2f oC per second",
                                            temperature, limitTemperature, rate);

    }

    // visualization (enabled with global command line argument)
    bhmHTTPMethods m = { get, post, space, BUFSIZE, 0 };
    bhmHTTPOpen(&m, "httpvis");

    // wait for end of simulation
    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
}



PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


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

#ifndef POWERMONITOR_USER_H
#define POWERMONITOR_USER_H

// define available rails to monitor
#ifndef RAILMON_MAX
    #error RAILMON_MAX is undefined. It must be set to the number of rails this device can monitor.
#endif

// include common power monitor data types
#include "ovpworld.org/modelSupport/powermonitor/1.0/pse/powermonitor.datatypes.h"

typedef struct itemS {
    Uns32 ref;          // unique index of the rail in the platform
    Uns32 value;        // current value
} itemT, *itemTP;

typedef struct monItemS {
    char       *name;   // name of the rail e.g. Vcc3v3
    itemT       data;   // reference index and value
    dataFormatE format; // register format of data
    dataTypeE   type;   // register type
    Bool        poil;   // set True if configured for Power Intercept Library usage
} monItemT, *monItemTP;

typedef struct vmonS {
    monItemT voltage[RAILMON_MAX];
    monItemT current[RAILMON_MAX];
    monItemT power[RAILMON_MAX];
    monItemT status_temp;
    monItemT temp1;
    monItemT temp2;
    monItemT temp3;
    monItemT tempSensor;
    monItemT last;
} vmonT, *vmonTP;

// defines the number of other monitored items excluding voltage, current, power and last
#define OTHERMONS     5
// maximum number of monitors
#define MON_MAX       (RAILMON_MAX + OTHERMONS)

#endif

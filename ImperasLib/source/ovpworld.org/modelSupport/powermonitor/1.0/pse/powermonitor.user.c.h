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

#ifndef POWERMONITOR_USER_C_H
#define POWERMONITOR_USER_C_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//////////////////////////////// intercepted Functions  ////////////////////////

#define UNUSED    __attribute__((unused))

//
// intercepted native function: passes initialisation info
//
FUNCTOHOST(Uns32, initNative, Uns32 diag)

//
// intercepted native function: requests current value
//
FUNCTOHOST(Uns32, getRailValue, Uns32 reference, Uns32 value, dataTypeE type, dataFormatE format)

//
// intercepted native function: set the rail value
//
FUNCTOHOST(Uns32, setRailValue, Uns32 reference, Uns32 value, dataTypeE type, dataFormatE format)

//
// intercepted native function: initialize the rail value
//
FUNCTOHOST(Uns32, initRailValue, Uns32 reference, Uns32 value, dataTypeE type, dataFormatE format)

//
// Read the rail configuration file
//

// indexes used from configuration files to setup temperature
#define STSTEMP_CFG_INDEX       0
#define TEMP1_CFG_INDEX         1
#define TEMP2_CFG_INDEX         2
#define TEMP3_CFG_INDEX         3
#define TEMPSENSOR_CFG_INDEX    4
// Set to the last temperature index
#define MAX_TEMP_CFG_INDEX  TEMPSENSOR_CFG_INDEX

void addMonitor(monItemTP mon, char *type, char * name, Uns32 ref, Uns32 init) {
    mon->name       = strdup(name);
    mon->data.ref   = ref;
    mon->data.value = init;
    mon->poil       = True;

    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_INIT_MON", "%s Monitor %d is %s, init value %d",
                type, mon->data.ref, mon->name, init);

}

//
// Initialise the power intercept library
// This must be called at simulation start to ensure library loaded
// WARNING: This must be the last function call in the peripheral constructor
//

void initPowerMonitorData() {

    // wait for simulation start
    // must ensure that any intercept libraries are installed
    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION));

    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX "_PMD_INIT", "Start Initialization");

    Uns32 position;
    for (position=0;position<RAILMON_MAX;position++) {
        // configure power library initial values
        if(vmon.voltage[position].poil) {
            vmon.voltage[position].format = PMBUS_LINEAR16;
            vmon.voltage[position].type   = VOLTAGE;
            if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_PMD_V", "%d", position);
            initRailValue(vmon.voltage[position].data.ref, vmon.voltage[position].data.value, VOLTAGE, PMBUS_LINEAR16);
        }
        if(vmon.current[position].poil) {
            vmon.current[position].format = PMBUS_LINEAR11;
            vmon.current[position].type   = CURRENT;
            if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_PMD_C", "%d", position);
            initRailValue(vmon.current[position].data.ref, vmon.current[position].data.value, CURRENT, PMBUS_LINEAR11);
        }
        if(vmon.power[position].poil) {
            vmon.power[position].format = PMBUS_LINEAR11;
            vmon.power[position].type   = POWER;
            if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_PMD_P", "%d", position);
            initRailValue(vmon.power[position].data.ref,   vmon.power[position].data.value,   POWER,   PMBUS_LINEAR11);
        }
    }
    // initialize the temperature
    // Only updated if PMBus
    if(vmon.status_temp.poil) {
        vmon.status_temp.format = PMBUS_LINEAR11;
        vmon.status_temp.type   = TEMPERATURE;
        if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_PMD_T", "Status Temperature");
        initRailValue(vmon.status_temp.data.ref, vmon.status_temp.data.value, TEMPERATURE, PMBUS_LINEAR11);
    }
    if(vmon.temp1.poil) {
        vmon.temp1.format = PMBUS_LINEAR11;
        vmon.temp1.type   = TEMPERATURE;
        if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_PMD_T", "Temperature 1");
        initRailValue(vmon.temp1.data.ref,       vmon.temp1.data.value,       TEMPERATURE, PMBUS_LINEAR11);
    }
    if(vmon.temp2.poil) {
        vmon.temp2.format = PMBUS_LINEAR11;
        vmon.temp2.type   = TEMPERATURE;
        if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_PMD_T", "Temperature 2");
        initRailValue(vmon.temp2.data.ref,       vmon.temp2.data.value,       TEMPERATURE, PMBUS_LINEAR11);
    }
    if(vmon.temp3.poil) {
        vmon.temp3.format = PMBUS_LINEAR11;
        vmon.temp3.type   = TEMPERATURE;
        if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_PMD_T", "Temperature 3");
        initRailValue(vmon.temp3.data.ref,       vmon.temp3.data.value,       TEMPERATURE, PMBUS_LINEAR11);
    }
    if(vmon.tempSensor.poil) {
        vmon.tempSensor.format = PMBUS_LINEAR11;
        vmon.tempSensor.type   = TEMPERATURE;
        if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_PMD_T", "Temperature Sensor");
        initRailValue(vmon.tempSensor.data.ref,  vmon.tempSensor.data.value,  TEMPERATURE, PMBUS_LINEAR11);
    }
}

void readConfiguration(char *configfile) {

    FILE *configFileFP = NULL;
    if (!(configFileFP = fopen(configfile, "r"))) {
        bhmMessage("W", PREFIX"_INIT_NCF", "config file '%s' could not be opened", configfile);
    } else {
        // Read configuration information
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX "_INIT_CN", "Initializing Data");

        char line[BHM_MAX_PATH];
        while (fgets(line, BHM_MAX_PATH, configFileFP) != NULL){
            if (line[0] == '#') {
                // Ignore comment line
            } else {
                Uns32 items;           // number of parsed items
                Uns32 position;        // monitor number in peripheral
                Uns32 ref;             // monitor unique reference in platform
                char monitorName[32];  // name of the monitor
                char type;             // type of monitor T, C, V
                Uns32 init;            // initial data value
                if (((items = sscanf(line, "%c%d%d%s%d", &type, &position, &ref, monitorName, &init)) == 5) ||
                    ((items = sscanf(line, "%c%d%d%s0x%x", &type, &position, &ref, monitorName, &init)) == 5))    {
                    if(position>MON_MAX) {
                        bhmMessage("W", PREFIX "_INIT_NV", "Specified monitor position %d above max %d", position, MON_MAX);
                    } else {
                        if (type == 'T') {
                            switch(position) {
                            case STSTEMP_CFG_INDEX:
                                addMonitor(&vmon.status_temp, "Status Temperature", monitorName, ref, init);
                                break;
                            case TEMP1_CFG_INDEX:
                                addMonitor(&vmon.temp1, "Temperature 1", monitorName, ref, init);
                                break;
                            case TEMP2_CFG_INDEX:
                                addMonitor(&vmon.temp2, "Temperature 2", monitorName, ref, init);
                                break;
                            case TEMP3_CFG_INDEX:
                                addMonitor(&vmon.temp3, "Temperature 3", monitorName, ref, init);
                                break;
                            case TEMPSENSOR_CFG_INDEX:
                                addMonitor(&vmon.tempSensor, "Sensor Temperature", monitorName, ref, init);
                                break;
                            default:
                                bhmMessage("I", PREFIX "_INIT_TI", "Temperature index %d is above max %d",
                                                        position, MAX_TEMP_CFG_INDEX);
                                break;
                            }
                        } else if (type == 'V') {
                            addMonitor(&vmon.voltage[position], "Voltage", monitorName, ref, init);
                        } else if (type == 'C') {
                            addMonitor(&vmon.current[position], "Current", monitorName, ref, init);
                        } else if (type == 'P') {
                            addMonitor(&vmon.power[position], "Power", monitorName, ref, init);
                        } else {
                            bhmMessage("W", PREFIX "_INIT_EM", "Type %c not recognized,"
                                       " expected V (voltage), C (current) , P (power) or T (temperature)",
                                         type);
                        }
                    }
                } else {
                    bhmMessage("W", PREFIX "_INIT_PE", "Failed to parse line '%s' items %d ignored"
                            " expected '<type> <rail index> <power monitor rref> <name string> <init value voltage/temp>"
                            , line, items);
                }
            }
        }
    }
}


#endif

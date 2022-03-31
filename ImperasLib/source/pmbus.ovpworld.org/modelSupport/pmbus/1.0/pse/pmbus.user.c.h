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

#ifndef PMBUS_USER_C_H
#define PMBUS_USER_C_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* PMBUS Commands */
#define CMD_PAGE                0x00
#define CMD_OPERATION           0x01
#define CMD_RSRVD_TEMP_SENSOR   0x08
#define CMD_VOUT_MODE           0x20
#define CMD_VOUT_COMMAND        0x21
#define CMD_VOUT_MAX            0x24
#define CMD_STATUS_TEMP         0x7D
#define CMD_STATUS_MFR_SPECIFIC 0x80
#define CMD_READ_VOUT           0x8B
#define CMD_READ_IOUT           0x8C
#define CMD_READ_TEMP_1         0x8D
#define CMD_READ_TEMP_2         0x8E
#define CMD_READ_TEMP_3         0x8F
#define CMD_READ_POUT           0x96

/* Operating modes for operation command */
#define OP_MODE_NOM             0x80
#define OP_MODE_MAR_LOW         0x94
#define OP_MODE_MAR_HIGH        0xA4

Uns32     accessPage;           // page (voltage/current rail) to access
monItemTP accessLocation;       // pointer to access structure

Int32     voutModeValue;        // holds the value read for VOUT_MODE
Uns32     statusMfrSpecific;    // holds the value read for STATUS_MFR_SPECIFIC

// Enum to track current state
typedef enum {
    IDLE,
    SET_PAGE,
    READ_VOUT_MODE_LOW,
    READ_VOUT_MODE_HIGH,
    WRITE_VOUT_LOW,
    WRITE_VOUT_HIGH,
    WRITE_OPERATION,
    WRITE_VOUT_MAX,
    READ_LOW,
    READ_HIGH,
    READ_STATUS_MFR_SPECIFIC,
    LAST
} stateE;

stateE status;

Uns32 pageAccess = 0xff;

//////////////////////////////// Callback stubs ////////////////////////////////

//
// Called on an I2C interface address read
//
PPM_REG_READ_CB(readI2C) {

    if (PSE_DIAG_MEDIUM) {
        Uns32 offset = addr - handles.iic;
        bhmMessage("I", PREFIX "_RD","Offset 0x%08x", offset);
    }

    Uns32 buffer = 0;

    // Check if this is a rail access we have set a location
    if (((status == READ_LOW) || (status == READ_HIGH)) && !accessLocation) {
    	bhmMessage("W", PREFIX "_MON","Access location failure");
        status = IDLE;                  // move to idle
    } else {
        // next state
        switch (status) {
            case READ_LOW:
                // read low byte
                buffer = accessLocation->data.value & 0xff;
                status = READ_HIGH;             // read high byte next
                break;
            case READ_HIGH:
                // read high byte
                buffer = (accessLocation->data.value >> 8) & 0xff;
                status = IDLE;                  // move to idle
                break;
            case READ_VOUT_MODE_LOW:
                // read low byte
                buffer = voutModeValue & 0xff;
                status = READ_VOUT_MODE_HIGH;   // read high byte next
                break;
            case READ_VOUT_MODE_HIGH:
                // read high byte
                buffer = (voutModeValue >> 8) & 0xff;
                status = IDLE;                  // move to idle
                break;
            case READ_STATUS_MFR_SPECIFIC:
                // read byte
                buffer = statusMfrSpecific;
                status = IDLE;                  // move to idle
                break;
            default:
                if (PSE_DIAG_MEDIUM) {
                    bhmMessage("W", PREFIX "_STS","Bad state when reading (%d)", status);
                }
                break;
        }
    }
    // Set so that last data value visible in debugger
    *(Uns8*)user = buffer;
    return *(Uns8*)user;
}

//
// Called on an I2C interface address write
//
PPM_REG_WRITE_CB(writeI2C) {
    if (PSE_DIAG_MEDIUM) {
        Uns32 offset = addr - handles.iic;
        bhmMessage("I", PREFIX "_WR","Offset 0x%08x 0x%x", offset, data);
    }

    Bool updateVoltageRail = False;    // set when value should be written to rail intercept library

    switch(status) {
        case IDLE:
            // if idle can take another command
            switch (data) {
                case CMD_PAGE:
                    status = SET_PAGE;
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Set PAGE");
                    }
                    break;
                case CMD_STATUS_TEMP:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Read Status Temperature (%d)",
                                vmon.status_temp.data.value);
                    }
                    accessLocation = &vmon.status_temp;
                    status = READ_LOW;
                    break;
                case CMD_READ_TEMP_1:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Read Temperature 1 (%d)",
                                vmon.temp1.data.value);
                    }
                    accessLocation = &vmon.temp1;
                    status = READ_LOW;
                    break;
                case CMD_READ_TEMP_2:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Read Temperature 2 (%d)",
                                vmon.temp2.data.value);
                    }
                    accessLocation = &vmon.temp2;
                    status = READ_LOW;
                    break;
                case CMD_READ_TEMP_3:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Read Temperature 3 (%d)",
                                vmon.temp3.data.value);
                    }
                    accessLocation = &vmon.temp3;
                    status = READ_LOW;
                    break;

                case CMD_RSRVD_TEMP_SENSOR:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Read Temperature Sensor PCB (%d)",
                                vmon.tempSensor.data.value);
                    }
                    accessLocation = &vmon.tempSensor;
                    status = READ_LOW;
                    break;

                case CMD_READ_VOUT:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Read (p%d) VOut", accessPage);
                    }
                    accessLocation = &vmon.voltage[accessPage];
                    status = READ_LOW;
                    break;
                case CMD_READ_IOUT:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Read (p%d) IOut", accessPage);
                    }
                    accessLocation = &vmon.current[accessPage];
                    status = READ_LOW;
                    break;
                case CMD_READ_POUT:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Read (p%d) POut", accessPage);
                    }
                    accessLocation = &vmon.power[accessPage];
                    status = READ_LOW;
                    break;

                case CMD_VOUT_COMMAND:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Set (p%d) Vout", accessPage);
                    }
                    status = WRITE_VOUT_LOW;
                    break;

                case CMD_VOUT_MODE:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Read Vout Mode");
                    }
                    status = READ_VOUT_MODE_LOW;
                    break;

                case CMD_STATUS_MFR_SPECIFIC:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Read Status Manufacturer Specific");
                    }
                    status = READ_STATUS_MFR_SPECIFIC;
                    break;

                case CMD_OPERATION:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Write Operation");
                    }
                    status = WRITE_OPERATION;
                    break;

                case CMD_VOUT_MAX:
                    if (PSE_DIAG_MEDIUM) {
                        bhmMessage("I", PREFIX "_CMD","Write VOut Max");
                    }
                    status = WRITE_VOUT_MAX;
                    break;

                default:
                    bhmMessage("W", PREFIX "_CMD","Command 0x%x not supported", data);
                    status = IDLE;
                    break;
            }
            break;
        case WRITE_VOUT_LOW:
            if (PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX "_CMD","Set Vout (p%d) Low %d (0x%x)", accessPage, data, data);
            }
            vmon.voltage[accessPage].data.value = (data & 0xff);
            updateVoltageRail = False;
            status = WRITE_VOUT_HIGH;
            break;
        case WRITE_VOUT_HIGH:
            if (PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX "_CMD","Set Vout (p%d) high %d (0x%x)", accessPage, data, data);
            }
            vmon.voltage[accessPage].data.value = ((data & 0xff) << 8) | vmon.voltage[accessPage].data.value;
            updateVoltageRail = True;  // update the power monitor library
            status = IDLE;
            break;
        case WRITE_OPERATION:
            if (PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX "_CMD","Write Operation 0x%x : No Operation", data);
            }
            status = IDLE;
            break;
        case WRITE_VOUT_MAX:
            if (PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX "_CMD","Write Vout Max (p%d) %d (0x%x) : No Operation", accessPage, data, data);
            }
            status = IDLE;
            break;
        case SET_PAGE:
            if (PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX "_CMD","Set Page 0x%x", data);
            }
            accessPage = data;          // page 0 is rail 1 is mon[0]
            status = IDLE;
            break;
        default:
            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX "_UST","Unknown state %d (data 0x%x ignored)", status, data);
            }

            status = IDLE;
            break;
    }

    *(Uns8*)user = data;

    // perform the power monitor access
    if (status == READ_LOW) {
        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX "_REQRAIL","Request Rail Update %s ref %d type/format %d/%d (%s)",
                    accessLocation->name, accessLocation->data.ref,
                    accessLocation->type, accessLocation->format,
                    accessLocation->poil ? "access Power Monitor" :
                                           "not configured for Power Monitor" );
        }
        Uns32 result = 0;
        // Only access if it has been configured
        if (accessLocation->poil) {
            result = getRailValue(accessLocation->data.ref,
                                    accessLocation->data.value,
                                    accessLocation->type,
                                    accessLocation->format);
            if(result != accessLocation->data.value) {
                if (PSE_DIAG_MEDIUM) {
                    bhmMessage("I", PREFIX "_GETRAIL","Rail Update %s ref %d type/format %d/%d %d->%d",
                            accessLocation->name, accessLocation->data.ref,
                            accessLocation->type, accessLocation->format,
                            accessLocation->data.value, result);

                    accessLocation->data.value = result;    // update
                }
            }
        }
    }

    if (updateVoltageRail) {
        updateVoltageRail = False;
        Uns32 rtn = 0;
        // Only access if it has been configured
        if (vmon.voltage[accessPage].poil) {
            rtn = setRailValue(vmon.voltage[accessPage].data.ref,
                               vmon.voltage[accessPage].data.value,
                               VOLTAGE, PMBUS_LINEAR16);
        }

        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX "_SETRAIL","Rail Update %s %d %d (%s)",
                    vmon.voltage[accessPage].name,
                    vmon.voltage[accessPage].data.ref,
                    vmon.voltage[accessPage].data.value,
                    vmon.voltage[accessPage].poil ? rtn ? "ok" : "failed" : "not configured for Power Monitor");
        }
    }
}

//
// Read other configuration information for static values
//
void readDefaultConfiguration(void) {

    bhmInt32ParamValue("voutmode", &voutModeValue);
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_VM", "VOUT_MODE Init value %d (0x%x)", voutModeValue, voutModeValue);

    bhmUns32ParamValue("statusmfrspecific", &statusMfrSpecific);
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_SMS", "STATUS_MFR_SPECIFIC Init value %d (0x%x)", statusMfrSpecific, statusMfrSpecific);

}

#endif

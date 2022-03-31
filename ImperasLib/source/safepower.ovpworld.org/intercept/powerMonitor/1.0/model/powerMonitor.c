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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"


#define PREFIX "PML"

// include common power monitor data types
#include "ovpworld.org/modelSupport/powermonitor/1.0/pse/powermonitor.datatypes.h"

// include common power monitor defines
#include "ovpworld.org/modelSupport/powermonitor/1.0/model/powermonitor.native.h"

// we will handle a maximum number of monitors
#define MAX_MONITORS  64

// CAF use-case values
// Power
#define P_PS_400_1    43740    // 357mW
#define P_PS_200_1    43646    // 311mW
#define P_PS_32_1     43585    // 281mW
#define P_PS_400_09   43554    // 266mW
#define P_PS_200_09   43468    // 224mW
#define P_PS_32_09    43439    // 210mW
#define P_DDR_400     43945    // 456mW
#define P_DDR_200     43905    // 437mW
#define P_DDR_32      43836    // 404mW
#define P_PL_C        47408    // 593mW
// Voltage
#define V_PL_C         4100    // 1000mV
#define V_DDR_C        5455    // 1330mV
// Temperature


// Mode detection
#define FS_LIMIT_1      25    // 500-(%25) = 375MHz --> 400 <-> 200
#define FS_LIMIT_2      65    // 500-(%65) = 175MHz --> 200 <-> 32
#define VS_LIMIT      4000    // 976mV

typedef struct monS {
    Uns32       voltage;
    Uns32       current;
    Uns32       power;
    Uns32       temperature;
    dataTypeE   type;
    dataFormatE format;
} monT, *monTP;

typedef struct vmiosObjectS {

    const char *name;       // The name of the instance this is loaded upon

    Uns32       diagLevel;  // diagnostic level

    vmiProcessorP  processor;   // processor on which power monitor is installed

    Uns32          frequency;   // the default frequency
    Flt64          ipsValue;    // instructions per second
    Flt64          deration;    // deration factor applied

    Bool           changetemperature;   // enable change of temperature over time
    Bool           powerwithfrequency;  // enable modification of power based upon frequency

    //
    // Power Monitor shared data handle
    //
    vmiSharedDataHandleP powerMonitorDataTransfer;

    //
    // Monitors (register values)
    //
    monT        monitor[MAX_MONITORS];

    //
    // The resolution of the voltage based upon the Vout Mode (default -12)
    //
    float       voltageResolution;

} vmiosObject;

#define DIAG_LEVEL(_O) (_O->diagLevel)


//////////////////////////////// Conversion functions //////////////////////////

// calculate 2 to power of
float pow2(Int8 exponent)
{
    float result = 1;
    Int32 i;
    if (exponent>=0) {
        for (i=0;i<exponent;i++)  result = result *2;
    } else {
        for (i=0;i<-exponent;i++) result = result /2;
    }
    return result;
}

// voltage resolution for VOUT_MODE, default -12 is 0.244mV

// convert a register value to a linear voltage value
float regLinear16ToFloat(Uns32 reg, float voltageResolution) {
    float linear = 0;

    linear = (float)(voltageResolution * (float)(reg & 0xffff));
    return linear;
}

// convert a linear voltage to a register
Uns32 floatToLinear16Reg(float linear, float voltageResolution) {
    Uns32 reg = 0;

    reg = (Uns32)(linear / voltageResolution);

    return reg;
}

// convert a register value to a linear11 value
float regLinear11ToFloat(Uns32 reg) {

    float linear = 0;
    Int16 mantissa  = (reg & 0x7ff);
    Int8  exponent  = ((reg >> 11) & 0x001f);
    if ( exponent > 0x0F )    exponent |= 0xE0;    // sign extend exponent
    if ( mantissa > 0x03FF )  mantissa |= 0xF800;  // sign extend mantissa

    // vmiMessage("I", PREFIX "_L11toF", "M=%d E=%d ",mantissa, exponent);

    float pow2Val = pow2(exponent);
    linear = (float)(mantissa) * pow2Val;

    // vmiMessage("I", PREFIX "_L11toF", "pow2Val=%f l=%f ",pow2Val, linear);

    return linear;
}

// convert a linear11 value to a register
#define MAX_MANTISSA    1023
#define MIN_MANTISSA      15
Uns32 floatToLinear11Reg(float value) {
    Uns32 reg = 0;
    Int16 mantissa = 0;
    Int16 exponent = 0;
    Bool  negVal = False;

    if (value < 0) {
        negVal = True;
        value  = -value;
    }

    // Reduce to fit into 10 bits
    while ((value >= MAX_MANTISSA) && (exponent < 15)) {
        exponent++;
        value = value / 2;
    }
    // Increase small mantissa to improve precision
    while ((value < MIN_MANTISSA) && (exponent > -15)) {
        exponent--;
        value = value * 2;
    }

    mantissa = (Int16)value;

    // Ensure that result is within range
    if (mantissa > 0x3ff) mantissa = 0x3ff;

    // restore sign
    if (negVal) mantissa = -mantissa;

    // Convert to 11 bit mantissa and 5 bit exponent
    reg = (mantissa & 0x7ff) | ((exponent & 0x001f) << 11);

    return reg;
}

//
// XADC (read only monitor) Voltage, Power and Temperature
//

// Temperature = (ADCVal * 503.975)/4096 - 273.15
// ADCVal bit 16 to 4 in register
Uns32 xadcTempToReg(float temp) {
    Uns32 reg = 0;
    reg = (Uns32)(((float)(temp + 273.15) * 4096) / 503.975);
    return reg << 4;
}

// Voltage/Power 3V (Max) = 4096
Uns32 xadcPowerSupplyToReg(float voltage) {
    Uns32 reg = 0;
    float value = (float)(voltage)*4096/3;
    reg = (Uns32) value;

    return reg << 4;
}

////////////////////////////// End Conversion functions /////////////////////////

typedef enum {
    INVALID_UPDATE_TYPE,
    POWER_FROM_VOLTAGE,
    POWER_FROM_CURRENT,
    CURRENT_FROM_POWER,
} updateTypeE;

//
// When a rail is updated this has an effect on the power (or current)
// update the Power rail for volateg and current changes, or the current rail for power changes
//
Bool updateOtherRailValues(updateTypeE update, vmiosObjectP object, monT *monitor, sharedItemTP changeItem) {
    float currentNow  = regLinear11ToFloat(monitor->current);
    float voltageNow  = regLinear16ToFloat(monitor->voltage, object->voltageResolution);
    float powerNow    = regLinear11ToFloat(monitor->power);
    switch(update) {
    case POWER_FROM_VOLTAGE:             // update power with voltage change
        if (monitor->current) {
            // Current specified
            float voltage  = regLinear16ToFloat(changeItem->value, object->voltageResolution);
            float power    = currentNow * voltage;
            Uns32 powerReg = floatToLinear11Reg(power);
            if (DIAG_HIGH(DIAG_LEVEL(object)))
                vmiMessage("I", PREFIX "_SETV_PWR", "%s:PM Data ref %d Current %f (0x%x) Voltage %f (0x%x)"
                                                    " Power %f (0x%x) -> Power %f (0x%x)",
                                object->name, changeItem->ref,
                                currentNow, monitor->current, voltage, monitor->voltage,
                                powerNow, monitor->power, power,    powerReg);
            monitor->power = powerReg;
            return True;
        }
        break;
    case POWER_FROM_CURRENT:             // update power with current change
        if (monitor->voltage) {
            // voltage specified
            float current  = regLinear11ToFloat(changeItem->value);
            float power    = voltageNow * current;
            Uns32 powerReg = floatToLinear11Reg(power);
            if (DIAG_HIGH(DIAG_LEVEL(object)))
                vmiMessage("I", PREFIX "_SETC_PWR", "%s:PM Data ref %d Current %f (0x%x) Voltage %f (0x%x)"
                                                    " Power %f (0x%x) -> Power %f (0x%x)",
                                object->name, changeItem->ref,
                                current,  monitor->current, voltageNow, monitor->voltage,
                                powerNow, monitor->power, power,    powerReg);
            monitor->power = powerReg;
            return True;
        }
        break;
    case CURRENT_FROM_POWER:             // update current with power change
        if (monitor->voltage) {
            // voltage specified
            float power    = regLinear11ToFloat(changeItem->value);
            float current  = power / voltageNow;
            Uns32 currentReg = floatToLinear11Reg(current);
            if (DIAG_HIGH(DIAG_LEVEL(object)))
                vmiMessage("I", PREFIX "_SETP_CRNT", "%s:PM Data ref %d Current %f (0x%x) -> Current %f (0x%x)"
                                                    " Voltage %f (0x%x) Power %f (0x%x)",
                                object->name, changeItem->ref,
                                currentNow, monitor->current, current,    currentReg,
                                voltageNow, monitor->voltage, powerNow, monitor->power);
            monitor->current = currentReg;
            return True;
        }
        break;
    default:
        break;
    }
    return False;
}

//
// Return the correct symbol to display in diagnostic messages
//
const char *getTypeSymbol(dataTypeE dataType) {
    const char *rtn = "-";
    switch(dataType) {
        case VOLTAGE:       rtn = "V"; break;
        case CURRENT:       rtn = "A"; break;
        case POWER:         rtn = "W"; break;
        case TEMPERATURE:   rtn = "°C"; break;
        default: break;
    }
    return rtn;
}

//
// respond to requests for information using shared data channel
//
VMI_SHARED_DATA_LISTENER_FN(powerMonitorListenerCB) {

    vmiosObjectP object     = userObject;
    sharedItemTP changeItem = userData;

    if(*ret != 0) {
        // something has already responded - assume this is the other core in an MP core so ignore
    } else {
        if (userData != NULL) {

            switch(id) {
            case GET_RAIL_VALUE_ID:
                if (changeItem->dataFormat == XADC_VOLTAGE_SUPPLY) {
                    // expect reference 0 VCCINT or 1 VCCPINT

                    Uns32 regValue = object->monitor[changeItem->ref].voltage;
                    float value    = regLinear16ToFloat(regValue, object->voltageResolution);
                    // convert linear16 power/voltage value to xADC representation
                    changeItem->value = xadcPowerSupplyToReg(value);

                    if (DIAG_HIGH(DIAG_LEVEL(object)))
                        vmiMessage("I", PREFIX "_GET_XADCV", "%s:PM Data ref %d type %d format %d value %d (0x%x) -> %fV -> %d (0x%x)",
                                        object->name, changeItem->ref,
                                        changeItem->dataType, changeItem->dataFormat,
                                        regValue, regValue,
                                        value,
                                        changeItem->value, changeItem->value);

                } else if (changeItem->dataFormat == XADC_TEMPERATURE) {
                    // expect reference 35 Sensor Temperature

                    // convert register linear11 value to temperature and back to xADC representation
                    Uns32 regValue    = object->monitor[changeItem->ref].temperature;
                    float temperature = regLinear11ToFloat(regValue);

                    if (object->changetemperature) {
                        float time = vmirtGetLocalTime(object->processor);
                        if      (time > 900)                   temperature = 54.300;
                        else if((time > 600) && (time <= 900)) temperature = (0.0056 *time) + 49.25;
                        else if((time > 400) && (time <= 600)) temperature = (0.01   *time) + 46.6;
                        else if((time > 200) && (time <= 400)) temperature = (0.0195 *time) + 42.85;
                        else if((time >  80) && (time <= 200)) temperature = (0.0329 *time) + 40.132;
                        else if((time >  30) && (time <=  80)) temperature = (0.155  *time) + 30.45;
                        else if                 (time <=  30)  temperature = (0.344  *time) + 24.655;
                        // write modified value back?
                        object->monitor[changeItem->ref].temperature = floatToLinear11Reg(temperature);
                    }

                    // convert temperature value to xADC representation
                    changeItem->value = xadcTempToReg(temperature);

                    if (DIAG_HIGH(DIAG_LEVEL(object)))
                        vmiMessage("I", PREFIX "_GET_XADCT", "%s:PM Data ref %d type %d format %d value %d(0x%x) -> %f°C -> %d (0x%x)",
                                        object->name, changeItem->ref,
                                        changeItem->dataType, changeItem->dataFormat,
                                        regValue, regValue,
                                        temperature,
                                        changeItem->value, changeItem->value);

                } else {
                    //
                    // PMBus device access
                    //
                    switch(changeItem->dataType) {
                        case VOLTAGE:
                            changeItem->value = object->monitor[changeItem->ref].voltage;
                            break;
                        case CURRENT:
                            changeItem->value = object->monitor[changeItem->ref].current;
                            break;
                        case POWER:
                            changeItem->value = object->monitor[changeItem->ref].power;

                            // Modify the power based upon the operating frequency
                            if (object->powerwithfrequency) {

                                // P(PS) depends on Frequency and VCCPINT
                                if(changeItem->ref==1)
                                {
                                    object->deration = vmirtGetDerateFactor(object->processor);

                                    Uns32 VCCPINT = (object->monitor[changeItem->ref].voltage);
                                    if (object->deration<FS_LIMIT_1) {
                                        if (VCCPINT>VS_LIMIT)   changeItem->value = P_PS_400_1;
                                        else                    changeItem->value = P_PS_400_09;
                                    }
                                    else if (object->deration<FS_LIMIT_2) {
                                        if (VCCPINT>VS_LIMIT)   changeItem->value = P_PS_200_1;
                                        else                    changeItem->value = P_PS_200_09;
                                    }
                                    else if (VCCPINT>VS_LIMIT)  changeItem->value = P_PS_32_1;
                                    else                        changeItem->value = P_PS_32_09;
                                }

                                //P(DDR) depends on Frequency
                                if(changeItem->ref==5) {
                                    object->deration = vmirtGetDerateFactor(object->processor);

                                    if      (object->deration<FS_LIMIT_1)  changeItem->value = P_DDR_400;
                                    else if (object->deration<FS_LIMIT_2)  changeItem->value = P_DDR_200;
                                    else                                   changeItem->value = P_DDR_32;
                                }
                            }
                            break;
                        default:
                            vmiMessage("W", PREFIX "_GETF", "%s:PM Data ref %d type %d format %d: Rail Type not recognized",
                                            object->name, changeItem->ref,
                                            changeItem->dataType, changeItem->dataFormat);
                            break;
                    }

                    if (DIAG_LOW(DIAG_LEVEL(object))) {
                        // calculate actual value for debug
                        float value = 0;
                        if (changeItem->dataFormat == PMBUS_LINEAR16) value = regLinear16ToFloat(changeItem->value, object->voltageResolution);
                        if (changeItem->dataFormat == PMBUS_LINEAR11) value = regLinear11ToFloat(changeItem->value);

                        vmiMessage("I", PREFIX "_GET", "%s:PM Data ref %d type %d format %d value %d (0x%x) %f%s",
                                        object->name, changeItem->ref,
                                        changeItem->dataType, changeItem->dataFormat,
                                        changeItem->value, changeItem->value,
                                        value, getTypeSymbol(changeItem->dataType));
                    }
                }
                break;

            case SET_RAIL_VALUE_ID:
                // Only from PMBus so store value
                if(changeItem->ref < MAX_MONITORS) {
                    if (DIAG_LOW(DIAG_LEVEL(object)))
                        vmiMessage("I", PREFIX "_SET", "%s:PM Data ref %d type %d format %d value %d (0x%x)",
                                        object->name, changeItem->ref,
                                        changeItem->dataType, changeItem->dataFormat,
                                        changeItem->value, changeItem->value);

                    switch(changeItem->dataType) {
                        case VOLTAGE:
                        {
                            Bool powerUpdate = updateOtherRailValues(POWER_FROM_VOLTAGE,
                                                     object, &object->monitor[changeItem->ref], changeItem);

                            // update voltage
                            object->monitor[changeItem->ref].voltage = changeItem->value;

                            if (DIAG_MEDIUM(DIAG_LEVEL(object))) {
                                float value = regLinear16ToFloat(changeItem->value, object->voltageResolution);
                                vmiMessage("I", PREFIX "_SETV", "%s:PM Data ref %d type %d format %d value %d (0x%x) %fV %s",
                                                object->name, changeItem->ref,
                                                changeItem->dataType, changeItem->dataFormat,
                                                changeItem->value, changeItem->value,
                                                value,
                                                powerUpdate ? " (Power Updated)" : "");
                            }
                            break;
                        }
                        case CURRENT:
                        case POWER:
                        case TEMPERATURE:
                            vmiMessage("W", PREFIX "_SETCPT", "%s:PM Data ref %d type %d format %d:"
                                                              " Cannot write Current, Power or Temperature (only when initializing)",
                                            object->name, changeItem->ref,
                                            changeItem->dataType, changeItem->dataFormat);
                            break;
                        default:
                            vmiMessage("W", PREFIX "_SETF", "%s:PM Data ref %d type %d format %d: Rail Type not recognized",
                                            object->name, changeItem->ref,
                                            changeItem->dataType, changeItem->dataFormat);
                            break;
                    }

                } else {
                    if (DIAG_MEDIUM(DIAG_LEVEL(object)))
                        vmiMessage("I", PREFIX "_VMX", "ref %d exceeded max %d - ignored", changeItem->ref, MAX_MONITORS);
                }
                break;

            case INITIAL_RAIL_VALUE_ID:
                // Only from PMBus so store value
                vmiMessage("I", PREFIX "_GET", "INITIAL_RAIL_VALUE_ID->ref:%d",changeItem->ref);//ainara
                if(changeItem->ref < MAX_MONITORS) {
                    Bool powerUpdate   = False;
                    Bool currentUpdate = False;
                    switch(changeItem->dataType) {
                        case VOLTAGE:
                            powerUpdate = updateOtherRailValues(POWER_FROM_VOLTAGE,
                                                object, &object->monitor[changeItem->ref], changeItem);
                            object->monitor[changeItem->ref].voltage = changeItem->value;
                            break;
                        case CURRENT:
                            powerUpdate = updateOtherRailValues(POWER_FROM_CURRENT,
                                                object, &object->monitor[changeItem->ref], changeItem);
                            object->monitor[changeItem->ref].current = changeItem->value;
                            break;
                        case POWER:
                            currentUpdate = updateOtherRailValues(CURRENT_FROM_POWER,
                                                object, &object->monitor[changeItem->ref], changeItem);
                            object->monitor[changeItem->ref].power = changeItem->value;
                            break;
                        case TEMPERATURE:
                            object->monitor[changeItem->ref].temperature = changeItem->value;
                            break;
                        default:
                            vmiMessage("W", PREFIX "_INITF", "%s:PM Data ref %d type %d format %d: Rail Type not recognized",
                                            object->name, changeItem->ref,
                                            changeItem->dataType, changeItem->dataFormat);
                            break;
                    }
                    if (DIAG_LOW(DIAG_LEVEL(object))) {
                        float value = 0;
                        if (changeItem->dataFormat == PMBUS_LINEAR16) value = regLinear16ToFloat(changeItem->value, object->voltageResolution);
                        if (changeItem->dataFormat == PMBUS_LINEAR11) value = regLinear11ToFloat(changeItem->value);

                        vmiMessage("I", PREFIX "_INIT", "%s:PM Data ref %d type %d format %d value %d (0x%x) %f%s%s",
                                        object->name, changeItem->ref,
                                        changeItem->dataType, changeItem->dataFormat,
                                        changeItem->value, changeItem->value,
                                        value,
                                        getTypeSymbol(changeItem->dataType),
                                        powerUpdate ? " (power updated)" : currentUpdate ? " (current updated)" : "");
                    }
                } else {
                    if (DIAG_LOW(DIAG_LEVEL(object)))
                        vmiMessage("I", PREFIX "_VMX", "ref %d exceeded max %d - ignored", changeItem->ref, MAX_MONITORS);
                }
                break;

            default:
                vmiMessage("W", PREFIX "_WUT", "Message type %d not recognized - ignored", id);
                break;
            }

            // change the return status as we have responded
            (*ret)++;

        } else {
            vmiMessage("I", PREFIX "_NE", "%s:PM received NULL data", object->name);
        }
    }
}


//////////////////////////////// Diagnostic Command /////////////////////////////////

VMIOS_COMMAND_PARSE_FN(diagnosticCB) {

    if (DIAG_LOW(DIAG_LEVEL(object))) {
        vmiMessage(
            "I", PREFIX, "%s: diagnostic level set to %d",
            object->name,
            DIAG_LEVEL(object)
        );
    }
    return "";
}

//////////////////////////////// Configuration Parameters ///////////////////////////

// Define parameters
typedef struct paramValueS {
    VMI_INT32_PARAM(voutmode);          // defines the VOUT_MODE value
    VMI_BOOL_PARAM(initdiag);           // Allows diagnostics to be enabled for the initialization
    VMI_UNS64_PARAM(frequency);         // Sets the default operating frequency for the ARM processor
    VMI_BOOL_PARAM(changetemperature);  // Enables the change of temperature over time
    VMI_BOOL_PARAM(powerwithfrequency); // Enables the modification of power based upon operating frequency
} paramValues, *paramValuesP;

// defaultFreq
Uns32 defaultFreq = 500000000;

// Define formals
static vmiParameter formals[] = {
    VMI_INT32_PARAM_SPEC(paramValues, voutmode, -12, -14, -10, "VOUT_MODE Configuration"),
    VMI_BOOL_PARAM_SPEC(paramValues, initdiag, False, "Enable initialization diagnostics messages"),
    VMI_UNS64_PARAM_SPEC(paramValues, frequency, 500000000, 50000000, 1000000000, "The default operating frequency of the ARM processor"),
    VMI_BOOL_PARAM_SPEC(paramValues, changetemperature, False, "Enable the change of reported temperature over time"),
    VMI_BOOL_PARAM_SPEC(paramValues, powerwithfrequency, False, "Enables the modification of power based upon operating frequency"),
    VMI_END_PARAM
};

// Iterate formals
static VMIOS_PARAM_SPEC_FN(getParamSpecs) {
    if(!prev) {
        prev = formals;
    } else {
        prev++;
    }
    return prev->name ? prev : 0;
}

// Return size of parameter structure
static VMIOS_PARAM_TABLE_SIZE_FN(getParamTableSize) {
    return sizeof(paramValues);
}

static VMIOS_CONSTRUCTOR_FN(constructor)
{
    object->name      = vmirtProcessorName(processor);
    object->processor = processor;
    // initialize variables
    object->ipsValue  = vmirtGetProcessorIPS(processor);
    object->deration  = vmirtGetDerateFactor(processor);

    vmiMessage("I", PREFIX "_INIT", "Shared PowerMonitor installed on '%s'", object->name);

    char *runtime = getenv("IMPERAS_RUNTIME");
    if (runtime && (strcmp(runtime, "CpuManager") == 0)) {

        object->powerMonitorDataTransfer = vmirtFindAddSharedData(POWERMONITOR_CHANNEL_VERSION, POWERMONITOR_CHANNEL_NAME, 0 );
        if(!object->powerMonitorDataTransfer) {

            vmiMessage("W", PREFIX "_PMD", "%s: Shared PowerMonitor not available", object->name);
        } else {

            vmiMessage("I", PREFIX "_PMI", "%s: Installed PowerMonitor listener", object->name);

            vmirtRegisterListener(object->powerMonitorDataTransfer, powerMonitorListenerCB, object);
        }
    } else {
        vmiMessage("W", PREFIX "_RUN", "%s: Imperas Professional runtime required for Power monitor updates", object->name);
    }

    vmiCommandP cmd;
    cmd = vmiosAddCommandParse(
        object,
        "diagnostic",
        "Set how much additional information is reported for the library",
        diagnosticCB,
        VMI_CT_QUERY|VMI_CO_DIAG|VMI_CA_REPORT
    );
    vmirtAddArg(
        cmd,
        "level",
        "Higher numbers print more diagnostic information (0 = off to 3 = max)",
        VMI_CA_UNS32,
        VMI_CAA_DEFAULT,
        True,
        &(DIAG_LEVEL(object))
    );

    paramValuesP params = parameterValues;

    // set intial diag level for init information
    object->diagLevel = (params->initdiag ? 1 : 0);

    // calculate the voltage resolution for the linear16 register
    object->voltageResolution = pow2(params->voutmode);

    // frequency
    object->frequency = params->frequency;

    // temperature update
    object->changetemperature = params->changetemperature;

    // modify power based upon frequency change
    object->powerwithfrequency = params->powerwithfrequency;

    if (DIAG_LOW(DIAG_LEVEL(object))) {
        vmiMessage(
            "I", PREFIX, "%s: Voltage Mode %d, Resolution %f",
                            object->name, params->voutmode,
                            object->voltageResolution
        );
        vmiMessage(
            "I", PREFIX, "%s: ARM default frequency " FMT_64u " IPS %f Derate %f",
                            object->name, params->frequency,
                            object->ipsValue, object->deration
        );
    }

}

static VMIOS_DESTRUCTOR_FN(destructor)
{
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,                // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,      // type
    .packageName    = "powerMonitor",             // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "safepower.ovpworld.org",
        .library = "intercept",
        .name    = "powerMonitor",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,                // object constructor
    .destructorCB   = destructor,                 // object destructor

    ////////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,
    .paramValueSizeCB = getParamTableSize,

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // -------------------          ----------- ------ -----------------
        // Name                         Address     Opaque Callback
        // -------------------          ----------- ------ -----------------
        {0}
    }
};

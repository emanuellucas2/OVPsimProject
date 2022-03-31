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

#ifndef POWERMONITOR_NATIVE_C_H
#define POWERMONITOR_NATIVE_C_H


#define POWERMONITOR_FUNCTION_INTERCEPTS     \
    {"initNative",           0,          True,  VMIOS_ABI_INT('4', "o4",    initNative)}, \
    {"getRailValue",         0,          True,  VMIOS_ABI_INT('4', "o4444", getRailValue)}, \
    {"setRailValue",         0,          True,  VMIOS_ABI_INT('4', "o4444", setRailValue)}, \
    {"initRailValue",        0,          True,  VMIOS_ABI_INT('4', "o4444", initRailValue)}

//
// Called to open the Power Montor shared data channel
//
vmiSharedDataHandleP openSharedPowerMonitor (const char *name) {

    vmiSharedDataHandleP channel = NULL;

    char *runtime = getenv("IMPERAS_RUNTIME");
    if (runtime && strcmp(runtime, "CpuManager") == 0) {

        channel = vmirtFindAddSharedData(POWERMONITOR_CHANNEL_VERSION, POWERMONITOR_CHANNEL_NAME, 0 );
        if(!channel) {
            vmiMessage("W", PREFIX "_PMD", "%s: Shared PowerMonitor not available", name);
        }

    } else {
        vmiMessage("W", PREFIX "_RUN", "%s: Imperas Professional runtime required for Power monitor updates",
                                            name);
    }

    return channel;
}

//
// Called to get rail update
//
static Uns32 getRailValue(
    vmiosObjectP object,
    Uns32        index,
    Uns32        value,
    dataTypeE    type,
    dataFormatE  format
) {
    sharedItemT powerValue;
    powerValue.ref         = index;
    powerValue.value       = value;
    powerValue.dataType    = type;
    powerValue.dataFormat  = format;

    if(object->powerMonitorDataTransfer) {
        // write to the listeners
        if(DIAG_LOW(object->diag))
            vmiMessage("I", PREFIX "_GMW", "%s: PM Data id %d value 0x%x (type %d format %d)",
                                                object->name,
                                                powerValue.ref, powerValue.value,
                                                powerValue.dataType, powerValue.dataFormat);

        Uns32 rtn = vmirtWriteListeners(object->powerMonitorDataTransfer, GET_RAIL_VALUE_ID, &powerValue);

        static Bool warningReported = False;
        if (rtn != 1) {
            if (rtn == 0) {
                if (!warningReported) {
                    vmiMessage("W", PREFIX "_GMWR", "%s: No response from Power Intercept Library. Check loaded", object->name);
                    warningReported = True;
                }
            } else {
                vmiMessage("W", PREFIX "_GMWR", "%s: Power Intercept Library return code %d, expected one PoIL response", object->name, rtn);
            }
            // return same value
            powerValue.value = value;
        }

        if(DIAG_LOW(object->diag))
            vmiMessage("I", PREFIX "_GMR", "%s:Index %d new value 0x%x", object->name, index, powerValue.value);

    } else {
        if(DIAG_LOW(object->diag))
                vmiMessage("W", PREFIX "_GMWNC", "%s: Write Listener not available", object->name);
    }
    Uns32 result = powerValue.value;    // return new value
    return result;
}

//
// Called to set value for rail
//
static Uns32 setRailValue(
    vmiosObjectP object,
    Uns32        index,
    Uns32        value,
    dataTypeE    type,
    dataFormatE  format
) {
    static Bool warn = True;    // only warn once when intercept does no respond

    sharedItemT powerValue;
    powerValue.ref         = index;
    powerValue.value       = value;
    powerValue.dataType    = type;
    powerValue.dataFormat  = format;

    Uns32 rtn = 0;
    if (object->powerMonitorDataTransfer) {
        // write to the listeners
        if(DIAG_LOW(object->diag))
            vmiMessage("I", PREFIX "_SMW", "%s: PM Data id %d value 0x%x (type %d format %d)",
                                                object->name,
                                                powerValue.ref, powerValue.value,
                                                powerValue.dataType, powerValue.dataFormat);

        rtn = vmirtWriteListeners(object->powerMonitorDataTransfer, SET_RAIL_VALUE_ID, &powerValue);

        if ((rtn != 1) && warn) {
            vmiMessage("W", PREFIX "_SMWR", "%s: Write Listeners return code %d, expected 1 (one listener)", object->name, rtn);
            warn = False;   // no more warnings
        }

    } else {
        if(DIAG_LOW(object->diag))
                vmiMessage("W", PREFIX "_SMWNC", "%s: Write Listener not available", object->name);
    }
    Uns32 result = rtn; // 1 = ok
    return result;
}

//
// Called to initialize value for rail
//
static Uns32 initRailValue(
    vmiosObjectP object,
    Uns32        index,
    Uns32        value,
    dataTypeE    type,
    dataFormatE  format
) {
    sharedItemT powerValue;
    powerValue.ref         = index;
    powerValue.value       = value;
    powerValue.dataType    = type;
    powerValue.dataFormat  = format;

    static Bool warn = True;    // only warn once when intercept does no respond
    Uns32        rtn = 0;       // shared data listener return code
    if (object->powerMonitorDataTransfer) {
        // write to the listeners
        if(DIAG_LOW(object->diag))
            vmiMessage("I", PREFIX "_IMW", "%s: PM Data Init id %d value 0x%x (type %d format %d)",
                                                object->name,
                                                powerValue.ref, powerValue.value,
                                                powerValue.dataType, powerValue.dataFormat);

        rtn = vmirtWriteListeners(object->powerMonitorDataTransfer, INITIAL_RAIL_VALUE_ID, &powerValue);

        if ((rtn != 1) && warn) {
            if(DIAG_LOW(object->diag))
                vmiMessage("W", PREFIX "_IMWR", "%s: Write Listeners return code %d, expected 1 (one listener)", object->name, rtn);
            warn = False;   // no more warnings
        }

    } else {
        if(DIAG_LOW(object->diag))
                vmiMessage("W", PREFIX "_IMWNC", "%s: Write Listener not available", object->name);
    }
    Uns32 result = rtn; // 1 = ok
    return result;
}


//
// Called to initialise
//
static Uns32 initNative(
    vmiosObjectP  object,
    Uns32         diag
) {
    object->diag = diag;

    if(DIAG_LOW(object->diag))
        vmiMessage("I", PREFIX "_INIT", "Diag Level %d", object->diag);

    return 1; // = ok
}

#endif

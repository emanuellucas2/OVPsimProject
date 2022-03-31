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
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////


#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/bhmHttp.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

#include "pse.igen.h"

static ppmNetPort netPorts[] = {
    {
        .name            = "wdi",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Watchdog input signal",
        .handlePtr       = &handles.wdi,
        .netCB           = wdReset,
    },
    {
        .name            = "wdo",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Watchdog output signal",
        .handlePtr       = &handles.wdo,
    },
    { 0 }
};

static PPM_NET_PORT_FN(nextNetPort) {
    if(!netPort) {
         netPort = netPorts;
    } else {
        netPort++;
    }
    return (netPort && netPort->name) ? netPort : 0;
}

static ppmParameter parameters[] = {
    {
        .name        = "TimeoutPeriod",
        .type        = ppm_PT_DOUBLE,
        .description = "Watchdog Timeout Period (milliSeconds)",
        .u.doubleParam.min          = 1.1,
        .u.doubleParam.max          = 2240,
        .u.doubleParam.defaultValue = 140,
    },
    {
        .name        = "InitialPeriod",
        .type        = ppm_PT_DOUBLE,
        .description = "Initial Watchdog Timeout Period (Seconds)",
        .u.doubleParam.min          = 35,
        .u.doubleParam.max          = 55,
        .u.doubleParam.defaultValue = 35,
    },
    { 0 }
};

static PPM_PARAMETER_FN(nextParameter) {
    if(!parameter) {
        parameter = parameters;
    } else {
        parameter++;
    }
    return parameter->name ? parameter : 0;
}

ppmModelAttr modelAttrs = {

    .versionString    = PPM_VERSION_STRING,
    .type             = PPM_MT_PERIPHERAL,

    .netPortsCB       = nextNetPort,  
    .paramSpecCB      = nextParameter,

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .docCB         = installDocs,

    .vlnv          = {
        .vendor  = "maxim.ovpworld.org",
        .library = "peripheral",
        .name    = "max673x",
        .version = "1.0"
    },

    .family               = "maxim.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

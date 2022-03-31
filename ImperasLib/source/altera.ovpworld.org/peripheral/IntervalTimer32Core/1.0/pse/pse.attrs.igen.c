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

static ppmBusPort busPorts[] = {
    {
        .name            = "sp1",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x17,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    { 0 }
};

static PPM_BUS_PORT_FN(nextBusPort) {
    if(!busPort) {
        busPort = busPorts;
    } else {
        busPort++;
    }
    return busPort->name ? busPort : 0;
}

static ppmNetPort netPorts[] = {
    {
        .name            = "irq",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq,
    },
    {
        .name            = "resetrequest",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.resetrequest,
    },
    {
        .name            = "timeout_pulse",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.timeout_pulse,
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

static ppmEnumParameter timeoutConfigValues[] = {
    { .name = "Simple", .value = 0},
    { .name = "Full", .value = 1},
    { .name = "Watchdog", .value = 2},
    { 0 }
};

static ppmParameter parameters[] = {
    {
        .name        = "timeoutPeriod",
        .type        = ppm_PT_UNS32,
        .description = "The timout period in microSeconds (default 10000 uS)",
        .u.uns32Param.defaultValue = 10000,
    },
    {
        .name        = "timerFrequency",
        .type        = ppm_PT_DOUBLE,
        .description = "The frequency of operation in MHz (default 166MHz)",
        .u.doubleParam.defaultValue = 166,
    },
    {
        .name        = "timeoutConfig",
        .type        = ppm_PT_ENUM,
        .description = 0,
        .u.enumParam.legalValues = timeoutConfigValues,
    },
    {
        .name        = "writeablePeriod",
        .type        = ppm_PT_BOOL,
        .description = 0,
        .u.boolParam.defaultValue = 0,
    },
    {
        .name        = "readableSnapshot",
        .type        = ppm_PT_BOOL,
        .description = 0,
        .u.boolParam.defaultValue = 0,
    },
    {
        .name        = "startStopControlBits",
        .type        = ppm_PT_BOOL,
        .description = 0,
        .u.boolParam.defaultValue = 0,
    },
    {
        .name        = "timeoutPulse",
        .type        = ppm_PT_BOOL,
        .description = 0,
        .u.boolParam.defaultValue = 0,
    },
    {
        .name        = "systemResetOnTimeout",
        .type        = ppm_PT_BOOL,
        .description = 0,
        .u.boolParam.defaultValue = 0,
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

    .busPortsCB       = nextBusPort,  
    .netPortsCB       = nextNetPort,  
    .paramSpecCB      = nextParameter,

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .docCB         = installDocs,

    .vlnv          = {
        .vendor  = "altera.ovpworld.org",
        .library = "peripheral",
        .name    = "IntervalTimer32Core",
        .version = "1.0"
    },

    .family               = "altera.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

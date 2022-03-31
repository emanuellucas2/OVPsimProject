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
        .addrHi          = 0x1f,
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
        .name            = "endofpacket",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.endofpacket,
    },
    {
        .name            = "dataavailable",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dataavailable,
    },
    {
        .name            = "readyfordata",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.readyfordata,
    },
    {
        .name            = "RXD",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.RXD,
    },
    {
        .name            = "CTS",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.CTS,
    },
    {
        .name            = "TXD",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TXD,
    },
    {
        .name            = "RTS",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.RTS,
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

static ppmEnumParameter parityValues[] = {
    { .name = "None", .value = 0},
    { .name = "Even", .value = 1},
    { .name = "Odd", .value = 2},
    { 0 }
};

static ppmParameter parameters[] = {
    {
        .name        = "baud",
        .type        = ppm_PT_UNS64,
        .description = 0,
    },
    {
        .name        = "dataBits",
        .type        = ppm_PT_UNS64,
        .description = 0,
    },
    {
        .name        = "fixedBaud",
        .type        = ppm_PT_UNS64,
        .description = 0,
    },
    {
        .name        = "parity",
        .type        = ppm_PT_ENUM,
        .description = 0,
        .u.enumParam.legalValues = parityValues,
    },
    {
        .name        = "stopBits",
        .type        = ppm_PT_UNS64,
        .description = 0,
    },
    {
        .name        = "syncRegDepth",
        .type        = ppm_PT_UNS64,
        .description = 0,
    },
    {
        .name        = "useCtsRts",
        .type        = ppm_PT_UNS64,
        .description = 0,
    },
    {
        .name        = "useEopRegister",
        .type        = ppm_PT_UNS64,
        .description = 0,
    },
    BHM_SER_OPEN_AUTO_FORMALS,
    BHM_RECORD_REPLAY_FORMALS,
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
        .name    = "Uart",
        .version = "1.0"
    },

    .family               = "altera.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

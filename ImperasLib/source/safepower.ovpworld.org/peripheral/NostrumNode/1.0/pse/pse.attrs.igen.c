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
        .name            = "hostif",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x1ffff,
        .mustBeConnected = 1,
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
        .name            = "syncOut",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.syncOut,
    },
    {
        .name            = "syncIn",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.syncIn,
        .netCB           = syncInput,
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


//                     Shared data for packetnet interface

Uns8 network_pnsd[598];

static ppmPacketnetPort packetnetPorts[] = {
    {
        .name            = "network",
        .mustBeConnected = 0,
        .description     = 0,
        .sharedData      = network_pnsd,
        .sharedDataBytes = 598,
        .handlePtr       = &handles.network,
        .packetnetCB     = networkReceiveMsg,
        .userData        = (void*)0
    },
    { 0 }
};

static PPM_PACKETNET_PORT_FN(nextPacketnetPort) {
    if(!port) {
         port = packetnetPorts;
    } else {
        port++;
    }
    return port->name ? port : 0;
}

static ppmParameter parameters[] = {
    {
        .name        = "id",
        .type        = ppm_PT_UNS32,
        .description = "Defines the id for the node (must all be unique in design)",
        .u.uns32Param.min          = 0,
        .u.uns32Param.max          = 16,
        .u.uns32Param.defaultValue = 1,
    },
    {
        .name        = "endian",
        .type        = ppm_PT_STRING,
        .description = 0,
        .u.stringParam.defaultValue = "little",
    },
    {
        .name        = "configfile",
        .type        = ppm_PT_STRING,
        .description = 0,
        .u.stringParam.defaultValue = "channel_config.inf",
    },
    {
        .name        = "sendChannelSize",
        .type        = ppm_PT_UNS32,
        .description = 0,
        .u.uns32Param.min          = 1,
        .u.uns32Param.max          = 128,
        .u.uns32Param.defaultValue = 2,
    },
    {
        .name        = "mboxSize",
        .type        = ppm_PT_UNS32,
        .description = 0,
        .u.uns32Param.min          = 16,
        .u.uns32Param.max          = 4096,
        .u.uns32Param.defaultValue = 256,
    },
    {
        .name        = "generateSync",
        .type        = ppm_PT_BOOL,
        .description = 0,
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
    .packetnetPortsCB = nextPacketnetPort,

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .docCB         = installDocs,

    .vlnv          = {
        .vendor  = "safepower.ovpworld.org",
        .library = "peripheral",
        .name    = "NostrumNode",
        .version = "1.0"
    },

    .family               = "safepower.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

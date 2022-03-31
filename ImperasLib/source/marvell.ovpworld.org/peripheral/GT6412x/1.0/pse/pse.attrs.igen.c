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
        .name            = "busPort",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0xfff,
        .mustBeConnected = 1,
        .remappable      = 1,
        .description     = 0,
    },
    {
        .name            = "PCIconfig",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x0,
        .mustBeConnected = 0,
        .remappable      = 1,
        .description     = 0,
    },
    {
        .name            = "PCIconfigM",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 16,
        .addrBitsMin     = 16,
        .addrBitsMax     = 0,
        .mustBeConnected = 1,
        .description     = 0,
    },
    {
        .name            = "PCIackM",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 0,
        .addrBitsMin     = 0,
        .addrBitsMax     = 0,
        .mustBeConnected = 0,
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
        .name            = "timerInt",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.timerInt,
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
        .name        = "PCIslot",
        .type        = ppm_PT_UNS32,
        .description = "Specify which PCI slot the device occupies.",
    },
    {
        .name        = "PCIfunction",
        .type        = ppm_PT_UNS32,
        .description = "Specify which PCI function the device implements.",
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
        .vendor  = "marvell.ovpworld.org",
        .library = "peripheral",
        .name    = "GT6412x",
        .version = "1.0"
    },

    .family               = "marvell.ovpworld.org",
    .noRecursiveCallbacks = 0,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

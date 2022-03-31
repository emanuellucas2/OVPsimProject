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
        .addrHi          = 0x7,
        .mustBeConnected = 1,
        .remappable      = 1,
        .description     = "PCI main bus connection for register access.",
    },
    {
        .name            = "PCIconfig",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x7ff,
        .mustBeConnected = 0,
        .remappable      = 1,
        .description     = "PCI configuration bus connection.",
    },
    {
        .name            = "dmaPort",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .addrBitsMin     = 32,
        .addrBitsMax     = 40,
        .mustBeConnected = 0,
        .description     = "PCI DMA bus connection.",
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
        .name            = "intOut0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut0,
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

Uns8 phy_pnsd[1524];

static ppmPacketnetPort packetnetPorts[] = {
    {
        .name            = "phy",
        .mustBeConnected = 0,
        .description     = "The port to connect the packetnet virtual network",
        .sharedData      = phy_pnsd,
        .sharedDataBytes = 1524,
        .handlePtr       = &handles.phy
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
        .name        = "PCIslot",
        .type        = ppm_PT_UNS32,
        .description = "Set the PCI slot at which the Ethernet card is installed",
    },
    {
        .name        = "PCIfunction",
        .type        = ppm_PT_UNS32,
        .description = "Set the PCI function of the device. The default of 0 is correct for this device.",
    },
    BHM_ETHERNET_OPEN_AUTO_FORMALS,
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
    .packetnetPortsCB = nextPacketnetPort,

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .docCB         = installDocs,

    .vlnv          = {
        .vendor  = "amd.ovpworld.org",
        .library = "peripheral",
        .name    = "79C970",
        .version = "1.0"
    },

    .family               = "amd.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

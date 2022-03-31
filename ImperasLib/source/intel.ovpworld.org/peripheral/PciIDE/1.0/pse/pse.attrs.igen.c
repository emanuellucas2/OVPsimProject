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
    {
        .name            = "intOut1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut1,
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
        .description = "Specify which PCI function:code the device implements.",
    },
    {
        .name        = "Drive0Name",
        .type        = ppm_PT_STRING,
        .description = "Virtual disk file for IDE channel 0",
    },
    {
        .name        = "Drive0Delta",
        .type        = ppm_PT_STRING,
        .description = "Delta file for IDE channel 0. This feature is incomplete.",
    },
    {
        .name        = "Drive1Name",
        .type        = ppm_PT_STRING,
        .description = "Virtual disk file for IDE channel 1",
    },
    {
        .name        = "Drive1Delta",
        .type        = ppm_PT_STRING,
        .description = "Delta file for IDE channel 1. This feature is incomplete.",
    },
    {
        .name        = "Drive2Name",
        .type        = ppm_PT_STRING,
        .description = "Virtual disk file for IDE channel 2",
    },
    {
        .name        = "Drive2Delta",
        .type        = ppm_PT_STRING,
        .description = "Delta file for IDE channel 2. This feature is incomplete.",
    },
    {
        .name        = "Drive3Name",
        .type        = ppm_PT_STRING,
        .description = "Virtual disk file for IDE channel 3",
    },
    {
        .name        = "Drive3Delta",
        .type        = ppm_PT_STRING,
        .description = "Delta file for IDE channel 3. This feature is incomplete.",
    },
    {
        .name        = "endian",
        .type        = ppm_PT_STRING,
        .description = "Set the system endian, \"big\" or \"little\"; used for writing boot code. Default is \"little\" endian.",
        .u.stringParam.defaultValue = "little",
    },
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
        .vendor  = "intel.ovpworld.org",
        .library = "peripheral",
        .name    = "PciIDE",
        .version = "1.0"
    },

    .family               = "intel.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

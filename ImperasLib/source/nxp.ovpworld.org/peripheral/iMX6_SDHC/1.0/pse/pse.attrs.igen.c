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
        .name            = "bport1",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x3fff,
        .mustBeConnected = 1,
        .remappable      = 0,
        .description     = "Slave port for register and data accesses",
    },
    {
        .name            = "mport",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .addrBitsMin     = 32,
        .addrBitsMax     = 0,
        .mustBeConnected = 1,
        .description     = "Master port for DMA accesses",
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
        .name            = "interrupt",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interrupt Output",
        .handlePtr       = &handles.interrupt,
    },
    {
        .name            = "CD",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = "SD Card Detect",
        .handlePtr       = &handles.CD,
    },
    {
        .name            = "WP",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = "SD Card Write Protect",
        .handlePtr       = &handles.WP,
    },
    {
        .name            = "LCTL",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "SD Card Interface busy LED drive",
        .handlePtr       = &handles.LCTL,
    },
    {
        .name            = "reset",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.reset,
        .netCB           = resetFunction,
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
        .name        = "SD_DRIVE",
        .type        = ppm_PT_STRING,
        .description = "The name of the Image file used for the SD Drive",
    },
    {
        .name        = "SD_DRIVE_DELTA",
        .type        = ppm_PT_BOOL,
        .description = "If present the SD Drive uses delta writes",
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
        .vendor  = "nxp.ovpworld.org",
        .library = "peripheral",
        .name    = "iMX6_SDHC",
        .version = "1.0"
    },

    .family               = "nxp.ovpworld.org",
    .noRecursiveCallbacks = 1,
    .extension = "model",

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

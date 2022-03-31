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
        .name            = "DMACSP",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x13f,
        .mustBeConnected = 1,
        .remappable      = 0,
        .description     = "DMA Registers Slave Port",
    },
    {
        .name            = "MREAD",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .addrBitsMin     = 32,
        .addrBitsMax     = 0,
        .mustBeConnected = 0,
        .description     = "DMA Registers Master Port - Read",
    },
    {
        .name            = "MWRITE",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .addrBitsMin     = 32,
        .addrBitsMax     = 0,
        .mustBeConnected = 0,
        .description     = "DMA Registers Master Port - Write",
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
        .name            = "INTTC",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interrupt Request when DMA operation is complete",
        .handlePtr       = &handles.INTTC,
    },
    {
        .name            = "RESET",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Peripheral Reset",
        .handlePtr       = &handles.RESET,
        .netCB           = uReset,
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

ppmModelAttr modelAttrs = {

    .versionString    = PPM_VERSION_STRING,
    .type             = PPM_MT_PERIPHERAL,

    .busPortsCB       = nextBusPort,  
    .netPortsCB       = nextNetPort,  

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .docCB         = installDocs,

    .vlnv          = {
        .vendor  = "ovpworld.org",
        .library = "peripheral",
        .name    = "SimpleDma",
        .version = "1.0"
    },

    .family               = "ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

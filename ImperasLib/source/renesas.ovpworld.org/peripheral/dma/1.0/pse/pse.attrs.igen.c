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
        .name            = "DMAP0",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0xf,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "DMAP1",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0xff,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "DMAPM",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 28,
        .addrBitsMin     = 28,
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
        .name            = "INTDMA0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDMA[0],
        .userData        = (void*)0,
    },
    {
        .name            = "INTDMA1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDMA[1],
        .userData        = (void*)1,
    },
    {
        .name            = "INTDMA2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDMA[2],
        .userData        = (void*)2,
    },
    {
        .name            = "INTDMA3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDMA[3],
        .userData        = (void*)3,
    },
    {
        .name            = "INTDMA4",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDMA[4],
        .userData        = (void*)4,
    },
    {
        .name            = "INTDMA5",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDMA[5],
        .userData        = (void*)5,
    },
    {
        .name            = "INTDMA6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDMA[6],
        .userData        = (void*)6,
    },
    {
        .name            = "INTDMA7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDMA[7],
        .userData        = (void*)7,
    },
    {
        .name            = "INTDMA8",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDMA[8],
        .userData        = (void*)8,
    },
    {
        .name            = "INTDMA9",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDMA[9],
        .userData        = (void*)9,
    },
    {
        .name            = "DMA0EN",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.DMA0EN,
    },
    {
        .name            = "DMA1EN",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.DMA1EN,
    },
    {
        .name            = "ADDMARQ0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ADDMARQ0,
        .netCB           = triggerADDMARQ0,
    },
    {
        .name            = "ADDMARQ1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ADDMARQ1,
        .netCB           = triggerADDMARQ1,
    },
    {
        .name            = "INTTS0CD",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTS0CD,
        .netCB           = triggerINTTS0CD,
    },
    {
        .name            = "INTTS1CD",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTS1CD,
        .netCB           = triggerINTTS1CD,
    },
    {
        .name            = "INTCE0C",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTCE0C,
        .netCB           = triggerINTCE0C,
    },
    {
        .name            = "INTCE1C",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTCE1C,
        .netCB           = triggerINTCE1C,
    },
    {
        .name            = "INTBE0R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTBE0R,
        .netCB           = triggerINTBE0R,
    },
    {
        .name            = "INTBE1R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTBE1R,
        .netCB           = triggerINTBE1R,
    },
    {
        .name            = "INTUC0R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTUC0R,
        .netCB           = triggerINTUC0R,
    },
    {
        .name            = "INTUC1R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTUC1R,
        .netCB           = triggerINTUC1R,
    },
    {
        .name            = "INTUC2R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTUC2R,
        .netCB           = triggerINTUC2R,
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
        .vendor  = "renesas.ovpworld.org",
        .library = "peripheral",
        .name    = "dma",
        .version = "1.0"
    },

    .family               = "renesas.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

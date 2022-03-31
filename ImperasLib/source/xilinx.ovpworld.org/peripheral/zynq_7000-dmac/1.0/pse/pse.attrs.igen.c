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
        .name            = "bportS",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0xfff,
        .mustBeConnected = 1,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "bportNS",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0xfff,
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
        .name            = "Int0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = " DMAC Interrupt",
        .handlePtr       = &handles.Int[0],
    },
    {
        .name            = "Int1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = " DMAC Interrupt",
        .handlePtr       = &handles.Int[1],
    },
    {
        .name            = "Int2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = " DMAC Interrupt",
        .handlePtr       = &handles.Int[2],
    },
    {
        .name            = "Int3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = " DMAC Interrupt",
        .handlePtr       = &handles.Int[3],
    },
    {
        .name            = "Int4",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = " DMAC Interrupt",
        .handlePtr       = &handles.Int[4],
    },
    {
        .name            = "Int5",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = " DMAC Interrupt",
        .handlePtr       = &handles.Int[5],
    },
    {
        .name            = "Int6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = " DMAC Interrupt",
        .handlePtr       = &handles.Int[6],
    },
    {
        .name            = "Int7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = " DMAC Interrupt",
        .handlePtr       = &handles.Int[7],
    },
    {
        .name            = "inta",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interrupt DMAC Transfer Abort",
        .handlePtr       = &handles.inta,
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
        .vendor  = "xilinx.ovpworld.org",
        .library = "peripheral",
        .name    = "zynq_7000-dmac",
        .version = "1.0"
    },

    .family               = "xilinx.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

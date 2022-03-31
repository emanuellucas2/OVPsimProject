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
        .addrHi          = 0xfff,
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
        .name            = "fiq",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.fiq,
    },
    {
        .name            = "ir0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[0],
        .netCB           = irqUpdate,
        .userData        = (void*)0,
    },
    {
        .name            = "ir1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[1],
        .netCB           = irqUpdate,
        .userData        = (void*)1,
    },
    {
        .name            = "ir2",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[2],
        .netCB           = irqUpdate,
        .userData        = (void*)2,
    },
    {
        .name            = "ir3",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[3],
        .netCB           = irqUpdate,
        .userData        = (void*)3,
    },
    {
        .name            = "ir4",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[4],
        .netCB           = irqUpdate,
        .userData        = (void*)4,
    },
    {
        .name            = "ir5",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[5],
        .netCB           = irqUpdate,
        .userData        = (void*)5,
    },
    {
        .name            = "ir6",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[6],
        .netCB           = irqUpdate,
        .userData        = (void*)6,
    },
    {
        .name            = "ir7",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[7],
        .netCB           = irqUpdate,
        .userData        = (void*)7,
    },
    {
        .name            = "ir8",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[8],
        .netCB           = irqUpdate,
        .userData        = (void*)8,
    },
    {
        .name            = "ir9",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[9],
        .netCB           = irqUpdate,
        .userData        = (void*)9,
    },
    {
        .name            = "ir10",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[10],
        .netCB           = irqUpdate,
        .userData        = (void*)10,
    },
    {
        .name            = "ir11",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[11],
        .netCB           = irqUpdate,
        .userData        = (void*)11,
    },
    {
        .name            = "ir12",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[12],
        .netCB           = irqUpdate,
        .userData        = (void*)12,
    },
    {
        .name            = "ir13",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[13],
        .netCB           = irqUpdate,
        .userData        = (void*)13,
    },
    {
        .name            = "ir14",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[14],
        .netCB           = irqUpdate,
        .userData        = (void*)14,
    },
    {
        .name            = "ir15",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[15],
        .netCB           = irqUpdate,
        .userData        = (void*)15,
    },
    {
        .name            = "ir16",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[16],
        .netCB           = irqUpdate,
        .userData        = (void*)16,
    },
    {
        .name            = "ir17",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[17],
        .netCB           = irqUpdate,
        .userData        = (void*)17,
    },
    {
        .name            = "ir18",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[18],
        .netCB           = irqUpdate,
        .userData        = (void*)18,
    },
    {
        .name            = "ir19",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[19],
        .netCB           = irqUpdate,
        .userData        = (void*)19,
    },
    {
        .name            = "ir20",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[20],
        .netCB           = irqUpdate,
        .userData        = (void*)20,
    },
    {
        .name            = "ir21",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[21],
        .netCB           = irqUpdate,
        .userData        = (void*)21,
    },
    {
        .name            = "ir22",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[22],
        .netCB           = irqUpdate,
        .userData        = (void*)22,
    },
    {
        .name            = "ir23",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[23],
        .netCB           = irqUpdate,
        .userData        = (void*)23,
    },
    {
        .name            = "ir24",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[24],
        .netCB           = irqUpdate,
        .userData        = (void*)24,
    },
    {
        .name            = "ir25",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[25],
        .netCB           = irqUpdate,
        .userData        = (void*)25,
    },
    {
        .name            = "ir26",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[26],
        .netCB           = irqUpdate,
        .userData        = (void*)26,
    },
    {
        .name            = "ir27",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[27],
        .netCB           = irqUpdate,
        .userData        = (void*)27,
    },
    {
        .name            = "ir28",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[28],
        .netCB           = irqUpdate,
        .userData        = (void*)28,
    },
    {
        .name            = "ir29",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[29],
        .netCB           = irqUpdate,
        .userData        = (void*)29,
    },
    {
        .name            = "ir30",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[30],
        .netCB           = irqUpdate,
        .userData        = (void*)30,
    },
    {
        .name            = "ir31",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir[31],
        .netCB           = irqUpdate,
        .userData        = (void*)31,
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
        .vendor  = "arm.ovpworld.org",
        .library = "peripheral",
        .name    = "IntICP",
        .version = "1.0"
    },

    .family               = "arm.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

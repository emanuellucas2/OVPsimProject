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
        .name            = "bp1",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x3fff,
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
        .name            = "P0",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[0],
        .netCB           = P_wcb,
        .userData        = (void*)0,
    },
    {
        .name            = "P1",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[1],
        .netCB           = P_wcb,
        .userData        = (void*)1,
    },
    {
        .name            = "P2",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[2],
        .netCB           = P_wcb,
        .userData        = (void*)2,
    },
    {
        .name            = "P3",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[3],
        .netCB           = P_wcb,
        .userData        = (void*)3,
    },
    {
        .name            = "P4",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[4],
        .netCB           = P_wcb,
        .userData        = (void*)4,
    },
    {
        .name            = "P5",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[5],
        .netCB           = P_wcb,
        .userData        = (void*)5,
    },
    {
        .name            = "P6",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[6],
        .netCB           = P_wcb,
        .userData        = (void*)6,
    },
    {
        .name            = "P7",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[7],
        .netCB           = P_wcb,
        .userData        = (void*)7,
    },
    {
        .name            = "P8",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[8],
        .netCB           = P_wcb,
        .userData        = (void*)8,
    },
    {
        .name            = "P9",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[9],
        .netCB           = P_wcb,
        .userData        = (void*)9,
    },
    {
        .name            = "P10",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[10],
        .netCB           = P_wcb,
        .userData        = (void*)10,
    },
    {
        .name            = "P11",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[11],
        .netCB           = P_wcb,
        .userData        = (void*)11,
    },
    {
        .name            = "P12",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[12],
        .netCB           = P_wcb,
        .userData        = (void*)12,
    },
    {
        .name            = "P13",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[13],
        .netCB           = P_wcb,
        .userData        = (void*)13,
    },
    {
        .name            = "P14",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[14],
        .netCB           = P_wcb,
        .userData        = (void*)14,
    },
    {
        .name            = "P15",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[15],
        .netCB           = P_wcb,
        .userData        = (void*)15,
    },
    {
        .name            = "P16",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[16],
        .netCB           = P_wcb,
        .userData        = (void*)16,
    },
    {
        .name            = "P17",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[17],
        .netCB           = P_wcb,
        .userData        = (void*)17,
    },
    {
        .name            = "P18",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[18],
        .netCB           = P_wcb,
        .userData        = (void*)18,
    },
    {
        .name            = "P19",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[19],
        .netCB           = P_wcb,
        .userData        = (void*)19,
    },
    {
        .name            = "P20",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[20],
        .netCB           = P_wcb,
        .userData        = (void*)20,
    },
    {
        .name            = "P21",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[21],
        .netCB           = P_wcb,
        .userData        = (void*)21,
    },
    {
        .name            = "P22",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[22],
        .netCB           = P_wcb,
        .userData        = (void*)22,
    },
    {
        .name            = "P23",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[23],
        .netCB           = P_wcb,
        .userData        = (void*)23,
    },
    {
        .name            = "P24",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[24],
        .netCB           = P_wcb,
        .userData        = (void*)24,
    },
    {
        .name            = "P25",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[25],
        .netCB           = P_wcb,
        .userData        = (void*)25,
    },
    {
        .name            = "P26",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[26],
        .netCB           = P_wcb,
        .userData        = (void*)26,
    },
    {
        .name            = "P27",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[27],
        .netCB           = P_wcb,
        .userData        = (void*)27,
    },
    {
        .name            = "P28",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[28],
        .netCB           = P_wcb,
        .userData        = (void*)28,
    },
    {
        .name            = "P29",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[29],
        .netCB           = P_wcb,
        .userData        = (void*)29,
    },
    {
        .name            = "P30",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[30],
        .netCB           = P_wcb,
        .userData        = (void*)30,
    },
    {
        .name            = "P31",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.P[31],
        .netCB           = P_wcb,
        .userData        = (void*)31,
    },
    {
        .name            = "IRQ",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.IRQ,
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
        .vendor  = "atmel.ovpworld.org",
        .library = "peripheral",
        .name    = "ParallelIOController",
        .version = "1.0"
    },

    .family               = "atmel.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

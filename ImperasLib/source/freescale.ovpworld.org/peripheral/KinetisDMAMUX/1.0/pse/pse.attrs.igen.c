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
        .name            = "Reset",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Reset,
        .netCB           = reset_Reset,
    },
    {
        .name            = "eDMARequest",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.eDMARequest,
    },
    {
        .name            = "dmaSrc0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[0],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)0,
    },
    {
        .name            = "dmaSrc1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[1],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)1,
    },
    {
        .name            = "dmaSrc2",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[2],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)2,
    },
    {
        .name            = "dmaSrc3",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[3],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)3,
    },
    {
        .name            = "dmaSrc4",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[4],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)4,
    },
    {
        .name            = "dmaSrc5",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[5],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)5,
    },
    {
        .name            = "dmaSrc6",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[6],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)6,
    },
    {
        .name            = "dmaSrc7",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[7],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)7,
    },
    {
        .name            = "dmaSrc8",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[8],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)8,
    },
    {
        .name            = "dmaSrc9",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[9],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)9,
    },
    {
        .name            = "dmaSrc10",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[10],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)10,
    },
    {
        .name            = "dmaSrc11",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[11],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)11,
    },
    {
        .name            = "dmaSrc12",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[12],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)12,
    },
    {
        .name            = "dmaSrc13",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[13],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)13,
    },
    {
        .name            = "dmaSrc14",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[14],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)14,
    },
    {
        .name            = "dmaSrc15",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[15],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)15,
    },
    {
        .name            = "dmaSrc16",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[16],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)16,
    },
    {
        .name            = "dmaSrc17",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[17],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)17,
    },
    {
        .name            = "dmaSrc18",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[18],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)18,
    },
    {
        .name            = "dmaSrc19",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[19],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)19,
    },
    {
        .name            = "dmaSrc20",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[20],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)20,
    },
    {
        .name            = "dmaSrc21",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[21],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)21,
    },
    {
        .name            = "dmaSrc22",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[22],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)22,
    },
    {
        .name            = "dmaSrc23",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[23],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)23,
    },
    {
        .name            = "dmaSrc24",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[24],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)24,
    },
    {
        .name            = "dmaSrc25",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[25],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)25,
    },
    {
        .name            = "dmaSrc26",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[26],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)26,
    },
    {
        .name            = "dmaSrc27",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[27],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)27,
    },
    {
        .name            = "dmaSrc28",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[28],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)28,
    },
    {
        .name            = "dmaSrc29",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[29],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)29,
    },
    {
        .name            = "dmaSrc30",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[30],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)30,
    },
    {
        .name            = "dmaSrc31",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[31],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)31,
    },
    {
        .name            = "dmaSrc32",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[32],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)32,
    },
    {
        .name            = "dmaSrc33",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[33],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)33,
    },
    {
        .name            = "dmaSrc34",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[34],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)34,
    },
    {
        .name            = "dmaSrc35",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[35],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)35,
    },
    {
        .name            = "dmaSrc36",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[36],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)36,
    },
    {
        .name            = "dmaSrc37",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[37],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)37,
    },
    {
        .name            = "dmaSrc38",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[38],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)38,
    },
    {
        .name            = "dmaSrc39",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[39],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)39,
    },
    {
        .name            = "dmaSrc40",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[40],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)40,
    },
    {
        .name            = "dmaSrc41",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[41],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)41,
    },
    {
        .name            = "dmaSrc42",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[42],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)42,
    },
    {
        .name            = "dmaSrc43",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[43],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)43,
    },
    {
        .name            = "dmaSrc44",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[44],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)44,
    },
    {
        .name            = "dmaSrc45",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[45],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)45,
    },
    {
        .name            = "dmaSrc46",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[46],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)46,
    },
    {
        .name            = "dmaSrc47",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[47],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)47,
    },
    {
        .name            = "dmaSrc48",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[48],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)48,
    },
    {
        .name            = "dmaSrc49",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[49],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)49,
    },
    {
        .name            = "dmaSrc50",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[50],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)50,
    },
    {
        .name            = "dmaSrc51",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[51],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)51,
    },
    {
        .name            = "dmaSrc52",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[52],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)52,
    },
    {
        .name            = "dmaSrc53",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[53],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)53,
    },
    {
        .name            = "dmaSrc54",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[54],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)54,
    },
    {
        .name            = "dmaSrc55",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[55],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)55,
    },
    {
        .name            = "dmaSrc56",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[56],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)56,
    },
    {
        .name            = "dmaSrc57",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[57],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)57,
    },
    {
        .name            = "dmaSrc58",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[58],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)58,
    },
    {
        .name            = "dmaSrc59",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[59],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)59,
    },
    {
        .name            = "dmaSrc60",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[60],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)60,
    },
    {
        .name            = "dmaSrc61",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[61],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)61,
    },
    {
        .name            = "dmaSrc62",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[62],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)62,
    },
    {
        .name            = "dmaSrc63",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.dmaSrc[63],
        .netCB           = dmaSrcRequest,
        .userData        = (void*)63,
    },
    {
        .name            = "trg1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.trg[0],
        .netCB           = dmaTrgRequest,
        .userData        = (void*)0,
    },
    {
        .name            = "trg2",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.trg[1],
        .netCB           = dmaTrgRequest,
        .userData        = (void*)1,
    },
    {
        .name            = "trg3",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.trg[2],
        .netCB           = dmaTrgRequest,
        .userData        = (void*)2,
    },
    {
        .name            = "trg4",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.trg[3],
        .netCB           = dmaTrgRequest,
        .userData        = (void*)3,
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
        .name        = "startDMAChannel",
        .type        = ppm_PT_UNS32,
        .description = "Starting channel number, 0, 16, 32.. (default 0)",
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
        .vendor  = "freescale.ovpworld.org",
        .library = "peripheral",
        .name    = "KinetisDMAMUX",
        .version = "1.0"
    },

    .family               = "freescale.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

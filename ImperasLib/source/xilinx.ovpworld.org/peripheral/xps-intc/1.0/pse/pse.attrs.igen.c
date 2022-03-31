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
        .name            = "plb",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x1f,
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
        .name            = "Irq",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Irq,
    },
    {
        .name            = "Intr0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[0],
        .netCB           = WriteIntr,
        .userData        = (void*)0,
    },
    {
        .name            = "Intr1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[1],
        .netCB           = WriteIntr,
        .userData        = (void*)1,
    },
    {
        .name            = "Intr2",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[2],
        .netCB           = WriteIntr,
        .userData        = (void*)2,
    },
    {
        .name            = "Intr3",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[3],
        .netCB           = WriteIntr,
        .userData        = (void*)3,
    },
    {
        .name            = "Intr4",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[4],
        .netCB           = WriteIntr,
        .userData        = (void*)4,
    },
    {
        .name            = "Intr5",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[5],
        .netCB           = WriteIntr,
        .userData        = (void*)5,
    },
    {
        .name            = "Intr6",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[6],
        .netCB           = WriteIntr,
        .userData        = (void*)6,
    },
    {
        .name            = "Intr7",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[7],
        .netCB           = WriteIntr,
        .userData        = (void*)7,
    },
    {
        .name            = "Intr8",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[8],
        .netCB           = WriteIntr,
        .userData        = (void*)8,
    },
    {
        .name            = "Intr9",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[9],
        .netCB           = WriteIntr,
        .userData        = (void*)9,
    },
    {
        .name            = "Intr10",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[10],
        .netCB           = WriteIntr,
        .userData        = (void*)10,
    },
    {
        .name            = "Intr11",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[11],
        .netCB           = WriteIntr,
        .userData        = (void*)11,
    },
    {
        .name            = "Intr12",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[12],
        .netCB           = WriteIntr,
        .userData        = (void*)12,
    },
    {
        .name            = "Intr13",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[13],
        .netCB           = WriteIntr,
        .userData        = (void*)13,
    },
    {
        .name            = "Intr14",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[14],
        .netCB           = WriteIntr,
        .userData        = (void*)14,
    },
    {
        .name            = "Intr15",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[15],
        .netCB           = WriteIntr,
        .userData        = (void*)15,
    },
    {
        .name            = "Intr16",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[16],
        .netCB           = WriteIntr,
        .userData        = (void*)16,
    },
    {
        .name            = "Intr17",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[17],
        .netCB           = WriteIntr,
        .userData        = (void*)17,
    },
    {
        .name            = "Intr18",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[18],
        .netCB           = WriteIntr,
        .userData        = (void*)18,
    },
    {
        .name            = "Intr19",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[19],
        .netCB           = WriteIntr,
        .userData        = (void*)19,
    },
    {
        .name            = "Intr20",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[20],
        .netCB           = WriteIntr,
        .userData        = (void*)20,
    },
    {
        .name            = "Intr21",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[21],
        .netCB           = WriteIntr,
        .userData        = (void*)21,
    },
    {
        .name            = "Intr22",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[22],
        .netCB           = WriteIntr,
        .userData        = (void*)22,
    },
    {
        .name            = "Intr23",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[23],
        .netCB           = WriteIntr,
        .userData        = (void*)23,
    },
    {
        .name            = "Intr24",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[24],
        .netCB           = WriteIntr,
        .userData        = (void*)24,
    },
    {
        .name            = "Intr25",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[25],
        .netCB           = WriteIntr,
        .userData        = (void*)25,
    },
    {
        .name            = "Intr26",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[26],
        .netCB           = WriteIntr,
        .userData        = (void*)26,
    },
    {
        .name            = "Intr27",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[27],
        .netCB           = WriteIntr,
        .userData        = (void*)27,
    },
    {
        .name            = "Intr28",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[28],
        .netCB           = WriteIntr,
        .userData        = (void*)28,
    },
    {
        .name            = "Intr29",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[29],
        .netCB           = WriteIntr,
        .userData        = (void*)29,
    },
    {
        .name            = "Intr30",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[30],
        .netCB           = WriteIntr,
        .userData        = (void*)30,
    },
    {
        .name            = "Intr31",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Intr[31],
        .netCB           = WriteIntr,
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

static ppmParameter parameters[] = {
    {
        .name        = "endian",
        .type        = ppm_PT_STRING,
        .description = "Specify the endian of the processor interface (default big endian)",
        .u.stringParam.defaultValue = "big",
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
        .vendor  = "xilinx.ovpworld.org",
        .library = "peripheral",
        .name    = "xps-intc",
        .version = "1.0"
    },

    .family               = "xilinx.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

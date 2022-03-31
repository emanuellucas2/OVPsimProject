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
        .addrHi          = 0xff,
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
        .name            = "reset",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Reset signal",
        .handlePtr       = &handles.reset,
        .netCB           = resetCB,
    },
    {
        .name            = "intOut_0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[0],
    },
    {
        .name            = "intOut_1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[1],
    },
    {
        .name            = "intOut_2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[2],
    },
    {
        .name            = "intOut_3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[3],
    },
    {
        .name            = "intOut_4",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[4],
    },
    {
        .name            = "intOut_5",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[5],
    },
    {
        .name            = "intOut_6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[6],
    },
    {
        .name            = "intOut_7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[7],
    },
    {
        .name            = "intOut_8",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[8],
    },
    {
        .name            = "intOut_9",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[9],
    },
    {
        .name            = "intOut_10",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[10],
    },
    {
        .name            = "intOut_11",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[11],
    },
    {
        .name            = "intOut_12",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[12],
    },
    {
        .name            = "intOut_13",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[13],
    },
    {
        .name            = "intOut_14",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[14],
    },
    {
        .name            = "intOut_15",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[15],
    },
    {
        .name            = "intOut_16",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[16],
    },
    {
        .name            = "intOut_17",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[17],
    },
    {
        .name            = "intOut_18",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[18],
    },
    {
        .name            = "intOut_19",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[19],
    },
    {
        .name            = "intOut_20",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[20],
    },
    {
        .name            = "intOut_21",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[21],
    },
    {
        .name            = "intOut_22",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[22],
    },
    {
        .name            = "intOut_23",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[23],
    },
    {
        .name            = "intOut_24",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[24],
    },
    {
        .name            = "intOut_25",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[25],
    },
    {
        .name            = "intOut_26",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[26],
    },
    {
        .name            = "intOut_27",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[27],
    },
    {
        .name            = "intOut_28",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[28],
    },
    {
        .name            = "intOut_29",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[29],
    },
    {
        .name            = "intOut_30",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interupt Outputs",
        .handlePtr       = &handles.intOut_[30],
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
        .name        = "clockMHz",
        .type        = ppm_PT_DOUBLE,
        .description = "Clock rate used in timer calculations (in MHz)",
        .u.doubleParam.defaultValue = 1.0,
    },
    {
        .name        = "numharts",
        .type        = ppm_PT_UNS32,
        .description = "Number of harts supported (1-31)",
        .u.uns32Param.min          = 1,
        .u.uns32Param.max          = 31,
        .u.uns32Param.defaultValue = 4,
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
        .vendor  = "andes.ovpworld.org",
        .library = "peripheral",
        .name    = "NCEPLMT100",
        .version = "1.0"
    },

    .family               = "andes.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

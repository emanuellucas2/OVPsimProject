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
        .name            = "TMSP0",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x29,
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
        .name            = "TOS0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TOS0,
    },
    {
        .name            = "TOS1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TOS1,
    },
    {
        .name            = "TOS2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TOS2,
    },
    {
        .name            = "TOS3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TOS3,
    },
    {
        .name            = "TOS4",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TOS4,
    },
    {
        .name            = "TOS5",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TOS5,
    },
    {
        .name            = "TOS6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TOS6,
    },
    {
        .name            = "TOS7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TOS7,
    },
    {
        .name            = "TSADTRG0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TSADTRG0,
    },
    {
        .name            = "TSADTRG1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TSADTRG1,
    },
    {
        .name            = "TSAEDO",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TSAEDO,
    },
    {
        .name            = "TSESG",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TSESG,
    },
    {
        .name            = "TSTSF",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TSTSF,
    },
    {
        .name            = "INTTSCC0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTSCC0,
    },
    {
        .name            = "INTTSCC1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTSCC1,
    },
    {
        .name            = "INTTSCC2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTSCC2,
    },
    {
        .name            = "INTTSCC3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTSCC3,
    },
    {
        .name            = "INTTSCC4",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTSCC4,
    },
    {
        .name            = "INTTSCC5",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTSCC5,
    },
    {
        .name            = "INTTSCD0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTSCD0,
    },
    {
        .name            = "INTTSOD",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTSOD,
    },
    {
        .name            = "INTTSOV",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTSOV,
    },
    {
        .name            = "INTTSER",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTSER,
    },
    {
        .name            = "INTTSWN",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTSWN,
    },
    {
        .name            = "TTRGS",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTRGS,
        .netCB           = P_TTRGS,
    },
    {
        .name            = "TEVTS",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TEVTS,
        .netCB           = P_TEVTS,
    },
    {
        .name            = "TAPTS0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TAPTS0,
        .netCB           = P_TAPTS0,
    },
    {
        .name            = "TAPTS1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TAPTS1,
        .netCB           = P_TAPTS1,
    },
    {
        .name            = "TAPTS2",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TAPTS2,
        .netCB           = P_TAPTS2,
    },
    {
        .name            = "ESO",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ESO,
        .netCB           = P_ESO,
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
        .name        = "PCLK0",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "PCLK1",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "PCLK2",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "PCLK3",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "PCLK4",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "PCLK5",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "PCLK7",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "PCLK9",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "PCLK_DEF",
        .type        = ppm_PT_UNS32,
        .description = 0,
        .u.uns32Param.min          = 0,
        .u.uns32Param.max          = 9,
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "PARAM_01",
        .type        = ppm_PT_UNS32,
        .description = 0,
        .u.uns32Param.defaultValue = 0,
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
        .vendor  = "renesas.ovpworld.org",
        .library = "peripheral",
        .name    = "tms",
        .version = "1.0"
    },

    .family               = "renesas.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

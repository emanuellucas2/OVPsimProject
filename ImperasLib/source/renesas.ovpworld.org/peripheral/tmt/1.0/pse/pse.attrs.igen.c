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
        .name            = "TMTP0",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0xf,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "TMTP1",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x1,
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
        .name            = "TOT0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TOT0,
    },
    {
        .name            = "TOT1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TOT1,
    },
    {
        .name            = "TTTTO0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTTO0,
    },
    {
        .name            = "TTTT01",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTT01,
    },
    {
        .name            = "TTTICC0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTICC0,
    },
    {
        .name            = "TTTICC1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTICC1,
    },
    {
        .name            = "TTTEQC0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTEQC0,
    },
    {
        .name            = "TTTEQC1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTEQC1,
    },
    {
        .name            = "INTTTCC0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTTCC0,
    },
    {
        .name            = "INTTTCC1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTTCC1,
    },
    {
        .name            = "INTTTOV",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTTOV,
    },
    {
        .name            = "INTTTEC",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTTTEC,
    },
    {
        .name            = "TIT0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TIT0,
        .netCB           = P_TIT0,
    },
    {
        .name            = "TIT1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TIT1,
        .netCB           = P_TIT1,
    },
    {
        .name            = "TEVTT",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TEVTT,
        .netCB           = P_TEVTT,
    },
    {
        .name            = "TTRGT",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTRGT,
        .netCB           = P_TTRGT,
    },
    {
        .name            = "TENCT0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TENCT0,
        .netCB           = P_TENCT0,
    },
    {
        .name            = "TENCT1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TENCT1,
        .netCB           = P_TENCT1,
    },
    {
        .name            = "TECRT",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TECRT,
        .netCB           = P_TECRT,
    },
    {
        .name            = "TTTTI0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTTI0,
        .netCB           = P_TTTTI0,
    },
    {
        .name            = "TTTTI1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTTI1,
        .netCB           = P_TTTTI1,
    },
    {
        .name            = "TTTENC0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTENC0,
        .netCB           = P_TTTENC0,
    },
    {
        .name            = "TTTENC1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTENC1,
        .netCB           = P_TTTENC1,
    },
    {
        .name            = "TTTTRG",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTTRG,
        .netCB           = P_TTTTRG,
    },
    {
        .name            = "TTTEVT",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTEVT,
        .netCB           = P_TTTEVT,
    },
    {
        .name            = "TTTECR",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TTTECR,
        .netCB           = P_TTTECR,
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
        .name        = "PlantModelPWMMode",
        .type        = ppm_PT_BOOL,
        .description = 0,
        .u.boolParam.defaultValue = False,
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
        .name    = "tmt",
        .version = "1.0"
    },

    .family               = "renesas.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

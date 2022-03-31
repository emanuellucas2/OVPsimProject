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
        .addrHi          = 0x7,
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
        .name            = "ExtSample",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ExtSample,
        .netCB           = extSampleCB,
    },
    {
        .name            = "Vin1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Vin1,
    },
    {
        .name            = "Vin2",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Vin2,
    },
    {
        .name            = "Input0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Input0,
        .netCB           = input0CB,
    },
    {
        .name            = "Input1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Input1,
        .netCB           = input1CB,
    },
    {
        .name            = "Input2",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Input2,
        .netCB           = input2CB,
    },
    {
        .name            = "Input3",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Input3,
        .netCB           = input3CB,
    },
    {
        .name            = "Input4",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Input4,
        .netCB           = input4CB,
    },
    {
        .name            = "Input5",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Input5,
        .netCB           = input5CB,
    },
    {
        .name            = "Input6",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Input6,
        .netCB           = input6CB,
    },
    {
        .name            = "Input7",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Input7,
        .netCB           = input7CB,
    },
    {
        .name            = "DacOutput",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.DacOutput,
    },
    {
        .name            = "CoutSoc",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.CoutSoc,
    },
    {
        .name            = "Interrupt",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Interrupt,
    },
    {
        .name            = "DmaReq",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.DmaReq,
    },
    {
        .name            = "CmpOPad",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.CmpOPad,
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
        .name        = "cmpNumber",
        .type        = ppm_PT_UNS32,
        .description = "Comparator channel number: 0,1,2 or3  (default 0)",
        .u.uns32Param.min          = 0,
        .u.uns32Param.max          = 3,
    },
    {
        .name        = "stimFile",
        .type        = ppm_PT_STRING,
        .description = "Stimulus file for the comparator",
    },
    {
        .name        = "configure_cr0",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_cr1",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_fpr",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_scr",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_daccr",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_muxcr",
        .type        = ppm_PT_UNS32,
        .description = 0,
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
        .name    = "KinetisCMP",
        .version = "1.0"
    },

    .family               = "freescale.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

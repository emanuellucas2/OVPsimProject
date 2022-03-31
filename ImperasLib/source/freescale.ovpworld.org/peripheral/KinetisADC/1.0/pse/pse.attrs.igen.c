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
        .name            = "AltClk",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.AltClk,
        .netCB           = altClkCB,
    },
    {
        .name            = "HwTrig",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.HwTrig,
        .netCB           = hwTrigCB,
    },
    {
        .name            = "AdIn",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.AdIn,
    },
    {
        .name            = "Vrefsh",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Vrefsh,
    },
    {
        .name            = "Vrefsl",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Vrefsl,
    },
    {
        .name            = "AdInId",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.AdInId,
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
        .name        = "stimFile0",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "bus_clock_freq",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_sc1a",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_sc1b",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_cfg1",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_cfg2",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_cv1",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_cv2",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_sc2",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "configure_sc3",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "input_vrefh",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "input_vrefl",
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
        .name    = "KinetisADC",
        .version = "1.0"
    },

    .family               = "freescale.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

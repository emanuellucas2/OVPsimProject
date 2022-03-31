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
        .name            = "irq0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "IRQ port",
        .handlePtr       = &handles.irq[0],
    },
    {
        .name            = "irq1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "IRQ port",
        .handlePtr       = &handles.irq[1],
    },
    {
        .name            = "irq2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "IRQ port",
        .handlePtr       = &handles.irq[2],
    },
    {
        .name            = "irq3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "IRQ port",
        .handlePtr       = &handles.irq[3],
    },
    {
        .name            = "trg0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Trigger port",
        .handlePtr       = &handles.trg[0],
    },
    {
        .name            = "trg1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Trigger port",
        .handlePtr       = &handles.trg[1],
    },
    {
        .name            = "trg2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Trigger port",
        .handlePtr       = &handles.trg[2],
    },
    {
        .name            = "trg3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Trigger port",
        .handlePtr       = &handles.trg[3],
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
        .name        = "frequency",
        .type        = ppm_PT_UNS64,
        .description = "Frequency of the clock input in MHz (default is 80MHz)",
        .u.uns64Param.defaultValue = 80,
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
        .name    = "KinetisPIT",
        .version = "1.0"
    },

    .family               = "freescale.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

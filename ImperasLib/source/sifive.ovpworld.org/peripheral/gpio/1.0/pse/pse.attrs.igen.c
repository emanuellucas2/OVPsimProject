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
        .name            = "resetNet",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.resetNet,
        .netCB           = resetCB,
    },
    {
        .name            = "intOut0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut0,
    },
    {
        .name            = "intOut1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut1,
    },
    {
        .name            = "intOut2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut2,
    },
    {
        .name            = "intOut3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut3,
    },
    {
        .name            = "intOut4",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut4,
    },
    {
        .name            = "intOut5",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut5,
    },
    {
        .name            = "intOut6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut6,
    },
    {
        .name            = "intOut7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut7,
    },
    {
        .name            = "intOut8",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut8,
    },
    {
        .name            = "intOut9",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut9,
    },
    {
        .name            = "intOut10",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut10,
    },
    {
        .name            = "intOut11",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut11,
    },
    {
        .name            = "intOut12",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut12,
    },
    {
        .name            = "intOut13",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut13,
    },
    {
        .name            = "intOut14",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut14,
    },
    {
        .name            = "intOut15",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intOut15,
    },
    {
        .name            = "gpios0",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios0,
        .netCB           = gpioInCB,
        .userData        = (void*)0,
    },
    {
        .name            = "gpios1",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios1,
        .netCB           = gpioInCB,
        .userData        = (void*)1,
    },
    {
        .name            = "gpios2",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios2,
        .netCB           = gpioInCB,
        .userData        = (void*)2,
    },
    {
        .name            = "gpios3",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios3,
        .netCB           = gpioInCB,
        .userData        = (void*)3,
    },
    {
        .name            = "gpios4",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios4,
        .netCB           = gpioInCB,
        .userData        = (void*)4,
    },
    {
        .name            = "gpios5",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios5,
        .netCB           = gpioInCB,
        .userData        = (void*)5,
    },
    {
        .name            = "gpios6",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios6,
        .netCB           = gpioInCB,
        .userData        = (void*)6,
    },
    {
        .name            = "gpios7",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios7,
        .netCB           = gpioInCB,
        .userData        = (void*)7,
    },
    {
        .name            = "gpios8",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios8,
        .netCB           = gpioInCB,
        .userData        = (void*)8,
    },
    {
        .name            = "gpios9",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios9,
        .netCB           = gpioInCB,
        .userData        = (void*)9,
    },
    {
        .name            = "gpios10",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios10,
        .netCB           = gpioInCB,
        .userData        = (void*)10,
    },
    {
        .name            = "gpios11",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios11,
        .netCB           = gpioInCB,
        .userData        = (void*)11,
    },
    {
        .name            = "gpios12",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios12,
        .netCB           = gpioInCB,
        .userData        = (void*)12,
    },
    {
        .name            = "gpios13",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios13,
        .netCB           = gpioInCB,
        .userData        = (void*)13,
    },
    {
        .name            = "gpios14",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios14,
        .netCB           = gpioInCB,
        .userData        = (void*)14,
    },
    {
        .name            = "gpios15",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.gpios15,
        .netCB           = gpioInCB,
        .userData        = (void*)15,
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
    BHM_HTTP_FORMALS,
    BHM_RECORD_REPLAY_FORMALS,
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
        .vendor  = "sifive.ovpworld.org",
        .library = "peripheral",
        .name    = "gpio",
        .version = "1.0"
    },

    .family               = "sifive.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

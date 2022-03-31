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
        .name            = "resetNet",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.resetNet,
        .netCB           = reset_resetNet,
    },
    {
        .name            = "TZPCR0SIZE",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCR0SIZE,
    },
    {
        .name            = "TZPCDECPROT0_0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_0,
    },
    {
        .name            = "TZPCDECPROT0_1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_1,
    },
    {
        .name            = "TZPCDECPROT0_2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_2,
    },
    {
        .name            = "TZPCDECPROT0_3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_3,
    },
    {
        .name            = "TZPCDECPROT0_4",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_4,
    },
    {
        .name            = "TZPCDECPROT0_5",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_5,
    },
    {
        .name            = "TZPCDECPROT0_6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_6,
    },
    {
        .name            = "TZPCDECPROT0_7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_7,
    },
    {
        .name            = "TZPCDECPROT0_8",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_8,
    },
    {
        .name            = "TZPCDECPROT0_9",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_9,
    },
    {
        .name            = "TZPCDECPROT0_10",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_10,
    },
    {
        .name            = "TZPCDECPROT0_11",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_11,
    },
    {
        .name            = "TZPCDECPROT0_12",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_12,
    },
    {
        .name            = "TZPCDECPROT0_13",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_13,
    },
    {
        .name            = "TZPCDECPROT0_14",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_14,
    },
    {
        .name            = "TZPCDECPROT0_15",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT0_15,
    },
    {
        .name            = "TZPCDECPROT1_0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_0,
    },
    {
        .name            = "TZPCDECPROT1_1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_1,
    },
    {
        .name            = "TZPCDECPROT1_2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_2,
    },
    {
        .name            = "TZPCDECPROT1_3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_3,
    },
    {
        .name            = "TZPCDECPROT1_4",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_4,
    },
    {
        .name            = "TZPCDECPROT1_5",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_5,
    },
    {
        .name            = "TZPCDECPROT1_6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_6,
    },
    {
        .name            = "TZPCDECPROT1_7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_7,
    },
    {
        .name            = "TZPCDECPROT1_8",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_8,
    },
    {
        .name            = "TZPCDECPROT1_9",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_9,
    },
    {
        .name            = "TZPCDECPROT1_10",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_10,
    },
    {
        .name            = "TZPCDECPROT1_11",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_11,
    },
    {
        .name            = "TZPCDECPROT1_12",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_12,
    },
    {
        .name            = "TZPCDECPROT1_13",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_13,
    },
    {
        .name            = "TZPCDECPROT1_14",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_14,
    },
    {
        .name            = "TZPCDECPROT1_15",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT1_15,
    },
    {
        .name            = "TZPCDECPROT2_0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_0,
    },
    {
        .name            = "TZPCDECPROT2_1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_1,
    },
    {
        .name            = "TZPCDECPROT2_2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_2,
    },
    {
        .name            = "TZPCDECPROT2_3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_3,
    },
    {
        .name            = "TZPCDECPROT2_4",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_4,
    },
    {
        .name            = "TZPCDECPROT2_5",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_5,
    },
    {
        .name            = "TZPCDECPROT2_6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_6,
    },
    {
        .name            = "TZPCDECPROT2_7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_7,
    },
    {
        .name            = "TZPCDECPROT2_8",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_8,
    },
    {
        .name            = "TZPCDECPROT2_9",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_9,
    },
    {
        .name            = "TZPCDECPROT2_10",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_10,
    },
    {
        .name            = "TZPCDECPROT2_11",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_11,
    },
    {
        .name            = "TZPCDECPROT2_12",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_12,
    },
    {
        .name            = "TZPCDECPROT2_13",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_13,
    },
    {
        .name            = "TZPCDECPROT2_14",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_14,
    },
    {
        .name            = "TZPCDECPROT2_15",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.TZPCDECPROT2_15,
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
        .vendor  = "arm.ovpworld.org",
        .library = "peripheral",
        .name    = "TzpcBP147",
        .version = "1.0"
    },

    .family               = "arm.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

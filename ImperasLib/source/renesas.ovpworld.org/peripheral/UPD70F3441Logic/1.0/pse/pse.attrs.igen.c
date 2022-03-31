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
        .name            = "LOGICP0",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x3,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "LOGICP1",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x75,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "LOGICP2",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0xb,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "LOGICP3",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x0,
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
        .name            = "NMIIN",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.NMIIN,
        .netCB           = P_NMIIN,
    },
    {
        .name            = "INTDEDF",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDEDF,
        .netCB           = P_INTDEDF,
    },
    {
        .name            = "INTDEDR",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDEDR,
        .netCB           = P_INTDEDR,
    },
    {
        .name            = "INTDEDFR",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDEDFR,
        .netCB           = P_INTDEDFR,
    },
    {
        .name            = "INTOSD",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTOSD,
        .netCB           = P_INTOSD,
    },
    {
        .name            = "INTP4",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTP4,
        .netCB           = P_INTP4,
    },
    {
        .name            = "INTUC0R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTUC0R,
        .netCB           = P_INTUC0R,
    },
    {
        .name            = "INTP5",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTP5,
        .netCB           = P_INTP5,
    },
    {
        .name            = "INTUC1R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTUC1R,
        .netCB           = P_INTUC1R,
    },
    {
        .name            = "INTBRG0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTBRG0,
        .netCB           = P_INTBRG0,
    },
    {
        .name            = "INTBRG1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTBRG1,
        .netCB           = P_INTBRG1,
    },
    {
        .name            = "INTCB0T",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTCB0T,
        .netCB           = P_INTCB0T,
    },
    {
        .name            = "INTUC2T",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTUC2T,
        .netCB           = P_INTUC2T,
    },
    {
        .name            = "INTCB0R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTCB0R,
        .netCB           = P_INTCB0R,
    },
    {
        .name            = "INTUC2R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTUC2R,
        .netCB           = P_INTUC2R,
    },
    {
        .name            = "INTP13",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTP13,
        .netCB           = P_INTP13,
    },
    {
        .name            = "INTCB0RE",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTCB0RE,
        .netCB           = P_INTCB0RE,
    },
    {
        .name            = "INTUC2RE",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTUC2RE,
        .netCB           = P_INTUC2RE,
    },
    {
        .name            = "INTDMA3",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTDMA3,
        .netCB           = P_INTDMA3,
    },
    {
        .name            = "INTFL",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INTFL,
        .netCB           = P_INTFL,
    },
    {
        .name            = "NMIOUT",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.NMIOUT,
    },
    {
        .name            = "INT0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INT0,
    },
    {
        .name            = "INT1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INT1,
    },
    {
        .name            = "INT6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INT6,
    },
    {
        .name            = "INT7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INT7,
    },
    {
        .name            = "INT75",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INT75,
    },
    {
        .name            = "INT99",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INT99,
    },
    {
        .name            = "INT100",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INT100,
    },
    {
        .name            = "INT101",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INT101,
    },
    {
        .name            = "INT116",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.INT116,
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
        .vendor  = "renesas.ovpworld.org",
        .library = "peripheral",
        .name    = "UPD70F3441Logic",
        .version = "1.0"
    },

    .family               = "renesas.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

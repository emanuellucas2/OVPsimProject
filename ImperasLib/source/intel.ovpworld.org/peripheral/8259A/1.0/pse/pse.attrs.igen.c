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
        .name            = "io",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x1,
        .mustBeConnected = 1,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "PCIackS",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x0,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "elcr",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x0,
        .mustBeConnected = 1,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "cascade",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 3,
        .addrBitsMin     = 3,
        .addrBitsMax     = 0,
        .mustBeConnected = 0,
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
        .name            = "ir0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir0,
    },
    {
        .name            = "ir1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir1,
    },
    {
        .name            = "ir2",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir2,
    },
    {
        .name            = "ir3",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir3,
    },
    {
        .name            = "ir4",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir4,
    },
    {
        .name            = "ir5",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir5,
    },
    {
        .name            = "ir6",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir6,
    },
    {
        .name            = "ir7",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ir7,
    },
    {
        .name            = "cas",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.cas,
    },
    {
        .name            = "intp",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 1,
        .description     = 0,
        .handlePtr       = &handles.intp,
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
        .name        = "spen",
        .type        = ppm_PT_STRING,
        .description = "Configure the PIC as a \"master\" or \"slave\"",
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
        .vendor  = "intel.ovpworld.org",
        .library = "peripheral",
        .name    = "8259A",
        .version = "1.0"
    },

    .family               = "intel.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

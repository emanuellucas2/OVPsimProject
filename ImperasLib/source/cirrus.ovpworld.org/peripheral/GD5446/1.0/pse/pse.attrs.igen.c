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
        .name            = "config",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x2f,
        .mustBeConnected = 1,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "memory",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x3fffff,
        .mustBeConnected = 1,
        .remappable      = 1,
        .description     = 0,
    },
    {
        .name            = "PCIconfig",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x7ff,
        .mustBeConnected = 0,
        .remappable      = 1,
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

static ppmParameter parameters[] = {
    {
        .name        = "PCIslot",
        .type        = ppm_PT_UNS32,
        .description = "Specify which PCI slot the device occupies.",
    },
    {
        .name        = "PCIfunction",
        .type        = ppm_PT_UNS32,
        .description = "Specify which PCI function the device responds to.",
    },
    {
        .name        = "scanDelay",
        .type        = ppm_PT_UNS32,
        .description = "Number of uS between frame refreshes.",
        .u.uns32Param.defaultValue = 200,
    },
    {
        .name        = "noGraphics",
        .type        = ppm_PT_BOOL,
        .description = "If non:zero, disables the graphics window.",
    },
    {
        .name        = "title",
        .type        = ppm_PT_STRING,
        .description = "Title for the VGA screen.",
    },
    {
        .name        = "endian",
        .type        = ppm_PT_STRING,
        .description = "Set the system endian, \"big\" or \"little\"; used for writing boot code. Default is \"little\" endian.",
        .u.stringParam.defaultValue = "little",
    },
    {
        .name        = "pixelChecksum",
        .type        = ppm_PT_BOOL,
        .description = "Write a checksum of each screen contents",
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
    .paramSpecCB      = nextParameter,

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .docCB         = installDocs,

    .vlnv          = {
        .vendor  = "cirrus.ovpworld.org",
        .library = "peripheral",
        .name    = "GD5446",
        .version = "1.0"
    },

    .family               = "cirrus.ovpworld.org",
    .noRecursiveCallbacks = 1,
    .extension = "model",

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

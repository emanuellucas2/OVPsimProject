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
        .name            = "memory",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x0,
        .mustBeConnected = 0,
        .remappable      = 1,
        .description     = 0,
    },
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
        .name            = "irq",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq,
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
        .name        = "busOffset",
        .type        = ppm_PT_UNS32,
        .description = "Set an offset for the display memory window",
    },
    {
        .name        = "scanDelay",
        .type        = ppm_PT_UNS32,
        .description = "Set the rate of the display refresh (default 20000)",
        .u.uns32Param.defaultValue = 20000,
    },
    {
        .name        = "noGraphics",
        .type        = ppm_PT_BOOL,
        .description = "Disable the graphics output",
    },
    {
        .name        = "resolution",
        .type        = ppm_PT_STRING,
        .description = "Set the resolution of the display. VGA (default), SVGA, XVGA/XGA.",
        .u.stringParam.defaultValue = "vga",
    },
    {
        .name        = "pixelChecksum",
        .type        = ppm_PT_BOOL,
        .description = "Write a checksum of each screen contents",
    },
    {
        .name        = "packedPixels",
        .type        = ppm_PT_BOOL,
        .description = "Only valid when 24BPP used. Set to enable pixel packing in data buffer. Default 24 bit pixel stored in 32-bit data word.",
    },
    {
        .name        = "title",
        .type        = ppm_PT_STRING,
        .description = "Set the title of the display window",
        .u.stringParam.defaultValue = "PL110 LCD",
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
        .vendor  = "arm.ovpworld.org",
        .library = "peripheral",
        .name    = "LcdPL110",
        .version = "1.0"
    },

    .family               = "arm.ovpworld.org",
    .noRecursiveCallbacks = 1,
    .extension = "model",

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

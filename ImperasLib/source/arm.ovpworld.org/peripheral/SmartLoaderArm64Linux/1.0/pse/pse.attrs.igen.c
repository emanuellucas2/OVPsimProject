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
        .name            = "mport",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .addrBitsMin     = 32,
        .addrBitsMax     = 49,
        .mustBeConnected = 1,
        .description     = "Master port - connect to same bus connected to Linux processor's data port",
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
        .name        = "kernel",
        .type        = ppm_PT_STRING,
        .description = "Name of the the Linux kernel image file (default: Image)",
        .u.stringParam.defaultValue = "Image",
    },
    {
        .name        = "kerneladdr",
        .type        = ppm_PT_UNS64,
        .description = "Address to load the Linux kernel image file (default: physicalbase+0x00080000)",
    },
    {
        .name        = "dtb",
        .type        = ppm_PT_STRING,
        .description = "Name of the device tree blob file. (required)",
    },
    {
        .name        = "command",
        .type        = ppm_PT_STRING,
        .description = "Set command line passed to kernel. (optional)",
    },
    {
        .name        = "append",
        .type        = ppm_PT_STRING,
        .description = "Append to the command line passed to kernel. (optional)",
    },
    {
        .name        = "initrd",
        .type        = ppm_PT_STRING,
        .description = "Name of the initial ram disk file to load. (optional)",
    },
    {
        .name        = "physicalbase",
        .type        = ppm_PT_UNS64,
        .description = "The physical address of the base of memory. (default: 0)",
    },
    {
        .name        = "disable",
        .type        = ppm_PT_BOOL,
        .description = "Set to True to disable the smart loader",
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
        .vendor  = "arm.ovpworld.org",
        .library = "peripheral",
        .name    = "SmartLoaderArm64Linux",
        .version = "1.0"
    },

    .family               = "arm.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

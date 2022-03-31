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
        .addrBitsMax     = 48,
        .mustBeConnected = 1,
        .description     = "Master port - connect this to the same bus connected to the Linux processor's data port.",
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

static ppmEnumParameter bootconventionValues[] = {
    { .name = "bbl", .value = 0},
    { .name = "fsbl", .value = 1},
    { 0 }
};

static ppmParameter parameters[] = {
    {
        .name        = "dtb",
        .type        = ppm_PT_STRING,
        .description = "Name of the device tree blob file. (required when Smart Loader is not disabled)",
    },
    {
        .name        = "command",
        .type        = ppm_PT_STRING,
        .description = "Set command line passed to kernel. Will override a command line defined in the dtb. (optional)",
    },
    {
        .name        = "append",
        .type        = ppm_PT_STRING,
        .description = "Append to the kernel command line defined in the dtb. (optional)",
    },
    {
        .name        = "membase",
        .type        = ppm_PT_UNS64,
        .description = "Base of main memory region (overrides device tree memory node when membase and memsize both set)",
    },
    {
        .name        = "memsize",
        .type        = ppm_PT_UNS64,
        .description = "Size of main memory region (overrides device tree memory node  when membase and memsize both set)",
    },
    {
        .name        = "slbootaddr",
        .type        = ppm_PT_UNS64,
        .description = "Address where SmartLoader generated boot code and dtb will be loaded. Jump to this address to start boot process. (default: 0x1000)",
    },
    {
        .name        = "bootimage",
        .type        = ppm_PT_STRING,
        .description = "Name of boot image file to load at bootaddr, e.g. bbl.bin (optional - may instead load boot elf file with standard --objfilenoentry option)",
    },
    {
        .name        = "bootaddr",
        .type        = ppm_PT_UNS64,
        .description = "Address to call from SmartLoader's generated boot code. (default 0x80000000)",
    },
    {
        .name        = "bootconvention",
        .type        = ppm_PT_ENUM,
        .description = "Boot convention to use in call from SmartLoader generated boot code (bbl=Berkeley Boot Loader, fsbl=SiFive FSBL). (default: bbl)",
        .u.enumParam.legalValues = bootconventionValues,
    },
    {
        .name        = "disable",
        .type        = ppm_PT_BOOL,
        .description = "Set to True to disable the SmartLoader. (all other parameters are ignored when this is set to True)",
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
        .vendor  = "riscv.ovpworld.org",
        .library = "peripheral",
        .name    = "SmartLoaderRV64Linux",
        .version = "1.0"
    },

    .family               = "riscv.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

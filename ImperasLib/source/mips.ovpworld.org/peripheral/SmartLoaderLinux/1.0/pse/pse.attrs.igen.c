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
        .name            = "idport",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x3,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = "This is a slave port that provides the boardId for Malta (default 0x420)",
    },
    {
        .name            = "mport",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .addrBitsMin     = 32,
        .addrBitsMax     = 40,
        .mustBeConnected = 0,
        .description     = "This is a master port to access the memory in the system for initalisation of initrd and writing boot code to the reset vector",
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
        .description = "This must specify the name of the Linux kernel that is being loaded. This must be consistent with the imagefile loaded and specified by the imagefile attribute on the processor.",
    },
    {
        .name        = "dtb",
        .type        = ppm_PT_STRING,
        .description = "Optionally specific the flattened device tree blob file specifying the development board details for the Linux kernel to read.",
    },
    {
        .name        = "envpaddress",
        .type        = ppm_PT_UNS32,
        .description = "The hex address in virtual memory that contains the command line. Default 0x80002000.",
        .u.uns32Param.defaultValue = 0x80002000,
    },
    {
        .name        = "initrd",
        .type        = ppm_PT_STRING,
        .description = "Specify a compressed initial ram disk file file for loading.",
    },
    {
        .name        = "root",
        .type        = ppm_PT_STRING,
        .description = "Specify the root filesystem for booting. This is a string of the form '/dev/hda1'.",
    },
    {
        .name        = "boardid",
        .type        = ppm_PT_UNS32,
        .description = "Allows the boardID to be configured. Defaults to 0x420 for Malta with CoreLV.",
    },
    {
        .name        = "memsize",
        .type        = ppm_PT_UNS32,
        .description = "The decimal size of the available memory. For Example 128MBytes is 134217728.",
        .u.uns32Param.defaultValue = 134217728,
    },
    {
        .name        = "command",
        .type        = ppm_PT_STRING,
        .description = "This attribute allows an additional kernal command(s) to be added.",
    },
    {
        .name        = "nonelinux",
        .type        = ppm_PT_BOOL,
        .description = "This attribute allows a non linux program to be loaded onto the Malta platform. \n                                         The program elf should be passed as though it was the kernel file.",
    },
    {
        .name        = "bootimage",
        .type        = ppm_PT_STRING,
        .description = "This attribute is used to pass a new boot image for the non:volatile memory \n                                         that contains the reset vector from which the procesor starts execution.",
    },
    {
        .name        = "endian",
        .type        = ppm_PT_STRING,
        .description = "Set the system endian, \"big\" or \"little\"; used for writing boot code. Default is \"little\" endian.",
        .u.stringParam.defaultValue = "little",
    },
    {
        .name        = "goldfish",
        .type        = ppm_PT_BOOL,
        .description = "This attribute is used to indicate that the peripheral is being used to configure the Android Goldfish platform.",
    },
    {
        .name        = "writebootimage",
        .type        = ppm_PT_STRING,
        .description = "This attribute is used to control the writing of a file of the boot code containing the reset vector from which the procesor starts execution.",
    },
    {
        .name        = "fixuplinuxstart",
        .type        = ppm_PT_UNS32,
        .description = "This attribute is used to set the address at which the the code should be 'fixed' \n                        to add the setup required for booting a linux kernel\n                        a0 = number of kernel arguments\n                        a1 = command table start\n                        a2 = command line arguments start\n                        a3 = size fo physical ram",
    },
    {
        .name        = "disablebootgen",
        .type        = ppm_PT_BOOL,
        .description = "Disable the generation of boot code.",
    },
    {
        .name        = "disable",
        .type        = ppm_PT_BOOL,
        .description = "Disable this peripheral. Only provides the boardId in this case.",
    },
    {
        .name        = "PCIslot",
        .type        = ppm_PT_UNS32,
        .description = "Specify the PCI slot.",
    },
    {
        .name        = "PCIfunction",
        .type        = ppm_PT_UNS32,
        .description = "Specify the PCI function number.",
    },
    {
        .name        = "pagebits",
        .type        = ppm_PT_UNS32,
        .description = "Specify the number of bits to be used when aligning the initrd data (should match page size configured into kernel). default=12.",
        .u.uns32Param.defaultValue = 12,
    },
    {
        .name        = "initrdhigh",
        .type        = ppm_PT_BOOL,
        .description = "Locate the initial ramdisk in top of memory. By default the ramdisk is located in the next page after the top of the kernel image.",
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
        .vendor  = "mips.ovpworld.org",
        .library = "peripheral",
        .name    = "SmartLoaderLinux",
        .version = "1.0"
    },

    .family               = "mips.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

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
        .addrHi          = 0xbff,
        .mustBeConnected = 1,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "spOCMDDR",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x0,
        .mustBeConnected = 1,
        .remappable      = 1,
        .description     = 0,
    },
    {
        .name            = "mpOCM",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .addrBitsMin     = 32,
        .addrBitsMax     = 0,
        .mustBeConnected = 1,
        .description     = 0,
    },
    {
        .name            = "mpDDR",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .addrBitsMin     = 32,
        .addrBitsMax     = 0,
        .mustBeConnected = 1,
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
        .name            = "A9_RST0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.A9_RST0,
    },
    {
        .name            = "A9_RST1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.A9_RST1,
    },
    {
        .name            = "ARM1Deration",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ARM1Deration,
    },
    {
        .name            = "ARM0Deration",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.ARM0Deration,
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
        .name        = "lockcode",
        .type        = ppm_PT_UNS32,
        .description = 0,
        .u.uns32Param.defaultValue = 0x767b,
    },
    {
        .name        = "unlockcode",
        .type        = ppm_PT_UNS32,
        .description = 0,
        .u.uns32Param.defaultValue = 0xdf0d,
    },
    {
        .name        = "deviceid",
        .type        = ppm_PT_UNS32,
        .description = 0,
        .u.uns32Param.defaultValue = 2,
    },
    {
        .name        = "devicerev",
        .type        = ppm_PT_UNS32,
        .description = 0,
        .u.uns32Param.defaultValue = 1,
    },
    {
        .name        = "psclock",
        .type        = ppm_PT_UNS32,
        .description = "Define the master clock (PS_CLK) frequency in MHz (default 33)",
        .u.uns32Param.defaultValue = 33,
    },
    {
        .name        = "armmips",
        .type        = ppm_PT_UNS32,
        .description = "Define ARM CPU MIPS Rate in MIPS (default 500)",
        .u.uns32Param.defaultValue = 500,
    },
    {
        .name        = "bootmode",
        .type        = ppm_PT_UNS32,
        .description = "Define BOOT_MODE value (default 0x04)",
        .u.uns32Param.defaultValue = 0x04,
    },
    {
        .name        = "clockcontroldisable",
        .type        = ppm_PT_BOOL,
        .description = "Disable change to ARM processor operating frequency when ARM PLL or clock control registers are modified.",
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
        .vendor  = "xilinx.ovpworld.org",
        .library = "peripheral",
        .name    = "zynq_7000-slcr",
        .version = "1.0"
    },

    .family               = "xilinx.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

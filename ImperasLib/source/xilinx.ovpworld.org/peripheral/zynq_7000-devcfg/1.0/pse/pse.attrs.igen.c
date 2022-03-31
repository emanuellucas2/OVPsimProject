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
    {
        .name            = "xadc",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 0,
        .addrBitsMin     = 0,
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
        .name            = "intOut",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interrupt signal",
        .handlePtr       = &handles.intOut,
    },
    {
        .name            = "xadcmux",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Selects the channel for the XADC interface sample",
        .handlePtr       = &handles.xadcmux,
        .netCB           = xadcMuxSelect,
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
        .name        = "board",
        .type        = ppm_PT_STRING,
        .description = "The XADC interface includes default data values, access is board dependent so must be configured. Valid 'zc706' or 'zc702' (default zc706)",
        .u.stringParam.defaultValue = "zc706",
    },
    {
        .name        = "config",
        .type        = ppm_PT_STRING,
        .description = "The configuratation file defining default values and Voltage Monitor names",
    },
    {
        .name        = "voutmode",
        .type        = ppm_PT_INT32,
        .description = "Set the value to read for VOUT_MODE (default -12)",
        .u.int32Param.defaultValue = -12,
    },
    {
        .name        = "statusmfrspecific",
        .type        = ppm_PT_UNS32,
        .description = "Set the value to read for STATUS_MFR_SPECIFIC (default 0)",
        .u.uns32Param.defaultValue = 0,
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
        .name    = "zynq_7000-devcfg",
        .version = "1.0"
    },

    .family               = "xilinx.ovpworld.org",
    .noRecursiveCallbacks = 1,
    .extension = "model",

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

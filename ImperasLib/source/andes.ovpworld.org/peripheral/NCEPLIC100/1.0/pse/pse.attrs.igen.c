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
        .name            = "port0",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x3fffff,
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
        .name            = "reset",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Reset signal",
        .handlePtr       = &handles.reset,
        .netCB           = resetCB,
    },
    {
        .name            = "irqS1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irqS1,
        .netCB           = irqUpdate,
        .userData        = (void*)1,
    },
    {
        .name            = "irqT0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irqT0,
    },
    { 0 }
};


#define NUM_NET_PORT_ENTRIES            (sizeof(netPorts) / sizeof(*netPorts))
#define NET_PORT_TERMINATOR             (netPorts + (NUM_NET_PORT_ENTRIES - 1))

static PPM_NET_PORT_FN(nextNetPort) {
    if(!netPort) {
         netPort = netPorts;
    } else {
        netPort++;
        if (netPort == NET_PORT_TERMINATOR) {
            netPort = nextNetPortUser(NULL);
        }
    }
    return (netPort && netPort->name) ? netPort : 0;
}

static ppmParameter parameters[] = {
    {
        .name        = "num_sources",
        .type        = ppm_PT_UNS32,
        .description = "Number of Input Interrupt Sources",
        .u.uns32Param.min          = 1,
        .u.uns32Param.max          = 1023,
        .u.uns32Param.defaultValue = 63,
    },
    {
        .name        = "num_targets",
        .type        = ppm_PT_UNS32,
        .description = "Number of Output Interrupt Targets",
        .u.uns32Param.min          = 1,
        .u.uns32Param.max          = 16,
        .u.uns32Param.defaultValue = 1,
    },
    {
        .name        = "num_priorities",
        .type        = ppm_PT_UNS32,
        .description = "Number of Priority levels",
        .u.uns32Param.min          = 1,
        .u.uns32Param.max          = 255,
        .u.uns32Param.defaultValue = 15,
    },
    {
        .name        = "priority_base",
        .type        = ppm_PT_UNS32,
        .description = "Base Address offset for Priority Registers",
        .u.uns32Param.defaultValue = 0x0,
    },
    {
        .name        = "pending_base",
        .type        = ppm_PT_UNS32,
        .description = "Base Address offset for Pending Registers",
        .u.uns32Param.defaultValue = 0x1000,
    },
    {
        .name        = "enable_base",
        .type        = ppm_PT_UNS32,
        .description = "Base Address offset for Enable Registers",
        .u.uns32Param.defaultValue = 0x2000,
    },
    {
        .name        = "enable_stride",
        .type        = ppm_PT_UNS32,
        .description = "Stride size for Enable Register Block",
        .u.uns32Param.defaultValue = 0x80,
    },
    {
        .name        = "context_base",
        .type        = ppm_PT_UNS32,
        .description = "Base Address offset for Context Registers, Threshold and Claim/Complete",
        .u.uns32Param.defaultValue = 0x200000,
    },
    {
        .name        = "context_stride",
        .type        = ppm_PT_UNS32,
        .description = "Stride size for Context Register Block",
        .u.uns32Param.defaultValue = 0x1000,
    },
    {
        .name        = "andes_version",
        .type        = ppm_PT_UNS32,
        .description = "Andes PLIC design version (value for VersionMaxPriority.VERSION field)",
        .u.uns32Param.max          = 0xffff,
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "vector_plic_support",
        .type        = ppm_PT_BOOL,
        .description = "Andes Vectored PLIC support - adds t<x>_eiid and t<x>_eack ports when enabled",
        .u.boolParam.defaultValue = 1,
    },
    {
        .name        = "trigger_type0",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 0 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type1",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 1 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type2",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 2 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type3",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 3 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type4",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 4 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type5",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 5 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type6",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 6 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type7",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 7 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type8",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 8 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type9",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 9 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type10",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 10 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type11",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 11 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type12",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 12 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type13",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 13 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type14",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 14 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type15",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 15 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type16",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 16 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type17",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 17 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type18",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 18 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type19",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 19 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type20",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 20 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type21",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 21 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type22",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 22 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type23",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 23 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type24",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 24 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type25",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 25 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type26",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 26 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type27",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 27 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type28",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 28 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type29",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 29 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type30",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 30 value",
        .u.uns32Param.defaultValue = 0,
    },
    {
        .name        = "trigger_type31",
        .type        = ppm_PT_UNS32,
        .description = "Trigger type register 31 value",
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
        .vendor  = "andes.ovpworld.org",
        .library = "peripheral",
        .name    = "NCEPLIC100",
        .version = "1.0"
    },

    .family               = "andes.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

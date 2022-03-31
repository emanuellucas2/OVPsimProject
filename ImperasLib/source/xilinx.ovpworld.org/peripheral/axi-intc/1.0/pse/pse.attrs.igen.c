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
        .addrHi          = 0x1ff,
        .mustBeConnected = 1,
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
        .name            = "intr0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[0],
        .netCB           = intrInput,
        .userData        = (void*)0,
    },
    {
        .name            = "intr1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[1],
        .netCB           = intrInput,
        .userData        = (void*)1,
    },
    {
        .name            = "intr2",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[2],
        .netCB           = intrInput,
        .userData        = (void*)2,
    },
    {
        .name            = "intr3",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[3],
        .netCB           = intrInput,
        .userData        = (void*)3,
    },
    {
        .name            = "intr4",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[4],
        .netCB           = intrInput,
        .userData        = (void*)4,
    },
    {
        .name            = "intr5",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[5],
        .netCB           = intrInput,
        .userData        = (void*)5,
    },
    {
        .name            = "intr6",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[6],
        .netCB           = intrInput,
        .userData        = (void*)6,
    },
    {
        .name            = "intr7",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[7],
        .netCB           = intrInput,
        .userData        = (void*)7,
    },
    {
        .name            = "intr8",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[8],
        .netCB           = intrInput,
        .userData        = (void*)8,
    },
    {
        .name            = "intr9",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[9],
        .netCB           = intrInput,
        .userData        = (void*)9,
    },
    {
        .name            = "intr10",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[10],
        .netCB           = intrInput,
        .userData        = (void*)10,
    },
    {
        .name            = "intr11",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[11],
        .netCB           = intrInput,
        .userData        = (void*)11,
    },
    {
        .name            = "intr12",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[12],
        .netCB           = intrInput,
        .userData        = (void*)12,
    },
    {
        .name            = "intr13",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[13],
        .netCB           = intrInput,
        .userData        = (void*)13,
    },
    {
        .name            = "intr14",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[14],
        .netCB           = intrInput,
        .userData        = (void*)14,
    },
    {
        .name            = "intr15",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[15],
        .netCB           = intrInput,
        .userData        = (void*)15,
    },
    {
        .name            = "intr16",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[16],
        .netCB           = intrInput,
        .userData        = (void*)16,
    },
    {
        .name            = "intr17",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[17],
        .netCB           = intrInput,
        .userData        = (void*)17,
    },
    {
        .name            = "intr18",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[18],
        .netCB           = intrInput,
        .userData        = (void*)18,
    },
    {
        .name            = "intr19",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[19],
        .netCB           = intrInput,
        .userData        = (void*)19,
    },
    {
        .name            = "intr20",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[20],
        .netCB           = intrInput,
        .userData        = (void*)20,
    },
    {
        .name            = "intr21",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[21],
        .netCB           = intrInput,
        .userData        = (void*)21,
    },
    {
        .name            = "intr22",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[22],
        .netCB           = intrInput,
        .userData        = (void*)22,
    },
    {
        .name            = "intr23",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[23],
        .netCB           = intrInput,
        .userData        = (void*)23,
    },
    {
        .name            = "intr24",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[24],
        .netCB           = intrInput,
        .userData        = (void*)24,
    },
    {
        .name            = "intr25",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[25],
        .netCB           = intrInput,
        .userData        = (void*)25,
    },
    {
        .name            = "intr26",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[26],
        .netCB           = intrInput,
        .userData        = (void*)26,
    },
    {
        .name            = "intr27",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[27],
        .netCB           = intrInput,
        .userData        = (void*)27,
    },
    {
        .name            = "intr28",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[28],
        .netCB           = intrInput,
        .userData        = (void*)28,
    },
    {
        .name            = "intr29",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[29],
        .netCB           = intrInput,
        .userData        = (void*)29,
    },
    {
        .name            = "intr30",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[30],
        .netCB           = intrInput,
        .userData        = (void*)30,
    },
    {
        .name            = "intr31",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.intr[31],
        .netCB           = intrInput,
        .userData        = (void*)31,
    },
    {
        .name            = "irq_in",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq_in,
        .netCB           = intrInput,
        .userData        = (void*)256,
    },
    {
        .name            = "irq_addr_in",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq_addr_in,
    },
    {
        .name            = "irq_ack_out",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq_ack_out,
    },
    {
        .name            = "irq",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq,
    },
    {
        .name            = "irq_ack",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq_ack,
        .netCB           = ackInput,
    },
    {
        .name            = "irq_addr_out",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq_addr_out,
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
        .name        = "C_HAS_IPR",
        .type        = ppm_PT_BOOL,
        .description = "The Interrupt Pending Register exists",
        .u.boolParam.defaultValue = 1,
    },
    {
        .name        = "C_HAS_SIE",
        .type        = ppm_PT_BOOL,
        .description = "The Set Interrupt Enables Register exists",
        .u.boolParam.defaultValue = 1,
    },
    {
        .name        = "C_HAS_CIE",
        .type        = ppm_PT_BOOL,
        .description = "The Clear Interrupt Enables Register exists",
        .u.boolParam.defaultValue = 1,
    },
    {
        .name        = "C_HAS_IMR",
        .type        = ppm_PT_BOOL,
        .description = "The Interrupt Mode Register exists",
        .u.boolParam.defaultValue = 1,
    },
    {
        .name        = "C_HAS_FAST",
        .type        = ppm_PT_BOOL,
        .description = "The Fast Interrupt Logic is enabled",
        .u.boolParam.defaultValue = 1,
    },
    {
        .name        = "C_EN_CASCADE_MODE",
        .type        = ppm_PT_BOOL,
        .description = "Set to enable the cascading of interrupts",
    },
    {
        .name        = "C_CASCADE_MASTER",
        .type        = ppm_PT_BOOL,
        .description = "Set when the cascade master",
    },
    {
        .name        = "C_NUM_INTR_INPUTS",
        .type        = ppm_PT_UNS32,
        .description = "Set the number of active hardware interrupt inputs (default 16)",
        .u.uns32Param.min          = 1,
        .u.uns32Param.max          = 32,
        .u.uns32Param.defaultValue = 16,
    },
    {
        .name        = "C_NUM_SW_INTR",
        .type        = ppm_PT_UNS32,
        .description = "Set the number of software interrupts (default 4)",
        .u.uns32Param.min          = 0,
        .u.uns32Param.max          = 32,
        .u.uns32Param.defaultValue = 4,
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
        .name    = "axi-intc",
        .version = "1.0"
    },

    .family               = "xilinx.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

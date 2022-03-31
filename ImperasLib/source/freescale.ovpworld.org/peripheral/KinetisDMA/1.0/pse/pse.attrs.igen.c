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
        .addrHi          = 0x1fff,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "MREAD",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .addrBitsMin     = 32,
        .addrBitsMax     = 0,
        .mustBeConnected = 0,
        .description     = "DMA Master Read of address space",
    },
    {
        .name            = "MWRITE",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .addrBitsMin     = 32,
        .addrBitsMax     = 0,
        .mustBeConnected = 0,
        .description     = "DMA Master Write of address space",
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
        .name            = "Reset",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.Reset,
        .netCB           = DMAReset,
    },
    {
        .name            = "eDMARequest",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.eDMARequest,
        .netCB           = DMARequest,
    },
    {
        .name            = "eDMADone",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.eDMADone,
    },
    {
        .name            = "errorInterrupt",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Error Interrupt port",
        .handlePtr       = &handles.errorInterrupt,
    },
    {
        .name            = "dmaInterrupt_ch0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[0],
    },
    {
        .name            = "dmaInterrupt_ch1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[1],
    },
    {
        .name            = "dmaInterrupt_ch2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[2],
    },
    {
        .name            = "dmaInterrupt_ch3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[3],
    },
    {
        .name            = "dmaInterrupt_ch4",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[4],
    },
    {
        .name            = "dmaInterrupt_ch5",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[5],
    },
    {
        .name            = "dmaInterrupt_ch6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[6],
    },
    {
        .name            = "dmaInterrupt_ch7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[7],
    },
    {
        .name            = "dmaInterrupt_ch8",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[8],
    },
    {
        .name            = "dmaInterrupt_ch9",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[9],
    },
    {
        .name            = "dmaInterrupt_ch10",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[10],
    },
    {
        .name            = "dmaInterrupt_ch11",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[11],
    },
    {
        .name            = "dmaInterrupt_ch12",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[12],
    },
    {
        .name            = "dmaInterrupt_ch13",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[13],
    },
    {
        .name            = "dmaInterrupt_ch14",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[14],
    },
    {
        .name            = "dmaInterrupt_ch15",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[15],
    },
    {
        .name            = "dmaInterrupt_ch16",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[16],
    },
    {
        .name            = "dmaInterrupt_ch17",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[17],
    },
    {
        .name            = "dmaInterrupt_ch18",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[18],
    },
    {
        .name            = "dmaInterrupt_ch19",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[19],
    },
    {
        .name            = "dmaInterrupt_ch20",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[20],
    },
    {
        .name            = "dmaInterrupt_ch21",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[21],
    },
    {
        .name            = "dmaInterrupt_ch22",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[22],
    },
    {
        .name            = "dmaInterrupt_ch23",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[23],
    },
    {
        .name            = "dmaInterrupt_ch24",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[24],
    },
    {
        .name            = "dmaInterrupt_ch25",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[25],
    },
    {
        .name            = "dmaInterrupt_ch26",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[26],
    },
    {
        .name            = "dmaInterrupt_ch27",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[27],
    },
    {
        .name            = "dmaInterrupt_ch28",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[28],
    },
    {
        .name            = "dmaInterrupt_ch29",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[29],
    },
    {
        .name            = "dmaInterrupt_ch30",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[30],
    },
    {
        .name            = "dmaInterrupt_ch31",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done Interrupt",
        .handlePtr       = &handles.dmaInterrupt_ch[31],
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

ppmModelAttr modelAttrs = {

    .versionString    = PPM_VERSION_STRING,
    .type             = PPM_MT_PERIPHERAL,

    .busPortsCB       = nextBusPort,  
    .netPortsCB       = nextNetPort,  

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .docCB         = installDocs,

    .vlnv          = {
        .vendor  = "freescale.ovpworld.org",
        .library = "peripheral",
        .name    = "KinetisDMA",
        .version = "1.0"
    },

    .family               = "freescale.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

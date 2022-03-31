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
        .addrHi          = 0x3f,
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
        .name            = "reset",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Reset signal",
        .handlePtr       = &handles.reset,
        .netCB           = resetCB,
    },
    {
        .name            = "intOut",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Interrupt signal",
        .handlePtr       = &handles.intOut,
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
        .name        = "uart16450",
        .type        = ppm_PT_BOOL,
        .description = "Run in 16450 mode (no FIFOs)",
    },
    {
        .name        = "fifoSize",
        .type        = ppm_PT_UNS32,
        .description = "Size of fifos",
    },
    {
        .name        = "refClkFreq",
        .type        = ppm_PT_UNS32,
        .description = "Frequency (in hertz) of reference clock rate used in baud rate calculation",
    },
    {
        .name        = "simulatebaud",
        .type        = ppm_PT_BOOL,
        .description = "Description\nSet to true to simulate baud delay determined by the Divisor Latch register value and reference clock frequency.\nSet to false to run without delay - next read data is made available immediately upon read of Receiver Buffer Register.\nDefaults to false\n",
    },
    {
        .name        = "charmode",
        .type        = ppm_PT_BOOL,
        .description = "Description\nSet to true when the port is used to connect to a Telnet program and character mode is desired rather than the default Telnet line mode.\nWhen set to true a Telnet command sequence is sent at startup that configures the Telnet program into character mode. In addition null bytes are stripped from the data received.\n",
    },
    BHM_SER_OPEN_AUTO_FORMALS,
    BHM_RECORD_REPLAY_FORMALS,
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
        .name    = "ATCUART100",
        .version = "1.0"
    },

    .family               = "andes.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

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

static ppmConnInputPort FIFOInputPorts[] = {
    {
        .name            = "fifoPortIn",
        .mustBeConnected = 0,
        .description     = 0,
        .width           = 32,
        .handlePtr       = &handles.fifoPortIn
    },
    { 0 }
};

static PPM_CONN_INPUT_FN(connNextInput) {
    if(!port) {
         port = FIFOInputPorts;
    } else {
        port++;
    }
    return port->name ? port : 0;
}

static ppmConnOutputPort FIFOOutputPorts[] = {
    {
        .name            = "fifoPortOut",
        .mustBeConnected = 0,
        .description     = 0,
        .width           = 32,
        .handlePtr       = &handles.fifoPortOut
    },
    { 0 }
};

static PPM_CONN_OUTPUT_FN(connNextOutput) {
    if(!port) {
         port = FIFOOutputPorts;
    } else {
        port++;
    }
    return port->name ? port : 0;
}

ppmModelAttr modelAttrs = {

    .versionString    = PPM_VERSION_STRING,
    .type             = PPM_MT_PERIPHERAL,

    .connInputsCB     = connNextInput,
    .connOutputsCB    = connNextOutput,

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .docCB         = installDocs,

    .vlnv          = {
        .vendor  = "vendor.com",
        .library = "peripheral",
        .name    = "fifo",
        .version = "1.0"
    },

    .family               = "vendor.com",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_IMPERAS,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};

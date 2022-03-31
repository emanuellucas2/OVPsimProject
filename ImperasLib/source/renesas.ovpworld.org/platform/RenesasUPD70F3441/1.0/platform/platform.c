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
//                           Imperas/OVP Generated
//
////////////////////////////////////////////////////////////////////////////////


#include <string.h>
#include <stdlib.h>

#include "op/op.h"


#define PLATFORM_NAME "RenesasUPD70F3441"

struct optionsS {
} options = {
};


typedef struct optModuleObjectS {
    // insert module persistent data here
} optModuleObject;



// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);

    // insert constructor code here
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {
    // insert pre simulation code here
}

static OP_SIMULATE_STARTING_FN(moduleSimulateStart) {
    // insert simulation starting code here
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
    // insert post simulation code here
}

static OP_DESTRUCT_FN(moduleDestruct) {
    // insert destructor code here
}

// instantiate module components
static OP_CONSTRUCT_FN(instantiateComponents) {

    optDocNodeP doc1_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc1_node, "Open Source Apache 2.0");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Description");
    opDocTextAdd(doc_11_node, "The Renesas uPD70F3441 - V850/PHO3 platform");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Limitiations of peripheral functionality is documented within the peripheral component.\n       Unimplemented Components:\n           System Controller\n           Standby Controller\n           Bus Control Unit\n           Memory Controller\n           CAN Controller\n           FlexRay\n           I/O Ports\n           CPU-CRC\n           DATA-CRC\n           On-chip Debug Unit\n           NBD\n       Partially Implemented Components (not complete - only certain modes or features modeled or tested)\n           DMA\n       ");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");


    // Module Instance UPD70F3441

    const char *UPD70F3441_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "module",
        "RenesasUPD70F3441",
        "1.0",
        OP_MODULE,
        OP_VLNV_FATAL
    );

    opModuleNew(
        mi,       // parent module
        UPD70F3441_path,       // modelfile
        0,   // name
        0,
        0
    );

}

optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_MODULE,
    .name                 = PLATFORM_NAME,
    .objectSize           = sizeof(optModuleObject),
    .releaseStatus        = OP_OVP,
    .purpose              = OP_PP_BAREMETAL,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "renesas.ovpworld.org",
        .library = "platform",
        .name    = "RenesasUPD70F3441",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(PLATFORM_NAME, OP_AC_ALL);

    opCmdParseArgs(parser, argc, argv);

    optModuleP mi = opRootModuleNew(
        &modelAttrs,
        PLATFORM_NAME,
        OP_PARAMS(
             OP_PARAM_BOOL_SET(OP_FP_STOPONCONTROLC, 1)
        )
    );
    opRootModuleSimulate(mi);
    opSessionTerminate();
    return opErrors() ? 1 : 0;
}


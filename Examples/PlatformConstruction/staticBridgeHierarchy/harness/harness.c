/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#include <string.h>
#include <stdlib.h>

#include "op/op.h"

struct optionsS {
} options = {
};


typedef struct optModuleObjectS {
    // insert module persistent data here
} optModuleObject;


////////////////////////////////////////////////////////////////////////////////
//                         U S E R   F U N C T I O N S
////////////////////////////////////////////////////////////////////////////////

static OP_PRE_SIMULATE_FN(modulePreSimulate) {
// insert modulePreSimulate code here
}

static OP_SIMULATE_STARTING_FN(moduleSimulate) {
// insert moduleSimulate code here
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
// insert modulePostSimulate code here
}

static OP_DESTRUCT_FN(moduleDestruct) {
// insert moduleDestruct code here
}



// Change the name here if required.

#define MODULE_NAME "top"

static OP_CONSTRUCT_FN(moduleConstruct) {

    // Module Instance uut

    const char *uut_path = "module/model";
    opModuleNew(
        mi,          // parent module
        uut_path,    // modelfile
        "uut",       // name
        0,
        0
    );

}

optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_MODULE,
    .name                 = MODULE_NAME,
    .objectSize           = sizeof(optModuleObject),
    .releaseStatus        = OP_UNSET,
    .purpose              = OP_PP_BAREMETAL,
    .visibility           = OP_VISIBLE,
    .constructCB          = moduleConstruct,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulate,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    opCmdParseArgs(parser, argc, argv);

    optModuleP mi = opRootModuleNew(&modelAttrs, MODULE_NAME, 0);
    opRootModuleSimulate(mi);
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

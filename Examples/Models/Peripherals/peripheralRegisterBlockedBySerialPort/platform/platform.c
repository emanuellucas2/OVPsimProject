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

#include "op/op.h"

#include "hostapi/impTypes.h"

int main(int argc, const char *argv[]) {

    const char *file = "module/model." IMPERAS_SHRSUF;
    opSessionInit(OP_VERSION);

    optCmdParserP parser =  opCmdParserNew(argv[0], OP_AC_ALL);

    char *topName = "top";
    opCmdParserAdd(parser, "topname", 0, "name", "platform", OP_FT_STRINGVAL, &topName, "Name of root", 0, 0, 0);

    opCmdParseArgs(parser, argc, argv);

    optModuleP top = opRootModuleNew(0, topName, 0);

    opModuleNew(top, file, "m1", 0, 0);

    opRootModuleSimulate(top);
    opSessionTerminate();
    return 0;
}

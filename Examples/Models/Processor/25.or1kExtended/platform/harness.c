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

// OP interface includes
#include "op/op.h"

//
// Name for root and root module
//
#define MODULE_NAME "platform"

static OP_BUS_SLAVE_READ_FN(rdm) {
    opPrintf("harness: detects %u-byte read 0x%x\n", bytes, (Uns32) addr);
    *(Uns32*)data = 0xb00b00;
}

static OP_BUS_SLAVE_WRITE_FN(wrm) {
    opPrintf("harness: detects %u-byte write 0x%x = 0x%x\n", bytes, (Uns32)addr, *(Uns32*)data);
}

//
// Virtual platform construction and simulation
//
int main(int argc, const char **argv) {

    // initialize simulation session before calling any other OP functions
    opSessionInit(OP_VERSION);

    // check arguments
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    if(! opCmdParseArgs(parser, argc, argv)) {
        opMessage("E", "CLI", "Command Line parser error");
        return 1;
    }

    // create root module, enabling simulation interruption if Ctrl-C is pressed
    optModuleP mr = opRootModuleNew(
        0,
        MODULE_NAME,
        OP_PARAMS (
            OP_PARAM_BOOL_SET(OP_FP_STOPONCONTROLC, 1)
        )
    );

    // get processor model file
    const char *modelFile = "model";

    // create the processor bus
    optBusP bus = opBusNew(mr, "bus", 32, 0, 0);

    optProcessorP processor = opProcessorNew(
        mr,
        modelFile,
        "proc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus, "DATA")
               ,OP_BUS_CONNECT(bus, "INSTRUCTION")
               ,OP_BUS_CONNECT(bus, "bps", .slave=1, .addrLo = 0x80000000, .addrHi = 0x8fffffff)
               ,OP_BUS_CONNECT(bus, "bpm")
            )
        ),
        0
    );

    const char *semihostFile = opVLNVString( 0, "ovpworld.org", "modelSupport", "imperasExit", "1.0", OP_EXTENSION, OP_VLNV_FATAL);

    // attach imperasExit semihost library to processor
    opProcessorExtensionNew(processor, semihostFile, "imperasExit", 0);

    opMemoryNew(
        mr,
        "prog",
        OP_PRIV_RWX,
        (0x7fffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x7fffffffULL)
            )
        ),
        0
    );
    opMemoryNew(
        mr,
        "stk",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0xf0000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus, "sp1", .slave=1, .addrLo=0xf0000000LL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    /// monitor calls from intercept lib
    opBusSlaveNew (bus, "monitor", 0, OP_PRIV_RWX, 0x90000000, 0x9000ffff, rdm, wrm, 0, 0);

    opRootModuleSimulate(mr);

    // terminate the simulation session
    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}


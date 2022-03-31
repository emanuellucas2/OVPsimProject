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

//
// This is the callback, called once per installed command
// when iterating the processor commands using opProcessorCommandIterAll
//
static OP_COMMAND_FN(printCommand) {
    opPrintf("Command %s\n", opObjectHierName(command));
}

//
// Main
//
int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd (argv[0], OP_AC_ALL, argc, argv);

    optModuleP mr = opRootModuleNew(0, 0, 0);
    optModuleP mi = opModuleNew(mr, "module", "u1", 0, 0);

    opRootModulePreSimulate(mr);

    // get processor, assumes only a single processor
    optProcessorP processor = opProcessorNext(mi, NULL);

    // Run the processor for 100 instructions
    opProcessorSimulate(processor, 100);

    // Call a command that had been created in a processor model
    // Pointer to the call command result string. This could be any string
    const char *result;

    opPrintf("\nCall Model Commands\n\n");

    // This shows how to call a command using its full name, starting at the root
    // (note that the platfrom root 'mr' is passed).
    // opCommandStringCall() returns NULL if the command failed or the string returned by the command.

    // set up the arguments
    const char *cmd0Argv[] = {"mipsDebugFlags",  "-help"};
    Uns32 cmd0Argc = sizeof(cmd0Argv)/sizeof(const char *);
    result = opCommandStringCall(mr, "u1/cpu1/mipsDebugFlags", cmd0Argc, cmd0Argv);
    opPrintf("\nopCommandStringCall result '%s'\n\n", result);

    // Setup command for reading MIPS COP0 registers
    const char* cmdToExecute = "u1/cpu1/mipsCOP0";
    optCommandP cmd = opObjectByName(mr, cmdToExecute, OP_COMMAND_EN).Command;
    if(!cmd)
        opMessage("F", "harness", "Command '%s' not found", cmdToExecute);

    // Setup calling arguments to read COP0 'Config' register
    const char *cmd1Argv[] = {"mipsCOP0", "-register", "16", "-select", "0"};
    Uns32 cmd1Argc = sizeof(cmd1Argv)/sizeof(const char *);

    result = opCommandCall( cmd, cmd1Argc, cmd1Argv);

    opPrintf("\nCall Command result '%s'\n", result);

    // Setup calling arguments to read COP0 'PrId' register
    const char *cmd2Argv[] = {"mipsCOP0", "-register", "15", "-select", "0"};
    Uns32 cmd2Argc = sizeof(cmd2Argv)/sizeof(const char *);

    result = opCommandCall( cmd, cmd2Argc, cmd2Argv);

    opPrintf("\nCall Command result '%s'\n", result);

    opPrintf("\nDiscover installed commands\n");

    // iterates over all commands on all processor instances
    opModuleCommandsShow(mi);

    const char *procName = "cpu1";
    opPrintf("Commands for %s\n", procName);
    optProcessorP proc = opObjectByName(mi, procName, OP_PROCESSOR_EN).Processor;

    // iterates over all commands on this processor instance
    opProcessorCommandIterAll(proc, printCommand, 0);

    opPrintf("\nComplete Simulation\n\n");

    // run simulation to completion
    opRootModuleSimulate(mr);

    // In this case the wrong root is passed to opCommandStringCall.
    // The correct
    opPrintf("\nNow trying to call a command giving the wrong root:\n\n");
    result = opCommandStringCall(mi, "u1/cpu1/mipsDebugFlags", cmd0Argc, cmd0Argv);
    opPrintf("\nopCommandStringCall returned '%s'\n\n", result);

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

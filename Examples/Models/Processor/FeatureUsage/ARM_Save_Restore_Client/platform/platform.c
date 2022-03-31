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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define PLATFORM_NAME "platform"

//
// Program arguments definitions
//
struct optionsS {
    const char*  saveRestoreFile;
    Bool         dosave;
    Bool         dorestore;
    Int32        icount;
} options = {
    .icount = -1
};


//
// Simulation main loop
//
static Bool simulate(optProcessorP processor, Uns64 instructions) {

    optStopReason stopReason = opProcessorSimulate(processor, instructions);

    switch(stopReason) {

       case OP_SR_SCHED:
           // hit the scheduler limit
           return True;

       case OP_SR_EXIT:
           // processor has exited
           return False;

       case OP_SR_FINISH:
           // simulation must end
           return False;

       default:
           opPrintf("unexpected stopReason %s\n", opStopReasonString(stopReason));
           return False;
    }
}

//
// Callback function for default state save to file
//
static OP_SAVE_FN(saveFileCB) {

    FILE       *file = userData;
    const Uns8 *src  = data;

    if(bytes) {

        Int32 i;

        // save numeric value as hexadecimal string
        for(i=bytes-1; i>=0; i--) {
            fprintf(file, "%02x", src[i]);
        }

        // emit newline
        fprintf(file, "\n");

    } else {

        // emit next character of string or string terminator
        if(*src) {
            fprintf(file, "%c", *src);
        } else {
            fprintf(file, "\n");
        }
    }

    return True;
}

//
// Callback function for default state restore from file
//
static OP_RESTORE_FN(restoreFileCB) {

    FILE *file = userData;
    Uns8 *dst  = data;

    if(bytes) {

        Int32 i;

        // restore numeric value previously saved as hexadecimal string
        for(i=bytes-1; i>=0; i--) {
            Uns32 ch;
            fscanf(file, "%02x", &ch);
            dst[i] = ch;
        }

        // absorb newline
        fscanf(file, "\n");

    } else {

        // get next character of string
        fscanf(file, "%c", dst);

        // handle string terminator
        if(*dst=='\n') {
            *dst = 0;
        }
    }

    return True;
}

//
// Main simulation routine
//
int main(int argc, char ** argv) {

    // initialize CpuManager
    opSessionInit(OP_VERSION);

    // Command line parser
    optCmdParserP parser = opCmdParserNew(PLATFORM_NAME, OP_AC_ALL);

    opCmdParserAdd(     parser, "dosave"     , 0 , 0, 0 , OP_FT_BOOLVAL   ,  &options.dosave,         "Perform a processor state save fater executing",      OP_AC_ALL, 0, 0);
    opCmdParserAdd(     parser, "dorestore"  , 0 , 0, 0 , OP_FT_BOOLVAL   ,  &options.dorestore,      "Perform a processor state restore before executing",  OP_AC_ALL, 0, 0);
    opCmdParserAdd(     parser, "icount"     , 0 , 0, 0 , OP_FT_INT32VAL  , &options.icount,          "Set the count of instructions to execute",            OP_AC_ALL, 0, 0);
    opCmdParserAdd(     parser, "srfile"     , 0 , 0, 0 , OP_FT_STRINGVAL , &options.saveRestoreFile, "The file for save/restore data",                      OP_AC_ALL, 0, 0);

    opCmdParseArgs(parser, (Uns32)argc, (const char **)argv);

    // Check program has been specified
    if(!opCmdArgUsed(parser, "program")){
        opMessage("E", PLATFORM_NAME"_PE", "Please ensure that -program <Application ELF> is specified");
        return 1;
    }

    optParamP paramsSim = NULL;
    paramsSim = opParamBoolSet(paramsSim, OP_FP_STOPONCONTROLC, True);

    optModuleP  mr = opRootModuleNew (NULL, PLATFORM_NAME, paramsSim);

    // create bus
    optBusP bus = opBusNew(mr, "bus", 32, 0, 0);


    // create physical memory
    // create and connect physical memory
    optMemoryP mem = opMemoryNew(
            mr,
            "memory",
            OP_PRIV_RWX,
            0xffffffffULL,
            OP_CONNECTIONS(
                OP_BUS_CONNECTIONS(
                    OP_BUS_CONNECT(bus, "sp1", .slave=1, .addrLo=0x000000000, .addrHi=0xffffffff)
                )
            ),
            0
            );


    // set up processor instance parameters
    optParamP paramsCpu = NULL;
    paramsCpu = opParamEndianSet(paramsCpu, OP_FP_ENDIAN, OP_ENDIAN_LITTLE);
    paramsCpu = opParamEnumSet(paramsCpu, "variant", "Cortex-A9UP");
    paramsCpu = opParamBoolSet(paramsCpu, OP_FP_SIMULATEEXCEPTIONS, True);
    paramsCpu = opParamBoolSet(paramsCpu, OP_FP_TRACE,              True);
    paramsCpu = opParamBoolSet(paramsCpu, OP_FP_TRACECHANGE,        True);
    paramsCpu = opParamBoolSet(paramsCpu, OP_FP_TRACESHOWICOUNT,    True);

    // create a processor and connect to bus
    const char *model    =
        opVLNVString(NULL, "arm.ovpworld.org", "processor",    "arm",         "1.0", OP_PROCESSOR, OP_VLNV_FATAL);

    optProcessorP cpu_c = opProcessorNew(
        mr,
        model,
        "cpu1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus, "INSTRUCTION"),
                OP_BUS_CONNECT(bus, "DATA")
            )
        ),
        paramsCpu
    );

    // Add the extension library to detect exit()
    const char *extension =
        opVLNVString(NULL, "ovpworld.org",     "modelSupport", "imperasExit", "1.0", OP_EXTENSION, OP_VLNV_FATAL);

    opProcessorExtensionNew(cpu_c, extension, "imperasExit", 0);

    opPrintf("\nPLATFORM INITIALIZED\n\n");

    // indicate that construction is complete
    opRootModulePreSimulate(mr);

    // restore from saved state if required
    if(options.dorestore) {
        FILE *file = fopen(options.saveRestoreFile, "r");
        opPrintf("Restore state file %s...\n", options.saveRestoreFile);
        opMemoryStateRestore(mem, restoreFileCB, file);
        opProcessorStateRestore(cpu_c, restoreFileCB, file);
        fclose(file);
    }

    // run processor
    simulate(cpu_c, options.icount);

    // save state if required
    if(options.dosave) {
        FILE *file = fopen(options.saveRestoreFile, "w");
        opPrintf("Save state file %s...\n", options.saveRestoreFile);
        opMemoryStateSave(mem, saveFileCB, file);
        opProcessorStateSave(cpu_c, saveFileCB, file);
        fclose(file);
    }

    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // check for errors
}


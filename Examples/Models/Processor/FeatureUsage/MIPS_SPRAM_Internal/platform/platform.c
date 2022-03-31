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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "op/op.h"

// an arbitary limit to terminate infinite loops
#define INSTRUCTION_RUN_LIMIT  80

// Message prefix for this platform
#define PLATFORM_NAME "platform"

//
// Program arguments definitions
//
struct optionsS {
    const char*  variant;
    const char*  vendor;
    const char*  endian;
    Uns32        trace;
    Bool         external;
    const char*  program;
    const char*  spram1;
    const char*  spram2;
} options = {
        0
};
//
// ISPRAM & DSPRAM memory (when externally implemented)
//
#define ISPRAMSIZE 0x4000
#define DSPRAMSIZE 0x4000
static Uns8 ISPRAM[ISPRAMSIZE];
static Uns8 DSPRAM[DSPRAMSIZE];

//
// ISPRAM read callback
//
static OP_BUS_SLAVE_READ_FN(readISPRAM) {

    optProcessorP processor = initiator.Processor;

    assert(addr+bytes < ISPRAMSIZE);

    void *ptr    = &ISPRAM[addr];
    Uns32 result = *(Uns32*)ptr;

    const char *accessType = processor ? "real" : "artifact";
    opPrintf(
        "readISPRAM(%s)  0x%08x %u => 0x%08x\n",
        accessType, (Uns32)addr, bytes, result
    );

    *(Uns32*)data = result;
}

//
// ISPRAM write callback
//
static OP_BUS_SLAVE_WRITE_FN(writeISPRAM) {

    optProcessorP processor = initiator.Processor;

    assert(addr+bytes < ISPRAMSIZE);

    void *ptr    = &ISPRAM[addr];
    Uns32 result = *(Uns32*)data;

    const char *accessType = processor ? "real" : "artifact";
    opPrintf(
        "writeISPRAM(%s) 0x%08x %u <= 0x%08x\n",
        accessType, (Uns32)addr, bytes, result
    );

    *(Uns32*)ptr = result;
}

//
// DSPRAM read callback
//
static OP_BUS_SLAVE_READ_FN(readDSPRAM) {

    optProcessorP processor = initiator.Processor;

    assert(addr+bytes < DSPRAMSIZE);

    void *ptr    = &DSPRAM[addr];
    Uns32 result = *(Uns32*)ptr;

    const char *accessType = processor ? "real" : "artifact";
    opPrintf(
        "readDSPRAM(%s)  0x%08x %u => 0x%08x\n",
        accessType, (Uns32)addr, bytes, result
    );

    *(Uns32*)data = result;
}

//
// DSPRAM write callback
//
static OP_BUS_SLAVE_WRITE_FN(writeDSPRAM) {

    optProcessorP processor = initiator.Processor;

    assert(addr+bytes < DSPRAMSIZE);

    void *ptr    = &DSPRAM[addr];
    Uns32 result = *(Uns32*)data;

    const char *accessType = processor ? "real" : "artifact";

    opPrintf(
        "writeDSPRAM(%s) 0x%08x %u <= 0x%08x\n",
        accessType, (Uns32)addr, bytes, result
    );

    *(Uns32*)ptr = result;
}

//
// Scheduler loop
//
static Bool simulate(optProcessorP processor, Uns64 instructions) {

    switch(opProcessorSimulate(processor, instructions)) {

        case OP_SR_SCHED:
        case OP_SR_HALT:
            return True;

        default:
            // end simulation
            return False;
    }
}

const char *vendors[] = {"mips.com", "mips.ovpworld.org", 0};
#define NUMBER_VENDORS 2

//
// Select vendor to use for models
//
static const char *selectVendor() {
    Uns32 i, index = 0;

    // Select default model vendor to be used to load model
    char *runtime = getenv("IMPERAS_RUNTIME");
    if(!runtime || !strcmp(runtime, "OVPsim") || !strcmp(runtime, "CpuManager")) {
        index++; // start from next vendor
    } else {
        ;        // leave default index
    }
    for(i=0;i<NUMBER_VENDORS;i++){
        const char *mipsModel    = opVLNVString(NULL, vendors[index], "processor", "mips32_r1r5", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
        const char *mipsSemihost = opVLNVString(NULL, vendors[index], "semihosting", "mips32Newlib", "1.0", OP_EXTENSION, OP_VLNV_FATAL);
        if(mipsModel && mipsSemihost) {
            return vendors[index];
        }
        // Select next in list, if zero back to first
        if (!vendors[++index]) index = 0;
    }

    opMessage("F", "MODEL", "No Model Available");
    // Will never reach here
    return NULL;
}

//
// Main simulation routine
//
int main(int argc, char ** argv) {

    Bool trace     = False;
    Bool traceRegs = False;
    Bool bigEndian = False;

    //////////////////////////////////////////////////////////////////////////////
    // Platform Creation Starts here

    // initialize CpuManager
    opSessionInit(OP_VERSION);

    // Command line parser
    optCmdParserP parser = opCmdParserNew(PLATFORM_NAME, OP_AC_ALL);

    opCmdParserAdd(     parser, "external"   , 0 , 0, 0 , OP_FT_BOOLVAL   , &options.external,  "Enable external ITC",                          OP_AC_ALL, 0, 0);
    opCmdParserReplace( parser, "trace"      , 0 , 0, 0 , OP_FT_UNS32VAL  , &options.trace,     "Select level of tracing bit 0:instructions bit 1: registers", OP_AC_ALL, 0, 0);
    opCmdParserReplace( parser, "variant"    , 0 , 0, 0 , OP_FT_STRINGVAL , &options.variant,   "The processor variant to be used",             OP_AC_ALL, 0, 0);
    opCmdParserReplace( parser, "endian"     , 0 , 0, 0 , OP_FT_STRINGVAL , &options.endian,    "The processor endian, set to L or B",          OP_AC_ALL, 0, 0);
    opCmdParserReplace( parser, "program"    , 0 , 0, 0 , OP_FT_STRINGVAL , &options.program,   "The application program to load",              OP_AC_ALL, 0, 0);
    opCmdParserAdd(     parser, "spram1"     , 0 , 0, 0 , OP_FT_STRINGVAL , &options.spram1,    "SPRAM code file 1",                  OP_AC_ALL, 0, 0);
    opCmdParserAdd(     parser, "spram2"     , 0 , 0, 0 , OP_FT_STRINGVAL , &options.spram2,    "SPRAM code file 2",                  OP_AC_ALL, 0, 0);

    if(!opCmdParseArgs(parser, (Uns32)argc, (const char **)argv)) {
        return 1;
    }

    bigEndian = (options.endian[0] == 'B') || (options.endian[0] == 'b');
    opPrintf("\nProcessor %s\n", options.variant);
    if(options.trace) {
        trace     = options.trace & 1;
        traceRegs = options.trace & 2;
        opPrintf("Tracing Instructions %s Registers %s\n",
            trace     ? "ON" : "-",
            traceRegs ? "ON" : "-"
        );
    }

    // Check program and exception vector have been specified
    if(!opCmdArgUsed(parser, "program") || !opCmdArgUsed(parser, "spram1") || !opCmdArgUsed(parser, "spram2")){
        opMessage("E", PLATFORM_NAME"_PE", "Please ensure that arguments -program, -spram1 and -spram2 are all specified");
        return 1;
    }

    optParamP paramsSim = NULL;
    paramsSim = opParamBoolSet(paramsSim, OP_FP_STOPONCONTROLC, True);

    optModuleP  mr = opRootModuleNew (NULL, PLATFORM_NAME, paramsSim);

    // create main bus
    optBusP bus = opBusNew(mr, "bus", 32, 0, 0);

    // create and connect physical memory
    opMemoryNew(
            mr,
            "memory",
            OP_PRIV_RWX,
            0xffffffffULL,
            OP_CONNECTIONS(
                OP_BUS_CONNECTIONS(
                    OP_BUS_CONNECT(bus, "sp1", .slave=1, .addrLo=0x000000000ULL, .addrHi=0xffffffffULL)
                )
            ),
            0
            );

    //
    // Setup the configuration attributes for the processor
    //
    optParamP paramsCpu = NULL;
    if(bigEndian)
        paramsCpu = opParamEndianSet(paramsCpu, OP_FP_ENDIAN, OP_ENDIAN_BIG);
    else
        paramsCpu = opParamEndianSet(paramsCpu, OP_FP_ENDIAN, OP_ENDIAN_LITTLE);
    paramsCpu = opParamEnumSet(paramsCpu, "variant", options.variant);
    paramsCpu = opParamBoolSet(paramsCpu, OP_FP_SIMULATEEXCEPTIONS, True);
    if(trace)
        paramsCpu = opParamBoolSet(paramsCpu, OP_FP_TRACE,              True);
    if (traceRegs)
        paramsCpu = opParamBoolSet(paramsCpu, OP_FP_TRACEREGSAFTER,     True);
    paramsCpu = opParamBoolSet(paramsCpu, OP_FP_TRACESHOWICOUNT,    True);

    // Enable vectored interrupts
    paramsCpu = opParamBoolSet(paramsCpu, "vectoredinterrupt", True);

    // Enable MIPS-format trace
    paramsCpu = opParamBoolSet(paramsCpu, "MIPS_TRACE", True);

    // Enable ISPRAM
    paramsCpu = opParamBoolSet(paramsCpu, "configISP", 1);

    // Enable DSPRAM
    paramsCpu = opParamBoolSet(paramsCpu, "configDSP", 1);

    // Enable SPRAM Debug messages from processor core
    paramsCpu = opParamUns32Set(paramsCpu, "debugflags",    0x10000000);

    // create a processor and connect to bus
    // Select processor model from library
    const char *vendor    = selectVendor();
    const char *model    =
        opVLNVString(NULL, vendor, "processor", "mips32_r1r5", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);

    optProcessorP cpu_c = opProcessorNew(
        mr,
        model,
        "mips32",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus, "INSTRUCTION"),
                OP_BUS_CONNECT(bus, "DATA")
            )
        ),
        paramsCpu
    );


    // create ISPRAM & DSPRAM busses
    optBusP ISPRAMBus = opBusNew(mr, "ISPRAMBus", 32, 0, 0);
    optBusP DSPRAMBus = opBusNew(mr, "DSPRAMBus", 32, 0, 0);

    if(!options.external) {

        opPrintf("****************************\n");
        opPrintf("*      INTERNAL SPRAM      *\n");
        opPrintf("****************************\n");

    } else {

        opPrintf("****************************\n");
        opPrintf("*      EXTERNAL SPRAM      *\n");
        opPrintf("****************************\n");

        // map ISPRAM memory using callbacks
        opBusSlaveNew  (
                ISPRAMBus,
                "ISPRAM_Memory",
                NULL,
                OP_PRIV_RWX,
                0,
                (Uns32)-1,
                readISPRAM,
                writeISPRAM,
                0,
                0
        );

        // map DSPRAM memory using callbacks
        opBusSlaveNew  (
                DSPRAMBus,
                "DSPRAM_Memory",
                NULL,
                OP_PRIV_RWX,
                0,
                (Uns32)-1,
                readDSPRAM,
                writeDSPRAM,
                0,
                0
        );

    }

    // external monitor SPRAM
    opProcessorBusConnect(cpu_c, ISPRAMBus, "ISPRAM");
    opProcessorBusConnect(cpu_c, DSPRAMBus, "DSPRAM");

    // load the processor object files at PHYSICAL address (not into SPRAM)
    if (!opProcessorApplicationLoad(cpu_c, options.program, OP_LDR_SET_START, 0)) {
        opPrintf("Fault loading Programs\n");
        return -1;
    }

    opRootModulePreSimulate(mr);

    // parameters for SPRAM configuration
    Uns32       index;
    Bool        enable;
    Uns32       size;
    Uns64       base;
    Uns32       offset;
    const char *file;
    Uns32       _unused;

    // configure ISPRAM region 0 (initially enabled, address 0x22000)
    index   = 0;              opProcessorRegWriteByName(cpu_c, "ISPRAM_INDEX",  &index);
    enable  = True;           opProcessorRegWriteByName(cpu_c, "ISPRAM_ENABLE", &enable);
    size    = 1;              opProcessorRegWriteByName(cpu_c, "ISPRAM_SIZE",   &size);
    base    = 0x22000;        opProcessorRegWriteByName(cpu_c, "ISPRAM_BASE",   &base);
    offset  = 0;              opProcessorRegWriteByName(cpu_c, "ISPRAM_OFFSET", &offset);
    file    = options.spram1; opProcessorRegWriteByName(cpu_c, "ISPRAM_FILE",   &file);
    _unused = 0;              opProcessorRegWriteByName(cpu_c, "ISPRAM_WRITE",  &_unused);

    // configure ISPRAM region 1
    index   = 1;              opProcessorRegWriteByName(cpu_c, "ISPRAM_INDEX",  &index);
    enable  = False;          opProcessorRegWriteByName(cpu_c, "ISPRAM_ENABLE", &enable);
    size    = 1;              opProcessorRegWriteByName(cpu_c, "ISPRAM_SIZE",   &size);
    base    = 0;              opProcessorRegWriteByName(cpu_c, "ISPRAM_BASE",   &base);
    offset  = 1<<12;          opProcessorRegWriteByName(cpu_c, "ISPRAM_OFFSET", &offset);
    file    = options.spram2; opProcessorRegWriteByName(cpu_c, "ISPRAM_FILE",   &file);
    _unused = 0;              opProcessorRegWriteByName(cpu_c, "ISPRAM_WRITE",  &_unused);

    // configure DSPRAM region 0
    index   = 0;              opProcessorRegWriteByName(cpu_c, "DSPRAM_INDEX",  &index);
    enable  = False;          opProcessorRegWriteByName(cpu_c, "DSPRAM_ENABLE", &enable);
    size    = 2;              opProcessorRegWriteByName(cpu_c, "DSPRAM_SIZE",   &size);
    base    = 0;              opProcessorRegWriteByName(cpu_c, "DSPRAM_BASE",   &base);
    offset  = 0;              opProcessorRegWriteByName(cpu_c, "DSPRAM_OFFSET", &offset);
    _unused = 0;              opProcessorRegWriteByName(cpu_c, "DSPRAM_WRITE",  &_unused);

    // configure DSPRAM region 1
    index   = 1;              opProcessorRegWriteByName(cpu_c, "DSPRAM_INDEX",  &index);
    enable  = False;          opProcessorRegWriteByName(cpu_c, "DSPRAM_ENABLE", &enable);
    size    = 2;              opProcessorRegWriteByName(cpu_c, "DSPRAM_SIZE",   &size);
    base    = 0;              opProcessorRegWriteByName(cpu_c, "DSPRAM_BASE",   &base);
    offset  = 2<<12;          opProcessorRegWriteByName(cpu_c, "DSPRAM_OFFSET", &offset);
    _unused = 0;              opProcessorRegWriteByName(cpu_c, "DSPRAM_WRITE",  &_unused);

    ////////////////////////////////////////////////////////////////////////////
    // DO A SIMULATION RUN
    ////////////////////////////////////////////////////////////////////////////

    simulate(cpu_c, INSTRUCTION_RUN_LIMIT);

    // show final configuration of all ISPRAM regions
    for(index=0; index<2; index++) {

        // select ISPRAM region
        opProcessorRegWriteByName(cpu_c, "ISPRAM_INDEX", &index);
        opProcessorRegWriteByName(cpu_c, "ISPRAM_READ",  &_unused);

        // get final configuration of ISPRAM region
        opProcessorRegReadByName(cpu_c, "ISPRAM_INDEX",  &index);
        opProcessorRegReadByName(cpu_c, "ISPRAM_ENABLE", &enable);
        opProcessorRegReadByName(cpu_c, "ISPRAM_SIZE",   &size);
        opProcessorRegReadByName(cpu_c, "ISPRAM_BASE",   &base);
        opProcessorRegReadByName(cpu_c, "ISPRAM_OFFSET", &offset);

        // show final configuration of ISPRAM region
        opPrintf(
            "ISPRAM region %u base=0x%08x size=%u SPRAM_offset=0x%08x enable=%u\n",
            index, (Uns32)base, size, offset, enable
        );
    }

    // show final configuration of all DSPRAM regions
    for(index=0; index<2; index++) {

        // select DSPRAM region
        opProcessorRegWriteByName(cpu_c, "DSPRAM_INDEX", &index);
        opProcessorRegWriteByName(cpu_c, "DSPRAM_READ",  &_unused);

        // get final configuration of ISPRAM region
        opProcessorRegReadByName(cpu_c, "DSPRAM_INDEX",  &index);
        opProcessorRegReadByName(cpu_c, "DSPRAM_ENABLE", &enable);
        opProcessorRegReadByName(cpu_c, "DSPRAM_SIZE",   &size);
        opProcessorRegReadByName(cpu_c, "DSPRAM_BASE",   &base);
        opProcessorRegReadByName(cpu_c, "DSPRAM_OFFSET", &offset);

        // show final configuration of ISPRAM region
        opPrintf(
            "DSPRAM region %u base=0x%08x size=%u SPRAM_offset=0x%08x enable=%u\n",
            index, (Uns32)base, size, offset, enable
        );
    }

    ////////////////////////////////////////////////////////////////////////////
    // DIRECTLY EXAMINE DSPRAM and ISPRAM MEMORY
    ////////////////////////////////////////////////////////////////////////////

    opPrintf("DSPRAM and ISPRAM direct bus access\n");

    for(index=0; index<16; index+=4) {
        Uns32 buffer;
        opBusRead(DSPRAMBus, NULL, index, &buffer, sizeof(buffer), 1);
        opPrintf("DSPRAM(%d) = 0x%08x\n", index, buffer);
    }
    for(index=0; index<16; index+=4) {
        Uns32 buffer;
        opBusRead(ISPRAMBus, NULL, index, &buffer, sizeof(buffer), 1);
        opPrintf("ISPRAM(%d) = 0x%08x\n", index, buffer);
    }

    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // check for errors
}

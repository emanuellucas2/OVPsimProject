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

#include "op/op.h"

// an arbitrary limit to terminate infinite loops
#define INSTRUCTION_RUN_LIMIT  500

// Message prefix for this platform
#define PLATFORM_NAME "platform"

// Message prefix for this module
#define CPU_PREFIX "MIPS32_ITC"


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
    const char*  exception;
} options = {
        0
};

// return processor name
#define GET_NAME(_P) opObjectName(_P)


////////////////////////////////////////////////////////////////////////////////
// EXTERNALLY-IMPLEMENTED ITC
////////////////////////////////////////////////////////////////////////////////

//
// static root description
//
optProcessorP root;

//
// implementation configuration limits
//
#define MIPS_ITC_MAX_FIFOS       16
#define MIPS_ITC_MAX_SEPAPHORES  16
#define MIPS_ITC_FIFO_DEPTH_LOG2 2
#define MIPS_ITC_FIFO_DEPTH      (1<<MIPS_ITC_FIFO_DEPTH_LOG2)
#define MIPS_ITC_SEMAPHORE_SAT   0xffff
#define MIPS_ITC_NUM_FIFO        8

//
// default views
//
typedef enum mipsITCViewE {
    ITCV_Bypass          = 0x0,
    ITCV_Control         = 0x1,
    ITCV_EF_Synchronized = 0x2,
    ITCV_EF_Try          = 0x3,
    ITCV_PV_Synchronized = 0x4,
    ITCV_PV_Try          = 0x5,
    ITCV_Last
} mipsITCView;

//
// default ITCAddressMap1 register definition
//
typedef struct mipsITCAddressMap1S {
    Uns32 EntryGrain :  3;
    Uns32 _u1        :  7;
    Uns32 AddrMask   :  7;
    Uns32 _u2        :  3;
    Uns32 NumEntries : 11;
    Uns32 M          :  1;
} mipsITCAddressMap1;

//
// default storage cell tag format
//
typedef struct mipsITCCellTagS {
    Uns32 E          :  1;
    Uns32 F          :  1;
    Uns32 _u1        : 14;
    Uns32 T          :  1;
    Uns32 FIFO       :  1;
    Uns32 FIFOPtr    :  3;
    Uns32 _u2        :  7;
    Uns32 FIFODepth  :  4;
} mipsITCCellTag;

//
// default storage cell
//
typedef struct mipsITCCellS {
    mipsITCCellTag tag;
    Bool           hasBlocked;
    Uns32          value[MIPS_ITC_FIFO_DEPTH];
} mipsITCCell, *mipsITCCellP;

//
// Type used to hold default ITC details
//
typedef struct mipsITCInfoS {
    mipsITCAddressMap1 addressMap1;
    mipsITCCell        cells[MIPS_ITC_MAX_FIFOS+MIPS_ITC_MAX_SEPAPHORES];
} mipsITCInfo, *mipsITCInfoP;

//
// static ITC block description
//
static mipsITCInfo ITCStatics;

//
// Emit current cell state
//
static void debugCell(mipsITCCellP cell) {

    // debug tag
    opMessage(
        "I", CPU_PREFIX,
        "    TAG: {E:%u F:%u T:%u FIFO:%u FIFOPtr:%u FIFODepth:%u}",
        cell->tag.E,
        cell->tag.F,
        cell->tag.T,
        cell->tag.FIFO,
        cell->tag.FIFOPtr,
        cell->tag.FIFODepth
    );

    if(cell->tag.FIFO) {

        // FIFO cell
        Uns32 i;

        // print all values in the FIFO
        for(i=0; i<cell->tag.FIFOPtr; i++) {
            opMessage(
                "I", CPU_PREFIX, "    VALUE[%u]: 0x%08x",
                i, cell->value[i]
            );
        }

    } else {

        // print the single semaphore value
        opMessage("I", CPU_PREFIX, "    VALUE: 0x%08x", cell->value[0]);
    }
}

//
// Emit debug for any cell access
//
static void debugAccess(
    optProcessorP tc,
    Uns32         cellIndex,
    mipsITCView   view,
    Uns32         result,
    Bool          isRead
) {
    // list of view names
    static const char *viewNames[] = {
        [ITCV_Bypass]          = "Bypass",
        [ITCV_Control]         = "Control",
        [ITCV_EF_Synchronized] = "E/F Synchronized",
        [ITCV_EF_Try]          = "E/F Try",
        [ITCV_PV_Synchronized] = "P/V Synchronized",
        [ITCV_PV_Try]          = "P/V Try"
    };

    // describe the transaction
    opMessage(
        "I", CPU_PREFIX,
        "%s %s cell %u %s view %s %08x",
        GET_NAME(tc),
        isRead ? "read" : "write",
        cellIndex,
        viewNames[view],
        isRead ? "<=" : "=>",
        result
    );
}

//
// Return spacing between ITC cells
//
inline static Uns32 getCellSpacing(void) {
    return 128*(1<<ITCStatics.addressMap1.EntryGrain);
}

//
// Return cell index implied by ITC address
//
inline static Uns32 getCellIndex(Uns32 address) {
    return address/getCellSpacing();
}

//
// Return view implied by ITC address
//
inline static mipsITCView getView(Uns32 address) {
    return (address>>3) & 0xf;
}

//
// Return the index of the oldest entry in the passed cell
//
inline static Uns32 getOldestIndex(mipsITCCellP cell) {
    return cell->tag.FIFOPtr ? cell->tag.FIFOPtr-1 : 0;
}

//
// Return the index of the newest entry in the passed cell
//
inline static Uns32 getNewestIndex(mipsITCCellP cell) {
    return 0;
}

//
// Is the value the minimum semaphore value?
//
inline static Bool isSemaphoreMin(Uns32 value) {
    return (value & MIPS_ITC_SEMAPHORE_SAT) == 0;
}

//
// Is the value the maximum semaphore value?
//
inline static Bool isSemaphoreMax(Uns32 value) {
    return (value & MIPS_ITC_SEMAPHORE_SAT) == MIPS_ITC_SEMAPHORE_SAT;
}

//
// Take gated exception trap when T bit is set
//
static void takeGatedExceptionTrap(optProcessorP tc) {
    Uns32 dummy = 0;
    opProcessorRegWriteByName(tc, "ITCGatedException", &dummy);
}

//
// If in an SC instruction, indicate failure
//
inline static void signalSCFail(optProcessorP tc) {
    Uns32 dummy = 0;
    opProcessorRegWriteByName(tc, "ITCSignalSCFail", &dummy);
}

//
// Perform actions when blocking on a gating storage access
//
static void blockTCGS(optProcessorP tc) {
    Uns32 dummy = 0;
    opProcessorRegWriteByName(tc, "ITCBlock", &dummy);
}

//
// Restart a TC if it is blocked reading or writing gating storage
//
static OP_PROCESSOR_ITERATOR_FN(unblockTCGS) {
    Uns32 dummy = 0;
    opProcessorRegWriteByName(processor, "ITCUnblock", &dummy);
}

//
// Perform actions when reading from an empty cell or writing to a full one
//
inline static void blockTCOnCell(optProcessorP tc, mipsITCCellP cell) {

    // indicate that the cell has TCs blocked on it
    cell->hasBlocked = True;

    // either halt the TC or take an exception
    blockTCGS(tc);
}

//
// Restart any siblings of the passed TC that are blocked waiting on the cell
//
static void restartTCOnCell(mipsITCCellP cell) {

    if(cell->hasBlocked) {

        opProcessorIterAll(root, unblockTCGS, 0);

        cell->hasBlocked = False;
    }
}

//
// Return bypass read for the passed cell
//
inline static Uns32 readCellBypass(mipsITCCellP cell) {

    return cell->value[getOldestIndex(cell)];
}

//
// Set bypass value for the passed cell
//
static void writeCellBypass(mipsITCCellP cell, Uns32 value) {

    cell->value[getNewestIndex(cell)] = value;

    // restart any TCs blocked waiting for this cell
    restartTCOnCell(cell);

    // emit debug if required
    debugCell(cell);
}

//
// Return tag for the passed cell
//
static Uns32 readCellTag(mipsITCCellP cell) {

    union {mipsITCCellTag tag; Uns32 u32;} u = {cell->tag};

    if(!u.tag.FIFO) {
        u.tag.FIFOPtr = 0;
    }

    return u.u32;
}

//
// Set tag for the passed cell
//
static void writeCellTag(mipsITCCellP cell, Uns32 value) {

    union {Uns32 u32; mipsITCCellTag tag;} u = {value};

    // update writable bits
    cell->tag.E = u.tag.E;
    cell->tag.F = u.tag.F;
    cell->tag.T = u.tag.T;

    // also clear FIFOPtr if E bit is set
    if(u.tag.E) {
        cell->tag.FIFOPtr = 0;
    }

    // restart any TCs blocked waiting for this cell
    restartTCOnCell(cell);

    // emit debug if required
    debugCell(cell);
}

//
// Read value from the passed cell using E/F view
//
static Uns32 readEFCellValue(mipsITCCellP cell) {

    Uns32 result;

    if(cell->tag.E) {

        result = 0;

    } else {

        // restart any TCs blocked waiting for this cell
        if(cell->tag.F) {
            restartTCOnCell(cell);
            cell->tag.F = 0;
        }

        // update cell state
        result = cell->value[--cell->tag.FIFOPtr];
        cell->tag.E = !cell->tag.FIFOPtr;

        // emit debug if required
        debugCell(cell);
    }

    return result;
}

//
// Write value to the passed cell using E/F view
//
static void writeEFCellValue(optProcessorP tc, mipsITCCellP cell, Uns32 value) {

    Uns32 entries = (1<<cell->tag.FIFODepth);

    if(cell->tag.F) {

        // indicate failure if this is an SC instruction
        signalSCFail(tc);

    } else if(cell->tag.FIFOPtr<entries) {

        Int32 i;

        // restart any TCs blocked waiting for this cell
        if(cell->tag.E) {
            restartTCOnCell(cell);
            cell->tag.E = 0;
        }

        // shift up current entries
        for(i=cell->tag.FIFOPtr; i>0; i--) {
            cell->value[i] = cell->value[i-1];
        }

        // update cell state
        cell->value[0] = value;
        cell->tag.F = (++cell->tag.FIFOPtr==entries);

        // emit debug if required
        debugCell(cell);
    }
}

//
// Read value from the passed cell using P/V view
//
static Uns32 readPVCellValue(mipsITCCellP cell) {

    Uns32 result;

    if(isSemaphoreMin(cell->value[0])) {

        result = 0;

    } else {

        // restart any TCs blocked waiting for this cell
        if(isSemaphoreMax(cell->value[0])) {
            restartTCOnCell(cell);
        }

        // update cell state
        result = cell->value[0]--;

        // emit debug if required
        debugCell(cell);
    }

    return result;
}

//
// Write value to the passed cell using P/V view
//
static void writePVCellValue(optProcessorP tc, mipsITCCellP cell, Uns32 value) {

    if(isSemaphoreMax(cell->value[0])) {

        // indicate failure if this is an SC instruction
        signalSCFail(tc);

    } else {

        // restart any TCs blocked waiting for this cell
        if(isSemaphoreMin(cell->value[0])) {
            restartTCOnCell(cell);
        }

        // update cell state
        cell->value[0]++;

        // emit debug if required
        debugCell(cell);
    }
}

//
// Validate parameters for access to an ITC cell
//
static Bool validateITC(
    Uns32       cellIndex,
    Uns32       view,
    Uns32       bytes,
    const char *access
) {
    Uns32 numCells = ITCStatics.addressMap1.NumEntries;

    if(bytes!=4) {

        // illegal access size
        opMessage(
            "W", CPU_PREFIX"_BSZ",
            "ITC %u-byte %s access ignored",
            bytes,
            access
        );
        return False;

    } else if(cellIndex>=numCells) {

        // illegal cell index
        opMessage(
            "W", CPU_PREFIX"_BCI",
            "ITC cell index %u exceeds maximum %u - %s ignored",
            cellIndex,
            numCells-1,
            access
        );
        return False;

    } else if(view>=ITCV_Last) {

        // illegal cell index
        opMessage(
            "W", CPU_PREFIX"_BCI",
            "ITC view %u exceeds maximum %u - %s ignored",
            view,
            ITCV_Last-1,
            access
        );
        return False;

    } else {

        return True;
    }
}

//
// ITC read callback
//
static OP_BUS_SLAVE_READ_FN(readITC) {

    optProcessorP processor = initiator.Processor;

    // refresh ITCAddressMap1
    opProcessorRegReadByName(processor, "ITCAddressMap1", &ITCStatics.addressMap1);

    optProcessorP tc        = processor;
    Uns32         cellIndex = getCellIndex(addr);
    mipsITCView   view      = getView(addr);

    if(validateITC(cellIndex, view, bytes, "read")) {

        mipsITCCellP cell   = &ITCStatics.cells[cellIndex];
        Uns32        result = 0;

        // take action based on view
        switch(view) {

            case ITCV_Bypass:
                result = readCellBypass(cell);
                break;

            case ITCV_Control:
                result = readCellTag(cell);
                break;

            case ITCV_EF_Synchronized:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else if(!cell->tag.E) {
                    result = readEFCellValue(cell);
                } else {
                    blockTCOnCell(tc, cell);
                }
                break;

            case ITCV_EF_Try:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else {
                    result = readEFCellValue(cell);
                }
                break;

            case ITCV_PV_Synchronized:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else if(!isSemaphoreMin(cell->value[0])) {
                    result = readPVCellValue(cell);
                } else {
                    blockTCOnCell(tc, cell);
                }
                break;

            case ITCV_PV_Try:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else {
                    result = readPVCellValue(cell);
                }
                break;

            default:
                break;
        }

        // emit debug if required
        debugAccess(tc, cellIndex, view, result, True);

        // return result
        *(Uns32*)data = result;

    } else {

        // return zero result
        memset(data, 0, bytes);
    }
}

//
// ITC write callback
//
static OP_BUS_SLAVE_WRITE_FN(writeITC) {

    optProcessorP processor = initiator.Processor;

    // refresh ITCAddressMap1
    opProcessorRegReadByName(processor, "ITCAddressMap1", &ITCStatics.addressMap1);

    optProcessorP tc        = processor;
    Uns32         cellIndex = getCellIndex(addr);
    mipsITCView   view      = getView(addr);

    if(validateITC(cellIndex, view, bytes, "write")) {

        mipsITCCellP cell   = &ITCStatics.cells[cellIndex];
        Uns32        result = *(Uns32*)data;

        // emit debug if required
        debugAccess(tc, cellIndex, view, result, False);

        // take action based on view
        switch(view) {

            case ITCV_Bypass:
                writeCellBypass(cell, result);
                break;

            case ITCV_Control:
                writeCellTag(cell, result);
                break;

            case ITCV_EF_Synchronized:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else if(!cell->tag.F) {
                    writeEFCellValue(tc, cell, result);
                } else {
                    blockTCOnCell(tc, cell);
                }
                break;

            case ITCV_EF_Try:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else {
                    writeEFCellValue(tc, cell, result);
                }
                break;

            case ITCV_PV_Synchronized:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else if(!isSemaphoreMax(cell->value[0])) {
                    writePVCellValue(tc, cell, result);
                } else {
                    blockTCOnCell(tc, cell);
                }
                break;

            case ITCV_PV_Try:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else {
                    writePVCellValue(tc, cell, result);
                }
                break;

            default:
                break;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
// COMMON CODE
////////////////////////////////////////////////////////////////////////////////

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
    opCmdParserAdd(     parser, "exception"  , 0 , 0, 0 , OP_FT_STRINGVAL , &options.exception, "The vector table exception program to load",   OP_AC_ALL, 0, 0);

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
    if(!opCmdArgUsed(parser, "program") || !opCmdArgUsed(parser, "exception")){
        opMessage("E", PLATFORM_NAME"_PE", "Please ensure that -program <Application ELF> and -exception <Exception Vector ELF> are specified");
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
    // Setup the configuration attributes for the simulator
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

    // Enable ITC with 8 FIFO entries and 4 semaphore entries
    paramsCpu = opParamUns32Set(paramsCpu, "ITCNumEntries", 12);
    paramsCpu = opParamUns32Set(paramsCpu, "ITCNumFIFO",    8);

    // Enable ITC Debug messages from processor core
    paramsCpu = opParamUns32Set(paramsCpu, "debugflags",    0x20000000);

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


    if(!options.external) {

        opPrintf("****************************\n");
        opPrintf("*       INTERNAL ITC       *\n");
        opPrintf("****************************\n");

    } else {

        opPrintf("****************************\n");
        opPrintf("*       EXTERNAL ITC       *\n");
        opPrintf("****************************\n");

        // create ITC bus
        optBusP ITCBus = opBusNew(mr, "ITCBus", 32, 0, 0);

        // map ITC memory using callbacks
        opBusSlaveNew  (
                ITCBus,
                "ITC_Memory",
                NULL,
                OP_PRIV_RWX,
                0,
                (Uns32)-1,
                readITC,
                writeITC,
                0,
                0
        );

        // connect ITC bus
        opProcessorBusConnect(cpu_c, ITCBus, "ITC");

        Uns32 i;

        // save root processor
        root = cpu_c;

        // initialize FIFO cells
        for(i=0; i<MIPS_ITC_NUM_FIFO; i++) {
            ITCStatics.cells[i].tag.E         = 1;
            ITCStatics.cells[i].tag.FIFODepth = MIPS_ITC_FIFO_DEPTH_LOG2;
            ITCStatics.cells[i].tag.FIFO      = 1;
        }
    }

    Uns32 ITCAddressMap0;
    Uns32 ITCAddressMap1;
    Uns32 index;

    // load the processor object files
    if(opProcessorApplicationLoad(cpu_c, options.program, OP_LDR_SET_START, 0) &&
       opProcessorApplicationLoad(cpu_c, options.exception, OP_LDR_DEFAULT, 0)) {
    } else {
        opPrintf("Fault loading Programs\n");
        return -1;
    }

    ////////////////////////////////////////////////////////////////////////////
    // DO A SIMULATION RUN
    ////////////////////////////////////////////////////////////////////////////

    for(index=0; index<INSTRUCTION_RUN_LIMIT; index++) {
        simulate(cpu_c, 1);
    }

    // show final configuration of ITC
    opProcessorRegReadByName(cpu_c, "ITCAddressMap0", &ITCAddressMap0);
    opProcessorRegReadByName(cpu_c, "ITCAddressMap1", &ITCAddressMap1);

    opPrintf(
        "ITCAddressMap0=0x%08x ITCAddressMap1=0x%08x\n",
        ITCAddressMap0, ITCAddressMap1
    );

    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // check for errors
}

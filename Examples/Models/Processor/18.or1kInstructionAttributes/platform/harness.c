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

// standard includes
#include <stdio.h>

// Imperas host API types
#include "hostapi/simAddrTypes.h"

// OP interface includes
#include "op/op.h"

// Imperas common library includes
#include "ocl/oclia.h"

//
// Name for root and root module
//
#define MODULE_NAME "platform"


////////////////////////////////////////////////////////////////////////////////
// WALK ADDRESS EXPRESSION
////////////////////////////////////////////////////////////////////////////////

//
// Print address expression
//
static void printAddrExp(octiaAddrExpP exp, octiaAttrP attrs) {

    if(exp->type==OCL_ET_UNKNOWN) {

        opPrintf("UNKNOWN");

    } else if(exp->type==OCL_ET_CONST) {

        opPrintf("0x"FMT_Ax, exp->c);

    } else if(exp->type==OCL_ET_REG) {

        optRegP reg = opRegConvert(exp->r);

        if(reg) {
            opPrintf("%s", opRegName(reg));
        } else {
            opPrintf("UNKNOWN_REGISTER");
        }

    } else if(exp->type==OCL_ET_EXTEND) {

        opPrintf(
            "(%cext-%u-to-%u ",
            exp->e.signExtend?'s':'z',
            exp->e.child->bits,
            exp->bits
        );
        printAddrExp(exp->e.child, 0);
        opPrintf(")");

    } else if(exp->type==OCL_ET_UNARY) {

        opPrintf("(%s ", exp->u.opName);
        printAddrExp(exp->u.child, 0);
        opPrintf(")");

    } else if(exp->type==OCL_ET_BINARY) {

        opPrintf("(%s ", exp->b.opName);
        printAddrExp(exp->b.child[0], 0);
        opPrintf(", ");
        printAddrExp(exp->b.child[1], 0);
        opPrintf(")");

    } else if(exp->type==OCL_ET_LOAD) {

        opPrintf("[");
        printAddrExp(exp->l.child, 0);
        opPrintf("]");

    } else {

        opPrintf("{unexpected expression type %u}", exp->type);
    }

    // print evaluated expression unless it is a constant
    if(attrs && (exp->type!=OCL_ET_CONST)) {

        Uns32 bytes = BITS_TO_BYTES(exp->bits);
        Uns8  result[bytes];
        Int32 i;

        // evaluate the expression
        ocliaEvaluate(attrs, exp, result);

        // print result
        opPrintf(" {current value:0x");
        for(i=bytes-1; i>=0; i--) {
            opPrintf("%02x", result[i]);
        }
        opPrintf("}");
    }
}


////////////////////////////////////////////////////////////////////////////////
// WALK INSTRUCTION ATTRIBUTES USING OP API
////////////////////////////////////////////////////////////////////////////////

//
// Define entry in class identification switch statement
//
#define CLASS_ENTRY(_NAME) case OCL_IC_##_NAME: opPrintf(#_NAME); break

//
// Print class - this identifies whether the instruction is a barrier of any
// kind (and possibly other processor-dependent class attributes)
//
static void printClass(octiaAttrP attrs) {

    octiaInstructionClass class;

    if((class=ocliaGetInstructionClass(attrs))) {

        octiaInstructionClass mask = 1;

        opPrintf("\n");
        opPrintf("  class ");

        do {

            if(class & mask) {

                switch(mask) {
                    CLASS_ENTRY(NOP       );
                    CLASS_ENTRY(INTEGER   );
                    CLASS_ENTRY(FLOAT     );
                    CLASS_ENTRY(DSP       );
                    CLASS_ENTRY(MULTIPLY  );
                    CLASS_ENTRY(DIVIDE    );
                    CLASS_ENTRY(FMA       );
                    CLASS_ENTRY(SIMD      );
                    CLASS_ENTRY(TRIG      );
                    CLASS_ENTRY(LOG       );
                    CLASS_ENTRY(RECIP     );
                    CLASS_ENTRY(SQRT      );
                    CLASS_ENTRY(SYSREG    );
                    CLASS_ENTRY(IBARRIER  );
                    CLASS_ENTRY(DBARRIER  );
                    CLASS_ENTRY(ABARRIER  );
                    CLASS_ENTRY(ICACHE    );
                    CLASS_ENTRY(DCACHE    );
                    CLASS_ENTRY(MMU       );
                    CLASS_ENTRY(ATOMIC    );
                    CLASS_ENTRY(EXCLUSIVE );
                    CLASS_ENTRY(HINT      );
                    CLASS_ENTRY(SYSTEM    );
                    CLASS_ENTRY(FCONVERT  );
                    CLASS_ENTRY(FCOMPARE  );
                    CLASS_ENTRY(BRANCH    );
                    CLASS_ENTRY(BRANCH_DS );
                    CLASS_ENTRY(BRANCH_DSA);
                    CLASS_ENTRY(OPAQUE_INT);
                    CLASS_ENTRY(CUSTOM1   );
                    CLASS_ENTRY(CUSTOM2   );
                    CLASS_ENTRY(CUSTOM3   );
                    CLASS_ENTRY(CUSTOM4   );
                    CLASS_ENTRY(CUSTOM5   );
                    CLASS_ENTRY(CUSTOM6   );
                    CLASS_ENTRY(CUSTOM7   );
                    CLASS_ENTRY(CUSTOM8   );
                    CLASS_ENTRY(CUSTOM9   );
                    CLASS_ENTRY(CUSTOM10  );
                    CLASS_ENTRY(CUSTOM11  );
                    CLASS_ENTRY(CUSTOM12  );
                    CLASS_ENTRY(CUSTOM13  );
                    CLASS_ENTRY(CUSTOM14  );
                    CLASS_ENTRY(CUSTOM15  );
                    CLASS_ENTRY(CUSTOM16  );
                    default: opPrintf("*unknown*");
                }

                class &= ~mask;

                if(class) {
                    opPrintf("|");
                }
            }

            mask <<= 1;

        } while(class);

        opPrintf("\n");
    }
}

//
// Print fetch records - these record the memory accesses that were made when
// fetching the instruction
//
static void printFetchRecords(octiaAttrP attrs) {

    octiaFetchRecordP fr;

    if((fr=ocliaGetFirstFetchRecord(attrs))) {

        opPrintf("\n");

        for(; fr; fr=ocliaGetNextFetchRecord(fr)) {

            Addr  fetchLow  = ocliaGetFetchRecordLow(fr);
            Addr  fetchHigh = ocliaGetFetchRecordHigh(fr);
            Uns8 *value     = ocliaGetFetchRecordBytes(fr);
            Uns32 bytes     = fetchHigh-fetchLow+1;
            Int32 i;

            opPrintf(
                "  fetch 0x"FMT_Ax":0x"FMT_Ax" (value:0x",
                fetchLow, fetchHigh
            );

            for(i=bytes-1; i>=0; i--) {
                opPrintf("%02x", value[i]);
            }

            opPrintf(")\n");
        }
    }
}

//
// Print register list - this records registers read or written by the
// instruction
//
static void printRegList(octiaRegListP regList, const char *type) {

    if(regList) {

        opPrintf("\n");

        for(; regList; regList=ocliaGetRegListNext(regList)) {
            optRegP reg = opRegConvert(ocliaGetRegListReg(regList));
            opPrintf("  %5s %s\n", type, opRegName(reg));
        }
    }
}

//
// Print range records - these record byte ranges in a processor structure that
// are accessed but not matched with registers described as a vmiRegInfoCP in
// the processor debug interface. Processors with fully-implemented instruction
// attribute interfaces should not have any unmatched range records.
//
static void printRangeList(octiaRawRangeP range, const char *type) {

    if(range) {

        opPrintf("\n");

        for(; range; range=ocliaGetRangeNext(range)) {
            opPrintf(
                "  %5s "FMT_PTRd":"FMT_PTRd"\n",
                type,
                ocliaGetRangeLow(range),
                ocliaGetRangeHigh(range)
            );
        }
    }
}

//
// Return string representation of a jump hint
//
static const char *getHintText(octiaJumpHint hint) {

    if(hint==OCL_JH_NONE) {

        return 0;

    } else {

        static char buffer[32];

        sprintf(
            buffer, "hint:%s%s%s%s",
            (hint&OCL_JH_CALL)     ? "call"        : "",
            (hint&OCL_JH_RETURN)   ? "return"      : "",
            (hint&OCL_JH_INT)      ? "int"         : "",
            (hint&OCL_JH_RELATIVE) ? " (relative)" : ""
        );

        return buffer;
    }
}

//
// Print nextPC list - this records possible execution addresses following
// this instruction address. The addresses can be constant or calculated by an
// expression.
//
static void printNextPCList(octiaAttrP attrs) {

    octiaNextPCP nextPC;

    if((nextPC=ocliaGetFirstNextPC(attrs))) {

        opPrintf("\n");

        for(; nextPC; nextPC=ocliaGetNextNextPC(nextPC)) {

            octiaJumpHint hint      = ocliaGetNextPCHint(nextPC);
            const char   *hintText  = getHintText(ocliaGetNextPCHint(nextPC));
            octiaAddrExpP nextPCExp = ocliaGetNextPCAddrExp(nextPC);

            opPrintf("  next PC ");

            printAddrExp(nextPCExp, attrs);

            if(hintText) {
                opPrintf(" %s", hintText);
            }
            if((nextPCExp->type==OCL_ET_CONST) && (hint&OCL_JH_RELATIVE)) {
                opPrintf(" offset "FMT_Ad, ocliaGetNextPCOffset(nextPC));
            }
            if(ocliaGetNextPCDS(nextPC)) {
                opPrintf(" (DS)");
            }

            opPrintf("\n");
        }
    }
}

//
// Print address expression list - this records possible load/store addresses
//
static void printAddressExpressionList(octiaAttrP attrs) {

    octiaMemAccessP ma;

    // memory access type strings
    static const char *memAccessTypeString[] = {
        [OCL_MAT_LOAD]       = "load",
        [OCL_MAT_STORE]      = "store",
        [OCL_MAT_PRELOAD_LD] = "preload-for-load",
        [OCL_MAT_PRELOAD_ST] = "preload-for-store",
        [OCL_MAT_PRELOAD_EX] = "preload-for-fetch"
    };

    if((ma=ocliaGetFirstMemAccess(attrs))) {

        opPrintf("\n");

        for(; ma; ma=ocliaGetNextMemAccess(ma)) {

            octiaAddrExpP addrExp = ocliaGetMemAccessAddrExp(ma);
            octiaRegListP depend;

            // print characteristics of memory access
            opPrintf(
                "  %u-bit %s address (bits %u): ",
                ocliaGetMemAccessMemBits(ma),
                memAccessTypeString[ocliaGetMemAccessType(ma)],
                addrExp->bits
            );

            // print load/store address expression
            printAddrExp(addrExp, attrs);
            opPrintf("\n");

            // print all dependencies of this load/store (registers that must
            // be known before it can be evaluated)
            for(
                depend=ocliaGetMemAccessFirstDepend(ma);
                depend;
                depend=ocliaGetRegListNext(depend)
            ) {
                optRegP reg = opRegConvert(ocliaGetRegListReg(depend));
                opPrintf("    depend %s\n", opRegName(reg));
            }
        }
    }
}

//
// Top level walk, printing available attributes
//
static void walkAttrs(octiaAttrP attrs) {

    printClass(attrs);
    printFetchRecords(attrs);

    printRegList(ocliaGetFirstReadReg(attrs), "read");
    printRangeList(ocliaGetFirstReadRange(attrs), "read");
    printRegList(ocliaGetFirstWrittenReg(attrs), "write");
    printRangeList(ocliaGetFirstWrittenRange(attrs), "write");

    printNextPCList(attrs);
    printAddressExpressionList(attrs);

    opPrintf("\n");
}

//
// Show instruction attributes for the processor current PC
//
static void showInstructionAttributes(optProcessorP processor) {

    Addr thisPC = opProcessorPC(processor);

    // select all attributes except nodes
    octiaDataSelect select = (
        OCL_DS_REG_R   |
        OCL_DS_REG_W   |
        OCL_DS_RANGE_R |
        OCL_DS_RANGE_W |
        OCL_DS_FETCH   |
        OCL_DS_NEXTPC  |
        OCL_DS_ADDRESS
    );

    // get instruction attributes for the current PC
    octiaAttrP attrs = opProcessorInstructionAttributes(
        processor, thisPC, select, False
    );

    if(attrs) {

        // print instruction disassembly
        opPrintf(
            "*** ATTRIBUTES FOR INSTRUCTION AT ADDRESS 0x"FMT_Ax" (%s)\n",
            thisPC,
            opProcessorDisassemble(processor, thisPC, OP_DSA_NORMAL)
        );

        // walk attributes
        walkAttrs(attrs);

        // free attributes
        ocliaFreeAttrs(attrs);
    }
}

//
// Standard command line parser
//
static Bool cmdParser(int argc, const char *argv[]) {

    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    return opCmdParseArgs(parser, argc, argv);
}

//
// Simulation main loop
//
static Bool simulate(optProcessorP processor, Uns32 clocks) {

    Uns32 i;

    for(i=0; i<clocks; i++) {

        showInstructionAttributes(processor);

        optStopReason stopReason = opProcessorSimulate(processor, 1);

        switch(stopReason) {

           case OP_SR_SCHED:
               // hit the scheduler limit
               break;

           case OP_SR_EXIT:
               // processor has exited
               return False;

           case OP_SR_FINISH:
               // simulation must end
               return False;

           case OP_SR_RD_PRIV:
           case OP_SR_WR_PRIV:
           case OP_SR_RD_ALIGN:
           case OP_SR_WR_ALIGN:
              // unhandled processor exception: simulation must end
              return False;

           default:
               opPrintf("unexpected stopReason %s\n", opStopReasonString(stopReason));
               return False;
        }
    }

    return True;
}

//
// Virtual platform construction and simulation
//
int main(int argc, const char **argv) {

    // initialize simulation session before calling any other OP functions
    opSessionInit(OP_VERSION);

    // check arguments
    if(!cmdParser(argc, argv)) {
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

    // create a processor instance
    const char *modelFile = "model."IMPERAS_SHRSUF;
    optProcessorP processor = opProcessorNew(mr, modelFile, "cpu1", 0, 0);

    // get semihost library to exit simulation
    const char *semihostFile = opVLNVString( 0, "ovpworld.org", "modelSupport", "imperasExit", "1.0", OP_EXTENSION, OP_VLNV_FATAL);

    // attach imperasExit semihost library to processor
    opProcessorExtensionNew(processor, semihostFile, "imperasExit", 0);

    // create the processor bus
    optBusP bus = opBusNew(mr, "bus", 32, 0, 0);

    // connect processor instruction and data ports to the common bus
    opProcessorBusConnect(processor, bus, "INSTRUCTION");
    opProcessorBusConnect(processor, bus, "DATA");

    // create memory
    optMemoryP memory = opMemoryNew(mr, "local", OP_PRIV_RWX, 0xffffffff, 0, 0);

    // connect the memory onto the bus
    opMemoryBusConnect(memory, bus, "mp1", 0x00000000, 0xffffffff);

    // force elaboration of simulation data structures
    opRootModulePreSimulate(mr);

    // run processor until done (no instruction limit)
    simulate(processor, -1);

    // terminate the simulation session
    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}


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

#define MODULE_NAME "top"
#define MODULE_INSTANCE "u1"

typedef struct memElemS {
    Uns8            *data;
    Uns32            bytes;
    struct memElemS *next;
} memElemT, *memElemP;

memElemP save_mem_head = NULL;
memElemP save_mem_tail = NULL;
memElemP restore_mem   = NULL;

OP_SAVE_FN(saveState) {

    Uns8    *ptr  = data;
    memElemP this = NULL;

    if (save_mem_head == NULL) {
        this = save_mem_head = (memElemP) malloc(sizeof(memElemT));
    } else {
        this = save_mem_tail->next = (memElemP) malloc(sizeof(memElemT));
    }
    save_mem_tail = this;

    this->data  = NULL;
    this->next  = NULL;
    this->bytes = bytes;
    if (bytes) {
        this->data = (Uns8 *) malloc(bytes);
        memcpy(this->data, data, bytes);
    } else {
        this->data = (Uns8 *) malloc(1);
        char c = (*ptr) ? *ptr : '\n';
        memcpy(this->data, &c, 1);
    }

    return 1;
}

OP_RESTORE_FN(restoreState) {

    Uns8    *ptr  = data;
    memElemP this = restore_mem;

    if (this) {
        if (this->bytes) {
            memcpy(data, this->data, this->bytes);
        } else {
            memcpy(data, this->data, 1);
            if(*ptr == '\n') {
                *ptr = 0;
            }
        }
    } else {
        opMessage("F", "RESTORE_MEM", "Restore data exceeded");
    }

    restore_mem = restore_mem->next;

    return 1;
}

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);
    opCmdParseStd(MODULE_NAME, OP_AC_ALL, argc, argv);

    optModuleP mr = opRootModuleNew(0, MODULE_NAME, 0);

    const char *u1_path = "module";
    optModuleP mi = opModuleNew(
        mr,                 // parent module
        u1_path,            // modelfile
        MODULE_INSTANCE,    // name
        0,
        0
    );

    optMemoryP    mem       = opObjectByName(mi, "mem",  OP_MEMORY_EN).Memory;
    optProcessorP processor = opObjectByName(mi, "cpu1", OP_PROCESSOR_EN).Processor;

    // break after 1000 instructions
    opRootModulePreSimulate(mr);
    opProcessorBreakpointICountSet(processor, 100);

    //
    // set break @+100
    // ST1: stop @100 insns
    //      save state
    //      break at +1000
    // ST2: stop @2000 insns
    //      restore state
    //      continue
    //
    enum {ST1, ST2, ST_UNDEF} state;

    int running = 1;
    state = ST1;
    while (running) {
        running = 0;

        optProcessorP processor = opRootModuleSimulate(mr);

        if(processor) {
            optStopReason sr = opProcessorStopReason(processor);
            opPrintf("Simulator StopReason = %s\n", opStopReasonString(sr));

            switch (sr) {
            case OP_SR_BP_ICOUNT:
                switch (state) {
                case ST1:   // stop time == +100
                    opPrintf("OP_SR_BP_ICOUNT @ST1 : Save State\n");

                    // save memory
                    opMemoryStateSave(mem, saveState, "mem");
                    opProcessorStateSave(processor, saveState, "proc");

                    // Break At +1000
                    opProcessorBreakpointICountSet(processor, 1000);
                    running = 1;
                    state = ST2;
                    break;

                case ST2:   // stop time == +1000
                    opPrintf("OP_SR_BP_ICOUNT @ST2 : Restore state\n");

                    // restore state
                    restore_mem = save_mem_head;
                    opMemoryStateRestore(mem, restoreState, "mem");
                    opProcessorStateRestore(processor, restoreState, "proc");

                    state = ST_UNDEF;
                    running = 1;
                    break;

                default:
                    opPrintf("OP_SR_BP_ICOUNT @ST_UNDEF : should not reach\n");
                    // ???
                    break;

                }
                break;
            case OP_SR_EXIT:
            case OP_SR_FINISH:
                break;
            default:
                opPrintf("Unexpected StopReason\n");
                break;
            }
        }
    }

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}


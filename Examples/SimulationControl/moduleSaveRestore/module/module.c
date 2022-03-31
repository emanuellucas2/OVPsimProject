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


#define MODULE_NAME "simpleCpuMemory"

#define COUNT "count"


typedef struct optModuleObjectS {
    // insert module persistent data here
    Uns32 count;
} optModuleObject;

static OP_MODULE_SAVE_FN(moduleSave) {
    opPrintf("Saving    module '%s'\n", opObjectHierName(mi));
    opStateItemSave(context, COUNT, sizeof(object->count), &object->count);
}

static OP_MODULE_RESTORE_FN(moduleRestore) {
    opPrintf("Restoring module '%s'\n", opObjectHierName(mi));
    opStateItemRestore(context, COUNT, sizeof(object->count), &object->count);
}

static OP_MONITOR_FN(wcb) {
    optModuleObjectP obj = userData;
    
    obj->count++;
}

static OP_CONSTRUCT_FN(moduleConstructor) {

    object->count = 0;
     
    optBusP mainBus_b = opBusNew(mi, "mainBus", 32, 0, 0);

    const char *cpu1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "processor",
        "or1k",
        "1.0",
        OP_PROCESSOR,
        OP_VLNV_FATAL
    );

    opProcessorNew(
        mi,
        cpu1_path,
        "cpu1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainBus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(mainBus_b, "DATA")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("variant", "generic"),
             OP_PARAM_BOOL_SET("trace", 1),
             OP_PARAM_BOOL_SET("traceshowicount", 1),
             OP_PARAM_BOOL_SET("defaultsemihost", 1)
        )
    );

    opMemoryNew(
        mi,
        "mem",
        OP_PRIV_RWX,
        (0xffffffffULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );
    
    opBusFetchMonitorAdd(mainBus_b, 0, 0, 0x1000, wcb, object);
}

static OP_DESTRUCT_FN(moduleDestructor) {
    opPrintf("Destruct %u\n", object->count);
}

optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_MODULE,
    .name                 = MODULE_NAME,
    .objectSize           = sizeof(optModuleObject),
    .releaseStatus        = OP_UNSET,
    .purpose              = OP_PP_BAREMETAL,
    .visibility           = OP_VISIBLE,
    .constructCB          = moduleConstructor,
    .destructCB           = moduleDestructor,
    .saveCB               = moduleSave,
    .restoreCB            = moduleRestore,
    .saveRestoreSupported = True
};


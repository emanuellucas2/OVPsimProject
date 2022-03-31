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

typedef struct optModuleObjectS {
    // insert module persistent data here
    Uns32 count;
} optModuleObject;

#define PREFIX          "BUS_MON"

// Give the monitoring a threshold
static unsigned int count;
#define MONITOR_THRESHOLD 100

//
// triggered when registered access happens and prints information of access
//
static OP_MONITOR_FN(monitorCallback) {
    if(++count < MONITOR_THRESHOLD) {
        opMessage ("I", PREFIX "_MT", "Monitor triggered (%03d): "
                                  "callback '%s': processor '%s' : "
                                  "type '%s' : bytes %u : "
                                  "address Physical 0x" FMT_A0Nx" Virtual  0x" FMT_A0Nx " %s",
                             count,
                             __FUNCTION__,
                             processor ? opObjectName(processor) : "artifact",  // if no processor this is an artifact access
                             (const char*)userData,
                             bytes,
                             addr,
                             VA,
                             (count == MONITOR_THRESHOLD) ? "(threshold reached)" : "");
    }
}

//
// iterate across the buses found in the module and register callbacks for read, write and fetch
//
static void monitorBus(optModuleP mi) {
    // iterate across all busses found in module
    optBusP bus = 0;
    while ((bus = opBusNext(mi, bus))) {
        Addr min = 0;
        Addr max = opBusMaxAddress(bus);
        opMessage("I", PREFIX "_BM", "Add monitor for '%s' (0x" FMT_A0Nx " to 0x" FMT_A0Nx ")\n",
                                      opObjectHierName(bus), (Addr)0, max);
        opBusFetchMonitorAdd(bus, 0, min, max, monitorCallback, "bus-fetch");
        opBusReadMonitorAdd (bus, 0, min, max, monitorCallback, "bus-read");
        opBusWriteMonitorAdd(bus, 0, min, max, monitorCallback, "bus-write");
    }
}

//
// iterate across the memories found in the module and register callbacks for read, write and fetch
//
static void monitorMemory(optModuleP mi) {
    // iterate across all memories found in module
    optMemoryP memory = 0;
    while ((memory = opMemoryNext(mi, memory))) {
        Addr min = 0;
        Addr max = opMemoryMaxAddress(memory);
        opMessage("I", PREFIX "_BM", "Add monitor for '%s' (0x" FMT_A0Nx " to 0x" FMT_A0Nx ")\n",
                                      opObjectHierName(memory), (Addr)0, max);
        opMemoryFetchMonitorAdd(memory, 0, min, max, monitorCallback, "memory-fetch");
        opMemoryReadMonitorAdd (memory, 0, min, max, monitorCallback, "memory-read");
        opMemoryWriteMonitorAdd(memory, 0, min, max, monitorCallback, "memory-write");
    }
}

////////////////////////////////////////////////////////////////////////////////
//                         U S E R   F U N C T I O N S
////////////////////////////////////////////////////////////////////////////////

// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);

    // insert constructor code here
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {

    // Set up bus monitors
    monitorBus(mi);

    // Set up memory monitors
    monitorMemory(mi);
}

static OP_SIMULATE_STARTING_FN(moduleSimulateStart) {
    // insert simulation starting code here
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
    // insert post simulation code here
}

static OP_DESTRUCT_FN(moduleDestruct) {
    // insert destructor code here
}

#include "module.igen.h"

/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

//#include "sysc/kernel/sc_module.h"
#include "tlm.h"                                // TLM headers
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "op/op.hpp"

#include "tlmModule.hpp"

using namespace op;
using namespace sc_core;
using namespace std;

namespace cw {

#define STACK_SIZE 0x50000

/// Generic TLM/OVP processor.
/// Instances one OVP Processor model and starts SystemC threads for each core

class tlmProcessor : public sc_module, public processor
{

private:
    bool                traceQuantaOn;       // trace controls
    bool                traceBusesOn;
    bool                traceBusErrorsOn;
    bool                traceSignalsOn;
    bool                dmiOn;               // current state of DMI

    sc_time             localQuantum;

    void setTracing(void) {
        if(getenv("IMPERAS_TLM_CPU_TRACE")) {
            opPrintf("TLM: %s Tracing ON (addresses [] and data {} in Hexadecimal)\n", hierCName());
            traceBusesOn     = true;
            traceBusErrorsOn = true;
            traceSignalsOn   = true;
            traceQuantaOn    = true;
        }
    }

    params setSystemC(params p) {
        p.set("systemc", True);
        return p;
    }

    params setSystemC() {
        params p;
        p.set("systemc", True);
        return p;
    }

    void startThreads();
    static void explore(tlmProcessor *t, processor *p);

public:

    /// Construct a generic TLM processor
    /// @param name      New instance name
    /// @param path      Path to the model (resolved from the VLNV)

    tlmProcessor (tlmModule &parent, std::string path, sc_module_name name);
    tlmProcessor (tlmModule &parent, std::string path, sc_module_name name, params p);

protected:
    void processorThread (processor *p);

    static void threadEntry(tlmProcessor *t, processor *p);

public:

    /// Control tracing of each quantum.
    /// @param on         On/Off.
    void traceQuanta(bool on) { traceQuantaOn = on; }

    /// Control tracing of each quantum.
    /// @return           On/Off.
    bool traceQuanta(void)    { return traceQuantaOn; }


    /// Control tracing of each bus cycle.
    /// @param on         On/Off.
    void traceBuses(bool on)  { traceBusesOn = on; }

    /// Fetch tracing of each bus cycle.
    /// @return           On/Off.
    bool traceBuses(void)         { return traceBusesOn; }

    /// Fetch tracing of each bus cycle.
    /// @param on         On/Off.
    void traceBusErrors(bool on) { traceBusErrorsOn = on; }

    /// Fetch tracing of each bus cycle.
    /// @return           On/Off.
    bool traceBusErrors(void) { return traceBusErrorsOn; }

    /// Control tracing of signals (interrupts).
    /// @param on        On/Off.
    void traceSignals(bool on) { traceSignalsOn = on; }

    /// Fetch tracing of signals.
    /// @return           On/Off.
    bool traceSignals(void) { return traceSignalsOn; }

    /// Set the local quantum (in SystemC time units)
    void    quantum (sc_time q) { localQuantum = q; }

    /// Return the current local quantum
    /// @return           Quantum (in SystemC time units)
    sc_time quantum (void     ) { return localQuantum; }

    /// Fetch DMI mode.
    /// @return           On/Off.
    bool dmi(void) { return dmiOn; }

    /// Set DMI mode.
    /// @param on        New state
    void dmi(bool on) { dmiOn = on; }

};


} // end namespace cw

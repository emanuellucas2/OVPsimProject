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

#include "tlm.h"                                // TLM headers
#include "tlm_utils/simple_initiator_socket.h"  // equivalent of OVP Bus Master Port
#include "tlm_utils/simple_target_socket.h"     // equivalent of OVP Bus Master Port

#include "tlmModule.hpp"

#include "op/op.hpp"

using namespace op;
using namespace std;
using namespace sc_core;
using namespace tlm;

namespace cw {

class module;
class tlmModule;
class tlmDecoder;
class tlmProcessor;

class tlmPeripheral : public sc_module, public peripheral {

private:
    bool traceBusesOn;
    bool traceBusErrorsOn;
    bool traceSignalsOn;

    tlmModule &parentModule;

    void setTracing(void) {
        if(getenv("IMPERAS_TLM_PSE_TRACE")) {
            opPrintf("TLM: %s Tracing ON (addresses [] and data {} in Hexadecimal)\n", hierCName());
            traceBusesOn     = true;
            traceBusErrorsOn = true;
            traceSignalsOn   = true;
        }
    }

public:

    /// The peripheral constructor.
    /// @param name             Instance name. Must be unique in the platform.
    /// @param model            Path to model PSE object file. See icmGetVlnvString().
    /// @param semihostLibrary  Path to intercept object (.dll or .so) if required.
    /// @param initialAttrs     (optional) List of user-defined attributes passed to the model.

    tlmPeripheral(tlmModule &parent, string path, sc_module_name name);
    tlmPeripheral(tlmModule &parent, string path, sc_module_name name, params p);

    ~tlmPeripheral() {}

    void traceBuses(bool on)     { traceBusesOn = on;       }
    bool traceBuses(void)        { return traceBusesOn;     }
    void traceBusErrors(bool on) { traceBusErrorsOn = on;   }
    bool traceBusErrors(void)    { return traceBusErrorsOn; }
    void traceSignals(bool on)   { traceSignalsOn = on;     }
    bool traceSignals(void)      { return traceSignalsOn;   }

    void connect(string localPort, tlmPeripheral &p, string remotePort);
    void connect(string localPort, tlmProcessor  &p, string remotePort);
    void connect(tlmDecoder   &target, string portName, Addr lo, Addr hi);
    void connect(tlmDecoder   &target, string portName);
    void connect(tlmDecoder   &initiator, string portName, Uns32 addrBits);
};


} // end namespace cw

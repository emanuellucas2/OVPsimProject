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
#include "tlm_utils/simple_target_socket.h"     // equivalent of OVP Bus Slave Port

#include "tlmModule.hpp"
#include "tlm/tlmDecoder.hpp"
#include "tlm/tlmBusPort.hpp"

#include "op/op.hpp"

using namespace op;
using namespace std;
using namespace sc_core;
using namespace tlm;

namespace cw {


/// Generic TLM/OVP MMC.
/// It instances one OVP MMC model which can be connected to TLM initiator and
/// acceptor sockets.

class tlmMMC : public sc_module, public MMC {

private:
    bool traceBusesOn;
    tlmModule &parentModule;

public:
    tlmMMC(tlmModule &parent, string path, sc_module_name name);
    tlmMMC(tlmModule &parent, string path, sc_module_name name, params p);

    ~tlmMMC() {}

    bool traceBuses(void)      { return traceBusesOn; }
    void traceBuses(bool on)   { traceBusesOn = on;   }

    void connect(tlmDecoder &initiator, string portName, Uns32 addrBits);
    void connect(tlmDecoder &target,    string portName);
};

} // end namespace cw

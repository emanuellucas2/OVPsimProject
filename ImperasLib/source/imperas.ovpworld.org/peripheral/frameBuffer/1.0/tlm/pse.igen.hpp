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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////

// MODEL IO:
//    Slave Port mp
//    Slave Port sp
//    Net input  reset;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class frameBuffer : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "imperas.ovpworld.org", "peripheral", "frameBuffer", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusDynamicSlavePort mp;
    tlmBusSlavePort sp;
    tlmNetInputPort reset;

    frameBuffer(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , mp(parent, this, "mp", 0) // dynamic
        , sp(parent, this, "sp", 0x1000) // static
        , reset(parent, this, "reset")
    {
    }

    frameBuffer(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , mp(parent, this, "mp", 0) // dynamic
        , sp(parent, this, "sp", 0x1000) // static
        , reset(parent, this, "reset")
    {
    }

}; /* class frameBuffer */


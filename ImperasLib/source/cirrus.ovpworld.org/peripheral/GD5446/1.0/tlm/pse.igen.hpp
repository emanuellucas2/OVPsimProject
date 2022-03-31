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
//    Slave Port config
//    Slave Port memory
//    Slave Port PCIconfig

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class GD5446 : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "cirrus.ovpworld.org", "peripheral", "GD5446", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort config;
    tlmBusDynamicSlavePort memory;
    tlmBusDynamicSlavePort PCIconfig;

    GD5446(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , config(parent, this, "config", 0x30) // static
        , memory(parent, this, "memory", 22) // dynamic
        , PCIconfig(parent, this, "PCIconfig", 11) // dynamic
    {
    }

    GD5446(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , config(parent, this, "config", 0x30) // static
        , memory(parent, this, "memory", 22) // dynamic
        , PCIconfig(parent, this, "PCIconfig", 11) // dynamic
    {
    }

}; /* class GD5446 */


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
//    Slave Port port0
//    Net input  reset;
//    Net input  irqS1;
//    Net output  irqT0;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class PLIC : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "sifive.ovpworld.org", "peripheral", "PLIC", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort port0;
    tlmNetInputPort reset;
    tlmNetInputPort irqS1;
    tlmNetOutputPort irqT0;

    PLIC(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , port0(parent, this, "port0", 0x400000) // static
        , reset(parent, this, "reset")
        , irqS1(parent, this, "irqS1")
        , irqT0(parent, this, "irqT0")
    {
    }

    PLIC(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , port0(parent, this, "port0", 0x400000) // static
        , reset(parent, this, "reset")
        , irqS1(parent, this, "irqS1")
        , irqT0(parent, this, "irqT0")
    {
    }

}; /* class PLIC */


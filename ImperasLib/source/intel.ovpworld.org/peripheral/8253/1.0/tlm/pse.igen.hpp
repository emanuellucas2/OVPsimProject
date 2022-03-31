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
//    Slave Port bport1
//    Net input  clk0;
//    Net input  clk1;
//    Net input  clk2;
//    Net input  gate0;
//    Net input  gate1;
//    Net input  gate2;
//    Net output  out0;
//    Net output  out1;
//    Net output  out2;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class _8253 : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "intel.ovpworld.org", "peripheral", "8253", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetInputPort clk0;
    tlmNetInputPort clk1;
    tlmNetInputPort clk2;
    tlmNetInputPort gate0;
    tlmNetInputPort gate1;
    tlmNetInputPort gate2;
    tlmNetOutputPort out0;
    tlmNetOutputPort out1;
    tlmNetOutputPort out2;

    _8253(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x4) // static
        , clk0(parent, this, "clk0")
        , clk1(parent, this, "clk1")
        , clk2(parent, this, "clk2")
        , gate0(parent, this, "gate0")
        , gate1(parent, this, "gate1")
        , gate2(parent, this, "gate2")
        , out0(parent, this, "out0")
        , out1(parent, this, "out1")
        , out2(parent, this, "out2")
    {
    }

    _8253(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x4) // static
        , clk0(parent, this, "clk0")
        , clk1(parent, this, "clk1")
        , clk2(parent, this, "clk2")
        , gate0(parent, this, "gate0")
        , gate1(parent, this, "gate1")
        , gate2(parent, this, "gate2")
        , out0(parent, this, "out0")
        , out1(parent, this, "out1")
        , out2(parent, this, "out2")
    {
    }

}; /* class _8253 */


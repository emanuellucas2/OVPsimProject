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
//    Slave Port bportS
//    Slave Port bportNS
//    Net output  Int0;
//    Net output  Int1;
//    Net output  Int2;
//    Net output  Int3;
//    Net output  Int4;
//    Net output  Int5;
//    Net output  Int6;
//    Net output  Int7;
//    Net output  inta;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class zynq_7000_dmac : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "xilinx.ovpworld.org", "peripheral", "zynq_7000-dmac", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bportS;
    tlmBusSlavePort bportNS;
    tlmNetOutputPort Int0;
    tlmNetOutputPort Int1;
    tlmNetOutputPort Int2;
    tlmNetOutputPort Int3;
    tlmNetOutputPort Int4;
    tlmNetOutputPort Int5;
    tlmNetOutputPort Int6;
    tlmNetOutputPort Int7;
    tlmNetOutputPort inta;

    zynq_7000_dmac(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bportS(parent, this, "bportS", 0x1000) // static
        , bportNS(parent, this, "bportNS", 0x1000) // static
        , Int0(parent, this, "Int0")
        , Int1(parent, this, "Int1")
        , Int2(parent, this, "Int2")
        , Int3(parent, this, "Int3")
        , Int4(parent, this, "Int4")
        , Int5(parent, this, "Int5")
        , Int6(parent, this, "Int6")
        , Int7(parent, this, "Int7")
        , inta(parent, this, "inta")
    {
    }

    zynq_7000_dmac(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bportS(parent, this, "bportS", 0x1000) // static
        , bportNS(parent, this, "bportNS", 0x1000) // static
        , Int0(parent, this, "Int0")
        , Int1(parent, this, "Int1")
        , Int2(parent, this, "Int2")
        , Int3(parent, this, "Int3")
        , Int4(parent, this, "Int4")
        , Int5(parent, this, "Int5")
        , Int6(parent, this, "Int6")
        , Int7(parent, this, "Int7")
        , inta(parent, this, "inta")
    {
    }

}; /* class zynq_7000_dmac */


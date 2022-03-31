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
//    Slave Port plb
//    Net output  Irq;
//    Net input  Intr0;
//    Net input  Intr1;
//    Net input  Intr2;
//    Net input  Intr3;
//    Net input  Intr4;
//    Net input  Intr5;
//    Net input  Intr6;
//    Net input  Intr7;
//    Net input  Intr8;
//    Net input  Intr9;
//    Net input  Intr10;
//    Net input  Intr11;
//    Net input  Intr12;
//    Net input  Intr13;
//    Net input  Intr14;
//    Net input  Intr15;
//    Net input  Intr16;
//    Net input  Intr17;
//    Net input  Intr18;
//    Net input  Intr19;
//    Net input  Intr20;
//    Net input  Intr21;
//    Net input  Intr22;
//    Net input  Intr23;
//    Net input  Intr24;
//    Net input  Intr25;
//    Net input  Intr26;
//    Net input  Intr27;
//    Net input  Intr28;
//    Net input  Intr29;
//    Net input  Intr30;
//    Net input  Intr31;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class xps_intc : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "xilinx.ovpworld.org", "peripheral", "xps-intc", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort plb;
    tlmNetOutputPort Irq;
    tlmNetInputPort Intr0;
    tlmNetInputPort Intr1;
    tlmNetInputPort Intr2;
    tlmNetInputPort Intr3;
    tlmNetInputPort Intr4;
    tlmNetInputPort Intr5;
    tlmNetInputPort Intr6;
    tlmNetInputPort Intr7;
    tlmNetInputPort Intr8;
    tlmNetInputPort Intr9;
    tlmNetInputPort Intr10;
    tlmNetInputPort Intr11;
    tlmNetInputPort Intr12;
    tlmNetInputPort Intr13;
    tlmNetInputPort Intr14;
    tlmNetInputPort Intr15;
    tlmNetInputPort Intr16;
    tlmNetInputPort Intr17;
    tlmNetInputPort Intr18;
    tlmNetInputPort Intr19;
    tlmNetInputPort Intr20;
    tlmNetInputPort Intr21;
    tlmNetInputPort Intr22;
    tlmNetInputPort Intr23;
    tlmNetInputPort Intr24;
    tlmNetInputPort Intr25;
    tlmNetInputPort Intr26;
    tlmNetInputPort Intr27;
    tlmNetInputPort Intr28;
    tlmNetInputPort Intr29;
    tlmNetInputPort Intr30;
    tlmNetInputPort Intr31;

    xps_intc(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , plb(parent, this, "plb", 0x20) // static
        , Irq(parent, this, "Irq")
        , Intr0(parent, this, "Intr0")
        , Intr1(parent, this, "Intr1")
        , Intr2(parent, this, "Intr2")
        , Intr3(parent, this, "Intr3")
        , Intr4(parent, this, "Intr4")
        , Intr5(parent, this, "Intr5")
        , Intr6(parent, this, "Intr6")
        , Intr7(parent, this, "Intr7")
        , Intr8(parent, this, "Intr8")
        , Intr9(parent, this, "Intr9")
        , Intr10(parent, this, "Intr10")
        , Intr11(parent, this, "Intr11")
        , Intr12(parent, this, "Intr12")
        , Intr13(parent, this, "Intr13")
        , Intr14(parent, this, "Intr14")
        , Intr15(parent, this, "Intr15")
        , Intr16(parent, this, "Intr16")
        , Intr17(parent, this, "Intr17")
        , Intr18(parent, this, "Intr18")
        , Intr19(parent, this, "Intr19")
        , Intr20(parent, this, "Intr20")
        , Intr21(parent, this, "Intr21")
        , Intr22(parent, this, "Intr22")
        , Intr23(parent, this, "Intr23")
        , Intr24(parent, this, "Intr24")
        , Intr25(parent, this, "Intr25")
        , Intr26(parent, this, "Intr26")
        , Intr27(parent, this, "Intr27")
        , Intr28(parent, this, "Intr28")
        , Intr29(parent, this, "Intr29")
        , Intr30(parent, this, "Intr30")
        , Intr31(parent, this, "Intr31")
    {
    }

    xps_intc(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , plb(parent, this, "plb", 0x20) // static
        , Irq(parent, this, "Irq")
        , Intr0(parent, this, "Intr0")
        , Intr1(parent, this, "Intr1")
        , Intr2(parent, this, "Intr2")
        , Intr3(parent, this, "Intr3")
        , Intr4(parent, this, "Intr4")
        , Intr5(parent, this, "Intr5")
        , Intr6(parent, this, "Intr6")
        , Intr7(parent, this, "Intr7")
        , Intr8(parent, this, "Intr8")
        , Intr9(parent, this, "Intr9")
        , Intr10(parent, this, "Intr10")
        , Intr11(parent, this, "Intr11")
        , Intr12(parent, this, "Intr12")
        , Intr13(parent, this, "Intr13")
        , Intr14(parent, this, "Intr14")
        , Intr15(parent, this, "Intr15")
        , Intr16(parent, this, "Intr16")
        , Intr17(parent, this, "Intr17")
        , Intr18(parent, this, "Intr18")
        , Intr19(parent, this, "Intr19")
        , Intr20(parent, this, "Intr20")
        , Intr21(parent, this, "Intr21")
        , Intr22(parent, this, "Intr22")
        , Intr23(parent, this, "Intr23")
        , Intr24(parent, this, "Intr24")
        , Intr25(parent, this, "Intr25")
        , Intr26(parent, this, "Intr26")
        , Intr27(parent, this, "Intr27")
        , Intr28(parent, this, "Intr28")
        , Intr29(parent, this, "Intr29")
        , Intr30(parent, this, "Intr30")
        , Intr31(parent, this, "Intr31")
    {
    }

}; /* class xps_intc */


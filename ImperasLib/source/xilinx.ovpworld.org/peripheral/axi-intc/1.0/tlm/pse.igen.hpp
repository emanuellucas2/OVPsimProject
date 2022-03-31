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
//    Net input  intr0;
//    Net input  intr1;
//    Net input  intr2;
//    Net input  intr3;
//    Net input  intr4;
//    Net input  intr5;
//    Net input  intr6;
//    Net input  intr7;
//    Net input  intr8;
//    Net input  intr9;
//    Net input  intr10;
//    Net input  intr11;
//    Net input  intr12;
//    Net input  intr13;
//    Net input  intr14;
//    Net input  intr15;
//    Net input  intr16;
//    Net input  intr17;
//    Net input  intr18;
//    Net input  intr19;
//    Net input  intr20;
//    Net input  intr21;
//    Net input  intr22;
//    Net input  intr23;
//    Net input  intr24;
//    Net input  intr25;
//    Net input  intr26;
//    Net input  intr27;
//    Net input  intr28;
//    Net input  intr29;
//    Net input  intr30;
//    Net input  intr31;
//    Net input  irq_in;
//    Net input  irq_addr_in;
//    Net output  irq_ack_out;
//    Net output  irq;
//    Net input  irq_ack;
//    Net output  irq_addr_out;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class axi_intc : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "xilinx.ovpworld.org", "peripheral", "axi-intc", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetInputPort intr0;
    tlmNetInputPort intr1;
    tlmNetInputPort intr2;
    tlmNetInputPort intr3;
    tlmNetInputPort intr4;
    tlmNetInputPort intr5;
    tlmNetInputPort intr6;
    tlmNetInputPort intr7;
    tlmNetInputPort intr8;
    tlmNetInputPort intr9;
    tlmNetInputPort intr10;
    tlmNetInputPort intr11;
    tlmNetInputPort intr12;
    tlmNetInputPort intr13;
    tlmNetInputPort intr14;
    tlmNetInputPort intr15;
    tlmNetInputPort intr16;
    tlmNetInputPort intr17;
    tlmNetInputPort intr18;
    tlmNetInputPort intr19;
    tlmNetInputPort intr20;
    tlmNetInputPort intr21;
    tlmNetInputPort intr22;
    tlmNetInputPort intr23;
    tlmNetInputPort intr24;
    tlmNetInputPort intr25;
    tlmNetInputPort intr26;
    tlmNetInputPort intr27;
    tlmNetInputPort intr28;
    tlmNetInputPort intr29;
    tlmNetInputPort intr30;
    tlmNetInputPort intr31;
    tlmNetInputPort irq_in;
    tlmNetInputPort irq_addr_in;
    tlmNetOutputPort irq_ack_out;
    tlmNetOutputPort irq;
    tlmNetInputPort irq_ack;
    tlmNetOutputPort irq_addr_out;

    axi_intc(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x200) // static
        , intr0(parent, this, "intr0")
        , intr1(parent, this, "intr1")
        , intr2(parent, this, "intr2")
        , intr3(parent, this, "intr3")
        , intr4(parent, this, "intr4")
        , intr5(parent, this, "intr5")
        , intr6(parent, this, "intr6")
        , intr7(parent, this, "intr7")
        , intr8(parent, this, "intr8")
        , intr9(parent, this, "intr9")
        , intr10(parent, this, "intr10")
        , intr11(parent, this, "intr11")
        , intr12(parent, this, "intr12")
        , intr13(parent, this, "intr13")
        , intr14(parent, this, "intr14")
        , intr15(parent, this, "intr15")
        , intr16(parent, this, "intr16")
        , intr17(parent, this, "intr17")
        , intr18(parent, this, "intr18")
        , intr19(parent, this, "intr19")
        , intr20(parent, this, "intr20")
        , intr21(parent, this, "intr21")
        , intr22(parent, this, "intr22")
        , intr23(parent, this, "intr23")
        , intr24(parent, this, "intr24")
        , intr25(parent, this, "intr25")
        , intr26(parent, this, "intr26")
        , intr27(parent, this, "intr27")
        , intr28(parent, this, "intr28")
        , intr29(parent, this, "intr29")
        , intr30(parent, this, "intr30")
        , intr31(parent, this, "intr31")
        , irq_in(parent, this, "irq_in")
        , irq_addr_in(parent, this, "irq_addr_in")
        , irq_ack_out(parent, this, "irq_ack_out")
        , irq(parent, this, "irq")
        , irq_ack(parent, this, "irq_ack")
        , irq_addr_out(parent, this, "irq_addr_out")
    {
    }

    axi_intc(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x200) // static
        , intr0(parent, this, "intr0")
        , intr1(parent, this, "intr1")
        , intr2(parent, this, "intr2")
        , intr3(parent, this, "intr3")
        , intr4(parent, this, "intr4")
        , intr5(parent, this, "intr5")
        , intr6(parent, this, "intr6")
        , intr7(parent, this, "intr7")
        , intr8(parent, this, "intr8")
        , intr9(parent, this, "intr9")
        , intr10(parent, this, "intr10")
        , intr11(parent, this, "intr11")
        , intr12(parent, this, "intr12")
        , intr13(parent, this, "intr13")
        , intr14(parent, this, "intr14")
        , intr15(parent, this, "intr15")
        , intr16(parent, this, "intr16")
        , intr17(parent, this, "intr17")
        , intr18(parent, this, "intr18")
        , intr19(parent, this, "intr19")
        , intr20(parent, this, "intr20")
        , intr21(parent, this, "intr21")
        , intr22(parent, this, "intr22")
        , intr23(parent, this, "intr23")
        , intr24(parent, this, "intr24")
        , intr25(parent, this, "intr25")
        , intr26(parent, this, "intr26")
        , intr27(parent, this, "intr27")
        , intr28(parent, this, "intr28")
        , intr29(parent, this, "intr29")
        , intr30(parent, this, "intr30")
        , intr31(parent, this, "intr31")
        , irq_in(parent, this, "irq_in")
        , irq_addr_in(parent, this, "irq_addr_in")
        , irq_ack_out(parent, this, "irq_ack_out")
        , irq(parent, this, "irq")
        , irq_ack(parent, this, "irq_ack")
        , irq_addr_out(parent, this, "irq_addr_out")
    {
    }

}; /* class axi_intc */


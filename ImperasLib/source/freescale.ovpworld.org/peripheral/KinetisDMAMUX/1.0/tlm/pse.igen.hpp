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
//    Net input  Reset;
//    Net output  eDMARequest;
//    Net input  dmaSrc0;
//    Net input  dmaSrc1;
//    Net input  dmaSrc2;
//    Net input  dmaSrc3;
//    Net input  dmaSrc4;
//    Net input  dmaSrc5;
//    Net input  dmaSrc6;
//    Net input  dmaSrc7;
//    Net input  dmaSrc8;
//    Net input  dmaSrc9;
//    Net input  dmaSrc10;
//    Net input  dmaSrc11;
//    Net input  dmaSrc12;
//    Net input  dmaSrc13;
//    Net input  dmaSrc14;
//    Net input  dmaSrc15;
//    Net input  dmaSrc16;
//    Net input  dmaSrc17;
//    Net input  dmaSrc18;
//    Net input  dmaSrc19;
//    Net input  dmaSrc20;
//    Net input  dmaSrc21;
//    Net input  dmaSrc22;
//    Net input  dmaSrc23;
//    Net input  dmaSrc24;
//    Net input  dmaSrc25;
//    Net input  dmaSrc26;
//    Net input  dmaSrc27;
//    Net input  dmaSrc28;
//    Net input  dmaSrc29;
//    Net input  dmaSrc30;
//    Net input  dmaSrc31;
//    Net input  dmaSrc32;
//    Net input  dmaSrc33;
//    Net input  dmaSrc34;
//    Net input  dmaSrc35;
//    Net input  dmaSrc36;
//    Net input  dmaSrc37;
//    Net input  dmaSrc38;
//    Net input  dmaSrc39;
//    Net input  dmaSrc40;
//    Net input  dmaSrc41;
//    Net input  dmaSrc42;
//    Net input  dmaSrc43;
//    Net input  dmaSrc44;
//    Net input  dmaSrc45;
//    Net input  dmaSrc46;
//    Net input  dmaSrc47;
//    Net input  dmaSrc48;
//    Net input  dmaSrc49;
//    Net input  dmaSrc50;
//    Net input  dmaSrc51;
//    Net input  dmaSrc52;
//    Net input  dmaSrc53;
//    Net input  dmaSrc54;
//    Net input  dmaSrc55;
//    Net input  dmaSrc56;
//    Net input  dmaSrc57;
//    Net input  dmaSrc58;
//    Net input  dmaSrc59;
//    Net input  dmaSrc60;
//    Net input  dmaSrc61;
//    Net input  dmaSrc62;
//    Net input  dmaSrc63;
//    Net input  trg1;
//    Net input  trg2;
//    Net input  trg3;
//    Net input  trg4;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class KinetisDMAMUX : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "freescale.ovpworld.org", "peripheral", "KinetisDMAMUX", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetInputPort Reset;
    tlmNetOutputPort eDMARequest;
    tlmNetInputPort dmaSrc0;
    tlmNetInputPort dmaSrc1;
    tlmNetInputPort dmaSrc2;
    tlmNetInputPort dmaSrc3;
    tlmNetInputPort dmaSrc4;
    tlmNetInputPort dmaSrc5;
    tlmNetInputPort dmaSrc6;
    tlmNetInputPort dmaSrc7;
    tlmNetInputPort dmaSrc8;
    tlmNetInputPort dmaSrc9;
    tlmNetInputPort dmaSrc10;
    tlmNetInputPort dmaSrc11;
    tlmNetInputPort dmaSrc12;
    tlmNetInputPort dmaSrc13;
    tlmNetInputPort dmaSrc14;
    tlmNetInputPort dmaSrc15;
    tlmNetInputPort dmaSrc16;
    tlmNetInputPort dmaSrc17;
    tlmNetInputPort dmaSrc18;
    tlmNetInputPort dmaSrc19;
    tlmNetInputPort dmaSrc20;
    tlmNetInputPort dmaSrc21;
    tlmNetInputPort dmaSrc22;
    tlmNetInputPort dmaSrc23;
    tlmNetInputPort dmaSrc24;
    tlmNetInputPort dmaSrc25;
    tlmNetInputPort dmaSrc26;
    tlmNetInputPort dmaSrc27;
    tlmNetInputPort dmaSrc28;
    tlmNetInputPort dmaSrc29;
    tlmNetInputPort dmaSrc30;
    tlmNetInputPort dmaSrc31;
    tlmNetInputPort dmaSrc32;
    tlmNetInputPort dmaSrc33;
    tlmNetInputPort dmaSrc34;
    tlmNetInputPort dmaSrc35;
    tlmNetInputPort dmaSrc36;
    tlmNetInputPort dmaSrc37;
    tlmNetInputPort dmaSrc38;
    tlmNetInputPort dmaSrc39;
    tlmNetInputPort dmaSrc40;
    tlmNetInputPort dmaSrc41;
    tlmNetInputPort dmaSrc42;
    tlmNetInputPort dmaSrc43;
    tlmNetInputPort dmaSrc44;
    tlmNetInputPort dmaSrc45;
    tlmNetInputPort dmaSrc46;
    tlmNetInputPort dmaSrc47;
    tlmNetInputPort dmaSrc48;
    tlmNetInputPort dmaSrc49;
    tlmNetInputPort dmaSrc50;
    tlmNetInputPort dmaSrc51;
    tlmNetInputPort dmaSrc52;
    tlmNetInputPort dmaSrc53;
    tlmNetInputPort dmaSrc54;
    tlmNetInputPort dmaSrc55;
    tlmNetInputPort dmaSrc56;
    tlmNetInputPort dmaSrc57;
    tlmNetInputPort dmaSrc58;
    tlmNetInputPort dmaSrc59;
    tlmNetInputPort dmaSrc60;
    tlmNetInputPort dmaSrc61;
    tlmNetInputPort dmaSrc62;
    tlmNetInputPort dmaSrc63;
    tlmNetInputPort trg1;
    tlmNetInputPort trg2;
    tlmNetInputPort trg3;
    tlmNetInputPort trg4;

    KinetisDMAMUX(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x1000) // static
        , Reset(parent, this, "Reset")
        , eDMARequest(parent, this, "eDMARequest")
        , dmaSrc0(parent, this, "dmaSrc0")
        , dmaSrc1(parent, this, "dmaSrc1")
        , dmaSrc2(parent, this, "dmaSrc2")
        , dmaSrc3(parent, this, "dmaSrc3")
        , dmaSrc4(parent, this, "dmaSrc4")
        , dmaSrc5(parent, this, "dmaSrc5")
        , dmaSrc6(parent, this, "dmaSrc6")
        , dmaSrc7(parent, this, "dmaSrc7")
        , dmaSrc8(parent, this, "dmaSrc8")
        , dmaSrc9(parent, this, "dmaSrc9")
        , dmaSrc10(parent, this, "dmaSrc10")
        , dmaSrc11(parent, this, "dmaSrc11")
        , dmaSrc12(parent, this, "dmaSrc12")
        , dmaSrc13(parent, this, "dmaSrc13")
        , dmaSrc14(parent, this, "dmaSrc14")
        , dmaSrc15(parent, this, "dmaSrc15")
        , dmaSrc16(parent, this, "dmaSrc16")
        , dmaSrc17(parent, this, "dmaSrc17")
        , dmaSrc18(parent, this, "dmaSrc18")
        , dmaSrc19(parent, this, "dmaSrc19")
        , dmaSrc20(parent, this, "dmaSrc20")
        , dmaSrc21(parent, this, "dmaSrc21")
        , dmaSrc22(parent, this, "dmaSrc22")
        , dmaSrc23(parent, this, "dmaSrc23")
        , dmaSrc24(parent, this, "dmaSrc24")
        , dmaSrc25(parent, this, "dmaSrc25")
        , dmaSrc26(parent, this, "dmaSrc26")
        , dmaSrc27(parent, this, "dmaSrc27")
        , dmaSrc28(parent, this, "dmaSrc28")
        , dmaSrc29(parent, this, "dmaSrc29")
        , dmaSrc30(parent, this, "dmaSrc30")
        , dmaSrc31(parent, this, "dmaSrc31")
        , dmaSrc32(parent, this, "dmaSrc32")
        , dmaSrc33(parent, this, "dmaSrc33")
        , dmaSrc34(parent, this, "dmaSrc34")
        , dmaSrc35(parent, this, "dmaSrc35")
        , dmaSrc36(parent, this, "dmaSrc36")
        , dmaSrc37(parent, this, "dmaSrc37")
        , dmaSrc38(parent, this, "dmaSrc38")
        , dmaSrc39(parent, this, "dmaSrc39")
        , dmaSrc40(parent, this, "dmaSrc40")
        , dmaSrc41(parent, this, "dmaSrc41")
        , dmaSrc42(parent, this, "dmaSrc42")
        , dmaSrc43(parent, this, "dmaSrc43")
        , dmaSrc44(parent, this, "dmaSrc44")
        , dmaSrc45(parent, this, "dmaSrc45")
        , dmaSrc46(parent, this, "dmaSrc46")
        , dmaSrc47(parent, this, "dmaSrc47")
        , dmaSrc48(parent, this, "dmaSrc48")
        , dmaSrc49(parent, this, "dmaSrc49")
        , dmaSrc50(parent, this, "dmaSrc50")
        , dmaSrc51(parent, this, "dmaSrc51")
        , dmaSrc52(parent, this, "dmaSrc52")
        , dmaSrc53(parent, this, "dmaSrc53")
        , dmaSrc54(parent, this, "dmaSrc54")
        , dmaSrc55(parent, this, "dmaSrc55")
        , dmaSrc56(parent, this, "dmaSrc56")
        , dmaSrc57(parent, this, "dmaSrc57")
        , dmaSrc58(parent, this, "dmaSrc58")
        , dmaSrc59(parent, this, "dmaSrc59")
        , dmaSrc60(parent, this, "dmaSrc60")
        , dmaSrc61(parent, this, "dmaSrc61")
        , dmaSrc62(parent, this, "dmaSrc62")
        , dmaSrc63(parent, this, "dmaSrc63")
        , trg1(parent, this, "trg1")
        , trg2(parent, this, "trg2")
        , trg3(parent, this, "trg3")
        , trg4(parent, this, "trg4")
    {
    }

    KinetisDMAMUX(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x1000) // static
        , Reset(parent, this, "Reset")
        , eDMARequest(parent, this, "eDMARequest")
        , dmaSrc0(parent, this, "dmaSrc0")
        , dmaSrc1(parent, this, "dmaSrc1")
        , dmaSrc2(parent, this, "dmaSrc2")
        , dmaSrc3(parent, this, "dmaSrc3")
        , dmaSrc4(parent, this, "dmaSrc4")
        , dmaSrc5(parent, this, "dmaSrc5")
        , dmaSrc6(parent, this, "dmaSrc6")
        , dmaSrc7(parent, this, "dmaSrc7")
        , dmaSrc8(parent, this, "dmaSrc8")
        , dmaSrc9(parent, this, "dmaSrc9")
        , dmaSrc10(parent, this, "dmaSrc10")
        , dmaSrc11(parent, this, "dmaSrc11")
        , dmaSrc12(parent, this, "dmaSrc12")
        , dmaSrc13(parent, this, "dmaSrc13")
        , dmaSrc14(parent, this, "dmaSrc14")
        , dmaSrc15(parent, this, "dmaSrc15")
        , dmaSrc16(parent, this, "dmaSrc16")
        , dmaSrc17(parent, this, "dmaSrc17")
        , dmaSrc18(parent, this, "dmaSrc18")
        , dmaSrc19(parent, this, "dmaSrc19")
        , dmaSrc20(parent, this, "dmaSrc20")
        , dmaSrc21(parent, this, "dmaSrc21")
        , dmaSrc22(parent, this, "dmaSrc22")
        , dmaSrc23(parent, this, "dmaSrc23")
        , dmaSrc24(parent, this, "dmaSrc24")
        , dmaSrc25(parent, this, "dmaSrc25")
        , dmaSrc26(parent, this, "dmaSrc26")
        , dmaSrc27(parent, this, "dmaSrc27")
        , dmaSrc28(parent, this, "dmaSrc28")
        , dmaSrc29(parent, this, "dmaSrc29")
        , dmaSrc30(parent, this, "dmaSrc30")
        , dmaSrc31(parent, this, "dmaSrc31")
        , dmaSrc32(parent, this, "dmaSrc32")
        , dmaSrc33(parent, this, "dmaSrc33")
        , dmaSrc34(parent, this, "dmaSrc34")
        , dmaSrc35(parent, this, "dmaSrc35")
        , dmaSrc36(parent, this, "dmaSrc36")
        , dmaSrc37(parent, this, "dmaSrc37")
        , dmaSrc38(parent, this, "dmaSrc38")
        , dmaSrc39(parent, this, "dmaSrc39")
        , dmaSrc40(parent, this, "dmaSrc40")
        , dmaSrc41(parent, this, "dmaSrc41")
        , dmaSrc42(parent, this, "dmaSrc42")
        , dmaSrc43(parent, this, "dmaSrc43")
        , dmaSrc44(parent, this, "dmaSrc44")
        , dmaSrc45(parent, this, "dmaSrc45")
        , dmaSrc46(parent, this, "dmaSrc46")
        , dmaSrc47(parent, this, "dmaSrc47")
        , dmaSrc48(parent, this, "dmaSrc48")
        , dmaSrc49(parent, this, "dmaSrc49")
        , dmaSrc50(parent, this, "dmaSrc50")
        , dmaSrc51(parent, this, "dmaSrc51")
        , dmaSrc52(parent, this, "dmaSrc52")
        , dmaSrc53(parent, this, "dmaSrc53")
        , dmaSrc54(parent, this, "dmaSrc54")
        , dmaSrc55(parent, this, "dmaSrc55")
        , dmaSrc56(parent, this, "dmaSrc56")
        , dmaSrc57(parent, this, "dmaSrc57")
        , dmaSrc58(parent, this, "dmaSrc58")
        , dmaSrc59(parent, this, "dmaSrc59")
        , dmaSrc60(parent, this, "dmaSrc60")
        , dmaSrc61(parent, this, "dmaSrc61")
        , dmaSrc62(parent, this, "dmaSrc62")
        , dmaSrc63(parent, this, "dmaSrc63")
        , trg1(parent, this, "trg1")
        , trg2(parent, this, "trg2")
        , trg3(parent, this, "trg3")
        , trg4(parent, this, "trg4")
    {
    }

}; /* class KinetisDMAMUX */


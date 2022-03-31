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
//    Net input  irqS2;
//    Net input  irqS3;
//    Net input  irqS4;
//    Net input  irqS5;
//    Net input  irqS6;
//    Net input  irqS7;
//    Net input  irqS8;
//    Net input  irqS9;
//    Net input  irqS10;
//    Net input  irqS11;
//    Net input  irqS12;
//    Net input  irqS13;
//    Net input  irqS14;
//    Net input  irqS15;
//    Net input  irqS16;
//    Net input  irqS17;
//    Net input  irqS18;
//    Net input  irqS19;
//    Net input  irqS20;
//    Net input  irqS21;
//    Net input  irqS22;
//    Net input  irqS23;
//    Net input  irqS24;
//    Net input  irqS25;
//    Net input  irqS26;
//    Net input  irqS27;
//    Net input  irqS28;
//    Net input  irqS29;
//    Net input  irqS30;
//    Net input  irqS31;
//    Net input  irqS32;
//    Net input  irqS33;
//    Net input  irqS34;
//    Net input  irqS35;
//    Net input  irqS36;
//    Net input  irqS37;
//    Net input  irqS38;
//    Net input  irqS39;
//    Net input  irqS40;
//    Net input  irqS41;
//    Net input  irqS42;
//    Net input  irqS43;
//    Net input  irqS44;
//    Net input  irqS45;
//    Net input  irqS46;
//    Net input  irqS47;
//    Net input  irqS48;
//    Net input  irqS49;
//    Net input  irqS50;
//    Net input  irqS51;
//    Net input  irqS52;
//    Net input  irqS53;
//    Net input  irqS54;
//    Net input  irqS55;
//    Net input  irqS56;
//    Net input  irqS57;
//    Net input  irqS58;
//    Net input  irqS59;
//    Net input  irqS60;
//    Net input  irqS61;
//    Net input  irqS62;
//    Net input  irqS63;
//    Net output  t0_eiid;
//    Net input  t0_eiack;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class NCEPLIC100 : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "andes.ovpworld.org", "peripheral", "NCEPLIC100", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort port0;
    tlmNetInputPort reset;
    tlmNetInputPort irqS1;
    tlmNetOutputPort irqT0;
    tlmNetInputPort irqS2;
    tlmNetInputPort irqS3;
    tlmNetInputPort irqS4;
    tlmNetInputPort irqS5;
    tlmNetInputPort irqS6;
    tlmNetInputPort irqS7;
    tlmNetInputPort irqS8;
    tlmNetInputPort irqS9;
    tlmNetInputPort irqS10;
    tlmNetInputPort irqS11;
    tlmNetInputPort irqS12;
    tlmNetInputPort irqS13;
    tlmNetInputPort irqS14;
    tlmNetInputPort irqS15;
    tlmNetInputPort irqS16;
    tlmNetInputPort irqS17;
    tlmNetInputPort irqS18;
    tlmNetInputPort irqS19;
    tlmNetInputPort irqS20;
    tlmNetInputPort irqS21;
    tlmNetInputPort irqS22;
    tlmNetInputPort irqS23;
    tlmNetInputPort irqS24;
    tlmNetInputPort irqS25;
    tlmNetInputPort irqS26;
    tlmNetInputPort irqS27;
    tlmNetInputPort irqS28;
    tlmNetInputPort irqS29;
    tlmNetInputPort irqS30;
    tlmNetInputPort irqS31;
    tlmNetInputPort irqS32;
    tlmNetInputPort irqS33;
    tlmNetInputPort irqS34;
    tlmNetInputPort irqS35;
    tlmNetInputPort irqS36;
    tlmNetInputPort irqS37;
    tlmNetInputPort irqS38;
    tlmNetInputPort irqS39;
    tlmNetInputPort irqS40;
    tlmNetInputPort irqS41;
    tlmNetInputPort irqS42;
    tlmNetInputPort irqS43;
    tlmNetInputPort irqS44;
    tlmNetInputPort irqS45;
    tlmNetInputPort irqS46;
    tlmNetInputPort irqS47;
    tlmNetInputPort irqS48;
    tlmNetInputPort irqS49;
    tlmNetInputPort irqS50;
    tlmNetInputPort irqS51;
    tlmNetInputPort irqS52;
    tlmNetInputPort irqS53;
    tlmNetInputPort irqS54;
    tlmNetInputPort irqS55;
    tlmNetInputPort irqS56;
    tlmNetInputPort irqS57;
    tlmNetInputPort irqS58;
    tlmNetInputPort irqS59;
    tlmNetInputPort irqS60;
    tlmNetInputPort irqS61;
    tlmNetInputPort irqS62;
    tlmNetInputPort irqS63;
    tlmNetOutputPort t0_eiid;
    tlmNetInputPort t0_eiack;

    NCEPLIC100(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , port0(parent, this, "port0", 0x400000) // static
        , reset(parent, this, "reset")
        , irqS1(parent, this, "irqS1")
        , irqT0(parent, this, "irqT0")
        , irqS2(parent, this, "irqS2")
        , irqS3(parent, this, "irqS3")
        , irqS4(parent, this, "irqS4")
        , irqS5(parent, this, "irqS5")
        , irqS6(parent, this, "irqS6")
        , irqS7(parent, this, "irqS7")
        , irqS8(parent, this, "irqS8")
        , irqS9(parent, this, "irqS9")
        , irqS10(parent, this, "irqS10")
        , irqS11(parent, this, "irqS11")
        , irqS12(parent, this, "irqS12")
        , irqS13(parent, this, "irqS13")
        , irqS14(parent, this, "irqS14")
        , irqS15(parent, this, "irqS15")
        , irqS16(parent, this, "irqS16")
        , irqS17(parent, this, "irqS17")
        , irqS18(parent, this, "irqS18")
        , irqS19(parent, this, "irqS19")
        , irqS20(parent, this, "irqS20")
        , irqS21(parent, this, "irqS21")
        , irqS22(parent, this, "irqS22")
        , irqS23(parent, this, "irqS23")
        , irqS24(parent, this, "irqS24")
        , irqS25(parent, this, "irqS25")
        , irqS26(parent, this, "irqS26")
        , irqS27(parent, this, "irqS27")
        , irqS28(parent, this, "irqS28")
        , irqS29(parent, this, "irqS29")
        , irqS30(parent, this, "irqS30")
        , irqS31(parent, this, "irqS31")
        , irqS32(parent, this, "irqS32")
        , irqS33(parent, this, "irqS33")
        , irqS34(parent, this, "irqS34")
        , irqS35(parent, this, "irqS35")
        , irqS36(parent, this, "irqS36")
        , irqS37(parent, this, "irqS37")
        , irqS38(parent, this, "irqS38")
        , irqS39(parent, this, "irqS39")
        , irqS40(parent, this, "irqS40")
        , irqS41(parent, this, "irqS41")
        , irqS42(parent, this, "irqS42")
        , irqS43(parent, this, "irqS43")
        , irqS44(parent, this, "irqS44")
        , irqS45(parent, this, "irqS45")
        , irqS46(parent, this, "irqS46")
        , irqS47(parent, this, "irqS47")
        , irqS48(parent, this, "irqS48")
        , irqS49(parent, this, "irqS49")
        , irqS50(parent, this, "irqS50")
        , irqS51(parent, this, "irqS51")
        , irqS52(parent, this, "irqS52")
        , irqS53(parent, this, "irqS53")
        , irqS54(parent, this, "irqS54")
        , irqS55(parent, this, "irqS55")
        , irqS56(parent, this, "irqS56")
        , irqS57(parent, this, "irqS57")
        , irqS58(parent, this, "irqS58")
        , irqS59(parent, this, "irqS59")
        , irqS60(parent, this, "irqS60")
        , irqS61(parent, this, "irqS61")
        , irqS62(parent, this, "irqS62")
        , irqS63(parent, this, "irqS63")
        , t0_eiid(parent, this, "t0_eiid")
        , t0_eiack(parent, this, "t0_eiack")
    {
    }

    NCEPLIC100(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , port0(parent, this, "port0", 0x400000) // static
        , reset(parent, this, "reset")
        , irqS1(parent, this, "irqS1")
        , irqT0(parent, this, "irqT0")
        , irqS2(parent, this, "irqS2")
        , irqS3(parent, this, "irqS3")
        , irqS4(parent, this, "irqS4")
        , irqS5(parent, this, "irqS5")
        , irqS6(parent, this, "irqS6")
        , irqS7(parent, this, "irqS7")
        , irqS8(parent, this, "irqS8")
        , irqS9(parent, this, "irqS9")
        , irqS10(parent, this, "irqS10")
        , irqS11(parent, this, "irqS11")
        , irqS12(parent, this, "irqS12")
        , irqS13(parent, this, "irqS13")
        , irqS14(parent, this, "irqS14")
        , irqS15(parent, this, "irqS15")
        , irqS16(parent, this, "irqS16")
        , irqS17(parent, this, "irqS17")
        , irqS18(parent, this, "irqS18")
        , irqS19(parent, this, "irqS19")
        , irqS20(parent, this, "irqS20")
        , irqS21(parent, this, "irqS21")
        , irqS22(parent, this, "irqS22")
        , irqS23(parent, this, "irqS23")
        , irqS24(parent, this, "irqS24")
        , irqS25(parent, this, "irqS25")
        , irqS26(parent, this, "irqS26")
        , irqS27(parent, this, "irqS27")
        , irqS28(parent, this, "irqS28")
        , irqS29(parent, this, "irqS29")
        , irqS30(parent, this, "irqS30")
        , irqS31(parent, this, "irqS31")
        , irqS32(parent, this, "irqS32")
        , irqS33(parent, this, "irqS33")
        , irqS34(parent, this, "irqS34")
        , irqS35(parent, this, "irqS35")
        , irqS36(parent, this, "irqS36")
        , irqS37(parent, this, "irqS37")
        , irqS38(parent, this, "irqS38")
        , irqS39(parent, this, "irqS39")
        , irqS40(parent, this, "irqS40")
        , irqS41(parent, this, "irqS41")
        , irqS42(parent, this, "irqS42")
        , irqS43(parent, this, "irqS43")
        , irqS44(parent, this, "irqS44")
        , irqS45(parent, this, "irqS45")
        , irqS46(parent, this, "irqS46")
        , irqS47(parent, this, "irqS47")
        , irqS48(parent, this, "irqS48")
        , irqS49(parent, this, "irqS49")
        , irqS50(parent, this, "irqS50")
        , irqS51(parent, this, "irqS51")
        , irqS52(parent, this, "irqS52")
        , irqS53(parent, this, "irqS53")
        , irqS54(parent, this, "irqS54")
        , irqS55(parent, this, "irqS55")
        , irqS56(parent, this, "irqS56")
        , irqS57(parent, this, "irqS57")
        , irqS58(parent, this, "irqS58")
        , irqS59(parent, this, "irqS59")
        , irqS60(parent, this, "irqS60")
        , irqS61(parent, this, "irqS61")
        , irqS62(parent, this, "irqS62")
        , irqS63(parent, this, "irqS63")
        , t0_eiid(parent, this, "t0_eiid")
        , t0_eiack(parent, this, "t0_eiack")
    {
    }

}; /* class NCEPLIC100 */


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
//    Slave Port bp1
//    Net inout  P0;
//    Net inout  P1;
//    Net inout  P2;
//    Net inout  P3;
//    Net inout  P4;
//    Net inout  P5;
//    Net inout  P6;
//    Net inout  P7;
//    Net inout  P8;
//    Net inout  P9;
//    Net inout  P10;
//    Net inout  P11;
//    Net inout  P12;
//    Net inout  P13;
//    Net inout  P14;
//    Net inout  P15;
//    Net inout  P16;
//    Net inout  P17;
//    Net inout  P18;
//    Net inout  P19;
//    Net inout  P20;
//    Net inout  P21;
//    Net inout  P22;
//    Net inout  P23;
//    Net inout  P24;
//    Net inout  P25;
//    Net inout  P26;
//    Net inout  P27;
//    Net inout  P28;
//    Net inout  P29;
//    Net inout  P30;
//    Net inout  P31;
//    Net output  IRQ;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class ParallelIOController : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "atmel.ovpworld.org", "peripheral", "ParallelIOController", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bp1;
    tlmNetInoutPort P0;
    tlmNetInoutPort P1;
    tlmNetInoutPort P2;
    tlmNetInoutPort P3;
    tlmNetInoutPort P4;
    tlmNetInoutPort P5;
    tlmNetInoutPort P6;
    tlmNetInoutPort P7;
    tlmNetInoutPort P8;
    tlmNetInoutPort P9;
    tlmNetInoutPort P10;
    tlmNetInoutPort P11;
    tlmNetInoutPort P12;
    tlmNetInoutPort P13;
    tlmNetInoutPort P14;
    tlmNetInoutPort P15;
    tlmNetInoutPort P16;
    tlmNetInoutPort P17;
    tlmNetInoutPort P18;
    tlmNetInoutPort P19;
    tlmNetInoutPort P20;
    tlmNetInoutPort P21;
    tlmNetInoutPort P22;
    tlmNetInoutPort P23;
    tlmNetInoutPort P24;
    tlmNetInoutPort P25;
    tlmNetInoutPort P26;
    tlmNetInoutPort P27;
    tlmNetInoutPort P28;
    tlmNetInoutPort P29;
    tlmNetInoutPort P30;
    tlmNetInoutPort P31;
    tlmNetOutputPort IRQ;

    ParallelIOController(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bp1(parent, this, "bp1", 0x4000) // static
        , P0(parent, this, "P0")
        , P1(parent, this, "P1")
        , P2(parent, this, "P2")
        , P3(parent, this, "P3")
        , P4(parent, this, "P4")
        , P5(parent, this, "P5")
        , P6(parent, this, "P6")
        , P7(parent, this, "P7")
        , P8(parent, this, "P8")
        , P9(parent, this, "P9")
        , P10(parent, this, "P10")
        , P11(parent, this, "P11")
        , P12(parent, this, "P12")
        , P13(parent, this, "P13")
        , P14(parent, this, "P14")
        , P15(parent, this, "P15")
        , P16(parent, this, "P16")
        , P17(parent, this, "P17")
        , P18(parent, this, "P18")
        , P19(parent, this, "P19")
        , P20(parent, this, "P20")
        , P21(parent, this, "P21")
        , P22(parent, this, "P22")
        , P23(parent, this, "P23")
        , P24(parent, this, "P24")
        , P25(parent, this, "P25")
        , P26(parent, this, "P26")
        , P27(parent, this, "P27")
        , P28(parent, this, "P28")
        , P29(parent, this, "P29")
        , P30(parent, this, "P30")
        , P31(parent, this, "P31")
        , IRQ(parent, this, "IRQ")
    {
    }

    ParallelIOController(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bp1(parent, this, "bp1", 0x4000) // static
        , P0(parent, this, "P0")
        , P1(parent, this, "P1")
        , P2(parent, this, "P2")
        , P3(parent, this, "P3")
        , P4(parent, this, "P4")
        , P5(parent, this, "P5")
        , P6(parent, this, "P6")
        , P7(parent, this, "P7")
        , P8(parent, this, "P8")
        , P9(parent, this, "P9")
        , P10(parent, this, "P10")
        , P11(parent, this, "P11")
        , P12(parent, this, "P12")
        , P13(parent, this, "P13")
        , P14(parent, this, "P14")
        , P15(parent, this, "P15")
        , P16(parent, this, "P16")
        , P17(parent, this, "P17")
        , P18(parent, this, "P18")
        , P19(parent, this, "P19")
        , P20(parent, this, "P20")
        , P21(parent, this, "P21")
        , P22(parent, this, "P22")
        , P23(parent, this, "P23")
        , P24(parent, this, "P24")
        , P25(parent, this, "P25")
        , P26(parent, this, "P26")
        , P27(parent, this, "P27")
        , P28(parent, this, "P28")
        , P29(parent, this, "P29")
        , P30(parent, this, "P30")
        , P31(parent, this, "P31")
        , IRQ(parent, this, "IRQ")
    {
    }

}; /* class ParallelIOController */


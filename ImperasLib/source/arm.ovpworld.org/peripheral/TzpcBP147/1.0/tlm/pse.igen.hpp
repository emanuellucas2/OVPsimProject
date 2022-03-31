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
//    Net input  resetNet;
//    Net output  TZPCR0SIZE;
//    Net output  TZPCDECPROT0_0;
//    Net output  TZPCDECPROT0_1;
//    Net output  TZPCDECPROT0_2;
//    Net output  TZPCDECPROT0_3;
//    Net output  TZPCDECPROT0_4;
//    Net output  TZPCDECPROT0_5;
//    Net output  TZPCDECPROT0_6;
//    Net output  TZPCDECPROT0_7;
//    Net output  TZPCDECPROT0_8;
//    Net output  TZPCDECPROT0_9;
//    Net output  TZPCDECPROT0_10;
//    Net output  TZPCDECPROT0_11;
//    Net output  TZPCDECPROT0_12;
//    Net output  TZPCDECPROT0_13;
//    Net output  TZPCDECPROT0_14;
//    Net output  TZPCDECPROT0_15;
//    Net output  TZPCDECPROT1_0;
//    Net output  TZPCDECPROT1_1;
//    Net output  TZPCDECPROT1_2;
//    Net output  TZPCDECPROT1_3;
//    Net output  TZPCDECPROT1_4;
//    Net output  TZPCDECPROT1_5;
//    Net output  TZPCDECPROT1_6;
//    Net output  TZPCDECPROT1_7;
//    Net output  TZPCDECPROT1_8;
//    Net output  TZPCDECPROT1_9;
//    Net output  TZPCDECPROT1_10;
//    Net output  TZPCDECPROT1_11;
//    Net output  TZPCDECPROT1_12;
//    Net output  TZPCDECPROT1_13;
//    Net output  TZPCDECPROT1_14;
//    Net output  TZPCDECPROT1_15;
//    Net output  TZPCDECPROT2_0;
//    Net output  TZPCDECPROT2_1;
//    Net output  TZPCDECPROT2_2;
//    Net output  TZPCDECPROT2_3;
//    Net output  TZPCDECPROT2_4;
//    Net output  TZPCDECPROT2_5;
//    Net output  TZPCDECPROT2_6;
//    Net output  TZPCDECPROT2_7;
//    Net output  TZPCDECPROT2_8;
//    Net output  TZPCDECPROT2_9;
//    Net output  TZPCDECPROT2_10;
//    Net output  TZPCDECPROT2_11;
//    Net output  TZPCDECPROT2_12;
//    Net output  TZPCDECPROT2_13;
//    Net output  TZPCDECPROT2_14;
//    Net output  TZPCDECPROT2_15;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class TzpcBP147 : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "arm.ovpworld.org", "peripheral", "TzpcBP147", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetInputPort resetNet;
    tlmNetOutputPort TZPCR0SIZE;
    tlmNetOutputPort TZPCDECPROT0_0;
    tlmNetOutputPort TZPCDECPROT0_1;
    tlmNetOutputPort TZPCDECPROT0_2;
    tlmNetOutputPort TZPCDECPROT0_3;
    tlmNetOutputPort TZPCDECPROT0_4;
    tlmNetOutputPort TZPCDECPROT0_5;
    tlmNetOutputPort TZPCDECPROT0_6;
    tlmNetOutputPort TZPCDECPROT0_7;
    tlmNetOutputPort TZPCDECPROT0_8;
    tlmNetOutputPort TZPCDECPROT0_9;
    tlmNetOutputPort TZPCDECPROT0_10;
    tlmNetOutputPort TZPCDECPROT0_11;
    tlmNetOutputPort TZPCDECPROT0_12;
    tlmNetOutputPort TZPCDECPROT0_13;
    tlmNetOutputPort TZPCDECPROT0_14;
    tlmNetOutputPort TZPCDECPROT0_15;
    tlmNetOutputPort TZPCDECPROT1_0;
    tlmNetOutputPort TZPCDECPROT1_1;
    tlmNetOutputPort TZPCDECPROT1_2;
    tlmNetOutputPort TZPCDECPROT1_3;
    tlmNetOutputPort TZPCDECPROT1_4;
    tlmNetOutputPort TZPCDECPROT1_5;
    tlmNetOutputPort TZPCDECPROT1_6;
    tlmNetOutputPort TZPCDECPROT1_7;
    tlmNetOutputPort TZPCDECPROT1_8;
    tlmNetOutputPort TZPCDECPROT1_9;
    tlmNetOutputPort TZPCDECPROT1_10;
    tlmNetOutputPort TZPCDECPROT1_11;
    tlmNetOutputPort TZPCDECPROT1_12;
    tlmNetOutputPort TZPCDECPROT1_13;
    tlmNetOutputPort TZPCDECPROT1_14;
    tlmNetOutputPort TZPCDECPROT1_15;
    tlmNetOutputPort TZPCDECPROT2_0;
    tlmNetOutputPort TZPCDECPROT2_1;
    tlmNetOutputPort TZPCDECPROT2_2;
    tlmNetOutputPort TZPCDECPROT2_3;
    tlmNetOutputPort TZPCDECPROT2_4;
    tlmNetOutputPort TZPCDECPROT2_5;
    tlmNetOutputPort TZPCDECPROT2_6;
    tlmNetOutputPort TZPCDECPROT2_7;
    tlmNetOutputPort TZPCDECPROT2_8;
    tlmNetOutputPort TZPCDECPROT2_9;
    tlmNetOutputPort TZPCDECPROT2_10;
    tlmNetOutputPort TZPCDECPROT2_11;
    tlmNetOutputPort TZPCDECPROT2_12;
    tlmNetOutputPort TZPCDECPROT2_13;
    tlmNetOutputPort TZPCDECPROT2_14;
    tlmNetOutputPort TZPCDECPROT2_15;

    TzpcBP147(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x1000) // static
        , resetNet(parent, this, "resetNet")
        , TZPCR0SIZE(parent, this, "TZPCR0SIZE")
        , TZPCDECPROT0_0(parent, this, "TZPCDECPROT0_0")
        , TZPCDECPROT0_1(parent, this, "TZPCDECPROT0_1")
        , TZPCDECPROT0_2(parent, this, "TZPCDECPROT0_2")
        , TZPCDECPROT0_3(parent, this, "TZPCDECPROT0_3")
        , TZPCDECPROT0_4(parent, this, "TZPCDECPROT0_4")
        , TZPCDECPROT0_5(parent, this, "TZPCDECPROT0_5")
        , TZPCDECPROT0_6(parent, this, "TZPCDECPROT0_6")
        , TZPCDECPROT0_7(parent, this, "TZPCDECPROT0_7")
        , TZPCDECPROT0_8(parent, this, "TZPCDECPROT0_8")
        , TZPCDECPROT0_9(parent, this, "TZPCDECPROT0_9")
        , TZPCDECPROT0_10(parent, this, "TZPCDECPROT0_10")
        , TZPCDECPROT0_11(parent, this, "TZPCDECPROT0_11")
        , TZPCDECPROT0_12(parent, this, "TZPCDECPROT0_12")
        , TZPCDECPROT0_13(parent, this, "TZPCDECPROT0_13")
        , TZPCDECPROT0_14(parent, this, "TZPCDECPROT0_14")
        , TZPCDECPROT0_15(parent, this, "TZPCDECPROT0_15")
        , TZPCDECPROT1_0(parent, this, "TZPCDECPROT1_0")
        , TZPCDECPROT1_1(parent, this, "TZPCDECPROT1_1")
        , TZPCDECPROT1_2(parent, this, "TZPCDECPROT1_2")
        , TZPCDECPROT1_3(parent, this, "TZPCDECPROT1_3")
        , TZPCDECPROT1_4(parent, this, "TZPCDECPROT1_4")
        , TZPCDECPROT1_5(parent, this, "TZPCDECPROT1_5")
        , TZPCDECPROT1_6(parent, this, "TZPCDECPROT1_6")
        , TZPCDECPROT1_7(parent, this, "TZPCDECPROT1_7")
        , TZPCDECPROT1_8(parent, this, "TZPCDECPROT1_8")
        , TZPCDECPROT1_9(parent, this, "TZPCDECPROT1_9")
        , TZPCDECPROT1_10(parent, this, "TZPCDECPROT1_10")
        , TZPCDECPROT1_11(parent, this, "TZPCDECPROT1_11")
        , TZPCDECPROT1_12(parent, this, "TZPCDECPROT1_12")
        , TZPCDECPROT1_13(parent, this, "TZPCDECPROT1_13")
        , TZPCDECPROT1_14(parent, this, "TZPCDECPROT1_14")
        , TZPCDECPROT1_15(parent, this, "TZPCDECPROT1_15")
        , TZPCDECPROT2_0(parent, this, "TZPCDECPROT2_0")
        , TZPCDECPROT2_1(parent, this, "TZPCDECPROT2_1")
        , TZPCDECPROT2_2(parent, this, "TZPCDECPROT2_2")
        , TZPCDECPROT2_3(parent, this, "TZPCDECPROT2_3")
        , TZPCDECPROT2_4(parent, this, "TZPCDECPROT2_4")
        , TZPCDECPROT2_5(parent, this, "TZPCDECPROT2_5")
        , TZPCDECPROT2_6(parent, this, "TZPCDECPROT2_6")
        , TZPCDECPROT2_7(parent, this, "TZPCDECPROT2_7")
        , TZPCDECPROT2_8(parent, this, "TZPCDECPROT2_8")
        , TZPCDECPROT2_9(parent, this, "TZPCDECPROT2_9")
        , TZPCDECPROT2_10(parent, this, "TZPCDECPROT2_10")
        , TZPCDECPROT2_11(parent, this, "TZPCDECPROT2_11")
        , TZPCDECPROT2_12(parent, this, "TZPCDECPROT2_12")
        , TZPCDECPROT2_13(parent, this, "TZPCDECPROT2_13")
        , TZPCDECPROT2_14(parent, this, "TZPCDECPROT2_14")
        , TZPCDECPROT2_15(parent, this, "TZPCDECPROT2_15")
    {
    }

    TzpcBP147(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x1000) // static
        , resetNet(parent, this, "resetNet")
        , TZPCR0SIZE(parent, this, "TZPCR0SIZE")
        , TZPCDECPROT0_0(parent, this, "TZPCDECPROT0_0")
        , TZPCDECPROT0_1(parent, this, "TZPCDECPROT0_1")
        , TZPCDECPROT0_2(parent, this, "TZPCDECPROT0_2")
        , TZPCDECPROT0_3(parent, this, "TZPCDECPROT0_3")
        , TZPCDECPROT0_4(parent, this, "TZPCDECPROT0_4")
        , TZPCDECPROT0_5(parent, this, "TZPCDECPROT0_5")
        , TZPCDECPROT0_6(parent, this, "TZPCDECPROT0_6")
        , TZPCDECPROT0_7(parent, this, "TZPCDECPROT0_7")
        , TZPCDECPROT0_8(parent, this, "TZPCDECPROT0_8")
        , TZPCDECPROT0_9(parent, this, "TZPCDECPROT0_9")
        , TZPCDECPROT0_10(parent, this, "TZPCDECPROT0_10")
        , TZPCDECPROT0_11(parent, this, "TZPCDECPROT0_11")
        , TZPCDECPROT0_12(parent, this, "TZPCDECPROT0_12")
        , TZPCDECPROT0_13(parent, this, "TZPCDECPROT0_13")
        , TZPCDECPROT0_14(parent, this, "TZPCDECPROT0_14")
        , TZPCDECPROT0_15(parent, this, "TZPCDECPROT0_15")
        , TZPCDECPROT1_0(parent, this, "TZPCDECPROT1_0")
        , TZPCDECPROT1_1(parent, this, "TZPCDECPROT1_1")
        , TZPCDECPROT1_2(parent, this, "TZPCDECPROT1_2")
        , TZPCDECPROT1_3(parent, this, "TZPCDECPROT1_3")
        , TZPCDECPROT1_4(parent, this, "TZPCDECPROT1_4")
        , TZPCDECPROT1_5(parent, this, "TZPCDECPROT1_5")
        , TZPCDECPROT1_6(parent, this, "TZPCDECPROT1_6")
        , TZPCDECPROT1_7(parent, this, "TZPCDECPROT1_7")
        , TZPCDECPROT1_8(parent, this, "TZPCDECPROT1_8")
        , TZPCDECPROT1_9(parent, this, "TZPCDECPROT1_9")
        , TZPCDECPROT1_10(parent, this, "TZPCDECPROT1_10")
        , TZPCDECPROT1_11(parent, this, "TZPCDECPROT1_11")
        , TZPCDECPROT1_12(parent, this, "TZPCDECPROT1_12")
        , TZPCDECPROT1_13(parent, this, "TZPCDECPROT1_13")
        , TZPCDECPROT1_14(parent, this, "TZPCDECPROT1_14")
        , TZPCDECPROT1_15(parent, this, "TZPCDECPROT1_15")
        , TZPCDECPROT2_0(parent, this, "TZPCDECPROT2_0")
        , TZPCDECPROT2_1(parent, this, "TZPCDECPROT2_1")
        , TZPCDECPROT2_2(parent, this, "TZPCDECPROT2_2")
        , TZPCDECPROT2_3(parent, this, "TZPCDECPROT2_3")
        , TZPCDECPROT2_4(parent, this, "TZPCDECPROT2_4")
        , TZPCDECPROT2_5(parent, this, "TZPCDECPROT2_5")
        , TZPCDECPROT2_6(parent, this, "TZPCDECPROT2_6")
        , TZPCDECPROT2_7(parent, this, "TZPCDECPROT2_7")
        , TZPCDECPROT2_8(parent, this, "TZPCDECPROT2_8")
        , TZPCDECPROT2_9(parent, this, "TZPCDECPROT2_9")
        , TZPCDECPROT2_10(parent, this, "TZPCDECPROT2_10")
        , TZPCDECPROT2_11(parent, this, "TZPCDECPROT2_11")
        , TZPCDECPROT2_12(parent, this, "TZPCDECPROT2_12")
        , TZPCDECPROT2_13(parent, this, "TZPCDECPROT2_13")
        , TZPCDECPROT2_14(parent, this, "TZPCDECPROT2_14")
        , TZPCDECPROT2_15(parent, this, "TZPCDECPROT2_15")
    {
    }

}; /* class TzpcBP147 */


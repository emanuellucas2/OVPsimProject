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
//    Net input  reset;
//    Net output  intOut_0;
//    Net output  intOut_1;
//    Net output  intOut_2;
//    Net output  intOut_3;
//    Net output  intOut_4;
//    Net output  intOut_5;
//    Net output  intOut_6;
//    Net output  intOut_7;
//    Net output  intOut_8;
//    Net output  intOut_9;
//    Net output  intOut_10;
//    Net output  intOut_11;
//    Net output  intOut_12;
//    Net output  intOut_13;
//    Net output  intOut_14;
//    Net output  intOut_15;
//    Net output  intOut_16;
//    Net output  intOut_17;
//    Net output  intOut_18;
//    Net output  intOut_19;
//    Net output  intOut_20;
//    Net output  intOut_21;
//    Net output  intOut_22;
//    Net output  intOut_23;
//    Net output  intOut_24;
//    Net output  intOut_25;
//    Net output  intOut_26;
//    Net output  intOut_27;
//    Net output  intOut_28;
//    Net output  intOut_29;
//    Net output  intOut_30;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class NCEPLMT100 : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "andes.ovpworld.org", "peripheral", "NCEPLMT100", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetInputPort reset;
    tlmNetOutputPort intOut_0;
    tlmNetOutputPort intOut_1;
    tlmNetOutputPort intOut_2;
    tlmNetOutputPort intOut_3;
    tlmNetOutputPort intOut_4;
    tlmNetOutputPort intOut_5;
    tlmNetOutputPort intOut_6;
    tlmNetOutputPort intOut_7;
    tlmNetOutputPort intOut_8;
    tlmNetOutputPort intOut_9;
    tlmNetOutputPort intOut_10;
    tlmNetOutputPort intOut_11;
    tlmNetOutputPort intOut_12;
    tlmNetOutputPort intOut_13;
    tlmNetOutputPort intOut_14;
    tlmNetOutputPort intOut_15;
    tlmNetOutputPort intOut_16;
    tlmNetOutputPort intOut_17;
    tlmNetOutputPort intOut_18;
    tlmNetOutputPort intOut_19;
    tlmNetOutputPort intOut_20;
    tlmNetOutputPort intOut_21;
    tlmNetOutputPort intOut_22;
    tlmNetOutputPort intOut_23;
    tlmNetOutputPort intOut_24;
    tlmNetOutputPort intOut_25;
    tlmNetOutputPort intOut_26;
    tlmNetOutputPort intOut_27;
    tlmNetOutputPort intOut_28;
    tlmNetOutputPort intOut_29;
    tlmNetOutputPort intOut_30;

    NCEPLMT100(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x100) // static
        , reset(parent, this, "reset")
        , intOut_0(parent, this, "intOut_0")
        , intOut_1(parent, this, "intOut_1")
        , intOut_2(parent, this, "intOut_2")
        , intOut_3(parent, this, "intOut_3")
        , intOut_4(parent, this, "intOut_4")
        , intOut_5(parent, this, "intOut_5")
        , intOut_6(parent, this, "intOut_6")
        , intOut_7(parent, this, "intOut_7")
        , intOut_8(parent, this, "intOut_8")
        , intOut_9(parent, this, "intOut_9")
        , intOut_10(parent, this, "intOut_10")
        , intOut_11(parent, this, "intOut_11")
        , intOut_12(parent, this, "intOut_12")
        , intOut_13(parent, this, "intOut_13")
        , intOut_14(parent, this, "intOut_14")
        , intOut_15(parent, this, "intOut_15")
        , intOut_16(parent, this, "intOut_16")
        , intOut_17(parent, this, "intOut_17")
        , intOut_18(parent, this, "intOut_18")
        , intOut_19(parent, this, "intOut_19")
        , intOut_20(parent, this, "intOut_20")
        , intOut_21(parent, this, "intOut_21")
        , intOut_22(parent, this, "intOut_22")
        , intOut_23(parent, this, "intOut_23")
        , intOut_24(parent, this, "intOut_24")
        , intOut_25(parent, this, "intOut_25")
        , intOut_26(parent, this, "intOut_26")
        , intOut_27(parent, this, "intOut_27")
        , intOut_28(parent, this, "intOut_28")
        , intOut_29(parent, this, "intOut_29")
        , intOut_30(parent, this, "intOut_30")
    {
    }

    NCEPLMT100(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x100) // static
        , reset(parent, this, "reset")
        , intOut_0(parent, this, "intOut_0")
        , intOut_1(parent, this, "intOut_1")
        , intOut_2(parent, this, "intOut_2")
        , intOut_3(parent, this, "intOut_3")
        , intOut_4(parent, this, "intOut_4")
        , intOut_5(parent, this, "intOut_5")
        , intOut_6(parent, this, "intOut_6")
        , intOut_7(parent, this, "intOut_7")
        , intOut_8(parent, this, "intOut_8")
        , intOut_9(parent, this, "intOut_9")
        , intOut_10(parent, this, "intOut_10")
        , intOut_11(parent, this, "intOut_11")
        , intOut_12(parent, this, "intOut_12")
        , intOut_13(parent, this, "intOut_13")
        , intOut_14(parent, this, "intOut_14")
        , intOut_15(parent, this, "intOut_15")
        , intOut_16(parent, this, "intOut_16")
        , intOut_17(parent, this, "intOut_17")
        , intOut_18(parent, this, "intOut_18")
        , intOut_19(parent, this, "intOut_19")
        , intOut_20(parent, this, "intOut_20")
        , intOut_21(parent, this, "intOut_21")
        , intOut_22(parent, this, "intOut_22")
        , intOut_23(parent, this, "intOut_23")
        , intOut_24(parent, this, "intOut_24")
        , intOut_25(parent, this, "intOut_25")
        , intOut_26(parent, this, "intOut_26")
        , intOut_27(parent, this, "intOut_27")
        , intOut_28(parent, this, "intOut_28")
        , intOut_29(parent, this, "intOut_29")
        , intOut_30(parent, this, "intOut_30")
    {
    }

}; /* class NCEPLMT100 */


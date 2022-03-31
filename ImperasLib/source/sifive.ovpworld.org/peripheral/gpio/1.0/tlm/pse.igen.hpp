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
//    Net output  intOut0;
//    Net output  intOut1;
//    Net output  intOut2;
//    Net output  intOut3;
//    Net output  intOut4;
//    Net output  intOut5;
//    Net output  intOut6;
//    Net output  intOut7;
//    Net output  intOut8;
//    Net output  intOut9;
//    Net output  intOut10;
//    Net output  intOut11;
//    Net output  intOut12;
//    Net output  intOut13;
//    Net output  intOut14;
//    Net output  intOut15;
//    Net inout  gpios0;
//    Net inout  gpios1;
//    Net inout  gpios2;
//    Net inout  gpios3;
//    Net inout  gpios4;
//    Net inout  gpios5;
//    Net inout  gpios6;
//    Net inout  gpios7;
//    Net inout  gpios8;
//    Net inout  gpios9;
//    Net inout  gpios10;
//    Net inout  gpios11;
//    Net inout  gpios12;
//    Net inout  gpios13;
//    Net inout  gpios14;
//    Net inout  gpios15;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class gpio : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "sifive.ovpworld.org", "peripheral", "gpio", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetInputPort resetNet;
    tlmNetOutputPort intOut0;
    tlmNetOutputPort intOut1;
    tlmNetOutputPort intOut2;
    tlmNetOutputPort intOut3;
    tlmNetOutputPort intOut4;
    tlmNetOutputPort intOut5;
    tlmNetOutputPort intOut6;
    tlmNetOutputPort intOut7;
    tlmNetOutputPort intOut8;
    tlmNetOutputPort intOut9;
    tlmNetOutputPort intOut10;
    tlmNetOutputPort intOut11;
    tlmNetOutputPort intOut12;
    tlmNetOutputPort intOut13;
    tlmNetOutputPort intOut14;
    tlmNetOutputPort intOut15;
    tlmNetInoutPort gpios0;
    tlmNetInoutPort gpios1;
    tlmNetInoutPort gpios2;
    tlmNetInoutPort gpios3;
    tlmNetInoutPort gpios4;
    tlmNetInoutPort gpios5;
    tlmNetInoutPort gpios6;
    tlmNetInoutPort gpios7;
    tlmNetInoutPort gpios8;
    tlmNetInoutPort gpios9;
    tlmNetInoutPort gpios10;
    tlmNetInoutPort gpios11;
    tlmNetInoutPort gpios12;
    tlmNetInoutPort gpios13;
    tlmNetInoutPort gpios14;
    tlmNetInoutPort gpios15;

    gpio(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x1000) // static
        , resetNet(parent, this, "resetNet")
        , intOut0(parent, this, "intOut0")
        , intOut1(parent, this, "intOut1")
        , intOut2(parent, this, "intOut2")
        , intOut3(parent, this, "intOut3")
        , intOut4(parent, this, "intOut4")
        , intOut5(parent, this, "intOut5")
        , intOut6(parent, this, "intOut6")
        , intOut7(parent, this, "intOut7")
        , intOut8(parent, this, "intOut8")
        , intOut9(parent, this, "intOut9")
        , intOut10(parent, this, "intOut10")
        , intOut11(parent, this, "intOut11")
        , intOut12(parent, this, "intOut12")
        , intOut13(parent, this, "intOut13")
        , intOut14(parent, this, "intOut14")
        , intOut15(parent, this, "intOut15")
        , gpios0(parent, this, "gpios0")
        , gpios1(parent, this, "gpios1")
        , gpios2(parent, this, "gpios2")
        , gpios3(parent, this, "gpios3")
        , gpios4(parent, this, "gpios4")
        , gpios5(parent, this, "gpios5")
        , gpios6(parent, this, "gpios6")
        , gpios7(parent, this, "gpios7")
        , gpios8(parent, this, "gpios8")
        , gpios9(parent, this, "gpios9")
        , gpios10(parent, this, "gpios10")
        , gpios11(parent, this, "gpios11")
        , gpios12(parent, this, "gpios12")
        , gpios13(parent, this, "gpios13")
        , gpios14(parent, this, "gpios14")
        , gpios15(parent, this, "gpios15")
    {
    }

    gpio(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x1000) // static
        , resetNet(parent, this, "resetNet")
        , intOut0(parent, this, "intOut0")
        , intOut1(parent, this, "intOut1")
        , intOut2(parent, this, "intOut2")
        , intOut3(parent, this, "intOut3")
        , intOut4(parent, this, "intOut4")
        , intOut5(parent, this, "intOut5")
        , intOut6(parent, this, "intOut6")
        , intOut7(parent, this, "intOut7")
        , intOut8(parent, this, "intOut8")
        , intOut9(parent, this, "intOut9")
        , intOut10(parent, this, "intOut10")
        , intOut11(parent, this, "intOut11")
        , intOut12(parent, this, "intOut12")
        , intOut13(parent, this, "intOut13")
        , intOut14(parent, this, "intOut14")
        , intOut15(parent, this, "intOut15")
        , gpios0(parent, this, "gpios0")
        , gpios1(parent, this, "gpios1")
        , gpios2(parent, this, "gpios2")
        , gpios3(parent, this, "gpios3")
        , gpios4(parent, this, "gpios4")
        , gpios5(parent, this, "gpios5")
        , gpios6(parent, this, "gpios6")
        , gpios7(parent, this, "gpios7")
        , gpios8(parent, this, "gpios8")
        , gpios9(parent, this, "gpios9")
        , gpios10(parent, this, "gpios10")
        , gpios11(parent, this, "gpios11")
        , gpios12(parent, this, "gpios12")
        , gpios13(parent, this, "gpios13")
        , gpios14(parent, this, "gpios14")
        , gpios15(parent, this, "gpios15")
    {
    }

}; /* class gpio */


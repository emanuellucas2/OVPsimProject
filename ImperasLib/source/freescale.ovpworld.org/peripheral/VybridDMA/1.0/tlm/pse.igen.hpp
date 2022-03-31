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
//    Master Port MREAD
//    Master Port MWRITE
//    Slave Port bport1
//    Net input  Reset;
//    Net input  eDMARequest;
//    Net output  eDMADone;
//    Net output  errorInterrupt;
//    Net output  dmaInterrupt_ch0;
//    Net output  dmaInterrupt_ch1;
//    Net output  dmaInterrupt_ch2;
//    Net output  dmaInterrupt_ch3;
//    Net output  dmaInterrupt_ch4;
//    Net output  dmaInterrupt_ch5;
//    Net output  dmaInterrupt_ch6;
//    Net output  dmaInterrupt_ch7;
//    Net output  dmaInterrupt_ch8;
//    Net output  dmaInterrupt_ch9;
//    Net output  dmaInterrupt_ch10;
//    Net output  dmaInterrupt_ch11;
//    Net output  dmaInterrupt_ch12;
//    Net output  dmaInterrupt_ch13;
//    Net output  dmaInterrupt_ch14;
//    Net output  dmaInterrupt_ch15;
//    Net output  dmaInterrupt_ch16;
//    Net output  dmaInterrupt_ch17;
//    Net output  dmaInterrupt_ch18;
//    Net output  dmaInterrupt_ch19;
//    Net output  dmaInterrupt_ch20;
//    Net output  dmaInterrupt_ch21;
//    Net output  dmaInterrupt_ch22;
//    Net output  dmaInterrupt_ch23;
//    Net output  dmaInterrupt_ch24;
//    Net output  dmaInterrupt_ch25;
//    Net output  dmaInterrupt_ch26;
//    Net output  dmaInterrupt_ch27;
//    Net output  dmaInterrupt_ch28;
//    Net output  dmaInterrupt_ch29;
//    Net output  dmaInterrupt_ch30;
//    Net output  dmaInterrupt_ch31;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class VybridDMA : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "freescale.ovpworld.org", "peripheral", "VybridDMA", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmBusMasterPort       MREAD;
    tlmBusMasterPort       MWRITE;
    tlmNetInputPort Reset;
    tlmNetInputPort eDMARequest;
    tlmNetOutputPort eDMADone;
    tlmNetOutputPort errorInterrupt;
    tlmNetOutputPort dmaInterrupt_ch0;
    tlmNetOutputPort dmaInterrupt_ch1;
    tlmNetOutputPort dmaInterrupt_ch2;
    tlmNetOutputPort dmaInterrupt_ch3;
    tlmNetOutputPort dmaInterrupt_ch4;
    tlmNetOutputPort dmaInterrupt_ch5;
    tlmNetOutputPort dmaInterrupt_ch6;
    tlmNetOutputPort dmaInterrupt_ch7;
    tlmNetOutputPort dmaInterrupt_ch8;
    tlmNetOutputPort dmaInterrupt_ch9;
    tlmNetOutputPort dmaInterrupt_ch10;
    tlmNetOutputPort dmaInterrupt_ch11;
    tlmNetOutputPort dmaInterrupt_ch12;
    tlmNetOutputPort dmaInterrupt_ch13;
    tlmNetOutputPort dmaInterrupt_ch14;
    tlmNetOutputPort dmaInterrupt_ch15;
    tlmNetOutputPort dmaInterrupt_ch16;
    tlmNetOutputPort dmaInterrupt_ch17;
    tlmNetOutputPort dmaInterrupt_ch18;
    tlmNetOutputPort dmaInterrupt_ch19;
    tlmNetOutputPort dmaInterrupt_ch20;
    tlmNetOutputPort dmaInterrupt_ch21;
    tlmNetOutputPort dmaInterrupt_ch22;
    tlmNetOutputPort dmaInterrupt_ch23;
    tlmNetOutputPort dmaInterrupt_ch24;
    tlmNetOutputPort dmaInterrupt_ch25;
    tlmNetOutputPort dmaInterrupt_ch26;
    tlmNetOutputPort dmaInterrupt_ch27;
    tlmNetOutputPort dmaInterrupt_ch28;
    tlmNetOutputPort dmaInterrupt_ch29;
    tlmNetOutputPort dmaInterrupt_ch30;
    tlmNetOutputPort dmaInterrupt_ch31;

    VybridDMA(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x2000) // static
        , MREAD(parent, this, "MREAD", 32)
        , MWRITE(parent, this, "MWRITE", 32)
        , Reset(parent, this, "Reset")
        , eDMARequest(parent, this, "eDMARequest")
        , eDMADone(parent, this, "eDMADone")
        , errorInterrupt(parent, this, "errorInterrupt")
        , dmaInterrupt_ch0(parent, this, "dmaInterrupt_ch0")
        , dmaInterrupt_ch1(parent, this, "dmaInterrupt_ch1")
        , dmaInterrupt_ch2(parent, this, "dmaInterrupt_ch2")
        , dmaInterrupt_ch3(parent, this, "dmaInterrupt_ch3")
        , dmaInterrupt_ch4(parent, this, "dmaInterrupt_ch4")
        , dmaInterrupt_ch5(parent, this, "dmaInterrupt_ch5")
        , dmaInterrupt_ch6(parent, this, "dmaInterrupt_ch6")
        , dmaInterrupt_ch7(parent, this, "dmaInterrupt_ch7")
        , dmaInterrupt_ch8(parent, this, "dmaInterrupt_ch8")
        , dmaInterrupt_ch9(parent, this, "dmaInterrupt_ch9")
        , dmaInterrupt_ch10(parent, this, "dmaInterrupt_ch10")
        , dmaInterrupt_ch11(parent, this, "dmaInterrupt_ch11")
        , dmaInterrupt_ch12(parent, this, "dmaInterrupt_ch12")
        , dmaInterrupt_ch13(parent, this, "dmaInterrupt_ch13")
        , dmaInterrupt_ch14(parent, this, "dmaInterrupt_ch14")
        , dmaInterrupt_ch15(parent, this, "dmaInterrupt_ch15")
        , dmaInterrupt_ch16(parent, this, "dmaInterrupt_ch16")
        , dmaInterrupt_ch17(parent, this, "dmaInterrupt_ch17")
        , dmaInterrupt_ch18(parent, this, "dmaInterrupt_ch18")
        , dmaInterrupt_ch19(parent, this, "dmaInterrupt_ch19")
        , dmaInterrupt_ch20(parent, this, "dmaInterrupt_ch20")
        , dmaInterrupt_ch21(parent, this, "dmaInterrupt_ch21")
        , dmaInterrupt_ch22(parent, this, "dmaInterrupt_ch22")
        , dmaInterrupt_ch23(parent, this, "dmaInterrupt_ch23")
        , dmaInterrupt_ch24(parent, this, "dmaInterrupt_ch24")
        , dmaInterrupt_ch25(parent, this, "dmaInterrupt_ch25")
        , dmaInterrupt_ch26(parent, this, "dmaInterrupt_ch26")
        , dmaInterrupt_ch27(parent, this, "dmaInterrupt_ch27")
        , dmaInterrupt_ch28(parent, this, "dmaInterrupt_ch28")
        , dmaInterrupt_ch29(parent, this, "dmaInterrupt_ch29")
        , dmaInterrupt_ch30(parent, this, "dmaInterrupt_ch30")
        , dmaInterrupt_ch31(parent, this, "dmaInterrupt_ch31")
    {
    }

    VybridDMA(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x2000) // static
        , MREAD(parent, this, "MREAD", 32)
        , MWRITE(parent, this, "MWRITE", 32)
        , Reset(parent, this, "Reset")
        , eDMARequest(parent, this, "eDMARequest")
        , eDMADone(parent, this, "eDMADone")
        , errorInterrupt(parent, this, "errorInterrupt")
        , dmaInterrupt_ch0(parent, this, "dmaInterrupt_ch0")
        , dmaInterrupt_ch1(parent, this, "dmaInterrupt_ch1")
        , dmaInterrupt_ch2(parent, this, "dmaInterrupt_ch2")
        , dmaInterrupt_ch3(parent, this, "dmaInterrupt_ch3")
        , dmaInterrupt_ch4(parent, this, "dmaInterrupt_ch4")
        , dmaInterrupt_ch5(parent, this, "dmaInterrupt_ch5")
        , dmaInterrupt_ch6(parent, this, "dmaInterrupt_ch6")
        , dmaInterrupt_ch7(parent, this, "dmaInterrupt_ch7")
        , dmaInterrupt_ch8(parent, this, "dmaInterrupt_ch8")
        , dmaInterrupt_ch9(parent, this, "dmaInterrupt_ch9")
        , dmaInterrupt_ch10(parent, this, "dmaInterrupt_ch10")
        , dmaInterrupt_ch11(parent, this, "dmaInterrupt_ch11")
        , dmaInterrupt_ch12(parent, this, "dmaInterrupt_ch12")
        , dmaInterrupt_ch13(parent, this, "dmaInterrupt_ch13")
        , dmaInterrupt_ch14(parent, this, "dmaInterrupt_ch14")
        , dmaInterrupt_ch15(parent, this, "dmaInterrupt_ch15")
        , dmaInterrupt_ch16(parent, this, "dmaInterrupt_ch16")
        , dmaInterrupt_ch17(parent, this, "dmaInterrupt_ch17")
        , dmaInterrupt_ch18(parent, this, "dmaInterrupt_ch18")
        , dmaInterrupt_ch19(parent, this, "dmaInterrupt_ch19")
        , dmaInterrupt_ch20(parent, this, "dmaInterrupt_ch20")
        , dmaInterrupt_ch21(parent, this, "dmaInterrupt_ch21")
        , dmaInterrupt_ch22(parent, this, "dmaInterrupt_ch22")
        , dmaInterrupt_ch23(parent, this, "dmaInterrupt_ch23")
        , dmaInterrupt_ch24(parent, this, "dmaInterrupt_ch24")
        , dmaInterrupt_ch25(parent, this, "dmaInterrupt_ch25")
        , dmaInterrupt_ch26(parent, this, "dmaInterrupt_ch26")
        , dmaInterrupt_ch27(parent, this, "dmaInterrupt_ch27")
        , dmaInterrupt_ch28(parent, this, "dmaInterrupt_ch28")
        , dmaInterrupt_ch29(parent, this, "dmaInterrupt_ch29")
        , dmaInterrupt_ch30(parent, this, "dmaInterrupt_ch30")
        , dmaInterrupt_ch31(parent, this, "dmaInterrupt_ch31")
    {
    }

    void before_end_of_elaboration() {
        MREAD.bindIfNotBound();
        MWRITE.bindIfNotBound();
    }
}; /* class VybridDMA */


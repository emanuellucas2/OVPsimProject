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
//    Net input  ExtSample;
//    Net input  Vin1;
//    Net input  Vin2;
//    Net input  Input0;
//    Net input  Input1;
//    Net input  Input2;
//    Net input  Input3;
//    Net input  Input4;
//    Net input  Input5;
//    Net input  Input6;
//    Net input  Input7;
//    Net output  DacOutput;
//    Net output  CoutSoc;
//    Net output  Interrupt;
//    Net output  DmaReq;
//    Net output  CmpOPad;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class KinetisCMP : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "freescale.ovpworld.org", "peripheral", "KinetisCMP", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetInputPort Reset;
    tlmNetInputPort ExtSample;
    tlmNetInputPort Vin1;
    tlmNetInputPort Vin2;
    tlmNetInputPort Input0;
    tlmNetInputPort Input1;
    tlmNetInputPort Input2;
    tlmNetInputPort Input3;
    tlmNetInputPort Input4;
    tlmNetInputPort Input5;
    tlmNetInputPort Input6;
    tlmNetInputPort Input7;
    tlmNetOutputPort DacOutput;
    tlmNetOutputPort CoutSoc;
    tlmNetOutputPort Interrupt;
    tlmNetOutputPort DmaReq;
    tlmNetOutputPort CmpOPad;

    KinetisCMP(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x8) // static
        , Reset(parent, this, "Reset")
        , ExtSample(parent, this, "ExtSample")
        , Vin1(parent, this, "Vin1")
        , Vin2(parent, this, "Vin2")
        , Input0(parent, this, "Input0")
        , Input1(parent, this, "Input1")
        , Input2(parent, this, "Input2")
        , Input3(parent, this, "Input3")
        , Input4(parent, this, "Input4")
        , Input5(parent, this, "Input5")
        , Input6(parent, this, "Input6")
        , Input7(parent, this, "Input7")
        , DacOutput(parent, this, "DacOutput")
        , CoutSoc(parent, this, "CoutSoc")
        , Interrupt(parent, this, "Interrupt")
        , DmaReq(parent, this, "DmaReq")
        , CmpOPad(parent, this, "CmpOPad")
    {
    }

    KinetisCMP(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x8) // static
        , Reset(parent, this, "Reset")
        , ExtSample(parent, this, "ExtSample")
        , Vin1(parent, this, "Vin1")
        , Vin2(parent, this, "Vin2")
        , Input0(parent, this, "Input0")
        , Input1(parent, this, "Input1")
        , Input2(parent, this, "Input2")
        , Input3(parent, this, "Input3")
        , Input4(parent, this, "Input4")
        , Input5(parent, this, "Input5")
        , Input6(parent, this, "Input6")
        , Input7(parent, this, "Input7")
        , DacOutput(parent, this, "DacOutput")
        , CoutSoc(parent, this, "CoutSoc")
        , Interrupt(parent, this, "Interrupt")
        , DmaReq(parent, this, "DmaReq")
        , CmpOPad(parent, this, "CmpOPad")
    {
    }

}; /* class KinetisCMP */


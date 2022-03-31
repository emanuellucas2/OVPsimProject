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
//    Net output  irq;
//    Net output  fiq;
//    Net input  ir0;
//    Net input  ir1;
//    Net input  ir2;
//    Net input  ir3;
//    Net input  ir4;
//    Net input  ir5;
//    Net input  ir6;
//    Net input  ir7;
//    Net input  ir8;
//    Net input  ir9;
//    Net input  ir10;
//    Net input  ir11;
//    Net input  ir12;
//    Net input  ir13;
//    Net input  ir14;
//    Net input  ir15;
//    Net input  ir16;
//    Net input  ir17;
//    Net input  ir18;
//    Net input  ir19;
//    Net input  ir20;
//    Net input  ir21;
//    Net input  ir22;
//    Net input  ir23;
//    Net input  ir24;
//    Net input  ir25;
//    Net input  ir26;
//    Net input  ir27;
//    Net input  ir28;
//    Net input  ir29;
//    Net input  ir30;
//    Net input  ir31;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class IntICP : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "arm.ovpworld.org", "peripheral", "IntICP", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetOutputPort irq;
    tlmNetOutputPort fiq;
    tlmNetInputPort ir0;
    tlmNetInputPort ir1;
    tlmNetInputPort ir2;
    tlmNetInputPort ir3;
    tlmNetInputPort ir4;
    tlmNetInputPort ir5;
    tlmNetInputPort ir6;
    tlmNetInputPort ir7;
    tlmNetInputPort ir8;
    tlmNetInputPort ir9;
    tlmNetInputPort ir10;
    tlmNetInputPort ir11;
    tlmNetInputPort ir12;
    tlmNetInputPort ir13;
    tlmNetInputPort ir14;
    tlmNetInputPort ir15;
    tlmNetInputPort ir16;
    tlmNetInputPort ir17;
    tlmNetInputPort ir18;
    tlmNetInputPort ir19;
    tlmNetInputPort ir20;
    tlmNetInputPort ir21;
    tlmNetInputPort ir22;
    tlmNetInputPort ir23;
    tlmNetInputPort ir24;
    tlmNetInputPort ir25;
    tlmNetInputPort ir26;
    tlmNetInputPort ir27;
    tlmNetInputPort ir28;
    tlmNetInputPort ir29;
    tlmNetInputPort ir30;
    tlmNetInputPort ir31;

    IntICP(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x1000) // static
        , irq(parent, this, "irq")
        , fiq(parent, this, "fiq")
        , ir0(parent, this, "ir0")
        , ir1(parent, this, "ir1")
        , ir2(parent, this, "ir2")
        , ir3(parent, this, "ir3")
        , ir4(parent, this, "ir4")
        , ir5(parent, this, "ir5")
        , ir6(parent, this, "ir6")
        , ir7(parent, this, "ir7")
        , ir8(parent, this, "ir8")
        , ir9(parent, this, "ir9")
        , ir10(parent, this, "ir10")
        , ir11(parent, this, "ir11")
        , ir12(parent, this, "ir12")
        , ir13(parent, this, "ir13")
        , ir14(parent, this, "ir14")
        , ir15(parent, this, "ir15")
        , ir16(parent, this, "ir16")
        , ir17(parent, this, "ir17")
        , ir18(parent, this, "ir18")
        , ir19(parent, this, "ir19")
        , ir20(parent, this, "ir20")
        , ir21(parent, this, "ir21")
        , ir22(parent, this, "ir22")
        , ir23(parent, this, "ir23")
        , ir24(parent, this, "ir24")
        , ir25(parent, this, "ir25")
        , ir26(parent, this, "ir26")
        , ir27(parent, this, "ir27")
        , ir28(parent, this, "ir28")
        , ir29(parent, this, "ir29")
        , ir30(parent, this, "ir30")
        , ir31(parent, this, "ir31")
    {
    }

    IntICP(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x1000) // static
        , irq(parent, this, "irq")
        , fiq(parent, this, "fiq")
        , ir0(parent, this, "ir0")
        , ir1(parent, this, "ir1")
        , ir2(parent, this, "ir2")
        , ir3(parent, this, "ir3")
        , ir4(parent, this, "ir4")
        , ir5(parent, this, "ir5")
        , ir6(parent, this, "ir6")
        , ir7(parent, this, "ir7")
        , ir8(parent, this, "ir8")
        , ir9(parent, this, "ir9")
        , ir10(parent, this, "ir10")
        , ir11(parent, this, "ir11")
        , ir12(parent, this, "ir12")
        , ir13(parent, this, "ir13")
        , ir14(parent, this, "ir14")
        , ir15(parent, this, "ir15")
        , ir16(parent, this, "ir16")
        , ir17(parent, this, "ir17")
        , ir18(parent, this, "ir18")
        , ir19(parent, this, "ir19")
        , ir20(parent, this, "ir20")
        , ir21(parent, this, "ir21")
        , ir22(parent, this, "ir22")
        , ir23(parent, this, "ir23")
        , ir24(parent, this, "ir24")
        , ir25(parent, this, "ir25")
        , ir26(parent, this, "ir26")
        , ir27(parent, this, "ir27")
        , ir28(parent, this, "ir28")
        , ir29(parent, this, "ir29")
        , ir30(parent, this, "ir30")
        , ir31(parent, this, "ir31")
    {
    }

}; /* class IntICP */


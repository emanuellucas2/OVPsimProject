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
//    Master Port cascade
//    Slave Port io
//    Slave Port PCIackS
//    Slave Port elcr
//    Net input  ir0;
//    Net input  ir1;
//    Net input  ir2;
//    Net input  ir3;
//    Net input  ir4;
//    Net input  ir5;
//    Net input  ir6;
//    Net input  ir7;
//    Net inout  cas;
//    Net output  intp;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class _8259A : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "intel.ovpworld.org", "peripheral", "8259A", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort io;
    tlmBusSlavePort PCIackS;
    tlmBusSlavePort elcr;
    tlmBusMasterPort       cascade;
    tlmNetInputPort ir0;
    tlmNetInputPort ir1;
    tlmNetInputPort ir2;
    tlmNetInputPort ir3;
    tlmNetInputPort ir4;
    tlmNetInputPort ir5;
    tlmNetInputPort ir6;
    tlmNetInputPort ir7;
    tlmNetInoutPort cas;
    tlmNetOutputPort intp;

    _8259A(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , io(parent, this, "io", 0x2) // static
        , PCIackS(parent, this, "PCIackS", 0x1) // static
        , elcr(parent, this, "elcr", 0x1) // static
        , cascade(parent, this, "cascade", 3)
        , ir0(parent, this, "ir0")
        , ir1(parent, this, "ir1")
        , ir2(parent, this, "ir2")
        , ir3(parent, this, "ir3")
        , ir4(parent, this, "ir4")
        , ir5(parent, this, "ir5")
        , ir6(parent, this, "ir6")
        , ir7(parent, this, "ir7")
        , cas(parent, this, "cas")
        , intp(parent, this, "intp")
    {
    }

    _8259A(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , io(parent, this, "io", 0x2) // static
        , PCIackS(parent, this, "PCIackS", 0x1) // static
        , elcr(parent, this, "elcr", 0x1) // static
        , cascade(parent, this, "cascade", 3)
        , ir0(parent, this, "ir0")
        , ir1(parent, this, "ir1")
        , ir2(parent, this, "ir2")
        , ir3(parent, this, "ir3")
        , ir4(parent, this, "ir4")
        , ir5(parent, this, "ir5")
        , ir6(parent, this, "ir6")
        , ir7(parent, this, "ir7")
        , cas(parent, this, "cas")
        , intp(parent, this, "intp")
    {
    }

    void before_end_of_elaboration() {
        cascade.bindIfNotBound();
    }
}; /* class _8259A */


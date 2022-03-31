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
//    Net output  irq0;
//    Net output  irq1;
//    Net output  irq2;
//    Net output  irq3;
//    Net output  trg0;
//    Net output  trg1;
//    Net output  trg2;
//    Net output  trg3;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class KinetisPIT : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "freescale.ovpworld.org", "peripheral", "KinetisPIT", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetInputPort Reset;
    tlmNetOutputPort irq0;
    tlmNetOutputPort irq1;
    tlmNetOutputPort irq2;
    tlmNetOutputPort irq3;
    tlmNetOutputPort trg0;
    tlmNetOutputPort trg1;
    tlmNetOutputPort trg2;
    tlmNetOutputPort trg3;

    KinetisPIT(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x1000) // static
        , Reset(parent, this, "Reset")
        , irq0(parent, this, "irq0")
        , irq1(parent, this, "irq1")
        , irq2(parent, this, "irq2")
        , irq3(parent, this, "irq3")
        , trg0(parent, this, "trg0")
        , trg1(parent, this, "trg1")
        , trg2(parent, this, "trg2")
        , trg3(parent, this, "trg3")
    {
    }

    KinetisPIT(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x1000) // static
        , Reset(parent, this, "Reset")
        , irq0(parent, this, "irq0")
        , irq1(parent, this, "irq1")
        , irq2(parent, this, "irq2")
        , irq3(parent, this, "irq3")
        , trg0(parent, this, "trg0")
        , trg1(parent, this, "trg1")
        , trg2(parent, this, "trg2")
        , trg3(parent, this, "trg3")
    {
    }

}; /* class KinetisPIT */


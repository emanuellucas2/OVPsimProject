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
//    Net output  IRQ0;
//    Net output  IRQ1;
//    Net output  IRQ2;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class TimerCounter : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "atmel.ovpworld.org", "peripheral", "TimerCounter", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bp1;
    tlmNetOutputPort IRQ0;
    tlmNetOutputPort IRQ1;
    tlmNetOutputPort IRQ2;

    TimerCounter(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bp1(parent, this, "bp1", 0x4000) // static
        , IRQ0(parent, this, "IRQ0")
        , IRQ1(parent, this, "IRQ1")
        , IRQ2(parent, this, "IRQ2")
    {
    }

    TimerCounter(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bp1(parent, this, "bp1", 0x4000) // static
        , IRQ0(parent, this, "IRQ0")
        , IRQ1(parent, this, "IRQ1")
        , IRQ2(parent, this, "IRQ2")
    {
    }

}; /* class TimerCounter */


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
//    Net output  NFIQ;
//    Net output  NIRQ;
//    Net input  FIQ;
//    Net input  SWIRQ;
//    Net input  US0IRQ;
//    Net input  US1IRQ;
//    Net input  TC0IRQ;
//    Net input  TC1IRQ;
//    Net input  TC2IRQ;
//    Net input  WDIRQ;
//    Net input  PIOIRQ;
//    Net input  IRQ0;
//    Net input  IRQ1;
//    Net input  IRQ2;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class AdvancedInterruptController : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "atmel.ovpworld.org", "peripheral", "AdvancedInterruptController", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bp1;
    tlmNetOutputPort NFIQ;
    tlmNetOutputPort NIRQ;
    tlmNetInputPort FIQ;
    tlmNetInputPort SWIRQ;
    tlmNetInputPort US0IRQ;
    tlmNetInputPort US1IRQ;
    tlmNetInputPort TC0IRQ;
    tlmNetInputPort TC1IRQ;
    tlmNetInputPort TC2IRQ;
    tlmNetInputPort WDIRQ;
    tlmNetInputPort PIOIRQ;
    tlmNetInputPort IRQ0;
    tlmNetInputPort IRQ1;
    tlmNetInputPort IRQ2;

    AdvancedInterruptController(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bp1(parent, this, "bp1", 0x1000) // static
        , NFIQ(parent, this, "NFIQ")
        , NIRQ(parent, this, "NIRQ")
        , FIQ(parent, this, "FIQ")
        , SWIRQ(parent, this, "SWIRQ")
        , US0IRQ(parent, this, "US0IRQ")
        , US1IRQ(parent, this, "US1IRQ")
        , TC0IRQ(parent, this, "TC0IRQ")
        , TC1IRQ(parent, this, "TC1IRQ")
        , TC2IRQ(parent, this, "TC2IRQ")
        , WDIRQ(parent, this, "WDIRQ")
        , PIOIRQ(parent, this, "PIOIRQ")
        , IRQ0(parent, this, "IRQ0")
        , IRQ1(parent, this, "IRQ1")
        , IRQ2(parent, this, "IRQ2")
    {
    }

    AdvancedInterruptController(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bp1(parent, this, "bp1", 0x1000) // static
        , NFIQ(parent, this, "NFIQ")
        , NIRQ(parent, this, "NIRQ")
        , FIQ(parent, this, "FIQ")
        , SWIRQ(parent, this, "SWIRQ")
        , US0IRQ(parent, this, "US0IRQ")
        , US1IRQ(parent, this, "US1IRQ")
        , TC0IRQ(parent, this, "TC0IRQ")
        , TC1IRQ(parent, this, "TC1IRQ")
        , TC2IRQ(parent, this, "TC2IRQ")
        , WDIRQ(parent, this, "WDIRQ")
        , PIOIRQ(parent, this, "PIOIRQ")
        , IRQ0(parent, this, "IRQ0")
        , IRQ1(parent, this, "IRQ1")
        , IRQ2(parent, this, "IRQ2")
    {
    }

}; /* class AdvancedInterruptController */


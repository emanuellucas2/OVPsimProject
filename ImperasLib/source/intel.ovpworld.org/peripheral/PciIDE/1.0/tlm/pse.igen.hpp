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
//    Master Port dmaPort
//    Slave Port busPort
//    Slave Port PCIconfig
//    Net output  intOut0;
//    Net output  intOut1;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class PciIDE : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "intel.ovpworld.org", "peripheral", "PciIDE", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusDynamicSlavePort busPort;
    tlmBusDynamicSlavePort PCIconfig;
    tlmBusMasterPort       dmaPort;
    tlmNetOutputPort intOut0;
    tlmNetOutputPort intOut1;

    PciIDE(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , busPort(parent, this, "busPort", 3) // dynamic
        , PCIconfig(parent, this, "PCIconfig", 11) // dynamic
        , dmaPort(parent, this, "dmaPort", 32)
        , intOut0(parent, this, "intOut0")
        , intOut1(parent, this, "intOut1")
    {
    }

    PciIDE(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , busPort(parent, this, "busPort", 3) // dynamic
        , PCIconfig(parent, this, "PCIconfig", 11) // dynamic
        , dmaPort(parent, this, "dmaPort", 32)
        , intOut0(parent, this, "intOut0")
        , intOut1(parent, this, "intOut1")
    {
    }

    void before_end_of_elaboration() {
        dmaPort.bindIfNotBound();
    }
}; /* class PciIDE */


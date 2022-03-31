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
//    Master Port PCIconfigM
//    Master Port PCIackM
//    Slave Port busPort
//    Slave Port PCIconfig
//    Net output  timerInt;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class GT6412x : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "marvell.ovpworld.org", "peripheral", "GT6412x", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusDynamicSlavePort busPort;
    tlmBusDynamicSlavePort PCIconfig;
    tlmBusMasterPort       PCIconfigM;
    tlmBusMasterPort       PCIackM;
    tlmNetOutputPort timerInt;

    GT6412x(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , busPort(parent, this, "busPort", 12) // dynamic
        , PCIconfig(parent, this, "PCIconfig", 0) // dynamic
        , PCIconfigM(parent, this, "PCIconfigM", 16)
        , PCIackM(parent, this, "PCIackM", 0)
        , timerInt(parent, this, "timerInt")
    {
    }

    GT6412x(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , busPort(parent, this, "busPort", 12) // dynamic
        , PCIconfig(parent, this, "PCIconfig", 0) // dynamic
        , PCIconfigM(parent, this, "PCIconfigM", 16)
        , PCIackM(parent, this, "PCIackM", 0)
        , timerInt(parent, this, "timerInt")
    {
    }

    void before_end_of_elaboration() {
        PCIackM.bindIfNotBound();
    }
}; /* class GT6412x */


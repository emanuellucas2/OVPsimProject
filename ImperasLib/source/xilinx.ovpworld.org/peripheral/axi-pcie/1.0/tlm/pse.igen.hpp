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
//    Slave Port ecam
//    Slave Port busPort
//    Slave Port PCIconfig
//    Net output  intOut;
//    Net input  intA;
//    Net input  intB;
//    Net input  intC;
//    Net input  intD;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class axi_pcie : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "xilinx.ovpworld.org", "peripheral", "axi-pcie", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusDynamicSlavePort ecam;
    tlmBusDynamicSlavePort busPort;
    tlmBusDynamicSlavePort PCIconfig;
    tlmBusMasterPort       PCIconfigM;
    tlmBusMasterPort       PCIackM;
    tlmNetOutputPort intOut;
    tlmNetInputPort intA;
    tlmNetInputPort intB;
    tlmNetInputPort intC;
    tlmNetInputPort intD;

    axi_pcie(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , ecam(parent, this, "ecam", 12) // dynamic
        , busPort(parent, this, "busPort", 12) // dynamic
        , PCIconfig(parent, this, "PCIconfig", 0) // dynamic
        , PCIconfigM(parent, this, "PCIconfigM", 28)
        , PCIackM(parent, this, "PCIackM", 0)
        , intOut(parent, this, "intOut")
        , intA(parent, this, "intA")
        , intB(parent, this, "intB")
        , intC(parent, this, "intC")
        , intD(parent, this, "intD")
    {
    }

    axi_pcie(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , ecam(parent, this, "ecam", 12) // dynamic
        , busPort(parent, this, "busPort", 12) // dynamic
        , PCIconfig(parent, this, "PCIconfig", 0) // dynamic
        , PCIconfigM(parent, this, "PCIconfigM", 28)
        , PCIackM(parent, this, "PCIackM", 0)
        , intOut(parent, this, "intOut")
        , intA(parent, this, "intA")
        , intB(parent, this, "intB")
        , intC(parent, this, "intC")
        , intD(parent, this, "intD")
    {
    }

    void before_end_of_elaboration() {
        PCIackM.bindIfNotBound();
    }
}; /* class axi_pcie */


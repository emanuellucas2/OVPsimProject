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
//    Master Port mpOCM
//    Master Port mpDDR
//    Slave Port bport1
//    Slave Port spOCMDDR
//    Net output  A9_RST0;
//    Net output  A9_RST1;
//    Net output  ARM1Deration;
//    Net output  ARM0Deration;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class zynq_7000_slcr : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "xilinx.ovpworld.org", "peripheral", "zynq_7000-slcr", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmBusDynamicSlavePort spOCMDDR;
    tlmBusMasterPort       mpOCM;
    tlmBusMasterPort       mpDDR;
    tlmNetOutputPort A9_RST0;
    tlmNetOutputPort A9_RST1;
    tlmNetOutputPort ARM1Deration;
    tlmNetOutputPort ARM0Deration;

    zynq_7000_slcr(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0xc00) // static
        , spOCMDDR(parent, this, "spOCMDDR", 0) // dynamic
        , mpOCM(parent, this, "mpOCM", 32)
        , mpDDR(parent, this, "mpDDR", 32)
        , A9_RST0(parent, this, "A9_RST0")
        , A9_RST1(parent, this, "A9_RST1")
        , ARM1Deration(parent, this, "ARM1Deration")
        , ARM0Deration(parent, this, "ARM0Deration")
    {
    }

    zynq_7000_slcr(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0xc00) // static
        , spOCMDDR(parent, this, "spOCMDDR", 0) // dynamic
        , mpOCM(parent, this, "mpOCM", 32)
        , mpDDR(parent, this, "mpDDR", 32)
        , A9_RST0(parent, this, "A9_RST0")
        , A9_RST1(parent, this, "A9_RST1")
        , ARM1Deration(parent, this, "ARM1Deration")
        , ARM0Deration(parent, this, "ARM0Deration")
    {
    }

}; /* class zynq_7000_slcr */


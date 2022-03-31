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
//    Master Port I2C_Master
//    Slave Port I2C_Slave
//    Slave Port bport1
//    Net output  intOut;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class zynq_7000_iic : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "xilinx.ovpworld.org", "peripheral", "zynq_7000-iic", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort I2C_Slave;
    tlmBusSlavePort bport1;
    tlmBusMasterPort       I2C_Master;
    tlmNetOutputPort intOut;

    zynq_7000_iic(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , I2C_Slave(parent, this, "I2C_Slave", 0x4) // static
        , bport1(parent, this, "bport1", 0x1000) // static
        , I2C_Master(parent, this, "I2C_Master", 10)
        , intOut(parent, this, "intOut")
    {
    }

    zynq_7000_iic(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , I2C_Slave(parent, this, "I2C_Slave", 0x4) // static
        , bport1(parent, this, "bport1", 0x1000) // static
        , I2C_Master(parent, this, "I2C_Master", 10)
        , intOut(parent, this, "intOut")
    {
    }

    void before_end_of_elaboration() {
        I2C_Master.bindIfNotBound();
    }
}; /* class zynq_7000_iic */


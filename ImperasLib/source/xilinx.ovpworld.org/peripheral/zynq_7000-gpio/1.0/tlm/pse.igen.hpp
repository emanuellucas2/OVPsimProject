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
//    Net output  interrupt;
//    Net input  gpio_bank0_in;
//    Net output  gpio_bank0_out;
//    Net input  gpio_bank1_in;
//    Net output  gpio_bank1_out;
//    Net input  gpio_bank2_in;
//    Net output  gpio_bank2_out;
//    Net output  gpio_bank2_oen_out;
//    Net input  gpio_bank3_in;
//    Net output  gpio_bank3_out;
//    Net output  gpio_bank3_oen_out;
//    Net output  intOut;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class zynq_7000_gpio : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "xilinx.ovpworld.org", "peripheral", "zynq_7000-gpio", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetOutputPort interrupt;
    tlmNetInputPort gpio_bank0_in;
    tlmNetOutputPort gpio_bank0_out;
    tlmNetInputPort gpio_bank1_in;
    tlmNetOutputPort gpio_bank1_out;
    tlmNetInputPort gpio_bank2_in;
    tlmNetOutputPort gpio_bank2_out;
    tlmNetOutputPort gpio_bank2_oen_out;
    tlmNetInputPort gpio_bank3_in;
    tlmNetOutputPort gpio_bank3_out;
    tlmNetOutputPort gpio_bank3_oen_out;
    tlmNetOutputPort intOut;

    zynq_7000_gpio(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x1000) // static
        , interrupt(parent, this, "interrupt")
        , gpio_bank0_in(parent, this, "gpio_bank0_in")
        , gpio_bank0_out(parent, this, "gpio_bank0_out")
        , gpio_bank1_in(parent, this, "gpio_bank1_in")
        , gpio_bank1_out(parent, this, "gpio_bank1_out")
        , gpio_bank2_in(parent, this, "gpio_bank2_in")
        , gpio_bank2_out(parent, this, "gpio_bank2_out")
        , gpio_bank2_oen_out(parent, this, "gpio_bank2_oen_out")
        , gpio_bank3_in(parent, this, "gpio_bank3_in")
        , gpio_bank3_out(parent, this, "gpio_bank3_out")
        , gpio_bank3_oen_out(parent, this, "gpio_bank3_oen_out")
        , intOut(parent, this, "intOut")
    {
    }

    zynq_7000_gpio(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x1000) // static
        , interrupt(parent, this, "interrupt")
        , gpio_bank0_in(parent, this, "gpio_bank0_in")
        , gpio_bank0_out(parent, this, "gpio_bank0_out")
        , gpio_bank1_in(parent, this, "gpio_bank1_in")
        , gpio_bank1_out(parent, this, "gpio_bank1_out")
        , gpio_bank2_in(parent, this, "gpio_bank2_in")
        , gpio_bank2_out(parent, this, "gpio_bank2_out")
        , gpio_bank2_oen_out(parent, this, "gpio_bank2_oen_out")
        , gpio_bank3_in(parent, this, "gpio_bank3_in")
        , gpio_bank3_out(parent, this, "gpio_bank3_out")
        , gpio_bank3_oen_out(parent, this, "gpio_bank3_oen_out")
        , intOut(parent, this, "intOut")
    {
    }

}; /* class zynq_7000_gpio */


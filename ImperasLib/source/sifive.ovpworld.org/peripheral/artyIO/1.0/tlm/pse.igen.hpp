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
//    Net output  SW0;
//    Net output  SW1;
//    Net output  SW2;
//    Net output  SW3;
//    Net output  BTN0;
//    Net output  BTN1;
//    Net output  BTN2;
//    Net output  BTN3;
//    Net input  LD0red;
//    Net input  LD0green;
//    Net input  LD0blue;
//    Net input  reset;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class artyIO : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "sifive.ovpworld.org", "peripheral", "artyIO", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmNetOutputPort SW0;
    tlmNetOutputPort SW1;
    tlmNetOutputPort SW2;
    tlmNetOutputPort SW3;
    tlmNetOutputPort BTN0;
    tlmNetOutputPort BTN1;
    tlmNetOutputPort BTN2;
    tlmNetOutputPort BTN3;
    tlmNetInputPort LD0red;
    tlmNetInputPort LD0green;
    tlmNetInputPort LD0blue;
    tlmNetInputPort reset;

    artyIO(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , SW0(parent, this, "SW0")
        , SW1(parent, this, "SW1")
        , SW2(parent, this, "SW2")
        , SW3(parent, this, "SW3")
        , BTN0(parent, this, "BTN0")
        , BTN1(parent, this, "BTN1")
        , BTN2(parent, this, "BTN2")
        , BTN3(parent, this, "BTN3")
        , LD0red(parent, this, "LD0red")
        , LD0green(parent, this, "LD0green")
        , LD0blue(parent, this, "LD0blue")
        , reset(parent, this, "reset")
    {
    }

    artyIO(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , SW0(parent, this, "SW0")
        , SW1(parent, this, "SW1")
        , SW2(parent, this, "SW2")
        , SW3(parent, this, "SW3")
        , BTN0(parent, this, "BTN0")
        , BTN1(parent, this, "BTN1")
        , BTN2(parent, this, "BTN2")
        , BTN3(parent, this, "BTN3")
        , LD0red(parent, this, "LD0red")
        , LD0green(parent, this, "LD0green")
        , LD0blue(parent, this, "LD0blue")
        , reset(parent, this, "reset")
    {
    }

}; /* class artyIO */


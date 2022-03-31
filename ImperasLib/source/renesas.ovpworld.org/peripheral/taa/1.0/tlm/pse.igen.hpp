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
//    Slave Port TAAP0
//    Net output  TOAA0;
//    Net output  TOAA1;
//    Net output  INTTAAOV;
//    Net output  INTTAACC0;
//    Net output  INTTAACC1;
//    Net input  TIAA0;
//    Net input  TIAA1;
//    Net input  TTRGAA;
//    Net input  TEVTAA;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class taa : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "renesas.ovpworld.org", "peripheral", "taa", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort TAAP0;
    tlmNetOutputPort TOAA0;
    tlmNetOutputPort TOAA1;
    tlmNetOutputPort INTTAAOV;
    tlmNetOutputPort INTTAACC0;
    tlmNetOutputPort INTTAACC1;
    tlmNetInputPort TIAA0;
    tlmNetInputPort TIAA1;
    tlmNetInputPort TTRGAA;
    tlmNetInputPort TEVTAA;

    taa(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , TAAP0(parent, this, "TAAP0", 0x10) // static
        , TOAA0(parent, this, "TOAA0")
        , TOAA1(parent, this, "TOAA1")
        , INTTAAOV(parent, this, "INTTAAOV")
        , INTTAACC0(parent, this, "INTTAACC0")
        , INTTAACC1(parent, this, "INTTAACC1")
        , TIAA0(parent, this, "TIAA0")
        , TIAA1(parent, this, "TIAA1")
        , TTRGAA(parent, this, "TTRGAA")
        , TEVTAA(parent, this, "TEVTAA")
    {
    }

    taa(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , TAAP0(parent, this, "TAAP0", 0x10) // static
        , TOAA0(parent, this, "TOAA0")
        , TOAA1(parent, this, "TOAA1")
        , INTTAAOV(parent, this, "INTTAAOV")
        , INTTAACC0(parent, this, "INTTAACC0")
        , INTTAACC1(parent, this, "INTTAACC1")
        , TIAA0(parent, this, "TIAA0")
        , TIAA1(parent, this, "TIAA1")
        , TTRGAA(parent, this, "TTRGAA")
        , TEVTAA(parent, this, "TEVTAA")
    {
    }

}; /* class taa */


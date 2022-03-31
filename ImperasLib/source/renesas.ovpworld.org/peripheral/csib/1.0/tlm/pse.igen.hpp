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
//    Slave Port CSIBP0
//    Net output  INTCBT;
//    Net output  INTCBR;
//    Net output  INTCBRE;
//    Net output  SOB;
//    Net input  SIB;
//    Net input  SSB;
//    Net inout  SCKB;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class csib : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "renesas.ovpworld.org", "peripheral", "csib", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort CSIBP0;
    tlmNetOutputPort INTCBT;
    tlmNetOutputPort INTCBR;
    tlmNetOutputPort INTCBRE;
    tlmNetOutputPort SOB;
    tlmNetInputPort SIB;
    tlmNetInputPort SSB;
    tlmNetInoutPort SCKB;

    csib(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , CSIBP0(parent, this, "CSIBP0", 0x8) // static
        , INTCBT(parent, this, "INTCBT")
        , INTCBR(parent, this, "INTCBR")
        , INTCBRE(parent, this, "INTCBRE")
        , SOB(parent, this, "SOB")
        , SIB(parent, this, "SIB")
        , SSB(parent, this, "SSB")
        , SCKB(parent, this, "SCKB")
    {
    }

    csib(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , CSIBP0(parent, this, "CSIBP0", 0x8) // static
        , INTCBT(parent, this, "INTCBT")
        , INTCBR(parent, this, "INTCBR")
        , INTCBRE(parent, this, "INTCBRE")
        , SOB(parent, this, "SOB")
        , SIB(parent, this, "SIB")
        , SSB(parent, this, "SSB")
        , SCKB(parent, this, "SCKB")
    {
    }

}; /* class csib */


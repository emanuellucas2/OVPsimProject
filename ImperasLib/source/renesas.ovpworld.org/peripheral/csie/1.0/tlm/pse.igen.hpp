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
//    Slave Port CSIEP0
//    Net output  INTCEOF;
//    Net output  INTCEC;
//    Net output  SOE;
//    Net output  SCSE0;
//    Net output  SCSE1;
//    Net output  SCSE2;
//    Net output  SCSE3;
//    Net output  SCSE4;
//    Net output  SCSE5;
//    Net output  SCSE6;
//    Net output  SCSE7;
//    Net input  SIE;
//    Net inout  SCKE;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class csie : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "renesas.ovpworld.org", "peripheral", "csie", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort CSIEP0;
    tlmNetOutputPort INTCEOF;
    tlmNetOutputPort INTCEC;
    tlmNetOutputPort SOE;
    tlmNetOutputPort SCSE0;
    tlmNetOutputPort SCSE1;
    tlmNetOutputPort SCSE2;
    tlmNetOutputPort SCSE3;
    tlmNetOutputPort SCSE4;
    tlmNetOutputPort SCSE5;
    tlmNetOutputPort SCSE6;
    tlmNetOutputPort SCSE7;
    tlmNetInputPort SIE;
    tlmNetInoutPort SCKE;

    csie(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , CSIEP0(parent, this, "CSIEP0", 0x20) // static
        , INTCEOF(parent, this, "INTCEOF")
        , INTCEC(parent, this, "INTCEC")
        , SOE(parent, this, "SOE")
        , SCSE0(parent, this, "SCSE0")
        , SCSE1(parent, this, "SCSE1")
        , SCSE2(parent, this, "SCSE2")
        , SCSE3(parent, this, "SCSE3")
        , SCSE4(parent, this, "SCSE4")
        , SCSE5(parent, this, "SCSE5")
        , SCSE6(parent, this, "SCSE6")
        , SCSE7(parent, this, "SCSE7")
        , SIE(parent, this, "SIE")
        , SCKE(parent, this, "SCKE")
    {
    }

    csie(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , CSIEP0(parent, this, "CSIEP0", 0x20) // static
        , INTCEOF(parent, this, "INTCEOF")
        , INTCEC(parent, this, "INTCEC")
        , SOE(parent, this, "SOE")
        , SCSE0(parent, this, "SCSE0")
        , SCSE1(parent, this, "SCSE1")
        , SCSE2(parent, this, "SCSE2")
        , SCSE3(parent, this, "SCSE3")
        , SCSE4(parent, this, "SCSE4")
        , SCSE5(parent, this, "SCSE5")
        , SCSE6(parent, this, "SCSE6")
        , SCSE7(parent, this, "SCSE7")
        , SIE(parent, this, "SIE")
        , SCKE(parent, this, "SCKE")
    {
    }

}; /* class csie */


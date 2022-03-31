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
//    Slave Port ADCP0
//    Slave Port ADCP1
//    Net output  INTAD;
//    Net output  ADDMARQ;
//    Net input  INTADEN;
//    Net input  ADTRG;
//    Net input  TS0ADT0;
//    Net input  TS0ADT1;
//    Net input  INTTS0OD;
//    Net input  INTTS0CD;
//    Net input  TS1ADT0;
//    Net input  TS1ADT1;
//    Net input  INTTS1OD;
//    Net input  INTTS1CD;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class adc : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "renesas.ovpworld.org", "peripheral", "adc", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort ADCP0;
    tlmBusSlavePort ADCP1;
    tlmNetOutputPort INTAD;
    tlmNetOutputPort ADDMARQ;
    tlmNetInputPort INTADEN;
    tlmNetInputPort ADTRG;
    tlmNetInputPort TS0ADT0;
    tlmNetInputPort TS0ADT1;
    tlmNetInputPort INTTS0OD;
    tlmNetInputPort INTTS0CD;
    tlmNetInputPort TS1ADT0;
    tlmNetInputPort TS1ADT1;
    tlmNetInputPort INTTS1OD;
    tlmNetInputPort INTTS1CD;

    adc(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , ADCP0(parent, this, "ADCP0", 0x30) // static
        , ADCP1(parent, this, "ADCP1", 0x1) // static
        , INTAD(parent, this, "INTAD")
        , ADDMARQ(parent, this, "ADDMARQ")
        , INTADEN(parent, this, "INTADEN")
        , ADTRG(parent, this, "ADTRG")
        , TS0ADT0(parent, this, "TS0ADT0")
        , TS0ADT1(parent, this, "TS0ADT1")
        , INTTS0OD(parent, this, "INTTS0OD")
        , INTTS0CD(parent, this, "INTTS0CD")
        , TS1ADT0(parent, this, "TS1ADT0")
        , TS1ADT1(parent, this, "TS1ADT1")
        , INTTS1OD(parent, this, "INTTS1OD")
        , INTTS1CD(parent, this, "INTTS1CD")
    {
    }

    adc(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , ADCP0(parent, this, "ADCP0", 0x30) // static
        , ADCP1(parent, this, "ADCP1", 0x1) // static
        , INTAD(parent, this, "INTAD")
        , ADDMARQ(parent, this, "ADDMARQ")
        , INTADEN(parent, this, "INTADEN")
        , ADTRG(parent, this, "ADTRG")
        , TS0ADT0(parent, this, "TS0ADT0")
        , TS0ADT1(parent, this, "TS0ADT1")
        , INTTS0OD(parent, this, "INTTS0OD")
        , INTTS0CD(parent, this, "INTTS0CD")
        , TS1ADT0(parent, this, "TS1ADT0")
        , TS1ADT1(parent, this, "TS1ADT1")
        , INTTS1OD(parent, this, "INTTS1OD")
        , INTTS1CD(parent, this, "INTTS1CD")
    {
    }

}; /* class adc */


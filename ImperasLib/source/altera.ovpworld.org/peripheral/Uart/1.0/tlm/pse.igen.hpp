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
//    Slave Port sp1
//    Net output  irq;
//    Net output  endofpacket;
//    Net output  dataavailable;
//    Net output  readyfordata;
//    Net input  RXD;
//    Net input  CTS;
//    Net output  TXD;
//    Net output  RTS;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class Uart : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "altera.ovpworld.org", "peripheral", "Uart", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort sp1;
    tlmNetOutputPort irq;
    tlmNetOutputPort endofpacket;
    tlmNetOutputPort dataavailable;
    tlmNetOutputPort readyfordata;
    tlmNetInputPort RXD;
    tlmNetInputPort CTS;
    tlmNetOutputPort TXD;
    tlmNetOutputPort RTS;

    Uart(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , sp1(parent, this, "sp1", 0x20) // static
        , irq(parent, this, "irq")
        , endofpacket(parent, this, "endofpacket")
        , dataavailable(parent, this, "dataavailable")
        , readyfordata(parent, this, "readyfordata")
        , RXD(parent, this, "RXD")
        , CTS(parent, this, "CTS")
        , TXD(parent, this, "TXD")
        , RTS(parent, this, "RTS")
    {
    }

    Uart(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , sp1(parent, this, "sp1", 0x20) // static
        , irq(parent, this, "irq")
        , endofpacket(parent, this, "endofpacket")
        , dataavailable(parent, this, "dataavailable")
        , readyfordata(parent, this, "readyfordata")
        , RXD(parent, this, "RXD")
        , CTS(parent, this, "CTS")
        , TXD(parent, this, "TXD")
        , RTS(parent, this, "RTS")
    {
    }

}; /* class Uart */


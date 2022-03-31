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
//    Slave Port LOGICP0
//    Slave Port LOGICP1
//    Slave Port LOGICP2
//    Slave Port LOGICP3
//    Net input  NMIIN;
//    Net input  INTDEDF;
//    Net input  INTDEDR;
//    Net input  INTDEDFR;
//    Net input  INTOSD;
//    Net input  INTP4;
//    Net input  INTUC0R;
//    Net input  INTP5;
//    Net input  INTUC1R;
//    Net input  INTBRG0;
//    Net input  INTBRG1;
//    Net input  INTCB0T;
//    Net input  INTUC2T;
//    Net input  INTCB0R;
//    Net input  INTUC2R;
//    Net input  INTP13;
//    Net input  INTCB0RE;
//    Net input  INTUC2RE;
//    Net input  INTDMA3;
//    Net input  INTFL;
//    Net output  NMIOUT;
//    Net output  INT0;
//    Net output  INT1;
//    Net output  INT6;
//    Net output  INT7;
//    Net output  INT75;
//    Net output  INT99;
//    Net output  INT100;
//    Net output  INT101;
//    Net output  INT116;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class UPD70F3441Logic : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "renesas.ovpworld.org", "peripheral", "UPD70F3441Logic", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort LOGICP0;
    tlmBusSlavePort LOGICP1;
    tlmBusSlavePort LOGICP2;
    tlmBusSlavePort LOGICP3;
    tlmNetInputPort NMIIN;
    tlmNetInputPort INTDEDF;
    tlmNetInputPort INTDEDR;
    tlmNetInputPort INTDEDFR;
    tlmNetInputPort INTOSD;
    tlmNetInputPort INTP4;
    tlmNetInputPort INTUC0R;
    tlmNetInputPort INTP5;
    tlmNetInputPort INTUC1R;
    tlmNetInputPort INTBRG0;
    tlmNetInputPort INTBRG1;
    tlmNetInputPort INTCB0T;
    tlmNetInputPort INTUC2T;
    tlmNetInputPort INTCB0R;
    tlmNetInputPort INTUC2R;
    tlmNetInputPort INTP13;
    tlmNetInputPort INTCB0RE;
    tlmNetInputPort INTUC2RE;
    tlmNetInputPort INTDMA3;
    tlmNetInputPort INTFL;
    tlmNetOutputPort NMIOUT;
    tlmNetOutputPort INT0;
    tlmNetOutputPort INT1;
    tlmNetOutputPort INT6;
    tlmNetOutputPort INT7;
    tlmNetOutputPort INT75;
    tlmNetOutputPort INT99;
    tlmNetOutputPort INT100;
    tlmNetOutputPort INT101;
    tlmNetOutputPort INT116;

    UPD70F3441Logic(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , LOGICP0(parent, this, "LOGICP0", 0x4) // static
        , LOGICP1(parent, this, "LOGICP1", 0x76) // static
        , LOGICP2(parent, this, "LOGICP2", 0xc) // static
        , LOGICP3(parent, this, "LOGICP3", 0x1) // static
        , NMIIN(parent, this, "NMIIN")
        , INTDEDF(parent, this, "INTDEDF")
        , INTDEDR(parent, this, "INTDEDR")
        , INTDEDFR(parent, this, "INTDEDFR")
        , INTOSD(parent, this, "INTOSD")
        , INTP4(parent, this, "INTP4")
        , INTUC0R(parent, this, "INTUC0R")
        , INTP5(parent, this, "INTP5")
        , INTUC1R(parent, this, "INTUC1R")
        , INTBRG0(parent, this, "INTBRG0")
        , INTBRG1(parent, this, "INTBRG1")
        , INTCB0T(parent, this, "INTCB0T")
        , INTUC2T(parent, this, "INTUC2T")
        , INTCB0R(parent, this, "INTCB0R")
        , INTUC2R(parent, this, "INTUC2R")
        , INTP13(parent, this, "INTP13")
        , INTCB0RE(parent, this, "INTCB0RE")
        , INTUC2RE(parent, this, "INTUC2RE")
        , INTDMA3(parent, this, "INTDMA3")
        , INTFL(parent, this, "INTFL")
        , NMIOUT(parent, this, "NMIOUT")
        , INT0(parent, this, "INT0")
        , INT1(parent, this, "INT1")
        , INT6(parent, this, "INT6")
        , INT7(parent, this, "INT7")
        , INT75(parent, this, "INT75")
        , INT99(parent, this, "INT99")
        , INT100(parent, this, "INT100")
        , INT101(parent, this, "INT101")
        , INT116(parent, this, "INT116")
    {
    }

    UPD70F3441Logic(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , LOGICP0(parent, this, "LOGICP0", 0x4) // static
        , LOGICP1(parent, this, "LOGICP1", 0x76) // static
        , LOGICP2(parent, this, "LOGICP2", 0xc) // static
        , LOGICP3(parent, this, "LOGICP3", 0x1) // static
        , NMIIN(parent, this, "NMIIN")
        , INTDEDF(parent, this, "INTDEDF")
        , INTDEDR(parent, this, "INTDEDR")
        , INTDEDFR(parent, this, "INTDEDFR")
        , INTOSD(parent, this, "INTOSD")
        , INTP4(parent, this, "INTP4")
        , INTUC0R(parent, this, "INTUC0R")
        , INTP5(parent, this, "INTP5")
        , INTUC1R(parent, this, "INTUC1R")
        , INTBRG0(parent, this, "INTBRG0")
        , INTBRG1(parent, this, "INTBRG1")
        , INTCB0T(parent, this, "INTCB0T")
        , INTUC2T(parent, this, "INTUC2T")
        , INTCB0R(parent, this, "INTCB0R")
        , INTUC2R(parent, this, "INTUC2R")
        , INTP13(parent, this, "INTP13")
        , INTCB0RE(parent, this, "INTCB0RE")
        , INTUC2RE(parent, this, "INTUC2RE")
        , INTDMA3(parent, this, "INTDMA3")
        , INTFL(parent, this, "INTFL")
        , NMIOUT(parent, this, "NMIOUT")
        , INT0(parent, this, "INT0")
        , INT1(parent, this, "INT1")
        , INT6(parent, this, "INT6")
        , INT7(parent, this, "INT7")
        , INT75(parent, this, "INT75")
        , INT99(parent, this, "INT99")
        , INT100(parent, this, "INT100")
        , INT101(parent, this, "INT101")
        , INT116(parent, this, "INT116")
    {
    }

}; /* class UPD70F3441Logic */


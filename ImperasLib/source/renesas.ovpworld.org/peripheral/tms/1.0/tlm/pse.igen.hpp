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
//    Slave Port TMSP0
//    Net output  TOS0;
//    Net output  TOS1;
//    Net output  TOS2;
//    Net output  TOS3;
//    Net output  TOS4;
//    Net output  TOS5;
//    Net output  TOS6;
//    Net output  TOS7;
//    Net output  TSADTRG0;
//    Net output  TSADTRG1;
//    Net output  TSAEDO;
//    Net output  TSESG;
//    Net output  TSTSF;
//    Net output  INTTSCC0;
//    Net output  INTTSCC1;
//    Net output  INTTSCC2;
//    Net output  INTTSCC3;
//    Net output  INTTSCC4;
//    Net output  INTTSCC5;
//    Net output  INTTSCD0;
//    Net output  INTTSOD;
//    Net output  INTTSOV;
//    Net output  INTTSER;
//    Net output  INTTSWN;
//    Net input  TTRGS;
//    Net input  TEVTS;
//    Net input  TAPTS0;
//    Net input  TAPTS1;
//    Net input  TAPTS2;
//    Net input  ESO;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class tms : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "renesas.ovpworld.org", "peripheral", "tms", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort TMSP0;
    tlmNetOutputPort TOS0;
    tlmNetOutputPort TOS1;
    tlmNetOutputPort TOS2;
    tlmNetOutputPort TOS3;
    tlmNetOutputPort TOS4;
    tlmNetOutputPort TOS5;
    tlmNetOutputPort TOS6;
    tlmNetOutputPort TOS7;
    tlmNetOutputPort TSADTRG0;
    tlmNetOutputPort TSADTRG1;
    tlmNetOutputPort TSAEDO;
    tlmNetOutputPort TSESG;
    tlmNetOutputPort TSTSF;
    tlmNetOutputPort INTTSCC0;
    tlmNetOutputPort INTTSCC1;
    tlmNetOutputPort INTTSCC2;
    tlmNetOutputPort INTTSCC3;
    tlmNetOutputPort INTTSCC4;
    tlmNetOutputPort INTTSCC5;
    tlmNetOutputPort INTTSCD0;
    tlmNetOutputPort INTTSOD;
    tlmNetOutputPort INTTSOV;
    tlmNetOutputPort INTTSER;
    tlmNetOutputPort INTTSWN;
    tlmNetInputPort TTRGS;
    tlmNetInputPort TEVTS;
    tlmNetInputPort TAPTS0;
    tlmNetInputPort TAPTS1;
    tlmNetInputPort TAPTS2;
    tlmNetInputPort ESO;

    tms(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , TMSP0(parent, this, "TMSP0", 0x2a) // static
        , TOS0(parent, this, "TOS0")
        , TOS1(parent, this, "TOS1")
        , TOS2(parent, this, "TOS2")
        , TOS3(parent, this, "TOS3")
        , TOS4(parent, this, "TOS4")
        , TOS5(parent, this, "TOS5")
        , TOS6(parent, this, "TOS6")
        , TOS7(parent, this, "TOS7")
        , TSADTRG0(parent, this, "TSADTRG0")
        , TSADTRG1(parent, this, "TSADTRG1")
        , TSAEDO(parent, this, "TSAEDO")
        , TSESG(parent, this, "TSESG")
        , TSTSF(parent, this, "TSTSF")
        , INTTSCC0(parent, this, "INTTSCC0")
        , INTTSCC1(parent, this, "INTTSCC1")
        , INTTSCC2(parent, this, "INTTSCC2")
        , INTTSCC3(parent, this, "INTTSCC3")
        , INTTSCC4(parent, this, "INTTSCC4")
        , INTTSCC5(parent, this, "INTTSCC5")
        , INTTSCD0(parent, this, "INTTSCD0")
        , INTTSOD(parent, this, "INTTSOD")
        , INTTSOV(parent, this, "INTTSOV")
        , INTTSER(parent, this, "INTTSER")
        , INTTSWN(parent, this, "INTTSWN")
        , TTRGS(parent, this, "TTRGS")
        , TEVTS(parent, this, "TEVTS")
        , TAPTS0(parent, this, "TAPTS0")
        , TAPTS1(parent, this, "TAPTS1")
        , TAPTS2(parent, this, "TAPTS2")
        , ESO(parent, this, "ESO")
    {
    }

    tms(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , TMSP0(parent, this, "TMSP0", 0x2a) // static
        , TOS0(parent, this, "TOS0")
        , TOS1(parent, this, "TOS1")
        , TOS2(parent, this, "TOS2")
        , TOS3(parent, this, "TOS3")
        , TOS4(parent, this, "TOS4")
        , TOS5(parent, this, "TOS5")
        , TOS6(parent, this, "TOS6")
        , TOS7(parent, this, "TOS7")
        , TSADTRG0(parent, this, "TSADTRG0")
        , TSADTRG1(parent, this, "TSADTRG1")
        , TSAEDO(parent, this, "TSAEDO")
        , TSESG(parent, this, "TSESG")
        , TSTSF(parent, this, "TSTSF")
        , INTTSCC0(parent, this, "INTTSCC0")
        , INTTSCC1(parent, this, "INTTSCC1")
        , INTTSCC2(parent, this, "INTTSCC2")
        , INTTSCC3(parent, this, "INTTSCC3")
        , INTTSCC4(parent, this, "INTTSCC4")
        , INTTSCC5(parent, this, "INTTSCC5")
        , INTTSCD0(parent, this, "INTTSCD0")
        , INTTSOD(parent, this, "INTTSOD")
        , INTTSOV(parent, this, "INTTSOV")
        , INTTSER(parent, this, "INTTSER")
        , INTTSWN(parent, this, "INTTSWN")
        , TTRGS(parent, this, "TTRGS")
        , TEVTS(parent, this, "TEVTS")
        , TAPTS0(parent, this, "TAPTS0")
        , TAPTS1(parent, this, "TAPTS1")
        , TAPTS2(parent, this, "TAPTS2")
        , ESO(parent, this, "ESO")
    {
    }

}; /* class tms */


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
//    Slave Port TMTP0
//    Slave Port TMTP1
//    Net output  TOT0;
//    Net output  TOT1;
//    Net output  TTTTO0;
//    Net output  TTTT01;
//    Net output  TTTICC0;
//    Net output  TTTICC1;
//    Net output  TTTEQC0;
//    Net output  TTTEQC1;
//    Net output  INTTTCC0;
//    Net output  INTTTCC1;
//    Net output  INTTTOV;
//    Net output  INTTTEC;
//    Net input  TIT0;
//    Net input  TIT1;
//    Net input  TEVTT;
//    Net input  TTRGT;
//    Net input  TENCT0;
//    Net input  TENCT1;
//    Net input  TECRT;
//    Net input  TTTTI0;
//    Net input  TTTTI1;
//    Net input  TTTENC0;
//    Net input  TTTENC1;
//    Net input  TTTTRG;
//    Net input  TTTEVT;
//    Net input  TTTECR;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class tmt : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "renesas.ovpworld.org", "peripheral", "tmt", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort TMTP0;
    tlmBusSlavePort TMTP1;
    tlmNetOutputPort TOT0;
    tlmNetOutputPort TOT1;
    tlmNetOutputPort TTTTO0;
    tlmNetOutputPort TTTT01;
    tlmNetOutputPort TTTICC0;
    tlmNetOutputPort TTTICC1;
    tlmNetOutputPort TTTEQC0;
    tlmNetOutputPort TTTEQC1;
    tlmNetOutputPort INTTTCC0;
    tlmNetOutputPort INTTTCC1;
    tlmNetOutputPort INTTTOV;
    tlmNetOutputPort INTTTEC;
    tlmNetInputPort TIT0;
    tlmNetInputPort TIT1;
    tlmNetInputPort TEVTT;
    tlmNetInputPort TTRGT;
    tlmNetInputPort TENCT0;
    tlmNetInputPort TENCT1;
    tlmNetInputPort TECRT;
    tlmNetInputPort TTTTI0;
    tlmNetInputPort TTTTI1;
    tlmNetInputPort TTTENC0;
    tlmNetInputPort TTTENC1;
    tlmNetInputPort TTTTRG;
    tlmNetInputPort TTTEVT;
    tlmNetInputPort TTTECR;

    tmt(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , TMTP0(parent, this, "TMTP0", 0x10) // static
        , TMTP1(parent, this, "TMTP1", 0x2) // static
        , TOT0(parent, this, "TOT0")
        , TOT1(parent, this, "TOT1")
        , TTTTO0(parent, this, "TTTTO0")
        , TTTT01(parent, this, "TTTT01")
        , TTTICC0(parent, this, "TTTICC0")
        , TTTICC1(parent, this, "TTTICC1")
        , TTTEQC0(parent, this, "TTTEQC0")
        , TTTEQC1(parent, this, "TTTEQC1")
        , INTTTCC0(parent, this, "INTTTCC0")
        , INTTTCC1(parent, this, "INTTTCC1")
        , INTTTOV(parent, this, "INTTTOV")
        , INTTTEC(parent, this, "INTTTEC")
        , TIT0(parent, this, "TIT0")
        , TIT1(parent, this, "TIT1")
        , TEVTT(parent, this, "TEVTT")
        , TTRGT(parent, this, "TTRGT")
        , TENCT0(parent, this, "TENCT0")
        , TENCT1(parent, this, "TENCT1")
        , TECRT(parent, this, "TECRT")
        , TTTTI0(parent, this, "TTTTI0")
        , TTTTI1(parent, this, "TTTTI1")
        , TTTENC0(parent, this, "TTTENC0")
        , TTTENC1(parent, this, "TTTENC1")
        , TTTTRG(parent, this, "TTTTRG")
        , TTTEVT(parent, this, "TTTEVT")
        , TTTECR(parent, this, "TTTECR")
    {
    }

    tmt(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , TMTP0(parent, this, "TMTP0", 0x10) // static
        , TMTP1(parent, this, "TMTP1", 0x2) // static
        , TOT0(parent, this, "TOT0")
        , TOT1(parent, this, "TOT1")
        , TTTTO0(parent, this, "TTTTO0")
        , TTTT01(parent, this, "TTTT01")
        , TTTICC0(parent, this, "TTTICC0")
        , TTTICC1(parent, this, "TTTICC1")
        , TTTEQC0(parent, this, "TTTEQC0")
        , TTTEQC1(parent, this, "TTTEQC1")
        , INTTTCC0(parent, this, "INTTTCC0")
        , INTTTCC1(parent, this, "INTTTCC1")
        , INTTTOV(parent, this, "INTTTOV")
        , INTTTEC(parent, this, "INTTTEC")
        , TIT0(parent, this, "TIT0")
        , TIT1(parent, this, "TIT1")
        , TEVTT(parent, this, "TEVTT")
        , TTRGT(parent, this, "TTRGT")
        , TENCT0(parent, this, "TENCT0")
        , TENCT1(parent, this, "TENCT1")
        , TECRT(parent, this, "TECRT")
        , TTTTI0(parent, this, "TTTTI0")
        , TTTTI1(parent, this, "TTTTI1")
        , TTTENC0(parent, this, "TTTENC0")
        , TTTENC1(parent, this, "TTTENC1")
        , TTTTRG(parent, this, "TTTTRG")
        , TTTEVT(parent, this, "TTTEVT")
        , TTTECR(parent, this, "TTTECR")
    {
    }

}; /* class tmt */


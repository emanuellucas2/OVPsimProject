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
//    Master Port DMAPM
//    Slave Port DMAP0
//    Slave Port DMAP1
//    Net output  INTDMA0;
//    Net output  INTDMA1;
//    Net output  INTDMA2;
//    Net output  INTDMA3;
//    Net output  INTDMA4;
//    Net output  INTDMA5;
//    Net output  INTDMA6;
//    Net output  INTDMA7;
//    Net output  INTDMA8;
//    Net output  INTDMA9;
//    Net output  DMA0EN;
//    Net output  DMA1EN;
//    Net input  ADDMARQ0;
//    Net input  ADDMARQ1;
//    Net input  INTTS0CD;
//    Net input  INTTS1CD;
//    Net input  INTCE0C;
//    Net input  INTCE1C;
//    Net input  INTBE0R;
//    Net input  INTBE1R;
//    Net input  INTUC0R;
//    Net input  INTUC1R;
//    Net input  INTUC2R;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class dma : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "renesas.ovpworld.org", "peripheral", "dma", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort DMAP0;
    tlmBusSlavePort DMAP1;
    tlmBusMasterPort       DMAPM;
    tlmNetOutputPort INTDMA0;
    tlmNetOutputPort INTDMA1;
    tlmNetOutputPort INTDMA2;
    tlmNetOutputPort INTDMA3;
    tlmNetOutputPort INTDMA4;
    tlmNetOutputPort INTDMA5;
    tlmNetOutputPort INTDMA6;
    tlmNetOutputPort INTDMA7;
    tlmNetOutputPort INTDMA8;
    tlmNetOutputPort INTDMA9;
    tlmNetOutputPort DMA0EN;
    tlmNetOutputPort DMA1EN;
    tlmNetInputPort ADDMARQ0;
    tlmNetInputPort ADDMARQ1;
    tlmNetInputPort INTTS0CD;
    tlmNetInputPort INTTS1CD;
    tlmNetInputPort INTCE0C;
    tlmNetInputPort INTCE1C;
    tlmNetInputPort INTBE0R;
    tlmNetInputPort INTBE1R;
    tlmNetInputPort INTUC0R;
    tlmNetInputPort INTUC1R;
    tlmNetInputPort INTUC2R;

    dma(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , DMAP0(parent, this, "DMAP0", 0x10) // static
        , DMAP1(parent, this, "DMAP1", 0x100) // static
        , DMAPM(parent, this, "DMAPM", 28)
        , INTDMA0(parent, this, "INTDMA0")
        , INTDMA1(parent, this, "INTDMA1")
        , INTDMA2(parent, this, "INTDMA2")
        , INTDMA3(parent, this, "INTDMA3")
        , INTDMA4(parent, this, "INTDMA4")
        , INTDMA5(parent, this, "INTDMA5")
        , INTDMA6(parent, this, "INTDMA6")
        , INTDMA7(parent, this, "INTDMA7")
        , INTDMA8(parent, this, "INTDMA8")
        , INTDMA9(parent, this, "INTDMA9")
        , DMA0EN(parent, this, "DMA0EN")
        , DMA1EN(parent, this, "DMA1EN")
        , ADDMARQ0(parent, this, "ADDMARQ0")
        , ADDMARQ1(parent, this, "ADDMARQ1")
        , INTTS0CD(parent, this, "INTTS0CD")
        , INTTS1CD(parent, this, "INTTS1CD")
        , INTCE0C(parent, this, "INTCE0C")
        , INTCE1C(parent, this, "INTCE1C")
        , INTBE0R(parent, this, "INTBE0R")
        , INTBE1R(parent, this, "INTBE1R")
        , INTUC0R(parent, this, "INTUC0R")
        , INTUC1R(parent, this, "INTUC1R")
        , INTUC2R(parent, this, "INTUC2R")
    {
    }

    dma(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , DMAP0(parent, this, "DMAP0", 0x10) // static
        , DMAP1(parent, this, "DMAP1", 0x100) // static
        , DMAPM(parent, this, "DMAPM", 28)
        , INTDMA0(parent, this, "INTDMA0")
        , INTDMA1(parent, this, "INTDMA1")
        , INTDMA2(parent, this, "INTDMA2")
        , INTDMA3(parent, this, "INTDMA3")
        , INTDMA4(parent, this, "INTDMA4")
        , INTDMA5(parent, this, "INTDMA5")
        , INTDMA6(parent, this, "INTDMA6")
        , INTDMA7(parent, this, "INTDMA7")
        , INTDMA8(parent, this, "INTDMA8")
        , INTDMA9(parent, this, "INTDMA9")
        , DMA0EN(parent, this, "DMA0EN")
        , DMA1EN(parent, this, "DMA1EN")
        , ADDMARQ0(parent, this, "ADDMARQ0")
        , ADDMARQ1(parent, this, "ADDMARQ1")
        , INTTS0CD(parent, this, "INTTS0CD")
        , INTTS1CD(parent, this, "INTTS1CD")
        , INTCE0C(parent, this, "INTCE0C")
        , INTCE1C(parent, this, "INTCE1C")
        , INTBE0R(parent, this, "INTBE0R")
        , INTBE1R(parent, this, "INTBE1R")
        , INTUC0R(parent, this, "INTUC0R")
        , INTUC1R(parent, this, "INTUC1R")
        , INTUC2R(parent, this, "INTUC2R")
    {
    }

    void before_end_of_elaboration() {
        DMAPM.bindIfNotBound();
    }
}; /* class dma */


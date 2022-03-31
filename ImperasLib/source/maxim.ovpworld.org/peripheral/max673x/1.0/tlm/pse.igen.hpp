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
//    Net input  wdi;
//    Net output  wdo;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class max673x : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "maxim.ovpworld.org", "peripheral", "max673x", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmNetInputPort wdi;
    tlmNetOutputPort wdo;

    max673x(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , wdi(parent, this, "wdi")
        , wdo(parent, this, "wdo")
    {
    }

    max673x(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , wdi(parent, this, "wdi")
        , wdo(parent, this, "wdo")
    {
    }

}; /* class max673x */


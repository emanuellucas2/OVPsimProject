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
//    Master Port mp1
//    Slave Port sp1

#pragma once

#include "tlm/tlmMmc.hpp"
using namespace sc_core;

class endianSwap : public tlmMMC
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "ovpworld.org", "mmc", "endianSwap", "1.0", OP_MMC, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort sp1;
    tlmBusMasterPort mp1;

    endianSwap(tlmModule &parent, sc_module_name name)
        : tlmMMC(parent, getModel(), name)
        , sp1(parent, this, "sp1")
        , mp1(parent, this, "mp1", 32)
    {
    }

}; /* class endianSwap */


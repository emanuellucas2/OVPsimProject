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

#pragma once

#include "tlm/tlmProcessor.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"

using namespace sc_core;
using namespace cw;

class rl78_RL78_S1 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "RL78-S1");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "RL78-S1");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "renesas.ovpworld.org", "processor", "rl78", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      reset;
    tlmNetInputPort      extint;
    tlmNetOutputPort     intAck;

    rl78_RL78_S1(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 20)
    , DATA (parent, this, "DATA", 20)
    , reset(parent, this, "reset")
    , extint(parent, this, "extint")
    , intAck(parent, this, "intAck")
    {
    }

    rl78_RL78_S1(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=20, Uns32 DATAWidth=20)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , reset(parent, this, "reset")
    , extint(parent, this, "extint")
    , intAck(parent, this, "intAck")
    {
    }

}; /* class rl78_RL78_S1 */


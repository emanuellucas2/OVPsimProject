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

class v850_V850E2M : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "V850E2M");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "V850E2M");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "renesas.ovpworld.org", "processor", "v850", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      intp;
    tlmNetInputPort      nmi0;
    tlmNetInputPort      nmi1;
    tlmNetInputPort      nmi2;
    tlmNetInputPort      reset;
    tlmNetOutputPort     mireti;
    tlmNetOutputPort     intack;

    v850_V850E2M(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 28)
    , DATA (parent, this, "DATA", 28)
    , intp(parent, this, "intp")
    , nmi0(parent, this, "nmi0")
    , nmi1(parent, this, "nmi1")
    , nmi2(parent, this, "nmi2")
    , reset(parent, this, "reset")
    , mireti(parent, this, "mireti")
    , intack(parent, this, "intack")
    {
    }

    v850_V850E2M(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=28, Uns32 DATAWidth=28)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , intp(parent, this, "intp")
    , nmi0(parent, this, "nmi0")
    , nmi1(parent, this, "nmi1")
    , nmi2(parent, this, "nmi2")
    , reset(parent, this, "reset")
    , mireti(parent, this, "mireti")
    , intack(parent, this, "intack")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class v850_V850E2M */


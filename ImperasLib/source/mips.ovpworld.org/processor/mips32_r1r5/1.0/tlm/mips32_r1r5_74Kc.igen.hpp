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

class mips32_r1r5_74Kc : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "74Kc");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "74Kc");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "mips.ovpworld.org", "processor", "mips32_r1r5", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      reset;
    tlmNetInputPort      dint;
    tlmNetInputPort      hwint0;
    tlmNetInputPort      hwint1;
    tlmNetInputPort      hwint2;
    tlmNetInputPort      hwint3;
    tlmNetInputPort      hwint4;
    tlmNetInputPort      hwint5;
    tlmNetInputPort      nmi;
    tlmNetInputPort      vc_run;

    mips32_r1r5_74Kc(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 32)
    , DATA (parent, this, "DATA", 32)
    , reset(parent, this, "reset")
    , dint(parent, this, "dint")
    , hwint0(parent, this, "hwint0")
    , hwint1(parent, this, "hwint1")
    , hwint2(parent, this, "hwint2")
    , hwint3(parent, this, "hwint3")
    , hwint4(parent, this, "hwint4")
    , hwint5(parent, this, "hwint5")
    , nmi(parent, this, "nmi")
    , vc_run(parent, this, "vc_run")
    {
    }

    mips32_r1r5_74Kc(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , reset(parent, this, "reset")
    , dint(parent, this, "dint")
    , hwint0(parent, this, "hwint0")
    , hwint1(parent, this, "hwint1")
    , hwint2(parent, this, "hwint2")
    , hwint3(parent, this, "hwint3")
    , hwint4(parent, this, "hwint4")
    , hwint5(parent, this, "hwint5")
    , nmi(parent, this, "nmi")
    , vc_run(parent, this, "vc_run")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class mips32_r1r5_74Kc */


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

class mips32_M5150 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "M5150");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "M5150");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "mips.ovpworld.org", "processor", "mips32", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     ISPRAM;
    tlmBusMasterPort     DSPRAM;
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      reset;
    tlmNetInputPort      softreset;
    tlmNetInputPort      dint;
    tlmNetInputPort      hwint0;
    tlmNetInputPort      hwint1;
    tlmNetInputPort      hwint2;
    tlmNetInputPort      hwint3;
    tlmNetInputPort      hwint4;
    tlmNetInputPort      hwint5;
    tlmNetInputPort      hwint6;
    tlmNetInputPort      hwint7;
    tlmNetInputPort      nmi;
    tlmNetInputPort      EICPresent;
    tlmNetInputPort      EIC_RIPL;
    tlmNetInputPort      EIC_EICSS;
    tlmNetInputPort      EIC_VectorNum;
    tlmNetInputPort      EIC_VectorOffset;
    tlmNetInputPort      EIC_GID;
    tlmNetOutputPort     intISS;
    tlmNetOutputPort     causeTI;
    tlmNetOutputPort     causeIP0;
    tlmNetOutputPort     causeIP1;
    tlmNetOutputPort     si_sleep;
    tlmNetInputPort      vc_run;
    tlmNetInputPort      Guest_EIC_RIPL;
    tlmNetInputPort      Guest_EIC_EICSS;
    tlmNetInputPort      Guest_EIC_VectorNum;
    tlmNetInputPort      Guest_EIC_VectorOffset;
    tlmNetInputPort      Guest_EIC_GID;
    tlmNetOutputPort     Guest_intISS;
    tlmNetOutputPort     Guest_causeTI;
    tlmNetOutputPort     Guest_causeIP0;
    tlmNetOutputPort     Guest_causeIP1;

    mips32_M5150(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , ISPRAM (parent, this, "ISPRAM", 32)
    , DSPRAM (parent, this, "DSPRAM", 32)
    , INSTRUCTION (parent, this, "INSTRUCTION", 32)
    , DATA (parent, this, "DATA", 32)
    , reset(parent, this, "reset")
    , softreset(parent, this, "softreset")
    , dint(parent, this, "dint")
    , hwint0(parent, this, "hwint0")
    , hwint1(parent, this, "hwint1")
    , hwint2(parent, this, "hwint2")
    , hwint3(parent, this, "hwint3")
    , hwint4(parent, this, "hwint4")
    , hwint5(parent, this, "hwint5")
    , hwint6(parent, this, "hwint6")
    , hwint7(parent, this, "hwint7")
    , nmi(parent, this, "nmi")
    , EICPresent(parent, this, "EICPresent")
    , EIC_RIPL(parent, this, "EIC_RIPL")
    , EIC_EICSS(parent, this, "EIC_EICSS")
    , EIC_VectorNum(parent, this, "EIC_VectorNum")
    , EIC_VectorOffset(parent, this, "EIC_VectorOffset")
    , EIC_GID(parent, this, "EIC_GID")
    , intISS(parent, this, "intISS")
    , causeTI(parent, this, "causeTI")
    , causeIP0(parent, this, "causeIP0")
    , causeIP1(parent, this, "causeIP1")
    , si_sleep(parent, this, "si_sleep")
    , vc_run(parent, this, "vc_run")
    , Guest_EIC_RIPL(parent, this, "Guest.EIC_RIPL")
    , Guest_EIC_EICSS(parent, this, "Guest.EIC_EICSS")
    , Guest_EIC_VectorNum(parent, this, "Guest.EIC_VectorNum")
    , Guest_EIC_VectorOffset(parent, this, "Guest.EIC_VectorOffset")
    , Guest_EIC_GID(parent, this, "Guest.EIC_GID")
    , Guest_intISS(parent, this, "Guest.intISS")
    , Guest_causeTI(parent, this, "Guest.causeTI")
    , Guest_causeIP0(parent, this, "Guest.causeIP0")
    , Guest_causeIP1(parent, this, "Guest.causeIP1")
    {
    }

    mips32_M5150(tlmModule &parent, sc_module_name name, params p, Uns32 ISPRAMWidth=32, Uns32 DSPRAMWidth=32, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , ISPRAM (parent, this, "ISPRAM", ISPRAMWidth)
    , DSPRAM (parent, this, "DSPRAM", DSPRAMWidth)
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , reset(parent, this, "reset")
    , softreset(parent, this, "softreset")
    , dint(parent, this, "dint")
    , hwint0(parent, this, "hwint0")
    , hwint1(parent, this, "hwint1")
    , hwint2(parent, this, "hwint2")
    , hwint3(parent, this, "hwint3")
    , hwint4(parent, this, "hwint4")
    , hwint5(parent, this, "hwint5")
    , hwint6(parent, this, "hwint6")
    , hwint7(parent, this, "hwint7")
    , nmi(parent, this, "nmi")
    , EICPresent(parent, this, "EICPresent")
    , EIC_RIPL(parent, this, "EIC_RIPL")
    , EIC_EICSS(parent, this, "EIC_EICSS")
    , EIC_VectorNum(parent, this, "EIC_VectorNum")
    , EIC_VectorOffset(parent, this, "EIC_VectorOffset")
    , EIC_GID(parent, this, "EIC_GID")
    , intISS(parent, this, "intISS")
    , causeTI(parent, this, "causeTI")
    , causeIP0(parent, this, "causeIP0")
    , causeIP1(parent, this, "causeIP1")
    , si_sleep(parent, this, "si_sleep")
    , vc_run(parent, this, "vc_run")
    , Guest_EIC_RIPL(parent, this, "Guest.EIC_RIPL")
    , Guest_EIC_EICSS(parent, this, "Guest.EIC_EICSS")
    , Guest_EIC_VectorNum(parent, this, "Guest.EIC_VectorNum")
    , Guest_EIC_VectorOffset(parent, this, "Guest.EIC_VectorOffset")
    , Guest_EIC_GID(parent, this, "Guest.EIC_GID")
    , Guest_intISS(parent, this, "Guest.intISS")
    , Guest_causeTI(parent, this, "Guest.causeTI")
    , Guest_causeIP0(parent, this, "Guest.causeIP0")
    , Guest_causeIP1(parent, this, "Guest.causeIP1")
    {
    }

    void before_end_of_elaboration() {
        ISPRAM.bindIfNotBound();
        DSPRAM.bindIfNotBound();
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        ISPRAM.dmi(on);
        DSPRAM.dmi(on);
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class mips32_M5150 */


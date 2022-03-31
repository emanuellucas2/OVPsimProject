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

class mips32_r1r5_34Kn : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "34Kn");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "34Kn");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "mips.ovpworld.org", "processor", "mips32_r1r5", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      yq;
    tlmNetInputPort      yq0;
    tlmNetInputPort      yq1;
    tlmNetInputPort      yq2;
    tlmNetInputPort      yq3;
    tlmNetInputPort      yq4;
    tlmNetInputPort      yq5;
    tlmNetInputPort      yq6;
    tlmNetInputPort      yq7;
    tlmNetInputPort      yq8;
    tlmNetInputPort      yq9;
    tlmNetInputPort      yq10;
    tlmNetInputPort      yq11;
    tlmNetInputPort      yq12;
    tlmNetInputPort      yq13;
    tlmNetInputPort      yq14;
    tlmNetInputPort      yq15;
    tlmNetInputPort      reset;
    tlmNetInputPort      dint;
    tlmNetInputPort      SI_UseExceptionBase;
    tlmNetInputPort      SI_ExceptionBase;
    tlmNetInputPort      hwint0_VPE0;
    tlmNetInputPort      hwint1_VPE0;
    tlmNetInputPort      hwint2_VPE0;
    tlmNetInputPort      hwint3_VPE0;
    tlmNetInputPort      hwint4_VPE0;
    tlmNetInputPort      hwint5_VPE0;
    tlmNetInputPort      nmi_VPE0;
    tlmNetInputPort      hwint0;
    tlmNetInputPort      vc_run_VPE0;
    tlmNetInputPort      hwint0_VPE1;
    tlmNetInputPort      hwint1_VPE1;
    tlmNetInputPort      hwint2_VPE1;
    tlmNetInputPort      hwint3_VPE1;
    tlmNetInputPort      hwint4_VPE1;
    tlmNetInputPort      hwint5_VPE1;
    tlmNetInputPort      nmi_VPE1;
    tlmNetInputPort      vc_run_VPE1;

    mips32_r1r5_34Kn(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 32)
    , DATA (parent, this, "DATA", 32)
    , yq(parent, this, "yq")
    , yq0(parent, this, "yq0")
    , yq1(parent, this, "yq1")
    , yq2(parent, this, "yq2")
    , yq3(parent, this, "yq3")
    , yq4(parent, this, "yq4")
    , yq5(parent, this, "yq5")
    , yq6(parent, this, "yq6")
    , yq7(parent, this, "yq7")
    , yq8(parent, this, "yq8")
    , yq9(parent, this, "yq9")
    , yq10(parent, this, "yq10")
    , yq11(parent, this, "yq11")
    , yq12(parent, this, "yq12")
    , yq13(parent, this, "yq13")
    , yq14(parent, this, "yq14")
    , yq15(parent, this, "yq15")
    , reset(parent, this, "reset")
    , dint(parent, this, "dint")
    , SI_UseExceptionBase(parent, this, "SI_UseExceptionBase")
    , SI_ExceptionBase(parent, this, "SI_ExceptionBase")
    , hwint0_VPE0(parent, this, "hwint0_VPE0")
    , hwint1_VPE0(parent, this, "hwint1_VPE0")
    , hwint2_VPE0(parent, this, "hwint2_VPE0")
    , hwint3_VPE0(parent, this, "hwint3_VPE0")
    , hwint4_VPE0(parent, this, "hwint4_VPE0")
    , hwint5_VPE0(parent, this, "hwint5_VPE0")
    , nmi_VPE0(parent, this, "nmi_VPE0")
    , hwint0(parent, this, "hwint0")
    , vc_run_VPE0(parent, this, "vc_run_VPE0")
    , hwint0_VPE1(parent, this, "hwint0_VPE1")
    , hwint1_VPE1(parent, this, "hwint1_VPE1")
    , hwint2_VPE1(parent, this, "hwint2_VPE1")
    , hwint3_VPE1(parent, this, "hwint3_VPE1")
    , hwint4_VPE1(parent, this, "hwint4_VPE1")
    , hwint5_VPE1(parent, this, "hwint5_VPE1")
    , nmi_VPE1(parent, this, "nmi_VPE1")
    , vc_run_VPE1(parent, this, "vc_run_VPE1")
    {
    }

    mips32_r1r5_34Kn(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , yq(parent, this, "yq")
    , yq0(parent, this, "yq0")
    , yq1(parent, this, "yq1")
    , yq2(parent, this, "yq2")
    , yq3(parent, this, "yq3")
    , yq4(parent, this, "yq4")
    , yq5(parent, this, "yq5")
    , yq6(parent, this, "yq6")
    , yq7(parent, this, "yq7")
    , yq8(parent, this, "yq8")
    , yq9(parent, this, "yq9")
    , yq10(parent, this, "yq10")
    , yq11(parent, this, "yq11")
    , yq12(parent, this, "yq12")
    , yq13(parent, this, "yq13")
    , yq14(parent, this, "yq14")
    , yq15(parent, this, "yq15")
    , reset(parent, this, "reset")
    , dint(parent, this, "dint")
    , SI_UseExceptionBase(parent, this, "SI_UseExceptionBase")
    , SI_ExceptionBase(parent, this, "SI_ExceptionBase")
    , hwint0_VPE0(parent, this, "hwint0_VPE0")
    , hwint1_VPE0(parent, this, "hwint1_VPE0")
    , hwint2_VPE0(parent, this, "hwint2_VPE0")
    , hwint3_VPE0(parent, this, "hwint3_VPE0")
    , hwint4_VPE0(parent, this, "hwint4_VPE0")
    , hwint5_VPE0(parent, this, "hwint5_VPE0")
    , nmi_VPE0(parent, this, "nmi_VPE0")
    , hwint0(parent, this, "hwint0")
    , vc_run_VPE0(parent, this, "vc_run_VPE0")
    , hwint0_VPE1(parent, this, "hwint0_VPE1")
    , hwint1_VPE1(parent, this, "hwint1_VPE1")
    , hwint2_VPE1(parent, this, "hwint2_VPE1")
    , hwint3_VPE1(parent, this, "hwint3_VPE1")
    , hwint4_VPE1(parent, this, "hwint4_VPE1")
    , hwint5_VPE1(parent, this, "hwint5_VPE1")
    , nmi_VPE1(parent, this, "nmi_VPE1")
    , vc_run_VPE1(parent, this, "vc_run_VPE1")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class mips32_r1r5_34Kn */


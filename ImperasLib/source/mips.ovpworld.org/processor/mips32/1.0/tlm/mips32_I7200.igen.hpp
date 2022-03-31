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

class mips32_I7200 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "I7200");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "I7200");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "mips.ovpworld.org", "processor", "mips32", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmBusMasterPort     USPRAM;
    tlmNetInputPort      reset;
    tlmNetInputPort      dint;
    tlmNetInputPort      int0;
    tlmNetInputPort      int1;
    tlmNetInputPort      int2;
    tlmNetInputPort      int3;
    tlmNetInputPort      int4;
    tlmNetInputPort      int5;
    tlmNetInputPort      int6;
    tlmNetInputPort      int7;
    tlmNetInputPort      int8;
    tlmNetInputPort      int9;
    tlmNetInputPort      int10;
    tlmNetInputPort      int11;
    tlmNetInputPort      int12;
    tlmNetInputPort      int13;
    tlmNetInputPort      int14;
    tlmNetInputPort      int15;
    tlmNetInputPort      int16;
    tlmNetInputPort      int17;
    tlmNetInputPort      int18;
    tlmNetInputPort      int19;
    tlmNetInputPort      int20;
    tlmNetInputPort      int21;
    tlmNetInputPort      int22;
    tlmNetInputPort      int23;
    tlmNetInputPort      int24;
    tlmNetInputPort      int25;
    tlmNetInputPort      int26;
    tlmNetInputPort      int27;
    tlmNetInputPort      int28;
    tlmNetInputPort      int29;
    tlmNetInputPort      int30;
    tlmNetInputPort      int31;
    tlmNetInputPort      int32;
    tlmNetInputPort      int33;
    tlmNetInputPort      int34;
    tlmNetInputPort      int35;
    tlmNetInputPort      int36;
    tlmNetInputPort      int37;
    tlmNetInputPort      int38;
    tlmNetInputPort      int39;
    tlmNetInputPort      ej_disable_probe_debug;
    tlmNetInputPort      ejtagbrk_override;
    tlmNetInputPort      ej_dint_in;
    tlmNetOutputPort     GCR_CUSTOM_BASE;
    tlmNetOutputPort     GCR_CUSTOM_BASE_UPPER;
    tlmNetInputPort      yq_CPU0;
    tlmNetInputPort      yq0_CPU0;
    tlmNetInputPort      yq1_CPU0;
    tlmNetInputPort      yq2_CPU0;
    tlmNetInputPort      yq3_CPU0;
    tlmNetInputPort      yq4_CPU0;
    tlmNetInputPort      yq5_CPU0;
    tlmNetInputPort      yq6_CPU0;
    tlmNetInputPort      yq7_CPU0;
    tlmNetInputPort      yq8_CPU0;
    tlmNetInputPort      yq9_CPU0;
    tlmNetInputPort      yq10_CPU0;
    tlmNetInputPort      yq11_CPU0;
    tlmNetInputPort      yq12_CPU0;
    tlmNetInputPort      yq13_CPU0;
    tlmNetInputPort      yq14_CPU0;
    tlmNetInputPort      yq15_CPU0;
    tlmNetInputPort      dint_CPU0_VPE0;
    tlmNetInputPort      hwint0_CPU0_VPE0;
    tlmNetInputPort      hwint1_CPU0_VPE0;
    tlmNetInputPort      hwint2_CPU0_VPE0;
    tlmNetInputPort      hwint3_CPU0_VPE0;
    tlmNetInputPort      hwint4_CPU0_VPE0;
    tlmNetInputPort      hwint5_CPU0_VPE0;
    tlmNetInputPort      nmi_CPU0_VPE0;
    tlmNetInputPort      EICPresent_CPU0_VPE0;
    tlmNetInputPort      EIC_RIPL_CPU0_VPE0;
    tlmNetInputPort      EIC_EICSS_CPU0_VPE0;
    tlmNetInputPort      EIC_VectorNum_CPU0_VPE0;
    tlmNetInputPort      EIC_VectorOffset_CPU0_VPE0;
    tlmNetOutputPort     intISS_CPU0_VPE0;
    tlmNetOutputPort     causeTI_CPU0_VPE0;
    tlmNetOutputPort     causeIP0_CPU0_VPE0;
    tlmNetOutputPort     causeIP1_CPU0_VPE0;
    tlmNetOutputPort     si_sleep_CPU0_VPE0;
    tlmNetInputPort      hwint0;
    tlmNetInputPort      vc_run_CPU0_VPE0;
    tlmNetInputPort      dint_CPU0_VPE1;
    tlmNetInputPort      hwint0_CPU0_VPE1;
    tlmNetInputPort      hwint1_CPU0_VPE1;
    tlmNetInputPort      hwint2_CPU0_VPE1;
    tlmNetInputPort      hwint3_CPU0_VPE1;
    tlmNetInputPort      hwint4_CPU0_VPE1;
    tlmNetInputPort      hwint5_CPU0_VPE1;
    tlmNetInputPort      nmi_CPU0_VPE1;
    tlmNetInputPort      EICPresent_CPU0_VPE1;
    tlmNetInputPort      EIC_RIPL_CPU0_VPE1;
    tlmNetInputPort      EIC_EICSS_CPU0_VPE1;
    tlmNetInputPort      EIC_VectorNum_CPU0_VPE1;
    tlmNetInputPort      EIC_VectorOffset_CPU0_VPE1;
    tlmNetOutputPort     intISS_CPU0_VPE1;
    tlmNetOutputPort     causeTI_CPU0_VPE1;
    tlmNetOutputPort     causeIP0_CPU0_VPE1;
    tlmNetOutputPort     causeIP1_CPU0_VPE1;
    tlmNetOutputPort     si_sleep_CPU0_VPE1;
    tlmNetInputPort      vc_run_CPU0_VPE1;
    tlmNetInputPort      yq_CPU1;
    tlmNetInputPort      yq0_CPU1;
    tlmNetInputPort      yq1_CPU1;
    tlmNetInputPort      yq2_CPU1;
    tlmNetInputPort      yq3_CPU1;
    tlmNetInputPort      yq4_CPU1;
    tlmNetInputPort      yq5_CPU1;
    tlmNetInputPort      yq6_CPU1;
    tlmNetInputPort      yq7_CPU1;
    tlmNetInputPort      yq8_CPU1;
    tlmNetInputPort      yq9_CPU1;
    tlmNetInputPort      yq10_CPU1;
    tlmNetInputPort      yq11_CPU1;
    tlmNetInputPort      yq12_CPU1;
    tlmNetInputPort      yq13_CPU1;
    tlmNetInputPort      yq14_CPU1;
    tlmNetInputPort      yq15_CPU1;
    tlmNetInputPort      dint_CPU1_VPE0;
    tlmNetInputPort      hwint0_CPU1_VPE0;
    tlmNetInputPort      hwint1_CPU1_VPE0;
    tlmNetInputPort      hwint2_CPU1_VPE0;
    tlmNetInputPort      hwint3_CPU1_VPE0;
    tlmNetInputPort      hwint4_CPU1_VPE0;
    tlmNetInputPort      hwint5_CPU1_VPE0;
    tlmNetInputPort      nmi_CPU1_VPE0;
    tlmNetInputPort      EICPresent_CPU1_VPE0;
    tlmNetInputPort      EIC_RIPL_CPU1_VPE0;
    tlmNetInputPort      EIC_EICSS_CPU1_VPE0;
    tlmNetInputPort      EIC_VectorNum_CPU1_VPE0;
    tlmNetInputPort      EIC_VectorOffset_CPU1_VPE0;
    tlmNetOutputPort     intISS_CPU1_VPE0;
    tlmNetOutputPort     causeTI_CPU1_VPE0;
    tlmNetOutputPort     causeIP0_CPU1_VPE0;
    tlmNetOutputPort     causeIP1_CPU1_VPE0;
    tlmNetOutputPort     si_sleep_CPU1_VPE0;
    tlmNetInputPort      vc_run_CPU1_VPE0;
    tlmNetInputPort      dint_CPU1_VPE1;
    tlmNetInputPort      hwint0_CPU1_VPE1;
    tlmNetInputPort      hwint1_CPU1_VPE1;
    tlmNetInputPort      hwint2_CPU1_VPE1;
    tlmNetInputPort      hwint3_CPU1_VPE1;
    tlmNetInputPort      hwint4_CPU1_VPE1;
    tlmNetInputPort      hwint5_CPU1_VPE1;
    tlmNetInputPort      nmi_CPU1_VPE1;
    tlmNetInputPort      EICPresent_CPU1_VPE1;
    tlmNetInputPort      EIC_RIPL_CPU1_VPE1;
    tlmNetInputPort      EIC_EICSS_CPU1_VPE1;
    tlmNetInputPort      EIC_VectorNum_CPU1_VPE1;
    tlmNetInputPort      EIC_VectorOffset_CPU1_VPE1;
    tlmNetOutputPort     intISS_CPU1_VPE1;
    tlmNetOutputPort     causeTI_CPU1_VPE1;
    tlmNetOutputPort     causeIP0_CPU1_VPE1;
    tlmNetOutputPort     causeIP1_CPU1_VPE1;
    tlmNetOutputPort     si_sleep_CPU1_VPE1;
    tlmNetInputPort      vc_run_CPU1_VPE1;
    tlmNetInputPort      yq_CPU2;
    tlmNetInputPort      yq0_CPU2;
    tlmNetInputPort      yq1_CPU2;
    tlmNetInputPort      yq2_CPU2;
    tlmNetInputPort      yq3_CPU2;
    tlmNetInputPort      yq4_CPU2;
    tlmNetInputPort      yq5_CPU2;
    tlmNetInputPort      yq6_CPU2;
    tlmNetInputPort      yq7_CPU2;
    tlmNetInputPort      yq8_CPU2;
    tlmNetInputPort      yq9_CPU2;
    tlmNetInputPort      yq10_CPU2;
    tlmNetInputPort      yq11_CPU2;
    tlmNetInputPort      yq12_CPU2;
    tlmNetInputPort      yq13_CPU2;
    tlmNetInputPort      yq14_CPU2;
    tlmNetInputPort      yq15_CPU2;
    tlmNetInputPort      dint_CPU2_VPE0;
    tlmNetInputPort      hwint0_CPU2_VPE0;
    tlmNetInputPort      hwint1_CPU2_VPE0;
    tlmNetInputPort      hwint2_CPU2_VPE0;
    tlmNetInputPort      hwint3_CPU2_VPE0;
    tlmNetInputPort      hwint4_CPU2_VPE0;
    tlmNetInputPort      hwint5_CPU2_VPE0;
    tlmNetInputPort      nmi_CPU2_VPE0;
    tlmNetInputPort      EICPresent_CPU2_VPE0;
    tlmNetInputPort      EIC_RIPL_CPU2_VPE0;
    tlmNetInputPort      EIC_EICSS_CPU2_VPE0;
    tlmNetInputPort      EIC_VectorNum_CPU2_VPE0;
    tlmNetInputPort      EIC_VectorOffset_CPU2_VPE0;
    tlmNetOutputPort     intISS_CPU2_VPE0;
    tlmNetOutputPort     causeTI_CPU2_VPE0;
    tlmNetOutputPort     causeIP0_CPU2_VPE0;
    tlmNetOutputPort     causeIP1_CPU2_VPE0;
    tlmNetOutputPort     si_sleep_CPU2_VPE0;
    tlmNetInputPort      vc_run_CPU2_VPE0;
    tlmNetInputPort      dint_CPU2_VPE1;
    tlmNetInputPort      hwint0_CPU2_VPE1;
    tlmNetInputPort      hwint1_CPU2_VPE1;
    tlmNetInputPort      hwint2_CPU2_VPE1;
    tlmNetInputPort      hwint3_CPU2_VPE1;
    tlmNetInputPort      hwint4_CPU2_VPE1;
    tlmNetInputPort      hwint5_CPU2_VPE1;
    tlmNetInputPort      nmi_CPU2_VPE1;
    tlmNetInputPort      EICPresent_CPU2_VPE1;
    tlmNetInputPort      EIC_RIPL_CPU2_VPE1;
    tlmNetInputPort      EIC_EICSS_CPU2_VPE1;
    tlmNetInputPort      EIC_VectorNum_CPU2_VPE1;
    tlmNetInputPort      EIC_VectorOffset_CPU2_VPE1;
    tlmNetOutputPort     intISS_CPU2_VPE1;
    tlmNetOutputPort     causeTI_CPU2_VPE1;
    tlmNetOutputPort     causeIP0_CPU2_VPE1;
    tlmNetOutputPort     causeIP1_CPU2_VPE1;
    tlmNetOutputPort     si_sleep_CPU2_VPE1;
    tlmNetInputPort      vc_run_CPU2_VPE1;
    tlmNetInputPort      yq_CPU3;
    tlmNetInputPort      yq0_CPU3;
    tlmNetInputPort      yq1_CPU3;
    tlmNetInputPort      yq2_CPU3;
    tlmNetInputPort      yq3_CPU3;
    tlmNetInputPort      yq4_CPU3;
    tlmNetInputPort      yq5_CPU3;
    tlmNetInputPort      yq6_CPU3;
    tlmNetInputPort      yq7_CPU3;
    tlmNetInputPort      yq8_CPU3;
    tlmNetInputPort      yq9_CPU3;
    tlmNetInputPort      yq10_CPU3;
    tlmNetInputPort      yq11_CPU3;
    tlmNetInputPort      yq12_CPU3;
    tlmNetInputPort      yq13_CPU3;
    tlmNetInputPort      yq14_CPU3;
    tlmNetInputPort      yq15_CPU3;
    tlmNetInputPort      dint_CPU3_VPE0;
    tlmNetInputPort      hwint0_CPU3_VPE0;
    tlmNetInputPort      hwint1_CPU3_VPE0;
    tlmNetInputPort      hwint2_CPU3_VPE0;
    tlmNetInputPort      hwint3_CPU3_VPE0;
    tlmNetInputPort      hwint4_CPU3_VPE0;
    tlmNetInputPort      hwint5_CPU3_VPE0;
    tlmNetInputPort      nmi_CPU3_VPE0;
    tlmNetInputPort      EICPresent_CPU3_VPE0;
    tlmNetInputPort      EIC_RIPL_CPU3_VPE0;
    tlmNetInputPort      EIC_EICSS_CPU3_VPE0;
    tlmNetInputPort      EIC_VectorNum_CPU3_VPE0;
    tlmNetInputPort      EIC_VectorOffset_CPU3_VPE0;
    tlmNetOutputPort     intISS_CPU3_VPE0;
    tlmNetOutputPort     causeTI_CPU3_VPE0;
    tlmNetOutputPort     causeIP0_CPU3_VPE0;
    tlmNetOutputPort     causeIP1_CPU3_VPE0;
    tlmNetOutputPort     si_sleep_CPU3_VPE0;
    tlmNetInputPort      vc_run_CPU3_VPE0;
    tlmNetInputPort      dint_CPU3_VPE1;
    tlmNetInputPort      hwint0_CPU3_VPE1;
    tlmNetInputPort      hwint1_CPU3_VPE1;
    tlmNetInputPort      hwint2_CPU3_VPE1;
    tlmNetInputPort      hwint3_CPU3_VPE1;
    tlmNetInputPort      hwint4_CPU3_VPE1;
    tlmNetInputPort      hwint5_CPU3_VPE1;
    tlmNetInputPort      nmi_CPU3_VPE1;
    tlmNetInputPort      EICPresent_CPU3_VPE1;
    tlmNetInputPort      EIC_RIPL_CPU3_VPE1;
    tlmNetInputPort      EIC_EICSS_CPU3_VPE1;
    tlmNetInputPort      EIC_VectorNum_CPU3_VPE1;
    tlmNetInputPort      EIC_VectorOffset_CPU3_VPE1;
    tlmNetOutputPort     intISS_CPU3_VPE1;
    tlmNetOutputPort     causeTI_CPU3_VPE1;
    tlmNetOutputPort     causeIP0_CPU3_VPE1;
    tlmNetOutputPort     causeIP1_CPU3_VPE1;
    tlmNetOutputPort     si_sleep_CPU3_VPE1;
    tlmNetInputPort      vc_run_CPU3_VPE1;

    mips32_I7200(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 32)
    , DATA (parent, this, "DATA", 32)
    , USPRAM (parent, this, "USPRAM", 32)
    , reset(parent, this, "reset")
    , dint(parent, this, "dint")
    , int0(parent, this, "int0")
    , int1(parent, this, "int1")
    , int2(parent, this, "int2")
    , int3(parent, this, "int3")
    , int4(parent, this, "int4")
    , int5(parent, this, "int5")
    , int6(parent, this, "int6")
    , int7(parent, this, "int7")
    , int8(parent, this, "int8")
    , int9(parent, this, "int9")
    , int10(parent, this, "int10")
    , int11(parent, this, "int11")
    , int12(parent, this, "int12")
    , int13(parent, this, "int13")
    , int14(parent, this, "int14")
    , int15(parent, this, "int15")
    , int16(parent, this, "int16")
    , int17(parent, this, "int17")
    , int18(parent, this, "int18")
    , int19(parent, this, "int19")
    , int20(parent, this, "int20")
    , int21(parent, this, "int21")
    , int22(parent, this, "int22")
    , int23(parent, this, "int23")
    , int24(parent, this, "int24")
    , int25(parent, this, "int25")
    , int26(parent, this, "int26")
    , int27(parent, this, "int27")
    , int28(parent, this, "int28")
    , int29(parent, this, "int29")
    , int30(parent, this, "int30")
    , int31(parent, this, "int31")
    , int32(parent, this, "int32")
    , int33(parent, this, "int33")
    , int34(parent, this, "int34")
    , int35(parent, this, "int35")
    , int36(parent, this, "int36")
    , int37(parent, this, "int37")
    , int38(parent, this, "int38")
    , int39(parent, this, "int39")
    , ej_disable_probe_debug(parent, this, "ej_disable_probe_debug")
    , ejtagbrk_override(parent, this, "ejtagbrk_override")
    , ej_dint_in(parent, this, "ej_dint_in")
    , GCR_CUSTOM_BASE(parent, this, "GCR_CUSTOM_BASE")
    , GCR_CUSTOM_BASE_UPPER(parent, this, "GCR_CUSTOM_BASE_UPPER")
    , yq_CPU0(parent, this, "yq_CPU0")
    , yq0_CPU0(parent, this, "yq0_CPU0")
    , yq1_CPU0(parent, this, "yq1_CPU0")
    , yq2_CPU0(parent, this, "yq2_CPU0")
    , yq3_CPU0(parent, this, "yq3_CPU0")
    , yq4_CPU0(parent, this, "yq4_CPU0")
    , yq5_CPU0(parent, this, "yq5_CPU0")
    , yq6_CPU0(parent, this, "yq6_CPU0")
    , yq7_CPU0(parent, this, "yq7_CPU0")
    , yq8_CPU0(parent, this, "yq8_CPU0")
    , yq9_CPU0(parent, this, "yq9_CPU0")
    , yq10_CPU0(parent, this, "yq10_CPU0")
    , yq11_CPU0(parent, this, "yq11_CPU0")
    , yq12_CPU0(parent, this, "yq12_CPU0")
    , yq13_CPU0(parent, this, "yq13_CPU0")
    , yq14_CPU0(parent, this, "yq14_CPU0")
    , yq15_CPU0(parent, this, "yq15_CPU0")
    , dint_CPU0_VPE0(parent, this, "dint_CPU0_VPE0")
    , hwint0_CPU0_VPE0(parent, this, "hwint0_CPU0_VPE0")
    , hwint1_CPU0_VPE0(parent, this, "hwint1_CPU0_VPE0")
    , hwint2_CPU0_VPE0(parent, this, "hwint2_CPU0_VPE0")
    , hwint3_CPU0_VPE0(parent, this, "hwint3_CPU0_VPE0")
    , hwint4_CPU0_VPE0(parent, this, "hwint4_CPU0_VPE0")
    , hwint5_CPU0_VPE0(parent, this, "hwint5_CPU0_VPE0")
    , nmi_CPU0_VPE0(parent, this, "nmi_CPU0_VPE0")
    , EICPresent_CPU0_VPE0(parent, this, "EICPresent_CPU0_VPE0")
    , EIC_RIPL_CPU0_VPE0(parent, this, "EIC_RIPL_CPU0_VPE0")
    , EIC_EICSS_CPU0_VPE0(parent, this, "EIC_EICSS_CPU0_VPE0")
    , EIC_VectorNum_CPU0_VPE0(parent, this, "EIC_VectorNum_CPU0_VPE0")
    , EIC_VectorOffset_CPU0_VPE0(parent, this, "EIC_VectorOffset_CPU0_VPE0")
    , intISS_CPU0_VPE0(parent, this, "intISS_CPU0_VPE0")
    , causeTI_CPU0_VPE0(parent, this, "causeTI_CPU0_VPE0")
    , causeIP0_CPU0_VPE0(parent, this, "causeIP0_CPU0_VPE0")
    , causeIP1_CPU0_VPE0(parent, this, "causeIP1_CPU0_VPE0")
    , si_sleep_CPU0_VPE0(parent, this, "si_sleep_CPU0_VPE0")
    , hwint0(parent, this, "hwint0")
    , vc_run_CPU0_VPE0(parent, this, "vc_run_CPU0_VPE0")
    , dint_CPU0_VPE1(parent, this, "dint_CPU0_VPE1")
    , hwint0_CPU0_VPE1(parent, this, "hwint0_CPU0_VPE1")
    , hwint1_CPU0_VPE1(parent, this, "hwint1_CPU0_VPE1")
    , hwint2_CPU0_VPE1(parent, this, "hwint2_CPU0_VPE1")
    , hwint3_CPU0_VPE1(parent, this, "hwint3_CPU0_VPE1")
    , hwint4_CPU0_VPE1(parent, this, "hwint4_CPU0_VPE1")
    , hwint5_CPU0_VPE1(parent, this, "hwint5_CPU0_VPE1")
    , nmi_CPU0_VPE1(parent, this, "nmi_CPU0_VPE1")
    , EICPresent_CPU0_VPE1(parent, this, "EICPresent_CPU0_VPE1")
    , EIC_RIPL_CPU0_VPE1(parent, this, "EIC_RIPL_CPU0_VPE1")
    , EIC_EICSS_CPU0_VPE1(parent, this, "EIC_EICSS_CPU0_VPE1")
    , EIC_VectorNum_CPU0_VPE1(parent, this, "EIC_VectorNum_CPU0_VPE1")
    , EIC_VectorOffset_CPU0_VPE1(parent, this, "EIC_VectorOffset_CPU0_VPE1")
    , intISS_CPU0_VPE1(parent, this, "intISS_CPU0_VPE1")
    , causeTI_CPU0_VPE1(parent, this, "causeTI_CPU0_VPE1")
    , causeIP0_CPU0_VPE1(parent, this, "causeIP0_CPU0_VPE1")
    , causeIP1_CPU0_VPE1(parent, this, "causeIP1_CPU0_VPE1")
    , si_sleep_CPU0_VPE1(parent, this, "si_sleep_CPU0_VPE1")
    , vc_run_CPU0_VPE1(parent, this, "vc_run_CPU0_VPE1")
    , yq_CPU1(parent, this, "yq_CPU1")
    , yq0_CPU1(parent, this, "yq0_CPU1")
    , yq1_CPU1(parent, this, "yq1_CPU1")
    , yq2_CPU1(parent, this, "yq2_CPU1")
    , yq3_CPU1(parent, this, "yq3_CPU1")
    , yq4_CPU1(parent, this, "yq4_CPU1")
    , yq5_CPU1(parent, this, "yq5_CPU1")
    , yq6_CPU1(parent, this, "yq6_CPU1")
    , yq7_CPU1(parent, this, "yq7_CPU1")
    , yq8_CPU1(parent, this, "yq8_CPU1")
    , yq9_CPU1(parent, this, "yq9_CPU1")
    , yq10_CPU1(parent, this, "yq10_CPU1")
    , yq11_CPU1(parent, this, "yq11_CPU1")
    , yq12_CPU1(parent, this, "yq12_CPU1")
    , yq13_CPU1(parent, this, "yq13_CPU1")
    , yq14_CPU1(parent, this, "yq14_CPU1")
    , yq15_CPU1(parent, this, "yq15_CPU1")
    , dint_CPU1_VPE0(parent, this, "dint_CPU1_VPE0")
    , hwint0_CPU1_VPE0(parent, this, "hwint0_CPU1_VPE0")
    , hwint1_CPU1_VPE0(parent, this, "hwint1_CPU1_VPE0")
    , hwint2_CPU1_VPE0(parent, this, "hwint2_CPU1_VPE0")
    , hwint3_CPU1_VPE0(parent, this, "hwint3_CPU1_VPE0")
    , hwint4_CPU1_VPE0(parent, this, "hwint4_CPU1_VPE0")
    , hwint5_CPU1_VPE0(parent, this, "hwint5_CPU1_VPE0")
    , nmi_CPU1_VPE0(parent, this, "nmi_CPU1_VPE0")
    , EICPresent_CPU1_VPE0(parent, this, "EICPresent_CPU1_VPE0")
    , EIC_RIPL_CPU1_VPE0(parent, this, "EIC_RIPL_CPU1_VPE0")
    , EIC_EICSS_CPU1_VPE0(parent, this, "EIC_EICSS_CPU1_VPE0")
    , EIC_VectorNum_CPU1_VPE0(parent, this, "EIC_VectorNum_CPU1_VPE0")
    , EIC_VectorOffset_CPU1_VPE0(parent, this, "EIC_VectorOffset_CPU1_VPE0")
    , intISS_CPU1_VPE0(parent, this, "intISS_CPU1_VPE0")
    , causeTI_CPU1_VPE0(parent, this, "causeTI_CPU1_VPE0")
    , causeIP0_CPU1_VPE0(parent, this, "causeIP0_CPU1_VPE0")
    , causeIP1_CPU1_VPE0(parent, this, "causeIP1_CPU1_VPE0")
    , si_sleep_CPU1_VPE0(parent, this, "si_sleep_CPU1_VPE0")
    , vc_run_CPU1_VPE0(parent, this, "vc_run_CPU1_VPE0")
    , dint_CPU1_VPE1(parent, this, "dint_CPU1_VPE1")
    , hwint0_CPU1_VPE1(parent, this, "hwint0_CPU1_VPE1")
    , hwint1_CPU1_VPE1(parent, this, "hwint1_CPU1_VPE1")
    , hwint2_CPU1_VPE1(parent, this, "hwint2_CPU1_VPE1")
    , hwint3_CPU1_VPE1(parent, this, "hwint3_CPU1_VPE1")
    , hwint4_CPU1_VPE1(parent, this, "hwint4_CPU1_VPE1")
    , hwint5_CPU1_VPE1(parent, this, "hwint5_CPU1_VPE1")
    , nmi_CPU1_VPE1(parent, this, "nmi_CPU1_VPE1")
    , EICPresent_CPU1_VPE1(parent, this, "EICPresent_CPU1_VPE1")
    , EIC_RIPL_CPU1_VPE1(parent, this, "EIC_RIPL_CPU1_VPE1")
    , EIC_EICSS_CPU1_VPE1(parent, this, "EIC_EICSS_CPU1_VPE1")
    , EIC_VectorNum_CPU1_VPE1(parent, this, "EIC_VectorNum_CPU1_VPE1")
    , EIC_VectorOffset_CPU1_VPE1(parent, this, "EIC_VectorOffset_CPU1_VPE1")
    , intISS_CPU1_VPE1(parent, this, "intISS_CPU1_VPE1")
    , causeTI_CPU1_VPE1(parent, this, "causeTI_CPU1_VPE1")
    , causeIP0_CPU1_VPE1(parent, this, "causeIP0_CPU1_VPE1")
    , causeIP1_CPU1_VPE1(parent, this, "causeIP1_CPU1_VPE1")
    , si_sleep_CPU1_VPE1(parent, this, "si_sleep_CPU1_VPE1")
    , vc_run_CPU1_VPE1(parent, this, "vc_run_CPU1_VPE1")
    , yq_CPU2(parent, this, "yq_CPU2")
    , yq0_CPU2(parent, this, "yq0_CPU2")
    , yq1_CPU2(parent, this, "yq1_CPU2")
    , yq2_CPU2(parent, this, "yq2_CPU2")
    , yq3_CPU2(parent, this, "yq3_CPU2")
    , yq4_CPU2(parent, this, "yq4_CPU2")
    , yq5_CPU2(parent, this, "yq5_CPU2")
    , yq6_CPU2(parent, this, "yq6_CPU2")
    , yq7_CPU2(parent, this, "yq7_CPU2")
    , yq8_CPU2(parent, this, "yq8_CPU2")
    , yq9_CPU2(parent, this, "yq9_CPU2")
    , yq10_CPU2(parent, this, "yq10_CPU2")
    , yq11_CPU2(parent, this, "yq11_CPU2")
    , yq12_CPU2(parent, this, "yq12_CPU2")
    , yq13_CPU2(parent, this, "yq13_CPU2")
    , yq14_CPU2(parent, this, "yq14_CPU2")
    , yq15_CPU2(parent, this, "yq15_CPU2")
    , dint_CPU2_VPE0(parent, this, "dint_CPU2_VPE0")
    , hwint0_CPU2_VPE0(parent, this, "hwint0_CPU2_VPE0")
    , hwint1_CPU2_VPE0(parent, this, "hwint1_CPU2_VPE0")
    , hwint2_CPU2_VPE0(parent, this, "hwint2_CPU2_VPE0")
    , hwint3_CPU2_VPE0(parent, this, "hwint3_CPU2_VPE0")
    , hwint4_CPU2_VPE0(parent, this, "hwint4_CPU2_VPE0")
    , hwint5_CPU2_VPE0(parent, this, "hwint5_CPU2_VPE0")
    , nmi_CPU2_VPE0(parent, this, "nmi_CPU2_VPE0")
    , EICPresent_CPU2_VPE0(parent, this, "EICPresent_CPU2_VPE0")
    , EIC_RIPL_CPU2_VPE0(parent, this, "EIC_RIPL_CPU2_VPE0")
    , EIC_EICSS_CPU2_VPE0(parent, this, "EIC_EICSS_CPU2_VPE0")
    , EIC_VectorNum_CPU2_VPE0(parent, this, "EIC_VectorNum_CPU2_VPE0")
    , EIC_VectorOffset_CPU2_VPE0(parent, this, "EIC_VectorOffset_CPU2_VPE0")
    , intISS_CPU2_VPE0(parent, this, "intISS_CPU2_VPE0")
    , causeTI_CPU2_VPE0(parent, this, "causeTI_CPU2_VPE0")
    , causeIP0_CPU2_VPE0(parent, this, "causeIP0_CPU2_VPE0")
    , causeIP1_CPU2_VPE0(parent, this, "causeIP1_CPU2_VPE0")
    , si_sleep_CPU2_VPE0(parent, this, "si_sleep_CPU2_VPE0")
    , vc_run_CPU2_VPE0(parent, this, "vc_run_CPU2_VPE0")
    , dint_CPU2_VPE1(parent, this, "dint_CPU2_VPE1")
    , hwint0_CPU2_VPE1(parent, this, "hwint0_CPU2_VPE1")
    , hwint1_CPU2_VPE1(parent, this, "hwint1_CPU2_VPE1")
    , hwint2_CPU2_VPE1(parent, this, "hwint2_CPU2_VPE1")
    , hwint3_CPU2_VPE1(parent, this, "hwint3_CPU2_VPE1")
    , hwint4_CPU2_VPE1(parent, this, "hwint4_CPU2_VPE1")
    , hwint5_CPU2_VPE1(parent, this, "hwint5_CPU2_VPE1")
    , nmi_CPU2_VPE1(parent, this, "nmi_CPU2_VPE1")
    , EICPresent_CPU2_VPE1(parent, this, "EICPresent_CPU2_VPE1")
    , EIC_RIPL_CPU2_VPE1(parent, this, "EIC_RIPL_CPU2_VPE1")
    , EIC_EICSS_CPU2_VPE1(parent, this, "EIC_EICSS_CPU2_VPE1")
    , EIC_VectorNum_CPU2_VPE1(parent, this, "EIC_VectorNum_CPU2_VPE1")
    , EIC_VectorOffset_CPU2_VPE1(parent, this, "EIC_VectorOffset_CPU2_VPE1")
    , intISS_CPU2_VPE1(parent, this, "intISS_CPU2_VPE1")
    , causeTI_CPU2_VPE1(parent, this, "causeTI_CPU2_VPE1")
    , causeIP0_CPU2_VPE1(parent, this, "causeIP0_CPU2_VPE1")
    , causeIP1_CPU2_VPE1(parent, this, "causeIP1_CPU2_VPE1")
    , si_sleep_CPU2_VPE1(parent, this, "si_sleep_CPU2_VPE1")
    , vc_run_CPU2_VPE1(parent, this, "vc_run_CPU2_VPE1")
    , yq_CPU3(parent, this, "yq_CPU3")
    , yq0_CPU3(parent, this, "yq0_CPU3")
    , yq1_CPU3(parent, this, "yq1_CPU3")
    , yq2_CPU3(parent, this, "yq2_CPU3")
    , yq3_CPU3(parent, this, "yq3_CPU3")
    , yq4_CPU3(parent, this, "yq4_CPU3")
    , yq5_CPU3(parent, this, "yq5_CPU3")
    , yq6_CPU3(parent, this, "yq6_CPU3")
    , yq7_CPU3(parent, this, "yq7_CPU3")
    , yq8_CPU3(parent, this, "yq8_CPU3")
    , yq9_CPU3(parent, this, "yq9_CPU3")
    , yq10_CPU3(parent, this, "yq10_CPU3")
    , yq11_CPU3(parent, this, "yq11_CPU3")
    , yq12_CPU3(parent, this, "yq12_CPU3")
    , yq13_CPU3(parent, this, "yq13_CPU3")
    , yq14_CPU3(parent, this, "yq14_CPU3")
    , yq15_CPU3(parent, this, "yq15_CPU3")
    , dint_CPU3_VPE0(parent, this, "dint_CPU3_VPE0")
    , hwint0_CPU3_VPE0(parent, this, "hwint0_CPU3_VPE0")
    , hwint1_CPU3_VPE0(parent, this, "hwint1_CPU3_VPE0")
    , hwint2_CPU3_VPE0(parent, this, "hwint2_CPU3_VPE0")
    , hwint3_CPU3_VPE0(parent, this, "hwint3_CPU3_VPE0")
    , hwint4_CPU3_VPE0(parent, this, "hwint4_CPU3_VPE0")
    , hwint5_CPU3_VPE0(parent, this, "hwint5_CPU3_VPE0")
    , nmi_CPU3_VPE0(parent, this, "nmi_CPU3_VPE0")
    , EICPresent_CPU3_VPE0(parent, this, "EICPresent_CPU3_VPE0")
    , EIC_RIPL_CPU3_VPE0(parent, this, "EIC_RIPL_CPU3_VPE0")
    , EIC_EICSS_CPU3_VPE0(parent, this, "EIC_EICSS_CPU3_VPE0")
    , EIC_VectorNum_CPU3_VPE0(parent, this, "EIC_VectorNum_CPU3_VPE0")
    , EIC_VectorOffset_CPU3_VPE0(parent, this, "EIC_VectorOffset_CPU3_VPE0")
    , intISS_CPU3_VPE0(parent, this, "intISS_CPU3_VPE0")
    , causeTI_CPU3_VPE0(parent, this, "causeTI_CPU3_VPE0")
    , causeIP0_CPU3_VPE0(parent, this, "causeIP0_CPU3_VPE0")
    , causeIP1_CPU3_VPE0(parent, this, "causeIP1_CPU3_VPE0")
    , si_sleep_CPU3_VPE0(parent, this, "si_sleep_CPU3_VPE0")
    , vc_run_CPU3_VPE0(parent, this, "vc_run_CPU3_VPE0")
    , dint_CPU3_VPE1(parent, this, "dint_CPU3_VPE1")
    , hwint0_CPU3_VPE1(parent, this, "hwint0_CPU3_VPE1")
    , hwint1_CPU3_VPE1(parent, this, "hwint1_CPU3_VPE1")
    , hwint2_CPU3_VPE1(parent, this, "hwint2_CPU3_VPE1")
    , hwint3_CPU3_VPE1(parent, this, "hwint3_CPU3_VPE1")
    , hwint4_CPU3_VPE1(parent, this, "hwint4_CPU3_VPE1")
    , hwint5_CPU3_VPE1(parent, this, "hwint5_CPU3_VPE1")
    , nmi_CPU3_VPE1(parent, this, "nmi_CPU3_VPE1")
    , EICPresent_CPU3_VPE1(parent, this, "EICPresent_CPU3_VPE1")
    , EIC_RIPL_CPU3_VPE1(parent, this, "EIC_RIPL_CPU3_VPE1")
    , EIC_EICSS_CPU3_VPE1(parent, this, "EIC_EICSS_CPU3_VPE1")
    , EIC_VectorNum_CPU3_VPE1(parent, this, "EIC_VectorNum_CPU3_VPE1")
    , EIC_VectorOffset_CPU3_VPE1(parent, this, "EIC_VectorOffset_CPU3_VPE1")
    , intISS_CPU3_VPE1(parent, this, "intISS_CPU3_VPE1")
    , causeTI_CPU3_VPE1(parent, this, "causeTI_CPU3_VPE1")
    , causeIP0_CPU3_VPE1(parent, this, "causeIP0_CPU3_VPE1")
    , causeIP1_CPU3_VPE1(parent, this, "causeIP1_CPU3_VPE1")
    , si_sleep_CPU3_VPE1(parent, this, "si_sleep_CPU3_VPE1")
    , vc_run_CPU3_VPE1(parent, this, "vc_run_CPU3_VPE1")
    {
    }

    mips32_I7200(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32, Uns32 USPRAMWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , USPRAM (parent, this, "USPRAM", USPRAMWidth)
    , reset(parent, this, "reset")
    , dint(parent, this, "dint")
    , int0(parent, this, "int0")
    , int1(parent, this, "int1")
    , int2(parent, this, "int2")
    , int3(parent, this, "int3")
    , int4(parent, this, "int4")
    , int5(parent, this, "int5")
    , int6(parent, this, "int6")
    , int7(parent, this, "int7")
    , int8(parent, this, "int8")
    , int9(parent, this, "int9")
    , int10(parent, this, "int10")
    , int11(parent, this, "int11")
    , int12(parent, this, "int12")
    , int13(parent, this, "int13")
    , int14(parent, this, "int14")
    , int15(parent, this, "int15")
    , int16(parent, this, "int16")
    , int17(parent, this, "int17")
    , int18(parent, this, "int18")
    , int19(parent, this, "int19")
    , int20(parent, this, "int20")
    , int21(parent, this, "int21")
    , int22(parent, this, "int22")
    , int23(parent, this, "int23")
    , int24(parent, this, "int24")
    , int25(parent, this, "int25")
    , int26(parent, this, "int26")
    , int27(parent, this, "int27")
    , int28(parent, this, "int28")
    , int29(parent, this, "int29")
    , int30(parent, this, "int30")
    , int31(parent, this, "int31")
    , int32(parent, this, "int32")
    , int33(parent, this, "int33")
    , int34(parent, this, "int34")
    , int35(parent, this, "int35")
    , int36(parent, this, "int36")
    , int37(parent, this, "int37")
    , int38(parent, this, "int38")
    , int39(parent, this, "int39")
    , ej_disable_probe_debug(parent, this, "ej_disable_probe_debug")
    , ejtagbrk_override(parent, this, "ejtagbrk_override")
    , ej_dint_in(parent, this, "ej_dint_in")
    , GCR_CUSTOM_BASE(parent, this, "GCR_CUSTOM_BASE")
    , GCR_CUSTOM_BASE_UPPER(parent, this, "GCR_CUSTOM_BASE_UPPER")
    , yq_CPU0(parent, this, "yq_CPU0")
    , yq0_CPU0(parent, this, "yq0_CPU0")
    , yq1_CPU0(parent, this, "yq1_CPU0")
    , yq2_CPU0(parent, this, "yq2_CPU0")
    , yq3_CPU0(parent, this, "yq3_CPU0")
    , yq4_CPU0(parent, this, "yq4_CPU0")
    , yq5_CPU0(parent, this, "yq5_CPU0")
    , yq6_CPU0(parent, this, "yq6_CPU0")
    , yq7_CPU0(parent, this, "yq7_CPU0")
    , yq8_CPU0(parent, this, "yq8_CPU0")
    , yq9_CPU0(parent, this, "yq9_CPU0")
    , yq10_CPU0(parent, this, "yq10_CPU0")
    , yq11_CPU0(parent, this, "yq11_CPU0")
    , yq12_CPU0(parent, this, "yq12_CPU0")
    , yq13_CPU0(parent, this, "yq13_CPU0")
    , yq14_CPU0(parent, this, "yq14_CPU0")
    , yq15_CPU0(parent, this, "yq15_CPU0")
    , dint_CPU0_VPE0(parent, this, "dint_CPU0_VPE0")
    , hwint0_CPU0_VPE0(parent, this, "hwint0_CPU0_VPE0")
    , hwint1_CPU0_VPE0(parent, this, "hwint1_CPU0_VPE0")
    , hwint2_CPU0_VPE0(parent, this, "hwint2_CPU0_VPE0")
    , hwint3_CPU0_VPE0(parent, this, "hwint3_CPU0_VPE0")
    , hwint4_CPU0_VPE0(parent, this, "hwint4_CPU0_VPE0")
    , hwint5_CPU0_VPE0(parent, this, "hwint5_CPU0_VPE0")
    , nmi_CPU0_VPE0(parent, this, "nmi_CPU0_VPE0")
    , EICPresent_CPU0_VPE0(parent, this, "EICPresent_CPU0_VPE0")
    , EIC_RIPL_CPU0_VPE0(parent, this, "EIC_RIPL_CPU0_VPE0")
    , EIC_EICSS_CPU0_VPE0(parent, this, "EIC_EICSS_CPU0_VPE0")
    , EIC_VectorNum_CPU0_VPE0(parent, this, "EIC_VectorNum_CPU0_VPE0")
    , EIC_VectorOffset_CPU0_VPE0(parent, this, "EIC_VectorOffset_CPU0_VPE0")
    , intISS_CPU0_VPE0(parent, this, "intISS_CPU0_VPE0")
    , causeTI_CPU0_VPE0(parent, this, "causeTI_CPU0_VPE0")
    , causeIP0_CPU0_VPE0(parent, this, "causeIP0_CPU0_VPE0")
    , causeIP1_CPU0_VPE0(parent, this, "causeIP1_CPU0_VPE0")
    , si_sleep_CPU0_VPE0(parent, this, "si_sleep_CPU0_VPE0")
    , hwint0(parent, this, "hwint0")
    , vc_run_CPU0_VPE0(parent, this, "vc_run_CPU0_VPE0")
    , dint_CPU0_VPE1(parent, this, "dint_CPU0_VPE1")
    , hwint0_CPU0_VPE1(parent, this, "hwint0_CPU0_VPE1")
    , hwint1_CPU0_VPE1(parent, this, "hwint1_CPU0_VPE1")
    , hwint2_CPU0_VPE1(parent, this, "hwint2_CPU0_VPE1")
    , hwint3_CPU0_VPE1(parent, this, "hwint3_CPU0_VPE1")
    , hwint4_CPU0_VPE1(parent, this, "hwint4_CPU0_VPE1")
    , hwint5_CPU0_VPE1(parent, this, "hwint5_CPU0_VPE1")
    , nmi_CPU0_VPE1(parent, this, "nmi_CPU0_VPE1")
    , EICPresent_CPU0_VPE1(parent, this, "EICPresent_CPU0_VPE1")
    , EIC_RIPL_CPU0_VPE1(parent, this, "EIC_RIPL_CPU0_VPE1")
    , EIC_EICSS_CPU0_VPE1(parent, this, "EIC_EICSS_CPU0_VPE1")
    , EIC_VectorNum_CPU0_VPE1(parent, this, "EIC_VectorNum_CPU0_VPE1")
    , EIC_VectorOffset_CPU0_VPE1(parent, this, "EIC_VectorOffset_CPU0_VPE1")
    , intISS_CPU0_VPE1(parent, this, "intISS_CPU0_VPE1")
    , causeTI_CPU0_VPE1(parent, this, "causeTI_CPU0_VPE1")
    , causeIP0_CPU0_VPE1(parent, this, "causeIP0_CPU0_VPE1")
    , causeIP1_CPU0_VPE1(parent, this, "causeIP1_CPU0_VPE1")
    , si_sleep_CPU0_VPE1(parent, this, "si_sleep_CPU0_VPE1")
    , vc_run_CPU0_VPE1(parent, this, "vc_run_CPU0_VPE1")
    , yq_CPU1(parent, this, "yq_CPU1")
    , yq0_CPU1(parent, this, "yq0_CPU1")
    , yq1_CPU1(parent, this, "yq1_CPU1")
    , yq2_CPU1(parent, this, "yq2_CPU1")
    , yq3_CPU1(parent, this, "yq3_CPU1")
    , yq4_CPU1(parent, this, "yq4_CPU1")
    , yq5_CPU1(parent, this, "yq5_CPU1")
    , yq6_CPU1(parent, this, "yq6_CPU1")
    , yq7_CPU1(parent, this, "yq7_CPU1")
    , yq8_CPU1(parent, this, "yq8_CPU1")
    , yq9_CPU1(parent, this, "yq9_CPU1")
    , yq10_CPU1(parent, this, "yq10_CPU1")
    , yq11_CPU1(parent, this, "yq11_CPU1")
    , yq12_CPU1(parent, this, "yq12_CPU1")
    , yq13_CPU1(parent, this, "yq13_CPU1")
    , yq14_CPU1(parent, this, "yq14_CPU1")
    , yq15_CPU1(parent, this, "yq15_CPU1")
    , dint_CPU1_VPE0(parent, this, "dint_CPU1_VPE0")
    , hwint0_CPU1_VPE0(parent, this, "hwint0_CPU1_VPE0")
    , hwint1_CPU1_VPE0(parent, this, "hwint1_CPU1_VPE0")
    , hwint2_CPU1_VPE0(parent, this, "hwint2_CPU1_VPE0")
    , hwint3_CPU1_VPE0(parent, this, "hwint3_CPU1_VPE0")
    , hwint4_CPU1_VPE0(parent, this, "hwint4_CPU1_VPE0")
    , hwint5_CPU1_VPE0(parent, this, "hwint5_CPU1_VPE0")
    , nmi_CPU1_VPE0(parent, this, "nmi_CPU1_VPE0")
    , EICPresent_CPU1_VPE0(parent, this, "EICPresent_CPU1_VPE0")
    , EIC_RIPL_CPU1_VPE0(parent, this, "EIC_RIPL_CPU1_VPE0")
    , EIC_EICSS_CPU1_VPE0(parent, this, "EIC_EICSS_CPU1_VPE0")
    , EIC_VectorNum_CPU1_VPE0(parent, this, "EIC_VectorNum_CPU1_VPE0")
    , EIC_VectorOffset_CPU1_VPE0(parent, this, "EIC_VectorOffset_CPU1_VPE0")
    , intISS_CPU1_VPE0(parent, this, "intISS_CPU1_VPE0")
    , causeTI_CPU1_VPE0(parent, this, "causeTI_CPU1_VPE0")
    , causeIP0_CPU1_VPE0(parent, this, "causeIP0_CPU1_VPE0")
    , causeIP1_CPU1_VPE0(parent, this, "causeIP1_CPU1_VPE0")
    , si_sleep_CPU1_VPE0(parent, this, "si_sleep_CPU1_VPE0")
    , vc_run_CPU1_VPE0(parent, this, "vc_run_CPU1_VPE0")
    , dint_CPU1_VPE1(parent, this, "dint_CPU1_VPE1")
    , hwint0_CPU1_VPE1(parent, this, "hwint0_CPU1_VPE1")
    , hwint1_CPU1_VPE1(parent, this, "hwint1_CPU1_VPE1")
    , hwint2_CPU1_VPE1(parent, this, "hwint2_CPU1_VPE1")
    , hwint3_CPU1_VPE1(parent, this, "hwint3_CPU1_VPE1")
    , hwint4_CPU1_VPE1(parent, this, "hwint4_CPU1_VPE1")
    , hwint5_CPU1_VPE1(parent, this, "hwint5_CPU1_VPE1")
    , nmi_CPU1_VPE1(parent, this, "nmi_CPU1_VPE1")
    , EICPresent_CPU1_VPE1(parent, this, "EICPresent_CPU1_VPE1")
    , EIC_RIPL_CPU1_VPE1(parent, this, "EIC_RIPL_CPU1_VPE1")
    , EIC_EICSS_CPU1_VPE1(parent, this, "EIC_EICSS_CPU1_VPE1")
    , EIC_VectorNum_CPU1_VPE1(parent, this, "EIC_VectorNum_CPU1_VPE1")
    , EIC_VectorOffset_CPU1_VPE1(parent, this, "EIC_VectorOffset_CPU1_VPE1")
    , intISS_CPU1_VPE1(parent, this, "intISS_CPU1_VPE1")
    , causeTI_CPU1_VPE1(parent, this, "causeTI_CPU1_VPE1")
    , causeIP0_CPU1_VPE1(parent, this, "causeIP0_CPU1_VPE1")
    , causeIP1_CPU1_VPE1(parent, this, "causeIP1_CPU1_VPE1")
    , si_sleep_CPU1_VPE1(parent, this, "si_sleep_CPU1_VPE1")
    , vc_run_CPU1_VPE1(parent, this, "vc_run_CPU1_VPE1")
    , yq_CPU2(parent, this, "yq_CPU2")
    , yq0_CPU2(parent, this, "yq0_CPU2")
    , yq1_CPU2(parent, this, "yq1_CPU2")
    , yq2_CPU2(parent, this, "yq2_CPU2")
    , yq3_CPU2(parent, this, "yq3_CPU2")
    , yq4_CPU2(parent, this, "yq4_CPU2")
    , yq5_CPU2(parent, this, "yq5_CPU2")
    , yq6_CPU2(parent, this, "yq6_CPU2")
    , yq7_CPU2(parent, this, "yq7_CPU2")
    , yq8_CPU2(parent, this, "yq8_CPU2")
    , yq9_CPU2(parent, this, "yq9_CPU2")
    , yq10_CPU2(parent, this, "yq10_CPU2")
    , yq11_CPU2(parent, this, "yq11_CPU2")
    , yq12_CPU2(parent, this, "yq12_CPU2")
    , yq13_CPU2(parent, this, "yq13_CPU2")
    , yq14_CPU2(parent, this, "yq14_CPU2")
    , yq15_CPU2(parent, this, "yq15_CPU2")
    , dint_CPU2_VPE0(parent, this, "dint_CPU2_VPE0")
    , hwint0_CPU2_VPE0(parent, this, "hwint0_CPU2_VPE0")
    , hwint1_CPU2_VPE0(parent, this, "hwint1_CPU2_VPE0")
    , hwint2_CPU2_VPE0(parent, this, "hwint2_CPU2_VPE0")
    , hwint3_CPU2_VPE0(parent, this, "hwint3_CPU2_VPE0")
    , hwint4_CPU2_VPE0(parent, this, "hwint4_CPU2_VPE0")
    , hwint5_CPU2_VPE0(parent, this, "hwint5_CPU2_VPE0")
    , nmi_CPU2_VPE0(parent, this, "nmi_CPU2_VPE0")
    , EICPresent_CPU2_VPE0(parent, this, "EICPresent_CPU2_VPE0")
    , EIC_RIPL_CPU2_VPE0(parent, this, "EIC_RIPL_CPU2_VPE0")
    , EIC_EICSS_CPU2_VPE0(parent, this, "EIC_EICSS_CPU2_VPE0")
    , EIC_VectorNum_CPU2_VPE0(parent, this, "EIC_VectorNum_CPU2_VPE0")
    , EIC_VectorOffset_CPU2_VPE0(parent, this, "EIC_VectorOffset_CPU2_VPE0")
    , intISS_CPU2_VPE0(parent, this, "intISS_CPU2_VPE0")
    , causeTI_CPU2_VPE0(parent, this, "causeTI_CPU2_VPE0")
    , causeIP0_CPU2_VPE0(parent, this, "causeIP0_CPU2_VPE0")
    , causeIP1_CPU2_VPE0(parent, this, "causeIP1_CPU2_VPE0")
    , si_sleep_CPU2_VPE0(parent, this, "si_sleep_CPU2_VPE0")
    , vc_run_CPU2_VPE0(parent, this, "vc_run_CPU2_VPE0")
    , dint_CPU2_VPE1(parent, this, "dint_CPU2_VPE1")
    , hwint0_CPU2_VPE1(parent, this, "hwint0_CPU2_VPE1")
    , hwint1_CPU2_VPE1(parent, this, "hwint1_CPU2_VPE1")
    , hwint2_CPU2_VPE1(parent, this, "hwint2_CPU2_VPE1")
    , hwint3_CPU2_VPE1(parent, this, "hwint3_CPU2_VPE1")
    , hwint4_CPU2_VPE1(parent, this, "hwint4_CPU2_VPE1")
    , hwint5_CPU2_VPE1(parent, this, "hwint5_CPU2_VPE1")
    , nmi_CPU2_VPE1(parent, this, "nmi_CPU2_VPE1")
    , EICPresent_CPU2_VPE1(parent, this, "EICPresent_CPU2_VPE1")
    , EIC_RIPL_CPU2_VPE1(parent, this, "EIC_RIPL_CPU2_VPE1")
    , EIC_EICSS_CPU2_VPE1(parent, this, "EIC_EICSS_CPU2_VPE1")
    , EIC_VectorNum_CPU2_VPE1(parent, this, "EIC_VectorNum_CPU2_VPE1")
    , EIC_VectorOffset_CPU2_VPE1(parent, this, "EIC_VectorOffset_CPU2_VPE1")
    , intISS_CPU2_VPE1(parent, this, "intISS_CPU2_VPE1")
    , causeTI_CPU2_VPE1(parent, this, "causeTI_CPU2_VPE1")
    , causeIP0_CPU2_VPE1(parent, this, "causeIP0_CPU2_VPE1")
    , causeIP1_CPU2_VPE1(parent, this, "causeIP1_CPU2_VPE1")
    , si_sleep_CPU2_VPE1(parent, this, "si_sleep_CPU2_VPE1")
    , vc_run_CPU2_VPE1(parent, this, "vc_run_CPU2_VPE1")
    , yq_CPU3(parent, this, "yq_CPU3")
    , yq0_CPU3(parent, this, "yq0_CPU3")
    , yq1_CPU3(parent, this, "yq1_CPU3")
    , yq2_CPU3(parent, this, "yq2_CPU3")
    , yq3_CPU3(parent, this, "yq3_CPU3")
    , yq4_CPU3(parent, this, "yq4_CPU3")
    , yq5_CPU3(parent, this, "yq5_CPU3")
    , yq6_CPU3(parent, this, "yq6_CPU3")
    , yq7_CPU3(parent, this, "yq7_CPU3")
    , yq8_CPU3(parent, this, "yq8_CPU3")
    , yq9_CPU3(parent, this, "yq9_CPU3")
    , yq10_CPU3(parent, this, "yq10_CPU3")
    , yq11_CPU3(parent, this, "yq11_CPU3")
    , yq12_CPU3(parent, this, "yq12_CPU3")
    , yq13_CPU3(parent, this, "yq13_CPU3")
    , yq14_CPU3(parent, this, "yq14_CPU3")
    , yq15_CPU3(parent, this, "yq15_CPU3")
    , dint_CPU3_VPE0(parent, this, "dint_CPU3_VPE0")
    , hwint0_CPU3_VPE0(parent, this, "hwint0_CPU3_VPE0")
    , hwint1_CPU3_VPE0(parent, this, "hwint1_CPU3_VPE0")
    , hwint2_CPU3_VPE0(parent, this, "hwint2_CPU3_VPE0")
    , hwint3_CPU3_VPE0(parent, this, "hwint3_CPU3_VPE0")
    , hwint4_CPU3_VPE0(parent, this, "hwint4_CPU3_VPE0")
    , hwint5_CPU3_VPE0(parent, this, "hwint5_CPU3_VPE0")
    , nmi_CPU3_VPE0(parent, this, "nmi_CPU3_VPE0")
    , EICPresent_CPU3_VPE0(parent, this, "EICPresent_CPU3_VPE0")
    , EIC_RIPL_CPU3_VPE0(parent, this, "EIC_RIPL_CPU3_VPE0")
    , EIC_EICSS_CPU3_VPE0(parent, this, "EIC_EICSS_CPU3_VPE0")
    , EIC_VectorNum_CPU3_VPE0(parent, this, "EIC_VectorNum_CPU3_VPE0")
    , EIC_VectorOffset_CPU3_VPE0(parent, this, "EIC_VectorOffset_CPU3_VPE0")
    , intISS_CPU3_VPE0(parent, this, "intISS_CPU3_VPE0")
    , causeTI_CPU3_VPE0(parent, this, "causeTI_CPU3_VPE0")
    , causeIP0_CPU3_VPE0(parent, this, "causeIP0_CPU3_VPE0")
    , causeIP1_CPU3_VPE0(parent, this, "causeIP1_CPU3_VPE0")
    , si_sleep_CPU3_VPE0(parent, this, "si_sleep_CPU3_VPE0")
    , vc_run_CPU3_VPE0(parent, this, "vc_run_CPU3_VPE0")
    , dint_CPU3_VPE1(parent, this, "dint_CPU3_VPE1")
    , hwint0_CPU3_VPE1(parent, this, "hwint0_CPU3_VPE1")
    , hwint1_CPU3_VPE1(parent, this, "hwint1_CPU3_VPE1")
    , hwint2_CPU3_VPE1(parent, this, "hwint2_CPU3_VPE1")
    , hwint3_CPU3_VPE1(parent, this, "hwint3_CPU3_VPE1")
    , hwint4_CPU3_VPE1(parent, this, "hwint4_CPU3_VPE1")
    , hwint5_CPU3_VPE1(parent, this, "hwint5_CPU3_VPE1")
    , nmi_CPU3_VPE1(parent, this, "nmi_CPU3_VPE1")
    , EICPresent_CPU3_VPE1(parent, this, "EICPresent_CPU3_VPE1")
    , EIC_RIPL_CPU3_VPE1(parent, this, "EIC_RIPL_CPU3_VPE1")
    , EIC_EICSS_CPU3_VPE1(parent, this, "EIC_EICSS_CPU3_VPE1")
    , EIC_VectorNum_CPU3_VPE1(parent, this, "EIC_VectorNum_CPU3_VPE1")
    , EIC_VectorOffset_CPU3_VPE1(parent, this, "EIC_VectorOffset_CPU3_VPE1")
    , intISS_CPU3_VPE1(parent, this, "intISS_CPU3_VPE1")
    , causeTI_CPU3_VPE1(parent, this, "causeTI_CPU3_VPE1")
    , causeIP0_CPU3_VPE1(parent, this, "causeIP0_CPU3_VPE1")
    , causeIP1_CPU3_VPE1(parent, this, "causeIP1_CPU3_VPE1")
    , si_sleep_CPU3_VPE1(parent, this, "si_sleep_CPU3_VPE1")
    , vc_run_CPU3_VPE1(parent, this, "vc_run_CPU3_VPE1")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
        USPRAM.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
        USPRAM.dmi(on);
    }
}; /* class mips32_I7200 */


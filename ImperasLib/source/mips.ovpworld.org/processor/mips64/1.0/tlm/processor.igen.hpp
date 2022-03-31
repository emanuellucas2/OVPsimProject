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

class mips64 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        return p;
    }

    params paramsForProc() {
        params p;
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "mips.ovpworld.org", "processor", "mips64", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
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
    tlmNetInputPort      reset_CPU0;
    tlmNetInputPort      hwint0_CPU0;
    tlmNetInputPort      hwint1_CPU0;
    tlmNetInputPort      hwint2_CPU0;
    tlmNetInputPort      hwint3_CPU0;
    tlmNetInputPort      hwint4_CPU0;
    tlmNetInputPort      hwint5_CPU0;
    tlmNetInputPort      nmi_CPU0;
    tlmNetInputPort      EICPresent_CPU0;
    tlmNetInputPort      EIC_RIPL_CPU0;
    tlmNetInputPort      EIC_EICSS_CPU0;
    tlmNetInputPort      EIC_VectorNum_CPU0;
    tlmNetInputPort      EIC_VectorOffset_CPU0;
    tlmNetInputPort      EIC_GID_CPU0;
    tlmNetOutputPort     intISS_CPU0;
    tlmNetOutputPort     causeTI_CPU0;
    tlmNetOutputPort     causeIP0_CPU0;
    tlmNetOutputPort     causeIP1_CPU0;
    tlmNetOutputPort     si_sleep_CPU0;
    tlmNetInputPort      hwint0;
    tlmNetInputPort      vc_run_CPU0;
    tlmNetInputPort      Guest_EIC_RIPL_CPU0;
    tlmNetInputPort      Guest_EIC_EICSS_CPU0;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU0;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU0;
    tlmNetInputPort      Guest_EIC_GID_CPU0;
    tlmNetOutputPort     Guest_intISS_CPU0;
    tlmNetOutputPort     Guest_causeTI_CPU0;
    tlmNetOutputPort     Guest_causeIP0_CPU0;
    tlmNetOutputPort     Guest_causeIP1_CPU0;
    tlmNetInputPort      reset_CPU1;
    tlmNetInputPort      hwint0_CPU1;
    tlmNetInputPort      hwint1_CPU1;
    tlmNetInputPort      hwint2_CPU1;
    tlmNetInputPort      hwint3_CPU1;
    tlmNetInputPort      hwint4_CPU1;
    tlmNetInputPort      hwint5_CPU1;
    tlmNetInputPort      nmi_CPU1;
    tlmNetInputPort      EICPresent_CPU1;
    tlmNetInputPort      EIC_RIPL_CPU1;
    tlmNetInputPort      EIC_EICSS_CPU1;
    tlmNetInputPort      EIC_VectorNum_CPU1;
    tlmNetInputPort      EIC_VectorOffset_CPU1;
    tlmNetInputPort      EIC_GID_CPU1;
    tlmNetOutputPort     intISS_CPU1;
    tlmNetOutputPort     causeTI_CPU1;
    tlmNetOutputPort     causeIP0_CPU1;
    tlmNetOutputPort     causeIP1_CPU1;
    tlmNetOutputPort     si_sleep_CPU1;
    tlmNetInputPort      vc_run_CPU1;
    tlmNetInputPort      Guest_EIC_RIPL_CPU1;
    tlmNetInputPort      Guest_EIC_EICSS_CPU1;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU1;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU1;
    tlmNetInputPort      Guest_EIC_GID_CPU1;
    tlmNetOutputPort     Guest_intISS_CPU1;
    tlmNetOutputPort     Guest_causeTI_CPU1;
    tlmNetOutputPort     Guest_causeIP0_CPU1;
    tlmNetOutputPort     Guest_causeIP1_CPU1;
    tlmNetInputPort      reset_CPU2;
    tlmNetInputPort      hwint0_CPU2;
    tlmNetInputPort      hwint1_CPU2;
    tlmNetInputPort      hwint2_CPU2;
    tlmNetInputPort      hwint3_CPU2;
    tlmNetInputPort      hwint4_CPU2;
    tlmNetInputPort      hwint5_CPU2;
    tlmNetInputPort      nmi_CPU2;
    tlmNetInputPort      EICPresent_CPU2;
    tlmNetInputPort      EIC_RIPL_CPU2;
    tlmNetInputPort      EIC_EICSS_CPU2;
    tlmNetInputPort      EIC_VectorNum_CPU2;
    tlmNetInputPort      EIC_VectorOffset_CPU2;
    tlmNetInputPort      EIC_GID_CPU2;
    tlmNetOutputPort     intISS_CPU2;
    tlmNetOutputPort     causeTI_CPU2;
    tlmNetOutputPort     causeIP0_CPU2;
    tlmNetOutputPort     causeIP1_CPU2;
    tlmNetOutputPort     si_sleep_CPU2;
    tlmNetInputPort      vc_run_CPU2;
    tlmNetInputPort      Guest_EIC_RIPL_CPU2;
    tlmNetInputPort      Guest_EIC_EICSS_CPU2;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU2;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU2;
    tlmNetInputPort      Guest_EIC_GID_CPU2;
    tlmNetOutputPort     Guest_intISS_CPU2;
    tlmNetOutputPort     Guest_causeTI_CPU2;
    tlmNetOutputPort     Guest_causeIP0_CPU2;
    tlmNetOutputPort     Guest_causeIP1_CPU2;
    tlmNetInputPort      reset_CPU3;
    tlmNetInputPort      hwint0_CPU3;
    tlmNetInputPort      hwint1_CPU3;
    tlmNetInputPort      hwint2_CPU3;
    tlmNetInputPort      hwint3_CPU3;
    tlmNetInputPort      hwint4_CPU3;
    tlmNetInputPort      hwint5_CPU3;
    tlmNetInputPort      nmi_CPU3;
    tlmNetInputPort      EICPresent_CPU3;
    tlmNetInputPort      EIC_RIPL_CPU3;
    tlmNetInputPort      EIC_EICSS_CPU3;
    tlmNetInputPort      EIC_VectorNum_CPU3;
    tlmNetInputPort      EIC_VectorOffset_CPU3;
    tlmNetInputPort      EIC_GID_CPU3;
    tlmNetOutputPort     intISS_CPU3;
    tlmNetOutputPort     causeTI_CPU3;
    tlmNetOutputPort     causeIP0_CPU3;
    tlmNetOutputPort     causeIP1_CPU3;
    tlmNetOutputPort     si_sleep_CPU3;
    tlmNetInputPort      vc_run_CPU3;
    tlmNetInputPort      Guest_EIC_RIPL_CPU3;
    tlmNetInputPort      Guest_EIC_EICSS_CPU3;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU3;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU3;
    tlmNetInputPort      Guest_EIC_GID_CPU3;
    tlmNetOutputPort     Guest_intISS_CPU3;
    tlmNetOutputPort     Guest_causeTI_CPU3;
    tlmNetOutputPort     Guest_causeIP0_CPU3;
    tlmNetOutputPort     Guest_causeIP1_CPU3;

    mips64(tlmModule &parent, sc_module_name name)
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
    , reset_CPU0(parent, this, "reset_CPU0")
    , hwint0_CPU0(parent, this, "hwint0_CPU0")
    , hwint1_CPU0(parent, this, "hwint1_CPU0")
    , hwint2_CPU0(parent, this, "hwint2_CPU0")
    , hwint3_CPU0(parent, this, "hwint3_CPU0")
    , hwint4_CPU0(parent, this, "hwint4_CPU0")
    , hwint5_CPU0(parent, this, "hwint5_CPU0")
    , nmi_CPU0(parent, this, "nmi_CPU0")
    , EICPresent_CPU0(parent, this, "EICPresent_CPU0")
    , EIC_RIPL_CPU0(parent, this, "EIC_RIPL_CPU0")
    , EIC_EICSS_CPU0(parent, this, "EIC_EICSS_CPU0")
    , EIC_VectorNum_CPU0(parent, this, "EIC_VectorNum_CPU0")
    , EIC_VectorOffset_CPU0(parent, this, "EIC_VectorOffset_CPU0")
    , EIC_GID_CPU0(parent, this, "EIC_GID_CPU0")
    , intISS_CPU0(parent, this, "intISS_CPU0")
    , causeTI_CPU0(parent, this, "causeTI_CPU0")
    , causeIP0_CPU0(parent, this, "causeIP0_CPU0")
    , causeIP1_CPU0(parent, this, "causeIP1_CPU0")
    , si_sleep_CPU0(parent, this, "si_sleep_CPU0")
    , hwint0(parent, this, "hwint0")
    , vc_run_CPU0(parent, this, "vc_run_CPU0")
    , Guest_EIC_RIPL_CPU0(parent, this, "Guest.EIC_RIPL_CPU0")
    , Guest_EIC_EICSS_CPU0(parent, this, "Guest.EIC_EICSS_CPU0")
    , Guest_EIC_VectorNum_CPU0(parent, this, "Guest.EIC_VectorNum_CPU0")
    , Guest_EIC_VectorOffset_CPU0(parent, this, "Guest.EIC_VectorOffset_CPU0")
    , Guest_EIC_GID_CPU0(parent, this, "Guest.EIC_GID_CPU0")
    , Guest_intISS_CPU0(parent, this, "Guest.intISS_CPU0")
    , Guest_causeTI_CPU0(parent, this, "Guest.causeTI_CPU0")
    , Guest_causeIP0_CPU0(parent, this, "Guest.causeIP0_CPU0")
    , Guest_causeIP1_CPU0(parent, this, "Guest.causeIP1_CPU0")
    , reset_CPU1(parent, this, "reset_CPU1")
    , hwint0_CPU1(parent, this, "hwint0_CPU1")
    , hwint1_CPU1(parent, this, "hwint1_CPU1")
    , hwint2_CPU1(parent, this, "hwint2_CPU1")
    , hwint3_CPU1(parent, this, "hwint3_CPU1")
    , hwint4_CPU1(parent, this, "hwint4_CPU1")
    , hwint5_CPU1(parent, this, "hwint5_CPU1")
    , nmi_CPU1(parent, this, "nmi_CPU1")
    , EICPresent_CPU1(parent, this, "EICPresent_CPU1")
    , EIC_RIPL_CPU1(parent, this, "EIC_RIPL_CPU1")
    , EIC_EICSS_CPU1(parent, this, "EIC_EICSS_CPU1")
    , EIC_VectorNum_CPU1(parent, this, "EIC_VectorNum_CPU1")
    , EIC_VectorOffset_CPU1(parent, this, "EIC_VectorOffset_CPU1")
    , EIC_GID_CPU1(parent, this, "EIC_GID_CPU1")
    , intISS_CPU1(parent, this, "intISS_CPU1")
    , causeTI_CPU1(parent, this, "causeTI_CPU1")
    , causeIP0_CPU1(parent, this, "causeIP0_CPU1")
    , causeIP1_CPU1(parent, this, "causeIP1_CPU1")
    , si_sleep_CPU1(parent, this, "si_sleep_CPU1")
    , vc_run_CPU1(parent, this, "vc_run_CPU1")
    , Guest_EIC_RIPL_CPU1(parent, this, "Guest.EIC_RIPL_CPU1")
    , Guest_EIC_EICSS_CPU1(parent, this, "Guest.EIC_EICSS_CPU1")
    , Guest_EIC_VectorNum_CPU1(parent, this, "Guest.EIC_VectorNum_CPU1")
    , Guest_EIC_VectorOffset_CPU1(parent, this, "Guest.EIC_VectorOffset_CPU1")
    , Guest_EIC_GID_CPU1(parent, this, "Guest.EIC_GID_CPU1")
    , Guest_intISS_CPU1(parent, this, "Guest.intISS_CPU1")
    , Guest_causeTI_CPU1(parent, this, "Guest.causeTI_CPU1")
    , Guest_causeIP0_CPU1(parent, this, "Guest.causeIP0_CPU1")
    , Guest_causeIP1_CPU1(parent, this, "Guest.causeIP1_CPU1")
    , reset_CPU2(parent, this, "reset_CPU2")
    , hwint0_CPU2(parent, this, "hwint0_CPU2")
    , hwint1_CPU2(parent, this, "hwint1_CPU2")
    , hwint2_CPU2(parent, this, "hwint2_CPU2")
    , hwint3_CPU2(parent, this, "hwint3_CPU2")
    , hwint4_CPU2(parent, this, "hwint4_CPU2")
    , hwint5_CPU2(parent, this, "hwint5_CPU2")
    , nmi_CPU2(parent, this, "nmi_CPU2")
    , EICPresent_CPU2(parent, this, "EICPresent_CPU2")
    , EIC_RIPL_CPU2(parent, this, "EIC_RIPL_CPU2")
    , EIC_EICSS_CPU2(parent, this, "EIC_EICSS_CPU2")
    , EIC_VectorNum_CPU2(parent, this, "EIC_VectorNum_CPU2")
    , EIC_VectorOffset_CPU2(parent, this, "EIC_VectorOffset_CPU2")
    , EIC_GID_CPU2(parent, this, "EIC_GID_CPU2")
    , intISS_CPU2(parent, this, "intISS_CPU2")
    , causeTI_CPU2(parent, this, "causeTI_CPU2")
    , causeIP0_CPU2(parent, this, "causeIP0_CPU2")
    , causeIP1_CPU2(parent, this, "causeIP1_CPU2")
    , si_sleep_CPU2(parent, this, "si_sleep_CPU2")
    , vc_run_CPU2(parent, this, "vc_run_CPU2")
    , Guest_EIC_RIPL_CPU2(parent, this, "Guest.EIC_RIPL_CPU2")
    , Guest_EIC_EICSS_CPU2(parent, this, "Guest.EIC_EICSS_CPU2")
    , Guest_EIC_VectorNum_CPU2(parent, this, "Guest.EIC_VectorNum_CPU2")
    , Guest_EIC_VectorOffset_CPU2(parent, this, "Guest.EIC_VectorOffset_CPU2")
    , Guest_EIC_GID_CPU2(parent, this, "Guest.EIC_GID_CPU2")
    , Guest_intISS_CPU2(parent, this, "Guest.intISS_CPU2")
    , Guest_causeTI_CPU2(parent, this, "Guest.causeTI_CPU2")
    , Guest_causeIP0_CPU2(parent, this, "Guest.causeIP0_CPU2")
    , Guest_causeIP1_CPU2(parent, this, "Guest.causeIP1_CPU2")
    , reset_CPU3(parent, this, "reset_CPU3")
    , hwint0_CPU3(parent, this, "hwint0_CPU3")
    , hwint1_CPU3(parent, this, "hwint1_CPU3")
    , hwint2_CPU3(parent, this, "hwint2_CPU3")
    , hwint3_CPU3(parent, this, "hwint3_CPU3")
    , hwint4_CPU3(parent, this, "hwint4_CPU3")
    , hwint5_CPU3(parent, this, "hwint5_CPU3")
    , nmi_CPU3(parent, this, "nmi_CPU3")
    , EICPresent_CPU3(parent, this, "EICPresent_CPU3")
    , EIC_RIPL_CPU3(parent, this, "EIC_RIPL_CPU3")
    , EIC_EICSS_CPU3(parent, this, "EIC_EICSS_CPU3")
    , EIC_VectorNum_CPU3(parent, this, "EIC_VectorNum_CPU3")
    , EIC_VectorOffset_CPU3(parent, this, "EIC_VectorOffset_CPU3")
    , EIC_GID_CPU3(parent, this, "EIC_GID_CPU3")
    , intISS_CPU3(parent, this, "intISS_CPU3")
    , causeTI_CPU3(parent, this, "causeTI_CPU3")
    , causeIP0_CPU3(parent, this, "causeIP0_CPU3")
    , causeIP1_CPU3(parent, this, "causeIP1_CPU3")
    , si_sleep_CPU3(parent, this, "si_sleep_CPU3")
    , vc_run_CPU3(parent, this, "vc_run_CPU3")
    , Guest_EIC_RIPL_CPU3(parent, this, "Guest.EIC_RIPL_CPU3")
    , Guest_EIC_EICSS_CPU3(parent, this, "Guest.EIC_EICSS_CPU3")
    , Guest_EIC_VectorNum_CPU3(parent, this, "Guest.EIC_VectorNum_CPU3")
    , Guest_EIC_VectorOffset_CPU3(parent, this, "Guest.EIC_VectorOffset_CPU3")
    , Guest_EIC_GID_CPU3(parent, this, "Guest.EIC_GID_CPU3")
    , Guest_intISS_CPU3(parent, this, "Guest.intISS_CPU3")
    , Guest_causeTI_CPU3(parent, this, "Guest.causeTI_CPU3")
    , Guest_causeIP0_CPU3(parent, this, "Guest.causeIP0_CPU3")
    , Guest_causeIP1_CPU3(parent, this, "Guest.causeIP1_CPU3")
    {
    }

    mips64(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32, Uns32 USPRAMWidth=32)
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
    , reset_CPU0(parent, this, "reset_CPU0")
    , hwint0_CPU0(parent, this, "hwint0_CPU0")
    , hwint1_CPU0(parent, this, "hwint1_CPU0")
    , hwint2_CPU0(parent, this, "hwint2_CPU0")
    , hwint3_CPU0(parent, this, "hwint3_CPU0")
    , hwint4_CPU0(parent, this, "hwint4_CPU0")
    , hwint5_CPU0(parent, this, "hwint5_CPU0")
    , nmi_CPU0(parent, this, "nmi_CPU0")
    , EICPresent_CPU0(parent, this, "EICPresent_CPU0")
    , EIC_RIPL_CPU0(parent, this, "EIC_RIPL_CPU0")
    , EIC_EICSS_CPU0(parent, this, "EIC_EICSS_CPU0")
    , EIC_VectorNum_CPU0(parent, this, "EIC_VectorNum_CPU0")
    , EIC_VectorOffset_CPU0(parent, this, "EIC_VectorOffset_CPU0")
    , EIC_GID_CPU0(parent, this, "EIC_GID_CPU0")
    , intISS_CPU0(parent, this, "intISS_CPU0")
    , causeTI_CPU0(parent, this, "causeTI_CPU0")
    , causeIP0_CPU0(parent, this, "causeIP0_CPU0")
    , causeIP1_CPU0(parent, this, "causeIP1_CPU0")
    , si_sleep_CPU0(parent, this, "si_sleep_CPU0")
    , hwint0(parent, this, "hwint0")
    , vc_run_CPU0(parent, this, "vc_run_CPU0")
    , Guest_EIC_RIPL_CPU0(parent, this, "Guest.EIC_RIPL_CPU0")
    , Guest_EIC_EICSS_CPU0(parent, this, "Guest.EIC_EICSS_CPU0")
    , Guest_EIC_VectorNum_CPU0(parent, this, "Guest.EIC_VectorNum_CPU0")
    , Guest_EIC_VectorOffset_CPU0(parent, this, "Guest.EIC_VectorOffset_CPU0")
    , Guest_EIC_GID_CPU0(parent, this, "Guest.EIC_GID_CPU0")
    , Guest_intISS_CPU0(parent, this, "Guest.intISS_CPU0")
    , Guest_causeTI_CPU0(parent, this, "Guest.causeTI_CPU0")
    , Guest_causeIP0_CPU0(parent, this, "Guest.causeIP0_CPU0")
    , Guest_causeIP1_CPU0(parent, this, "Guest.causeIP1_CPU0")
    , reset_CPU1(parent, this, "reset_CPU1")
    , hwint0_CPU1(parent, this, "hwint0_CPU1")
    , hwint1_CPU1(parent, this, "hwint1_CPU1")
    , hwint2_CPU1(parent, this, "hwint2_CPU1")
    , hwint3_CPU1(parent, this, "hwint3_CPU1")
    , hwint4_CPU1(parent, this, "hwint4_CPU1")
    , hwint5_CPU1(parent, this, "hwint5_CPU1")
    , nmi_CPU1(parent, this, "nmi_CPU1")
    , EICPresent_CPU1(parent, this, "EICPresent_CPU1")
    , EIC_RIPL_CPU1(parent, this, "EIC_RIPL_CPU1")
    , EIC_EICSS_CPU1(parent, this, "EIC_EICSS_CPU1")
    , EIC_VectorNum_CPU1(parent, this, "EIC_VectorNum_CPU1")
    , EIC_VectorOffset_CPU1(parent, this, "EIC_VectorOffset_CPU1")
    , EIC_GID_CPU1(parent, this, "EIC_GID_CPU1")
    , intISS_CPU1(parent, this, "intISS_CPU1")
    , causeTI_CPU1(parent, this, "causeTI_CPU1")
    , causeIP0_CPU1(parent, this, "causeIP0_CPU1")
    , causeIP1_CPU1(parent, this, "causeIP1_CPU1")
    , si_sleep_CPU1(parent, this, "si_sleep_CPU1")
    , vc_run_CPU1(parent, this, "vc_run_CPU1")
    , Guest_EIC_RIPL_CPU1(parent, this, "Guest.EIC_RIPL_CPU1")
    , Guest_EIC_EICSS_CPU1(parent, this, "Guest.EIC_EICSS_CPU1")
    , Guest_EIC_VectorNum_CPU1(parent, this, "Guest.EIC_VectorNum_CPU1")
    , Guest_EIC_VectorOffset_CPU1(parent, this, "Guest.EIC_VectorOffset_CPU1")
    , Guest_EIC_GID_CPU1(parent, this, "Guest.EIC_GID_CPU1")
    , Guest_intISS_CPU1(parent, this, "Guest.intISS_CPU1")
    , Guest_causeTI_CPU1(parent, this, "Guest.causeTI_CPU1")
    , Guest_causeIP0_CPU1(parent, this, "Guest.causeIP0_CPU1")
    , Guest_causeIP1_CPU1(parent, this, "Guest.causeIP1_CPU1")
    , reset_CPU2(parent, this, "reset_CPU2")
    , hwint0_CPU2(parent, this, "hwint0_CPU2")
    , hwint1_CPU2(parent, this, "hwint1_CPU2")
    , hwint2_CPU2(parent, this, "hwint2_CPU2")
    , hwint3_CPU2(parent, this, "hwint3_CPU2")
    , hwint4_CPU2(parent, this, "hwint4_CPU2")
    , hwint5_CPU2(parent, this, "hwint5_CPU2")
    , nmi_CPU2(parent, this, "nmi_CPU2")
    , EICPresent_CPU2(parent, this, "EICPresent_CPU2")
    , EIC_RIPL_CPU2(parent, this, "EIC_RIPL_CPU2")
    , EIC_EICSS_CPU2(parent, this, "EIC_EICSS_CPU2")
    , EIC_VectorNum_CPU2(parent, this, "EIC_VectorNum_CPU2")
    , EIC_VectorOffset_CPU2(parent, this, "EIC_VectorOffset_CPU2")
    , EIC_GID_CPU2(parent, this, "EIC_GID_CPU2")
    , intISS_CPU2(parent, this, "intISS_CPU2")
    , causeTI_CPU2(parent, this, "causeTI_CPU2")
    , causeIP0_CPU2(parent, this, "causeIP0_CPU2")
    , causeIP1_CPU2(parent, this, "causeIP1_CPU2")
    , si_sleep_CPU2(parent, this, "si_sleep_CPU2")
    , vc_run_CPU2(parent, this, "vc_run_CPU2")
    , Guest_EIC_RIPL_CPU2(parent, this, "Guest.EIC_RIPL_CPU2")
    , Guest_EIC_EICSS_CPU2(parent, this, "Guest.EIC_EICSS_CPU2")
    , Guest_EIC_VectorNum_CPU2(parent, this, "Guest.EIC_VectorNum_CPU2")
    , Guest_EIC_VectorOffset_CPU2(parent, this, "Guest.EIC_VectorOffset_CPU2")
    , Guest_EIC_GID_CPU2(parent, this, "Guest.EIC_GID_CPU2")
    , Guest_intISS_CPU2(parent, this, "Guest.intISS_CPU2")
    , Guest_causeTI_CPU2(parent, this, "Guest.causeTI_CPU2")
    , Guest_causeIP0_CPU2(parent, this, "Guest.causeIP0_CPU2")
    , Guest_causeIP1_CPU2(parent, this, "Guest.causeIP1_CPU2")
    , reset_CPU3(parent, this, "reset_CPU3")
    , hwint0_CPU3(parent, this, "hwint0_CPU3")
    , hwint1_CPU3(parent, this, "hwint1_CPU3")
    , hwint2_CPU3(parent, this, "hwint2_CPU3")
    , hwint3_CPU3(parent, this, "hwint3_CPU3")
    , hwint4_CPU3(parent, this, "hwint4_CPU3")
    , hwint5_CPU3(parent, this, "hwint5_CPU3")
    , nmi_CPU3(parent, this, "nmi_CPU3")
    , EICPresent_CPU3(parent, this, "EICPresent_CPU3")
    , EIC_RIPL_CPU3(parent, this, "EIC_RIPL_CPU3")
    , EIC_EICSS_CPU3(parent, this, "EIC_EICSS_CPU3")
    , EIC_VectorNum_CPU3(parent, this, "EIC_VectorNum_CPU3")
    , EIC_VectorOffset_CPU3(parent, this, "EIC_VectorOffset_CPU3")
    , EIC_GID_CPU3(parent, this, "EIC_GID_CPU3")
    , intISS_CPU3(parent, this, "intISS_CPU3")
    , causeTI_CPU3(parent, this, "causeTI_CPU3")
    , causeIP0_CPU3(parent, this, "causeIP0_CPU3")
    , causeIP1_CPU3(parent, this, "causeIP1_CPU3")
    , si_sleep_CPU3(parent, this, "si_sleep_CPU3")
    , vc_run_CPU3(parent, this, "vc_run_CPU3")
    , Guest_EIC_RIPL_CPU3(parent, this, "Guest.EIC_RIPL_CPU3")
    , Guest_EIC_EICSS_CPU3(parent, this, "Guest.EIC_EICSS_CPU3")
    , Guest_EIC_VectorNum_CPU3(parent, this, "Guest.EIC_VectorNum_CPU3")
    , Guest_EIC_VectorOffset_CPU3(parent, this, "Guest.EIC_VectorOffset_CPU3")
    , Guest_EIC_GID_CPU3(parent, this, "Guest.EIC_GID_CPU3")
    , Guest_intISS_CPU3(parent, this, "Guest.intISS_CPU3")
    , Guest_causeTI_CPU3(parent, this, "Guest.causeTI_CPU3")
    , Guest_causeIP0_CPU3(parent, this, "Guest.causeIP0_CPU3")
    , Guest_causeIP1_CPU3(parent, this, "Guest.causeIP1_CPU3")
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
}; /* class mips64 */


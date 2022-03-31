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

class mips64_I6500 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "I6500");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "I6500");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "mips.ovpworld.org", "processor", "mips64", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmBusMasterPort     DSPRAM_CPU0;
    tlmBusMasterPort     DSPRAM_CPU1;
    tlmBusMasterPort     DSPRAM_CPU2;
    tlmBusMasterPort     DSPRAM_CPU3;
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
    tlmNetInputPort      int40;
    tlmNetInputPort      int41;
    tlmNetInputPort      int42;
    tlmNetInputPort      int43;
    tlmNetInputPort      int44;
    tlmNetInputPort      int45;
    tlmNetInputPort      int46;
    tlmNetInputPort      int47;
    tlmNetInputPort      int48;
    tlmNetInputPort      int49;
    tlmNetInputPort      int50;
    tlmNetInputPort      int51;
    tlmNetInputPort      int52;
    tlmNetInputPort      int53;
    tlmNetInputPort      int54;
    tlmNetInputPort      int55;
    tlmNetInputPort      int56;
    tlmNetInputPort      int57;
    tlmNetInputPort      int58;
    tlmNetInputPort      int59;
    tlmNetInputPort      int60;
    tlmNetInputPort      int61;
    tlmNetInputPort      int62;
    tlmNetInputPort      int63;
    tlmNetInputPort      int64;
    tlmNetInputPort      int65;
    tlmNetInputPort      int66;
    tlmNetInputPort      int67;
    tlmNetInputPort      int68;
    tlmNetInputPort      int69;
    tlmNetInputPort      int70;
    tlmNetInputPort      int71;
    tlmNetInputPort      int72;
    tlmNetInputPort      int73;
    tlmNetInputPort      int74;
    tlmNetInputPort      int75;
    tlmNetInputPort      int76;
    tlmNetInputPort      int77;
    tlmNetInputPort      int78;
    tlmNetInputPort      int79;
    tlmNetInputPort      int80;
    tlmNetInputPort      int81;
    tlmNetInputPort      int82;
    tlmNetInputPort      int83;
    tlmNetInputPort      int84;
    tlmNetInputPort      int85;
    tlmNetInputPort      int86;
    tlmNetInputPort      int87;
    tlmNetInputPort      int88;
    tlmNetInputPort      int89;
    tlmNetInputPort      int90;
    tlmNetInputPort      int91;
    tlmNetInputPort      int92;
    tlmNetInputPort      int93;
    tlmNetInputPort      int94;
    tlmNetInputPort      int95;
    tlmNetInputPort      int96;
    tlmNetInputPort      int97;
    tlmNetInputPort      int98;
    tlmNetInputPort      int99;
    tlmNetInputPort      int100;
    tlmNetInputPort      int101;
    tlmNetInputPort      int102;
    tlmNetInputPort      int103;
    tlmNetInputPort      int104;
    tlmNetInputPort      int105;
    tlmNetInputPort      int106;
    tlmNetInputPort      int107;
    tlmNetInputPort      int108;
    tlmNetInputPort      int109;
    tlmNetInputPort      int110;
    tlmNetInputPort      int111;
    tlmNetInputPort      int112;
    tlmNetInputPort      int113;
    tlmNetInputPort      int114;
    tlmNetInputPort      int115;
    tlmNetInputPort      int116;
    tlmNetInputPort      int117;
    tlmNetInputPort      int118;
    tlmNetInputPort      int119;
    tlmNetInputPort      int120;
    tlmNetInputPort      int121;
    tlmNetInputPort      int122;
    tlmNetInputPort      int123;
    tlmNetInputPort      int124;
    tlmNetInputPort      int125;
    tlmNetInputPort      int126;
    tlmNetInputPort      int127;
    tlmNetInputPort      ej_disable_probe_debug;
    tlmNetInputPort      ejtagbrk_override;
    tlmNetInputPort      ej_dint_in;
    tlmNetOutputPort     GCR_CUSTOM_BASE;
    tlmNetOutputPort     GCR_CUSTOM_BASE_UPPER;
    tlmNetInputPort      dint_CPU0_VP0;
    tlmNetInputPort      hwint0_CPU0_VP0;
    tlmNetInputPort      hwint1_CPU0_VP0;
    tlmNetInputPort      hwint2_CPU0_VP0;
    tlmNetInputPort      hwint3_CPU0_VP0;
    tlmNetInputPort      hwint4_CPU0_VP0;
    tlmNetInputPort      hwint5_CPU0_VP0;
    tlmNetInputPort      nmi_CPU0_VP0;
    tlmNetInputPort      EICPresent_CPU0_VP0;
    tlmNetInputPort      EIC_RIPL_CPU0_VP0;
    tlmNetInputPort      EIC_EICSS_CPU0_VP0;
    tlmNetInputPort      EIC_VectorNum_CPU0_VP0;
    tlmNetInputPort      EIC_VectorOffset_CPU0_VP0;
    tlmNetInputPort      EIC_GID_CPU0_VP0;
    tlmNetOutputPort     intISS_CPU0_VP0;
    tlmNetOutputPort     causeTI_CPU0_VP0;
    tlmNetOutputPort     causeIP0_CPU0_VP0;
    tlmNetOutputPort     causeIP1_CPU0_VP0;
    tlmNetOutputPort     si_sleep_CPU0_VP0;
    tlmNetInputPort      hwint0;
    tlmNetInputPort      vc_run_CPU0_VP0;
    tlmNetInputPort      Guest_EIC_RIPL_CPU0_VP0;
    tlmNetInputPort      Guest_EIC_EICSS_CPU0_VP0;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU0_VP0;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU0_VP0;
    tlmNetInputPort      Guest_EIC_GID_CPU0_VP0;
    tlmNetOutputPort     Guest_intISS_CPU0_VP0;
    tlmNetOutputPort     Guest_causeTI_CPU0_VP0;
    tlmNetOutputPort     Guest_causeIP0_CPU0_VP0;
    tlmNetOutputPort     Guest_causeIP1_CPU0_VP0;
    tlmNetInputPort      dint_CPU0_VP1;
    tlmNetInputPort      hwint0_CPU0_VP1;
    tlmNetInputPort      hwint1_CPU0_VP1;
    tlmNetInputPort      hwint2_CPU0_VP1;
    tlmNetInputPort      hwint3_CPU0_VP1;
    tlmNetInputPort      hwint4_CPU0_VP1;
    tlmNetInputPort      hwint5_CPU0_VP1;
    tlmNetInputPort      nmi_CPU0_VP1;
    tlmNetInputPort      EICPresent_CPU0_VP1;
    tlmNetInputPort      EIC_RIPL_CPU0_VP1;
    tlmNetInputPort      EIC_EICSS_CPU0_VP1;
    tlmNetInputPort      EIC_VectorNum_CPU0_VP1;
    tlmNetInputPort      EIC_VectorOffset_CPU0_VP1;
    tlmNetInputPort      EIC_GID_CPU0_VP1;
    tlmNetOutputPort     intISS_CPU0_VP1;
    tlmNetOutputPort     causeTI_CPU0_VP1;
    tlmNetOutputPort     causeIP0_CPU0_VP1;
    tlmNetOutputPort     causeIP1_CPU0_VP1;
    tlmNetOutputPort     si_sleep_CPU0_VP1;
    tlmNetInputPort      vc_run_CPU0_VP1;
    tlmNetInputPort      Guest_EIC_RIPL_CPU0_VP1;
    tlmNetInputPort      Guest_EIC_EICSS_CPU0_VP1;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU0_VP1;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU0_VP1;
    tlmNetInputPort      Guest_EIC_GID_CPU0_VP1;
    tlmNetOutputPort     Guest_intISS_CPU0_VP1;
    tlmNetOutputPort     Guest_causeTI_CPU0_VP1;
    tlmNetOutputPort     Guest_causeIP0_CPU0_VP1;
    tlmNetOutputPort     Guest_causeIP1_CPU0_VP1;
    tlmNetInputPort      dint_CPU1_VP0;
    tlmNetInputPort      hwint0_CPU1_VP0;
    tlmNetInputPort      hwint1_CPU1_VP0;
    tlmNetInputPort      hwint2_CPU1_VP0;
    tlmNetInputPort      hwint3_CPU1_VP0;
    tlmNetInputPort      hwint4_CPU1_VP0;
    tlmNetInputPort      hwint5_CPU1_VP0;
    tlmNetInputPort      nmi_CPU1_VP0;
    tlmNetInputPort      EICPresent_CPU1_VP0;
    tlmNetInputPort      EIC_RIPL_CPU1_VP0;
    tlmNetInputPort      EIC_EICSS_CPU1_VP0;
    tlmNetInputPort      EIC_VectorNum_CPU1_VP0;
    tlmNetInputPort      EIC_VectorOffset_CPU1_VP0;
    tlmNetInputPort      EIC_GID_CPU1_VP0;
    tlmNetOutputPort     intISS_CPU1_VP0;
    tlmNetOutputPort     causeTI_CPU1_VP0;
    tlmNetOutputPort     causeIP0_CPU1_VP0;
    tlmNetOutputPort     causeIP1_CPU1_VP0;
    tlmNetOutputPort     si_sleep_CPU1_VP0;
    tlmNetInputPort      vc_run_CPU1_VP0;
    tlmNetInputPort      Guest_EIC_RIPL_CPU1_VP0;
    tlmNetInputPort      Guest_EIC_EICSS_CPU1_VP0;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU1_VP0;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU1_VP0;
    tlmNetInputPort      Guest_EIC_GID_CPU1_VP0;
    tlmNetOutputPort     Guest_intISS_CPU1_VP0;
    tlmNetOutputPort     Guest_causeTI_CPU1_VP0;
    tlmNetOutputPort     Guest_causeIP0_CPU1_VP0;
    tlmNetOutputPort     Guest_causeIP1_CPU1_VP0;
    tlmNetInputPort      dint_CPU1_VP1;
    tlmNetInputPort      hwint0_CPU1_VP1;
    tlmNetInputPort      hwint1_CPU1_VP1;
    tlmNetInputPort      hwint2_CPU1_VP1;
    tlmNetInputPort      hwint3_CPU1_VP1;
    tlmNetInputPort      hwint4_CPU1_VP1;
    tlmNetInputPort      hwint5_CPU1_VP1;
    tlmNetInputPort      nmi_CPU1_VP1;
    tlmNetInputPort      EICPresent_CPU1_VP1;
    tlmNetInputPort      EIC_RIPL_CPU1_VP1;
    tlmNetInputPort      EIC_EICSS_CPU1_VP1;
    tlmNetInputPort      EIC_VectorNum_CPU1_VP1;
    tlmNetInputPort      EIC_VectorOffset_CPU1_VP1;
    tlmNetInputPort      EIC_GID_CPU1_VP1;
    tlmNetOutputPort     intISS_CPU1_VP1;
    tlmNetOutputPort     causeTI_CPU1_VP1;
    tlmNetOutputPort     causeIP0_CPU1_VP1;
    tlmNetOutputPort     causeIP1_CPU1_VP1;
    tlmNetOutputPort     si_sleep_CPU1_VP1;
    tlmNetInputPort      vc_run_CPU1_VP1;
    tlmNetInputPort      Guest_EIC_RIPL_CPU1_VP1;
    tlmNetInputPort      Guest_EIC_EICSS_CPU1_VP1;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU1_VP1;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU1_VP1;
    tlmNetInputPort      Guest_EIC_GID_CPU1_VP1;
    tlmNetOutputPort     Guest_intISS_CPU1_VP1;
    tlmNetOutputPort     Guest_causeTI_CPU1_VP1;
    tlmNetOutputPort     Guest_causeIP0_CPU1_VP1;
    tlmNetOutputPort     Guest_causeIP1_CPU1_VP1;
    tlmNetInputPort      dint_CPU2_VP0;
    tlmNetInputPort      hwint0_CPU2_VP0;
    tlmNetInputPort      hwint1_CPU2_VP0;
    tlmNetInputPort      hwint2_CPU2_VP0;
    tlmNetInputPort      hwint3_CPU2_VP0;
    tlmNetInputPort      hwint4_CPU2_VP0;
    tlmNetInputPort      hwint5_CPU2_VP0;
    tlmNetInputPort      nmi_CPU2_VP0;
    tlmNetInputPort      EICPresent_CPU2_VP0;
    tlmNetInputPort      EIC_RIPL_CPU2_VP0;
    tlmNetInputPort      EIC_EICSS_CPU2_VP0;
    tlmNetInputPort      EIC_VectorNum_CPU2_VP0;
    tlmNetInputPort      EIC_VectorOffset_CPU2_VP0;
    tlmNetInputPort      EIC_GID_CPU2_VP0;
    tlmNetOutputPort     intISS_CPU2_VP0;
    tlmNetOutputPort     causeTI_CPU2_VP0;
    tlmNetOutputPort     causeIP0_CPU2_VP0;
    tlmNetOutputPort     causeIP1_CPU2_VP0;
    tlmNetOutputPort     si_sleep_CPU2_VP0;
    tlmNetInputPort      vc_run_CPU2_VP0;
    tlmNetInputPort      Guest_EIC_RIPL_CPU2_VP0;
    tlmNetInputPort      Guest_EIC_EICSS_CPU2_VP0;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU2_VP0;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU2_VP0;
    tlmNetInputPort      Guest_EIC_GID_CPU2_VP0;
    tlmNetOutputPort     Guest_intISS_CPU2_VP0;
    tlmNetOutputPort     Guest_causeTI_CPU2_VP0;
    tlmNetOutputPort     Guest_causeIP0_CPU2_VP0;
    tlmNetOutputPort     Guest_causeIP1_CPU2_VP0;
    tlmNetInputPort      dint_CPU2_VP1;
    tlmNetInputPort      hwint0_CPU2_VP1;
    tlmNetInputPort      hwint1_CPU2_VP1;
    tlmNetInputPort      hwint2_CPU2_VP1;
    tlmNetInputPort      hwint3_CPU2_VP1;
    tlmNetInputPort      hwint4_CPU2_VP1;
    tlmNetInputPort      hwint5_CPU2_VP1;
    tlmNetInputPort      nmi_CPU2_VP1;
    tlmNetInputPort      EICPresent_CPU2_VP1;
    tlmNetInputPort      EIC_RIPL_CPU2_VP1;
    tlmNetInputPort      EIC_EICSS_CPU2_VP1;
    tlmNetInputPort      EIC_VectorNum_CPU2_VP1;
    tlmNetInputPort      EIC_VectorOffset_CPU2_VP1;
    tlmNetInputPort      EIC_GID_CPU2_VP1;
    tlmNetOutputPort     intISS_CPU2_VP1;
    tlmNetOutputPort     causeTI_CPU2_VP1;
    tlmNetOutputPort     causeIP0_CPU2_VP1;
    tlmNetOutputPort     causeIP1_CPU2_VP1;
    tlmNetOutputPort     si_sleep_CPU2_VP1;
    tlmNetInputPort      vc_run_CPU2_VP1;
    tlmNetInputPort      Guest_EIC_RIPL_CPU2_VP1;
    tlmNetInputPort      Guest_EIC_EICSS_CPU2_VP1;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU2_VP1;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU2_VP1;
    tlmNetInputPort      Guest_EIC_GID_CPU2_VP1;
    tlmNetOutputPort     Guest_intISS_CPU2_VP1;
    tlmNetOutputPort     Guest_causeTI_CPU2_VP1;
    tlmNetOutputPort     Guest_causeIP0_CPU2_VP1;
    tlmNetOutputPort     Guest_causeIP1_CPU2_VP1;
    tlmNetInputPort      dint_CPU3_VP0;
    tlmNetInputPort      hwint0_CPU3_VP0;
    tlmNetInputPort      hwint1_CPU3_VP0;
    tlmNetInputPort      hwint2_CPU3_VP0;
    tlmNetInputPort      hwint3_CPU3_VP0;
    tlmNetInputPort      hwint4_CPU3_VP0;
    tlmNetInputPort      hwint5_CPU3_VP0;
    tlmNetInputPort      nmi_CPU3_VP0;
    tlmNetInputPort      EICPresent_CPU3_VP0;
    tlmNetInputPort      EIC_RIPL_CPU3_VP0;
    tlmNetInputPort      EIC_EICSS_CPU3_VP0;
    tlmNetInputPort      EIC_VectorNum_CPU3_VP0;
    tlmNetInputPort      EIC_VectorOffset_CPU3_VP0;
    tlmNetInputPort      EIC_GID_CPU3_VP0;
    tlmNetOutputPort     intISS_CPU3_VP0;
    tlmNetOutputPort     causeTI_CPU3_VP0;
    tlmNetOutputPort     causeIP0_CPU3_VP0;
    tlmNetOutputPort     causeIP1_CPU3_VP0;
    tlmNetOutputPort     si_sleep_CPU3_VP0;
    tlmNetInputPort      vc_run_CPU3_VP0;
    tlmNetInputPort      Guest_EIC_RIPL_CPU3_VP0;
    tlmNetInputPort      Guest_EIC_EICSS_CPU3_VP0;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU3_VP0;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU3_VP0;
    tlmNetInputPort      Guest_EIC_GID_CPU3_VP0;
    tlmNetOutputPort     Guest_intISS_CPU3_VP0;
    tlmNetOutputPort     Guest_causeTI_CPU3_VP0;
    tlmNetOutputPort     Guest_causeIP0_CPU3_VP0;
    tlmNetOutputPort     Guest_causeIP1_CPU3_VP0;
    tlmNetInputPort      dint_CPU3_VP1;
    tlmNetInputPort      hwint0_CPU3_VP1;
    tlmNetInputPort      hwint1_CPU3_VP1;
    tlmNetInputPort      hwint2_CPU3_VP1;
    tlmNetInputPort      hwint3_CPU3_VP1;
    tlmNetInputPort      hwint4_CPU3_VP1;
    tlmNetInputPort      hwint5_CPU3_VP1;
    tlmNetInputPort      nmi_CPU3_VP1;
    tlmNetInputPort      EICPresent_CPU3_VP1;
    tlmNetInputPort      EIC_RIPL_CPU3_VP1;
    tlmNetInputPort      EIC_EICSS_CPU3_VP1;
    tlmNetInputPort      EIC_VectorNum_CPU3_VP1;
    tlmNetInputPort      EIC_VectorOffset_CPU3_VP1;
    tlmNetInputPort      EIC_GID_CPU3_VP1;
    tlmNetOutputPort     intISS_CPU3_VP1;
    tlmNetOutputPort     causeTI_CPU3_VP1;
    tlmNetOutputPort     causeIP0_CPU3_VP1;
    tlmNetOutputPort     causeIP1_CPU3_VP1;
    tlmNetOutputPort     si_sleep_CPU3_VP1;
    tlmNetInputPort      vc_run_CPU3_VP1;
    tlmNetInputPort      Guest_EIC_RIPL_CPU3_VP1;
    tlmNetInputPort      Guest_EIC_EICSS_CPU3_VP1;
    tlmNetInputPort      Guest_EIC_VectorNum_CPU3_VP1;
    tlmNetInputPort      Guest_EIC_VectorOffset_CPU3_VP1;
    tlmNetInputPort      Guest_EIC_GID_CPU3_VP1;
    tlmNetOutputPort     Guest_intISS_CPU3_VP1;
    tlmNetOutputPort     Guest_causeTI_CPU3_VP1;
    tlmNetOutputPort     Guest_causeIP0_CPU3_VP1;
    tlmNetOutputPort     Guest_causeIP1_CPU3_VP1;

    mips64_I6500(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 32)
    , DATA (parent, this, "DATA", 32)
    , DSPRAM_CPU0 (parent, this, "DSPRAM_CPU0", 32)
    , DSPRAM_CPU1 (parent, this, "DSPRAM_CPU1", 32)
    , DSPRAM_CPU2 (parent, this, "DSPRAM_CPU2", 32)
    , DSPRAM_CPU3 (parent, this, "DSPRAM_CPU3", 32)
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
    , int40(parent, this, "int40")
    , int41(parent, this, "int41")
    , int42(parent, this, "int42")
    , int43(parent, this, "int43")
    , int44(parent, this, "int44")
    , int45(parent, this, "int45")
    , int46(parent, this, "int46")
    , int47(parent, this, "int47")
    , int48(parent, this, "int48")
    , int49(parent, this, "int49")
    , int50(parent, this, "int50")
    , int51(parent, this, "int51")
    , int52(parent, this, "int52")
    , int53(parent, this, "int53")
    , int54(parent, this, "int54")
    , int55(parent, this, "int55")
    , int56(parent, this, "int56")
    , int57(parent, this, "int57")
    , int58(parent, this, "int58")
    , int59(parent, this, "int59")
    , int60(parent, this, "int60")
    , int61(parent, this, "int61")
    , int62(parent, this, "int62")
    , int63(parent, this, "int63")
    , int64(parent, this, "int64")
    , int65(parent, this, "int65")
    , int66(parent, this, "int66")
    , int67(parent, this, "int67")
    , int68(parent, this, "int68")
    , int69(parent, this, "int69")
    , int70(parent, this, "int70")
    , int71(parent, this, "int71")
    , int72(parent, this, "int72")
    , int73(parent, this, "int73")
    , int74(parent, this, "int74")
    , int75(parent, this, "int75")
    , int76(parent, this, "int76")
    , int77(parent, this, "int77")
    , int78(parent, this, "int78")
    , int79(parent, this, "int79")
    , int80(parent, this, "int80")
    , int81(parent, this, "int81")
    , int82(parent, this, "int82")
    , int83(parent, this, "int83")
    , int84(parent, this, "int84")
    , int85(parent, this, "int85")
    , int86(parent, this, "int86")
    , int87(parent, this, "int87")
    , int88(parent, this, "int88")
    , int89(parent, this, "int89")
    , int90(parent, this, "int90")
    , int91(parent, this, "int91")
    , int92(parent, this, "int92")
    , int93(parent, this, "int93")
    , int94(parent, this, "int94")
    , int95(parent, this, "int95")
    , int96(parent, this, "int96")
    , int97(parent, this, "int97")
    , int98(parent, this, "int98")
    , int99(parent, this, "int99")
    , int100(parent, this, "int100")
    , int101(parent, this, "int101")
    , int102(parent, this, "int102")
    , int103(parent, this, "int103")
    , int104(parent, this, "int104")
    , int105(parent, this, "int105")
    , int106(parent, this, "int106")
    , int107(parent, this, "int107")
    , int108(parent, this, "int108")
    , int109(parent, this, "int109")
    , int110(parent, this, "int110")
    , int111(parent, this, "int111")
    , int112(parent, this, "int112")
    , int113(parent, this, "int113")
    , int114(parent, this, "int114")
    , int115(parent, this, "int115")
    , int116(parent, this, "int116")
    , int117(parent, this, "int117")
    , int118(parent, this, "int118")
    , int119(parent, this, "int119")
    , int120(parent, this, "int120")
    , int121(parent, this, "int121")
    , int122(parent, this, "int122")
    , int123(parent, this, "int123")
    , int124(parent, this, "int124")
    , int125(parent, this, "int125")
    , int126(parent, this, "int126")
    , int127(parent, this, "int127")
    , ej_disable_probe_debug(parent, this, "ej_disable_probe_debug")
    , ejtagbrk_override(parent, this, "ejtagbrk_override")
    , ej_dint_in(parent, this, "ej_dint_in")
    , GCR_CUSTOM_BASE(parent, this, "GCR_CUSTOM_BASE")
    , GCR_CUSTOM_BASE_UPPER(parent, this, "GCR_CUSTOM_BASE_UPPER")
    , dint_CPU0_VP0(parent, this, "dint_CPU0_VP0")
    , hwint0_CPU0_VP0(parent, this, "hwint0_CPU0_VP0")
    , hwint1_CPU0_VP0(parent, this, "hwint1_CPU0_VP0")
    , hwint2_CPU0_VP0(parent, this, "hwint2_CPU0_VP0")
    , hwint3_CPU0_VP0(parent, this, "hwint3_CPU0_VP0")
    , hwint4_CPU0_VP0(parent, this, "hwint4_CPU0_VP0")
    , hwint5_CPU0_VP0(parent, this, "hwint5_CPU0_VP0")
    , nmi_CPU0_VP0(parent, this, "nmi_CPU0_VP0")
    , EICPresent_CPU0_VP0(parent, this, "EICPresent_CPU0_VP0")
    , EIC_RIPL_CPU0_VP0(parent, this, "EIC_RIPL_CPU0_VP0")
    , EIC_EICSS_CPU0_VP0(parent, this, "EIC_EICSS_CPU0_VP0")
    , EIC_VectorNum_CPU0_VP0(parent, this, "EIC_VectorNum_CPU0_VP0")
    , EIC_VectorOffset_CPU0_VP0(parent, this, "EIC_VectorOffset_CPU0_VP0")
    , EIC_GID_CPU0_VP0(parent, this, "EIC_GID_CPU0_VP0")
    , intISS_CPU0_VP0(parent, this, "intISS_CPU0_VP0")
    , causeTI_CPU0_VP0(parent, this, "causeTI_CPU0_VP0")
    , causeIP0_CPU0_VP0(parent, this, "causeIP0_CPU0_VP0")
    , causeIP1_CPU0_VP0(parent, this, "causeIP1_CPU0_VP0")
    , si_sleep_CPU0_VP0(parent, this, "si_sleep_CPU0_VP0")
    , hwint0(parent, this, "hwint0")
    , vc_run_CPU0_VP0(parent, this, "vc_run_CPU0_VP0")
    , Guest_EIC_RIPL_CPU0_VP0(parent, this, "Guest.EIC_RIPL_CPU0_VP0")
    , Guest_EIC_EICSS_CPU0_VP0(parent, this, "Guest.EIC_EICSS_CPU0_VP0")
    , Guest_EIC_VectorNum_CPU0_VP0(parent, this, "Guest.EIC_VectorNum_CPU0_VP0")
    , Guest_EIC_VectorOffset_CPU0_VP0(parent, this, "Guest.EIC_VectorOffset_CPU0_VP0")
    , Guest_EIC_GID_CPU0_VP0(parent, this, "Guest.EIC_GID_CPU0_VP0")
    , Guest_intISS_CPU0_VP0(parent, this, "Guest.intISS_CPU0_VP0")
    , Guest_causeTI_CPU0_VP0(parent, this, "Guest.causeTI_CPU0_VP0")
    , Guest_causeIP0_CPU0_VP0(parent, this, "Guest.causeIP0_CPU0_VP0")
    , Guest_causeIP1_CPU0_VP0(parent, this, "Guest.causeIP1_CPU0_VP0")
    , dint_CPU0_VP1(parent, this, "dint_CPU0_VP1")
    , hwint0_CPU0_VP1(parent, this, "hwint0_CPU0_VP1")
    , hwint1_CPU0_VP1(parent, this, "hwint1_CPU0_VP1")
    , hwint2_CPU0_VP1(parent, this, "hwint2_CPU0_VP1")
    , hwint3_CPU0_VP1(parent, this, "hwint3_CPU0_VP1")
    , hwint4_CPU0_VP1(parent, this, "hwint4_CPU0_VP1")
    , hwint5_CPU0_VP1(parent, this, "hwint5_CPU0_VP1")
    , nmi_CPU0_VP1(parent, this, "nmi_CPU0_VP1")
    , EICPresent_CPU0_VP1(parent, this, "EICPresent_CPU0_VP1")
    , EIC_RIPL_CPU0_VP1(parent, this, "EIC_RIPL_CPU0_VP1")
    , EIC_EICSS_CPU0_VP1(parent, this, "EIC_EICSS_CPU0_VP1")
    , EIC_VectorNum_CPU0_VP1(parent, this, "EIC_VectorNum_CPU0_VP1")
    , EIC_VectorOffset_CPU0_VP1(parent, this, "EIC_VectorOffset_CPU0_VP1")
    , EIC_GID_CPU0_VP1(parent, this, "EIC_GID_CPU0_VP1")
    , intISS_CPU0_VP1(parent, this, "intISS_CPU0_VP1")
    , causeTI_CPU0_VP1(parent, this, "causeTI_CPU0_VP1")
    , causeIP0_CPU0_VP1(parent, this, "causeIP0_CPU0_VP1")
    , causeIP1_CPU0_VP1(parent, this, "causeIP1_CPU0_VP1")
    , si_sleep_CPU0_VP1(parent, this, "si_sleep_CPU0_VP1")
    , vc_run_CPU0_VP1(parent, this, "vc_run_CPU0_VP1")
    , Guest_EIC_RIPL_CPU0_VP1(parent, this, "Guest.EIC_RIPL_CPU0_VP1")
    , Guest_EIC_EICSS_CPU0_VP1(parent, this, "Guest.EIC_EICSS_CPU0_VP1")
    , Guest_EIC_VectorNum_CPU0_VP1(parent, this, "Guest.EIC_VectorNum_CPU0_VP1")
    , Guest_EIC_VectorOffset_CPU0_VP1(parent, this, "Guest.EIC_VectorOffset_CPU0_VP1")
    , Guest_EIC_GID_CPU0_VP1(parent, this, "Guest.EIC_GID_CPU0_VP1")
    , Guest_intISS_CPU0_VP1(parent, this, "Guest.intISS_CPU0_VP1")
    , Guest_causeTI_CPU0_VP1(parent, this, "Guest.causeTI_CPU0_VP1")
    , Guest_causeIP0_CPU0_VP1(parent, this, "Guest.causeIP0_CPU0_VP1")
    , Guest_causeIP1_CPU0_VP1(parent, this, "Guest.causeIP1_CPU0_VP1")
    , dint_CPU1_VP0(parent, this, "dint_CPU1_VP0")
    , hwint0_CPU1_VP0(parent, this, "hwint0_CPU1_VP0")
    , hwint1_CPU1_VP0(parent, this, "hwint1_CPU1_VP0")
    , hwint2_CPU1_VP0(parent, this, "hwint2_CPU1_VP0")
    , hwint3_CPU1_VP0(parent, this, "hwint3_CPU1_VP0")
    , hwint4_CPU1_VP0(parent, this, "hwint4_CPU1_VP0")
    , hwint5_CPU1_VP0(parent, this, "hwint5_CPU1_VP0")
    , nmi_CPU1_VP0(parent, this, "nmi_CPU1_VP0")
    , EICPresent_CPU1_VP0(parent, this, "EICPresent_CPU1_VP0")
    , EIC_RIPL_CPU1_VP0(parent, this, "EIC_RIPL_CPU1_VP0")
    , EIC_EICSS_CPU1_VP0(parent, this, "EIC_EICSS_CPU1_VP0")
    , EIC_VectorNum_CPU1_VP0(parent, this, "EIC_VectorNum_CPU1_VP0")
    , EIC_VectorOffset_CPU1_VP0(parent, this, "EIC_VectorOffset_CPU1_VP0")
    , EIC_GID_CPU1_VP0(parent, this, "EIC_GID_CPU1_VP0")
    , intISS_CPU1_VP0(parent, this, "intISS_CPU1_VP0")
    , causeTI_CPU1_VP0(parent, this, "causeTI_CPU1_VP0")
    , causeIP0_CPU1_VP0(parent, this, "causeIP0_CPU1_VP0")
    , causeIP1_CPU1_VP0(parent, this, "causeIP1_CPU1_VP0")
    , si_sleep_CPU1_VP0(parent, this, "si_sleep_CPU1_VP0")
    , vc_run_CPU1_VP0(parent, this, "vc_run_CPU1_VP0")
    , Guest_EIC_RIPL_CPU1_VP0(parent, this, "Guest.EIC_RIPL_CPU1_VP0")
    , Guest_EIC_EICSS_CPU1_VP0(parent, this, "Guest.EIC_EICSS_CPU1_VP0")
    , Guest_EIC_VectorNum_CPU1_VP0(parent, this, "Guest.EIC_VectorNum_CPU1_VP0")
    , Guest_EIC_VectorOffset_CPU1_VP0(parent, this, "Guest.EIC_VectorOffset_CPU1_VP0")
    , Guest_EIC_GID_CPU1_VP0(parent, this, "Guest.EIC_GID_CPU1_VP0")
    , Guest_intISS_CPU1_VP0(parent, this, "Guest.intISS_CPU1_VP0")
    , Guest_causeTI_CPU1_VP0(parent, this, "Guest.causeTI_CPU1_VP0")
    , Guest_causeIP0_CPU1_VP0(parent, this, "Guest.causeIP0_CPU1_VP0")
    , Guest_causeIP1_CPU1_VP0(parent, this, "Guest.causeIP1_CPU1_VP0")
    , dint_CPU1_VP1(parent, this, "dint_CPU1_VP1")
    , hwint0_CPU1_VP1(parent, this, "hwint0_CPU1_VP1")
    , hwint1_CPU1_VP1(parent, this, "hwint1_CPU1_VP1")
    , hwint2_CPU1_VP1(parent, this, "hwint2_CPU1_VP1")
    , hwint3_CPU1_VP1(parent, this, "hwint3_CPU1_VP1")
    , hwint4_CPU1_VP1(parent, this, "hwint4_CPU1_VP1")
    , hwint5_CPU1_VP1(parent, this, "hwint5_CPU1_VP1")
    , nmi_CPU1_VP1(parent, this, "nmi_CPU1_VP1")
    , EICPresent_CPU1_VP1(parent, this, "EICPresent_CPU1_VP1")
    , EIC_RIPL_CPU1_VP1(parent, this, "EIC_RIPL_CPU1_VP1")
    , EIC_EICSS_CPU1_VP1(parent, this, "EIC_EICSS_CPU1_VP1")
    , EIC_VectorNum_CPU1_VP1(parent, this, "EIC_VectorNum_CPU1_VP1")
    , EIC_VectorOffset_CPU1_VP1(parent, this, "EIC_VectorOffset_CPU1_VP1")
    , EIC_GID_CPU1_VP1(parent, this, "EIC_GID_CPU1_VP1")
    , intISS_CPU1_VP1(parent, this, "intISS_CPU1_VP1")
    , causeTI_CPU1_VP1(parent, this, "causeTI_CPU1_VP1")
    , causeIP0_CPU1_VP1(parent, this, "causeIP0_CPU1_VP1")
    , causeIP1_CPU1_VP1(parent, this, "causeIP1_CPU1_VP1")
    , si_sleep_CPU1_VP1(parent, this, "si_sleep_CPU1_VP1")
    , vc_run_CPU1_VP1(parent, this, "vc_run_CPU1_VP1")
    , Guest_EIC_RIPL_CPU1_VP1(parent, this, "Guest.EIC_RIPL_CPU1_VP1")
    , Guest_EIC_EICSS_CPU1_VP1(parent, this, "Guest.EIC_EICSS_CPU1_VP1")
    , Guest_EIC_VectorNum_CPU1_VP1(parent, this, "Guest.EIC_VectorNum_CPU1_VP1")
    , Guest_EIC_VectorOffset_CPU1_VP1(parent, this, "Guest.EIC_VectorOffset_CPU1_VP1")
    , Guest_EIC_GID_CPU1_VP1(parent, this, "Guest.EIC_GID_CPU1_VP1")
    , Guest_intISS_CPU1_VP1(parent, this, "Guest.intISS_CPU1_VP1")
    , Guest_causeTI_CPU1_VP1(parent, this, "Guest.causeTI_CPU1_VP1")
    , Guest_causeIP0_CPU1_VP1(parent, this, "Guest.causeIP0_CPU1_VP1")
    , Guest_causeIP1_CPU1_VP1(parent, this, "Guest.causeIP1_CPU1_VP1")
    , dint_CPU2_VP0(parent, this, "dint_CPU2_VP0")
    , hwint0_CPU2_VP0(parent, this, "hwint0_CPU2_VP0")
    , hwint1_CPU2_VP0(parent, this, "hwint1_CPU2_VP0")
    , hwint2_CPU2_VP0(parent, this, "hwint2_CPU2_VP0")
    , hwint3_CPU2_VP0(parent, this, "hwint3_CPU2_VP0")
    , hwint4_CPU2_VP0(parent, this, "hwint4_CPU2_VP0")
    , hwint5_CPU2_VP0(parent, this, "hwint5_CPU2_VP0")
    , nmi_CPU2_VP0(parent, this, "nmi_CPU2_VP0")
    , EICPresent_CPU2_VP0(parent, this, "EICPresent_CPU2_VP0")
    , EIC_RIPL_CPU2_VP0(parent, this, "EIC_RIPL_CPU2_VP0")
    , EIC_EICSS_CPU2_VP0(parent, this, "EIC_EICSS_CPU2_VP0")
    , EIC_VectorNum_CPU2_VP0(parent, this, "EIC_VectorNum_CPU2_VP0")
    , EIC_VectorOffset_CPU2_VP0(parent, this, "EIC_VectorOffset_CPU2_VP0")
    , EIC_GID_CPU2_VP0(parent, this, "EIC_GID_CPU2_VP0")
    , intISS_CPU2_VP0(parent, this, "intISS_CPU2_VP0")
    , causeTI_CPU2_VP0(parent, this, "causeTI_CPU2_VP0")
    , causeIP0_CPU2_VP0(parent, this, "causeIP0_CPU2_VP0")
    , causeIP1_CPU2_VP0(parent, this, "causeIP1_CPU2_VP0")
    , si_sleep_CPU2_VP0(parent, this, "si_sleep_CPU2_VP0")
    , vc_run_CPU2_VP0(parent, this, "vc_run_CPU2_VP0")
    , Guest_EIC_RIPL_CPU2_VP0(parent, this, "Guest.EIC_RIPL_CPU2_VP0")
    , Guest_EIC_EICSS_CPU2_VP0(parent, this, "Guest.EIC_EICSS_CPU2_VP0")
    , Guest_EIC_VectorNum_CPU2_VP0(parent, this, "Guest.EIC_VectorNum_CPU2_VP0")
    , Guest_EIC_VectorOffset_CPU2_VP0(parent, this, "Guest.EIC_VectorOffset_CPU2_VP0")
    , Guest_EIC_GID_CPU2_VP0(parent, this, "Guest.EIC_GID_CPU2_VP0")
    , Guest_intISS_CPU2_VP0(parent, this, "Guest.intISS_CPU2_VP0")
    , Guest_causeTI_CPU2_VP0(parent, this, "Guest.causeTI_CPU2_VP0")
    , Guest_causeIP0_CPU2_VP0(parent, this, "Guest.causeIP0_CPU2_VP0")
    , Guest_causeIP1_CPU2_VP0(parent, this, "Guest.causeIP1_CPU2_VP0")
    , dint_CPU2_VP1(parent, this, "dint_CPU2_VP1")
    , hwint0_CPU2_VP1(parent, this, "hwint0_CPU2_VP1")
    , hwint1_CPU2_VP1(parent, this, "hwint1_CPU2_VP1")
    , hwint2_CPU2_VP1(parent, this, "hwint2_CPU2_VP1")
    , hwint3_CPU2_VP1(parent, this, "hwint3_CPU2_VP1")
    , hwint4_CPU2_VP1(parent, this, "hwint4_CPU2_VP1")
    , hwint5_CPU2_VP1(parent, this, "hwint5_CPU2_VP1")
    , nmi_CPU2_VP1(parent, this, "nmi_CPU2_VP1")
    , EICPresent_CPU2_VP1(parent, this, "EICPresent_CPU2_VP1")
    , EIC_RIPL_CPU2_VP1(parent, this, "EIC_RIPL_CPU2_VP1")
    , EIC_EICSS_CPU2_VP1(parent, this, "EIC_EICSS_CPU2_VP1")
    , EIC_VectorNum_CPU2_VP1(parent, this, "EIC_VectorNum_CPU2_VP1")
    , EIC_VectorOffset_CPU2_VP1(parent, this, "EIC_VectorOffset_CPU2_VP1")
    , EIC_GID_CPU2_VP1(parent, this, "EIC_GID_CPU2_VP1")
    , intISS_CPU2_VP1(parent, this, "intISS_CPU2_VP1")
    , causeTI_CPU2_VP1(parent, this, "causeTI_CPU2_VP1")
    , causeIP0_CPU2_VP1(parent, this, "causeIP0_CPU2_VP1")
    , causeIP1_CPU2_VP1(parent, this, "causeIP1_CPU2_VP1")
    , si_sleep_CPU2_VP1(parent, this, "si_sleep_CPU2_VP1")
    , vc_run_CPU2_VP1(parent, this, "vc_run_CPU2_VP1")
    , Guest_EIC_RIPL_CPU2_VP1(parent, this, "Guest.EIC_RIPL_CPU2_VP1")
    , Guest_EIC_EICSS_CPU2_VP1(parent, this, "Guest.EIC_EICSS_CPU2_VP1")
    , Guest_EIC_VectorNum_CPU2_VP1(parent, this, "Guest.EIC_VectorNum_CPU2_VP1")
    , Guest_EIC_VectorOffset_CPU2_VP1(parent, this, "Guest.EIC_VectorOffset_CPU2_VP1")
    , Guest_EIC_GID_CPU2_VP1(parent, this, "Guest.EIC_GID_CPU2_VP1")
    , Guest_intISS_CPU2_VP1(parent, this, "Guest.intISS_CPU2_VP1")
    , Guest_causeTI_CPU2_VP1(parent, this, "Guest.causeTI_CPU2_VP1")
    , Guest_causeIP0_CPU2_VP1(parent, this, "Guest.causeIP0_CPU2_VP1")
    , Guest_causeIP1_CPU2_VP1(parent, this, "Guest.causeIP1_CPU2_VP1")
    , dint_CPU3_VP0(parent, this, "dint_CPU3_VP0")
    , hwint0_CPU3_VP0(parent, this, "hwint0_CPU3_VP0")
    , hwint1_CPU3_VP0(parent, this, "hwint1_CPU3_VP0")
    , hwint2_CPU3_VP0(parent, this, "hwint2_CPU3_VP0")
    , hwint3_CPU3_VP0(parent, this, "hwint3_CPU3_VP0")
    , hwint4_CPU3_VP0(parent, this, "hwint4_CPU3_VP0")
    , hwint5_CPU3_VP0(parent, this, "hwint5_CPU3_VP0")
    , nmi_CPU3_VP0(parent, this, "nmi_CPU3_VP0")
    , EICPresent_CPU3_VP0(parent, this, "EICPresent_CPU3_VP0")
    , EIC_RIPL_CPU3_VP0(parent, this, "EIC_RIPL_CPU3_VP0")
    , EIC_EICSS_CPU3_VP0(parent, this, "EIC_EICSS_CPU3_VP0")
    , EIC_VectorNum_CPU3_VP0(parent, this, "EIC_VectorNum_CPU3_VP0")
    , EIC_VectorOffset_CPU3_VP0(parent, this, "EIC_VectorOffset_CPU3_VP0")
    , EIC_GID_CPU3_VP0(parent, this, "EIC_GID_CPU3_VP0")
    , intISS_CPU3_VP0(parent, this, "intISS_CPU3_VP0")
    , causeTI_CPU3_VP0(parent, this, "causeTI_CPU3_VP0")
    , causeIP0_CPU3_VP0(parent, this, "causeIP0_CPU3_VP0")
    , causeIP1_CPU3_VP0(parent, this, "causeIP1_CPU3_VP0")
    , si_sleep_CPU3_VP0(parent, this, "si_sleep_CPU3_VP0")
    , vc_run_CPU3_VP0(parent, this, "vc_run_CPU3_VP0")
    , Guest_EIC_RIPL_CPU3_VP0(parent, this, "Guest.EIC_RIPL_CPU3_VP0")
    , Guest_EIC_EICSS_CPU3_VP0(parent, this, "Guest.EIC_EICSS_CPU3_VP0")
    , Guest_EIC_VectorNum_CPU3_VP0(parent, this, "Guest.EIC_VectorNum_CPU3_VP0")
    , Guest_EIC_VectorOffset_CPU3_VP0(parent, this, "Guest.EIC_VectorOffset_CPU3_VP0")
    , Guest_EIC_GID_CPU3_VP0(parent, this, "Guest.EIC_GID_CPU3_VP0")
    , Guest_intISS_CPU3_VP0(parent, this, "Guest.intISS_CPU3_VP0")
    , Guest_causeTI_CPU3_VP0(parent, this, "Guest.causeTI_CPU3_VP0")
    , Guest_causeIP0_CPU3_VP0(parent, this, "Guest.causeIP0_CPU3_VP0")
    , Guest_causeIP1_CPU3_VP0(parent, this, "Guest.causeIP1_CPU3_VP0")
    , dint_CPU3_VP1(parent, this, "dint_CPU3_VP1")
    , hwint0_CPU3_VP1(parent, this, "hwint0_CPU3_VP1")
    , hwint1_CPU3_VP1(parent, this, "hwint1_CPU3_VP1")
    , hwint2_CPU3_VP1(parent, this, "hwint2_CPU3_VP1")
    , hwint3_CPU3_VP1(parent, this, "hwint3_CPU3_VP1")
    , hwint4_CPU3_VP1(parent, this, "hwint4_CPU3_VP1")
    , hwint5_CPU3_VP1(parent, this, "hwint5_CPU3_VP1")
    , nmi_CPU3_VP1(parent, this, "nmi_CPU3_VP1")
    , EICPresent_CPU3_VP1(parent, this, "EICPresent_CPU3_VP1")
    , EIC_RIPL_CPU3_VP1(parent, this, "EIC_RIPL_CPU3_VP1")
    , EIC_EICSS_CPU3_VP1(parent, this, "EIC_EICSS_CPU3_VP1")
    , EIC_VectorNum_CPU3_VP1(parent, this, "EIC_VectorNum_CPU3_VP1")
    , EIC_VectorOffset_CPU3_VP1(parent, this, "EIC_VectorOffset_CPU3_VP1")
    , EIC_GID_CPU3_VP1(parent, this, "EIC_GID_CPU3_VP1")
    , intISS_CPU3_VP1(parent, this, "intISS_CPU3_VP1")
    , causeTI_CPU3_VP1(parent, this, "causeTI_CPU3_VP1")
    , causeIP0_CPU3_VP1(parent, this, "causeIP0_CPU3_VP1")
    , causeIP1_CPU3_VP1(parent, this, "causeIP1_CPU3_VP1")
    , si_sleep_CPU3_VP1(parent, this, "si_sleep_CPU3_VP1")
    , vc_run_CPU3_VP1(parent, this, "vc_run_CPU3_VP1")
    , Guest_EIC_RIPL_CPU3_VP1(parent, this, "Guest.EIC_RIPL_CPU3_VP1")
    , Guest_EIC_EICSS_CPU3_VP1(parent, this, "Guest.EIC_EICSS_CPU3_VP1")
    , Guest_EIC_VectorNum_CPU3_VP1(parent, this, "Guest.EIC_VectorNum_CPU3_VP1")
    , Guest_EIC_VectorOffset_CPU3_VP1(parent, this, "Guest.EIC_VectorOffset_CPU3_VP1")
    , Guest_EIC_GID_CPU3_VP1(parent, this, "Guest.EIC_GID_CPU3_VP1")
    , Guest_intISS_CPU3_VP1(parent, this, "Guest.intISS_CPU3_VP1")
    , Guest_causeTI_CPU3_VP1(parent, this, "Guest.causeTI_CPU3_VP1")
    , Guest_causeIP0_CPU3_VP1(parent, this, "Guest.causeIP0_CPU3_VP1")
    , Guest_causeIP1_CPU3_VP1(parent, this, "Guest.causeIP1_CPU3_VP1")
    {
    }

    mips64_I6500(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32, Uns32 DSPRAM_CPU0Width=32, Uns32 DSPRAM_CPU1Width=32, Uns32 DSPRAM_CPU2Width=32, Uns32 DSPRAM_CPU3Width=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , DSPRAM_CPU0 (parent, this, "DSPRAM_CPU0", DSPRAM_CPU0Width)
    , DSPRAM_CPU1 (parent, this, "DSPRAM_CPU1", DSPRAM_CPU1Width)
    , DSPRAM_CPU2 (parent, this, "DSPRAM_CPU2", DSPRAM_CPU2Width)
    , DSPRAM_CPU3 (parent, this, "DSPRAM_CPU3", DSPRAM_CPU3Width)
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
    , int40(parent, this, "int40")
    , int41(parent, this, "int41")
    , int42(parent, this, "int42")
    , int43(parent, this, "int43")
    , int44(parent, this, "int44")
    , int45(parent, this, "int45")
    , int46(parent, this, "int46")
    , int47(parent, this, "int47")
    , int48(parent, this, "int48")
    , int49(parent, this, "int49")
    , int50(parent, this, "int50")
    , int51(parent, this, "int51")
    , int52(parent, this, "int52")
    , int53(parent, this, "int53")
    , int54(parent, this, "int54")
    , int55(parent, this, "int55")
    , int56(parent, this, "int56")
    , int57(parent, this, "int57")
    , int58(parent, this, "int58")
    , int59(parent, this, "int59")
    , int60(parent, this, "int60")
    , int61(parent, this, "int61")
    , int62(parent, this, "int62")
    , int63(parent, this, "int63")
    , int64(parent, this, "int64")
    , int65(parent, this, "int65")
    , int66(parent, this, "int66")
    , int67(parent, this, "int67")
    , int68(parent, this, "int68")
    , int69(parent, this, "int69")
    , int70(parent, this, "int70")
    , int71(parent, this, "int71")
    , int72(parent, this, "int72")
    , int73(parent, this, "int73")
    , int74(parent, this, "int74")
    , int75(parent, this, "int75")
    , int76(parent, this, "int76")
    , int77(parent, this, "int77")
    , int78(parent, this, "int78")
    , int79(parent, this, "int79")
    , int80(parent, this, "int80")
    , int81(parent, this, "int81")
    , int82(parent, this, "int82")
    , int83(parent, this, "int83")
    , int84(parent, this, "int84")
    , int85(parent, this, "int85")
    , int86(parent, this, "int86")
    , int87(parent, this, "int87")
    , int88(parent, this, "int88")
    , int89(parent, this, "int89")
    , int90(parent, this, "int90")
    , int91(parent, this, "int91")
    , int92(parent, this, "int92")
    , int93(parent, this, "int93")
    , int94(parent, this, "int94")
    , int95(parent, this, "int95")
    , int96(parent, this, "int96")
    , int97(parent, this, "int97")
    , int98(parent, this, "int98")
    , int99(parent, this, "int99")
    , int100(parent, this, "int100")
    , int101(parent, this, "int101")
    , int102(parent, this, "int102")
    , int103(parent, this, "int103")
    , int104(parent, this, "int104")
    , int105(parent, this, "int105")
    , int106(parent, this, "int106")
    , int107(parent, this, "int107")
    , int108(parent, this, "int108")
    , int109(parent, this, "int109")
    , int110(parent, this, "int110")
    , int111(parent, this, "int111")
    , int112(parent, this, "int112")
    , int113(parent, this, "int113")
    , int114(parent, this, "int114")
    , int115(parent, this, "int115")
    , int116(parent, this, "int116")
    , int117(parent, this, "int117")
    , int118(parent, this, "int118")
    , int119(parent, this, "int119")
    , int120(parent, this, "int120")
    , int121(parent, this, "int121")
    , int122(parent, this, "int122")
    , int123(parent, this, "int123")
    , int124(parent, this, "int124")
    , int125(parent, this, "int125")
    , int126(parent, this, "int126")
    , int127(parent, this, "int127")
    , ej_disable_probe_debug(parent, this, "ej_disable_probe_debug")
    , ejtagbrk_override(parent, this, "ejtagbrk_override")
    , ej_dint_in(parent, this, "ej_dint_in")
    , GCR_CUSTOM_BASE(parent, this, "GCR_CUSTOM_BASE")
    , GCR_CUSTOM_BASE_UPPER(parent, this, "GCR_CUSTOM_BASE_UPPER")
    , dint_CPU0_VP0(parent, this, "dint_CPU0_VP0")
    , hwint0_CPU0_VP0(parent, this, "hwint0_CPU0_VP0")
    , hwint1_CPU0_VP0(parent, this, "hwint1_CPU0_VP0")
    , hwint2_CPU0_VP0(parent, this, "hwint2_CPU0_VP0")
    , hwint3_CPU0_VP0(parent, this, "hwint3_CPU0_VP0")
    , hwint4_CPU0_VP0(parent, this, "hwint4_CPU0_VP0")
    , hwint5_CPU0_VP0(parent, this, "hwint5_CPU0_VP0")
    , nmi_CPU0_VP0(parent, this, "nmi_CPU0_VP0")
    , EICPresent_CPU0_VP0(parent, this, "EICPresent_CPU0_VP0")
    , EIC_RIPL_CPU0_VP0(parent, this, "EIC_RIPL_CPU0_VP0")
    , EIC_EICSS_CPU0_VP0(parent, this, "EIC_EICSS_CPU0_VP0")
    , EIC_VectorNum_CPU0_VP0(parent, this, "EIC_VectorNum_CPU0_VP0")
    , EIC_VectorOffset_CPU0_VP0(parent, this, "EIC_VectorOffset_CPU0_VP0")
    , EIC_GID_CPU0_VP0(parent, this, "EIC_GID_CPU0_VP0")
    , intISS_CPU0_VP0(parent, this, "intISS_CPU0_VP0")
    , causeTI_CPU0_VP0(parent, this, "causeTI_CPU0_VP0")
    , causeIP0_CPU0_VP0(parent, this, "causeIP0_CPU0_VP0")
    , causeIP1_CPU0_VP0(parent, this, "causeIP1_CPU0_VP0")
    , si_sleep_CPU0_VP0(parent, this, "si_sleep_CPU0_VP0")
    , hwint0(parent, this, "hwint0")
    , vc_run_CPU0_VP0(parent, this, "vc_run_CPU0_VP0")
    , Guest_EIC_RIPL_CPU0_VP0(parent, this, "Guest.EIC_RIPL_CPU0_VP0")
    , Guest_EIC_EICSS_CPU0_VP0(parent, this, "Guest.EIC_EICSS_CPU0_VP0")
    , Guest_EIC_VectorNum_CPU0_VP0(parent, this, "Guest.EIC_VectorNum_CPU0_VP0")
    , Guest_EIC_VectorOffset_CPU0_VP0(parent, this, "Guest.EIC_VectorOffset_CPU0_VP0")
    , Guest_EIC_GID_CPU0_VP0(parent, this, "Guest.EIC_GID_CPU0_VP0")
    , Guest_intISS_CPU0_VP0(parent, this, "Guest.intISS_CPU0_VP0")
    , Guest_causeTI_CPU0_VP0(parent, this, "Guest.causeTI_CPU0_VP0")
    , Guest_causeIP0_CPU0_VP0(parent, this, "Guest.causeIP0_CPU0_VP0")
    , Guest_causeIP1_CPU0_VP0(parent, this, "Guest.causeIP1_CPU0_VP0")
    , dint_CPU0_VP1(parent, this, "dint_CPU0_VP1")
    , hwint0_CPU0_VP1(parent, this, "hwint0_CPU0_VP1")
    , hwint1_CPU0_VP1(parent, this, "hwint1_CPU0_VP1")
    , hwint2_CPU0_VP1(parent, this, "hwint2_CPU0_VP1")
    , hwint3_CPU0_VP1(parent, this, "hwint3_CPU0_VP1")
    , hwint4_CPU0_VP1(parent, this, "hwint4_CPU0_VP1")
    , hwint5_CPU0_VP1(parent, this, "hwint5_CPU0_VP1")
    , nmi_CPU0_VP1(parent, this, "nmi_CPU0_VP1")
    , EICPresent_CPU0_VP1(parent, this, "EICPresent_CPU0_VP1")
    , EIC_RIPL_CPU0_VP1(parent, this, "EIC_RIPL_CPU0_VP1")
    , EIC_EICSS_CPU0_VP1(parent, this, "EIC_EICSS_CPU0_VP1")
    , EIC_VectorNum_CPU0_VP1(parent, this, "EIC_VectorNum_CPU0_VP1")
    , EIC_VectorOffset_CPU0_VP1(parent, this, "EIC_VectorOffset_CPU0_VP1")
    , EIC_GID_CPU0_VP1(parent, this, "EIC_GID_CPU0_VP1")
    , intISS_CPU0_VP1(parent, this, "intISS_CPU0_VP1")
    , causeTI_CPU0_VP1(parent, this, "causeTI_CPU0_VP1")
    , causeIP0_CPU0_VP1(parent, this, "causeIP0_CPU0_VP1")
    , causeIP1_CPU0_VP1(parent, this, "causeIP1_CPU0_VP1")
    , si_sleep_CPU0_VP1(parent, this, "si_sleep_CPU0_VP1")
    , vc_run_CPU0_VP1(parent, this, "vc_run_CPU0_VP1")
    , Guest_EIC_RIPL_CPU0_VP1(parent, this, "Guest.EIC_RIPL_CPU0_VP1")
    , Guest_EIC_EICSS_CPU0_VP1(parent, this, "Guest.EIC_EICSS_CPU0_VP1")
    , Guest_EIC_VectorNum_CPU0_VP1(parent, this, "Guest.EIC_VectorNum_CPU0_VP1")
    , Guest_EIC_VectorOffset_CPU0_VP1(parent, this, "Guest.EIC_VectorOffset_CPU0_VP1")
    , Guest_EIC_GID_CPU0_VP1(parent, this, "Guest.EIC_GID_CPU0_VP1")
    , Guest_intISS_CPU0_VP1(parent, this, "Guest.intISS_CPU0_VP1")
    , Guest_causeTI_CPU0_VP1(parent, this, "Guest.causeTI_CPU0_VP1")
    , Guest_causeIP0_CPU0_VP1(parent, this, "Guest.causeIP0_CPU0_VP1")
    , Guest_causeIP1_CPU0_VP1(parent, this, "Guest.causeIP1_CPU0_VP1")
    , dint_CPU1_VP0(parent, this, "dint_CPU1_VP0")
    , hwint0_CPU1_VP0(parent, this, "hwint0_CPU1_VP0")
    , hwint1_CPU1_VP0(parent, this, "hwint1_CPU1_VP0")
    , hwint2_CPU1_VP0(parent, this, "hwint2_CPU1_VP0")
    , hwint3_CPU1_VP0(parent, this, "hwint3_CPU1_VP0")
    , hwint4_CPU1_VP0(parent, this, "hwint4_CPU1_VP0")
    , hwint5_CPU1_VP0(parent, this, "hwint5_CPU1_VP0")
    , nmi_CPU1_VP0(parent, this, "nmi_CPU1_VP0")
    , EICPresent_CPU1_VP0(parent, this, "EICPresent_CPU1_VP0")
    , EIC_RIPL_CPU1_VP0(parent, this, "EIC_RIPL_CPU1_VP0")
    , EIC_EICSS_CPU1_VP0(parent, this, "EIC_EICSS_CPU1_VP0")
    , EIC_VectorNum_CPU1_VP0(parent, this, "EIC_VectorNum_CPU1_VP0")
    , EIC_VectorOffset_CPU1_VP0(parent, this, "EIC_VectorOffset_CPU1_VP0")
    , EIC_GID_CPU1_VP0(parent, this, "EIC_GID_CPU1_VP0")
    , intISS_CPU1_VP0(parent, this, "intISS_CPU1_VP0")
    , causeTI_CPU1_VP0(parent, this, "causeTI_CPU1_VP0")
    , causeIP0_CPU1_VP0(parent, this, "causeIP0_CPU1_VP0")
    , causeIP1_CPU1_VP0(parent, this, "causeIP1_CPU1_VP0")
    , si_sleep_CPU1_VP0(parent, this, "si_sleep_CPU1_VP0")
    , vc_run_CPU1_VP0(parent, this, "vc_run_CPU1_VP0")
    , Guest_EIC_RIPL_CPU1_VP0(parent, this, "Guest.EIC_RIPL_CPU1_VP0")
    , Guest_EIC_EICSS_CPU1_VP0(parent, this, "Guest.EIC_EICSS_CPU1_VP0")
    , Guest_EIC_VectorNum_CPU1_VP0(parent, this, "Guest.EIC_VectorNum_CPU1_VP0")
    , Guest_EIC_VectorOffset_CPU1_VP0(parent, this, "Guest.EIC_VectorOffset_CPU1_VP0")
    , Guest_EIC_GID_CPU1_VP0(parent, this, "Guest.EIC_GID_CPU1_VP0")
    , Guest_intISS_CPU1_VP0(parent, this, "Guest.intISS_CPU1_VP0")
    , Guest_causeTI_CPU1_VP0(parent, this, "Guest.causeTI_CPU1_VP0")
    , Guest_causeIP0_CPU1_VP0(parent, this, "Guest.causeIP0_CPU1_VP0")
    , Guest_causeIP1_CPU1_VP0(parent, this, "Guest.causeIP1_CPU1_VP0")
    , dint_CPU1_VP1(parent, this, "dint_CPU1_VP1")
    , hwint0_CPU1_VP1(parent, this, "hwint0_CPU1_VP1")
    , hwint1_CPU1_VP1(parent, this, "hwint1_CPU1_VP1")
    , hwint2_CPU1_VP1(parent, this, "hwint2_CPU1_VP1")
    , hwint3_CPU1_VP1(parent, this, "hwint3_CPU1_VP1")
    , hwint4_CPU1_VP1(parent, this, "hwint4_CPU1_VP1")
    , hwint5_CPU1_VP1(parent, this, "hwint5_CPU1_VP1")
    , nmi_CPU1_VP1(parent, this, "nmi_CPU1_VP1")
    , EICPresent_CPU1_VP1(parent, this, "EICPresent_CPU1_VP1")
    , EIC_RIPL_CPU1_VP1(parent, this, "EIC_RIPL_CPU1_VP1")
    , EIC_EICSS_CPU1_VP1(parent, this, "EIC_EICSS_CPU1_VP1")
    , EIC_VectorNum_CPU1_VP1(parent, this, "EIC_VectorNum_CPU1_VP1")
    , EIC_VectorOffset_CPU1_VP1(parent, this, "EIC_VectorOffset_CPU1_VP1")
    , EIC_GID_CPU1_VP1(parent, this, "EIC_GID_CPU1_VP1")
    , intISS_CPU1_VP1(parent, this, "intISS_CPU1_VP1")
    , causeTI_CPU1_VP1(parent, this, "causeTI_CPU1_VP1")
    , causeIP0_CPU1_VP1(parent, this, "causeIP0_CPU1_VP1")
    , causeIP1_CPU1_VP1(parent, this, "causeIP1_CPU1_VP1")
    , si_sleep_CPU1_VP1(parent, this, "si_sleep_CPU1_VP1")
    , vc_run_CPU1_VP1(parent, this, "vc_run_CPU1_VP1")
    , Guest_EIC_RIPL_CPU1_VP1(parent, this, "Guest.EIC_RIPL_CPU1_VP1")
    , Guest_EIC_EICSS_CPU1_VP1(parent, this, "Guest.EIC_EICSS_CPU1_VP1")
    , Guest_EIC_VectorNum_CPU1_VP1(parent, this, "Guest.EIC_VectorNum_CPU1_VP1")
    , Guest_EIC_VectorOffset_CPU1_VP1(parent, this, "Guest.EIC_VectorOffset_CPU1_VP1")
    , Guest_EIC_GID_CPU1_VP1(parent, this, "Guest.EIC_GID_CPU1_VP1")
    , Guest_intISS_CPU1_VP1(parent, this, "Guest.intISS_CPU1_VP1")
    , Guest_causeTI_CPU1_VP1(parent, this, "Guest.causeTI_CPU1_VP1")
    , Guest_causeIP0_CPU1_VP1(parent, this, "Guest.causeIP0_CPU1_VP1")
    , Guest_causeIP1_CPU1_VP1(parent, this, "Guest.causeIP1_CPU1_VP1")
    , dint_CPU2_VP0(parent, this, "dint_CPU2_VP0")
    , hwint0_CPU2_VP0(parent, this, "hwint0_CPU2_VP0")
    , hwint1_CPU2_VP0(parent, this, "hwint1_CPU2_VP0")
    , hwint2_CPU2_VP0(parent, this, "hwint2_CPU2_VP0")
    , hwint3_CPU2_VP0(parent, this, "hwint3_CPU2_VP0")
    , hwint4_CPU2_VP0(parent, this, "hwint4_CPU2_VP0")
    , hwint5_CPU2_VP0(parent, this, "hwint5_CPU2_VP0")
    , nmi_CPU2_VP0(parent, this, "nmi_CPU2_VP0")
    , EICPresent_CPU2_VP0(parent, this, "EICPresent_CPU2_VP0")
    , EIC_RIPL_CPU2_VP0(parent, this, "EIC_RIPL_CPU2_VP0")
    , EIC_EICSS_CPU2_VP0(parent, this, "EIC_EICSS_CPU2_VP0")
    , EIC_VectorNum_CPU2_VP0(parent, this, "EIC_VectorNum_CPU2_VP0")
    , EIC_VectorOffset_CPU2_VP0(parent, this, "EIC_VectorOffset_CPU2_VP0")
    , EIC_GID_CPU2_VP0(parent, this, "EIC_GID_CPU2_VP0")
    , intISS_CPU2_VP0(parent, this, "intISS_CPU2_VP0")
    , causeTI_CPU2_VP0(parent, this, "causeTI_CPU2_VP0")
    , causeIP0_CPU2_VP0(parent, this, "causeIP0_CPU2_VP0")
    , causeIP1_CPU2_VP0(parent, this, "causeIP1_CPU2_VP0")
    , si_sleep_CPU2_VP0(parent, this, "si_sleep_CPU2_VP0")
    , vc_run_CPU2_VP0(parent, this, "vc_run_CPU2_VP0")
    , Guest_EIC_RIPL_CPU2_VP0(parent, this, "Guest.EIC_RIPL_CPU2_VP0")
    , Guest_EIC_EICSS_CPU2_VP0(parent, this, "Guest.EIC_EICSS_CPU2_VP0")
    , Guest_EIC_VectorNum_CPU2_VP0(parent, this, "Guest.EIC_VectorNum_CPU2_VP0")
    , Guest_EIC_VectorOffset_CPU2_VP0(parent, this, "Guest.EIC_VectorOffset_CPU2_VP0")
    , Guest_EIC_GID_CPU2_VP0(parent, this, "Guest.EIC_GID_CPU2_VP0")
    , Guest_intISS_CPU2_VP0(parent, this, "Guest.intISS_CPU2_VP0")
    , Guest_causeTI_CPU2_VP0(parent, this, "Guest.causeTI_CPU2_VP0")
    , Guest_causeIP0_CPU2_VP0(parent, this, "Guest.causeIP0_CPU2_VP0")
    , Guest_causeIP1_CPU2_VP0(parent, this, "Guest.causeIP1_CPU2_VP0")
    , dint_CPU2_VP1(parent, this, "dint_CPU2_VP1")
    , hwint0_CPU2_VP1(parent, this, "hwint0_CPU2_VP1")
    , hwint1_CPU2_VP1(parent, this, "hwint1_CPU2_VP1")
    , hwint2_CPU2_VP1(parent, this, "hwint2_CPU2_VP1")
    , hwint3_CPU2_VP1(parent, this, "hwint3_CPU2_VP1")
    , hwint4_CPU2_VP1(parent, this, "hwint4_CPU2_VP1")
    , hwint5_CPU2_VP1(parent, this, "hwint5_CPU2_VP1")
    , nmi_CPU2_VP1(parent, this, "nmi_CPU2_VP1")
    , EICPresent_CPU2_VP1(parent, this, "EICPresent_CPU2_VP1")
    , EIC_RIPL_CPU2_VP1(parent, this, "EIC_RIPL_CPU2_VP1")
    , EIC_EICSS_CPU2_VP1(parent, this, "EIC_EICSS_CPU2_VP1")
    , EIC_VectorNum_CPU2_VP1(parent, this, "EIC_VectorNum_CPU2_VP1")
    , EIC_VectorOffset_CPU2_VP1(parent, this, "EIC_VectorOffset_CPU2_VP1")
    , EIC_GID_CPU2_VP1(parent, this, "EIC_GID_CPU2_VP1")
    , intISS_CPU2_VP1(parent, this, "intISS_CPU2_VP1")
    , causeTI_CPU2_VP1(parent, this, "causeTI_CPU2_VP1")
    , causeIP0_CPU2_VP1(parent, this, "causeIP0_CPU2_VP1")
    , causeIP1_CPU2_VP1(parent, this, "causeIP1_CPU2_VP1")
    , si_sleep_CPU2_VP1(parent, this, "si_sleep_CPU2_VP1")
    , vc_run_CPU2_VP1(parent, this, "vc_run_CPU2_VP1")
    , Guest_EIC_RIPL_CPU2_VP1(parent, this, "Guest.EIC_RIPL_CPU2_VP1")
    , Guest_EIC_EICSS_CPU2_VP1(parent, this, "Guest.EIC_EICSS_CPU2_VP1")
    , Guest_EIC_VectorNum_CPU2_VP1(parent, this, "Guest.EIC_VectorNum_CPU2_VP1")
    , Guest_EIC_VectorOffset_CPU2_VP1(parent, this, "Guest.EIC_VectorOffset_CPU2_VP1")
    , Guest_EIC_GID_CPU2_VP1(parent, this, "Guest.EIC_GID_CPU2_VP1")
    , Guest_intISS_CPU2_VP1(parent, this, "Guest.intISS_CPU2_VP1")
    , Guest_causeTI_CPU2_VP1(parent, this, "Guest.causeTI_CPU2_VP1")
    , Guest_causeIP0_CPU2_VP1(parent, this, "Guest.causeIP0_CPU2_VP1")
    , Guest_causeIP1_CPU2_VP1(parent, this, "Guest.causeIP1_CPU2_VP1")
    , dint_CPU3_VP0(parent, this, "dint_CPU3_VP0")
    , hwint0_CPU3_VP0(parent, this, "hwint0_CPU3_VP0")
    , hwint1_CPU3_VP0(parent, this, "hwint1_CPU3_VP0")
    , hwint2_CPU3_VP0(parent, this, "hwint2_CPU3_VP0")
    , hwint3_CPU3_VP0(parent, this, "hwint3_CPU3_VP0")
    , hwint4_CPU3_VP0(parent, this, "hwint4_CPU3_VP0")
    , hwint5_CPU3_VP0(parent, this, "hwint5_CPU3_VP0")
    , nmi_CPU3_VP0(parent, this, "nmi_CPU3_VP0")
    , EICPresent_CPU3_VP0(parent, this, "EICPresent_CPU3_VP0")
    , EIC_RIPL_CPU3_VP0(parent, this, "EIC_RIPL_CPU3_VP0")
    , EIC_EICSS_CPU3_VP0(parent, this, "EIC_EICSS_CPU3_VP0")
    , EIC_VectorNum_CPU3_VP0(parent, this, "EIC_VectorNum_CPU3_VP0")
    , EIC_VectorOffset_CPU3_VP0(parent, this, "EIC_VectorOffset_CPU3_VP0")
    , EIC_GID_CPU3_VP0(parent, this, "EIC_GID_CPU3_VP0")
    , intISS_CPU3_VP0(parent, this, "intISS_CPU3_VP0")
    , causeTI_CPU3_VP0(parent, this, "causeTI_CPU3_VP0")
    , causeIP0_CPU3_VP0(parent, this, "causeIP0_CPU3_VP0")
    , causeIP1_CPU3_VP0(parent, this, "causeIP1_CPU3_VP0")
    , si_sleep_CPU3_VP0(parent, this, "si_sleep_CPU3_VP0")
    , vc_run_CPU3_VP0(parent, this, "vc_run_CPU3_VP0")
    , Guest_EIC_RIPL_CPU3_VP0(parent, this, "Guest.EIC_RIPL_CPU3_VP0")
    , Guest_EIC_EICSS_CPU3_VP0(parent, this, "Guest.EIC_EICSS_CPU3_VP0")
    , Guest_EIC_VectorNum_CPU3_VP0(parent, this, "Guest.EIC_VectorNum_CPU3_VP0")
    , Guest_EIC_VectorOffset_CPU3_VP0(parent, this, "Guest.EIC_VectorOffset_CPU3_VP0")
    , Guest_EIC_GID_CPU3_VP0(parent, this, "Guest.EIC_GID_CPU3_VP0")
    , Guest_intISS_CPU3_VP0(parent, this, "Guest.intISS_CPU3_VP0")
    , Guest_causeTI_CPU3_VP0(parent, this, "Guest.causeTI_CPU3_VP0")
    , Guest_causeIP0_CPU3_VP0(parent, this, "Guest.causeIP0_CPU3_VP0")
    , Guest_causeIP1_CPU3_VP0(parent, this, "Guest.causeIP1_CPU3_VP0")
    , dint_CPU3_VP1(parent, this, "dint_CPU3_VP1")
    , hwint0_CPU3_VP1(parent, this, "hwint0_CPU3_VP1")
    , hwint1_CPU3_VP1(parent, this, "hwint1_CPU3_VP1")
    , hwint2_CPU3_VP1(parent, this, "hwint2_CPU3_VP1")
    , hwint3_CPU3_VP1(parent, this, "hwint3_CPU3_VP1")
    , hwint4_CPU3_VP1(parent, this, "hwint4_CPU3_VP1")
    , hwint5_CPU3_VP1(parent, this, "hwint5_CPU3_VP1")
    , nmi_CPU3_VP1(parent, this, "nmi_CPU3_VP1")
    , EICPresent_CPU3_VP1(parent, this, "EICPresent_CPU3_VP1")
    , EIC_RIPL_CPU3_VP1(parent, this, "EIC_RIPL_CPU3_VP1")
    , EIC_EICSS_CPU3_VP1(parent, this, "EIC_EICSS_CPU3_VP1")
    , EIC_VectorNum_CPU3_VP1(parent, this, "EIC_VectorNum_CPU3_VP1")
    , EIC_VectorOffset_CPU3_VP1(parent, this, "EIC_VectorOffset_CPU3_VP1")
    , EIC_GID_CPU3_VP1(parent, this, "EIC_GID_CPU3_VP1")
    , intISS_CPU3_VP1(parent, this, "intISS_CPU3_VP1")
    , causeTI_CPU3_VP1(parent, this, "causeTI_CPU3_VP1")
    , causeIP0_CPU3_VP1(parent, this, "causeIP0_CPU3_VP1")
    , causeIP1_CPU3_VP1(parent, this, "causeIP1_CPU3_VP1")
    , si_sleep_CPU3_VP1(parent, this, "si_sleep_CPU3_VP1")
    , vc_run_CPU3_VP1(parent, this, "vc_run_CPU3_VP1")
    , Guest_EIC_RIPL_CPU3_VP1(parent, this, "Guest.EIC_RIPL_CPU3_VP1")
    , Guest_EIC_EICSS_CPU3_VP1(parent, this, "Guest.EIC_EICSS_CPU3_VP1")
    , Guest_EIC_VectorNum_CPU3_VP1(parent, this, "Guest.EIC_VectorNum_CPU3_VP1")
    , Guest_EIC_VectorOffset_CPU3_VP1(parent, this, "Guest.EIC_VectorOffset_CPU3_VP1")
    , Guest_EIC_GID_CPU3_VP1(parent, this, "Guest.EIC_GID_CPU3_VP1")
    , Guest_intISS_CPU3_VP1(parent, this, "Guest.intISS_CPU3_VP1")
    , Guest_causeTI_CPU3_VP1(parent, this, "Guest.causeTI_CPU3_VP1")
    , Guest_causeIP0_CPU3_VP1(parent, this, "Guest.causeIP0_CPU3_VP1")
    , Guest_causeIP1_CPU3_VP1(parent, this, "Guest.causeIP1_CPU3_VP1")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
        DSPRAM_CPU0.bindIfNotBound();
        DSPRAM_CPU1.bindIfNotBound();
        DSPRAM_CPU2.bindIfNotBound();
        DSPRAM_CPU3.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
        DSPRAM_CPU0.dmi(on);
        DSPRAM_CPU1.dmi(on);
        DSPRAM_CPU2.dmi(on);
        DSPRAM_CPU3.dmi(on);
    }
}; /* class mips64_I6500 */


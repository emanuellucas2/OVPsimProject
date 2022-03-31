/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * YOU MAY USE THE SOFTWARE SUBJECT TO THE LICENSE TERMS BELOW
 * PROVIDED THAT YOU ENSURE THAT THIS NOTICE IS REPLICATED UNMODIFIED
 * AND IN ITS ENTIRETY IN ALL DISTRIBUTIONS OF THE SOFTWARE,
 * MODIFIED OR UNMODIFIED, IN SOURCE CODE OR IN BINARY FORM.
 *
 * In respect of all models:
 *   The license shall not be construed as granting a license to create a hardware
 *   implementation of the functionality of the software licensed hereunder.
 *
 * In respect of ARM related models:
 *   The license below extends only for your use of the software for the sole
 *   purpose of designing, developing, analyzing, debugging, testing,
 *   verifying, validating and optimizing software which: (a) (i) is for ARM
 *   based systems; and (ii) does not incorporate the ARM Models or any part
 *   thereof; and (b) such ARM Models may not be used to emulate an ARM based
 *   system to run application software in a production or live environment.
 *
 *   The license does not entitle you to use the ARM models for evaluating
 *   the validity of any ARM patent.
 *
 * The license is non-exclusive, worldwide, non-transferable and revocable.
 *
 * Licensed under an Imperas Modified Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.ovpworld.org/licenses/OVP_MODIFIED_1.1_APACHE_OPEN_SOURCE_LICENSE_2.0.pdf
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

class arm_MultiCluster : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "MultiCluster");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "MultiCluster");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "arm.ovpworld.org", "processor", "arm", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmBusMasterPort     GICRegisters;
    tlmNetInputPort      SPI32;
    tlmNetInputPort      SPI33;
    tlmNetInputPort      SPI34;
    tlmNetInputPort      SPI35;
    tlmNetInputPort      SPI36;
    tlmNetInputPort      SPI37;
    tlmNetInputPort      SPI38;
    tlmNetInputPort      SPI39;
    tlmNetInputPort      SPI40;
    tlmNetInputPort      SPI41;
    tlmNetInputPort      SPI42;
    tlmNetInputPort      SPI43;
    tlmNetInputPort      SPI44;
    tlmNetInputPort      SPI45;
    tlmNetInputPort      SPI46;
    tlmNetInputPort      SPI47;
    tlmNetInputPort      SPI48;
    tlmNetInputPort      SPI49;
    tlmNetInputPort      SPI50;
    tlmNetInputPort      SPI51;
    tlmNetInputPort      SPI52;
    tlmNetInputPort      SPI53;
    tlmNetInputPort      SPI54;
    tlmNetInputPort      SPI55;
    tlmNetInputPort      SPI56;
    tlmNetInputPort      SPI57;
    tlmNetInputPort      SPI58;
    tlmNetInputPort      SPI59;
    tlmNetInputPort      SPI60;
    tlmNetInputPort      SPI61;
    tlmNetInputPort      SPI62;
    tlmNetInputPort      SPI63;
    tlmNetInputPort      SPI64;
    tlmNetInputPort      SPI65;
    tlmNetInputPort      SPI66;
    tlmNetInputPort      SPI67;
    tlmNetInputPort      SPI68;
    tlmNetInputPort      SPI69;
    tlmNetInputPort      SPI70;
    tlmNetInputPort      SPI71;
    tlmNetInputPort      SPI72;
    tlmNetInputPort      SPI73;
    tlmNetInputPort      SPI74;
    tlmNetInputPort      SPI75;
    tlmNetInputPort      SPI76;
    tlmNetInputPort      SPI77;
    tlmNetInputPort      SPI78;
    tlmNetInputPort      SPI79;
    tlmNetInputPort      SPI80;
    tlmNetInputPort      SPI81;
    tlmNetInputPort      SPI82;
    tlmNetInputPort      SPI83;
    tlmNetInputPort      SPI84;
    tlmNetInputPort      SPI85;
    tlmNetInputPort      SPI86;
    tlmNetInputPort      SPI87;
    tlmNetInputPort      SPI88;
    tlmNetInputPort      SPI89;
    tlmNetInputPort      SPI90;
    tlmNetInputPort      SPI91;
    tlmNetInputPort      SPI92;
    tlmNetInputPort      SPI93;
    tlmNetInputPort      SPI94;
    tlmNetInputPort      SPI95;
    tlmNetInputPort      SPIVector;
    tlmNetInputPort      periphReset;
    tlmNetInputPort      CFGSDISABLE;
    tlmNetInputPort      GICCDISABLE;
    tlmNetInputPort      EVENTI;
    tlmNetOutputPort     EVENTO;
    tlmNetInputPort      PPI16_C0_0;
    tlmNetInputPort      PPI17_C0_0;
    tlmNetInputPort      PPI18_C0_0;
    tlmNetInputPort      PPI19_C0_0;
    tlmNetInputPort      PPI20_C0_0;
    tlmNetInputPort      PPI21_C0_0;
    tlmNetInputPort      PPI22_C0_0;
    tlmNetInputPort      PPI23_C0_0;
    tlmNetInputPort      PPI24_C0_0;
    tlmNetInputPort      PPI25_C0_0;
    tlmNetInputPort      PPI26_C0_0;
    tlmNetInputPort      PPI27_C0_0;
    tlmNetInputPort      PPI28_C0_0;
    tlmNetInputPort      PPI29_C0_0;
    tlmNetInputPort      PPI30_C0_0;
    tlmNetInputPort      PPI31_C0_0;
    tlmNetOutputPort     CNTVIRQ_C0_0;
    tlmNetOutputPort     CNTPSIRQ_C0_0;
    tlmNetOutputPort     CNTPNSIRQ_C0_0;
    tlmNetOutputPort     CNTPHPIRQ_C0_0;
    tlmNetOutputPort     IRQOUT_C0_0;
    tlmNetOutputPort     FIQOUT_C0_0;
    tlmNetInputPort      CLUSTERIDAFF1_C0;
    tlmNetInputPort      CLUSTERIDAFF2_C0;
    tlmNetInputPort      CLUSTERIDAFF3_C0;
    tlmNetInputPort      RVBARADDRx_C0_0;
    tlmNetInputPort      AA64nAA32_C0_0;
    tlmNetInputPort      VINITHI_C0_0;
    tlmNetInputPort      CFGEND_C0_0;
    tlmNetInputPort      CFGTE_C0_0;
    tlmNetInputPort      reset_C0_0;
    tlmNetInputPort      fiq_C0_0;
    tlmNetInputPort      irq_C0_0;
    tlmNetInputPort      sei_C0_0;
    tlmNetInputPort      vfiq_C0_0;
    tlmNetInputPort      virq_C0_0;
    tlmNetInputPort      vsei_C0_0;
    tlmNetInputPort      AXI_SLVERR_C0_0;
    tlmNetInputPort      CP15SDISABLE_C0_0;
    tlmNetOutputPort     PMUIRQ_C0_0;
    tlmNetOutputPort     SMPEN_C0_0;
    tlmNetInputPort      PPI16_C0_1;
    tlmNetInputPort      PPI17_C0_1;
    tlmNetInputPort      PPI18_C0_1;
    tlmNetInputPort      PPI19_C0_1;
    tlmNetInputPort      PPI20_C0_1;
    tlmNetInputPort      PPI21_C0_1;
    tlmNetInputPort      PPI22_C0_1;
    tlmNetInputPort      PPI23_C0_1;
    tlmNetInputPort      PPI24_C0_1;
    tlmNetInputPort      PPI25_C0_1;
    tlmNetInputPort      PPI26_C0_1;
    tlmNetInputPort      PPI27_C0_1;
    tlmNetInputPort      PPI28_C0_1;
    tlmNetInputPort      PPI29_C0_1;
    tlmNetInputPort      PPI30_C0_1;
    tlmNetInputPort      PPI31_C0_1;
    tlmNetOutputPort     CNTVIRQ_C0_1;
    tlmNetOutputPort     CNTPSIRQ_C0_1;
    tlmNetOutputPort     CNTPNSIRQ_C0_1;
    tlmNetOutputPort     CNTPHPIRQ_C0_1;
    tlmNetOutputPort     IRQOUT_C0_1;
    tlmNetOutputPort     FIQOUT_C0_1;
    tlmNetInputPort      RVBARADDRx_C0_1;
    tlmNetInputPort      AA64nAA32_C0_1;
    tlmNetInputPort      VINITHI_C0_1;
    tlmNetInputPort      CFGEND_C0_1;
    tlmNetInputPort      CFGTE_C0_1;
    tlmNetInputPort      reset_C0_1;
    tlmNetInputPort      fiq_C0_1;
    tlmNetInputPort      irq_C0_1;
    tlmNetInputPort      sei_C0_1;
    tlmNetInputPort      vfiq_C0_1;
    tlmNetInputPort      virq_C0_1;
    tlmNetInputPort      vsei_C0_1;
    tlmNetInputPort      AXI_SLVERR_C0_1;
    tlmNetInputPort      CP15SDISABLE_C0_1;
    tlmNetOutputPort     PMUIRQ_C0_1;
    tlmNetOutputPort     SMPEN_C0_1;
    tlmNetInputPort      PPI16_C0_2;
    tlmNetInputPort      PPI17_C0_2;
    tlmNetInputPort      PPI18_C0_2;
    tlmNetInputPort      PPI19_C0_2;
    tlmNetInputPort      PPI20_C0_2;
    tlmNetInputPort      PPI21_C0_2;
    tlmNetInputPort      PPI22_C0_2;
    tlmNetInputPort      PPI23_C0_2;
    tlmNetInputPort      PPI24_C0_2;
    tlmNetInputPort      PPI25_C0_2;
    tlmNetInputPort      PPI26_C0_2;
    tlmNetInputPort      PPI27_C0_2;
    tlmNetInputPort      PPI28_C0_2;
    tlmNetInputPort      PPI29_C0_2;
    tlmNetInputPort      PPI30_C0_2;
    tlmNetInputPort      PPI31_C0_2;
    tlmNetOutputPort     CNTVIRQ_C0_2;
    tlmNetOutputPort     CNTPSIRQ_C0_2;
    tlmNetOutputPort     CNTPNSIRQ_C0_2;
    tlmNetOutputPort     CNTPHPIRQ_C0_2;
    tlmNetOutputPort     IRQOUT_C0_2;
    tlmNetOutputPort     FIQOUT_C0_2;
    tlmNetInputPort      RVBARADDRx_C0_2;
    tlmNetInputPort      AA64nAA32_C0_2;
    tlmNetInputPort      VINITHI_C0_2;
    tlmNetInputPort      CFGEND_C0_2;
    tlmNetInputPort      CFGTE_C0_2;
    tlmNetInputPort      reset_C0_2;
    tlmNetInputPort      fiq_C0_2;
    tlmNetInputPort      irq_C0_2;
    tlmNetInputPort      sei_C0_2;
    tlmNetInputPort      vfiq_C0_2;
    tlmNetInputPort      virq_C0_2;
    tlmNetInputPort      vsei_C0_2;
    tlmNetInputPort      AXI_SLVERR_C0_2;
    tlmNetInputPort      CP15SDISABLE_C0_2;
    tlmNetOutputPort     PMUIRQ_C0_2;
    tlmNetOutputPort     SMPEN_C0_2;
    tlmNetInputPort      PPI16_C0_3;
    tlmNetInputPort      PPI17_C0_3;
    tlmNetInputPort      PPI18_C0_3;
    tlmNetInputPort      PPI19_C0_3;
    tlmNetInputPort      PPI20_C0_3;
    tlmNetInputPort      PPI21_C0_3;
    tlmNetInputPort      PPI22_C0_3;
    tlmNetInputPort      PPI23_C0_3;
    tlmNetInputPort      PPI24_C0_3;
    tlmNetInputPort      PPI25_C0_3;
    tlmNetInputPort      PPI26_C0_3;
    tlmNetInputPort      PPI27_C0_3;
    tlmNetInputPort      PPI28_C0_3;
    tlmNetInputPort      PPI29_C0_3;
    tlmNetInputPort      PPI30_C0_3;
    tlmNetInputPort      PPI31_C0_3;
    tlmNetOutputPort     CNTVIRQ_C0_3;
    tlmNetOutputPort     CNTPSIRQ_C0_3;
    tlmNetOutputPort     CNTPNSIRQ_C0_3;
    tlmNetOutputPort     CNTPHPIRQ_C0_3;
    tlmNetOutputPort     IRQOUT_C0_3;
    tlmNetOutputPort     FIQOUT_C0_3;
    tlmNetInputPort      RVBARADDRx_C0_3;
    tlmNetInputPort      AA64nAA32_C0_3;
    tlmNetInputPort      VINITHI_C0_3;
    tlmNetInputPort      CFGEND_C0_3;
    tlmNetInputPort      CFGTE_C0_3;
    tlmNetInputPort      reset_C0_3;
    tlmNetInputPort      fiq_C0_3;
    tlmNetInputPort      irq_C0_3;
    tlmNetInputPort      sei_C0_3;
    tlmNetInputPort      vfiq_C0_3;
    tlmNetInputPort      virq_C0_3;
    tlmNetInputPort      vsei_C0_3;
    tlmNetInputPort      AXI_SLVERR_C0_3;
    tlmNetInputPort      CP15SDISABLE_C0_3;
    tlmNetOutputPort     PMUIRQ_C0_3;
    tlmNetOutputPort     SMPEN_C0_3;
    tlmNetInputPort      PPI16_C1_0;
    tlmNetInputPort      PPI17_C1_0;
    tlmNetInputPort      PPI18_C1_0;
    tlmNetInputPort      PPI19_C1_0;
    tlmNetInputPort      PPI20_C1_0;
    tlmNetInputPort      PPI21_C1_0;
    tlmNetInputPort      PPI22_C1_0;
    tlmNetInputPort      PPI23_C1_0;
    tlmNetInputPort      PPI24_C1_0;
    tlmNetInputPort      PPI25_C1_0;
    tlmNetInputPort      PPI26_C1_0;
    tlmNetInputPort      PPI27_C1_0;
    tlmNetInputPort      PPI28_C1_0;
    tlmNetInputPort      PPI29_C1_0;
    tlmNetInputPort      PPI30_C1_0;
    tlmNetInputPort      PPI31_C1_0;
    tlmNetOutputPort     CNTVIRQ_C1_0;
    tlmNetOutputPort     CNTPSIRQ_C1_0;
    tlmNetOutputPort     CNTPNSIRQ_C1_0;
    tlmNetOutputPort     CNTPHPIRQ_C1_0;
    tlmNetOutputPort     IRQOUT_C1_0;
    tlmNetOutputPort     FIQOUT_C1_0;
    tlmNetInputPort      CLUSTERIDAFF1_C1;
    tlmNetInputPort      CLUSTERIDAFF2_C1;
    tlmNetInputPort      CLUSTERIDAFF3_C1;
    tlmNetInputPort      RVBARADDRx_C1_0;
    tlmNetInputPort      AA64nAA32_C1_0;
    tlmNetInputPort      VINITHI_C1_0;
    tlmNetInputPort      CFGEND_C1_0;
    tlmNetInputPort      CFGTE_C1_0;
    tlmNetInputPort      reset_C1_0;
    tlmNetInputPort      fiq_C1_0;
    tlmNetInputPort      irq_C1_0;
    tlmNetInputPort      sei_C1_0;
    tlmNetInputPort      vfiq_C1_0;
    tlmNetInputPort      virq_C1_0;
    tlmNetInputPort      vsei_C1_0;
    tlmNetInputPort      AXI_SLVERR_C1_0;
    tlmNetInputPort      CP15SDISABLE_C1_0;
    tlmNetOutputPort     PMUIRQ_C1_0;
    tlmNetOutputPort     SMPEN_C1_0;
    tlmNetInputPort      PPI16_C1_1;
    tlmNetInputPort      PPI17_C1_1;
    tlmNetInputPort      PPI18_C1_1;
    tlmNetInputPort      PPI19_C1_1;
    tlmNetInputPort      PPI20_C1_1;
    tlmNetInputPort      PPI21_C1_1;
    tlmNetInputPort      PPI22_C1_1;
    tlmNetInputPort      PPI23_C1_1;
    tlmNetInputPort      PPI24_C1_1;
    tlmNetInputPort      PPI25_C1_1;
    tlmNetInputPort      PPI26_C1_1;
    tlmNetInputPort      PPI27_C1_1;
    tlmNetInputPort      PPI28_C1_1;
    tlmNetInputPort      PPI29_C1_1;
    tlmNetInputPort      PPI30_C1_1;
    tlmNetInputPort      PPI31_C1_1;
    tlmNetOutputPort     CNTVIRQ_C1_1;
    tlmNetOutputPort     CNTPSIRQ_C1_1;
    tlmNetOutputPort     CNTPNSIRQ_C1_1;
    tlmNetOutputPort     CNTPHPIRQ_C1_1;
    tlmNetOutputPort     IRQOUT_C1_1;
    tlmNetOutputPort     FIQOUT_C1_1;
    tlmNetInputPort      RVBARADDRx_C1_1;
    tlmNetInputPort      AA64nAA32_C1_1;
    tlmNetInputPort      VINITHI_C1_1;
    tlmNetInputPort      CFGEND_C1_1;
    tlmNetInputPort      CFGTE_C1_1;
    tlmNetInputPort      reset_C1_1;
    tlmNetInputPort      fiq_C1_1;
    tlmNetInputPort      irq_C1_1;
    tlmNetInputPort      sei_C1_1;
    tlmNetInputPort      vfiq_C1_1;
    tlmNetInputPort      virq_C1_1;
    tlmNetInputPort      vsei_C1_1;
    tlmNetInputPort      AXI_SLVERR_C1_1;
    tlmNetInputPort      CP15SDISABLE_C1_1;
    tlmNetOutputPort     PMUIRQ_C1_1;
    tlmNetOutputPort     SMPEN_C1_1;
    tlmNetInputPort      PPI16_C1_2;
    tlmNetInputPort      PPI17_C1_2;
    tlmNetInputPort      PPI18_C1_2;
    tlmNetInputPort      PPI19_C1_2;
    tlmNetInputPort      PPI20_C1_2;
    tlmNetInputPort      PPI21_C1_2;
    tlmNetInputPort      PPI22_C1_2;
    tlmNetInputPort      PPI23_C1_2;
    tlmNetInputPort      PPI24_C1_2;
    tlmNetInputPort      PPI25_C1_2;
    tlmNetInputPort      PPI26_C1_2;
    tlmNetInputPort      PPI27_C1_2;
    tlmNetInputPort      PPI28_C1_2;
    tlmNetInputPort      PPI29_C1_2;
    tlmNetInputPort      PPI30_C1_2;
    tlmNetInputPort      PPI31_C1_2;
    tlmNetOutputPort     CNTVIRQ_C1_2;
    tlmNetOutputPort     CNTPSIRQ_C1_2;
    tlmNetOutputPort     CNTPNSIRQ_C1_2;
    tlmNetOutputPort     CNTPHPIRQ_C1_2;
    tlmNetOutputPort     IRQOUT_C1_2;
    tlmNetOutputPort     FIQOUT_C1_2;
    tlmNetInputPort      RVBARADDRx_C1_2;
    tlmNetInputPort      AA64nAA32_C1_2;
    tlmNetInputPort      VINITHI_C1_2;
    tlmNetInputPort      CFGEND_C1_2;
    tlmNetInputPort      CFGTE_C1_2;
    tlmNetInputPort      reset_C1_2;
    tlmNetInputPort      fiq_C1_2;
    tlmNetInputPort      irq_C1_2;
    tlmNetInputPort      sei_C1_2;
    tlmNetInputPort      vfiq_C1_2;
    tlmNetInputPort      virq_C1_2;
    tlmNetInputPort      vsei_C1_2;
    tlmNetInputPort      AXI_SLVERR_C1_2;
    tlmNetInputPort      CP15SDISABLE_C1_2;
    tlmNetOutputPort     PMUIRQ_C1_2;
    tlmNetOutputPort     SMPEN_C1_2;
    tlmNetInputPort      PPI16_C1_3;
    tlmNetInputPort      PPI17_C1_3;
    tlmNetInputPort      PPI18_C1_3;
    tlmNetInputPort      PPI19_C1_3;
    tlmNetInputPort      PPI20_C1_3;
    tlmNetInputPort      PPI21_C1_3;
    tlmNetInputPort      PPI22_C1_3;
    tlmNetInputPort      PPI23_C1_3;
    tlmNetInputPort      PPI24_C1_3;
    tlmNetInputPort      PPI25_C1_3;
    tlmNetInputPort      PPI26_C1_3;
    tlmNetInputPort      PPI27_C1_3;
    tlmNetInputPort      PPI28_C1_3;
    tlmNetInputPort      PPI29_C1_3;
    tlmNetInputPort      PPI30_C1_3;
    tlmNetInputPort      PPI31_C1_3;
    tlmNetOutputPort     CNTVIRQ_C1_3;
    tlmNetOutputPort     CNTPSIRQ_C1_3;
    tlmNetOutputPort     CNTPNSIRQ_C1_3;
    tlmNetOutputPort     CNTPHPIRQ_C1_3;
    tlmNetOutputPort     IRQOUT_C1_3;
    tlmNetOutputPort     FIQOUT_C1_3;
    tlmNetInputPort      RVBARADDRx_C1_3;
    tlmNetInputPort      AA64nAA32_C1_3;
    tlmNetInputPort      VINITHI_C1_3;
    tlmNetInputPort      CFGEND_C1_3;
    tlmNetInputPort      CFGTE_C1_3;
    tlmNetInputPort      reset_C1_3;
    tlmNetInputPort      fiq_C1_3;
    tlmNetInputPort      irq_C1_3;
    tlmNetInputPort      sei_C1_3;
    tlmNetInputPort      vfiq_C1_3;
    tlmNetInputPort      virq_C1_3;
    tlmNetInputPort      vsei_C1_3;
    tlmNetInputPort      AXI_SLVERR_C1_3;
    tlmNetInputPort      CP15SDISABLE_C1_3;
    tlmNetOutputPort     PMUIRQ_C1_3;
    tlmNetOutputPort     SMPEN_C1_3;

    arm_MultiCluster(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 44)
    , DATA (parent, this, "DATA", 44)
    , GICRegisters (parent, this, "GICRegisters", 32)
    , SPI32(parent, this, "SPI32")
    , SPI33(parent, this, "SPI33")
    , SPI34(parent, this, "SPI34")
    , SPI35(parent, this, "SPI35")
    , SPI36(parent, this, "SPI36")
    , SPI37(parent, this, "SPI37")
    , SPI38(parent, this, "SPI38")
    , SPI39(parent, this, "SPI39")
    , SPI40(parent, this, "SPI40")
    , SPI41(parent, this, "SPI41")
    , SPI42(parent, this, "SPI42")
    , SPI43(parent, this, "SPI43")
    , SPI44(parent, this, "SPI44")
    , SPI45(parent, this, "SPI45")
    , SPI46(parent, this, "SPI46")
    , SPI47(parent, this, "SPI47")
    , SPI48(parent, this, "SPI48")
    , SPI49(parent, this, "SPI49")
    , SPI50(parent, this, "SPI50")
    , SPI51(parent, this, "SPI51")
    , SPI52(parent, this, "SPI52")
    , SPI53(parent, this, "SPI53")
    , SPI54(parent, this, "SPI54")
    , SPI55(parent, this, "SPI55")
    , SPI56(parent, this, "SPI56")
    , SPI57(parent, this, "SPI57")
    , SPI58(parent, this, "SPI58")
    , SPI59(parent, this, "SPI59")
    , SPI60(parent, this, "SPI60")
    , SPI61(parent, this, "SPI61")
    , SPI62(parent, this, "SPI62")
    , SPI63(parent, this, "SPI63")
    , SPI64(parent, this, "SPI64")
    , SPI65(parent, this, "SPI65")
    , SPI66(parent, this, "SPI66")
    , SPI67(parent, this, "SPI67")
    , SPI68(parent, this, "SPI68")
    , SPI69(parent, this, "SPI69")
    , SPI70(parent, this, "SPI70")
    , SPI71(parent, this, "SPI71")
    , SPI72(parent, this, "SPI72")
    , SPI73(parent, this, "SPI73")
    , SPI74(parent, this, "SPI74")
    , SPI75(parent, this, "SPI75")
    , SPI76(parent, this, "SPI76")
    , SPI77(parent, this, "SPI77")
    , SPI78(parent, this, "SPI78")
    , SPI79(parent, this, "SPI79")
    , SPI80(parent, this, "SPI80")
    , SPI81(parent, this, "SPI81")
    , SPI82(parent, this, "SPI82")
    , SPI83(parent, this, "SPI83")
    , SPI84(parent, this, "SPI84")
    , SPI85(parent, this, "SPI85")
    , SPI86(parent, this, "SPI86")
    , SPI87(parent, this, "SPI87")
    , SPI88(parent, this, "SPI88")
    , SPI89(parent, this, "SPI89")
    , SPI90(parent, this, "SPI90")
    , SPI91(parent, this, "SPI91")
    , SPI92(parent, this, "SPI92")
    , SPI93(parent, this, "SPI93")
    , SPI94(parent, this, "SPI94")
    , SPI95(parent, this, "SPI95")
    , SPIVector(parent, this, "SPIVector")
    , periphReset(parent, this, "periphReset")
    , CFGSDISABLE(parent, this, "CFGSDISABLE")
    , GICCDISABLE(parent, this, "GICCDISABLE")
    , EVENTI(parent, this, "EVENTI")
    , EVENTO(parent, this, "EVENTO")
    , PPI16_C0_0(parent, this, "PPI16_C0_0")
    , PPI17_C0_0(parent, this, "PPI17_C0_0")
    , PPI18_C0_0(parent, this, "PPI18_C0_0")
    , PPI19_C0_0(parent, this, "PPI19_C0_0")
    , PPI20_C0_0(parent, this, "PPI20_C0_0")
    , PPI21_C0_0(parent, this, "PPI21_C0_0")
    , PPI22_C0_0(parent, this, "PPI22_C0_0")
    , PPI23_C0_0(parent, this, "PPI23_C0_0")
    , PPI24_C0_0(parent, this, "PPI24_C0_0")
    , PPI25_C0_0(parent, this, "PPI25_C0_0")
    , PPI26_C0_0(parent, this, "PPI26_C0_0")
    , PPI27_C0_0(parent, this, "PPI27_C0_0")
    , PPI28_C0_0(parent, this, "PPI28_C0_0")
    , PPI29_C0_0(parent, this, "PPI29_C0_0")
    , PPI30_C0_0(parent, this, "PPI30_C0_0")
    , PPI31_C0_0(parent, this, "PPI31_C0_0")
    , CNTVIRQ_C0_0(parent, this, "CNTVIRQ_C0_0")
    , CNTPSIRQ_C0_0(parent, this, "CNTPSIRQ_C0_0")
    , CNTPNSIRQ_C0_0(parent, this, "CNTPNSIRQ_C0_0")
    , CNTPHPIRQ_C0_0(parent, this, "CNTPHPIRQ_C0_0")
    , IRQOUT_C0_0(parent, this, "IRQOUT_C0_0")
    , FIQOUT_C0_0(parent, this, "FIQOUT_C0_0")
    , CLUSTERIDAFF1_C0(parent, this, "CLUSTERIDAFF1_C0")
    , CLUSTERIDAFF2_C0(parent, this, "CLUSTERIDAFF2_C0")
    , CLUSTERIDAFF3_C0(parent, this, "CLUSTERIDAFF3_C0")
    , RVBARADDRx_C0_0(parent, this, "RVBARADDRx_C0_0")
    , AA64nAA32_C0_0(parent, this, "AA64nAA32_C0_0")
    , VINITHI_C0_0(parent, this, "VINITHI_C0_0")
    , CFGEND_C0_0(parent, this, "CFGEND_C0_0")
    , CFGTE_C0_0(parent, this, "CFGTE_C0_0")
    , reset_C0_0(parent, this, "reset_C0_0")
    , fiq_C0_0(parent, this, "fiq_C0_0")
    , irq_C0_0(parent, this, "irq_C0_0")
    , sei_C0_0(parent, this, "sei_C0_0")
    , vfiq_C0_0(parent, this, "vfiq_C0_0")
    , virq_C0_0(parent, this, "virq_C0_0")
    , vsei_C0_0(parent, this, "vsei_C0_0")
    , AXI_SLVERR_C0_0(parent, this, "AXI_SLVERR_C0_0")
    , CP15SDISABLE_C0_0(parent, this, "CP15SDISABLE_C0_0")
    , PMUIRQ_C0_0(parent, this, "PMUIRQ_C0_0")
    , SMPEN_C0_0(parent, this, "SMPEN_C0_0")
    , PPI16_C0_1(parent, this, "PPI16_C0_1")
    , PPI17_C0_1(parent, this, "PPI17_C0_1")
    , PPI18_C0_1(parent, this, "PPI18_C0_1")
    , PPI19_C0_1(parent, this, "PPI19_C0_1")
    , PPI20_C0_1(parent, this, "PPI20_C0_1")
    , PPI21_C0_1(parent, this, "PPI21_C0_1")
    , PPI22_C0_1(parent, this, "PPI22_C0_1")
    , PPI23_C0_1(parent, this, "PPI23_C0_1")
    , PPI24_C0_1(parent, this, "PPI24_C0_1")
    , PPI25_C0_1(parent, this, "PPI25_C0_1")
    , PPI26_C0_1(parent, this, "PPI26_C0_1")
    , PPI27_C0_1(parent, this, "PPI27_C0_1")
    , PPI28_C0_1(parent, this, "PPI28_C0_1")
    , PPI29_C0_1(parent, this, "PPI29_C0_1")
    , PPI30_C0_1(parent, this, "PPI30_C0_1")
    , PPI31_C0_1(parent, this, "PPI31_C0_1")
    , CNTVIRQ_C0_1(parent, this, "CNTVIRQ_C0_1")
    , CNTPSIRQ_C0_1(parent, this, "CNTPSIRQ_C0_1")
    , CNTPNSIRQ_C0_1(parent, this, "CNTPNSIRQ_C0_1")
    , CNTPHPIRQ_C0_1(parent, this, "CNTPHPIRQ_C0_1")
    , IRQOUT_C0_1(parent, this, "IRQOUT_C0_1")
    , FIQOUT_C0_1(parent, this, "FIQOUT_C0_1")
    , RVBARADDRx_C0_1(parent, this, "RVBARADDRx_C0_1")
    , AA64nAA32_C0_1(parent, this, "AA64nAA32_C0_1")
    , VINITHI_C0_1(parent, this, "VINITHI_C0_1")
    , CFGEND_C0_1(parent, this, "CFGEND_C0_1")
    , CFGTE_C0_1(parent, this, "CFGTE_C0_1")
    , reset_C0_1(parent, this, "reset_C0_1")
    , fiq_C0_1(parent, this, "fiq_C0_1")
    , irq_C0_1(parent, this, "irq_C0_1")
    , sei_C0_1(parent, this, "sei_C0_1")
    , vfiq_C0_1(parent, this, "vfiq_C0_1")
    , virq_C0_1(parent, this, "virq_C0_1")
    , vsei_C0_1(parent, this, "vsei_C0_1")
    , AXI_SLVERR_C0_1(parent, this, "AXI_SLVERR_C0_1")
    , CP15SDISABLE_C0_1(parent, this, "CP15SDISABLE_C0_1")
    , PMUIRQ_C0_1(parent, this, "PMUIRQ_C0_1")
    , SMPEN_C0_1(parent, this, "SMPEN_C0_1")
    , PPI16_C0_2(parent, this, "PPI16_C0_2")
    , PPI17_C0_2(parent, this, "PPI17_C0_2")
    , PPI18_C0_2(parent, this, "PPI18_C0_2")
    , PPI19_C0_2(parent, this, "PPI19_C0_2")
    , PPI20_C0_2(parent, this, "PPI20_C0_2")
    , PPI21_C0_2(parent, this, "PPI21_C0_2")
    , PPI22_C0_2(parent, this, "PPI22_C0_2")
    , PPI23_C0_2(parent, this, "PPI23_C0_2")
    , PPI24_C0_2(parent, this, "PPI24_C0_2")
    , PPI25_C0_2(parent, this, "PPI25_C0_2")
    , PPI26_C0_2(parent, this, "PPI26_C0_2")
    , PPI27_C0_2(parent, this, "PPI27_C0_2")
    , PPI28_C0_2(parent, this, "PPI28_C0_2")
    , PPI29_C0_2(parent, this, "PPI29_C0_2")
    , PPI30_C0_2(parent, this, "PPI30_C0_2")
    , PPI31_C0_2(parent, this, "PPI31_C0_2")
    , CNTVIRQ_C0_2(parent, this, "CNTVIRQ_C0_2")
    , CNTPSIRQ_C0_2(parent, this, "CNTPSIRQ_C0_2")
    , CNTPNSIRQ_C0_2(parent, this, "CNTPNSIRQ_C0_2")
    , CNTPHPIRQ_C0_2(parent, this, "CNTPHPIRQ_C0_2")
    , IRQOUT_C0_2(parent, this, "IRQOUT_C0_2")
    , FIQOUT_C0_2(parent, this, "FIQOUT_C0_2")
    , RVBARADDRx_C0_2(parent, this, "RVBARADDRx_C0_2")
    , AA64nAA32_C0_2(parent, this, "AA64nAA32_C0_2")
    , VINITHI_C0_2(parent, this, "VINITHI_C0_2")
    , CFGEND_C0_2(parent, this, "CFGEND_C0_2")
    , CFGTE_C0_2(parent, this, "CFGTE_C0_2")
    , reset_C0_2(parent, this, "reset_C0_2")
    , fiq_C0_2(parent, this, "fiq_C0_2")
    , irq_C0_2(parent, this, "irq_C0_2")
    , sei_C0_2(parent, this, "sei_C0_2")
    , vfiq_C0_2(parent, this, "vfiq_C0_2")
    , virq_C0_2(parent, this, "virq_C0_2")
    , vsei_C0_2(parent, this, "vsei_C0_2")
    , AXI_SLVERR_C0_2(parent, this, "AXI_SLVERR_C0_2")
    , CP15SDISABLE_C0_2(parent, this, "CP15SDISABLE_C0_2")
    , PMUIRQ_C0_2(parent, this, "PMUIRQ_C0_2")
    , SMPEN_C0_2(parent, this, "SMPEN_C0_2")
    , PPI16_C0_3(parent, this, "PPI16_C0_3")
    , PPI17_C0_3(parent, this, "PPI17_C0_3")
    , PPI18_C0_3(parent, this, "PPI18_C0_3")
    , PPI19_C0_3(parent, this, "PPI19_C0_3")
    , PPI20_C0_3(parent, this, "PPI20_C0_3")
    , PPI21_C0_3(parent, this, "PPI21_C0_3")
    , PPI22_C0_3(parent, this, "PPI22_C0_3")
    , PPI23_C0_3(parent, this, "PPI23_C0_3")
    , PPI24_C0_3(parent, this, "PPI24_C0_3")
    , PPI25_C0_3(parent, this, "PPI25_C0_3")
    , PPI26_C0_3(parent, this, "PPI26_C0_3")
    , PPI27_C0_3(parent, this, "PPI27_C0_3")
    , PPI28_C0_3(parent, this, "PPI28_C0_3")
    , PPI29_C0_3(parent, this, "PPI29_C0_3")
    , PPI30_C0_3(parent, this, "PPI30_C0_3")
    , PPI31_C0_3(parent, this, "PPI31_C0_3")
    , CNTVIRQ_C0_3(parent, this, "CNTVIRQ_C0_3")
    , CNTPSIRQ_C0_3(parent, this, "CNTPSIRQ_C0_3")
    , CNTPNSIRQ_C0_3(parent, this, "CNTPNSIRQ_C0_3")
    , CNTPHPIRQ_C0_3(parent, this, "CNTPHPIRQ_C0_3")
    , IRQOUT_C0_3(parent, this, "IRQOUT_C0_3")
    , FIQOUT_C0_3(parent, this, "FIQOUT_C0_3")
    , RVBARADDRx_C0_3(parent, this, "RVBARADDRx_C0_3")
    , AA64nAA32_C0_3(parent, this, "AA64nAA32_C0_3")
    , VINITHI_C0_3(parent, this, "VINITHI_C0_3")
    , CFGEND_C0_3(parent, this, "CFGEND_C0_3")
    , CFGTE_C0_3(parent, this, "CFGTE_C0_3")
    , reset_C0_3(parent, this, "reset_C0_3")
    , fiq_C0_3(parent, this, "fiq_C0_3")
    , irq_C0_3(parent, this, "irq_C0_3")
    , sei_C0_3(parent, this, "sei_C0_3")
    , vfiq_C0_3(parent, this, "vfiq_C0_3")
    , virq_C0_3(parent, this, "virq_C0_3")
    , vsei_C0_3(parent, this, "vsei_C0_3")
    , AXI_SLVERR_C0_3(parent, this, "AXI_SLVERR_C0_3")
    , CP15SDISABLE_C0_3(parent, this, "CP15SDISABLE_C0_3")
    , PMUIRQ_C0_3(parent, this, "PMUIRQ_C0_3")
    , SMPEN_C0_3(parent, this, "SMPEN_C0_3")
    , PPI16_C1_0(parent, this, "PPI16_C1_0")
    , PPI17_C1_0(parent, this, "PPI17_C1_0")
    , PPI18_C1_0(parent, this, "PPI18_C1_0")
    , PPI19_C1_0(parent, this, "PPI19_C1_0")
    , PPI20_C1_0(parent, this, "PPI20_C1_0")
    , PPI21_C1_0(parent, this, "PPI21_C1_0")
    , PPI22_C1_0(parent, this, "PPI22_C1_0")
    , PPI23_C1_0(parent, this, "PPI23_C1_0")
    , PPI24_C1_0(parent, this, "PPI24_C1_0")
    , PPI25_C1_0(parent, this, "PPI25_C1_0")
    , PPI26_C1_0(parent, this, "PPI26_C1_0")
    , PPI27_C1_0(parent, this, "PPI27_C1_0")
    , PPI28_C1_0(parent, this, "PPI28_C1_0")
    , PPI29_C1_0(parent, this, "PPI29_C1_0")
    , PPI30_C1_0(parent, this, "PPI30_C1_0")
    , PPI31_C1_0(parent, this, "PPI31_C1_0")
    , CNTVIRQ_C1_0(parent, this, "CNTVIRQ_C1_0")
    , CNTPSIRQ_C1_0(parent, this, "CNTPSIRQ_C1_0")
    , CNTPNSIRQ_C1_0(parent, this, "CNTPNSIRQ_C1_0")
    , CNTPHPIRQ_C1_0(parent, this, "CNTPHPIRQ_C1_0")
    , IRQOUT_C1_0(parent, this, "IRQOUT_C1_0")
    , FIQOUT_C1_0(parent, this, "FIQOUT_C1_0")
    , CLUSTERIDAFF1_C1(parent, this, "CLUSTERIDAFF1_C1")
    , CLUSTERIDAFF2_C1(parent, this, "CLUSTERIDAFF2_C1")
    , CLUSTERIDAFF3_C1(parent, this, "CLUSTERIDAFF3_C1")
    , RVBARADDRx_C1_0(parent, this, "RVBARADDRx_C1_0")
    , AA64nAA32_C1_0(parent, this, "AA64nAA32_C1_0")
    , VINITHI_C1_0(parent, this, "VINITHI_C1_0")
    , CFGEND_C1_0(parent, this, "CFGEND_C1_0")
    , CFGTE_C1_0(parent, this, "CFGTE_C1_0")
    , reset_C1_0(parent, this, "reset_C1_0")
    , fiq_C1_0(parent, this, "fiq_C1_0")
    , irq_C1_0(parent, this, "irq_C1_0")
    , sei_C1_0(parent, this, "sei_C1_0")
    , vfiq_C1_0(parent, this, "vfiq_C1_0")
    , virq_C1_0(parent, this, "virq_C1_0")
    , vsei_C1_0(parent, this, "vsei_C1_0")
    , AXI_SLVERR_C1_0(parent, this, "AXI_SLVERR_C1_0")
    , CP15SDISABLE_C1_0(parent, this, "CP15SDISABLE_C1_0")
    , PMUIRQ_C1_0(parent, this, "PMUIRQ_C1_0")
    , SMPEN_C1_0(parent, this, "SMPEN_C1_0")
    , PPI16_C1_1(parent, this, "PPI16_C1_1")
    , PPI17_C1_1(parent, this, "PPI17_C1_1")
    , PPI18_C1_1(parent, this, "PPI18_C1_1")
    , PPI19_C1_1(parent, this, "PPI19_C1_1")
    , PPI20_C1_1(parent, this, "PPI20_C1_1")
    , PPI21_C1_1(parent, this, "PPI21_C1_1")
    , PPI22_C1_1(parent, this, "PPI22_C1_1")
    , PPI23_C1_1(parent, this, "PPI23_C1_1")
    , PPI24_C1_1(parent, this, "PPI24_C1_1")
    , PPI25_C1_1(parent, this, "PPI25_C1_1")
    , PPI26_C1_1(parent, this, "PPI26_C1_1")
    , PPI27_C1_1(parent, this, "PPI27_C1_1")
    , PPI28_C1_1(parent, this, "PPI28_C1_1")
    , PPI29_C1_1(parent, this, "PPI29_C1_1")
    , PPI30_C1_1(parent, this, "PPI30_C1_1")
    , PPI31_C1_1(parent, this, "PPI31_C1_1")
    , CNTVIRQ_C1_1(parent, this, "CNTVIRQ_C1_1")
    , CNTPSIRQ_C1_1(parent, this, "CNTPSIRQ_C1_1")
    , CNTPNSIRQ_C1_1(parent, this, "CNTPNSIRQ_C1_1")
    , CNTPHPIRQ_C1_1(parent, this, "CNTPHPIRQ_C1_1")
    , IRQOUT_C1_1(parent, this, "IRQOUT_C1_1")
    , FIQOUT_C1_1(parent, this, "FIQOUT_C1_1")
    , RVBARADDRx_C1_1(parent, this, "RVBARADDRx_C1_1")
    , AA64nAA32_C1_1(parent, this, "AA64nAA32_C1_1")
    , VINITHI_C1_1(parent, this, "VINITHI_C1_1")
    , CFGEND_C1_1(parent, this, "CFGEND_C1_1")
    , CFGTE_C1_1(parent, this, "CFGTE_C1_1")
    , reset_C1_1(parent, this, "reset_C1_1")
    , fiq_C1_1(parent, this, "fiq_C1_1")
    , irq_C1_1(parent, this, "irq_C1_1")
    , sei_C1_1(parent, this, "sei_C1_1")
    , vfiq_C1_1(parent, this, "vfiq_C1_1")
    , virq_C1_1(parent, this, "virq_C1_1")
    , vsei_C1_1(parent, this, "vsei_C1_1")
    , AXI_SLVERR_C1_1(parent, this, "AXI_SLVERR_C1_1")
    , CP15SDISABLE_C1_1(parent, this, "CP15SDISABLE_C1_1")
    , PMUIRQ_C1_1(parent, this, "PMUIRQ_C1_1")
    , SMPEN_C1_1(parent, this, "SMPEN_C1_1")
    , PPI16_C1_2(parent, this, "PPI16_C1_2")
    , PPI17_C1_2(parent, this, "PPI17_C1_2")
    , PPI18_C1_2(parent, this, "PPI18_C1_2")
    , PPI19_C1_2(parent, this, "PPI19_C1_2")
    , PPI20_C1_2(parent, this, "PPI20_C1_2")
    , PPI21_C1_2(parent, this, "PPI21_C1_2")
    , PPI22_C1_2(parent, this, "PPI22_C1_2")
    , PPI23_C1_2(parent, this, "PPI23_C1_2")
    , PPI24_C1_2(parent, this, "PPI24_C1_2")
    , PPI25_C1_2(parent, this, "PPI25_C1_2")
    , PPI26_C1_2(parent, this, "PPI26_C1_2")
    , PPI27_C1_2(parent, this, "PPI27_C1_2")
    , PPI28_C1_2(parent, this, "PPI28_C1_2")
    , PPI29_C1_2(parent, this, "PPI29_C1_2")
    , PPI30_C1_2(parent, this, "PPI30_C1_2")
    , PPI31_C1_2(parent, this, "PPI31_C1_2")
    , CNTVIRQ_C1_2(parent, this, "CNTVIRQ_C1_2")
    , CNTPSIRQ_C1_2(parent, this, "CNTPSIRQ_C1_2")
    , CNTPNSIRQ_C1_2(parent, this, "CNTPNSIRQ_C1_2")
    , CNTPHPIRQ_C1_2(parent, this, "CNTPHPIRQ_C1_2")
    , IRQOUT_C1_2(parent, this, "IRQOUT_C1_2")
    , FIQOUT_C1_2(parent, this, "FIQOUT_C1_2")
    , RVBARADDRx_C1_2(parent, this, "RVBARADDRx_C1_2")
    , AA64nAA32_C1_2(parent, this, "AA64nAA32_C1_2")
    , VINITHI_C1_2(parent, this, "VINITHI_C1_2")
    , CFGEND_C1_2(parent, this, "CFGEND_C1_2")
    , CFGTE_C1_2(parent, this, "CFGTE_C1_2")
    , reset_C1_2(parent, this, "reset_C1_2")
    , fiq_C1_2(parent, this, "fiq_C1_2")
    , irq_C1_2(parent, this, "irq_C1_2")
    , sei_C1_2(parent, this, "sei_C1_2")
    , vfiq_C1_2(parent, this, "vfiq_C1_2")
    , virq_C1_2(parent, this, "virq_C1_2")
    , vsei_C1_2(parent, this, "vsei_C1_2")
    , AXI_SLVERR_C1_2(parent, this, "AXI_SLVERR_C1_2")
    , CP15SDISABLE_C1_2(parent, this, "CP15SDISABLE_C1_2")
    , PMUIRQ_C1_2(parent, this, "PMUIRQ_C1_2")
    , SMPEN_C1_2(parent, this, "SMPEN_C1_2")
    , PPI16_C1_3(parent, this, "PPI16_C1_3")
    , PPI17_C1_3(parent, this, "PPI17_C1_3")
    , PPI18_C1_3(parent, this, "PPI18_C1_3")
    , PPI19_C1_3(parent, this, "PPI19_C1_3")
    , PPI20_C1_3(parent, this, "PPI20_C1_3")
    , PPI21_C1_3(parent, this, "PPI21_C1_3")
    , PPI22_C1_3(parent, this, "PPI22_C1_3")
    , PPI23_C1_3(parent, this, "PPI23_C1_3")
    , PPI24_C1_3(parent, this, "PPI24_C1_3")
    , PPI25_C1_3(parent, this, "PPI25_C1_3")
    , PPI26_C1_3(parent, this, "PPI26_C1_3")
    , PPI27_C1_3(parent, this, "PPI27_C1_3")
    , PPI28_C1_3(parent, this, "PPI28_C1_3")
    , PPI29_C1_3(parent, this, "PPI29_C1_3")
    , PPI30_C1_3(parent, this, "PPI30_C1_3")
    , PPI31_C1_3(parent, this, "PPI31_C1_3")
    , CNTVIRQ_C1_3(parent, this, "CNTVIRQ_C1_3")
    , CNTPSIRQ_C1_3(parent, this, "CNTPSIRQ_C1_3")
    , CNTPNSIRQ_C1_3(parent, this, "CNTPNSIRQ_C1_3")
    , CNTPHPIRQ_C1_3(parent, this, "CNTPHPIRQ_C1_3")
    , IRQOUT_C1_3(parent, this, "IRQOUT_C1_3")
    , FIQOUT_C1_3(parent, this, "FIQOUT_C1_3")
    , RVBARADDRx_C1_3(parent, this, "RVBARADDRx_C1_3")
    , AA64nAA32_C1_3(parent, this, "AA64nAA32_C1_3")
    , VINITHI_C1_3(parent, this, "VINITHI_C1_3")
    , CFGEND_C1_3(parent, this, "CFGEND_C1_3")
    , CFGTE_C1_3(parent, this, "CFGTE_C1_3")
    , reset_C1_3(parent, this, "reset_C1_3")
    , fiq_C1_3(parent, this, "fiq_C1_3")
    , irq_C1_3(parent, this, "irq_C1_3")
    , sei_C1_3(parent, this, "sei_C1_3")
    , vfiq_C1_3(parent, this, "vfiq_C1_3")
    , virq_C1_3(parent, this, "virq_C1_3")
    , vsei_C1_3(parent, this, "vsei_C1_3")
    , AXI_SLVERR_C1_3(parent, this, "AXI_SLVERR_C1_3")
    , CP15SDISABLE_C1_3(parent, this, "CP15SDISABLE_C1_3")
    , PMUIRQ_C1_3(parent, this, "PMUIRQ_C1_3")
    , SMPEN_C1_3(parent, this, "SMPEN_C1_3")
    {
    }

    arm_MultiCluster(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=44, Uns32 DATAWidth=44, Uns32 GICRegistersWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , GICRegisters (parent, this, "GICRegisters", GICRegistersWidth)
    , SPI32(parent, this, "SPI32")
    , SPI33(parent, this, "SPI33")
    , SPI34(parent, this, "SPI34")
    , SPI35(parent, this, "SPI35")
    , SPI36(parent, this, "SPI36")
    , SPI37(parent, this, "SPI37")
    , SPI38(parent, this, "SPI38")
    , SPI39(parent, this, "SPI39")
    , SPI40(parent, this, "SPI40")
    , SPI41(parent, this, "SPI41")
    , SPI42(parent, this, "SPI42")
    , SPI43(parent, this, "SPI43")
    , SPI44(parent, this, "SPI44")
    , SPI45(parent, this, "SPI45")
    , SPI46(parent, this, "SPI46")
    , SPI47(parent, this, "SPI47")
    , SPI48(parent, this, "SPI48")
    , SPI49(parent, this, "SPI49")
    , SPI50(parent, this, "SPI50")
    , SPI51(parent, this, "SPI51")
    , SPI52(parent, this, "SPI52")
    , SPI53(parent, this, "SPI53")
    , SPI54(parent, this, "SPI54")
    , SPI55(parent, this, "SPI55")
    , SPI56(parent, this, "SPI56")
    , SPI57(parent, this, "SPI57")
    , SPI58(parent, this, "SPI58")
    , SPI59(parent, this, "SPI59")
    , SPI60(parent, this, "SPI60")
    , SPI61(parent, this, "SPI61")
    , SPI62(parent, this, "SPI62")
    , SPI63(parent, this, "SPI63")
    , SPI64(parent, this, "SPI64")
    , SPI65(parent, this, "SPI65")
    , SPI66(parent, this, "SPI66")
    , SPI67(parent, this, "SPI67")
    , SPI68(parent, this, "SPI68")
    , SPI69(parent, this, "SPI69")
    , SPI70(parent, this, "SPI70")
    , SPI71(parent, this, "SPI71")
    , SPI72(parent, this, "SPI72")
    , SPI73(parent, this, "SPI73")
    , SPI74(parent, this, "SPI74")
    , SPI75(parent, this, "SPI75")
    , SPI76(parent, this, "SPI76")
    , SPI77(parent, this, "SPI77")
    , SPI78(parent, this, "SPI78")
    , SPI79(parent, this, "SPI79")
    , SPI80(parent, this, "SPI80")
    , SPI81(parent, this, "SPI81")
    , SPI82(parent, this, "SPI82")
    , SPI83(parent, this, "SPI83")
    , SPI84(parent, this, "SPI84")
    , SPI85(parent, this, "SPI85")
    , SPI86(parent, this, "SPI86")
    , SPI87(parent, this, "SPI87")
    , SPI88(parent, this, "SPI88")
    , SPI89(parent, this, "SPI89")
    , SPI90(parent, this, "SPI90")
    , SPI91(parent, this, "SPI91")
    , SPI92(parent, this, "SPI92")
    , SPI93(parent, this, "SPI93")
    , SPI94(parent, this, "SPI94")
    , SPI95(parent, this, "SPI95")
    , SPIVector(parent, this, "SPIVector")
    , periphReset(parent, this, "periphReset")
    , CFGSDISABLE(parent, this, "CFGSDISABLE")
    , GICCDISABLE(parent, this, "GICCDISABLE")
    , EVENTI(parent, this, "EVENTI")
    , EVENTO(parent, this, "EVENTO")
    , PPI16_C0_0(parent, this, "PPI16_C0_0")
    , PPI17_C0_0(parent, this, "PPI17_C0_0")
    , PPI18_C0_0(parent, this, "PPI18_C0_0")
    , PPI19_C0_0(parent, this, "PPI19_C0_0")
    , PPI20_C0_0(parent, this, "PPI20_C0_0")
    , PPI21_C0_0(parent, this, "PPI21_C0_0")
    , PPI22_C0_0(parent, this, "PPI22_C0_0")
    , PPI23_C0_0(parent, this, "PPI23_C0_0")
    , PPI24_C0_0(parent, this, "PPI24_C0_0")
    , PPI25_C0_0(parent, this, "PPI25_C0_0")
    , PPI26_C0_0(parent, this, "PPI26_C0_0")
    , PPI27_C0_0(parent, this, "PPI27_C0_0")
    , PPI28_C0_0(parent, this, "PPI28_C0_0")
    , PPI29_C0_0(parent, this, "PPI29_C0_0")
    , PPI30_C0_0(parent, this, "PPI30_C0_0")
    , PPI31_C0_0(parent, this, "PPI31_C0_0")
    , CNTVIRQ_C0_0(parent, this, "CNTVIRQ_C0_0")
    , CNTPSIRQ_C0_0(parent, this, "CNTPSIRQ_C0_0")
    , CNTPNSIRQ_C0_0(parent, this, "CNTPNSIRQ_C0_0")
    , CNTPHPIRQ_C0_0(parent, this, "CNTPHPIRQ_C0_0")
    , IRQOUT_C0_0(parent, this, "IRQOUT_C0_0")
    , FIQOUT_C0_0(parent, this, "FIQOUT_C0_0")
    , CLUSTERIDAFF1_C0(parent, this, "CLUSTERIDAFF1_C0")
    , CLUSTERIDAFF2_C0(parent, this, "CLUSTERIDAFF2_C0")
    , CLUSTERIDAFF3_C0(parent, this, "CLUSTERIDAFF3_C0")
    , RVBARADDRx_C0_0(parent, this, "RVBARADDRx_C0_0")
    , AA64nAA32_C0_0(parent, this, "AA64nAA32_C0_0")
    , VINITHI_C0_0(parent, this, "VINITHI_C0_0")
    , CFGEND_C0_0(parent, this, "CFGEND_C0_0")
    , CFGTE_C0_0(parent, this, "CFGTE_C0_0")
    , reset_C0_0(parent, this, "reset_C0_0")
    , fiq_C0_0(parent, this, "fiq_C0_0")
    , irq_C0_0(parent, this, "irq_C0_0")
    , sei_C0_0(parent, this, "sei_C0_0")
    , vfiq_C0_0(parent, this, "vfiq_C0_0")
    , virq_C0_0(parent, this, "virq_C0_0")
    , vsei_C0_0(parent, this, "vsei_C0_0")
    , AXI_SLVERR_C0_0(parent, this, "AXI_SLVERR_C0_0")
    , CP15SDISABLE_C0_0(parent, this, "CP15SDISABLE_C0_0")
    , PMUIRQ_C0_0(parent, this, "PMUIRQ_C0_0")
    , SMPEN_C0_0(parent, this, "SMPEN_C0_0")
    , PPI16_C0_1(parent, this, "PPI16_C0_1")
    , PPI17_C0_1(parent, this, "PPI17_C0_1")
    , PPI18_C0_1(parent, this, "PPI18_C0_1")
    , PPI19_C0_1(parent, this, "PPI19_C0_1")
    , PPI20_C0_1(parent, this, "PPI20_C0_1")
    , PPI21_C0_1(parent, this, "PPI21_C0_1")
    , PPI22_C0_1(parent, this, "PPI22_C0_1")
    , PPI23_C0_1(parent, this, "PPI23_C0_1")
    , PPI24_C0_1(parent, this, "PPI24_C0_1")
    , PPI25_C0_1(parent, this, "PPI25_C0_1")
    , PPI26_C0_1(parent, this, "PPI26_C0_1")
    , PPI27_C0_1(parent, this, "PPI27_C0_1")
    , PPI28_C0_1(parent, this, "PPI28_C0_1")
    , PPI29_C0_1(parent, this, "PPI29_C0_1")
    , PPI30_C0_1(parent, this, "PPI30_C0_1")
    , PPI31_C0_1(parent, this, "PPI31_C0_1")
    , CNTVIRQ_C0_1(parent, this, "CNTVIRQ_C0_1")
    , CNTPSIRQ_C0_1(parent, this, "CNTPSIRQ_C0_1")
    , CNTPNSIRQ_C0_1(parent, this, "CNTPNSIRQ_C0_1")
    , CNTPHPIRQ_C0_1(parent, this, "CNTPHPIRQ_C0_1")
    , IRQOUT_C0_1(parent, this, "IRQOUT_C0_1")
    , FIQOUT_C0_1(parent, this, "FIQOUT_C0_1")
    , RVBARADDRx_C0_1(parent, this, "RVBARADDRx_C0_1")
    , AA64nAA32_C0_1(parent, this, "AA64nAA32_C0_1")
    , VINITHI_C0_1(parent, this, "VINITHI_C0_1")
    , CFGEND_C0_1(parent, this, "CFGEND_C0_1")
    , CFGTE_C0_1(parent, this, "CFGTE_C0_1")
    , reset_C0_1(parent, this, "reset_C0_1")
    , fiq_C0_1(parent, this, "fiq_C0_1")
    , irq_C0_1(parent, this, "irq_C0_1")
    , sei_C0_1(parent, this, "sei_C0_1")
    , vfiq_C0_1(parent, this, "vfiq_C0_1")
    , virq_C0_1(parent, this, "virq_C0_1")
    , vsei_C0_1(parent, this, "vsei_C0_1")
    , AXI_SLVERR_C0_1(parent, this, "AXI_SLVERR_C0_1")
    , CP15SDISABLE_C0_1(parent, this, "CP15SDISABLE_C0_1")
    , PMUIRQ_C0_1(parent, this, "PMUIRQ_C0_1")
    , SMPEN_C0_1(parent, this, "SMPEN_C0_1")
    , PPI16_C0_2(parent, this, "PPI16_C0_2")
    , PPI17_C0_2(parent, this, "PPI17_C0_2")
    , PPI18_C0_2(parent, this, "PPI18_C0_2")
    , PPI19_C0_2(parent, this, "PPI19_C0_2")
    , PPI20_C0_2(parent, this, "PPI20_C0_2")
    , PPI21_C0_2(parent, this, "PPI21_C0_2")
    , PPI22_C0_2(parent, this, "PPI22_C0_2")
    , PPI23_C0_2(parent, this, "PPI23_C0_2")
    , PPI24_C0_2(parent, this, "PPI24_C0_2")
    , PPI25_C0_2(parent, this, "PPI25_C0_2")
    , PPI26_C0_2(parent, this, "PPI26_C0_2")
    , PPI27_C0_2(parent, this, "PPI27_C0_2")
    , PPI28_C0_2(parent, this, "PPI28_C0_2")
    , PPI29_C0_2(parent, this, "PPI29_C0_2")
    , PPI30_C0_2(parent, this, "PPI30_C0_2")
    , PPI31_C0_2(parent, this, "PPI31_C0_2")
    , CNTVIRQ_C0_2(parent, this, "CNTVIRQ_C0_2")
    , CNTPSIRQ_C0_2(parent, this, "CNTPSIRQ_C0_2")
    , CNTPNSIRQ_C0_2(parent, this, "CNTPNSIRQ_C0_2")
    , CNTPHPIRQ_C0_2(parent, this, "CNTPHPIRQ_C0_2")
    , IRQOUT_C0_2(parent, this, "IRQOUT_C0_2")
    , FIQOUT_C0_2(parent, this, "FIQOUT_C0_2")
    , RVBARADDRx_C0_2(parent, this, "RVBARADDRx_C0_2")
    , AA64nAA32_C0_2(parent, this, "AA64nAA32_C0_2")
    , VINITHI_C0_2(parent, this, "VINITHI_C0_2")
    , CFGEND_C0_2(parent, this, "CFGEND_C0_2")
    , CFGTE_C0_2(parent, this, "CFGTE_C0_2")
    , reset_C0_2(parent, this, "reset_C0_2")
    , fiq_C0_2(parent, this, "fiq_C0_2")
    , irq_C0_2(parent, this, "irq_C0_2")
    , sei_C0_2(parent, this, "sei_C0_2")
    , vfiq_C0_2(parent, this, "vfiq_C0_2")
    , virq_C0_2(parent, this, "virq_C0_2")
    , vsei_C0_2(parent, this, "vsei_C0_2")
    , AXI_SLVERR_C0_2(parent, this, "AXI_SLVERR_C0_2")
    , CP15SDISABLE_C0_2(parent, this, "CP15SDISABLE_C0_2")
    , PMUIRQ_C0_2(parent, this, "PMUIRQ_C0_2")
    , SMPEN_C0_2(parent, this, "SMPEN_C0_2")
    , PPI16_C0_3(parent, this, "PPI16_C0_3")
    , PPI17_C0_3(parent, this, "PPI17_C0_3")
    , PPI18_C0_3(parent, this, "PPI18_C0_3")
    , PPI19_C0_3(parent, this, "PPI19_C0_3")
    , PPI20_C0_3(parent, this, "PPI20_C0_3")
    , PPI21_C0_3(parent, this, "PPI21_C0_3")
    , PPI22_C0_3(parent, this, "PPI22_C0_3")
    , PPI23_C0_3(parent, this, "PPI23_C0_3")
    , PPI24_C0_3(parent, this, "PPI24_C0_3")
    , PPI25_C0_3(parent, this, "PPI25_C0_3")
    , PPI26_C0_3(parent, this, "PPI26_C0_3")
    , PPI27_C0_3(parent, this, "PPI27_C0_3")
    , PPI28_C0_3(parent, this, "PPI28_C0_3")
    , PPI29_C0_3(parent, this, "PPI29_C0_3")
    , PPI30_C0_3(parent, this, "PPI30_C0_3")
    , PPI31_C0_3(parent, this, "PPI31_C0_3")
    , CNTVIRQ_C0_3(parent, this, "CNTVIRQ_C0_3")
    , CNTPSIRQ_C0_3(parent, this, "CNTPSIRQ_C0_3")
    , CNTPNSIRQ_C0_3(parent, this, "CNTPNSIRQ_C0_3")
    , CNTPHPIRQ_C0_3(parent, this, "CNTPHPIRQ_C0_3")
    , IRQOUT_C0_3(parent, this, "IRQOUT_C0_3")
    , FIQOUT_C0_3(parent, this, "FIQOUT_C0_3")
    , RVBARADDRx_C0_3(parent, this, "RVBARADDRx_C0_3")
    , AA64nAA32_C0_3(parent, this, "AA64nAA32_C0_3")
    , VINITHI_C0_3(parent, this, "VINITHI_C0_3")
    , CFGEND_C0_3(parent, this, "CFGEND_C0_3")
    , CFGTE_C0_3(parent, this, "CFGTE_C0_3")
    , reset_C0_3(parent, this, "reset_C0_3")
    , fiq_C0_3(parent, this, "fiq_C0_3")
    , irq_C0_3(parent, this, "irq_C0_3")
    , sei_C0_3(parent, this, "sei_C0_3")
    , vfiq_C0_3(parent, this, "vfiq_C0_3")
    , virq_C0_3(parent, this, "virq_C0_3")
    , vsei_C0_3(parent, this, "vsei_C0_3")
    , AXI_SLVERR_C0_3(parent, this, "AXI_SLVERR_C0_3")
    , CP15SDISABLE_C0_3(parent, this, "CP15SDISABLE_C0_3")
    , PMUIRQ_C0_3(parent, this, "PMUIRQ_C0_3")
    , SMPEN_C0_3(parent, this, "SMPEN_C0_3")
    , PPI16_C1_0(parent, this, "PPI16_C1_0")
    , PPI17_C1_0(parent, this, "PPI17_C1_0")
    , PPI18_C1_0(parent, this, "PPI18_C1_0")
    , PPI19_C1_0(parent, this, "PPI19_C1_0")
    , PPI20_C1_0(parent, this, "PPI20_C1_0")
    , PPI21_C1_0(parent, this, "PPI21_C1_0")
    , PPI22_C1_0(parent, this, "PPI22_C1_0")
    , PPI23_C1_0(parent, this, "PPI23_C1_0")
    , PPI24_C1_0(parent, this, "PPI24_C1_0")
    , PPI25_C1_0(parent, this, "PPI25_C1_0")
    , PPI26_C1_0(parent, this, "PPI26_C1_0")
    , PPI27_C1_0(parent, this, "PPI27_C1_0")
    , PPI28_C1_0(parent, this, "PPI28_C1_0")
    , PPI29_C1_0(parent, this, "PPI29_C1_0")
    , PPI30_C1_0(parent, this, "PPI30_C1_0")
    , PPI31_C1_0(parent, this, "PPI31_C1_0")
    , CNTVIRQ_C1_0(parent, this, "CNTVIRQ_C1_0")
    , CNTPSIRQ_C1_0(parent, this, "CNTPSIRQ_C1_0")
    , CNTPNSIRQ_C1_0(parent, this, "CNTPNSIRQ_C1_0")
    , CNTPHPIRQ_C1_0(parent, this, "CNTPHPIRQ_C1_0")
    , IRQOUT_C1_0(parent, this, "IRQOUT_C1_0")
    , FIQOUT_C1_0(parent, this, "FIQOUT_C1_0")
    , CLUSTERIDAFF1_C1(parent, this, "CLUSTERIDAFF1_C1")
    , CLUSTERIDAFF2_C1(parent, this, "CLUSTERIDAFF2_C1")
    , CLUSTERIDAFF3_C1(parent, this, "CLUSTERIDAFF3_C1")
    , RVBARADDRx_C1_0(parent, this, "RVBARADDRx_C1_0")
    , AA64nAA32_C1_0(parent, this, "AA64nAA32_C1_0")
    , VINITHI_C1_0(parent, this, "VINITHI_C1_0")
    , CFGEND_C1_0(parent, this, "CFGEND_C1_0")
    , CFGTE_C1_0(parent, this, "CFGTE_C1_0")
    , reset_C1_0(parent, this, "reset_C1_0")
    , fiq_C1_0(parent, this, "fiq_C1_0")
    , irq_C1_0(parent, this, "irq_C1_0")
    , sei_C1_0(parent, this, "sei_C1_0")
    , vfiq_C1_0(parent, this, "vfiq_C1_0")
    , virq_C1_0(parent, this, "virq_C1_0")
    , vsei_C1_0(parent, this, "vsei_C1_0")
    , AXI_SLVERR_C1_0(parent, this, "AXI_SLVERR_C1_0")
    , CP15SDISABLE_C1_0(parent, this, "CP15SDISABLE_C1_0")
    , PMUIRQ_C1_0(parent, this, "PMUIRQ_C1_0")
    , SMPEN_C1_0(parent, this, "SMPEN_C1_0")
    , PPI16_C1_1(parent, this, "PPI16_C1_1")
    , PPI17_C1_1(parent, this, "PPI17_C1_1")
    , PPI18_C1_1(parent, this, "PPI18_C1_1")
    , PPI19_C1_1(parent, this, "PPI19_C1_1")
    , PPI20_C1_1(parent, this, "PPI20_C1_1")
    , PPI21_C1_1(parent, this, "PPI21_C1_1")
    , PPI22_C1_1(parent, this, "PPI22_C1_1")
    , PPI23_C1_1(parent, this, "PPI23_C1_1")
    , PPI24_C1_1(parent, this, "PPI24_C1_1")
    , PPI25_C1_1(parent, this, "PPI25_C1_1")
    , PPI26_C1_1(parent, this, "PPI26_C1_1")
    , PPI27_C1_1(parent, this, "PPI27_C1_1")
    , PPI28_C1_1(parent, this, "PPI28_C1_1")
    , PPI29_C1_1(parent, this, "PPI29_C1_1")
    , PPI30_C1_1(parent, this, "PPI30_C1_1")
    , PPI31_C1_1(parent, this, "PPI31_C1_1")
    , CNTVIRQ_C1_1(parent, this, "CNTVIRQ_C1_1")
    , CNTPSIRQ_C1_1(parent, this, "CNTPSIRQ_C1_1")
    , CNTPNSIRQ_C1_1(parent, this, "CNTPNSIRQ_C1_1")
    , CNTPHPIRQ_C1_1(parent, this, "CNTPHPIRQ_C1_1")
    , IRQOUT_C1_1(parent, this, "IRQOUT_C1_1")
    , FIQOUT_C1_1(parent, this, "FIQOUT_C1_1")
    , RVBARADDRx_C1_1(parent, this, "RVBARADDRx_C1_1")
    , AA64nAA32_C1_1(parent, this, "AA64nAA32_C1_1")
    , VINITHI_C1_1(parent, this, "VINITHI_C1_1")
    , CFGEND_C1_1(parent, this, "CFGEND_C1_1")
    , CFGTE_C1_1(parent, this, "CFGTE_C1_1")
    , reset_C1_1(parent, this, "reset_C1_1")
    , fiq_C1_1(parent, this, "fiq_C1_1")
    , irq_C1_1(parent, this, "irq_C1_1")
    , sei_C1_1(parent, this, "sei_C1_1")
    , vfiq_C1_1(parent, this, "vfiq_C1_1")
    , virq_C1_1(parent, this, "virq_C1_1")
    , vsei_C1_1(parent, this, "vsei_C1_1")
    , AXI_SLVERR_C1_1(parent, this, "AXI_SLVERR_C1_1")
    , CP15SDISABLE_C1_1(parent, this, "CP15SDISABLE_C1_1")
    , PMUIRQ_C1_1(parent, this, "PMUIRQ_C1_1")
    , SMPEN_C1_1(parent, this, "SMPEN_C1_1")
    , PPI16_C1_2(parent, this, "PPI16_C1_2")
    , PPI17_C1_2(parent, this, "PPI17_C1_2")
    , PPI18_C1_2(parent, this, "PPI18_C1_2")
    , PPI19_C1_2(parent, this, "PPI19_C1_2")
    , PPI20_C1_2(parent, this, "PPI20_C1_2")
    , PPI21_C1_2(parent, this, "PPI21_C1_2")
    , PPI22_C1_2(parent, this, "PPI22_C1_2")
    , PPI23_C1_2(parent, this, "PPI23_C1_2")
    , PPI24_C1_2(parent, this, "PPI24_C1_2")
    , PPI25_C1_2(parent, this, "PPI25_C1_2")
    , PPI26_C1_2(parent, this, "PPI26_C1_2")
    , PPI27_C1_2(parent, this, "PPI27_C1_2")
    , PPI28_C1_2(parent, this, "PPI28_C1_2")
    , PPI29_C1_2(parent, this, "PPI29_C1_2")
    , PPI30_C1_2(parent, this, "PPI30_C1_2")
    , PPI31_C1_2(parent, this, "PPI31_C1_2")
    , CNTVIRQ_C1_2(parent, this, "CNTVIRQ_C1_2")
    , CNTPSIRQ_C1_2(parent, this, "CNTPSIRQ_C1_2")
    , CNTPNSIRQ_C1_2(parent, this, "CNTPNSIRQ_C1_2")
    , CNTPHPIRQ_C1_2(parent, this, "CNTPHPIRQ_C1_2")
    , IRQOUT_C1_2(parent, this, "IRQOUT_C1_2")
    , FIQOUT_C1_2(parent, this, "FIQOUT_C1_2")
    , RVBARADDRx_C1_2(parent, this, "RVBARADDRx_C1_2")
    , AA64nAA32_C1_2(parent, this, "AA64nAA32_C1_2")
    , VINITHI_C1_2(parent, this, "VINITHI_C1_2")
    , CFGEND_C1_2(parent, this, "CFGEND_C1_2")
    , CFGTE_C1_2(parent, this, "CFGTE_C1_2")
    , reset_C1_2(parent, this, "reset_C1_2")
    , fiq_C1_2(parent, this, "fiq_C1_2")
    , irq_C1_2(parent, this, "irq_C1_2")
    , sei_C1_2(parent, this, "sei_C1_2")
    , vfiq_C1_2(parent, this, "vfiq_C1_2")
    , virq_C1_2(parent, this, "virq_C1_2")
    , vsei_C1_2(parent, this, "vsei_C1_2")
    , AXI_SLVERR_C1_2(parent, this, "AXI_SLVERR_C1_2")
    , CP15SDISABLE_C1_2(parent, this, "CP15SDISABLE_C1_2")
    , PMUIRQ_C1_2(parent, this, "PMUIRQ_C1_2")
    , SMPEN_C1_2(parent, this, "SMPEN_C1_2")
    , PPI16_C1_3(parent, this, "PPI16_C1_3")
    , PPI17_C1_3(parent, this, "PPI17_C1_3")
    , PPI18_C1_3(parent, this, "PPI18_C1_3")
    , PPI19_C1_3(parent, this, "PPI19_C1_3")
    , PPI20_C1_3(parent, this, "PPI20_C1_3")
    , PPI21_C1_3(parent, this, "PPI21_C1_3")
    , PPI22_C1_3(parent, this, "PPI22_C1_3")
    , PPI23_C1_3(parent, this, "PPI23_C1_3")
    , PPI24_C1_3(parent, this, "PPI24_C1_3")
    , PPI25_C1_3(parent, this, "PPI25_C1_3")
    , PPI26_C1_3(parent, this, "PPI26_C1_3")
    , PPI27_C1_3(parent, this, "PPI27_C1_3")
    , PPI28_C1_3(parent, this, "PPI28_C1_3")
    , PPI29_C1_3(parent, this, "PPI29_C1_3")
    , PPI30_C1_3(parent, this, "PPI30_C1_3")
    , PPI31_C1_3(parent, this, "PPI31_C1_3")
    , CNTVIRQ_C1_3(parent, this, "CNTVIRQ_C1_3")
    , CNTPSIRQ_C1_3(parent, this, "CNTPSIRQ_C1_3")
    , CNTPNSIRQ_C1_3(parent, this, "CNTPNSIRQ_C1_3")
    , CNTPHPIRQ_C1_3(parent, this, "CNTPHPIRQ_C1_3")
    , IRQOUT_C1_3(parent, this, "IRQOUT_C1_3")
    , FIQOUT_C1_3(parent, this, "FIQOUT_C1_3")
    , RVBARADDRx_C1_3(parent, this, "RVBARADDRx_C1_3")
    , AA64nAA32_C1_3(parent, this, "AA64nAA32_C1_3")
    , VINITHI_C1_3(parent, this, "VINITHI_C1_3")
    , CFGEND_C1_3(parent, this, "CFGEND_C1_3")
    , CFGTE_C1_3(parent, this, "CFGTE_C1_3")
    , reset_C1_3(parent, this, "reset_C1_3")
    , fiq_C1_3(parent, this, "fiq_C1_3")
    , irq_C1_3(parent, this, "irq_C1_3")
    , sei_C1_3(parent, this, "sei_C1_3")
    , vfiq_C1_3(parent, this, "vfiq_C1_3")
    , virq_C1_3(parent, this, "virq_C1_3")
    , vsei_C1_3(parent, this, "vsei_C1_3")
    , AXI_SLVERR_C1_3(parent, this, "AXI_SLVERR_C1_3")
    , CP15SDISABLE_C1_3(parent, this, "CP15SDISABLE_C1_3")
    , PMUIRQ_C1_3(parent, this, "PMUIRQ_C1_3")
    , SMPEN_C1_3(parent, this, "SMPEN_C1_3")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
        GICRegisters.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
        GICRegisters.dmi(on);
    }
}; /* class arm_MultiCluster */


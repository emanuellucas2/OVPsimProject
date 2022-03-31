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

class arm_Cortex_A17MPx4 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "Cortex-A17MPx4");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "Cortex-A17MPx4");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "arm.ovpworld.org", "processor", "arm", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmBusMasterPort     GICRegisters;
    tlmNetInputPort      EVENTI;
    tlmNetOutputPort     EVENTO;
    tlmNetOutputPort     CNTVIRQ_CPU0;
    tlmNetOutputPort     CNTPSIRQ_CPU0;
    tlmNetOutputPort     CNTPNSIRQ_CPU0;
    tlmNetOutputPort     CNTPHPIRQ_CPU0;
    tlmNetInputPort      CLUSTERIDAFF1;
    tlmNetInputPort      CLUSTERIDAFF2;
    tlmNetInputPort      VINITHI_CPU0;
    tlmNetInputPort      CFGEND_CPU0;
    tlmNetInputPort      TEINIT_CPU0;
    tlmNetInputPort      reset_CPU0;
    tlmNetInputPort      fiq_CPU0;
    tlmNetInputPort      irq_CPU0;
    tlmNetInputPort      sei_CPU0;
    tlmNetInputPort      vfiq_CPU0;
    tlmNetInputPort      virq_CPU0;
    tlmNetInputPort      vsei_CPU0;
    tlmNetInputPort      AXI_SLVERR_CPU0;
    tlmNetInputPort      CP15SDISABLE_CPU0;
    tlmNetOutputPort     CNTVIRQ_CPU1;
    tlmNetOutputPort     CNTPSIRQ_CPU1;
    tlmNetOutputPort     CNTPNSIRQ_CPU1;
    tlmNetOutputPort     CNTPHPIRQ_CPU1;
    tlmNetInputPort      VINITHI_CPU1;
    tlmNetInputPort      CFGEND_CPU1;
    tlmNetInputPort      TEINIT_CPU1;
    tlmNetInputPort      reset_CPU1;
    tlmNetInputPort      fiq_CPU1;
    tlmNetInputPort      irq_CPU1;
    tlmNetInputPort      sei_CPU1;
    tlmNetInputPort      vfiq_CPU1;
    tlmNetInputPort      virq_CPU1;
    tlmNetInputPort      vsei_CPU1;
    tlmNetInputPort      AXI_SLVERR_CPU1;
    tlmNetInputPort      CP15SDISABLE_CPU1;
    tlmNetOutputPort     CNTVIRQ_CPU2;
    tlmNetOutputPort     CNTPSIRQ_CPU2;
    tlmNetOutputPort     CNTPNSIRQ_CPU2;
    tlmNetOutputPort     CNTPHPIRQ_CPU2;
    tlmNetInputPort      VINITHI_CPU2;
    tlmNetInputPort      CFGEND_CPU2;
    tlmNetInputPort      TEINIT_CPU2;
    tlmNetInputPort      reset_CPU2;
    tlmNetInputPort      fiq_CPU2;
    tlmNetInputPort      irq_CPU2;
    tlmNetInputPort      sei_CPU2;
    tlmNetInputPort      vfiq_CPU2;
    tlmNetInputPort      virq_CPU2;
    tlmNetInputPort      vsei_CPU2;
    tlmNetInputPort      AXI_SLVERR_CPU2;
    tlmNetInputPort      CP15SDISABLE_CPU2;
    tlmNetOutputPort     CNTVIRQ_CPU3;
    tlmNetOutputPort     CNTPSIRQ_CPU3;
    tlmNetOutputPort     CNTPNSIRQ_CPU3;
    tlmNetOutputPort     CNTPHPIRQ_CPU3;
    tlmNetInputPort      VINITHI_CPU3;
    tlmNetInputPort      CFGEND_CPU3;
    tlmNetInputPort      TEINIT_CPU3;
    tlmNetInputPort      reset_CPU3;
    tlmNetInputPort      fiq_CPU3;
    tlmNetInputPort      irq_CPU3;
    tlmNetInputPort      sei_CPU3;
    tlmNetInputPort      vfiq_CPU3;
    tlmNetInputPort      virq_CPU3;
    tlmNetInputPort      vsei_CPU3;
    tlmNetInputPort      AXI_SLVERR_CPU3;
    tlmNetInputPort      CP15SDISABLE_CPU3;

    arm_Cortex_A17MPx4(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 40)
    , DATA (parent, this, "DATA", 40)
    , GICRegisters (parent, this, "GICRegisters", 32)
    , EVENTI(parent, this, "EVENTI")
    , EVENTO(parent, this, "EVENTO")
    , CNTVIRQ_CPU0(parent, this, "CNTVIRQ_CPU0")
    , CNTPSIRQ_CPU0(parent, this, "CNTPSIRQ_CPU0")
    , CNTPNSIRQ_CPU0(parent, this, "CNTPNSIRQ_CPU0")
    , CNTPHPIRQ_CPU0(parent, this, "CNTPHPIRQ_CPU0")
    , CLUSTERIDAFF1(parent, this, "CLUSTERIDAFF1")
    , CLUSTERIDAFF2(parent, this, "CLUSTERIDAFF2")
    , VINITHI_CPU0(parent, this, "VINITHI_CPU0")
    , CFGEND_CPU0(parent, this, "CFGEND_CPU0")
    , TEINIT_CPU0(parent, this, "TEINIT_CPU0")
    , reset_CPU0(parent, this, "reset_CPU0")
    , fiq_CPU0(parent, this, "fiq_CPU0")
    , irq_CPU0(parent, this, "irq_CPU0")
    , sei_CPU0(parent, this, "sei_CPU0")
    , vfiq_CPU0(parent, this, "vfiq_CPU0")
    , virq_CPU0(parent, this, "virq_CPU0")
    , vsei_CPU0(parent, this, "vsei_CPU0")
    , AXI_SLVERR_CPU0(parent, this, "AXI_SLVERR_CPU0")
    , CP15SDISABLE_CPU0(parent, this, "CP15SDISABLE_CPU0")
    , CNTVIRQ_CPU1(parent, this, "CNTVIRQ_CPU1")
    , CNTPSIRQ_CPU1(parent, this, "CNTPSIRQ_CPU1")
    , CNTPNSIRQ_CPU1(parent, this, "CNTPNSIRQ_CPU1")
    , CNTPHPIRQ_CPU1(parent, this, "CNTPHPIRQ_CPU1")
    , VINITHI_CPU1(parent, this, "VINITHI_CPU1")
    , CFGEND_CPU1(parent, this, "CFGEND_CPU1")
    , TEINIT_CPU1(parent, this, "TEINIT_CPU1")
    , reset_CPU1(parent, this, "reset_CPU1")
    , fiq_CPU1(parent, this, "fiq_CPU1")
    , irq_CPU1(parent, this, "irq_CPU1")
    , sei_CPU1(parent, this, "sei_CPU1")
    , vfiq_CPU1(parent, this, "vfiq_CPU1")
    , virq_CPU1(parent, this, "virq_CPU1")
    , vsei_CPU1(parent, this, "vsei_CPU1")
    , AXI_SLVERR_CPU1(parent, this, "AXI_SLVERR_CPU1")
    , CP15SDISABLE_CPU1(parent, this, "CP15SDISABLE_CPU1")
    , CNTVIRQ_CPU2(parent, this, "CNTVIRQ_CPU2")
    , CNTPSIRQ_CPU2(parent, this, "CNTPSIRQ_CPU2")
    , CNTPNSIRQ_CPU2(parent, this, "CNTPNSIRQ_CPU2")
    , CNTPHPIRQ_CPU2(parent, this, "CNTPHPIRQ_CPU2")
    , VINITHI_CPU2(parent, this, "VINITHI_CPU2")
    , CFGEND_CPU2(parent, this, "CFGEND_CPU2")
    , TEINIT_CPU2(parent, this, "TEINIT_CPU2")
    , reset_CPU2(parent, this, "reset_CPU2")
    , fiq_CPU2(parent, this, "fiq_CPU2")
    , irq_CPU2(parent, this, "irq_CPU2")
    , sei_CPU2(parent, this, "sei_CPU2")
    , vfiq_CPU2(parent, this, "vfiq_CPU2")
    , virq_CPU2(parent, this, "virq_CPU2")
    , vsei_CPU2(parent, this, "vsei_CPU2")
    , AXI_SLVERR_CPU2(parent, this, "AXI_SLVERR_CPU2")
    , CP15SDISABLE_CPU2(parent, this, "CP15SDISABLE_CPU2")
    , CNTVIRQ_CPU3(parent, this, "CNTVIRQ_CPU3")
    , CNTPSIRQ_CPU3(parent, this, "CNTPSIRQ_CPU3")
    , CNTPNSIRQ_CPU3(parent, this, "CNTPNSIRQ_CPU3")
    , CNTPHPIRQ_CPU3(parent, this, "CNTPHPIRQ_CPU3")
    , VINITHI_CPU3(parent, this, "VINITHI_CPU3")
    , CFGEND_CPU3(parent, this, "CFGEND_CPU3")
    , TEINIT_CPU3(parent, this, "TEINIT_CPU3")
    , reset_CPU3(parent, this, "reset_CPU3")
    , fiq_CPU3(parent, this, "fiq_CPU3")
    , irq_CPU3(parent, this, "irq_CPU3")
    , sei_CPU3(parent, this, "sei_CPU3")
    , vfiq_CPU3(parent, this, "vfiq_CPU3")
    , virq_CPU3(parent, this, "virq_CPU3")
    , vsei_CPU3(parent, this, "vsei_CPU3")
    , AXI_SLVERR_CPU3(parent, this, "AXI_SLVERR_CPU3")
    , CP15SDISABLE_CPU3(parent, this, "CP15SDISABLE_CPU3")
    {
    }

    arm_Cortex_A17MPx4(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=40, Uns32 DATAWidth=40, Uns32 GICRegistersWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , GICRegisters (parent, this, "GICRegisters", GICRegistersWidth)
    , EVENTI(parent, this, "EVENTI")
    , EVENTO(parent, this, "EVENTO")
    , CNTVIRQ_CPU0(parent, this, "CNTVIRQ_CPU0")
    , CNTPSIRQ_CPU0(parent, this, "CNTPSIRQ_CPU0")
    , CNTPNSIRQ_CPU0(parent, this, "CNTPNSIRQ_CPU0")
    , CNTPHPIRQ_CPU0(parent, this, "CNTPHPIRQ_CPU0")
    , CLUSTERIDAFF1(parent, this, "CLUSTERIDAFF1")
    , CLUSTERIDAFF2(parent, this, "CLUSTERIDAFF2")
    , VINITHI_CPU0(parent, this, "VINITHI_CPU0")
    , CFGEND_CPU0(parent, this, "CFGEND_CPU0")
    , TEINIT_CPU0(parent, this, "TEINIT_CPU0")
    , reset_CPU0(parent, this, "reset_CPU0")
    , fiq_CPU0(parent, this, "fiq_CPU0")
    , irq_CPU0(parent, this, "irq_CPU0")
    , sei_CPU0(parent, this, "sei_CPU0")
    , vfiq_CPU0(parent, this, "vfiq_CPU0")
    , virq_CPU0(parent, this, "virq_CPU0")
    , vsei_CPU0(parent, this, "vsei_CPU0")
    , AXI_SLVERR_CPU0(parent, this, "AXI_SLVERR_CPU0")
    , CP15SDISABLE_CPU0(parent, this, "CP15SDISABLE_CPU0")
    , CNTVIRQ_CPU1(parent, this, "CNTVIRQ_CPU1")
    , CNTPSIRQ_CPU1(parent, this, "CNTPSIRQ_CPU1")
    , CNTPNSIRQ_CPU1(parent, this, "CNTPNSIRQ_CPU1")
    , CNTPHPIRQ_CPU1(parent, this, "CNTPHPIRQ_CPU1")
    , VINITHI_CPU1(parent, this, "VINITHI_CPU1")
    , CFGEND_CPU1(parent, this, "CFGEND_CPU1")
    , TEINIT_CPU1(parent, this, "TEINIT_CPU1")
    , reset_CPU1(parent, this, "reset_CPU1")
    , fiq_CPU1(parent, this, "fiq_CPU1")
    , irq_CPU1(parent, this, "irq_CPU1")
    , sei_CPU1(parent, this, "sei_CPU1")
    , vfiq_CPU1(parent, this, "vfiq_CPU1")
    , virq_CPU1(parent, this, "virq_CPU1")
    , vsei_CPU1(parent, this, "vsei_CPU1")
    , AXI_SLVERR_CPU1(parent, this, "AXI_SLVERR_CPU1")
    , CP15SDISABLE_CPU1(parent, this, "CP15SDISABLE_CPU1")
    , CNTVIRQ_CPU2(parent, this, "CNTVIRQ_CPU2")
    , CNTPSIRQ_CPU2(parent, this, "CNTPSIRQ_CPU2")
    , CNTPNSIRQ_CPU2(parent, this, "CNTPNSIRQ_CPU2")
    , CNTPHPIRQ_CPU2(parent, this, "CNTPHPIRQ_CPU2")
    , VINITHI_CPU2(parent, this, "VINITHI_CPU2")
    , CFGEND_CPU2(parent, this, "CFGEND_CPU2")
    , TEINIT_CPU2(parent, this, "TEINIT_CPU2")
    , reset_CPU2(parent, this, "reset_CPU2")
    , fiq_CPU2(parent, this, "fiq_CPU2")
    , irq_CPU2(parent, this, "irq_CPU2")
    , sei_CPU2(parent, this, "sei_CPU2")
    , vfiq_CPU2(parent, this, "vfiq_CPU2")
    , virq_CPU2(parent, this, "virq_CPU2")
    , vsei_CPU2(parent, this, "vsei_CPU2")
    , AXI_SLVERR_CPU2(parent, this, "AXI_SLVERR_CPU2")
    , CP15SDISABLE_CPU2(parent, this, "CP15SDISABLE_CPU2")
    , CNTVIRQ_CPU3(parent, this, "CNTVIRQ_CPU3")
    , CNTPSIRQ_CPU3(parent, this, "CNTPSIRQ_CPU3")
    , CNTPNSIRQ_CPU3(parent, this, "CNTPNSIRQ_CPU3")
    , CNTPHPIRQ_CPU3(parent, this, "CNTPHPIRQ_CPU3")
    , VINITHI_CPU3(parent, this, "VINITHI_CPU3")
    , CFGEND_CPU3(parent, this, "CFGEND_CPU3")
    , TEINIT_CPU3(parent, this, "TEINIT_CPU3")
    , reset_CPU3(parent, this, "reset_CPU3")
    , fiq_CPU3(parent, this, "fiq_CPU3")
    , irq_CPU3(parent, this, "irq_CPU3")
    , sei_CPU3(parent, this, "sei_CPU3")
    , vfiq_CPU3(parent, this, "vfiq_CPU3")
    , virq_CPU3(parent, this, "virq_CPU3")
    , vsei_CPU3(parent, this, "vsei_CPU3")
    , AXI_SLVERR_CPU3(parent, this, "AXI_SLVERR_CPU3")
    , CP15SDISABLE_CPU3(parent, this, "CP15SDISABLE_CPU3")
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
}; /* class arm_Cortex_A17MPx4 */


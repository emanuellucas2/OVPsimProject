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

class riscv_S76 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "S76");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "S76");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "sifive.ovpworld.org", "processor", "riscv", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      hart0_reset;
    tlmNetInputPort      hart0_reset_addr;
    tlmNetInputPort      hart0_nmi;
    tlmNetInputPort      hart0_nmi_cause;
    tlmNetInputPort      hart0_nmi_addr;
    tlmNetInputPort      hart0_nmiexc_addr;
    tlmNetInputPort      hart0_MSWInterrupt;
    tlmNetInputPort      hart0_MTimerInterrupt;
    tlmNetInputPort      hart0_MExternalInterrupt;
    tlmNetInputPort      hart0_LocalInterrupt0;
    tlmNetInputPort      hart0_LocalInterrupt1;
    tlmNetInputPort      hart0_LocalInterrupt2;
    tlmNetInputPort      hart0_LocalInterrupt3;
    tlmNetInputPort      hart0_LocalInterrupt4;
    tlmNetInputPort      hart0_LocalInterrupt5;
    tlmNetInputPort      hart0_LocalInterrupt6;
    tlmNetInputPort      hart0_LocalInterrupt7;
    tlmNetInputPort      hart0_LocalInterrupt8;
    tlmNetInputPort      hart0_LocalInterrupt9;
    tlmNetInputPort      hart0_LocalInterrupt10;
    tlmNetInputPort      hart0_LocalInterrupt11;
    tlmNetInputPort      hart0_LocalInterrupt12;
    tlmNetInputPort      hart0_LocalInterrupt13;
    tlmNetInputPort      hart0_LocalInterrupt14;
    tlmNetInputPort      hart0_LocalInterrupt15;
    tlmNetOutputPort     hart0_irq_ack_o;
    tlmNetOutputPort     hart0_irq_id_o;
    tlmNetOutputPort     hart0_sec_lvl_o;
    tlmNetOutputPort     hart0_LR_address;
    tlmNetOutputPort     hart0_SC_address;
    tlmNetInputPort      hart0_SC_valid;
    tlmNetOutputPort     hart0_AMO_active;
    tlmNetInputPort      hart0_deferint;

    riscv_S76(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 56)
    , DATA (parent, this, "DATA", 56)
    , hart0_reset(parent, this, "hart0_reset")
    , hart0_reset_addr(parent, this, "hart0_reset_addr")
    , hart0_nmi(parent, this, "hart0_nmi")
    , hart0_nmi_cause(parent, this, "hart0_nmi_cause")
    , hart0_nmi_addr(parent, this, "hart0_nmi_addr")
    , hart0_nmiexc_addr(parent, this, "hart0_nmiexc_addr")
    , hart0_MSWInterrupt(parent, this, "hart0_MSWInterrupt")
    , hart0_MTimerInterrupt(parent, this, "hart0_MTimerInterrupt")
    , hart0_MExternalInterrupt(parent, this, "hart0_MExternalInterrupt")
    , hart0_LocalInterrupt0(parent, this, "hart0_LocalInterrupt0")
    , hart0_LocalInterrupt1(parent, this, "hart0_LocalInterrupt1")
    , hart0_LocalInterrupt2(parent, this, "hart0_LocalInterrupt2")
    , hart0_LocalInterrupt3(parent, this, "hart0_LocalInterrupt3")
    , hart0_LocalInterrupt4(parent, this, "hart0_LocalInterrupt4")
    , hart0_LocalInterrupt5(parent, this, "hart0_LocalInterrupt5")
    , hart0_LocalInterrupt6(parent, this, "hart0_LocalInterrupt6")
    , hart0_LocalInterrupt7(parent, this, "hart0_LocalInterrupt7")
    , hart0_LocalInterrupt8(parent, this, "hart0_LocalInterrupt8")
    , hart0_LocalInterrupt9(parent, this, "hart0_LocalInterrupt9")
    , hart0_LocalInterrupt10(parent, this, "hart0_LocalInterrupt10")
    , hart0_LocalInterrupt11(parent, this, "hart0_LocalInterrupt11")
    , hart0_LocalInterrupt12(parent, this, "hart0_LocalInterrupt12")
    , hart0_LocalInterrupt13(parent, this, "hart0_LocalInterrupt13")
    , hart0_LocalInterrupt14(parent, this, "hart0_LocalInterrupt14")
    , hart0_LocalInterrupt15(parent, this, "hart0_LocalInterrupt15")
    , hart0_irq_ack_o(parent, this, "hart0_irq_ack_o")
    , hart0_irq_id_o(parent, this, "hart0_irq_id_o")
    , hart0_sec_lvl_o(parent, this, "hart0_sec_lvl_o")
    , hart0_LR_address(parent, this, "hart0_LR_address")
    , hart0_SC_address(parent, this, "hart0_SC_address")
    , hart0_SC_valid(parent, this, "hart0_SC_valid")
    , hart0_AMO_active(parent, this, "hart0_AMO_active")
    , hart0_deferint(parent, this, "hart0_deferint")
    {
    }

    riscv_S76(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=56, Uns32 DATAWidth=56)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , hart0_reset(parent, this, "hart0_reset")
    , hart0_reset_addr(parent, this, "hart0_reset_addr")
    , hart0_nmi(parent, this, "hart0_nmi")
    , hart0_nmi_cause(parent, this, "hart0_nmi_cause")
    , hart0_nmi_addr(parent, this, "hart0_nmi_addr")
    , hart0_nmiexc_addr(parent, this, "hart0_nmiexc_addr")
    , hart0_MSWInterrupt(parent, this, "hart0_MSWInterrupt")
    , hart0_MTimerInterrupt(parent, this, "hart0_MTimerInterrupt")
    , hart0_MExternalInterrupt(parent, this, "hart0_MExternalInterrupt")
    , hart0_LocalInterrupt0(parent, this, "hart0_LocalInterrupt0")
    , hart0_LocalInterrupt1(parent, this, "hart0_LocalInterrupt1")
    , hart0_LocalInterrupt2(parent, this, "hart0_LocalInterrupt2")
    , hart0_LocalInterrupt3(parent, this, "hart0_LocalInterrupt3")
    , hart0_LocalInterrupt4(parent, this, "hart0_LocalInterrupt4")
    , hart0_LocalInterrupt5(parent, this, "hart0_LocalInterrupt5")
    , hart0_LocalInterrupt6(parent, this, "hart0_LocalInterrupt6")
    , hart0_LocalInterrupt7(parent, this, "hart0_LocalInterrupt7")
    , hart0_LocalInterrupt8(parent, this, "hart0_LocalInterrupt8")
    , hart0_LocalInterrupt9(parent, this, "hart0_LocalInterrupt9")
    , hart0_LocalInterrupt10(parent, this, "hart0_LocalInterrupt10")
    , hart0_LocalInterrupt11(parent, this, "hart0_LocalInterrupt11")
    , hart0_LocalInterrupt12(parent, this, "hart0_LocalInterrupt12")
    , hart0_LocalInterrupt13(parent, this, "hart0_LocalInterrupt13")
    , hart0_LocalInterrupt14(parent, this, "hart0_LocalInterrupt14")
    , hart0_LocalInterrupt15(parent, this, "hart0_LocalInterrupt15")
    , hart0_irq_ack_o(parent, this, "hart0_irq_ack_o")
    , hart0_irq_id_o(parent, this, "hart0_irq_id_o")
    , hart0_sec_lvl_o(parent, this, "hart0_sec_lvl_o")
    , hart0_LR_address(parent, this, "hart0_LR_address")
    , hart0_SC_address(parent, this, "hart0_SC_address")
    , hart0_SC_valid(parent, this, "hart0_SC_valid")
    , hart0_AMO_active(parent, this, "hart0_AMO_active")
    , hart0_deferint(parent, this, "hart0_deferint")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class riscv_S76 */


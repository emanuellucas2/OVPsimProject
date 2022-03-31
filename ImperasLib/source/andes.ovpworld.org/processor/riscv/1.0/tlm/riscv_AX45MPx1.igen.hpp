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

class riscv_AX45MPx1 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "AX45MPx1");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "AX45MPx1");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "andes.ovpworld.org", "processor", "riscv", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      hart0_reset;
    tlmNetInputPort      hart0_reset_addr;
    tlmNetInputPort      hart0_nmi;
    tlmNetInputPort      hart0_nmi_cause;
    tlmNetInputPort      hart0_nmi_addr;
    tlmNetInputPort      hart0_USWInterrupt;
    tlmNetInputPort      hart0_SSWInterrupt;
    tlmNetInputPort      hart0_MSWInterrupt;
    tlmNetInputPort      hart0_UTimerInterrupt;
    tlmNetInputPort      hart0_STimerInterrupt;
    tlmNetInputPort      hart0_MTimerInterrupt;
    tlmNetInputPort      hart0_UExternalInterrupt;
    tlmNetInputPort      hart0_UExternalInterruptID;
    tlmNetInputPort      hart0_SExternalInterrupt;
    tlmNetInputPort      hart0_SExternalInterruptID;
    tlmNetInputPort      hart0_MExternalInterrupt;
    tlmNetInputPort      hart0_MExternalInterruptID;
    tlmNetOutputPort     hart0_irq_ack_o;
    tlmNetOutputPort     hart0_irq_id_o;
    tlmNetOutputPort     hart0_sec_lvl_o;
    tlmNetOutputPort     hart0_LR_address;
    tlmNetOutputPort     hart0_SC_address;
    tlmNetInputPort      hart0_SC_valid;
    tlmNetOutputPort     hart0_AMO_active;
    tlmNetInputPort      hart0_deferint;
    tlmNetOutputPort     hart0_MExternalInterruptACK;
    tlmNetOutputPort     hart0_SExternalInterruptACK;
    tlmNetOutputPort     hart0_UExternalInterruptACK;

    riscv_AX45MPx1(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 56)
    , DATA (parent, this, "DATA", 56)
    , hart0_reset(parent, this, "hart0_reset")
    , hart0_reset_addr(parent, this, "hart0_reset_addr")
    , hart0_nmi(parent, this, "hart0_nmi")
    , hart0_nmi_cause(parent, this, "hart0_nmi_cause")
    , hart0_nmi_addr(parent, this, "hart0_nmi_addr")
    , hart0_USWInterrupt(parent, this, "hart0_USWInterrupt")
    , hart0_SSWInterrupt(parent, this, "hart0_SSWInterrupt")
    , hart0_MSWInterrupt(parent, this, "hart0_MSWInterrupt")
    , hart0_UTimerInterrupt(parent, this, "hart0_UTimerInterrupt")
    , hart0_STimerInterrupt(parent, this, "hart0_STimerInterrupt")
    , hart0_MTimerInterrupt(parent, this, "hart0_MTimerInterrupt")
    , hart0_UExternalInterrupt(parent, this, "hart0_UExternalInterrupt")
    , hart0_UExternalInterruptID(parent, this, "hart0_UExternalInterruptID")
    , hart0_SExternalInterrupt(parent, this, "hart0_SExternalInterrupt")
    , hart0_SExternalInterruptID(parent, this, "hart0_SExternalInterruptID")
    , hart0_MExternalInterrupt(parent, this, "hart0_MExternalInterrupt")
    , hart0_MExternalInterruptID(parent, this, "hart0_MExternalInterruptID")
    , hart0_irq_ack_o(parent, this, "hart0_irq_ack_o")
    , hart0_irq_id_o(parent, this, "hart0_irq_id_o")
    , hart0_sec_lvl_o(parent, this, "hart0_sec_lvl_o")
    , hart0_LR_address(parent, this, "hart0_LR_address")
    , hart0_SC_address(parent, this, "hart0_SC_address")
    , hart0_SC_valid(parent, this, "hart0_SC_valid")
    , hart0_AMO_active(parent, this, "hart0_AMO_active")
    , hart0_deferint(parent, this, "hart0_deferint")
    , hart0_MExternalInterruptACK(parent, this, "hart0_MExternalInterruptACK")
    , hart0_SExternalInterruptACK(parent, this, "hart0_SExternalInterruptACK")
    , hart0_UExternalInterruptACK(parent, this, "hart0_UExternalInterruptACK")
    {
    }

    riscv_AX45MPx1(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=56, Uns32 DATAWidth=56)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , hart0_reset(parent, this, "hart0_reset")
    , hart0_reset_addr(parent, this, "hart0_reset_addr")
    , hart0_nmi(parent, this, "hart0_nmi")
    , hart0_nmi_cause(parent, this, "hart0_nmi_cause")
    , hart0_nmi_addr(parent, this, "hart0_nmi_addr")
    , hart0_USWInterrupt(parent, this, "hart0_USWInterrupt")
    , hart0_SSWInterrupt(parent, this, "hart0_SSWInterrupt")
    , hart0_MSWInterrupt(parent, this, "hart0_MSWInterrupt")
    , hart0_UTimerInterrupt(parent, this, "hart0_UTimerInterrupt")
    , hart0_STimerInterrupt(parent, this, "hart0_STimerInterrupt")
    , hart0_MTimerInterrupt(parent, this, "hart0_MTimerInterrupt")
    , hart0_UExternalInterrupt(parent, this, "hart0_UExternalInterrupt")
    , hart0_UExternalInterruptID(parent, this, "hart0_UExternalInterruptID")
    , hart0_SExternalInterrupt(parent, this, "hart0_SExternalInterrupt")
    , hart0_SExternalInterruptID(parent, this, "hart0_SExternalInterruptID")
    , hart0_MExternalInterrupt(parent, this, "hart0_MExternalInterrupt")
    , hart0_MExternalInterruptID(parent, this, "hart0_MExternalInterruptID")
    , hart0_irq_ack_o(parent, this, "hart0_irq_ack_o")
    , hart0_irq_id_o(parent, this, "hart0_irq_id_o")
    , hart0_sec_lvl_o(parent, this, "hart0_sec_lvl_o")
    , hart0_LR_address(parent, this, "hart0_LR_address")
    , hart0_SC_address(parent, this, "hart0_SC_address")
    , hart0_SC_valid(parent, this, "hart0_SC_valid")
    , hart0_AMO_active(parent, this, "hart0_AMO_active")
    , hart0_deferint(parent, this, "hart0_deferint")
    , hart0_MExternalInterruptACK(parent, this, "hart0_MExternalInterruptACK")
    , hart0_SExternalInterruptACK(parent, this, "hart0_SExternalInterruptACK")
    , hart0_UExternalInterruptACK(parent, this, "hart0_UExternalInterruptACK")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class riscv_AX45MPx1 */


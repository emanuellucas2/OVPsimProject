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

class riscv_AX45MPx4 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "AX45MPx4");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "AX45MPx4");
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
    tlmNetInputPort      hart1_reset;
    tlmNetInputPort      hart1_reset_addr;
    tlmNetInputPort      hart1_nmi;
    tlmNetInputPort      hart1_nmi_cause;
    tlmNetInputPort      hart1_nmi_addr;
    tlmNetInputPort      hart1_USWInterrupt;
    tlmNetInputPort      hart1_SSWInterrupt;
    tlmNetInputPort      hart1_MSWInterrupt;
    tlmNetInputPort      hart1_UTimerInterrupt;
    tlmNetInputPort      hart1_STimerInterrupt;
    tlmNetInputPort      hart1_MTimerInterrupt;
    tlmNetInputPort      hart1_UExternalInterrupt;
    tlmNetInputPort      hart1_UExternalInterruptID;
    tlmNetInputPort      hart1_SExternalInterrupt;
    tlmNetInputPort      hart1_SExternalInterruptID;
    tlmNetInputPort      hart1_MExternalInterrupt;
    tlmNetInputPort      hart1_MExternalInterruptID;
    tlmNetOutputPort     hart1_irq_ack_o;
    tlmNetOutputPort     hart1_irq_id_o;
    tlmNetOutputPort     hart1_sec_lvl_o;
    tlmNetOutputPort     hart1_LR_address;
    tlmNetOutputPort     hart1_SC_address;
    tlmNetInputPort      hart1_SC_valid;
    tlmNetOutputPort     hart1_AMO_active;
    tlmNetInputPort      hart1_deferint;
    tlmNetOutputPort     hart1_MExternalInterruptACK;
    tlmNetOutputPort     hart1_SExternalInterruptACK;
    tlmNetOutputPort     hart1_UExternalInterruptACK;
    tlmNetInputPort      hart2_reset;
    tlmNetInputPort      hart2_reset_addr;
    tlmNetInputPort      hart2_nmi;
    tlmNetInputPort      hart2_nmi_cause;
    tlmNetInputPort      hart2_nmi_addr;
    tlmNetInputPort      hart2_USWInterrupt;
    tlmNetInputPort      hart2_SSWInterrupt;
    tlmNetInputPort      hart2_MSWInterrupt;
    tlmNetInputPort      hart2_UTimerInterrupt;
    tlmNetInputPort      hart2_STimerInterrupt;
    tlmNetInputPort      hart2_MTimerInterrupt;
    tlmNetInputPort      hart2_UExternalInterrupt;
    tlmNetInputPort      hart2_UExternalInterruptID;
    tlmNetInputPort      hart2_SExternalInterrupt;
    tlmNetInputPort      hart2_SExternalInterruptID;
    tlmNetInputPort      hart2_MExternalInterrupt;
    tlmNetInputPort      hart2_MExternalInterruptID;
    tlmNetOutputPort     hart2_irq_ack_o;
    tlmNetOutputPort     hart2_irq_id_o;
    tlmNetOutputPort     hart2_sec_lvl_o;
    tlmNetOutputPort     hart2_LR_address;
    tlmNetOutputPort     hart2_SC_address;
    tlmNetInputPort      hart2_SC_valid;
    tlmNetOutputPort     hart2_AMO_active;
    tlmNetInputPort      hart2_deferint;
    tlmNetOutputPort     hart2_MExternalInterruptACK;
    tlmNetOutputPort     hart2_SExternalInterruptACK;
    tlmNetOutputPort     hart2_UExternalInterruptACK;
    tlmNetInputPort      hart3_reset;
    tlmNetInputPort      hart3_reset_addr;
    tlmNetInputPort      hart3_nmi;
    tlmNetInputPort      hart3_nmi_cause;
    tlmNetInputPort      hart3_nmi_addr;
    tlmNetInputPort      hart3_USWInterrupt;
    tlmNetInputPort      hart3_SSWInterrupt;
    tlmNetInputPort      hart3_MSWInterrupt;
    tlmNetInputPort      hart3_UTimerInterrupt;
    tlmNetInputPort      hart3_STimerInterrupt;
    tlmNetInputPort      hart3_MTimerInterrupt;
    tlmNetInputPort      hart3_UExternalInterrupt;
    tlmNetInputPort      hart3_UExternalInterruptID;
    tlmNetInputPort      hart3_SExternalInterrupt;
    tlmNetInputPort      hart3_SExternalInterruptID;
    tlmNetInputPort      hart3_MExternalInterrupt;
    tlmNetInputPort      hart3_MExternalInterruptID;
    tlmNetOutputPort     hart3_irq_ack_o;
    tlmNetOutputPort     hart3_irq_id_o;
    tlmNetOutputPort     hart3_sec_lvl_o;
    tlmNetOutputPort     hart3_LR_address;
    tlmNetOutputPort     hart3_SC_address;
    tlmNetInputPort      hart3_SC_valid;
    tlmNetOutputPort     hart3_AMO_active;
    tlmNetInputPort      hart3_deferint;
    tlmNetOutputPort     hart3_MExternalInterruptACK;
    tlmNetOutputPort     hart3_SExternalInterruptACK;
    tlmNetOutputPort     hart3_UExternalInterruptACK;

    riscv_AX45MPx4(tlmModule &parent, sc_module_name name)
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
    , hart1_reset(parent, this, "hart1_reset")
    , hart1_reset_addr(parent, this, "hart1_reset_addr")
    , hart1_nmi(parent, this, "hart1_nmi")
    , hart1_nmi_cause(parent, this, "hart1_nmi_cause")
    , hart1_nmi_addr(parent, this, "hart1_nmi_addr")
    , hart1_USWInterrupt(parent, this, "hart1_USWInterrupt")
    , hart1_SSWInterrupt(parent, this, "hart1_SSWInterrupt")
    , hart1_MSWInterrupt(parent, this, "hart1_MSWInterrupt")
    , hart1_UTimerInterrupt(parent, this, "hart1_UTimerInterrupt")
    , hart1_STimerInterrupt(parent, this, "hart1_STimerInterrupt")
    , hart1_MTimerInterrupt(parent, this, "hart1_MTimerInterrupt")
    , hart1_UExternalInterrupt(parent, this, "hart1_UExternalInterrupt")
    , hart1_UExternalInterruptID(parent, this, "hart1_UExternalInterruptID")
    , hart1_SExternalInterrupt(parent, this, "hart1_SExternalInterrupt")
    , hart1_SExternalInterruptID(parent, this, "hart1_SExternalInterruptID")
    , hart1_MExternalInterrupt(parent, this, "hart1_MExternalInterrupt")
    , hart1_MExternalInterruptID(parent, this, "hart1_MExternalInterruptID")
    , hart1_irq_ack_o(parent, this, "hart1_irq_ack_o")
    , hart1_irq_id_o(parent, this, "hart1_irq_id_o")
    , hart1_sec_lvl_o(parent, this, "hart1_sec_lvl_o")
    , hart1_LR_address(parent, this, "hart1_LR_address")
    , hart1_SC_address(parent, this, "hart1_SC_address")
    , hart1_SC_valid(parent, this, "hart1_SC_valid")
    , hart1_AMO_active(parent, this, "hart1_AMO_active")
    , hart1_deferint(parent, this, "hart1_deferint")
    , hart1_MExternalInterruptACK(parent, this, "hart1_MExternalInterruptACK")
    , hart1_SExternalInterruptACK(parent, this, "hart1_SExternalInterruptACK")
    , hart1_UExternalInterruptACK(parent, this, "hart1_UExternalInterruptACK")
    , hart2_reset(parent, this, "hart2_reset")
    , hart2_reset_addr(parent, this, "hart2_reset_addr")
    , hart2_nmi(parent, this, "hart2_nmi")
    , hart2_nmi_cause(parent, this, "hart2_nmi_cause")
    , hart2_nmi_addr(parent, this, "hart2_nmi_addr")
    , hart2_USWInterrupt(parent, this, "hart2_USWInterrupt")
    , hart2_SSWInterrupt(parent, this, "hart2_SSWInterrupt")
    , hart2_MSWInterrupt(parent, this, "hart2_MSWInterrupt")
    , hart2_UTimerInterrupt(parent, this, "hart2_UTimerInterrupt")
    , hart2_STimerInterrupt(parent, this, "hart2_STimerInterrupt")
    , hart2_MTimerInterrupt(parent, this, "hart2_MTimerInterrupt")
    , hart2_UExternalInterrupt(parent, this, "hart2_UExternalInterrupt")
    , hart2_UExternalInterruptID(parent, this, "hart2_UExternalInterruptID")
    , hart2_SExternalInterrupt(parent, this, "hart2_SExternalInterrupt")
    , hart2_SExternalInterruptID(parent, this, "hart2_SExternalInterruptID")
    , hart2_MExternalInterrupt(parent, this, "hart2_MExternalInterrupt")
    , hart2_MExternalInterruptID(parent, this, "hart2_MExternalInterruptID")
    , hart2_irq_ack_o(parent, this, "hart2_irq_ack_o")
    , hart2_irq_id_o(parent, this, "hart2_irq_id_o")
    , hart2_sec_lvl_o(parent, this, "hart2_sec_lvl_o")
    , hart2_LR_address(parent, this, "hart2_LR_address")
    , hart2_SC_address(parent, this, "hart2_SC_address")
    , hart2_SC_valid(parent, this, "hart2_SC_valid")
    , hart2_AMO_active(parent, this, "hart2_AMO_active")
    , hart2_deferint(parent, this, "hart2_deferint")
    , hart2_MExternalInterruptACK(parent, this, "hart2_MExternalInterruptACK")
    , hart2_SExternalInterruptACK(parent, this, "hart2_SExternalInterruptACK")
    , hart2_UExternalInterruptACK(parent, this, "hart2_UExternalInterruptACK")
    , hart3_reset(parent, this, "hart3_reset")
    , hart3_reset_addr(parent, this, "hart3_reset_addr")
    , hart3_nmi(parent, this, "hart3_nmi")
    , hart3_nmi_cause(parent, this, "hart3_nmi_cause")
    , hart3_nmi_addr(parent, this, "hart3_nmi_addr")
    , hart3_USWInterrupt(parent, this, "hart3_USWInterrupt")
    , hart3_SSWInterrupt(parent, this, "hart3_SSWInterrupt")
    , hart3_MSWInterrupt(parent, this, "hart3_MSWInterrupt")
    , hart3_UTimerInterrupt(parent, this, "hart3_UTimerInterrupt")
    , hart3_STimerInterrupt(parent, this, "hart3_STimerInterrupt")
    , hart3_MTimerInterrupt(parent, this, "hart3_MTimerInterrupt")
    , hart3_UExternalInterrupt(parent, this, "hart3_UExternalInterrupt")
    , hart3_UExternalInterruptID(parent, this, "hart3_UExternalInterruptID")
    , hart3_SExternalInterrupt(parent, this, "hart3_SExternalInterrupt")
    , hart3_SExternalInterruptID(parent, this, "hart3_SExternalInterruptID")
    , hart3_MExternalInterrupt(parent, this, "hart3_MExternalInterrupt")
    , hart3_MExternalInterruptID(parent, this, "hart3_MExternalInterruptID")
    , hart3_irq_ack_o(parent, this, "hart3_irq_ack_o")
    , hart3_irq_id_o(parent, this, "hart3_irq_id_o")
    , hart3_sec_lvl_o(parent, this, "hart3_sec_lvl_o")
    , hart3_LR_address(parent, this, "hart3_LR_address")
    , hart3_SC_address(parent, this, "hart3_SC_address")
    , hart3_SC_valid(parent, this, "hart3_SC_valid")
    , hart3_AMO_active(parent, this, "hart3_AMO_active")
    , hart3_deferint(parent, this, "hart3_deferint")
    , hart3_MExternalInterruptACK(parent, this, "hart3_MExternalInterruptACK")
    , hart3_SExternalInterruptACK(parent, this, "hart3_SExternalInterruptACK")
    , hart3_UExternalInterruptACK(parent, this, "hart3_UExternalInterruptACK")
    {
    }

    riscv_AX45MPx4(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=56, Uns32 DATAWidth=56)
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
    , hart1_reset(parent, this, "hart1_reset")
    , hart1_reset_addr(parent, this, "hart1_reset_addr")
    , hart1_nmi(parent, this, "hart1_nmi")
    , hart1_nmi_cause(parent, this, "hart1_nmi_cause")
    , hart1_nmi_addr(parent, this, "hart1_nmi_addr")
    , hart1_USWInterrupt(parent, this, "hart1_USWInterrupt")
    , hart1_SSWInterrupt(parent, this, "hart1_SSWInterrupt")
    , hart1_MSWInterrupt(parent, this, "hart1_MSWInterrupt")
    , hart1_UTimerInterrupt(parent, this, "hart1_UTimerInterrupt")
    , hart1_STimerInterrupt(parent, this, "hart1_STimerInterrupt")
    , hart1_MTimerInterrupt(parent, this, "hart1_MTimerInterrupt")
    , hart1_UExternalInterrupt(parent, this, "hart1_UExternalInterrupt")
    , hart1_UExternalInterruptID(parent, this, "hart1_UExternalInterruptID")
    , hart1_SExternalInterrupt(parent, this, "hart1_SExternalInterrupt")
    , hart1_SExternalInterruptID(parent, this, "hart1_SExternalInterruptID")
    , hart1_MExternalInterrupt(parent, this, "hart1_MExternalInterrupt")
    , hart1_MExternalInterruptID(parent, this, "hart1_MExternalInterruptID")
    , hart1_irq_ack_o(parent, this, "hart1_irq_ack_o")
    , hart1_irq_id_o(parent, this, "hart1_irq_id_o")
    , hart1_sec_lvl_o(parent, this, "hart1_sec_lvl_o")
    , hart1_LR_address(parent, this, "hart1_LR_address")
    , hart1_SC_address(parent, this, "hart1_SC_address")
    , hart1_SC_valid(parent, this, "hart1_SC_valid")
    , hart1_AMO_active(parent, this, "hart1_AMO_active")
    , hart1_deferint(parent, this, "hart1_deferint")
    , hart1_MExternalInterruptACK(parent, this, "hart1_MExternalInterruptACK")
    , hart1_SExternalInterruptACK(parent, this, "hart1_SExternalInterruptACK")
    , hart1_UExternalInterruptACK(parent, this, "hart1_UExternalInterruptACK")
    , hart2_reset(parent, this, "hart2_reset")
    , hart2_reset_addr(parent, this, "hart2_reset_addr")
    , hart2_nmi(parent, this, "hart2_nmi")
    , hart2_nmi_cause(parent, this, "hart2_nmi_cause")
    , hart2_nmi_addr(parent, this, "hart2_nmi_addr")
    , hart2_USWInterrupt(parent, this, "hart2_USWInterrupt")
    , hart2_SSWInterrupt(parent, this, "hart2_SSWInterrupt")
    , hart2_MSWInterrupt(parent, this, "hart2_MSWInterrupt")
    , hart2_UTimerInterrupt(parent, this, "hart2_UTimerInterrupt")
    , hart2_STimerInterrupt(parent, this, "hart2_STimerInterrupt")
    , hart2_MTimerInterrupt(parent, this, "hart2_MTimerInterrupt")
    , hart2_UExternalInterrupt(parent, this, "hart2_UExternalInterrupt")
    , hart2_UExternalInterruptID(parent, this, "hart2_UExternalInterruptID")
    , hart2_SExternalInterrupt(parent, this, "hart2_SExternalInterrupt")
    , hart2_SExternalInterruptID(parent, this, "hart2_SExternalInterruptID")
    , hart2_MExternalInterrupt(parent, this, "hart2_MExternalInterrupt")
    , hart2_MExternalInterruptID(parent, this, "hart2_MExternalInterruptID")
    , hart2_irq_ack_o(parent, this, "hart2_irq_ack_o")
    , hart2_irq_id_o(parent, this, "hart2_irq_id_o")
    , hart2_sec_lvl_o(parent, this, "hart2_sec_lvl_o")
    , hart2_LR_address(parent, this, "hart2_LR_address")
    , hart2_SC_address(parent, this, "hart2_SC_address")
    , hart2_SC_valid(parent, this, "hart2_SC_valid")
    , hart2_AMO_active(parent, this, "hart2_AMO_active")
    , hart2_deferint(parent, this, "hart2_deferint")
    , hart2_MExternalInterruptACK(parent, this, "hart2_MExternalInterruptACK")
    , hart2_SExternalInterruptACK(parent, this, "hart2_SExternalInterruptACK")
    , hart2_UExternalInterruptACK(parent, this, "hart2_UExternalInterruptACK")
    , hart3_reset(parent, this, "hart3_reset")
    , hart3_reset_addr(parent, this, "hart3_reset_addr")
    , hart3_nmi(parent, this, "hart3_nmi")
    , hart3_nmi_cause(parent, this, "hart3_nmi_cause")
    , hart3_nmi_addr(parent, this, "hart3_nmi_addr")
    , hart3_USWInterrupt(parent, this, "hart3_USWInterrupt")
    , hart3_SSWInterrupt(parent, this, "hart3_SSWInterrupt")
    , hart3_MSWInterrupt(parent, this, "hart3_MSWInterrupt")
    , hart3_UTimerInterrupt(parent, this, "hart3_UTimerInterrupt")
    , hart3_STimerInterrupt(parent, this, "hart3_STimerInterrupt")
    , hart3_MTimerInterrupt(parent, this, "hart3_MTimerInterrupt")
    , hart3_UExternalInterrupt(parent, this, "hart3_UExternalInterrupt")
    , hart3_UExternalInterruptID(parent, this, "hart3_UExternalInterruptID")
    , hart3_SExternalInterrupt(parent, this, "hart3_SExternalInterrupt")
    , hart3_SExternalInterruptID(parent, this, "hart3_SExternalInterruptID")
    , hart3_MExternalInterrupt(parent, this, "hart3_MExternalInterrupt")
    , hart3_MExternalInterruptID(parent, this, "hart3_MExternalInterruptID")
    , hart3_irq_ack_o(parent, this, "hart3_irq_ack_o")
    , hart3_irq_id_o(parent, this, "hart3_irq_id_o")
    , hart3_sec_lvl_o(parent, this, "hart3_sec_lvl_o")
    , hart3_LR_address(parent, this, "hart3_LR_address")
    , hart3_SC_address(parent, this, "hart3_SC_address")
    , hart3_SC_valid(parent, this, "hart3_SC_valid")
    , hart3_AMO_active(parent, this, "hart3_AMO_active")
    , hart3_deferint(parent, this, "hart3_deferint")
    , hart3_MExternalInterruptACK(parent, this, "hart3_MExternalInterruptACK")
    , hart3_SExternalInterruptACK(parent, this, "hart3_SExternalInterruptACK")
    , hart3_UExternalInterruptACK(parent, this, "hart3_UExternalInterruptACK")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class riscv_AX45MPx4 */


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

class riscv_RV64X : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "RV64X");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "RV64X");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "vendor.com", "processor", "riscv", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      reset;
    tlmNetInputPort      reset_addr;
    tlmNetInputPort      nmi;
    tlmNetInputPort      nmi_cause;
    tlmNetInputPort      nmi_addr;
    tlmNetInputPort      MSWInterrupt;
    tlmNetInputPort      MTimerInterrupt;
    tlmNetInputPort      MExternalInterrupt;
    tlmNetInputPort      LocalInterrupt5;
    tlmNetInputPort      LocalInterrupt6;
    tlmNetOutputPort     irq_ack_o;
    tlmNetOutputPort     irq_id_o;
    tlmNetOutputPort     sec_lvl_o;
    tlmNetOutputPort     LR_address;
    tlmNetOutputPort     SC_address;
    tlmNetInputPort      SC_valid;
    tlmNetOutputPort     AMO_active;
    tlmNetInputPort      deferint;

    riscv_RV64X(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 56)
    , DATA (parent, this, "DATA", 56)
    , reset(parent, this, "reset")
    , reset_addr(parent, this, "reset_addr")
    , nmi(parent, this, "nmi")
    , nmi_cause(parent, this, "nmi_cause")
    , nmi_addr(parent, this, "nmi_addr")
    , MSWInterrupt(parent, this, "MSWInterrupt")
    , MTimerInterrupt(parent, this, "MTimerInterrupt")
    , MExternalInterrupt(parent, this, "MExternalInterrupt")
    , LocalInterrupt5(parent, this, "LocalInterrupt5")
    , LocalInterrupt6(parent, this, "LocalInterrupt6")
    , irq_ack_o(parent, this, "irq_ack_o")
    , irq_id_o(parent, this, "irq_id_o")
    , sec_lvl_o(parent, this, "sec_lvl_o")
    , LR_address(parent, this, "LR_address")
    , SC_address(parent, this, "SC_address")
    , SC_valid(parent, this, "SC_valid")
    , AMO_active(parent, this, "AMO_active")
    , deferint(parent, this, "deferint")
    {
    }

    riscv_RV64X(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=56, Uns32 DATAWidth=56)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , reset(parent, this, "reset")
    , reset_addr(parent, this, "reset_addr")
    , nmi(parent, this, "nmi")
    , nmi_cause(parent, this, "nmi_cause")
    , nmi_addr(parent, this, "nmi_addr")
    , MSWInterrupt(parent, this, "MSWInterrupt")
    , MTimerInterrupt(parent, this, "MTimerInterrupt")
    , MExternalInterrupt(parent, this, "MExternalInterrupt")
    , LocalInterrupt5(parent, this, "LocalInterrupt5")
    , LocalInterrupt6(parent, this, "LocalInterrupt6")
    , irq_ack_o(parent, this, "irq_ack_o")
    , irq_id_o(parent, this, "irq_id_o")
    , sec_lvl_o(parent, this, "sec_lvl_o")
    , LR_address(parent, this, "LR_address")
    , SC_address(parent, this, "SC_address")
    , SC_valid(parent, this, "SC_valid")
    , AMO_active(parent, this, "AMO_active")
    , deferint(parent, this, "deferint")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class riscv_RV64X */


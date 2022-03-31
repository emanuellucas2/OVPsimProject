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

class riscv_CV32E40P : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "CV32E40P");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "CV32E40P");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "openhwgroup.ovpworld.org", "processor", "riscv", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
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
    tlmNetInputPort      LocalInterrupt0;
    tlmNetInputPort      LocalInterrupt1;
    tlmNetInputPort      LocalInterrupt2;
    tlmNetInputPort      LocalInterrupt3;
    tlmNetInputPort      LocalInterrupt4;
    tlmNetInputPort      LocalInterrupt5;
    tlmNetInputPort      LocalInterrupt6;
    tlmNetInputPort      LocalInterrupt7;
    tlmNetInputPort      LocalInterrupt8;
    tlmNetInputPort      LocalInterrupt9;
    tlmNetInputPort      LocalInterrupt10;
    tlmNetInputPort      LocalInterrupt11;
    tlmNetInputPort      LocalInterrupt12;
    tlmNetInputPort      LocalInterrupt13;
    tlmNetInputPort      LocalInterrupt14;
    tlmNetInputPort      LocalInterrupt15;
    tlmNetOutputPort     irq_ack_o;
    tlmNetOutputPort     irq_id_o;
    tlmNetOutputPort     sec_lvl_o;
    tlmNetOutputPort     DM;
    tlmNetInputPort      haltreq;
    tlmNetInputPort      resethaltreq;
    tlmNetInputPort      deferint;
    tlmNetInputPort      IllegalInstruction;

    riscv_CV32E40P(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 34)
    , DATA (parent, this, "DATA", 34)
    , reset(parent, this, "reset")
    , reset_addr(parent, this, "reset_addr")
    , nmi(parent, this, "nmi")
    , nmi_cause(parent, this, "nmi_cause")
    , nmi_addr(parent, this, "nmi_addr")
    , MSWInterrupt(parent, this, "MSWInterrupt")
    , MTimerInterrupt(parent, this, "MTimerInterrupt")
    , MExternalInterrupt(parent, this, "MExternalInterrupt")
    , LocalInterrupt0(parent, this, "LocalInterrupt0")
    , LocalInterrupt1(parent, this, "LocalInterrupt1")
    , LocalInterrupt2(parent, this, "LocalInterrupt2")
    , LocalInterrupt3(parent, this, "LocalInterrupt3")
    , LocalInterrupt4(parent, this, "LocalInterrupt4")
    , LocalInterrupt5(parent, this, "LocalInterrupt5")
    , LocalInterrupt6(parent, this, "LocalInterrupt6")
    , LocalInterrupt7(parent, this, "LocalInterrupt7")
    , LocalInterrupt8(parent, this, "LocalInterrupt8")
    , LocalInterrupt9(parent, this, "LocalInterrupt9")
    , LocalInterrupt10(parent, this, "LocalInterrupt10")
    , LocalInterrupt11(parent, this, "LocalInterrupt11")
    , LocalInterrupt12(parent, this, "LocalInterrupt12")
    , LocalInterrupt13(parent, this, "LocalInterrupt13")
    , LocalInterrupt14(parent, this, "LocalInterrupt14")
    , LocalInterrupt15(parent, this, "LocalInterrupt15")
    , irq_ack_o(parent, this, "irq_ack_o")
    , irq_id_o(parent, this, "irq_id_o")
    , sec_lvl_o(parent, this, "sec_lvl_o")
    , DM(parent, this, "DM")
    , haltreq(parent, this, "haltreq")
    , resethaltreq(parent, this, "resethaltreq")
    , deferint(parent, this, "deferint")
    , IllegalInstruction(parent, this, "IllegalInstruction")
    {
    }

    riscv_CV32E40P(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=34, Uns32 DATAWidth=34)
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
    , LocalInterrupt0(parent, this, "LocalInterrupt0")
    , LocalInterrupt1(parent, this, "LocalInterrupt1")
    , LocalInterrupt2(parent, this, "LocalInterrupt2")
    , LocalInterrupt3(parent, this, "LocalInterrupt3")
    , LocalInterrupt4(parent, this, "LocalInterrupt4")
    , LocalInterrupt5(parent, this, "LocalInterrupt5")
    , LocalInterrupt6(parent, this, "LocalInterrupt6")
    , LocalInterrupt7(parent, this, "LocalInterrupt7")
    , LocalInterrupt8(parent, this, "LocalInterrupt8")
    , LocalInterrupt9(parent, this, "LocalInterrupt9")
    , LocalInterrupt10(parent, this, "LocalInterrupt10")
    , LocalInterrupt11(parent, this, "LocalInterrupt11")
    , LocalInterrupt12(parent, this, "LocalInterrupt12")
    , LocalInterrupt13(parent, this, "LocalInterrupt13")
    , LocalInterrupt14(parent, this, "LocalInterrupt14")
    , LocalInterrupt15(parent, this, "LocalInterrupt15")
    , irq_ack_o(parent, this, "irq_ack_o")
    , irq_id_o(parent, this, "irq_id_o")
    , sec_lvl_o(parent, this, "sec_lvl_o")
    , DM(parent, this, "DM")
    , haltreq(parent, this, "haltreq")
    , resethaltreq(parent, this, "resethaltreq")
    , deferint(parent, this, "deferint")
    , IllegalInstruction(parent, this, "IllegalInstruction")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class riscv_CV32E40P */


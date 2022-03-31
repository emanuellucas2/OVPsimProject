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

class riscv_U74 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "U74");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "U74");
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
    tlmNetInputPort      hart0_SSWInterrupt;
    tlmNetInputPort      hart0_MSWInterrupt;
    tlmNetInputPort      hart0_STimerInterrupt;
    tlmNetInputPort      hart0_MTimerInterrupt;
    tlmNetInputPort      hart0_SExternalInterrupt;
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
    tlmNetInputPort      hart0_LocalInterrupt16;
    tlmNetInputPort      hart0_LocalInterrupt17;
    tlmNetInputPort      hart0_LocalInterrupt18;
    tlmNetInputPort      hart0_LocalInterrupt19;
    tlmNetInputPort      hart0_LocalInterrupt20;
    tlmNetInputPort      hart0_LocalInterrupt21;
    tlmNetInputPort      hart0_LocalInterrupt22;
    tlmNetInputPort      hart0_LocalInterrupt23;
    tlmNetInputPort      hart0_LocalInterrupt24;
    tlmNetInputPort      hart0_LocalInterrupt25;
    tlmNetInputPort      hart0_LocalInterrupt26;
    tlmNetInputPort      hart0_LocalInterrupt27;
    tlmNetInputPort      hart0_LocalInterrupt28;
    tlmNetInputPort      hart0_LocalInterrupt29;
    tlmNetInputPort      hart0_LocalInterrupt30;
    tlmNetInputPort      hart0_LocalInterrupt31;
    tlmNetInputPort      hart0_LocalInterrupt32;
    tlmNetInputPort      hart0_LocalInterrupt33;
    tlmNetInputPort      hart0_LocalInterrupt34;
    tlmNetInputPort      hart0_LocalInterrupt35;
    tlmNetInputPort      hart0_LocalInterrupt36;
    tlmNetInputPort      hart0_LocalInterrupt37;
    tlmNetInputPort      hart0_LocalInterrupt38;
    tlmNetInputPort      hart0_LocalInterrupt39;
    tlmNetInputPort      hart0_LocalInterrupt40;
    tlmNetInputPort      hart0_LocalInterrupt41;
    tlmNetInputPort      hart0_LocalInterrupt42;
    tlmNetInputPort      hart0_LocalInterrupt43;
    tlmNetInputPort      hart0_LocalInterrupt44;
    tlmNetInputPort      hart0_LocalInterrupt45;
    tlmNetInputPort      hart0_LocalInterrupt46;
    tlmNetInputPort      hart0_LocalInterrupt47;
    tlmNetOutputPort     hart0_irq_ack_o;
    tlmNetOutputPort     hart0_irq_id_o;
    tlmNetOutputPort     hart0_sec_lvl_o;
    tlmNetOutputPort     hart0_LR_address;
    tlmNetOutputPort     hart0_SC_address;
    tlmNetInputPort      hart0_SC_valid;
    tlmNetOutputPort     hart0_AMO_active;
    tlmNetInputPort      hart0_deferint;

    riscv_U74(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 56)
    , DATA (parent, this, "DATA", 56)
    , hart0_reset(parent, this, "hart0_reset")
    , hart0_reset_addr(parent, this, "hart0_reset_addr")
    , hart0_nmi(parent, this, "hart0_nmi")
    , hart0_nmi_cause(parent, this, "hart0_nmi_cause")
    , hart0_nmi_addr(parent, this, "hart0_nmi_addr")
    , hart0_nmiexc_addr(parent, this, "hart0_nmiexc_addr")
    , hart0_SSWInterrupt(parent, this, "hart0_SSWInterrupt")
    , hart0_MSWInterrupt(parent, this, "hart0_MSWInterrupt")
    , hart0_STimerInterrupt(parent, this, "hart0_STimerInterrupt")
    , hart0_MTimerInterrupt(parent, this, "hart0_MTimerInterrupt")
    , hart0_SExternalInterrupt(parent, this, "hart0_SExternalInterrupt")
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
    , hart0_LocalInterrupt16(parent, this, "hart0_LocalInterrupt16")
    , hart0_LocalInterrupt17(parent, this, "hart0_LocalInterrupt17")
    , hart0_LocalInterrupt18(parent, this, "hart0_LocalInterrupt18")
    , hart0_LocalInterrupt19(parent, this, "hart0_LocalInterrupt19")
    , hart0_LocalInterrupt20(parent, this, "hart0_LocalInterrupt20")
    , hart0_LocalInterrupt21(parent, this, "hart0_LocalInterrupt21")
    , hart0_LocalInterrupt22(parent, this, "hart0_LocalInterrupt22")
    , hart0_LocalInterrupt23(parent, this, "hart0_LocalInterrupt23")
    , hart0_LocalInterrupt24(parent, this, "hart0_LocalInterrupt24")
    , hart0_LocalInterrupt25(parent, this, "hart0_LocalInterrupt25")
    , hart0_LocalInterrupt26(parent, this, "hart0_LocalInterrupt26")
    , hart0_LocalInterrupt27(parent, this, "hart0_LocalInterrupt27")
    , hart0_LocalInterrupt28(parent, this, "hart0_LocalInterrupt28")
    , hart0_LocalInterrupt29(parent, this, "hart0_LocalInterrupt29")
    , hart0_LocalInterrupt30(parent, this, "hart0_LocalInterrupt30")
    , hart0_LocalInterrupt31(parent, this, "hart0_LocalInterrupt31")
    , hart0_LocalInterrupt32(parent, this, "hart0_LocalInterrupt32")
    , hart0_LocalInterrupt33(parent, this, "hart0_LocalInterrupt33")
    , hart0_LocalInterrupt34(parent, this, "hart0_LocalInterrupt34")
    , hart0_LocalInterrupt35(parent, this, "hart0_LocalInterrupt35")
    , hart0_LocalInterrupt36(parent, this, "hart0_LocalInterrupt36")
    , hart0_LocalInterrupt37(parent, this, "hart0_LocalInterrupt37")
    , hart0_LocalInterrupt38(parent, this, "hart0_LocalInterrupt38")
    , hart0_LocalInterrupt39(parent, this, "hart0_LocalInterrupt39")
    , hart0_LocalInterrupt40(parent, this, "hart0_LocalInterrupt40")
    , hart0_LocalInterrupt41(parent, this, "hart0_LocalInterrupt41")
    , hart0_LocalInterrupt42(parent, this, "hart0_LocalInterrupt42")
    , hart0_LocalInterrupt43(parent, this, "hart0_LocalInterrupt43")
    , hart0_LocalInterrupt44(parent, this, "hart0_LocalInterrupt44")
    , hart0_LocalInterrupt45(parent, this, "hart0_LocalInterrupt45")
    , hart0_LocalInterrupt46(parent, this, "hart0_LocalInterrupt46")
    , hart0_LocalInterrupt47(parent, this, "hart0_LocalInterrupt47")
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

    riscv_U74(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=56, Uns32 DATAWidth=56)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , hart0_reset(parent, this, "hart0_reset")
    , hart0_reset_addr(parent, this, "hart0_reset_addr")
    , hart0_nmi(parent, this, "hart0_nmi")
    , hart0_nmi_cause(parent, this, "hart0_nmi_cause")
    , hart0_nmi_addr(parent, this, "hart0_nmi_addr")
    , hart0_nmiexc_addr(parent, this, "hart0_nmiexc_addr")
    , hart0_SSWInterrupt(parent, this, "hart0_SSWInterrupt")
    , hart0_MSWInterrupt(parent, this, "hart0_MSWInterrupt")
    , hart0_STimerInterrupt(parent, this, "hart0_STimerInterrupt")
    , hart0_MTimerInterrupt(parent, this, "hart0_MTimerInterrupt")
    , hart0_SExternalInterrupt(parent, this, "hart0_SExternalInterrupt")
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
    , hart0_LocalInterrupt16(parent, this, "hart0_LocalInterrupt16")
    , hart0_LocalInterrupt17(parent, this, "hart0_LocalInterrupt17")
    , hart0_LocalInterrupt18(parent, this, "hart0_LocalInterrupt18")
    , hart0_LocalInterrupt19(parent, this, "hart0_LocalInterrupt19")
    , hart0_LocalInterrupt20(parent, this, "hart0_LocalInterrupt20")
    , hart0_LocalInterrupt21(parent, this, "hart0_LocalInterrupt21")
    , hart0_LocalInterrupt22(parent, this, "hart0_LocalInterrupt22")
    , hart0_LocalInterrupt23(parent, this, "hart0_LocalInterrupt23")
    , hart0_LocalInterrupt24(parent, this, "hart0_LocalInterrupt24")
    , hart0_LocalInterrupt25(parent, this, "hart0_LocalInterrupt25")
    , hart0_LocalInterrupt26(parent, this, "hart0_LocalInterrupt26")
    , hart0_LocalInterrupt27(parent, this, "hart0_LocalInterrupt27")
    , hart0_LocalInterrupt28(parent, this, "hart0_LocalInterrupt28")
    , hart0_LocalInterrupt29(parent, this, "hart0_LocalInterrupt29")
    , hart0_LocalInterrupt30(parent, this, "hart0_LocalInterrupt30")
    , hart0_LocalInterrupt31(parent, this, "hart0_LocalInterrupt31")
    , hart0_LocalInterrupt32(parent, this, "hart0_LocalInterrupt32")
    , hart0_LocalInterrupt33(parent, this, "hart0_LocalInterrupt33")
    , hart0_LocalInterrupt34(parent, this, "hart0_LocalInterrupt34")
    , hart0_LocalInterrupt35(parent, this, "hart0_LocalInterrupt35")
    , hart0_LocalInterrupt36(parent, this, "hart0_LocalInterrupt36")
    , hart0_LocalInterrupt37(parent, this, "hart0_LocalInterrupt37")
    , hart0_LocalInterrupt38(parent, this, "hart0_LocalInterrupt38")
    , hart0_LocalInterrupt39(parent, this, "hart0_LocalInterrupt39")
    , hart0_LocalInterrupt40(parent, this, "hart0_LocalInterrupt40")
    , hart0_LocalInterrupt41(parent, this, "hart0_LocalInterrupt41")
    , hart0_LocalInterrupt42(parent, this, "hart0_LocalInterrupt42")
    , hart0_LocalInterrupt43(parent, this, "hart0_LocalInterrupt43")
    , hart0_LocalInterrupt44(parent, this, "hart0_LocalInterrupt44")
    , hart0_LocalInterrupt45(parent, this, "hart0_LocalInterrupt45")
    , hart0_LocalInterrupt46(parent, this, "hart0_LocalInterrupt46")
    , hart0_LocalInterrupt47(parent, this, "hart0_LocalInterrupt47")
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
}; /* class riscv_U74 */


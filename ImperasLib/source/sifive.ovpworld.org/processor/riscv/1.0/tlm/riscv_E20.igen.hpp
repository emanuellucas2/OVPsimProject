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

class riscv_E20 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "E20");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "E20");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "sifive.ovpworld.org", "processor", "riscv", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
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
    tlmNetInputPort      CSIP;
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
    tlmNetInputPort      LocalInterrupt16;
    tlmNetInputPort      LocalInterrupt17;
    tlmNetInputPort      LocalInterrupt18;
    tlmNetInputPort      LocalInterrupt19;
    tlmNetInputPort      LocalInterrupt20;
    tlmNetInputPort      LocalInterrupt21;
    tlmNetInputPort      LocalInterrupt22;
    tlmNetInputPort      LocalInterrupt23;
    tlmNetInputPort      LocalInterrupt24;
    tlmNetInputPort      LocalInterrupt25;
    tlmNetInputPort      LocalInterrupt26;
    tlmNetInputPort      LocalInterrupt27;
    tlmNetInputPort      LocalInterrupt28;
    tlmNetInputPort      LocalInterrupt29;
    tlmNetInputPort      LocalInterrupt30;
    tlmNetInputPort      LocalInterrupt31;
    tlmNetOutputPort     irq_ack_o;
    tlmNetOutputPort     irq_id_o;
    tlmNetOutputPort     sec_lvl_o;
    tlmNetInputPort      deferint;

    riscv_E20(tlmModule &parent, sc_module_name name)
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
    , CSIP(parent, this, "CSIP")
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
    , LocalInterrupt16(parent, this, "LocalInterrupt16")
    , LocalInterrupt17(parent, this, "LocalInterrupt17")
    , LocalInterrupt18(parent, this, "LocalInterrupt18")
    , LocalInterrupt19(parent, this, "LocalInterrupt19")
    , LocalInterrupt20(parent, this, "LocalInterrupt20")
    , LocalInterrupt21(parent, this, "LocalInterrupt21")
    , LocalInterrupt22(parent, this, "LocalInterrupt22")
    , LocalInterrupt23(parent, this, "LocalInterrupt23")
    , LocalInterrupt24(parent, this, "LocalInterrupt24")
    , LocalInterrupt25(parent, this, "LocalInterrupt25")
    , LocalInterrupt26(parent, this, "LocalInterrupt26")
    , LocalInterrupt27(parent, this, "LocalInterrupt27")
    , LocalInterrupt28(parent, this, "LocalInterrupt28")
    , LocalInterrupt29(parent, this, "LocalInterrupt29")
    , LocalInterrupt30(parent, this, "LocalInterrupt30")
    , LocalInterrupt31(parent, this, "LocalInterrupt31")
    , irq_ack_o(parent, this, "irq_ack_o")
    , irq_id_o(parent, this, "irq_id_o")
    , sec_lvl_o(parent, this, "sec_lvl_o")
    , deferint(parent, this, "deferint")
    {
    }

    riscv_E20(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=34, Uns32 DATAWidth=34)
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
    , CSIP(parent, this, "CSIP")
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
    , LocalInterrupt16(parent, this, "LocalInterrupt16")
    , LocalInterrupt17(parent, this, "LocalInterrupt17")
    , LocalInterrupt18(parent, this, "LocalInterrupt18")
    , LocalInterrupt19(parent, this, "LocalInterrupt19")
    , LocalInterrupt20(parent, this, "LocalInterrupt20")
    , LocalInterrupt21(parent, this, "LocalInterrupt21")
    , LocalInterrupt22(parent, this, "LocalInterrupt22")
    , LocalInterrupt23(parent, this, "LocalInterrupt23")
    , LocalInterrupt24(parent, this, "LocalInterrupt24")
    , LocalInterrupt25(parent, this, "LocalInterrupt25")
    , LocalInterrupt26(parent, this, "LocalInterrupt26")
    , LocalInterrupt27(parent, this, "LocalInterrupt27")
    , LocalInterrupt28(parent, this, "LocalInterrupt28")
    , LocalInterrupt29(parent, this, "LocalInterrupt29")
    , LocalInterrupt30(parent, this, "LocalInterrupt30")
    , LocalInterrupt31(parent, this, "LocalInterrupt31")
    , irq_ack_o(parent, this, "irq_ack_o")
    , irq_id_o(parent, this, "irq_id_o")
    , sec_lvl_o(parent, this, "sec_lvl_o")
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
}; /* class riscv_E20 */


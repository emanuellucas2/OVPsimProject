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

class nios_ii_Nios_II_E : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "Nios_II_E");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "Nios_II_E");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "altera.ovpworld.org", "processor", "nios_ii", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      reset_n;
    tlmNetInputPort      d_irq0;
    tlmNetInputPort      d_irq1;
    tlmNetInputPort      d_irq2;
    tlmNetInputPort      d_irq3;
    tlmNetInputPort      d_irq4;
    tlmNetInputPort      d_irq5;
    tlmNetInputPort      d_irq6;
    tlmNetInputPort      d_irq7;
    tlmNetInputPort      d_irq8;
    tlmNetInputPort      d_irq9;
    tlmNetInputPort      d_irq10;
    tlmNetInputPort      d_irq11;
    tlmNetInputPort      d_irq12;
    tlmNetInputPort      d_irq13;
    tlmNetInputPort      d_irq14;
    tlmNetInputPort      d_irq15;
    tlmNetInputPort      d_irq16;
    tlmNetInputPort      d_irq17;
    tlmNetInputPort      d_irq18;
    tlmNetInputPort      d_irq19;
    tlmNetInputPort      d_irq20;
    tlmNetInputPort      d_irq21;
    tlmNetInputPort      d_irq22;
    tlmNetInputPort      d_irq23;
    tlmNetInputPort      d_irq24;
    tlmNetInputPort      d_irq25;
    tlmNetInputPort      d_irq26;
    tlmNetInputPort      d_irq27;
    tlmNetInputPort      d_irq28;
    tlmNetInputPort      d_irq29;
    tlmNetInputPort      d_irq30;
    tlmNetInputPort      d_irq31;

    nios_ii_Nios_II_E(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 32)
    , DATA (parent, this, "DATA", 32)
    , reset_n(parent, this, "reset_n")
    , d_irq0(parent, this, "d_irq0")
    , d_irq1(parent, this, "d_irq1")
    , d_irq2(parent, this, "d_irq2")
    , d_irq3(parent, this, "d_irq3")
    , d_irq4(parent, this, "d_irq4")
    , d_irq5(parent, this, "d_irq5")
    , d_irq6(parent, this, "d_irq6")
    , d_irq7(parent, this, "d_irq7")
    , d_irq8(parent, this, "d_irq8")
    , d_irq9(parent, this, "d_irq9")
    , d_irq10(parent, this, "d_irq10")
    , d_irq11(parent, this, "d_irq11")
    , d_irq12(parent, this, "d_irq12")
    , d_irq13(parent, this, "d_irq13")
    , d_irq14(parent, this, "d_irq14")
    , d_irq15(parent, this, "d_irq15")
    , d_irq16(parent, this, "d_irq16")
    , d_irq17(parent, this, "d_irq17")
    , d_irq18(parent, this, "d_irq18")
    , d_irq19(parent, this, "d_irq19")
    , d_irq20(parent, this, "d_irq20")
    , d_irq21(parent, this, "d_irq21")
    , d_irq22(parent, this, "d_irq22")
    , d_irq23(parent, this, "d_irq23")
    , d_irq24(parent, this, "d_irq24")
    , d_irq25(parent, this, "d_irq25")
    , d_irq26(parent, this, "d_irq26")
    , d_irq27(parent, this, "d_irq27")
    , d_irq28(parent, this, "d_irq28")
    , d_irq29(parent, this, "d_irq29")
    , d_irq30(parent, this, "d_irq30")
    , d_irq31(parent, this, "d_irq31")
    {
    }

    nios_ii_Nios_II_E(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , reset_n(parent, this, "reset_n")
    , d_irq0(parent, this, "d_irq0")
    , d_irq1(parent, this, "d_irq1")
    , d_irq2(parent, this, "d_irq2")
    , d_irq3(parent, this, "d_irq3")
    , d_irq4(parent, this, "d_irq4")
    , d_irq5(parent, this, "d_irq5")
    , d_irq6(parent, this, "d_irq6")
    , d_irq7(parent, this, "d_irq7")
    , d_irq8(parent, this, "d_irq8")
    , d_irq9(parent, this, "d_irq9")
    , d_irq10(parent, this, "d_irq10")
    , d_irq11(parent, this, "d_irq11")
    , d_irq12(parent, this, "d_irq12")
    , d_irq13(parent, this, "d_irq13")
    , d_irq14(parent, this, "d_irq14")
    , d_irq15(parent, this, "d_irq15")
    , d_irq16(parent, this, "d_irq16")
    , d_irq17(parent, this, "d_irq17")
    , d_irq18(parent, this, "d_irq18")
    , d_irq19(parent, this, "d_irq19")
    , d_irq20(parent, this, "d_irq20")
    , d_irq21(parent, this, "d_irq21")
    , d_irq22(parent, this, "d_irq22")
    , d_irq23(parent, this, "d_irq23")
    , d_irq24(parent, this, "d_irq24")
    , d_irq25(parent, this, "d_irq25")
    , d_irq26(parent, this, "d_irq26")
    , d_irq27(parent, this, "d_irq27")
    , d_irq28(parent, this, "d_irq28")
    , d_irq29(parent, this, "d_irq29")
    , d_irq30(parent, this, "d_irq30")
    , d_irq31(parent, this, "d_irq31")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class nios_ii_Nios_II_E */


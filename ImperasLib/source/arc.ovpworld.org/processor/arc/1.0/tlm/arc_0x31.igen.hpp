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

class arc_0x31 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "0x31");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "0x31");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "arc.ovpworld.org", "processor", "arc", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      reset;
    tlmNetOutputPort     watchdog;
    tlmNetInputPort      irq5;
    tlmNetInputPort      irq6;
    tlmNetInputPort      irq7;
    tlmNetInputPort      irq8;
    tlmNetInputPort      irq9;
    tlmNetInputPort      irq10;
    tlmNetInputPort      irq11;
    tlmNetInputPort      irq12;
    tlmNetInputPort      irq13;
    tlmNetInputPort      irq14;
    tlmNetInputPort      irq15;
    tlmNetInputPort      irq16;
    tlmNetInputPort      irq17;
    tlmNetInputPort      irq18;
    tlmNetInputPort      irq19;
    tlmNetInputPort      irq20;
    tlmNetInputPort      irq21;
    tlmNetInputPort      irq22;
    tlmNetInputPort      irq23;
    tlmNetInputPort      irq24;
    tlmNetInputPort      irq25;
    tlmNetInputPort      irq26;
    tlmNetInputPort      irq27;
    tlmNetInputPort      irq28;
    tlmNetInputPort      irq29;
    tlmNetInputPort      irq30;
    tlmNetInputPort      irq31;

    arc_0x31(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 32)
    , DATA (parent, this, "DATA", 32)
    , reset(parent, this, "reset")
    , watchdog(parent, this, "watchdog")
    , irq5(parent, this, "irq5")
    , irq6(parent, this, "irq6")
    , irq7(parent, this, "irq7")
    , irq8(parent, this, "irq8")
    , irq9(parent, this, "irq9")
    , irq10(parent, this, "irq10")
    , irq11(parent, this, "irq11")
    , irq12(parent, this, "irq12")
    , irq13(parent, this, "irq13")
    , irq14(parent, this, "irq14")
    , irq15(parent, this, "irq15")
    , irq16(parent, this, "irq16")
    , irq17(parent, this, "irq17")
    , irq18(parent, this, "irq18")
    , irq19(parent, this, "irq19")
    , irq20(parent, this, "irq20")
    , irq21(parent, this, "irq21")
    , irq22(parent, this, "irq22")
    , irq23(parent, this, "irq23")
    , irq24(parent, this, "irq24")
    , irq25(parent, this, "irq25")
    , irq26(parent, this, "irq26")
    , irq27(parent, this, "irq27")
    , irq28(parent, this, "irq28")
    , irq29(parent, this, "irq29")
    , irq30(parent, this, "irq30")
    , irq31(parent, this, "irq31")
    {
    }

    arc_0x31(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , reset(parent, this, "reset")
    , watchdog(parent, this, "watchdog")
    , irq5(parent, this, "irq5")
    , irq6(parent, this, "irq6")
    , irq7(parent, this, "irq7")
    , irq8(parent, this, "irq8")
    , irq9(parent, this, "irq9")
    , irq10(parent, this, "irq10")
    , irq11(parent, this, "irq11")
    , irq12(parent, this, "irq12")
    , irq13(parent, this, "irq13")
    , irq14(parent, this, "irq14")
    , irq15(parent, this, "irq15")
    , irq16(parent, this, "irq16")
    , irq17(parent, this, "irq17")
    , irq18(parent, this, "irq18")
    , irq19(parent, this, "irq19")
    , irq20(parent, this, "irq20")
    , irq21(parent, this, "irq21")
    , irq22(parent, this, "irq22")
    , irq23(parent, this, "irq23")
    , irq24(parent, this, "irq24")
    , irq25(parent, this, "irq25")
    , irq26(parent, this, "irq26")
    , irq27(parent, this, "irq27")
    , irq28(parent, this, "irq28")
    , irq29(parent, this, "irq29")
    , irq30(parent, this, "irq30")
    , irq31(parent, this, "irq31")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class arc_0x31 */


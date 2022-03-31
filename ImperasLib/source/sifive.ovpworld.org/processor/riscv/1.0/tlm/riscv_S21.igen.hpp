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

class riscv_S21 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "S21");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "S21");
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
    tlmNetInputPort      hart0_CSIP;
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
    tlmNetInputPort      hart0_LocalInterrupt48;
    tlmNetInputPort      hart0_LocalInterrupt49;
    tlmNetInputPort      hart0_LocalInterrupt50;
    tlmNetInputPort      hart0_LocalInterrupt51;
    tlmNetInputPort      hart0_LocalInterrupt52;
    tlmNetInputPort      hart0_LocalInterrupt53;
    tlmNetInputPort      hart0_LocalInterrupt54;
    tlmNetInputPort      hart0_LocalInterrupt55;
    tlmNetInputPort      hart0_LocalInterrupt56;
    tlmNetInputPort      hart0_LocalInterrupt57;
    tlmNetInputPort      hart0_LocalInterrupt58;
    tlmNetInputPort      hart0_LocalInterrupt59;
    tlmNetInputPort      hart0_LocalInterrupt60;
    tlmNetInputPort      hart0_LocalInterrupt61;
    tlmNetInputPort      hart0_LocalInterrupt62;
    tlmNetInputPort      hart0_LocalInterrupt63;
    tlmNetInputPort      hart0_LocalInterrupt64;
    tlmNetInputPort      hart0_LocalInterrupt65;
    tlmNetInputPort      hart0_LocalInterrupt66;
    tlmNetInputPort      hart0_LocalInterrupt67;
    tlmNetInputPort      hart0_LocalInterrupt68;
    tlmNetInputPort      hart0_LocalInterrupt69;
    tlmNetInputPort      hart0_LocalInterrupt70;
    tlmNetInputPort      hart0_LocalInterrupt71;
    tlmNetInputPort      hart0_LocalInterrupt72;
    tlmNetInputPort      hart0_LocalInterrupt73;
    tlmNetInputPort      hart0_LocalInterrupt74;
    tlmNetInputPort      hart0_LocalInterrupt75;
    tlmNetInputPort      hart0_LocalInterrupt76;
    tlmNetInputPort      hart0_LocalInterrupt77;
    tlmNetInputPort      hart0_LocalInterrupt78;
    tlmNetInputPort      hart0_LocalInterrupt79;
    tlmNetInputPort      hart0_LocalInterrupt80;
    tlmNetInputPort      hart0_LocalInterrupt81;
    tlmNetInputPort      hart0_LocalInterrupt82;
    tlmNetInputPort      hart0_LocalInterrupt83;
    tlmNetInputPort      hart0_LocalInterrupt84;
    tlmNetInputPort      hart0_LocalInterrupt85;
    tlmNetInputPort      hart0_LocalInterrupt86;
    tlmNetInputPort      hart0_LocalInterrupt87;
    tlmNetInputPort      hart0_LocalInterrupt88;
    tlmNetInputPort      hart0_LocalInterrupt89;
    tlmNetInputPort      hart0_LocalInterrupt90;
    tlmNetInputPort      hart0_LocalInterrupt91;
    tlmNetInputPort      hart0_LocalInterrupt92;
    tlmNetInputPort      hart0_LocalInterrupt93;
    tlmNetInputPort      hart0_LocalInterrupt94;
    tlmNetInputPort      hart0_LocalInterrupt95;
    tlmNetInputPort      hart0_LocalInterrupt96;
    tlmNetInputPort      hart0_LocalInterrupt97;
    tlmNetInputPort      hart0_LocalInterrupt98;
    tlmNetInputPort      hart0_LocalInterrupt99;
    tlmNetInputPort      hart0_LocalInterrupt100;
    tlmNetInputPort      hart0_LocalInterrupt101;
    tlmNetInputPort      hart0_LocalInterrupt102;
    tlmNetInputPort      hart0_LocalInterrupt103;
    tlmNetInputPort      hart0_LocalInterrupt104;
    tlmNetInputPort      hart0_LocalInterrupt105;
    tlmNetInputPort      hart0_LocalInterrupt106;
    tlmNetInputPort      hart0_LocalInterrupt107;
    tlmNetInputPort      hart0_LocalInterrupt108;
    tlmNetInputPort      hart0_LocalInterrupt109;
    tlmNetInputPort      hart0_LocalInterrupt110;
    tlmNetInputPort      hart0_LocalInterrupt111;
    tlmNetInputPort      hart0_LocalInterrupt112;
    tlmNetInputPort      hart0_LocalInterrupt113;
    tlmNetInputPort      hart0_LocalInterrupt114;
    tlmNetInputPort      hart0_LocalInterrupt115;
    tlmNetInputPort      hart0_LocalInterrupt116;
    tlmNetInputPort      hart0_LocalInterrupt117;
    tlmNetInputPort      hart0_LocalInterrupt118;
    tlmNetInputPort      hart0_LocalInterrupt119;
    tlmNetInputPort      hart0_LocalInterrupt120;
    tlmNetInputPort      hart0_LocalInterrupt121;
    tlmNetInputPort      hart0_LocalInterrupt122;
    tlmNetInputPort      hart0_LocalInterrupt123;
    tlmNetInputPort      hart0_LocalInterrupt124;
    tlmNetInputPort      hart0_LocalInterrupt125;
    tlmNetInputPort      hart0_LocalInterrupt126;
    tlmNetOutputPort     hart0_irq_ack_o;
    tlmNetOutputPort     hart0_irq_id_o;
    tlmNetOutputPort     hart0_sec_lvl_o;
    tlmNetOutputPort     hart0_LR_address;
    tlmNetOutputPort     hart0_SC_address;
    tlmNetInputPort      hart0_SC_valid;
    tlmNetOutputPort     hart0_AMO_active;
    tlmNetInputPort      hart0_deferint;

    riscv_S21(tlmModule &parent, sc_module_name name)
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
    , hart0_CSIP(parent, this, "hart0_CSIP")
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
    , hart0_LocalInterrupt48(parent, this, "hart0_LocalInterrupt48")
    , hart0_LocalInterrupt49(parent, this, "hart0_LocalInterrupt49")
    , hart0_LocalInterrupt50(parent, this, "hart0_LocalInterrupt50")
    , hart0_LocalInterrupt51(parent, this, "hart0_LocalInterrupt51")
    , hart0_LocalInterrupt52(parent, this, "hart0_LocalInterrupt52")
    , hart0_LocalInterrupt53(parent, this, "hart0_LocalInterrupt53")
    , hart0_LocalInterrupt54(parent, this, "hart0_LocalInterrupt54")
    , hart0_LocalInterrupt55(parent, this, "hart0_LocalInterrupt55")
    , hart0_LocalInterrupt56(parent, this, "hart0_LocalInterrupt56")
    , hart0_LocalInterrupt57(parent, this, "hart0_LocalInterrupt57")
    , hart0_LocalInterrupt58(parent, this, "hart0_LocalInterrupt58")
    , hart0_LocalInterrupt59(parent, this, "hart0_LocalInterrupt59")
    , hart0_LocalInterrupt60(parent, this, "hart0_LocalInterrupt60")
    , hart0_LocalInterrupt61(parent, this, "hart0_LocalInterrupt61")
    , hart0_LocalInterrupt62(parent, this, "hart0_LocalInterrupt62")
    , hart0_LocalInterrupt63(parent, this, "hart0_LocalInterrupt63")
    , hart0_LocalInterrupt64(parent, this, "hart0_LocalInterrupt64")
    , hart0_LocalInterrupt65(parent, this, "hart0_LocalInterrupt65")
    , hart0_LocalInterrupt66(parent, this, "hart0_LocalInterrupt66")
    , hart0_LocalInterrupt67(parent, this, "hart0_LocalInterrupt67")
    , hart0_LocalInterrupt68(parent, this, "hart0_LocalInterrupt68")
    , hart0_LocalInterrupt69(parent, this, "hart0_LocalInterrupt69")
    , hart0_LocalInterrupt70(parent, this, "hart0_LocalInterrupt70")
    , hart0_LocalInterrupt71(parent, this, "hart0_LocalInterrupt71")
    , hart0_LocalInterrupt72(parent, this, "hart0_LocalInterrupt72")
    , hart0_LocalInterrupt73(parent, this, "hart0_LocalInterrupt73")
    , hart0_LocalInterrupt74(parent, this, "hart0_LocalInterrupt74")
    , hart0_LocalInterrupt75(parent, this, "hart0_LocalInterrupt75")
    , hart0_LocalInterrupt76(parent, this, "hart0_LocalInterrupt76")
    , hart0_LocalInterrupt77(parent, this, "hart0_LocalInterrupt77")
    , hart0_LocalInterrupt78(parent, this, "hart0_LocalInterrupt78")
    , hart0_LocalInterrupt79(parent, this, "hart0_LocalInterrupt79")
    , hart0_LocalInterrupt80(parent, this, "hart0_LocalInterrupt80")
    , hart0_LocalInterrupt81(parent, this, "hart0_LocalInterrupt81")
    , hart0_LocalInterrupt82(parent, this, "hart0_LocalInterrupt82")
    , hart0_LocalInterrupt83(parent, this, "hart0_LocalInterrupt83")
    , hart0_LocalInterrupt84(parent, this, "hart0_LocalInterrupt84")
    , hart0_LocalInterrupt85(parent, this, "hart0_LocalInterrupt85")
    , hart0_LocalInterrupt86(parent, this, "hart0_LocalInterrupt86")
    , hart0_LocalInterrupt87(parent, this, "hart0_LocalInterrupt87")
    , hart0_LocalInterrupt88(parent, this, "hart0_LocalInterrupt88")
    , hart0_LocalInterrupt89(parent, this, "hart0_LocalInterrupt89")
    , hart0_LocalInterrupt90(parent, this, "hart0_LocalInterrupt90")
    , hart0_LocalInterrupt91(parent, this, "hart0_LocalInterrupt91")
    , hart0_LocalInterrupt92(parent, this, "hart0_LocalInterrupt92")
    , hart0_LocalInterrupt93(parent, this, "hart0_LocalInterrupt93")
    , hart0_LocalInterrupt94(parent, this, "hart0_LocalInterrupt94")
    , hart0_LocalInterrupt95(parent, this, "hart0_LocalInterrupt95")
    , hart0_LocalInterrupt96(parent, this, "hart0_LocalInterrupt96")
    , hart0_LocalInterrupt97(parent, this, "hart0_LocalInterrupt97")
    , hart0_LocalInterrupt98(parent, this, "hart0_LocalInterrupt98")
    , hart0_LocalInterrupt99(parent, this, "hart0_LocalInterrupt99")
    , hart0_LocalInterrupt100(parent, this, "hart0_LocalInterrupt100")
    , hart0_LocalInterrupt101(parent, this, "hart0_LocalInterrupt101")
    , hart0_LocalInterrupt102(parent, this, "hart0_LocalInterrupt102")
    , hart0_LocalInterrupt103(parent, this, "hart0_LocalInterrupt103")
    , hart0_LocalInterrupt104(parent, this, "hart0_LocalInterrupt104")
    , hart0_LocalInterrupt105(parent, this, "hart0_LocalInterrupt105")
    , hart0_LocalInterrupt106(parent, this, "hart0_LocalInterrupt106")
    , hart0_LocalInterrupt107(parent, this, "hart0_LocalInterrupt107")
    , hart0_LocalInterrupt108(parent, this, "hart0_LocalInterrupt108")
    , hart0_LocalInterrupt109(parent, this, "hart0_LocalInterrupt109")
    , hart0_LocalInterrupt110(parent, this, "hart0_LocalInterrupt110")
    , hart0_LocalInterrupt111(parent, this, "hart0_LocalInterrupt111")
    , hart0_LocalInterrupt112(parent, this, "hart0_LocalInterrupt112")
    , hart0_LocalInterrupt113(parent, this, "hart0_LocalInterrupt113")
    , hart0_LocalInterrupt114(parent, this, "hart0_LocalInterrupt114")
    , hart0_LocalInterrupt115(parent, this, "hart0_LocalInterrupt115")
    , hart0_LocalInterrupt116(parent, this, "hart0_LocalInterrupt116")
    , hart0_LocalInterrupt117(parent, this, "hart0_LocalInterrupt117")
    , hart0_LocalInterrupt118(parent, this, "hart0_LocalInterrupt118")
    , hart0_LocalInterrupt119(parent, this, "hart0_LocalInterrupt119")
    , hart0_LocalInterrupt120(parent, this, "hart0_LocalInterrupt120")
    , hart0_LocalInterrupt121(parent, this, "hart0_LocalInterrupt121")
    , hart0_LocalInterrupt122(parent, this, "hart0_LocalInterrupt122")
    , hart0_LocalInterrupt123(parent, this, "hart0_LocalInterrupt123")
    , hart0_LocalInterrupt124(parent, this, "hart0_LocalInterrupt124")
    , hart0_LocalInterrupt125(parent, this, "hart0_LocalInterrupt125")
    , hart0_LocalInterrupt126(parent, this, "hart0_LocalInterrupt126")
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

    riscv_S21(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=56, Uns32 DATAWidth=56)
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
    , hart0_CSIP(parent, this, "hart0_CSIP")
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
    , hart0_LocalInterrupt48(parent, this, "hart0_LocalInterrupt48")
    , hart0_LocalInterrupt49(parent, this, "hart0_LocalInterrupt49")
    , hart0_LocalInterrupt50(parent, this, "hart0_LocalInterrupt50")
    , hart0_LocalInterrupt51(parent, this, "hart0_LocalInterrupt51")
    , hart0_LocalInterrupt52(parent, this, "hart0_LocalInterrupt52")
    , hart0_LocalInterrupt53(parent, this, "hart0_LocalInterrupt53")
    , hart0_LocalInterrupt54(parent, this, "hart0_LocalInterrupt54")
    , hart0_LocalInterrupt55(parent, this, "hart0_LocalInterrupt55")
    , hart0_LocalInterrupt56(parent, this, "hart0_LocalInterrupt56")
    , hart0_LocalInterrupt57(parent, this, "hart0_LocalInterrupt57")
    , hart0_LocalInterrupt58(parent, this, "hart0_LocalInterrupt58")
    , hart0_LocalInterrupt59(parent, this, "hart0_LocalInterrupt59")
    , hart0_LocalInterrupt60(parent, this, "hart0_LocalInterrupt60")
    , hart0_LocalInterrupt61(parent, this, "hart0_LocalInterrupt61")
    , hart0_LocalInterrupt62(parent, this, "hart0_LocalInterrupt62")
    , hart0_LocalInterrupt63(parent, this, "hart0_LocalInterrupt63")
    , hart0_LocalInterrupt64(parent, this, "hart0_LocalInterrupt64")
    , hart0_LocalInterrupt65(parent, this, "hart0_LocalInterrupt65")
    , hart0_LocalInterrupt66(parent, this, "hart0_LocalInterrupt66")
    , hart0_LocalInterrupt67(parent, this, "hart0_LocalInterrupt67")
    , hart0_LocalInterrupt68(parent, this, "hart0_LocalInterrupt68")
    , hart0_LocalInterrupt69(parent, this, "hart0_LocalInterrupt69")
    , hart0_LocalInterrupt70(parent, this, "hart0_LocalInterrupt70")
    , hart0_LocalInterrupt71(parent, this, "hart0_LocalInterrupt71")
    , hart0_LocalInterrupt72(parent, this, "hart0_LocalInterrupt72")
    , hart0_LocalInterrupt73(parent, this, "hart0_LocalInterrupt73")
    , hart0_LocalInterrupt74(parent, this, "hart0_LocalInterrupt74")
    , hart0_LocalInterrupt75(parent, this, "hart0_LocalInterrupt75")
    , hart0_LocalInterrupt76(parent, this, "hart0_LocalInterrupt76")
    , hart0_LocalInterrupt77(parent, this, "hart0_LocalInterrupt77")
    , hart0_LocalInterrupt78(parent, this, "hart0_LocalInterrupt78")
    , hart0_LocalInterrupt79(parent, this, "hart0_LocalInterrupt79")
    , hart0_LocalInterrupt80(parent, this, "hart0_LocalInterrupt80")
    , hart0_LocalInterrupt81(parent, this, "hart0_LocalInterrupt81")
    , hart0_LocalInterrupt82(parent, this, "hart0_LocalInterrupt82")
    , hart0_LocalInterrupt83(parent, this, "hart0_LocalInterrupt83")
    , hart0_LocalInterrupt84(parent, this, "hart0_LocalInterrupt84")
    , hart0_LocalInterrupt85(parent, this, "hart0_LocalInterrupt85")
    , hart0_LocalInterrupt86(parent, this, "hart0_LocalInterrupt86")
    , hart0_LocalInterrupt87(parent, this, "hart0_LocalInterrupt87")
    , hart0_LocalInterrupt88(parent, this, "hart0_LocalInterrupt88")
    , hart0_LocalInterrupt89(parent, this, "hart0_LocalInterrupt89")
    , hart0_LocalInterrupt90(parent, this, "hart0_LocalInterrupt90")
    , hart0_LocalInterrupt91(parent, this, "hart0_LocalInterrupt91")
    , hart0_LocalInterrupt92(parent, this, "hart0_LocalInterrupt92")
    , hart0_LocalInterrupt93(parent, this, "hart0_LocalInterrupt93")
    , hart0_LocalInterrupt94(parent, this, "hart0_LocalInterrupt94")
    , hart0_LocalInterrupt95(parent, this, "hart0_LocalInterrupt95")
    , hart0_LocalInterrupt96(parent, this, "hart0_LocalInterrupt96")
    , hart0_LocalInterrupt97(parent, this, "hart0_LocalInterrupt97")
    , hart0_LocalInterrupt98(parent, this, "hart0_LocalInterrupt98")
    , hart0_LocalInterrupt99(parent, this, "hart0_LocalInterrupt99")
    , hart0_LocalInterrupt100(parent, this, "hart0_LocalInterrupt100")
    , hart0_LocalInterrupt101(parent, this, "hart0_LocalInterrupt101")
    , hart0_LocalInterrupt102(parent, this, "hart0_LocalInterrupt102")
    , hart0_LocalInterrupt103(parent, this, "hart0_LocalInterrupt103")
    , hart0_LocalInterrupt104(parent, this, "hart0_LocalInterrupt104")
    , hart0_LocalInterrupt105(parent, this, "hart0_LocalInterrupt105")
    , hart0_LocalInterrupt106(parent, this, "hart0_LocalInterrupt106")
    , hart0_LocalInterrupt107(parent, this, "hart0_LocalInterrupt107")
    , hart0_LocalInterrupt108(parent, this, "hart0_LocalInterrupt108")
    , hart0_LocalInterrupt109(parent, this, "hart0_LocalInterrupt109")
    , hart0_LocalInterrupt110(parent, this, "hart0_LocalInterrupt110")
    , hart0_LocalInterrupt111(parent, this, "hart0_LocalInterrupt111")
    , hart0_LocalInterrupt112(parent, this, "hart0_LocalInterrupt112")
    , hart0_LocalInterrupt113(parent, this, "hart0_LocalInterrupt113")
    , hart0_LocalInterrupt114(parent, this, "hart0_LocalInterrupt114")
    , hart0_LocalInterrupt115(parent, this, "hart0_LocalInterrupt115")
    , hart0_LocalInterrupt116(parent, this, "hart0_LocalInterrupt116")
    , hart0_LocalInterrupt117(parent, this, "hart0_LocalInterrupt117")
    , hart0_LocalInterrupt118(parent, this, "hart0_LocalInterrupt118")
    , hart0_LocalInterrupt119(parent, this, "hart0_LocalInterrupt119")
    , hart0_LocalInterrupt120(parent, this, "hart0_LocalInterrupt120")
    , hart0_LocalInterrupt121(parent, this, "hart0_LocalInterrupt121")
    , hart0_LocalInterrupt122(parent, this, "hart0_LocalInterrupt122")
    , hart0_LocalInterrupt123(parent, this, "hart0_LocalInterrupt123")
    , hart0_LocalInterrupt124(parent, this, "hart0_LocalInterrupt124")
    , hart0_LocalInterrupt125(parent, this, "hart0_LocalInterrupt125")
    , hart0_LocalInterrupt126(parent, this, "hart0_LocalInterrupt126")
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
}; /* class riscv_S21 */


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

class riscv_E24 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "E24");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "E24");
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
    tlmNetInputPort      nmiexc_addr;
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
    tlmNetInputPort      LocalInterrupt32;
    tlmNetInputPort      LocalInterrupt33;
    tlmNetInputPort      LocalInterrupt34;
    tlmNetInputPort      LocalInterrupt35;
    tlmNetInputPort      LocalInterrupt36;
    tlmNetInputPort      LocalInterrupt37;
    tlmNetInputPort      LocalInterrupt38;
    tlmNetInputPort      LocalInterrupt39;
    tlmNetInputPort      LocalInterrupt40;
    tlmNetInputPort      LocalInterrupt41;
    tlmNetInputPort      LocalInterrupt42;
    tlmNetInputPort      LocalInterrupt43;
    tlmNetInputPort      LocalInterrupt44;
    tlmNetInputPort      LocalInterrupt45;
    tlmNetInputPort      LocalInterrupt46;
    tlmNetInputPort      LocalInterrupt47;
    tlmNetInputPort      LocalInterrupt48;
    tlmNetInputPort      LocalInterrupt49;
    tlmNetInputPort      LocalInterrupt50;
    tlmNetInputPort      LocalInterrupt51;
    tlmNetInputPort      LocalInterrupt52;
    tlmNetInputPort      LocalInterrupt53;
    tlmNetInputPort      LocalInterrupt54;
    tlmNetInputPort      LocalInterrupt55;
    tlmNetInputPort      LocalInterrupt56;
    tlmNetInputPort      LocalInterrupt57;
    tlmNetInputPort      LocalInterrupt58;
    tlmNetInputPort      LocalInterrupt59;
    tlmNetInputPort      LocalInterrupt60;
    tlmNetInputPort      LocalInterrupt61;
    tlmNetInputPort      LocalInterrupt62;
    tlmNetInputPort      LocalInterrupt63;
    tlmNetInputPort      LocalInterrupt64;
    tlmNetInputPort      LocalInterrupt65;
    tlmNetInputPort      LocalInterrupt66;
    tlmNetInputPort      LocalInterrupt67;
    tlmNetInputPort      LocalInterrupt68;
    tlmNetInputPort      LocalInterrupt69;
    tlmNetInputPort      LocalInterrupt70;
    tlmNetInputPort      LocalInterrupt71;
    tlmNetInputPort      LocalInterrupt72;
    tlmNetInputPort      LocalInterrupt73;
    tlmNetInputPort      LocalInterrupt74;
    tlmNetInputPort      LocalInterrupt75;
    tlmNetInputPort      LocalInterrupt76;
    tlmNetInputPort      LocalInterrupt77;
    tlmNetInputPort      LocalInterrupt78;
    tlmNetInputPort      LocalInterrupt79;
    tlmNetInputPort      LocalInterrupt80;
    tlmNetInputPort      LocalInterrupt81;
    tlmNetInputPort      LocalInterrupt82;
    tlmNetInputPort      LocalInterrupt83;
    tlmNetInputPort      LocalInterrupt84;
    tlmNetInputPort      LocalInterrupt85;
    tlmNetInputPort      LocalInterrupt86;
    tlmNetInputPort      LocalInterrupt87;
    tlmNetInputPort      LocalInterrupt88;
    tlmNetInputPort      LocalInterrupt89;
    tlmNetInputPort      LocalInterrupt90;
    tlmNetInputPort      LocalInterrupt91;
    tlmNetInputPort      LocalInterrupt92;
    tlmNetInputPort      LocalInterrupt93;
    tlmNetInputPort      LocalInterrupt94;
    tlmNetInputPort      LocalInterrupt95;
    tlmNetInputPort      LocalInterrupt96;
    tlmNetInputPort      LocalInterrupt97;
    tlmNetInputPort      LocalInterrupt98;
    tlmNetInputPort      LocalInterrupt99;
    tlmNetInputPort      LocalInterrupt100;
    tlmNetInputPort      LocalInterrupt101;
    tlmNetInputPort      LocalInterrupt102;
    tlmNetInputPort      LocalInterrupt103;
    tlmNetInputPort      LocalInterrupt104;
    tlmNetInputPort      LocalInterrupt105;
    tlmNetInputPort      LocalInterrupt106;
    tlmNetInputPort      LocalInterrupt107;
    tlmNetInputPort      LocalInterrupt108;
    tlmNetInputPort      LocalInterrupt109;
    tlmNetInputPort      LocalInterrupt110;
    tlmNetInputPort      LocalInterrupt111;
    tlmNetInputPort      LocalInterrupt112;
    tlmNetInputPort      LocalInterrupt113;
    tlmNetInputPort      LocalInterrupt114;
    tlmNetInputPort      LocalInterrupt115;
    tlmNetInputPort      LocalInterrupt116;
    tlmNetInputPort      LocalInterrupt117;
    tlmNetInputPort      LocalInterrupt118;
    tlmNetInputPort      LocalInterrupt119;
    tlmNetInputPort      LocalInterrupt120;
    tlmNetInputPort      LocalInterrupt121;
    tlmNetInputPort      LocalInterrupt122;
    tlmNetInputPort      LocalInterrupt123;
    tlmNetInputPort      LocalInterrupt124;
    tlmNetInputPort      LocalInterrupt125;
    tlmNetInputPort      LocalInterrupt126;
    tlmNetOutputPort     irq_ack_o;
    tlmNetOutputPort     irq_id_o;
    tlmNetOutputPort     sec_lvl_o;
    tlmNetOutputPort     LR_address;
    tlmNetOutputPort     SC_address;
    tlmNetInputPort      SC_valid;
    tlmNetOutputPort     AMO_active;
    tlmNetInputPort      deferint;

    riscv_E24(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 34)
    , DATA (parent, this, "DATA", 34)
    , reset(parent, this, "reset")
    , reset_addr(parent, this, "reset_addr")
    , nmi(parent, this, "nmi")
    , nmi_cause(parent, this, "nmi_cause")
    , nmi_addr(parent, this, "nmi_addr")
    , nmiexc_addr(parent, this, "nmiexc_addr")
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
    , LocalInterrupt32(parent, this, "LocalInterrupt32")
    , LocalInterrupt33(parent, this, "LocalInterrupt33")
    , LocalInterrupt34(parent, this, "LocalInterrupt34")
    , LocalInterrupt35(parent, this, "LocalInterrupt35")
    , LocalInterrupt36(parent, this, "LocalInterrupt36")
    , LocalInterrupt37(parent, this, "LocalInterrupt37")
    , LocalInterrupt38(parent, this, "LocalInterrupt38")
    , LocalInterrupt39(parent, this, "LocalInterrupt39")
    , LocalInterrupt40(parent, this, "LocalInterrupt40")
    , LocalInterrupt41(parent, this, "LocalInterrupt41")
    , LocalInterrupt42(parent, this, "LocalInterrupt42")
    , LocalInterrupt43(parent, this, "LocalInterrupt43")
    , LocalInterrupt44(parent, this, "LocalInterrupt44")
    , LocalInterrupt45(parent, this, "LocalInterrupt45")
    , LocalInterrupt46(parent, this, "LocalInterrupt46")
    , LocalInterrupt47(parent, this, "LocalInterrupt47")
    , LocalInterrupt48(parent, this, "LocalInterrupt48")
    , LocalInterrupt49(parent, this, "LocalInterrupt49")
    , LocalInterrupt50(parent, this, "LocalInterrupt50")
    , LocalInterrupt51(parent, this, "LocalInterrupt51")
    , LocalInterrupt52(parent, this, "LocalInterrupt52")
    , LocalInterrupt53(parent, this, "LocalInterrupt53")
    , LocalInterrupt54(parent, this, "LocalInterrupt54")
    , LocalInterrupt55(parent, this, "LocalInterrupt55")
    , LocalInterrupt56(parent, this, "LocalInterrupt56")
    , LocalInterrupt57(parent, this, "LocalInterrupt57")
    , LocalInterrupt58(parent, this, "LocalInterrupt58")
    , LocalInterrupt59(parent, this, "LocalInterrupt59")
    , LocalInterrupt60(parent, this, "LocalInterrupt60")
    , LocalInterrupt61(parent, this, "LocalInterrupt61")
    , LocalInterrupt62(parent, this, "LocalInterrupt62")
    , LocalInterrupt63(parent, this, "LocalInterrupt63")
    , LocalInterrupt64(parent, this, "LocalInterrupt64")
    , LocalInterrupt65(parent, this, "LocalInterrupt65")
    , LocalInterrupt66(parent, this, "LocalInterrupt66")
    , LocalInterrupt67(parent, this, "LocalInterrupt67")
    , LocalInterrupt68(parent, this, "LocalInterrupt68")
    , LocalInterrupt69(parent, this, "LocalInterrupt69")
    , LocalInterrupt70(parent, this, "LocalInterrupt70")
    , LocalInterrupt71(parent, this, "LocalInterrupt71")
    , LocalInterrupt72(parent, this, "LocalInterrupt72")
    , LocalInterrupt73(parent, this, "LocalInterrupt73")
    , LocalInterrupt74(parent, this, "LocalInterrupt74")
    , LocalInterrupt75(parent, this, "LocalInterrupt75")
    , LocalInterrupt76(parent, this, "LocalInterrupt76")
    , LocalInterrupt77(parent, this, "LocalInterrupt77")
    , LocalInterrupt78(parent, this, "LocalInterrupt78")
    , LocalInterrupt79(parent, this, "LocalInterrupt79")
    , LocalInterrupt80(parent, this, "LocalInterrupt80")
    , LocalInterrupt81(parent, this, "LocalInterrupt81")
    , LocalInterrupt82(parent, this, "LocalInterrupt82")
    , LocalInterrupt83(parent, this, "LocalInterrupt83")
    , LocalInterrupt84(parent, this, "LocalInterrupt84")
    , LocalInterrupt85(parent, this, "LocalInterrupt85")
    , LocalInterrupt86(parent, this, "LocalInterrupt86")
    , LocalInterrupt87(parent, this, "LocalInterrupt87")
    , LocalInterrupt88(parent, this, "LocalInterrupt88")
    , LocalInterrupt89(parent, this, "LocalInterrupt89")
    , LocalInterrupt90(parent, this, "LocalInterrupt90")
    , LocalInterrupt91(parent, this, "LocalInterrupt91")
    , LocalInterrupt92(parent, this, "LocalInterrupt92")
    , LocalInterrupt93(parent, this, "LocalInterrupt93")
    , LocalInterrupt94(parent, this, "LocalInterrupt94")
    , LocalInterrupt95(parent, this, "LocalInterrupt95")
    , LocalInterrupt96(parent, this, "LocalInterrupt96")
    , LocalInterrupt97(parent, this, "LocalInterrupt97")
    , LocalInterrupt98(parent, this, "LocalInterrupt98")
    , LocalInterrupt99(parent, this, "LocalInterrupt99")
    , LocalInterrupt100(parent, this, "LocalInterrupt100")
    , LocalInterrupt101(parent, this, "LocalInterrupt101")
    , LocalInterrupt102(parent, this, "LocalInterrupt102")
    , LocalInterrupt103(parent, this, "LocalInterrupt103")
    , LocalInterrupt104(parent, this, "LocalInterrupt104")
    , LocalInterrupt105(parent, this, "LocalInterrupt105")
    , LocalInterrupt106(parent, this, "LocalInterrupt106")
    , LocalInterrupt107(parent, this, "LocalInterrupt107")
    , LocalInterrupt108(parent, this, "LocalInterrupt108")
    , LocalInterrupt109(parent, this, "LocalInterrupt109")
    , LocalInterrupt110(parent, this, "LocalInterrupt110")
    , LocalInterrupt111(parent, this, "LocalInterrupt111")
    , LocalInterrupt112(parent, this, "LocalInterrupt112")
    , LocalInterrupt113(parent, this, "LocalInterrupt113")
    , LocalInterrupt114(parent, this, "LocalInterrupt114")
    , LocalInterrupt115(parent, this, "LocalInterrupt115")
    , LocalInterrupt116(parent, this, "LocalInterrupt116")
    , LocalInterrupt117(parent, this, "LocalInterrupt117")
    , LocalInterrupt118(parent, this, "LocalInterrupt118")
    , LocalInterrupt119(parent, this, "LocalInterrupt119")
    , LocalInterrupt120(parent, this, "LocalInterrupt120")
    , LocalInterrupt121(parent, this, "LocalInterrupt121")
    , LocalInterrupt122(parent, this, "LocalInterrupt122")
    , LocalInterrupt123(parent, this, "LocalInterrupt123")
    , LocalInterrupt124(parent, this, "LocalInterrupt124")
    , LocalInterrupt125(parent, this, "LocalInterrupt125")
    , LocalInterrupt126(parent, this, "LocalInterrupt126")
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

    riscv_E24(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=34, Uns32 DATAWidth=34)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , reset(parent, this, "reset")
    , reset_addr(parent, this, "reset_addr")
    , nmi(parent, this, "nmi")
    , nmi_cause(parent, this, "nmi_cause")
    , nmi_addr(parent, this, "nmi_addr")
    , nmiexc_addr(parent, this, "nmiexc_addr")
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
    , LocalInterrupt32(parent, this, "LocalInterrupt32")
    , LocalInterrupt33(parent, this, "LocalInterrupt33")
    , LocalInterrupt34(parent, this, "LocalInterrupt34")
    , LocalInterrupt35(parent, this, "LocalInterrupt35")
    , LocalInterrupt36(parent, this, "LocalInterrupt36")
    , LocalInterrupt37(parent, this, "LocalInterrupt37")
    , LocalInterrupt38(parent, this, "LocalInterrupt38")
    , LocalInterrupt39(parent, this, "LocalInterrupt39")
    , LocalInterrupt40(parent, this, "LocalInterrupt40")
    , LocalInterrupt41(parent, this, "LocalInterrupt41")
    , LocalInterrupt42(parent, this, "LocalInterrupt42")
    , LocalInterrupt43(parent, this, "LocalInterrupt43")
    , LocalInterrupt44(parent, this, "LocalInterrupt44")
    , LocalInterrupt45(parent, this, "LocalInterrupt45")
    , LocalInterrupt46(parent, this, "LocalInterrupt46")
    , LocalInterrupt47(parent, this, "LocalInterrupt47")
    , LocalInterrupt48(parent, this, "LocalInterrupt48")
    , LocalInterrupt49(parent, this, "LocalInterrupt49")
    , LocalInterrupt50(parent, this, "LocalInterrupt50")
    , LocalInterrupt51(parent, this, "LocalInterrupt51")
    , LocalInterrupt52(parent, this, "LocalInterrupt52")
    , LocalInterrupt53(parent, this, "LocalInterrupt53")
    , LocalInterrupt54(parent, this, "LocalInterrupt54")
    , LocalInterrupt55(parent, this, "LocalInterrupt55")
    , LocalInterrupt56(parent, this, "LocalInterrupt56")
    , LocalInterrupt57(parent, this, "LocalInterrupt57")
    , LocalInterrupt58(parent, this, "LocalInterrupt58")
    , LocalInterrupt59(parent, this, "LocalInterrupt59")
    , LocalInterrupt60(parent, this, "LocalInterrupt60")
    , LocalInterrupt61(parent, this, "LocalInterrupt61")
    , LocalInterrupt62(parent, this, "LocalInterrupt62")
    , LocalInterrupt63(parent, this, "LocalInterrupt63")
    , LocalInterrupt64(parent, this, "LocalInterrupt64")
    , LocalInterrupt65(parent, this, "LocalInterrupt65")
    , LocalInterrupt66(parent, this, "LocalInterrupt66")
    , LocalInterrupt67(parent, this, "LocalInterrupt67")
    , LocalInterrupt68(parent, this, "LocalInterrupt68")
    , LocalInterrupt69(parent, this, "LocalInterrupt69")
    , LocalInterrupt70(parent, this, "LocalInterrupt70")
    , LocalInterrupt71(parent, this, "LocalInterrupt71")
    , LocalInterrupt72(parent, this, "LocalInterrupt72")
    , LocalInterrupt73(parent, this, "LocalInterrupt73")
    , LocalInterrupt74(parent, this, "LocalInterrupt74")
    , LocalInterrupt75(parent, this, "LocalInterrupt75")
    , LocalInterrupt76(parent, this, "LocalInterrupt76")
    , LocalInterrupt77(parent, this, "LocalInterrupt77")
    , LocalInterrupt78(parent, this, "LocalInterrupt78")
    , LocalInterrupt79(parent, this, "LocalInterrupt79")
    , LocalInterrupt80(parent, this, "LocalInterrupt80")
    , LocalInterrupt81(parent, this, "LocalInterrupt81")
    , LocalInterrupt82(parent, this, "LocalInterrupt82")
    , LocalInterrupt83(parent, this, "LocalInterrupt83")
    , LocalInterrupt84(parent, this, "LocalInterrupt84")
    , LocalInterrupt85(parent, this, "LocalInterrupt85")
    , LocalInterrupt86(parent, this, "LocalInterrupt86")
    , LocalInterrupt87(parent, this, "LocalInterrupt87")
    , LocalInterrupt88(parent, this, "LocalInterrupt88")
    , LocalInterrupt89(parent, this, "LocalInterrupt89")
    , LocalInterrupt90(parent, this, "LocalInterrupt90")
    , LocalInterrupt91(parent, this, "LocalInterrupt91")
    , LocalInterrupt92(parent, this, "LocalInterrupt92")
    , LocalInterrupt93(parent, this, "LocalInterrupt93")
    , LocalInterrupt94(parent, this, "LocalInterrupt94")
    , LocalInterrupt95(parent, this, "LocalInterrupt95")
    , LocalInterrupt96(parent, this, "LocalInterrupt96")
    , LocalInterrupt97(parent, this, "LocalInterrupt97")
    , LocalInterrupt98(parent, this, "LocalInterrupt98")
    , LocalInterrupt99(parent, this, "LocalInterrupt99")
    , LocalInterrupt100(parent, this, "LocalInterrupt100")
    , LocalInterrupt101(parent, this, "LocalInterrupt101")
    , LocalInterrupt102(parent, this, "LocalInterrupt102")
    , LocalInterrupt103(parent, this, "LocalInterrupt103")
    , LocalInterrupt104(parent, this, "LocalInterrupt104")
    , LocalInterrupt105(parent, this, "LocalInterrupt105")
    , LocalInterrupt106(parent, this, "LocalInterrupt106")
    , LocalInterrupt107(parent, this, "LocalInterrupt107")
    , LocalInterrupt108(parent, this, "LocalInterrupt108")
    , LocalInterrupt109(parent, this, "LocalInterrupt109")
    , LocalInterrupt110(parent, this, "LocalInterrupt110")
    , LocalInterrupt111(parent, this, "LocalInterrupt111")
    , LocalInterrupt112(parent, this, "LocalInterrupt112")
    , LocalInterrupt113(parent, this, "LocalInterrupt113")
    , LocalInterrupt114(parent, this, "LocalInterrupt114")
    , LocalInterrupt115(parent, this, "LocalInterrupt115")
    , LocalInterrupt116(parent, this, "LocalInterrupt116")
    , LocalInterrupt117(parent, this, "LocalInterrupt117")
    , LocalInterrupt118(parent, this, "LocalInterrupt118")
    , LocalInterrupt119(parent, this, "LocalInterrupt119")
    , LocalInterrupt120(parent, this, "LocalInterrupt120")
    , LocalInterrupt121(parent, this, "LocalInterrupt121")
    , LocalInterrupt122(parent, this, "LocalInterrupt122")
    , LocalInterrupt123(parent, this, "LocalInterrupt123")
    , LocalInterrupt124(parent, this, "LocalInterrupt124")
    , LocalInterrupt125(parent, this, "LocalInterrupt125")
    , LocalInterrupt126(parent, this, "LocalInterrupt126")
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
}; /* class riscv_E24 */


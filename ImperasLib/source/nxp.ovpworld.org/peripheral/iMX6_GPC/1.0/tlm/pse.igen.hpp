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

// MODEL IO:
//    Slave Port bport1
//    Net input  irq32;
//    Net input  irq33;
//    Net input  irq34;
//    Net input  irq35;
//    Net input  irq36;
//    Net input  irq37;
//    Net input  irq38;
//    Net input  irq39;
//    Net input  irq40;
//    Net input  irq41;
//    Net input  irq42;
//    Net input  irq43;
//    Net input  irq44;
//    Net input  irq45;
//    Net input  irq46;
//    Net input  irq47;
//    Net input  irq48;
//    Net input  irq49;
//    Net input  irq50;
//    Net input  irq51;
//    Net input  irq52;
//    Net input  irq53;
//    Net input  irq54;
//    Net input  irq55;
//    Net input  irq56;
//    Net input  irq57;
//    Net input  irq58;
//    Net input  irq59;
//    Net input  irq60;
//    Net input  irq61;
//    Net input  irq62;
//    Net input  irq63;
//    Net input  irq64;
//    Net input  irq65;
//    Net input  irq66;
//    Net input  irq67;
//    Net input  irq68;
//    Net input  irq69;
//    Net input  irq70;
//    Net input  irq71;
//    Net input  irq72;
//    Net input  irq73;
//    Net input  irq74;
//    Net input  irq75;
//    Net input  irq76;
//    Net input  irq77;
//    Net input  irq78;
//    Net input  irq79;
//    Net input  irq80;
//    Net input  irq81;
//    Net input  irq82;
//    Net input  irq83;
//    Net input  irq84;
//    Net input  irq85;
//    Net input  irq86;
//    Net input  irq87;
//    Net input  irq88;
//    Net input  irq89;
//    Net input  irq90;
//    Net input  irq91;
//    Net input  irq92;
//    Net input  irq93;
//    Net input  irq94;
//    Net input  irq95;
//    Net input  irq96;
//    Net input  irq97;
//    Net input  irq98;
//    Net input  irq99;
//    Net input  irq100;
//    Net input  irq101;
//    Net input  irq102;
//    Net input  irq103;
//    Net input  irq104;
//    Net input  irq105;
//    Net input  irq106;
//    Net input  irq107;
//    Net input  irq108;
//    Net input  irq109;
//    Net input  irq110;
//    Net input  irq111;
//    Net input  irq112;
//    Net input  irq113;
//    Net input  irq114;
//    Net input  irq115;
//    Net input  irq116;
//    Net input  irq117;
//    Net input  irq118;
//    Net input  irq119;
//    Net input  irq120;
//    Net input  irq121;
//    Net input  irq122;
//    Net input  irq123;
//    Net input  irq124;
//    Net input  irq125;
//    Net input  irq126;
//    Net input  irq127;
//    Net input  irq128;
//    Net input  irq129;
//    Net input  irq130;
//    Net input  irq131;
//    Net input  irq132;
//    Net input  irq133;
//    Net input  irq134;
//    Net input  irq135;
//    Net input  irq136;
//    Net input  irq137;
//    Net input  irq138;
//    Net input  irq139;
//    Net input  irq140;
//    Net input  irq141;
//    Net input  irq142;
//    Net input  irq143;
//    Net input  irq144;
//    Net input  irq145;
//    Net input  irq146;
//    Net input  irq147;
//    Net input  irq148;
//    Net input  irq149;
//    Net input  irq150;
//    Net input  irq151;
//    Net input  irq152;
//    Net input  irq153;
//    Net input  irq154;
//    Net input  irq155;
//    Net input  irq156;
//    Net input  irq157;
//    Net input  irq158;
//    Net input  irq159;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class iMX6_GPC : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "nxp.ovpworld.org", "peripheral", "iMX6_GPC", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetInputPort irq32;
    tlmNetInputPort irq33;
    tlmNetInputPort irq34;
    tlmNetInputPort irq35;
    tlmNetInputPort irq36;
    tlmNetInputPort irq37;
    tlmNetInputPort irq38;
    tlmNetInputPort irq39;
    tlmNetInputPort irq40;
    tlmNetInputPort irq41;
    tlmNetInputPort irq42;
    tlmNetInputPort irq43;
    tlmNetInputPort irq44;
    tlmNetInputPort irq45;
    tlmNetInputPort irq46;
    tlmNetInputPort irq47;
    tlmNetInputPort irq48;
    tlmNetInputPort irq49;
    tlmNetInputPort irq50;
    tlmNetInputPort irq51;
    tlmNetInputPort irq52;
    tlmNetInputPort irq53;
    tlmNetInputPort irq54;
    tlmNetInputPort irq55;
    tlmNetInputPort irq56;
    tlmNetInputPort irq57;
    tlmNetInputPort irq58;
    tlmNetInputPort irq59;
    tlmNetInputPort irq60;
    tlmNetInputPort irq61;
    tlmNetInputPort irq62;
    tlmNetInputPort irq63;
    tlmNetInputPort irq64;
    tlmNetInputPort irq65;
    tlmNetInputPort irq66;
    tlmNetInputPort irq67;
    tlmNetInputPort irq68;
    tlmNetInputPort irq69;
    tlmNetInputPort irq70;
    tlmNetInputPort irq71;
    tlmNetInputPort irq72;
    tlmNetInputPort irq73;
    tlmNetInputPort irq74;
    tlmNetInputPort irq75;
    tlmNetInputPort irq76;
    tlmNetInputPort irq77;
    tlmNetInputPort irq78;
    tlmNetInputPort irq79;
    tlmNetInputPort irq80;
    tlmNetInputPort irq81;
    tlmNetInputPort irq82;
    tlmNetInputPort irq83;
    tlmNetInputPort irq84;
    tlmNetInputPort irq85;
    tlmNetInputPort irq86;
    tlmNetInputPort irq87;
    tlmNetInputPort irq88;
    tlmNetInputPort irq89;
    tlmNetInputPort irq90;
    tlmNetInputPort irq91;
    tlmNetInputPort irq92;
    tlmNetInputPort irq93;
    tlmNetInputPort irq94;
    tlmNetInputPort irq95;
    tlmNetInputPort irq96;
    tlmNetInputPort irq97;
    tlmNetInputPort irq98;
    tlmNetInputPort irq99;
    tlmNetInputPort irq100;
    tlmNetInputPort irq101;
    tlmNetInputPort irq102;
    tlmNetInputPort irq103;
    tlmNetInputPort irq104;
    tlmNetInputPort irq105;
    tlmNetInputPort irq106;
    tlmNetInputPort irq107;
    tlmNetInputPort irq108;
    tlmNetInputPort irq109;
    tlmNetInputPort irq110;
    tlmNetInputPort irq111;
    tlmNetInputPort irq112;
    tlmNetInputPort irq113;
    tlmNetInputPort irq114;
    tlmNetInputPort irq115;
    tlmNetInputPort irq116;
    tlmNetInputPort irq117;
    tlmNetInputPort irq118;
    tlmNetInputPort irq119;
    tlmNetInputPort irq120;
    tlmNetInputPort irq121;
    tlmNetInputPort irq122;
    tlmNetInputPort irq123;
    tlmNetInputPort irq124;
    tlmNetInputPort irq125;
    tlmNetInputPort irq126;
    tlmNetInputPort irq127;
    tlmNetInputPort irq128;
    tlmNetInputPort irq129;
    tlmNetInputPort irq130;
    tlmNetInputPort irq131;
    tlmNetInputPort irq132;
    tlmNetInputPort irq133;
    tlmNetInputPort irq134;
    tlmNetInputPort irq135;
    tlmNetInputPort irq136;
    tlmNetInputPort irq137;
    tlmNetInputPort irq138;
    tlmNetInputPort irq139;
    tlmNetInputPort irq140;
    tlmNetInputPort irq141;
    tlmNetInputPort irq142;
    tlmNetInputPort irq143;
    tlmNetInputPort irq144;
    tlmNetInputPort irq145;
    tlmNetInputPort irq146;
    tlmNetInputPort irq147;
    tlmNetInputPort irq148;
    tlmNetInputPort irq149;
    tlmNetInputPort irq150;
    tlmNetInputPort irq151;
    tlmNetInputPort irq152;
    tlmNetInputPort irq153;
    tlmNetInputPort irq154;
    tlmNetInputPort irq155;
    tlmNetInputPort irq156;
    tlmNetInputPort irq157;
    tlmNetInputPort irq158;
    tlmNetInputPort irq159;

    iMX6_GPC(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x260) // static
        , irq32(parent, this, "irq32")
        , irq33(parent, this, "irq33")
        , irq34(parent, this, "irq34")
        , irq35(parent, this, "irq35")
        , irq36(parent, this, "irq36")
        , irq37(parent, this, "irq37")
        , irq38(parent, this, "irq38")
        , irq39(parent, this, "irq39")
        , irq40(parent, this, "irq40")
        , irq41(parent, this, "irq41")
        , irq42(parent, this, "irq42")
        , irq43(parent, this, "irq43")
        , irq44(parent, this, "irq44")
        , irq45(parent, this, "irq45")
        , irq46(parent, this, "irq46")
        , irq47(parent, this, "irq47")
        , irq48(parent, this, "irq48")
        , irq49(parent, this, "irq49")
        , irq50(parent, this, "irq50")
        , irq51(parent, this, "irq51")
        , irq52(parent, this, "irq52")
        , irq53(parent, this, "irq53")
        , irq54(parent, this, "irq54")
        , irq55(parent, this, "irq55")
        , irq56(parent, this, "irq56")
        , irq57(parent, this, "irq57")
        , irq58(parent, this, "irq58")
        , irq59(parent, this, "irq59")
        , irq60(parent, this, "irq60")
        , irq61(parent, this, "irq61")
        , irq62(parent, this, "irq62")
        , irq63(parent, this, "irq63")
        , irq64(parent, this, "irq64")
        , irq65(parent, this, "irq65")
        , irq66(parent, this, "irq66")
        , irq67(parent, this, "irq67")
        , irq68(parent, this, "irq68")
        , irq69(parent, this, "irq69")
        , irq70(parent, this, "irq70")
        , irq71(parent, this, "irq71")
        , irq72(parent, this, "irq72")
        , irq73(parent, this, "irq73")
        , irq74(parent, this, "irq74")
        , irq75(parent, this, "irq75")
        , irq76(parent, this, "irq76")
        , irq77(parent, this, "irq77")
        , irq78(parent, this, "irq78")
        , irq79(parent, this, "irq79")
        , irq80(parent, this, "irq80")
        , irq81(parent, this, "irq81")
        , irq82(parent, this, "irq82")
        , irq83(parent, this, "irq83")
        , irq84(parent, this, "irq84")
        , irq85(parent, this, "irq85")
        , irq86(parent, this, "irq86")
        , irq87(parent, this, "irq87")
        , irq88(parent, this, "irq88")
        , irq89(parent, this, "irq89")
        , irq90(parent, this, "irq90")
        , irq91(parent, this, "irq91")
        , irq92(parent, this, "irq92")
        , irq93(parent, this, "irq93")
        , irq94(parent, this, "irq94")
        , irq95(parent, this, "irq95")
        , irq96(parent, this, "irq96")
        , irq97(parent, this, "irq97")
        , irq98(parent, this, "irq98")
        , irq99(parent, this, "irq99")
        , irq100(parent, this, "irq100")
        , irq101(parent, this, "irq101")
        , irq102(parent, this, "irq102")
        , irq103(parent, this, "irq103")
        , irq104(parent, this, "irq104")
        , irq105(parent, this, "irq105")
        , irq106(parent, this, "irq106")
        , irq107(parent, this, "irq107")
        , irq108(parent, this, "irq108")
        , irq109(parent, this, "irq109")
        , irq110(parent, this, "irq110")
        , irq111(parent, this, "irq111")
        , irq112(parent, this, "irq112")
        , irq113(parent, this, "irq113")
        , irq114(parent, this, "irq114")
        , irq115(parent, this, "irq115")
        , irq116(parent, this, "irq116")
        , irq117(parent, this, "irq117")
        , irq118(parent, this, "irq118")
        , irq119(parent, this, "irq119")
        , irq120(parent, this, "irq120")
        , irq121(parent, this, "irq121")
        , irq122(parent, this, "irq122")
        , irq123(parent, this, "irq123")
        , irq124(parent, this, "irq124")
        , irq125(parent, this, "irq125")
        , irq126(parent, this, "irq126")
        , irq127(parent, this, "irq127")
        , irq128(parent, this, "irq128")
        , irq129(parent, this, "irq129")
        , irq130(parent, this, "irq130")
        , irq131(parent, this, "irq131")
        , irq132(parent, this, "irq132")
        , irq133(parent, this, "irq133")
        , irq134(parent, this, "irq134")
        , irq135(parent, this, "irq135")
        , irq136(parent, this, "irq136")
        , irq137(parent, this, "irq137")
        , irq138(parent, this, "irq138")
        , irq139(parent, this, "irq139")
        , irq140(parent, this, "irq140")
        , irq141(parent, this, "irq141")
        , irq142(parent, this, "irq142")
        , irq143(parent, this, "irq143")
        , irq144(parent, this, "irq144")
        , irq145(parent, this, "irq145")
        , irq146(parent, this, "irq146")
        , irq147(parent, this, "irq147")
        , irq148(parent, this, "irq148")
        , irq149(parent, this, "irq149")
        , irq150(parent, this, "irq150")
        , irq151(parent, this, "irq151")
        , irq152(parent, this, "irq152")
        , irq153(parent, this, "irq153")
        , irq154(parent, this, "irq154")
        , irq155(parent, this, "irq155")
        , irq156(parent, this, "irq156")
        , irq157(parent, this, "irq157")
        , irq158(parent, this, "irq158")
        , irq159(parent, this, "irq159")
    {
    }

    iMX6_GPC(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x260) // static
        , irq32(parent, this, "irq32")
        , irq33(parent, this, "irq33")
        , irq34(parent, this, "irq34")
        , irq35(parent, this, "irq35")
        , irq36(parent, this, "irq36")
        , irq37(parent, this, "irq37")
        , irq38(parent, this, "irq38")
        , irq39(parent, this, "irq39")
        , irq40(parent, this, "irq40")
        , irq41(parent, this, "irq41")
        , irq42(parent, this, "irq42")
        , irq43(parent, this, "irq43")
        , irq44(parent, this, "irq44")
        , irq45(parent, this, "irq45")
        , irq46(parent, this, "irq46")
        , irq47(parent, this, "irq47")
        , irq48(parent, this, "irq48")
        , irq49(parent, this, "irq49")
        , irq50(parent, this, "irq50")
        , irq51(parent, this, "irq51")
        , irq52(parent, this, "irq52")
        , irq53(parent, this, "irq53")
        , irq54(parent, this, "irq54")
        , irq55(parent, this, "irq55")
        , irq56(parent, this, "irq56")
        , irq57(parent, this, "irq57")
        , irq58(parent, this, "irq58")
        , irq59(parent, this, "irq59")
        , irq60(parent, this, "irq60")
        , irq61(parent, this, "irq61")
        , irq62(parent, this, "irq62")
        , irq63(parent, this, "irq63")
        , irq64(parent, this, "irq64")
        , irq65(parent, this, "irq65")
        , irq66(parent, this, "irq66")
        , irq67(parent, this, "irq67")
        , irq68(parent, this, "irq68")
        , irq69(parent, this, "irq69")
        , irq70(parent, this, "irq70")
        , irq71(parent, this, "irq71")
        , irq72(parent, this, "irq72")
        , irq73(parent, this, "irq73")
        , irq74(parent, this, "irq74")
        , irq75(parent, this, "irq75")
        , irq76(parent, this, "irq76")
        , irq77(parent, this, "irq77")
        , irq78(parent, this, "irq78")
        , irq79(parent, this, "irq79")
        , irq80(parent, this, "irq80")
        , irq81(parent, this, "irq81")
        , irq82(parent, this, "irq82")
        , irq83(parent, this, "irq83")
        , irq84(parent, this, "irq84")
        , irq85(parent, this, "irq85")
        , irq86(parent, this, "irq86")
        , irq87(parent, this, "irq87")
        , irq88(parent, this, "irq88")
        , irq89(parent, this, "irq89")
        , irq90(parent, this, "irq90")
        , irq91(parent, this, "irq91")
        , irq92(parent, this, "irq92")
        , irq93(parent, this, "irq93")
        , irq94(parent, this, "irq94")
        , irq95(parent, this, "irq95")
        , irq96(parent, this, "irq96")
        , irq97(parent, this, "irq97")
        , irq98(parent, this, "irq98")
        , irq99(parent, this, "irq99")
        , irq100(parent, this, "irq100")
        , irq101(parent, this, "irq101")
        , irq102(parent, this, "irq102")
        , irq103(parent, this, "irq103")
        , irq104(parent, this, "irq104")
        , irq105(parent, this, "irq105")
        , irq106(parent, this, "irq106")
        , irq107(parent, this, "irq107")
        , irq108(parent, this, "irq108")
        , irq109(parent, this, "irq109")
        , irq110(parent, this, "irq110")
        , irq111(parent, this, "irq111")
        , irq112(parent, this, "irq112")
        , irq113(parent, this, "irq113")
        , irq114(parent, this, "irq114")
        , irq115(parent, this, "irq115")
        , irq116(parent, this, "irq116")
        , irq117(parent, this, "irq117")
        , irq118(parent, this, "irq118")
        , irq119(parent, this, "irq119")
        , irq120(parent, this, "irq120")
        , irq121(parent, this, "irq121")
        , irq122(parent, this, "irq122")
        , irq123(parent, this, "irq123")
        , irq124(parent, this, "irq124")
        , irq125(parent, this, "irq125")
        , irq126(parent, this, "irq126")
        , irq127(parent, this, "irq127")
        , irq128(parent, this, "irq128")
        , irq129(parent, this, "irq129")
        , irq130(parent, this, "irq130")
        , irq131(parent, this, "irq131")
        , irq132(parent, this, "irq132")
        , irq133(parent, this, "irq133")
        , irq134(parent, this, "irq134")
        , irq135(parent, this, "irq135")
        , irq136(parent, this, "irq136")
        , irq137(parent, this, "irq137")
        , irq138(parent, this, "irq138")
        , irq139(parent, this, "irq139")
        , irq140(parent, this, "irq140")
        , irq141(parent, this, "irq141")
        , irq142(parent, this, "irq142")
        , irq143(parent, this, "irq143")
        , irq144(parent, this, "irq144")
        , irq145(parent, this, "irq145")
        , irq146(parent, this, "irq146")
        , irq147(parent, this, "irq147")
        , irq148(parent, this, "irq148")
        , irq149(parent, this, "irq149")
        , irq150(parent, this, "irq150")
        , irq151(parent, this, "irq151")
        , irq152(parent, this, "irq152")
        , irq153(parent, this, "irq153")
        , irq154(parent, this, "irq154")
        , irq155(parent, this, "irq155")
        , irq156(parent, this, "irq156")
        , irq157(parent, this, "irq157")
        , irq158(parent, this, "irq158")
        , irq159(parent, this, "irq159")
    {
    }

}; /* class iMX6_GPC */


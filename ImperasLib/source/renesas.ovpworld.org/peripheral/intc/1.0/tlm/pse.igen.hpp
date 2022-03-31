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
//    Slave Port INTCP0
//    Net output  RESET;
//    Net output  NMI0;
//    Net output  NMI1;
//    Net output  NMI2;
//    Net output  INTP;
//    Net input  INTACK;
//    Net input  MIRETI;
//    Net input  IRESET;
//    Net input  NMI_00;
//    Net input  NMI_01;
//    Net input  NMI_02;
//    Net input  NMI_03;
//    Net input  NMI_04;
//    Net input  NMI_05;
//    Net input  NMI_06;
//    Net input  NMI_07;
//    Net input  NMI_08;
//    Net input  NMI_09;
//    Net input  NMI_10;
//    Net input  NMI_11;
//    Net input  NMI_12;
//    Net input  NMI_13;
//    Net input  NMI_14;
//    Net input  NMI_15;
//    Net input  NMI_16;
//    Net input  NMI_17;
//    Net input  NMI_18;
//    Net input  NMI_19;
//    Net input  NMI_20;
//    Net input  NMI_21;
//    Net input  NMI_22;
//    Net input  NMI_23;
//    Net input  NMI_24;
//    Net input  NMI_25;
//    Net input  NMI_26;
//    Net input  NMI_27;
//    Net input  NMI_28;
//    Net input  NMI_29;
//    Net input  NMI_30;
//    Net input  NMI_31;
//    Net input  NMI_32;
//    Net input  NMI_33;
//    Net input  NMI_34;
//    Net input  NMI_35;
//    Net input  NMI_36;
//    Net input  NMI_37;
//    Net input  NMI_38;
//    Net input  NMI_39;
//    Net input  NMI_40;
//    Net input  NMI_41;
//    Net input  NMI_42;
//    Net input  NMI_43;
//    Net input  NMI_44;
//    Net input  NMI_45;
//    Net input  NMI_46;
//    Net input  NMI_47;
//    Net input  NMI_48;
//    Net input  NMI_49;
//    Net input  NMI_50;
//    Net input  NMI_51;
//    Net input  NMI_52;
//    Net input  NMI_53;
//    Net input  NMI_54;
//    Net input  NMI_55;
//    Net input  NMI_56;
//    Net input  NMI_57;
//    Net input  NMI_58;
//    Net input  NMI_59;
//    Net input  NMI_60;
//    Net input  NMI_61;
//    Net input  NMI_62;
//    Net input  NMI_63;
//    Net input  INT_00;
//    Net input  INT_01;
//    Net input  INT_02;
//    Net input  INT_03;
//    Net input  INT_04;
//    Net input  INT_05;
//    Net input  INT_06;
//    Net input  INT_07;
//    Net input  INT_08;
//    Net input  INT_09;
//    Net input  INT_10;
//    Net input  INT_11;
//    Net input  INT_12;
//    Net input  INT_13;
//    Net input  INT_14;
//    Net input  INT_15;
//    Net input  INT_16;
//    Net input  INT_17;
//    Net input  INT_18;
//    Net input  INT_19;
//    Net input  INT_20;
//    Net input  INT_21;
//    Net input  INT_22;
//    Net input  INT_23;
//    Net input  INT_24;
//    Net input  INT_25;
//    Net input  INT_26;
//    Net input  INT_27;
//    Net input  INT_28;
//    Net input  INT_29;
//    Net input  INT_30;
//    Net input  INT_31;
//    Net input  INT_32;
//    Net input  INT_33;
//    Net input  INT_34;
//    Net input  INT_35;
//    Net input  INT_36;
//    Net input  INT_37;
//    Net input  INT_38;
//    Net input  INT_39;
//    Net input  INT_40;
//    Net input  INT_41;
//    Net input  INT_42;
//    Net input  INT_43;
//    Net input  INT_44;
//    Net input  INT_45;
//    Net input  INT_46;
//    Net input  INT_47;
//    Net input  INT_48;
//    Net input  INT_49;
//    Net input  INT_50;
//    Net input  INT_51;
//    Net input  INT_52;
//    Net input  INT_53;
//    Net input  INT_54;
//    Net input  INT_55;
//    Net input  INT_56;
//    Net input  INT_57;
//    Net input  INT_58;
//    Net input  INT_59;
//    Net input  INT_60;
//    Net input  INT_61;
//    Net input  INT_62;
//    Net input  INT_63;
//    Net input  INT_64;
//    Net input  INT_65;
//    Net input  INT_66;
//    Net input  INT_67;
//    Net input  INT_68;
//    Net input  INT_69;
//    Net input  INT_70;
//    Net input  INT_71;
//    Net input  INT_72;
//    Net input  INT_73;
//    Net input  INT_74;
//    Net input  INT_75;
//    Net input  INT_76;
//    Net input  INT_77;
//    Net input  INT_78;
//    Net input  INT_79;
//    Net input  INT_80;
//    Net input  INT_81;
//    Net input  INT_82;
//    Net input  INT_83;
//    Net input  INT_84;
//    Net input  INT_85;
//    Net input  INT_86;
//    Net input  INT_87;
//    Net input  INT_88;
//    Net input  INT_89;
//    Net input  INT_90;
//    Net input  INT_91;
//    Net input  INT_92;
//    Net input  INT_93;
//    Net input  INT_94;
//    Net input  INT_95;
//    Net input  INT_96;
//    Net input  INT_97;
//    Net input  INT_98;
//    Net input  INT_99;
//    Net input  INT_100;
//    Net input  INT_101;
//    Net input  INT_102;
//    Net input  INT_103;
//    Net input  INT_104;
//    Net input  INT_105;
//    Net input  INT_106;
//    Net input  INT_107;
//    Net input  INT_108;
//    Net input  INT_109;
//    Net input  INT_110;
//    Net input  INT_111;
//    Net input  INT_112;
//    Net input  INT_113;
//    Net input  INT_114;
//    Net input  INT_115;
//    Net input  INT_116;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class intc : public tlmPeripheral
{
  private:
    const char *getModel() {
        return opVLNVString (NULL, "renesas.ovpworld.org", "peripheral", "intc", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

  public:
    tlmBusSlavePort INTCP0;
    tlmNetOutputPort RESET;
    tlmNetOutputPort NMI0;
    tlmNetOutputPort NMI1;
    tlmNetOutputPort NMI2;
    tlmNetOutputPort INTP;
    tlmNetInputPort INTACK;
    tlmNetInputPort MIRETI;
    tlmNetInputPort IRESET;
    tlmNetInputPort NMI_00;
    tlmNetInputPort NMI_01;
    tlmNetInputPort NMI_02;
    tlmNetInputPort NMI_03;
    tlmNetInputPort NMI_04;
    tlmNetInputPort NMI_05;
    tlmNetInputPort NMI_06;
    tlmNetInputPort NMI_07;
    tlmNetInputPort NMI_08;
    tlmNetInputPort NMI_09;
    tlmNetInputPort NMI_10;
    tlmNetInputPort NMI_11;
    tlmNetInputPort NMI_12;
    tlmNetInputPort NMI_13;
    tlmNetInputPort NMI_14;
    tlmNetInputPort NMI_15;
    tlmNetInputPort NMI_16;
    tlmNetInputPort NMI_17;
    tlmNetInputPort NMI_18;
    tlmNetInputPort NMI_19;
    tlmNetInputPort NMI_20;
    tlmNetInputPort NMI_21;
    tlmNetInputPort NMI_22;
    tlmNetInputPort NMI_23;
    tlmNetInputPort NMI_24;
    tlmNetInputPort NMI_25;
    tlmNetInputPort NMI_26;
    tlmNetInputPort NMI_27;
    tlmNetInputPort NMI_28;
    tlmNetInputPort NMI_29;
    tlmNetInputPort NMI_30;
    tlmNetInputPort NMI_31;
    tlmNetInputPort NMI_32;
    tlmNetInputPort NMI_33;
    tlmNetInputPort NMI_34;
    tlmNetInputPort NMI_35;
    tlmNetInputPort NMI_36;
    tlmNetInputPort NMI_37;
    tlmNetInputPort NMI_38;
    tlmNetInputPort NMI_39;
    tlmNetInputPort NMI_40;
    tlmNetInputPort NMI_41;
    tlmNetInputPort NMI_42;
    tlmNetInputPort NMI_43;
    tlmNetInputPort NMI_44;
    tlmNetInputPort NMI_45;
    tlmNetInputPort NMI_46;
    tlmNetInputPort NMI_47;
    tlmNetInputPort NMI_48;
    tlmNetInputPort NMI_49;
    tlmNetInputPort NMI_50;
    tlmNetInputPort NMI_51;
    tlmNetInputPort NMI_52;
    tlmNetInputPort NMI_53;
    tlmNetInputPort NMI_54;
    tlmNetInputPort NMI_55;
    tlmNetInputPort NMI_56;
    tlmNetInputPort NMI_57;
    tlmNetInputPort NMI_58;
    tlmNetInputPort NMI_59;
    tlmNetInputPort NMI_60;
    tlmNetInputPort NMI_61;
    tlmNetInputPort NMI_62;
    tlmNetInputPort NMI_63;
    tlmNetInputPort INT_00;
    tlmNetInputPort INT_01;
    tlmNetInputPort INT_02;
    tlmNetInputPort INT_03;
    tlmNetInputPort INT_04;
    tlmNetInputPort INT_05;
    tlmNetInputPort INT_06;
    tlmNetInputPort INT_07;
    tlmNetInputPort INT_08;
    tlmNetInputPort INT_09;
    tlmNetInputPort INT_10;
    tlmNetInputPort INT_11;
    tlmNetInputPort INT_12;
    tlmNetInputPort INT_13;
    tlmNetInputPort INT_14;
    tlmNetInputPort INT_15;
    tlmNetInputPort INT_16;
    tlmNetInputPort INT_17;
    tlmNetInputPort INT_18;
    tlmNetInputPort INT_19;
    tlmNetInputPort INT_20;
    tlmNetInputPort INT_21;
    tlmNetInputPort INT_22;
    tlmNetInputPort INT_23;
    tlmNetInputPort INT_24;
    tlmNetInputPort INT_25;
    tlmNetInputPort INT_26;
    tlmNetInputPort INT_27;
    tlmNetInputPort INT_28;
    tlmNetInputPort INT_29;
    tlmNetInputPort INT_30;
    tlmNetInputPort INT_31;
    tlmNetInputPort INT_32;
    tlmNetInputPort INT_33;
    tlmNetInputPort INT_34;
    tlmNetInputPort INT_35;
    tlmNetInputPort INT_36;
    tlmNetInputPort INT_37;
    tlmNetInputPort INT_38;
    tlmNetInputPort INT_39;
    tlmNetInputPort INT_40;
    tlmNetInputPort INT_41;
    tlmNetInputPort INT_42;
    tlmNetInputPort INT_43;
    tlmNetInputPort INT_44;
    tlmNetInputPort INT_45;
    tlmNetInputPort INT_46;
    tlmNetInputPort INT_47;
    tlmNetInputPort INT_48;
    tlmNetInputPort INT_49;
    tlmNetInputPort INT_50;
    tlmNetInputPort INT_51;
    tlmNetInputPort INT_52;
    tlmNetInputPort INT_53;
    tlmNetInputPort INT_54;
    tlmNetInputPort INT_55;
    tlmNetInputPort INT_56;
    tlmNetInputPort INT_57;
    tlmNetInputPort INT_58;
    tlmNetInputPort INT_59;
    tlmNetInputPort INT_60;
    tlmNetInputPort INT_61;
    tlmNetInputPort INT_62;
    tlmNetInputPort INT_63;
    tlmNetInputPort INT_64;
    tlmNetInputPort INT_65;
    tlmNetInputPort INT_66;
    tlmNetInputPort INT_67;
    tlmNetInputPort INT_68;
    tlmNetInputPort INT_69;
    tlmNetInputPort INT_70;
    tlmNetInputPort INT_71;
    tlmNetInputPort INT_72;
    tlmNetInputPort INT_73;
    tlmNetInputPort INT_74;
    tlmNetInputPort INT_75;
    tlmNetInputPort INT_76;
    tlmNetInputPort INT_77;
    tlmNetInputPort INT_78;
    tlmNetInputPort INT_79;
    tlmNetInputPort INT_80;
    tlmNetInputPort INT_81;
    tlmNetInputPort INT_82;
    tlmNetInputPort INT_83;
    tlmNetInputPort INT_84;
    tlmNetInputPort INT_85;
    tlmNetInputPort INT_86;
    tlmNetInputPort INT_87;
    tlmNetInputPort INT_88;
    tlmNetInputPort INT_89;
    tlmNetInputPort INT_90;
    tlmNetInputPort INT_91;
    tlmNetInputPort INT_92;
    tlmNetInputPort INT_93;
    tlmNetInputPort INT_94;
    tlmNetInputPort INT_95;
    tlmNetInputPort INT_96;
    tlmNetInputPort INT_97;
    tlmNetInputPort INT_98;
    tlmNetInputPort INT_99;
    tlmNetInputPort INT_100;
    tlmNetInputPort INT_101;
    tlmNetInputPort INT_102;
    tlmNetInputPort INT_103;
    tlmNetInputPort INT_104;
    tlmNetInputPort INT_105;
    tlmNetInputPort INT_106;
    tlmNetInputPort INT_107;
    tlmNetInputPort INT_108;
    tlmNetInputPort INT_109;
    tlmNetInputPort INT_110;
    tlmNetInputPort INT_111;
    tlmNetInputPort INT_112;
    tlmNetInputPort INT_113;
    tlmNetInputPort INT_114;
    tlmNetInputPort INT_115;
    tlmNetInputPort INT_116;

    intc(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , INTCP0(parent, this, "INTCP0", 0xfc) // static
        , RESET(parent, this, "RESET")
        , NMI0(parent, this, "NMI0")
        , NMI1(parent, this, "NMI1")
        , NMI2(parent, this, "NMI2")
        , INTP(parent, this, "INTP")
        , INTACK(parent, this, "INTACK")
        , MIRETI(parent, this, "MIRETI")
        , IRESET(parent, this, "IRESET")
        , NMI_00(parent, this, "NMI_00")
        , NMI_01(parent, this, "NMI_01")
        , NMI_02(parent, this, "NMI_02")
        , NMI_03(parent, this, "NMI_03")
        , NMI_04(parent, this, "NMI_04")
        , NMI_05(parent, this, "NMI_05")
        , NMI_06(parent, this, "NMI_06")
        , NMI_07(parent, this, "NMI_07")
        , NMI_08(parent, this, "NMI_08")
        , NMI_09(parent, this, "NMI_09")
        , NMI_10(parent, this, "NMI_10")
        , NMI_11(parent, this, "NMI_11")
        , NMI_12(parent, this, "NMI_12")
        , NMI_13(parent, this, "NMI_13")
        , NMI_14(parent, this, "NMI_14")
        , NMI_15(parent, this, "NMI_15")
        , NMI_16(parent, this, "NMI_16")
        , NMI_17(parent, this, "NMI_17")
        , NMI_18(parent, this, "NMI_18")
        , NMI_19(parent, this, "NMI_19")
        , NMI_20(parent, this, "NMI_20")
        , NMI_21(parent, this, "NMI_21")
        , NMI_22(parent, this, "NMI_22")
        , NMI_23(parent, this, "NMI_23")
        , NMI_24(parent, this, "NMI_24")
        , NMI_25(parent, this, "NMI_25")
        , NMI_26(parent, this, "NMI_26")
        , NMI_27(parent, this, "NMI_27")
        , NMI_28(parent, this, "NMI_28")
        , NMI_29(parent, this, "NMI_29")
        , NMI_30(parent, this, "NMI_30")
        , NMI_31(parent, this, "NMI_31")
        , NMI_32(parent, this, "NMI_32")
        , NMI_33(parent, this, "NMI_33")
        , NMI_34(parent, this, "NMI_34")
        , NMI_35(parent, this, "NMI_35")
        , NMI_36(parent, this, "NMI_36")
        , NMI_37(parent, this, "NMI_37")
        , NMI_38(parent, this, "NMI_38")
        , NMI_39(parent, this, "NMI_39")
        , NMI_40(parent, this, "NMI_40")
        , NMI_41(parent, this, "NMI_41")
        , NMI_42(parent, this, "NMI_42")
        , NMI_43(parent, this, "NMI_43")
        , NMI_44(parent, this, "NMI_44")
        , NMI_45(parent, this, "NMI_45")
        , NMI_46(parent, this, "NMI_46")
        , NMI_47(parent, this, "NMI_47")
        , NMI_48(parent, this, "NMI_48")
        , NMI_49(parent, this, "NMI_49")
        , NMI_50(parent, this, "NMI_50")
        , NMI_51(parent, this, "NMI_51")
        , NMI_52(parent, this, "NMI_52")
        , NMI_53(parent, this, "NMI_53")
        , NMI_54(parent, this, "NMI_54")
        , NMI_55(parent, this, "NMI_55")
        , NMI_56(parent, this, "NMI_56")
        , NMI_57(parent, this, "NMI_57")
        , NMI_58(parent, this, "NMI_58")
        , NMI_59(parent, this, "NMI_59")
        , NMI_60(parent, this, "NMI_60")
        , NMI_61(parent, this, "NMI_61")
        , NMI_62(parent, this, "NMI_62")
        , NMI_63(parent, this, "NMI_63")
        , INT_00(parent, this, "INT_00")
        , INT_01(parent, this, "INT_01")
        , INT_02(parent, this, "INT_02")
        , INT_03(parent, this, "INT_03")
        , INT_04(parent, this, "INT_04")
        , INT_05(parent, this, "INT_05")
        , INT_06(parent, this, "INT_06")
        , INT_07(parent, this, "INT_07")
        , INT_08(parent, this, "INT_08")
        , INT_09(parent, this, "INT_09")
        , INT_10(parent, this, "INT_10")
        , INT_11(parent, this, "INT_11")
        , INT_12(parent, this, "INT_12")
        , INT_13(parent, this, "INT_13")
        , INT_14(parent, this, "INT_14")
        , INT_15(parent, this, "INT_15")
        , INT_16(parent, this, "INT_16")
        , INT_17(parent, this, "INT_17")
        , INT_18(parent, this, "INT_18")
        , INT_19(parent, this, "INT_19")
        , INT_20(parent, this, "INT_20")
        , INT_21(parent, this, "INT_21")
        , INT_22(parent, this, "INT_22")
        , INT_23(parent, this, "INT_23")
        , INT_24(parent, this, "INT_24")
        , INT_25(parent, this, "INT_25")
        , INT_26(parent, this, "INT_26")
        , INT_27(parent, this, "INT_27")
        , INT_28(parent, this, "INT_28")
        , INT_29(parent, this, "INT_29")
        , INT_30(parent, this, "INT_30")
        , INT_31(parent, this, "INT_31")
        , INT_32(parent, this, "INT_32")
        , INT_33(parent, this, "INT_33")
        , INT_34(parent, this, "INT_34")
        , INT_35(parent, this, "INT_35")
        , INT_36(parent, this, "INT_36")
        , INT_37(parent, this, "INT_37")
        , INT_38(parent, this, "INT_38")
        , INT_39(parent, this, "INT_39")
        , INT_40(parent, this, "INT_40")
        , INT_41(parent, this, "INT_41")
        , INT_42(parent, this, "INT_42")
        , INT_43(parent, this, "INT_43")
        , INT_44(parent, this, "INT_44")
        , INT_45(parent, this, "INT_45")
        , INT_46(parent, this, "INT_46")
        , INT_47(parent, this, "INT_47")
        , INT_48(parent, this, "INT_48")
        , INT_49(parent, this, "INT_49")
        , INT_50(parent, this, "INT_50")
        , INT_51(parent, this, "INT_51")
        , INT_52(parent, this, "INT_52")
        , INT_53(parent, this, "INT_53")
        , INT_54(parent, this, "INT_54")
        , INT_55(parent, this, "INT_55")
        , INT_56(parent, this, "INT_56")
        , INT_57(parent, this, "INT_57")
        , INT_58(parent, this, "INT_58")
        , INT_59(parent, this, "INT_59")
        , INT_60(parent, this, "INT_60")
        , INT_61(parent, this, "INT_61")
        , INT_62(parent, this, "INT_62")
        , INT_63(parent, this, "INT_63")
        , INT_64(parent, this, "INT_64")
        , INT_65(parent, this, "INT_65")
        , INT_66(parent, this, "INT_66")
        , INT_67(parent, this, "INT_67")
        , INT_68(parent, this, "INT_68")
        , INT_69(parent, this, "INT_69")
        , INT_70(parent, this, "INT_70")
        , INT_71(parent, this, "INT_71")
        , INT_72(parent, this, "INT_72")
        , INT_73(parent, this, "INT_73")
        , INT_74(parent, this, "INT_74")
        , INT_75(parent, this, "INT_75")
        , INT_76(parent, this, "INT_76")
        , INT_77(parent, this, "INT_77")
        , INT_78(parent, this, "INT_78")
        , INT_79(parent, this, "INT_79")
        , INT_80(parent, this, "INT_80")
        , INT_81(parent, this, "INT_81")
        , INT_82(parent, this, "INT_82")
        , INT_83(parent, this, "INT_83")
        , INT_84(parent, this, "INT_84")
        , INT_85(parent, this, "INT_85")
        , INT_86(parent, this, "INT_86")
        , INT_87(parent, this, "INT_87")
        , INT_88(parent, this, "INT_88")
        , INT_89(parent, this, "INT_89")
        , INT_90(parent, this, "INT_90")
        , INT_91(parent, this, "INT_91")
        , INT_92(parent, this, "INT_92")
        , INT_93(parent, this, "INT_93")
        , INT_94(parent, this, "INT_94")
        , INT_95(parent, this, "INT_95")
        , INT_96(parent, this, "INT_96")
        , INT_97(parent, this, "INT_97")
        , INT_98(parent, this, "INT_98")
        , INT_99(parent, this, "INT_99")
        , INT_100(parent, this, "INT_100")
        , INT_101(parent, this, "INT_101")
        , INT_102(parent, this, "INT_102")
        , INT_103(parent, this, "INT_103")
        , INT_104(parent, this, "INT_104")
        , INT_105(parent, this, "INT_105")
        , INT_106(parent, this, "INT_106")
        , INT_107(parent, this, "INT_107")
        , INT_108(parent, this, "INT_108")
        , INT_109(parent, this, "INT_109")
        , INT_110(parent, this, "INT_110")
        , INT_111(parent, this, "INT_111")
        , INT_112(parent, this, "INT_112")
        , INT_113(parent, this, "INT_113")
        , INT_114(parent, this, "INT_114")
        , INT_115(parent, this, "INT_115")
        , INT_116(parent, this, "INT_116")
    {
    }

    intc(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , INTCP0(parent, this, "INTCP0", 0xfc) // static
        , RESET(parent, this, "RESET")
        , NMI0(parent, this, "NMI0")
        , NMI1(parent, this, "NMI1")
        , NMI2(parent, this, "NMI2")
        , INTP(parent, this, "INTP")
        , INTACK(parent, this, "INTACK")
        , MIRETI(parent, this, "MIRETI")
        , IRESET(parent, this, "IRESET")
        , NMI_00(parent, this, "NMI_00")
        , NMI_01(parent, this, "NMI_01")
        , NMI_02(parent, this, "NMI_02")
        , NMI_03(parent, this, "NMI_03")
        , NMI_04(parent, this, "NMI_04")
        , NMI_05(parent, this, "NMI_05")
        , NMI_06(parent, this, "NMI_06")
        , NMI_07(parent, this, "NMI_07")
        , NMI_08(parent, this, "NMI_08")
        , NMI_09(parent, this, "NMI_09")
        , NMI_10(parent, this, "NMI_10")
        , NMI_11(parent, this, "NMI_11")
        , NMI_12(parent, this, "NMI_12")
        , NMI_13(parent, this, "NMI_13")
        , NMI_14(parent, this, "NMI_14")
        , NMI_15(parent, this, "NMI_15")
        , NMI_16(parent, this, "NMI_16")
        , NMI_17(parent, this, "NMI_17")
        , NMI_18(parent, this, "NMI_18")
        , NMI_19(parent, this, "NMI_19")
        , NMI_20(parent, this, "NMI_20")
        , NMI_21(parent, this, "NMI_21")
        , NMI_22(parent, this, "NMI_22")
        , NMI_23(parent, this, "NMI_23")
        , NMI_24(parent, this, "NMI_24")
        , NMI_25(parent, this, "NMI_25")
        , NMI_26(parent, this, "NMI_26")
        , NMI_27(parent, this, "NMI_27")
        , NMI_28(parent, this, "NMI_28")
        , NMI_29(parent, this, "NMI_29")
        , NMI_30(parent, this, "NMI_30")
        , NMI_31(parent, this, "NMI_31")
        , NMI_32(parent, this, "NMI_32")
        , NMI_33(parent, this, "NMI_33")
        , NMI_34(parent, this, "NMI_34")
        , NMI_35(parent, this, "NMI_35")
        , NMI_36(parent, this, "NMI_36")
        , NMI_37(parent, this, "NMI_37")
        , NMI_38(parent, this, "NMI_38")
        , NMI_39(parent, this, "NMI_39")
        , NMI_40(parent, this, "NMI_40")
        , NMI_41(parent, this, "NMI_41")
        , NMI_42(parent, this, "NMI_42")
        , NMI_43(parent, this, "NMI_43")
        , NMI_44(parent, this, "NMI_44")
        , NMI_45(parent, this, "NMI_45")
        , NMI_46(parent, this, "NMI_46")
        , NMI_47(parent, this, "NMI_47")
        , NMI_48(parent, this, "NMI_48")
        , NMI_49(parent, this, "NMI_49")
        , NMI_50(parent, this, "NMI_50")
        , NMI_51(parent, this, "NMI_51")
        , NMI_52(parent, this, "NMI_52")
        , NMI_53(parent, this, "NMI_53")
        , NMI_54(parent, this, "NMI_54")
        , NMI_55(parent, this, "NMI_55")
        , NMI_56(parent, this, "NMI_56")
        , NMI_57(parent, this, "NMI_57")
        , NMI_58(parent, this, "NMI_58")
        , NMI_59(parent, this, "NMI_59")
        , NMI_60(parent, this, "NMI_60")
        , NMI_61(parent, this, "NMI_61")
        , NMI_62(parent, this, "NMI_62")
        , NMI_63(parent, this, "NMI_63")
        , INT_00(parent, this, "INT_00")
        , INT_01(parent, this, "INT_01")
        , INT_02(parent, this, "INT_02")
        , INT_03(parent, this, "INT_03")
        , INT_04(parent, this, "INT_04")
        , INT_05(parent, this, "INT_05")
        , INT_06(parent, this, "INT_06")
        , INT_07(parent, this, "INT_07")
        , INT_08(parent, this, "INT_08")
        , INT_09(parent, this, "INT_09")
        , INT_10(parent, this, "INT_10")
        , INT_11(parent, this, "INT_11")
        , INT_12(parent, this, "INT_12")
        , INT_13(parent, this, "INT_13")
        , INT_14(parent, this, "INT_14")
        , INT_15(parent, this, "INT_15")
        , INT_16(parent, this, "INT_16")
        , INT_17(parent, this, "INT_17")
        , INT_18(parent, this, "INT_18")
        , INT_19(parent, this, "INT_19")
        , INT_20(parent, this, "INT_20")
        , INT_21(parent, this, "INT_21")
        , INT_22(parent, this, "INT_22")
        , INT_23(parent, this, "INT_23")
        , INT_24(parent, this, "INT_24")
        , INT_25(parent, this, "INT_25")
        , INT_26(parent, this, "INT_26")
        , INT_27(parent, this, "INT_27")
        , INT_28(parent, this, "INT_28")
        , INT_29(parent, this, "INT_29")
        , INT_30(parent, this, "INT_30")
        , INT_31(parent, this, "INT_31")
        , INT_32(parent, this, "INT_32")
        , INT_33(parent, this, "INT_33")
        , INT_34(parent, this, "INT_34")
        , INT_35(parent, this, "INT_35")
        , INT_36(parent, this, "INT_36")
        , INT_37(parent, this, "INT_37")
        , INT_38(parent, this, "INT_38")
        , INT_39(parent, this, "INT_39")
        , INT_40(parent, this, "INT_40")
        , INT_41(parent, this, "INT_41")
        , INT_42(parent, this, "INT_42")
        , INT_43(parent, this, "INT_43")
        , INT_44(parent, this, "INT_44")
        , INT_45(parent, this, "INT_45")
        , INT_46(parent, this, "INT_46")
        , INT_47(parent, this, "INT_47")
        , INT_48(parent, this, "INT_48")
        , INT_49(parent, this, "INT_49")
        , INT_50(parent, this, "INT_50")
        , INT_51(parent, this, "INT_51")
        , INT_52(parent, this, "INT_52")
        , INT_53(parent, this, "INT_53")
        , INT_54(parent, this, "INT_54")
        , INT_55(parent, this, "INT_55")
        , INT_56(parent, this, "INT_56")
        , INT_57(parent, this, "INT_57")
        , INT_58(parent, this, "INT_58")
        , INT_59(parent, this, "INT_59")
        , INT_60(parent, this, "INT_60")
        , INT_61(parent, this, "INT_61")
        , INT_62(parent, this, "INT_62")
        , INT_63(parent, this, "INT_63")
        , INT_64(parent, this, "INT_64")
        , INT_65(parent, this, "INT_65")
        , INT_66(parent, this, "INT_66")
        , INT_67(parent, this, "INT_67")
        , INT_68(parent, this, "INT_68")
        , INT_69(parent, this, "INT_69")
        , INT_70(parent, this, "INT_70")
        , INT_71(parent, this, "INT_71")
        , INT_72(parent, this, "INT_72")
        , INT_73(parent, this, "INT_73")
        , INT_74(parent, this, "INT_74")
        , INT_75(parent, this, "INT_75")
        , INT_76(parent, this, "INT_76")
        , INT_77(parent, this, "INT_77")
        , INT_78(parent, this, "INT_78")
        , INT_79(parent, this, "INT_79")
        , INT_80(parent, this, "INT_80")
        , INT_81(parent, this, "INT_81")
        , INT_82(parent, this, "INT_82")
        , INT_83(parent, this, "INT_83")
        , INT_84(parent, this, "INT_84")
        , INT_85(parent, this, "INT_85")
        , INT_86(parent, this, "INT_86")
        , INT_87(parent, this, "INT_87")
        , INT_88(parent, this, "INT_88")
        , INT_89(parent, this, "INT_89")
        , INT_90(parent, this, "INT_90")
        , INT_91(parent, this, "INT_91")
        , INT_92(parent, this, "INT_92")
        , INT_93(parent, this, "INT_93")
        , INT_94(parent, this, "INT_94")
        , INT_95(parent, this, "INT_95")
        , INT_96(parent, this, "INT_96")
        , INT_97(parent, this, "INT_97")
        , INT_98(parent, this, "INT_98")
        , INT_99(parent, this, "INT_99")
        , INT_100(parent, this, "INT_100")
        , INT_101(parent, this, "INT_101")
        , INT_102(parent, this, "INT_102")
        , INT_103(parent, this, "INT_103")
        , INT_104(parent, this, "INT_104")
        , INT_105(parent, this, "INT_105")
        , INT_106(parent, this, "INT_106")
        , INT_107(parent, this, "INT_107")
        , INT_108(parent, this, "INT_108")
        , INT_109(parent, this, "INT_109")
        , INT_110(parent, this, "INT_110")
        , INT_111(parent, this, "INT_111")
        , INT_112(parent, this, "INT_112")
        , INT_113(parent, this, "INT_113")
        , INT_114(parent, this, "INT_114")
        , INT_115(parent, this, "INT_115")
        , INT_116(parent, this, "INT_116")
    {
    }

}; /* class intc */


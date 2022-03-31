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

#include "peripheral/bhm.h"
#include "pse.igen.h"
#include "string.h"

#define PREFIX "LAN9118"

typedef struct macRegS {
    union {
        Uns32 value;
        struct {
            unsigned __pad1 : 2;
            unsigned RXEN : 1;
            unsigned TXEN : 1;
            unsigned __pad2 : 1;
            unsigned DFCHK : 1;
            unsigned BOLMT : 2;
            unsigned PADSTR : 1;
            unsigned __pad3 : 1;
            unsigned DISRTY : 1;
            unsigned BCAST : 1;
            unsigned LCOLL : 1;
            unsigned HPFILT : 1;
            unsigned __pad4 : 1;
            unsigned HO : 1;
            unsigned PASSBAD : 1;
            unsigned INVFILT : 1;
            unsigned PRMS : 1;
            unsigned MCPAS : 1;
            unsigned FDPX : 1;
            unsigned LOOPBK : 1;
            unsigned __pad5 : 1;
            unsigned RCVOWN : 1;
            unsigned __pad6 : 7;
            unsigned RXALL : 1;
        } bits;
    } MAC_CR;
    union {
        Uns32 value;
        struct {
            unsigned PA_47_32 : 16;
            unsigned __pad1 : 16;
        } bits;
    } ADDRH;
    union {
        Uns32 value;
        struct {
            unsigned PA_31_0 : 32;
        } bits;
    } ADDRL;
    union {
        Uns32 value;
        struct {
            unsigned HI : 32;
        } bits;
    } HASHH;
    union {
        Uns32 value;
        struct {
            unsigned LO : 32;
        } bits;
    } HASHL;
    union {
        Uns32 value;
        struct {
            unsigned MIIBZY : 1;
            unsigned MIIWnR : 1;
            unsigned __pad1 : 4;
            unsigned MIIRINDA : 5;
            unsigned PHYADDR : 5;
            unsigned __pad2 : 16;
        } bits;
    } MII_ACC;
    union {
        Uns32 value;
        struct {
            unsigned MIIData : 16;
            unsigned __pad1 : 16;
        } bits;
    } MII_DATA;
    union {
        Uns32 value;
        struct {
            unsigned FCBSY : 1;
            unsigned FCEN : 1;
            unsigned FCPASS : 1;
            unsigned __pad1 : 13;
            unsigned FCPT : 16;
        } bits;
    } FLOW;
    union {
        Uns32 value;
        struct {
            unsigned VTI1 : 16;
            unsigned __pad1 : 16;
        } bits;
    } VLAN1;
    union {
        Uns32 value;
        struct {
            unsigned VTI2 : 16;
            unsigned __pad1 : 16;
        } bits;
    } VLAN2;
    union {
        Uns32 value;
        struct {
            unsigned WFF : 32;
        } bits;
    } WUFF;
    union {
        Uns32 value;
        struct {
            unsigned __pad1 : 1;
            unsigned MPEN : 1;
            unsigned WUEN : 1;
            unsigned __pad2 : 2;
            unsigned MPR : 1;
            unsigned WUFR : 1;
            unsigned __pad3 : 2;
            unsigned GUE : 1;
            unsigned __pad4 : 22;
        } bits;
    } WUCSR;
} macRegT;

typedef struct phyRegS {
    union {
        Uns16 value;
        struct {
            Uns16 __pad1 : 7;
            Uns16 CollisionTest : 1;
            Uns16 DuplexMode : 1;
            Uns16 RestartAtoNegotiate : 1;
            Uns16 __pad2 : 1;
            Uns16 PowerDown : 1;
            Uns16 AutoNegotiationEnable : 1;
            Uns16 SpeedSelect : 1;
            Uns16 Loopback : 1;
            Uns16 Reset : 1;
        } bits;
    } BasicControl;
    union {
        Uns16 value;
        struct {
            Uns16 ExtendedCapabilities : 1;
            Uns16 JabberDetect : 1;
            Uns16 LinkStatus : 1;
            Uns16 AutoNegotiationAbility : 1;
            Uns16 RemoteFault : 1;
            Uns16 AutoNegotiationComplete : 1;
            Uns16 __pad1 : 5;
            Uns16 x10BaseTHalfDuplex : 1;
            Uns16 x10BaseTFullDuplex : 1;
            Uns16 x100BaseTXHalfDuplex : 1;
            Uns16 x100BaseTXFullDuplex : 1;
            Uns16 x100BaseT4 : 1;
        } bits;
    } BasicStatus;
    union {
        Uns16 value;
        struct {
            Uns16 PHYIDNumber : 16;
        } bits;
    } PhyIdentifier1;
    union {
        Uns16 value;
        struct {
            Uns16 RevisionNumber : 4;
            Uns16 ModelNumber : 6;
            Uns16 PHYIDNumberb : 6;
        } bits;
    } PhyIdentifier2;
    union {
        Uns16 value;
        struct {
            Uns16 SelectorField : 5;
            Uns16 x10BaseT : 1;
            Uns16 x10BaseTFullDuplex : 1;
            Uns16 x100BaseTX : 1;
            Uns16 x100BaseTXFullDuplex : 1;
            Uns16 __pad1 : 1;
            Uns16 PauseOperation : 2;
            Uns16 __pad2 : 1;
            Uns16 RemoteFault : 1;
            Uns16 __pad3 : 2;
        } bits;
    } AutoNegotiationAdvertisement;
    union {
        Uns16 value;
        struct {
            Uns16 SelectorField : 5;
            Uns16 x10BaseT : 1;
            Uns16 x10BaseTFullDuplex : 1;
            Uns16 x100BaseTX : 1;
            Uns16 x100BaseTXFullDuplex : 1;
            Uns16 x100BaseT4 : 1;
            Uns16 PauseOperation : 2;
            Uns16 __pad1 : 1;
            Uns16 RemoteFault : 1;
            Uns16 Acknowledge : 1;
            Uns16 NextPage : 1;
        } bits;
    } AutoNegotiationLinkPartnerAbility;
    union {
        Uns16 value;
        struct {
            Uns16 LinkPartnerAutoNegotiationAble : 1;
            Uns16 PageReceived : 1;
            Uns16 NextPageAble : 1;
            Uns16 LinkPartnerNextPageAble : 1;
            Uns16 ParallelDetectionFault : 1;
            Uns16 __pad1 : 11;
        } bits;
    } AutoNegotiationExpansion;
    union {
        Uns16 value;
        struct {
            Uns16 __pad1 : 1;
            Uns16 ENERGYON : 1;
            Uns16 __pad2 : 11;
            Uns16 EDPWRDOWN : 1;
            Uns16 __pad3 : 2;
        } bits;
    } ModeControlStatus;
    union {
        Uns16 value;
        struct {
            Uns16 PHYAD : 5;
            Uns16 MODE : 3;
            Uns16 __pad1 : 8;
        } bits;
    } SpecialModes;
    union {
        Uns16 value;
        struct {
            Uns16 __pad1 : 4;
            Uns16 XPOL : 1;
            Uns16 __pad2 : 5;
            Uns16 VCOOFF_LP : 1;
            Uns16 __pad3 : 5;
        } bits;
    } SpecialControlStatusIndications;
    union {
        Uns16 value;
        struct {
            Uns16 __pad1 : 1;
            Uns16 INT1 : 1;
            Uns16 INT2 : 1;
            Uns16 INT3 : 1;
            Uns16 INT4 : 1;
            Uns16 INT5 : 1;
            Uns16 INT6 : 1;
            Uns16 INT7 : 1;
            Uns16 __pad2 : 8;
        } bits;
    } InterruptSourceFlag;
    union {
        Uns16 value;
        struct {
            Uns16 MaskBits : 8;
            Uns16 __pad1 : 8;
        } bits;
    } InterruptMask;
    union {
        Uns16 value;
        struct {
            Uns16 __pad1 : 2;
            Uns16 SpeedIndication : 3;
            Uns16 __pad2 : 7;
            Uns16 AutoDone : 1;
            Uns16 __pad3 : 3;
        } bits;
    } PHYSpecialControlStatus;
} phyRegT;

macRegT macReg;
phyRegT phyReg;

#define IDX_MAC_CR          1
#define IDX_MAC_ADDRH       2
#define IDX_MAC_ADDRL       3
#define IDX_MAC_HASHH       4
#define IDX_MAC_HASHL       5
#define IDX_MAC_MII_ACC     6
#define IDX_MAC_MII_DATA    7
#define IDX_MAC_FLOW        8
#define IDX_MAC_VLAN1       9 /* TODO */
#define IDX_MAC_VLAN2       10 /* TODO */
#define IDX_MAC_WUFF        11 /* TODO */
#define IDX_MAC_WUCSR       12 /* TODO */

#define MAC_CR_RXALL    0x80000000
#define MAC_CR_RCVOWN   0x00800000
#define MAC_CR_LOOPBK   0x00200000
#define MAC_CR_FDPX     0x00100000
#define MAC_CR_MCPAS    0x00080000
#define MAC_CR_PRMS     0x00040000
#define MAC_CR_INVFILT  0x00020000
#define MAC_CR_PASSBAD  0x00010000
#define MAC_CR_HO       0x00008000
#define MAC_CR_HPFILT   0x00002000
#define MAC_CR_LCOLL    0x00001000
#define MAC_CR_BCAST    0x00000800
#define MAC_CR_DISRTY   0x00000400
#define MAC_CR_PADSTR   0x00000100
#define MAC_CR_BOLMT    0x000000c0
#define MAC_CR_DFCHK    0x00000020
#define MAC_CR_TXEN     0x00000008
#define MAC_CR_RXEN     0x00000004
#define MAC_CR_RESERVED 0x7f404213

#define IRQ_CFG_RW_MASK 0xff000111

#define THREAD_STACK      (8*1024)

enum tx_state {
    TX_IDLE,
    TX_A,
    TX_B,
    TX_DATA
};

typedef struct {
    enum tx_state state;
    unsigned int cmd_a;
    unsigned int cmd_b;
    int buffer_size;    // remaining buffer payload bytes to be pushed
    int offset;         // remaining bytes to be pushed before buffer's payload
    int pad;            // remaining bytes to be pushed after buffer's payload
    int fifo_used;      // Tx data FIFO dwords used by this packet
    int len;
    int index;
    int tag;
    unsigned char data[2048];
} LAN9118Packet;

struct {

    Uns32 ethHandle;

    int tx_fifo_size;
    LAN9118Packet *txp;
    LAN9118Packet tx_packet;

//    NICState *nic;
//    NICConf conf;

    int tx_status_fifo_used;    // dwords
    int tx_status_fifo_head;    // element (dword) index
    Uns32 tx_status_fifo[128];

    int rx_status_fifo_size;    // dwords
    int rx_status_fifo_used;    // dwords
    int rx_status_fifo_head;    // dwords
    Uns32 rx_status_fifo[224];

    int rx_fifo_size;   // dwords
    int rx_fifo_used;   // dwords
    int rx_fifo_head;   // element (dword) index
    Uns32 rx_fifo[3360];

    Uns8 rx_packet_buf[2048];

    Uns32 mac_cr;
    Uns32 mac_hashh;
    Uns32 mac_hashl;
    Uns32 mac_mii_acc;
    Uns32 mac_mii_data;
    Uns32 mac_flow;


    Int32 eeprom_writable;
    Uns32 eeprom[128];

    Bool irqAsserted;

} state;


static void updateInts()
{
    // update the master interrupt bit
    bport1_ab_data.IRQ_CFG.bits.IRQ_INT = (bport1_ab_data.INT_STS.value & bport1_ab_data.INT_EN.value) != 0U;

    // get the new interrupt pin state
    Bool irqWasAsserted = state.irqAsserted;
    state.irqAsserted = bport1_ab_data.IRQ_CFG.bits.IRQ_INT && bport1_ab_data.IRQ_CFG.bits.IRQ_EN;

    // update the interrupt pin;  TODO: support interrupt de-assertion interval
    if (state.irqAsserted != irqWasAsserted) {
        Bool val = !state.irqAsserted == !(bport1_ab_data.IRQ_CFG.bits.IRQ_POL && bport1_ab_data.IRQ_CFG.bits.IRQ_TYPE);

        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Pin IRQ %sasserted\n", (state.irqAsserted ? "" : "de-"));

        ppmWriteNet(handles.irq, val);
    }
}


static void updateTxFifoInts()
{
    if (state.tx_fifo_size - 4 * state.txp->fifo_used > 64 * bport1_ab_data.FIFO_INT.bits.TXDataAvailL)
        bport1_ab_data.INT_STS.bits.TDFA = 1;
    if (state.tx_status_fifo_used > bport1_ab_data.FIFO_INT.bits.TXStatusL)
        bport1_ab_data.INT_STS.bits.TSFL = 1;

    updateInts();
}


static void updateRxFifoInts()
{
//  if (4 * (state.rx_fifo_size - state.rx_fifo_used) < 64 * bport1_ab_data.FIFO_INT.bits.RXDataAvailL)
//      bport1_ab_data.INT_STS.bits.RDFL = 1;
    if (state.rx_status_fifo_used > bport1_ab_data.FIFO_INT.bits.RXStatusL)
        bport1_ab_data.INT_STS.bits.RSFL = 1;

    updateInts();
}


static inline void raiseTxError(void)
{
    bport1_ab_data.INT_STS.bits.TXE = 1;

    updateInts();
}


static inline void raiseTxFifoOverflow(void)
{
    bport1_ab_data.INT_STS.bits.TDFO = 1;
    bport1_ab_data.INT_STS.bits.TXE = 1;

    updateInts();
}


//static void lan9118_reload_eeprom(lan9118_state *s)
//{
//    int i;
//    if (state.eeprom[0] != 0xa5) {
//        state.e2p_cmd &= ~0x10;
//        bhmMessage("F", "eeprom", "MACADDR load failed\n");
//        return;
//    }
//    for (i = 0; i < 6; i++) {
//        state.conf.macaddr.a[i] = state.eeprom[i + 1];
//    }
//    state.e2p_cmd |= 0x10;
//    bhmMessage("I", "eeprom", "MACADDR loaded from eeprom\n");
//    lan9118_mac_changed(s);
//}

void doReset() {
                                               // True Init Value
    bport1_ab_data.ID_REV.value         = 0x01180001;
    bport1_ab_data.IRQ_CFG.value        = 0x0; // = 0x00000000;
    bport1_ab_data.INT_STS.value        = 0x0; // = 0x00000000;
    bport1_ab_data.INT_EN.value         = 0x0; // = 0x00000000;
    bport1_ab_data.BYTE_TEST.value      = 0x87654321;
    bport1_ab_data.FIFO_INT.value       = 0x48000000;
    bport1_ab_data.RX_CFG.value         = 0x0; // = 0x00000000;
    bport1_ab_data.TX_CFG.value         = 0x0; // = 0x00000000;
    bport1_ab_data.HW_CFG.value         = 0x00050000;
    bport1_ab_data.RX_DP_CTRL.value     = 0x0; // = 0x00000000;
    bport1_ab_data.RX_FIFO_INF.value    = 0x0; // = 0x00000000;
    bport1_ab_data.TX_FIFO_INF.value    = 0x00001200;
    bport1_ab_data.PMT_CTRL.value       = 0x0; // = 0x00000000;
    bport1_ab_data.GPIO_CFG.value       = 0x0; // = 0x00000000;
    bport1_ab_data.GPT_CFG.value        = 0x0000FFFF;
    bport1_ab_data.GPT_CNT.value        = 0x0000FFFF;
    bport1_ab_data.WORD_SWAP.value      = 0x0; // = 0x00000000;
    bport1_ab_data.FREE_RUN.value       = 0x0; // = 0x00000000;
    bport1_ab_data.RX_DROP.value        = 0x0; // = 0x00000000;
    bport1_ab_data.MAC_CSR_CMD.value    = 0x0; // = 0x00000000;
    bport1_ab_data.MAC_CSR_DATA.value   = 0x0; // = 0x00000000;
    bport1_ab_data.AFC_CFG.value        = 0x0; // = 0x00000000;
    bport1_ab_data.E2P_CMD.value        = 0x0; // = 0x00000000;
    bport1_ab_data.E2P_DATA.value       = 0x0; // = 0x00000000;

    Uns64  mac;
    if(bhmUns64ParamValue("macaddress", &mac)) {
        macReg.ADDRH.value                  = (mac >> 32) & 0x0000FFFF;
        macReg.ADDRL.value                  = (mac >>  0) & 0xFFFFFFFF;
    } else {
        macReg.ADDRH.value                  = 0x0000FFFF;
        macReg.ADDRL.value                  = 0xFFFFFFFF;
    }



    macReg.MAC_CR.value                 = 0x00040000;
    macReg.HASHH.value                  = 0x00000000;
    macReg.HASHL.value                  = 0x00000000;
    macReg.MII_ACC.value                = 0x00000000;
    macReg.MII_DATA.value               = 0x00000000;
    macReg.FLOW.value                   = 0x00000000;
    macReg.VLAN1.value                  = 0x00000000;
    macReg.VLAN2.value                  = 0x00000000;
    macReg.WUFF.value                   = 0x00000000;
    macReg.WUCSR.value                  = 0x00000000;

    phyReg.BasicControl.value                       = 0x3000;   // Determined by pin speed sel
    phyReg.BasicStatus.value                        = 0x7809;
    phyReg.PhyIdentifier1.value                     = 0x0007;
    phyReg.PhyIdentifier2.value                     = 0xc0d1;
    phyReg.AutoNegotiationAdvertisement.value       = 0x01e1;
    phyReg.AutoNegotiationLinkPartnerAbility.value  = 0x0001;
    phyReg.AutoNegotiationExpansion.value           = 0x0000;
    phyReg.ModeControlStatus.value                  = 0x0002;
    phyReg.SpecialModes.value                       = 0x0001;
    phyReg.SpecialControlStatusIndications.value    = 0x000b;
    phyReg.InterruptSourceFlag.value                = 0x0000;
    phyReg.InterruptMask.value                      = 0x0000;
    phyReg.PHYSpecialControlStatus.value            = 0x0054;

    state.txp = &(state.tx_packet);

//    state.irq_cfg &= ~(IRQ_TYPE | IRQ_POL);
//    state.int_sts = 0;
//    state.int_en = 0;
//    state.fifo_int = 0x48000000;
//    state.rx_cfg = 0;
//    state.tx_cfg = 0;
//    state.hw_cfg = 0x00050000;
//    state.pmt_ctrl &= 0x45;
//    state.gpio_cfg = 0;
    state.txp->state = TX_IDLE;
    state.txp->cmd_a = 0xffffffffu;
    state.txp->cmd_b = 0xffffffffu;
    state.txp->len = 0;
    state.txp->fifo_used = 0;
    state.tx_fifo_size = 4608;
    state.tx_status_fifo_used = 0;
    state.rx_status_fifo_head = 0;
    state.rx_status_fifo_size = 176;
    state.rx_status_fifo_used = 0;
    state.rx_fifo_size = 2640;
    state.rx_fifo_used = 0;
    state.rx_fifo_head = 0;

//    state.rxp_offset = 0;
//    state.rxp_size = 0;
//    state.rxp_pad = 0;
 //   state.rx_packet_size_tail = state.rx_packet_size_head;
 //   state.rx_packet_size[state.rx_packet_size_head] = 0;
//    state.mac_cmd = 0;
//    state.mac_data = 0;
//    state.afc_cfg = 0;
//    state.e2p_cmd = 0;
//    state.e2p_data = 0;
//    state.free_timer_start = qemu_get_clock(vm_clock) / 40;

//    ptimer_stop(state.timer);
//    ptimer_set_count(state.timer, 0xffff);
//    state.gpt_cfg = 0xffff;

    state.mac_cr = MAC_CR_PRMS;
    state.mac_hashh = 0;
    state.mac_hashl = 0;
    state.mac_mii_acc = 0;
    state.mac_mii_data = 0;
    state.mac_flow = 0;

    state.irqAsserted = False;

}

static void do_phy_read()
{
    unsigned index = macReg.MII_ACC.bits.MIIRINDA;
    Uns16    value = 0;
    Bool     noReg = False;

    switch (index) {
      case 0: /* Basic Control */
          value =  phyReg.BasicControl.value;
          break;
      case 1: /* Basic Status */
          value = phyReg.BasicStatus.value;
          break;
      case 2: /* ID1 */
          value = phyReg.PhyIdentifier1.value;
          break;
      case 3: /* ID2 */
          value = phyReg.PhyIdentifier2.value;
          break;
      case 4: /* Auto-neg advertisment */
          value = phyReg.AutoNegotiationAdvertisement.value;
          break;
      case 5: /* Auto-neg Link Partner Ability */
          value = phyReg.AutoNegotiationLinkPartnerAbility.value;
          break;
      case 6: /* Auto-neg Expansion */
          value = phyReg.AutoNegotiationExpansion.value;
          break;
      case 17: /* Mode Control/Status register*/
          value = phyReg.ModeControlStatus.value;
          break;
      case 18: /* Special Modes register*/
          value = phyReg.SpecialModes.value;
          break;
      case 27: /* Special Control/Status indications*/
          value = phyReg.SpecialControlStatusIndications.value;
          break;
      case 29: /* Interrupt source.  */
          value = phyReg.InterruptSourceFlag.value;
          break;
      case 30: /* Interrupt mask */
          value = phyReg.InterruptMask.value;
          break;
      case 31: /* SCSR*/
          value = phyReg.PHYSpecialControlStatus.value;
          break;
      default:
          noReg = True;
          break;
    }

    macReg.MII_DATA.bits.MIIData = value;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Read PHY register index=%u, value=0x%04x (%s)",
                            index, (unsigned)value,
                            noReg ? "NO Register at Index" : "ok");
    }
}

static void do_phy_write()
{
    unsigned index = macReg.MII_ACC.bits.MIIRINDA;
    Uns16    value = macReg.MII_DATA.bits.MIIData;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Write PHY register index=%u, value=0x%04x", index, (unsigned)value);
    }
    switch (index) {
        case 0: /* Basic Control */
            phyReg.BasicControl.value = (value & 0x7980);
            if (value & 0x8000) {
                // TODO: Reset to defaults
            }
            /* Complete autonegotiation imediately.  */
            if (phyReg.BasicControl.bits.AutoNegotiationEnable) {
                phyReg.BasicStatus.bits.AutoNegotiationComplete = 1;
            }
            break;
        case 4: /* Auto-neg advertisment */
            phyReg.AutoNegotiationAdvertisement.value = (value & 0x2d7f) | 0x0080;
            break;
        // Read - Only Regsiters
        case 1: /* Basic Status */
        case 2: /* ID1 */
        case 3: /* ID2 */
        case 5: /* Auto-neg Link Partner Ability */
        case 6: /* Auto-neg Expansion */
            if (PSE_DIAG_HIGH) {
                bhmMessage("W", PREFIX, "Write PHY Attempt to a read only register at index=%u", index);
            }
            break;
        // Read/Write but no behavior modelled
        case 17: /* Model Control/Status register*/
        case 18: /* Special Modes register*/
        case 27: /* Special Control/Status indications*/
        case 29: /* Interrupt source.  */
        case 30: /* Interrupt mask */
        case 31: /* SCSR*/
            break;
        default:
            if (PSE_DIAG_HIGH) {
                bhmMessage("W", PREFIX, "Write PHY No register at index=%u", index);
            }
            break;
    }
}

static void do_mac_write()
{
    Uns32 index = bport1_ab_data.MAC_CSR_CMD.bits.CSRAddress;
    Uns32 value = bport1_ab_data.MAC_CSR_DATA.value;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Write MAC register index=%u, value=0x%08x", index, value);
    }
    Uns32 RXENprev = macReg.MAC_CR.bits.RXEN;

    switch (index) {
      case IDX_MAC_CR:
          macReg.MAC_CR.value = value;

          // has the receiver been disabled ?
          // if so the Interrupt is pulsed
          if (RXENprev==1 && macReg.MAC_CR.bits.RXEN==0) {
              bport1_ab_data.INT_STS.bits.RXSTOP_INT = 1;
              updateInts();
          }
          break;
      case IDX_MAC_ADDRH:
          macReg.ADDRH.value = value;
          break;
      case IDX_MAC_ADDRL:
          macReg.ADDRL.value = value;
          break;
//    case MAC_HASHH:
//        state.mac_hashh = val;
//        break;
//    case MAC_HASHL:
//        state.mac_hashl = val;
//        break;
      case IDX_MAC_MII_ACC:
          macReg.MII_ACC.value = value;

          if (macReg.MII_ACC.bits.MIIWnR) {
              do_phy_write();
          } else {
              do_phy_read();
          }
          // Self clearing
          macReg.MII_ACC.bits.MIIBZY = 0;
          break;
      case IDX_MAC_MII_DATA:
          macReg.MII_DATA.bits.MIIData = value;
          break;
//    case MAC_FLOW:
//        state.mac_flow = val & 0xffff0000;
//        break;
      default:
          break;
    }
}

static void do_mac_read()
{
    Uns32 index = bport1_ab_data.MAC_CSR_CMD.bits.CSRAddress;
    Uns32 value = 0;

    switch (index) {
      case IDX_MAC_CR:
          value = macReg.MAC_CR.value;
          break;
      case IDX_MAC_ADDRH:
          value = macReg.ADDRH.value;
          break;
      case IDX_MAC_ADDRL:
          value = macReg.ADDRL.value;
          break;
//    case MAC_HASHH:
//        return state.mac_hashh;
//        break;
//    case MAC_HASHL:
//        return state.mac_hashl;
//        break;
      case IDX_MAC_MII_ACC:
          value = macReg.MII_ACC.value;
          break;
      case IDX_MAC_MII_DATA:
          value = macReg.MII_DATA.value;
          break;
//    case IDX_MAC_FLOW:
//        return state.mac_flow;
      default:
          break;
    }

    bport1_ab_data.MAC_CSR_DATA.value = value;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Read MAC register index=%u, value=0x%08x", index, value);
    }
}


//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(defaultRdCB) {
    Uns32 index = PTR_TO_UNS32(user);
    Uns32 value = 0;

    switch (index) {
    case 0x84:
        // PMT_CTRL - Power Management Control
        value = 0x01;
        break;
    default:
        break;
    }

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Read CSR register index=0x%02x, value=0x%08x", index, value);
    }

    return value;
}

PPM_REG_WRITE_CB(defaultWrCB) {
    Uns32 index = PTR_TO_UNS32(user);

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Write CSR register index=0x%02x, value=0x%08x", index, data);
    }

    return;
}

PPM_REG_READ_CB(idRev) {
    return bport1_ab_data.ID_REV.value;
}

PPM_REG_READ_CB(byteTest) {
    return bport1_ab_data.BYTE_TEST.value;
}

PPM_REG_READ_CB(hwCfgRd) {
    return bport1_ab_data.HW_CFG.value;
}

PPM_REG_WRITE_CB(hwCfgWr) {
    bport1_ab_data.HW_CFG.value = data & 0x003f300;

    if (bport1_ab_data.HW_CFG.bits.SRST) {
        doReset();
    }
}

PPM_REG_READ_CB(intEnRd) {
    return bport1_ab_data.INT_EN.value;
}

#define RESERVED_INT    0x7c001000
#define SW_INT          0x80000000

PPM_REG_WRITE_CB(intEnWr) {
    bport1_ab_data.INT_EN.value   = data & ~RESERVED_INT;
    bport1_ab_data.INT_STS.value |= data & SW_INT;
    updateInts();
}

PPM_REG_READ_CB(irqCfgRd) {
    return bport1_ab_data.IRQ_CFG.value;
}


PPM_REG_WRITE_CB(irqCfgWr) {
    /* TODO: Implement interrupt deassertion intervals.  */
    bport1_ab_data.IRQ_CFG.value = (bport1_ab_data.IRQ_CFG.value & ~IRQ_CFG_RW_MASK) | (data & IRQ_CFG_RW_MASK);
}

PPM_REG_READ_CB(intStsRd) {
    return bport1_ab_data.INT_STS.value;
}

PPM_REG_WRITE_CB(intStsWr) {
    bport1_ab_data.INT_STS.value &= ~data;
    updateInts();
}



PPM_REG_READ_CB(macCsrCmdRd) {
//    bhmMessage("F", "Unsupported", "%s %s:%d", __FUNCTION__, __FILE__ ,  __LINE__);
    return bport1_ab_data.MAC_CSR_CMD.value;
}

PPM_REG_WRITE_CB(macCsrCmdWr) {
//    bhmMessage("F", "Unsupported", "%s %s:%d", __FUNCTION__, __FILE__ ,  __LINE__);
    bport1_ab_data.MAC_CSR_CMD.value = data;
    if (bport1_ab_data.MAC_CSR_CMD.bits.CSRBusy) {
        if (bport1_ab_data.MAC_CSR_CMD.bits.RnW) {
            do_mac_read();
        } else {
            do_mac_write();
        }
    }

    // Self Clearing
    bport1_ab_data.MAC_CSR_CMD.bits.CSRBusy = 0;
}

PPM_REG_READ_CB(macCsrDataRd) {
    return bport1_ab_data.MAC_CSR_DATA.value;
}

PPM_REG_WRITE_CB(macCsrDataWr) {
    bport1_ab_data.MAC_CSR_DATA.value = data;
}

PPM_REG_READ_CB(txCfgRd) {
//    bhmMessage("F", "Unsupported", "%s %s:%d", __FUNCTION__, __FILE__ ,  __LINE__);
    return bport1_ab_data.TX_CFG.value;
}

PPM_REG_WRITE_CB(txCfgWr) {
//    bhmMessage("F", "Unsupported", "%s %s:%d", __FUNCTION__, __FILE__ ,  __LINE__);
    bport1_ab_data.TX_CFG.value = data;

    if (bport1_ab_data.TX_CFG.bits.TXS_DUMP) {
        state.tx_status_fifo_used = 0;
    }
    if (bport1_ab_data.TX_CFG.bits.TXD_DUMP) {
        state.txp->state = TX_IDLE;
        state.txp->fifo_used = 0;
        state.txp->cmd_a = 0xffffffff;
        updateTxFifoInts();
    }

    // Self Clearing
    bport1_ab_data.TX_CFG.bits.TXS_DUMP = 0;
    bport1_ab_data.TX_CFG.bits.TXD_DUMP = 0;
}

PPM_REG_READ_CB(rxCfgRd) {
    return bport1_ab_data.RX_CFG.value;
}

PPM_REG_WRITE_CB(rxCfgWr) {
//    bhmMessage("F", "Unsupported", "%s %s:%d", __FUNCTION__, __FILE__ ,  __LINE__);
    bport1_ab_data.RX_CFG.value = data & 0xcfff9f00;

    if (bport1_ab_data.RX_CFG.bits.RX_DUMP) {
        /* RX_DUMP */
        state.rx_fifo_used = 0;
        state.rx_status_fifo_used = 0;
    //    state.rx_packet_size_tail = state.rx_packet_size_head;
    //    state.rx_packet_size[state.rx_packet_size_head] = 0;
    }

    // Self Clearing
    bport1_ab_data.RX_CFG.bits.RX_DUMP = 0;
}

PPM_REG_READ_CB(rxDropRd) {
    Uns32 ret = bport1_ab_data.RX_DROP.value;
    bport1_ab_data.RX_DROP.value = 0U;
    return ret;
}

PPM_REG_READ_CB(rxFifoInfRd) {
    bport1_ab_data.RX_FIFO_INF.bits.RXSUSED = state.rx_status_fifo_used;
    bport1_ab_data.RX_FIFO_INF.bits.RXDUSED = 4 * state.rx_fifo_used;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I",PREFIX, "rxFifoInfRd() = %x", bport1_ab_data.RX_FIFO_INF.value);
    }
    return bport1_ab_data.RX_FIFO_INF.value;
}

PPM_REG_READ_CB(rxFifoRd) {
    if (state.rx_fifo_used == 0) {
        //error
        return 0;
    }

    Uns32 tail = (state.rx_fifo_head >= state.rx_fifo_used) ? (state.rx_fifo_head - state.rx_fifo_used) :
                                                              (state.rx_fifo_size + state.rx_fifo_head - state.rx_fifo_used);
    state.rx_fifo_used--;

    return state.rx_fifo[tail];
}

PPM_REG_READ_CB(rxStatusFifoPeek) {
    if (state.rx_status_fifo_used == 0) {
        //error
        return 0;
    }

    Uns32 tail = (state.rx_status_fifo_head >= state.rx_status_fifo_used) ? (state.rx_status_fifo_head - state.rx_status_fifo_used) :
                                                                            (state.rx_status_fifo_size + state.rx_status_fifo_head - state.rx_status_fifo_used);
    return state.rx_status_fifo[tail];
}

PPM_REG_READ_CB(rxStatusFifoRd) {

    if (state.rx_status_fifo_used == 0) {
        //error
        return 0;
    }

    Uns32 tail = (state.rx_status_fifo_head >= state.rx_status_fifo_used) ? (state.rx_status_fifo_head - state.rx_status_fifo_used) :
                                                                            (state.rx_status_fifo_size + state.rx_status_fifo_head - state.rx_status_fifo_used);
    state.rx_status_fifo_used--;

    return state.rx_status_fifo[tail];
}

static void dropRxFrame(void)
{
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Dropping an Rx frame");

    // Increment the dropped frames counter
    bport1_ab_data.RX_DROP.bits.RX_DFC++;

    // Trigger affected interrupt bits
    bport1_ab_data.INT_STS.bits.RXDF_INT = 1;
    if (bport1_ab_data.RX_DROP.bits.RX_DFC == 0x80000000)
        bport1_ab_data.INT_STS.bits.RXDFH_INT = 1;

    // Update the irq pin
    updateInts();
}


static Bool pushRxFrame(Uns8 *frame, int len)
{
    int offset = bport1_ab_data.RX_CFG.bits.RXDOFF;

    // Compute number of padding bytes needed at end for correct alignment
    int pad = 0;
    int buffer_bytes = len + offset;
    if (bport1_ab_data.RX_CFG.bits.RXEndAlign == 0) { // 4-byte alignment
        pad = (-buffer_bytes & 0x3);
    } else if (bport1_ab_data.RX_CFG.bits.RXEndAlign == 1) { // 16-bytes alignment
        pad = (-buffer_bytes & 0xf);
    } else if (bport1_ab_data.RX_CFG.bits.RXEndAlign == 2) { // 32-byte alignment
        pad = (-buffer_bytes & 0x1f);
    } else {
        // Error, reserved value
        pad = (-buffer_bytes & 0x3);
    }

    buffer_bytes += pad;

    // Check if enough room in fifo
    if (buffer_bytes > 4 * (state.rx_fifo_size - state.rx_fifo_used)) {
        // overflow
        dropRxFrame();
        return False;
    }

    // Use the dword-organized Rx FIFO as a byte array
    Uns8 *rxFifo = (Uns8*)state.rx_fifo;
    int rxFifoPos = 4 * state.rx_fifo_head;
    int rxFifoBytes = 4 * state.rx_fifo_size;

    // Skip offset bytes
    rxFifoPos = (rxFifoPos + offset) % rxFifoBytes;

    // Check if copy will wrap around fifo array
    int remainingBytes = (rxFifoPos + len > rxFifoBytes) ? (rxFifoPos + len - rxFifoBytes) : 0;
    int segmentBytes = len - remainingBytes;

    memcpy(&rxFifo[rxFifoPos], frame, segmentBytes);
    rxFifoPos = (rxFifoPos + segmentBytes) % rxFifoBytes;

    // If wraps, copy segment to begining of fifo
    if (remainingBytes > 0) {
        memcpy(rxFifo, &frame[segmentBytes], remainingBytes);
        rxFifoPos = remainingBytes;
    }

    // Skip pad bytes
    rxFifoPos = (rxFifoPos + pad) % rxFifoBytes;

    // Move head to correct index
    state.rx_fifo_head = rxFifoPos / 4;

    state.rx_fifo_used += buffer_bytes / 4;

    // RX Status Fifo
    Uns32 val = (len & 0x3FFF) << 16;                   // length field
    val |= ((len < 0) ? (1U << 1) : 0U);                // represent receive errors as CRC errors
    val |= ((val & 0x000008c2) ? (1U << 15) : 0U);      // error summary

    state.rx_status_fifo[state.rx_status_fifo_head++] = val;
    if (state.rx_status_fifo_head >= state.rx_status_fifo_size)
        state.rx_status_fifo_head = 0;

    state.rx_status_fifo_used++;
    updateRxFifoInts();

    return True;
}

static BHM_ETHER_PACKET_CB(rxFrame) {

    if (!macReg.MAC_CR.bits.RXEN) {
        return;
    }
    pushRxFrame(data, bytes+4);
}

PPM_REG_READ_CB(txFifoInfRd) {
    bport1_ab_data.TX_FIFO_INF.bits.TXSUSED = state.tx_status_fifo_used;
    bport1_ab_data.TX_FIFO_INF.bits.TXDFREE = state.tx_fifo_size - 4 * state.txp->fifo_used;

    return bport1_ab_data.TX_FIFO_INF.value;
}

PPM_REG_WRITE_CB(txFifoWr) {
    Uns32 val, txbytes;

    int buffer_bytes, result;


    switch(state.txp->state) {
        case TX_A:
        case TX_IDLE:
            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Writing buffer to fifo: TX_CMD_A\n");
            }
            state.txp->cmd_a = data;

            // Interrupt on Completion [31]
            if (data & 0x80000000) {
                // TODO: Ints
            }


            // Data Start Offset [20:16]
            state.txp->offset = (data >> 16) & 0x1F;

            // First Segment [13]
            if ((data & 0x2000) && (state.txp->state != TX_IDLE)) {
                bhmMessage("W", PREFIX, "Detected first segment flag set for an intermediate buffer; ignoring\n");
            }
            else if (!(data & 0x2000) && (state.txp->state == TX_IDLE)) {
                bhmMessage("W", PREFIX, "First segment flag not set for first buffer of a packet; setting\n");
                state.txp->cmd_a |= 0x2000;
            }

            // Buffer Size [10:0]
            state.txp->buffer_size = data & 0x7FF;


            // Buffer End Alignment [25:24]
            // Compute extra bytes at end of buffer
            state.txp->pad = 0;
            buffer_bytes = state.txp->buffer_size + state.txp->offset;
            if ((data & 0x03000000) == 0) { // 4-byte alignment
                state.txp->pad = (-buffer_bytes & 0x3);
            } else if ((data & 0x03000000) == 0x01000000) { // 16-bytes alignment
                state.txp->pad = (-buffer_bytes & 0xf);
            } else if ((data & 0x03000000) == 0x02000000) { // 32-byte alignment
                state.txp->pad = (-buffer_bytes & 0x1f);
            } else {
                // Error, reserved value
            }

            state.txp->state = TX_B;
            state.txp->fifo_used++;
            break;
        case TX_B:
            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Writing buffer to fifo: TX_CMD_B\n");
            }
            // If first segment, otherwise don't save
            if (state.txp->cmd_a & 0x2000) {
                state.txp->cmd_b = data;
                // Packet Tag [31:16]
                state.txp->tag = (data >> 16) & 0xFFFF;

                // Packet Length
                state.txp->len = data & 0x7FF;

                state.txp->fifo_used++;
            }
            else if (data != state.txp->cmd_b) {
                raiseTxError();
            }
            state.txp->state = TX_DATA;
            break;
        case TX_DATA:

            // Handle padding/offset at start/end of buffer

            if (state.txp->offset > 4) { // Padding at start of buffer, no real data
                state.txp->offset -= 4;
                txbytes = 0;
            } else if (state.txp->offset > 0) { // Some padding at start of buffer, less than 4 bytes
                txbytes = 4 - state.txp->offset;
                val = data >> (8 * state.txp->offset);
                state.txp->offset = 0;
            } else if (state.txp->buffer_size < 4) { // End of buffer, less than 4 bytes of data remain
                txbytes = state.txp->buffer_size;
                // At end of buffer, check remaining bytes to get correct alignment
                state.txp->pad -= (4 - txbytes);
                val = data;
            } else { // Full 4 bytes of data
                txbytes = 4;
                val = data;
            }

            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Writing buffer to fifo: TX Data bytes remaining %d\n",state.txp->buffer_size - txbytes );
            }

            // If Bytes available to add to payload
            if (txbytes > 0)
            {
                if (state.txp->index < sizeof(state.txp->data)/sizeof(state.txp->data[0])) {
                    memcpy(&state.txp->data[state.txp->index],&val,txbytes);
                    state.txp->index += txbytes;
                    state.txp->fifo_used++;
                }
                else {
                    raiseTxFifoOverflow();
                }

                state.txp->buffer_size -= txbytes;
            }


            // If Buffer complete
            if (state.txp->buffer_size  == 0 && state.txp->pad <= 0) {


                // Check if Last segment
                if (state.txp->cmd_a & 0x1000) {
                    if (state.txp->index != state.txp->len) {
                        // frame size / buffer sizes mismatch
                        raiseTxError();
                        state.txp->len = state.txp->index;
                    }
                    if ((state.tx_status_fifo_used >= 128) && !bport1_ab_data.TX_CFG.bits.TXSAO) {
                        // TX Status FIFO full, discard frame and status  TODO: actual HW stops transmission, waits for status room
                        raiseTxError();
                    } else {
                        // If Loopback
                        if (phyReg.BasicControl.bits.Loopback || macReg.MAC_CR.bits.LOOPBK) {
                            if (PSE_DIAG_HIGH) {
                                bhmMessage("I", PREFIX, "Writing buffer to fifo: Transmit frame in loopback");
                            }

                            // Add a pseudo FCS if needed as a partial workaround for missing MAC functionality
                            int pktLen = state.txp->len + ((state.txp->cmd_b & 0x2000) ? 0U : 4U);

                            result = pushRxFrame(state.txp->data, pktLen) ? 0 : -1;
                        } else {
                            if (PSE_DIAG_HIGH) {
                                bhmMessage("I", PREFIX, "Writing buffer to fifo: Frame Complete");
                            }
                            // Write Frame

                            result = bhmEthernetWriteFrameN(state.ethHandle, state.txp->data, state.txp->len) == (unsigned)state.txp->len ? 0 : -1;
                        }

                        if (state.tx_status_fifo_used < 128) {
                            // set status bits
                            val = state.txp->tag << 16;                         // tag field
                            val |= (result ? (1U << 8) : 0U);                   // represent send errors as excessive collisions
                            val |= ((val & 0x00000f06) ? (1U << 15) : 0U);      // error summary

                            state.tx_status_fifo[state.tx_status_fifo_head++] = val;
                            if (state.tx_status_fifo_head >= 128)
                                state.tx_status_fifo_head = 0;

                            state.tx_status_fifo_used++;
                        }
                    }

                    state.txp->fifo_used = 0;
                    state.txp->index = 0;

                    updateTxFifoInts();

                    state.txp->state = TX_IDLE;
                } else {
                    if (PSE_DIAG_HIGH) {
                        bhmMessage("I", PREFIX, "Writing buffer to fifo: Buffer Complete, wait for next segment");
                    }
                    state.txp->state = TX_A;
                }
            }
            break;
    }
}

PPM_REG_READ_CB(txStatusFifoPeek) {
    if (state.tx_status_fifo_used == 0) {
        //error
        return 0;
    }
    Uns32 tail = (state.tx_status_fifo_head >= state.tx_status_fifo_used) ? (state.tx_status_fifo_head - state.tx_status_fifo_used) :
                                                                            (128 + state.tx_status_fifo_head - state.tx_status_fifo_used);

    return state.tx_status_fifo[tail];
}

PPM_REG_READ_CB(txStatusFifoRd) {
    if (state.tx_status_fifo_used == 0) {
        //error
        return 0;
    }

    Uns32 tail = (state.tx_status_fifo_head >= state.tx_status_fifo_used) ? (state.tx_status_fifo_head - state.tx_status_fifo_used) :
                                                                            (128 + state.tx_status_fifo_head - state.tx_status_fifo_used);

    state.tx_status_fifo_used--;

    return state.tx_status_fifo[tail];
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();

    // Initialize semihosting
    state.ethHandle = bhmEthernetOpenAuto(); //Open(0,0,"etherinlog.dat","etherlog.dat");

    doReset();
    phyReg.BasicStatus.bits.AutoNegotiationComplete = phyReg.BasicStatus.bits.LinkStatus = 1U;

    bhmEthernetInstallCB(state.ethHandle, rxFrame, 0);
}

PPM_DESTRUCTOR_CB(destructor) {
    bhmEthernetClose(state.ethHandle);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


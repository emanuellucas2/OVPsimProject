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


#include "pse.igen.h"
#include "string.h"

#include "net.h"
#include "gem.h"

#include "gem_macb.h"
#include "gem_dma.h"
#include "mii_phy.h"


extern int cksum(Uns16 *w, int mlen);

typedef struct MacStateS {
    Uns32 txBufOfs;
    double txLastActivityTS;
    GemTxStatusT txStatus;
    Uns32 rxBufOfs;
    Uns32 rxFrameLen;
    GemRxStatusT rxStatus;
    ppmNetHandle          irqHandle;
    Bool                  irqAsserted;
} MacStateT;


static MacStateT macState;

static Uns8 txBuffer[8192];
static Uns32 const txBufferSize = sizeof(txBuffer);

static Uns8 rxBuffer[8192];
static Uns32 const rxBufferSize = sizeof(rxBuffer);



static void initMacState(MacStateT *macState)
{
    // initialize all fields but ethHandle
    macState->txBufOfs = 0U;
    macState->txLastActivityTS = 0.0;
    macState->txStatus.value = 0U;
    macState->rxBufOfs = 0U;
    macState->rxFrameLen = 0U;
    macState->rxStatus.value = 0U;
    macState->irqHandle = handles.irq;
    macState->irqAsserted = False;
}


static inline Uns16 etherTypeField(Uns8 *frame)
{
    return htons(*(Uns16 *)(frame + 2 * ETHER_ADDR_LEN));
}

static inline Uns16 vlanTagField(Uns8 *frame)
{
    return htons(*(Uns16 *)(frame + ETHER_HDR_LEN));
}

static inline Bool isEtherTypeFrame(Uns8 *frame)
{
    return etherTypeField(frame) >= 0x600;
}

static inline Bool isVlanFrame(Uns8 *frame)
{
    return etherTypeField(frame) == 0x8101;
}

static inline Bool isValidVlanTag(Uns8 *frame)
{
    //Uns16 tagMask = 0; //macRegs->VLAN_Tag.bits.etv ? 0x0fff : 0xffff; // TODO:
    //Uns16 tag = 0; //macRegs->VLAN_Tag.bits.vl & tagMask; // TODO:
    return isVlanFrame(frame);// && (tag == 0U || tag == (vlanTagField(frame) & tagMask));
}

static inline Bool isTxEnabled(void)
{
    return bport1_ab_data.net_ctrl.bits.tx_en;
}

static inline Bool isRxEnabled(void)
{
    return bport1_ab_data.net_ctrl.bits.rx_en;
}


static Bool checkRxState()
{
    // ignore the request if Rx is disabled
    if (!isRxEnabled()) {
        if (PSE_DIAG_LOW)
            bhmMessage("W", PREFIX, "Ignoring MAC read request while Rx is disabled\n");
        macState.rxStatus.bits.frame_length = 0U;
        return False;
    }

    return True;
}

static void rxCutOff(void)
{
    // find out the size at which the receive watchdog will trigger
    unsigned int wdFrameLen = 16384U;
    if (0) // !macRegs->MAC_Configuration.bits.wd) // TODO:
        wdFrameLen = /*(macRegs->MAC_Configuration.bits.je) ? 10240U :*/ 2048U;  // TODO:

    // cut off larger frames
    if (macState.rxFrameLen > wdFrameLen) {
        macState.rxFrameLen = wdFrameLen;
        macState.rxStatus.bits.receive_watchdog = 1;
    }
}

static void rxCheckFilter(void)
{
    // TODO: check SA / DA filter; update rxFrameLen
}

static void rxStripPadding(void)
{
    // frames from the backend are stripped
    Bool addFcs = False;
    Uns16 typeField = etherTypeField(rxBuffer);
    if (typeField < 0x600) {
        // add back pad and FCS placeholder if stripping is disabled
         unsigned int len = typeField + ETHER_HDR_LEN; // TODO:
        if (/*!macRegs->MAC_Configuration.bits.acs && */macState.rxFrameLen >= len // TODO:
         && macState.rxFrameLen < ETHER_MIN_LEN) {
            macState.rxFrameLen = ETHER_MIN_LEN;
            addFcs = True;
        }
    }
    else {
        // add back FCS placeholder if stripping is disabled  (TODO: also if IP COE type 1 is enabled?)
        if (!bport1_ab_data.net_cfg.bits.fcs_remove && (macState.rxFrameLen <= rxBufferSize - ETHER_CRC_LEN)) { // TODO:
            macState.rxFrameLen += ETHER_CRC_LEN;
            addFcs = True;
        }
    }
    if (addFcs) {
        // update the FCS placeholder with a fake CRC; the crc_error status bit should take precedence
        Uns32 *pFcs = (Uns32 *)(rxBuffer + macState.rxFrameLen - ETHER_CRC_LEN);
        *pFcs = htonl( 0x0BADFC50 );
    }
}

static void rxCheckFcs(void)
{
    // frames from the backend are FCS stripped
    macState.rxStatus.bits.crc_error = 0;
}



static void rxReadFrame(void)
{
    // don't read a new frame if there's already one in the buffer
    if (macState.rxFrameLen > 0U)
        return;

    // reset state info
    macState.rxStatus.value = 0U;
    macState.rxBufOfs = 0U;

    // try to ensure a (not dropped) frame in the Rx buffer
    while (macState.rxFrameLen == 0U) {
        // read a frame from PHY
        macState.rxFrameLen = phyReadFrame(rxBuffer, rxBufferSize);
        if (macState.rxFrameLen == 0U)
            break;          // no more Rx data at the moment

        rxCutOff();         // cut off large frames
        rxCheckFilter();    // check the SA / DA filters

        if (macState.rxFrameLen == 0U)
            continue;       // the frame was dropped

        // update status bits
        macState.rxStatus.bits.frame_type = isEtherTypeFrame(rxBuffer);  // TODO:
        macState.rxStatus.bits.vlan_tag = isValidVlanTag(rxBuffer); // TODO:

        bport1_ab_data.frames_rx.value++;

        rxCheckFcs();       // check the CRC
        rxStripPadding();   // strip padding and FCS as needed
    }
}

GemRxStatusT gemMacbReadData(void *buf, unsigned int bufSize)
{
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Reading up to %u bytes from the MAC\n", bufSize);

    // check if the request corresponds to the current Rx state
    if (!checkRxState())
        return macState.rxStatus;

    // TODO : this is never executed
    if (macState.rxFrameLen == 0U)
        rxReadFrame();      // read the next passing frame into the Rx buffer

     macState.rxStatus.bits.start_of_frame = (macState.rxBufOfs == 0U);

    // copy frame data to the application buffer
    unsigned int len = macState.rxFrameLen - macState.rxBufOfs;
    len = (len < bufSize) ? len : bufSize;
    memcpy(buf, rxBuffer + macState.rxBufOfs, len);
    macState.rxBufOfs += len;

    // update status flags
    macState.rxStatus.bits.frame_length = len;
    if (macState.rxBufOfs == macState.rxFrameLen) {
        macState.rxStatus.bits.end_of_frame = 1;
        macState.rxFrameLen = macState.rxBufOfs = 0U;
    }

    return macState.rxStatus;
}

static Bool padTxFrame(Uns8 *frame, unsigned int *size, Uns32 flags)
{
    // check if padding is needed and enabled
    //if (*size >= ETHER_MIN_LEN || flags.bits.disable_padding) // TODO:
      //  return False;

    // SW requests padding, but backend accepts stripped frames; do nothing
    return False;
}

static inline void addTxFcs(Uns8 *frame, unsigned int size, Uns32 flags, Bool force)
{
    // check if FCS is required
    if (bport1_ab_data.dma_cfg.bits.csum_gen_offload_en) {
        if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "addTxFcs() field type = 0x%x\n", etherTypeField(frame));
        if (etherTypeField(frame) == ETH_P_IP) {
            int ip_hdr_len = (frame[ETH_HLEN] & 0x0F) * 4;
            //bhmMessage("I", PREFIX, "IP packet, hdr_len=%d\n", ip_hdr_len);

            //Uns16 oldcsum = (*(Uns16 *)(frame + ETH_IP_CRC_OFFSET));
            (*(Uns16 *)(frame + ETH_IP_CRC_OFFSET)) = 0x000;
            Uns16 csum = cksum((Uns16 *)(frame + ETH_HLEN), ip_hdr_len);
            (*(Uns16 *)(frame + ETH_IP_CRC_OFFSET)) =  csum;
            //bhmMessage("I", PREFIX, "csum=0x%x, 0x%x\n type = 0x%x", csum, oldcsum, frame[23]);
            if (frame[23] == ETH_P_TCP) { // TCP

                Uns16 total_len = htons((*(Uns16 *)(frame + 16)));
                Uns16 len = total_len - ip_hdr_len;
                //oldcsum = (*(Uns16 *)(frame + ETH_HLEN + ip_hdr_len + ETH_TCP_CRC_OFFSET));

                //Zero out CRC
                (*(Uns16 *)(frame + ETH_HLEN + ip_hdr_len + ETH_TCP_CRC_OFFSET)) = 0;

                // Psuedo Header for CRC generation
                Uns8 buf[4096];
                memcpy(buf,frame + ETH_HLEN + ip_hdr_len - 8,8);
                buf[8] = 0x0;
                buf[9] = ETH_P_TCP;
                (*(Uns16 *) (buf + 10)) = htons(len);

                memcpy(&buf[12],frame + ETH_HLEN + ip_hdr_len,len);
                Uns16 csum = cksum((Uns16* )buf, len+12);
                //bhmMessage("I", PREFIX, "TCP csum=0x%x, 0x%x, len = 0x%x", csum, oldcsum, len);
                (*(Uns16 *)(frame + ETH_HLEN + ip_hdr_len + ETH_TCP_CRC_OFFSET)) = csum;
            }
        }
    }

    // SW requests CRC insertion, but backend accepts stripped frames; do nothing
}

GemTxStatusT gemMacbWriteData(void *data, unsigned int len)
{
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Writing %u bytes to the MAC\n", len);

    Uns32 flags = 0;  // TODO:
    // check if the request corresponds to the current Tx state
    //if (!checkTxState(flags))  // FIXME:
    //    return macState.txStatus;

    // reset some state info on the first segment of a frame
    if (macState.txBufOfs == 0U) {
         macState.txStatus.value = 0U; // FIXME:
        macState.txLastActivityTS = 0.0;
    }

    // check for buffer overflow
    if (macState.txBufOfs + len > txBufferSize) {
        if (PSE_DIAG_LOW)
            bhmMessage("W", PREFIX, "Tx MAC buffer overflow\n");
         macState.txStatus.bits.jabber_timeout = 1;
         return macState.txStatus;
    }

    // copy application data to the frame buffer
    memcpy(txBuffer + macState.txBufOfs, data, len);
    macState.txBufOfs += len;

    // TODO: if lastActivityTS > 0 then check for underflow; flush, return status=?
    // TODO: if !eof && threshold crossed then set/increase lastActivityTS

    // wait for more data if this is not the end of frame
    //if (!flags.bits.last_segment)
    //    return macState.txStatus;  // FIXME:

    unsigned int frameLen = macState.txBufOfs;
    macState.txBufOfs = 0U;  // expect SOF on next write

    // TODO: warn on Ethernet frame size error; skip? status=?

    // pad (MAC TFC) and add FCS (MAC CTX) as needed
    Bool padded = padTxFrame(txBuffer, &frameLen, flags);
    addTxFcs(txBuffer, frameLen, flags, padded);

    // write the frame to PHY
    phyWriteData(txBuffer, frameLen);

    // update status bits
    macState.txStatus.bits.vlan_frame = 0; //isVlanFrame(txBuffer); // FIXME:

    return macState.txStatus;

}

int gemMacbCanRead(void)
{
    if (!isRxEnabled())
        return False;

    // if no remaining frame data, try to get a new frame
    if (macState.rxFrameLen == 0U) {
        rxReadFrame();
    }

    return macState.rxFrameLen > 0U;
}

void gemMacbInit() {


    // Initialize state info
    initMacState(&macState);

    if (isLinkUp()) {
        bport1_ab_data.net_status.bits.pcs_link_state = 1;
    }
    else {
        bhmMessage("W", PREFIX,"MAC failed to open a backend Ethernet device\n");
    }
}

void incrStats() {
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I",PREFIX, "Increment Stats");

    bport1_ab_data.octets_tx_bot.value++;
    bport1_ab_data.octets_tx_top.value++;
    bport1_ab_data.frames_tx.value++;
    bport1_ab_data.broadcast_frames_tx.value++;
    bport1_ab_data.multi_frames_tx.value++;
    bport1_ab_data.pause_frames_tx.value++;
    bport1_ab_data.frames_64b_tx.value++;
    bport1_ab_data.frames_65to127b_tx.value++;
    bport1_ab_data.frames_128to255b_tx.value++;
    bport1_ab_data.frames_256to511b_tx.value++;
    bport1_ab_data.frames_512to1023b_tx.value++;
    bport1_ab_data.frames_1024to1518b_tx.value++;
    bport1_ab_data.frames_1519bplus_tx.value++;
    bport1_ab_data.tx_under_runs.value++;
    bport1_ab_data.single_collisn_frames.value++;
    bport1_ab_data.multi_collisn_frames.value++;
    bport1_ab_data.excessive_collisns.value++;
    bport1_ab_data.late_collisns.value++;
    bport1_ab_data.deferred_tx_frames.value++;
    bport1_ab_data.carrier_sense_errs.value++;
    bport1_ab_data.octets_rx_bot.value++;
    bport1_ab_data.octets_rx_top.value++;
    bport1_ab_data.frames_rx.value++;
    bport1_ab_data.bdcast_frames_rx.value++;
    bport1_ab_data.multi_frames_rx.value++;
    bport1_ab_data.pause_rx.value++;
    bport1_ab_data.frames_64b_rx.value++;
    bport1_ab_data.frames_65to127b_rx.value++;
    bport1_ab_data.frames_128to255b_rx.value++;
    bport1_ab_data.frames_256to511b_rx.value++;
    bport1_ab_data.frames_512to1023b_rx.value++;
    bport1_ab_data.frames_1024to1518b_rx.value++;
    bport1_ab_data.frames_1519bplus_rx.value++;
    bport1_ab_data.undersz_rx.value++;
    bport1_ab_data.oversz_rx.value++;
    bport1_ab_data.jab_rx.value++;
    bport1_ab_data.fcs_errors.value++;
    bport1_ab_data.length_field_errors.value++;
    bport1_ab_data.rx_symbol_errors.value++;
    bport1_ab_data.align_errors.value++;
    bport1_ab_data.rx_resource_errors.value++;
    bport1_ab_data.rx_overrun_errors.value++;
    bport1_ab_data.ip_hdr_csum_errors.value++;
    bport1_ab_data.tcp_csum_errors.value++;
    bport1_ab_data.udp_csum_errors.value++;

}

void clearStats() {
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I",PREFIX, "Clear Stats");


    bport1_ab_data.octets_tx_bot.value = 0;
    bport1_ab_data.octets_tx_top.value = 0;
    bport1_ab_data.frames_tx.value = 0;
    bport1_ab_data.broadcast_frames_tx.value = 0;
    bport1_ab_data.multi_frames_tx.value = 0;
    bport1_ab_data.pause_frames_tx.value = 0;
    bport1_ab_data.frames_64b_tx.value = 0;
    bport1_ab_data.frames_65to127b_tx.value = 0;
    bport1_ab_data.frames_128to255b_tx.value = 0;
    bport1_ab_data.frames_256to511b_tx.value = 0;
    bport1_ab_data.frames_512to1023b_tx.value = 0;
    bport1_ab_data.frames_1024to1518b_tx.value = 0;
    bport1_ab_data.frames_1519bplus_tx.value = 0;
    bport1_ab_data.tx_under_runs.value = 0;
    bport1_ab_data.single_collisn_frames.value = 0;
    bport1_ab_data.multi_collisn_frames.value = 0;
    bport1_ab_data.excessive_collisns.value = 0;
    bport1_ab_data.late_collisns.value = 0;
    bport1_ab_data.deferred_tx_frames.value = 0;
    bport1_ab_data.carrier_sense_errs.value = 0;
    bport1_ab_data.octets_rx_bot.value = 0;
    bport1_ab_data.octets_rx_top.value = 0;
    bport1_ab_data.frames_rx.value = 0;
    bport1_ab_data.bdcast_frames_rx.value = 0;
    bport1_ab_data.multi_frames_rx.value = 0;
    bport1_ab_data.pause_rx.value = 0;
    bport1_ab_data.frames_64b_rx.value = 0;
    bport1_ab_data.frames_65to127b_rx.value = 0;
    bport1_ab_data.frames_128to255b_rx.value = 0;
    bport1_ab_data.frames_256to511b_rx.value = 0;
    bport1_ab_data.frames_512to1023b_rx.value = 0;
    bport1_ab_data.frames_1024to1518b_rx.value = 0;
    bport1_ab_data.frames_1519bplus_rx.value = 0;
    bport1_ab_data.undersz_rx.value = 0;
    bport1_ab_data.oversz_rx.value = 0;
    bport1_ab_data.jab_rx.value = 0;
    bport1_ab_data.fcs_errors.value = 0;
    bport1_ab_data.length_field_errors.value = 0;
    bport1_ab_data.rx_symbol_errors.value = 0;
    bport1_ab_data.align_errors.value = 0;
    bport1_ab_data.rx_resource_errors.value = 0;
    bport1_ab_data.rx_overrun_errors.value = 0;
    bport1_ab_data.ip_hdr_csum_errors.value = 0;
    bport1_ab_data.tcp_csum_errors.value = 0;
    bport1_ab_data.udp_csum_errors.value = 0;

}

void updateInts(void)
{

    // get the new interrupt net state
    Bool irqWasAsserted = macState.irqAsserted;
    macState.irqAsserted = (bport1_ab_data.intr_status.value & bport1_ab_data.intr_mask.value) != 0;

    // update the interrupt net
    if (macState.irqAsserted != irqWasAsserted) {
        ppmWriteNet(macState.irqHandle, macState.irqAsserted);
        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Net irq %sasserted\n", (macState.irqAsserted ? "" : "de-"));
    }
}

PPM_REG_READ_CB(Readnet_ctrl) {
    // Mask off write-only registers
    return *(Uns32*)user & 0x0000819E;
}

PPM_REG_WRITE_CB(Writenet_ctrl) {

    Uns32 old_val = *(Uns32*)user;

    *(Uns32*)user = data;

    if (bport1_ab_data.net_ctrl.bits.flush_next_rx_dpram_) {
        flushRx();
    }

    if (bport1_ab_data.net_ctrl.bits.tx_pfc_pri_pri_pause_f) {
        pauseRx();
    }

    if (bport1_ab_data.net_ctrl.bits.en_pfc_pri_pause_rx) {
        //pauseRx();
    }

    if (bport1_ab_data.net_ctrl.bits.start_tx) {
        startTx();
    }

    if (bport1_ab_data.net_ctrl.bits.tx_halt) {
        haltTx();
    }

    if (bport1_ab_data.net_ctrl.bits.tx_pause_frame) {
        pauseTx(0);
    }

    if (bport1_ab_data.net_ctrl.bits.tx_zeroq_pause_frame) {
        pauseTx(1);
    }

    if (bport1_ab_data.net_ctrl.bits.incr_stat_regs) {
        incrStats();
    }

    if (bport1_ab_data.net_ctrl.bits.clear_stat_regs) {
        clearStats();
    }

    if (bport1_ab_data.net_ctrl.bits.rx_en && ((old_val & 0x04) == 0)) {
        startRx();
    }
}



PPM_REG_WRITE_CB(Writerx_status) {
    //Write to Clear (WTC) status bits.
    bport1_ab_data.rx_status.value &= ~(data) & 0x0000000F;
}

PPM_REG_WRITE_CB(Writetx_status) {
    //Write to Clear (WTC) status bits.
    bport1_ab_data.tx_status.value &= ~(data) & 0x000001FF;
}

PPM_REG_READ_CB(Readintr_status) {
  // Status values will be held in register.  However, only return asserted values for ones that are enabled.
    return *(Uns32*)user & bport1_ab_data.intr_mask.value;
}


PPM_REG_WRITE_CB(Writeintr_status) {
    //Write to Clear (WTC) status bits.
    bport1_ab_data.intr_status.value &= ~(data) & 0x07FFFEFF;
    updateInts();
}

PPM_REG_WRITE_CB(Writeintr_dis) {
    // Clear bits in mask
    bport1_ab_data.intr_mask.value &= (~(data) & 0x07FFFEFF);
    updateInts();

}

PPM_REG_WRITE_CB(Writeintr_en) {
    // Set bits in mask
    bport1_ab_data.intr_mask.value |= (data & 0x07FFFEFF);
    updateInts();
}


PPM_REG_WRITE_CB(Writeintr_mask) {
    // Writing to mask sets bits in status reg (for testing)
    bport1_ab_data.intr_status.value |= (data & 0x07FFFEFF);
    updateInts();
}



PPM_REG_WRITE_CB(Writephy_maint) {

    if (!bport1_ab_data.net_ctrl.bits.mgmt_port_en) {
      bhmMessage("W", PREFIX,"Write to phy_maint when management port not enabled.");
      return;
    }
    // YOUR CODE HERE (Writephy_maint)
    *(Uns32*)user = data;

    if (bport1_ab_data.phy_maint.bits.phy_addr != 7) {
        if (PSE_DIAG_HIGH)
            bhmMessage("I",PREFIX, "Ignoring PHY address %d", bport1_ab_data.phy_maint.bits.phy_addr);
        bport1_ab_data.phy_maint.bits.data = 0;
        return;
    }

    // PHY Write Operation
    if (bport1_ab_data.phy_maint.bits.operation == 0x1) {

        if (PSE_DIAG_HIGH)
            bhmMessage("I",PREFIX, "PHY Write to address 0x%x, reg addr 0x%x", bport1_ab_data.phy_maint.bits.phy_addr,  bport1_ab_data.phy_maint.bits.reg_addr);

        mdioWrite(bport1_ab_data.phy_maint.bits.reg_addr,data & 0x0000FFFF);

    // PHY Read Operation
    } else if (bport1_ab_data.phy_maint.bits.operation == 0x2) {

        if (PSE_DIAG_HIGH)
            bhmMessage("I",PREFIX,"PHY Read from address 0x%x, reg addr 0x%x", bport1_ab_data.phy_maint.bits.phy_addr, bport1_ab_data.phy_maint.bits.reg_addr);

        bport1_ab_data.phy_maint.bits.data = mdioRead(bport1_ab_data.phy_maint.bits.reg_addr);

    // Unknown operation
    } else {
        bhmMessage("W", PREFIX,"Unsupported PHY operation");
    }
}

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

#include "gem.h"
#include "net.h"

#include "gem_dma.h"
#include "gem_macb.h"


typedef struct DmaRxDesc {
    union {
      Uns32 data[2];
      struct {
        // Word 0
        unsigned owns : 1; // 0
        unsigned wrap : 1; // 1
        unsigned address : 30; // 31:2
        // Word1
        unsigned length : 13; // 12:0
        unsigned bad_fcs : 1;  // 13
        unsigned start_of_frame : 1;  // 14
        unsigned end_of_frame : 1; // 15
        unsigned cfi : 1; //16
        unsigned vlan_priority : 3; // 19:17
        unsigned priority_tag : 1; // 20
        unsigned vlan_tag : 1; // 21
        unsigned checksum_match : 2;  //23:22
        unsigned snap_encoded : 1;  // 24
        unsigned sar_num : 2; // 26:25
        unsigned sar_match : 1; // 27
        unsigned : 1; // 28
        unsigned unicast_match : 1; // 29
        unsigned multicast_match : 1; // 30
        unsigned broadcast : 1; // 31


      } bits;
    };
} DmaRxDescT;

typedef struct DmaTxDesc {
    union {
      Uns32 data[2];
      struct {
        // Word 0
        unsigned address : 32; // 31:0
        // Word1
        unsigned length : 14; // 13:0
        unsigned : 1;  // 14
        unsigned last_buffer : 1; // 15
        unsigned no_crc : 1; //16
        unsigned : 3; // 19:17
        unsigned checksum_error : 3; // 22:20
        unsigned : 3;  //25:23
        unsigned late_collision : 1; // 26
        unsigned frame_corrupt : 1; // 27
        unsigned : 1; // 28
        unsigned retry_limit : 1; // 29
        unsigned wrap : 1; // 30
        unsigned used : 1; // 31


      } bits;
    };
} DmaTxDescT;


typedef enum {
    txStopped = 0,
    txRunFetch,
    txRunWait,
    txRunRead,
    txTimeStmp,
    txReserve,
    txSuspTx,
    txRunClose
} TxSmState;

typedef enum {
    rxStopped = 0,
    rxRunFetch,
    rxReserve,
    rxRunWait,
    rxSuspRx,
    rxRunClose,
    rxTimeStmp,
    rxRunTrans
} RxSmState;

typedef struct {
    bhmThreadHandle       thread;
    bhmEventHandle        event;
    TxSmState             smState;
    Uns32                 queueBaseAddr;
  //  Bool                  txPollReq;
    Bool                  inReset;
    DmaTxDescT            txDesc;
} TxChannelState;

typedef struct {
    bhmThreadHandle       thread;
    bhmEventHandle        event;
    RxSmState             smState;
    Uns32                 queueBaseAddr;
  //  Bool                  rxPollReq;
    Bool                  inReset;
    Bool                  inFrame;
    Bool                  riwtEn;
    double                riwt;
    DmaRxDescT            rxDesc;
} RxChannelState;

typedef struct {
    ppmAddressSpaceHandle dataRWHandle;
    TxChannelState        txCh;
    RxChannelState        rxCh;
} DmaState, *DmaStateP;

Uns8 txBuffer[8192];
Uns8 rxBuffer[8192];

DmaState dmaState;

static double rxPollDelay = 1000.0; // 1ms

static inline Bool isTxReset(void)
{
    // check SW reset only; it is auto asserted on HW reset
    return dmaState.txCh.inReset;
}

static inline Bool isTxEnabled(void)
{
    return bport1_ab_data.net_ctrl.bits.tx_en;
}

static inline Bool isRxReset(void)
{
    // check SW reset only; it is auto asserted on HW reset
    return dmaState.rxCh.inReset;
}

static inline Bool isRxEnabled(void)
{
    return bport1_ab_data.net_ctrl.bits.rx_en;
}

static Bool txFetchDescriptor(DmaTxDescT *txDesc)
{
    // a transient state change
    dmaState.txCh.smState = txRunFetch;

    // fetch current descriptor through the master bus port
    Uns32 descAddr = bport1_ab_data.tx_qbar.value;
    int const descSize = sizeof(DmaTxDescT);
    ppmReadAddressSpace(dmaState.dataRWHandle, (Uns64)descAddr, descSize, (void *)txDesc);

    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Fetched %d bytes of Tx descriptor from address 0x%08x\ndesc[0]=0x%08x,desc[1]=0x%08x\n", descSize, descAddr, txDesc->data[0],txDesc->data[1]);

    if (txDesc->bits.used) {
        bport1_ab_data.intr_status.bits.tx_used_read = 1;
    }
    // return true if DMA owns the descriptor
    return !txDesc->bits.used;
}

static void txCloseDescriptor(DmaTxDescT *txDesc)
{
    // a transient state change
    dmaState.txCh.smState = txRunClose;

    // return descriptor ownership to SW
    txDesc->bits.used = 1;
    txDesc->bits.no_crc = 0;
    txDesc->bits.checksum_error = 0;
    txDesc->bits.late_collision = 0;
    txDesc->bits.frame_corrupt = 0;
    txDesc->bits.retry_limit = 0;

    // write current descriptor through the master bus port
    Uns32 descAddr = bport1_ab_data.tx_qbar.value;

    int const descSize = sizeof(DmaTxDescT);
    ppmWriteAddressSpace(dmaState.dataRWHandle, (Uns64)descAddr, descSize, (void *)txDesc);

    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Closed Tx descriptor at address 0x%08x; wrote %d bytes\n", descAddr, descSize);
}

static void txAdvanceDescriptor(DmaTxDescT *txDesc)
{
    // update current descriptor address
    Uns32 descAddr = bport1_ab_data.tx_qbar.value;
    int const descSize = sizeof(DmaTxDescT);

    if (txDesc->bits.wrap)

        descAddr = dmaState.txCh.queueBaseAddr;
    else
        descAddr += descSize;
    bport1_ab_data.tx_qbar.value = descAddr;

    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Advanced current Tx descriptor address to 0x%08x\n", descAddr);
}

static unsigned int txReadBuffer(DmaTxDescT *txDesc, Uns8 *buf, unsigned int bufSize)
{
    // copy descriptor's first buffer
    dmaState.txCh.smState = txRunRead;

    Uns32 bufAddr = txDesc->bits.address;
    unsigned int bufLen = txDesc->bits.length;
    if (bufLen > bufSize) {
        // TODO: handle buffer overflow
        bufLen = bufSize;
    }

    ppmReadAddressSpace(dmaState.dataRWHandle, (Uns64)bufAddr, bufLen, (void *)buf);

    if (PSE_DIAG_MEDIUM && bufLen > 0U)
        bhmMessage("I", PREFIX, "Read %d bytes Tx buffer from address 0x%08x\n", bufLen, bufAddr);

    return bufLen;
}

static void txStop(void)
{
    if (PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "Tx DMA channel stop\n");
    dmaState.txCh.smState = txStopped;
}

static void txReset(void)
{
    if (PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "Tx DMA channel reset\n");

    //dmaRegs->Status.bits.tps = 1;
  //  dmaState.txCh.txPollReq = False;
    dmaState.txCh.inReset = False;
    //updateSwr();
    dmaState.txCh.smState = txStopped;
}


static void txRun(void)
{
    DmaTxDescT *txDesc = &dmaState.txCh.txDesc;
    Bool lastSeg = False;
    unsigned int totalLen = 0U;

    if (PSE_DIAG_LOW && dmaState.txCh.smState == txStopped)
        bhmMessage("I", PREFIX, "Tx DMA channel start\n");
    else if (PSE_DIAG_MEDIUM && dmaState.txCh.smState == txSuspTx)
        bhmMessage("I", PREFIX, "Tx DMA channel resume\n");

    // fetch descriptors up to end of frame; read their buffers; send them to MAC
    while (!lastSeg && txFetchDescriptor(txDesc)) {
        lastSeg = txDesc->bits.last_buffer;
        unsigned int len = txReadBuffer(txDesc, txBuffer, sizeof(txBuffer));
        totalLen += len;

        // Write data to MAC
        gemMacbWriteData(txBuffer, len);
        if (!lastSeg) {
            txCloseDescriptor(txDesc);
            txAdvanceDescriptor(txDesc);
        }
    }

    if (!lastSeg) {
        // couldn't fetch all descriptors of the frame; suspend
        //dmaRegs->Status.bits.tu = 1;
        //dmaState.txCh.txPollReq = 0;
        dmaState.txCh.smState = txStopped;
        if (PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX, "No descriptor available; suspending Tx DMA channel\n");
    }
    else {
        //txCloseDescriptor(txDesc);
        // processed the whole frame; simulate MAC delay
        //dmaRegs->Status.bits.eti = 1;
        //dmaState.txCh.txPollReq = 0;
        dmaState.txCh.smState = txRunWait;
        double linkOctetDelay = 8 * 0.001;  // TODO: use current link speed
        double macWriteDelay = (totalLen + 20U) * linkOctetDelay;
        bhmTriggerAfter(dmaState.txCh.event, macWriteDelay); //TODO: simulate delay?
    }
}



static Bool rxFetchDescriptor(DmaRxDescT *rxDesc)
{
  // a transient state change
  dmaState.rxCh.smState = rxRunFetch;

  // fetch current descriptor through the master bus port
  Uns32 descAddr = bport1_ab_data.rx_qbar.value;
  int const descSize = sizeof(DmaRxDescT);
  ppmReadAddressSpace(dmaState.dataRWHandle, (Uns64)descAddr, descSize, (void *)rxDesc);

  if (PSE_DIAG_MEDIUM)
      bhmMessage("I", PREFIX, "Fetched %d bytes of Rx descriptor from address 0x%08x\ndesc[0]=0x%08x,desc[1]=0x%08x\n", descSize, descAddr, rxDesc->data[0],rxDesc->data[1]);

  if (rxDesc->bits.owns) {
    bport1_ab_data.intr_status.bits.rx_used_read = 1;
  }
  // return true if DMA owns the descriptor
  return !rxDesc->bits.owns;
}

static void rxCloseDescriptor(DmaRxDescT *rxDesc, Uns32 descAddr)
{
  // a transient state change
  dmaState.rxCh.smState = rxRunClose;

/*  // return descriptor ownership to SW
  rxDesc->bits.used = 1;
  rxDesc->bits.no_crc = 0;
  rxDesc->bits.checksum_error = 0;
  rxDesc->bits.late_collision = 0;
  rxDesc->bits.frame_corrupt = 0;
  rxDesc->bits.retry_limit = 0;
*/
  // write current descriptor through the master bus port
//  Uns32 descAddr = bport1_ab_data.rx_qbar.value;

  int const descSize = sizeof(DmaRxDescT);
  ppmWriteAddressSpace(dmaState.dataRWHandle, (Uns64)descAddr, descSize, (void *)rxDesc);

  if (PSE_DIAG_MEDIUM)
      bhmMessage("I", PREFIX, "Closed Rx descriptor at address 0x%08x; wrote %d bytes\n", descAddr, descSize);

}

static void rxAdvanceDescriptor(DmaRxDescT *rxDesc)
{

  // update current descriptor address
  Uns32 descAddr = bport1_ab_data.rx_qbar.value;
  int const descSize = sizeof(DmaRxDescT);

  if (rxDesc->bits.wrap)

      descAddr = dmaState.rxCh.queueBaseAddr;
  else
      descAddr += descSize;
  bport1_ab_data.rx_qbar.value = descAddr;

  if (PSE_DIAG_MEDIUM)
      bhmMessage("I", PREFIX, "Advanced current Rx descriptor address to 0x%08x\n", descAddr);

}

static unsigned int rxRecvData(Uns32 bufAddr, unsigned int bufSize, DmaRxDescT *rxDesc)
{
    unsigned int totalLen = bufSize;
    Bool eof = False;

    rxDesc->bits.start_of_frame = 1;

    while (bufSize > 0U && !eof) {
        unsigned int len = (bufSize < sizeof(rxBuffer)) ? bufSize : sizeof(rxBuffer);

        // copy data from MAC to the buffer
        GemRxStatusT status = gemMacbReadData(rxBuffer, len);
        len = status.bits.frame_length;
        ppmWriteAddressSpace(dmaState.dataRWHandle, (Uns64)bufAddr, len, (void *)rxBuffer);
        bufSize -= len;
        bufAddr += len;

        eof = status.bits.end_of_frame;
        rxDesc->bits.end_of_frame = eof;
        rxDesc->bits.length = len;
        rxDesc->bits.broadcast = 0;
        rxDesc->bits.bad_fcs = 0;
        rxDesc->bits.owns = 1;
        bport1_ab_data.rx_status.bits.frame_recd = 1;
        bport1_ab_data.rx_status.bits.buffer_not_avail = 0;
    }

    totalLen -= bufSize;

    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Read %d bytes of Rx data from the MAC\n", totalLen);

    return totalLen;
}

static unsigned int rxStoreData(DmaRxDescT *rxDesc)
{
    // copy descriptor's first buffer
    dmaState.rxCh.smState = rxRunTrans;
    Uns32 bufAddr = rxDesc->bits.address << 2;
    bufAddr += bport1_ab_data.net_cfg.bits.rx_buf_offset;
    unsigned int bufSize = bport1_ab_data.net_cfg.bits.rx_1536_byte_frames ? 1536 : 1518;
    unsigned int len = rxRecvData(bufAddr, bufSize, rxDesc);
    unsigned int totalLen = len;

    if (PSE_DIAG_MEDIUM && len > 0U)
        bhmMessage("I", PREFIX, "Wrote %d bytes to Rx buffer at address 0x%08x\n", len, bufAddr);

    return totalLen;
}

static void rxSuspend(Bool flush)
{
  /*  if (flush && !dmaRegs->Operation_Mode.bits.dff) {
        emacGmacFlushRx();
    }

    if (DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "No descriptor available; suspending Rx DMA channel\n");

    bhmTriggerAfter(dmaState.rxCh.event, rxPollDelay);
    dmaRegs->Status.bits.ru = 1;
  */  //dmaState.rxCh.rxPollReq = False;
    dmaState.rxCh.smState = rxSuspRx;
}

static inline void rxDelay(double uSec)
{
    bhmTriggerAfter(dmaState.rxCh.event, uSec);
    dmaState.rxCh.smState = rxRunWait;
}

static void rxRun(Bool fetch)
{
    if (PSE_DIAG_LOW && dmaState.rxCh.smState == rxStopped)
        bhmMessage("I", PREFIX, "Rx DMA channel start\n");
    else if (PSE_DIAG_MEDIUM && dmaState.rxCh.smState == rxSuspRx)
        bhmMessage("I", PREFIX, "Rx DMA channel resume\n");

    DmaRxDescT *rxDesc = &dmaState.rxCh.rxDesc;
    Bool lastSeg = !dmaState.rxCh.inFrame;
    Bool ownDesc = !fetch || rxFetchDescriptor(rxDesc);
    Uns32 frameLen = 0U;

    // transfer available MAC data to memory up to end of frame or end of available descriptors
    while (True) {
        if (!ownDesc) {
            // no descriptor available; flush incomplete data (if allowed) and suspend
            rxSuspend(!lastSeg);
            bport1_ab_data.intr_status.bits.rx_used_read = 1;
            break;
        }

        // for simplicity, rxDataAvailable should go false only between frames
        if (!gemMacbCanRead()) {
            // no more Rx data is available now, wait for new data
            rxDelay(rxPollDelay);
            break;
        }

        Uns32 len = rxStoreData(rxDesc);    // copy data from MAC to rxDesc's buffers
        frameLen += len;
      //  RX_DESC_FLAG(rxDesc, frame_length) = frameLen;
        lastSeg = rxDesc->bits.end_of_frame;
    //

        // a new descriptor is needed before closing an intermediate one (to set flags)
        DmaRxDescT nextRxDesc;
        Uns32 lastDescAddr = bport1_ab_data.rx_qbar.value;
        rxAdvanceDescriptor(rxDesc);
        ownDesc = rxFetchDescriptor(&nextRxDesc);

        rxCloseDescriptor(rxDesc, lastDescAddr);
  //      rxIrq(rxDesc);
        *rxDesc = nextRxDesc;
        dmaState.rxCh.inFrame = !rxDesc->bits.end_of_frame;

        if (lastSeg && ownDesc) {
             bport1_ab_data.intr_status.bits.rx_complete = 1;
            // complete frame was received, simulate IO delay
            double ioDelay = 1.0;   // TODO: use frame_sim_time - current_sim_time
            rxDelay(ioDelay);
            break;
        }
    }

    // check if RI watchdog timer has expired
  //  riwtCheck();*/
}




static void rxStop(void)
{
    if (PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "Rx DMA channel stop\n");
    //dmaRegs->Status.bits.rps = 1; // FIXME:
    dmaState.rxCh.smState = rxStopped;
    //riwtDisable();
}

static void rxReset(void)
{
    if (PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "Rx DMA channel reset\n");
    //dmaState.rxCh.rxPollReq = False;
    dmaState.rxCh.inFrame = False;
    dmaState.rxCh.inReset = False;
    dmaState.rxCh.riwtEn = False;
    dmaState.rxCh.riwt = 0.0;
    //updateSwr();
    dmaState.rxCh.smState = rxStopped;
}


static void rxThread(void *user)
{
    for (;;) {
        //if (PSE_DIAG_HIGH)
        //    bhmMessage("I", PREFIX, "Rx DMA channel waiting, state=%d\n", (int)dmaState.rxCh.smState); //TODO: Temporarily commented out

        bhmRestartReason rr = bhmWaitEvent(dmaState.rxCh.event);
        if (rr != BHM_RR_TRIGGERED)
            break;

        // check for reset
        if (isRxReset()) {
            rxReset();
        }
        else {
            //if (PSE_DIAG_HIGH)
            //    bhmMessage("I", PREFIX, "Rx channel running, state=%d\n", (int)dmaState.rxCh.smState); //TODO: Temporarily commented out

            // perform an Rx DMA operation, according to current state
            switch (dmaState.rxCh.smState) {
              case rxStopped:
                if (isRxEnabled()) {
                    rxRun(True);
                }
                break;

              case rxRunWait:
                if (!isRxEnabled())
                    rxStop();
                else
                    rxRun(False);
                break;

              case rxSuspRx:
                if (!isRxEnabled())
                    rxStop();
                else
                    rxRun(True);
                break;

              default:
                // should not get here; other Rx states are transient
                break;
            }
        }

        // update Rx state in status register
        //dmaRegs->Status.bits.rs = dmaState.rxCh.smState;
        updateInts();
    }
}


static void txThread(void *user)
{
    for (;;) {
        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Tx DMA channel waiting, state=%d\n", (int)dmaState.txCh.smState);

        bhmRestartReason rr = bhmWaitEvent(dmaState.txCh.event);
        if (rr != BHM_RR_TRIGGERED)
            break;

        // check for reset
        if (isTxReset()) {
            // TODO: close the descriptor if in txRunWait state?
            txReset();
        }
        else {
            if (PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX, "Tx DMA channel running, state=%d\n", (int)dmaState.txCh.smState);

            // perform a Tx DMA operation, according to current state
            switch (dmaState.txCh.smState) {
              case txStopped:
                if (isTxEnabled()) {
                    txRun();
                }
                break;

              case txRunWait:
                txCloseDescriptor(&dmaState.txCh.txDesc);
                txAdvanceDescriptor(&dmaState.txCh.txDesc);
                bport1_ab_data.intr_status.bits.tx_complete = 1;
                bport1_ab_data.tx_status.bits.tx_complete = 1;
                //txDoneIrq(&dmaState.txCh.txDesc);
                if (!isTxEnabled())
                    txStop();
                else
                    // TODO: restart delay waiting if Tx not done
                    txRun();
                break;

              case txSuspTx:
                if (!isTxEnabled())
                    txStop();
                else //if (isTxPollRequested()) //TODO:
                    txRun();
                break;

              default:
                // should not get here; other Tx states are transient
                break;
            }
        }

        // update Tx state in status register
        //dmaRegs->Status.bits.ts = dmaState.txCh.smState;
        updateInts();

    }
}


void flushRx(void) {
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I",PREFIX, "Flush RX");

}
void pauseRx(void) {
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I",PREFIX, "Pause RX");

}

void startRx(void) {
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I",PREFIX, "Start RX");
    if (dmaState.rxCh.smState == rxStopped)
        bhmTriggerAfter(dmaState.rxCh.event, 0);
}


void startTx(void) {
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I",PREFIX, "Start Transmission");

    if (dmaState.txCh.smState == txStopped)
        bhmTriggerAfter(dmaState.txCh.event, 0);

}


void haltTx(void) {
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I",PREFIX, "Halt TX");
}

void pauseTx(int zq) {
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I",PREFIX, "Pause TX");

}


void gemDmaInit() {
    if (PSE_DIAG_LOW)
        bhmMessage("I", PREFIX,"DMA initialization\n");

        // Initialize DMA state info
    dmaState.dataRWHandle = handles.bport2;


    txReset();
    rxReset();

    // Create DMA engine threads
    dmaState.txCh.event = bhmCreateEvent();
    dmaState.txCh.thread = bhmCreateThread(txThread, (void *)0, "DMA_Tx", 0);
    dmaState.rxCh.event = bhmCreateEvent();
    dmaState.rxCh.thread = bhmCreateThread(rxThread, (void *)0, "DMA_Rx", 0);

}

void gemDmaDestroy(void)
{
    if (PSE_DIAG_LOW)
        bhmMessage("I", PREFIX,"DMA termination\n");

    // Release DMA resources (unconditionally, no pending events processing)
    bhmDeleteThread(dmaState.rxCh.thread);
    dmaState.rxCh.thread = (bhmThreadHandle)0;
    bhmDeleteEvent(dmaState.rxCh.event);
    dmaState.rxCh.event = (bhmEventHandle)0;
    bhmDeleteThread(dmaState.txCh.thread);
    dmaState.txCh.thread = (bhmThreadHandle)0;
    bhmDeleteEvent(dmaState.txCh.event);
    dmaState.txCh.event = (bhmEventHandle)0;
}





PPM_REG_WRITE_CB(Writerx_qbar) {
    if (!bport1_ab_data.net_ctrl.bits.rx_en) {
      *(Uns32*)user = data;
      dmaState.rxCh.queueBaseAddr = data;
    } else {
      if (PSE_DIAG_MEDIUM)
          bhmMessage("I",PREFIX, "rx_qbar write ignored when RX is enabled");
    }


}

PPM_REG_WRITE_CB(Writetx_qbar) {
  if (!bport1_ab_data.net_ctrl.bits.tx_en) {
    *(Uns32*)user = data;
    dmaState.txCh.queueBaseAddr = data;
  } else {
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I",PREFIX, "tx_qbar write ignored when TX is enabled");
  }
}

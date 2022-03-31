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

#ifndef PSE_IGEN_H
#define PSE_IGEN_H                      

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/bhmHttp.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

#ifdef _PSE_
//////////////////////////////////// Externs ///////////////////////////////////

extern Uns32 diagnosticLevel;


/////////////////////////// Dynamic Diagnostic Macros //////////////////////////

// Bottom two bits of word used for PSE diagnostics
#define PSE_DIAG_LOW                    (BHM_DIAG_MASK_LOW(diagnosticLevel))
#define PSE_DIAG_MEDIUM                 (BHM_DIAG_MASK_MEDIUM(diagnosticLevel))

#define PSE_DIAG_HIGH                   (BHM_DIAG_MASK_HIGH(diagnosticLevel))
// Next two bits of word used for PSE semihost/intercept library diagnostics
#define PSE_DIAG_SEMIHOST               (BHM_DIAG_MASK_SEMIHOST(diagnosticLevel))

#endif
/////////////////////////// Register data declaration //////////////////////////

typedef struct bport1_ab_dataS { 
    union { 
        Uns32 value;
    } RX_DATA_FIFO;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_1;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_2;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_3;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_4;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_5;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_6;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_7;
    union { 
        Uns32 value;
    } TX_DATA_FIFO;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_1;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_2;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_3;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_4;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_5;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_6;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_7;
    union { 
        Uns32 value;
    } RX_STATUS_FIFO;
    union { 
        Uns32 value;
    } RX_STATUS_FIFO_PEEK;
    union { 
        Uns32 value;
    } TX_STATUS_FIFO;
    union { 
        Uns32 value;
    } TX_STATUS_FIFO_PEEK;
    union { 
        Uns32 value;
        struct {
            Uns32 REV : 16;
            Uns32 ID : 16;
        } bits;
    } ID_REV;
    union { 
        Uns32 value;
        struct {
            Uns32 IRQ_TYPE : 1;
            Uns32 __pad1 : 3;
            Uns32 IRQ_POL : 1;
            Uns32 __pad5 : 3;
            Uns32 IRQ_EN : 1;
            Uns32 __pad9 : 3;
            Uns32 IRQ_INT : 1;
            Uns32 INT_DEAS_STS : 1;
            Uns32 INT_DEAS_CLR : 1;
            Uns32 __pad15 : 9;
            Uns32 INT_DEAS : 8;
        } bits;
    } IRQ_CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 GPIOx_INT : 3;
            Uns32 RSFL : 1;
            Uns32 RSFF : 1;
            Uns32 __pad5 : 1;
            Uns32 RXDF_INT : 1;
            Uns32 TSFL : 1;
            Uns32 TSFF : 1;
            Uns32 TDFA : 1;
            Uns32 TDFO : 1;
            Uns32 __pad11 : 2;
            Uns32 TXE : 1;
            Uns32 RXE : 1;
            Uns32 RWT : 1;
            Uns32 TXSO : 1;
            Uns32 PME_INT : 1;
            Uns32 PHY_INT : 1;
            Uns32 GPT_INT : 1;
            Uns32 RXD_INT : 1;
            Uns32 TX_IOC : 1;
            Uns32 __pad22 : 1;
            Uns32 RXDFH_INT : 1;
            Uns32 RXSTOP_INT : 1;
            Uns32 TXSTOP_INT : 1;
            Uns32 __pad26 : 5;
            Uns32 SW_INT : 1;
        } bits;
    } INT_STS;
    union { 
        Uns32 value;
        struct {
            Uns32 GPIOx_INT_EN : 3;
            Uns32 RSFL_INT_EN : 1;
            Uns32 RSFF_INT_EN : 1;
            Uns32 __pad5 : 1;
            Uns32 RXDF_INT_EN : 1;
            Uns32 TSFL_INT_EN : 1;
            Uns32 TSFF_INT_EN : 1;
            Uns32 TDFA_INT_EN : 1;
            Uns32 TDFO_INT_EN : 1;
            Uns32 __pad11 : 2;
            Uns32 TXE_INT_EN : 1;
            Uns32 RXE_INT_EN : 1;
            Uns32 RWT_INT_EN : 1;
            Uns32 TXSO_EN : 1;
            Uns32 PME_INT_EN : 1;
            Uns32 PHY_INT_EN : 1;
            Uns32 GPT_INT_EN : 1;
            Uns32 RXD_INT : 1;
            Uns32 TIOC_INT_EN : 1;
            Uns32 __pad22 : 1;
            Uns32 RXDFH_INT_EN : 1;
            Uns32 RXSTOP_INT_EN : 1;
            Uns32 TXSTOP_INT_EN : 1;
            Uns32 __pad26 : 5;
            Uns32 SW_INT_EN : 1;
        } bits;
    } INT_EN;
    union { 
        Uns32 value;
    } BYTE_TEST;
    union { 
        Uns32 value;
        struct {
            Uns32 RXStatusL : 8;
            Uns32 __pad8 : 8;
            Uns32 TXStatusL : 8;
            Uns32 TXDataAvailL : 8;
        } bits;
    } FIFO_INT;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 8;
            Uns32 RXDOFF : 5;
            Uns32 __pad13 : 2;
            Uns32 RX_DUMP : 1;
            Uns32 RX_DMA_CNT : 12;
            Uns32 __pad28 : 2;
            Uns32 RXEndAlign : 2;
        } bits;
    } RX_CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 STOP_TX : 1;
            Uns32 TX_ON : 1;
            Uns32 TXSAO : 1;
            Uns32 __pad3 : 11;
            Uns32 TXD_DUMP : 1;
            Uns32 TXS_DUMP : 1;
        } bits;
    } TX_CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 SRST : 1;
            Uns32 SRST_TO : 1;
            Uns32 MODE1632 : 1;
            Uns32 __pad3 : 13;
            Uns32 TX_FIF_SZ : 4;
            Uns32 MBO : 1;
        } bits;
    } HW_CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 31;
            Uns32 RX_FFWD : 1;
        } bits;
    } RX_DP_CTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDUSED : 16;
            Uns32 RXSUSED : 8;
        } bits;
    } RX_FIFO_INF;
    union { 
        Uns32 value;
        struct {
            Uns32 TXDFREE : 16;
            Uns32 TXSUSED : 8;
        } bits;
    } TX_FIFO_INF;
    union { 
        Uns32 value;
        struct {
            Uns32 READY : 1;
            Uns32 PME_EN : 1;
            Uns32 PME_POL : 1;
            Uns32 PME_IND : 1;
            Uns32 WUPS : 2;
            Uns32 PME_TYPE : 1;
            Uns32 __pad7 : 1;
            Uns32 ED_EN : 1;
            Uns32 WOL_EN : 1;
            Uns32 PHY_RST : 1;
            Uns32 __pad11 : 1;
            Uns32 PM_MODE : 2;
        } bits;
    } PMT_CTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 GPIODn : 3;
            Uns32 GPODn : 2;
            Uns32 __pad5 : 3;
            Uns32 GPDIRn : 3;
            Uns32 __pad11 : 5;
            Uns32 GPIOBUFn : 3;
            Uns32 __pad19 : 1;
            Uns32 EEPR_EN : 3;
            Uns32 __pad23 : 1;
            Uns32 GPIO_INT_POL : 3;
            Uns32 __pad27 : 1;
            Uns32 LEDx_EN : 3;
        } bits;
    } GPIO_CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 GPT_LOAD : 16;
            Uns32 __pad16 : 13;
            Uns32 TIMER_EN : 1;
        } bits;
    } GPT_CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 GPT_CNT : 16;
        } bits;
    } GPT_CNT;
    union { 
        Uns32 value;
    } WORD_SWAP;
    union { 
        Uns32 value;
        struct {
            Uns32 FR_CNT : 32;
        } bits;
    } FREE_RUN;
    union { 
        Uns32 value;
        struct {
            Uns32 RX_DFC : 32;
        } bits;
    } RX_DROP;
    union { 
        Uns32 value;
        struct {
            Uns32 CSRAddress : 8;
            Uns32 __pad8 : 22;
            Uns32 RnW : 1;
            Uns32 CSRBusy : 1;
        } bits;
    } MAC_CSR_CMD;
    union { 
        Uns32 value;
        struct {
            Uns32 MACCSRData : 32;
        } bits;
    } MAC_CSR_DATA;
    union { 
        Uns32 value;
        struct {
            Uns32 FCANY : 1;
            Uns32 FCADD : 1;
            Uns32 FCBRD : 1;
            Uns32 FCMULT : 1;
            Uns32 BACK_DUR : 4;
            Uns32 AFC_LO : 8;
            Uns32 AFC_HI : 8;
        } bits;
    } AFC_CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 EPCAddr : 8;
            Uns32 MACAddrLoaded : 1;
            Uns32 EPCTimeout : 1;
            Uns32 __pad10 : 18;
            Uns32 EPCcommand : 3;
            Uns32 EPCBusy : 1;
        } bits;
    } E2P_CMD;
    union { 
        Uns32 value;
        struct {
            Uns32 EEPROMData : 8;
        } bits;
    } E2P_DATA;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq;
    ppmPacketnetHandle    phy;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(byteTest);
PPM_REG_READ_CB(defaultRdCB);
PPM_REG_WRITE_CB(defaultWrCB);
PPM_REG_READ_CB(hwCfgRd);
PPM_REG_WRITE_CB(hwCfgWr);
PPM_REG_READ_CB(idRev);
PPM_REG_READ_CB(intEnRd);
PPM_REG_WRITE_CB(intEnWr);
PPM_REG_READ_CB(intStsRd);
PPM_REG_WRITE_CB(intStsWr);
PPM_REG_READ_CB(irqCfgRd);
PPM_REG_WRITE_CB(irqCfgWr);
PPM_REG_READ_CB(macCsrCmdRd);
PPM_REG_WRITE_CB(macCsrCmdWr);
PPM_REG_READ_CB(macCsrDataRd);
PPM_REG_WRITE_CB(macCsrDataWr);
PPM_REG_READ_CB(rxCfgRd);
PPM_REG_WRITE_CB(rxCfgWr);
PPM_REG_READ_CB(rxDropRd);
PPM_REG_READ_CB(rxFifoInfRd);
PPM_REG_READ_CB(rxFifoRd);
PPM_REG_READ_CB(rxStatusFifoPeek);
PPM_REG_READ_CB(rxStatusFifoRd);
PPM_REG_READ_CB(txCfgRd);
PPM_REG_WRITE_CB(txCfgWr);
PPM_REG_READ_CB(txFifoInfRd);
PPM_REG_WRITE_CB(txFifoWr);
PPM_REG_READ_CB(txStatusFifoPeek);
PPM_REG_READ_CB(txStatusFifoRd);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_RX_DATA_FIFO_WIDTH    32
#define BPORT1_AB_RX_DATA_FIFO_1_WIDTH  32
#define BPORT1_AB_RX_DATA_FIFO_2_WIDTH  32
#define BPORT1_AB_RX_DATA_FIFO_3_WIDTH  32
#define BPORT1_AB_RX_DATA_FIFO_4_WIDTH  32
#define BPORT1_AB_RX_DATA_FIFO_5_WIDTH  32
#define BPORT1_AB_RX_DATA_FIFO_6_WIDTH  32
#define BPORT1_AB_RX_DATA_FIFO_7_WIDTH  32
#define BPORT1_AB_TX_DATA_FIFO_WIDTH    32
#define BPORT1_AB_TX_DATA_FIFO_1_WIDTH  32
#define BPORT1_AB_TX_DATA_FIFO_2_WIDTH  32
#define BPORT1_AB_TX_DATA_FIFO_3_WIDTH  32
#define BPORT1_AB_TX_DATA_FIFO_4_WIDTH  32
#define BPORT1_AB_TX_DATA_FIFO_5_WIDTH  32
#define BPORT1_AB_TX_DATA_FIFO_6_WIDTH  32
#define BPORT1_AB_TX_DATA_FIFO_7_WIDTH  32
#define BPORT1_AB_RX_STATUS_FIFO_WIDTH  32
#define BPORT1_AB_RX_STATUS_FIFO_PEEK_WIDTH  32
#define BPORT1_AB_TX_STATUS_FIFO_WIDTH  32
#define BPORT1_AB_TX_STATUS_FIFO_PEEK_WIDTH  32
#define BPORT1_AB_ID_REV_WIDTH          32
#define BPORT1_AB_IRQ_CFG_WIDTH         32
#define BPORT1_AB_INT_STS_WIDTH         32
#define BPORT1_AB_INT_EN_WIDTH          32
#define BPORT1_AB_BYTE_TEST_WIDTH       32
#define BPORT1_AB_FIFO_INT_WIDTH        32
#define BPORT1_AB_RX_CFG_WIDTH          32
#define BPORT1_AB_TX_CFG_WIDTH          32
#define BPORT1_AB_HW_CFG_WIDTH          32
#define BPORT1_AB_RX_DP_CTRL_WIDTH      32
#define BPORT1_AB_RX_FIFO_INF_WIDTH     32
#define BPORT1_AB_TX_FIFO_INF_WIDTH     32
#define BPORT1_AB_PMT_CTRL_WIDTH        32
#define BPORT1_AB_GPIO_CFG_WIDTH        32
#define BPORT1_AB_GPT_CFG_WIDTH         32
#define BPORT1_AB_GPT_CNT_WIDTH         32
#define BPORT1_AB_WORD_SWAP_WIDTH       32
#define BPORT1_AB_FREE_RUN_WIDTH        32
#define BPORT1_AB_RX_DROP_WIDTH         32
#define BPORT1_AB_MAC_CSR_CMD_WIDTH     32
#define BPORT1_AB_MAC_CSR_DATA_WIDTH    32
#define BPORT1_AB_AFC_CFG_WIDTH         32
#define BPORT1_AB_E2P_CMD_WIDTH         32
#define BPORT1_AB_E2P_DATA_WIDTH        32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

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

typedef struct bpAXI_abm_dataS { 
} bpAXI_abm_dataT, *bpAXI_abm_dataTP;

typedef struct bpAPB_ab_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 mode_sel : 1;
            Uns32 clk_pol : 1;
            Uns32 clk_ph : 1;
            Uns32 baud_rate_dic : 3;
            Uns32 fifo_width : 2;
            Uns32 ref_clk : 1;
            Uns32 __pad9 : 1;
            Uns32 pcs : 1;
            Uns32 __pad11 : 4;
            Uns32 manual_cs : 1;
            Uns32 man_start_com : 1;
            Uns32 __pad17 : 2;
            Uns32 holdb_dr : 1;
            Uns32 __pad20 : 6;
            Uns32 endian : 1;
            Uns32 __pad27 : 4;
            Uns32 leg_flsh : 1;
        } bits;
    } Config_reg;
    union { 
        Uns32 value;
        struct {
            Uns32 RXOVR : 1;
            Uns32 __pad1 : 1;
            Uns32 TXOW : 1;
            Uns32 TXFULL : 1;
            Uns32 RXNEMPTY : 1;
            Uns32 RXFULL : 1;
            Uns32 TXUF : 1;
        } bits;
    } Intr_status_REG;
    union { 
        Uns32 value;
        struct {
            Uns32 RXOVR : 1;
            Uns32 __pad1 : 1;
            Uns32 TXOW : 1;
            Uns32 TXFULL : 1;
            Uns32 RXNEMPTY : 1;
            Uns32 RXFULL : 1;
            Uns32 TXUF : 1;
        } bits;
    } Intrpt_en_REG;
    union { 
        Uns32 value;
        struct {
            Uns32 RXOVR : 1;
            Uns32 __pad1 : 1;
            Uns32 TXOW : 1;
            Uns32 TXFULL : 1;
            Uns32 RXNEMPTY : 1;
            Uns32 RXFULL : 1;
            Uns32 TXUF : 1;
        } bits;
    } Intrpt_dis_REG;
    union { 
        Uns32 value;
        struct {
            Uns32 RXOVR : 1;
            Uns32 __pad1 : 1;
            Uns32 TXOW : 1;
            Uns32 TXFULL : 1;
            Uns32 RXNEMPTY : 1;
            Uns32 RXFULL : 1;
            Uns32 TXUF : 1;
        } bits;
    } Intrpt_mask_REG;
    union { 
        Uns32 value;
        struct {
            Uns32 ENABLE : 1;
        } bits;
    } En_REG;
    union { 
        Uns32 value;
        struct {
            Uns32 INIT : 8;
            Uns32 AFTER : 8;
            Uns32 BTWN : 8;
            Uns32 NSS : 8;
        } bits;
    } Delay_REG;
    union { 
        Uns32 value;
    } TXD0;
    union { 
        Uns32 value;
    } Rx_data_REG;
    union { 
        Uns32 value;
        struct {
            Uns32 MASK : 8;
        } bits;
    } Slave_Idle_count_REG;
    union { 
        Uns32 value;
    } TX_thres_REG;
    union { 
        Uns32 value;
    } RX_thres_REG;
    union { 
        Uns32 value;
        struct {
            Uns32 WP : 1;
        } bits;
    } GPIO;
    union { 
        Uns32 value;
    } LPBK_DLY_ADJ;
    union { 
        Uns32 value;
    } TXD1;
    union { 
        Uns32 value;
    } TXD2;
    union { 
        Uns32 value;
    } TXD3;
    union { 
        Uns32 value;
        struct {
            Uns32 INST : 8;
            Uns32 DUMMY : 3;
            Uns32 __pad11 : 5;
            Uns32 MODE_BITS : 8;
            Uns32 MODE_ON : 1;
            Uns32 MODE_EN : 1;
            Uns32 __pad26 : 2;
            Uns32 U_PAGE : 1;
            Uns32 SEP_BUS : 1;
            Uns32 TWO_MEM : 1;
            Uns32 LQ_MODE : 1;
        } bits;
    } LQSPI_CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 1;
            Uns32 WR_RECVD : 1;
            Uns32 D_FSM_ERR : 1;
        } bits;
    } LQSPI_STS;
    union { 
        Uns32 value;
    } MOD_ID;
} bpAPB_ab_dataT, *bpAPB_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bpAXI_abm_dataT bpAXI_abm_data;

extern bpAPB_ab_dataT bpAPB_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bpAXI;
    void                 *bpAPB;
    ppmNetHandle          interrupt;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(rtnZero);
PPM_REG_READ_CB(rxData);
PPM_REG_WRITE_CB(txData0);
PPM_REG_WRITE_CB(txData1);
PPM_REG_WRITE_CB(txData2);
PPM_REG_WRITE_CB(txData3);
PPM_REG_WRITE_CB(wrConfig);
PPM_REG_WRITE_CB(wrEn);
PPM_REG_WRITE_CB(wrIntDis);
PPM_REG_WRITE_CB(wrIntEn);
PPM_REG_WRITE_CB(wrIntStat);
PPM_READ_CB(regNoDefinitionRead);
PPM_WRITE_CB(regNoDefinitionWrite);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bpAXI/abm/flash : (for example)
// char value = ((char*)handles.bpAXI)[BPAXI_ABM_FLASH_OFFSET + myAddress];

#define BPAXI_ABM_FLASH_OFFSET          0x0
#define BPAXI_ABM_FLASH_SIZE            0x2000000

// To access local memory bpAPB/ab/buffer : (for example)
// char value = ((char*)handles.bpAPB)[BPAPB_AB_BUFFER_OFFSET + myAddress];

#define BPAPB_AB_BUFFER_OFFSET          0x0
#define BPAPB_AB_BUFFER_SIZE            0x1000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPAPB_AB_CONFIG_REG_WRMASK      0x8409ffff
#define BPAPB_AB_CONFIG_REG_WRNMASK     (0x7bf60000)
#define BPAPB_AB_CONFIG_REG_WIDTH       32
#define BPAPB_AB_INTR_STATUS_REG_WRMASK  0x41
#define BPAPB_AB_INTR_STATUS_REG_WRNMASK  (0xffffffbe)
#define BPAPB_AB_INTR_STATUS_REG_WIDTH  32
#define BPAPB_AB_INTRPT_EN_REG_WRMASK   0x7d
#define BPAPB_AB_INTRPT_EN_REG_WRNMASK  (0xffffff82)
#define BPAPB_AB_INTRPT_EN_REG_WIDTH    32
#define BPAPB_AB_INTRPT_DIS_REG_WRMASK  0x7d
#define BPAPB_AB_INTRPT_DIS_REG_WRNMASK  (0xffffff82)
#define BPAPB_AB_INTRPT_DIS_REG_WIDTH   32
#define BPAPB_AB_INTRPT_MASK_REG_WIDTH  32
#define BPAPB_AB_EN_REG_WRMASK          0x1
#define BPAPB_AB_EN_REG_WRNMASK         (0xfffffffe)
#define BPAPB_AB_EN_REG_WIDTH           32
#define BPAPB_AB_DELAY_REG_WIDTH        32
#define BPAPB_AB_TXD0_WIDTH             32
#define BPAPB_AB_RX_DATA_REG_WIDTH      32
#define BPAPB_AB_SLAVE_IDLE_COUNT_REG_WRMASK  0xff
#define BPAPB_AB_SLAVE_IDLE_COUNT_REG_WRNMASK  (0xffffff00)
#define BPAPB_AB_SLAVE_IDLE_COUNT_REG_WIDTH  32
#define BPAPB_AB_TX_THRES_REG_WIDTH     32
#define BPAPB_AB_RX_THRES_REG_WIDTH     32
#define BPAPB_AB_GPIO_WIDTH             32
#define BPAPB_AB_LPBK_DLY_ADJ_WIDTH     32
#define BPAPB_AB_TXD1_WIDTH             32
#define BPAPB_AB_TXD2_WIDTH             32
#define BPAPB_AB_TXD3_WIDTH             32
#define BPAPB_AB_LQSPI_CFG_WIDTH        32
#define BPAPB_AB_LQSPI_STS_WRMASK       0xff
#define BPAPB_AB_LQSPI_STS_WRNMASK      (0xffffff00)
#define BPAPB_AB_LQSPI_STS_WIDTH        32
#define BPAPB_AB_MOD_ID_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

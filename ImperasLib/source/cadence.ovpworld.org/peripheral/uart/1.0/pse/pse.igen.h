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
        struct {
            Uns32 RXRES : 1;
            Uns32 TXRES : 1;
            Uns32 RXEN : 1;
            Uns32 RXDIS : 1;
            Uns32 TXEN : 1;
            Uns32 TXDIS : 1;
            Uns32 RSTT0 : 1;
            Uns32 STTBRK : 1;
            Uns32 STPBRK : 1;
        } bits;
    } Control;
    union { 
        Uns32 value;
        struct {
            Uns32 CLKS : 1;
            Uns32 CHRL : 2;
            Uns32 PAR : 3;
            Uns32 NBSTOP : 2;
            Uns32 CHMODE : 2;
        } bits;
    } mode;
    union { 
        Uns32 value;
        struct {
            Uns32 RTRIG : 1;
            Uns32 REMPTY : 1;
            Uns32 RFUL : 1;
            Uns32 TEMPTY : 1;
            Uns32 TFUL : 1;
            Uns32 ROVR : 1;
            Uns32 FRAME : 1;
            Uns32 PARE : 1;
            Uns32 TIMEOUT : 1;
            Uns32 DMSI : 1;
            Uns32 TTRIG : 1;
            Uns32 TNFUL : 1;
            Uns32 TOVR : 1;
        } bits;
    } Intrpt_en;
    union { 
        Uns32 value;
        struct {
            Uns32 RTRIG : 1;
            Uns32 REMPTY : 1;
            Uns32 RFUL : 1;
            Uns32 TEMPTY : 1;
            Uns32 TFUL : 1;
            Uns32 ROVR : 1;
            Uns32 FRAME : 1;
            Uns32 PARE : 1;
            Uns32 TIMEOUT : 1;
            Uns32 DMSI : 1;
            Uns32 TTRIG : 1;
            Uns32 TNFUL : 1;
            Uns32 TOVR : 1;
        } bits;
    } Intrpt_dis;
    union { 
        Uns32 value;
        struct {
            Uns32 RTRIG : 1;
            Uns32 REMPTY : 1;
            Uns32 RFUL : 1;
            Uns32 TEMPTY : 1;
            Uns32 TFUL : 1;
            Uns32 ROVR : 1;
            Uns32 FRAME : 1;
            Uns32 PARE : 1;
            Uns32 TIMEOUT : 1;
            Uns32 DMSI : 1;
            Uns32 TTRIG : 1;
            Uns32 TNFUL : 1;
            Uns32 TOVR : 1;
        } bits;
    } Intrpt_mask;
    union { 
        Uns32 value;
        struct {
            Uns32 RTRIG : 1;
            Uns32 REMPTY : 1;
            Uns32 RFUL : 1;
            Uns32 TEMPTY : 1;
            Uns32 TFUL : 1;
            Uns32 ROVR : 1;
            Uns32 FRAME : 1;
            Uns32 PARE : 1;
            Uns32 TIMEOUT : 1;
            Uns32 DMSI : 1;
            Uns32 TTRIG : 1;
            Uns32 TNFUL : 1;
            Uns32 TOVR : 1;
        } bits;
    } Chnl_int_sts;
    union { 
        Uns32 value;
        struct {
            Uns32 CD : 16;
        } bits;
    } Baud_rate_gen;
    union { 
        Uns32 value;
        struct {
            Uns32 RTO : 8;
        } bits;
    } Rcvr_timeout;
    union { 
        Uns32 value;
        struct {
            Uns32 RTRIG : 6;
        } bits;
    } Rcvr_FIFO_trigger_level;
    union { 
        Uns32 value;
        struct {
            Uns32 DTR : 1;
            Uns32 RTS : 1;
            Uns32 __pad2 : 3;
            Uns32 FCM : 1;
        } bits;
    } Modem_ctrl;
    union { 
        Uns32 value;
        struct {
            Uns32 DCTS : 1;
            Uns32 DDSR : 1;
            Uns32 TERI : 1;
            Uns32 DDCD : 1;
            Uns32 CTS : 1;
            Uns32 DSR : 1;
            Uns32 RI : 1;
            Uns32 DCD : 1;
            Uns32 FCMS : 1;
        } bits;
    } Modem_sts;
    union { 
        Uns32 value;
        struct {
            Uns32 RTRIG : 1;
            Uns32 REMPTY : 1;
            Uns32 RFUL : 1;
            Uns32 TEMPTY : 1;
            Uns32 TFUL : 1;
            Uns32 __pad5 : 5;
            Uns32 RACTIVE : 1;
            Uns32 TACTIVE : 1;
            Uns32 FDELT : 1;
            Uns32 TTRIG : 1;
            Uns32 TNFUL : 1;
        } bits;
    } Channel_sts;
    union { 
        Uns32 value;
        struct {
            Uns32 FIF0 : 8;
        } bits;
    } TX_RX_FIFO;
    union { 
        Uns32 value;
        struct {
            Uns32 BDIV : 8;
        } bits;
    } Baud_rate_divider;
    union { 
        Uns32 value;
        struct {
            Uns32 FDEL : 6;
        } bits;
    } Flow_delay;
    union { 
        Uns32 value;
        struct {
            Uns32 TTRIG : 6;
        } bits;
    } Tx_FIFO_trigger_level;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(ReadChannel_sts);
PPM_REG_READ_CB(ReadIntrpt_mask);
PPM_REG_READ_CB(ReadTX_RX_FIFO);
PPM_REG_WRITE_CB(WriteChnl_int_sts);
PPM_REG_WRITE_CB(WriteControl);
PPM_REG_WRITE_CB(WriteIntrpt_dis);
PPM_REG_WRITE_CB(WriteIntrpt_en);
PPM_REG_WRITE_CB(WriteTX_RX_FIFO);
PPM_WRITE_CB(regNoDefinitionRead);
PPM_READ_CB(regNoDefinitionWrite);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/ab/buffer : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER_OFFSET + myAddress];

#define BPORT1_AB_BUFFER_OFFSET         0x0
#define BPORT1_AB_BUFFER_SIZE           0x1000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_CONTROL_WRMASK        0x1f
#define BPORT1_AB_CONTROL_WRNMASK       (0xffffffe0)
#define BPORT1_AB_CONTROL_WIDTH         32
#define BPORT1_AB_MODE_WRMASK           0x7ff
#define BPORT1_AB_MODE_WRNMASK          (0xfffff800)
#define BPORT1_AB_MODE_WIDTH            32
#define BPORT1_AB_INTRPT_EN_WRMASK      0x1fff
#define BPORT1_AB_INTRPT_EN_WRNMASK     (0xffffe000)
#define BPORT1_AB_INTRPT_EN_WIDTH       32
#define BPORT1_AB_INTRPT_DIS_WRMASK     0x1fff
#define BPORT1_AB_INTRPT_DIS_WRNMASK    (0xffffe000)
#define BPORT1_AB_INTRPT_DIS_WIDTH      32
#define BPORT1_AB_INTRPT_MASK_WIDTH     32
#define BPORT1_AB_CHNL_INT_STS_WRMASK   0x1fff
#define BPORT1_AB_CHNL_INT_STS_WRNMASK  (0xffffe000)
#define BPORT1_AB_CHNL_INT_STS_WIDTH    32
#define BPORT1_AB_BAUD_RATE_GEN_WRMASK  0xffff
#define BPORT1_AB_BAUD_RATE_GEN_WRNMASK  (0xffff0000)
#define BPORT1_AB_BAUD_RATE_GEN_WIDTH   32
#define BPORT1_AB_RCVR_TIMEOUT_WRMASK   0xff
#define BPORT1_AB_RCVR_TIMEOUT_WRNMASK  (0xffffff00)
#define BPORT1_AB_RCVR_TIMEOUT_WIDTH    32
#define BPORT1_AB_RCVR_FIFO_TRIGGER_LEVEL_WRMASK  0x3f
#define BPORT1_AB_RCVR_FIFO_TRIGGER_LEVEL_WRNMASK  (0xffffffc0)
#define BPORT1_AB_RCVR_FIFO_TRIGGER_LEVEL_WIDTH  32
#define BPORT1_AB_MODEM_CTRL_WRMASK     0x13
#define BPORT1_AB_MODEM_CTRL_WRNMASK    (0xffffffec)
#define BPORT1_AB_MODEM_CTRL_WIDTH      32
#define BPORT1_AB_MODEM_STS_WRMASK      0x1ff
#define BPORT1_AB_MODEM_STS_WRNMASK     (0xfffffe00)
#define BPORT1_AB_MODEM_STS_WIDTH       32
#define BPORT1_AB_CHANNEL_STS_WIDTH     32
#define BPORT1_AB_TX_RX_FIFO_WIDTH      32
#define BPORT1_AB_BAUD_RATE_DIVIDER_WRMASK  0xff
#define BPORT1_AB_BAUD_RATE_DIVIDER_WRNMASK  (0xffffff00)
#define BPORT1_AB_BAUD_RATE_DIVIDER_WIDTH  32
#define BPORT1_AB_FLOW_DELAY_WRMASK     0x1f
#define BPORT1_AB_FLOW_DELAY_WRNMASK    (0xffffffe0)
#define BPORT1_AB_FLOW_DELAY_WIDTH      32
#define BPORT1_AB_TX_FIFO_TRIGGER_LEVEL_WRMASK  0x1f
#define BPORT1_AB_TX_FIFO_TRIGGER_LEVEL_WRNMASK  (0xffffffe0)
#define BPORT1_AB_TX_FIFO_TRIGGER_LEVEL_WIDTH  32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

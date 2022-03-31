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
            Uns32 __pad0 : 15;
            Uns32 TS_TIMER : 1;
            Uns32 TS_AVAIL : 1;
            Uns32 WAKEUP : 1;
            Uns32 PLR : 1;
            Uns32 UN : 1;
            Uns32 RL : 1;
            Uns32 LC : 1;
            Uns32 EBERR : 1;
            Uns32 MII : 1;
            Uns32 RXB : 1;
            Uns32 RXF : 1;
            Uns32 TXB : 1;
            Uns32 TXF : 1;
            Uns32 GRA : 1;
            Uns32 BABT : 1;
            Uns32 BABR : 1;
        } bits;
    } EIR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 15;
            Uns32 TS_TIMER : 1;
            Uns32 TS_AVAIL : 1;
            Uns32 WAKEUP : 1;
            Uns32 PLR : 1;
            Uns32 UN : 1;
            Uns32 RL : 1;
            Uns32 LC : 1;
            Uns32 EBERR : 1;
            Uns32 MII : 1;
            Uns32 RXB : 1;
            Uns32 RXF : 1;
            Uns32 TXB : 1;
            Uns32 TXF : 1;
            Uns32 GRA : 1;
            Uns32 BABT : 1;
            Uns32 BABR : 1;
        } bits;
    } EIMR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 24;
            Uns32 RDAR : 1;
        } bits;
    } RDAR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 24;
            Uns32 TDAR : 1;
        } bits;
    } TDAR;
    union { 
        Uns32 value;
        struct {
            Uns32 RESET : 1;
            Uns32 ETHEREN : 1;
            Uns32 MAGICEN : 1;
            Uns32 SLEEP : 1;
            Uns32 EN1588 : 1;
            Uns32 __pad5 : 1;
            Uns32 DBGEN : 1;
            Uns32 STOPEN : 1;
            Uns32 DBSWP : 1;
        } bits;
    } ECR;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 16;
            Uns32 TA : 2;
            Uns32 RA : 5;
            Uns32 PA : 5;
            Uns32 OP : 2;
            Uns32 ST : 2;
        } bits;
    } MMFR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 1;
            Uns32 MII_SPEED : 6;
            Uns32 DIS_PRE : 1;
            Uns32 HOLDTIME : 3;
        } bits;
    } MSCR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 29;
            Uns32 MIB_CLEAR : 1;
            Uns32 MIB_IDLE : 1;
            Uns32 MIB_DIS : 1;
        } bits;
    } MIBC;
    union { 
        Uns32 value;
        struct {
            Uns32 LOOP : 1;
            Uns32 DRT : 1;
            Uns32 MII_MODE : 1;
            Uns32 PROM : 1;
            Uns32 BC_REJ : 1;
            Uns32 FCE : 1;
            Uns32 __pad6 : 2;
            Uns32 RMII_MODE : 1;
            Uns32 RMII_10T : 1;
            Uns32 __pad10 : 2;
            Uns32 PADEN : 1;
            Uns32 PAUFWD : 1;
            Uns32 CRCFWD : 1;
            Uns32 CFEN : 1;
            Uns32 MAX_FL : 14;
            Uns32 NLC : 1;
            Uns32 GRS : 1;
        } bits;
    } RCR;
    union { 
        Uns32 value;
        struct {
            Uns32 GTS : 1;
            Uns32 __pad1 : 1;
            Uns32 FDEN : 1;
            Uns32 TFC_PAUSE : 1;
            Uns32 RFC_PAUSE : 1;
            Uns32 ADDSEL : 3;
            Uns32 ADDINS : 1;
            Uns32 CRCFWD : 1;
        } bits;
    } TCR;
    union { 
        Uns32 value;
        struct {
            Uns32 PADDR1 : 32;
        } bits;
    } PALR;
    union { 
        Uns32 value;
        struct {
            Uns32 TYPE : 16;
            Uns32 PADDR2 : 16;
        } bits;
    } PAUR;
    union { 
        Uns32 value;
        struct {
            Uns32 PAUSE_DUR : 16;
            Uns32 OPCODE : 16;
        } bits;
    } OPD;
    union { 
        Uns32 value;
        struct {
            Uns32 IADDR1 : 32;
        } bits;
    } IAUR;
    union { 
        Uns32 value;
        struct {
            Uns32 IADDR2 : 32;
        } bits;
    } IALR;
    union { 
        Uns32 value;
        struct {
            Uns32 GADDR1 : 32;
        } bits;
    } GAUR;
    union { 
        Uns32 value;
        struct {
            Uns32 GADDR2 : 32;
        } bits;
    } GALR;
    union { 
        Uns32 value;
        struct {
            Uns32 TFWR : 6;
            Uns32 __pad6 : 2;
            Uns32 STRFWD : 1;
        } bits;
    } TFWR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 R_DES_START : 29;
        } bits;
    } RDSR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 X_DES_START : 29;
        } bits;
    } TDSR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 4;
            Uns32 R_BUF_SIZE : 10;
        } bits;
    } MRBR;
    union { 
        Uns32 value;
        struct {
            Uns32 RX_SECTION_FULL : 8;
        } bits;
    } RSFL;
    union { 
        Uns32 value;
        struct {
            Uns32 RX_SECTION_EMPTY : 8;
        } bits;
    } RSEM;
    union { 
        Uns32 value;
        struct {
            Uns32 RX_ALMOST_EMPTY : 8;
        } bits;
    } RAEM;
    union { 
        Uns32 value;
        struct {
            Uns32 RX_ALMOST_FULL : 8;
        } bits;
    } RAFL;
    union { 
        Uns32 value;
        struct {
            Uns32 TX_SECTION_EMPTY : 8;
        } bits;
    } TSEM;
    union { 
        Uns32 value;
        struct {
            Uns32 TX_ALMOST_EMPTY : 8;
        } bits;
    } TAEM;
    union { 
        Uns32 value;
        struct {
            Uns32 TX_ALMOST_FULL : 8;
        } bits;
    } TAFL;
    union { 
        Uns32 value;
        struct {
            Uns32 IPG : 5;
        } bits;
    } TIPG;
    union { 
        Uns32 value;
        struct {
            Uns32 TRUNC_FL : 14;
        } bits;
    } FTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 SHIFT16 : 1;
            Uns32 __pad1 : 2;
            Uns32 IPCHK : 1;
            Uns32 PROCHK : 1;
        } bits;
    } TACC;
    union { 
        Uns32 value;
        struct {
            Uns32 PADREM : 1;
            Uns32 IPDIS : 1;
            Uns32 PRODIS : 1;
            Uns32 __pad3 : 3;
            Uns32 LINEDIS : 1;
            Uns32 SHIFT16 : 1;
        } bits;
    } RACC;
    union { 
        Uns32 value;
    } RMON_T_DROP;
    union { 
        Uns32 value;
    } RMON_T_PACKETS;
    union { 
        Uns32 value;
    } RMON_T_BC_PKT;
    union { 
        Uns32 value;
    } RMON_T_MC_PKT;
    union { 
        Uns32 value;
    } RMON_T_CRC_ALIGN;
    union { 
        Uns32 value;
    } RMON_T_UNDERSIZE;
    union { 
        Uns32 value;
    } RMON_T_OVERSIZE;
    union { 
        Uns32 value;
    } RMON_T_FRAG;
    union { 
        Uns32 value;
    } RMON_T_JAB;
    union { 
        Uns32 value;
    } RMON_T_COL;
    union { 
        Uns32 value;
    } RMON_T_P64;
    union { 
        Uns32 value;
    } RMON_T_P65TO127;
    union { 
        Uns32 value;
    } RMON_T_P128TO255;
    union { 
        Uns32 value;
    } RMON_T_P256TO511;
    union { 
        Uns32 value;
    } RMON_T_P512TO1023;
    union { 
        Uns32 value;
    } RMON_T_P1024TO2047;
    union { 
        Uns32 value;
    } RMON_T_P_GTE2048;
    union { 
        Uns32 value;
    } RMON_T_OCTETS;
    union { 
        Uns32 value;
    } IEEE_T_DROP;
    union { 
        Uns32 value;
    } IEEE_T_FRAME_OK;
    union { 
        Uns32 value;
    } IEEE_T_1COL;
    union { 
        Uns32 value;
    } IEEE_T_MCOL;
    union { 
        Uns32 value;
    } IEEE_T_DEF;
    union { 
        Uns32 value;
    } IEEE_T_LCOL;
    union { 
        Uns32 value;
    } IEEE_T_EXCOL;
    union { 
        Uns32 value;
    } IEEE_T_MACERR;
    union { 
        Uns32 value;
    } IEEE_T_CSERR;
    union { 
        Uns32 value;
    } IEEE_T_SQE;
    union { 
        Uns32 value;
    } IEEE_T_FDXFC;
    union { 
        Uns32 value;
    } IEEE_T_OCTETS_OK;
    union { 
        Uns32 value;
    } RMON_R_PACKETS;
    union { 
        Uns32 value;
    } RMON_R_BC_PKT;
    union { 
        Uns32 value;
    } RMON_R_MC_PKT;
    union { 
        Uns32 value;
    } RMON_R_CRC_ALIGN;
    union { 
        Uns32 value;
    } RMON_R_UNDERSIZE;
    union { 
        Uns32 value;
    } RMON_R_OVERSIZE;
    union { 
        Uns32 value;
    } RMON_R_FRAG;
    union { 
        Uns32 value;
    } RMON_R_JAB;
    union { 
        Uns32 value;
    } RMON_R_RESVD_0;
    union { 
        Uns32 value;
    } RMON_R_P64;
    union { 
        Uns32 value;
    } RMON_R_P65TO127;
    union { 
        Uns32 value;
    } RMON_R_P128TO255;
    union { 
        Uns32 value;
    } RMON_R_P256TO511;
    union { 
        Uns32 value;
    } RMON_R_P512TO1023;
    union { 
        Uns32 value;
    } RMON_R_P1024TO2047;
    union { 
        Uns32 value;
    } RMON_R_P_GTE2048;
    union { 
        Uns32 value;
    } RMON_R_OCTETS;
    union { 
        Uns32 value;
    } RMON_R_DROP;
    union { 
        Uns32 value;
    } RMON_R_FRAME_OK;
    union { 
        Uns32 value;
    } IEEE_R_CRC;
    union { 
        Uns32 value;
    } IEEE_R_ALIGN;
    union { 
        Uns32 value;
    } IEEE_R_MACERR;
    union { 
        Uns32 value;
    } IEEE_R_FDXFC;
    union { 
        Uns32 value;
    } IEEE_R_OCTETS_OK;
    union { 
        Uns32 value;
        struct {
            Uns32 EN : 1;
            Uns32 __pad1 : 1;
            Uns32 OFFEN : 1;
            Uns32 OFFRST : 1;
            Uns32 PEREN : 1;
            Uns32 __pad5 : 2;
            Uns32 PINPER : 1;
            Uns32 __pad8 : 1;
            Uns32 RESTART : 1;
            Uns32 __pad10 : 1;
            Uns32 CAPTURE : 1;
            Uns32 __pad12 : 1;
            Uns32 SLAVE : 1;
        } bits;
    } ATCR;
    union { 
        Uns32 value;
        struct {
            Uns32 ATIME : 32;
        } bits;
    } ATVR;
    union { 
        Uns32 value;
        struct {
            Uns32 OFFSET : 32;
        } bits;
    } ATOFF;
    union { 
        Uns32 value;
        struct {
            Uns32 PERIOD : 32;
        } bits;
    } ATPER;
    union { 
        Uns32 value;
        struct {
            Uns32 COR : 31;
        } bits;
    } ATCOR;
    union { 
        Uns32 value;
        struct {
            Uns32 INC : 7;
            Uns32 __pad7 : 1;
            Uns32 INC_CORR : 7;
        } bits;
    } ATINC;
    union { 
        Uns32 value;
        struct {
            Uns32 TIMESTAMP : 32;
        } bits;
    } ATSTMP;
    union { 
        Uns32 value;
        struct {
            Uns32 TF0 : 1;
            Uns32 TF1 : 1;
            Uns32 TF2 : 1;
            Uns32 TF3 : 1;
        } bits;
    } TGSR;
    union { 
        Uns32 value;
        struct {
            Uns32 TDRE : 1;
            Uns32 __pad1 : 1;
            Uns32 TMODE : 4;
            Uns32 TIE : 1;
            Uns32 TF : 1;
        } bits;
    } TCSR0;
    union { 
        Uns32 value;
        struct {
            Uns32 TCC : 32;
        } bits;
    } TCCR0;
    union { 
        Uns32 value;
        struct {
            Uns32 TDRE : 1;
            Uns32 __pad1 : 1;
            Uns32 TMODE : 4;
            Uns32 TIE : 1;
            Uns32 TF : 1;
        } bits;
    } TCSR1;
    union { 
        Uns32 value;
        struct {
            Uns32 TCC : 32;
        } bits;
    } TCCR1;
    union { 
        Uns32 value;
        struct {
            Uns32 TDRE : 1;
            Uns32 __pad1 : 1;
            Uns32 TMODE : 4;
            Uns32 TIE : 1;
            Uns32 TF : 1;
        } bits;
    } TCSR2;
    union { 
        Uns32 value;
        struct {
            Uns32 TCC : 32;
        } bits;
    } TCCR2;
    union { 
        Uns32 value;
        struct {
            Uns32 TDRE : 1;
            Uns32 __pad1 : 1;
            Uns32 TMODE : 4;
            Uns32 TIE : 1;
            Uns32 TF : 1;
        } bits;
    } TCSR3;
    union { 
        Uns32 value;
        struct {
            Uns32 TCC : 32;
        } bits;
    } TCCR3;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_EIR_WRMASK            0x7fff8000
#define BPORT1_AB_EIR_WRNMASK           (0x80007fff)
#define BPORT1_AB_EIR_WIDTH             32
#define BPORT1_AB_EIMR_WRMASK           0x7fff8000
#define BPORT1_AB_EIMR_WRNMASK          (0x80007fff)
#define BPORT1_AB_EIMR_WIDTH            32
#define BPORT1_AB_RDAR_WRMASK           0x1000000
#define BPORT1_AB_RDAR_WRNMASK          (0xfeffffff)
#define BPORT1_AB_RDAR_WIDTH            32
#define BPORT1_AB_TDAR_WRMASK           0x1000000
#define BPORT1_AB_TDAR_WRNMASK          (0xfeffffff)
#define BPORT1_AB_TDAR_WIDTH            32
#define BPORT1_AB_ECR_WRMASK            0x1df
#define BPORT1_AB_ECR_WRNMASK           (0xfffffe20)
#define BPORT1_AB_ECR_WIDTH             32
#define BPORT1_AB_MMFR_WRMASK           0xffffffff
#define BPORT1_AB_MMFR_WRNMASK          (0x0)
#define BPORT1_AB_MMFR_WIDTH            32
#define BPORT1_AB_MSCR_WRMASK           0x7fe
#define BPORT1_AB_MSCR_WRNMASK          (0xfffff801)
#define BPORT1_AB_MSCR_WIDTH            32
#define BPORT1_AB_MIBC_WRMASK           0xa0000000
#define BPORT1_AB_MIBC_WRNMASK          (0x5fffffff)
#define BPORT1_AB_MIBC_WIDTH            32
#define BPORT1_AB_RCR_WRMASK            0x47fff33f
#define BPORT1_AB_RCR_WRNMASK           (0xb8000cc0)
#define BPORT1_AB_RCR_WIDTH             32
#define BPORT1_AB_TCR_WRMASK            0x3ed
#define BPORT1_AB_TCR_WRNMASK           (0xfffffc12)
#define BPORT1_AB_TCR_WIDTH             32
#define BPORT1_AB_PALR_WRMASK           0xffffffff
#define BPORT1_AB_PALR_WRNMASK          (0x0)
#define BPORT1_AB_PALR_WIDTH            32
#define BPORT1_AB_PAUR_WRMASK           0xffff0000
#define BPORT1_AB_PAUR_WRNMASK          (0xffff)
#define BPORT1_AB_PAUR_WIDTH            32
#define BPORT1_AB_OPD_WRMASK            0xffff
#define BPORT1_AB_OPD_WRNMASK           (0xffff0000)
#define BPORT1_AB_OPD_WIDTH             32
#define BPORT1_AB_IAUR_WRMASK           0xffffffff
#define BPORT1_AB_IAUR_WRNMASK          (0x0)
#define BPORT1_AB_IAUR_WIDTH            32
#define BPORT1_AB_IALR_WRMASK           0xffffffff
#define BPORT1_AB_IALR_WRNMASK          (0x0)
#define BPORT1_AB_IALR_WIDTH            32
#define BPORT1_AB_GAUR_WRMASK           0xffffffff
#define BPORT1_AB_GAUR_WRNMASK          (0x0)
#define BPORT1_AB_GAUR_WIDTH            32
#define BPORT1_AB_GALR_WRMASK           0xffffffff
#define BPORT1_AB_GALR_WRNMASK          (0x0)
#define BPORT1_AB_GALR_WIDTH            32
#define BPORT1_AB_TFWR_WRMASK           0x13f
#define BPORT1_AB_TFWR_WRNMASK          (0xfffffec0)
#define BPORT1_AB_TFWR_WIDTH            32
#define BPORT1_AB_RDSR_WRMASK           0xfffffff8
#define BPORT1_AB_RDSR_WRNMASK          (0x7)
#define BPORT1_AB_RDSR_WIDTH            32
#define BPORT1_AB_TDSR_WRMASK           0xfffffff8
#define BPORT1_AB_TDSR_WRNMASK          (0x7)
#define BPORT1_AB_TDSR_WIDTH            32
#define BPORT1_AB_MRBR_WRMASK           0x3ff0
#define BPORT1_AB_MRBR_WRNMASK          (0xffffc00f)
#define BPORT1_AB_MRBR_WIDTH            32
#define BPORT1_AB_RSFL_WRMASK           0xff
#define BPORT1_AB_RSFL_WRNMASK          (0xffffff00)
#define BPORT1_AB_RSFL_WIDTH            32
#define BPORT1_AB_RSEM_WRMASK           0xff
#define BPORT1_AB_RSEM_WRNMASK          (0xffffff00)
#define BPORT1_AB_RSEM_WIDTH            32
#define BPORT1_AB_RAEM_WRMASK           0xff
#define BPORT1_AB_RAEM_WRNMASK          (0xffffff00)
#define BPORT1_AB_RAEM_WIDTH            32
#define BPORT1_AB_RAFL_WRMASK           0xff
#define BPORT1_AB_RAFL_WRNMASK          (0xffffff00)
#define BPORT1_AB_RAFL_WIDTH            32
#define BPORT1_AB_TSEM_WRMASK           0xff
#define BPORT1_AB_TSEM_WRNMASK          (0xffffff00)
#define BPORT1_AB_TSEM_WIDTH            32
#define BPORT1_AB_TAEM_WRMASK           0xff
#define BPORT1_AB_TAEM_WRNMASK          (0xffffff00)
#define BPORT1_AB_TAEM_WIDTH            32
#define BPORT1_AB_TAFL_WRMASK           0xff
#define BPORT1_AB_TAFL_WRNMASK          (0xffffff00)
#define BPORT1_AB_TAFL_WIDTH            32
#define BPORT1_AB_TIPG_WRMASK           0x1f
#define BPORT1_AB_TIPG_WRNMASK          (0xffffffe0)
#define BPORT1_AB_TIPG_WIDTH            32
#define BPORT1_AB_FTRL_WRMASK           0x3fff
#define BPORT1_AB_FTRL_WRNMASK          (0xffffc000)
#define BPORT1_AB_FTRL_WIDTH            32
#define BPORT1_AB_TACC_WRMASK           0x19
#define BPORT1_AB_TACC_WRNMASK          (0xffffffe6)
#define BPORT1_AB_TACC_WIDTH            32
#define BPORT1_AB_RACC_WRMASK           0xc7
#define BPORT1_AB_RACC_WRNMASK          (0xffffff38)
#define BPORT1_AB_RACC_WIDTH            32
#define BPORT1_AB_RMON_T_DROP_WIDTH     32
#define BPORT1_AB_RMON_T_PACKETS_WIDTH  32
#define BPORT1_AB_RMON_T_BC_PKT_WIDTH   32
#define BPORT1_AB_RMON_T_MC_PKT_WIDTH   32
#define BPORT1_AB_RMON_T_CRC_ALIGN_WIDTH  32
#define BPORT1_AB_RMON_T_UNDERSIZE_WIDTH  32
#define BPORT1_AB_RMON_T_OVERSIZE_WIDTH  32
#define BPORT1_AB_RMON_T_FRAG_WIDTH     32
#define BPORT1_AB_RMON_T_JAB_WIDTH      32
#define BPORT1_AB_RMON_T_COL_WIDTH      32
#define BPORT1_AB_RMON_T_P64_WIDTH      32
#define BPORT1_AB_RMON_T_P65TO127_WIDTH  32
#define BPORT1_AB_RMON_T_P128TO255_WIDTH  32
#define BPORT1_AB_RMON_T_P256TO511_WIDTH  32
#define BPORT1_AB_RMON_T_P512TO1023_WIDTH  32
#define BPORT1_AB_RMON_T_P1024TO2047_WIDTH  32
#define BPORT1_AB_RMON_T_P_GTE2048_WIDTH  32
#define BPORT1_AB_RMON_T_OCTETS_WIDTH   32
#define BPORT1_AB_IEEE_T_DROP_WIDTH     32
#define BPORT1_AB_IEEE_T_FRAME_OK_WIDTH  32
#define BPORT1_AB_IEEE_T_1COL_WIDTH     32
#define BPORT1_AB_IEEE_T_MCOL_WIDTH     32
#define BPORT1_AB_IEEE_T_DEF_WIDTH      32
#define BPORT1_AB_IEEE_T_LCOL_WIDTH     32
#define BPORT1_AB_IEEE_T_EXCOL_WIDTH    32
#define BPORT1_AB_IEEE_T_MACERR_WIDTH   32
#define BPORT1_AB_IEEE_T_CSERR_WIDTH    32
#define BPORT1_AB_IEEE_T_SQE_WIDTH      32
#define BPORT1_AB_IEEE_T_FDXFC_WIDTH    32
#define BPORT1_AB_IEEE_T_OCTETS_OK_WIDTH  32
#define BPORT1_AB_RMON_R_PACKETS_WIDTH  32
#define BPORT1_AB_RMON_R_BC_PKT_WIDTH   32
#define BPORT1_AB_RMON_R_MC_PKT_WIDTH   32
#define BPORT1_AB_RMON_R_CRC_ALIGN_WIDTH  32
#define BPORT1_AB_RMON_R_UNDERSIZE_WIDTH  32
#define BPORT1_AB_RMON_R_OVERSIZE_WIDTH  32
#define BPORT1_AB_RMON_R_FRAG_WIDTH     32
#define BPORT1_AB_RMON_R_JAB_WIDTH      32
#define BPORT1_AB_RMON_R_RESVD_0_WIDTH  32
#define BPORT1_AB_RMON_R_P64_WIDTH      32
#define BPORT1_AB_RMON_R_P65TO127_WIDTH  32
#define BPORT1_AB_RMON_R_P128TO255_WIDTH  32
#define BPORT1_AB_RMON_R_P256TO511_WIDTH  32
#define BPORT1_AB_RMON_R_P512TO1023_WIDTH  32
#define BPORT1_AB_RMON_R_P1024TO2047_WIDTH  32
#define BPORT1_AB_RMON_R_P_GTE2048_WIDTH  32
#define BPORT1_AB_RMON_R_OCTETS_WIDTH   32
#define BPORT1_AB_RMON_R_DROP_WIDTH     32
#define BPORT1_AB_RMON_R_FRAME_OK_WIDTH  32
#define BPORT1_AB_IEEE_R_CRC_WIDTH      32
#define BPORT1_AB_IEEE_R_ALIGN_WIDTH    32
#define BPORT1_AB_IEEE_R_MACERR_WIDTH   32
#define BPORT1_AB_IEEE_R_FDXFC_WIDTH    32
#define BPORT1_AB_IEEE_R_OCTETS_OK_WIDTH  32
#define BPORT1_AB_ATCR_WRMASK           0x2a9d
#define BPORT1_AB_ATCR_WRNMASK          (0xffffd562)
#define BPORT1_AB_ATCR_WIDTH            32
#define BPORT1_AB_ATVR_WRMASK           0xffffffff
#define BPORT1_AB_ATVR_WRNMASK          (0x0)
#define BPORT1_AB_ATVR_WIDTH            32
#define BPORT1_AB_ATOFF_WRMASK          0xffffffff
#define BPORT1_AB_ATOFF_WRNMASK         (0x0)
#define BPORT1_AB_ATOFF_WIDTH           32
#define BPORT1_AB_ATPER_WRMASK          0xffffffff
#define BPORT1_AB_ATPER_WRNMASK         (0x0)
#define BPORT1_AB_ATPER_WIDTH           32
#define BPORT1_AB_ATCOR_WRMASK          0x7fffffff
#define BPORT1_AB_ATCOR_WRNMASK         (0x80000000)
#define BPORT1_AB_ATCOR_WIDTH           32
#define BPORT1_AB_ATINC_WRMASK          0x7e7f
#define BPORT1_AB_ATINC_WRNMASK         (0xffff8180)
#define BPORT1_AB_ATINC_WIDTH           32
#define BPORT1_AB_ATSTMP_WRMASK         0xffffffff
#define BPORT1_AB_ATSTMP_WRNMASK        (0x0)
#define BPORT1_AB_ATSTMP_WIDTH          32
#define BPORT1_AB_TGSR_WRMASK           0xf
#define BPORT1_AB_TGSR_WRNMASK          (0xfffffff0)
#define BPORT1_AB_TGSR_WIDTH            32
#define BPORT1_AB_TCSR0_WRMASK          0xfd
#define BPORT1_AB_TCSR0_WRNMASK         (0xffffff02)
#define BPORT1_AB_TCSR0_WIDTH           32
#define BPORT1_AB_TCCR0_WRMASK          0xffffffff
#define BPORT1_AB_TCCR0_WRNMASK         (0x0)
#define BPORT1_AB_TCCR0_WIDTH           32
#define BPORT1_AB_TCSR1_WRMASK          0xfd
#define BPORT1_AB_TCSR1_WRNMASK         (0xffffff02)
#define BPORT1_AB_TCSR1_WIDTH           32
#define BPORT1_AB_TCCR1_WRMASK          0xffffffff
#define BPORT1_AB_TCCR1_WRNMASK         (0x0)
#define BPORT1_AB_TCCR1_WIDTH           32
#define BPORT1_AB_TCSR2_WRMASK          0xfd
#define BPORT1_AB_TCSR2_WRNMASK         (0xffffff02)
#define BPORT1_AB_TCSR2_WIDTH           32
#define BPORT1_AB_TCCR2_WRMASK          0xffffffff
#define BPORT1_AB_TCCR2_WRNMASK         (0x0)
#define BPORT1_AB_TCCR2_WIDTH           32
#define BPORT1_AB_TCSR3_WRMASK          0xfd
#define BPORT1_AB_TCSR3_WRNMASK         (0xffffff02)
#define BPORT1_AB_TCSR3_WIDTH           32
#define BPORT1_AB_TCCR3_WRMASK          0xffffffff
#define BPORT1_AB_TCCR3_WRNMASK         (0x0)
#define BPORT1_AB_TCCR3_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

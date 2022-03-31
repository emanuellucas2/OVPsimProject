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
            Uns32 MAXMB : 7;
            Uns32 __pad7 : 1;
            Uns32 IDAM : 2;
            Uns32 __pad10 : 2;
            Uns32 AEN : 1;
            Uns32 LPRIOEN : 1;
            Uns32 __pad14 : 2;
            Uns32 IRMQ : 1;
            Uns32 SRXDIS : 1;
            Uns32 DOZE : 1;
            Uns32 __pad19 : 1;
            Uns32 LPMACK : 1;
            Uns32 WRNEN : 1;
            Uns32 SLFWAK : 1;
            Uns32 SUPV : 1;
            Uns32 FRZACK : 1;
            Uns32 SOFTRST : 1;
            Uns32 WAKMSK : 1;
            Uns32 NOTRDY : 1;
            Uns32 HALT : 1;
            Uns32 RFEN : 1;
            Uns32 FRZ : 1;
            Uns32 MDIS : 1;
        } bits;
    } MCR;
    union { 
        Uns32 value;
        struct {
            Uns32 PROPSEG : 3;
            Uns32 LOM : 1;
            Uns32 LBUF : 1;
            Uns32 TSYN : 1;
            Uns32 BOFFREC : 1;
            Uns32 SMP : 1;
            Uns32 __pad8 : 2;
            Uns32 RWRNMSK : 1;
            Uns32 TWRNMSK : 1;
            Uns32 LPB : 1;
            Uns32 CLKSRC : 1;
            Uns32 ERRMSK : 1;
            Uns32 BOFFMSK : 1;
            Uns32 PSEG2 : 3;
            Uns32 PSEG1 : 3;
            Uns32 RJW : 2;
            Uns32 PRESDIV : 8;
        } bits;
    } CTRL1;
    union { 
        Uns32 value;
        struct {
            Uns32 TIMER : 16;
        } bits;
    } TIMER;
    union { 
        Uns32 value;
        struct {
            Uns32 MG : 32;
        } bits;
    } RXMGMASK;
    union { 
        Uns32 value;
        struct {
            Uns32 RX14M : 32;
        } bits;
    } RX14MASK;
    union { 
        Uns32 value;
        struct {
            Uns32 RX15M : 32;
        } bits;
    } RX15MASK;
    union { 
        Uns32 value;
        struct {
            Uns32 TXERRCNT : 8;
            Uns32 RXERRCNT : 8;
        } bits;
    } ECR;
    union { 
        Uns32 value;
        struct {
            Uns32 WAKINT : 1;
            Uns32 ERRINT : 1;
            Uns32 BOFFINT : 1;
            Uns32 RX : 1;
            Uns32 FLTCONF : 2;
            Uns32 TX : 1;
            Uns32 IDLE : 1;
            Uns32 RXWRN : 1;
            Uns32 TXWRN : 1;
            Uns32 STFERR : 1;
            Uns32 FRMERR : 1;
            Uns32 CRCERR : 1;
            Uns32 ACKERR : 1;
            Uns32 BIT0ERR : 1;
            Uns32 BIT1ERR : 1;
            Uns32 RWRNINT : 1;
            Uns32 TWRNINT : 1;
            Uns32 SYNCH : 1;
        } bits;
    } ESR1;
    union { 
        Uns32 value;
        struct {
            Uns32 BUFHM : 32;
        } bits;
    } IMASK2;
    union { 
        Uns32 value;
        struct {
            Uns32 BUFLM : 32;
        } bits;
    } IMASK1;
    union { 
        Uns32 value;
        struct {
            Uns32 BUFHI : 32;
        } bits;
    } IFLAG2;
    union { 
        Uns32 value;
        struct {
            Uns32 BUF4TO0I : 5;
            Uns32 BUF5I : 1;
            Uns32 BUF6I : 1;
            Uns32 BUF7I : 1;
            Uns32 BUF31TO8I : 24;
        } bits;
    } IFLAG1;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 EACEN : 1;
            Uns32 RRS : 1;
            Uns32 MRP : 1;
            Uns32 TASD : 5;
            Uns32 RFFN : 4;
            Uns32 WRMFRZ : 1;
        } bits;
    } CTRL2;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 13;
            Uns32 IMB : 1;
            Uns32 VPS : 1;
            Uns32 __pad15 : 1;
            Uns32 LPTM : 7;
        } bits;
    } ESR2;
    union { 
        Uns32 value;
        struct {
            Uns32 TXCRC : 15;
            Uns32 __pad15 : 1;
            Uns32 MBCRC : 7;
        } bits;
    } CRCR;
    union { 
        Uns32 value;
        struct {
            Uns32 FGM : 32;
        } bits;
    } RXFGMASK;
    union { 
        Uns32 value;
        struct {
            Uns32 IDHIT : 9;
        } bits;
    } RXFIR;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR0;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR1;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR2;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR3;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR4;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR5;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR6;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR7;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR8;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR9;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR10;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR11;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR12;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR13;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR14;
    union { 
        Uns32 value;
        struct {
            Uns32 MI : 32;
        } bits;
    } RXIMR15;
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

#define BPORT1_AB_MCR_WRMASK            0xf6e7337f
#define BPORT1_AB_MCR_WRNMASK           (0x918cc80)
#define BPORT1_AB_MCR_WIDTH             32
#define BPORT1_AB_CTRL1_WRMASK          0xfffffcff
#define BPORT1_AB_CTRL1_WRNMASK         (0x300)
#define BPORT1_AB_CTRL1_WIDTH           32
#define BPORT1_AB_TIMER_WRMASK          0xffff
#define BPORT1_AB_TIMER_WRNMASK         (0xffff0000)
#define BPORT1_AB_TIMER_WIDTH           32
#define BPORT1_AB_RXMGMASK_WRMASK       0xffffffff
#define BPORT1_AB_RXMGMASK_WRNMASK      (0x0)
#define BPORT1_AB_RXMGMASK_WIDTH        32
#define BPORT1_AB_RX14MASK_WRMASK       0xffffffff
#define BPORT1_AB_RX14MASK_WRNMASK      (0x0)
#define BPORT1_AB_RX14MASK_WIDTH        32
#define BPORT1_AB_RX15MASK_WRMASK       0xffffffff
#define BPORT1_AB_RX15MASK_WRNMASK      (0x0)
#define BPORT1_AB_RX15MASK_WIDTH        32
#define BPORT1_AB_ECR_WRMASK            0xffff
#define BPORT1_AB_ECR_WRNMASK           (0xffff0000)
#define BPORT1_AB_ECR_WIDTH             32
#define BPORT1_AB_ESR1_WRMASK           0x30007
#define BPORT1_AB_ESR1_WRNMASK          (0xfffcfff8)
#define BPORT1_AB_ESR1_WIDTH            32
#define BPORT1_AB_IMASK2_WRMASK         0xffffffff
#define BPORT1_AB_IMASK2_WRNMASK        (0x0)
#define BPORT1_AB_IMASK2_WIDTH          32
#define BPORT1_AB_IMASK1_WRMASK         0xffffffff
#define BPORT1_AB_IMASK1_WRNMASK        (0x0)
#define BPORT1_AB_IMASK1_WIDTH          32
#define BPORT1_AB_IFLAG2_WRMASK         0xffffffff
#define BPORT1_AB_IFLAG2_WRNMASK        (0x0)
#define BPORT1_AB_IFLAG2_WIDTH          32
#define BPORT1_AB_IFLAG1_WRMASK         0xffffffff
#define BPORT1_AB_IFLAG1_WRNMASK        (0x0)
#define BPORT1_AB_IFLAG1_WIDTH          32
#define BPORT1_AB_CTRL2_WRMASK          0x1fff0000
#define BPORT1_AB_CTRL2_WRNMASK         (0xe000ffff)
#define BPORT1_AB_CTRL2_WIDTH           32
#define BPORT1_AB_ESR2_WIDTH            32
#define BPORT1_AB_CRCR_WIDTH            32
#define BPORT1_AB_RXFGMASK_WRMASK       0xffffffff
#define BPORT1_AB_RXFGMASK_WRNMASK      (0x0)
#define BPORT1_AB_RXFGMASK_WIDTH        32
#define BPORT1_AB_RXFIR_WIDTH           32
#define BPORT1_AB_RXIMR0_WRMASK         0xffffffff
#define BPORT1_AB_RXIMR0_WRNMASK        (0x0)
#define BPORT1_AB_RXIMR0_WIDTH          32
#define BPORT1_AB_RXIMR1_WRMASK         0xffffffff
#define BPORT1_AB_RXIMR1_WRNMASK        (0x0)
#define BPORT1_AB_RXIMR1_WIDTH          32
#define BPORT1_AB_RXIMR2_WRMASK         0xffffffff
#define BPORT1_AB_RXIMR2_WRNMASK        (0x0)
#define BPORT1_AB_RXIMR2_WIDTH          32
#define BPORT1_AB_RXIMR3_WRMASK         0xffffffff
#define BPORT1_AB_RXIMR3_WRNMASK        (0x0)
#define BPORT1_AB_RXIMR3_WIDTH          32
#define BPORT1_AB_RXIMR4_WRMASK         0xffffffff
#define BPORT1_AB_RXIMR4_WRNMASK        (0x0)
#define BPORT1_AB_RXIMR4_WIDTH          32
#define BPORT1_AB_RXIMR5_WRMASK         0xffffffff
#define BPORT1_AB_RXIMR5_WRNMASK        (0x0)
#define BPORT1_AB_RXIMR5_WIDTH          32
#define BPORT1_AB_RXIMR6_WRMASK         0xffffffff
#define BPORT1_AB_RXIMR6_WRNMASK        (0x0)
#define BPORT1_AB_RXIMR6_WIDTH          32
#define BPORT1_AB_RXIMR7_WRMASK         0xffffffff
#define BPORT1_AB_RXIMR7_WRNMASK        (0x0)
#define BPORT1_AB_RXIMR7_WIDTH          32
#define BPORT1_AB_RXIMR8_WRMASK         0xffffffff
#define BPORT1_AB_RXIMR8_WRNMASK        (0x0)
#define BPORT1_AB_RXIMR8_WIDTH          32
#define BPORT1_AB_RXIMR9_WRMASK         0xffffffff
#define BPORT1_AB_RXIMR9_WRNMASK        (0x0)
#define BPORT1_AB_RXIMR9_WIDTH          32
#define BPORT1_AB_RXIMR10_WRMASK        0xffffffff
#define BPORT1_AB_RXIMR10_WRNMASK       (0x0)
#define BPORT1_AB_RXIMR10_WIDTH         32
#define BPORT1_AB_RXIMR11_WRMASK        0xffffffff
#define BPORT1_AB_RXIMR11_WRNMASK       (0x0)
#define BPORT1_AB_RXIMR11_WIDTH         32
#define BPORT1_AB_RXIMR12_WRMASK        0xffffffff
#define BPORT1_AB_RXIMR12_WRNMASK       (0x0)
#define BPORT1_AB_RXIMR12_WIDTH         32
#define BPORT1_AB_RXIMR13_WRMASK        0xffffffff
#define BPORT1_AB_RXIMR13_WRNMASK       (0x0)
#define BPORT1_AB_RXIMR13_WIDTH         32
#define BPORT1_AB_RXIMR14_WRMASK        0xffffffff
#define BPORT1_AB_RXIMR14_WRNMASK       (0x0)
#define BPORT1_AB_RXIMR14_WIDTH         32
#define BPORT1_AB_RXIMR15_WRMASK        0xffffffff
#define BPORT1_AB_RXIMR15_WRNMASK       (0x0)
#define BPORT1_AB_RXIMR15_WIDTH         32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

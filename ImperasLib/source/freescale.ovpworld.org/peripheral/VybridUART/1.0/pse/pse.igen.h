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
        Uns8 value;
        struct {
            Uns8 SBR : 5;
            Uns8 __pad5 : 1;
            Uns8 RXEDGIE : 1;
            Uns8 LBKDIE : 1;
        } bits;
    } BDH;
    union { 
        Uns8 value;
        struct {
            Uns8 SBR : 8;
        } bits;
    } BDL;
    union { 
        Uns8 value;
        struct {
            Uns8 PT : 1;
            Uns8 PE : 1;
            Uns8 ILT : 1;
            Uns8 WAKE : 1;
            Uns8 M : 1;
            Uns8 RSRC : 1;
            Uns8 __pad6 : 1;
            Uns8 LOOPS : 1;
        } bits;
    } C1;
    union { 
        Uns8 value;
        struct {
            Uns8 SBK : 1;
            Uns8 RWU : 1;
            Uns8 RE : 1;
            Uns8 TE : 1;
            Uns8 ILIE : 1;
            Uns8 RIE : 1;
            Uns8 TCIE : 1;
            Uns8 TIE : 1;
        } bits;
    } C2;
    union { 
        Uns8 value;
        struct {
            Uns8 PF : 1;
            Uns8 FE : 1;
            Uns8 NF : 1;
            Uns8 OR : 1;
            Uns8 IDLE : 1;
            Uns8 RDRF : 1;
            Uns8 TC : 1;
            Uns8 TDRE : 1;
        } bits;
    } S1;
    union { 
        Uns8 value;
        struct {
            Uns8 RAF : 1;
            Uns8 LBKDE : 1;
            Uns8 BRK13 : 1;
            Uns8 RWUID : 1;
            Uns8 RXINV : 1;
            Uns8 MSBF : 1;
            Uns8 RXEDGIF : 1;
            Uns8 LBKDIF : 1;
        } bits;
    } S2;
    union { 
        Uns8 value;
        struct {
            Uns8 PEIE : 1;
            Uns8 FEIE : 1;
            Uns8 NEIE : 1;
            Uns8 ORIE : 1;
            Uns8 TXINV : 1;
            Uns8 TXDIR : 1;
            Uns8 T8 : 1;
            Uns8 R8 : 1;
        } bits;
    } C3;
    union { 
        Uns8 value;
        struct {
            Uns8 RT : 8;
        } bits;
    } D;
    union { 
        Uns8 value;
        struct {
            Uns8 MA : 8;
        } bits;
    } MA1;
    union { 
        Uns8 value;
        struct {
            Uns8 MA : 8;
        } bits;
    } MA2;
    union { 
        Uns8 value;
        struct {
            Uns8 BRFA : 5;
            Uns8 M10 : 1;
            Uns8 MAEN2 : 1;
            Uns8 MAEN1 : 1;
        } bits;
    } C4;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 5;
            Uns8 RDMAS : 1;
            Uns8 __pad6 : 1;
            Uns8 TDMAS : 1;
        } bits;
    } C5;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 6;
            Uns8 PARITYE : 1;
            Uns8 NOISY : 1;
        } bits;
    } ED;
    union { 
        Uns8 value;
        struct {
            Uns8 TXCTSE : 1;
            Uns8 TXRTSE : 1;
            Uns8 TXRTSPOL : 1;
            Uns8 RXRTSE : 1;
        } bits;
    } MODEM;
    union { 
        Uns8 value;
        struct {
            Uns8 TNP : 2;
            Uns8 IREN : 1;
        } bits;
    } IR;
    union { 
        Uns8 value;
        struct {
            Uns8 RXFIFOSIZE : 3;
            Uns8 RXFE : 1;
            Uns8 TXFIFOSIZE : 3;
            Uns8 TXFE : 1;
        } bits;
    } PFIFO;
    union { 
        Uns8 value;
        struct {
            Uns8 RXUFE : 1;
            Uns8 TXOFE : 1;
            Uns8 __pad2 : 4;
            Uns8 RXFLUSH : 1;
            Uns8 TXFLUSH : 1;
        } bits;
    } CFIFO;
    union { 
        Uns8 value;
        struct {
            Uns8 RXUF : 1;
            Uns8 TXOF : 1;
            Uns8 __pad2 : 4;
            Uns8 RXEMPT : 1;
            Uns8 TXEMPT : 1;
        } bits;
    } SFIFO;
    union { 
        Uns8 value;
        struct {
            Uns8 TXWATER : 8;
        } bits;
    } TWFIFO;
    union { 
        Uns8 value;
        struct {
            Uns8 TXCOUNT : 8;
        } bits;
    } TCFIFO;
    union { 
        Uns8 value;
        struct {
            Uns8 RXWATER : 8;
        } bits;
    } RWFIFO;
    union { 
        Uns8 value;
        struct {
            Uns8 RXCOUNT : 8;
        } bits;
    } RCFIFO;
    union { 
        Uns8 value;
        struct {
            Uns8 ISO_7816E : 1;
            Uns8 TTYPE : 1;
            Uns8 INIT : 1;
            Uns8 ANACK : 1;
            Uns8 ONACK : 1;
        } bits;
    } C7816;
    union { 
        Uns8 value;
        struct {
            Uns8 RXTE : 1;
            Uns8 TXTE : 1;
            Uns8 GTVE : 1;
            Uns8 __pad3 : 1;
            Uns8 INITDE : 1;
            Uns8 BWTE : 1;
            Uns8 CWTE : 1;
            Uns8 WTE : 1;
        } bits;
    } IE7816;
    union { 
        Uns8 value;
        struct {
            Uns8 RXT : 1;
            Uns8 TXT : 1;
            Uns8 GTV : 1;
            Uns8 __pad3 : 1;
            Uns8 INITD : 1;
            Uns8 BWT : 1;
            Uns8 CWT : 1;
            Uns8 WT : 1;
        } bits;
    } IS7816;
    union { 
        Uns8 value;
        struct {
            Uns8 WI : 8;
        } bits;
    } WP7816T0;
    union { 
        Uns8 value;
        struct {
            Uns8 GTN : 8;
        } bits;
    } WN7816;
    union { 
        Uns8 value;
        struct {
            Uns8 GTFD : 8;
        } bits;
    } WF7816;
    union { 
        Uns8 value;
        struct {
            Uns8 RXTHRESHOLD : 4;
            Uns8 TXTHRESHOLD : 4;
        } bits;
    } ET7816;
    union { 
        Uns8 value;
        struct {
            Uns8 TLEN : 8;
        } bits;
    } TL7816;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          DirectWrite;
    ppmNetHandle          DirectRead;
    ppmNetHandle          Interrupt;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(directReadCB);
PPM_REG_READ_CB(readD);
PPM_REG_READ_CB(readS1);
PPM_NET_CB(resetCB);
PPM_REG_VIEW_CB(viewS1);
PPM_REG_WRITE_CB(writeBDH);
PPM_REG_WRITE_CB(writeBDL);
PPM_REG_WRITE_CB(writeC2);
PPM_REG_WRITE_CB(writeC4);
PPM_REG_WRITE_CB(writeCFIFO);
PPM_REG_WRITE_CB(writeD);
PPM_REG_WRITE_CB(writeRWFIFO);
PPM_REG_WRITE_CB(writeTWFIFO);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_BDH_WRMASK            0xdf
#define BPORT1_AB_BDH_WRNMASK           (0x20)
#define BPORT1_AB_BDH_WIDTH             8
#define BPORT1_AB_BDL_WRMASK            0xff
#define BPORT1_AB_BDL_WRNMASK           (0x0)
#define BPORT1_AB_BDL_WIDTH             8
#define BPORT1_AB_C1_WRMASK             0xcf
#define BPORT1_AB_C1_WRNMASK            (0x30)
#define BPORT1_AB_C1_WIDTH              8
#define BPORT1_AB_C2_WRMASK             0xff
#define BPORT1_AB_C2_WRNMASK            (0x0)
#define BPORT1_AB_C2_WIDTH              8
#define BPORT1_AB_S1_WIDTH              8
#define BPORT1_AB_S2_WRMASK             0xfe
#define BPORT1_AB_S2_WRNMASK            (0x1)
#define BPORT1_AB_S2_WIDTH              8
#define BPORT1_AB_C3_WRMASK             0x7f
#define BPORT1_AB_C3_WRNMASK            (0x80)
#define BPORT1_AB_C3_WIDTH              8
#define BPORT1_AB_D_WRMASK              0xff
#define BPORT1_AB_D_WRNMASK             (0x0)
#define BPORT1_AB_D_WIDTH               8
#define BPORT1_AB_MA1_WRMASK            0xff
#define BPORT1_AB_MA1_WRNMASK           (0x0)
#define BPORT1_AB_MA1_WIDTH             8
#define BPORT1_AB_MA2_WRMASK            0xff
#define BPORT1_AB_MA2_WRNMASK           (0x0)
#define BPORT1_AB_MA2_WIDTH             8
#define BPORT1_AB_C4_WRMASK             0xff
#define BPORT1_AB_C4_WRNMASK            (0x0)
#define BPORT1_AB_C4_WIDTH              8
#define BPORT1_AB_C5_WRMASK             0xa0
#define BPORT1_AB_C5_WRNMASK            (0x5f)
#define BPORT1_AB_C5_WIDTH              8
#define BPORT1_AB_ED_WIDTH              8
#define BPORT1_AB_MODEM_WRMASK          0xf
#define BPORT1_AB_MODEM_WRNMASK         (0xf0)
#define BPORT1_AB_MODEM_WIDTH           8
#define BPORT1_AB_IR_WRMASK             0x7
#define BPORT1_AB_IR_WRNMASK            (0xf8)
#define BPORT1_AB_IR_WIDTH              8
#define BPORT1_AB_PFIFO_WRMASK          0x88
#define BPORT1_AB_PFIFO_WRNMASK         (0x77)
#define BPORT1_AB_PFIFO_WIDTH           8
#define BPORT1_AB_CFIFO_WRMASK          0xc3
#define BPORT1_AB_CFIFO_WRNMASK         (0x3c)
#define BPORT1_AB_CFIFO_WIDTH           8
#define BPORT1_AB_SFIFO_WRMASK          0x3
#define BPORT1_AB_SFIFO_WRNMASK         (0xfc)
#define BPORT1_AB_SFIFO_WIDTH           8
#define BPORT1_AB_TWFIFO_WRMASK         0xff
#define BPORT1_AB_TWFIFO_WRNMASK        (0x0)
#define BPORT1_AB_TWFIFO_WIDTH          8
#define BPORT1_AB_TCFIFO_WIDTH          8
#define BPORT1_AB_RWFIFO_WRMASK         0xff
#define BPORT1_AB_RWFIFO_WRNMASK        (0x0)
#define BPORT1_AB_RWFIFO_WIDTH          8
#define BPORT1_AB_RCFIFO_WIDTH          8
#define BPORT1_AB_C7816_WRMASK          0x1f
#define BPORT1_AB_C7816_WRNMASK         (0xe0)
#define BPORT1_AB_C7816_WIDTH           8
#define BPORT1_AB_IE7816_WRMASK         0xf7
#define BPORT1_AB_IE7816_WRNMASK        (0x8)
#define BPORT1_AB_IE7816_WIDTH          8
#define BPORT1_AB_IS7816_WRMASK         0xf7
#define BPORT1_AB_IS7816_WRNMASK        (0x8)
#define BPORT1_AB_IS7816_WIDTH          8
#define BPORT1_AB_WP7816T0_WRMASK       0xff
#define BPORT1_AB_WP7816T0_WRNMASK      (0x0)
#define BPORT1_AB_WP7816T0_WIDTH        8
#define BPORT1_AB_WN7816_WRMASK         0xff
#define BPORT1_AB_WN7816_WRNMASK        (0x0)
#define BPORT1_AB_WN7816_WIDTH          8
#define BPORT1_AB_WF7816_WRMASK         0xff
#define BPORT1_AB_WF7816_WRNMASK        (0x0)
#define BPORT1_AB_WF7816_WIDTH          8
#define BPORT1_AB_ET7816_WRMASK         0xff
#define BPORT1_AB_ET7816_WRNMASK        (0x0)
#define BPORT1_AB_ET7816_WIDTH          8
#define BPORT1_AB_TL7816_WRMASK         0xff
#define BPORT1_AB_TL7816_WRNMASK        (0x0)
#define BPORT1_AB_TL7816_WIDTH          8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

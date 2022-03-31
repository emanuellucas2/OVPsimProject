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
            Uns32 START : 1;
            Uns32 __pad1 : 7;
            Uns32 DDRCLS : 4;
            Uns32 __pad12 : 4;
            Uns32 VERSION : 16;
        } bits;
    } CR00;
    union { 
        Uns32 value;
        struct {
            Uns32 MAXROW : 5;
            Uns32 __pad5 : 3;
            Uns32 MAXCOL : 4;
            Uns32 __pad12 : 4;
            Uns32 CSMAX : 2;
        } bits;
    } CR01;
    union { 
        Uns32 value;
        struct {
            Uns32 TINIT : 24;
            Uns32 INITAREF : 4;
        } bits;
    } CR02;
    union { 
        Uns32 value;
        struct {
            Uns32 LATLIN : 4;
            Uns32 __pad4 : 4;
            Uns32 LATGATE : 4;
            Uns32 __pad12 : 4;
            Uns32 WRLAT : 4;
            Uns32 __pad20 : 4;
            Uns32 TCCD : 5;
        } bits;
    } CR03;
    union { 
        Uns32 value;
        struct {
            Uns32 TBINT : 3;
            Uns32 __pad3 : 5;
            Uns32 TRRD : 3;
            Uns32 __pad11 : 5;
            Uns32 TRC : 6;
            Uns32 __pad22 : 2;
            Uns32 TRASMIN : 8;
        } bits;
    } CR04;
    union { 
        Uns32 value;
        struct {
            Uns32 TWTR : 4;
            Uns32 __pad4 : 4;
            Uns32 TRP : 4;
            Uns32 __pad12 : 4;
            Uns32 TRTP : 3;
            Uns32 __pad19 : 5;
            Uns32 TMRD : 5;
        } bits;
    } CR05;
    union { 
        Uns32 value;
        struct {
            Uns32 TMOD : 8;
            Uns32 TRASMAX : 16;
            Uns32 INTWBR : 1;
        } bits;
    } CR06;
    union { 
        Uns32 value;
        struct {
            Uns32 CLKPW : 3;
            Uns32 __pad3 : 5;
            Uns32 TCKESR : 5;
            Uns32 __pad13 : 3;
            Uns32 AP : 1;
            Uns32 __pad17 : 7;
            Uns32 CCAPEN : 1;
        } bits;
    } CR07;
    union { 
        Uns32 value;
        struct {
            Uns32 TRAS : 1;
            Uns32 __pad1 : 7;
            Uns32 TRASDI : 8;
            Uns32 TWR : 5;
            Uns32 __pad21 : 3;
            Uns32 TDAL : 5;
        } bits;
    } CR08;
    union { 
        Uns32 value;
        struct {
            Uns32 TDLL : 16;
            Uns32 NOCMD : 1;
            Uns32 __pad17 : 7;
            Uns32 BSTLEN : 3;
        } bits;
    } CR09;
    union { 
        Uns32 value;
        struct {
            Uns32 TFAW : 6;
            Uns32 __pad6 : 2;
            Uns32 TCPD : 16;
            Uns32 TRPAB : 4;
        } bits;
    } CR10;
    union { 
        Uns32 value;
        struct {
            Uns32 REGDIMM : 1;
            Uns32 __pad1 : 7;
            Uns32 AREF : 1;
            Uns32 __pad9 : 7;
            Uns32 AREFMODE : 1;
            Uns32 __pad17 : 7;
            Uns32 TREFEN : 1;
        } bits;
    } CR11;
    union { 
        Uns32 value;
        struct {
            Uns32 TRFC : 10;
            Uns32 __pad10 : 6;
            Uns32 TREF : 14;
        } bits;
    } CR12;
    union { 
        Uns32 value;
        struct {
            Uns32 TREFINT : 14;
            Uns32 __pad14 : 2;
            Uns32 PD : 1;
        } bits;
    } CR13;
    union { 
        Uns32 value;
        struct {
            Uns32 TPDEX : 16;
            Uns32 TXSR : 16;
        } bits;
    } CR14;
    union { 
        Uns32 value;
        struct {
            Uns32 TXSNR : 16;
            Uns32 SREF : 1;
            Uns32 __pad17 : 7;
            Uns32 PUREF : 1;
        } bits;
    } CR15;
    union { 
        Uns32 value;
        struct {
            Uns32 QKREF : 1;
            Uns32 __pad1 : 7;
            Uns32 CLKDLY : 3;
            Uns32 __pad11 : 5;
            Uns32 LPCTRL : 5;
        } bits;
    } CR16;
    union { 
        Uns32 value;
        struct {
            Uns32 LPPDCNT : 16;
            Uns32 LPRFCNT : 16;
        } bits;
    } CR17;
    union { 
        Uns32 value;
        struct {
            Uns32 LPEXTCNT : 16;
            Uns32 LPAUTO : 5;
        } bits;
    } CR18;
    union { 
        Uns32 value;
        struct {
            Uns32 LPINTCNT : 16;
            Uns32 LPRFHOLD : 16;
        } bits;
    } CR19;
    union { 
        Uns32 value;
        struct {
            Uns32 LPRE : 2;
            Uns32 __pad2 : 6;
            Uns32 CKSRE : 4;
            Uns32 __pad12 : 4;
            Uns32 CKSRX : 4;
            Uns32 __pad20 : 4;
            Uns32 WRMD : 1;
        } bits;
    } CR20;
    union { 
        Uns32 value;
        struct {
            Uns32 MR0DAT0 : 16;
            Uns32 MR1DAT0 : 16;
        } bits;
    } CR21;
    union { 
        Uns32 value;
        struct {
            Uns32 MR2DATA0 : 16;
            Uns32 MR3DAT0 : 16;
        } bits;
    } CR22;
    union { 
        Uns32 value;
        struct {
            Uns32 NOT_USED2 : 16;
            Uns32 NOT_USED : 16;
        } bits;
    } CR23;
    union { 
        Uns32 value;
    } CR24;
    union { 
        Uns32 value;
        struct {
            Uns32 BNK8 : 1;
            Uns32 __pad1 : 7;
            Uns32 ADDPINS : 3;
            Uns32 __pad11 : 5;
            Uns32 COLSIZ : 3;
            Uns32 __pad19 : 5;
            Uns32 APREBIT : 4;
        } bits;
    } CR25;
    union { 
        Uns32 value;
        struct {
            Uns32 AGECNT : 8;
            Uns32 CMDAGE : 8;
            Uns32 ADDCOL : 1;
            Uns32 __pad17 : 7;
            Uns32 BNKSPT : 1;
        } bits;
    } CR26;
    union { 
        Uns32 value;
        struct {
            Uns32 PLEN : 1;
            Uns32 __pad1 : 7;
            Uns32 PRIEN : 1;
            Uns32 __pad9 : 7;
            Uns32 RWEN : 1;
            Uns32 __pad17 : 7;
            Uns32 SWPEN : 1;
        } bits;
    } CR27;
    union { 
        Uns32 value;
        struct {
            Uns32 CSMAP : 1;
            Uns32 __pad1 : 7;
            Uns32 REDUC : 1;
            Uns32 __pad9 : 7;
            Uns32 BIGEND : 1;
            Uns32 __pad17 : 7;
            Uns32 CMDLATR : 1;
        } bits;
    } CR28;
    union { 
        Uns32 value;
        struct {
            Uns32 WRLATR : 1;
            Uns32 __pad1 : 7;
            Uns32 FSTWR : 1;
            Uns32 __pad9 : 7;
            Uns32 QFULL : 2;
            Uns32 __pad18 : 6;
            Uns32 RESYNC : 1;
        } bits;
    } CR29;
    union { 
        Uns32 value;
        struct {
            Uns32 RSYNCRF : 1;
            Uns32 __pad1 : 7;
            Uns32 INTSTAT : 9;
            Uns32 __pad17 : 7;
            Uns32 INTACK : 8;
        } bits;
    } CR30;
    union { 
        Uns32 value;
        struct {
            Uns32 INTMASK : 9;
        } bits;
    } CR31;
    union { 
        Uns32 value;
        struct {
            Uns32 OORAD : 32;
        } bits;
    } CR32;
    union { 
        Uns32 value;
        struct {
            Uns32 OORLEN : 10;
            Uns32 __pad10 : 6;
            Uns32 OORTYP : 6;
            Uns32 __pad22 : 2;
            Uns32 OORID : 2;
        } bits;
    } CR33;
    union { 
        Uns32 value;
        struct {
            Uns32 ODTRDC : 1;
            Uns32 __pad1 : 7;
            Uns32 ODTWRCS : 1;
        } bits;
    } CR34;
    union { 
        Uns32 value;
        struct {
            Uns32 R2WSMCS : 4;
            Uns32 __pad4 : 4;
            Uns32 W2RSMCS : 4;
        } bits;
    } CR35;
    union { 
        Uns32 value;
        struct {
            Uns32 NOT_USED2 : 16;
            Uns32 NOT_USED : 16;
        } bits;
    } CR36;
    union { 
        Uns32 value;
        struct {
            Uns32 R2RSAME : 3;
            Uns32 __pad3 : 5;
            Uns32 R2WSAME : 3;
            Uns32 __pad11 : 5;
            Uns32 W2RSAME : 3;
            Uns32 __pad19 : 5;
            Uns32 W2WSAME : 3;
        } bits;
    } CR37;
    union { 
        Uns32 value;
        struct {
            Uns32 PDNCS : 5;
            Uns32 __pad5 : 3;
            Uns32 PUPCS : 5;
            Uns32 __pad13 : 3;
            Uns32 PWRCNT : 11;
        } bits;
    } CR38;
    union { 
        Uns32 value;
        struct {
            Uns32 P0RDCNT : 11;
            Uns32 __pad11 : 5;
            Uns32 RP0 : 2;
            Uns32 __pad18 : 6;
            Uns32 WP0 : 2;
        } bits;
    } CR39;
    union { 
        Uns32 value;
        struct {
            Uns32 P0TYP : 2;
            Uns32 __pad2 : 6;
            Uns32 P1WRCNT : 11;
        } bits;
    } CR40;
    union { 
        Uns32 value;
        struct {
            Uns32 P1RDCNT : 11;
            Uns32 __pad11 : 5;
            Uns32 RP1 : 2;
            Uns32 __pad18 : 6;
            Uns32 WP1 : 2;
        } bits;
    } CR41;
    union { 
        Uns32 value;
        struct {
            Uns32 P1TYP : 2;
            Uns32 __pad2 : 6;
            Uns32 P2WRCNT : 11;
        } bits;
    } CR42;
    union { 
        Uns32 value;
        struct {
            Uns32 P2RDCNT : 11;
            Uns32 __pad11 : 5;
            Uns32 RP2 : 2;
            Uns32 __pad18 : 6;
            Uns32 WP2 : 2;
        } bits;
    } CR43;
    union { 
        Uns32 value;
        struct {
            Uns32 P2TYP : 2;
            Uns32 __pad2 : 6;
            Uns32 WRRLAT : 1;
            Uns32 __pad9 : 7;
            Uns32 WRRSHARE : 1;
            Uns32 __pad17 : 7;
            Uns32 WRRERR : 4;
        } bits;
    } CR44;
    union { 
        Uns32 value;
        struct {
            Uns32 P0PRI0 : 4;
            Uns32 __pad4 : 4;
            Uns32 P0PRI1 : 4;
            Uns32 __pad12 : 4;
            Uns32 P0PRI2 : 4;
            Uns32 __pad20 : 4;
            Uns32 P0PRI3 : 4;
        } bits;
    } CR45;
    union { 
        Uns32 value;
        struct {
            Uns32 P0ORD : 2;
            Uns32 __pad2 : 6;
            Uns32 P0PRIRLX : 10;
            Uns32 __pad18 : 6;
            Uns32 P1PRI0 : 4;
        } bits;
    } CR46;
    union { 
        Uns32 value;
        struct {
            Uns32 P1PRI1 : 4;
            Uns32 __pad4 : 4;
            Uns32 P1PRI2 : 4;
            Uns32 __pad12 : 4;
            Uns32 P1PRI3 : 4;
            Uns32 __pad20 : 4;
            Uns32 P1ORD : 2;
        } bits;
    } CR47;
    union { 
        Uns32 value;
        struct {
            Uns32 P1PRIRLX : 10;
            Uns32 __pad10 : 6;
            Uns32 P2PRI0 : 4;
            Uns32 __pad20 : 4;
            Uns32 P2PRI1 : 4;
        } bits;
    } CR48;
    union { 
        Uns32 value;
        struct {
            Uns32 P2PRI2 : 4;
            Uns32 __pad4 : 4;
            Uns32 P2PRI3 : 4;
            Uns32 __pad12 : 4;
            Uns32 P2ORD : 2;
        } bits;
    } CR49;
    union { 
        Uns32 value;
        struct {
            Uns32 P2PRIRLX : 10;
            Uns32 __pad10 : 6;
            Uns32 CLKSTATUS : 1;
        } bits;
    } CR50;
    union { 
        Uns32 value;
        struct {
            Uns32 DLLRSTDLY : 16;
            Uns32 DLLRADLY : 8;
            Uns32 PHYWRLAT : 4;
        } bits;
    } CR51;
    union { 
        Uns32 value;
        struct {
            Uns32 PYWRLTBS : 4;
            Uns32 __pad4 : 4;
            Uns32 PHYRDLAT : 4;
            Uns32 __pad12 : 4;
            Uns32 RDDATAEN : 4;
            Uns32 __pad20 : 4;
            Uns32 RDDTENBAS : 4;
        } bits;
    } CR52;
    union { 
        Uns32 value;
        struct {
            Uns32 CLKDISCS : 1;
            Uns32 __pad1 : 7;
            Uns32 CRTLUPDMN : 4;
            Uns32 __pad12 : 4;
            Uns32 CTRLUPDMX : 14;
        } bits;
    } CR53;
    union { 
        Uns32 value;
        struct {
            Uns32 PHYUPDTY0 : 14;
            Uns32 __pad14 : 2;
            Uns32 PHYUPDTY1 : 14;
        } bits;
    } CR54;
    union { 
        Uns32 value;
        struct {
            Uns32 PHYUPDTY2 : 14;
            Uns32 __pad14 : 2;
            Uns32 PHYUPDTY3 : 14;
        } bits;
    } CR55;
    union { 
        Uns32 value;
        struct {
            Uns32 PHYUPDRESP : 14;
            Uns32 __pad14 : 2;
            Uns32 RDLATADJ : 4;
            Uns32 __pad20 : 4;
            Uns32 WRLATADJ : 4;
        } bits;
    } CR56;
    union { 
        Uns32 value;
        struct {
            Uns32 CMDDLY : 4;
            Uns32 __pad4 : 4;
            Uns32 CLKDISDLY : 3;
            Uns32 __pad11 : 5;
            Uns32 CLKENDLY : 4;
            Uns32 __pad20 : 4;
            Uns32 ODTALTEN : 1;
        } bits;
    } CR57;
    union { 
        Uns32 value;
        struct {
            Uns32 NOT_USED2 : 16;
            Uns32 NOT_USED : 16;
        } bits;
    } CR58;
    union { 
        Uns32 value;
        struct {
            Uns32 NOT_USED2 : 16;
            Uns32 NOT_USED : 16;
        } bits;
    } CR59;
    union { 
        Uns32 value;
        struct {
            Uns32 NOT_USED2 : 16;
            Uns32 NOT_USED : 16;
        } bits;
    } CR60;
    union { 
        Uns32 value;
        struct {
            Uns32 NOT_USED2 : 16;
            Uns32 NOT_USED : 16;
        } bits;
    } CR61;
    union { 
        Uns32 value;
        struct {
            Uns32 NOT_USED2 : 16;
            Uns32 NOT_USED : 16;
        } bits;
    } CR62;
    union { 
        Uns32 value;
        struct {
            Uns32 NOT_USED2 : 16;
            Uns32 NOT_USED : 16;
        } bits;
    } CR63;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 30;
            Uns32 RST : 1;
        } bits;
    } RCR;
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

#define BPORT1_AB_CR00_WIDTH            32
#define BPORT1_AB_CR01_WIDTH            32
#define BPORT1_AB_CR02_WIDTH            32
#define BPORT1_AB_CR03_WIDTH            32
#define BPORT1_AB_CR04_WIDTH            32
#define BPORT1_AB_CR05_WIDTH            32
#define BPORT1_AB_CR06_WIDTH            32
#define BPORT1_AB_CR07_WIDTH            32
#define BPORT1_AB_CR08_WIDTH            32
#define BPORT1_AB_CR09_WIDTH            32
#define BPORT1_AB_CR10_WIDTH            32
#define BPORT1_AB_CR11_WIDTH            32
#define BPORT1_AB_CR12_WIDTH            32
#define BPORT1_AB_CR13_WIDTH            32
#define BPORT1_AB_CR14_WIDTH            32
#define BPORT1_AB_CR15_WIDTH            32
#define BPORT1_AB_CR16_WIDTH            32
#define BPORT1_AB_CR17_WIDTH            32
#define BPORT1_AB_CR18_WIDTH            32
#define BPORT1_AB_CR19_WIDTH            32
#define BPORT1_AB_CR20_WIDTH            32
#define BPORT1_AB_CR21_WIDTH            32
#define BPORT1_AB_CR22_WIDTH            32
#define BPORT1_AB_CR23_WIDTH            32
#define BPORT1_AB_CR24_WIDTH            32
#define BPORT1_AB_CR25_WIDTH            32
#define BPORT1_AB_CR26_WIDTH            32
#define BPORT1_AB_CR27_WIDTH            32
#define BPORT1_AB_CR28_WIDTH            32
#define BPORT1_AB_CR29_WIDTH            32
#define BPORT1_AB_CR30_WIDTH            32
#define BPORT1_AB_CR31_WIDTH            32
#define BPORT1_AB_CR32_WIDTH            32
#define BPORT1_AB_CR33_WIDTH            32
#define BPORT1_AB_CR34_WIDTH            32
#define BPORT1_AB_CR35_WIDTH            32
#define BPORT1_AB_CR36_WIDTH            32
#define BPORT1_AB_CR37_WIDTH            32
#define BPORT1_AB_CR38_WIDTH            32
#define BPORT1_AB_CR39_WIDTH            32
#define BPORT1_AB_CR40_WIDTH            32
#define BPORT1_AB_CR41_WIDTH            32
#define BPORT1_AB_CR42_WIDTH            32
#define BPORT1_AB_CR43_WIDTH            32
#define BPORT1_AB_CR44_WIDTH            32
#define BPORT1_AB_CR45_WIDTH            32
#define BPORT1_AB_CR46_WIDTH            32
#define BPORT1_AB_CR47_WIDTH            32
#define BPORT1_AB_CR48_WIDTH            32
#define BPORT1_AB_CR49_WIDTH            32
#define BPORT1_AB_CR50_WIDTH            32
#define BPORT1_AB_CR51_WIDTH            32
#define BPORT1_AB_CR52_WIDTH            32
#define BPORT1_AB_CR53_WIDTH            32
#define BPORT1_AB_CR54_WIDTH            32
#define BPORT1_AB_CR55_WIDTH            32
#define BPORT1_AB_CR56_WIDTH            32
#define BPORT1_AB_CR57_WIDTH            32
#define BPORT1_AB_CR58_WIDTH            32
#define BPORT1_AB_CR59_WIDTH            32
#define BPORT1_AB_CR60_WIDTH            32
#define BPORT1_AB_CR61_WIDTH            32
#define BPORT1_AB_CR62_WIDTH            32
#define BPORT1_AB_CR63_WIDTH            32
#define BPORT1_AB_RCR_WIDTH             32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

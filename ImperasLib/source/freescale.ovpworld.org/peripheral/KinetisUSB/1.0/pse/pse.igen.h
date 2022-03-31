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
            Uns8 ID : 6;
        } bits;
    } PERID;
    union { 
        Uns8 value;
        struct {
            Uns8 NID : 6;
        } bits;
    } IDCOMP;
    union { 
        Uns8 value;
        struct {
            Uns8 REV : 8;
        } bits;
    } REV;
    union { 
        Uns8 value;
        struct {
            Uns8 IEHOST : 1;
            Uns8 __pad1 : 2;
            Uns8 IRQNUM : 5;
        } bits;
    } ADDINFO;
    union { 
        Uns8 value;
        struct {
            Uns8 AVBUSCHG : 1;
            Uns8 __pad1 : 1;
            Uns8 B_SESS_CHG : 1;
            Uns8 SESSVLDCHG : 1;
            Uns8 __pad4 : 1;
            Uns8 LINE_STATE_CHG : 1;
            Uns8 ONEMSEC : 1;
            Uns8 IDCHG : 1;
        } bits;
    } OTGISTAT;
    union { 
        Uns8 value;
        struct {
            Uns8 AVBUSEN : 1;
            Uns8 __pad1 : 1;
            Uns8 BSESSEN : 1;
            Uns8 SESSVLDEN : 1;
            Uns8 __pad4 : 1;
            Uns8 LINESTATEEN : 1;
            Uns8 ONEMSECEN : 1;
            Uns8 IDEN : 1;
        } bits;
    } OTGICR;
    union { 
        Uns8 value;
        struct {
            Uns8 AVBUSVLD : 1;
            Uns8 __pad1 : 1;
            Uns8 BSESSEND : 1;
            Uns8 SESS_VLD : 1;
            Uns8 __pad4 : 1;
            Uns8 LINESTATESTABLE : 1;
            Uns8 ONEMSECEN : 1;
            Uns8 ID : 1;
        } bits;
    } OTGSTAT;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 2;
            Uns8 OTGEN : 1;
            Uns8 __pad3 : 1;
            Uns8 DMLOW : 1;
            Uns8 DPLOW : 1;
            Uns8 __pad6 : 1;
            Uns8 DPHIGH : 1;
        } bits;
    } OTGCTL;
    union { 
        Uns8 value;
        struct {
            Uns8 USBRST : 1;
            Uns8 ERROR : 1;
            Uns8 SOFTOK : 1;
            Uns8 TOKDNE : 1;
            Uns8 SLEEP : 1;
            Uns8 RESUME : 1;
            Uns8 ATTACH : 1;
            Uns8 STALL : 1;
        } bits;
    } ISTAT;
    union { 
        Uns8 value;
        struct {
            Uns8 USBRSTEN : 1;
            Uns8 ERROREN : 1;
            Uns8 SOFTOKEN : 1;
            Uns8 TOKDNEEN : 1;
            Uns8 SLEEPEN : 1;
            Uns8 RESUMEEN : 1;
            Uns8 ATTACHEN : 1;
            Uns8 STALLEN : 1;
        } bits;
    } INTEN;
    union { 
        Uns8 value;
        struct {
            Uns8 PIDERR : 1;
            Uns8 CRC5EOF : 1;
            Uns8 CRC16 : 1;
            Uns8 DFN8 : 1;
            Uns8 BTOERR : 1;
            Uns8 DMAERR : 1;
            Uns8 __pad6 : 1;
            Uns8 BTSERR : 1;
        } bits;
    } ERRSTAT;
    union { 
        Uns8 value;
        struct {
            Uns8 PIDERREN : 1;
            Uns8 CRC5EOFEN : 1;
            Uns8 CRC16EN : 1;
            Uns8 DFN8EN : 1;
            Uns8 BTOERREN : 1;
            Uns8 DMAERREN : 1;
            Uns8 __pad6 : 1;
            Uns8 BTSERREN : 1;
        } bits;
    } ERREN;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 2;
            Uns8 ODD : 1;
            Uns8 TX : 1;
            Uns8 ENDP : 4;
        } bits;
    } STAT;
    union { 
        Uns8 value;
        struct {
            Uns8 USBENSOFEN : 1;
            Uns8 ODDRST : 1;
            Uns8 RESUME : 1;
            Uns8 HOSTMODEEN : 1;
            Uns8 RESET : 1;
            Uns8 TXSUSPENDTOKENBUSY : 1;
            Uns8 SE0 : 1;
            Uns8 JSTATE : 1;
        } bits;
    } CTL;
    union { 
        Uns8 value;
        struct {
            Uns8 ADDR : 7;
            Uns8 LSEN : 1;
        } bits;
    } ADDR;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 1;
            Uns8 BDTBA : 7;
        } bits;
    } BDTPAGE1;
    union { 
        Uns8 value;
        struct {
            Uns8 FRM : 8;
        } bits;
    } FRMNUML;
    union { 
        Uns8 value;
        struct {
            Uns8 FRM : 3;
        } bits;
    } FRMNUMH;
    union { 
        Uns8 value;
        struct {
            Uns8 TOKENENDPT : 4;
            Uns8 TOKENPID : 4;
        } bits;
    } TOKEN;
    union { 
        Uns8 value;
        struct {
            Uns8 CNT : 8;
        } bits;
    } SOFTHLD;
    union { 
        Uns8 value;
        struct {
            Uns8 BDTBA : 8;
        } bits;
    } BDTPAGE2;
    union { 
        Uns8 value;
        struct {
            Uns8 BDTBA : 8;
        } bits;
    } BDTPAGE3;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT0;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT1;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT2;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT3;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT4;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT5;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT6;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT7;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT8;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT9;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT10;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT11;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT12;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT13;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT14;
    union { 
        Uns8 value;
        struct {
            Uns8 EPHSHK : 1;
            Uns8 EPSTALL : 1;
            Uns8 EPTXEN : 1;
            Uns8 EPRXEN : 1;
            Uns8 EPCTLDIS : 1;
            Uns8 __pad5 : 1;
            Uns8 RETRYDIS : 1;
            Uns8 HOSTWOHUB : 1;
        } bits;
    } ENDPOINT15;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 6;
            Uns8 PDE : 1;
            Uns8 SUSP : 1;
        } bits;
    } USBCTRL;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 4;
            Uns8 DMPD : 1;
            Uns8 __pad5 : 1;
            Uns8 DPPD : 1;
            Uns8 DPPU : 1;
        } bits;
    } OBSERVE;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 4;
            Uns8 DPPULLUPNONOTG : 1;
        } bits;
    } CONTROL;
    union { 
        Uns8 value;
        struct {
            Uns8 USB_RESUME_INT : 1;
            Uns8 SYNC_DET : 1;
            Uns8 __pad2 : 3;
            Uns8 USBRESMEN : 1;
            Uns8 __pad6 : 1;
            Uns8 USBRESET : 1;
        } bits;
    } USBTRC0;
    union { 
        Uns8 value;
        struct {
            Uns8 ADJ : 8;
        } bits;
    } USBFRMADJUST;
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

#define BPORT1_AB_PERID_WIDTH           8
#define BPORT1_AB_IDCOMP_WIDTH          8
#define BPORT1_AB_REV_WIDTH             8
#define BPORT1_AB_ADDINFO_WIDTH         8
#define BPORT1_AB_OTGISTAT_WRMASK       0xed
#define BPORT1_AB_OTGISTAT_WRNMASK      (0x12)
#define BPORT1_AB_OTGISTAT_WIDTH        8
#define BPORT1_AB_OTGICR_WRMASK         0xed
#define BPORT1_AB_OTGICR_WRNMASK        (0x12)
#define BPORT1_AB_OTGICR_WIDTH          8
#define BPORT1_AB_OTGSTAT_WRMASK        0xed
#define BPORT1_AB_OTGSTAT_WRNMASK       (0x12)
#define BPORT1_AB_OTGSTAT_WIDTH         8
#define BPORT1_AB_OTGCTL_WRMASK         0xb4
#define BPORT1_AB_OTGCTL_WRNMASK        (0x4b)
#define BPORT1_AB_OTGCTL_WIDTH          8
#define BPORT1_AB_ISTAT_WRMASK          0xff
#define BPORT1_AB_ISTAT_WRNMASK         (0x0)
#define BPORT1_AB_ISTAT_WIDTH           8
#define BPORT1_AB_INTEN_WRMASK          0xff
#define BPORT1_AB_INTEN_WRNMASK         (0x0)
#define BPORT1_AB_INTEN_WIDTH           8
#define BPORT1_AB_ERRSTAT_WRMASK        0xbf
#define BPORT1_AB_ERRSTAT_WRNMASK       (0x40)
#define BPORT1_AB_ERRSTAT_WIDTH         8
#define BPORT1_AB_ERREN_WRMASK          0xbf
#define BPORT1_AB_ERREN_WRNMASK         (0x40)
#define BPORT1_AB_ERREN_WIDTH           8
#define BPORT1_AB_STAT_WIDTH            8
#define BPORT1_AB_CTL_WRMASK            0xff
#define BPORT1_AB_CTL_WRNMASK           (0x0)
#define BPORT1_AB_CTL_WIDTH             8
#define BPORT1_AB_ADDR_WRMASK           0xff
#define BPORT1_AB_ADDR_WRNMASK          (0x0)
#define BPORT1_AB_ADDR_WIDTH            8
#define BPORT1_AB_BDTPAGE1_WRMASK       0xfe
#define BPORT1_AB_BDTPAGE1_WRNMASK      (0x1)
#define BPORT1_AB_BDTPAGE1_WIDTH        8
#define BPORT1_AB_FRMNUML_WRMASK        0xff
#define BPORT1_AB_FRMNUML_WRNMASK       (0x0)
#define BPORT1_AB_FRMNUML_WIDTH         8
#define BPORT1_AB_FRMNUMH_WRMASK        0x7
#define BPORT1_AB_FRMNUMH_WRNMASK       (0xf8)
#define BPORT1_AB_FRMNUMH_WIDTH         8
#define BPORT1_AB_TOKEN_WRMASK          0xff
#define BPORT1_AB_TOKEN_WRNMASK         (0x0)
#define BPORT1_AB_TOKEN_WIDTH           8
#define BPORT1_AB_SOFTHLD_WRMASK        0xff
#define BPORT1_AB_SOFTHLD_WRNMASK       (0x0)
#define BPORT1_AB_SOFTHLD_WIDTH         8
#define BPORT1_AB_BDTPAGE2_WRMASK       0xff
#define BPORT1_AB_BDTPAGE2_WRNMASK      (0x0)
#define BPORT1_AB_BDTPAGE2_WIDTH        8
#define BPORT1_AB_BDTPAGE3_WRMASK       0xff
#define BPORT1_AB_BDTPAGE3_WRNMASK      (0x0)
#define BPORT1_AB_BDTPAGE3_WIDTH        8
#define BPORT1_AB_ENDPOINT0_WRMASK      0xdf
#define BPORT1_AB_ENDPOINT0_WRNMASK     (0x20)
#define BPORT1_AB_ENDPOINT0_WIDTH       8
#define BPORT1_AB_ENDPOINT1_WRMASK      0xdf
#define BPORT1_AB_ENDPOINT1_WRNMASK     (0x20)
#define BPORT1_AB_ENDPOINT1_WIDTH       8
#define BPORT1_AB_ENDPOINT2_WRMASK      0xdf
#define BPORT1_AB_ENDPOINT2_WRNMASK     (0x20)
#define BPORT1_AB_ENDPOINT2_WIDTH       8
#define BPORT1_AB_ENDPOINT3_WRMASK      0xdf
#define BPORT1_AB_ENDPOINT3_WRNMASK     (0x20)
#define BPORT1_AB_ENDPOINT3_WIDTH       8
#define BPORT1_AB_ENDPOINT4_WRMASK      0xdf
#define BPORT1_AB_ENDPOINT4_WRNMASK     (0x20)
#define BPORT1_AB_ENDPOINT4_WIDTH       8
#define BPORT1_AB_ENDPOINT5_WRMASK      0xdf
#define BPORT1_AB_ENDPOINT5_WRNMASK     (0x20)
#define BPORT1_AB_ENDPOINT5_WIDTH       8
#define BPORT1_AB_ENDPOINT6_WRMASK      0xdf
#define BPORT1_AB_ENDPOINT6_WRNMASK     (0x20)
#define BPORT1_AB_ENDPOINT6_WIDTH       8
#define BPORT1_AB_ENDPOINT7_WRMASK      0xdf
#define BPORT1_AB_ENDPOINT7_WRNMASK     (0x20)
#define BPORT1_AB_ENDPOINT7_WIDTH       8
#define BPORT1_AB_ENDPOINT8_WRMASK      0xdf
#define BPORT1_AB_ENDPOINT8_WRNMASK     (0x20)
#define BPORT1_AB_ENDPOINT8_WIDTH       8
#define BPORT1_AB_ENDPOINT9_WRMASK      0xdf
#define BPORT1_AB_ENDPOINT9_WRNMASK     (0x20)
#define BPORT1_AB_ENDPOINT9_WIDTH       8
#define BPORT1_AB_ENDPOINT10_WRMASK     0xdf
#define BPORT1_AB_ENDPOINT10_WRNMASK    (0x20)
#define BPORT1_AB_ENDPOINT10_WIDTH      8
#define BPORT1_AB_ENDPOINT11_WRMASK     0xdf
#define BPORT1_AB_ENDPOINT11_WRNMASK    (0x20)
#define BPORT1_AB_ENDPOINT11_WIDTH      8
#define BPORT1_AB_ENDPOINT12_WRMASK     0xdf
#define BPORT1_AB_ENDPOINT12_WRNMASK    (0x20)
#define BPORT1_AB_ENDPOINT12_WIDTH      8
#define BPORT1_AB_ENDPOINT13_WRMASK     0xdf
#define BPORT1_AB_ENDPOINT13_WRNMASK    (0x20)
#define BPORT1_AB_ENDPOINT13_WIDTH      8
#define BPORT1_AB_ENDPOINT14_WRMASK     0xdf
#define BPORT1_AB_ENDPOINT14_WRNMASK    (0x20)
#define BPORT1_AB_ENDPOINT14_WIDTH      8
#define BPORT1_AB_ENDPOINT15_WRMASK     0xdf
#define BPORT1_AB_ENDPOINT15_WRNMASK    (0x20)
#define BPORT1_AB_ENDPOINT15_WIDTH      8
#define BPORT1_AB_USBCTRL_WRMASK        0xc0
#define BPORT1_AB_USBCTRL_WRNMASK       (0x3f)
#define BPORT1_AB_USBCTRL_WIDTH         8
#define BPORT1_AB_OBSERVE_WIDTH         8
#define BPORT1_AB_CONTROL_WRMASK        0x10
#define BPORT1_AB_CONTROL_WRNMASK       (0xef)
#define BPORT1_AB_CONTROL_WIDTH         8
#define BPORT1_AB_USBTRC0_WRMASK        0xa0
#define BPORT1_AB_USBTRC0_WRNMASK       (0x5f)
#define BPORT1_AB_USBTRC0_WIDTH         8
#define BPORT1_AB_USBFRMADJUST_WRMASK   0xff
#define BPORT1_AB_USBFRMADJUST_WRNMASK  (0x0)
#define BPORT1_AB_USBFRMADJUST_WIDTH    8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

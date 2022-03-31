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
            Uns32 ID : 6;
            Uns32 __pad6 : 2;
            Uns32 NID : 6;
            Uns32 __pad14 : 2;
            Uns32 REVISION : 8;
        } bits;
    } ID;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 4;
            Uns32 PHYW : 2;
            Uns32 PHYM : 3;
            Uns32 SM : 2;
        } bits;
    } HWGENERAL;
    union { 
        Uns32 value;
        struct {
            Uns32 HC : 1;
            Uns32 NPORT : 3;
        } bits;
    } HWHOST;
    union { 
        Uns32 value;
        struct {
            Uns32 DC : 1;
            Uns32 DEVEP : 5;
        } bits;
    } HWDEVICE;
    union { 
        Uns32 value;
        struct {
            Uns32 TXBURST : 8;
            Uns32 __pad8 : 8;
            Uns32 TXCHANADD : 8;
        } bits;
    } HWTXBUF;
    union { 
        Uns32 value;
        struct {
            Uns32 RXBURST : 8;
            Uns32 RXADD : 8;
        } bits;
    } HWRXBUF;
    union { 
        Uns32 value;
        struct {
            Uns32 GPTLD : 24;
        } bits;
    } GPTIMER0LD;
    union { 
        Uns32 value;
        struct {
            Uns32 GPTCNT : 24;
            Uns32 GPTMODE : 1;
            Uns32 __pad25 : 5;
            Uns32 GPTRST : 1;
            Uns32 GPTRUN : 1;
        } bits;
    } GPTIMER0CTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 GPTLD : 24;
        } bits;
    } GPTIMER1LD;
    union { 
        Uns32 value;
        struct {
            Uns32 GPTCNT : 24;
            Uns32 GPTMODE : 1;
            Uns32 __pad25 : 5;
            Uns32 GPTRST : 1;
            Uns32 GPTRUN : 1;
        } bits;
    } GPTIMER1CTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 AHBBRST : 3;
        } bits;
    } SBUSCFG;
    union { 
        Uns32 value;
    } CAPVERSION;
    union { 
        Uns32 value;
        struct {
            Uns32 N_PORTS : 4;
            Uns32 PPC : 1;
            Uns32 __pad5 : 3;
            Uns32 N_PCC : 4;
            Uns32 N_CC : 4;
            Uns32 PI : 1;
            Uns32 __pad17 : 3;
            Uns32 N_PTT : 4;
            Uns32 N_TT : 4;
        } bits;
    } HCSPARAMS;
    union { 
        Uns32 value;
        struct {
            Uns32 ADC : 1;
            Uns32 PFL : 1;
            Uns32 ASP : 1;
            Uns32 __pad3 : 1;
            Uns32 IST : 4;
            Uns32 EECP : 8;
        } bits;
    } HCCPARAMS;
    union { 
        Uns32 value;
    } DCIVERSION;
    union { 
        Uns32 value;
        struct {
            Uns32 DEN : 5;
            Uns32 __pad5 : 2;
            Uns32 DC : 1;
            Uns32 HC : 1;
        } bits;
    } DCCPARAMS;
    union { 
        Uns32 value;
        struct {
            Uns32 RS : 1;
            Uns32 RST : 1;
            Uns32 FS1 : 2;
            Uns32 PSE : 1;
            Uns32 ASE : 1;
            Uns32 IAA : 1;
            Uns32 __pad7 : 1;
            Uns32 ASP : 2;
            Uns32 __pad10 : 1;
            Uns32 ASPE : 1;
            Uns32 __pad12 : 1;
            Uns32 SUTW : 1;
            Uns32 ATDTW : 1;
            Uns32 FS2 : 1;
            Uns32 ITC : 8;
        } bits;
    } USBCMD;
    union { 
        Uns32 value;
        struct {
            Uns32 UI : 1;
            Uns32 UEI : 1;
            Uns32 PCI : 1;
            Uns32 FRI : 1;
            Uns32 SEI : 1;
            Uns32 AAI : 1;
            Uns32 URI : 1;
            Uns32 SRI : 1;
            Uns32 SLI : 1;
            Uns32 __pad9 : 1;
            Uns32 ULPII : 1;
            Uns32 __pad11 : 1;
            Uns32 HCH : 1;
            Uns32 RCL : 1;
            Uns32 PS : 1;
            Uns32 AS : 1;
            Uns32 NAKI : 1;
            Uns32 __pad17 : 1;
            Uns32 UAI : 1;
            Uns32 UPI : 1;
            Uns32 __pad20 : 4;
            Uns32 TI0 : 1;
            Uns32 TI1 : 1;
        } bits;
    } USBSTS;
    union { 
        Uns32 value;
        struct {
            Uns32 UE : 1;
            Uns32 UEE : 1;
            Uns32 PCE : 1;
            Uns32 FRE : 1;
            Uns32 SEE : 1;
            Uns32 AAE : 1;
            Uns32 URE : 1;
            Uns32 SRE : 1;
            Uns32 SLE : 1;
            Uns32 __pad9 : 1;
            Uns32 ULPIE : 1;
            Uns32 __pad11 : 5;
            Uns32 NAKE : 1;
            Uns32 __pad17 : 1;
            Uns32 UAIE : 1;
            Uns32 UPIE : 1;
            Uns32 __pad20 : 4;
            Uns32 TIE0 : 1;
            Uns32 TIE1 : 1;
        } bits;
    } USBINTR;
    union { 
        Uns32 value;
        struct {
            Uns32 FRINDEX : 14;
        } bits;
    } FRINDEX;
    union { 
        Uns32 value;
    } DEVICEADDR;
    union { 
        Uns32 value;
    } ASYNCLISTADDR;
    union { 
        Uns32 value;
        struct {
            Uns32 RXPBURST : 8;
            Uns32 TXPBURST : 9;
        } bits;
    } BURSTSIZE;
    union { 
        Uns32 value;
        struct {
            Uns32 TXSCHOH : 8;
            Uns32 TXSCHHEALTH : 5;
            Uns32 __pad13 : 3;
            Uns32 TXFIFOTHRES : 6;
        } bits;
    } TXFILLTUNING;
    union { 
        Uns32 value;
        struct {
            Uns32 EPRN : 6;
            Uns32 __pad6 : 10;
            Uns32 EPTN : 6;
        } bits;
    } ENDPTNAK;
    union { 
        Uns32 value;
        struct {
            Uns32 EPRNE : 6;
            Uns32 __pad6 : 10;
            Uns32 EPTNE : 6;
        } bits;
    } ENDPTNAKEN;
    union { 
        Uns32 value;
        struct {
            Uns32 CCS : 1;
            Uns32 CSC : 1;
            Uns32 PE : 1;
            Uns32 PEC : 1;
            Uns32 OCA : 1;
            Uns32 OCC : 1;
            Uns32 FPR : 1;
            Uns32 SUSP : 1;
            Uns32 PR : 1;
            Uns32 HSP : 1;
            Uns32 LS : 2;
            Uns32 PP : 1;
            Uns32 PO : 1;
            Uns32 PIC : 2;
            Uns32 PTC : 4;
            Uns32 WKCN : 1;
            Uns32 WKDC : 1;
            Uns32 WKOC : 1;
            Uns32 PHCD : 1;
            Uns32 PFSC : 1;
            Uns32 PTS1 : 1;
            Uns32 PSPD : 2;
            Uns32 PTW : 1;
            Uns32 STS : 1;
            Uns32 PTS2 : 2;
        } bits;
    } PORTSC1;
    union { 
        Uns32 value;
        struct {
            Uns32 VD : 1;
            Uns32 __pad1 : 2;
            Uns32 OT : 1;
            Uns32 __pad4 : 1;
            Uns32 IDPU : 1;
            Uns32 __pad6 : 2;
            Uns32 ID : 1;
            Uns32 AVV : 1;
            Uns32 ASV : 1;
            Uns32 BSV : 1;
            Uns32 BSE : 1;
            Uns32 MST1 : 1;
            Uns32 DPS : 1;
            Uns32 __pad15 : 1;
            Uns32 IDIS : 1;
            Uns32 AVVIS : 1;
            Uns32 ASVIS : 1;
            Uns32 BSVIS : 1;
            Uns32 BSEIS : 1;
            Uns32 MSS1 : 1;
            Uns32 DPIS : 1;
            Uns32 __pad23 : 1;
            Uns32 IDIE : 1;
            Uns32 AVVIE : 1;
            Uns32 ASVIE : 1;
            Uns32 BSVIE : 1;
            Uns32 BSEIE : 1;
            Uns32 MSSE1 : 1;
            Uns32 DPIE : 1;
        } bits;
    } OTGSC;
    union { 
        Uns32 value;
        struct {
            Uns32 CM : 2;
            Uns32 ES : 1;
            Uns32 SLOM : 1;
            Uns32 SDIS : 1;
        } bits;
    } USBMODE;
    union { 
        Uns32 value;
        struct {
            Uns32 ENDPTSETUPSTAT : 16;
        } bits;
    } ENDPTSETUPSTAT;
    union { 
        Uns32 value;
        struct {
            Uns32 PERB : 6;
            Uns32 __pad6 : 10;
            Uns32 PETB : 6;
        } bits;
    } ENDPTPRIME;
    union { 
        Uns32 value;
        struct {
            Uns32 FERB : 6;
            Uns32 __pad6 : 10;
            Uns32 FETB : 6;
        } bits;
    } ENDPTFLUSH;
    union { 
        Uns32 value;
        struct {
            Uns32 ERBR : 6;
            Uns32 __pad6 : 10;
            Uns32 ETBR : 6;
        } bits;
    } ENDPTSTAT;
    union { 
        Uns32 value;
        struct {
            Uns32 ERCE : 6;
            Uns32 __pad6 : 10;
            Uns32 ETCE : 6;
        } bits;
    } ENDPTCOMPLETE;
    union { 
        Uns32 value;
        struct {
            Uns32 RXS : 1;
            Uns32 __pad1 : 1;
            Uns32 RXT : 2;
            Uns32 __pad4 : 3;
            Uns32 RXE : 1;
            Uns32 __pad8 : 8;
            Uns32 TXS : 1;
            Uns32 __pad17 : 1;
            Uns32 TXT : 2;
            Uns32 __pad20 : 3;
            Uns32 TXE : 1;
        } bits;
    } ENDPTCTRL0;
    union { 
        Uns32 value;
        struct {
            Uns32 RXS : 1;
            Uns32 RXD : 1;
            Uns32 RXT : 2;
            Uns32 __pad4 : 1;
            Uns32 RXI : 1;
            Uns32 RXR : 1;
            Uns32 RXE : 1;
            Uns32 __pad8 : 8;
            Uns32 TXS : 1;
            Uns32 TXD : 1;
            Uns32 TXT : 2;
            Uns32 __pad20 : 1;
            Uns32 TXI : 1;
            Uns32 TXR : 1;
            Uns32 TXE : 1;
        } bits;
    } ENDPTCTRL1;
    union { 
        Uns32 value;
        struct {
            Uns32 RXS : 1;
            Uns32 RXD : 1;
            Uns32 RXT : 2;
            Uns32 __pad4 : 1;
            Uns32 RXI : 1;
            Uns32 RXR : 1;
            Uns32 RXE : 1;
            Uns32 __pad8 : 8;
            Uns32 TXS : 1;
            Uns32 TXD : 1;
            Uns32 TXT : 2;
            Uns32 __pad20 : 1;
            Uns32 TXI : 1;
            Uns32 TXR : 1;
            Uns32 TXE : 1;
        } bits;
    } ENDPTCTRL2;
    union { 
        Uns32 value;
        struct {
            Uns32 RXS : 1;
            Uns32 RXD : 1;
            Uns32 RXT : 2;
            Uns32 __pad4 : 1;
            Uns32 RXI : 1;
            Uns32 RXR : 1;
            Uns32 RXE : 1;
            Uns32 __pad8 : 8;
            Uns32 TXS : 1;
            Uns32 TXD : 1;
            Uns32 TXT : 2;
            Uns32 __pad20 : 1;
            Uns32 TXI : 1;
            Uns32 TXR : 1;
            Uns32 TXE : 1;
        } bits;
    } ENDPTCTRL3;
    union { 
        Uns32 value;
        struct {
            Uns32 RXS : 1;
            Uns32 RXD : 1;
            Uns32 RXT : 2;
            Uns32 __pad4 : 1;
            Uns32 RXI : 1;
            Uns32 RXR : 1;
            Uns32 RXE : 1;
            Uns32 __pad8 : 8;
            Uns32 TXS : 1;
            Uns32 TXD : 1;
            Uns32 TXT : 2;
            Uns32 __pad20 : 1;
            Uns32 TXI : 1;
            Uns32 TXR : 1;
            Uns32 TXE : 1;
        } bits;
    } ENDPTCTRL4;
    union { 
        Uns32 value;
        struct {
            Uns32 RXS : 1;
            Uns32 RXD : 1;
            Uns32 RXT : 2;
            Uns32 __pad4 : 1;
            Uns32 RXI : 1;
            Uns32 RXR : 1;
            Uns32 RXE : 1;
            Uns32 __pad8 : 8;
            Uns32 TXS : 1;
            Uns32 TXD : 1;
            Uns32 TXT : 2;
            Uns32 __pad20 : 1;
            Uns32 TXI : 1;
            Uns32 TXR : 1;
            Uns32 TXE : 1;
        } bits;
    } ENDPTCTRL5;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 7;
            Uns32 OVER_CUR_DIS : 1;
            Uns32 OVER_CUR_POL : 1;
            Uns32 PM : 1;
            Uns32 WIE : 1;
            Uns32 RESET : 1;
            Uns32 SUSPENDM : 1;
            Uns32 ETMI_ON_CLOSK : 1;
            Uns32 WKUP_SW_EN : 1;
            Uns32 WKUP_SW : 1;
            Uns32 __pad16 : 1;
            Uns32 WKUP_VBUS_EN : 1;
            Uns32 __pad18 : 6;
            Uns32 VBUS_CH_STAT : 1;
            Uns32 VBUS_CH_INT_MASK : 1;
            Uns32 __pad26 : 5;
            Uns32 WIR : 1;
        } bits;
    } CTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 CHRGDET_INT_FLG : 1;
            Uns32 CHRGDET_INT_EN : 1;
            Uns32 CHRGDET : 1;
            Uns32 __pad3 : 28;
            Uns32 UTMI_CLK_VLD : 1;
        } bits;
    } PHY;
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

PPM_REG_WRITE_CB(PHYWrite1c);
PPM_REG_READ_CB(readCapVersion);
PPM_REG_READ_CB(readDCIVersion);
PPM_REG_READ_CB(readShare154h);
PPM_REG_READ_CB(readShare158h);
PPM_REG_WRITE_CB(writeShare154h);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_ID_WIDTH              32
#define BPORT1_AB_HWGENERAL_WIDTH       32
#define BPORT1_AB_HWHOST_WIDTH          32
#define BPORT1_AB_HWDEVICE_WIDTH        32
#define BPORT1_AB_HWTXBUF_WIDTH         32
#define BPORT1_AB_HWRXBUF_WIDTH         32
#define BPORT1_AB_GPTIMER0LD_WRMASK     0xffffff
#define BPORT1_AB_GPTIMER0LD_WRNMASK    (0xff000000)
#define BPORT1_AB_GPTIMER0LD_WIDTH      32
#define BPORT1_AB_GPTIMER0CTRL_WRMASK   0xc1ffffff
#define BPORT1_AB_GPTIMER0CTRL_WRNMASK  (0x3e000000)
#define BPORT1_AB_GPTIMER0CTRL_WIDTH    32
#define BPORT1_AB_GPTIMER1LD_WRMASK     0xffffff
#define BPORT1_AB_GPTIMER1LD_WRNMASK    (0xff000000)
#define BPORT1_AB_GPTIMER1LD_WIDTH      32
#define BPORT1_AB_GPTIMER1CTRL_WRMASK   0xc1ffffff
#define BPORT1_AB_GPTIMER1CTRL_WRNMASK  (0x3e000000)
#define BPORT1_AB_GPTIMER1CTRL_WIDTH    32
#define BPORT1_AB_SBUSCFG_WRMASK        0x7
#define BPORT1_AB_SBUSCFG_WRNMASK       (0xfffffff8)
#define BPORT1_AB_SBUSCFG_WIDTH         32
#define BPORT1_AB_CAPVERSION_WIDTH      32
#define BPORT1_AB_HCSPARAMS_WIDTH       32
#define BPORT1_AB_HCCPARAMS_WIDTH       32
#define BPORT1_AB_DCIVERSION_WIDTH      32
#define BPORT1_AB_DCCPARAMS_WIDTH       32
#define BPORT1_AB_USBCMD_WRMASK         0xffeb7f
#define BPORT1_AB_USBCMD_WRNMASK        (0xff001480)
#define BPORT1_AB_USBCMD_WIDTH          32
#define BPORT1_AB_USBSTS_WRMASK         0x30cf5ff
#define BPORT1_AB_USBSTS_WRNMASK        (0xfcf30a00)
#define BPORT1_AB_USBSTS_WIDTH          32
#define BPORT1_AB_USBINTR_WRMASK        0x30c05ff
#define BPORT1_AB_USBINTR_WRNMASK       (0xfcf3fa00)
#define BPORT1_AB_USBINTR_WIDTH         32
#define BPORT1_AB_FRINDEX_WRMASK        0x3fff
#define BPORT1_AB_FRINDEX_WRNMASK       (0xffffc000)
#define BPORT1_AB_FRINDEX_WIDTH         32
#define BPORT1_AB_DEVICEADDR_WRMASK     0xffffffff
#define BPORT1_AB_DEVICEADDR_WRNMASK    (0x0)
#define BPORT1_AB_DEVICEADDR_WIDTH      32
#define BPORT1_AB_ASYNCLISTADDR_WRMASK  0xffffffff
#define BPORT1_AB_ASYNCLISTADDR_WRNMASK  (0x0)
#define BPORT1_AB_ASYNCLISTADDR_WIDTH   32
#define BPORT1_AB_BURSTSIZE_WRMASK      0x1fff
#define BPORT1_AB_BURSTSIZE_WRNMASK     (0xffffe000)
#define BPORT1_AB_BURSTSIZE_WIDTH       32
#define BPORT1_AB_TXFILLTUNING_WRMASK   0x3f1fff
#define BPORT1_AB_TXFILLTUNING_WRNMASK  (0xffc0e000)
#define BPORT1_AB_TXFILLTUNING_WIDTH    32
#define BPORT1_AB_ENDPTNAK_WRMASK       0x3f003f
#define BPORT1_AB_ENDPTNAK_WRNMASK      (0xffc0ffc0)
#define BPORT1_AB_ENDPTNAK_WIDTH        32
#define BPORT1_AB_ENDPTNAKEN_WRMASK     0x3f003f
#define BPORT1_AB_ENDPTNAKEN_WRNMASK    (0xffc0ffc0)
#define BPORT1_AB_ENDPTNAKEN_WIDTH      32
#define BPORT1_AB_PORTSC1_WRMASK        0xffffffff
#define BPORT1_AB_PORTSC1_WRNMASK       (0x0)
#define BPORT1_AB_PORTSC1_WIDTH         32
#define BPORT1_AB_OTGSC_WRMASK          0x7f7f7f29
#define BPORT1_AB_OTGSC_WRNMASK         (0x808080d6)
#define BPORT1_AB_OTGSC_WIDTH           32
#define BPORT1_AB_USBMODE_WRMASK        0x1f
#define BPORT1_AB_USBMODE_WRNMASK       (0xffffffe0)
#define BPORT1_AB_USBMODE_WIDTH         32
#define BPORT1_AB_ENDPTSETUPSTAT_WRMASK  0xffff
#define BPORT1_AB_ENDPTSETUPSTAT_WRNMASK  (0xffff0000)
#define BPORT1_AB_ENDPTSETUPSTAT_WIDTH  32
#define BPORT1_AB_ENDPTPRIME_WRMASK     0x3f003f
#define BPORT1_AB_ENDPTPRIME_WRNMASK    (0xffc0ffc0)
#define BPORT1_AB_ENDPTPRIME_WIDTH      32
#define BPORT1_AB_ENDPTFLUSH_WRMASK     0x3f003f
#define BPORT1_AB_ENDPTFLUSH_WRNMASK    (0xffc0ffc0)
#define BPORT1_AB_ENDPTFLUSH_WIDTH      32
#define BPORT1_AB_ENDPTSTAT_WIDTH       32
#define BPORT1_AB_ENDPTCOMPLETE_WRMASK  0x3f003f
#define BPORT1_AB_ENDPTCOMPLETE_WRNMASK  (0xffc0ffc0)
#define BPORT1_AB_ENDPTCOMPLETE_WIDTH   32
#define BPORT1_AB_ENDPTCTRL0_WRMASK     0x8d008d
#define BPORT1_AB_ENDPTCTRL0_WRNMASK    (0xff72ff72)
#define BPORT1_AB_ENDPTCTRL0_WIDTH      32
#define BPORT1_AB_ENDPTCTRL1_WRMASK     0xef00ef
#define BPORT1_AB_ENDPTCTRL1_WRNMASK    (0xff10ff10)
#define BPORT1_AB_ENDPTCTRL1_WIDTH      32
#define BPORT1_AB_ENDPTCTRL2_WRMASK     0xef00ef
#define BPORT1_AB_ENDPTCTRL2_WRNMASK    (0xff10ff10)
#define BPORT1_AB_ENDPTCTRL2_WIDTH      32
#define BPORT1_AB_ENDPTCTRL3_WRMASK     0xef00ef
#define BPORT1_AB_ENDPTCTRL3_WRNMASK    (0xff10ff10)
#define BPORT1_AB_ENDPTCTRL3_WIDTH      32
#define BPORT1_AB_ENDPTCTRL4_WRMASK     0xef00ef
#define BPORT1_AB_ENDPTCTRL4_WRNMASK    (0xff10ff10)
#define BPORT1_AB_ENDPTCTRL4_WIDTH      32
#define BPORT1_AB_ENDPTCTRL5_WRMASK     0xef00ef
#define BPORT1_AB_ENDPTCTRL5_WRNMASK    (0xff10ff10)
#define BPORT1_AB_ENDPTCTRL5_WIDTH      32
#define BPORT1_AB_CTRL_WRMASK           0x302ff80
#define BPORT1_AB_CTRL_WRNMASK          (0xfcfd007f)
#define BPORT1_AB_CTRL_WIDTH            32
#define BPORT1_AB_PHY_WRMASK            0x80000007
#define BPORT1_AB_PHY_WRNMASK           (0x7ffffff8)
#define BPORT1_AB_PHY_WIDTH             32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

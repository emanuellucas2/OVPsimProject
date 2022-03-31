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
            Uns32 TAG : 5;
            Uns32 REVISION : 4;
            Uns32 VERSION : 4;
            Uns32 VERSIONID : 3;
        } bits;
    } ID;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 6;
            Uns32 PHYM : 3;
            Uns32 SM : 2;
        } bits;
    } HWGENERAL;
    union { 
        Uns32 value;
        struct {
            Uns32 HC : 1;
            Uns32 NPORT : 3;
            Uns32 __pad4 : 12;
            Uns32 TTASY : 8;
            Uns32 TTPER : 8;
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
            Uns32 TXADD : 8;
            Uns32 TXCHANADD : 8;
            Uns32 __pad24 : 7;
            Uns32 TXLC : 1;
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
            Uns32 MODE : 1;
            Uns32 __pad25 : 5;
            Uns32 RST : 1;
            Uns32 RUN : 1;
        } bits;
    } GPTIMER0CTL;
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
            Uns32 MODE : 1;
            Uns32 __pad25 : 5;
            Uns32 RST : 1;
            Uns32 RUN : 1;
        } bits;
    } GPTIMER1CTL;
    union { 
        Uns32 value;
        struct {
            Uns32 BURSTMODE : 3;
        } bits;
    } SBUSCFG;
    union { 
        Uns32 value;
        struct {
            Uns32 CAPLENGTH : 8;
            Uns32 __pad8 : 8;
            Uns32 HCIVERSION : 16;
        } bits;
    } HCIVERSION;
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
        struct {
            Uns32 DCIVERSION : 16;
        } bits;
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
            Uns32 FS : 2;
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
        struct {
            Uns32 __pad0 : 24;
            Uns32 USBADRA : 1;
            Uns32 USBADR : 7;
        } bits;
    } DEVICEADDR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 5;
            Uns32 ASYBASE : 27;
        } bits;
    } ASYNCLISTADDR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 24;
            Uns32 TTHA : 7;
        } bits;
    } TTCTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 RXPBURST : 8;
            Uns32 TXPBURST : 8;
        } bits;
    } BURSTSIZE;
    union { 
        Uns32 value;
        struct {
            Uns32 TXSCHOH : 7;
            Uns32 __pad7 : 1;
            Uns32 TXSCHHEALTH : 5;
            Uns32 __pad13 : 3;
            Uns32 TXFIFOTHRES : 6;
        } bits;
    } TXFILLTUNING;
    union { 
        Uns32 value;
        struct {
            Uns32 ULPI_DATWR : 8;
            Uns32 ULPI_DATRD : 8;
            Uns32 ULPI_ADDR : 8;
            Uns32 ULPI_PORT : 3;
            Uns32 ULPI_SS : 1;
            Uns32 __pad28 : 1;
            Uns32 ULPI_RW : 1;
            Uns32 ULPI_RUN : 1;
            Uns32 ULPI_WU : 1;
        } bits;
    } ULPI_VIEWPORT;
    union { 
        Uns32 value;
        struct {
            Uns32 EPRNE : 4;
            Uns32 __pad4 : 12;
            Uns32 EPTNE : 4;
        } bits;
    } ENDPTNAK;
    union { 
        Uns32 value;
        struct {
            Uns32 EPRNE : 4;
            Uns32 __pad4 : 12;
            Uns32 EPTNE : 4;
        } bits;
    } ENDPTNAKEN;
    union { 
        Uns32 value;
    } CONFIGFLAG;
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
            Uns32 WKDS : 1;
            Uns32 WKOC : 1;
            Uns32 PHCD : 1;
            Uns32 PFSC : 1;
            Uns32 __pad25 : 1;
            Uns32 PSPD : 2;
            Uns32 __pad28 : 2;
            Uns32 PTS : 2;
        } bits;
    } PORTSC1;
    union { 
        Uns32 value;
        struct {
            Uns32 VD : 1;
            Uns32 VC : 1;
            Uns32 HAAR : 1;
            Uns32 OT : 1;
            Uns32 DP : 1;
            Uns32 IDPU : 1;
            Uns32 __pad6 : 1;
            Uns32 HABA : 1;
            Uns32 ID : 1;
            Uns32 AVV : 1;
            Uns32 ASV : 1;
            Uns32 BSV : 1;
            Uns32 BSE : 1;
            Uns32 MST : 1;
            Uns32 DPS : 1;
            Uns32 __pad15 : 1;
            Uns32 IDIS : 1;
            Uns32 AVVIS : 1;
            Uns32 ASVIS : 1;
            Uns32 BSVIS : 1;
            Uns32 BSEIS : 1;
            Uns32 MSS : 1;
            Uns32 DPIS : 1;
            Uns32 __pad23 : 1;
            Uns32 IDIE : 1;
            Uns32 AVVIE : 1;
            Uns32 ASVIE : 1;
            Uns32 BSVIE : 1;
            Uns32 BSEIE : 1;
            Uns32 MSE : 1;
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
            Uns32 __pad5 : 7;
            Uns32 TXHSD : 3;
        } bits;
    } USBMODE;
    union { 
        Uns32 value;
        struct {
            Uns32 EPSETUPSTAT : 4;
        } bits;
    } EPSETUPSR;
    union { 
        Uns32 value;
        struct {
            Uns32 PERB : 4;
            Uns32 __pad4 : 12;
            Uns32 PETB : 4;
        } bits;
    } EPPRIME;
    union { 
        Uns32 value;
        struct {
            Uns32 FERB : 4;
            Uns32 __pad4 : 12;
            Uns32 FETB : 4;
        } bits;
    } EPFLUSH;
    union { 
        Uns32 value;
        struct {
            Uns32 ERBR : 4;
            Uns32 __pad4 : 12;
            Uns32 ETBR : 4;
        } bits;
    } EPSR;
    union { 
        Uns32 value;
        struct {
            Uns32 ERCE : 4;
            Uns32 __pad4 : 12;
            Uns32 ETCE : 4;
        } bits;
    } EPCOMPLETE;
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
    } EPCR0;
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
    } EPCR1;
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
    } EPCR2;
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
    } EPCR3;
    union { 
        Uns32 value;
        struct {
            Uns32 WU_IE : 1;
            Uns32 WU_ULPI_EN : 1;
            Uns32 __pad2 : 3;
            Uns32 WU_INT_CLR : 1;
        } bits;
    } USBGENCTRL;
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

#define BPORT1_AB_ID_WIDTH              32
#define BPORT1_AB_HWGENERAL_WIDTH       32
#define BPORT1_AB_HWHOST_WIDTH          32
#define BPORT1_AB_HWDEVICE_WIDTH        32
#define BPORT1_AB_HWTXBUF_WIDTH         32
#define BPORT1_AB_HWRXBUF_WIDTH         32
#define BPORT1_AB_GPTIMER0LD_WRMASK     0xffffff
#define BPORT1_AB_GPTIMER0LD_WRNMASK    (0xff000000)
#define BPORT1_AB_GPTIMER0LD_WIDTH      32
#define BPORT1_AB_GPTIMER0CTL_WRMASK    0xc1000000
#define BPORT1_AB_GPTIMER0CTL_WRNMASK   (0x3effffff)
#define BPORT1_AB_GPTIMER0CTL_WIDTH     32
#define BPORT1_AB_GPTIMER1LD_WRMASK     0xffffff
#define BPORT1_AB_GPTIMER1LD_WRNMASK    (0xff000000)
#define BPORT1_AB_GPTIMER1LD_WIDTH      32
#define BPORT1_AB_GPTIMER1CTL_WRMASK    0xc1000000
#define BPORT1_AB_GPTIMER1CTL_WRNMASK   (0x3effffff)
#define BPORT1_AB_GPTIMER1CTL_WIDTH     32
#define BPORT1_AB_SBUSCFG_WRMASK        0x7
#define BPORT1_AB_SBUSCFG_WRNMASK       (0xfffffff8)
#define BPORT1_AB_SBUSCFG_WIDTH         32
#define BPORT1_AB_HCIVERSION_WIDTH      32
#define BPORT1_AB_HCSPARAMS_WIDTH       32
#define BPORT1_AB_HCCPARAMS_WIDTH       32
#define BPORT1_AB_DCIVERSION_WIDTH      32
#define BPORT1_AB_DCCPARAMS_WIDTH       32
#define BPORT1_AB_USBCMD_WRMASK         0xffeb7f
#define BPORT1_AB_USBCMD_WRNMASK        (0xff001480)
#define BPORT1_AB_USBCMD_WIDTH          32
#define BPORT1_AB_USBSTS_WRMASK         0x30a01ff
#define BPORT1_AB_USBSTS_WRNMASK        (0xfcf5fe00)
#define BPORT1_AB_USBSTS_WIDTH          32
#define BPORT1_AB_USBINTR_WRMASK        0x30d05ff
#define BPORT1_AB_USBINTR_WRNMASK       (0xfcf2fa00)
#define BPORT1_AB_USBINTR_WIDTH         32
#define BPORT1_AB_FRINDEX_WRMASK        0x3fff
#define BPORT1_AB_FRINDEX_WRNMASK       (0xffffc000)
#define BPORT1_AB_FRINDEX_WIDTH         32
#define BPORT1_AB_DEVICEADDR_WRMASK     0xfffff000
#define BPORT1_AB_DEVICEADDR_WRNMASK    (0xfff)
#define BPORT1_AB_DEVICEADDR_WIDTH      32
#define BPORT1_AB_ASYNCLISTADDR_WRMASK  0xffffffe0
#define BPORT1_AB_ASYNCLISTADDR_WRNMASK  (0x1f)
#define BPORT1_AB_ASYNCLISTADDR_WIDTH   32
#define BPORT1_AB_TTCTRL_WIDTH          32
#define BPORT1_AB_BURSTSIZE_WRMASK      0xffff
#define BPORT1_AB_BURSTSIZE_WRNMASK     (0xffff0000)
#define BPORT1_AB_BURSTSIZE_WIDTH       32
#define BPORT1_AB_TXFILLTUNING_WRMASK   0x3f1f7f
#define BPORT1_AB_TXFILLTUNING_WRNMASK  (0xffc0e080)
#define BPORT1_AB_TXFILLTUNING_WIDTH    32
#define BPORT1_AB_ULPI_VIEWPORT_WRMASK  0xefff00ff
#define BPORT1_AB_ULPI_VIEWPORT_WRNMASK  (0x1000ff00)
#define BPORT1_AB_ULPI_VIEWPORT_WIDTH   32
#define BPORT1_AB_ENDPTNAK_WRMASK       0xf000f
#define BPORT1_AB_ENDPTNAK_WRNMASK      (0xfff0fff0)
#define BPORT1_AB_ENDPTNAK_WIDTH        32
#define BPORT1_AB_ENDPTNAKEN_WRMASK     0xf000f
#define BPORT1_AB_ENDPTNAKEN_WRNMASK    (0xfff0fff0)
#define BPORT1_AB_ENDPTNAKEN_WIDTH      32
#define BPORT1_AB_CONFIGFLAG_WIDTH      32
#define BPORT1_AB_PORTSC1_WRMASK        0xc1fff1ee
#define BPORT1_AB_PORTSC1_WRNMASK       (0x3e000e11)
#define BPORT1_AB_PORTSC1_WIDTH         32
#define BPORT1_AB_OTGSC_WRMASK          0x7f7f00bf
#define BPORT1_AB_OTGSC_WRNMASK         (0x8080ff40)
#define BPORT1_AB_OTGSC_WIDTH           32
#define BPORT1_AB_USBMODE_WRMASK        0x701f
#define BPORT1_AB_USBMODE_WRNMASK       (0xffff8fe0)
#define BPORT1_AB_USBMODE_WIDTH         32
#define BPORT1_AB_EPSETUPSR_WRMASK      0xf
#define BPORT1_AB_EPSETUPSR_WRNMASK     (0xfffffff0)
#define BPORT1_AB_EPSETUPSR_WIDTH       32
#define BPORT1_AB_EPPRIME_WRMASK        0xf000f
#define BPORT1_AB_EPPRIME_WRNMASK       (0xfff0fff0)
#define BPORT1_AB_EPPRIME_WIDTH         32
#define BPORT1_AB_EPFLUSH_WRMASK        0xf000f
#define BPORT1_AB_EPFLUSH_WRNMASK       (0xfff0fff0)
#define BPORT1_AB_EPFLUSH_WIDTH         32
#define BPORT1_AB_EPSR_WIDTH            32
#define BPORT1_AB_EPCOMPLETE_WRMASK     0xf000f
#define BPORT1_AB_EPCOMPLETE_WRNMASK    (0xfff0fff0)
#define BPORT1_AB_EPCOMPLETE_WIDTH      32
#define BPORT1_AB_EPCR0_WRMASK          0x10001
#define BPORT1_AB_EPCR0_WRNMASK         (0xfffefffe)
#define BPORT1_AB_EPCR0_WIDTH           32
#define BPORT1_AB_EPCR1_WRMASK          0xef00ef
#define BPORT1_AB_EPCR1_WRNMASK         (0xff10ff10)
#define BPORT1_AB_EPCR1_WIDTH           32
#define BPORT1_AB_EPCR2_WRMASK          0xef00ef
#define BPORT1_AB_EPCR2_WRNMASK         (0xff10ff10)
#define BPORT1_AB_EPCR2_WIDTH           32
#define BPORT1_AB_EPCR3_WRMASK          0xef00ef
#define BPORT1_AB_EPCR3_WRNMASK         (0xff10ff10)
#define BPORT1_AB_EPCR3_WIDTH           32
#define BPORT1_AB_USBGENCTRL_WRMASK     0x23
#define BPORT1_AB_USBGENCTRL_WRNMASK    (0xffffffdc)
#define BPORT1_AB_USBGENCTRL_WIDTH      32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

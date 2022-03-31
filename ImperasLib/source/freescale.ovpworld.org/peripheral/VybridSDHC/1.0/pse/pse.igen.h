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
            Uns32 __pad0 : 2;
            Uns32 DSADDR : 30;
        } bits;
    } DSADDR;
    union { 
        Uns32 value;
        struct {
            Uns32 BLKSIZE : 13;
            Uns32 __pad13 : 3;
            Uns32 BLKCNT : 16;
        } bits;
    } BLKATTR;
    union { 
        Uns32 value;
        struct {
            Uns32 CMDARG : 32;
        } bits;
    } CMDARG;
    union { 
        Uns32 value;
        struct {
            Uns32 DMAEN : 1;
            Uns32 BCEN : 1;
            Uns32 AC12EN : 1;
            Uns32 __pad3 : 1;
            Uns32 DTDSEL : 1;
            Uns32 MSBSEL : 1;
            Uns32 __pad6 : 10;
            Uns32 RSPTYP : 2;
            Uns32 __pad18 : 1;
            Uns32 CCCEN : 1;
            Uns32 CICEN : 1;
            Uns32 DPSEL : 1;
            Uns32 CMDTYP : 2;
            Uns32 CMDINX : 6;
        } bits;
    } XFERTYP;
    union { 
        Uns32 value;
        struct {
            Uns32 CMDRSP0 : 32;
        } bits;
    } CMDRSP0;
    union { 
        Uns32 value;
        struct {
            Uns32 CMDRSP1 : 32;
        } bits;
    } CMDRSP1;
    union { 
        Uns32 value;
        struct {
            Uns32 CMDRSP2 : 32;
        } bits;
    } CMDRSP2;
    union { 
        Uns32 value;
        struct {
            Uns32 CMDRSP3 : 32;
        } bits;
    } CMDRSP3;
    union { 
        Uns32 value;
        struct {
            Uns32 DATCONT : 32;
        } bits;
    } DATPORT;
    union { 
        Uns32 value;
        struct {
            Uns32 CIHB : 1;
            Uns32 CDIHB : 1;
            Uns32 DLA : 1;
            Uns32 SDSTB : 1;
            Uns32 IPGOFF : 1;
            Uns32 HCKOFF : 1;
            Uns32 PEROFF : 1;
            Uns32 SDOFF : 1;
            Uns32 WTA : 1;
            Uns32 RTA : 1;
            Uns32 BWEN : 1;
            Uns32 BREN : 1;
            Uns32 __pad12 : 4;
            Uns32 CINS : 1;
            Uns32 __pad17 : 1;
            Uns32 CDPL : 1;
            Uns32 WPSPL : 1;
            Uns32 __pad20 : 3;
            Uns32 CLSL : 1;
            Uns32 DLSL : 8;
        } bits;
    } PRSSTAT;
    union { 
        Uns32 value;
        struct {
            Uns32 LCTL : 1;
            Uns32 DTW : 2;
            Uns32 D3CD : 1;
            Uns32 EMODE : 2;
            Uns32 CDTL : 1;
            Uns32 CDSS : 1;
            Uns32 DMAS : 2;
            Uns32 __pad10 : 6;
            Uns32 SABGREQ : 1;
            Uns32 CREQ : 1;
            Uns32 RWCTL : 1;
            Uns32 IABG : 1;
            Uns32 __pad20 : 4;
            Uns32 WECINT : 1;
            Uns32 WECINS : 1;
            Uns32 WECRM : 1;
        } bits;
    } PROCTL;
    union { 
        Uns32 value;
        struct {
            Uns32 IPGEN : 1;
            Uns32 HCKEN : 1;
            Uns32 PEREN : 1;
            Uns32 SDCLKEN : 1;
            Uns32 DVS : 4;
            Uns32 SDCLKFS : 8;
            Uns32 DTOCV : 4;
            Uns32 __pad20 : 4;
            Uns32 RSTA : 1;
            Uns32 RSTC : 1;
            Uns32 RSTD : 1;
            Uns32 INITA : 1;
        } bits;
    } SYSCTL;
    union { 
        Uns32 value;
        struct {
            Uns32 CC : 1;
            Uns32 TC : 1;
            Uns32 BGE : 1;
            Uns32 DINT : 1;
            Uns32 BWR : 1;
            Uns32 BRR : 1;
            Uns32 CINS : 1;
            Uns32 CRM : 1;
            Uns32 CINT : 1;
            Uns32 __pad9 : 7;
            Uns32 CTOE : 1;
            Uns32 CCE : 1;
            Uns32 CEBE : 1;
            Uns32 CIE : 1;
            Uns32 DTOE : 1;
            Uns32 DCE : 1;
            Uns32 DEBE : 1;
            Uns32 __pad23 : 1;
            Uns32 AC12E : 1;
            Uns32 __pad25 : 3;
            Uns32 DMAE : 1;
        } bits;
    } IRQSTAT;
    union { 
        Uns32 value;
        struct {
            Uns32 CCSEN : 1;
            Uns32 TCSEN : 1;
            Uns32 BGESEN : 1;
            Uns32 DINTSEN : 1;
            Uns32 BWRSEN : 1;
            Uns32 BRRSEN : 1;
            Uns32 CINSEN : 1;
            Uns32 CRMSEN : 1;
            Uns32 CINTSEN : 1;
            Uns32 __pad9 : 7;
            Uns32 CTOESEN : 1;
            Uns32 CCESEN : 1;
            Uns32 CEBESEN : 1;
            Uns32 CIESEN : 1;
            Uns32 DTOESEN : 1;
            Uns32 DCESEN : 1;
            Uns32 DEBESEN : 1;
            Uns32 __pad23 : 1;
            Uns32 AC12ESEN : 1;
            Uns32 __pad25 : 3;
            Uns32 DMAESEN : 1;
        } bits;
    } IRQSTATEN;
    union { 
        Uns32 value;
        struct {
            Uns32 CCIEN : 1;
            Uns32 TCIEN : 1;
            Uns32 BGEIEN : 1;
            Uns32 DINTIEN : 1;
            Uns32 BWRIEN : 1;
            Uns32 BRRIEN : 1;
            Uns32 CINSIEN : 1;
            Uns32 CRMIEN : 1;
            Uns32 CINTIEN : 1;
            Uns32 __pad9 : 7;
            Uns32 CTOEIEN : 1;
            Uns32 CCEIEN : 1;
            Uns32 CEBEIEN : 1;
            Uns32 CIEIEN : 1;
            Uns32 DTOEIEN : 1;
            Uns32 DCEIEN : 1;
            Uns32 DEBEIEN : 1;
            Uns32 __pad23 : 1;
            Uns32 AC12EIEN : 1;
            Uns32 __pad25 : 3;
            Uns32 DMAEIEN : 1;
        } bits;
    } IRQSIGEN;
    union { 
        Uns32 value;
        struct {
            Uns32 AC12NE : 1;
            Uns32 AC12TOE : 1;
            Uns32 AC12EBE : 1;
            Uns32 AC12CE : 1;
            Uns32 AC12IE : 1;
            Uns32 __pad5 : 2;
            Uns32 CNIBAC12E : 1;
        } bits;
    } AC12ERR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 MBL : 3;
            Uns32 __pad19 : 1;
            Uns32 ADMAS : 1;
            Uns32 HSS : 1;
            Uns32 DMAS : 1;
            Uns32 SRS : 1;
            Uns32 VS33 : 1;
        } bits;
    } HTCAPBLT;
    union { 
        Uns32 value;
        struct {
            Uns32 RDWML : 8;
            Uns32 RDBRSTLEN : 5;
            Uns32 __pad13 : 3;
            Uns32 WRWML : 8;
            Uns32 WRBRSTLEN : 5;
        } bits;
    } WML;
    union { 
        Uns32 value;
        struct {
            Uns32 AC12NE : 1;
            Uns32 AC12TOE : 1;
            Uns32 AC12CE : 1;
            Uns32 AC12EBE : 1;
            Uns32 AC12IE : 1;
            Uns32 __pad5 : 2;
            Uns32 CNIBAC12E : 1;
            Uns32 __pad8 : 8;
            Uns32 CTOE : 1;
            Uns32 CCE : 1;
            Uns32 CEBE : 1;
            Uns32 CIE : 1;
            Uns32 DTOE : 1;
            Uns32 DCE : 1;
            Uns32 DEBE : 1;
            Uns32 __pad23 : 1;
            Uns32 AC12E : 1;
            Uns32 __pad25 : 3;
            Uns32 DMAE : 1;
            Uns32 __pad29 : 2;
            Uns32 CINT : 1;
        } bits;
    } FEVT;
    union { 
        Uns32 value;
        struct {
            Uns32 ADMAES : 2;
            Uns32 ADMALME : 1;
            Uns32 ADMADCE : 1;
        } bits;
    } ADMAES;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 2;
            Uns32 ADSADDR : 30;
        } bits;
    } ADSADDR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 1;
            Uns32 EXBLKNU : 1;
            Uns32 __pad2 : 14;
            Uns32 INTSTVAL : 8;
        } bits;
    } VENDOR;
    union { 
        Uns32 value;
        struct {
            Uns32 DTOCVACK : 4;
            Uns32 BOOTACK : 1;
            Uns32 BOOTMODE : 1;
            Uns32 BOOTEN : 1;
            Uns32 AUTOSABGEN : 1;
            Uns32 __pad8 : 8;
            Uns32 BOOTBLKCNT : 16;
        } bits;
    } MMCBOOT;
    union { 
        Uns32 value;
        struct {
            Uns32 SVN : 8;
            Uns32 VVN : 8;
        } bits;
    } HOSTVER;
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

#define BPORT1_AB_DSADDR_WRMASK         0xfffffffc
#define BPORT1_AB_DSADDR_WRNMASK        (0x3)
#define BPORT1_AB_DSADDR_WIDTH          32
#define BPORT1_AB_BLKATTR_WRMASK        0xffff1fff
#define BPORT1_AB_BLKATTR_WRNMASK       (0xe000)
#define BPORT1_AB_BLKATTR_WIDTH         32
#define BPORT1_AB_CMDARG_WRMASK         0xffffffff
#define BPORT1_AB_CMDARG_WRNMASK        (0x0)
#define BPORT1_AB_CMDARG_WIDTH          32
#define BPORT1_AB_XFERTYP_WRMASK        0x3ffb0037
#define BPORT1_AB_XFERTYP_WRNMASK       (0xc004ffc8)
#define BPORT1_AB_XFERTYP_WIDTH         32
#define BPORT1_AB_CMDRSP0_WIDTH         32
#define BPORT1_AB_CMDRSP1_WIDTH         32
#define BPORT1_AB_CMDRSP2_WIDTH         32
#define BPORT1_AB_CMDRSP3_WIDTH         32
#define BPORT1_AB_DATPORT_WRMASK        0xffffffff
#define BPORT1_AB_DATPORT_WRNMASK       (0x0)
#define BPORT1_AB_DATPORT_WIDTH         32
#define BPORT1_AB_PRSSTAT_WIDTH         32
#define BPORT1_AB_PROCTL_WRMASK         0x70f03ff
#define BPORT1_AB_PROCTL_WRNMASK        (0xf8f0fc00)
#define BPORT1_AB_PROCTL_WIDTH          32
#define BPORT1_AB_SYSCTL_WRMASK         0xf0fffff
#define BPORT1_AB_SYSCTL_WRNMASK        (0xf0f00000)
#define BPORT1_AB_SYSCTL_WIDTH          32
#define BPORT1_AB_IRQSTAT_WRMASK        0x113f01ff
#define BPORT1_AB_IRQSTAT_WRNMASK       (0xeec0fe00)
#define BPORT1_AB_IRQSTAT_WIDTH         32
#define BPORT1_AB_IRQSTATEN_WRMASK      0x113f01ff
#define BPORT1_AB_IRQSTATEN_WRNMASK     (0xeec0fe00)
#define BPORT1_AB_IRQSTATEN_WIDTH       32
#define BPORT1_AB_IRQSIGEN_WRMASK       0x113f01ff
#define BPORT1_AB_IRQSIGEN_WRNMASK      (0xeec0fe00)
#define BPORT1_AB_IRQSIGEN_WIDTH        32
#define BPORT1_AB_AC12ERR_WIDTH         32
#define BPORT1_AB_HTCAPBLT_WIDTH        32
#define BPORT1_AB_WML_WRMASK            0x1fff1fff
#define BPORT1_AB_WML_WRNMASK           (0xe000e000)
#define BPORT1_AB_WML_WIDTH             32
#define BPORT1_AB_FEVT_WRMASK           0x917f009f
#define BPORT1_AB_FEVT_WRNMASK          (0x6e80ff60)
#define BPORT1_AB_FEVT_WIDTH            32
#define BPORT1_AB_ADMAES_WIDTH          32
#define BPORT1_AB_ADSADDR_WRMASK        0xfffffffc
#define BPORT1_AB_ADSADDR_WRNMASK       (0x3)
#define BPORT1_AB_ADSADDR_WIDTH         32
#define BPORT1_AB_VENDOR_WRMASK         0x3
#define BPORT1_AB_VENDOR_WRNMASK        (0xfffffffc)
#define BPORT1_AB_VENDOR_WIDTH          32
#define BPORT1_AB_MMCBOOT_WRMASK        0xff
#define BPORT1_AB_MMCBOOT_WRNMASK       (0xffffff00)
#define BPORT1_AB_MMCBOOT_WIDTH         32
#define BPORT1_AB_HOSTVER_WIDTH         32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

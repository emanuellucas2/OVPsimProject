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
            Uns32 BLKSIZE : 13;
            Uns32 __pad13 : 3;
            Uns32 BLKCNT : 16;
        } bits;
    } uSDHC_DS_ADDR;
    union { 
        Uns32 value;
    } uSDHC_BLK_ATT;
    union { 
        Uns32 value;
    } uSDHC_CMD_ARG;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 RSPTYP : 2;
            Uns32 __pad18 : 1;
            Uns32 CCCEN : 1;
            Uns32 CICEN : 1;
            Uns32 DPSEL : 1;
            Uns32 CMDTYP : 2;
            Uns32 CMDINX : 6;
        } bits;
    } uSDHC_CMD_XFR_TYP;
    union { 
        Uns32 value;
    } uSDHC_CMD_RSP0;
    union { 
        Uns32 value;
    } uSDHC_CMD_RSP1;
    union { 
        Uns32 value;
    } uSDHC_CMD_RSP2;
    union { 
        Uns32 value;
    } uSDHC_CMD_RSP3;
    union { 
        Uns32 value;
    } uSDHC_DATA_BUFF_ACC_PORT;
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
            Uns32 RTR : 1;
            Uns32 __pad13 : 3;
            Uns32 CINST : 1;
            Uns32 __pad17 : 1;
            Uns32 CDPL : 1;
            Uns32 WPSPL : 1;
            Uns32 __pad20 : 3;
            Uns32 CLSL : 1;
            Uns32 DLSL : 8;
        } bits;
    } uSDHC_PRES_STATE;
    union { 
        Uns32 value;
        struct {
            Uns32 LCTL : 1;
            Uns32 DTW : 2;
            Uns32 D3CD : 1;
            Uns32 EMODE : 2;
            Uns32 CDTL : 1;
            Uns32 CDSS : 1;
            Uns32 DMASEL : 2;
            Uns32 __pad10 : 6;
            Uns32 SABGREQ : 1;
            Uns32 CREQ : 1;
            Uns32 RWCTL : 1;
            Uns32 IABG : 1;
            Uns32 RD_DONE_NO_8CLK : 1;
            Uns32 __pad21 : 3;
            Uns32 WECINT : 1;
            Uns32 WECINS : 1;
            Uns32 WECRM : 1;
            Uns32 BURST_LEN_EN : 3;
            Uns32 NON_EXACT_BLK_RD : 1;
        } bits;
    } uSDHC_PROT_CTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 4;
            Uns32 DVS : 3;
            Uns32 __pad7 : 1;
            Uns32 SDCLKFS : 7;
            Uns32 __pad15 : 1;
            Uns32 DTOCV : 4;
            Uns32 __pad20 : 3;
            Uns32 IPP_RST_N : 1;
            Uns32 RSTA : 1;
            Uns32 RSTC : 1;
            Uns32 RSTD : 1;
            Uns32 INITA : 1;
        } bits;
    } uSDHC_SYS_CTRL;
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
            Uns32 __pad9 : 3;
            Uns32 RTE : 1;
            Uns32 __pad13 : 1;
            Uns32 TP : 1;
            Uns32 __pad15 : 1;
            Uns32 CTOE : 1;
            Uns32 CCE : 1;
            Uns32 CEBE : 1;
            Uns32 CIE : 1;
            Uns32 DTOE : 1;
            Uns32 DCE : 1;
            Uns32 DEBE : 1;
            Uns32 __pad23 : 1;
            Uns32 AC12E : 1;
            Uns32 __pad25 : 1;
            Uns32 TNE : 1;
            Uns32 __pad27 : 1;
            Uns32 DMAE : 1;
        } bits;
    } uSDHC_INT_STATUS;
    union { 
        Uns32 value;
        struct {
            Uns32 CCSEN : 1;
            Uns32 TCSEN : 1;
            Uns32 BGESEN : 1;
            Uns32 DINTSEN : 1;
            Uns32 BWRSEN : 1;
            Uns32 BRRSEN : 1;
            Uns32 CINSSEN : 1;
            Uns32 CRMSEN : 1;
            Uns32 CINTSEN : 1;
            Uns32 __pad9 : 3;
            Uns32 RTESEN : 1;
            Uns32 __pad13 : 1;
            Uns32 TPSEN : 1;
            Uns32 __pad15 : 1;
            Uns32 CTOESEN : 1;
            Uns32 CCESEN : 1;
            Uns32 CEBESEN : 1;
            Uns32 CIESEN : 1;
            Uns32 DTOESEN : 1;
            Uns32 DCESEN : 1;
            Uns32 DEBESEN : 1;
            Uns32 __pad23 : 1;
            Uns32 AC12ESEN : 1;
            Uns32 __pad25 : 1;
            Uns32 TNESEN : 1;
            Uns32 __pad27 : 1;
            Uns32 DMAESEN : 1;
        } bits;
    } uSDHC_INT_STATUS_EN;
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
            Uns32 __pad9 : 3;
            Uns32 RTEIEN : 1;
            Uns32 __pad13 : 1;
            Uns32 TPIEN : 1;
            Uns32 __pad15 : 1;
            Uns32 CTOEIEN : 1;
            Uns32 CCEIEN : 1;
            Uns32 CEBEIEN : 1;
            Uns32 CIEIEN : 1;
            Uns32 DTOEIEN : 1;
            Uns32 DCEIEN : 1;
            Uns32 DEBEIEN : 1;
            Uns32 __pad23 : 1;
            Uns32 AC12EIEN : 1;
            Uns32 __pad25 : 1;
            Uns32 TNEIEN : 1;
            Uns32 __pad27 : 1;
            Uns32 DMAEIEN : 1;
        } bits;
    } uSDHC_INT_SIGNAL_EN;
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
    } uSDHC_AUTOCMD12_ERR_STATUS;
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
            Uns32 VS30 : 1;
            Uns32 VS18 : 1;
        } bits;
    } uSDHC_HOST_CTRL_CAP;
    union { 
        Uns32 value;
        struct {
            Uns32 RD_WML : 8;
            Uns32 RD_BRST_LEN : 5;
            Uns32 __pad13 : 3;
            Uns32 WR_WML : 8;
            Uns32 WR_BRST_LEN : 5;
        } bits;
    } uSDHC_WTMK_LVL;
    union { 
        Uns32 value;
        struct {
            Uns32 DMAEN : 1;
            Uns32 BCEN : 1;
            Uns32 AC12EN : 1;
            Uns32 DDR_EN : 1;
            Uns32 DTDSEL : 1;
            Uns32 MSBSEL : 1;
            Uns32 NIBBLE_POS : 1;
            Uns32 AC23EN : 1;
            Uns32 __pad8 : 14;
            Uns32 EXE_TUNE : 1;
            Uns32 SMP_CLK_SEL : 1;
            Uns32 AUTO_TUNE_EN : 1;
            Uns32 FBCLK_SEL : 1;
        } bits;
    } uSDHC_MIX_CTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 FEVTAC12NE : 1;
            Uns32 FEVTAC12TOE : 1;
            Uns32 FEVTAC12CE : 1;
            Uns32 FEVTAC12EBE : 1;
            Uns32 FEVTAC12IE : 1;
            Uns32 __pad5 : 2;
            Uns32 FEVTCNIBAC12E : 1;
            Uns32 __pad8 : 8;
            Uns32 FEVTCTOE : 1;
            Uns32 FEVTCCE : 1;
            Uns32 FEVTCEBE : 1;
            Uns32 FEVTCIE : 1;
            Uns32 FEVTDTOE : 1;
            Uns32 FEVTDCE : 1;
            Uns32 FEVTDEBE : 1;
            Uns32 __pad23 : 1;
            Uns32 FEVTAC12E : 1;
            Uns32 __pad25 : 1;
            Uns32 FEVTTNE : 1;
            Uns32 __pad27 : 1;
            Uns32 FEVTDMAE : 1;
            Uns32 __pad29 : 2;
            Uns32 FEVTCINT : 1;
        } bits;
    } uSDHC_FORCE_EVENT;
    union { 
        Uns32 value;
        struct {
            Uns32 ADMAES : 2;
            Uns32 ADMALME : 1;
            Uns32 ADMADCE : 1;
        } bits;
    } uSDHC_ADMA_ERR_STATUS;
    union { 
        Uns32 value;
    } uSDHC_ADMA_SYS_ADDR;
    union { 
        Uns32 value;
        struct {
            Uns32 DLL_CTRL_ENABLE : 1;
            Uns32 DLL_CTRL_RESET : 1;
            Uns32 DLL_CTRL_SLV_FORCE_UPD : 1;
            Uns32 DLL_CTRL_SLV_DLY_TARGET0 : 4;
            Uns32 DLL_CTRL_GATE_UPDATE : 1;
            Uns32 DLL_CTRL_SLV_OVERRIDE : 1;
            Uns32 DLL_CTRL_SLV_OVERRIDE_VAL : 6;
            Uns32 __pad15 : 1;
            Uns32 DLL_CTRL_SLV_DLY_TARGET1 : 3;
            Uns32 __pad19 : 1;
            Uns32 DLL_CTRL_SLV_UPDATE_INT : 8;
            Uns32 DLL_CTRL_REF_UPDATE_INT : 4;
        } bits;
    } uSDHC_DLL_CTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 DLL_STS_SLV_LOCK : 1;
            Uns32 DLL_STS_REF_LOCK : 1;
            Uns32 DLL_STS_SLV_SEL : 7;
            Uns32 DLL_STS_REF_SEL : 7;
        } bits;
    } uSDHC_DLL_STATUS;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY_CELL_SET_POST : 3;
            Uns32 __pad3 : 1;
            Uns32 DLY_CELL_SET_OUT : 3;
            Uns32 __pad7 : 1;
            Uns32 DLY_CELL_SET_PRE : 7;
            Uns32 NXT_ERR : 1;
            Uns32 TAP_SEL_POST : 4;
            Uns32 TAP_SEL_OUT : 4;
            Uns32 TAP_SEL_PRE : 7;
            Uns32 PRE_ERR : 1;
        } bits;
    } uSDHC_CLK_TUNE_CTRL_STATUS;
    union { 
        Uns32 value;
        struct {
            Uns32 EXT_DMA_EN : 1;
            Uns32 VSELECT : 1;
            Uns32 CONFLICT_CHK_EN : 1;
            Uns32 AC12_WR_CHKBUSY_EN : 1;
            Uns32 DAT3_CD_POL : 1;
            Uns32 CD_POL : 1;
            Uns32 WP_POL : 1;
            Uns32 CLKONJ_IN_ABORT : 1;
            Uns32 FRC_SDCLK_ON : 1;
            Uns32 __pad9 : 2;
            Uns32 IPG_CLK_SOFT_EN : 1;
            Uns32 HCLK_SOFT_EN : 1;
            Uns32 IPG_PERCLK_SOFT_EN : 1;
            Uns32 CARD_CLK_SOFT_EN : 1;
            Uns32 CRC_CHK_DIS : 1;
            Uns32 INT_ST_VAL : 8;
            Uns32 __pad24 : 7;
            Uns32 CMD_BYTE_EN : 1;
        } bits;
    } uSDHC_VEND_SPEC;
    union { 
        Uns32 value;
        struct {
            Uns32 DTOCV_ACK : 4;
            Uns32 BOOT_ACK : 1;
            Uns32 BOOT_MODE : 1;
            Uns32 BOOT_EN : 1;
            Uns32 AUTO_SABG_EN : 1;
            Uns32 DISABLE_TIME_OUT : 1;
            Uns32 __pad9 : 7;
            Uns32 BOOT_BLK_CNT : 16;
        } bits;
    } uSDHC_MMC_BOOT;
    union { 
        Uns32 value;
        struct {
            Uns32 SDR104_TIMING_DIS : 1;
            Uns32 SDR104_OE_DIS : 1;
            Uns32 SDR104_NSD_DIS : 1;
            Uns32 CARD_INT_D3_TEST : 1;
            Uns32 TUNING_8bit_EN : 1;
            Uns32 TUNING_1bit_EN : 1;
            Uns32 TUNING_CMD_EN : 1;
            Uns32 CARD_INT_AUTO_CLR_DIS : 1;
        } bits;
    } uSDHC_VEND_SPEC2;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle mport;
    void                 *bport1;
    ppmNetHandle          interrupt;
    ppmNetHandle          CD;
    ppmNetHandle          WP;
    ppmNetHandle          LCTL;
    ppmNetHandle          reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(ReaduSDHC_SYS_CTRL);
PPM_REG_WRITE_CB(WriteuSDHC_CMD_ARG);
PPM_REG_WRITE_CB(WriteuSDHC_CMD_XFR_TYP);
PPM_REG_WRITE_CB(WriteuSDHC_FORCE_EVENT);
PPM_REG_WRITE_CB(WriteuSDHC_INT_SIGNAL_EN);
PPM_REG_WRITE_CB(WriteuSDHC_INT_STATUS);
PPM_REG_WRITE_CB(WriteuSDHC_INT_STATUS_EN);
PPM_REG_WRITE_CB(WriteuSDHC_PROT_CTRL);
PPM_REG_WRITE_CB(WriteuSDHC_SYS_CTRL);
PPM_REG_WRITE_CB(WriteuSDHC_WTMK_LVL);
PPM_NET_CB(resetFunction);
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

// To access local memory bport1/ab/buffer76 : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER76_OFFSET + myAddress];

#define BPORT1_AB_BUFFER76_OFFSET       0x4c
#define BPORT1_AB_BUFFER76_SIZE         0x4

// To access local memory bport1/ab/buffer92 : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER92_OFFSET + myAddress];

#define BPORT1_AB_BUFFER92_OFFSET       0x5c
#define BPORT1_AB_BUFFER92_SIZE         0x4

// To access local memory bport1/ab/buffer108 : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER108_OFFSET + myAddress];

#define BPORT1_AB_BUFFER108_OFFSET      0x6c
#define BPORT1_AB_BUFFER108_SIZE        0x54

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_USDHC_DS_ADDR_WRMASK  0xfffffffe
#define BPORT1_AB_USDHC_DS_ADDR_WRNMASK  (0x1)
#define BPORT1_AB_USDHC_DS_ADDR_WIDTH   32
#define BPORT1_AB_USDHC_BLK_ATT_WRMASK  0xffff1fff
#define BPORT1_AB_USDHC_BLK_ATT_WRNMASK  (0xe000)
#define BPORT1_AB_USDHC_BLK_ATT_WIDTH   32
#define BPORT1_AB_USDHC_CMD_ARG_WIDTH   32
#define BPORT1_AB_USDHC_CMD_XFR_TYP_WRMASK  0x3ffb0000
#define BPORT1_AB_USDHC_CMD_XFR_TYP_WRNMASK  (0xc004ffff)
#define BPORT1_AB_USDHC_CMD_XFR_TYP_WIDTH  32
#define BPORT1_AB_USDHC_CMD_RSP0_WIDTH  32
#define BPORT1_AB_USDHC_CMD_RSP1_WIDTH  32
#define BPORT1_AB_USDHC_CMD_RSP2_WIDTH  32
#define BPORT1_AB_USDHC_CMD_RSP3_WIDTH  32
#define BPORT1_AB_USDHC_DATA_BUFF_ACC_PORT_WIDTH  32
#define BPORT1_AB_USDHC_PRES_STATE_WIDTH  32
#define BPORT1_AB_USDHC_PROT_CTRL_WRMASK  0x7f1f03ff
#define BPORT1_AB_USDHC_PROT_CTRL_WRNMASK  (0x80e0fc00)
#define BPORT1_AB_USDHC_PROT_CTRL_WIDTH  32
#define BPORT1_AB_USDHC_SYS_CTRL_WRMASK  0xf8ffff0
#define BPORT1_AB_USDHC_SYS_CTRL_WRNMASK  (0xf070000f)
#define BPORT1_AB_USDHC_SYS_CTRL_WIDTH  32
#define BPORT1_AB_USDHC_INT_STATUS_WRMASK  0x157f51ff
#define BPORT1_AB_USDHC_INT_STATUS_WRNMASK  (0xea80ae00)
#define BPORT1_AB_USDHC_INT_STATUS_WIDTH  32
#define BPORT1_AB_USDHC_INT_STATUS_EN_WRMASK  0x157f51ff
#define BPORT1_AB_USDHC_INT_STATUS_EN_WRNMASK  (0xea80ae00)
#define BPORT1_AB_USDHC_INT_STATUS_EN_WIDTH  32
#define BPORT1_AB_USDHC_INT_SIGNAL_EN_WRMASK  0x157f51ff
#define BPORT1_AB_USDHC_INT_SIGNAL_EN_WRNMASK  (0xea80ae00)
#define BPORT1_AB_USDHC_INT_SIGNAL_EN_WIDTH  32
#define BPORT1_AB_USDHC_AUTOCMD12_ERR_STATUS_WIDTH  32
#define BPORT1_AB_USDHC_HOST_CTRL_CAP_WIDTH  32
#define BPORT1_AB_USDHC_WTMK_LVL_WRMASK  0x1fff1fff
#define BPORT1_AB_USDHC_WTMK_LVL_WRNMASK  (0xe000e000)
#define BPORT1_AB_USDHC_WTMK_LVL_WIDTH  32
#define BPORT1_AB_USDHC_MIX_CTRL_WRMASK  0x1e0000ff
#define BPORT1_AB_USDHC_MIX_CTRL_WRNMASK  (0xe1ffff00)
#define BPORT1_AB_USDHC_MIX_CTRL_WIDTH  32
#define BPORT1_AB_USDHC_FORCE_EVENT_WRMASK  0x957f009f
#define BPORT1_AB_USDHC_FORCE_EVENT_WRNMASK  (0x6a80ff60)
#define BPORT1_AB_USDHC_FORCE_EVENT_WIDTH  32
#define BPORT1_AB_USDHC_ADMA_ERR_STATUS_WIDTH  32
#define BPORT1_AB_USDHC_ADMA_SYS_ADDR_WRMASK  0xfffffffe
#define BPORT1_AB_USDHC_ADMA_SYS_ADDR_WRNMASK  (0x1)
#define BPORT1_AB_USDHC_ADMA_SYS_ADDR_WIDTH  32
#define BPORT1_AB_USDHC_DLL_CTRL_WRMASK  0xfff7ffff
#define BPORT1_AB_USDHC_DLL_CTRL_WRNMASK  (0x80000)
#define BPORT1_AB_USDHC_DLL_CTRL_WIDTH  32
#define BPORT1_AB_USDHC_DLL_STATUS_WIDTH  32
#define BPORT1_AB_USDHC_CLK_TUNE_CTRL_STATUS_WRMASK  0x7fff
#define BPORT1_AB_USDHC_CLK_TUNE_CTRL_STATUS_WRNMASK  (0xffff8000)
#define BPORT1_AB_USDHC_CLK_TUNE_CTRL_STATUS_WIDTH  32
#define BPORT1_AB_USDHC_VEND_SPEC_WRMASK  0x8000f9ff
#define BPORT1_AB_USDHC_VEND_SPEC_WRNMASK  (0x7fff0600)
#define BPORT1_AB_USDHC_VEND_SPEC_WIDTH  32
#define BPORT1_AB_USDHC_MMC_BOOT_WRMASK  0xffff1fff
#define BPORT1_AB_USDHC_MMC_BOOT_WRNMASK  (0xe000)
#define BPORT1_AB_USDHC_MMC_BOOT_WIDTH  32
#define BPORT1_AB_USDHC_VEND_SPEC2_WRMASK  0x3ff
#define BPORT1_AB_USDHC_VEND_SPEC2_WRNMASK  (0xfffffc00)
#define BPORT1_AB_USDHC_VEND_SPEC2_WIDTH  32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

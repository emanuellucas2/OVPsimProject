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
            Uns32 __pad0 : 1;
            Uns32 EDBG : 1;
            Uns32 ERCA : 1;
            Uns32 ERGA : 1;
            Uns32 HOE : 1;
            Uns32 HALT : 1;
            Uns32 CLM : 1;
            Uns32 EMLM : 1;
            Uns32 GRP0PRI : 2;
            Uns32 GRP1PRI : 2;
            Uns32 __pad12 : 4;
            Uns32 ECX : 1;
            Uns32 CX : 1;
        } bits;
    } CR;
    union { 
        Uns32 value;
        struct {
            Uns32 DBE : 1;
            Uns32 SBE : 1;
            Uns32 SGE : 1;
            Uns32 NCE : 1;
            Uns32 DOE : 1;
            Uns32 DAE : 1;
            Uns32 SOE : 1;
            Uns32 SAE : 1;
            Uns32 ERRCHN : 5;
            Uns32 __pad13 : 1;
            Uns32 CPE : 1;
            Uns32 GPE : 1;
            Uns32 ECX : 1;
            Uns32 __pad17 : 14;
            Uns32 VLD : 1;
        } bits;
    } ES;
    union { 
        Uns32 value;
        struct {
            Uns32 ERQ0 : 1;
            Uns32 ERQ1 : 1;
            Uns32 ERQ2 : 1;
            Uns32 ERQ3 : 1;
            Uns32 ERQ4 : 1;
            Uns32 ERQ5 : 1;
            Uns32 ERQ6 : 1;
            Uns32 ERQ7 : 1;
            Uns32 ERQ8 : 1;
            Uns32 ERQ9 : 1;
            Uns32 ERQ10 : 1;
            Uns32 ERQ11 : 1;
            Uns32 ERQ12 : 1;
            Uns32 ERQ13 : 1;
            Uns32 ERQ14 : 1;
            Uns32 ERQ15 : 1;
            Uns32 ERQ16 : 1;
            Uns32 ERQ17 : 1;
            Uns32 ERQ18 : 1;
            Uns32 ERQ19 : 1;
            Uns32 ERQ20 : 1;
            Uns32 ERQ21 : 1;
            Uns32 ERQ22 : 1;
            Uns32 ERQ23 : 1;
            Uns32 ERQ24 : 1;
            Uns32 ERQ25 : 1;
            Uns32 ERQ26 : 1;
            Uns32 ERQ27 : 1;
            Uns32 ERQ28 : 1;
            Uns32 ERQ29 : 1;
            Uns32 ERQ30 : 1;
            Uns32 ERQ31 : 1;
        } bits;
    } ERQ;
    union { 
        Uns32 value;
        struct {
            Uns32 EEI00 : 1;
            Uns32 EEI01 : 1;
            Uns32 EEI02 : 1;
            Uns32 EEI03 : 1;
            Uns32 EEI04 : 1;
            Uns32 EEI05 : 1;
            Uns32 EEI06 : 1;
            Uns32 EEI07 : 1;
            Uns32 EEI08 : 1;
            Uns32 EEI09 : 1;
            Uns32 EEI010 : 1;
            Uns32 EEI011 : 1;
            Uns32 EEI012 : 1;
            Uns32 EEI013 : 1;
            Uns32 EEI014 : 1;
            Uns32 EEI015 : 1;
            Uns32 EEI016 : 1;
            Uns32 EEI017 : 1;
            Uns32 EEI018 : 1;
            Uns32 EEI019 : 1;
            Uns32 EEI020 : 1;
            Uns32 EEI021 : 1;
            Uns32 EEI022 : 1;
            Uns32 EEI023 : 1;
            Uns32 EEI024 : 1;
            Uns32 EEI025 : 1;
            Uns32 EEI026 : 1;
            Uns32 EEI027 : 1;
            Uns32 EEI028 : 1;
            Uns32 EEI029 : 1;
            Uns32 EEI030 : 1;
            Uns32 EEI031 : 1;
        } bits;
    } EEI;
    union { 
        Uns32 value;
    } CS_EEI_ERC;
    union { 
        Uns32 value;
    } DNE_SRT_ERR_INT;
    union { 
        Uns32 value;
        struct {
            Uns32 INT0 : 1;
            Uns32 INT1 : 1;
            Uns32 INT2 : 1;
            Uns32 INT3 : 1;
            Uns32 INT4 : 1;
            Uns32 INT5 : 1;
            Uns32 INT6 : 1;
            Uns32 INT7 : 1;
            Uns32 INT8 : 1;
            Uns32 INT9 : 1;
            Uns32 INT10 : 1;
            Uns32 INT11 : 1;
            Uns32 INT12 : 1;
            Uns32 INT13 : 1;
            Uns32 INT14 : 1;
            Uns32 INT15 : 1;
            Uns32 INT16 : 1;
            Uns32 INT17 : 1;
            Uns32 INT18 : 1;
            Uns32 INT19 : 1;
            Uns32 INT20 : 1;
            Uns32 INT21 : 1;
            Uns32 INT22 : 1;
            Uns32 INT23 : 1;
            Uns32 INT24 : 1;
            Uns32 INT25 : 1;
            Uns32 INT26 : 1;
            Uns32 INT27 : 1;
            Uns32 INT28 : 1;
            Uns32 INT29 : 1;
            Uns32 INT30 : 1;
            Uns32 INT31 : 1;
        } bits;
    } INT;
    union { 
        Uns32 value;
        struct {
            Uns32 ERR0 : 1;
            Uns32 ERR1 : 1;
            Uns32 ERR2 : 1;
            Uns32 ERR3 : 1;
            Uns32 ERR4 : 1;
            Uns32 ERR5 : 1;
            Uns32 ERR6 : 1;
            Uns32 ERR7 : 1;
            Uns32 ERR8 : 1;
            Uns32 ERR9 : 1;
            Uns32 ERR10 : 1;
            Uns32 ERR11 : 1;
            Uns32 ERR12 : 1;
            Uns32 ERR13 : 1;
            Uns32 ERR14 : 1;
            Uns32 ERR15 : 1;
            Uns32 ERR16 : 1;
            Uns32 ERR17 : 1;
            Uns32 ERR18 : 1;
            Uns32 ERR19 : 1;
            Uns32 ERR20 : 1;
            Uns32 ERR21 : 1;
            Uns32 ERR22 : 1;
            Uns32 ERR23 : 1;
            Uns32 ERR24 : 1;
            Uns32 ERR25 : 1;
            Uns32 ERR26 : 1;
            Uns32 ERR27 : 1;
            Uns32 ERR28 : 1;
            Uns32 ERR29 : 1;
            Uns32 ERR30 : 1;
            Uns32 ERR31 : 1;
        } bits;
    } ERR;
    union { 
        Uns32 value;
        struct {
            Uns32 HRS0 : 1;
            Uns32 HRS1 : 1;
            Uns32 HRS2 : 1;
            Uns32 HRS3 : 1;
            Uns32 HRS4 : 1;
            Uns32 HRS5 : 1;
            Uns32 HRS6 : 1;
            Uns32 HRS7 : 1;
            Uns32 HRS8 : 1;
            Uns32 HRS9 : 1;
            Uns32 HRS10 : 1;
            Uns32 HRS11 : 1;
            Uns32 HRS12 : 1;
            Uns32 HRS13 : 1;
            Uns32 HRS14 : 1;
            Uns32 HRS15 : 1;
            Uns32 HRS16 : 1;
            Uns32 HRS17 : 1;
            Uns32 HRS18 : 1;
            Uns32 HRS19 : 1;
            Uns32 HRS20 : 1;
            Uns32 HRS21 : 1;
            Uns32 HRS22 : 1;
            Uns32 HRS23 : 1;
            Uns32 HRS24 : 1;
            Uns32 HRS25 : 1;
            Uns32 HRS26 : 1;
            Uns32 HRS27 : 1;
            Uns32 HRS28 : 1;
            Uns32 HRS29 : 1;
            Uns32 HRS30 : 1;
            Uns32 HRS31 : 1;
        } bits;
    } HRS;
    union { 
        Uns32 value;
    } DCHPRI3_0;
    union { 
        Uns32 value;
    } DCHPRI7_4;
    union { 
        Uns32 value;
    } DCHPRI11_8;
    union { 
        Uns32 value;
    } DCHPRI15_12;
    union { 
        Uns32 value;
    } DCHPRI19_16;
    union { 
        Uns32 value;
    } DCHPRI23_20;
    union { 
        Uns32 value;
    } DCHPRI27_24;
    union { 
        Uns32 value;
    } DCHPRI31_28;
} bport1_ab_dataT, *bport1_ab_dataTP;

typedef struct bport1_TCD_dataS { 
    union { 
        Uns32 value;
    } SADDR;
    union { 
        Uns32 value;
    } SOFF_ATTR;
    union { 
        Uns32 value;
    } NBYTES;
    union { 
        Uns32 value;
    } SLAST;
    union { 
        Uns32 value;
    } DADDR;
    union { 
        Uns32 value;
    } DOFF_CITER;
    union { 
        Uns32 value;
    } DLASTSGA;
    union { 
        Uns32 value;
    } CSR_BITER;
} bport1_TCD_dataT, *bport1_TCD_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

extern bport1_TCD_dataT bport1_TCD_data[32];

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle MREAD;
    ppmAddressSpaceHandle MWRITE;
    void                 *bport1;
    ppmNetHandle          Reset;
    ppmNetHandle          eDMARequest;
    ppmNetHandle          eDMADone;
    ppmNetHandle          errorInterrupt;
    ppmNetHandle          dmaInterrupt_ch[32];
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(DMARequest);
PPM_NET_CB(DMAReset);
PPM_REG_READ_CB(regRead32);
PPM_REG_READ_CB(regReadCHPRI);
PPM_REG_READ_CB(regReadCR);
PPM_REG_READ_CB(regReadES);
PPM_NBYTE_READ_CB(regReadTCD);
PPM_NBYTE_READ_CB(regReadTCD16);
PPM_REG_READ_CB(regReadZero);
PPM_REG_WRITE_CB(regSetGroup);
PPM_REG_WRITE_CB(regWrite1c);
PPM_REG_WRITE_CB(regWrite32);
PPM_REG_WRITE_CB(regWriteCHPRI);
PPM_REG_WRITE_CB(regWriteCR);
PPM_NBYTE_WRITE_CB(regWriteTCD);
PPM_NBYTE_WRITE_CB(regWriteTCD16);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_CR_WRMASK             0x30ffe
#define BPORT1_AB_CR_WRNMASK            (0xfffcf001)
#define BPORT1_AB_CR_WIDTH              32
#define BPORT1_AB_ES_WIDTH              32
#define BPORT1_AB_ERQ_WRMASK            0xffffffff
#define BPORT1_AB_ERQ_WRNMASK           (0x0)
#define BPORT1_AB_ERQ_WIDTH             32
#define BPORT1_AB_EEI_WRMASK            0xffffffff
#define BPORT1_AB_EEI_WRNMASK           (0x0)
#define BPORT1_AB_EEI_WIDTH             32
#define BPORT1_AB_CS_EEI_ERC_WRMASK     0xdfdfdfdf
#define BPORT1_AB_CS_EEI_ERC_WRNMASK    (0x20202020)
#define BPORT1_AB_CS_EEI_ERC_WIDTH      32
#define BPORT1_AB_DNE_SRT_ERR_INT_WRMASK  0xdfdfdfdf
#define BPORT1_AB_DNE_SRT_ERR_INT_WRNMASK  (0x20202020)
#define BPORT1_AB_DNE_SRT_ERR_INT_WIDTH  32
#define BPORT1_AB_INT_WRMASK            0xffffffff
#define BPORT1_AB_INT_WRNMASK           (0x0)
#define BPORT1_AB_INT_WIDTH             32
#define BPORT1_AB_ERR_WRMASK            0xffffffff
#define BPORT1_AB_ERR_WRNMASK           (0x0)
#define BPORT1_AB_ERR_WIDTH             32
#define BPORT1_AB_HRS_WRMASK            0xffffffff
#define BPORT1_AB_HRS_WRNMASK           (0x0)
#define BPORT1_AB_HRS_WIDTH             32
#define BPORT1_AB_DCHPRI3_0_WRMASK      0xcf
#define BPORT1_AB_DCHPRI3_0_WRNMASK     (0xffffff30)
#define BPORT1_AB_DCHPRI3_0_WIDTH       32
#define BPORT1_AB_DCHPRI7_4_WRMASK      0xcf
#define BPORT1_AB_DCHPRI7_4_WRNMASK     (0xffffff30)
#define BPORT1_AB_DCHPRI7_4_WIDTH       32
#define BPORT1_AB_DCHPRI11_8_WRMASK     0xcf
#define BPORT1_AB_DCHPRI11_8_WRNMASK    (0xffffff30)
#define BPORT1_AB_DCHPRI11_8_WIDTH      32
#define BPORT1_AB_DCHPRI15_12_WRMASK    0xcf
#define BPORT1_AB_DCHPRI15_12_WRNMASK   (0xffffff30)
#define BPORT1_AB_DCHPRI15_12_WIDTH     32
#define BPORT1_AB_DCHPRI19_16_WRMASK    0xcf
#define BPORT1_AB_DCHPRI19_16_WRNMASK   (0xffffff30)
#define BPORT1_AB_DCHPRI19_16_WIDTH     32
#define BPORT1_AB_DCHPRI23_20_WRMASK    0xcf
#define BPORT1_AB_DCHPRI23_20_WRNMASK   (0xffffff30)
#define BPORT1_AB_DCHPRI23_20_WIDTH     32
#define BPORT1_AB_DCHPRI27_24_WRMASK    0xcf
#define BPORT1_AB_DCHPRI27_24_WRNMASK   (0xffffff30)
#define BPORT1_AB_DCHPRI27_24_WIDTH     32
#define BPORT1_AB_DCHPRI31_28_WRMASK    0xcf
#define BPORT1_AB_DCHPRI31_28_WRNMASK   (0xffffff30)
#define BPORT1_AB_DCHPRI31_28_WIDTH     32
#define BPORT1_TCD_SADDR_WIDTH          32
#define BPORT1_TCD_SOFF_ATTR_WIDTH      32
#define BPORT1_TCD_NBYTES_WIDTH         32
#define BPORT1_TCD_SLAST_WIDTH          32
#define BPORT1_TCD_DADDR_WIDTH          32
#define BPORT1_TCD_DOFF_CITER_WIDTH     32
#define BPORT1_TCD_DLASTSGA_WIDTH       32
#define BPORT1_TCD_CSR_BITER_WIDTH      32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

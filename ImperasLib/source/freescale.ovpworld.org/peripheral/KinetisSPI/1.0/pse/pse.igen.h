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
            Uns32 HALT : 1;
            Uns32 __pad1 : 7;
            Uns32 SMPL_PT : 2;
            Uns32 CLR_RXF : 1;
            Uns32 CLR_TXF : 1;
            Uns32 DIS_RXF : 1;
            Uns32 DIS_TXF : 1;
            Uns32 MDIS : 1;
            Uns32 DOZE : 1;
            Uns32 PCSIS : 6;
            Uns32 __pad22 : 2;
            Uns32 ROOE : 1;
            Uns32 PCSSE : 1;
            Uns32 MTFE : 1;
            Uns32 FRZ : 1;
            Uns32 DCONF : 2;
            Uns32 CONT_SCKE : 1;
            Uns32 MSTR : 1;
        } bits;
    } MCR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 SPI_TCNT : 16;
        } bits;
    } TCR;
    union { 
        Uns32 value;
        struct {
            Uns32 BR : 4;
            Uns32 DT : 4;
            Uns32 ASC : 4;
            Uns32 CSSCK : 4;
            Uns32 PBR : 2;
            Uns32 PDT : 2;
            Uns32 PASC : 2;
            Uns32 PCSSCK : 2;
            Uns32 LSBFE : 1;
            Uns32 CPHA : 1;
            Uns32 CPOL : 1;
            Uns32 FMSZ : 4;
            Uns32 DBR : 1;
        } bits;
    } CTAR0;
    union { 
        Uns32 value;
        struct {
            Uns32 BR : 4;
            Uns32 DT : 4;
            Uns32 ASC : 4;
            Uns32 CSSCK : 4;
            Uns32 PBR : 2;
            Uns32 PDT : 2;
            Uns32 PASC : 2;
            Uns32 PCSSCK : 2;
            Uns32 LSBFE : 1;
            Uns32 CPHA : 1;
            Uns32 CPOL : 1;
            Uns32 FMSZ : 4;
            Uns32 DBR : 1;
        } bits;
    } CTAR1;
    union { 
        Uns32 value;
        struct {
            Uns32 POPNXTPTR : 4;
            Uns32 RXCTR : 4;
            Uns32 TXNXTPTR : 4;
            Uns32 TXCTR : 4;
            Uns32 __pad16 : 1;
            Uns32 RFDF : 1;
            Uns32 __pad18 : 1;
            Uns32 RFOF : 1;
            Uns32 __pad20 : 5;
            Uns32 TFFF : 1;
            Uns32 __pad26 : 1;
            Uns32 TFUF : 1;
            Uns32 EOQF : 1;
            Uns32 __pad29 : 1;
            Uns32 TXRXS : 1;
            Uns32 TCF : 1;
        } bits;
    } SR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 RFDF_DIRS : 1;
            Uns32 RFDF_RE : 1;
            Uns32 __pad18 : 1;
            Uns32 RFOF_RE : 1;
            Uns32 __pad20 : 4;
            Uns32 TFFF_DIRS : 1;
            Uns32 TFFF_RE : 1;
            Uns32 __pad26 : 1;
            Uns32 TFUF_RE : 1;
            Uns32 EOQF_RE : 1;
            Uns32 __pad29 : 2;
            Uns32 TCF_RE : 1;
        } bits;
    } RSER;
    union { 
        Uns32 value;
        struct {
            Uns32 TXDATA : 16;
            Uns32 PCS : 6;
            Uns32 __pad22 : 4;
            Uns32 CTCNT : 1;
            Uns32 EOQ : 1;
            Uns32 CTAS : 3;
            Uns32 CONT : 1;
        } bits;
    } PUSHR;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } POPR;
    union { 
        Uns32 value;
        struct {
            Uns32 TXDATA : 16;
            Uns32 TXCMD_TXDATA : 16;
        } bits;
    } TXFR0;
    union { 
        Uns32 value;
        struct {
            Uns32 TXDATA : 16;
            Uns32 TXCMD_TXDATA : 16;
        } bits;
    } TXFR1;
    union { 
        Uns32 value;
        struct {
            Uns32 TXDATA : 16;
            Uns32 TXCMD_TXDATA : 16;
        } bits;
    } TXFR2;
    union { 
        Uns32 value;
        struct {
            Uns32 TXDATA : 16;
            Uns32 TXCMD_TXDATA : 16;
        } bits;
    } TXFR3;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RXFR0;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RXFR1;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RXFR2;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RXFR3;
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

#define BPORT1_AB_MCR_WRMASK            0xff3fff01
#define BPORT1_AB_MCR_WRNMASK           (0xc000fe)
#define BPORT1_AB_MCR_WIDTH             32
#define BPORT1_AB_TCR_WRMASK            0xffff0000
#define BPORT1_AB_TCR_WRNMASK           (0xffff)
#define BPORT1_AB_TCR_WIDTH             32
#define BPORT1_AB_CTAR0_WRMASK          0xffffffff
#define BPORT1_AB_CTAR0_WRNMASK         (0x0)
#define BPORT1_AB_CTAR0_WIDTH           32
#define BPORT1_AB_CTAR1_WRMASK          0xffffffff
#define BPORT1_AB_CTAR1_WRNMASK         (0x0)
#define BPORT1_AB_CTAR1_WIDTH           32
#define BPORT1_AB_SR_WRMASK             0xda0a0000
#define BPORT1_AB_SR_WRNMASK            (0x25f5ffff)
#define BPORT1_AB_SR_WIDTH              32
#define BPORT1_AB_RSER_WRMASK           0x9b0b0000
#define BPORT1_AB_RSER_WRNMASK          (0x64f4ffff)
#define BPORT1_AB_RSER_WIDTH            32
#define BPORT1_AB_PUSHR_WRMASK          0xffffffff
#define BPORT1_AB_PUSHR_WRNMASK         (0x0)
#define BPORT1_AB_PUSHR_WIDTH           32
#define BPORT1_AB_POPR_WIDTH            32
#define BPORT1_AB_TXFR0_WIDTH           32
#define BPORT1_AB_TXFR1_WIDTH           32
#define BPORT1_AB_TXFR2_WIDTH           32
#define BPORT1_AB_TXFR3_WIDTH           32
#define BPORT1_AB_RXFR0_WIDTH           32
#define BPORT1_AB_RXFR1_WIDTH           32
#define BPORT1_AB_RXFR2_WIDTH           32
#define BPORT1_AB_RXFR3_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

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
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR0;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR1;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR2;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR3;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR4;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR5;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR6;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR7;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR8;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR9;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR10;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR11;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR12;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR13;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR14;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR15;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR16;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR17;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR18;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR19;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR20;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR21;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR22;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR23;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR24;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR25;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR26;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR27;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR28;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR29;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR30;
    union { 
        Uns32 value;
        struct {
            Uns32 PS : 1;
            Uns32 PE : 1;
            Uns32 SRE : 1;
            Uns32 __pad3 : 1;
            Uns32 PFE : 1;
            Uns32 ODE : 1;
            Uns32 DSE : 1;
            Uns32 __pad7 : 1;
            Uns32 MUX : 3;
            Uns32 __pad11 : 4;
            Uns32 LK : 1;
            Uns32 IRQC : 4;
            Uns32 __pad20 : 4;
            Uns32 ISF : 1;
        } bits;
    } PCR31;
    union { 
        Uns32 value;
        struct {
            Uns32 GPWD : 16;
            Uns32 GPWE : 16;
        } bits;
    } GPCLR;
    union { 
        Uns32 value;
        struct {
            Uns32 GPWD : 16;
            Uns32 GPWE : 16;
        } bits;
    } GPCHR;
    union { 
        Uns32 value;
        struct {
            Uns32 ISF : 32;
        } bits;
    } ISFR;
    union { 
        Uns32 value;
        struct {
            Uns32 DFE : 32;
        } bits;
    } DFER;
    union { 
        Uns32 value;
        struct {
            Uns32 CS : 1;
        } bits;
    } DFCR;
    union { 
        Uns32 value;
        struct {
            Uns32 FILT : 5;
        } bits;
    } DFWR;
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

#define BPORT1_AB_PCR0_WRMASK           0x10f8777
#define BPORT1_AB_PCR0_WRNMASK          (0xfef07888)
#define BPORT1_AB_PCR0_WIDTH            32
#define BPORT1_AB_PCR1_WRMASK           0x10f8777
#define BPORT1_AB_PCR1_WRNMASK          (0xfef07888)
#define BPORT1_AB_PCR1_WIDTH            32
#define BPORT1_AB_PCR2_WRMASK           0x10f8777
#define BPORT1_AB_PCR2_WRNMASK          (0xfef07888)
#define BPORT1_AB_PCR2_WIDTH            32
#define BPORT1_AB_PCR3_WRMASK           0x10f8777
#define BPORT1_AB_PCR3_WRNMASK          (0xfef07888)
#define BPORT1_AB_PCR3_WIDTH            32
#define BPORT1_AB_PCR4_WRMASK           0x10f8777
#define BPORT1_AB_PCR4_WRNMASK          (0xfef07888)
#define BPORT1_AB_PCR4_WIDTH            32
#define BPORT1_AB_PCR5_WRMASK           0x10f8777
#define BPORT1_AB_PCR5_WRNMASK          (0xfef07888)
#define BPORT1_AB_PCR5_WIDTH            32
#define BPORT1_AB_PCR6_WRMASK           0x10f8777
#define BPORT1_AB_PCR6_WRNMASK          (0xfef07888)
#define BPORT1_AB_PCR6_WIDTH            32
#define BPORT1_AB_PCR7_WRMASK           0x10f8777
#define BPORT1_AB_PCR7_WRNMASK          (0xfef07888)
#define BPORT1_AB_PCR7_WIDTH            32
#define BPORT1_AB_PCR8_WRMASK           0x10f8777
#define BPORT1_AB_PCR8_WRNMASK          (0xfef07888)
#define BPORT1_AB_PCR8_WIDTH            32
#define BPORT1_AB_PCR9_WRMASK           0x10f8777
#define BPORT1_AB_PCR9_WRNMASK          (0xfef07888)
#define BPORT1_AB_PCR9_WIDTH            32
#define BPORT1_AB_PCR10_WRMASK          0x10f8777
#define BPORT1_AB_PCR10_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR10_WIDTH           32
#define BPORT1_AB_PCR11_WRMASK          0x10f8777
#define BPORT1_AB_PCR11_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR11_WIDTH           32
#define BPORT1_AB_PCR12_WRMASK          0x10f8777
#define BPORT1_AB_PCR12_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR12_WIDTH           32
#define BPORT1_AB_PCR13_WRMASK          0x10f8777
#define BPORT1_AB_PCR13_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR13_WIDTH           32
#define BPORT1_AB_PCR14_WRMASK          0x10f8777
#define BPORT1_AB_PCR14_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR14_WIDTH           32
#define BPORT1_AB_PCR15_WRMASK          0x10f8777
#define BPORT1_AB_PCR15_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR15_WIDTH           32
#define BPORT1_AB_PCR16_WRMASK          0x10f8777
#define BPORT1_AB_PCR16_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR16_WIDTH           32
#define BPORT1_AB_PCR17_WRMASK          0x10f8777
#define BPORT1_AB_PCR17_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR17_WIDTH           32
#define BPORT1_AB_PCR18_WRMASK          0x10f8777
#define BPORT1_AB_PCR18_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR18_WIDTH           32
#define BPORT1_AB_PCR19_WRMASK          0x10f8777
#define BPORT1_AB_PCR19_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR19_WIDTH           32
#define BPORT1_AB_PCR20_WRMASK          0x10f8777
#define BPORT1_AB_PCR20_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR20_WIDTH           32
#define BPORT1_AB_PCR21_WRMASK          0x10f8777
#define BPORT1_AB_PCR21_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR21_WIDTH           32
#define BPORT1_AB_PCR22_WRMASK          0x10f8777
#define BPORT1_AB_PCR22_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR22_WIDTH           32
#define BPORT1_AB_PCR23_WRMASK          0x10f8777
#define BPORT1_AB_PCR23_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR23_WIDTH           32
#define BPORT1_AB_PCR24_WRMASK          0x10f8777
#define BPORT1_AB_PCR24_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR24_WIDTH           32
#define BPORT1_AB_PCR25_WRMASK          0x10f8777
#define BPORT1_AB_PCR25_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR25_WIDTH           32
#define BPORT1_AB_PCR26_WRMASK          0x10f8777
#define BPORT1_AB_PCR26_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR26_WIDTH           32
#define BPORT1_AB_PCR27_WRMASK          0x10f8777
#define BPORT1_AB_PCR27_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR27_WIDTH           32
#define BPORT1_AB_PCR28_WRMASK          0x10f8777
#define BPORT1_AB_PCR28_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR28_WIDTH           32
#define BPORT1_AB_PCR29_WRMASK          0x10f8777
#define BPORT1_AB_PCR29_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR29_WIDTH           32
#define BPORT1_AB_PCR30_WRMASK          0x10f8777
#define BPORT1_AB_PCR30_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR30_WIDTH           32
#define BPORT1_AB_PCR31_WRMASK          0x10f8777
#define BPORT1_AB_PCR31_WRNMASK         (0xfef07888)
#define BPORT1_AB_PCR31_WIDTH           32
#define BPORT1_AB_GPCLR_WRMASK          0xffffffff
#define BPORT1_AB_GPCLR_WRNMASK         (0x0)
#define BPORT1_AB_GPCLR_WIDTH           32
#define BPORT1_AB_GPCHR_WRMASK          0xffffffff
#define BPORT1_AB_GPCHR_WRNMASK         (0x0)
#define BPORT1_AB_GPCHR_WIDTH           32
#define BPORT1_AB_ISFR_WRMASK           0xffffffff
#define BPORT1_AB_ISFR_WRNMASK          (0x0)
#define BPORT1_AB_ISFR_WIDTH            32
#define BPORT1_AB_DFER_WRMASK           0xffffffff
#define BPORT1_AB_DFER_WRNMASK          (0x0)
#define BPORT1_AB_DFER_WIDTH            32
#define BPORT1_AB_DFCR_WRMASK           0x1
#define BPORT1_AB_DFCR_WRNMASK          (0xfffffffe)
#define BPORT1_AB_DFCR_WIDTH            32
#define BPORT1_AB_DFWR_WRMASK           0x1f
#define BPORT1_AB_DFWR_WRNMASK          (0xffffffe0)
#define BPORT1_AB_DFWR_WIDTH            32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

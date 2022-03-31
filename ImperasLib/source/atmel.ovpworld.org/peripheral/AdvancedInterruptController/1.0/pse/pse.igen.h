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

typedef struct bp1_REG_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 PRIOR : 2;
            Uns32 __pad2 : 3;
            Uns32 SRCTYPE : 2;
        } bits;
    } AIC_SMR[32];
    union { 
        Uns32 value;
        struct {
            Uns32 VECTOR : 32;
        } bits;
    } AIC_SVR[32];
    union { 
        Uns32 value;
    } AIC_IVR;
    union { 
        Uns32 value;
    } AIC_FVR;
    union { 
        Uns32 value;
        struct {
            Uns32 IRQID : 5;
        } bits;
    } AIC_ISR;
    union { 
        Uns32 value;
        struct {
            Uns32 FIQ : 1;
            Uns32 SWIRQ : 1;
            Uns32 US0IRQ : 1;
            Uns32 US1IRQ : 1;
            Uns32 TC0IRQ : 1;
            Uns32 TC1IRQ : 1;
            Uns32 TC2IRQ : 1;
            Uns32 WDIRQ : 1;
            Uns32 PIOIRQ : 1;
            Uns32 __pad9 : 7;
            Uns32 IRQ0 : 1;
            Uns32 IRQ1 : 1;
            Uns32 IRQ2 : 1;
        } bits;
    } AIC_IPR;
    union { 
        Uns32 value;
        struct {
            Uns32 FIQ : 1;
            Uns32 SWIRQ : 1;
            Uns32 US0IRQ : 1;
            Uns32 US1IRQ : 1;
            Uns32 TC0IRQ : 1;
            Uns32 TC1IRQ : 1;
            Uns32 TC2IRQ : 1;
            Uns32 WDIRQ : 1;
            Uns32 PIOIRQ : 1;
            Uns32 __pad9 : 7;
            Uns32 IRQ0 : 1;
            Uns32 IRQ1 : 1;
            Uns32 IRQ2 : 1;
        } bits;
    } AIC_IMR;
    union { 
        Uns32 value;
        struct {
            Uns32 NFIQ : 1;
            Uns32 NIRQ : 1;
        } bits;
    } AIC_CISR;
    union { 
        Uns32 value;
        struct {
            Uns32 FIQ : 1;
            Uns32 SWIRQ : 1;
            Uns32 US0IRQ : 1;
            Uns32 US1IRQ : 1;
            Uns32 TC0IRQ : 1;
            Uns32 TC1IRQ : 1;
            Uns32 TC2IRQ : 1;
            Uns32 WDIRQ : 1;
            Uns32 PIOIRQ : 1;
            Uns32 __pad9 : 7;
            Uns32 IRQ0 : 1;
            Uns32 IRQ1 : 1;
            Uns32 IRQ2 : 1;
        } bits;
    } AIC_IECR;
    union { 
        Uns32 value;
        struct {
            Uns32 FIQ : 1;
            Uns32 SWIRQ : 1;
            Uns32 US0IRQ : 1;
            Uns32 US1IRQ : 1;
            Uns32 TC0IRQ : 1;
            Uns32 TC1IRQ : 1;
            Uns32 TC2IRQ : 1;
            Uns32 WDIRQ : 1;
            Uns32 PIOIRQ : 1;
            Uns32 __pad9 : 7;
            Uns32 IRQ0 : 1;
            Uns32 IRQ1 : 1;
            Uns32 IRQ2 : 1;
        } bits;
    } AIC_IDCR;
    union { 
        Uns32 value;
        struct {
            Uns32 FIQ : 1;
            Uns32 SWIRQ : 1;
            Uns32 US0IRQ : 1;
            Uns32 US1IRQ : 1;
            Uns32 TC0IRQ : 1;
            Uns32 TC1IRQ : 1;
            Uns32 TC2IRQ : 1;
            Uns32 WDIRQ : 1;
            Uns32 PIOIRQ : 1;
            Uns32 __pad9 : 7;
            Uns32 IRQ0 : 1;
            Uns32 IRQ1 : 1;
            Uns32 IRQ2 : 1;
        } bits;
    } AIC_ICCR;
    union { 
        Uns32 value;
        struct {
            Uns32 FIQ : 1;
            Uns32 SWIRQ : 1;
            Uns32 US0IRQ : 1;
            Uns32 US1IRQ : 1;
            Uns32 TC0IRQ : 1;
            Uns32 TC1IRQ : 1;
            Uns32 TC2IRQ : 1;
            Uns32 WDIRQ : 1;
            Uns32 PIOIRQ : 1;
            Uns32 __pad9 : 7;
            Uns32 IRQ0 : 1;
            Uns32 IRQ1 : 1;
            Uns32 IRQ2 : 1;
        } bits;
    } AIC_ISCR;
    union { 
        Uns32 value;
    } AIC_EOICR;
    union { 
        Uns32 value;
    } AIC_SPU;
} bp1_REG_dataT, *bp1_REG_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bp1_REG_dataT bp1_REG_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bp1;
    ppmNetHandle          NFIQ;
    ppmNetHandle          NIRQ;
    ppmNetHandle          FIQ;
    ppmNetHandle          SWIRQ;
    ppmNetHandle          US0IRQ;
    ppmNetHandle          US1IRQ;
    ppmNetHandle          TC0IRQ;
    ppmNetHandle          TC1IRQ;
    ppmNetHandle          TC2IRQ;
    ppmNetHandle          WDIRQ;
    ppmNetHandle          PIOIRQ;
    ppmNetHandle          IRQ0;
    ppmNetHandle          IRQ1;
    ppmNetHandle          IRQ2;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(AIC_EOICR_wcb);
PPM_REG_WRITE_CB(AIC_ICCR_wcb);
PPM_REG_WRITE_CB(AIC_IDCR_wcb);
PPM_REG_WRITE_CB(AIC_IECR_wcb);
PPM_REG_WRITE_CB(AIC_ISCR_wcb);
PPM_REG_READ_CB(AIC_IVR_rcb);
PPM_NBYTE_WRITE_CB(AIC_SMR_wcb);
PPM_REG_WRITE_CB(AIC_SPU_wcb);
PPM_NBYTE_WRITE_CB(AIC_SVR_wcb);
PPM_NET_CB(FIQ_wcb);
PPM_NET_CB(IRQ0_wcb);
PPM_NET_CB(IRQ1_wcb);
PPM_NET_CB(IRQ2_wcb);
PPM_NET_CB(PIOIRQ_wcb);
PPM_NET_CB(SWIRQ_wcb);
PPM_NET_CB(TC0IRQ_wcb);
PPM_NET_CB(TC1IRQ_wcb);
PPM_NET_CB(TC2IRQ_wcb);
PPM_NET_CB(US0IRQ_wcb);
PPM_NET_CB(US1IRQ_wcb);
PPM_NET_CB(WDIRQ_wcb);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BP1_REG_AIC_SMR_WIDTH           32
#define BP1_REG_AIC_SVR_WIDTH           32
#define BP1_REG_AIC_IVR_WIDTH           32
#define BP1_REG_AIC_FVR_WIDTH           32
#define BP1_REG_AIC_ISR_WIDTH           32
#define BP1_REG_AIC_IPR_WIDTH           32
#define BP1_REG_AIC_IMR_WIDTH           32
#define BP1_REG_AIC_CISR_WIDTH          32
#define BP1_REG_AIC_IECR_WIDTH          32
#define BP1_REG_AIC_IDCR_WIDTH          32
#define BP1_REG_AIC_ICCR_WIDTH          32
#define BP1_REG_AIC_ISCR_WIDTH          32
#define BP1_REG_AIC_EOICR_WIDTH         32
#define BP1_REG_AIC_SPU_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

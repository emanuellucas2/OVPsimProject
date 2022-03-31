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
            Uns32 CLKEN : 1;
            Uns32 CLKDIS : 1;
            Uns32 SWTRG : 1;
        } bits;
    } TC_CCR0;
    union { 
        Uns32 value;
        struct {
            Uns32 TCCLKS : 3;
            Uns32 CLKI : 1;
            Uns32 BURST : 2;
            Uns32 LDBSTOP : 1;
            Uns32 LDBDIS : 1;
            Uns32 ETRGEDG : 2;
            Uns32 ABETRG : 1;
            Uns32 __pad11 : 3;
            Uns32 CPCTRG : 1;
            Uns32 WAVE : 1;
            Uns32 LDRA : 2;
            Uns32 LDRB : 2;
        } bits;
    } TC_CMR0;
    union { 
        Uns32 value;
        struct {
            Uns32 CV : 16;
        } bits;
    } TC_CVR0;
    union { 
        Uns32 value;
        struct {
            Uns32 RA : 16;
        } bits;
    } TC_RA0;
    union { 
        Uns32 value;
        struct {
            Uns32 RB : 16;
        } bits;
    } TC_RB0;
    union { 
        Uns32 value;
        struct {
            Uns32 RC : 16;
        } bits;
    } TC_RC0;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
            Uns32 __pad8 : 8;
            Uns32 CLKSTA : 1;
            Uns32 MTIOA : 1;
            Uns32 MTIOB : 1;
        } bits;
    } TC_SR0;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
        } bits;
    } TC_IER0;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
        } bits;
    } TC_IDR0;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
        } bits;
    } TC_IMR0;
    union { 
        Uns32 value;
        struct {
            Uns32 CLKEN : 1;
            Uns32 CLKDIS : 1;
            Uns32 SWTRG : 1;
        } bits;
    } TC_CCR1;
    union { 
        Uns32 value;
        struct {
            Uns32 TCCLKS : 3;
            Uns32 CLKI : 1;
            Uns32 BURST : 2;
            Uns32 LDBSTOP : 1;
            Uns32 LDBDIS : 1;
            Uns32 ETRGEDG : 2;
            Uns32 ABETRG : 1;
            Uns32 __pad11 : 3;
            Uns32 CPCTRG : 1;
            Uns32 WAVE : 1;
            Uns32 LDRA : 2;
            Uns32 LDRB : 2;
        } bits;
    } TC_CMR1;
    union { 
        Uns32 value;
        struct {
            Uns32 CV : 16;
        } bits;
    } TC_CVR1;
    union { 
        Uns32 value;
        struct {
            Uns32 RA : 16;
        } bits;
    } TC_RA1;
    union { 
        Uns32 value;
        struct {
            Uns32 RB : 16;
        } bits;
    } TC_RB1;
    union { 
        Uns32 value;
        struct {
            Uns32 RC : 16;
        } bits;
    } TC_RC1;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
            Uns32 __pad8 : 8;
            Uns32 CLKSTA : 1;
            Uns32 MTIOA : 1;
            Uns32 MTIOB : 1;
        } bits;
    } TC_SR1;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
        } bits;
    } TC_IER1;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
        } bits;
    } TC_IDR1;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
        } bits;
    } TC_IMR1;
    union { 
        Uns32 value;
        struct {
            Uns32 CLKEN : 1;
            Uns32 CLKDIS : 1;
            Uns32 SWTRG : 1;
        } bits;
    } TC_CCR2;
    union { 
        Uns32 value;
        struct {
            Uns32 TCCLKS : 3;
            Uns32 CLKI : 1;
            Uns32 BURST : 2;
            Uns32 LDBSTOP : 1;
            Uns32 LDBDIS : 1;
            Uns32 ETRGEDG : 2;
            Uns32 ABETRG : 1;
            Uns32 __pad11 : 3;
            Uns32 CPCTRG : 1;
            Uns32 WAVE : 1;
            Uns32 LDRA : 2;
            Uns32 LDRB : 2;
        } bits;
    } TC_CMR2;
    union { 
        Uns32 value;
        struct {
            Uns32 CV : 16;
        } bits;
    } TC_CVR2;
    union { 
        Uns32 value;
        struct {
            Uns32 RA : 16;
        } bits;
    } TC_RA2;
    union { 
        Uns32 value;
        struct {
            Uns32 RB : 16;
        } bits;
    } TC_RB2;
    union { 
        Uns32 value;
        struct {
            Uns32 RC : 16;
        } bits;
    } TC_RC2;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
            Uns32 __pad8 : 8;
            Uns32 CLKSTA : 1;
            Uns32 MTIOA : 1;
            Uns32 MTIOB : 1;
        } bits;
    } TC_SR2;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
        } bits;
    } TC_IER2;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
        } bits;
    } TC_IDR2;
    union { 
        Uns32 value;
        struct {
            Uns32 COVFS : 1;
            Uns32 LOVRS : 1;
            Uns32 CPAS : 1;
            Uns32 CPBS : 1;
            Uns32 CPCS : 1;
            Uns32 LDRAS : 1;
            Uns32 LDRBS : 1;
            Uns32 ETRGS : 1;
        } bits;
    } TC_IMR2;
    union { 
        Uns32 value;
        struct {
            Uns32 SYNC : 1;
        } bits;
    } TC_BCR;
    union { 
        Uns32 value;
        struct {
            Uns32 TC0X0CS : 2;
            Uns32 TC1X1CS : 2;
            Uns32 TC2X2CS : 2;
        } bits;
    } TC_BMR;
} bp1_REG_dataT, *bp1_REG_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bp1_REG_dataT bp1_REG_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bp1;
    ppmNetHandle          IRQ0;
    ppmNetHandle          IRQ1;
    ppmNetHandle          IRQ2;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(TC_BCR_wcb);
PPM_REG_WRITE_CB(TC_BMR_wcb);
PPM_REG_WRITE_CB(TC_CCR_wcb0);
PPM_REG_WRITE_CB(TC_CCR_wcb1);
PPM_REG_WRITE_CB(TC_CCR_wcb2);
PPM_REG_WRITE_CB(TC_CMR_wcb0);
PPM_REG_WRITE_CB(TC_CMR_wcb1);
PPM_REG_WRITE_CB(TC_CMR_wcb2);
PPM_REG_WRITE_CB(TC_CVR_wcb0);
PPM_REG_WRITE_CB(TC_CVR_wcb1);
PPM_REG_WRITE_CB(TC_CVR_wcb2);
PPM_REG_WRITE_CB(TC_IDR_wcb0);
PPM_REG_WRITE_CB(TC_IDR_wcb1);
PPM_REG_WRITE_CB(TC_IDR_wcb2);
PPM_REG_WRITE_CB(TC_IER_wcb0);
PPM_REG_WRITE_CB(TC_IER_wcb1);
PPM_REG_WRITE_CB(TC_IER_wcb2);
PPM_REG_WRITE_CB(TC_RA_wcb0);
PPM_REG_WRITE_CB(TC_RA_wcb1);
PPM_REG_WRITE_CB(TC_RA_wcb2);
PPM_REG_WRITE_CB(TC_RB_wcb0);
PPM_REG_WRITE_CB(TC_RB_wcb1);
PPM_REG_WRITE_CB(TC_RB_wcb2);
PPM_REG_WRITE_CB(TC_RC_wcb0);
PPM_REG_WRITE_CB(TC_RC_wcb1);
PPM_REG_WRITE_CB(TC_RC_wcb2);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BP1_REG_TC_CCR0_WIDTH           32
#define BP1_REG_TC_CMR0_WIDTH           32
#define BP1_REG_TC_CVR0_WIDTH           32
#define BP1_REG_TC_RA0_WIDTH            32
#define BP1_REG_TC_RB0_WIDTH            32
#define BP1_REG_TC_RC0_WIDTH            32
#define BP1_REG_TC_SR0_WIDTH            32
#define BP1_REG_TC_IER0_WIDTH           32
#define BP1_REG_TC_IDR0_WIDTH           32
#define BP1_REG_TC_IMR0_WIDTH           32
#define BP1_REG_TC_CCR1_WIDTH           32
#define BP1_REG_TC_CMR1_WIDTH           32
#define BP1_REG_TC_CVR1_WIDTH           32
#define BP1_REG_TC_RA1_WIDTH            32
#define BP1_REG_TC_RB1_WIDTH            32
#define BP1_REG_TC_RC1_WIDTH            32
#define BP1_REG_TC_SR1_WIDTH            32
#define BP1_REG_TC_IER1_WIDTH           32
#define BP1_REG_TC_IDR1_WIDTH           32
#define BP1_REG_TC_IMR1_WIDTH           32
#define BP1_REG_TC_CCR2_WIDTH           32
#define BP1_REG_TC_CMR2_WIDTH           32
#define BP1_REG_TC_CVR2_WIDTH           32
#define BP1_REG_TC_RA2_WIDTH            32
#define BP1_REG_TC_RB2_WIDTH            32
#define BP1_REG_TC_RC2_WIDTH            32
#define BP1_REG_TC_SR2_WIDTH            32
#define BP1_REG_TC_IER2_WIDTH           32
#define BP1_REG_TC_IDR2_WIDTH           32
#define BP1_REG_TC_IMR2_WIDTH           32
#define BP1_REG_TC_BCR_WIDTH            32
#define BP1_REG_TC_BMR_WIDTH            32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

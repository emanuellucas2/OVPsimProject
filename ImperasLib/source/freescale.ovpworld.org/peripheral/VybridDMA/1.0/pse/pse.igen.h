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
            Uns32 EEI0 : 1;
            Uns32 EEI1 : 1;
            Uns32 EEI2 : 1;
            Uns32 EEI3 : 1;
            Uns32 EEI4 : 1;
            Uns32 EEI5 : 1;
            Uns32 EEI6 : 1;
            Uns32 EEI7 : 1;
            Uns32 EEI8 : 1;
            Uns32 EEI9 : 1;
            Uns32 EEI10 : 1;
            Uns32 EEI11 : 1;
            Uns32 EEI12 : 1;
            Uns32 EEI13 : 1;
            Uns32 EEI14 : 1;
            Uns32 EEI15 : 1;
            Uns32 EEI16 : 1;
            Uns32 EEI17 : 1;
            Uns32 EEI18 : 1;
            Uns32 EEI19 : 1;
            Uns32 EEI20 : 1;
            Uns32 EEI21 : 1;
            Uns32 EEI22 : 1;
            Uns32 EEI23 : 1;
            Uns32 EEI24 : 1;
            Uns32 EEI25 : 1;
            Uns32 EEI26 : 1;
            Uns32 EEI27 : 1;
            Uns32 EEI28 : 1;
            Uns32 EEI29 : 1;
            Uns32 EEI30 : 1;
            Uns32 EEI31 : 1;
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
        struct {
            Uns32 EDREQ_0 : 1;
            Uns32 EDREQ_1 : 1;
            Uns32 EDREQ_2 : 1;
            Uns32 EDREQ_3 : 1;
            Uns32 EDREQ_4 : 1;
            Uns32 EDREQ_5 : 1;
            Uns32 EDREQ_6 : 1;
            Uns32 EDREQ_7 : 1;
            Uns32 EDREQ_8 : 1;
            Uns32 EDREQ_9 : 1;
            Uns32 EDREQ_10 : 1;
            Uns32 EDREQ_11 : 1;
            Uns32 EDREQ_12 : 1;
            Uns32 EDREQ_13 : 1;
            Uns32 EDREQ_14 : 1;
            Uns32 EDREQ_15 : 1;
            Uns32 EDREQ_16 : 1;
            Uns32 EDREQ_17 : 1;
            Uns32 EDREQ_18 : 1;
            Uns32 EDREQ_19 : 1;
            Uns32 EDREQ_20 : 1;
            Uns32 EDREQ_21 : 1;
            Uns32 EDREQ_22 : 1;
            Uns32 EDREQ_23 : 1;
            Uns32 EDREQ_24 : 1;
            Uns32 EDREQ_25 : 1;
            Uns32 EDREQ_26 : 1;
            Uns32 EDREQ_27 : 1;
            Uns32 EDREQ_28 : 1;
            Uns32 EDREQ_29 : 1;
            Uns32 EDREQ_30 : 1;
            Uns32 EDREQ_31 : 1;
        } bits;
    } EARS;
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
    union { 
        Uns32 value;
    } TCD0_SADDR;
    union { 
        Uns32 value;
    } TCD0_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD0_NBYTES;
    union { 
        Uns32 value;
    } TCD0_SLAST;
    union { 
        Uns32 value;
    } TCD0_DADDR;
    union { 
        Uns32 value;
    } TCD0_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD0_DLASTSGA;
    union { 
        Uns32 value;
    } TCD0_CSR_BITER;
    union { 
        Uns32 value;
    } TCD1_SADDR;
    union { 
        Uns32 value;
    } TCD1_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD1_NBYTES;
    union { 
        Uns32 value;
    } TCD1_SLAST;
    union { 
        Uns32 value;
    } TCD1_DADDR;
    union { 
        Uns32 value;
    } TCD1_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD1_DLASTSGA;
    union { 
        Uns32 value;
    } TCD1_CSR_BITER;
    union { 
        Uns32 value;
    } TCD2_SADDR;
    union { 
        Uns32 value;
    } TCD2_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD2_NBYTES;
    union { 
        Uns32 value;
    } TCD2_SLAST;
    union { 
        Uns32 value;
    } TCD2_DADDR;
    union { 
        Uns32 value;
    } TCD2_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD2_DLASTSGA;
    union { 
        Uns32 value;
    } TCD2_CSR_BITER;
    union { 
        Uns32 value;
    } TCD3_SADDR;
    union { 
        Uns32 value;
    } TCD3_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD3_NBYTES;
    union { 
        Uns32 value;
    } TCD3_SLAST;
    union { 
        Uns32 value;
    } TCD3_DADDR;
    union { 
        Uns32 value;
    } TCD3_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD3_DLASTSGA;
    union { 
        Uns32 value;
    } TCD3_CSR_BITER;
    union { 
        Uns32 value;
    } TCD4_SADDR;
    union { 
        Uns32 value;
    } TCD4_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD4_NBYTES;
    union { 
        Uns32 value;
    } TCD4_SLAST;
    union { 
        Uns32 value;
    } TCD4_DADDR;
    union { 
        Uns32 value;
    } TCD4_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD4_DLASTSGA;
    union { 
        Uns32 value;
    } TCD4_CSR_BITER;
    union { 
        Uns32 value;
    } TCD5_SADDR;
    union { 
        Uns32 value;
    } TCD5_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD5_NBYTES;
    union { 
        Uns32 value;
    } TCD5_SLAST;
    union { 
        Uns32 value;
    } TCD5_DADDR;
    union { 
        Uns32 value;
    } TCD5_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD5_DLASTSGA;
    union { 
        Uns32 value;
    } TCD5_CSR_BITER;
    union { 
        Uns32 value;
    } TCD6_SADDR;
    union { 
        Uns32 value;
    } TCD6_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD6_NBYTES;
    union { 
        Uns32 value;
    } TCD6_SLAST;
    union { 
        Uns32 value;
    } TCD6_DADDR;
    union { 
        Uns32 value;
    } TCD6_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD6_DLASTSGA;
    union { 
        Uns32 value;
    } TCD6_CSR_BITER;
    union { 
        Uns32 value;
    } TCD7_SADDR;
    union { 
        Uns32 value;
    } TCD7_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD7_NBYTES;
    union { 
        Uns32 value;
    } TCD7_SLAST;
    union { 
        Uns32 value;
    } TCD7_DADDR;
    union { 
        Uns32 value;
    } TCD7_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD7_DLASTSGA;
    union { 
        Uns32 value;
    } TCD7_CSR_BITER;
    union { 
        Uns32 value;
    } TCD8_SADDR;
    union { 
        Uns32 value;
    } TCD8_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD8_NBYTES;
    union { 
        Uns32 value;
    } TCD8_SLAST;
    union { 
        Uns32 value;
    } TCD8_DADDR;
    union { 
        Uns32 value;
    } TCD8_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD8_DLASTSGA;
    union { 
        Uns32 value;
    } TCD8_CSR_BITER;
    union { 
        Uns32 value;
    } TCD9_SADDR;
    union { 
        Uns32 value;
    } TCD9_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD9_NBYTES;
    union { 
        Uns32 value;
    } TCD9_SLAST;
    union { 
        Uns32 value;
    } TCD9_DADDR;
    union { 
        Uns32 value;
    } TCD9_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD9_DLASTSGA;
    union { 
        Uns32 value;
    } TCD9_CSR_BITER;
    union { 
        Uns32 value;
    } TCD10_SADDR;
    union { 
        Uns32 value;
    } TCD10_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD10_NBYTES;
    union { 
        Uns32 value;
    } TCD10_SLAST;
    union { 
        Uns32 value;
    } TCD10_DADDR;
    union { 
        Uns32 value;
    } TCD10_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD10_DLASTSGA;
    union { 
        Uns32 value;
    } TCD10_CSR_BITER;
    union { 
        Uns32 value;
    } TCD11_SADDR;
    union { 
        Uns32 value;
    } TCD11_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD11_NBYTES;
    union { 
        Uns32 value;
    } TCD11_SLAST;
    union { 
        Uns32 value;
    } TCD11_DADDR;
    union { 
        Uns32 value;
    } TCD11_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD11_DLASTSGA;
    union { 
        Uns32 value;
    } TCD11_CSR_BITER;
    union { 
        Uns32 value;
    } TCD12_SADDR;
    union { 
        Uns32 value;
    } TCD12_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD12_NBYTES;
    union { 
        Uns32 value;
    } TCD12_SLAST;
    union { 
        Uns32 value;
    } TCD12_DADDR;
    union { 
        Uns32 value;
    } TCD12_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD12_DLASTSGA;
    union { 
        Uns32 value;
    } TCD12_CSR_BITER;
    union { 
        Uns32 value;
    } TCD13_SADDR;
    union { 
        Uns32 value;
    } TCD13_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD13_NBYTES;
    union { 
        Uns32 value;
    } TCD13_SLAST;
    union { 
        Uns32 value;
    } TCD13_DADDR;
    union { 
        Uns32 value;
    } TCD13_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD13_DLASTSGA;
    union { 
        Uns32 value;
    } TCD13_CSR_BITER;
    union { 
        Uns32 value;
    } TCD14_SADDR;
    union { 
        Uns32 value;
    } TCD14_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD14_NBYTES;
    union { 
        Uns32 value;
    } TCD14_SLAST;
    union { 
        Uns32 value;
    } TCD14_DADDR;
    union { 
        Uns32 value;
    } TCD14_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD14_DLASTSGA;
    union { 
        Uns32 value;
    } TCD14_CSR_BITER;
    union { 
        Uns32 value;
    } TCD15_SADDR;
    union { 
        Uns32 value;
    } TCD15_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD15_NBYTES;
    union { 
        Uns32 value;
    } TCD15_SLAST;
    union { 
        Uns32 value;
    } TCD15_DADDR;
    union { 
        Uns32 value;
    } TCD15_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD15_DLASTSGA;
    union { 
        Uns32 value;
    } TCD15_CSR_BITER;
    union { 
        Uns32 value;
    } TCD16_SADDR;
    union { 
        Uns32 value;
    } TCD16_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD16_NBYTES;
    union { 
        Uns32 value;
    } TCD16_SLAST;
    union { 
        Uns32 value;
    } TCD16_DADDR;
    union { 
        Uns32 value;
    } TCD16_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD16_DLASTSGA;
    union { 
        Uns32 value;
    } TCD16_CSR_BITER;
    union { 
        Uns32 value;
    } TCD17_SADDR;
    union { 
        Uns32 value;
    } TCD17_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD17_NBYTES;
    union { 
        Uns32 value;
    } TCD17_SLAST;
    union { 
        Uns32 value;
    } TCD17_DADDR;
    union { 
        Uns32 value;
    } TCD17_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD17_DLASTSGA;
    union { 
        Uns32 value;
    } TCD17_CSR_BITER;
    union { 
        Uns32 value;
    } TCD18_SADDR;
    union { 
        Uns32 value;
    } TCD18_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD18_NBYTES;
    union { 
        Uns32 value;
    } TCD18_SLAST;
    union { 
        Uns32 value;
    } TCD18_DADDR;
    union { 
        Uns32 value;
    } TCD18_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD18_DLASTSGA;
    union { 
        Uns32 value;
    } TCD18_CSR_BITER;
    union { 
        Uns32 value;
    } TCD19_SADDR;
    union { 
        Uns32 value;
    } TCD19_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD19_NBYTES;
    union { 
        Uns32 value;
    } TCD19_SLAST;
    union { 
        Uns32 value;
    } TCD19_DADDR;
    union { 
        Uns32 value;
    } TCD19_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD19_DLASTSGA;
    union { 
        Uns32 value;
    } TCD19_CSR_BITER;
    union { 
        Uns32 value;
    } TCD20_SADDR;
    union { 
        Uns32 value;
    } TCD20_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD20_NBYTES;
    union { 
        Uns32 value;
    } TCD20_SLAST;
    union { 
        Uns32 value;
    } TCD20_DADDR;
    union { 
        Uns32 value;
    } TCD20_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD20_DLASTSGA;
    union { 
        Uns32 value;
    } TCD20_CSR_BITER;
    union { 
        Uns32 value;
    } TCD21_SADDR;
    union { 
        Uns32 value;
    } TCD21_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD21_NBYTES;
    union { 
        Uns32 value;
    } TCD21_SLAST;
    union { 
        Uns32 value;
    } TCD21_DADDR;
    union { 
        Uns32 value;
    } TCD21_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD21_DLASTSGA;
    union { 
        Uns32 value;
    } TCD21_CSR_BITER;
    union { 
        Uns32 value;
    } TCD22_SADDR;
    union { 
        Uns32 value;
    } TCD22_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD22_NBYTES;
    union { 
        Uns32 value;
    } TCD22_SLAST;
    union { 
        Uns32 value;
    } TCD22_DADDR;
    union { 
        Uns32 value;
    } TCD22_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD22_DLASTSGA;
    union { 
        Uns32 value;
    } TCD22_CSR_BITER;
    union { 
        Uns32 value;
    } TCD23_SADDR;
    union { 
        Uns32 value;
    } TCD23_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD23_NBYTES;
    union { 
        Uns32 value;
    } TCD23_SLAST;
    union { 
        Uns32 value;
    } TCD23_DADDR;
    union { 
        Uns32 value;
    } TCD23_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD23_DLASTSGA;
    union { 
        Uns32 value;
    } TCD23_CSR_BITER;
    union { 
        Uns32 value;
    } TCD24_SADDR;
    union { 
        Uns32 value;
    } TCD24_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD24_NBYTES;
    union { 
        Uns32 value;
    } TCD24_SLAST;
    union { 
        Uns32 value;
    } TCD24_DADDR;
    union { 
        Uns32 value;
    } TCD24_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD24_DLASTSGA;
    union { 
        Uns32 value;
    } TCD24_CSR_BITER;
    union { 
        Uns32 value;
    } TCD25_SADDR;
    union { 
        Uns32 value;
    } TCD25_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD25_NBYTES;
    union { 
        Uns32 value;
    } TCD25_SLAST;
    union { 
        Uns32 value;
    } TCD25_DADDR;
    union { 
        Uns32 value;
    } TCD25_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD25_DLASTSGA;
    union { 
        Uns32 value;
    } TCD25_CSR_BITER;
    union { 
        Uns32 value;
    } TCD26_SADDR;
    union { 
        Uns32 value;
    } TCD26_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD26_NBYTES;
    union { 
        Uns32 value;
    } TCD26_SLAST;
    union { 
        Uns32 value;
    } TCD26_DADDR;
    union { 
        Uns32 value;
    } TCD26_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD26_DLASTSGA;
    union { 
        Uns32 value;
    } TCD26_CSR_BITER;
    union { 
        Uns32 value;
    } TCD27_SADDR;
    union { 
        Uns32 value;
    } TCD27_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD27_NBYTES;
    union { 
        Uns32 value;
    } TCD27_SLAST;
    union { 
        Uns32 value;
    } TCD27_DADDR;
    union { 
        Uns32 value;
    } TCD27_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD27_DLASTSGA;
    union { 
        Uns32 value;
    } TCD27_CSR_BITER;
    union { 
        Uns32 value;
    } TCD28_SADDR;
    union { 
        Uns32 value;
    } TCD28_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD28_NBYTES;
    union { 
        Uns32 value;
    } TCD28_SLAST;
    union { 
        Uns32 value;
    } TCD28_DADDR;
    union { 
        Uns32 value;
    } TCD28_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD28_DLASTSGA;
    union { 
        Uns32 value;
    } TCD28_CSR_BITER;
    union { 
        Uns32 value;
    } TCD29_SADDR;
    union { 
        Uns32 value;
    } TCD29_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD29_NBYTES;
    union { 
        Uns32 value;
    } TCD29_SLAST;
    union { 
        Uns32 value;
    } TCD29_DADDR;
    union { 
        Uns32 value;
    } TCD29_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD29_DLASTSGA;
    union { 
        Uns32 value;
    } TCD29_CSR_BITER;
    union { 
        Uns32 value;
    } TCD30_SADDR;
    union { 
        Uns32 value;
    } TCD30_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD30_NBYTES;
    union { 
        Uns32 value;
    } TCD30_SLAST;
    union { 
        Uns32 value;
    } TCD30_DADDR;
    union { 
        Uns32 value;
    } TCD30_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD30_DLASTSGA;
    union { 
        Uns32 value;
    } TCD30_CSR_BITER;
    union { 
        Uns32 value;
    } TCD31_SADDR;
    union { 
        Uns32 value;
    } TCD31_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD31_NBYTES;
    union { 
        Uns32 value;
    } TCD31_SLAST;
    union { 
        Uns32 value;
    } TCD31_DADDR;
    union { 
        Uns32 value;
    } TCD31_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD31_DLASTSGA;
    union { 
        Uns32 value;
    } TCD31_CSR_BITER;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

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
PPM_REG_READ_CB(regReadTCD);
PPM_REG_READ_CB(regReadTCD16);
PPM_REG_READ_CB(regReadZero);
PPM_REG_WRITE_CB(regSetGroup);
PPM_REG_WRITE_CB(regWrite1c);
PPM_REG_WRITE_CB(regWrite32);
PPM_REG_WRITE_CB(regWriteCHPRI);
PPM_REG_WRITE_CB(regWriteCR);
PPM_REG_WRITE_CB(regWriteTCD);
PPM_REG_WRITE_CB(regWriteTCD16);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_CR_WRMASK             0x305fe
#define BPORT1_AB_CR_WRNMASK            (0xfffcfa01)
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
#define BPORT1_AB_EARS_WRMASK           0xffffffff
#define BPORT1_AB_EARS_WRNMASK          (0x0)
#define BPORT1_AB_EARS_WIDTH            32
#define BPORT1_AB_DCHPRI3_0_WRMASK      0xcfcfcfcf
#define BPORT1_AB_DCHPRI3_0_WRNMASK     (0x30303030)
#define BPORT1_AB_DCHPRI3_0_WIDTH       32
#define BPORT1_AB_DCHPRI7_4_WRMASK      0xcfcfcfcf
#define BPORT1_AB_DCHPRI7_4_WRNMASK     (0x30303030)
#define BPORT1_AB_DCHPRI7_4_WIDTH       32
#define BPORT1_AB_DCHPRI11_8_WRMASK     0xcfcfcfcf
#define BPORT1_AB_DCHPRI11_8_WRNMASK    (0x30303030)
#define BPORT1_AB_DCHPRI11_8_WIDTH      32
#define BPORT1_AB_DCHPRI15_12_WRMASK    0xcfcfcfcf
#define BPORT1_AB_DCHPRI15_12_WRNMASK   (0x30303030)
#define BPORT1_AB_DCHPRI15_12_WIDTH     32
#define BPORT1_AB_DCHPRI19_16_WRMASK    0xcfcfcfcf
#define BPORT1_AB_DCHPRI19_16_WRNMASK   (0x30303030)
#define BPORT1_AB_DCHPRI19_16_WIDTH     32
#define BPORT1_AB_DCHPRI23_20_WRMASK    0xcfcfcfcf
#define BPORT1_AB_DCHPRI23_20_WRNMASK   (0x30303030)
#define BPORT1_AB_DCHPRI23_20_WIDTH     32
#define BPORT1_AB_DCHPRI27_24_WRMASK    0xcfcfcfcf
#define BPORT1_AB_DCHPRI27_24_WRNMASK   (0x30303030)
#define BPORT1_AB_DCHPRI27_24_WIDTH     32
#define BPORT1_AB_DCHPRI31_28_WRMASK    0xcfcfcfcf
#define BPORT1_AB_DCHPRI31_28_WRNMASK   (0x30303030)
#define BPORT1_AB_DCHPRI31_28_WIDTH     32
#define BPORT1_AB_TCD0_SADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD0_SADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD0_SADDR_WIDTH      32
#define BPORT1_AB_TCD0_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD0_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD0_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD0_NBYTES_WRMASK    0xffffffff
#define BPORT1_AB_TCD0_NBYTES_WRNMASK   (0x0)
#define BPORT1_AB_TCD0_NBYTES_WIDTH     32
#define BPORT1_AB_TCD0_SLAST_WRMASK     0xffffffff
#define BPORT1_AB_TCD0_SLAST_WRNMASK    (0x0)
#define BPORT1_AB_TCD0_SLAST_WIDTH      32
#define BPORT1_AB_TCD0_DADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD0_DADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD0_DADDR_WIDTH      32
#define BPORT1_AB_TCD0_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD0_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD0_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD0_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD0_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD0_DLASTSGA_WIDTH   32
#define BPORT1_AB_TCD0_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD0_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD0_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD1_SADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD1_SADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD1_SADDR_WIDTH      32
#define BPORT1_AB_TCD1_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD1_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD1_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD1_NBYTES_WRMASK    0xffffffff
#define BPORT1_AB_TCD1_NBYTES_WRNMASK   (0x0)
#define BPORT1_AB_TCD1_NBYTES_WIDTH     32
#define BPORT1_AB_TCD1_SLAST_WRMASK     0xffffffff
#define BPORT1_AB_TCD1_SLAST_WRNMASK    (0x0)
#define BPORT1_AB_TCD1_SLAST_WIDTH      32
#define BPORT1_AB_TCD1_DADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD1_DADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD1_DADDR_WIDTH      32
#define BPORT1_AB_TCD1_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD1_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD1_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD1_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD1_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD1_DLASTSGA_WIDTH   32
#define BPORT1_AB_TCD1_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD1_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD1_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD2_SADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD2_SADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD2_SADDR_WIDTH      32
#define BPORT1_AB_TCD2_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD2_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD2_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD2_NBYTES_WRMASK    0xffffffff
#define BPORT1_AB_TCD2_NBYTES_WRNMASK   (0x0)
#define BPORT1_AB_TCD2_NBYTES_WIDTH     32
#define BPORT1_AB_TCD2_SLAST_WRMASK     0xffffffff
#define BPORT1_AB_TCD2_SLAST_WRNMASK    (0x0)
#define BPORT1_AB_TCD2_SLAST_WIDTH      32
#define BPORT1_AB_TCD2_DADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD2_DADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD2_DADDR_WIDTH      32
#define BPORT1_AB_TCD2_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD2_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD2_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD2_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD2_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD2_DLASTSGA_WIDTH   32
#define BPORT1_AB_TCD2_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD2_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD2_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD3_SADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD3_SADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD3_SADDR_WIDTH      32
#define BPORT1_AB_TCD3_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD3_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD3_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD3_NBYTES_WRMASK    0xffffffff
#define BPORT1_AB_TCD3_NBYTES_WRNMASK   (0x0)
#define BPORT1_AB_TCD3_NBYTES_WIDTH     32
#define BPORT1_AB_TCD3_SLAST_WRMASK     0xffffffff
#define BPORT1_AB_TCD3_SLAST_WRNMASK    (0x0)
#define BPORT1_AB_TCD3_SLAST_WIDTH      32
#define BPORT1_AB_TCD3_DADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD3_DADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD3_DADDR_WIDTH      32
#define BPORT1_AB_TCD3_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD3_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD3_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD3_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD3_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD3_DLASTSGA_WIDTH   32
#define BPORT1_AB_TCD3_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD3_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD3_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD4_SADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD4_SADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD4_SADDR_WIDTH      32
#define BPORT1_AB_TCD4_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD4_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD4_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD4_NBYTES_WRMASK    0xffffffff
#define BPORT1_AB_TCD4_NBYTES_WRNMASK   (0x0)
#define BPORT1_AB_TCD4_NBYTES_WIDTH     32
#define BPORT1_AB_TCD4_SLAST_WRMASK     0xffffffff
#define BPORT1_AB_TCD4_SLAST_WRNMASK    (0x0)
#define BPORT1_AB_TCD4_SLAST_WIDTH      32
#define BPORT1_AB_TCD4_DADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD4_DADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD4_DADDR_WIDTH      32
#define BPORT1_AB_TCD4_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD4_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD4_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD4_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD4_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD4_DLASTSGA_WIDTH   32
#define BPORT1_AB_TCD4_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD4_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD4_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD5_SADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD5_SADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD5_SADDR_WIDTH      32
#define BPORT1_AB_TCD5_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD5_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD5_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD5_NBYTES_WRMASK    0xffffffff
#define BPORT1_AB_TCD5_NBYTES_WRNMASK   (0x0)
#define BPORT1_AB_TCD5_NBYTES_WIDTH     32
#define BPORT1_AB_TCD5_SLAST_WRMASK     0xffffffff
#define BPORT1_AB_TCD5_SLAST_WRNMASK    (0x0)
#define BPORT1_AB_TCD5_SLAST_WIDTH      32
#define BPORT1_AB_TCD5_DADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD5_DADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD5_DADDR_WIDTH      32
#define BPORT1_AB_TCD5_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD5_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD5_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD5_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD5_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD5_DLASTSGA_WIDTH   32
#define BPORT1_AB_TCD5_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD5_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD5_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD6_SADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD6_SADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD6_SADDR_WIDTH      32
#define BPORT1_AB_TCD6_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD6_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD6_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD6_NBYTES_WRMASK    0xffffffff
#define BPORT1_AB_TCD6_NBYTES_WRNMASK   (0x0)
#define BPORT1_AB_TCD6_NBYTES_WIDTH     32
#define BPORT1_AB_TCD6_SLAST_WRMASK     0xffffffff
#define BPORT1_AB_TCD6_SLAST_WRNMASK    (0x0)
#define BPORT1_AB_TCD6_SLAST_WIDTH      32
#define BPORT1_AB_TCD6_DADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD6_DADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD6_DADDR_WIDTH      32
#define BPORT1_AB_TCD6_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD6_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD6_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD6_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD6_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD6_DLASTSGA_WIDTH   32
#define BPORT1_AB_TCD6_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD6_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD6_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD7_SADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD7_SADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD7_SADDR_WIDTH      32
#define BPORT1_AB_TCD7_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD7_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD7_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD7_NBYTES_WRMASK    0xffffffff
#define BPORT1_AB_TCD7_NBYTES_WRNMASK   (0x0)
#define BPORT1_AB_TCD7_NBYTES_WIDTH     32
#define BPORT1_AB_TCD7_SLAST_WRMASK     0xffffffff
#define BPORT1_AB_TCD7_SLAST_WRNMASK    (0x0)
#define BPORT1_AB_TCD7_SLAST_WIDTH      32
#define BPORT1_AB_TCD7_DADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD7_DADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD7_DADDR_WIDTH      32
#define BPORT1_AB_TCD7_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD7_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD7_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD7_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD7_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD7_DLASTSGA_WIDTH   32
#define BPORT1_AB_TCD7_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD7_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD7_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD8_SADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD8_SADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD8_SADDR_WIDTH      32
#define BPORT1_AB_TCD8_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD8_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD8_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD8_NBYTES_WRMASK    0xffffffff
#define BPORT1_AB_TCD8_NBYTES_WRNMASK   (0x0)
#define BPORT1_AB_TCD8_NBYTES_WIDTH     32
#define BPORT1_AB_TCD8_SLAST_WRMASK     0xffffffff
#define BPORT1_AB_TCD8_SLAST_WRNMASK    (0x0)
#define BPORT1_AB_TCD8_SLAST_WIDTH      32
#define BPORT1_AB_TCD8_DADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD8_DADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD8_DADDR_WIDTH      32
#define BPORT1_AB_TCD8_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD8_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD8_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD8_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD8_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD8_DLASTSGA_WIDTH   32
#define BPORT1_AB_TCD8_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD8_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD8_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD9_SADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD9_SADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD9_SADDR_WIDTH      32
#define BPORT1_AB_TCD9_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD9_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD9_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD9_NBYTES_WRMASK    0xffffffff
#define BPORT1_AB_TCD9_NBYTES_WRNMASK   (0x0)
#define BPORT1_AB_TCD9_NBYTES_WIDTH     32
#define BPORT1_AB_TCD9_SLAST_WRMASK     0xffffffff
#define BPORT1_AB_TCD9_SLAST_WRNMASK    (0x0)
#define BPORT1_AB_TCD9_SLAST_WIDTH      32
#define BPORT1_AB_TCD9_DADDR_WRMASK     0xffffffff
#define BPORT1_AB_TCD9_DADDR_WRNMASK    (0x0)
#define BPORT1_AB_TCD9_DADDR_WIDTH      32
#define BPORT1_AB_TCD9_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD9_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD9_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD9_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD9_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD9_DLASTSGA_WIDTH   32
#define BPORT1_AB_TCD9_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD9_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD9_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD10_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD10_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD10_SADDR_WIDTH     32
#define BPORT1_AB_TCD10_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD10_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD10_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD10_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD10_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD10_NBYTES_WIDTH    32
#define BPORT1_AB_TCD10_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD10_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD10_SLAST_WIDTH     32
#define BPORT1_AB_TCD10_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD10_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD10_DADDR_WIDTH     32
#define BPORT1_AB_TCD10_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD10_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD10_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD10_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD10_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD10_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD10_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD10_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD10_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD11_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD11_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD11_SADDR_WIDTH     32
#define BPORT1_AB_TCD11_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD11_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD11_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD11_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD11_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD11_NBYTES_WIDTH    32
#define BPORT1_AB_TCD11_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD11_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD11_SLAST_WIDTH     32
#define BPORT1_AB_TCD11_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD11_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD11_DADDR_WIDTH     32
#define BPORT1_AB_TCD11_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD11_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD11_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD11_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD11_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD11_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD11_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD11_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD11_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD12_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD12_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD12_SADDR_WIDTH     32
#define BPORT1_AB_TCD12_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD12_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD12_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD12_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD12_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD12_NBYTES_WIDTH    32
#define BPORT1_AB_TCD12_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD12_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD12_SLAST_WIDTH     32
#define BPORT1_AB_TCD12_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD12_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD12_DADDR_WIDTH     32
#define BPORT1_AB_TCD12_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD12_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD12_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD12_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD12_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD12_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD12_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD12_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD12_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD13_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD13_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD13_SADDR_WIDTH     32
#define BPORT1_AB_TCD13_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD13_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD13_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD13_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD13_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD13_NBYTES_WIDTH    32
#define BPORT1_AB_TCD13_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD13_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD13_SLAST_WIDTH     32
#define BPORT1_AB_TCD13_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD13_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD13_DADDR_WIDTH     32
#define BPORT1_AB_TCD13_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD13_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD13_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD13_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD13_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD13_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD13_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD13_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD13_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD14_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD14_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD14_SADDR_WIDTH     32
#define BPORT1_AB_TCD14_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD14_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD14_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD14_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD14_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD14_NBYTES_WIDTH    32
#define BPORT1_AB_TCD14_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD14_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD14_SLAST_WIDTH     32
#define BPORT1_AB_TCD14_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD14_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD14_DADDR_WIDTH     32
#define BPORT1_AB_TCD14_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD14_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD14_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD14_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD14_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD14_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD14_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD14_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD14_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD15_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD15_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD15_SADDR_WIDTH     32
#define BPORT1_AB_TCD15_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD15_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD15_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD15_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD15_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD15_NBYTES_WIDTH    32
#define BPORT1_AB_TCD15_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD15_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD15_SLAST_WIDTH     32
#define BPORT1_AB_TCD15_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD15_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD15_DADDR_WIDTH     32
#define BPORT1_AB_TCD15_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD15_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD15_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD15_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD15_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD15_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD15_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD15_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD15_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD16_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD16_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD16_SADDR_WIDTH     32
#define BPORT1_AB_TCD16_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD16_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD16_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD16_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD16_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD16_NBYTES_WIDTH    32
#define BPORT1_AB_TCD16_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD16_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD16_SLAST_WIDTH     32
#define BPORT1_AB_TCD16_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD16_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD16_DADDR_WIDTH     32
#define BPORT1_AB_TCD16_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD16_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD16_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD16_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD16_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD16_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD16_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD16_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD16_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD17_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD17_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD17_SADDR_WIDTH     32
#define BPORT1_AB_TCD17_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD17_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD17_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD17_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD17_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD17_NBYTES_WIDTH    32
#define BPORT1_AB_TCD17_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD17_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD17_SLAST_WIDTH     32
#define BPORT1_AB_TCD17_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD17_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD17_DADDR_WIDTH     32
#define BPORT1_AB_TCD17_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD17_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD17_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD17_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD17_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD17_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD17_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD17_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD17_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD18_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD18_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD18_SADDR_WIDTH     32
#define BPORT1_AB_TCD18_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD18_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD18_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD18_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD18_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD18_NBYTES_WIDTH    32
#define BPORT1_AB_TCD18_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD18_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD18_SLAST_WIDTH     32
#define BPORT1_AB_TCD18_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD18_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD18_DADDR_WIDTH     32
#define BPORT1_AB_TCD18_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD18_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD18_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD18_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD18_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD18_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD18_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD18_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD18_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD19_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD19_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD19_SADDR_WIDTH     32
#define BPORT1_AB_TCD19_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD19_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD19_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD19_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD19_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD19_NBYTES_WIDTH    32
#define BPORT1_AB_TCD19_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD19_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD19_SLAST_WIDTH     32
#define BPORT1_AB_TCD19_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD19_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD19_DADDR_WIDTH     32
#define BPORT1_AB_TCD19_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD19_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD19_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD19_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD19_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD19_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD19_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD19_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD19_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD20_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD20_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD20_SADDR_WIDTH     32
#define BPORT1_AB_TCD20_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD20_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD20_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD20_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD20_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD20_NBYTES_WIDTH    32
#define BPORT1_AB_TCD20_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD20_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD20_SLAST_WIDTH     32
#define BPORT1_AB_TCD20_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD20_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD20_DADDR_WIDTH     32
#define BPORT1_AB_TCD20_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD20_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD20_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD20_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD20_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD20_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD20_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD20_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD20_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD21_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD21_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD21_SADDR_WIDTH     32
#define BPORT1_AB_TCD21_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD21_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD21_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD21_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD21_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD21_NBYTES_WIDTH    32
#define BPORT1_AB_TCD21_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD21_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD21_SLAST_WIDTH     32
#define BPORT1_AB_TCD21_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD21_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD21_DADDR_WIDTH     32
#define BPORT1_AB_TCD21_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD21_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD21_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD21_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD21_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD21_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD21_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD21_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD21_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD22_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD22_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD22_SADDR_WIDTH     32
#define BPORT1_AB_TCD22_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD22_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD22_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD22_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD22_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD22_NBYTES_WIDTH    32
#define BPORT1_AB_TCD22_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD22_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD22_SLAST_WIDTH     32
#define BPORT1_AB_TCD22_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD22_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD22_DADDR_WIDTH     32
#define BPORT1_AB_TCD22_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD22_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD22_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD22_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD22_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD22_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD22_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD22_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD22_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD23_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD23_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD23_SADDR_WIDTH     32
#define BPORT1_AB_TCD23_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD23_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD23_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD23_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD23_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD23_NBYTES_WIDTH    32
#define BPORT1_AB_TCD23_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD23_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD23_SLAST_WIDTH     32
#define BPORT1_AB_TCD23_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD23_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD23_DADDR_WIDTH     32
#define BPORT1_AB_TCD23_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD23_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD23_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD23_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD23_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD23_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD23_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD23_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD23_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD24_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD24_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD24_SADDR_WIDTH     32
#define BPORT1_AB_TCD24_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD24_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD24_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD24_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD24_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD24_NBYTES_WIDTH    32
#define BPORT1_AB_TCD24_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD24_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD24_SLAST_WIDTH     32
#define BPORT1_AB_TCD24_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD24_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD24_DADDR_WIDTH     32
#define BPORT1_AB_TCD24_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD24_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD24_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD24_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD24_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD24_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD24_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD24_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD24_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD25_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD25_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD25_SADDR_WIDTH     32
#define BPORT1_AB_TCD25_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD25_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD25_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD25_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD25_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD25_NBYTES_WIDTH    32
#define BPORT1_AB_TCD25_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD25_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD25_SLAST_WIDTH     32
#define BPORT1_AB_TCD25_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD25_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD25_DADDR_WIDTH     32
#define BPORT1_AB_TCD25_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD25_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD25_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD25_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD25_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD25_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD25_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD25_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD25_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD26_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD26_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD26_SADDR_WIDTH     32
#define BPORT1_AB_TCD26_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD26_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD26_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD26_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD26_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD26_NBYTES_WIDTH    32
#define BPORT1_AB_TCD26_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD26_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD26_SLAST_WIDTH     32
#define BPORT1_AB_TCD26_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD26_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD26_DADDR_WIDTH     32
#define BPORT1_AB_TCD26_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD26_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD26_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD26_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD26_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD26_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD26_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD26_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD26_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD27_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD27_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD27_SADDR_WIDTH     32
#define BPORT1_AB_TCD27_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD27_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD27_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD27_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD27_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD27_NBYTES_WIDTH    32
#define BPORT1_AB_TCD27_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD27_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD27_SLAST_WIDTH     32
#define BPORT1_AB_TCD27_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD27_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD27_DADDR_WIDTH     32
#define BPORT1_AB_TCD27_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD27_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD27_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD27_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD27_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD27_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD27_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD27_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD27_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD28_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD28_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD28_SADDR_WIDTH     32
#define BPORT1_AB_TCD28_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD28_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD28_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD28_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD28_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD28_NBYTES_WIDTH    32
#define BPORT1_AB_TCD28_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD28_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD28_SLAST_WIDTH     32
#define BPORT1_AB_TCD28_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD28_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD28_DADDR_WIDTH     32
#define BPORT1_AB_TCD28_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD28_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD28_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD28_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD28_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD28_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD28_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD28_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD28_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD29_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD29_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD29_SADDR_WIDTH     32
#define BPORT1_AB_TCD29_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD29_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD29_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD29_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD29_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD29_NBYTES_WIDTH    32
#define BPORT1_AB_TCD29_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD29_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD29_SLAST_WIDTH     32
#define BPORT1_AB_TCD29_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD29_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD29_DADDR_WIDTH     32
#define BPORT1_AB_TCD29_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD29_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD29_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD29_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD29_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD29_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD29_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD29_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD29_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD30_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD30_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD30_SADDR_WIDTH     32
#define BPORT1_AB_TCD30_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD30_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD30_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD30_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD30_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD30_NBYTES_WIDTH    32
#define BPORT1_AB_TCD30_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD30_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD30_SLAST_WIDTH     32
#define BPORT1_AB_TCD30_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD30_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD30_DADDR_WIDTH     32
#define BPORT1_AB_TCD30_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD30_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD30_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD30_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD30_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD30_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD30_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD30_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD30_CSR_BITER_WIDTH  32
#define BPORT1_AB_TCD31_SADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD31_SADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD31_SADDR_WIDTH     32
#define BPORT1_AB_TCD31_SOFF_ATTR_WRMASK  0xffffffff
#define BPORT1_AB_TCD31_SOFF_ATTR_WRNMASK  (0x0)
#define BPORT1_AB_TCD31_SOFF_ATTR_WIDTH  32
#define BPORT1_AB_TCD31_NBYTES_WRMASK   0xffffffff
#define BPORT1_AB_TCD31_NBYTES_WRNMASK  (0x0)
#define BPORT1_AB_TCD31_NBYTES_WIDTH    32
#define BPORT1_AB_TCD31_SLAST_WRMASK    0xffffffff
#define BPORT1_AB_TCD31_SLAST_WRNMASK   (0x0)
#define BPORT1_AB_TCD31_SLAST_WIDTH     32
#define BPORT1_AB_TCD31_DADDR_WRMASK    0xffffffff
#define BPORT1_AB_TCD31_DADDR_WRNMASK   (0x0)
#define BPORT1_AB_TCD31_DADDR_WIDTH     32
#define BPORT1_AB_TCD31_DOFF_CITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD31_DOFF_CITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD31_DOFF_CITER_WIDTH  32
#define BPORT1_AB_TCD31_DLASTSGA_WRMASK  0xffffffff
#define BPORT1_AB_TCD31_DLASTSGA_WRNMASK  (0x0)
#define BPORT1_AB_TCD31_DLASTSGA_WIDTH  32
#define BPORT1_AB_TCD31_CSR_BITER_WRMASK  0xffffffff
#define BPORT1_AB_TCD31_CSR_BITER_WRNMASK  (0x0)
#define BPORT1_AB_TCD31_CSR_BITER_WIDTH  32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

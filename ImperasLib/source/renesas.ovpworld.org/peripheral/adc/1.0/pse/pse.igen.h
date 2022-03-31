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

typedef struct ADCP0_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 4;
            Uns8 MS : 1;
            Uns8 BS : 1;
            Uns8 ADCS : 1;
            Uns8 ADCE : 1;
        } bits;
    } ADM0;
    union { 
        Uns8 value;
        struct {
            Uns8 FR : 2;
            Uns8 __pad2 : 2;
            Uns8 TRG : 2;
            Uns8 EGA : 2;
        } bits;
    } ADM1;
    union { 
        Uns8 value;
        struct {
            Uns8 ANI : 4;
        } bits;
    } ADM2;
} ADCP0_reg0_dataT, *ADCP0_reg0_dataTP;

typedef struct ADCP0_reg1_dataS { 
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 6;
            Uns16 AD : 10;
        } bits;
    } ADCR0;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 6;
            Uns16 AD : 10;
        } bits;
    } ADCR1;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 6;
            Uns16 AD : 10;
        } bits;
    } ADCR2;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 6;
            Uns16 AD : 10;
        } bits;
    } ADCR3;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 6;
            Uns16 AD : 10;
        } bits;
    } ADCR4;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 6;
            Uns16 AD : 10;
        } bits;
    } ADCR5;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 6;
            Uns16 AD : 10;
        } bits;
    } ADCR6;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 6;
            Uns16 AD : 10;
        } bits;
    } ADCR7;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 6;
            Uns16 AD : 10;
        } bits;
    } ADCR8;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 6;
            Uns16 AD : 10;
        } bits;
    } ADCR9;
} ADCP0_reg1_dataT, *ADCP0_reg1_dataTP;

typedef struct ADCP0_reg2_dataS { 
    union { 
        Uns16 value;
        struct {
            Uns16 ODF : 1;
            Uns16 __pad1 : 5;
            Uns16 ADDMA : 10;
        } bits;
    } ADDMA;
} ADCP0_reg2_dataT, *ADCP0_reg2_dataTP;

typedef struct ADCP1_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 TSEL : 4;
        } bits;
    } ADTRSEL;
} ADCP1_reg0_dataT, *ADCP1_reg0_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern ADCP0_reg0_dataT ADCP0_reg0_data;

extern ADCP0_reg1_dataT ADCP0_reg1_data;

extern ADCP0_reg2_dataT ADCP0_reg2_data;

extern ADCP1_reg0_dataT ADCP1_reg0_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *ADCP0;
    void                 *ADCP1;
    ppmNetHandle          INTAD;
    ppmNetHandle          ADDMARQ;
    ppmNetHandle          INTADEN;
    ppmNetHandle          ADTRG;
    ppmNetHandle          TS0ADT0;
    ppmNetHandle          TS0ADT1;
    ppmNetHandle          INTTS0OD;
    ppmNetHandle          INTTS0CD;
    ppmNetHandle          TS1ADT0;
    ppmNetHandle          TS1ADT1;
    ppmNetHandle          INTTS1OD;
    ppmNetHandle          INTTS1CD;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_ADTRG);
PPM_NET_CB(P_INTADEN);
PPM_NET_CB(P_INTTS0CD);
PPM_NET_CB(P_INTTS0OD);
PPM_NET_CB(P_INTTS1CD);
PPM_NET_CB(P_INTTS1OD);
PPM_NET_CB(P_TS0ADT0);
PPM_NET_CB(P_TS0ADT1);
PPM_NET_CB(P_TS1ADT0);
PPM_NET_CB(P_TS1ADT1);
PPM_REG_READ_CB(readADCR);
PPM_REG_READ_CB(readADDMA);
PPM_REG_WRITE_CB(writeADM0);
PPM_REG_WRITE_CB(writeADM1);
PPM_REG_WRITE_CB(writeADM2);
PPM_REG_WRITE_CB(writeADTRSEL);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define ADCP0_REG0_ADM0_WRMASK          0xf0
#define ADCP0_REG0_ADM0_WRNMASK         (0xf)
#define ADCP0_REG0_ADM0_WIDTH           8
#define ADCP0_REG0_ADM1_WRMASK          0xf3
#define ADCP0_REG0_ADM1_WRNMASK         (0xc)
#define ADCP0_REG0_ADM1_WIDTH           8
#define ADCP0_REG0_ADM2_WRMASK          0xf
#define ADCP0_REG0_ADM2_WRNMASK         (0xf0)
#define ADCP0_REG0_ADM2_WIDTH           8
#define ADCP0_REG1_ADCR0_WIDTH          16
#define ADCP0_REG1_ADCR1_WIDTH          16
#define ADCP0_REG1_ADCR2_WIDTH          16
#define ADCP0_REG1_ADCR3_WIDTH          16
#define ADCP0_REG1_ADCR4_WIDTH          16
#define ADCP0_REG1_ADCR5_WIDTH          16
#define ADCP0_REG1_ADCR6_WIDTH          16
#define ADCP0_REG1_ADCR7_WIDTH          16
#define ADCP0_REG1_ADCR8_WIDTH          16
#define ADCP0_REG1_ADCR9_WIDTH          16
#define ADCP0_REG2_ADDMA_WIDTH          16
#define ADCP1_REG0_ADTRSEL_WRMASK       0xf
#define ADCP1_REG0_ADTRSEL_WRNMASK      (0xf0)
#define ADCP1_REG0_ADTRSEL_WIDTH        8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

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
        Uns8 value;
        struct {
            Uns8 sbr : 5;
        } bits;
    } bdh;
    union { 
        Uns8 value;
    } bdl;
    union { 
        Uns8 value;
    } c1;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 2;
            Uns8 re : 1;
            Uns8 te : 1;
            Uns8 ilie : 1;
            Uns8 rie : 1;
            Uns8 tcie : 1;
            Uns8 tie : 1;
        } bits;
    } c2;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 4;
            Uns8 idle : 1;
            Uns8 rdrf : 1;
            Uns8 tc : 1;
            Uns8 tdre : 1;
        } bits;
    } s1;
    union { 
        Uns8 value;
    } s2;
    union { 
        Uns8 value;
    } c3;
    union { 
        Uns8 value;
    } d;
    union { 
        Uns8 value;
    } ma1;
    union { 
        Uns8 value;
    } ma2;
    union { 
        Uns8 value;
        struct {
            Uns8 brfa : 5;
        } bits;
    } c4;
    union { 
        Uns8 value;
    } c5;
    union { 
        Uns8 value;
    } ed;
    union { 
        Uns8 value;
    } modem;
    union { 
        Uns8 value;
    } infrared;
    union { 
        Uns8 value;
        struct {
            Uns8 rxfifosize : 3;
            Uns8 rxfe : 1;
            Uns8 txfifosize : 3;
            Uns8 txfe : 1;
        } bits;
    } pfifo;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 6;
            Uns8 rxflush : 1;
            Uns8 txflush : 1;
        } bits;
    } cfifo;
    union { 
        Uns8 value;
    } sfifo;
    union { 
        Uns8 value;
    } twfifo;
    union { 
        Uns8 value;
    } tcfifo;
    union { 
        Uns8 value;
    } rwfifo;
    union { 
        Uns8 value;
    } rcfifo;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          DirectWrite;
    ppmNetHandle          DirectRead;
    ppmNetHandle          Interrupt;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(directReadCB);
PPM_REG_READ_CB(readD);
PPM_REG_READ_CB(readS1);
PPM_NET_CB(resetCB);
PPM_REG_WRITE_CB(writeBDH);
PPM_REG_WRITE_CB(writeBDL);
PPM_REG_WRITE_CB(writeC2);
PPM_REG_WRITE_CB(writeC4);
PPM_REG_WRITE_CB(writeCFIFO);
PPM_REG_WRITE_CB(writeD);
PPM_REG_WRITE_CB(writeRWFIFO);
PPM_REG_WRITE_CB(writeTWFIFO);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_BDH_WRMASK            0xdf
#define BPORT1_AB_BDH_WRNMASK           (0x20)
#define BPORT1_AB_BDH_WIDTH             8
#define BPORT1_AB_BDL_WIDTH             8
#define BPORT1_AB_C1_WIDTH              8
#define BPORT1_AB_C2_WIDTH              8
#define BPORT1_AB_S1_WIDTH              8
#define BPORT1_AB_S2_WRMASK             0xfe
#define BPORT1_AB_S2_WRNMASK            (0x1)
#define BPORT1_AB_S2_WIDTH              8
#define BPORT1_AB_C3_WRMASK             0x7f
#define BPORT1_AB_C3_WRNMASK            (0x80)
#define BPORT1_AB_C3_WIDTH              8
#define BPORT1_AB_D_WIDTH               8
#define BPORT1_AB_MA1_WIDTH             8
#define BPORT1_AB_MA2_WIDTH             8
#define BPORT1_AB_C4_WIDTH              8
#define BPORT1_AB_C5_WRMASK             0xa0
#define BPORT1_AB_C5_WRNMASK            (0x5f)
#define BPORT1_AB_C5_WIDTH              8
#define BPORT1_AB_ED_WIDTH              8
#define BPORT1_AB_MODEM_WRMASK          0xf
#define BPORT1_AB_MODEM_WRNMASK         (0xf0)
#define BPORT1_AB_MODEM_WIDTH           8
#define BPORT1_AB_INFRARED_WRMASK       0x7
#define BPORT1_AB_INFRARED_WRNMASK      (0xf8)
#define BPORT1_AB_INFRARED_WIDTH        8
#define BPORT1_AB_PFIFO_WRMASK          0x88
#define BPORT1_AB_PFIFO_WRNMASK         (0x77)
#define BPORT1_AB_PFIFO_WIDTH           8
#define BPORT1_AB_CFIFO_WRMASK          0xc3
#define BPORT1_AB_CFIFO_WRNMASK         (0x3c)
#define BPORT1_AB_CFIFO_WIDTH           8
#define BPORT1_AB_SFIFO_WRMASK          0x3
#define BPORT1_AB_SFIFO_WRNMASK         (0xfc)
#define BPORT1_AB_SFIFO_WIDTH           8
#define BPORT1_AB_TWFIFO_WIDTH          8
#define BPORT1_AB_TCFIFO_WIDTH          8
#define BPORT1_AB_RWFIFO_WIDTH          8
#define BPORT1_AB_RCFIFO_WIDTH          8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

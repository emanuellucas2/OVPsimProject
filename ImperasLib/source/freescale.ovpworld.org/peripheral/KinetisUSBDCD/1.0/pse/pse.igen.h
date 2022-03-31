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
            Uns32 IACK : 1;
            Uns32 __pad1 : 7;
            Uns32 IF : 1;
            Uns32 __pad9 : 7;
            Uns32 IE : 1;
            Uns32 __pad17 : 7;
            Uns32 START : 1;
            Uns32 SR : 1;
        } bits;
    } CONTROL;
    union { 
        Uns32 value;
        struct {
            Uns32 CLOCK_UNIT : 1;
            Uns32 __pad1 : 1;
            Uns32 CLOCK_SPEED : 10;
        } bits;
    } CLOCK;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 SEQ_RES : 2;
            Uns32 SEQ_STAT : 2;
            Uns32 ERR : 1;
            Uns32 TO : 1;
            Uns32 ACTIVE : 1;
        } bits;
    } STATUS;
    union { 
        Uns32 value;
        struct {
            Uns32 TUNITCON : 12;
            Uns32 __pad12 : 4;
            Uns32 TSEQ_INIT : 10;
        } bits;
    } TIMER0;
    union { 
        Uns32 value;
        struct {
            Uns32 TVDPSRC_ON : 10;
            Uns32 __pad10 : 6;
            Uns32 TDCD_DBNC : 10;
        } bits;
    } TIMER1;
    union { 
        Uns32 value;
        struct {
            Uns32 CHECK_DM : 4;
            Uns32 __pad4 : 12;
            Uns32 TVDPSRC_CON : 10;
        } bits;
    } TIMER2;
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

#define BPORT1_AB_CONTROL_WRMASK        0x3010001
#define BPORT1_AB_CONTROL_WRNMASK       (0xfcfefffe)
#define BPORT1_AB_CONTROL_WIDTH         32
#define BPORT1_AB_CLOCK_WRMASK          0xffd
#define BPORT1_AB_CLOCK_WRNMASK         (0xfffff002)
#define BPORT1_AB_CLOCK_WIDTH           32
#define BPORT1_AB_STATUS_WIDTH          32
#define BPORT1_AB_TIMER0_WRMASK         0x1ff0000
#define BPORT1_AB_TIMER0_WRNMASK        (0xfe00ffff)
#define BPORT1_AB_TIMER0_WIDTH          32
#define BPORT1_AB_TIMER1_WRMASK         0x3ff03ff
#define BPORT1_AB_TIMER1_WRNMASK        (0xfc00fc00)
#define BPORT1_AB_TIMER1_WIDTH          32
#define BPORT1_AB_TIMER2_WRMASK         0x3ff000f
#define BPORT1_AB_TIMER2_WRNMASK        (0xfc00fff0)
#define BPORT1_AB_TIMER2_WIDTH          32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

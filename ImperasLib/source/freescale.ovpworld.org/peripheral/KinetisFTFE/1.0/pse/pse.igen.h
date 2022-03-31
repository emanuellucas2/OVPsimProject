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
            Uns8 MGSTAT0 : 1;
            Uns8 __pad1 : 3;
            Uns8 FPVIOL : 1;
            Uns8 ACCERR : 1;
            Uns8 RDCOLERR : 1;
            Uns8 CCIF : 1;
        } bits;
    } FSTAT;
    union { 
        Uns8 value;
        struct {
            Uns8 EEERDY : 1;
            Uns8 RAMRDY : 1;
            Uns8 PFLSH : 1;
            Uns8 SWAP : 1;
            Uns8 ERSSUSP : 1;
            Uns8 ERSAREQ : 1;
            Uns8 RDCOLLIE : 1;
            Uns8 CCIE : 1;
        } bits;
    } FCNFG;
    union { 
        Uns8 value;
        struct {
            Uns8 SEC : 2;
            Uns8 FSLACC : 2;
            Uns8 MEEN : 2;
            Uns8 KEYEN : 2;
        } bits;
    } FSEC;
    union { 
        Uns8 value;
        struct {
            Uns8 OPT : 8;
        } bits;
    } FOPT;
    union { 
        Uns8 value;
        struct {
            Uns8 CCOBn : 8;
        } bits;
    } FCCOB3;
    union { 
        Uns8 value;
        struct {
            Uns8 CCOBn : 8;
        } bits;
    } FCCOB2;
    union { 
        Uns8 value;
        struct {
            Uns8 CCOBn : 8;
        } bits;
    } FCCOB1;
    union { 
        Uns8 value;
        struct {
            Uns8 CCOBn : 8;
        } bits;
    } FCCOB0;
    union { 
        Uns8 value;
        struct {
            Uns8 CCOBn : 8;
        } bits;
    } FCCOB7;
    union { 
        Uns8 value;
    } FCCOB6;
    union { 
        Uns8 value;
        struct {
            Uns8 CCOBn : 8;
        } bits;
    } FCCOB5;
    union { 
        Uns8 value;
        struct {
            Uns8 CCOBn : 8;
        } bits;
    } FCCOB4;
    union { 
        Uns8 value;
        struct {
            Uns8 CCOBn : 8;
        } bits;
    } FCCOBB;
    union { 
        Uns8 value;
        struct {
            Uns8 CCOBn : 8;
        } bits;
    } FCCOBA;
    union { 
        Uns8 value;
        struct {
            Uns8 CCOBn : 8;
        } bits;
    } FCCOB9;
    union { 
        Uns8 value;
        struct {
            Uns8 CCOBn : 8;
        } bits;
    } FCCOB8;
    union { 
        Uns8 value;
        struct {
            Uns8 PROT : 8;
        } bits;
    } FPROT3;
    union { 
        Uns8 value;
        struct {
            Uns8 PROT : 8;
        } bits;
    } FPROT2;
    union { 
        Uns8 value;
        struct {
            Uns8 PROT : 8;
        } bits;
    } FPROT1;
    union { 
        Uns8 value;
        struct {
            Uns8 PROT : 8;
        } bits;
    } FPROT0;
    union { 
        Uns8 value;
        struct {
            Uns8 EPROT : 8;
        } bits;
    } FEPROT;
    union { 
        Uns8 value;
        struct {
            Uns8 DPROT : 8;
        } bits;
    } FDPROT;
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

#define BPORT1_AB_FSTAT_WRMASK          0xf0
#define BPORT1_AB_FSTAT_WRNMASK         (0xf)
#define BPORT1_AB_FSTAT_WIDTH           8
#define BPORT1_AB_FCNFG_WRMASK          0xd0
#define BPORT1_AB_FCNFG_WRNMASK         (0x2f)
#define BPORT1_AB_FCNFG_WIDTH           8
#define BPORT1_AB_FSEC_WIDTH            8
#define BPORT1_AB_FOPT_WIDTH            8
#define BPORT1_AB_FCCOB3_WRMASK         0xff
#define BPORT1_AB_FCCOB3_WRNMASK        (0x0)
#define BPORT1_AB_FCCOB3_WIDTH          8
#define BPORT1_AB_FCCOB2_WRMASK         0xff
#define BPORT1_AB_FCCOB2_WRNMASK        (0x0)
#define BPORT1_AB_FCCOB2_WIDTH          8
#define BPORT1_AB_FCCOB1_WRMASK         0xff
#define BPORT1_AB_FCCOB1_WRNMASK        (0x0)
#define BPORT1_AB_FCCOB1_WIDTH          8
#define BPORT1_AB_FCCOB0_WRMASK         0xff
#define BPORT1_AB_FCCOB0_WRNMASK        (0x0)
#define BPORT1_AB_FCCOB0_WIDTH          8
#define BPORT1_AB_FCCOB7_WRMASK         0xff
#define BPORT1_AB_FCCOB7_WRNMASK        (0x0)
#define BPORT1_AB_FCCOB7_WIDTH          8
#define BPORT1_AB_FCCOB6_WRMASK         0xff
#define BPORT1_AB_FCCOB6_WRNMASK        (0x0)
#define BPORT1_AB_FCCOB6_WIDTH          8
#define BPORT1_AB_FCCOB5_WRMASK         0xff
#define BPORT1_AB_FCCOB5_WRNMASK        (0x0)
#define BPORT1_AB_FCCOB5_WIDTH          8
#define BPORT1_AB_FCCOB4_WRMASK         0xff
#define BPORT1_AB_FCCOB4_WRNMASK        (0x0)
#define BPORT1_AB_FCCOB4_WIDTH          8
#define BPORT1_AB_FCCOBB_WRMASK         0xff
#define BPORT1_AB_FCCOBB_WRNMASK        (0x0)
#define BPORT1_AB_FCCOBB_WIDTH          8
#define BPORT1_AB_FCCOBA_WRMASK         0xff
#define BPORT1_AB_FCCOBA_WRNMASK        (0x0)
#define BPORT1_AB_FCCOBA_WIDTH          8
#define BPORT1_AB_FCCOB9_WRMASK         0xff
#define BPORT1_AB_FCCOB9_WRNMASK        (0x0)
#define BPORT1_AB_FCCOB9_WIDTH          8
#define BPORT1_AB_FCCOB8_WRMASK         0xff
#define BPORT1_AB_FCCOB8_WRNMASK        (0x0)
#define BPORT1_AB_FCCOB8_WIDTH          8
#define BPORT1_AB_FPROT3_WRMASK         0xff
#define BPORT1_AB_FPROT3_WRNMASK        (0x0)
#define BPORT1_AB_FPROT3_WIDTH          8
#define BPORT1_AB_FPROT2_WRMASK         0xff
#define BPORT1_AB_FPROT2_WRNMASK        (0x0)
#define BPORT1_AB_FPROT2_WIDTH          8
#define BPORT1_AB_FPROT1_WRMASK         0xff
#define BPORT1_AB_FPROT1_WRNMASK        (0x0)
#define BPORT1_AB_FPROT1_WIDTH          8
#define BPORT1_AB_FPROT0_WRMASK         0xff
#define BPORT1_AB_FPROT0_WRNMASK        (0x0)
#define BPORT1_AB_FPROT0_WIDTH          8
#define BPORT1_AB_FEPROT_WRMASK         0xff
#define BPORT1_AB_FEPROT_WRNMASK        (0x0)
#define BPORT1_AB_FEPROT_WIDTH          8
#define BPORT1_AB_FDPROT_WRMASK         0xff
#define BPORT1_AB_FDPROT_WRNMASK        (0x0)
#define BPORT1_AB_FDPROT_WIDTH          8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

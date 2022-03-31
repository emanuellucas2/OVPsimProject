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

typedef struct INTCP0_reg0_dataS { 
    union { 
        Uns16 value;
    } IMR0;
    union { 
        Uns16 value;
    } IMR1;
    union { 
        Uns16 value;
    } IMR2;
    union { 
        Uns16 value;
    } IMR3;
    union { 
        Uns16 value;
    } IMR4;
    union { 
        Uns16 value;
    } IMR5;
    union { 
        Uns16 value;
    } IMR6;
    union { 
        Uns16 value;
    } IMR7;
} INTCP0_reg0_dataT, *INTCP0_reg0_dataTP;

typedef struct INTCP0_reg1_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC000;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC001;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC002;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC003;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC004;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC005;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC006;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC007;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC008;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC009;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC010;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC011;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC012;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC013;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC014;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC015;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC016;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC017;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC018;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC019;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC020;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC021;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC022;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC023;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC024;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC025;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC026;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC027;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC028;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC029;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC030;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC031;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC032;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC033;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC034;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC035;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC036;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC037;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC038;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC039;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC040;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC041;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC042;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC043;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC044;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC045;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC046;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC047;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC048;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC049;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC050;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC051;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC052;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC053;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC054;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC055;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC056;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC057;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC058;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC059;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC060;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC061;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC062;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC063;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC064;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC065;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC066;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC067;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC068;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC069;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC070;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC071;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC072;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC073;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC074;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC075;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC076;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC077;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC078;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC079;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC080;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC081;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC082;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC083;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC084;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC085;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC086;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC087;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC088;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC089;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC090;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC091;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC092;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC093;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC094;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC095;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC096;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC097;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC098;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC099;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC100;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC101;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC102;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC103;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC104;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC105;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC106;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC107;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC108;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC109;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC110;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC111;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC112;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC113;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC114;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC115;
    union { 
        Uns8 value;
        struct {
            Uns8 PR : 3;
            Uns8 __pad3 : 3;
            Uns8 MK : 1;
            Uns8 IF : 1;
        } bits;
    } IC116;
    union { 
        Uns8 value;
        struct {
            Uns8 ISPR0 : 1;
            Uns8 ISPR1 : 1;
            Uns8 ISPR2 : 1;
            Uns8 ISPR3 : 1;
            Uns8 ISPR4 : 1;
            Uns8 ISPR5 : 1;
            Uns8 ISPR6 : 1;
            Uns8 ISPR7 : 1;
        } bits;
    } ISPR;
} INTCP0_reg1_dataT, *INTCP0_reg1_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern INTCP0_reg0_dataT INTCP0_reg0_data;

extern INTCP0_reg1_dataT INTCP0_reg1_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *INTCP0;
    ppmNetHandle          RESET;
    ppmNetHandle          NMI0;
    ppmNetHandle          NMI1;
    ppmNetHandle          NMI2;
    ppmNetHandle          INTP;
    ppmNetHandle          INTACK;
    ppmNetHandle          MIRETI;
    ppmNetHandle          IRESET;
    ppmNetHandle          NMI_00;
    ppmNetHandle          NMI_01;
    ppmNetHandle          NMI_02;
    ppmNetHandle          NMI_03;
    ppmNetHandle          NMI_04;
    ppmNetHandle          NMI_05;
    ppmNetHandle          NMI_06;
    ppmNetHandle          NMI_07;
    ppmNetHandle          NMI_08;
    ppmNetHandle          NMI_09;
    ppmNetHandle          NMI_10;
    ppmNetHandle          NMI_11;
    ppmNetHandle          NMI_12;
    ppmNetHandle          NMI_13;
    ppmNetHandle          NMI_14;
    ppmNetHandle          NMI_15;
    ppmNetHandle          NMI_16;
    ppmNetHandle          NMI_17;
    ppmNetHandle          NMI_18;
    ppmNetHandle          NMI_19;
    ppmNetHandle          NMI_20;
    ppmNetHandle          NMI_21;
    ppmNetHandle          NMI_22;
    ppmNetHandle          NMI_23;
    ppmNetHandle          NMI_24;
    ppmNetHandle          NMI_25;
    ppmNetHandle          NMI_26;
    ppmNetHandle          NMI_27;
    ppmNetHandle          NMI_28;
    ppmNetHandle          NMI_29;
    ppmNetHandle          NMI_30;
    ppmNetHandle          NMI_31;
    ppmNetHandle          NMI_32;
    ppmNetHandle          NMI_33;
    ppmNetHandle          NMI_34;
    ppmNetHandle          NMI_35;
    ppmNetHandle          NMI_36;
    ppmNetHandle          NMI_37;
    ppmNetHandle          NMI_38;
    ppmNetHandle          NMI_39;
    ppmNetHandle          NMI_40;
    ppmNetHandle          NMI_41;
    ppmNetHandle          NMI_42;
    ppmNetHandle          NMI_43;
    ppmNetHandle          NMI_44;
    ppmNetHandle          NMI_45;
    ppmNetHandle          NMI_46;
    ppmNetHandle          NMI_47;
    ppmNetHandle          NMI_48;
    ppmNetHandle          NMI_49;
    ppmNetHandle          NMI_50;
    ppmNetHandle          NMI_51;
    ppmNetHandle          NMI_52;
    ppmNetHandle          NMI_53;
    ppmNetHandle          NMI_54;
    ppmNetHandle          NMI_55;
    ppmNetHandle          NMI_56;
    ppmNetHandle          NMI_57;
    ppmNetHandle          NMI_58;
    ppmNetHandle          NMI_59;
    ppmNetHandle          NMI_60;
    ppmNetHandle          NMI_61;
    ppmNetHandle          NMI_62;
    ppmNetHandle          NMI_63;
    ppmNetHandle          INT_00;
    ppmNetHandle          INT_01;
    ppmNetHandle          INT_02;
    ppmNetHandle          INT_03;
    ppmNetHandle          INT_04;
    ppmNetHandle          INT_05;
    ppmNetHandle          INT_06;
    ppmNetHandle          INT_07;
    ppmNetHandle          INT_08;
    ppmNetHandle          INT_09;
    ppmNetHandle          INT_10;
    ppmNetHandle          INT_11;
    ppmNetHandle          INT_12;
    ppmNetHandle          INT_13;
    ppmNetHandle          INT_14;
    ppmNetHandle          INT_15;
    ppmNetHandle          INT_16;
    ppmNetHandle          INT_17;
    ppmNetHandle          INT_18;
    ppmNetHandle          INT_19;
    ppmNetHandle          INT_20;
    ppmNetHandle          INT_21;
    ppmNetHandle          INT_22;
    ppmNetHandle          INT_23;
    ppmNetHandle          INT_24;
    ppmNetHandle          INT_25;
    ppmNetHandle          INT_26;
    ppmNetHandle          INT_27;
    ppmNetHandle          INT_28;
    ppmNetHandle          INT_29;
    ppmNetHandle          INT_30;
    ppmNetHandle          INT_31;
    ppmNetHandle          INT_32;
    ppmNetHandle          INT_33;
    ppmNetHandle          INT_34;
    ppmNetHandle          INT_35;
    ppmNetHandle          INT_36;
    ppmNetHandle          INT_37;
    ppmNetHandle          INT_38;
    ppmNetHandle          INT_39;
    ppmNetHandle          INT_40;
    ppmNetHandle          INT_41;
    ppmNetHandle          INT_42;
    ppmNetHandle          INT_43;
    ppmNetHandle          INT_44;
    ppmNetHandle          INT_45;
    ppmNetHandle          INT_46;
    ppmNetHandle          INT_47;
    ppmNetHandle          INT_48;
    ppmNetHandle          INT_49;
    ppmNetHandle          INT_50;
    ppmNetHandle          INT_51;
    ppmNetHandle          INT_52;
    ppmNetHandle          INT_53;
    ppmNetHandle          INT_54;
    ppmNetHandle          INT_55;
    ppmNetHandle          INT_56;
    ppmNetHandle          INT_57;
    ppmNetHandle          INT_58;
    ppmNetHandle          INT_59;
    ppmNetHandle          INT_60;
    ppmNetHandle          INT_61;
    ppmNetHandle          INT_62;
    ppmNetHandle          INT_63;
    ppmNetHandle          INT_64;
    ppmNetHandle          INT_65;
    ppmNetHandle          INT_66;
    ppmNetHandle          INT_67;
    ppmNetHandle          INT_68;
    ppmNetHandle          INT_69;
    ppmNetHandle          INT_70;
    ppmNetHandle          INT_71;
    ppmNetHandle          INT_72;
    ppmNetHandle          INT_73;
    ppmNetHandle          INT_74;
    ppmNetHandle          INT_75;
    ppmNetHandle          INT_76;
    ppmNetHandle          INT_77;
    ppmNetHandle          INT_78;
    ppmNetHandle          INT_79;
    ppmNetHandle          INT_80;
    ppmNetHandle          INT_81;
    ppmNetHandle          INT_82;
    ppmNetHandle          INT_83;
    ppmNetHandle          INT_84;
    ppmNetHandle          INT_85;
    ppmNetHandle          INT_86;
    ppmNetHandle          INT_87;
    ppmNetHandle          INT_88;
    ppmNetHandle          INT_89;
    ppmNetHandle          INT_90;
    ppmNetHandle          INT_91;
    ppmNetHandle          INT_92;
    ppmNetHandle          INT_93;
    ppmNetHandle          INT_94;
    ppmNetHandle          INT_95;
    ppmNetHandle          INT_96;
    ppmNetHandle          INT_97;
    ppmNetHandle          INT_98;
    ppmNetHandle          INT_99;
    ppmNetHandle          INT_100;
    ppmNetHandle          INT_101;
    ppmNetHandle          INT_102;
    ppmNetHandle          INT_103;
    ppmNetHandle          INT_104;
    ppmNetHandle          INT_105;
    ppmNetHandle          INT_106;
    ppmNetHandle          INT_107;
    ppmNetHandle          INT_108;
    ppmNetHandle          INT_109;
    ppmNetHandle          INT_110;
    ppmNetHandle          INT_111;
    ppmNetHandle          INT_112;
    ppmNetHandle          INT_113;
    ppmNetHandle          INT_114;
    ppmNetHandle          INT_115;
    ppmNetHandle          INT_116;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_INT);
PPM_NET_CB(P_INTACK);
PPM_NET_CB(P_IRESET);
PPM_NET_CB(P_MIRETI);
PPM_NET_CB(P_NMI);
PPM_REG_READ_CB(readIC);
PPM_REG_READ_CB(readIMR);
PPM_REG_WRITE_CB(writeIC);
PPM_REG_WRITE_CB(writeIMR);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define INTCP0_REG0_IMR0_WIDTH          16
#define INTCP0_REG0_IMR1_WIDTH          16
#define INTCP0_REG0_IMR2_WIDTH          16
#define INTCP0_REG0_IMR3_WIDTH          16
#define INTCP0_REG0_IMR4_WIDTH          16
#define INTCP0_REG0_IMR5_WIDTH          16
#define INTCP0_REG0_IMR6_WIDTH          16
#define INTCP0_REG0_IMR7_WIDTH          16
#define INTCP0_REG1_IC000_WIDTH         8
#define INTCP0_REG1_IC001_WIDTH         8
#define INTCP0_REG1_IC002_WIDTH         8
#define INTCP0_REG1_IC003_WIDTH         8
#define INTCP0_REG1_IC004_WIDTH         8
#define INTCP0_REG1_IC005_WIDTH         8
#define INTCP0_REG1_IC006_WIDTH         8
#define INTCP0_REG1_IC007_WIDTH         8
#define INTCP0_REG1_IC008_WIDTH         8
#define INTCP0_REG1_IC009_WIDTH         8
#define INTCP0_REG1_IC010_WIDTH         8
#define INTCP0_REG1_IC011_WIDTH         8
#define INTCP0_REG1_IC012_WIDTH         8
#define INTCP0_REG1_IC013_WIDTH         8
#define INTCP0_REG1_IC014_WIDTH         8
#define INTCP0_REG1_IC015_WIDTH         8
#define INTCP0_REG1_IC016_WIDTH         8
#define INTCP0_REG1_IC017_WIDTH         8
#define INTCP0_REG1_IC018_WIDTH         8
#define INTCP0_REG1_IC019_WIDTH         8
#define INTCP0_REG1_IC020_WIDTH         8
#define INTCP0_REG1_IC021_WIDTH         8
#define INTCP0_REG1_IC022_WIDTH         8
#define INTCP0_REG1_IC023_WIDTH         8
#define INTCP0_REG1_IC024_WIDTH         8
#define INTCP0_REG1_IC025_WIDTH         8
#define INTCP0_REG1_IC026_WIDTH         8
#define INTCP0_REG1_IC027_WIDTH         8
#define INTCP0_REG1_IC028_WIDTH         8
#define INTCP0_REG1_IC029_WIDTH         8
#define INTCP0_REG1_IC030_WIDTH         8
#define INTCP0_REG1_IC031_WIDTH         8
#define INTCP0_REG1_IC032_WIDTH         8
#define INTCP0_REG1_IC033_WIDTH         8
#define INTCP0_REG1_IC034_WIDTH         8
#define INTCP0_REG1_IC035_WIDTH         8
#define INTCP0_REG1_IC036_WIDTH         8
#define INTCP0_REG1_IC037_WIDTH         8
#define INTCP0_REG1_IC038_WIDTH         8
#define INTCP0_REG1_IC039_WIDTH         8
#define INTCP0_REG1_IC040_WIDTH         8
#define INTCP0_REG1_IC041_WIDTH         8
#define INTCP0_REG1_IC042_WIDTH         8
#define INTCP0_REG1_IC043_WIDTH         8
#define INTCP0_REG1_IC044_WIDTH         8
#define INTCP0_REG1_IC045_WIDTH         8
#define INTCP0_REG1_IC046_WIDTH         8
#define INTCP0_REG1_IC047_WIDTH         8
#define INTCP0_REG1_IC048_WIDTH         8
#define INTCP0_REG1_IC049_WIDTH         8
#define INTCP0_REG1_IC050_WIDTH         8
#define INTCP0_REG1_IC051_WIDTH         8
#define INTCP0_REG1_IC052_WIDTH         8
#define INTCP0_REG1_IC053_WIDTH         8
#define INTCP0_REG1_IC054_WIDTH         8
#define INTCP0_REG1_IC055_WIDTH         8
#define INTCP0_REG1_IC056_WIDTH         8
#define INTCP0_REG1_IC057_WIDTH         8
#define INTCP0_REG1_IC058_WIDTH         8
#define INTCP0_REG1_IC059_WIDTH         8
#define INTCP0_REG1_IC060_WIDTH         8
#define INTCP0_REG1_IC061_WIDTH         8
#define INTCP0_REG1_IC062_WIDTH         8
#define INTCP0_REG1_IC063_WIDTH         8
#define INTCP0_REG1_IC064_WIDTH         8
#define INTCP0_REG1_IC065_WIDTH         8
#define INTCP0_REG1_IC066_WIDTH         8
#define INTCP0_REG1_IC067_WIDTH         8
#define INTCP0_REG1_IC068_WIDTH         8
#define INTCP0_REG1_IC069_WIDTH         8
#define INTCP0_REG1_IC070_WIDTH         8
#define INTCP0_REG1_IC071_WIDTH         8
#define INTCP0_REG1_IC072_WIDTH         8
#define INTCP0_REG1_IC073_WIDTH         8
#define INTCP0_REG1_IC074_WIDTH         8
#define INTCP0_REG1_IC075_WIDTH         8
#define INTCP0_REG1_IC076_WIDTH         8
#define INTCP0_REG1_IC077_WIDTH         8
#define INTCP0_REG1_IC078_WIDTH         8
#define INTCP0_REG1_IC079_WIDTH         8
#define INTCP0_REG1_IC080_WIDTH         8
#define INTCP0_REG1_IC081_WIDTH         8
#define INTCP0_REG1_IC082_WIDTH         8
#define INTCP0_REG1_IC083_WIDTH         8
#define INTCP0_REG1_IC084_WIDTH         8
#define INTCP0_REG1_IC085_WIDTH         8
#define INTCP0_REG1_IC086_WIDTH         8
#define INTCP0_REG1_IC087_WIDTH         8
#define INTCP0_REG1_IC088_WIDTH         8
#define INTCP0_REG1_IC089_WIDTH         8
#define INTCP0_REG1_IC090_WIDTH         8
#define INTCP0_REG1_IC091_WIDTH         8
#define INTCP0_REG1_IC092_WIDTH         8
#define INTCP0_REG1_IC093_WIDTH         8
#define INTCP0_REG1_IC094_WIDTH         8
#define INTCP0_REG1_IC095_WIDTH         8
#define INTCP0_REG1_IC096_WIDTH         8
#define INTCP0_REG1_IC097_WIDTH         8
#define INTCP0_REG1_IC098_WIDTH         8
#define INTCP0_REG1_IC099_WIDTH         8
#define INTCP0_REG1_IC100_WIDTH         8
#define INTCP0_REG1_IC101_WIDTH         8
#define INTCP0_REG1_IC102_WIDTH         8
#define INTCP0_REG1_IC103_WIDTH         8
#define INTCP0_REG1_IC104_WIDTH         8
#define INTCP0_REG1_IC105_WIDTH         8
#define INTCP0_REG1_IC106_WIDTH         8
#define INTCP0_REG1_IC107_WIDTH         8
#define INTCP0_REG1_IC108_WIDTH         8
#define INTCP0_REG1_IC109_WIDTH         8
#define INTCP0_REG1_IC110_WIDTH         8
#define INTCP0_REG1_IC111_WIDTH         8
#define INTCP0_REG1_IC112_WIDTH         8
#define INTCP0_REG1_IC113_WIDTH         8
#define INTCP0_REG1_IC114_WIDTH         8
#define INTCP0_REG1_IC115_WIDTH         8
#define INTCP0_REG1_IC116_WIDTH         8
#define INTCP0_REG1_ISPR_WIDTH          8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

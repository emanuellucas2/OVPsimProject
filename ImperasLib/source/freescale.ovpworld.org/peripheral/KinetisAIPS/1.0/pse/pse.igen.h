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
            Uns32 MPL7 : 1;
            Uns32 MTW7 : 1;
            Uns32 MTR7 : 1;
            Uns32 __pad3 : 1;
            Uns32 MPL6 : 1;
            Uns32 MTW6 : 1;
            Uns32 MTR6 : 1;
            Uns32 __pad7 : 1;
            Uns32 MPL5 : 1;
            Uns32 MTW5 : 1;
            Uns32 MTR5 : 1;
            Uns32 __pad11 : 1;
            Uns32 MPL4 : 1;
            Uns32 MTW4 : 1;
            Uns32 MTR4 : 1;
            Uns32 __pad15 : 1;
            Uns32 MPL3 : 1;
            Uns32 MTW3 : 1;
            Uns32 MTR3 : 1;
            Uns32 __pad19 : 1;
            Uns32 MPL2 : 1;
            Uns32 MTW2 : 1;
            Uns32 MTR2 : 1;
            Uns32 __pad23 : 1;
            Uns32 MPL1 : 1;
            Uns32 MTW1 : 1;
            Uns32 MTR1 : 1;
            Uns32 __pad27 : 1;
            Uns32 MPL0 : 1;
            Uns32 MTW0 : 1;
            Uns32 MTR0 : 1;
        } bits;
    } MPRA;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRA;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRB;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRC;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRD;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRE;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRF;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRG;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRH;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRI;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRJ;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRK;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRL;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRM;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRN;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRO;
    union { 
        Uns32 value;
        struct {
            Uns32 TP7 : 1;
            Uns32 WP7 : 1;
            Uns32 SP7 : 1;
            Uns32 __pad3 : 1;
            Uns32 TP6 : 1;
            Uns32 WP6 : 1;
            Uns32 SP6 : 1;
            Uns32 __pad7 : 1;
            Uns32 TP5 : 1;
            Uns32 WP5 : 1;
            Uns32 SP5 : 1;
            Uns32 __pad11 : 1;
            Uns32 TP4 : 1;
            Uns32 WP4 : 1;
            Uns32 SP4 : 1;
            Uns32 __pad15 : 1;
            Uns32 TP3 : 1;
            Uns32 WP3 : 1;
            Uns32 SP3 : 1;
            Uns32 __pad19 : 1;
            Uns32 TP2 : 1;
            Uns32 WP2 : 1;
            Uns32 SP2 : 1;
            Uns32 __pad23 : 1;
            Uns32 TP1 : 1;
            Uns32 WP1 : 1;
            Uns32 SP1 : 1;
            Uns32 __pad27 : 1;
            Uns32 TP0 : 1;
            Uns32 WP0 : 1;
            Uns32 SP0 : 1;
        } bits;
    } PACRP;
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

#define BPORT1_AB_MPRA_WRMASK           0x77777777
#define BPORT1_AB_MPRA_WRNMASK          (0x88888888)
#define BPORT1_AB_MPRA_WIDTH            32
#define BPORT1_AB_PACRA_WRMASK          0x77777777
#define BPORT1_AB_PACRA_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRA_WIDTH           32
#define BPORT1_AB_PACRB_WRMASK          0x77777777
#define BPORT1_AB_PACRB_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRB_WIDTH           32
#define BPORT1_AB_PACRC_WRMASK          0x77777777
#define BPORT1_AB_PACRC_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRC_WIDTH           32
#define BPORT1_AB_PACRD_WRMASK          0x77777777
#define BPORT1_AB_PACRD_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRD_WIDTH           32
#define BPORT1_AB_PACRE_WRMASK          0x77777777
#define BPORT1_AB_PACRE_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRE_WIDTH           32
#define BPORT1_AB_PACRF_WRMASK          0x77777777
#define BPORT1_AB_PACRF_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRF_WIDTH           32
#define BPORT1_AB_PACRG_WRMASK          0x77777777
#define BPORT1_AB_PACRG_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRG_WIDTH           32
#define BPORT1_AB_PACRH_WRMASK          0x77777777
#define BPORT1_AB_PACRH_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRH_WIDTH           32
#define BPORT1_AB_PACRI_WRMASK          0x77777777
#define BPORT1_AB_PACRI_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRI_WIDTH           32
#define BPORT1_AB_PACRJ_WRMASK          0x77777777
#define BPORT1_AB_PACRJ_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRJ_WIDTH           32
#define BPORT1_AB_PACRK_WRMASK          0x77777777
#define BPORT1_AB_PACRK_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRK_WIDTH           32
#define BPORT1_AB_PACRL_WRMASK          0x77777777
#define BPORT1_AB_PACRL_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRL_WIDTH           32
#define BPORT1_AB_PACRM_WRMASK          0x77777777
#define BPORT1_AB_PACRM_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRM_WIDTH           32
#define BPORT1_AB_PACRN_WRMASK          0x77777777
#define BPORT1_AB_PACRN_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRN_WIDTH           32
#define BPORT1_AB_PACRO_WRMASK          0x77777777
#define BPORT1_AB_PACRO_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRO_WIDTH           32
#define BPORT1_AB_PACRP_WRMASK          0x77777777
#define BPORT1_AB_PACRP_WRNMASK         (0x88888888)
#define BPORT1_AB_PACRP_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

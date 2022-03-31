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

typedef struct config_ab_dataS { 
    union { 
        Uns8 value;
    } cr_index;
    union { 
        Uns8 value;
    } cr;
    union { 
        Uns8 value;
    } gr_index;
    union { 
        Uns8 value;
    } ar_index;
    union { 
        Uns8 value;
    } ar;
    union { 
        Uns8 value;
    } msrWrite;
    union { 
        Uns8 value;
    } st00;
    union { 
        Uns8 value;
    } gr;
    union { 
        Uns8 value;
    } sr_index;
    union { 
        Uns8 value;
    } sr;
    union { 
        Uns8 value;
    } fcrWrite;
    union { 
        Uns8 value;
    } st01;
    union { 
        Uns8 value;
    } dac_read_index;
    union { 
        Uns8 value;
    } dac_write_index;
    union { 
        Uns8 value;
    } dac_cache;
    union { 
        Uns8 value;
    } fcrRead;
    union { 
        Uns8 value;
    } msrRead;
} config_ab_dataT, *config_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern config_ab_dataT config_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *config;
    void                 *memory;
    void                 *PCIconfig;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define CONFIG_AB_CR_INDEX_WIDTH        8
#define CONFIG_AB_CR_WIDTH              8
#define CONFIG_AB_GR_INDEX_WIDTH        8
#define CONFIG_AB_AR_INDEX_WIDTH        8
#define CONFIG_AB_AR_WIDTH              8
#define CONFIG_AB_MSRWRITE_WIDTH        8
#define CONFIG_AB_ST00_WIDTH            8
#define CONFIG_AB_GR_WIDTH              8
#define CONFIG_AB_SR_INDEX_WIDTH        8
#define CONFIG_AB_SR_WIDTH              8
#define CONFIG_AB_FCRWRITE_WIDTH        8
#define CONFIG_AB_ST01_WIDTH            8
#define CONFIG_AB_DAC_READ_INDEX_WIDTH  8
#define CONFIG_AB_DAC_WRITE_INDEX_WIDTH  8
#define CONFIG_AB_DAC_CACHE_WIDTH       8
#define CONFIG_AB_FCRREAD_WIDTH         8
#define CONFIG_AB_MSRREAD_WIDTH         8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

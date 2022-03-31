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
            Uns32 VPU_PDN : 1;
            Uns32 VPU_PUP : 1;
            Uns32 __pad2 : 19;
            Uns32 GPCIRQM : 1;
        } bits;
    } GPC_CNTR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 29;
            Uns32 DRCIC : 2;
        } bits;
    } GPC_PGR;
    union { 
        Uns32 value;
    } GPC_IMR1;
    union { 
        Uns32 value;
    } GPC_IMR2;
    union { 
        Uns32 value;
    } GPC_IMR3;
    union { 
        Uns32 value;
    } GPC_IMR4;
    union { 
        Uns32 value;
    } GPC_ISR1;
    union { 
        Uns32 value;
    } GPC_ISR2;
    union { 
        Uns32 value;
    } GPC_ISR3;
    union { 
        Uns32 value;
    } GPC_ISR4;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq32;
    ppmNetHandle          irq33;
    ppmNetHandle          irq34;
    ppmNetHandle          irq35;
    ppmNetHandle          irq36;
    ppmNetHandle          irq37;
    ppmNetHandle          irq38;
    ppmNetHandle          irq39;
    ppmNetHandle          irq40;
    ppmNetHandle          irq41;
    ppmNetHandle          irq42;
    ppmNetHandle          irq43;
    ppmNetHandle          irq44;
    ppmNetHandle          irq45;
    ppmNetHandle          irq46;
    ppmNetHandle          irq47;
    ppmNetHandle          irq48;
    ppmNetHandle          irq49;
    ppmNetHandle          irq50;
    ppmNetHandle          irq51;
    ppmNetHandle          irq52;
    ppmNetHandle          irq53;
    ppmNetHandle          irq54;
    ppmNetHandle          irq55;
    ppmNetHandle          irq56;
    ppmNetHandle          irq57;
    ppmNetHandle          irq58;
    ppmNetHandle          irq59;
    ppmNetHandle          irq60;
    ppmNetHandle          irq61;
    ppmNetHandle          irq62;
    ppmNetHandle          irq63;
    ppmNetHandle          irq64;
    ppmNetHandle          irq65;
    ppmNetHandle          irq66;
    ppmNetHandle          irq67;
    ppmNetHandle          irq68;
    ppmNetHandle          irq69;
    ppmNetHandle          irq70;
    ppmNetHandle          irq71;
    ppmNetHandle          irq72;
    ppmNetHandle          irq73;
    ppmNetHandle          irq74;
    ppmNetHandle          irq75;
    ppmNetHandle          irq76;
    ppmNetHandle          irq77;
    ppmNetHandle          irq78;
    ppmNetHandle          irq79;
    ppmNetHandle          irq80;
    ppmNetHandle          irq81;
    ppmNetHandle          irq82;
    ppmNetHandle          irq83;
    ppmNetHandle          irq84;
    ppmNetHandle          irq85;
    ppmNetHandle          irq86;
    ppmNetHandle          irq87;
    ppmNetHandle          irq88;
    ppmNetHandle          irq89;
    ppmNetHandle          irq90;
    ppmNetHandle          irq91;
    ppmNetHandle          irq92;
    ppmNetHandle          irq93;
    ppmNetHandle          irq94;
    ppmNetHandle          irq95;
    ppmNetHandle          irq96;
    ppmNetHandle          irq97;
    ppmNetHandle          irq98;
    ppmNetHandle          irq99;
    ppmNetHandle          irq100;
    ppmNetHandle          irq101;
    ppmNetHandle          irq102;
    ppmNetHandle          irq103;
    ppmNetHandle          irq104;
    ppmNetHandle          irq105;
    ppmNetHandle          irq106;
    ppmNetHandle          irq107;
    ppmNetHandle          irq108;
    ppmNetHandle          irq109;
    ppmNetHandle          irq110;
    ppmNetHandle          irq111;
    ppmNetHandle          irq112;
    ppmNetHandle          irq113;
    ppmNetHandle          irq114;
    ppmNetHandle          irq115;
    ppmNetHandle          irq116;
    ppmNetHandle          irq117;
    ppmNetHandle          irq118;
    ppmNetHandle          irq119;
    ppmNetHandle          irq120;
    ppmNetHandle          irq121;
    ppmNetHandle          irq122;
    ppmNetHandle          irq123;
    ppmNetHandle          irq124;
    ppmNetHandle          irq125;
    ppmNetHandle          irq126;
    ppmNetHandle          irq127;
    ppmNetHandle          irq128;
    ppmNetHandle          irq129;
    ppmNetHandle          irq130;
    ppmNetHandle          irq131;
    ppmNetHandle          irq132;
    ppmNetHandle          irq133;
    ppmNetHandle          irq134;
    ppmNetHandle          irq135;
    ppmNetHandle          irq136;
    ppmNetHandle          irq137;
    ppmNetHandle          irq138;
    ppmNetHandle          irq139;
    ppmNetHandle          irq140;
    ppmNetHandle          irq141;
    ppmNetHandle          irq142;
    ppmNetHandle          irq143;
    ppmNetHandle          irq144;
    ppmNetHandle          irq145;
    ppmNetHandle          irq146;
    ppmNetHandle          irq147;
    ppmNetHandle          irq148;
    ppmNetHandle          irq149;
    ppmNetHandle          irq150;
    ppmNetHandle          irq151;
    ppmNetHandle          irq152;
    ppmNetHandle          irq153;
    ppmNetHandle          irq154;
    ppmNetHandle          irq155;
    ppmNetHandle          irq156;
    ppmNetHandle          irq157;
    ppmNetHandle          irq158;
    ppmNetHandle          irq159;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(WriteGPC_CNTR);
PPM_NET_CB(interruptIn);
PPM_READ_CB(regNoDefinitionRead);
PPM_WRITE_CB(regNoDefinitionWrite);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/ab/buffer : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER_OFFSET + myAddress];

#define BPORT1_AB_BUFFER_OFFSET         0x0
#define BPORT1_AB_BUFFER_SIZE           0x260

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_GPC_CNTR_WRMASK       0x200003
#define BPORT1_AB_GPC_CNTR_WRNMASK      (0xffdffffc)
#define BPORT1_AB_GPC_CNTR_WIDTH        32
#define BPORT1_AB_GPC_PGR_WRMASK        0x60000000
#define BPORT1_AB_GPC_PGR_WRNMASK       (0x9fffffff)
#define BPORT1_AB_GPC_PGR_WIDTH         32
#define BPORT1_AB_GPC_IMR1_WIDTH        32
#define BPORT1_AB_GPC_IMR2_WIDTH        32
#define BPORT1_AB_GPC_IMR3_WIDTH        32
#define BPORT1_AB_GPC_IMR4_WIDTH        32
#define BPORT1_AB_GPC_ISR1_WIDTH        32
#define BPORT1_AB_GPC_ISR2_WIDTH        32
#define BPORT1_AB_GPC_ISR3_WIDTH        32
#define BPORT1_AB_GPC_ISR4_WIDTH        32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

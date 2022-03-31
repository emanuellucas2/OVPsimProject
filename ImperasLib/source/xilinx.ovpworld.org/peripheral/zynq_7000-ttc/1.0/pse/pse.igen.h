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
            Uns32 PS_EN : 1;
            Uns32 PS_V : 4;
            Uns32 SRC : 1;
            Uns32 E : 1;
        } bits;
    } Clock_Control_1;
    union { 
        Uns32 value;
        struct {
            Uns32 PS_EN : 1;
            Uns32 PS_V : 4;
            Uns32 SRC : 1;
            Uns32 E : 1;
        } bits;
    } Clock_Control_2;
    union { 
        Uns32 value;
        struct {
            Uns32 PS_EN : 1;
            Uns32 PS_V : 4;
            Uns32 SRC : 1;
            Uns32 E : 1;
        } bits;
    } Clock_Control_3;
    union { 
        Uns32 value;
        struct {
            Uns32 DIS : 1;
            Uns32 INT : 1;
            Uns32 DEC : 1;
            Uns32 MATCH : 1;
            Uns32 RST : 1;
            Uns32 WAVEN : 1;
            Uns32 WAVPOL : 1;
        } bits;
    } Counter_Control_1;
    union { 
        Uns32 value;
        struct {
            Uns32 DIS : 1;
            Uns32 INT : 1;
            Uns32 DEC : 1;
            Uns32 MATCH : 1;
            Uns32 RST : 1;
            Uns32 WAVEN : 1;
            Uns32 WAVPOL : 1;
        } bits;
    } Counter_Control_2;
    union { 
        Uns32 value;
        struct {
            Uns32 DIS : 1;
            Uns32 INT : 1;
            Uns32 DEC : 1;
            Uns32 MATCH : 1;
            Uns32 RST : 1;
            Uns32 WAVEN : 1;
            Uns32 WAVPOL : 1;
        } bits;
    } Counter_Control_3;
    union { 
        Uns32 value;
    } Counter_Value_1;
    union { 
        Uns32 value;
    } Counter_Value_2;
    union { 
        Uns32 value;
    } Counter_Value_3;
    union { 
        Uns32 value;
    } Interval_Counter_1;
    union { 
        Uns32 value;
    } Interval_Counter_2;
    union { 
        Uns32 value;
    } Interval_Counter_3;
    union { 
        Uns32 value;
    } Match_1_Counter_1;
    union { 
        Uns32 value;
    } Match_1_Counter_2;
    union { 
        Uns32 value;
    } Match_1_Counter_3;
    union { 
        Uns32 value;
    } Match_2_Counter_1;
    union { 
        Uns32 value;
    } Match_2_Counter_2;
    union { 
        Uns32 value;
    } Match_2_Counter_3;
    union { 
        Uns32 value;
    } Match_3_Counter_1;
    union { 
        Uns32 value;
    } Match_3_Counter_2;
    union { 
        Uns32 value;
    } Match_3_Counter_3;
    union { 
        Uns32 value;
        struct {
            Uns32 IV : 1;
            Uns32 M1 : 1;
            Uns32 M2 : 1;
            Uns32 M3 : 1;
            Uns32 OV : 1;
            Uns32 EV : 1;
        } bits;
    } Interrupt_Register_1;
    union { 
        Uns32 value;
        struct {
            Uns32 IV : 1;
            Uns32 M1 : 1;
            Uns32 M2 : 1;
            Uns32 M3 : 1;
            Uns32 OV : 1;
            Uns32 EV : 1;
        } bits;
    } Interrupt_Register_2;
    union { 
        Uns32 value;
        struct {
            Uns32 IV : 1;
            Uns32 M1 : 1;
            Uns32 M2 : 1;
            Uns32 M3 : 1;
            Uns32 OV : 1;
            Uns32 EV : 1;
        } bits;
    } Interrupt_Register_3;
    union { 
        Uns32 value;
    } Interrupt_Enable_1;
    union { 
        Uns32 value;
    } Interrupt_Enable_2;
    union { 
        Uns32 value;
    } Interrupt_Enable_3;
    union { 
        Uns32 value;
        struct {
            Uns32 EN : 1;
            Uns32 LO : 1;
            Uns32 OV : 1;
        } bits;
    } Event_Control_Timer_1;
    union { 
        Uns32 value;
        struct {
            Uns32 EN : 1;
            Uns32 LO : 1;
            Uns32 OV : 1;
        } bits;
    } Event_Control_Timer_2;
    union { 
        Uns32 value;
        struct {
            Uns32 EN : 1;
            Uns32 LO : 1;
            Uns32 OV : 1;
        } bits;
    } Event_Control_Timer_3;
    union { 
        Uns32 value;
    } Event_Register_1;
    union { 
        Uns32 value;
    } Event_Register_2;
    union { 
        Uns32 value;
    } Event_Register_3;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          int1;
    ppmNetHandle          int2;
    ppmNetHandle          int3;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(rdCurrent1);
PPM_REG_READ_CB(rdCurrent2);
PPM_REG_READ_CB(rdCurrent3);
PPM_REG_READ_CB(rdInt1);
PPM_REG_READ_CB(rdInt2);
PPM_REG_READ_CB(rdInt3);
PPM_REG_WRITE_CB(wrClkCtrl1);
PPM_REG_WRITE_CB(wrClkCtrl2);
PPM_REG_WRITE_CB(wrClkCtrl3);
PPM_REG_WRITE_CB(wrCntrCtrl1);
PPM_REG_WRITE_CB(wrCntrCtrl2);
PPM_REG_WRITE_CB(wrCntrCtrl3);
PPM_REG_WRITE_CB(wrInt);
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
#define BPORT1_AB_BUFFER_SIZE           0x1000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_CLOCK_CONTROL_1_WRMASK  0x7f
#define BPORT1_AB_CLOCK_CONTROL_1_WRNMASK  (0xffffff80)
#define BPORT1_AB_CLOCK_CONTROL_1_WIDTH  32
#define BPORT1_AB_CLOCK_CONTROL_2_WRMASK  0x7f
#define BPORT1_AB_CLOCK_CONTROL_2_WRNMASK  (0xffffff80)
#define BPORT1_AB_CLOCK_CONTROL_2_WIDTH  32
#define BPORT1_AB_CLOCK_CONTROL_3_WRMASK  0x7f
#define BPORT1_AB_CLOCK_CONTROL_3_WRNMASK  (0xffffff80)
#define BPORT1_AB_CLOCK_CONTROL_3_WIDTH  32
#define BPORT1_AB_COUNTER_CONTROL_1_WRMASK  0x7f
#define BPORT1_AB_COUNTER_CONTROL_1_WRNMASK  (0xffffff80)
#define BPORT1_AB_COUNTER_CONTROL_1_WIDTH  32
#define BPORT1_AB_COUNTER_CONTROL_2_WRMASK  0x7f
#define BPORT1_AB_COUNTER_CONTROL_2_WRNMASK  (0xffffff80)
#define BPORT1_AB_COUNTER_CONTROL_2_WIDTH  32
#define BPORT1_AB_COUNTER_CONTROL_3_WRMASK  0x7f
#define BPORT1_AB_COUNTER_CONTROL_3_WRNMASK  (0xffffff80)
#define BPORT1_AB_COUNTER_CONTROL_3_WIDTH  32
#define BPORT1_AB_COUNTER_VALUE_1_WIDTH  32
#define BPORT1_AB_COUNTER_VALUE_2_WIDTH  32
#define BPORT1_AB_COUNTER_VALUE_3_WIDTH  32
#define BPORT1_AB_INTERVAL_COUNTER_1_WIDTH  32
#define BPORT1_AB_INTERVAL_COUNTER_2_WIDTH  32
#define BPORT1_AB_INTERVAL_COUNTER_3_WIDTH  32
#define BPORT1_AB_MATCH_1_COUNTER_1_WIDTH  32
#define BPORT1_AB_MATCH_1_COUNTER_2_WIDTH  32
#define BPORT1_AB_MATCH_1_COUNTER_3_WIDTH  32
#define BPORT1_AB_MATCH_2_COUNTER_1_WIDTH  32
#define BPORT1_AB_MATCH_2_COUNTER_2_WIDTH  32
#define BPORT1_AB_MATCH_2_COUNTER_3_WIDTH  32
#define BPORT1_AB_MATCH_3_COUNTER_1_WIDTH  32
#define BPORT1_AB_MATCH_3_COUNTER_2_WIDTH  32
#define BPORT1_AB_MATCH_3_COUNTER_3_WIDTH  32
#define BPORT1_AB_INTERRUPT_REGISTER_1_WIDTH  32
#define BPORT1_AB_INTERRUPT_REGISTER_2_WIDTH  32
#define BPORT1_AB_INTERRUPT_REGISTER_3_WIDTH  32
#define BPORT1_AB_INTERRUPT_ENABLE_1_WIDTH  32
#define BPORT1_AB_INTERRUPT_ENABLE_2_WIDTH  32
#define BPORT1_AB_INTERRUPT_ENABLE_3_WIDTH  32
#define BPORT1_AB_EVENT_CONTROL_TIMER_1_WIDTH  32
#define BPORT1_AB_EVENT_CONTROL_TIMER_2_WIDTH  32
#define BPORT1_AB_EVENT_CONTROL_TIMER_3_WIDTH  32
#define BPORT1_AB_EVENT_REGISTER_1_WIDTH  32
#define BPORT1_AB_EVENT_REGISTER_2_WIDTH  32
#define BPORT1_AB_EVENT_REGISTER_3_WIDTH  32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

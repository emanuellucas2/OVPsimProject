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

#ifndef PSE_MACROS_IGEN_H
#define PSE_MACROS_IGEN_H               

// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.

// Set the macro 'BPORT1' to the base of port 'bport1'
#ifndef BPORT1
#error BPORT1 is undefined. It needs to be set to the port base address
#endif


#define BPORT1_AB_POFFSET               0x0
#define BPORT1_AB_QOS_CNTL_POFFSET      0x10c
#define BPORT1_AB_QOS_CNTL              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_QOS_CNTL_POFFSET)

#define BPORT1_AB_MAX_OT_POFFSET        0x110
#define BPORT1_AB_MAX_OT                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MAX_OT_POFFSET)

#define BPORT1_AB_MAX_COMB_OT_POFFSET   0x114
#define BPORT1_AB_MAX_COMB_OT           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MAX_COMB_OT_POFFSET)

#define BPORT1_AB_AW_P_POFFSET          0x118
#define BPORT1_AB_AW_P                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AW_P_POFFSET)

#define BPORT1_AB_AW_B_POFFSET          0x11c
#define BPORT1_AB_AW_B                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AW_B_POFFSET)

#define BPORT1_AB_AW_R_POFFSET          0x120
#define BPORT1_AB_AW_R                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AW_R_POFFSET)

#define BPORT1_AB_AR_P_POFFSET          0x124
#define BPORT1_AB_AR_P                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AR_P_POFFSET)

#define BPORT1_AB_AR_B_POFFSET          0x128
#define BPORT1_AB_AR_B                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AR_B_POFFSET)

#define BPORT1_AB_AR_R_POFFSET          0x12c
#define BPORT1_AB_AR_R                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AR_R_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x1000


#endif

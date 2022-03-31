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

// Set the macro 'HOSTIF' to the base of port 'hostif'
#ifndef HOSTIF
#error HOSTIF is undefined. It needs to be set to the port base address
#endif


#define HOSTIF_REG_POFFSET              0x0
#define HOSTIF_REG_STATUS_POFFSET       0x0
#define HOSTIF_REG_STATUS               (HOSTIF + HOSTIF_REG_POFFSET + HOSTIF_REG_STATUS_POFFSET)

#define HOSTIF_REG_COMMAND_POFFSET      0x0
#define HOSTIF_REG_COMMAND              (HOSTIF + HOSTIF_REG_POFFSET + HOSTIF_REG_COMMAND_POFFSET)

#define HOSTIF_REG_INTCLR_POFFSET       0x4
#define HOSTIF_REG_INTCLR               (HOSTIF + HOSTIF_REG_POFFSET + HOSTIF_REG_INTCLR_POFFSET)

#define HOSTIF_REG_INTSTATUS_POFFSET    0x8
#define HOSTIF_REG_INTSTATUS            (HOSTIF + HOSTIF_REG_POFFSET + HOSTIF_REG_INTSTATUS_POFFSET)

#define HOSTIF_REG_NODEID_POFFSET       0x10
#define HOSTIF_REG_NODEID               (HOSTIF + HOSTIF_REG_POFFSET + HOSTIF_REG_NODEID_POFFSET)

#define HOSTIF_REG_HEARTBEAT_POFFSET    0x10
#define HOSTIF_REG_HEARTBEAT            (HOSTIF + HOSTIF_REG_POFFSET + HOSTIF_REG_HEARTBEAT_POFFSET)

#define HOSTIF_REG_SYNCH_POFFSET        0xc
#define HOSTIF_REG_SYNCH                (HOSTIF + HOSTIF_REG_POFFSET + HOSTIF_REG_SYNCH_POFFSET)
#define HOSTIF_REG_SYNCH_BYTES          0x4

#define HOSTIF_REG_MSGLENGTH_POFFSET    0x20
#define HOSTIF_REG_MSGLENGTH            (HOSTIF + HOSTIF_REG_POFFSET + HOSTIF_REG_MSGLENGTH_POFFSET)
#define HOSTIF_REG_MSGLENGTH_BYTES      0x20

#define HOSTIF_REG_MSGSTATUS_POFFSET    0x40
#define HOSTIF_REG_MSGSTATUS            (HOSTIF + HOSTIF_REG_POFFSET + HOSTIF_REG_MSGSTATUS_POFFSET)
#define HOSTIF_REG_MSGSTATUS_BYTES      0x20

#define HOSTIF_OUTBOX_POFFSET           0x8000
#define HOSTIF_OUTBOX_BUF_POFFSET       0x0
#define HOSTIF_OUTBOX_BUF               (HOSTIF + HOSTIF_OUTBOX_POFFSET + HOSTIF_OUTBOX_BUF_POFFSET)
#define HOSTIF_OUTBOX_BUF_BYTES         0x1000

#define HOSTIF_INBOX_POFFSET            0x10000
#define HOSTIF_INBOX_BUF_POFFSET        0x0
#define HOSTIF_INBOX_BUF                (HOSTIF + HOSTIF_INBOX_POFFSET + HOSTIF_INBOX_BUF_POFFSET)
#define HOSTIF_INBOX_BUF_BYTES          0x1000


#endif

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
#define HOSTIF_REG_CONTROL_POFFSET      0x0
#define HOSTIF_REG_CONTROL              (HOSTIF + HOSTIF_REG_POFFSET + HOSTIF_REG_CONTROL_POFFSET)

#define HOSTIF_REG_STATUS_POFFSET       0x4
#define HOSTIF_REG_STATUS               (HOSTIF + HOSTIF_REG_POFFSET + HOSTIF_REG_STATUS_POFFSET)

#define HOSTIF_MSGTX_POFFSET            0x100
#define HOSTIF_MSGTX_ID_POFFSET         0x0
#define HOSTIF_MSGTX_ID                 (HOSTIF + HOSTIF_MSGTX_POFFSET + HOSTIF_MSGTX_ID_POFFSET)

#define HOSTIF_MSGTX_FROM_POFFSET       0x4
#define HOSTIF_MSGTX_FROM               (HOSTIF + HOSTIF_MSGTX_POFFSET + HOSTIF_MSGTX_FROM_POFFSET)

#define HOSTIF_MSGTX_NID_POFFSET        0x8
#define HOSTIF_MSGTX_NID                (HOSTIF + HOSTIF_MSGTX_POFFSET + HOSTIF_MSGTX_NID_POFFSET)

#define HOSTIF_MSGTX_MSGLEN_POFFSET     0xc
#define HOSTIF_MSGTX_MSGLEN             (HOSTIF + HOSTIF_MSGTX_POFFSET + HOSTIF_MSGTX_MSGLEN_POFFSET)

#define HOSTIF_MSGRX_POFFSET            0x200
#define HOSTIF_MSGRX_ID_POFFSET         0x0
#define HOSTIF_MSGRX_ID                 (HOSTIF + HOSTIF_MSGRX_POFFSET + HOSTIF_MSGRX_ID_POFFSET)

#define HOSTIF_MSGRX_FROM_POFFSET       0x4
#define HOSTIF_MSGRX_FROM               (HOSTIF + HOSTIF_MSGRX_POFFSET + HOSTIF_MSGRX_FROM_POFFSET)

#define HOSTIF_MSGRX_NID_POFFSET        0x8
#define HOSTIF_MSGRX_NID                (HOSTIF + HOSTIF_MSGRX_POFFSET + HOSTIF_MSGRX_NID_POFFSET)

#define HOSTIF_MSGRX_MSGLEN_POFFSET     0xc
#define HOSTIF_MSGRX_MSGLEN             (HOSTIF + HOSTIF_MSGRX_POFFSET + HOSTIF_MSGRX_MSGLEN_POFFSET)

#define HOSTIF_MSGTX_MSGBUF_POFFSET     0x10
#define HOSTIF_MSGTX_MSGBUF             (HOSTIF + HOSTIF_MSGTX_POFFSET + HOSTIF_MSGTX_MSGBUF_POFFSET)
#define HOSTIF_MSGTX_MSGBUF_BYTES       0xf0

#define HOSTIF_MSGRX_MSGBUF_POFFSET     0x10
#define HOSTIF_MSGRX_MSGBUF             (HOSTIF + HOSTIF_MSGRX_POFFSET + HOSTIF_MSGRX_MSGBUF_POFFSET)
#define HOSTIF_MSGRX_MSGBUF_BYTES       0xf0


#endif

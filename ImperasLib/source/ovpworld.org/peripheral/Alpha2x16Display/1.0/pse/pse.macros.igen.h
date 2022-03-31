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

// Set the macro 'BUSPORT' to the base of port 'busPort'
#ifndef BUSPORT
#error BUSPORT is undefined. It needs to be set to the port base address
#endif


#define BUSPORT_A_POFFSET               0x0
#define BUSPORT_A_CONTROL_POFFSET       0x0
#define BUSPORT_A_CONTROL               (BUSPORT + BUSPORT_A_POFFSET + BUSPORT_A_CONTROL_POFFSET)
#define BUSPORT_A_CONTROL_INVERT        (0x1 << 3)
#define BUSPORT_A_CONTROL_INVERT_GET(_v)  ((_v >> 3) & 0x1)
#define BUSPORT_A_CONTROL_SET           (0x1 << 2)
#define BUSPORT_A_CONTROL_SET_GET(_v)   ((_v >> 2) & 0x1)
#define BUSPORT_A_CONTROL_CLEAR         (0x1 << 1)
#define BUSPORT_A_CONTROL_CLEAR_GET(_v)  ((_v >> 1) & 0x1)
#define BUSPORT_A_CONTROL_ENABLE        0x1
#define BUSPORT_A_CONTROL_ENABLE_GET(_v)  (_v & 0x1)

#define BUSPORT_A_ADDRESS_POFFSET       0x1
#define BUSPORT_A_ADDRESS               (BUSPORT + BUSPORT_A_POFFSET + BUSPORT_A_ADDRESS_POFFSET)

#define BUSPORT_A_STATUS_POFFSET        0x2
#define BUSPORT_A_STATUS                (BUSPORT + BUSPORT_A_POFFSET + BUSPORT_A_STATUS_POFFSET)
#define BUSPORT_A_STATUS_ENABLE         (0x1 << 1)
#define BUSPORT_A_STATUS_ENABLE_GET(_v)  ((_v >> 1) & 0x1)
#define BUSPORT_A_STATUS_BUSY           0x1
#define BUSPORT_A_STATUS_BUSY_GET(_v)   (_v & 0x1)

#define BUSPORT_A_DATA_POFFSET          0x3
#define BUSPORT_A_DATA                  (BUSPORT + BUSPORT_A_POFFSET + BUSPORT_A_DATA_POFFSET)


#endif

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
#define BPORT1_AB_MAGICVALUE_POFFSET    0x0
#define BPORT1_AB_MAGICVALUE            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MAGICVALUE_POFFSET)

#define BPORT1_AB_VERSION_POFFSET       0x4
#define BPORT1_AB_VERSION               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_VERSION_POFFSET)

#define BPORT1_AB_DEVICEID_POFFSET      0x8
#define BPORT1_AB_DEVICEID              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DEVICEID_POFFSET)

#define BPORT1_AB_VENDORID_POFFSET      0xc
#define BPORT1_AB_VENDORID              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_VENDORID_POFFSET)

#define BPORT1_AB_HOSTFEATURES_POFFSET  0x10
#define BPORT1_AB_HOSTFEATURES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HOSTFEATURES_POFFSET)

#define BPORT1_AB_HOSTFSEL_POFFSET      0x14
#define BPORT1_AB_HOSTFSEL              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HOSTFSEL_POFFSET)

#define BPORT1_AB_GUESTFEATURES_POFFSET  0x20
#define BPORT1_AB_GUESTFEATURES         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GUESTFEATURES_POFFSET)

#define BPORT1_AB_GUESTFSEL_POFFSET     0x24
#define BPORT1_AB_GUESTFSEL             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GUESTFSEL_POFFSET)

#define BPORT1_AB_GUESTPAGESZ_POFFSET   0x28
#define BPORT1_AB_GUESTPAGESZ           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GUESTPAGESZ_POFFSET)

#define BPORT1_AB_QUEUESEL_POFFSET      0x30
#define BPORT1_AB_QUEUESEL              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_QUEUESEL_POFFSET)

#define BPORT1_AB_QUEUENUMMAX_POFFSET   0x34
#define BPORT1_AB_QUEUENUMMAX           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_QUEUENUMMAX_POFFSET)

#define BPORT1_AB_QUEUENUM_POFFSET      0x38
#define BPORT1_AB_QUEUENUM              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_QUEUENUM_POFFSET)

#define BPORT1_AB_QUEUEALIGN_POFFSET    0x3c
#define BPORT1_AB_QUEUEALIGN            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_QUEUEALIGN_POFFSET)

#define BPORT1_AB_QUEUEPFN_POFFSET      0x40
#define BPORT1_AB_QUEUEPFN              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_QUEUEPFN_POFFSET)

#define BPORT1_AB_QUEUENOTIFY_POFFSET   0x50
#define BPORT1_AB_QUEUENOTIFY           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_QUEUENOTIFY_POFFSET)

#define BPORT1_AB_INTSTATUS_POFFSET     0x60
#define BPORT1_AB_INTSTATUS             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTSTATUS_POFFSET)

#define BPORT1_AB_INTACK_POFFSET        0x64
#define BPORT1_AB_INTACK                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTACK_POFFSET)

#define BPORT1_AB_STATUS_POFFSET        0x70
#define BPORT1_AB_STATUS                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STATUS_POFFSET)

#define BPORT1_AB_NETCONFIG_POFFSET     0x100
#define BPORT1_AB_NETCONFIG             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_NETCONFIG_POFFSET)
#define BPORT1_AB_NETCONFIG_BYTES       0x100


#endif

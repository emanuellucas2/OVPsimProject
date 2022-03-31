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

#include "vmi/vmiAttrs.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"
#include "v850Structure.h"
#include "v850VM.h"
#include "v850MPU.h"

VMI_VMINIT_FN(v850VMInit) {
     v850P      v850       = (v850P)processor;
     memDomainP physDomainC = codeDomains[0];
     memDomainP physDomainD = dataDomains[0];
     Uns32      bitsC       = vmirtGetDomainAddressBits(physDomainC);
     Uns32      bitsD       = vmirtGetDomainAddressBits(physDomainD);

     v850->physDomainC = physDomainC;
     v850->physDomainD = physDomainD;

     //
     // Address Range
     //
     Addr lowPA  = 0;
     Addr highPA = -1;

     //
     // RH850G3M has an MPU
     //
     if (v850HasMPU(v850)) {

         memDomainP virtDomainSC     = vmirtNewDomain("virtDomainSC",     bitsC);
         memDomainP virtDomainSD     = vmirtNewDomain("virtDomainSD",     bitsD);
         memDomainP virtDomainSC_MPU = vmirtNewDomain("virtDomainSC_MPU", bitsC);
         memDomainP virtDomainSD_MPU = vmirtNewDomain("virtDomainSD_MPU", bitsD);
         memDomainP virtDomainUC     = vmirtNewDomain("virtDomainUC",     bitsC);
         memDomainP virtDomainUD     = vmirtNewDomain("virtDomainUD",     bitsD);
         memDomainP virtDomainUC_MPU = vmirtNewDomain("virtDomainUC_MPU", bitsC);
         memDomainP virtDomainUD_MPU = vmirtNewDomain("virtDomainUD_MPU", bitsD);

         v850->virtDomainC[RH850_M_SUPERVISOR]     = virtDomainSC;
         v850->virtDomainD[RH850_M_SUPERVISOR]     = virtDomainSD;
         v850->virtDomainC[RH850_M_SUPERVISOR_MPU] = virtDomainSC_MPU;
         v850->virtDomainD[RH850_M_SUPERVISOR_MPU] = virtDomainSD_MPU;
         v850->virtDomainC[RH850_M_USER]           = virtDomainUC;
         v850->virtDomainD[RH850_M_USER]           = virtDomainUD;
         v850->virtDomainC[RH850_M_USER_MPU]       = virtDomainUC_MPU;
         v850->virtDomainD[RH850_M_USER_MPU]       = virtDomainUD_MPU;

         vmirtAliasMemory(physDomainC, virtDomainSC,     lowPA, highPA, 0x00000000, 0);
         vmirtAliasMemory(physDomainD, virtDomainSD,     lowPA, highPA, 0x00000000, 0);
         vmirtAliasMemory(physDomainC, virtDomainSC_MPU, lowPA, highPA, 0x00000000, 0);
         vmirtAliasMemory(physDomainD, virtDomainSD_MPU, lowPA, highPA, 0x00000000, 0);
         vmirtAliasMemory(physDomainC, virtDomainUC,     lowPA, highPA, 0x00000000, 0);
         vmirtAliasMemory(physDomainD, virtDomainUD,     lowPA, highPA, 0x00000000, 0);
         vmirtAliasMemory(physDomainC, virtDomainUC_MPU, lowPA, highPA, 0x00000000, 0);
         vmirtAliasMemory(physDomainD, virtDomainUD_MPU, lowPA, highPA, 0x00000000, 0);

         vmirtProtectMemory(virtDomainSC_MPU, lowPA, highPA, MEM_PRIV_NONE, MEM_PRIV_SET);
         vmirtProtectMemory(virtDomainSD_MPU, lowPA, highPA, MEM_PRIV_NONE, MEM_PRIV_SET);
         vmirtProtectMemory(virtDomainUC_MPU, lowPA, highPA, MEM_PRIV_NONE, MEM_PRIV_SET);
         vmirtProtectMemory(virtDomainUD_MPU, lowPA, highPA, MEM_PRIV_NONE, MEM_PRIV_SET);

         codeDomains[RH850_M_SUPERVISOR]     = virtDomainSC;
         dataDomains[RH850_M_SUPERVISOR]     = virtDomainSD;
         codeDomains[RH850_M_SUPERVISOR_MPU] = virtDomainSC_MPU;
         dataDomains[RH850_M_SUPERVISOR_MPU] = virtDomainSD_MPU;
         codeDomains[RH850_M_USER]           = virtDomainUC;
         dataDomains[RH850_M_USER]           = virtDomainUD;
         codeDomains[RH850_M_USER_MPU]       = virtDomainUC_MPU;
         dataDomains[RH850_M_USER_MPU]       = virtDomainUD_MPU;

     } else {
         //
         // No MPU, Supervisor only
         //
         memDomainP virtDomainSC = vmirtNewDomain("virtDomainSC", bitsC);
         memDomainP virtDomainSD = vmirtNewDomain("virtDomainSD", bitsD);

         v850->virtDomainC[RH850_M_SUPERVISOR] = virtDomainSC;
         v850->virtDomainD[RH850_M_SUPERVISOR] = virtDomainSD;

         vmirtAliasMemory(physDomainC, virtDomainSC, lowPA, highPA, 0x00000000, 0);
         vmirtAliasMemory(physDomainD, virtDomainSD, lowPA, highPA, 0x00000000, 0);

         codeDomains[RH850_M_SUPERVISOR] = virtDomainSC;
         dataDomains[RH850_M_SUPERVISOR] = virtDomainSD;
     }
}


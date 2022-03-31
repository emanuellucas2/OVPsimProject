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

#include <string.h>
#include "vmi/vmiAttrs.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "ppc32Ports.h"
#include "ppc32Bus.h"
#include "ppc32Decode.h"
#include "ppc32Doc.h"
#include "ppc32Structure.h"
#include "ppc32Parameters.h"
#include "ppc32SPR.h"
#include "ppc32MorphFP.h"

VMI_CONSTRUCTOR_FN(ppc32Constructor) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32ParamValuesP params = (ppc32ParamValuesP)parameterValues;

    ppc32->flags = vmirtProcessorFlags(processor);
    ppc32->configInfo = ppc32ConfigTable[params->variant];
    if (ppc32->configInfo.name == NULL) {
        // Assign value as First Variant
        ppc32->configInfo = ppc32ConfigTable[0];
    }
    Int32 iter;
    for (iter=0; iter<32; iter++) {
        ppc32->GPR[iter] = 0;
    }
    for (iter=0; iter<32; iter++) {
        ppc32->FPR[iter] = 0;
    }
    for (iter=0; iter<32; iter++) {
        ppc32->VR[iter] = 0;
    }
    ppc32->CR.reg = 0x0; // readonly=0
    ppc32->CR_wmask.reg = ~0;
    ppc32->CR_rmask.reg = ~0;
    ppc32->XER_SO = 0; // readonly=0
    ppc32->XER_OV = 0; // readonly=0
    ppc32->XER_CA = 0; // readonly=0
    for (iter=0; iter<8; iter++) {
        ppc32->LT[iter] = 0;
    }
    for (iter=0; iter<8; iter++) {
        ppc32->GT[iter] = 0;
    }
    for (iter=0; iter<8; iter++) {
        ppc32->EQ[iter] = 0;
    }
    for (iter=0; iter<8; iter++) {
        ppc32->SO[iter] = 0;
    }
    for (iter=0; iter<4; iter++) {
        ppc32->TEMP[iter] = 0;
    }

    ppc32->iendian = params->SETBIT(endian) ? params->endian : MEM_ENDIAN_BIG;
    ppc32->dendian = params->SETBIT(endian) ? params->endian : MEM_ENDIAN_BIG;
    ppc32->exception = ppc32_E_Reset;

    // Store the parameters for later retrieval
    ppc32->params.UISA_I_B = params->UISA_I_B;
    ppc32->params.UISA_I_BCDA = params->UISA_I_BCDA;
    ppc32->params.UISA_I_S = params->UISA_I_S;
    ppc32->params.UISA_I_E = params->UISA_I_E;
    ppc32->params.UISA_I_E_PC = params->UISA_I_E_PC;
    ppc32->params.UISA_I_E_PD = params->UISA_I_E_PD;
    ppc32->params.UISA_I_EC = params->UISA_I_EC;
    ppc32->params.UISA_I_FP = params->UISA_I_FP;
    ppc32->params.UISA_I_DFP = params->UISA_I_DFP;
    ppc32->params.UISA_I_MA = params->UISA_I_MA;
    ppc32->params.UISA_I_SP = params->UISA_I_SP;
    ppc32->params.UISA_I_V = params->UISA_I_V;
    ppc32->params.UISA_I_LMA = params->UISA_I_LMA;
    ppc32->params.UISA_I_WT = params->UISA_I_WT;
    ppc32->params.UISA_I_VLE = params->UISA_I_VLE;
    ppc32->params.ENABLE_FPU = params->ENABLE_FPU;
    ppc32->params.UNIMP_TO_NOP = params->UNIMP_TO_NOP;
    ppc32->params.WARN_NOP = params->WARN_NOP;

    // allocate net port descriptions
    ppc32NewNetPorts(ppc32);

    // Allocate Bus Port Descriptors
    ppc32NewBusPorts(ppc32);

    // Call the Doc Generator
    ppc32Doc(processor, params);

    // Link the Decoder CallBack
    ppc32->decoder = ppc32Decode;

    //
    // Allocate and initialize the SPRs
    //
    ppc32AllocSPR(ppc32);
    ppc32InitSPR(ppc32);
    ppc32->SPRdelta = (UnsPS)(ppc32->SPR) - (UnsPS)ppc32;

    //
    // Initialize FPU (if present)
    //
    ppc32ConfigureFPU(ppc32);
}

VMI_DESTRUCTOR_FN(ppc32Destructor) {
    ppc32P ppc32 = (ppc32P)processor;

    // Free Net/Bus Port Descriptors
    ppc32FreeBusPorts(ppc32);
    ppc32FreeNetPorts(ppc32);
}

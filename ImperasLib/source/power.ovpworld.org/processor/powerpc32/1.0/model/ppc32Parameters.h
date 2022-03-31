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

#ifndef PPC32_PARAMETERS_H
#define PPC32_PARAMETERS_H

#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"

#include "ppc32TypeRefs.h"

//
// Define the attributes value structure
//
typedef struct ppc32ParamValuesS {

    VMI_ENUM_PARAM(variant);
    VMI_BOOL_PARAM(verbose);
    VMI_ENDIAN_PARAM(endian);
    VMI_BOOL_PARAM(UISA_I_B);
    VMI_BOOL_PARAM(UISA_I_BCDA);
    VMI_BOOL_PARAM(UISA_I_S);
    VMI_BOOL_PARAM(UISA_I_E);
    VMI_BOOL_PARAM(UISA_I_E_PC);
    VMI_BOOL_PARAM(UISA_I_E_PD);
    VMI_BOOL_PARAM(UISA_I_EC);
    VMI_BOOL_PARAM(UISA_I_FP);
    VMI_BOOL_PARAM(UISA_I_DFP);
    VMI_BOOL_PARAM(UISA_I_MA);
    VMI_BOOL_PARAM(UISA_I_SP);
    VMI_BOOL_PARAM(UISA_I_V);
    VMI_BOOL_PARAM(UISA_I_LMA);
    VMI_BOOL_PARAM(UISA_I_WT);
    VMI_BOOL_PARAM(UISA_I_VLE);
    VMI_UNS32_PARAM(ENABLE_FPU);
    VMI_BOOL_PARAM(UNIMP_TO_NOP);
    VMI_BOOL_PARAM(WARN_NOP);
} ppc32ParamValues, *ppc32ParamValuesP;

#endif // PPC32_PARAMETERS_H

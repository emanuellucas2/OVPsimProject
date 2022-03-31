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

#ifndef V850_PARAMETERS_H
#define V850_PARAMETERS_H

#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"

#include "v850TypeRefs.h"

//
// Define the attributes value structure
//
typedef struct v850ParamValuesS {

    VMI_ENUM_PARAM(variant);
    VMI_BOOL_PARAM(verbose);
    VMI_ENDIAN_PARAM(endian);
    VMI_BOOL_PARAM(GDBSIMMODE);
    VMI_BOOL_PARAM(nofpu);
    VMI_UNS32_PARAM(RBASE);
    VMI_BOOL_PARAM(ucbank);
    VMI_UNS32_PARAM(PEID);
    VMI_UNS32_PARAM(SPID);

} v850ParamValues, *v850ParamValuesP;

#endif // V850_PARAMETERS_H

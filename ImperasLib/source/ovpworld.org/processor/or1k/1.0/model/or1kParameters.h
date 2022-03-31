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

#ifndef OR1K_PARAMETERS_H
#define OR1K_PARAMETERS_H

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"

//
// Define the attributes value structure
//
typedef struct or1kParamValuesS {

    VMI_BOOL_PARAM(fifos);
    VMI_BOOL_PARAM(verbose);

    // Only provides a single variant 'Generic'
    VMI_ENUM_PARAM(variant);

} or1kParamValues, *or1kParamValuesP;

#endif

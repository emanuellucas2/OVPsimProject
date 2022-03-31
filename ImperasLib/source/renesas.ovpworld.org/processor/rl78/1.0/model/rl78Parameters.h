/*
 * Copyright (c)      2016 eSOL TRINITY, www.esol-trinity.co.jp
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


#ifndef RL78_PARAMETERS_H
#define RL78_PARAMETERS_H

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"

//
// Define the attributes value structure
//
typedef struct rl78ParamValuesS {

    VMI_ENUM_PARAM(variant);
    VMI_BOOL_PARAM(verbose);
    VMI_BOOL_PARAM(sim_ac_flag);
    VMI_BOOL_PARAM(exit_on_halt);
    VMI_UNS32_PARAM(mirror_rom_addr);
    VMI_UNS32_PARAM(mirror_start_addr);
    VMI_UNS32_PARAM(mirror_end_addr);

} rl78ParamValues, *rl78ParamValuesP;

enum en_variant {
    en_RL78_S1 = 1,
    en_RL78_S2 = 2,
    en_RL78_S3 = 3,
};

#endif

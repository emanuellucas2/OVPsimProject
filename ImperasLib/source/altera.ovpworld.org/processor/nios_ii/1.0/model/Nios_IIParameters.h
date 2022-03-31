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

#ifndef NIOS_II_PARAMETERS_H
#define NIOS_II_PARAMETERS_H

#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"

#include "Nios_IITypeRefs.h"

//
// Define the attributes value structure
//
typedef struct Nios_IIParamValuesS {

    VMI_ENUM_PARAM(variant);
    VMI_BOOL_PARAM(verbose);
    VMI_ENDIAN_PARAM(endian);
    VMI_BOOL_PARAM(TEST_MODE_EXIT);
    VMI_BOOL_PARAM(TEST_HALT_EXIT);
    VMI_UNS32_PARAM(INST_ADDR_WIDTH);
    VMI_UNS32_PARAM(DATA_ADDR_WIDTH);
    VMI_BOOL_PARAM(HW_MULTIPLY);
    VMI_BOOL_PARAM(HW_MULX);
    VMI_BOOL_PARAM(HW_DIVIDE);
    VMI_UNS32_PARAM(RESET_VECTOR);
    VMI_UNS32_PARAM(EXCEPTION_VECTOR);
    VMI_UNS32_PARAM(BREAK_VECTOR);
    VMI_BOOL_PARAM(INCLUDE_MMU);
    VMI_UNS32_PARAM(FAST_TLB_MISS_EXCEPTION_VECTOR);
    VMI_BOOL_PARAM(INCLUDE_MPU);
    VMI_BOOL_PARAM(INCLUDE_CPURESETREQUEST);
    VMI_BOOL_PARAM(INCLUDE_CPURESETTAKEN);
    VMI_UNS32_PARAM(CPUID_CONTROL_VALUE);
    VMI_BOOL_PARAM(EXCEPTION_ILLEGAL_INSTRUCTION);
    VMI_BOOL_PARAM(EXCEPTION_DIVISION_ERROR);
    VMI_BOOL_PARAM(EXCEPTION_MISALIGNED_MEMORY_ACCESS);
    VMI_BOOL_PARAM(EXCEPTION_EXTRA_INFORMATION);
    VMI_ENUM_PARAM(INTERRUPT_CONTROLLER_INTERFACE);
    VMI_UNS32_PARAM(NUMBER_SHADOW_REGISTER_SETS);
    VMI_BOOL_PARAM(HARDCOPY_COMPATIBILITY);
    VMI_UNS32_PARAM(MMU_PID_BITS);
    VMI_BOOL_PARAM(MMU_OPTIMIZE_NUMBER_OF_TLB_ENTRIES);
    VMI_ENUM_PARAM(MMU_TLB_ENTRIES);
    VMI_ENUM_PARAM(MMU_TLB_SET_ASSOCIATIVITY);
    VMI_UNS32_PARAM(MMU_MICRO_DTLB_ENTRIES);
    VMI_UNS32_PARAM(MMU_MICRO_ITLB_ENTRIES);
    VMI_BOOL_PARAM(MPU_USE_LIMIT_FOR_REGION_RANGE);
    VMI_UNS32_PARAM(MPU_NUMBER_DATA_REGIONS);
    VMI_UNS32_PARAM(MPU_MINIMUM_DATA_REGION_SIZE);
    VMI_UNS32_PARAM(MPU_NUMBER_INSTRUCTION_REGIONS);
    VMI_UNS32_PARAM(MPU_MINIMUM_INSTRUCTION_REGION_SIZE);
    VMI_BOOL_PARAM(CUSTOM_FP_DIVISION);
    VMI_BOOL_PARAM(CUSTOM_BITSWAP);
    VMI_BOOL_PARAM(CUSTOM_ENDIAN_CONVERT);
    VMI_BOOL_PARAM(CUSTOM_INTERRUPT_VECTOR);

} Nios_IIParamValues, *Nios_IIParamValuesP;

#endif // NIOS_II_PARAMETERS_H

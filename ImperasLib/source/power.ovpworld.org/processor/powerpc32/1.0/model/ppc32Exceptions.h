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

#ifndef PPC32_EXCEPTIONS_H
#define PPC32_EXCEPTIONS_H
#include "vmi/vmiAttrs.h"
#include "ppc32Structure.h"

typedef enum ppc32ExceptionMask {
    EXC_CRITICAL_INPUT                   = 0x0000000000000001ULL,
    EXC_MACHINE_CHECK                    = 0x0000000000000002ULL,
    EXC_DATA_STORAGE                     = 0x0000000000000004ULL,
    EXC_INSTRUCTION_STORAGE              = 0x0000000000000008ULL,
    EXC_EXTERNAL                         = 0x0000000000000010ULL,
    EXC_ALIGNMENT                        = 0x0000000000000020ULL,
    EXC_PROGRAM                          = 0x0000000000000040ULL,
    EXC_FLOATING_POINT_UNAVAILABLE       = 0x0000000000000080ULL,
    EXC_SYSTEM_CALL                      = 0x0000000000000100ULL,
    EXC_AUXILLIARY_PROCESSOR_UNAVAILABLE = 0x0000000000000200ULL,
    EXC_DECREMENTER                      = 0x0000000000000400ULL,
    EXC_FIXED_INTERVAL_TIMER             = 0x0000000000000800ULL,
    EXC_WATCHDOG_TIMER                   = 0x0000000000001000ULL,
    EXC_DATA_TLB_ERROR                   = 0x0000000000002000ULL,
    EXC_INSTRUCTION_TLB_ERROR            = 0x0000000000004000ULL,
    EXC_DEBUG                            = 0x0000000000008000ULL,
    // gap
    EXC_SPE_FP_VECTOR_UNAVAILABLE        = 0x0000000100000000ULL,
    EXC_FP_DATA_INTERRUPT                = 0x0000000200000000ULL,
    EXC_FP_ROUND_INTERRUPT               = 0x0000000400000000ULL,
    EXC_PERFORMANCE_MONITOR              = 0x0000000800000000ULL,
    EXC_PROCESSOR_DOORBELL               = 0x0000001000000000ULL,
    EXC_PROCESSOR_DOORBELL_CRITICAL      = 0x0000002000000000ULL,
} ppc32ExceptionMask;

#define RESET_VECTOR 0xFFFFFFFC

void ppc32ProcessException (vmiProcessorP processor, Addr address, Uns64 exc);

#endif // PPC32_EXCEPTIONS_H

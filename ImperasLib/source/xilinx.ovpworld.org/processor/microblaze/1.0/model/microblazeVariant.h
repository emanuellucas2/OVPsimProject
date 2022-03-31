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

#ifndef MICROBLAZE_VARIANT_H
#define MICROBLAZE_VARIANT_H

typedef enum microblazeArchitectureE {
    //
    // UISA use for User defined Instruction Set combination
    //
    UISA         = 0x00000001,

    //
    // Base Enumerated Architecture types
    //
    ISA_V7_00    = 0x00000002,
    ISA_V7_10    = 0x00000004,
    ISA_V7_20    = 0x00000008,
    ISA_V7_30    = 0x00000010,
    ISA_V8_00    = 0x00000020,
    ISA_V8_10    = 0x00000040,
    ISA_V8_20    = 0x00000080,
    ISA_V9_50    = 0x00000100,
    ISA_V10_00   = 0x00000200,

    //
    // Compound Enumerated Architecture types
    //
    V7_00        = 0x00000400 | ISA_V7_00,
    V7_10        = 0x00000800 | ISA_V7_00 | ISA_V7_10,
    V7_20        = 0x00001000 | ISA_V7_00 | ISA_V7_10 | ISA_V7_20,
    V7_30        = 0x00002000 | ISA_V7_00 | ISA_V7_10 | ISA_V7_20 | ISA_V7_30,
    V8_00        = 0x00004000 | ISA_V7_00 | ISA_V7_10 | ISA_V7_20 | ISA_V7_30 | ISA_V8_00,
    V8_10        = 0x00008000 | ISA_V7_00 | ISA_V7_10 | ISA_V7_20 | ISA_V7_30 | ISA_V8_00 | ISA_V8_10,
    V8_20        = 0x00010000 | ISA_V7_00 | ISA_V7_10 | ISA_V7_20 | ISA_V7_30 | ISA_V8_00 | ISA_V8_10 | ISA_V8_20,
    V9_50        = 0x00020000 | ISA_V7_00 | ISA_V7_10 | ISA_V7_20 | ISA_V7_30 | ISA_V8_00 | ISA_V8_10 | ISA_V8_20 | ISA_V9_50,
    V10_00       = 0x00040000 | ISA_V7_00 | ISA_V7_10 | ISA_V7_20 | ISA_V7_30 | ISA_V8_00 | ISA_V8_10 | ISA_V8_20 | ISA_V9_50 | ISA_V10_00,
} microblazeArchitecture;

#endif // MICROBLAZE_VARIANT_H

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

#pragma once

#include "peripheral/impTypes.h"

// Structure for the GUID (aka UUID) in GPT format Disk Image files
// See https://tools.ietf.org/html/rfc4122#section-4.1
typedef struct guidS {
    Uns32   timeLow;
    Uns16   timeMid;
    Uns16   timeHi;
    Uns8    clkSeqHi;
    Uns8    clkSeqLow;
    Uns8    node[6];
} guidT, *guidP;

//
// Read a partition from a GPT disk image file into simulated memory
// - Search for a partition in the disk image file whose type matches partitionType
// - Read the partition into simulated memory at loadAddress
// Return 1 on success, 0 on error
//
Bool readPartition(const char *imageFN, guidP partitionType, Addr loadAddress);

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

#ifndef RL78UTILS_H
#define RL78UTILS_H

// model header files
#include "rl78Exceptions.h"                // rl78Exception


//typedef struct rl78S rl78, *rl78P;        // rl78Structure.h


Uns8 rl78GetPSW_REG(rl78P rl78);
void rl78SetPSW_BIT(rl78P rl78);

void rl78TakeException(rl78P rl78, rl78Exception exception, Uns32 pcOffset);
void rl78Reset(rl78P rl78);

void snprint_hex(char* buf, Uns32 n, const void* value, Uns32 bytes);
void dumpRAM(vmiProcessorP processor);

#endif

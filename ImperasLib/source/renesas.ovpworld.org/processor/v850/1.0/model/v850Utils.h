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

#ifndef V850_UTILS_H
#define V850_UTILS_H

// basic number types
#include "hostapi/impTypes.h"

// model header files
#include "v850TypeRefs.h"
#include "v850Structure.h"

Uns32 v850PackPSW(v850P v850);
void  v850UnPackPSW(v850P v850);

Uns32 v850PackEFG(v850P v850);
void  v850UnPackEFG(v850P v850);

Uns32 v850PackECR(v850P v850);
void  v850UnPackECR(v850P v850);

Uns32 v850PackFPSR(v850P v850);
void  v850UnPackFPSR(v850P v850);

void v850UnPackFPST(v850P v850);
Uns32 v850PackFPST(v850P v850);

void v850UnPackFPCC(v850P v850);
Uns32 v850PackFPCC(v850P v850);

void v850UnPackFPCFG(v850P v850);
Uns32 v850PackFPCFG(v850P v850);

#endif /*V850_UTILS_H*/

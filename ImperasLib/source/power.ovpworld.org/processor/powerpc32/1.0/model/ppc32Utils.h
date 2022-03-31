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

#ifndef PPC32_UTILS_H
#define PPC32_UTILS_H
#include "vmi/vmiTypes.h"

//
// Packing and Unpacking Functions
//
void ppc32PackCR(ppc32P ppc32);
void ppc32UnpackCR(ppc32P ppc32);
void ppc32PackFPSCR(ppc32P ppc32);
void ppc32UnpackFPSCR(ppc32P ppc32);
void ppc32PackMSR(ppc32P ppc32);
void ppc32UnpackMSR(ppc32P ppc32);
void ppc32PackXER(ppc32P ppc32);
void ppc32UnpackXER(ppc32P ppc32);
void ppc32PackRegs(ppc32P ppc32);
void ppc32UnpackRegs(ppc32P ppc32);

void ppc32MaskEnable64(Uns64 *mask, Bool Enable, Uns64 left, Uns64 right);

#endif /*PPC32_UTILS_H*/

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

#ifndef PPC32_BUS_H
#define PPC32_BUS_H

// Model header files
#include "ppc32TypeRefs.h"

//
// Allocate bus port specifications
//
void ppc32NewBusPorts(ppc32P ppc32);

//
// Free bus port specifications
//
void ppc32FreeBusPorts(ppc32P ppc32);

#endif /* PPC32_BUS_H */

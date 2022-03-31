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

#ifndef PPC32_CONFIG_H
#define PPC32_CONFIG_H
#include "hostapi/impTypes.h"
#include "ppc32TypeRefs.h"
#include "ppc32Variant.h"

typedef struct ppc32ConfigS {
    const char       *name;
    ppc32Architecture arch;
    Uns32             pvr;
} ppc32Config;

DEFINE_CS(ppc32Config);
extern const struct ppc32ConfigS ppc32ConfigTable[];
#endif // PPC32_CONFIG_H

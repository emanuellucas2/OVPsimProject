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

#include "ppc32Config.h"
#include "ppc32Variant.h"

const struct ppc32ConfigS ppc32ConfigTable[] = {
    ////////////////////////////////////////////////////////////////////////////
    // ISA CONFIGURATIONS
    ////////////////////////////////////////////////////////////////////////////
    {.name = "m476", .arch = VARIANT_M476, .pvr = 0x11a50000},
    {.name = "m470", .arch = VARIANT_M470, .pvr = 0x00000000},
    {.name = "m460", .arch = VARIANT_M460, .pvr = 0x00000000},
    {.name = "m440", .arch = VARIANT_M440, .pvr = 0x00000000},
    {0} // null terminator
};


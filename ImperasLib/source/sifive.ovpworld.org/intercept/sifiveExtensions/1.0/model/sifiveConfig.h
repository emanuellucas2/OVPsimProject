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

// Imperas header files
#include "hostapi/impTypes.h"

// extension header files
#include "sifiveTypeRefs.h"
#include "sifiveVariant.h"

// Unique ID for SiFive OVPworld model extension
#define SIFIVE_OVP_CONFIG_ID (('S' << 8) + 'O')

//
// This is used to define extension configuration options
//
typedef struct sifiveConfigS {

    sifiveVariant variant;

} sifiveConfig;

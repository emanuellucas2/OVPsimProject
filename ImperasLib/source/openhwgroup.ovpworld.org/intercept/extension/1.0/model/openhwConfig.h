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
#include "openhwTypeRefs.h"

//
// Unique ID for Mellanox OVPworld model extension
//
#define OPENHW_OVP_CONFIG_ID (('O' << 8) + 'P')

typedef enum openhwFeatureE {

    OHWF_NA        = 0x0,   // no features
    OHWF_PMA16     = 0x1,   // is static 16-entry PMA available?
    OHWF_BUS_FAULT = 0x2,   // custom bus fault exceptions implemented?

} openhwFeature;

//
// This is used to define extension configuration options
//
typedef struct openhwConfigS {

    openhwFeature features;

} openhwConfig;

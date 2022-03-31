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

//
// Primary cache parameters: number of bits for ways, number of bits of address
// per line, number of bits per tag
//
#define CACHE_WRITEBACK   1
#define CACHE_WAYS        1
#define CACHE_LINE_BITS   5
#define CACHE_TAG_BITS    11
#define MODEL_NAME        "wb_1way_32byteline_2048tags"

//
// Include cache inplementation
//
#include "cache.h"

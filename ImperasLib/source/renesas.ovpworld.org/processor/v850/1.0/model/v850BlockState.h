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

#ifndef V850_BLOCK_STATE_H
#define V850_BLOCK_STATE_H

// VMI header files
#include "vmi/vmiTypes.h"

// model header files
#include "v850TypeRefs.h"

//
// This structure holds state for a code block as it is morphed
//
typedef struct v850BlockStateS {
    Bool jmpIsCall;     // is what appears to be a jump actually a call?
} v850BlockState;

#endif

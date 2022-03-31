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

#ifndef PLB_BUS_H
#define PLB_BUS_H
#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"

//
// Reorganize word for Big/Little Endian and correct size
//
Uns32 toLittleEndian (Uns32 val, Uns8 bytes) {
    Uns32 rval = 0;
    //
    // Swap Endian to Little
    //
    rval = SWAP_4_BYTE(val);
    //
    // Mask upper bytes
    //
    Uns32 mask = -1 >> (bytes * 8);
    rval &= mask;
    return rval;
}

Uns32 toBigEndian (Uns32 val, Uns8 bytes) {
    Uns32 rval = 0;
    //
    // Swap Endian to Big
    //
    rval = SWAP_4_BYTE(val);
    //
    // Mask upper bytes
    //
    Uns32 mask = -1 << (bytes * 8);
    rval &= mask;
    return rval;
}

#define GETLE(_e,_v) (_e ? toLittleEndian(_v, bytes): _v)
#define GETBE(_e,_v) (_e ? toBigEndian(_v, bytes): _v)

#endif

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


////////////////////////////////////////////////////////////////////////////////
// DATA FOR 32-BIT INSTRUCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Attribute entries for 32-bit instructions like CFLUSH
//
#define ATTR32_CFLUSH(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1,              \
    type     : S5_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_19_15,          \
}

//
// Attribute entries for 32-bit instructions like CEASE
//
#define ATTR32_CEASE(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_NONE,            \
    type     : S5_IT_##_GENERIC,    \
    arch     : _ARCH,               \
}

//
// Attribute entries for 32-bit instructions like LAST
//
#define ATTR32_LAST(_NAME, _GENERIC, _OPCODE) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    format   : FMT_NONE,            \
    type     : S5_IT_##_GENERIC     \
}


/*
 * Copyright (c)      2016 eSOL TRINITY, www.esol-trinity.co.jp
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

#include "vmi/vmiMessage.h"        // vmiMessage


#define RL78_IDENT    "RL78"


#define MY_ASSERT(bol_cond, txt_mesg)    \
    if (bol_cond == 0) {                 \
        vmiMessage("A", RL78_IDENT, "MY_ASSERT @ %s(%d) : %s\n", __FILE__, __LINE__, txt_mesg);    \
        *((int*) 0) = 1;                 \
    }


#define MY_MESSAGE(rl78_cpu, severity, ...)                      \
    switch (severity[0]) {                                       \
        case 'I':                                                \
        case 'T':                                                \
            if (rl78_cpu->verbose != 0) {                        \
                vmiMessage(severity, RL78_IDENT, __VA_ARGS__);   \
            }                                                    \
            break;                                               \
        case 'W':                                                \
        case 'E':                                                \
        case 'F':                                                \
        case 'A':                                                \
        default:                                                 \
            vmiMessage(severity, RL78_IDENT, __VA_ARGS__);       \
            break;                                               \
    }

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

#ifndef RL78EXCEPTIONS_H
#define RL78EXCEPTIONS_H

#include "vmi/vmiDbg.h"     // vmiExceptionInfo

//typedef struct rl78S rl78, *rl78P;        // rl78Structure.h



typedef enum rl78ExceptionE {
    RL78_EXCPT_RST,         // reset
    RL78_EXCPT_TRP,         // Execution of illegal instruction
    RL78_EXCPT_IAW,         // Illegal memory access
    RL78_EXCPT_BRK,         // system call
    RL78_EXCPT_IRQ,         // external interrupt
    RL78_EXCPT_LAST         // KEEP LAST: for sizing
} rl78Exception;


//
// Exception vector addresses
//
#define RST_ADDRESS 0x0000  // RESET vector
#define IAW_ADDRESS 0x0000
#define BRK_ADDRESS 0x007E  // sys exception vector
#define IRQ_ADDRESS 0xFFFF  // external interrupt exception vector


const vmiExceptionInfo exceptions[RL78_EXCPT_LAST];


////
//// Ensure any pending interrupt is taken before the next instruction
////
//void rl78InterruptNext(rl78P rl78);



#endif

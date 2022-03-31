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

#ifndef OR1KEXCEPTIONTYPES_H
#define OR1KEXCEPTIONTYPES_H

//
// Exception types
//
typedef enum or1kExceptionE {
    OR1K_EXCPT_RST,         // reset
    OR1K_EXCPT_BUS,         // alignment
    OR1K_EXCPT_DPF,         // data privilege
    OR1K_EXCPT_IPF,         // instruction privilege
    OR1K_EXCPT_TTI,         // tick timer
    OR1K_EXCPT_ILL,         // illegal instruction
    OR1K_EXCPT_EXI,         // external interrupt
    OR1K_EXCPT_SYS,         // system call
    OR1K_EXCPT_LAST         // KEEP LAST: for sizing
} or1kException;

//
// Exception vector addresses
//
#define RST_ADDRESS 0x100   // reset exception vector
#define BUS_ADDRESS 0x200   // alignment exception vector
#define DPF_ADDRESS 0x300   // data privilege exception vector
#define IPF_ADDRESS 0x400   // instruction privilege exception vector
#define TTI_ADDRESS 0x500   // tick timer exception vector
#define ILL_ADDRESS 0x700   // illegal instruction exception vector
#define EXI_ADDRESS 0x800   // external interrupt exception vector
#define SYS_ADDRESS 0xc00   // sys exception vector

#endif

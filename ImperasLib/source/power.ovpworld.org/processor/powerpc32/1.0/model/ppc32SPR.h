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

#ifndef PPC32_SPR_H
#define PPC32_SPR_H
#include "vmi/vmiTypes.h"

#define DEFSPRIF1(_RETURN,_NAME,_VAR,_ARGS) _RETURN _NAME##_##_VAR _ARGS;
#define DEFSPRIF(_VAR)  \
    DEFSPRIF1(void,  ppc32AllocSPR,       _VAR, (ppc32P ppc32))                                      \
    DEFSPRIF1(void,  ppc32InitSPR,        _VAR, (ppc32P ppc32))                                      \
                                                                                                     \
    DEFSPRIF1(void,  ppc32mtspr,          _VAR, (ppc32P ppc32, Uns16 spr, vmiReg gpr_rs, Uns8   rs)) \
    DEFSPRIF1(void,  ppc32mfspr,          _VAR, (ppc32P ppc32, Uns8   rt, vmiReg gpr_rt, Uns16 spr)) \
    DEFSPRIF1(void,  ppc32mtmsr,          _VAR, (ppc32P ppc32, Uns8    l, vmiReg gpr_rs, Uns8   rs)) \
    DEFSPRIF1(void,  ppc32mfmsr,          _VAR, (ppc32P ppc32,            vmiReg gpr_rt, Uns8   rt)) \
    DEFSPRIF1(void,  ppc32wrteei,         _VAR, (ppc32P ppc32,                           Uns8    e)) \
    DEFSPRIF1(void,  ppc32wrtee,          _VAR, (ppc32P ppc32,            vmiReg gpr_rs, Uns8   rs)) \
                                                                                                     \
    DEFSPRIF1(Uns32, ppc32ReadSPR,        _VAR, (ppc32P ppc32, Uns32 index))                         \
    DEFSPRIF1(void,  ppc32WriteSPR,       _VAR, (ppc32P ppc32, Uns32 index, Uns32 value))            \
    DEFSPRIF1(Uns32, ppc32ReadMSR,        _VAR, (ppc32P ppc32))                                      \
    DEFSPRIF1(void,  ppc32WriteMSR,       _VAR, (ppc32P ppc32, Uns32 value))                         \
    DEFSPRIF1(Uns8,  ppc32ReadMSR_VMMode, _VAR, (ppc32P ppc32))                                      \
    DEFSPRIF1(Bool,  ppc32IsUserMode,     _VAR, (ppc32P ppc32))                                      \
    DEFSPRIF1(Bool,  ppc32IsPrivMode,     _VAR, (ppc32P ppc32))                                      \
    DEFSPRIF1(Bool,  ppc32IsHypvMode,     _VAR, (ppc32P ppc32))

void  ppc32AllocSPR(ppc32P ppc32);
void  ppc32InitSPR(ppc32P  ppc32);

void  ppc32mtspr (ppc32P ppc32, Uns16 spr, vmiReg gpr_rs,  Uns8  rs);
void  ppc32mfspr (ppc32P ppc32, Uns8   rt, vmiReg gpr_rt, Uns16 spr);
void  ppc32mtmsr (ppc32P ppc32, Uns8    l, vmiReg gpr_rs,  Uns8  rs);
void  ppc32mfmsr (ppc32P ppc32,            vmiReg gpr_rt,  Uns8  rt);
void  ppc32wrteei(ppc32P ppc32,                            Uns8   e);
void  ppc32wrtee (ppc32P ppc32,            vmiReg gpr_rs,  Uns8  rs);

Uns32 ppc32ReadSPR(ppc32P  ppc32, Uns32 index);
void  ppc32WriteSPR(ppc32P ppc32, Uns32 index, Uns32 value);
Uns32 ppc32ReadMSR(ppc32P  ppc32);
void  ppc32WriteMSR(ppc32P ppc32, Uns32 value);
Uns8  ppc32ReadMSR_VMMode(ppc32P  ppc32);
Bool  ppc32IsUserMode(ppc32P ppc32);
Bool  ppc32IsPrivMode(ppc32P ppc32);
Bool  ppc32IsHypvMode(ppc32P ppc32);

#endif /*PPC32_SPR_H*/

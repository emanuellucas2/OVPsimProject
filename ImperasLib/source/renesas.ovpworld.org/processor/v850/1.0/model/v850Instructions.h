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

#ifndef V850_INSTRUCTIONS_H
#define V850_INSTRUCTIONS_H

//
// Macros to perform shift, mask, sign/zero extend and bit extraction
//

// mask out _VEC from _HI and above
#define MASK(_VEC, _HI) (((Uns64)_VEC) & ((1<<(_HI))-1))

// strip _VEC, _HI downto _LO, and position at _ORIGIN
#define VECINDEX(_VEC,_HI,_LO,_ORIGIN) (((Uns64) -1 >> (63 - (_HI) + (_LO))) & (((Uns64)_VEC) >> (_LO))) << _ORIGIN

// Sign extend _VEC, from _POS all the way to left
#define SEXTEND(_VEC,_POS) ((Int64)(0x8000000000000000ULL & (((Uns64)_VEC) << (63 - (_POS)))) >> (63 - (_POS))) | ((Uns64)_VEC)

// ZERO extend _VEC, after _POS all the way left
#define ZERO(_VEC,_POS) ((Uns64)(((Uns64)_VEC) << (63 - (_POS))) >> (31 - (_POS)))

// SHIFTL _VEC _SHIFT
#define SHIFTL(_VEC,_SHIFT) ((Uns64)(((Uns64)_VEC) << (_SHIFT)))

// SHIFTR _VEC _SHIFT
#define SHIFTR(_VEC,_SHIFT) ((Uns64)(((Uns64)_VEC) >> (_SHIFT)))

//
// MorphTime/RunTime move to/from system register macros
//
#define MT_MFSREG(_GPR, _SREG) { \
    Uns32 mask = getSPRMask(state->v850, V850_## _SREG ## _RMASK); \
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND, _GPR, V850_## _SREG ##_RD, mask, 0); \
}

#define MT_MTSREG(_SREG, _GPR) { \
    Uns32 mask = getSPRMask(state->v850, V850_## _SREG ## _WMASK); \
    vmimtRegNotReadR(V850_GPR_BITS, V850_## _SREG ##_RD); \
    vmimtBinopRC (V850_GPR_BITS, vmi_ANDN, V850_## _SREG ##_WR,  mask,           0); \
    vmimtBinopRRC(V850_GPR_BITS, vmi_AND,  V850_TMP_WR(0), _GPR, mask,           0); \
    vmimtBinopRR (V850_GPR_BITS, vmi_OR,   V850_## _SREG ##_WR,  V850_TMP_WR(0), 0); \
}

#define RT_MFSREG(GPR, SREG) \
    if (GPR) \
    v850->gpr[GPR] = v850->SPR_ ## SREG .reg & v850->SPR_ ## SREG ## _rmask.reg;

#define RT_MTSREG(SREG, GPR) { \
    Uns32 mask    = v850->SPR_ ## SREG ## _wmask.reg; \
    Uns32 prevREG = v850->SPR_ ## SREG .reg & ~mask;  \
    Uns32 nextREG = v850->gpr[GPR]          &  mask;  \
    v850->SPR_ ## SREG .reg = prevREG | nextREG;      \
}

#endif // V850_INSTRUCTIONS_H

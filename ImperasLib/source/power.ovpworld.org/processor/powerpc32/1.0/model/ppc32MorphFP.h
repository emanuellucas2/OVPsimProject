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

#ifndef PPC32_MORPHFP_H
#define PPC32_MORPHFP_H

// VMI header files
#include "vmi/vmiTypes.h"
#include "vmi/vmiDbg.h"

// sign [00]
// exp  [01:11]
// frac [12:63]
typedef union {
    Uns64 r64;
    Flt64 f64;
    struct {
        Uns64 frac : 52;
        Uns64  exp : 11;
        Uns64 sign :  1;
    } bits;
} doubleT;

typedef union {
    Uns32 r32;
    Flt32 f32;
    struct {
        Uns32 frac : 23;
        Uns32  exp :  8;
        Uns32 sign :  1;
    } bits;
} singleT;

typedef enum {
    FPUOP_None,
    FPUOP_ConvertRR,
    FPUOP_UnopRR,
    FPUOP_BinopRRR,
    FPUOP_TernopRRRR,
    FPUOP_CompareRR,
    FPUOP_FRSP,
    FPUOP_Store,
    FPUOP_Load
} ppc32fpuOpTypeE;

//
// Set simulator floating point control word
//
void ppc32UpdateFPControlWord(ppc32P ppc32);

//
// Configure FPU
//
void ppc32ConfigureFPU(ppc32P ppc32);

//
// Function for special Rounding control on frsp
//
Uns8 ppc32RoundingDFP_TO_SFP(ppc32P ppc32, Uns32 FRT, Uns32 FRB);

//
// Floating point masks
//
#define PPC32_DFP_QNAN_MASK  0x7FF8000000000000ULL
#define PPC32_DFP_SNAN_MASK  0x7FF0000000000000ULL
#define PPC32_SFP_QNAN_MASK  0x7FC00000
#define PPC32_SFP_SNAN_MASK  0x7F800000

#define PPC32_DFP_QUIET_MASK 0x0008000000000000ULL
#define PPC32_SFP_QUIET_MASK 0x00400000

#define PPC32_DFP_SIGN_MASK  0x8000000000000000ULL
#define PPC32_SFP_SIGN_MASK  0x80000000

//
// Signalling Nan range - ignoring sign bit
//
#define PPC32_DFP_SNAN_MAX   0x7FF7FFFFFFFFFFFFULL
#define PPC32_DFP_SNAN_MIN   0x7FF0000000000001ULL
#define PPC32_SFP_SNAN_MAX   0x7FBFFFFF
#define PPC32_SFP_SNAN_MIN   0x7F800001

#define PPC32_DFP_POS_INF    0x7FF0000000000000ULL
#define PPC32_DFP_NEG_INF    0xFFF0000000000000ULL

//
// Quiet Nan range - ignoring sign bit
//
#define PPC32_DFP_QNAN_MAX   0x7FFFFFFFFFFFFFFFULL
#define PPC32_DFP_QNAN_MIN   0x7FF8000000000000ULL
#define PPC32_SFP_QNAN_MAX   0x7FFFFFFF
#define PPC32_SFP_QNAN_MIN   0x7FC00000

#define PPC32_SFP_SIGN(_arg)      ((_arg >> 31) & 0x1)
#define PPC32_SFP_EXPONENT(_arg)  ((_arg >> 23) & 0xFF)
#define PPC32_SFP_MANTISSA(_arg)  ((_arg >> 0)  & 0x7FFFFF)
#define PPC32_DFP_SIGN(_arg)      ((_arg >> 63) & 0x1)
#define PPC32_DFP_EXPONENT(_arg)  ((_arg >> 52) & 0x7FF)
#define PPC32_DFP_MANTISSA(_arg)  ((_arg >> 0)  & 0xFFFFFFFFFFFFFULL)

#define IS_PPC32_SFP_NAN(_arg)    (PPC32_SFP_EXPONENT(_arg)==0xFF  && PPC32_SFP_MANTISSA(_arg)!=0)
#define IS_PPC32_SFP_INF(_arg)    (PPC32_SFP_EXPONENT(_arg)==0xFF  && PPC32_SFP_MANTISSA(_arg)==0)
#define IS_PPC32_SFP_DNORM(_arg)  (PPC32_SFP_EXPONENT(_arg)==0x00  && PPC32_SFP_MANTISSA(_arg)!=0)
#define IS_PPC32_SFP_ZERO(_arg)   (PPC32_SFP_EXPONENT(_arg)==0x00  && PPC32_SFP_MANTISSA(_arg)==0)
#define IS_PPC32_SFP_POS(_arg)    (PPC32_SFP_SIGN(_arg)==0x0)
#define IS_PPC32_SFP_NEG(_arg)    (PPC32_SFP_SIGN(_arg)==0x1)
#define IS_PPC32_SFP_SNAN(_arg)   (IS_PPC32_SFP_NAN(_arg) && !(PPC32_SFP_MANTISSA(_arg) & PPC32_SFP_QUIET_MASK))
#define IS_PPC32_SFP_QNAN(_arg)   (IS_PPC32_SFP_NAN(_arg) &&  (PPC32_SFP_MANTISSA(_arg) & PPC32_SFP_QUIET_MASK))

#define IS_PPC32_DFP_NAN(_arg)    (PPC32_DFP_EXPONENT(_arg)==0x7FF && PPC32_DFP_MANTISSA(_arg)!=0ULL)
#define IS_PPC32_DFP_INF(_arg)    (PPC32_DFP_EXPONENT(_arg)==0x7FF && PPC32_DFP_MANTISSA(_arg)==0ULL)
#define IS_PPC32_DFP_DNORM(_arg)  (PPC32_DFP_EXPONENT(_arg)==0x000 && PPC32_DFP_MANTISSA(_arg)!=0ULL)
#define IS_PPC32_DFP_ZERO(_arg)   (PPC32_DFP_EXPONENT(_arg)==0x000 && PPC32_DFP_MANTISSA(_arg)==0ULL)
#define IS_PPC32_DFP_POS(_arg)    (PPC32_DFP_SIGN(_arg)==0x0)
#define IS_PPC32_DFP_NEG(_arg)    (PPC32_DFP_SIGN(_arg)==0x1)
#define IS_PPC32_DFP_SNAN(_arg)   (IS_PPC32_DFP_NAN(_arg) && !(PPC32_DFP_MANTISSA(_arg) & PPC32_DFP_QUIET_MASK))
#define IS_PPC32_DFP_QNAN(_arg)   (IS_PPC32_DFP_NAN(_arg) &&  (PPC32_DFP_MANTISSA(_arg) & PPC32_DFP_QUIET_MASK))

#define PPC32_MIN_INT64 0x8000000000000000ULL
#define PPC32_MIN_UNS64 0x0000000000000000ULL
#define PPC32_MAX_INT64 0x7FFFFFFFFFFFFFFFULL
#define PPC32_MAX_UNS64 0xFFFFFFFFFFFFFFFFULL
#define PPC32_MIN_INT32 0x80000000
#define PPC32_MIN_UNS32 0x00000000
#define PPC32_MAX_INT32 0x7FFFFFFF
#define PPC32_MAX_UNS32 0xFFFFFFFF

//
// vmiFPFlags indices
//
#define FPFLAGS_I 0x01
#define FPFLAGS_D 0x02
#define FPFLAGS_Z 0x04
#define FPFLAGS_O 0x08
#define FPFLAGS_U 0x10
#define FPFLAGS_P 0x20

//
// Relation Flags
//
#define FPUREL_UN 0x1
#define FPUREL_EQ 0x2
#define FPUREL_LT 0x4
#define FPUREL_GT 0x8

#endif // PPC32_MORPHFP_H

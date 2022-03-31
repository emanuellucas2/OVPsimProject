/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */


#ifndef OCLIATYPES_H
#define OCLIATYPES_H

#include "hostapi/impTypes.h"
#include "hostapi/memTyperefs.h"
#include "ocl/ocliaTyperefs.h"


////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

/// This defines unary operation types
typedef enum octiaUnopE {
    OCL_UN_MOV    , ///< d = a
    OCL_UN_SWP    , ///< d = byteswap(a)
    OCL_UN_NEG    , ///< d = -a
    OCL_UN_ABS    , ///< d = (a<0) ? -a : a
    OCL_UN_NEGSQ  , ///< d = saturate_signed(-a)
    OCL_UN_ABSSQ  , ///< d = (a<0) ? saturate_signed(-a) : a
    OCL_UN_NOT    , ///< d = ~a
    OCL_UN_RBIT   , ///< d = bit_reverse(a)
    OCL_UN_CNTZ   , ///< d = count_zeros(a)
    OCL_UN_CNTO   , ///< d = count_ones(a)
    OCL_UN_CLS    , ///< d = count_leading_sign(a)
    OCL_UN_CLZ    , ///< d = count_leading_zeros(a)
    OCL_UN_CLO    , ///< d = count_leading_ones(a)
    OCL_UN_CTZ    , ///< d = count_trailing_zeros(a)
    OCL_UN_CTO    , ///< d = count_trailing_ones(a)
    OCL_UN_BSFZ   , ///< d = least_significant_zero_index(a)
    OCL_UN_BSFO   , ///< d = most_significant_zero_index(a)
    OCL_UN_BSRZ   , ///< d = most_significant_zero_index(a)
    OCL_UN_BSRO   , ///< d = most_significant_one_index(a)
    OCL_UN_AESMC  , ///< d = AES_mix_columns(a)
    OCL_UN_AESIMC , ///< d = AES_inverse_mix_columns(a)
    OCL_UN_LAST     ///< KEEP LAST
} octiaUnop;

/// This defines binary operation types
typedef enum octiaBinopE {
    OCL_BIN_ADD      , ///< d = a + b
    OCL_BIN_ADC      , ///< d = a + b + C
    OCL_BIN_SUB      , ///< d = a - b
    OCL_BIN_SBB      , ///< d = a - b - C
    OCL_BIN_RSBB     , ///< d = b - a - C
    OCL_BIN_RSUB     , ///< d = b - a
    OCL_BIN_IMUL     , ///< d = a * b (signed)
    OCL_BIN_MUL      , ///< d = a * b (unsigned)
    OCL_BIN_IDIV     , ///< d = a / b (signed)
    OCL_BIN_DIV      , ///< d = a / b (unsigned)
    OCL_BIN_IREM     , ///< d = a % b (signed)
    OCL_BIN_REM      , ///< d = a % b (unsigned)
    OCL_BIN_CMP      , ///< a - b
    OCL_BIN_ADDSQ    , ///< d = saturate_signed(a + b)
    OCL_BIN_ADCSQ    , ///< d = saturate_signed(a + b + C)
    OCL_BIN_SUBSQ    , ///< d = saturate_signed(a - b)
    OCL_BIN_SBBSQ    , ///< d = saturate_signed(a - b - C)
    OCL_BIN_RSUBSQ   , ///< d = saturate_signed(b - a)
    OCL_BIN_RSBBSQ   , ///< d = saturate_signed(b - a - C)
    OCL_BIN_ADDUQ    , ///< d = saturate_unsigned(a + b)
    OCL_BIN_ADCUQ    , ///< d = saturate_unsigned(a + b + C)
    OCL_BIN_SUBUQ    , ///< d = saturate_unsigned(a - b)
    OCL_BIN_SBBUQ    , ///< d = saturate_unsigned(a - b - C)
    OCL_BIN_RSUBUQ   , ///< d = saturate_unsigned(b - a)
    OCL_BIN_RSBBUQ   , ///< d = saturate_unsigned(b - a - C)
    OCL_BIN_ADDSH    , ///< d = ((signed)(a + b)) / 2
    OCL_BIN_SUBSH    , ///< d = ((signed)(a - b)) / 2
    OCL_BIN_RSUBSH   , ///< d = ((signed)(b - a)) / 2
    OCL_BIN_ADDUH    , ///< d = ((unsigned)(a + b)) / 2
    OCL_BIN_SUBUH    , ///< d = ((unsigned)(a - b)) / 2
    OCL_BIN_RSUBUH   , ///< d = ((unsigned)(b - a)) / 2
    OCL_BIN_ADDSHR   , ///< d = round(((signed)(a + b)) / 2)
    OCL_BIN_SUBSHR   , ///< d = round(((signed)(a - b)) / 2)
    OCL_BIN_RSUBSHR  , ///< d = round(((signed)(b - a)) / 2)
    OCL_BIN_ADDUHR   , ///< d = round(((unsigned)(a + b)) / 2)
    OCL_BIN_SUBUHR   , ///< d = round(((unsigned)(a - b)) / 2)
    OCL_BIN_RSUBUHR  , ///< d = round(((unsigned)(b - a)) / 2)
    OCL_BIN_OR       , ///< d = a | b
    OCL_BIN_AND      , ///< d = a & b
    OCL_BIN_XOR      , ///< d = a ^ b
    OCL_BIN_ORN      , ///< d = a | ~b
    OCL_BIN_ANDN     , ///< d = a & ~b
    OCL_BIN_XORN     , ///< d = a ^ ~b
    OCL_BIN_NOR      , ///< d = ~(a | b)
    OCL_BIN_NAND     , ///< d = ~(a & b)
    OCL_BIN_XNOR     , ///< d = ~(a ^ b)
    OCL_BIN_ROL      , ///< d = a << b | a >> [bits]-b
    OCL_BIN_ROR      , ///< d = a >> b | a << [bits]-b
    OCL_BIN_RCL      , ///< (d,c) = (a,c) << b | (a,c) >> [bits]-b
    OCL_BIN_RCR      , ///< (d,c) = (a,c) >> b | (a,c) << [bits]-b
    OCL_BIN_SHL      , ///< d = a << b
    OCL_BIN_SHR      , ///< d = (unsigned)a >> b
    OCL_BIN_SAR      , ///< (signed)a >> b
    OCL_BIN_SHLSQ    , ///< d = saturate_signed(a << b)
    OCL_BIN_SHLUQ    , ///< d = saturate_unsigned(a << b)
    OCL_BIN_SHRR     , ///< d = round((unsigned)a >> b)
    OCL_BIN_SARR     , ///< d = round((signed)a >> b)
    OCL_BIN_IMIN     , ///< d = min_signed(a, b)
    OCL_BIN_MIN      , ///< d = min_unsigned(a, b)
    OCL_BIN_IMAX     , ///< d = max_signed(a, b)
    OCL_BIN_MAX      , ///< d = max_unsigned(a, b)
    OCL_BIN_IMULSU   , ///< d = a (signed) * b (unsigned)
    OCL_BIN_IMULUS   , ///< d = a (unsigned) * b (signed)
    OCL_BIN_PMUL     , ///< d = a * b (carryless)
    OCL_BIN_AESENC1  , ///< d = AES_encrypt1(a), not last round
    OCL_BIN_AESENC1L , ///< d = AES_encrypt1(a), last round
    OCL_BIN_AESDEC1  , ///< d = AES_decrypt1(a), not last round
    OCL_BIN_AESDEC1L , ///< d = AES_decrypt1(a), last round
    OCL_BIN_AESENC2  , ///< d = AES_encrypt2(a), not last round
    OCL_BIN_AESENC2L , ///< d = AES_encrypt2(a), last round
    OCL_BIN_AESDEC2  , ///< d = AES_decrypt2(a), not last round
    OCL_BIN_AESDEC2L , ///< d = AES_decrypt2(a), last round
    OCL_BIN_LAST       ///< KEEP LAST
} octiaBinop;

/// This defines bit operation types
typedef enum octiaBitopE {
    OCL_BIT_BT   , ///< bit test
    OCL_BIT_BTR  , ///< bit test and reset
    OCL_BIT_BTS  , ///< bit test and set
    OCL_BIT_BTC  , ///< bit test and complement
    OCL_BIT_LAST   ///< KEEP LAST
} octiaBitop;

/// Hint for jump types (call/return pairing and relative jump indication)
typedef enum octiaJumpHintE {
    OCL_JH_NONE     = 0x00, ///< no jump hint
    OCL_JH_CALL     = 0x01, ///< call
    OCL_JH_RETURN   = 0x02, ///< return
    OCL_JH_INT      = 0x04, ///< interrupt
    OCL_JH_RELATIVE = 0x08  ///< target is relative
} octiaJumpHint;

/// This defines the type of an address expression
typedef enum octiaAddrExpTypeE {
    OCL_ET_UNKNOWN , ///< unknown value
    OCL_ET_CONST   , ///< constant value
    OCL_ET_REG     , ///< register value
    OCL_ET_EXTEND  , ///< extended value
    OCL_ET_UNARY   , ///< unary value
    OCL_ET_BINARY  , ///< binary value
    OCL_ET_LOAD      ///< load from address
} octiaAddrExpType;

/// This type selects data recorded when gathering information about a processor
/// instruction
typedef enum octiaDataSelectE {
    OCL_DS_NONE    = 0x00, ///< empty mask
    OCL_DS_NODES   = 0x01, ///< record node list
    OCL_DS_REG_R   = 0x02, ///< record debug interface registers read
    OCL_DS_REG_W   = 0x04, ///< record debug interface registers written
    OCL_DS_RANGE_R = 0x08, ///< record field ranges read (and not registers)
    OCL_DS_RANGE_W = 0x10, ///< record field ranges written (and not registers)
    OCL_DS_FETCH   = 0x20, ///< record fetch ranges
    OCL_DS_NEXTPC  = 0x40, ///< record next PC expressions
    OCL_DS_ADDRESS = 0x80  ///< record load/store address expressions
} octiaDataSelect;

/// This defines the type of a memory access
typedef enum octiaMemAccessTypeE {
    OCL_MAT_LOAD       , ///< Load
    OCL_MAT_STORE      , ///< Store
    OCL_MAT_PRELOAD_LD , ///< Preload for likely load
    OCL_MAT_PRELOAD_ST , ///< Preload for likely store
    OCL_MAT_PRELOAD_EX   ///< Preload for likely fetch
} octiaMemAccessType;

/// The class of instruction
typedef enum octiaInstructionClassE {
    OCL_IC_NONE        = 0x0                                             , ///< no class information
    OCL_IC_NOP         = 1ULL<<0                                         , ///< explicit NOP
    OCL_IC_INTEGER     = 1ULL<<1                                         , ///< instruction uses integer ALU
    OCL_IC_FLOAT       = 1ULL<<2                                         , ///< instruction uses FPU
    OCL_IC_DSP         = 1ULL<<3                                         , ///< instruction uses DSP
    OCL_IC_MULTIPLY    = 1ULL<<4                                         , ///< instruction implements multiply
    OCL_IC_DIVIDE      = 1ULL<<5                                         , ///< instruction implements divide
    OCL_IC_FMA         = 1ULL<<6                                         , ///< instruction implements
                                                                           ///  fused-multiply-add
    OCL_IC_SIMD        = 1ULL<<7                                         , ///< instruction implements SIMD
                                                                           ///  operation
    OCL_IC_TRIG        = 1ULL<<8                                         , ///< instruction implements
                                                                           ///  trigonometric operation
    OCL_IC_LOG         = 1ULL<<9                                         , ///< instruction implements logarithmic
                                                                           ///  operation
    OCL_IC_RECIP       = 1ULL<<10                                        , ///< instruction implements reciprocal
                                                                           ///  operation
    OCL_IC_SQRT        = 1ULL<<11                                        , ///< instruction implements square root
                                                                           ///  operation
    OCL_IC_SYSREG      = 1ULL<<12                                        , ///< instruction accesses system
                                                                           ///  register state
    OCL_IC_IBARRIER    = 1ULL<<13                                        , ///< instruction barrier
    OCL_IC_DBARRIER    = 1ULL<<14                                        , ///< data barrier
    OCL_IC_ABARRIER    = 1ULL<<15                                        , ///< artifact barrier
    OCL_IC_ICACHE      = 1ULL<<16                                        , ///< instruction cache maintenance
    OCL_IC_DCACHE      = 1ULL<<17                                        , ///< data cache maintenance
    OCL_IC_MMU         = 1ULL<<18                                        , ///< memory management unit operation
    OCL_IC_ATOMIC      = 1ULL<<19                                        , ///< instruction implements atomic
                                                                           ///  operation
    OCL_IC_EXCLUSIVE   = 1ULL<<20                                        , ///< instruction implements exclusive
                                                                           ///  operation
    OCL_IC_HINT        = 1ULL<<21                                        , ///< hint instruction
    OCL_IC_SYSTEM      = 1ULL<<22                                        , ///< system instruction
    OCL_IC_FCONVERT    = 1ULL<<23                                        , ///< instruction implements floating
                                                                           ///  point conversion
    OCL_IC_FCOMPARE    = 1ULL<<24                                        , ///< instruction implements floating
                                                                           ///  point comparison
    OCL_IC_BRANCH      = 1ULL<<25                                        , ///< instruction implements branch
                                                                           ///  operation
    OCL_IC_BRANCH_DS   = 1ULL<<26                                        , ///< instruction implements branch
                                                                           ///  operation with delay slot
    OCL_IC_BRANCH_DSA  = 1ULL<<27                                        , ///< instruction implements branch
                                                                           ///  operation with annulled delay slot
                                                                           ///  (if not taken)
    OCL_IC_OPAQUE_INT  = 1ULL<<28                                        , ///< instruction is subject to opaque
                                                                           ///  intercept
    OCL_IC_VECTOR      = 1ULL<<29                                        , ///< instruction implements vector
                                                                           ///  operation
    OCL_IC_CRYPTO      = 1ULL<<30                                        , ///< instruction implements
                                                                           ///  cryptographic operation
    OCL_IC_BRANCH_MASK = OCL_IC_BRANCH|OCL_IC_BRANCH_DS|OCL_IC_BRANCH_DSA, ///< instruction implements any branch
                                                                           ///  operation
    OCL_IC_UCACHE      = OCL_IC_ICACHE|OCL_IC_DCACHE                     , ///< instruction implements any cache
                                                                           ///  operation
    OCL_IC_RSQRT       = OCL_IC_RECIP|OCL_IC_SQRT                        , ///< instruction implements reciprocal
                                                                           ///  square root operation
    OCL_IC_RESERVED1   = 1ULL<<31                                        , ///< start range for future class
                                                                           ///  extensions
    OCL_IC_RESERVEDN   = 1ULL<<47                                        , ///< end range for future class
                                                                           ///  extensions
    OCL_IC_CUSTOM1     = 1ULL<<48                                        , ///< custom class 1
    OCL_IC_CUSTOM2     = 1ULL<<49                                        , ///< custom class 2
    OCL_IC_CUSTOM3     = 1ULL<<50                                        , ///< custom class 3
    OCL_IC_CUSTOM4     = 1ULL<<51                                        , ///< custom class 4
    OCL_IC_CUSTOM5     = 1ULL<<52                                        , ///< custom class 5
    OCL_IC_CUSTOM6     = 1ULL<<53                                        , ///< custom class 6
    OCL_IC_CUSTOM7     = 1ULL<<54                                        , ///< custom class 7
    OCL_IC_CUSTOM8     = 1ULL<<55                                        , ///< custom class 8
    OCL_IC_CUSTOM9     = 1ULL<<56                                        , ///< custom class 9
    OCL_IC_CUSTOM10    = 1ULL<<57                                        , ///< custom class 10
    OCL_IC_CUSTOM11    = 1ULL<<58                                        , ///< custom class 11
    OCL_IC_CUSTOM12    = 1ULL<<59                                        , ///< custom class 12
    OCL_IC_CUSTOM13    = 1ULL<<60                                        , ///< custom class 13
    OCL_IC_CUSTOM14    = 1ULL<<61                                        , ///< custom class 14
    OCL_IC_CUSTOM15    = 1ULL<<62                                        , ///< custom class 15
    OCL_IC_CUSTOM16    = 1ULL<<63                                          ///< custom class 16
} octiaInstructionClass;

/// Register description (used by JIT code generator)
typedef enum octiaRegTypeE {
    OCL_RT_NOREG      = 0, ///< no register
    OCL_RT_NORMAL     = 1, ///< normal register
    OCL_RT_FUNCRESULT = 3  ///< register holding function result
} octiaRegType;

/// Register state (used by JIT code generator)
typedef enum octiaRegStateE {
    OCL_RS_LIVE      = 0, ///< register is live
    OCL_RS_WRITEBACK = 1, ///< register must be written back
    OCL_RS_KILL      = 2  ///< register can be killed
} octiaRegState;


////////////////////////////////////////////////////////////////////////////////
// Public structures
////////////////////////////////////////////////////////////////////////////////

/// @struct octiaAddrExpExtendS
/// Extend address expression

typedef struct octiaAddrExpExtendS {
    Bool          signExtend; ///< is extension signed?
    octiaAddrExpP child     ; ///< child expression
} octiaAddrExpExtend;

/// @struct octiaAddrExpUnaryS
/// Unary address expression

typedef struct octiaAddrExpUnaryS {
    octiaUnop     op    ; ///< unary operation type
    const char *  opName; ///< unary operation name
    octiaAddrExpP child ; ///< unary operation name
} octiaAddrExpUnary;

/// @struct octiaAddrExpBinaryS
/// Binary address expression

typedef struct octiaAddrExpBinaryS {
    octiaBinop    op      ; ///< binary operation type
    const char *  opName  ; ///< binary operation name
    octiaAddrExpP child[2]; ///< children expressions
} octiaAddrExpBinary;

/// @struct octiaAddrExpLoadS
/// Load address expression

typedef struct octiaAddrExpLoadS {
    memDomainP    domain; ///< domain for load
    octiaAddrExpP child ; ///< address expression in domain
} octiaAddrExpLoad;

/// @struct octiaAddrExpS
/// Address expression

typedef struct octiaAddrExpS {
    octiaAddrExpType type; ///< expression type
    Uns32            bits; ///< expression bit size
    union {
        Offset             c; ///< if type==OCL_ET_CONST
        octiaRegInfoP      r; ///< if type==OCL_ET_REG
        octiaAddrExpExtend e; ///< if type==OCL_ET_EXTEND
        octiaAddrExpUnary  u; ///< if type==OCL_ET_UNARY
        octiaAddrExpBinary b; ///< if type==OCL_ET_BINARY
        octiaAddrExpLoad   l; ///< if type==OCL_ET_LOAD
    };

} octiaAddrExp;


#endif /* OCLIATYPES_H */


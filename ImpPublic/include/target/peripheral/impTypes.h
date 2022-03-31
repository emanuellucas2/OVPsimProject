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

#ifndef IMPTYPES_H
#define IMPTYPES_H

#include <sys/types.h>

// fixed width types
typedef signed char            SChar;
typedef unsigned char          UChar;
typedef signed char            Int8;
typedef unsigned char          Uns8;
typedef short                  Int16;
typedef unsigned short         Uns16;
typedef int                    Int32;
typedef unsigned int           Uns32;
typedef long long int          Int64;
typedef unsigned long long int Uns64;
typedef float                  Flt32;
typedef double                 Flt64;

// Boolean data types
#if defined(__cplusplus)
    typedef bool  Bool;
    #define False false
    #define True  true
#else
    typedef _Bool Bool;
    #define False ((Bool)0)
    #define True  ((Bool)1)
#endif

// common to all toolchains
typedef Uns64         Addr;

#if (__LP64__==1)
    typedef Uns64     UnsPS;
    typedef Int64     Offset;
#else
    typedef Uns32     UnsPS;
    typedef Int32     Offset;
#endif

#define PTR_TO_UNS32(_P)    ((Uns32)(UnsPS)(_P))
#define PTR_TO_UNS64(_P)    ((Uns64)(UnsPS)(_P))
#define PTR_TO_INT32(_P)    ((Int32)(UnsPS)(_P))
#define PTR_TO_INT64(_P)    ((Int64)(UnsPS)(_P))
#define UNS32_TO_PTR(_U32)  ((void*)(UnsPS)(_U32))

//
// 2 byte endian swap
//
#define SWAP_2_BYTE(_V) \
    ({                                                              \
        Uns16 _R16;                                                 \
        Uns16 _V16 = _V;                                            \
        _R16 = (((_V16)<<8) | ((_V16)>>8));                         \
        _R16;                                                       \
    })

//
// 4 byte endian swap
//
#define SWAP_4_BYTE(_V) \
    ({                                                              \
        Uns32 _R32;                                                 \
        Uns32 _V32 = _V;                                            \
        _R32 = ((SWAP_2_BYTE(_V32)<<16) | (SWAP_2_BYTE(_V32>>16))); \
        _R32;                                                       \
    })

//
// 2 byte conditional endian swap
//
#define SWAP_2_BYTE_COND(_V, _DO_SWAP) \
    ({                                                              \
        Uns16 _V16C = _V;                                           \
        _DO_SWAP ? SWAP_2_BYTE(_V16C) : _V16C;                      \
    })

//
// 4 byte conditional endian swap
//
#define SWAP_4_BYTE_COND(_V, _DO_SWAP) \
    ({                                                              \
        Uns32 _V32C = _V;                                           \
        _DO_SWAP ? SWAP_4_BYTE(_V32C) : _V32C;                      \
    })

//
// Use this to prevent inline/clone of intercepted functions
//
#define NOINLINE __attribute__((noinline))
#define NOCLONE  __attribute__((noclone))
#ifndef FNINTCPT
#  if(__riscv==1)
#    define FNINTCPT NOINLINE NOCLONE
#  else
#    define FNINTCPT NOINLINE
#  endif
#endif

//
// Trap any non-intercepted functions which were intended to be trapped
//
#define FUNCTOHOST(_RETURN, _NAME, ...) \
    _RETURN FNINTCPT _NAME (__VA_ARGS__) { \
        bhmMessage("E", "FUNCTOHOST", "Failed to intercept Function (%s)%s(%s)\n", \
            #_RETURN, #_NAME, #__VA_ARGS__); \
        return (_RETURN)0; \
    }

#endif /*IMPTYPES_H*/

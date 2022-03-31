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

typedef signed char    SChar;
typedef unsigned char  UChar;
typedef signed char    Int8;
typedef unsigned char  Uns8;
typedef __int16_t      Int16;
typedef __uint16_t     Uns16;
typedef __int32_t      Int32;
typedef __uint32_t     Uns32;
typedef __int64_t      Int64;
typedef __uint64_t     Uns64;
typedef double         Flt64;
typedef unsigned char  Bool;

#define False          ((Bool)0)
#define True           ((Bool)1)

#endif /*IMPTYPES_H*/

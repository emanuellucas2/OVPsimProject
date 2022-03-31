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

#ifndef IMP_ALLOC_H
#define IMP_ALLOC_H

#include <stdlib.h>

//
// Wrappers for standard allocators using a type instead of a size.
//
#define STYPE_ALLOC(_TYPE) \
    (_TYPE*)malloc(sizeof(_TYPE))

#define STYPE_ALLOC_N( _TYPE, _N) \
    (_TYPE*)malloc( ((_N) * sizeof(_TYPE)))

#define STYPE_CALLOC( _TYPE) \
    (_TYPE*)calloc( 1, sizeof(_TYPE))

#define STYPE_CALLOC_N( _TYPE, _N) \
    (_TYPE*)calloc((_N), sizeof(_TYPE))

#define STYPE_FREE( _P) \
    {const void *pointer = _P; free((void *)pointer);}

#endif /*IMP_ALLOC_H*/

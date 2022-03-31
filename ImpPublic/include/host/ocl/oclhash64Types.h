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


#ifndef OCLHASH64TYPES_H
#define OCLHASH64TYPES_H

#include "hostapi/impTypes.h"
#include "ocl/oclhash64Typerefs.h"

////////////////////////////////////////////////////////////////////////////////
// Callbacks
////////////////////////////////////////////////////////////////////////////////

/// This function is called for each entry found

/// @par Parameters:
/// @par
/// @a hash64 The hash entry
/// @par
/// @a userData User data passed to the iterator function

#define OCL_HASH64_FN(_name) \
void _name ( \
    octHash64P hash64, \
    void *     userData)

/// This is a pointer to a function of the type defined by OCL_HASH64_FN

typedef OCL_HASH64_FN((*octHash64Fn));


#endif /* OCLHASH64TYPES_H */


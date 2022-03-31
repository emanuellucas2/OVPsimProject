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


#ifndef OCLSYMBOLTYPES_H
#define OCLSYMBOLTYPES_H

#include "hostapi/impTypes.h"
#include "hostapi/memTyperefs.h"
#include "ocl/oclSymbolTyperefs.h"

////////////////////////////////////////////////////////////////////////////////
// Callbacks
////////////////////////////////////////////////////////////////////////////////

/// This function is called for each symbol found

/// @par Parameters:
/// @par
/// @a symbol The symbol
/// @par
/// @a userData User data passed to the iterator function

#define OCL_SYMBOL_FN(_name) \
void _name ( \
    octSymbolP symbol, \
    void *     userData)

/// This is a pointer to a function of the type defined by OCL_SYMBOL_FN

typedef OCL_SYMBOL_FN((*octSymbolFn));


#endif /* OCLSYMBOLTYPES_H */


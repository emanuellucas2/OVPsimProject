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


#ifndef OCLAPPSYMBOL_H
#define OCLAPPSYMBOL_H

#include "ocl/oclASTyperefs.h"
#include "ocl/oclASTypes.h"

////////////////////////////////////////////////////////////////////////////////
// OCL_AS Functions
////////////////////////////////////////////////////////////////////////////////

/// Return the symbol address
/// @return The address
/// @param symbol The given symbol

Addr oclASAddress (
    octASSymbolP symbol
);

/// Return the symbol binding
/// @return The type
/// @param symbol The given symbol

ordSymbolBinding oclASBinding (
    octASSymbolP symbol
);

/// Find the nearest symbol to the given address
/// @return The nearest symbol
/// @param object  The context
/// @param address The given address

octASSymbolP oclASFindByAddress (
    octASObjP object,
    Addr      address
);

/// Find the symbol with the given name
/// @return The symbol
/// @param object The context
/// @param name   The given name

octASSymbolP oclASFindByName (
    octASObjP    object,
    const char * name
);

/// Return the symbol name
/// @return The name (symbol)
/// @param symbol The given symbol

const char * oclASName (
    octASSymbolP symbol
);

/// Return the symbol size
/// @return The size in bytes
/// @param symbol The given symbol

Addr oclASSize (
    octASSymbolP symbol
);

/// Return the symbol type
/// @return The type
/// @param symbol The given symbol

ordSymbolType oclASType (
    octASSymbolP symbol
);


#endif /* OCLAPPSYMBOL_H */


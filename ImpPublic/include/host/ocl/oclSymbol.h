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


#ifndef OCLSYMBOL_H
#define OCLSYMBOL_H

#include "ocl/oclSymbolTyperefs.h"
#include "ocl/oclSymbolTypes.h"

////////////////////////////////////////////////////////////////////////////////
// OCL Functions
////////////////////////////////////////////////////////////////////////////////

/// Add a symbol by name to a symbol table. Return null if the symbol already
/// exists
/// @return Symbol handle if created, null if it already exists
/// @param table The symbol table and its contents
/// @param name  The name of a symbol
/// @param value User data associated with the new symbol

octSymbolP oclSymbolAdd (
    octSymbolTableP table,
    const char *    name,
    void *          value
);

/// Find a symbol by name in a symbol table
/// @return Symbol handle
/// @param table The symbol table and its contents
/// @param name  The name of a symbol

octSymbolP oclSymbolFind (
    octSymbolTableP table,
    const char *    name
);

/// Find a symbol by name in a symbol table, and create one if not found. Return
/// the new or existing symbol
/// @return Symbol handle if created or if it already exists
/// @param table The symbol table and its contents
/// @param name  The name of a symbol
/// @param value User data associated with the new symbol

octSymbolP oclSymbolFindAdd (
    octSymbolTableP table,
    const char *    name,
    void *          value
);

/// Call given function for every symbol in the table, in (arbitrary) symbol
/// table order
/// @param table    The symbol table and its contents
/// @param fn       The function to be called with each symbol
/// @param userData User data passed to the iterator function

void oclSymbolFindAll (
    octSymbolTableP table,
    octSymbolFn     fn,
    void *          userData
);

/// Call given function for every symbol in the table, in alphabetic table order
/// @param table    The symbol table and its contents
/// @param fn       The function to be called with each symbol
/// @param userData User data passed to the iterator function

void oclSymbolFindAllSorted (
    octSymbolTableP table,
    octSymbolFn     fn,
    void *          userData
);

/// Return the name of the symbol
/// @return The name of the symbol
/// @param symbol An existing symbol

const char * oclSymbolName (
    octSymbolP symbol
);

/// Remove and delete a symbol by name from a symbol table.
/// @return True if the symbol was found
/// @param table The symbol table and its contents
/// @param name  The name of a symbol

Bool oclSymbolRemove (
    octSymbolTableP table,
    const char *    name
);

/// Change the data associated with the symbol
/// @param symbol An existing symbol
/// @param value  Data to associated with the symbol

void oclSymbolSet (
    octSymbolP symbol,
    void*      value
);

/// Create a general purpose symbol table
/// @return Symbol Table handle

octSymbolTableP oclSymbolTableCreate (void);

/// Free the resources of a symbol table
/// @param table The symbol table and its contents

void oclSymbolTableDestroy (
    octSymbolTableP table
);

/// Return the data associated with the symbol
/// @return User data associated with the symbol
/// @param symbol An existing symbol

void* oclSymbolValue (
    octSymbolP symbol
);


#endif /* OCLSYMBOL_H */


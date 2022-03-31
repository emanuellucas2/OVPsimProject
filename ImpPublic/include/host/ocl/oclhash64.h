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


#ifndef OCLHASH64_H
#define OCLHASH64_H

#include "ocl/oclhash64Typerefs.h"
#include "ocl/oclhash64Types.h"

////////////////////////////////////////////////////////////////////////////////
// OCL Functions
////////////////////////////////////////////////////////////////////////////////

/// Add an entry by key to a hash64 table. Return null if the entry already
/// exists
/// @return Hash64 handle if created, null if it already exists
/// @param table The hash64 table and its contents
/// @param key   The key of an entry
/// @param value User data associated with the new entry

octHash64P oclHash64Add (
    octHash64TableP table,
    Uns64           key,
    void *          value
);

/// Find an entry by key in a hash64 table
/// @return Hash64 handle
/// @param table The hash64 table and its contents
/// @param key   The name of a entry

octHash64P oclHash64Find (
    octHash64TableP table,
    Uns64           key
);

/// Find an entry by name in a hash64 table, and create one if not found. Return
/// the new or existing entry
/// @return Hash64 handle if created or if it already exists
/// @param table The hash64 table and its contents
/// @param key   The name of an entry

octHash64P oclHash64FindAdd (
    octHash64TableP table,
    Uns64           key
);

/// Call given function for every entry in the table, in (arbitrary) hash table
/// order
/// @param table    The hash64 table and its contents
/// @param fn       The function to be called with each entry
/// @param userData User data passed to the iterator function

void oclHash64FindAll (
    octHash64TableP table,
    octHash64Fn     fn,
    void *          userData
);

/// Remove and delete an entry by name from a hash64 table.
/// @return True if the entry was found
/// @param table The hash64 table and its contents
/// @param key   The entry key

Bool oclHash64Remove (
    octHash64TableP table,
    Uns64           key
);

/// Change the data associated with the entry
/// @param entry An existing entry
/// @param value Data to associated with the entry

void oclHash64Set (
    octHash64P entry,
    void*      value
);

/// Create a hash table keys by 64bit integers
/// @return Hash64 Table handle

octHash64TableP oclHash64TableCreate (void);

/// Free the resources of a hash64 table
/// @param table The hassh64 table and its contents

void oclHash64TableDestroy (
    octHash64TableP table
);

/// Return the data associated with the entry
/// @return User data associated with the entry
/// @param entry An existing entry

void* oclHash64Value (
    octHash64P entry
);


#endif /* OCLHASH64_H */


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

// Delta to a simulated disk.
//     All writes go to the delta.
//     Reads from 'over-written sectors come from the delta
//     The delta is lost when the simulation finishes.

#include <string.h>
#include <stdlib.h>

// VMI area includes
#include "vmi/vmiMessage.h"

#include "hostapi/impTypes.h"

#include "semihost.h"

#include "delta.h"

#define DELTA_PREFIX PREFIX"_DELTA"

typedef struct hashEntryS {
    Uns64 key;
    void *value;
    Uns64 hash;
    struct hashEntryS *left;
    struct hashEntryS *right;
} hashEntry, *hashEntryP, **hashEntryPP;

typedef struct hashTableS {
    hashEntryP     head;
    Uns32          sectorSize;
} hashTable;

Uns32 sectorSize = 512;

//
// Hash the key (reverse the bits)
//
static Uns64 hashFunc(Uns64 key)
{
    Uns64 hash = 0;
    Uns64 keyv = (Uns64)key;
    Int64 c = (sizeof(keyv) * 8);
    while(c--) {
        hash <<= 1;
        hash |= keyv & 1;
        keyv >>= 1;
    }
    return hash;
}

//
// recursive search
//
static hashEntryP search(hashEntryP this, Uns64 hash, Uns64 key, int d)
{
    hashEntryP p;
    if (this) {
        if (hash > this->hash)
            p = this->left;
        else if (hash < this->hash)
            p = this->right;
        else {
            if (key == this->key) {
                return this;
            }
            p = this->left;
        }
        return search(p, hash, key, d+1);
    }
    return NULL;
}

//
// return the hash if found, create one otherwise
//
static hashEntryP findAdd(hashEntryPP p, Uns64 hash, Uns64 key)
{
    if (*p) {
        hashEntryP  next = *p;
        hashEntryPP np;
        if (hash > next->hash)
            np = &(next->left);
        else if (hash < next->hash)
            np = &(next->right);
        else {
            if (key == next->key)
                return next;
            np = &(next->left);
        }
        return findAdd(np, hash, key);
    }
    *p = malloc (sizeof(hashEntry));
    (*p)->hash  = hash;
    (*p)->key   = key;
    (*p)->value = NULL;
    (*p)->left  = NULL;
    (*p)->right = NULL;
    return *p;
}

hashTableP hash64TableCreate(Uns32 size)
{
    hashTableP table =  malloc (sizeof(hashTable));
    table->head       = NULL;
    table->sectorSize = size;
    return table;
}

//
// Entry point to find-and-add.
// Return the hash if found, create one otherwise
//
hashEntryP hash64FindAdd(hashTableP table, Uns64 key)
{
    Uns64 hash = hashFunc(key);
    return findAdd(&(table->head), hash, key);
}

//
// Entry point to search-only function
//
hashEntryP hash64Find(hashTableP table, Uns64 key)
{
    Uns64 hash = hashFunc(key);
    return search(table->head, hash, key, 0);
}

//
// Value accessor functions
//
void *hash64GetValue(hashEntryP entry)
{
    return entry->value;
}

void hash64SetValue(hashEntryP entry, void *v)
{
    entry->value = v;
}

//
// left side, then this, then right side
//
//static void findAll(hashEntryP entry, void *user, hash64CB cb)
//{
//    if (entry) {
//        findAll(entry->left, user, cb);
//        cb(entry, user);
//        findAll(entry->right, user, cb);
//    }
//}

//
// Call user function for all entries in a table
//
//void hash64FindAll(hashTableP table, void *user, hash64CB cb)
//{
//    findAll(table->head, user, cb);
//}

hashTableP deltaNew(Uns32 size)
{
    return hash64TableCreate(size);
}

Bool deltaRead(hashTableP table, Uns64 sector, Uns8 *buffer)
{
    hashEntryP n = hash64Find(table, sector);
    if (n) {
        Uns8 *data = hash64GetValue(n);
        memcpy(buffer, data, table->sectorSize);
        if(0)vmiMessage("I", DELTA_PREFIX,
            "deltaRead sector:" FMT_64d,
            sector
        );
        return True;
    }
    return False;
}

void deltaWrite(hashTableP table, Uns64 sector, const Uns8 *buffer)
{
    hashEntryP n = hash64FindAdd(table, sector);
    if (n) {
        Uns8 *data = hash64GetValue(n);
        if(!data) {
            data = malloc(table->sectorSize);
            hash64SetValue(n, data);
        }
        memcpy(data, buffer, table->sectorSize);
        if(0)vmiMessage("I", DELTA_PREFIX,
            "deltaWrite sector:" FMT_64d,
            sector
        );
    } else {
        vmiMessage("F", DELTA_PREFIX, "Failed to create delta");
    }
}


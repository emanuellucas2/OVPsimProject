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



#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Imperas Support Library includes
#include "isl/sharedTiming.h"

// VMI module includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiMmcAttrs.h"
#include "vmi/vmiMmc.h"
#include "vmi/vmiParameters.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"


//
// Check that the cache model is configured
//
#ifndef MODEL_NAME
# error "MODEL_NAME must be defined for the cache."
#endif
#ifndef CACHE_WRITEBACK
# error "CACHE_WRITEBACK must specify 1 for write back or 0 for write through cache."
#endif
#ifndef CACHE_WAYS
# error "CACHE_WAYS must specify in how may possible cache entries a particular address might be cached."
#endif
#ifndef CACHE_LINE_BITS
# error "CACHE_LINE_BITS must specify how many least-significant address bits are ignored because they have no effect on the cache algorithm."
#endif
#ifndef CACHE_TAG_BITS
# error "CACHE_TAG_BITS must specify how many bits of the address are used to determine the cache bucket index (the cache tag)."
#endif

//
// Model prefix (used by vmiMessage interface)
//
#define CPU_PREFIX "cache_" MODEL_NAME

//
// Secondary cache parameters: number of ways and number of bytes per line
//
#define CACHE_TAGS        (1<<CACHE_TAG_BITS)
#define CACHE_LINE_BYTES  (1<<CACHE_LINE_BITS)
#define CACHE_TAG_MASK    ((CACHE_TAGS-1)<<CACHE_LINE_BITS)
#define CACHE_KEY_MASK    ((-1)<<CACHE_LINE_BITS)
#define CACHE_SIZE        (CACHE_LINE_BYTES * CACHE_TAGS * CACHE_WAYS)

//
// Pattern to use for empty cache entries
//
#define CACHE_ENTRY_EMPTY ((Uns32)-1)

//
// Type used for cache access accounting
//
typedef struct cacheAccessInfoS {

                                        // MODELLING ARTIFACTS
    const char          *type;          // type of access
    vmiMemWatchFn        missCB;        // function to call on a miss (TRANSPARENT)

                                        // ACCOUNTING
    Uns64                misses;        // miss count
    Uns64                count1;        // 1-byte accesses
    Uns64                count2;        // 2-byte accesses
    Uns64                count4;        // 4-byte accesses
    Uns64                count8;        // 8-byte accesses
    Uns64                countN;        // N-byte accesses
    Uns64                countNBytes;   // total bytes for N-byte accesses

                                        // CYCLE PENALTIES
    Uns64                missCycleNum;  // total missed cycles added
    Uns32                missCycles;    // cycle penalty for miss
    vmiSharedDataHandleP missHandle;    // handle for miss notification
    vmiProcessorP        missContext;   // context for processor access

} cacheAccessInfo, *cacheAccessInfoP;

//
// Cache line object
//
typedef struct cacheLineS {

    #if(CACHE_WRITEBACK)
    Bool  dirty;                    // dirty bit (writeback cache only)
    #endif

    Uns8  data[CACHE_LINE_BYTES];   // data for this line

} cacheLine, *cacheLineP, **cacheLinePP;

//
// Cache object
//
typedef struct cacheObjectS {

                                                // MODELLING ARTIFACTS
    vmimmcPortP     nextPort;                   // next port (TRANSPARENT model)
    memDomainP      nextDomain;                 // next domain (FULL model)
    memRegionP      lastRegion;                 // last accessed (FULL model)
    Uns32           mruKey;                     // access optimization
    cacheLineP      mruLine;                    // access optimization
    cacheAccessInfo readInfo;                   // read access recording
    cacheAccessInfo writeInfo;                  // write access recording

                                                // TRUE CACHE CONTENTS
    Uns32      keys[CACHE_TAGS][CACHE_WAYS];    // set of keys for cache
    cacheLineP index[CACHE_TAGS][CACHE_WAYS];   // index into cache lines
    cacheLine  lines[CACHE_TAGS][CACHE_WAYS];   // set of lines for cache

    Uns32      diagnostics;                     // diagnostic level
    Uns32      numSlavePorts;                   // slave port count
    Bool       statisticsEnabled;               // enable cache

} cacheObject, *cacheObjectP;

#define BUF_SIZE 30

static char tmpCharBuffer[BUF_SIZE];

#define DIAG_LOW(_O) (_O->diagnostics > 1)
#define DIAG_MED(_O) (_O->diagnostics > 2)
#define DIAG_HI(_O)  (_O->diagnostics > 3)

//
// Return cache name
//
inline static const char *getName(cacheObjectP cache) {
    return vmimmcGetHierarchicalName((vmimmcComponentP)cache);
}

//
// Notify other tools of a cache miss delay if required
//
static void notifyMissDelay(vmiProcessorP processor, cacheAccessInfoP info) {

    // refresh the handle to notify about cache misses if processor context
    // has changed
    if(info->missContext != processor) {
        info->missContext = processor;
        info->missHandle  = vmirtFindProcessorSharedData(
            processor, SHRT_API_VERSION, SHRT_MEMORY_PENALTY
        );
    }

    // notify listeners of cycle penalty
    if(info->missHandle) {
        vmirtWriteListeners(info->missHandle, info->missCycles, 0);
    }
}

//
// Update cache data on a miss
//
inline static void notifyMiss(vmiProcessorP processor, cacheAccessInfoP info) {

    // increment miss count
    info->misses++;

    if(info->missCycles) {
        notifyMissDelay(processor, info);
    }
}

//
// Return a static temporary string that has the digits in the passed string
// separated into groups by a comma, e.g. "1234567" -> "1,234,567". The result
// is in a static buffer so it will be overwritten by the next call.
//
static const char *getCommaString(const char *string) {

    static char buffer2[BUF_SIZE];

    Uns32       length = strlen(string);
    Uns32       count  = 0;
    char       *dst    = buffer2+BUF_SIZE;
    const char *src    = string+length;

    // copy null terminator for comma string
    *--dst = *src--;

    // copy remaining characters in groups
    do {

        *--dst = *src--;

        // insert comma every three characters
        if((++count==3) && (src>=string)) {
            count = 0;
            *--dst = ',';
        }

    } while((src>=string) && (dst>=buffer2));

    return dst;
}

//
// Return a static temporary string that has the passed Uns32 value shown
// with digits separated by commas
//
static const char *uns32String(Uns32 value) {
    sprintf(tmpCharBuffer, "%u", value);
    return getCommaString(tmpCharBuffer);
}

//
// Return a static temporary string that has the passed Uns64 value shown
// with digits separated by commas
//
static const char *uns64String(Uns64 value) {
    sprintf(tmpCharBuffer, FMT_64u, value);
    return getCommaString(tmpCharBuffer);
}

//
// Utility routine for statistics reporting
//
static void printStats(cacheAccessInfoP info) {

    Uns64 totalCount = (
        info->count1 +
        info->count2 +
        info->count4 +
        info->count8 +
        info->countN
    );

    Uns64 totalBytes = (
        info->count1*1 +
        info->count2*2 +
        info->count4*4 +
        info->count8*8 +
        info->countNBytes
    );

    if(totalCount) {

        Uns64  hits = totalCount - info->misses;
        double averageSize;

        if(info->countNBytes) {
            averageSize = ((double)info->countNBytes)/info->countN;
        } else {
            averageSize = 0.0;
        }

        vmiPrintf("\n%s ACCESSES:\n", info->type);
        vmiPrintf("  HITS       : %15s\n", uns64String(hits));
        vmiPrintf("  MISSES     : %15s\n", uns64String(info->misses));
        vmiPrintf("  1-byte     : %15s\n", uns64String(info->count1));
        vmiPrintf("  2-byte     : %15s\n", uns64String(info->count2));
        vmiPrintf("  4-byte     : %15s\n", uns64String(info->count4));
        vmiPrintf("  8-byte     : %15s\n", uns64String(info->count8));
        vmiPrintf("  N-byte     : %15s", uns64String(info->countN));
        vmiPrintf( " (%s bytes,", uns64String(info->countNBytes));
        vmiPrintf( " average size=%.1f bytes)\n", averageSize);
        vmiPrintf("  TOTAL %-5s: %15s\n", info->type, uns64String(totalCount));
        vmiPrintf("  TOTAL BYTES: %15s\n", uns64String(totalBytes));
    }
}

//
// Cache object constructor debug routine
//
static void debugConstructor(cacheObjectP cache) {

    Uns32 rdMissCycles = cache->readInfo.missCycles;
    Uns32 wrMissCycles = cache->writeInfo.missCycles;
    Uns32 mask;

    vmiPrintf("  --------------------------------------------\n");
    vmiPrintf("  Ways      : %u\n", CACHE_WAYS);
    vmiPrintf("  Line bits : %u\n", CACHE_LINE_BITS);
    vmiPrintf("  Tag bits  : %u\n", CACHE_TAG_BITS);
    vmiPrintf("  --------------------------------------------\n");
    vmiPrintf("  Tags      : %s\n", uns32String(CACHE_TAGS));
    vmiPrintf("  Line bytes: %u\n", CACHE_LINE_BYTES);
    vmiPrintf("  Size      : %s\n", uns32String(CACHE_SIZE));

    vmiPrintf("  Tag mask  : ");
    for(mask=0x80000000; mask; mask=mask>>1) {
        vmiPrintf("%s", (mask&CACHE_TAG_MASK) ? "1" : ".");
    }
    vmiPrintf("\n");

    vmiPrintf("  Key mask  : ");
    for(mask=0x80000000; mask; mask=mask>>1) {
        vmiPrintf("%s", (mask&CACHE_KEY_MASK) ? "1" : ".");
    }
    vmiPrintf("\n");

    if(rdMissCycles || wrMissCycles) {
        vmiPrintf("  --------------------------------------------\n");
        vmiPrintf("  Read miss : %u-cycle penalty\n", rdMissCycles);
        vmiPrintf("  Write miss: %u-cycle penalty\n", wrMissCycles);
    }

    vmiPrintf("  --------------------------------------------\n");
    vmiPrintf("\n");
}

//
// Cache object destructor debug routine
//
static void debugDestructor(cacheObjectP cache) {
    printStats(&cache->readInfo);
    printStats(&cache->writeInfo);
}

//
// Reset cache statistics
//
void resetCacheStatistics(cacheObjectP cache) {

    // clear read information
    cache->readInfo.misses       = 0;
    cache->readInfo.count1       = 0;
    cache->readInfo.count2       = 0;
    cache->readInfo.count4       = 0;
    cache->readInfo.count8       = 0;
    cache->readInfo.countN       = 0;
    cache->readInfo.countNBytes  = 0;
    cache->readInfo.missCycleNum = 0;

    // clear write information
    cache->writeInfo.misses       = 0;
    cache->writeInfo.count1       = 0;
    cache->writeInfo.count2       = 0;
    cache->writeInfo.count4       = 0;
    cache->writeInfo.count8       = 0;
    cache->writeInfo.countN       = 0;
    cache->writeInfo.countNBytes  = 0;
    cache->writeInfo.missCycleNum = 0;
}

//
// Reset cache content and statistics
//
void resetCache(cacheObjectP cache) {

    Uns32 tag;
    Uns32 way;

    // mark every entry in the cache as empty
    for(tag=0; tag<CACHE_TAGS; tag++) {
        for(way=0; way<CACHE_WAYS; way++) {
            cache->keys[tag][way]  = CACHE_ENTRY_EMPTY;
            cache->index[tag][way] = &cache->lines[tag][way];
        }
    }

    // initialize the MRU key
    cache->mruKey  = CACHE_ENTRY_EMPTY;
    cache->mruLine = NULL;

    resetCacheStatistics(cache);
}

//
// Cache object link
//
static VMIMMC_LINK_FN(cacheLink) {

    vmiPrintf(
        "\n%s called for %s\n",
        FUNC_NAME,
        vmimmcGetHierarchicalName(component)
    );

    cacheObjectP cache      = (cacheObjectP)component;
    vmimmcPortP  nextPort   = vmimmcGetNextPort(component, "mp1");
    memDomainP   nextDomain = vmimmcGetNextDomain(component, "mp1");

    // set the next connected MMC model port
    cache->nextPort   = nextPort;
    cache->nextDomain = nextDomain;

    if(nextPort) {

        vmimmcAttrCP attrs = vmimmcGetPortAttrs(nextPort);

        // set transparent functions to call on a miss
        if(attrs) {
            cache->readInfo.missCB  = attrs->readNTransparentCB;
            cache->writeInfo.missCB = attrs->writeNTransparentCB;
        }
    }
}

//
// Refresh cache model contents at the start of a timeslice
//
static VMIMMC_REFRESH_FN(cacheRefresh) {

    cacheObjectP cache      = (cacheObjectP)component;
    vmimmcPortP  nextPort   = cache->nextPort;
    memDomainP   nextDomain = cache->nextDomain;

    // refresh any successor models
    if(nextPort) {
        vmimmcRefreshTransparent(nextPort, state);
    } else if(nextDomain) {
        vmimmcRefreshFull(nextDomain, state);
    }

    // action only for full models
    if((state==RS_RUN) && nextDomain) {

        Uns32 tag;
        Uns32 way;

        // refresh each valid entry
        for(tag=0; tag<CACHE_TAGS; tag++) {

            for(way=0; way<CACHE_WAYS; way++) {

                Uns32 key = cache->keys[tag][way];

                if(key!=CACHE_ENTRY_EMPTY) {

                    cacheLinePP lines = cache->index[tag];
                    cacheLineP  line  = lines[way];

                    #if(CACHE_WRITEBACK)
                        // writeback cache: refresh only lines that are not
                        // dirty
                        if(!line->dirty) {
                            vmirtReadNByteDomain(
                                nextDomain,
                                key,
                                line->data,
                                CACHE_LINE_BYTES,
                                &cache->lastRegion,
                                False
                            );
                        }
                    #else
                        // writethru cache: refresh all valid lines
                        vmirtReadNByteDomain(
                            nextDomain,
                            key,
                            line->data,
                            CACHE_LINE_BYTES,
                            &cache->lastRegion,
                            False
                        );
                    #endif
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// PARAMETERS
////////////////////////////////////////////////////////////////////////////////

//
// Define the attributes value structure
//
typedef struct paramValuesS {

    VMI_UNS32_PARAM(diagnostics);   // diagnostic level
    VMI_UNS32_PARAM(numSlavePorts); // number of slave ports
    VMI_UNS32_PARAM(rdMissCycles);  // cycle penalty for read miss
    VMI_UNS32_PARAM(wrMissCycles);  // cycle penalty for write miss

} paramValues, *paramValuesP;

//
// Define formals
//
static vmiParameter formals[] = {
    VMI_UNS32_PARAM_SPEC(paramValues, diagnostics,   0, 0, -1, "MMC diagnostic level"),
    VMI_UNS32_PARAM_SPEC(paramValues, numSlavePorts, 1, 1,  8, "Number of slave ports"),
    VMI_UNS32_PARAM_SPEC(paramValues, rdMissCycles,  0, 0, -1, "Cycles to add for a read miss"),
    VMI_UNS32_PARAM_SPEC(paramValues, wrMissCycles,  0, 0, -1, "Cycles to add for a write miss"),
    VMI_END_PARAM
};

//
// Iterate formals
//
static VMIMMC_PARAM_SPEC_FN(getParamSpecs) {
    if(!prev) {
        return formals;
    } else {
        prev++;
        if (prev->name) {
            return prev;
        } else {
            return NULL;
        }
    }
}

//
// Return size of parameter structure
//
static VMIMMC_PARAM_TABLE_SIZE_FN(getParamTableSize) {
    return sizeof(paramValues);
}

////////////////////////////////////////////////////////////////////////////////
// SAVE AND RESTORE
////////////////////////////////////////////////////////////////////////////////

//
// Save cache access statistics
//
static void saveAccessInfo(vmiSaveContextP cxt, cacheAccessInfoP info) {

    VMIRT_SAVE_FIELD(cxt, info, misses);
    VMIRT_SAVE_FIELD(cxt, info, count1);
    VMIRT_SAVE_FIELD(cxt, info, count2);
    VMIRT_SAVE_FIELD(cxt, info, count4);
    VMIRT_SAVE_FIELD(cxt, info, count8);
    VMIRT_SAVE_FIELD(cxt, info, countN);
    VMIRT_SAVE_FIELD(cxt, info, countNBytes);
}

//
// Restore cache access statistics
//
static void restoreAccessInfo(vmiRestoreContextP cxt, cacheAccessInfoP info) {

    VMIRT_RESTORE_FIELD(cxt, info, misses);
    VMIRT_RESTORE_FIELD(cxt, info, count1);
    VMIRT_RESTORE_FIELD(cxt, info, count2);
    VMIRT_RESTORE_FIELD(cxt, info, count4);
    VMIRT_RESTORE_FIELD(cxt, info, count8);
    VMIRT_RESTORE_FIELD(cxt, info, countN);
    VMIRT_RESTORE_FIELD(cxt, info, countNBytes);
}

//
// Save cache state
//
static VMIMMC_SAVE_STATE_FN(cacheSave) {

    cacheObjectP cache = (cacheObjectP)component;

    // both full and transparent have keys
    VMIRT_SAVE_FIELD(cxt, cache, keys);

    // save access accounting
    saveAccessInfo(cxt, &cache->readInfo);
    saveAccessInfo(cxt, &cache->writeInfo);

    // save lines
    VMIRT_SAVE_FIELD(cxt, cache, lines);
}

//
// Restore cache state
//
static VMIMMC_RESTORE_STATE_FN(cacheRestore) {

    cacheObjectP cache = (cacheObjectP)component;

    // both full and transparent have keys
    VMIRT_RESTORE_FIELD(cxt, cache, keys);

    // save access accounting
    restoreAccessInfo(cxt, &cache->readInfo);
    restoreAccessInfo(cxt, &cache->writeInfo);

    // restore lines
    VMIRT_RESTORE_FIELD(cxt, cache, lines);

    // reset MRU cache
    cache->mruKey  = CACHE_ENTRY_EMPTY;
    cache->mruLine = NULL;
}


////////////////////////////////////////////////////////////////////////////////
// FULL MODEL UTILITY FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// If there is a line for the passed key in the cache, return that line
// structure
//
static cacheLineP getLine(Uns32 key, Uns32 *keys, cacheLinePP lines) {

    Uns32 i;

    // search for any other matching line in the cache
    for(i=0; i<CACHE_WAYS; i++) {
        if(key == keys[i]) {
            return lines[i];
        }
    }

    return NULL;
}

//
// If there is a line for the passed key in the cache, return that line
// structure and promote it to the MRU slot
//
static cacheLineP getLineAsMRU(Uns32 key, Uns32 *keys, cacheLinePP lines) {

    cacheLineP line;
    Uns32      i;

    if(key == keys[0]) {

        // match in MRU slot for the key
        line = lines[0];

    } else {

        // try ways other than the MRU way
        line = NULL;

        for(i=1; i<CACHE_WAYS; i++) {

            // if there is a match, promote to the MRU slot
            if(key == keys[i]) {

                line = lines[i];

                // shift down less-recently-used entries
                do {
                    keys[i]  = keys[i-1];
                    lines[i] = lines[i-1];
                } while(--i);

                // insert this entry in the most-recently-used slot
                keys[0]  = key;
                lines[0] = line;

                break;
            }
        }
    }

    return line;
}


////////////////////////////////////////////////////////////////////////////////
// FULL MODEL CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// N-byte read function
//
static VMI_MEM_READ_FN(readNFull) {

    vmimmcPortP  port       = userData;
    cacheObjectP cache      = (cacheObjectP)port->component;
    Uns32        addressLow = (Uns32)address;
    Uns8        *buffer     = value;

    // read all lines except the last
    {
        Uns32 addressHigh = addressLow+bytes-1;
        Uns32 address1    = addressLow  & CACHE_KEY_MASK;
        Uns32 address2    = addressHigh & CACHE_KEY_MASK;

        while(address1!=address2) {
            address1  += CACHE_LINE_BYTES;
            Uns32 partBytes = address1-addressLow;
            readNFull(
                processor, addressLow, partBytes,
                buffer, port, VA, isFetch, attrs
            );
            addressLow = address1;
            bytes     -= partBytes;
            buffer    += partBytes;
        }
    }

    if(MEM_AA_IS_TRUE_ACCESS(attrs)) {

        // true access from simulated processor
        if(cache->statisticsEnabled) {
            switch(bytes) {
                case 1:
                    cache->readInfo.count1++;
                    break;
                case 2:
                    cache->readInfo.count2++;
                    break;
                case 4:
                    cache->readInfo.count4++;
                    break;
                case 8:
                    cache->readInfo.count8++;
                    break;
                default:
                    cache->readInfo.countN++;
                    cache->readInfo.countNBytes += bytes;
                    break;
            }
        }

        Uns32 key = addressLow & CACHE_KEY_MASK;

        // see if we are accessing using the same key as last time
        if(key != cache->mruKey) {

            Uns32       tag   = (key & CACHE_TAG_MASK) >> CACHE_LINE_BITS;
            Uns32      *keys  = cache->keys[tag];
            cacheLinePP lines = cache->index[tag];
            cacheLineP  line  = getLineAsMRU(key, keys, lines);

            if(!line) {

                // here if a cache MISS
                if(cache->statisticsEnabled) {
                    notifyMiss(processor, &cache->readInfo);
                }

                // get the line to replace
                line = lines[CACHE_WAYS-1];

                // writeback cache - flush the line if it is dirty
                #if(CACHE_WRITEBACK)

                    if(line->dirty) {

                        if(DIAG_LOW(cache)) {
                            vmiMessage("I", CPU_PREFIX,
                                "%s: %s Read 0x%08x MISS WriteBack Flush 0x%08x->0x%08x",
                                vmimmcGetHierarchicalName(port->component),
                                vmirtProcessorName(processor),
                                (Uns32)address,
                                keys[CACHE_WAYS-1],
                                keys[CACHE_WAYS-1]+CACHE_LINE_BYTES-1
                            );
                        }

                        vmirtWriteNByteDomain(
                            cache->nextDomain,
                            keys[CACHE_WAYS-1],
                            line->data,
                            CACHE_LINE_BYTES,
                            &cache->lastRegion,
                            True
                        );

                        line->dirty = False;
                    }

                #endif

                // load line if there is a miss
                vmirtReadNByteDomain(
                    cache->nextDomain,
                    key,
                    line->data,
                    CACHE_LINE_BYTES,
                    &cache->lastRegion,
                    True
                );

                // shift down less-recently-used entries
                Uns32 i;
                for(i=CACHE_WAYS-1; i!=0; i--) {
                    keys[i]  = keys[i-1];
                    lines[i] = lines[i-1];
                }

                // insert this entry in the most-recently-used slot
                keys[0]  = key;
                lines[0] = line;

                if(DIAG_LOW(cache)) {
                    vmiMessage("I", CPU_PREFIX,
                        "%s: %s Read 0x%08x MISS fill 0x%08x->0x%08x",
                        vmimmcGetHierarchicalName(port->component),
                        vmirtProcessorName(processor),
                        (Uns32)address,
                        key,
                        key+CACHE_LINE_BYTES-1
                    );
                }

            } else {

                if(DIAG_LOW(cache)) {
                    vmiMessage("I", CPU_PREFIX,
                        "%s: %s Read 0x%08x HIT",
                        vmimmcGetHierarchicalName(port->component),
                        vmirtProcessorName(processor),
                        (Uns32)address
                    );
                }
            }

            // record the key and line used this time
            cache->mruKey  = key;
            cache->mruLine = line;

        } else {

            if(DIAG_LOW(cache)) {
                vmiMessage("I", CPU_PREFIX,
                    "%s: %s Read 0x%08x HIT (same line)",
                    vmimmcGetHierarchicalName(port->component),
                    vmirtProcessorName(processor),
                    (Uns32)address
                );
            }
        }

        // read the data from the line in the cache
        {
            Uns32 offset = addressLow - key;
            Uns8 *base   = &cache->mruLine->data[offset];
            Uns32 i;

            for(i=0; i<bytes; i++) {
                buffer[i] = base[i];
            }
        }

    } else {

        // artifact read
        Uns32      key = addressLow & CACHE_KEY_MASK;
        cacheLineP line;

        // see if we are accessing using the same key as last time
        if(key == cache->mruKey) {

            // line to use is the MRU line
            line = cache->mruLine;

        } else {

            Uns32       tag   = (key & CACHE_TAG_MASK) >> CACHE_LINE_BITS;
            Uns32      *keys  = cache->keys[tag];
            cacheLinePP lines = cache->index[tag];

            line = getLine(key, keys, lines);
        }

        if(line) {

            // read from the cache line
            Uns32 offset = addressLow - key;
            Uns8 *base   = &line->data[offset];
            Uns32 i;

            for(i=0; i<bytes; i++) {
                buffer[i] = base[i];
            }

        } else {

            // read from the next object
            vmirtReadNByteDomain(
                cache->nextDomain,
                addressLow,
                buffer,
                bytes,
                &cache->lastRegion,
                False
            );
        }
    }
}

//
// N-byte write function
//
static VMI_MEM_WRITE_FN(writeNFull) {

    vmimmcPortP  port       = userData;
    cacheObjectP cache      = (cacheObjectP)port->component;
    Uns32        addressLow = (Uns32)address;
    const Uns8  *buffer     = value;

    // write all lines except the last
    {
        Uns32 addressHigh = addressLow+bytes-1;
        Uns32 address1    = addressLow  & CACHE_KEY_MASK;
        Uns32 address2    = addressHigh & CACHE_KEY_MASK;

        while(address1!=address2) {
            address1  += CACHE_LINE_BYTES;
            Uns32 partBytes = address1-addressLow;
            writeNFull(
                processor, addressLow, partBytes, buffer, port, VA, attrs
            );
            addressLow = address1;
            bytes     -= partBytes;
            buffer    += partBytes;
        }
    }

    if(MEM_AA_IS_TRUE_ACCESS(attrs)) {

        // true access from simulated processor
        if(cache->statisticsEnabled) {
            switch(bytes) {
                case 1:
                    cache->writeInfo.count1++;
                    break;
                case 2:
                    cache->writeInfo.count2++;
                    break;
                case 4:
                    cache->writeInfo.count4++;
                    break;
                case 8:
                    cache->writeInfo.count8++;
                    break;
                default:
                    cache->writeInfo.countN++;
                    cache->writeInfo.countNBytes += bytes;
                    break;
            }
        }

        Uns32 key = addressLow & CACHE_KEY_MASK;

        // see if we are accessing using the same key as last time
        if(key != cache->mruKey) {

            Uns32       tag   = (key & CACHE_TAG_MASK) >> CACHE_LINE_BITS;
            Uns32      *keys  = cache->keys[tag];
            cacheLinePP lines = cache->index[tag];
            cacheLineP  line  = getLineAsMRU(key, keys, lines);

            if(!line) {

                // here if a cache MISS
                if(cache->statisticsEnabled) {
                    notifyMiss(processor, &cache->writeInfo);
                }

                // get the line to replace
                line = lines[CACHE_WAYS-1];

                // writeback cache - flush the line if it is dirty
                #if(CACHE_WRITEBACK)

                    if(line->dirty) {

                        if(DIAG_LOW(cache)) {
                            vmiMessage("I", CPU_PREFIX,
                                "%s: %s Write 0x%08x MISS WriteBack Flush 0x%08x->0x%08x",
                                vmimmcGetHierarchicalName(port->component),
                                vmirtProcessorName(processor),
                                (Uns32)address,
                                keys[CACHE_WAYS-1],
                                keys[CACHE_WAYS-1]+CACHE_LINE_BYTES-1
                            );
                        }

                        vmirtWriteNByteDomain(
                            cache->nextDomain,
                            keys[CACHE_WAYS-1],
                            line->data,
                            CACHE_LINE_BYTES,
                            &cache->lastRegion,
                            True
                        );
                    }

                #endif

                // read the line if it isn't going to be fully written
                if(bytes!=CACHE_LINE_BYTES) {
                    vmirtReadNByteDomain(
                        cache->nextDomain,
                        key,
                        line->data,
                        CACHE_LINE_BYTES,
                        &cache->lastRegion,
                        True
                    );
                }

                // shift down less-recently-used entries
                Uns32 i;
                for(i=CACHE_WAYS-1; i!=0; i--) {
                    keys[i]  = keys[i-1];
                    lines[i] = lines[i-1];
                }

                // insert this entry in the most-recently-used slot
                keys[0]  = key;
                lines[0] = line;

                if(DIAG_LOW(cache)) {
                    vmiMessage("I", CPU_PREFIX,
                        "%s: %s Write 0x%08x MISS fill 0x%08x->0x%08x",
                        vmimmcGetHierarchicalName(port->component),
                        vmirtProcessorName(processor),
                        (Uns32)address,
                        key,
                        key+CACHE_LINE_BYTES-1
                    );
                }

            } else {

                if(DIAG_LOW(cache)) {
                    vmiMessage("I", CPU_PREFIX,
                        "%s: %s Write 0x%08x HIT",
                        vmimmcGetHierarchicalName(port->component),
                        vmirtProcessorName(processor),
                        (Uns32)address
                    );
                }
            }

            // record the key and line used this time
            cache->mruKey  = key;
            cache->mruLine = line;

        } else {

            if(DIAG_LOW(cache)) {
                vmiMessage("I", CPU_PREFIX,
                    "%s: %s Write 0x%08x HIT (same line)",
                    vmimmcGetHierarchicalName(port->component),
                    vmirtProcessorName(processor),
                    (Uns32)address
                );
            }
        }

        // update the contents of the cache line
        {
            Uns32 offset = addressLow - key;
            Uns8 *base   = &cache->mruLine->data[offset];
            Uns32 i;

            for(i=0; i<bytes; i++) {
                base[i] = buffer[i];
            }
        }

        #if(CACHE_WRITEBACK)

            // mark the line as dirty
            cache->mruLine->dirty = True;

            if(DIAG_LOW(cache)) {
                vmiMessage("I", CPU_PREFIX,
                    "%s: %s Write 0x%08x TAG dirty line",
                    vmimmcGetHierarchicalName(port->component),
                    vmirtProcessorName(processor),
                    (Uns32)address
                );
            }

        #else

            if(DIAG_LOW(cache)) {
                vmiMessage("I", CPU_PREFIX,
                    "%s: %s Write 0x%08x WriteThrough 0x%08x->0x%08x",
                    vmimmcGetHierarchicalName(port->component),
                    vmirtProcessorName(processor),
                    (Uns32)address,
                    addressLow,
                    addressLow+bytes-1
                );
            }

            if(DIAG_HI(cache)) {

                Uns32 count;
                char  dataBlock[bytes];

                for(count=0; (count<bytes) && (count<32); count++) {
                    sprintf(dataBlock, " %02x", buffer[count]);
                }

                dataBlock[bytes+1] = 0;

                vmiMessage("I", CPU_PREFIX, "      Data %s", dataBlock);
            }

            // do the write-through
            vmirtWriteNByteDomain(
                cache->nextDomain,
                addressLow,
                buffer,
                bytes,
                &cache->lastRegion,
                True
            );

        #endif

    } else {

        // artifact read
        Uns32      key = addressLow & CACHE_KEY_MASK;
        cacheLineP line;

        // see if we are accessing using the same key as last time
        if(key == cache->mruKey) {

            // line to use is the MRU line
            line = cache->mruLine;

        } else {

            Uns32       tag   = (key & CACHE_TAG_MASK) >> CACHE_LINE_BITS;
            Uns32      *keys  = cache->keys[tag];
            cacheLinePP lines = cache->index[tag];

            line = getLine(key, keys, lines);
        }

        if(line) {

            // write to the cache line
            Uns32 offset = addressLow - key;
            Uns8 *base   = &line->data[offset];
            Uns32 i;

            for(i=0; i<bytes; i++) {
                base[i] = buffer[i];
            }
        }

        // replicate the write in the next object
        vmirtWriteNByteDomain(
            cache->nextDomain,
            addressLow,
            buffer,
            bytes,
            &cache->lastRegion,
            False
        );
    }
}


////////////////////////////////////////////////////////////////////////////////
// TRANSPARENT MODEL CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// N-byte read transparent
//
static VMI_MEM_WATCH_FN(readNTransparent) {

    // ignore artifact accesses
    if(!processor) {
        return;
    }

    // here only if this is a true access
    vmimmcPortP  port       = userData;
    cacheObjectP cache      = (cacheObjectP)port->component;
    Uns32        addressLow = (Uns32)address;

    // read all lines except the last
    {
        Uns32 addressHigh = addressLow+bytes-1;
        Uns32 address1    = addressLow  & CACHE_KEY_MASK;
        Uns32 address2    = addressHigh & CACHE_KEY_MASK;

        while(address1!=address2) {
            address1  += CACHE_LINE_BYTES;
            Uns32 partBytes = address1-addressLow;
            readNTransparent(processor, addressLow, partBytes, value, port, VA);
            addressLow = address1;
            bytes     -= partBytes;
            value      = ((const Uns8 *)value) + partBytes;
        }
    }

    // account for bytes read from this line
    if(cache->statisticsEnabled) {
        switch(bytes) {
            case 1:
                cache->readInfo.count1++;
                break;
            case 2:
                cache->readInfo.count2++;
                break;
            case 4:
                cache->readInfo.count4++;
                break;
            case 8:
                cache->readInfo.count8++;
                break;
            default:
                cache->readInfo.countN++;
                cache->readInfo.countNBytes+=bytes;
                break;
        }
    }
    // update data structures for read from this line
    Uns32 key = addressLow & CACHE_KEY_MASK;

    // see if we are accessing using the same key as last time
    if(key != cache->mruKey) {

        Uns32  tag  = (key & CACHE_TAG_MASK) >> CACHE_LINE_BITS;
        Uns32 *keys = cache->keys[tag];

        #if(CACHE_WRITEBACK)
            cacheLinePP lines = cache->index[tag];
            cacheLineP  line  = lines[0];
        #endif

        if(key != keys[0]) {

            // here if the key doesn't match the MRU key for that tag
            Uns32 i;

            // try ways other than the MRU way
            for(i=1; i<CACHE_WAYS; i++) {

                // if there is a match, promote to the MRU slot
                if(key == keys[i]) {

                    #if(CACHE_WRITEBACK)
                        line = lines[i];
                    #endif

                    do {
                        keys[i] = keys[i-1];
                        #if(CACHE_WRITEBACK)
                            lines[i] = lines[i-1];
                        #endif
                    } while(--i);

                    goto setMRUEntry;
                }
            }

            // here if a cache MISS
            if(cache->statisticsEnabled) {
                notifyMiss(processor, &cache->readInfo);
            }

            // writeback cache - flush the line if it is dirty
            #if(CACHE_WRITEBACK)

                // get the line to replace
                line = lines[CACHE_WAYS-1];

                if(line->dirty) {

                    if(cache->writeInfo.missCB) {
                        cache->writeInfo.missCB(
                            processor,
                            keys[CACHE_WAYS-1],
                            CACHE_LINE_BYTES,
                            NULL,
                            cache->nextPort,
                            VA
                        );
                    }

                    line->dirty = False;
                }

            #endif

            // activate next port callback if there is a miss
            if(cache->readInfo.missCB) {
                cache->readInfo.missCB(
                    processor,
                    key,
                    CACHE_LINE_BYTES,
                    NULL,
                    cache->nextPort,
                    VA
                );
            }

            // move existing entries down
            for(i=CACHE_WAYS-1; i!=0; i--) {
                keys[i] = keys[i-1];
                #if(CACHE_WRITEBACK)
                    lines[i] = lines[i-1];
                #endif
            }

            // replace MRU entry
            setMRUEntry:

            keys[0] = key;
            #if(CACHE_WRITEBACK)
                lines[0] = line;
            #endif
        }

        // record the key used this time
        cache->mruKey = key;
        #if(CACHE_WRITEBACK)
            cache->mruLine = line;
        #endif
    }
}

//
// N-byte write transparent
//
static VMI_MEM_WATCH_FN(writeNTransparent) {

    // ignore artifact accesses
    if(!processor) {
        return;
    }

    vmimmcPortP  port       = userData;
    cacheObjectP cache      = (cacheObjectP)port->component;
    Uns32        addressLow = (Uns32)address;

    // write all lines except the last
    {
        Uns32 addressHigh = addressLow+bytes-1;
        Uns32 address1    = addressLow  & CACHE_KEY_MASK;
        Uns32 address2    = addressHigh & CACHE_KEY_MASK;

        while(address1!=address2) {
            address1  += CACHE_LINE_BYTES;
            Uns32 partBytes = address1-addressLow;
            writeNTransparent(processor, addressLow, partBytes, value, port, VA);
            addressLow = address1;
            bytes     -= partBytes;
            value      = ((const Uns8 *)value) + partBytes;
        }
    }

    // account for bytes written to this line
    if(cache->statisticsEnabled) {
        switch(bytes) {
            case 1:
                cache->writeInfo.count1++;
                break;
            case 2:
                cache->writeInfo.count2++;
                break;
            case 4:
                cache->writeInfo.count4++;
                break;
            case 8:
                cache->writeInfo.count8++;
                break;
            default:
                cache->writeInfo.countN++;
                cache->writeInfo.countNBytes+=bytes;
                break;
        }
    }

    // update data structures for write to this line
    Uns32 key = addressLow & CACHE_KEY_MASK;

    // see if we are accessing using the same key as last time
    if(key != cache->mruKey) {

        Uns32  tag  = (key & CACHE_TAG_MASK) >> CACHE_LINE_BITS;
        Uns32 *keys = cache->keys[tag];

        #if(CACHE_WRITEBACK)
            cacheLinePP lines = cache->index[tag];
            cacheLineP  line  = lines[0];
        #endif

        if(key != keys[0]) {

            // here if the key doesn't match the MRU key for that tag
            Uns32 i;

            // try ways other than the MRU way
            for(i=1; i<CACHE_WAYS; i++) {

                // if there is a match, promote to the MRU slot
                if(key == keys[i]) {

                    #if(CACHE_WRITEBACK)
                        line = lines[i];
                    #endif

                    do {
                        keys[i] = keys[i-1];
                        #if(CACHE_WRITEBACK)
                            lines[i] = lines[i-1];
                        #endif
                    } while(--i);

                    goto setMRUEntry;
                }
            }

            // here if a cache MISS
            if(cache->statisticsEnabled) {
                notifyMiss(processor, &cache->writeInfo);
            }

            // writeback cache - flush the line if it is dirty
            #if(CACHE_WRITEBACK)

                // get the line to replace
                line = lines[CACHE_WAYS-1];

                if(line->dirty) {

                    if(cache->writeInfo.missCB) {
                        cache->writeInfo.missCB(
                            processor,
                            keys[CACHE_WAYS-1],
                            CACHE_LINE_BYTES,
                            NULL,
                            cache->nextPort,
                            VA
                        );
                    }
                }

            #endif

            // activate next port READ callback if there is a miss
            if(cache->readInfo.missCB) {
                cache->readInfo.missCB(
                    processor,
                    key,
                    CACHE_LINE_BYTES,
                    NULL,
                    cache->nextPort,
                    VA
                );
            }

            // move existing entries down
            for(i=CACHE_WAYS-1; i!=0; i--) {
                keys[i] = keys[i-1];
                #if(CACHE_WRITEBACK)
                    lines[i] = lines[i-1];
                #endif
            }

            // replace MRU entry
            setMRUEntry:
            keys[0] = key;
            #if(CACHE_WRITEBACK)
                lines[0] = line;
            #endif
        }

        // record the key used this time
        cache->mruKey = key;
        #if(CACHE_WRITEBACK)
            cache->mruLine = line;
        #endif
    }

    #if(CACHE_WRITEBACK)
        // mark the line as dirty
        cache->mruLine->dirty = True;
    #else
        // do the write-through
        if(cache->writeInfo.missCB) {
            cache->writeInfo.missCB(
                processor,
                addressLow,
                bytes,
                NULL,
                cache->nextPort,
                VA
            );
        }
    #endif
}

//
// Get the next bus port
//
static VMIMMC_BUSPORT_FN(nextBusPortSpec) {

    // this model supports one master port and up to eight slave ports
    const static vmiBusPort busPorts[] = {
        { .name = "mp1", .type = vmi_BP_MASTER, .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp1", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp2", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp3", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp4", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp5", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp6", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp7", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
        { .name = "sp8", .type = vmi_BP_SLAVE,  .domainType = vmi_DOM_DATA, .addrBits = {32,64}, .mustBeConnected = 1},
    };

    vmiBusPortP firstPort = (vmiBusPortP)&busPorts[0];

    if(!prev) {

        // first (master) port
        return firstPort;

    } else {

        // subsequent (slave) port
        cacheObjectP cache = (cacheObjectP)component;
        vmiBusPortP  this  = ++prev;
        Uns32        index = this-firstPort;

        return (index<=cache->numSlavePorts) ? this : NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////
// COMMAND INTERFACE
////////////////////////////////////////////////////////////////////////////////

//
// Add up all the counts
//
static Uns64 addCounts(cacheAccessInfoP info) {
    return (
        info->count1 +
        info->count2 +
        info->count4 +
        info->count8 +
        info->countN
    );
}

//
// Get hit/miss ratio as a percentage
//
static Flt64 getRatio(cacheObjectP cache) {

    Uns64 accesses = addCounts(&cache->writeInfo) + addCounts(&cache->readInfo);
    Flt64 ratio    = 0.0;

    if(!accesses) {

        vmiPrintf("%s: No accesses accumulated for Cache\n", getName(cache));

    } else {

        Uns64 misses = cache->writeInfo.misses + cache->readInfo.misses;
        Flt64 hits   = accesses - misses;

        ratio = (hits/accesses) * 100.0;
    }

    return ratio;
}

//
// Command to enable caches
//
static VMIMMC_COMMAND_PARSE_FN(cacheEnableCmd) {

    cacheObjectP cache = (cacheObjectP)component;

    vmiMessage("I", CPU_PREFIX, "Command %s", __FUNCTION__);

    cache->statisticsEnabled = True;

    return "";
}

//
// Command to disable caches
//
static VMIMMC_COMMAND_PARSE_FN(cacheDisableCmd) {

    cacheObjectP cache = (cacheObjectP)component;

    vmiMessage("I", CPU_PREFIX, "Command %s", __FUNCTION__);

    cache->statisticsEnabled = False;

    return "";
}

//
// Command to report caches
//
static VMIMMC_COMMAND_PARSE_FN(cacheReportCmd) {

    cacheObjectP cache = (cacheObjectP)component;

    vmiMessage("I", CPU_PREFIX, "Command %s", __FUNCTION__);

    printStats(&cache->readInfo);
    printStats(&cache->writeInfo);

    return "";
}

//
// Command to reset caches
//
static VMIMMC_COMMAND_PARSE_FN(cacheResetCmd) {

    cacheObjectP cache = (cacheObjectP)component;

    vmiMessage("I", CPU_PREFIX, "Command %s", __FUNCTION__);

    resetCacheStatistics(cache);

    return "";
}

//
// Command to output cache ratio
//
static VMIMMC_COMMAND_PARSE_FN(cacheRatioCmd) {

    cacheObjectP cache = (cacheObjectP)component;

    vmiMessage("I", CPU_PREFIX, "Command %s", __FUNCTION__);

    static char result[16];
    snprintf(result, sizeof(result), "%.3f%%", getRatio(cache));

    vmiPrintf("Hit\\Miss ratio %s\n", result);

    return result;
}

//
// Add cache commands to the command interpreter
//
void addCacheCommands(vmimmcComponentP component) {

    vmimmcAddCommandParse(
        component,
        "CacheEnable",
        "Enable (default state) cache model statistics gathering (does not change operations)",
        cacheEnableCmd,
        VMI_CT_MODE|VMI_CO_CACHE|VMI_CA_CONTROL
    );
    vmimmcAddCommandParse(
        component,
        "CacheDisable",
        "Disable cache model statistics gathering (does not change operations)",
        cacheDisableCmd,
        VMI_CT_MODE|VMI_CO_CACHE|VMI_CA_CONTROL
    );
    vmimmcAddCommandParse(
        component,
        "CacheReport",
        "Report current cache statistics",
        cacheReportCmd,
        VMI_CT_QUERY|VMI_CO_CACHE|VMI_CA_QUERY
    );

    vmimmcAddCommandParse(
        component,
        "CacheReset",
        "Reset the cache model statistics gathering (does not change operations)",
        cacheResetCmd,
        VMI_CT_QUERY|VMI_CO_CACHE|VMI_CA_CONTROL
    );

    vmimmcAddCommandParse(
        component,
        "CacheRatio",
        "Report current hit/miss ratio",
        cacheRatioCmd,
        VMI_CT_QUERY|VMI_CO_CACHE|VMI_CA_QUERY
    );
}

//
// Cache object constructor
//
static VMIMMC_CONSTRUCTOR_FN(cacheConstructor) {

    paramValuesP params = parameterValues;

    cacheObjectP cache = (cacheObjectP)component;

    vmiPrintf("\n%s called for %s\n", FUNC_NAME, getName(cache));

    // name the cache info structures (for debug)
    cache->readInfo.type  = "READ";
    cache->writeInfo.type = "WRITE";

    // enable diagnostics if required
    if(params->SETBIT(diagnostics)) {

        vmiMessage("I", CPU_PREFIX, "Diagnostics enabled for %s at level %u",
            vmimmcGetHierarchicalName(component),
            params->diagnostics
        );

        cache->diagnostics = params->diagnostics;
    }

    // configure miss cycles
    cache->readInfo.missCycles  = params->rdMissCycles;
    cache->writeInfo.missCycles = params->wrMissCycles;

    // configure the number of slave ports
    cache->numSlavePorts = params->numSlavePorts;

    // enabled by default
    cache->statisticsEnabled = True;

    resetCache(cache);
    debugConstructor(cache);

    // add commands
    addCacheCommands(component);
}

//
// Cache object destructor
//
static VMIMMC_DESTRUCTOR_FN(cacheDestructor) {

    vmiPrintf(
        "\n%s called for %s\n",
        FUNC_NAME,
        vmimmcGetHierarchicalName(component)
    );

    cacheObjectP cache = (cacheObjectP)component;

    debugDestructor(cache);
}


vmimmcAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,              // version string
    .modelType      = VMI_MMC_MODEL,            // type
    .componentSize  = sizeof(cacheObject),      // size in bytes of MMC object

    ////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .saveCB    = cacheSave,                     // model state save callback
    .restoreCB = cacheRestore,                  // model state restore callback
    .srVersion = 1,                             // model save/restore version

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = cacheConstructor,          // constructor
    .linkCB        = cacheLink,                 // link component
    .destructorCB  = cacheDestructor,           // destructor

    ////////////////////////////////////////////////////////////////////////
    // MODEL REFRESH (AT START OF TIME SLICE)
    ////////////////////////////////////////////////////////////////////////

    .refreshCB = cacheRefresh,                  // refresh

    ////////////////////////////////////////////////////////////////////////
    // FULL MODEL CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .readNFullCB  = readNFull,                  // N-byte read callback
    .writeNFullCB = writeNFull,                 // N-byte write callback

    ////////////////////////////////////////////////////////////////////////
    // TRANSPARENT MODEL CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .readNTransparentCB  = readNTransparent,    // N-byte read callback
    .writeNTransparentCB = writeNTransparent,   // N-byte write callback

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,          // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,      // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // BUS INTERFACE CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .busPortSpecsCB = nextBusPortSpec,          // iterate ports

    ////////////////////////////////////////////////////////////////////////
    // MODEL VLNV
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "ovpworld.org",
        .library = "mmc",
        .name    = MODEL_NAME,
        .version = "1.0"
    }
};


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

#pragma once

// VMI header files
#include "vmi/vmiTypes.h"


////////////////////////////////////////////////////////////////////////////////
// CACHE FUNCTION TYPES USED IN vmiIASAttrs STRUCTURE
////////////////////////////////////////////////////////////////////////////////

//
// VMI cache types - only level 1 Instruction and Data caches supported
//
typedef enum vmiCacheTypeE {
    VMI_CT_I = 0,  // level 1 instruction
    VMI_CT_D = 1,  // level 1 data
    VMI_CT_LAST    // KEEP LAST - May be used for array size
} vmiCacheType, *vmiCacheTypeP;

//
// Function to call on a Cache hit.
// userData is value provided by caller when cache was enabled
//
#define VMI_CACHE_HIT_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,      \
    Uns32          rowIndex,       \
    Addr           hitAddr,        \
    void          *userData        \
)
typedef VMI_CACHE_HIT_FN((*vmiCacheHitFn));

//
// Function to call on a cache miss
// Return value will be passed as cacheContext when this entry is evicted
// userData is value provided by caller when cache was enabled
//
#define VMI_CACHE_MISS_FN(_NAME) void *_NAME( \
    vmiProcessorP  processor,      \
    Uns32          rowIndex,       \
    Addr           missAddr,       \
    Addr           victimAddr,     \
    void          *cacheContext,   \
    void          *userData        \
)
typedef VMI_CACHE_MISS_FN((*vmiCacheMissFn));

//
// Function to call on a cache invalidate
// cacheContext is return value from miss callback when victim was added
// userData is value provided by caller when cache was enabled
//
#define VMI_CACHE_INVALIDATE_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,      \
    Uns32          rowIndex,       \
    Addr           invalidateAddr, \
    Addr           victimAddr,     \
    void          *cacheContext,   \
    void          *userData        \
)
typedef VMI_CACHE_INVALIDATE_FN((*vmiCacheInvalidateFn));

//
// Called to enable/disable a cache and register/clear callbacks for cache events
//
// When enable is true the cache is enabled, when false it is disabled
//
// CB functions may be specified as NULL if no callback is required.
//
// Returns a unique name for the cache if successful, If the same cache
// is connected to multiple processors they will each get the same name returned.
// NULL if no cache with that type is available
//
// userData will be passed to callback functions
//
// To get callbacks on all cache events this must be called for every
// processor connected to the cache when the cache is shared between
// multiple processors (e.g. in a multi-threaded processor)
//
#define VMI_CACHE_REGISTER_FN(_NAME) const char * _NAME( \
    vmiProcessorP        processor,     \
    vmiCacheType         cacheType,     \
    Bool                 enable,        \
    vmiCacheHitFn        hitCB,         \
    vmiCacheMissFn       missCB,        \
    vmiCacheInvalidateFn invalidateCB,  \
    void                *userData       \
)
typedef VMI_CACHE_REGISTER_FN((*vmiCacheRegisterFn));


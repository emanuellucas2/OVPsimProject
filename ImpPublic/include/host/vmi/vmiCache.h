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
#include "vmi/vmiCacheAttrs.h"
#include "vmi/vmiTypes.h"

//
// Value to use for an uninitialized cacheContext value
//
#define INVALID_CACHE_CONTEXT ((void *)~0)

//
// Return a description string for a vmiCacheType
//
static inline const char *vmiCacheTypeName(vmiCacheType type) {
    switch (type) {
    case VMI_CT_I: return "ICache";
    case VMI_CT_D: return "DCache";
    default:       return "???";
    }
}

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
const char *vmirtCacheRegister( \
    vmiProcessorP        processor,
    vmiCacheType         cacheType,
    Bool                 enable,
    vmiCacheHitFn        hitCB,
    vmiCacheMissFn       missCB,
    vmiCacheInvalidateFn invalidateCB,
    void                *userData
);


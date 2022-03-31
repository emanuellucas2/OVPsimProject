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

// basic types
#include "hostapi/simAddrTypes.h"

// Imperas common library includes
#include "ocl/oclhttpTypes.h"

// VMI types
#include "vmi/vmiTypes.h"

//
// Open an HTTP connection on the requested port, or a port allocated from the pool
// in portNum is zero.
// Returns a channel to be used by oclHTTP functions.
//
octHTTPChannelP vmihttpOpen(
    vmiosObjectP    object,        // The intercept library object
    octHTTPMethodsP methods,       // callback to service HTTP requests
    Uns32           portNum,       // host port number for HTTP connection
    const char     *fileRoot       // directory when HTTP files are stored
);

//
// Use these to declare space for the HTTP parameter values
//
#define VMI_HTTP_VIS_PORT_PARAM_VALUES         \
    VMI_UNS32_PARAM (httpvisportnum) \
    VMI_STRING_PARAM(httpvisdir)     \
    VMI_STRING_PARAM(record)         \
    VMI_STRING_PARAM(replay)

//
// Use these to define the HTTP parameters
//
#define VMI_HTTP_VIS_PORT_PARAM_SPECS \
    VMI_UNS32_PARAM_SPEC (paramValues,httpvisportnum,8000,0,32763, "port number used by http visualization"), \
    VMI_STRING_PARAM_SPEC(paramValues,httpvisdir,0, "alternative directory for http visualization files"),    \
    VMI_STRING_PARAM_SPEC(paramValues,record,0, "http visualization record file"),                            \
    VMI_STRING_PARAM_SPEC(paramValues,replay,0, "http visualization replay file")




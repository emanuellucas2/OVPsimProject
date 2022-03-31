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


#ifndef OCLHTTPTYPES_H
#define OCLHTTPTYPES_H

#include <stdarg.h>
#include "hostapi/impTypes.h"
#include "ocl/oclhttpTyperefs.h"


////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////

/// An HTTP channel
typedef void*  octHTTPChannelP;

////////////////////////////////////////////////////////////////////////////////
// Callbacks
////////////////////////////////////////////////////////////////////////////////

/// This function is called when the server receives a GET

/// @par Parameters:
/// @par
/// @a ch The current channel
/// @par
/// @a data null-terminated HTTP request
/// @par
/// @a userData User data passed to the connect function

#define OCL_HTTP_GET_FN(_name) \
void _name ( \
    octHTTPChannelP ch, \
    const char *    data, \
    void *          userData)

/// This is a pointer to a function of the type defined by OCL_HTTP_GET_FN

typedef OCL_HTTP_GET_FN((*octHTTPGetFn));

/// This function is called when the server receives a POST

/// @par Parameters:
/// @par
/// @a ch The current channel
/// @par
/// @a body null-terminated HTTP POST
/// @par
/// @a userData User data passed to the connect function

#define OCL_HTTP_POST_FN(_name) \
void _name ( \
    octHTTPChannelP ch, \
    const char *    body, \
    void *          userData)

/// This is a pointer to a function of the type defined by OCL_HTTP_POST_FN

typedef OCL_HTTP_POST_FN((*octHTTPPostFn));



////////////////////////////////////////////////////////////////////////////////
// Public structures
////////////////////////////////////////////////////////////////////////////////

/// @struct octHTTPMethodsS
/// callback information

typedef struct octHTTPMethodsS {
    octHTTPGetFn  get     ; ///< method called when browser sends GET
    octHTTPPostFn post    ; ///< method called when browser sends POST
    void *        userData; ///< User data, passed to callbacks
} octHTTPMethods;



////////////////////////////////////////////////////////////////////////////////
// Macros
////////////////////////////////////////////////////////////////////////////////

#define OCL_HTTP_HTTP_VIS_PORT_FORMALS { \
    .name = "httpvisportnum", \
    .type = OP_PARAM_UNS32, \
    .description = "Visualization HTTP port", \
    .spec.uns32Spec.min          = 0, \
    .spec.uns32Spec.max          = 32767, \
    .spec.uns32Spec.defaultValue = 8000, \
},{  \
    .name = "httpvisdir", \
    .type = OP_PARAM_STRING, \
    .description = "Visualization data directory", \
},{ \
    .name = "record", \
    .type = OP_PARAM_STRING, \
    .description = "file to record visualization inputs", \
},{ \
    .name = "replay", \
    .type = OP_PARAM_STRING, \
    .description = "file to replay visualization inputs", \
}   
        

#endif /* OCLHTTPTYPES_H */


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

/*
 * bhmHttp.h - HTTP Visualization interface.
 *
 * Use this interface to construct an HTTP server driven by the peripheral model, providing
 * graphical input and output via the user's web browser.
 *
 */

#ifndef BHM_BHM_HTTP_H
#define BHM_BHM_HTTP_H

#include <stdarg.h>
#include "peripheral/impTypes.h"

#include "peripheral/bhm.h"

///
/// Handle to an HTTP channel
///
typedef struct bhmHTTPChannelS *bhmHTTPChannel;

///
/// Callback that is called when the browser issues the HTTP GET command.
///
#define BHM_HTTP_GET_FN(_NAME) \
    void _NAME(bhmHTTPChannel ch, const char *data, void *userData)

typedef BHM_HTTP_GET_FN((*bhmHTTPGetFn));

///
/// Callback that is called when the browser issues the HTTP POST command.
///
#define BHM_HTTP_POST_FN(_NAME) \
    void _NAME(bhmHTTPChannel ch, const char *body, void *userData)

typedef BHM_HTTP_POST_FN((*bhmHTTPPostFn));

///
/// Use this to specify the callbacks
///
typedef struct bhmHTTPMethodsS {

    bhmHTTPGetFn      get;       // method called when browser sends GET
    bhmHTTPPostFn     post;      // method called when browser sends POST
    char             *message;   // space allocated for POST string to be passed
    Uns32             length;    // maximum number of bytes allowed in POST
    void             *userData;  // user data to be passed to methods

} bhmHTTPMethods, *bhmHTTPMethodsP;

///
/// Start an HTTP server for this model.
///
/// @param methods           Structure containing the server's callbacks.

/// @param fileRoot          Root of files for this model.
///                          If null this defaults to  a directory 'httpvis'
///                          under the directory that contains the peripheral executable.
/// @return                  The channel number.
///
bhmHTTPChannel bhmHTTPOpen(
    bhmHTTPMethodsP methods,
    const char     *fileRoot
);

///
/// Create a key-value pair for use with Imperas CSS and JSN
/// This function should be used in the HTTP GET callback
/// @param ch      The HTTP Channel
/// @param key     The key
/// @param fmt     The format string
///
void bhmHTTPKeyPrintf     (bhmHTTPChannel ch, const char *key, const char *fmt, ...);

///
/// While in the get or post callback, having appended some text,
/// use this function to send the text to the attached browser
/// @param ch     The HTTP channel
///
void bhmHTTPSend(bhmHTTPChannel ch);

///
/// Close the HTTP port and terminate the server.
/// @param ch     The HTTP channel
///
void bhmHTTPClose(bhmHTTPChannel ch);

///////////////////////////////////////////////////////////////////////////////

void bhmHTTPElementOpen   (bhmHTTPChannel ch, const char *key);
void bhmHTTPElementClose  (bhmHTTPChannel ch, const char *key);

///
/// Append a printf formatted string to the HTTP buffer.
/// This function should be used in the HTTP GET callback
/// @param ch      The HTTP channel
/// @param fmt     The format string
///
void bhmHTTPPrintf(bhmHTTPChannel ch, const char *fmt, ...);

/// Append a printf formatted string to the HTTP buffer.
/// This function should be used in the HTTP GET callback
/// @param ch      The HTTP channel
/// @param fmt     The format string
/// @param ap      The VA list
///
void bhmHTTPVPrintf(bhmHTTPChannel ch, const char *fmt, va_list ap);

///
/// Append a string to the HTTP buffer.
/// This function should be used only if the model does its own formatting.
/// @param ch      The HTTP channel
/// @param string  The string to append
///
void bhmHTTPAppendBuffer(bhmHTTPChannel ch, const char *string);

///
/// Remove the last given number of bytes from the end of the buffer
/// This function should be used only if the model does its own formatting.
/// @param ch      The HTTP channel
/// @param bytes   The number of bytes
///
void bhmHTTPTruncateBuffer(bhmHTTPChannel ch, Uns32 bytes);

///
/// Include this macro in the model's formal parameter list
/// to declare the formal parameters used by HTTP visualization
/// in igen.exe TCL, use:
///     imodeladdformalmacro -name BHM_HTTP_FORMALS
///

#define BHM_HTTP_FORMALS \
    { .name = "httpvisportnum",  .type = ppm_PT_UNS32,  .description = "Specify the HTTP port number", .u.uns32Param.defaultValue = 8000 }, \
    { .name = "httpvisdir",      .type = ppm_PT_STRING, .description = "Specify an alternative directory for visualization data" }
#endif

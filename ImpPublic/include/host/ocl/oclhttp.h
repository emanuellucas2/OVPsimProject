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


#ifndef OCLHTTP_H
#define OCLHTTP_H

#define OCL_HTTP_VERSION "1.0.0"

#include "ocl/oclhttpTyperefs.h"
#include "ocl/oclhttpTypes.h"

////////////////////////////////////////////////////////////////////////////////
// OCL_HTTP Functions
////////////////////////////////////////////////////////////////////////////////

/// Add this null-terminated string to the HTTP string being constructed.
/// @param channel The channel
/// @param buffer  The buffer

void oclHTTPAppendBuffer (
    octHTTPChannelP channel,
    const char *    buffer
);

/// Close HTTP channel
/// @param channel The channel

void oclHTTPClose (
    octHTTPChannelP channel
);

/// Close the nesting of a list of key-value pairs
/// @param channel The channel
/// @param key     Name of the key

void oclHTTPElementClose (
    octHTTPChannelP channel,
    const char *    key
);

/// Open the nesting of a list of key-value pairs
/// @param channel The channel
/// @param key     Name of the key

void oclHTTPElementOpen (
    octHTTPChannelP channel,
    const char *    key
);

/// Create a key-value pair using printf for the value
/// @param channel The channel
/// @param key     The key name
/// @param fmt     The value format string
/// @param ...     Varargs list (see libC varargs documentation)

void oclHTTPKeyPrintf (
    octHTTPChannelP channel,
    const char *    key,
    const char *    fmt,
                    ...
);

/// Add raw text to the HTTP buffer. This is to be used when the model creates
/// it's own HTTP, rather than using the Imperas JSN and CSS.
/// @param channel The channel
/// @param fmt     The format string
/// @param ...     Varargs list (see libC varargs documentation)

void oclHTTPPrintf (
    octHTTPChannelP channel,
    const char *    fmt,
                    ...
);

/// Send the HTTP string that has been constructed (since the last send), then
/// delete the string.
/// @param channel The channel

void oclHTTPSend (
    octHTTPChannelP channel
);

/// Shorten the HTTP string being constructed by this many bytes.
/// @param channel The channel
/// @param bytes   The number of bytes to remove from the end of the string

void oclHTTPTruncateBuffer (
    octHTTPChannelP channel,
    Uns32           bytes
);

/// Same as Printf, but using using a VA list instead of variable arguments.
/// @param channel The channel
/// @param fmt     The format string
/// @param ap      VA structure (see libC varargs documentation)

void oclHTTPVPrintf (
    octHTTPChannelP channel,
    const char *    fmt,
    va_list         ap
);


#endif /* OCLHTTP_H */


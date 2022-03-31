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


#ifndef OCLSTRINGVAR_H
#define OCLSTRINGVAR_H

#include "ocl/oclStringVarTyperefs.h"
#include "ocl/oclStringVarTypes.h"

////////////////////////////////////////////////////////////////////////////////
// OCL Functions
////////////////////////////////////////////////////////////////////////////////

/// Append a character temporary string
/// @param sv    An existing string variable
/// @param value Character to append to the string. Do not append a null
///              character

void oclSVappendC (
    octStringVarP sv,
    char          value
);

/// Append a C string to a temporary string
/// @param sv    An existing string variable
/// @param value C string to append to the string variable

void oclSVappendS (
    octStringVarP sv,
    const char*   value
);

/// Return the current length of a temporary string
/// @return The current number of characters in the temporary string,
///         including new-lines etc, but excluding the terminating null
///         character.
/// @param sv An existing string variable

Uns32 oclSVlen (
    octStringVarP sv
);

/// Return a new temporary string. This will remain valid until 31 other string
/// variables have been requested, then be re-used. It will grow to accommodate
/// characters as they are added
/// @return Pointer to the new string variable

octStringVarP oclSVnew (void);

/// Shorten a temporary string by one character from the right hand end,
/// returning that character
/// @return What was the last character, or zero if the string was empty.
/// @param sv An existing string variable

char oclSVpop (
    octStringVarP sv
);

/// Append a formatted C string to a temporary string
/// @return New length of the string
/// @param sv  An existing string variable
/// @param fmt Printf format string (see gnu printf for details)
/// @param ... This is a vararg function

Uns32 oclSVprintf (
    octStringVarP sv,
    const char*   fmt,
                  ...
) __attribute__(( format (printf, 2,3)));

/// Return the C string from a string variable. Note that this pointer to not be
/// stored; when the string grows it will become invalid.
/// @return Pointer to the string variable
/// @param sv An existing string variable

const char * oclSVstring (
    octStringVarP sv
);

/// Shorten a temporary string to the given length. Has no effect if the string
/// in this length or shorter
/// @param sv     An existing string variable
/// @param length The new maximum length; can be zero if required.

void oclSVtruncate (
    octStringVarP sv,
    Uns32         length
);


#endif /* OCLSTRINGVAR_H */


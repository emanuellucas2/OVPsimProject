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

#ifndef HOSTMACROS_H
#define HOSTMACROS_H

/*
 * Windows32 =  _WIN32 && !_WIN64
 * Windows64 =  _WIN32 &&  _WIN64
 * Linux32   = !_WIN32 && !__LP64__
 * Linux64   = !_WIN32 &&  __LP64__
 */

#if defined (_WIN32)
#    define IMPERAS_WINDOWS 1
#    define IMPERAS_LINUX   0
#    define IMPERAS_LINUX64 0
#    define IMPERAS_LINUX32 0
#    if defined (_WIN64)
#        define IMPERAS_64_BIT_HOST 1
#        define IMPERAS_WINDOWS64   1
#        define IMPERAS_WINDOWS32   0
#    else
#        define IMPERAS_64_BIT_HOST 0
#        define IMPERAS_WINDOWS64   0
#        define IMPERAS_WINDOWS32   1
#    endif
#else
#    define IMPERAS_LINUX     1
#    define IMPERAS_WINDOWS   0
#    define IMPERAS_WINDOWS64 0
#    define IMPERAS_WINDOWS32 0
#    if defined (__LP64__)
#        define IMPERAS_64_BIT_HOST 1
#        define IMPERAS_LINUX64     1
#        define IMPERAS_LINUX32     0
#    else
#        define IMPERAS_64_BIT_HOST 0
#        define IMPERAS_LINUX64     0
#        define IMPERAS_LINUX32     1
#    endif
#endif

#ifdef __GNUC__
#   define IMPERAS_GCC ((__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + (__GNUC_PATCHLEVEL__))
#else
#   define IMPERAS_GCC 0
#endif

#endif /* HOSTMACROS_H */

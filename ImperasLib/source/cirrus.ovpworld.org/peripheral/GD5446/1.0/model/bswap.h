/*
 * QEMU VGA Emulator.
 *
 * Copyright (c) 2003 Fabrice Bellard
 * Copyright (c) 2006 Openedhand Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
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

#ifndef BSWAP_H
#define BSWAP_H

//#include "config-host.h"

//#include <inttypes.h>

#ifdef HAVE_BYTESWAP_H
#include <byteswap.h>
#error
#else

#define bswap_16(x) \
({ \
    Uns16 __x = (x); \
    ((Uns16)( \
        (((Uns16)(__x) & (Uns16)0x00ffU) << 8) | \
        (((Uns16)(__x) & (Uns16)0xff00U) >> 8) )); \
})

#define bswap_32(x) \
({ \
    Uns32 __x = (x); \
    ((Uns32)( \
        (((Uns32)(__x) & (Uns32)0x000000ffUL) << 24) | \
        (((Uns32)(__x) & (Uns32)0x0000ff00UL) <<  8) | \
        (((Uns32)(__x) & (Uns32)0x00ff0000UL) >>  8) | \
        (((Uns32)(__x) & (Uns32)0xff000000UL) >> 24) )); \
})

#define bswap_64(x) \
({ \
    Uns64 __x = (x); \
    ((Uns64)( \
        (Uns64)(((Uns64)(__x) & (Uns64)0x00000000000000ffULL) << 56) | \
        (Uns64)(((Uns64)(__x) & (Uns64)0x000000000000ff00ULL) << 40) | \
        (Uns64)(((Uns64)(__x) & (Uns64)0x0000000000ff0000ULL) << 24) | \
        (Uns64)(((Uns64)(__x) & (Uns64)0x00000000ff000000ULL) <<  8) | \
            (Uns64)(((Uns64)(__x) & (Uns64)0x000000ff00000000ULL) >>  8) | \
        (Uns64)(((Uns64)(__x) & (Uns64)0x0000ff0000000000ULL) >> 24) | \
        (Uns64)(((Uns64)(__x) & (Uns64)0x00ff000000000000ULL) >> 40) | \
        (Uns64)(((Uns64)(__x) & (Uns64)0xff00000000000000ULL) >> 56) )); \
})

#endif /* !HAVE_BYTESWAP_H */

static inline Uns16 bswap16(Uns16 x)
{
    return bswap_16(x);
}

static inline Uns32 bswap32(Uns32 x)
{
    return bswap_32(x);
}

static inline Uns64 bswap64(Uns64 x)
{
    return bswap_64(x);
}

static inline void bswap16s(Uns16 *s)
{
    *s = bswap16(*s);
}

static inline void bswap32s(Uns32 *s)
{
    *s = bswap32(*s);
}

static inline void bswap64s(Uns64 *s)
{
    *s = bswap64(*s);
}

#if defined(WORDS_BIGENDIAN)
#define be_bswap(v, size) (v)
#define le_bswap(v, size) bswap ## size(v)
#define be_bswaps(v, size)
#define le_bswaps(p, size) *p = bswap ## size(*p);
#else
#define le_bswap(v, size) (v)
#define be_bswap(v, size) bswap ## size(v)
#define le_bswaps(v, size)
#define be_bswaps(p, size) *p = bswap ## size(*p);
#endif

#define CPU_CONVERT(endian, size, type)\
static inline type endian ## size ## _to_cpu(type v)\
{\
    return endian ## _bswap(v, size);\
}\
\
static inline type cpu_to_ ## endian ## size(type v)\
{\
    return endian ## _bswap(v, size);\
}\
\
static inline void endian ## size ## _to_cpus(type *p)\
{\
    endian ## _bswaps(p, size)\
}\
\
static inline void cpu_to_ ## endian ## size ## s(type *p)\
{\
    endian ## _bswaps(p, size)\
}\
\
static inline type endian ## size ## _to_cpup(const type *p)\
{\
    return endian ## size ## _to_cpu(*p);\
}\
\
static inline void cpu_to_ ## endian ## size ## w(type *p, type v)\
{\
     *p = cpu_to_ ## endian ## size(v);\
}

CPU_CONVERT(be, 16, Uns16)
CPU_CONVERT(be, 32, Uns32)
CPU_CONVERT(be, 64, Uns64)

CPU_CONVERT(le, 16, Uns16)
CPU_CONVERT(le, 32, Uns32)
CPU_CONVERT(le, 64, Uns64)

/* unaligned versions (optimized for frequent unaligned accesses)*/

#if defined(__i386__) || defined(__powerpc__)

#define cpu_to_le16wu(p, v) cpu_to_le16w(p, v)
#define cpu_to_le32wu(p, v) cpu_to_le32w(p, v)
#define le16_to_cpupu(p) le16_to_cpup(p)
#define le32_to_cpupu(p) le32_to_cpup(p)

#define cpu_to_be16wu(p, v) cpu_to_be16w(p, v)
#define cpu_to_be32wu(p, v) cpu_to_be32w(p, v)

#else

static inline void cpu_to_le16wu(Uns16 *p, Uns16 v)
{
    Uns8 *p1 = (Uns8 *)p;

    p1[0] = v;
    p1[1] = v >> 8;
}

static inline void cpu_to_le32wu(Uns32 *p, Uns32 v)
{
    Uns8 *p1 = (Uns8 *)p;

    p1[0] = v;
    p1[1] = v >> 8;
    p1[2] = v >> 16;
    p1[3] = v >> 24;
}

static inline Uns16 le16_to_cpupu(const Uns16 *p)
{
    const Uns8 *p1 = (const Uns8 *)p;
    return p1[0] | (p1[1] << 8);
}

static inline Uns32 le32_to_cpupu(const Uns32 *p)
{
    const Uns8 *p1 = (const Uns8 *)p;
    return p1[0] | (p1[1] << 8) | (p1[2] << 16) | (p1[3] << 24);
}

static inline void cpu_to_be16wu(Uns16 *p, Uns16 v)
{
    Uns8 *p1 = (Uns8 *)p;

    p1[0] = v >> 8;
    p1[1] = v;
}

static inline void cpu_to_be32wu(Uns32 *p, Uns32 v)
{
    Uns8 *p1 = (Uns8 *)p;

    p1[0] = v >> 24;
    p1[1] = v >> 16;
    p1[2] = v >> 8;
    p1[3] = v;
}

#endif

#ifdef WORDS_BIGENDIAN
#define cpu_to_32wu cpu_to_be32wu
#else
#define cpu_to_32wu cpu_to_le32wu
#endif

#undef le_bswap
#undef be_bswap
#undef le_bswaps
#undef be_bswaps

#endif /* BSWAP_H */

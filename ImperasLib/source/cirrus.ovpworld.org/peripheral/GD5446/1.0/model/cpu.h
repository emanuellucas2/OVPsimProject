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

#ifndef CPU_ALL_H
#define CPU_ALL_H

#if defined(__arm__) || defined(__sparc__) || defined(__mips__)
#define WORDS_ALIGNED
#endif

/* some important defines:
 *
 * WORDS_ALIGNED : if defined, the host cpu can only make word aligned
 * memory accesses.
 *
 * WORDS_BIGENDIAN : if defined, the host cpu is big endian and
 * otherwise little endian.
 *
 * (TARGET_WORDS_ALIGNED : same for target cpu (not supported yet))
 *
 * TARGET_WORDS_BIGENDIAN : same for target cpu
 */

#include "bswap.h"

#if defined(WORDS_BIGENDIAN) != defined(TARGET_WORDS_BIGENDIAN)
#define BSWAP_NEEDED
#endif

#ifdef BSWAP_NEEDED

static inline Uns16 tswap16(Uns16 s)
{
    return bswap16(s);
}

static inline Uns32 tswap32(Uns32 s)
{
    return bswap32(s);
}

static inline Uns64 tswap64(Uns64 s)
{
    return bswap64(s);
}

static inline void tswap16s(Uns16 *s)
{
    *s = bswap16(*s);
}

static inline void tswap32s(Uns32 *s)
{
    *s = bswap32(*s);
}

static inline void tswap64s(Uns64 *s)
{
    *s = bswap64(*s);
}

#else

static inline Uns16 tswap16(Uns16 s)
{
    return s;
}

static inline Uns32 tswap32(Uns32 s)
{
    return s;
}

static inline Uns64 tswap64(Uns64 s)
{
    return s;
}

static inline void tswap16s(Uns16 *s)
{
}

static inline void tswap32s(Uns32 *s)
{
}

static inline void tswap64s(Uns64 *s)
{
}

#endif

#if TARGET_LONG_SIZE == 4
#define tswapl(s) tswap32(s)
#define tswapls(s) tswap32s((Uns32 *)(s))
#define bswaptls(s) bswap32s(s)
#else
#define tswapl(s) tswap64(s)
#define tswapls(s) tswap64s((Uns64 *)(s))
#define bswaptls(s) bswap64s(s)
#endif


/* CPU memory access without any memory or io remapping */

/*
 * the generic syntax for the memory accesses is:
 *
 * load: ld{type}{sign}{size}{endian}_{access_type}(ptr)
 *
 * store: st{type}{size}{endian}_{access_type}(ptr, val)
 *
 * type is:
 * (empty): integer access
 *   f    : float access
 *
 * sign is:
 * (empty): for floats or 32 bit size
 *   u    : unsigned
 *   s    : signed
 *
 * size is:
 *   b: 8 bits
 *   w: 16 bits
 *   l: 32 bits
 *   q: 64 bits
 *
 * endian is:
 * (empty): target cpu endianness or 8 bit access
 *   r    : reversed target cpu endianness (not implemented yet)
 *   be   : big endian (not implemented yet)
 *   le   : little endian (not implemented yet)
 *
 * access_type is:
 *   raw    : host memory access
 *   user   : user mode access using soft MMU
 *   kernel : kernel mode access using soft MMU
 */
static inline Int32 ldub_p(void *ptr)
{
    return *(Uns8 *)ptr;
}

static inline Int32 ldsb_p(void *ptr)
{
    return *(Int8 *)ptr;
}

static inline void stb_p(void *ptr, Int32 v)
{
    *(Uns8 *)ptr = v;
}

/* NOTE: on arm, putting 2 in /proc/sys/debug/alignment so that the
   kernel handles unaligned load/stores may give better results, but
   it is a system wide setting : bad */
#if defined(WORDS_BIGENDIAN) || defined(WORDS_ALIGNED)

/* conservative code for little endian unaligned accesses */
static inline Int32 lduw_le_p(void *ptr)
{
#ifdef __powerpc__
    Int32 val;
    __asm__ __volatile__ ("lhbrx %0,0,%1" : "=r" (val) : "r" (ptr));
    return val;
#else
    Uns8 *p = ptr;
    return p[0] | (p[1] << 8);
#endif
}

static inline Int32 ldsw_le_p(void *ptr)
{
#ifdef __powerpc__
    Int32 val;
    __asm__ __volatile__ ("lhbrx %0,0,%1" : "=r" (val) : "r" (ptr));
    return (Int16)val;
#else
    Uns8 *p = ptr;
    return (Int16)(p[0] | (p[1] << 8));
#endif
}

static inline Int32 ldl_le_p(void *ptr)
{
#ifdef __powerpc__
    Int32 val;
    __asm__ __volatile__ ("lwbrx %0,0,%1" : "=r" (val) : "r" (ptr));
    return val;
#else
    Uns8 *p = ptr;
    return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
#endif
}

static inline Uns64 ldq_le_p(void *ptr)
{
    Uns8 *p = ptr;
    Uns32 v1, v2;
    v1 = ldl_le_p(p);
    v2 = ldl_le_p(p + 4);
    return v1 | ((Uns64)v2 << 32);
}

static inline void stw_le_p(void *ptr, Int32 v)
{
#ifdef __powerpc__
    __asm__ __volatile__ ("sthbrx %1,0,%2" : "=m" (*(Uns16 *)ptr) : "r" (v), "r" (ptr));
#else
    Uns8 *p = ptr;
    p[0] = v;
    p[1] = v >> 8;
#endif
}

static inline void stl_le_p(void *ptr, Int32 v)
{
#ifdef __powerpc__
    __asm__ __volatile__ ("stwbrx %1,0,%2" : "=m" (*(Uns32 *)ptr) : "r" (v), "r" (ptr));
#else
    Uns8 *p = ptr;
    p[0] = v;
    p[1] = v >> 8;
    p[2] = v >> 16;
    p[3] = v >> 24;
#endif
}

static inline void stq_le_p(void *ptr, Uns64 v)
{
    Uns8 *p = ptr;
    stl_le_p(p, (Uns32)v);
    stl_le_p(p + 4, v >> 32);
}

/* float access */

static inline Flt32 ldfl_le_p(void *ptr)
{
    union {
        Flt32 f;
        Uns32 i;
    } u;
    u.i = ldl_le_p(ptr);
    return u.f;
}

static inline void stfl_le_p(void *ptr, Flt32 v)
{
    union {
        Flt32 f;
        Uns32 i;
    } u;
    u.f = v;
    stl_le_p(ptr, u.i);
}

static inline Flt64 ldfq_le_p(void *ptr)
{
    CPU_DoubleU u;
    u.l.lower = ldl_le_p(ptr);
    u.l.upper = ldl_le_p(ptr + 4);
    return u.d;
}

static inline void stfq_le_p(void *ptr, Flt64 v)
{
    CPU_DoubleU u;
    u.d = v;
    stl_le_p(ptr, u.l.lower);
    stl_le_p(ptr + 4, u.l.upper);
}

#else

static inline Int32 lduw_le_p(void *ptr)
{
    return *(Uns16 *)ptr;
}

static inline Int32 ldsw_le_p(void *ptr)
{
    return *(Int16 *)ptr;
}

static inline Int32 ldl_le_p(void *ptr)
{
    return *(Uns32 *)ptr;
}

static inline Uns64 ldq_le_p(void *ptr)
{
    return *(Uns64 *)ptr;
}

static inline void stw_le_p(void *ptr, Int32 v)
{
    *(Uns16 *)ptr = v;
}

static inline void stl_le_p(void *ptr, Int32 v)
{
    *(Uns32 *)ptr = v;
}

static inline void stq_le_p(void *ptr, Uns64 v)
{
    *(Uns64 *)ptr = v;
}

#endif

#if !defined(WORDS_BIGENDIAN) || defined(WORDS_ALIGNED)

static inline Int32 lduw_be_p(void *ptr)
{
#if defined(__i386__)
    Int32 val;
    asm volatile ("movzwl %1, %0\n"
                  "xchgb %b0, %h0\n"
                  : "=q" (val)
                  : "m" (*(Uns16 *)ptr));
    return val;
#else
    Uns8 *b = (Uns8 *) ptr;
    return ((b[0] << 8) | b[1]);
#endif
}

static inline Int32 ldsw_be_p(void *ptr)
{
#if defined(__i386__)
    Int32 val;
    asm volatile ("movzwl %1, %0\n"
                  "xchgb %b0, %h0\n"
                  : "=q" (val)
                  : "m" (*(Uns16 *)ptr));
    return (Int16)val;
#else
    Uns8 *b = (Uns8 *) ptr;
    return (Int16)((b[0] << 8) | b[1]);
#endif
}

static inline Int32 ldl_be_p(void *ptr)
{
#if defined(__i386__) || defined(__x86_64__)
    Int32 val;
    asm volatile ("movl %1, %0\n"
                  "bswap %0\n"
                  : "=r" (val)
                  : "m" (*(Uns32 *)ptr));
    return val;
#else
    Uns8 *b = (Uns8 *) ptr;
    return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
#endif
}

static inline Uns64 ldq_be_p(void *ptr)
{
    Uns32 a,b;
    a = ldl_be_p(ptr);
    b = ldl_be_p(ptr+4);
    return (((Uns64)a<<32)|b);
}

static inline void stw_be_p(void *ptr, Int32 v)
{
#if defined(__i386__)
    asm volatile ("xchgb %b0, %h0\n"
                  "movw %w0, %1\n"
                  : "=q" (v)
                  : "m" (*(Uns16 *)ptr), "0" (v));
#else
    Uns8 *d = (Uns8 *) ptr;
    d[0] = v >> 8;
    d[1] = v;
#endif
}

static inline void stl_be_p(void *ptr, Int32 v)
{
#if defined(__i386__) || defined(__x86_64__)
    asm volatile ("bswap %0\n"
                  "movl %0, %1\n"
                  : "=r" (v)
                  : "m" (*(Uns32 *)ptr), "0" (v));
#else
    Uns8 *d = (Uns8 *) ptr;
    d[0] = v >> 24;
    d[1] = v >> 16;
    d[2] = v >> 8;
    d[3] = v;
#endif
}

static inline void stq_be_p(void *ptr, Uns64 v)
{
    stl_be_p(ptr, v >> 32);
    stl_be_p(ptr + 4, v);
}


#else

static inline Int32 lduw_be_p(void *ptr)
{
    return *(Uns16 *)ptr;
}

static inline Int32 ldsw_be_p(void *ptr)
{
    return *(Int16 *)ptr;
}

static inline Int32 ldl_be_p(void *ptr)
{
    return *(Uns32 *)ptr;
}

static inline Uns64 ldq_be_p(void *ptr)
{
    return *(Uns64 *)ptr;
}

static inline void stw_be_p(void *ptr, Int32 v)
{
    *(Uns16 *)ptr = v;
}

static inline void stl_be_p(void *ptr, Int32 v)
{
    *(Uns32 *)ptr = v;
}

static inline void stq_be_p(void *ptr, Uns64 v)
{
    *(Uns64 *)ptr = v;
}

#endif

/* target CPU memory access functions */
#if defined(TARGET_WORDS_BIGENDIAN)
#define lduw_p(p) lduw_be_p(p)
#define ldsw_p(p) ldsw_be_p(p)
#define ldl_p(p) ldl_be_p(p)
#define ldq_p(p) ldq_be_p(p)
#define ldfl_p(p) ldfl_be_p(p)
#define ldfq_p(p) ldfq_be_p(p)
#define stw_p(p, v) stw_be_p(p, v)
#define stl_p(p, v) stl_be_p(p, v)
#define stq_p(p, v) stq_be_p(p, v)
#define stfl_p(p, v) stfl_be_p(p, v)
#define stfq_p(p, v) stfq_be_p(p, v)
#else
#define lduw_p(p) lduw_le_p(p)
#define ldsw_p(p) ldsw_le_p(p)
#define ldl_p(p) ldl_le_p(p)
#define ldq_p(p) ldq_le_p(p)
#define ldfl_p(p) ldfl_le_p(p)
#define ldfq_p(p) ldfq_le_p(p)
#define stw_p(p, v) stw_le_p(p, v)
#define stl_p(p, v) stl_le_p(p, v)
#define stq_p(p, v) stq_le_p(p, v)
#define stfl_p(p, v) stfl_le_p(p, v)
#define stfq_p(p, v) stfq_le_p(p, v)
#endif

/* MMU memory access macros */

#if defined(CONFIG_USER_ONLY)
/* On some host systems the guest address space is reserved on the host.
 * This allows the guest address space to be offset to a convenient location.
 */

#define saddr(x) g2h(x)
#define laddr(x) g2h(x)

#else /* !CONFIG_USER_ONLY */
/* NOTE: we use double casts if pointers and target_ulong have
   different sizes */
#define saddr(x) (Uns8 *)(UnsPS)(x)
#define laddr(x) (Uns8 *)(UnsPS)(x)
#endif

#define ldub_raw(p) ldub_p(laddr((p)))
#define ldsb_raw(p) ldsb_p(laddr((p)))
#define lduw_raw(p) lduw_p(laddr((p)))
#define ldsw_raw(p) ldsw_p(laddr((p)))
#define ldl_raw(p) ldl_p(laddr((p)))
#define ldq_raw(p) ldq_p(laddr((p)))
#define ldfl_raw(p) ldfl_p(laddr((p)))
#define ldfq_raw(p) ldfq_p(laddr((p)))
#define stb_raw(p, v) stb_p(saddr((p)), v)
#define stw_raw(p, v) stw_p(saddr((p)), v)
#define stl_raw(p, v) stl_p(saddr((p)), v)
#define stq_raw(p, v) stq_p(saddr((p)), v)
#define stfl_raw(p, v) stfl_p(saddr((p)), v)
#define stfq_raw(p, v) stfq_p(saddr((p)), v)

#endif /* CPU_ALL_H */

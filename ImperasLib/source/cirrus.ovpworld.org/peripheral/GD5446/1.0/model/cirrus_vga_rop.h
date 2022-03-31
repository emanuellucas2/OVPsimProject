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

static void
glue(cirrus_bitblt_rop_fwd_, ROP_NAME)(CirrusVGAStateP s,
                             Uns8 *dst,const Uns8 *src,
                             Int32 dstpitch,Int32 srcpitch,
                             Int32 bltwidth,Int32 bltheight)
{
    Int32 x,y;
    dstpitch -= bltwidth;
    srcpitch -= bltwidth;
    for (y = 0; y < bltheight; y++) {
        for (x = 0; x < bltwidth; x++) {
            ROP_OP(*dst, *src);
            dst++;
            src++;
        }
        dst += dstpitch;
        src += srcpitch;
    }
}

static void
glue(cirrus_bitblt_rop_bkwd_, ROP_NAME)(CirrusVGAStateP s,
                                        Uns8 *dst,const Uns8 *src,
                                        Int32 dstpitch,Int32 srcpitch,
                                        Int32 bltwidth,Int32 bltheight)
{
    Int32 x,y;
    dstpitch += bltwidth;
    srcpitch += bltwidth;
    for (y = 0; y < bltheight; y++) {
        for (x = 0; x < bltwidth; x++) {
            ROP_OP(*dst, *src);
            dst--;
            src--;
        }
        dst += dstpitch;
        src += srcpitch;
    }
}

static void
glue(glue(cirrus_bitblt_rop_fwd_transp_, ROP_NAME),_8)(CirrusVGAStateP s,
                               Uns8 *dst,const Uns8 *src,
                               Int32 dstpitch,Int32 srcpitch,
                               Int32 bltwidth,Int32 bltheight)
{
    Int32 x,y;
    Uns8 p;
    dstpitch -= bltwidth;
    srcpitch -= bltwidth;
    for (y = 0; y < bltheight; y++) {
        for (x = 0; x < bltwidth; x++) {
        p = *dst;
            ROP_OP(p, *src);
        if (p != s->gr[0x34]) *dst = p;
            dst++;
            src++;
        }
        dst += dstpitch;
        src += srcpitch;
    }
}

static void
glue(glue(cirrus_bitblt_rop_bkwd_transp_, ROP_NAME),_8)(CirrusVGAStateP s,
                            Uns8 *dst,const Uns8 *src,
                            Int32 dstpitch,Int32 srcpitch,
                            Int32 bltwidth,Int32 bltheight)
{
    Int32 x,y;
    Uns8 p;
    dstpitch += bltwidth;
    srcpitch += bltwidth;
    for (y = 0; y < bltheight; y++) {
        for (x = 0; x < bltwidth; x++) {
        p = *dst;
            ROP_OP(p, *src);
        if (p != s->gr[0x34]) *dst = p;
            dst--;
            src--;
        }
        dst += dstpitch;
        src += srcpitch;
    }
}

static void
glue(glue(cirrus_bitblt_rop_fwd_transp_, ROP_NAME),_16)(CirrusVGAStateP s,
                            Uns8 *dst,const Uns8 *src,
                            Int32 dstpitch,Int32 srcpitch,
                            Int32 bltwidth,Int32 bltheight)
{
    Int32 x,y;
    Uns8 p1, p2;
    dstpitch -= bltwidth;
    srcpitch -= bltwidth;
    for (y = 0; y < bltheight; y++) {
        for (x = 0; x < bltwidth; x+=2) {
        p1 = *dst;
        p2 = *(dst+1);
            ROP_OP(p1, *src);
            ROP_OP(p2, *(src+1));
        if ((p1 != s->gr[0x34]) || (p2 != s->gr[0x35])) {
        *dst = p1;
        *(dst+1) = p2;
        }
            dst+=2;
            src+=2;
        }
        dst += dstpitch;
        src += srcpitch;
    }
}

static void
glue(glue(cirrus_bitblt_rop_bkwd_transp_, ROP_NAME),_16)(CirrusVGAStateP s,
                             Uns8 *dst,const Uns8 *src,
                             Int32 dstpitch,Int32 srcpitch,
                             Int32 bltwidth,Int32 bltheight)
{
    Int32 x,y;
    Uns8 p1, p2;
    dstpitch += bltwidth;
    srcpitch += bltwidth;
    for (y = 0; y < bltheight; y++) {
        for (x = 0; x < bltwidth; x+=2) {
        p1 = *(dst-1);
        p2 = *dst;
            ROP_OP(p1, *(src-1));
            ROP_OP(p2, *src);
        if ((p1 != s->gr[0x34]) || (p2 != s->gr[0x35])) {
        *(dst-1) = p1;
        *dst = p2;
        }
            dst-=2;
            src-=2;
        }
        dst += dstpitch;
        src += srcpitch;
    }
}

#define DEPTH 8
#include "cirrus_vga_rop2.h"

#define DEPTH 16
#include "cirrus_vga_rop2.h"

#define DEPTH 24
#include "cirrus_vga_rop2.h"

#define DEPTH 32
#include "cirrus_vga_rop2.h"

#undef ROP_NAME
#undef ROP_OP

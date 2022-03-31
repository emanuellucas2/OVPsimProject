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


#if DEPTH == 8
#define BPP 1
#define PIXEL_TYPE Uns8
#elif DEPTH == 15 || DEPTH == 16
#define BPP 2
#define PIXEL_TYPE Uns16
#elif DEPTH == 32
#define BPP 4
#define PIXEL_TYPE Uns32
#else
#error unsupport depth
#endif

#ifdef BGR_FORMAT
#define PIXEL_NAME glue(DEPTH, bgr)
#else
#define PIXEL_NAME DEPTH
#endif /* BGR_FORMAT */

#if DEPTH != 15 && !defined(BGR_FORMAT)

static inline void glue(vga_draw_glyph_line_, DEPTH)(Uns8 *d,
                                                     Uns32 font_data,
                                                     Uns32 xorcol,
                                                     Uns32 bgcol)
{
#if BPP == 1
        ((Uns32 *)d)[0] = (dmask16[(font_data >> 4)] & xorcol) ^ bgcol;
        ((Uns32 *)d)[1] = (dmask16[(font_data >> 0) & 0xf] & xorcol) ^ bgcol;
#elif BPP == 2
        ((Uns32 *)d)[0] = (dmask4[(font_data >> 6)] & xorcol) ^ bgcol;
        ((Uns32 *)d)[1] = (dmask4[(font_data >> 4) & 3] & xorcol) ^ bgcol;
        ((Uns32 *)d)[2] = (dmask4[(font_data >> 2) & 3] & xorcol) ^ bgcol;
        ((Uns32 *)d)[3] = (dmask4[(font_data >> 0) & 3] & xorcol) ^ bgcol;
#else
        ((Uns32 *)d)[0] = (-((font_data >> 7)) & xorcol) ^ bgcol;
        ((Uns32 *)d)[1] = (-((font_data >> 6) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[2] = (-((font_data >> 5) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[3] = (-((font_data >> 4) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[4] = (-((font_data >> 3) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[5] = (-((font_data >> 2) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[6] = (-((font_data >> 1) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[7] = (-((font_data >> 0) & 1) & xorcol) ^ bgcol;
#endif
}

static void glue(vga_draw_glyph8_, DEPTH)(Uns8 *d, int linesize,
                                          const Uns8 *font_ptr, int h,
                                          Uns32 fgcol, Uns32 bgcol)
{
    Uns32 font_data, xorcol;

    xorcol = bgcol ^ fgcol;
    do {
        font_data = font_ptr[0];
        glue(vga_draw_glyph_line_, DEPTH)(d, font_data, xorcol, bgcol);
        font_ptr += 4;
        d += linesize;
    } while (--h);
}

static void glue(vga_draw_glyph16_, DEPTH)(Uns8 *d, int linesize,
                                          const Uns8 *font_ptr, int h,
                                          Uns32 fgcol, Uns32 bgcol)
{
    Uns32 font_data, xorcol;

    xorcol = bgcol ^ fgcol;
    do {
        font_data = font_ptr[0];
        glue(vga_draw_glyph_line_, DEPTH)(d,
                                          expand4to8[font_data >> 4],
                                          xorcol, bgcol);
        glue(vga_draw_glyph_line_, DEPTH)(d + 8 * BPP,
                                          expand4to8[font_data & 0x0f],
                                          xorcol, bgcol);
        font_ptr += 4;
        d += linesize;
    } while (--h);
}

static void glue(vga_draw_glyph9_, DEPTH)(Uns8 *d, int linesize,
                                          const Uns8 *font_ptr, int h,
                                          Uns32 fgcol, Uns32 bgcol, int dup9)
{
    Uns32 font_data, xorcol, v;

    xorcol = bgcol ^ fgcol;
    do {
        font_data = font_ptr[0];
#if BPP == 1
        cpu_to_32wu((Uns32 *)d, (dmask16[(font_data >> 4)] & xorcol) ^ bgcol);
        v = (dmask16[(font_data >> 0) & 0xf] & xorcol) ^ bgcol;
        cpu_to_32wu(((Uns32 *)d)+1, v);
        if (dup9)
            ((Uns8 *)d)[8] = v >> (24 * (1 - BIG));
        else
            ((Uns8 *)d)[8] = bgcol;

#elif BPP == 2
        cpu_to_32wu(((Uns32 *)d)+0, (dmask4[(font_data >> 6)] & xorcol) ^ bgcol);
        cpu_to_32wu(((Uns32 *)d)+1, (dmask4[(font_data >> 4) & 3] & xorcol) ^ bgcol);
        cpu_to_32wu(((Uns32 *)d)+2, (dmask4[(font_data >> 2) & 3] & xorcol) ^ bgcol);
        v = (dmask4[(font_data >> 0) & 3] & xorcol) ^ bgcol;
        cpu_to_32wu(((Uns32 *)d)+3, v);
        if (dup9)
            ((Uns16 *)d)[8] = v >> (16 * (1 - BIG));
        else
            ((Uns16 *)d)[8] = bgcol;
#else
        ((Uns32 *)d)[0] = (-((font_data >> 7)) & xorcol) ^ bgcol;
        ((Uns32 *)d)[1] = (-((font_data >> 6) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[2] = (-((font_data >> 5) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[3] = (-((font_data >> 4) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[4] = (-((font_data >> 3) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[5] = (-((font_data >> 2) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[6] = (-((font_data >> 1) & 1) & xorcol) ^ bgcol;
        v = (-((font_data >> 0) & 1) & xorcol) ^ bgcol;
        ((Uns32 *)d)[7] = v;
        if (dup9)
            ((Uns32 *)d)[8] = v;
        else
            ((Uns32 *)d)[8] = bgcol;
#endif
        font_ptr += 4;
        d += linesize;
    } while (--h);
}

/*
 * 4 color mode
 */
static void glue(vga_draw_line2_, DEPTH)(VGAState *s1, Uns8 *d,
                                         const Uns8 *s, int width)
{
    Uns32 plane_mask, *palette, data, v;
    int x;

    palette = s1->last_palette;
    plane_mask = mask16[s1->ar[0x12] & 0xf];
    width >>= 3;
    for(x = 0; x < width; x++) {
        data = ((Uns32 *)s)[0];
        data &= plane_mask;
        v = expand2[GET_PLANE(data, 0)];
        v |= expand2[GET_PLANE(data, 2)] << 2;
        ((PIXEL_TYPE *)d)[0] = palette[v >> 12];
        ((PIXEL_TYPE *)d)[1] = palette[(v >> 8) & 0xf];
        ((PIXEL_TYPE *)d)[2] = palette[(v >> 4) & 0xf];
        ((PIXEL_TYPE *)d)[3] = palette[(v >> 0) & 0xf];

        v = expand2[GET_PLANE(data, 1)];
        v |= expand2[GET_PLANE(data, 3)] << 2;
        ((PIXEL_TYPE *)d)[4] = palette[v >> 12];
        ((PIXEL_TYPE *)d)[5] = palette[(v >> 8) & 0xf];
        ((PIXEL_TYPE *)d)[6] = palette[(v >> 4) & 0xf];
        ((PIXEL_TYPE *)d)[7] = palette[(v >> 0) & 0xf];
        d += BPP * 8;
        s += 4;
    }
}

#if BPP == 1
#define PUT_PIXEL2(d, n, v) ((Uns16 *)d)[(n)] = (v)
#elif BPP == 2
#define PUT_PIXEL2(d, n, v) ((Uns32 *)d)[(n)] = (v)
#else
#define PUT_PIXEL2(d, n, v) \
((Uns32 *)d)[2*(n)] = ((Uns32 *)d)[2*(n)+1] = (v)
#endif

/*
 * 4 color mode, dup2 horizontal
 */
static void glue(vga_draw_line2d2_, DEPTH)(VGAState *s1, Uns8 *d,
                                           const Uns8 *s, int width)
{
    Uns32 plane_mask, *palette, data, v;
    int x;

    palette = s1->last_palette;
    plane_mask = mask16[s1->ar[0x12] & 0xf];
    width >>= 3;
    for(x = 0; x < width; x++) {
        data = ((Uns32 *)s)[0];
        data &= plane_mask;
        v = expand2[GET_PLANE(data, 0)];
        v |= expand2[GET_PLANE(data, 2)] << 2;
        PUT_PIXEL2(d, 0, palette[v >> 12]);
        PUT_PIXEL2(d, 1, palette[(v >> 8) & 0xf]);
        PUT_PIXEL2(d, 2, palette[(v >> 4) & 0xf]);
        PUT_PIXEL2(d, 3, palette[(v >> 0) & 0xf]);

        v = expand2[GET_PLANE(data, 1)];
        v |= expand2[GET_PLANE(data, 3)] << 2;
        PUT_PIXEL2(d, 4, palette[v >> 12]);
        PUT_PIXEL2(d, 5, palette[(v >> 8) & 0xf]);
        PUT_PIXEL2(d, 6, palette[(v >> 4) & 0xf]);
        PUT_PIXEL2(d, 7, palette[(v >> 0) & 0xf]);
        d += BPP * 16;
        s += 4;
    }
}

/*
 * 16 color mode
 */
static void glue(vga_draw_line4_, DEPTH)(VGAState *s1, Uns8 *d,
                                         const Uns8 *s, int width)
{
    Uns32 plane_mask, data, v, *palette;
    int x;

    palette = s1->last_palette;
    plane_mask = mask16[s1->ar[0x12] & 0xf];
    width >>= 3;
    for(x = 0; x < width; x++) {
        data = ((Uns32 *)s)[0];
        data &= plane_mask;
        v = expand4[GET_PLANE(data, 0)];
        v |= expand4[GET_PLANE(data, 1)] << 1;
        v |= expand4[GET_PLANE(data, 2)] << 2;
        v |= expand4[GET_PLANE(data, 3)] << 3;
        ((PIXEL_TYPE *)d)[0] = palette[v >> 28];
        ((PIXEL_TYPE *)d)[1] = palette[(v >> 24) & 0xf];
        ((PIXEL_TYPE *)d)[2] = palette[(v >> 20) & 0xf];
        ((PIXEL_TYPE *)d)[3] = palette[(v >> 16) & 0xf];
        ((PIXEL_TYPE *)d)[4] = palette[(v >> 12) & 0xf];
        ((PIXEL_TYPE *)d)[5] = palette[(v >> 8) & 0xf];
        ((PIXEL_TYPE *)d)[6] = palette[(v >> 4) & 0xf];
        ((PIXEL_TYPE *)d)[7] = palette[(v >> 0) & 0xf];
        d += BPP * 8;
        s += 4;
    }
}

/*
 * 16 color mode, dup2 horizontal
 */
static void glue(vga_draw_line4d2_, DEPTH)(VGAState *s1, Uns8 *d,
                                           const Uns8 *s, int width)
{
    Uns32 plane_mask, data, v, *palette;
    int x;

    palette = s1->last_palette;
    plane_mask = mask16[s1->ar[0x12] & 0xf];
    width >>= 3;
    for(x = 0; x < width; x++) {
        data = ((Uns32 *)s)[0];
        data &= plane_mask;
        v = expand4[GET_PLANE(data, 0)];
        v |= expand4[GET_PLANE(data, 1)] << 1;
        v |= expand4[GET_PLANE(data, 2)] << 2;
        v |= expand4[GET_PLANE(data, 3)] << 3;
        PUT_PIXEL2(d, 0, palette[v >> 28]);
        PUT_PIXEL2(d, 1, palette[(v >> 24) & 0xf]);
        PUT_PIXEL2(d, 2, palette[(v >> 20) & 0xf]);
        PUT_PIXEL2(d, 3, palette[(v >> 16) & 0xf]);
        PUT_PIXEL2(d, 4, palette[(v >> 12) & 0xf]);
        PUT_PIXEL2(d, 5, palette[(v >> 8) & 0xf]);
        PUT_PIXEL2(d, 6, palette[(v >> 4) & 0xf]);
        PUT_PIXEL2(d, 7, palette[(v >> 0) & 0xf]);
        d += BPP * 16;
        s += 4;
    }
}

/*
 * 256 color mode, double pixels
 *
 * XXX: add plane_mask support (never used in standard VGA modes)
 */
static void glue(vga_draw_line8d2_, DEPTH)(VGAState *s1, Uns8 *d,
                                           const Uns8 *s, int width)
{
    Uns32 *palette;
    int x;

    palette = s1->last_palette;
    width >>= 3;
    for(x = 0; x < width; x++) {
        PUT_PIXEL2(d, 0, palette[s[0]]);
        PUT_PIXEL2(d, 1, palette[s[1]]);
        PUT_PIXEL2(d, 2, palette[s[2]]);
        PUT_PIXEL2(d, 3, palette[s[3]]);
        d += BPP * 8;
        s += 4;
    }
}

/*
 * standard 256 color mode
 *
 * XXX: add plane_mask support (never used in standard VGA modes)
 */
static void glue(vga_draw_line8_, DEPTH)(VGAState *s1, Uns8 *d,
                                         const Uns8 *s, int width)
{
    Uns32 *palette;
    int x;

    palette = s1->last_palette;
    width >>= 3;
    for(x = 0; x < width; x++) {
        ((PIXEL_TYPE *)d)[0] = palette[s[0]];
        ((PIXEL_TYPE *)d)[1] = palette[s[1]];
        ((PIXEL_TYPE *)d)[2] = palette[s[2]];
        ((PIXEL_TYPE *)d)[3] = palette[s[3]];
        ((PIXEL_TYPE *)d)[4] = palette[s[4]];
        ((PIXEL_TYPE *)d)[5] = palette[s[5]];
        ((PIXEL_TYPE *)d)[6] = palette[s[6]];
        ((PIXEL_TYPE *)d)[7] = palette[s[7]];
        d += BPP * 8;
        s += 8;
    }
}

void glue(vga_draw_cursor_line_, DEPTH)(Uns8 *d1,
                                        const Uns8 *src1,
                                        int poffset, int w,
                                        Uns32 color0,
                                        Uns32 color1,
                                        Uns32 color_xor)
{
    const Uns8 *plane0, *plane1;
    int x, b0, b1;
    Uns8 *d;

    d = d1;
    plane0 = src1;
    plane1 = src1 + poffset;
    for(x = 0; x < w; x++) {
        b0 = (plane0[x >> 3] >> (7 - (x & 7))) & 1;
        b1 = (plane1[x >> 3] >> (7 - (x & 7))) & 1;
#if DEPTH == 8
        switch(b0 | (b1 << 1)) {
        case 0:
            break;
        case 1:
            d[0] ^= color_xor;
            break;
        case 2:
            d[0] = color0;
            break;
        case 3:
            d[0] = color1;
            break;
        }
#elif DEPTH == 16
        switch(b0 | (b1 << 1)) {
        case 0:
            break;
        case 1:
            ((Uns16 *)d)[0] ^= color_xor;
            break;
        case 2:
            ((Uns16 *)d)[0] = color0;
            break;
        case 3:
            ((Uns16 *)d)[0] = color1;
            break;
        }
#elif DEPTH == 32
        switch(b0 | (b1 << 1)) {
        case 0:
            break;
        case 1:
            ((Uns32 *)d)[0] ^= color_xor;
            break;
        case 2:
            ((Uns32 *)d)[0] = color0;
            break;
        case 3:
            ((Uns32 *)d)[0] = color1;
            break;
        }
#else
#error unsupported depth
#endif
        d += BPP;
    }
}

#endif /* DEPTH != 15 */


/* XXX: optimize */

/*
 * 15 bit color
 */
static void glue(vga_draw_line15_, PIXEL_NAME)(VGAState *s1, Uns8 *d,
                                          const Uns8 *s, int width)
{
#if DEPTH == 15 && defined(WORDS_BIGENDIAN) == defined(TARGET_WORDS_BIGENDIAN)
    memcpy(d, s, width * 2);
#else
    int w;
    Uns32 v, r, g, b;

    w = width;
    do {
        v = lduw_raw((void *)s);
        r = (v >> 7) & 0xf8;
        g = (v >> 2) & 0xf8;
        b = (v << 3) & 0xf8;
        ((PIXEL_TYPE *)d)[0] = glue(rgb_to_pixel, PIXEL_NAME)(r, g, b);
        s += 2;
        d += BPP;
    } while (--w != 0);
#endif
}

/*
 * 16 bit color
 */
static void glue(vga_draw_line16_, PIXEL_NAME)(VGAState *s1, Uns8 *d,
                                          const Uns8 *s, int width)
{
#if DEPTH == 16 && defined(WORDS_BIGENDIAN) == defined(TARGET_WORDS_BIGENDIAN)
    memcpy(d, s, width * 2);
#else
    int w;
    Uns32 v, r, g, b;

    w = width;
    do {
        v = lduw_raw((void *)s);
        r = (v >> 8) & 0xf8;
        g = (v >> 3) & 0xfc;
        b = (v << 3) & 0xf8;
        ((PIXEL_TYPE *)d)[0] = glue(rgb_to_pixel, PIXEL_NAME)(r, g, b);
        s += 2;
        d += BPP;
    } while (--w != 0);
#endif
}

/*
 * 24 bit color
 */
static void glue(vga_draw_line24_, PIXEL_NAME)(VGAState *s1, Uns8 *d,
                                          const Uns8 *s, int width)
{
    int w;
    Uns32 r, g, b;

    w = width;
    do {
#if defined(TARGET_WORDS_BIGENDIAN)
        r = s[0];
        g = s[1];
        b = s[2];
#else
        b = s[0];
        g = s[1];
        r = s[2];
#endif
        ((PIXEL_TYPE *)d)[0] = glue(rgb_to_pixel, PIXEL_NAME)(r, g, b);
        s += 3;
        d += BPP;
    } while (--w != 0);
}

/*
 * 32 bit color
 */
static void glue(vga_draw_line32_, PIXEL_NAME)(VGAState *s1, Uns8 *d,
                                          const Uns8 *s, int width)
{
#if DEPTH == 32 && defined(WORDS_BIGENDIAN) == defined(TARGET_WORDS_BIGENDIAN) && !defined(BGR_FORMAT)
    memcpy(d, s, width * 4);
#else
    int w;
    Uns32 r, g, b;

    w = width;
    do {
#if defined(TARGET_WORDS_BIGENDIAN)
        r = s[1];
        g = s[2];
        b = s[3];
#else
        b = s[0];
        g = s[1];
        r = s[2];
#endif
        ((PIXEL_TYPE *)d)[0] = glue(rgb_to_pixel, PIXEL_NAME)(r, g, b);
        s += 4;
        d += BPP;
    } while (--w != 0);
#endif
}

#undef PUT_PIXEL2
#undef DEPTH
#undef BPP
#undef PIXEL_TYPE
#undef PIXEL_NAME
#undef BGR_FORMAT

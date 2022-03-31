/*
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

/*
 * Arm PrimeCell PL110 Color LCD Controller
 *
 * Copyright (c) 2005 CodeSourcery, LLC.
 * Written by Paul Brook
 *
 * This code is licenced under the GNU LGPL
 *
 */

#ifndef PIXEL_H_
#define PIXEL_H_

static inline Uns32 rgb_to_pixel8(unsigned int r, unsigned int g, unsigned b)
{
    return ((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6);
}

static inline Uns32 rgb_to_pixel15(unsigned int r, unsigned int g, unsigned b)
{
    return ((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3);
}

static inline Uns32 rgb_to_pixel16(unsigned int r, unsigned int g, unsigned b)
{
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

static inline Uns32 rgb_to_pixel24(unsigned int r, unsigned int g, unsigned b)
{
    return (r << 16) | (g << 8) | b;
}

static inline Uns32 rgb_to_pixel32(unsigned int r, unsigned int g, unsigned b)
{
    return (r << 16) | (g << 8) | b;
}

#endif /* PIXEL_H_ */

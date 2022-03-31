/* Copyright (c) 2007-2008 The Android Open Source Project
**
** This software is licensed under the terms of the GNU General Public
** License version 2, as published by the Free Software Foundation, and
** may be copied, distributed, and modified under those terms.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/

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


#ifndef FBSTATE_H_
#define FBSTATE_H_

#include "framebuffer.h"

#define MAX_RAMBUFFER (128 * 1024 * 1024)
#define MAX_TITLE_LENGTH 64

typedef struct fb_stateS {
    Uns32 fb_base;
    Bool  base_valid;
    Bool  need_update;
    Bool  blank;
} fb_stateT, *fb_stateP;

#define FB_INT_VSYNC             (1U << 0)
#define FB_INT_BASE_UPDATE_DONE  (1U << 1)

typedef QFrameBuffer  QFrameBufferT;
typedef QFrameBuffer* QFrameBufferP;

#endif /* FBSTATE_H_ */

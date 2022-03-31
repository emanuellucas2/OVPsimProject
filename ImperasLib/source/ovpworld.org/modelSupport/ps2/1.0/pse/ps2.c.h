/*
 * Keyboard to PS2 conversion.
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

#include <stdlib.h>

//#include "ps2.h"
#include "ps2Interface.h"

#include "peripheral/bhm.h"

extern  Uns32         diagnosticLevel;
#define DIAG_HIGH   ((diagnosticLevel & 3) >  2)
#define DIAG_MEDIUM ((diagnosticLevel & 3) >  1)
#define DIAG_LOW    ((diagnosticLevel & 3) >  0)

/* debug PC keyboard */
//#define DEBUG_KBD

/* debug PC keyboard : only mouse */
//#define DEBUG_MOUSE

/* Keyboard Commands */
#define KBD_CMD_SET_LEDS        0xED    /* Set keyboard leds */
#define KBD_CMD_ECHO            0xEE
#define KBD_CMD_GET_ID          0xF2    /* get keyboard ID */
#define KBD_CMD_SET_RATE        0xF3    /* Set typematic rate */
#define KBD_CMD_ENABLE          0xF4    /* Enable scanning */
#define KBD_CMD_RESET_DISABLE   0xF5    /* reset and disable scanning */
#define KBD_CMD_RESET_ENABLE    0xF6    /* reset and enable scanning */
#define KBD_CMD_RESET           0xFF    /* Reset */

/* Keyboard Replies */
#define KBD_REPLY_POR       0xAA    /* Power on reset */
#define KBD_REPLY_ACK       0xFA    /* Command ACK */
#define KBD_REPLY_RESEND    0xFE    /* Command NACK, send the cmd again */

/* Mouse Commands */
#define AUX_SET_SCALE11     0xE6    /* Set 1:1 scaling */
#define AUX_SET_SCALE21     0xE7    /* Set 2:1 scaling */
#define AUX_SET_RES         0xE8    /* Set resolution */
#define AUX_GET_SCALE       0xE9    /* Get scaling factor */
#define AUX_SET_STREAM      0xEA    /* Set stream mode */
#define AUX_POLL            0xEB    /* Poll */
#define AUX_RESET_WRAP      0xEC    /* Reset wrap mode */
#define AUX_SET_WRAP        0xEE    /* Set wrap mode */
#define AUX_SET_REMOTE      0xF0    /* Set remote mode */
#define AUX_GET_TYPE        0xF2    /* Get type */
#define AUX_SET_SAMPLE      0xF3    /* Set sample rate */
#define AUX_ENABLE_DEV      0xF4    /* Enable aux device */
#define AUX_DISABLE_DEV     0xF5    /* Disable aux device */
#define AUX_SET_DEFAULT     0xF6
#define AUX_RESET           0xFF    /* Reset aux device */
#define AUX_ACK             0xFA    /* Command byte ACK. */

#define MOUSE_STATUS_REMOTE     0x40
#define MOUSE_STATUS_ENABLED    0x20
#define MOUSE_STATUS_SCALE21    0x10

#define PS2_QUEUE_SIZE 256

typedef struct {
    Uns8 data[PS2_QUEUE_SIZE];
    Int32 rptr, wptr, count;
} PS2Queue;

typedef struct {
    PS2Queue queue;
    Int32   write_cmd;
    updateFn update;
} PS2State;

typedef struct {
    PS2State common;
    Int32 scan_enabled;
} PS2KbdState;

typedef struct {
    PS2State common;
    Uns8 mouse_status;
    Uns8 mouse_resolution;
    Uns8 mouse_sample_rate;
    Uns8 mouse_wrap;
    Uns8 mouse_type; /* 0 = PS2, 3 = IMPS/2, 4 = IMEX */
    Uns8 mouse_detect_state;
    Int32 mouse_dx; /* current values, needed for 'poll' mode */
    Int32 mouse_dy;
    Int32 mouse_dz;
    Uns8 mouse_buttons;
} PS2MouseState;


// ****************************************************************************
// Keyboard functions
// ****************************************************************************

/* Convert PC scan codes to raw scan codes.  */

static const Uns8 ps2_raw_keycode[128] = {
          0,118, 22, 30, 38, 37, 46, 54, 61, 62, 70, 69, 78, 85,102, 13,
         21, 29, 36, 45, 44, 53, 60, 67, 68, 77, 84, 91, 90, 20, 28, 27,
         35, 43, 52, 51, 59, 66, 75, 76, 82, 14, 18, 93, 26, 34, 33, 42,
         50, 49, 58, 65, 73, 74, 89,124, 17, 41, 88,  5,  6,  4, 12,  3,
         11,  2, 10,  1,  9,119,126,108,117,125,123,107,115,116,121,105,
        114,122,112,113,127, 96, 97,120,  7, 15, 23, 31, 39, 47, 55, 63,
         71, 79, 86, 94,  8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 87,111,
         19, 25, 57, 81, 83, 92, 95, 98, 99,100,101,103,104,106,109,110
};

void ps2_queue(void *opaque, Int32 b)
{
    PS2State *s = (PS2State *)opaque;
    PS2Queue *q = &s->queue;

    if (DIAG_MEDIUM)
        bhmMessage("I", "PS2", "ps2: queue 0x%02x (count %d)  %p\n", b, q->count, opaque);

    if (q->count >= PS2_QUEUE_SIZE) {
        bhmMessage("W", "PS2", "ps2: queue : FULL data lost 0x%02x\n", b);
        return;
    }
    q->data[q->wptr] = b;
    if (++q->wptr == PS2_QUEUE_SIZE)
        q->wptr = 0;
    q->count++;
    if(s->update) {
        s->update(1);
    }

}

// This function takes keyboard input and converts
void ps2_put_keycode(void *opaque, Int32 keycode)
{
    PS2KbdState *s = opaque;

    if (DIAG_MEDIUM)
        bhmMessage("I", "PS2", "ps2: put keycode 0x%02x\n", keycode);

    if (keycode < 0xe0)
      {
        if (keycode & 0x80)
            ps2_queue(&s->common, 0xf0);
        keycode = ps2_raw_keycode[keycode & 0x7f];
      }
    ps2_queue(&s->common, keycode);
}

Uns32 ps2_read_data(void *opaque)
{
    PS2State *s = (PS2State *)opaque;
    PS2Queue *q;
    Int32 val, index;


    q = &s->queue;
    if (q->count == 0) {
        /* NOTE: if no data left, we return the last keyboard one
           (needed for EMM386) */
        /* XXX: need a timer to do things correctly */
        index = q->rptr - 1;
        if (index < 0)
            index = PS2_QUEUE_SIZE - 1;
        val = q->data[index];
    } else {
        val = q->data[q->rptr];
        if (++q->rptr == PS2_QUEUE_SIZE)
            q->rptr = 0;
        q->count--;

        /* reading deasserts IRQ */
        if (s->update) {
            s->update( 0);
            /* reassert IRQs if data left */
            s->update(q->count != 0);
        }
    }
    if (DIAG_MEDIUM)
        bhmMessage("I", "PS2", "ps2: read data=0x%02x count %d\n", val, q->count);
    return val;
}

static void ps2_reset_keyboard(PS2KbdState *s, Uns32 scan)
{
    s->scan_enabled = scan;
}

void ps2_write_keyboard(void *opaque, Int32 val)
{
    PS2KbdState *s = (PS2KbdState *)opaque;

    if (DIAG_HIGH)
        bhmMessage("I", "PS2", "ps2: write keyboard 0x%02x command 0x%x\n", val, s->common.write_cmd);

    switch(s->common.write_cmd) {
    default:
    case -1:
        switch(val) {
        case 0x00:
            ps2_queue(&s->common, KBD_REPLY_ACK);
            break;
        case 0x05:
            ps2_queue(&s->common, KBD_REPLY_RESEND);
            break;
        case KBD_CMD_GET_ID:
            ps2_queue(&s->common, KBD_REPLY_ACK);
            ps2_queue(&s->common, 0xab);
            ps2_queue(&s->common, 0x83);
            break;
        case KBD_CMD_ECHO:
            ps2_queue(&s->common, KBD_CMD_ECHO);
            break;
        case KBD_CMD_ENABLE:
            s->scan_enabled = 1;
            ps2_queue(&s->common, KBD_REPLY_ACK);
            break;
        case KBD_CMD_SET_LEDS:
        case KBD_CMD_SET_RATE:
            s->common.write_cmd = val;
            ps2_queue(&s->common, KBD_REPLY_ACK);
            break;
        case KBD_CMD_RESET_DISABLE:
            ps2_reset_keyboard(s, 0);
            ps2_queue(&s->common, KBD_REPLY_ACK);
            break;
        case KBD_CMD_RESET_ENABLE:
            ps2_reset_keyboard(s, 1);
            ps2_queue(&s->common, KBD_REPLY_ACK);
            break;
        case KBD_CMD_RESET:
            ps2_reset_keyboard(s, 1);
            ps2_queue(&s->common, KBD_REPLY_ACK);
            ps2_queue(&s->common, KBD_REPLY_POR);
            break;
        default:
            ps2_queue(&s->common, KBD_REPLY_ACK);
            break;
        }
        break;
    case KBD_CMD_SET_LEDS:
        ps2_queue(&s->common, KBD_REPLY_ACK);
        s->common.write_cmd = -1;
        break;
    case KBD_CMD_SET_RATE:
        ps2_queue(&s->common, KBD_REPLY_ACK);
        s->common.write_cmd = -1;
        break;
    }
}


// ****************************************************************************
// Mouse processing functions
// ****************************************************************************


static void ps2_mouse_send_packet(PS2MouseState *s)
{
    Uns32 b;
    Int32 dx1, dy1, dz1;

    dx1 = s->mouse_dx;
    dy1 = s->mouse_dy;
    dz1 = s->mouse_dz;
    /* XXX: increase range to 8 bits ? */
    if (dx1 > 127)
        dx1 = 127;
    else if (dx1 < -127)
        dx1 = -127;
    if (dy1 > 127)
        dy1 = 127;
    else if (dy1 < -127)
        dy1 = -127;
    b = 0x08 | ((dx1 < 0) << 4) | ((dy1 < 0) << 5) | (s->mouse_buttons & 0x07);

    if (DIAG_HIGH)
        bhmMessage("I", "PS2", "ps2: ps2_mouse_send_packet val=%d, dx=%d, dy=%d mouse type %d", b, dx1, dy1, s->mouse_type);

    ps2_queue(&s->common, b);
    ps2_queue(&s->common, dx1 & 0xff);
    ps2_queue(&s->common, dy1 & 0xff);
    /* extra byte for IMPS/2 or IMEX */
    switch(s->mouse_type) {
    default:
        break;
    case 3:
        if (dz1 > 127)
            dz1 = 127;
        else if (dz1 < -127)
                dz1 = -127;
        ps2_queue(&s->common, dz1 & 0xff);
        break;
    case 4:
        if (dz1 > 7)
            dz1 = 7;
        else if (dz1 < -7)
            dz1 = -7;
        b = (dz1 & 0x0f) | ((s->mouse_buttons & 0x18) << 1);
        ps2_queue(&s->common, b);
        break;
    }

    /* update deltas */
    s->mouse_dx -= dx1;
    s->mouse_dy -= dy1;
    s->mouse_dz -= dz1;

    if (DIAG_HIGH)
        bhmMessage("I", "PS2", "ps2: update mouse\n");

}

void ps2_mouse_event(void *opaque,
                            Int32 dx, Int32 dy, Int32 dz, Int32 buttons_state)
{
    PS2MouseState *s = opaque;

    if (DIAG_HIGH)
        bhmMessage("I", "PS2", "ps2: ps2_mouse_event dx=%d, dy=%d, dz=%d, buttons_state=%d", dx, dy, dz, buttons_state);

    /* check if deltas are recorded when disabled */
    if (!(s->mouse_status & MOUSE_STATUS_ENABLED))
        return;

    s->mouse_dx += dx;
    s->mouse_dy -= dy;
    s->mouse_dz += dz;
    /* XXX: SDL sometimes generates nul events: we delete them */
    if (s->mouse_dx == 0 && s->mouse_dy == 0 && s->mouse_dz == 0 &&
        s->mouse_buttons == buttons_state)
    return;
    s->mouse_buttons = buttons_state;

    if (!(s->mouse_status & MOUSE_STATUS_REMOTE) &&
        (s->common.queue.count < (PS2_QUEUE_SIZE - 16))) {
        for(;;) {
            /* if not remote, send event. Multiple events are sent if
               too big deltas */
            ps2_mouse_send_packet(s);
            if (s->mouse_dx == 0 && s->mouse_dy == 0 && s->mouse_dz == 0)
                break;
        }
    }
    if (DIAG_HIGH)
        bhmMessage("I", "PS2", "ps2: mouse event\n");
}

void ps2_write_mouse(void *opaque, Int32 val)
{
    PS2MouseState *s = (PS2MouseState *)opaque;

    if (DIAG_HIGH)
        bhmMessage("I", "PS2", "kbd: write mouse 0x%02x\n", val);

    switch(s->common.write_cmd) {
    default:
    case -1:
        /* mouse command */
        if (s->mouse_wrap) {
            if (val == AUX_RESET_WRAP) {
                s->mouse_wrap = 0;
                ps2_queue(&s->common, AUX_ACK);
                return;
            } else if (val != AUX_RESET) {
                ps2_queue(&s->common, val);
                return;
            }
        }
        switch(val) {
        case AUX_SET_SCALE11:
            s->mouse_status &= ~MOUSE_STATUS_SCALE21;
            ps2_queue(&s->common, AUX_ACK);
            break;
        case AUX_SET_SCALE21:
            s->mouse_status |= MOUSE_STATUS_SCALE21;
            ps2_queue(&s->common, AUX_ACK);
            break;
        case AUX_SET_STREAM:
            s->mouse_status &= ~MOUSE_STATUS_REMOTE;
            ps2_queue(&s->common, AUX_ACK);
            break;
        case AUX_SET_WRAP:
            s->mouse_wrap = 1;
            ps2_queue(&s->common, AUX_ACK);
            break;
        case AUX_SET_REMOTE:
            s->mouse_status |= MOUSE_STATUS_REMOTE;
            ps2_queue(&s->common, AUX_ACK);
            break;
        case AUX_GET_TYPE:
            ps2_queue(&s->common, AUX_ACK);
            ps2_queue(&s->common, s->mouse_type);
            break;
        case AUX_SET_RES:
        case AUX_SET_SAMPLE:
            s->common.write_cmd = val;
            ps2_queue(&s->common, AUX_ACK);
            break;
        case AUX_GET_SCALE:
            ps2_queue(&s->common, AUX_ACK);
            ps2_queue(&s->common, s->mouse_status);
            ps2_queue(&s->common, s->mouse_resolution);
            ps2_queue(&s->common, s->mouse_sample_rate);
            break;
        case AUX_POLL:
            ps2_queue(&s->common, AUX_ACK);
            ps2_mouse_send_packet(s);
            break;
        case AUX_ENABLE_DEV:
            s->mouse_status |= MOUSE_STATUS_ENABLED;
            ps2_queue(&s->common, AUX_ACK);
            break;
        case AUX_DISABLE_DEV:
            s->mouse_status &= ~MOUSE_STATUS_ENABLED;
            ps2_queue(&s->common, AUX_ACK);
            break;
        case AUX_SET_DEFAULT:
            s->mouse_sample_rate = 100;
            s->mouse_resolution = 2;
            s->mouse_status = 0;
            ps2_queue(&s->common, AUX_ACK);
            break;
        case AUX_RESET:
            s->mouse_sample_rate = 100;
            s->mouse_resolution = 2;
            s->mouse_status = 0;
            s->mouse_type = 0;
            ps2_queue(&s->common, AUX_ACK);
            ps2_queue(&s->common, 0xaa);
            ps2_queue(&s->common, s->mouse_type);
            break;
        default:
            break;
        }
        break;
    case AUX_SET_SAMPLE:
        s->mouse_sample_rate = val;
        /* detect IMPS/2 or IMEX */
        switch(s->mouse_detect_state) {
        default:
        case 0:
            if (val == 200)
                s->mouse_detect_state = 1;
            break;
        case 1:
            if (val == 100)
                s->mouse_detect_state = 2;
            else if (val == 200)
                s->mouse_detect_state = 3;
            else
                s->mouse_detect_state = 0;
            break;
        case 2:
            if (val == 80)
                s->mouse_type = 3; /* IMPS/2 */
            s->mouse_detect_state = 0;
            break;
        case 3:
            if (val == 80)
                s->mouse_type = 4; /* IMEX */
            s->mouse_detect_state = 0;
            break;
        }
        ps2_queue(&s->common, AUX_ACK);
        if (DIAG_HIGH)
            bhmMessage("I", "PS2", "kbd: detect mouse type val %d, state %d type %d\n",
                                            val, s->mouse_detect_state, s->mouse_type);
        s->common.write_cmd = -1;
        break;
    case AUX_SET_RES:
        s->mouse_resolution = val;
        ps2_queue(&s->common, AUX_ACK);
        s->common.write_cmd = -1;
        break;
    }
}

// ****************************************************************************
// Common and initialisation
// ****************************************************************************

static void ps2_reset(void *opaque)
{
    PS2State *s = (PS2State *)opaque;
    PS2Queue *q;
    s->write_cmd = -1;
    q = &s->queue;
    q->rptr = 0;
    q->wptr = 0;
    q->count = 0;
}

void *ps2_kbd_init(updateFn update)
{
    PS2KbdState *s = (PS2KbdState *)malloc(sizeof(PS2KbdState));

    s->common.update = update;
    ps2_reset(&s->common);

    if(DIAG_LOW)
        bhmMessage("I", "PS2", "kbd: init diag %d    0x%p\n", diagnosticLevel, s);

    return s;
}

void *ps2_mouse_init(updateFn update)
{
    PS2MouseState *s = (PS2MouseState *)malloc(sizeof(PS2MouseState));

    s->common.update = update;
    ps2_reset(&s->common);

    if(DIAG_LOW)
        bhmMessage("I", "PS2", "mouse: init diag %d   0x%p\n", diagnosticLevel, s);

    return s;
}

/*
 * QEMU PC keyboard emulation
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

/* generic PSE interface, for all models using PS2 */


#include "peripheral/bhm.h"

extern  Uns32         diagnosticLevel;
#define DIAG_HIGH   ((diagnosticLevel & 3) >  2)
#define DIAG_MEDIUM ((diagnosticLevel & 3) >  1)
#define DIAG_LOW    ((diagnosticLevel & 3) >  0)

static Bool    isMouse     = False;
static Bool    isKeyboard  = False;
static Uns32   kbMouse     = 0;

#include "ps2Interface.h"
#include "sdlInputState.h"

#include "ps2.c.h"

void *keyboardHandle;
void *mouseHandle;

//
// Semihosted function: polls for the next SDL event
//
static FUNCTOHOST(Bool, kbControlPoll, InputStateP inputState, Uns32 kbMouse)

//
// Semihosted function: initilises the SDL input
//
static FUNCTOHOST(void, kbControlInit, Uns32 diag, Uns32 grabDisable, Uns32 cursorEnable)

//
// Semihosted function: cleanup the SDL input
//
static FUNCTOHOST(void, kbControlCleanUp)

Uns8 modifiers_state[256];

static void reset_keys(void)
{
    int i;
    for(i = 0; i < 256; i++) {
        if (modifiers_state[i]) {
            if (i & 0x80)
                ps2_put_keycode(keyboardHandle, 0xe0);
            ps2_put_keycode(keyboardHandle, i | 0x80);
            modifiers_state[i] = 0;
        }
    }
}


static void process_key(InputStateP is)
{
    Uns32 keycode = is->event.keyboard.key;

    switch(keycode) {
        case 0x00:
            // Should not get here!!
            bhmMessage("W", "PS2_IF", "reset not detected but Keycode indicates reset");
            return;
        case 0x2a:                          /* Left Shift */
        case 0x36:                          /* Right Shift */
        case 0x1d:                          /* Left CTRL */
        case 0x9d:                          /* Right CTRL */
        case 0x38:                          /* Left ALT */
        case 0xb8:                         /* Right ALT */
            if (is->event.keyboard.state == INP_KEYUP)
                modifiers_state[keycode] = 0;
            else
                modifiers_state[keycode] = 1;
            break;
        case 0x45: /* num lock */
        case 0x3a: /* caps lock */
            /* SDL does not send the key up event, so we generate it */
            ps2_put_keycode(keyboardHandle, keycode);
            ps2_put_keycode(keyboardHandle, keycode | 0x80);
            return;
    }

    if(DIAG_MEDIUM)
        bhmMessage("I", "PS2_IF", "process_key: key=0x%02x state=%d\n",
                                                    is->event.keyboard.key,
                                                    is->event.keyboard.state);

    /* now send the key code */
    if (keycode & 0x80)
        ps2_put_keycode(keyboardHandle, 0xe0);
    if (is->event.keyboard.state == KEYUP)
        ps2_put_keycode(keyboardHandle, keycode | 0x80);
    else
        ps2_put_keycode(keyboardHandle, keycode & 0x7f);
}


static void actOnEvent(InputStateP is)
{
    Uns32     v = 0;
    if(DIAG_MEDIUM)
        bhmMessage("I", "PS2_IF", "Event=%d", is->eventType);
    switch(is->eventType) {

        // **********************************************************
        // Keyboard Events
        // **********************************************************
        case INP_KEYRESET:
            /* sent when leaving window: reset the modifiers state */
            reset_keys();
            break;
        case INP_KEYUP_PAUSE:
            v |= 0x80;
        case INP_KEYDOWN_PAUSE:
            ps2_put_keycode(keyboardHandle, 0xe1);
            ps2_put_keycode(keyboardHandle, 0x1d | v);
            ps2_put_keycode(keyboardHandle, 0x45 | v);
            break;
        case INP_KEYNUMCAPSLOCK:
            ps2_put_keycode(keyboardHandle, is->event.keyboard.key);
            ps2_put_keycode(keyboardHandle, is->event.keyboard.key | 0x80);
            break;
        case INP_KEYUP:
        case INP_KEYDOWN: {
            if(DIAG_MEDIUM)
                bhmMessage("I", "PS2_IF", "keyboardHandle: key=0x%02x state=%d\n",
                                                is->event.keyboard.key,
                                                is->event.keyboard.state);
            process_key(is);
        }
        break;

        // **********************************************************
        // Mouse events
        // **********************************************************
        case INP_MOUSE_MOVE:
        case INP_MOUSE_BUTTONUP:
        case INP_MOUSE_BUTTONDOWN: {
            if(DIAG_MEDIUM)
                bhmMessage("I", "PS2_IF", "mouse: dx=%d, dy=%d, dz=%d, buttons_state=%d",
                                                is->event.mouse.dx,
                                                is->event.mouse.dy,
                                                is->event.mouse.dz,
                                                is->event.mouse.state);

            ps2_mouse_event(mouseHandle, is->event.mouse.dx,
                                      is->event.mouse.dy,
                                      is->event.mouse.dz,
                                      is->event.mouse.state);
        }
        break;
        // **********************************************************
        // Other events TODO: What todo with these events
        // **********************************************************
        case INP_VIDEOEXPOSE:  // the video window is exposed or hidden
        case INP_ACTIVEEVENT:
            break;
        // **********************************************************
        // Unrecognized events
        // **********************************************************
        default:
            if(DIAG_LOW)
                bhmMessage("W", "PS2_IF", "Unrecognised event %d", is->eventType);
        break;
    }
}

////////////////////////////////// RECORD / REPLAY ////////////////////////////////////

typedef enum ktEventTypesE {
    KT_NULL = 78,   // random non-zero number
    KT_EVENT,
    KT_NO_MORE_EVENTS,
    KT_FINISH
} ktEventTypes;

static Bool recording = False;
static Bool replaying = False;

static Bool recordOpen(void)
{
    return (recording = bhmRecordStart());
}

static Bool replayOpen(void)
{
    return (replaying = bhmReplayStart());
}

static void recordNullEvent(void)
{
    if(recording) {
        bhmRecordEvent(KT_NULL, 0, NULL);
    }
}

static void recordEvent(InputStateP is)
{
    if(recording) {
        bhmRecordEvent(KT_EVENT, sizeof(*is), is);
    }
}

static void recordEndOfGroup(void)
{
    if(recording) {
        bhmRecordEvent(KT_NO_MORE_EVENTS, 0, NULL);
    }
}

//
// Poll replay file instead of input device.
// The replay file should feed exactly the same events to actOnEvent()
// as the original run.
//
static void replayPoll(void)
{
    static Bool fetch = True;

    while(fetch) {

        Uns32      type;
        InputState inputState;

        // get next event from the replay file
        Int32 bytes = bhmReplayEvent(
            NULL, &type, sizeof(inputState), &inputState
        );

        if (bytes < 0) {

            // detect end-of-file
            fetch = False;

        } else {

            switch(type) {

                case KT_NULL:
                    return;

                case KT_EVENT:
                    actOnEvent(&inputState);
                    break;

                case KT_NO_MORE_EVENTS:
                    return;

                case KT_FINISH:
                    // legacy finish state (no longer generated, may be present
                    // in pre-recorded files)
                    fetch = False;
                    return;

                default:
                    bhmMessage("F", "PS2_IF", "Illegal entry in record file");
                    break;
            }
        }
    }
}

//
// Poll input device. This is called by an external event:
//     timer, host interrupt, writing to special location.
// If input is disabled, still poll (to clear the input queue)
// but ignore the input.
//
static void livePoll(Bool disableInput)
{
    if (disableInput) {
        return;
    }
    // Struct passed to and filled in by SDL interface
    InputState  inputState;
    Uns32       iters = 0;

    while(kbControlPoll(&inputState,kbMouse)) {
        actOnEvent(&inputState);
        recordEvent(&inputState);

        if(DIAG_MEDIUM) {
            bhmMessage("I", "PS2_IF", "Iterations %u", iters);
        }
        iters++;
    }
    if(iters == 0)
        recordNullEvent();
    else
        recordEndOfGroup();
}

void ps2Poll(Bool disableInput) {
    if (replaying) {
        replayPoll();

        // Dummy Poll to SDL for display update (if enabled)
        InputState  inputState;
        kbControlPoll(&inputState,kbMouse);
    } else {
        livePoll(disableInput);
    }
}

void ps2Init(Bool grabDisable, Bool cursorEnable, updateFn keyboardCB, updateFn mouseCB) {
    replayOpen();
    recordOpen();
    if(!replaying) {
        if(DIAG_LOW) {
            bhmMessage("W", "PS2_IF", "Starting. diagnostic level:%d  Grab Disable:%d Cursor Enable:%d",
                    diagnosticLevel,
                grabDisable, cursorEnable
            );
        }
        kbControlInit((diagnosticLevel & 8) && True, grabDisable, cursorEnable);
    } else {
        // SDL initialised for display update (if enabled)
        kbControlInit(False, True, True);
    }
    keyboardHandle   = ps2_kbd_init(keyboardCB);
    mouseHandle      = ps2_mouse_init(mouseCB);
}

void ps2Restore(void) {
    replayOpen();
    recordOpen();
}

void ps2Finish(void) {
    kbControlCleanUp();

    if(recording) {
        bhmRecordFinish();
    }
    if(replaying) {
        bhmReplayFinish();
    }
}

void ps2Queue(Uns8 b, Bool aux) {
    if(DIAG_HIGH)
        bhmMessage("I", "PS2_IF", "Queue 0x%02x for %s\n", b, aux ? "AUX" : "KBD" );

    if(aux) {
        ps2_queue(mouseHandle, b);
    } else {
        ps2_queue(keyboardHandle, b);
    }
}

void ps2WriteByte(Uns8 b, Bool aux) {
    if (aux)
        ps2_write_mouse(mouseHandle, b);
    else
        ps2_write_keyboard(keyboardHandle, b);
}

Uns8 ps2ReadByte(Bool aux) {
    if (aux)
        return ps2_read_data(mouseHandle);
    else
        return ps2_read_data(keyboardHandle);
}

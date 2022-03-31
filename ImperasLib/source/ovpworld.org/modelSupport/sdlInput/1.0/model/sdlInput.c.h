/*
 * QEMU SDL display driver
 *
 * Copyright (c) 2003 Fabrice Bellard
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


#include <SDL.h>
#include <stdlib.h>
#ifndef _WInt32
#include <signal.h>
#endif

#include "sdlInputState.h"
//#include "sdlInput.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

#include "keymap.h"

#define PREFIX "SIO_SDL_INP"

// Use this define to disable the mouse
//#define MOUSE_DISABLED

#define DIAG_EVENTS   1

static Uns32 diagLevel = 0;
static Uns32 grabDisable = 0;
static Uns32 enableCursor = 0;

static Uns32 gui_grab = 0; /* if true, all keyboard/mouse events are grabbed */
static Uns32 gui_key_modifier_pressed = 0;
static Uns32 gui_grab_code = KMOD_LALT | KMOD_LCTRL;

#define USE_MY_CURSOR (enableCursor == 1)
static SDL_Cursor *myCursor = 0;

static const char *arrow[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  "X c #000000",
  ". c #ffffff",
  "  c None",
  /* pixels */
  "X                               ",
  "XX                              ",
  "X.X                             ",
  "X..X                            ",
  "X...X                           ",
  "X....X                          ",
  "X.....X                         ",
  "X......X                        ",
  "X.......X                       ",
  "X........X                      ",
  "X.....XXXXX                     ",
  "X..X..X                         ",
  "X.X X..X                        ",
  "XX  X..X                        ",
  "X    X..X                       ",
  "     X..X                       ",
  "      X..X                      ",
  "      X..X                      ",
  "       XX                       ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "0,0"
};

static SDL_Cursor *init_system_cursor(const char *image[])
{
  int i, row, col;
  Uint8 data[4*32];
  Uint8 mask[4*32];
  int hot_x, hot_y;

  i = -1;
  for ( row=0; row<32; ++row ) {
    for ( col=0; col<32; ++col ) {
      if ( col % 8 ) {
        data[i] <<= 1;
        mask[i] <<= 1;
      } else {
        ++i;
        data[i] = mask[i] = 0;
      }
      switch (image[4+row][col]) {
        case 'X':
          data[i] |= 0x01;
          mask[i] |= 0x01;
          break;
        case '.':
          mask[i] |= 0x01;
          break;
        case ' ':
          break;
      }
    }
  }
  sscanf(image[4+row], "%d,%d", &hot_x, &hot_y);
  return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}

static SDL_Cursor *sdl_cursor_normal;

#ifdef DEFAULT_SCREEN

// This does not work when the video is initialised first.
// Need to find out why (but not now).
//
static void sdlDefaultScreen(void)
{
    Int32  flags = SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE;
    if (SDL_Init(flags)) {
        vmiMessage("E", PREFIX, "Could not initialize SDL");
        return;
    }
     Int32 videoFlags = SDL_ASYNCBLIT|SDL_HWACCEL;

    //flags |= SDL_FULLSCREEN;
    //flags |= SDL_NOFRAME;
    SDL_SetVideoMode(640, 480, 0, videoFlags);
    printf("set video mode\n");
}
#endif


void sdlInputInit(Uns32 diag, Uns32 grabDis, Uns32 enCurs)
{
    diagLevel = diag;
    grabDisable = grabDis;
    enableCursor = enCurs;

    if(diag)
        vmiMessage("I", PREFIX, "SDL Init diag %d, GUI Grab %s User Cursor %s",
                diag,
                grabDis ? "DISABLED" : "ENABLED",
                enCurs ? "DISABLED" : "ENABLED"
        );

#ifdef DEFAULT_SCREEN
    if (SDL_WasInit(SDL_INIT_VIDEO)==0) {
        sdlDefaultScreen();
    }
#endif
    sdl_cursor_normal = SDL_GetCursor();

    SDL_EnableKeyRepeat(250, 50);
    SDL_EnableUNICODE(1);

#ifdef MOUSE_DISABLED
    vmiMessage("W", PREFIX, "Mouse Input is Disabled");
#endif
}

/* specific keyboard conversions from scan codes */

#if (IMPERAS_WINDOWS==1)

static Uns8 sdl_keyevent_to_keycode(const SDL_KeyboardEvent *ev)
{
    if(diagLevel & DIAG_EVENTS)
        vmiMessage("I", PREFIX, "WIN23 sdl_keyevent_to_keycode scancode:%d\n",
                        ev->keysym.scancode
                    );
    return ev->keysym.scancode;
}

#else

static Uns8 sdl_keyevent_to_keycode(const SDL_KeyboardEvent *ev)
{
    Uns32 keycode;

    keycode = ev->keysym.scancode;

    if (keycode < 9) {
        keycode = 0;
    } else if (keycode < 97) {
        keycode -= 8; /* just an offset */
    } else if (keycode < 212) {
        /* use conversion table */
        keycode = _translate_keycode(keycode - 97);
    } else {
        keycode = 0;
    }
    if(diagLevel & DIAG_EVENTS)
        vmiMessage("I", PREFIX, "sdl_keyevent_to_keycode keycode %d (0x%x) scancode %d\n",
                        keycode,keycode,
                        ev->keysym.scancode
                    );
    return keycode;
}

#endif

static Uns32 process_key(SDL_KeyboardEvent *ev, Uns32 *keycode)
{
    Uns32 key;

    if (ev->keysym.sym == SDLK_PAUSE) {
        /* specific case */
        return SDL_KEYUP ? INP_KEYUP_PAUSE : INP_KEYDOWN_PAUSE;
    }

// TODO: Work out what mapping we need to support
//    if (kbd_layout) {
//        keycode = sdl_keyevent_to_keycode_generic(ev);
//    } else {
        key = sdl_keyevent_to_keycode(ev);
//    }
    *keycode = key;
    switch(key) {
    case 0x00:
        /* sent when leaving window: reset the modifiers state */
        return INP_KEYRESET;
    case 0x45: /* num lock */
    case 0x3a: /* caps lock */
        /* SDL does not send the key up event, so we generate it */
        return INP_KEYNUMCAPSLOCK;
    }

    return (ev->type == SDL_KEYUP) ? INP_KEYUP : INP_KEYDOWN;
}

char theTitle[128] = "Default Title";
char theIcon[16];

static void sdl_grab_start(void)
{
    static Bool gotCaption = False;
    if(!myCursor && USE_MY_CURSOR) {
        myCursor = init_system_cursor(arrow);
    }

    char *titleP;
    char *iconP;

    if(!gotCaption) {
        SDL_WM_GetCaption(&titleP, &iconP);
        gotCaption = True;
        // save title and icon for restore
        if(titleP)
            strncpy(theTitle, titleP, sizeof(theTitle));
        if(iconP)
            strncpy(theIcon, iconP, sizeof(theIcon));
    }

    if(!grabDisable) {
        SDL_WM_GrabInput(SDL_GRAB_ON);
        sdl_cursor_normal = SDL_GetCursor();// save current cursor
        if(myCursor)
            SDL_SetCursor(myCursor);
        else
            SDL_ShowCursor(0);

    }

    /* dummy read to avoid moving the mouse */
    SDL_GetRelativeMouseState(NULL, NULL);
    gui_grab = 1;
    if(diagLevel & DIAG_EVENTS) vmiMessage("I", PREFIX, "Mouse Grab Start\n");

    char buffer[128];
    if(!grabDisable) {
        snprintf(buffer, sizeof(buffer), "%s : Grabbed Keyboard and Mouse Ctl-Alt to Release", theTitle);
    } else {
        snprintf(buffer, sizeof(buffer), "%s : NO Grab of Keyboard and Mouse", theTitle);
    }
    SDL_WM_SetCaption(buffer, theIcon);

}

static void sdl_grab_end(void)
{
    if(!grabDisable) {
        SDL_WM_GrabInput(SDL_GRAB_OFF);
        SDL_SetCursor(sdl_cursor_normal);
        SDL_ShowCursor(1);
    }
    gui_grab = 0;
    if(diagLevel & DIAG_EVENTS) vmiMessage("I", PREFIX, "Mouse Grab End\n");
    SDL_WM_SetCaption(theTitle, theIcon);

}

Bool sdlInputPoll(InputStateP is, Uns32 kbMouse)
{
    SDL_Event  ev1;
    SDL_Event  *ev = &ev1;
    Bool       event = False;
    Uns32      keycode = 0;
    Uns32      mod_state = 0;
#ifdef MOUSE_DISABLED
mouse_disabled:
#endif

    Uns32 mask = (kbMouse == 1) ? SDL_MOUSEEVENTMASK :
          ((kbMouse == 2) ? ~SDL_MOUSEEVENTMASK :
          SDL_ALLEVENTS);

    SDL_PumpEvents();
    if (SDL_PeepEvents(ev, 1, SDL_GETEVENT, mask) > 0) {
        switch (ev->type) {
            case SDL_VIDEOEXPOSE:
                is->eventType = INP_VIDEOEXPOSE;
                if(diagLevel & DIAG_EVENTS)
                    vmiMessage("I", PREFIX, "Video Expose");
                event = True;
                break;
            case SDL_ACTIVEEVENT:
                is->eventType = INP_ACTIVEEVENT;
                if(diagLevel & DIAG_EVENTS)
                    vmiMessage("I", PREFIX, "Active Event gain %d state %d\ngui_grab %d, state == SDL_APPINPUTFOCUS %d, state == SDL_APPMOUSEFOCUS %d, active.gain %d\n",
                        ev->active.gain,
                        ev->active.state,
                        gui_grab,
                        ev->active.state == SDL_APPINPUTFOCUS,
                        ev->active.state == SDL_APPMOUSEFOCUS,
                        ev->active.gain);
#if 1
                if (gui_grab &&
                        (ev->active.state == SDL_APPINPUTFOCUS || ev->active.state == SDL_APPMOUSEFOCUS ) &&
                        !ev->active.gain) {
                    sdl_grab_end();
                }
#endif
                event = True;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                if(diagLevel & DIAG_EVENTS)
                    vmiMessage("I", PREFIX, "key%s  state:%d   mod:%d  sym:0x%x  unicode:0x%x scancode:0x%x\n",
                        ev->type == SDL_KEYUP ? "up" : "down",
                        ev->key.state,
                        ev->key.keysym.mod,
                        ev->key.keysym.sym,
                        ev->key.keysym.unicode,
                        ev->key.keysym.scancode
                    );

                if (ev->type == SDL_KEYDOWN) {
                    mod_state = (SDL_GetModState() & gui_grab_code) == gui_grab_code;
                    if(diagLevel & DIAG_EVENTS)
                        vmiMessage("I", PREFIX"_DEBUG", "SDL_GetModState 0x%08x ev->key.keysym.mod 0x%08x ",
                                                     SDL_GetModState(), ev->key.keysym.mod);
                    gui_key_modifier_pressed = mod_state;
                } else if (ev->type == SDL_KEYUP) {
                    mod_state = (ev->key.keysym.mod & gui_grab_code);
                    if (!mod_state) {
                        if (gui_key_modifier_pressed) {
                            gui_key_modifier_pressed = 0;
                            /* exit/enter grab if pressing Ctrl-Alt */
                            if (!gui_grab) {
                                /* if the application is not active, do not try to enter grab state.
                                 * It prevents 'SDL_WM_GrabInput(SDL_GRAB_ON)' from blocking all
                                 * the application (SDL bug). */
                                if (SDL_GetAppState() & SDL_APPACTIVE)
                                    sdl_grab_start();
                            } else {
                                sdl_grab_end();
                            }
                            /* SDL does not send back all the
                               modifiers key, so we must correct it */
//This is performed in the kbControl Function
//                            reset_keys();
//                            break;
                        }
                    }
                }

                is->eventType = process_key(&ev->key, &keycode);
                is->event.keyboard.key   = keycode;
                is->event.keyboard.state = ev->key.state;
                event = True;
                break;

            case SDL_QUIT:
                if(diagLevel & DIAG_EVENTS) vmiMessage("I", PREFIX, "sdl exit();\n");
                vmirtFinish(0); // stop simulation
                event = True;
                break;

            case SDL_MOUSEMOTION:
            {
#ifdef MOUSE_DISABLED
                goto mouse_disabled;
#endif
                // Reduce number of mouse motion events reported
                {
                    Uns32 i, rtnVal;
                    for(i=0;i<50;i++){
                        if ((rtnVal = SDL_PeepEvents(ev, 1, SDL_GETEVENT, SDL_EVENTMASK(SDL_MOUSEMOTION))) <= 0){
                            break;
                        }
                    }
                }
                if (gui_grab) {

                    Int32 dx, dy;
                    Uns32 state, buttons;
    //                SDL_MouseButtonEvent *bev = &ev->button;
                    state = SDL_GetRelativeMouseState(&dx, &dy);
                    buttons = 0;
                    if (state & SDL_BUTTON(SDL_BUTTON_LEFT))
                        buttons |= INP_MOUSE_LEFT;
                    if (state & SDL_BUTTON(SDL_BUTTON_RIGHT))
                        buttons |= INP_MOUSE_RIGHT;
                    if (state & SDL_BUTTON(SDL_BUTTON_MIDDLE))
                        buttons |= INP_MOUSE_MIDDLE;

                    is->eventType          = INP_MOUSE_MOVE;
                    is->event.mouse.x      = ev->motion.x;
                    is->event.mouse.y      = ev->motion.y;
                    is->event.mouse.button = buttons;
                    is->event.mouse.state  = state;
                    is->event.mouse.dx     = dx;
                    is->event.mouse.dy     = dy;
                    is->event.mouse.dz     = 0;

                    event = True;
                    if(diagLevel & DIAG_EVENTS) vmiMessage("I", PREFIX, "mouse motion event:%d buttons:%d state:%d x:%d y:%d dx:%d dy:%d dz:%d",
                            event,
                            is->event.mouse.button,
                            is->event.mouse.state,
                            is->event.mouse.x,
                            is->event.mouse.y,
                            is->event.mouse.dx,
                            is->event.mouse.dy,
                            is->event.mouse.dz
                        );
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
//#ifdef MOUSE_DISABLED
//                goto mouse_disabled;
//#endif
                Int32 dx, dy;
                Uns32 state, buttons;
                SDL_MouseButtonEvent *bev = &ev->button;
                if (!gui_grab) {
                    if (ev->type == SDL_MOUSEBUTTONDOWN &&
                        (bev->state & SDL_BUTTON_LMASK)) {
                        /* start grabbing all events */
                        sdl_grab_start();
                    }
                } else {
                    state = SDL_GetRelativeMouseState(&dx, &dy);
                    buttons = 0;
                    if (state & SDL_BUTTON(SDL_BUTTON_LEFT))
                        buttons |= INP_MOUSE_LEFT;
                    if (state & SDL_BUTTON(SDL_BUTTON_RIGHT))
                        buttons |= INP_MOUSE_RIGHT;
                    if (state & SDL_BUTTON(SDL_BUTTON_MIDDLE))
                        buttons |= INP_MOUSE_MIDDLE;

                    is->eventType          = SDL_MOUSEBUTTONUP ? INP_MOUSE_BUTTONUP : INP_MOUSE_BUTTONDOWN;
                    is->event.mouse.x      = ev->button.x;
                    is->event.mouse.y      = ev->button.y;
                    is->event.mouse.button = buttons;
                    is->event.mouse.state  = state;
                    is->event.mouse.dx = dx;
                    is->event.mouse.dy = dy;
                    is->event.mouse.dz = 0;     // TODO: mouse wheel

                    event = True;
                    if(diagLevel & DIAG_EVENTS) vmiMessage("I", PREFIX, "mouse button %s. button:%d state:%d x:%d y:%d dx %d dy %d dz %d",
                            ev->type ==  SDL_MOUSEBUTTONUP ? "up" : "down",
                            is->event.mouse.button,
                            is->event.mouse.state,
                            is->event.mouse.x,
                            is->event.mouse.y,
                            is->event.mouse.dx,
                            is->event.mouse.dy,
                            is->event.mouse.dz
                    );
                }
                break;
            }
            default:
                is->eventType              = INP_NONE;
                break;
        }
    }
    return event;
}

void sdlInputCleanUp()
{
    sdl_grab_end();

    if (myCursor) {
        SDL_FreeCursor(myCursor);
        myCursor = NULL;
    }

}

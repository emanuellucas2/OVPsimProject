#ifndef SDL_INPUT_STATE_H
#define SDL_INPUT_STATE_H

#ifdef _PSE_
#   include "peripheral/impTypes.h"
#else
#   include "hostapi/impTypes.h"
#endif

typedef enum eventTypeE {
    INP_NONE,
    INP_MOUSE_BUTTONUP,
    INP_MOUSE_BUTTONDOWN,
    INP_MOUSE_MOVE,
    INP_KEYRESET,
    INP_KEYUP,
    INP_KEYUP_PAUSE,        // special case to identify
    INP_KEYDOWN,
    INP_KEYDOWN_PAUSE,      // special case to identify
    INP_KEYNUMCAPSLOCK,
    INP_VIDEOEXPOSE,
    INP_ACTIVEEVENT
} eventType;

const char * eventTypeName[] = {
        "INP_NONE",
        "INP_MOUSE_BUTTONUP",
        "INP_MOUSE_BUTTONDOWN",
        "INP_MOUSE_MOVE",
        "INP_KEYRESET",
        "INP_KEYUP",
        "INP_KEYUP_PAUSE",        // special case to identify
        "INP_KEYDOWN",
        "INP_KEYDOWN_PAUSE",      // special case to identify
        "INP_KEYNUMCAPSLOCK",
        "INP_VIDEOEXPOSE",
        "INP_ACTIVEEVENT"
};

#define INP_MOUSE_LEFT          0x01
#define INP_MOUSE_MIDDLE        0x02
#define INP_MOUSE_RIGHT         0x04
#define INP_MOUSE_SCROLL_UP     0x08
#define INP_MOUSE_SCROLL_DOWN   0x10

typedef union InputEventU {
    struct mouseS {
        Uns8        button;
        Uns8        state;
        Uns16       x;
        Uns16       y;
        Int16       dx;
        Int16       dy;
        Int16       dz;
    } mouse;
    struct keyboardS {
        Uns8        key;
        Uns8        state;
    } keyboard;
} InputEvent;

typedef struct InputStateS {
    eventType      eventType;
    InputEvent     event;
} InputState, *InputStateP;

#define KEYUP   0
#define KEYDOWN 1

#endif

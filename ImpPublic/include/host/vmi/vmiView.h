/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */

/******************************************************************************/
/*                                                                            */
/*            V I R T U A L   M A C H I N E   I N T E R F A C E               */
/*                                                                            */
/*           R U N T I M E   C A L L A B L E   F U N C T I O N S              */
/*                                                                            */
/*                       V I E W   I N T E R F A C E                          */
/*                                                                            */
/******************************************************************************/


#pragma once

// basic types
#include "hostapi/simAddrTypes.h"

// VMI area includes
#include "vmi/vmiCommand.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiTyperefs.h"


////////////////////////////////////////////////////////////////////////////////
// VIEW USER INTERFACE
////////////////////////////////////////////////////////////////////////////////

//
// Install a callback to be invoked each time a view object is created or deleted
//
void vmiviewAddViewObjectNotificationCallback(
    vmiViewObjectNotifyFn   notifyCB,
    void                   *userData
);

//
// Remove callback which is invoked each time a view object is created or deleted
//
void vmiviewRemoveViewObjectNotificationCallback(
    vmiViewObjectNotifyFn   notifyCB,
    void                   *userData
);

//
// Install a callback to be invoked each time a view event is created or deleted
//
void vmiviewAddViewEventNotificationCallback(
    vmiViewEventNotifyFn    notifyCB,
    void                   *userData
);

//
// Remove callback which is invoked each time a view event is created or deleted
//
void vmiviewRemoveViewEventNotificationCallback(
    vmiViewEventNotifyFn    notifyCB,
    void                   *userData
);

//
// Install a callback to be invoked each time a particular view event occurs
//
void vmiviewAddViewEventListener(
    vmiViewEventP           event,
    vmiViewEventListenerFn  listenerCB,
    void                   *userData
);

//
// Remove callback which is invoked each time a particular view event occurs
//
void vmiviewRemoveViewEventListener(
    vmiViewEventP           event,
    vmiViewEventListenerFn  listenerCB,
    void                   *userData
);

//
// Return a view object's name (e.g. "registerA")
//
const char *vmiviewGetViewObjectName(vmiViewObjectP object);

//
// Return a view object's description string (or NULL if none available)
//
const char *vmiviewGetViewObjectDescription(vmiViewObjectP object);

//
// Return a view object's full path (e.g. "/platform/peripheral0/registerA")
//
const char *vmiviewGetViewObjectPath(vmiViewObjectP object);

//
// Return a view object's value
//
// The caller passes in a buffer and the buffer size in bytes.
// If the buffer is large enough the value is written to the buffer and the value type
// is returned, otherwise VMI_VVT_NOSPACE is returned and bufferSize is updated with
// the size required. VMI_VVT_ERROR is returned if no value is available for an object.
//
vmiViewValueType vmiviewGetViewObjectValue(
    vmiViewObjectP          object,
    void                   *buffer,
    Uns32                  *bufferSize
);

//
// Return a view object's value as a string
//
// The caller passes in a buffer and the buffer size in bytes.
// If the buffer is large enough the value string is written to the buffer and a pointer to the string
// is returned, otherwise NULL is returned and bufferSize is updated with the size required.
// NULL is returned with bufferSize of zero if no value is available for an object.
//
const char *vmiviewGetViewObjectValueString(
    vmiViewObjectP          object,
    void                   *buffer,
    Uns32                  *bufferSize
);

//
// Return a view object's parent object
//
vmiViewObjectP vmiviewGetViewObjectParent(vmiViewObjectP object);

//
// Return a view object's child object
//
vmiViewObjectP vmiviewGetViewObjectChild(vmiViewObjectP object);

//
// Return a view object's sibling object
//
vmiViewObjectP vmiviewGetViewObjectSibling(vmiViewObjectP object);

//
// Return a view event's name (e.g. "read")
//
const char *vmiviewGetViewEventName(vmiViewEventP event);

//
// Return a view event's description string (or NULL if none available)
//
const char *vmiviewGetViewEventDescription(vmiViewEventP event);

//
// Return a view event's full path (e.g. "/platform/peripheral0/registerA/read")
//
const char *vmiviewGetViewEventPath(vmiViewEventP event);

//
// Return a view event's parent object
//
vmiViewObjectP vmiviewGetViewEventParent(vmiViewEventP event);


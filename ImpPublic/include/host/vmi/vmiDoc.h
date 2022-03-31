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

#pragma once

#include "vmi/vmiTyperefs.h"
#include "hostapi/impTypes.h"

//
// Create a new node. The name is a paragraph or section heading.
//
vmiDocNodeP vmidocAddSection(vmiDocNodeP parent, const char *name);

//
// Create a new text node. The text will appear in the paragraph or section
//
vmiDocNodeP vmidocAddText(vmiDocNodeP node, const char *text);

//
// Set the root document node on a processor model.
//
void vmidocProcessor(vmiProcessorP processor, vmiDocNodeP document);

//
// Create a new node documenting a collection of bit fields - a register or instruction.
//
vmiDocNodeP vmidocAddFields(vmiDocNodeP parent, const char *name, Uns32 width);

//
// Create a new node documenting a field of one or more bits.
//
vmiDocNodeP vmidocAddField(
    vmiDocNodeP parent,
    const char *name,
    Uns32       offset,
    Uns32       width
);

//
// Alternative form of vmidocAddField, taking LSB and MSB
//
#define vmidocAddFieldMSLS(_PARENT, _NAME, _MSB, _LSB) \
    vmidocAddField(_PARENT, _NAME, _LSB, (_MSB)-(_LSB)+1)

//
// Create a new node documenting a constant field of one or more bits.
//
vmiDocNodeP vmidocAddConstField(
    vmiDocNodeP parent,
    Uns64       value,
    Uns32       offset,
    Uns32       width
);

//
// Alternative form of ppmDocAddConstField, taking LSB and MSB
//
#define vmidocAddConstFieldMSLS(_PARENT, _value, _MSB, _LSB) \
    vmidocAddConstField(_PARENT, _value, _LSB, (_MSB)-(_LSB)+1)



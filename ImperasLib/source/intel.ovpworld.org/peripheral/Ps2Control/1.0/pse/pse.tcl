#
# Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
#
# The contents of this file are provided under the Software License
# Agreement that you accepted before downloading this file.
#
# This source forms part of the Software and can be used for educational,
# training, and demonstration purposes but cannot be used for derivative
# works except in cases where the derivative works require OVP technology
# to run.
#
# For open source models released under licenses that you can use for
# derivative works, please visit www.OVPworld.org or www.imperas.com
# for the location of the open source models.
#
# NAME : Ps2Control

imodelnewperipheral  \
                -name    Ps2Control  \
                -vendor  intel.ovpworld.org  \
                -library peripheral  \
                -version 1.0  \
                -extensionfile model \
                -constructor constructor \
                -destructor  destructor

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "PS2 Keyboard/Mouse Controller."

iadddocumentation  \
                -name Limitations  \
                -text "This is a preliminary model with sufficient functionality
to enable Linux to Boot on the MIPS:MALTA platform.
Mouse functions are currently turned off."

iadddocumentation  \
                -name Reference  \
                -text "SMsC FDC37M817 Super I/O Controller Datasheet"

imodeladdbusslaveport  \
                -name config  \
                -size 0x8  \
                -mustbeconnected

imodeladdnetport  \
                -name kbdInterrupt   \
                -type output

imodeladdnetport  \
                -name mouseInterrupt   \
                -type output

imodeladdnetport -name reset   \
                 -type input

imodeladdformal -name disableInput  -type bool
iadddocumentation  -name Description  -text "If set, disables mouse and keyboard events."


imodeladdformal  -name pollPeriod  -type uns32 -defaultvalue 2000
iadddocumentation -name Description -text "Number of uS between each polling of the keyboard and mouse queues. (default 2000)"


imodeladdformal -name grabDisable -type bool
iadddocumentation -name Description -text "If set, disables grabbing of the mouse by the VGA/input window."

imodeladdformal  -name cursorEnable -type bool
iadddocumentation  -name Description  -text "If set, shows a basic software cursor in the VGA/input window at the mouse position."

imodeladdformal  -name isMouse -type bool
iadddocumentation  -name Description  -text "If set, turns on mouse input function."

imodeladdformal  -name isKeyboard -type bool
iadddocumentation  -name Description  -text "If set, turns on keyboard input function."

imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

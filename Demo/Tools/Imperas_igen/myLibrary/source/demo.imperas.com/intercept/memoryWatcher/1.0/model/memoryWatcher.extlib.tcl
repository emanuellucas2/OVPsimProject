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


imodelnewsemihostlibrary \
	-name           memoryWatcher \
	-vendor         demo.imperas.com \
	-library        intercept   \
	-version        1.0         \
	-imagefile      model       \
	-autoload

iadddocumentation -name Description \
	-text "Memory Watcher Intercept Library. Implements simple memory access monitor."

iadddocumentation -name Licensing \
	-text "Copyright (c) 2005-2021 Imperas Software Ltd. All Rights Reserved. Commercial License Required."

# Tool Control
imodeladdcommand -name memory -class "VMI_CT_DEFAULT"
iadddocumentation -name Description -handle memory \
    -text "Enable/disable memory region watch"
    
    imodeladdformalargument -name address -type address -handle memory
        iadddocumentation -name Description -handle memory/address \
            -text "Set the address for the base of the memory region to watch"

    imodeladdformalargument -name size -type uns32 -handle memory
        iadddocumentation -name Description -handle memory/size \
            -text "Set the size of the memory region to watch"


# Diagnostics Control
imodeladdcommand -name diagnostic  -class "VMI_CT_MODE|VMI_CO_DIAG|VMI_CA_REPORT"
iadddocumentation -name Description -handle diagnostic \
	-text "Set how much additional information is reported for the library"

	imodeladdformalargument -name level -type integer -handle diagnostic -class menu
		iadddocumentation -name Description -handle diagnostic/level \
			-text \
"Higher numbers print more diagnostic information
  Normally would be
    0 = off (initial, default)
    1 = startup and shutdown
    2 = changes of major modes, infrequent commands
    3 = full noisy."



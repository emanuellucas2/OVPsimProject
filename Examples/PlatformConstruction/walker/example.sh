#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# generate and compile the iGen created module
make -C module 

# compile the hand coded C harness
make -C harness

# run the module using the harness
harness/harness.${IMPERAS_ARCH}.exe --output walker.log \
    --modulepath module \
    --objectname u1/periph0 \
	$*
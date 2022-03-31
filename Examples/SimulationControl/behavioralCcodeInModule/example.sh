#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# generate and compile the iGen created module
make -C module 

# compile the hand coded C harness
make -C harness

# run the module using the local C harness (note no application)
harness/harness.${IMPERAS_ARCH}.exe $*

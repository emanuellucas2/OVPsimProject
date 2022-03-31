#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# compile the harness
make -C harness

# compile the design
make -C module

# run the platform
harness/harness.${IMPERAS_ARCH}.exe $*

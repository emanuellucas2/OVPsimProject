#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# compile the design
make -C module

# compile the harness
make -C harness

# note there is no application as the harness writes / reads the bus
./harness/harness.${IMPERAS_ARCH}.exe $*

#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=AARCH64

# compile the application
make -C application CROSS=${CROSS}

# compile the CPP harness
make -C harness

# run the harness
./harness/harness.${IMPERAS_ARCH}.exe  $*

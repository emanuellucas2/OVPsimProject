#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

# compile the application
make -C application CROSS=${CROSS}

# compile the platform
make -C platform

# run the platform
platform/platform.${IMPERAS_ARCH}.exe  $*


#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=RISCV32

# compile the application
make -C application CROSS=${CROSS}

# compile platform
make -C harness

# run the module using the harness
./harness/harness.${IMPERAS_ARCH}.exe  "$@"


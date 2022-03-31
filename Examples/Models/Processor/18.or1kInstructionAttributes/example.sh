#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# Use OP harness
HARNESS=harness

# Make all targets required for this example
make all
    
# Execute harness
platform/$HARNESS.${IMPERAS_ARCH}.exe --program application/asmtest.OR1K.elf


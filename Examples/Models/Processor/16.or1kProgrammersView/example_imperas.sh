#!/bin/bash

# Check Installation supports this example
checkinstall.exe -group imperas -p install.pkg --nobanner || exit

# Use OP harness (harness.*.exe) by default
HARNESS=harness

# Use legacy ICM harness (platform.*.exe) if BUILD_ICM_LEGACY=1
if [ "$BUILD_ICM_LEGACY" = 1 ] ; then 
    HARNESS=platform
fi
    
# Make all targets required for this example
make all

if [ "${IMPERAS_RUNTIME}" = "CpuManager" ]; then 

    # Execute harness
    platform/$HARNESS.${IMPERAS_ARCH}.exe \
        --program application/asmtest.OR1K.elf \
        --trace --mpdconsole
  
else

    echo "This example requires the Imperas Professional Tools - Not Available in current installation"
fi



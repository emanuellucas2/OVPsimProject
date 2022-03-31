#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg --nobanner || exit

ANSWER=
echo "Do you want to connect browser for user visualization ? [y/N]"
read ANSWER
if [ "${ANSWER}" = "y" ]; then
    echo "Enabling GPIO LED Port. Open and connect browser on port 8000"
    OPENPORT="--httpvis \
              --override ArmCortexMFreeRTOS.led/httpvisportnum=8000 \
              --override ArmCortexMFreeRTOS.sw/httpvisportnum=8001 \
              --wallclock"
else
    echo "Setting Diagnostics on ArmCortexMFreeRTOS/led to see LED state"
    DIAG="--override ArmCortexMFreeRTOS.led/diagnosticlevel=1"
fi

platform.${IMPERAS_ARCH}.exe \
        --verbose  --output imperas.log \
        \
        --override ArmCortexMFreeRTOS.cpu1/mips=12 \
        \
        --program ../FreeRTOS/FreeRTOSDemo.ARM_CORTEX_M3.elf \
        \
        $DIAG $OPENPORT \
        \
        "$@"

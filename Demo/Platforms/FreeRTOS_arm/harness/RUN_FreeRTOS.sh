#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg --nobanner || exit

ANSWER=
echo "Do you want to connect browser for user visualization ? [y/N]"
read ANSWER
if [ "${ANSWER}" = "y" ]; then
    echo "Enabling GPIO LED Port. Open and connect browser on port 8000"
    OPENPORT="--httpvis \
              --override ArmCortexMFreeRTOS/led/httpvisportnum=8000 \
              --override ArmCortexMFreeRTOS/sw/httpvisportnum=8001 \
              --wallclock"
  if [ -x /usr/bin/firefox ]; then 
    (sleep 1; firefox http://localhost:8000) &
  elif [ "$(uname)" = "MINGW32_NT-6.1" ]; then 
    (sleep 1; explorer http://localhost:8000) &
  else
    echo "Use 'firefox http://localhost:8000' to see visualization"
  fi
else
    echo "Setting Diagnostics on ArmCortexMFreeRTOS/led to see LED state"
    DIAG="--override ArmCortexMFreeRTOS/led/diagnosticlevel=1"
fi

harness.exe  \
        --verbose --output imperas.log \
        \
        --modulefile ../module/model.${IMPERAS_ARCH}.${IMPERAS_SHRSUF} \
        --override ArmCortexMFreeRTOS/cpu1/mips=12 \
        \
        --program ../FreeRTOS/FreeRTOSDemo.ARM_CORTEX_M3.elf \
        \
        $DIAG $OPENPORT \
        \
        "$@"

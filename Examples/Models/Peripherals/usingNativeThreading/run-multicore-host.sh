#!/bin/bash

# Check Installation supports this example
checkinstall.exe -g thread -p install.pkg --nobanner || exit

if [ -x module/model.${IMPERAS_SHRSUF} ]; then

harness.exe \
    --modulefile module/model.${IMPERAS_SHRSUF} \
    --program application/dataSortTest.ARM7TDMI.elf \
    --verbose --output multicorehost.log \
    --parallelperipherals \
    $@

# Enable quantum delay to run faster but not deterministic 
#     --override peripheralNativeThreadTest/sort*/quantumdelay=T

else

echo "Please run the build script to build this example" 

fi

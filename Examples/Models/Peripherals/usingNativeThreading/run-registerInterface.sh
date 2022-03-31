#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

if [ -x module/model.${IMPERAS_SHRSUF} ]; then

harness.exe \
    --modulefile module/model.${IMPERAS_SHRSUF} \
    --program application/dataSortTest.ARM7TDMI.elf \
    --verbose --output registeronly.log \
    --override peripheralNativeThreadTest/sort*/registeronly=T \
    $@

else

echo "Please run the build script to build this example" 

fi

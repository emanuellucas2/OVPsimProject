#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application CROSS=${CROSS}

make -C submodule
make -C topmodule

# run the platform
# flags that could be used
# --showdomains
# --showoverrides
# --override top/periph1/diagnosticlevel=0x3

harness.exe \
	--modulefile topmodule/model.${IMPERAS_SHRSUF} \
	--program application/application.${CROSS}.elf $*

echo "-- uartTTY0.log contents --"
cat uartTTY0.log
echo "-- uartTTY1.log contents --"
cat uartTTY1.log

#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=RISCV32

make -C application CROSS=${CROSS}

make -C submodule
make -C topmodule
make -C harness

harness/harness.${IMPERAS_ARCH}.exe \
	--program application/application.${CROSS}.elf $*

echo "-- subUart0-uart0.txt contents --"
cat subUart0-uart0.txt
echo "-- subUart1-uart0.txt contents --"
cat subUart1-uart0.txt

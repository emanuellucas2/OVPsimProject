#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application0 CROSS=${CROSS}
make -C application1 CROSS=${CROSS}

make -C topmodule
make -C submodule

harness.exe \
	--modulefile topmodule/model.${IMPERAS_SHRSUF} \
	--program simpleHierarchy/sub0/cpu1=application0/application0.${CROSS}.elf \
	--program simpleHierarchy/sub1/cpu1=application1/application1.${CROSS}.elf \
	$*


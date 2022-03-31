#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application0 CROSS=${CROSS}
make -C application1 CROSS=${CROSS}

VLNVROOT=$(pwd)/vlnvroot
VLNVSRC=$(pwd)/source

mkdir -p ${VLNVROOT}

make VLNVSRC=${VLNVSRC} \
     VLNVROOT=${VLNVROOT} \
     -f ${IMPERAS_HOME}/ImperasLib/buildutils/Makefile.library \
     VERBOSE=0

harness.exe \
	--vlnvroot ${VLNVROOT} \
	--modulevendor ovpworld.org --modulelibrary module --modulename simpleHierarchy_top --moduleversion 1.0 \
	--program simpleHierarchy_top/sub0/cpu1=application0/application0.${CROSS}.elf \
	--program simpleHierarchy_top/sub1/cpu1=application1/application1.${CROSS}.elf \
	$*


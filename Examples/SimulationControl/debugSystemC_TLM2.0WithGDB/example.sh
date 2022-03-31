#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

make -C application application.OR1K.elf

make -C platform -f ${IMPERAS_HOME}/ImperasLib/buildutils/Makefile.TLM.platform

platform/platform.${IMPERAS_ARCH}.exe application/application.OR1K.elf

#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=IMG_MIPS32R2LE
make -C application CROSS=${CROSS}
make -C platform NOVLNV=1

# Run C Platform
if [ -e platform/platform.${IMPERAS_ARCH}.exe ]; then

  echo "Run ITC example"
  platform/platform.${IMPERAS_ARCH}.exe -program   application/main.${CROSS}.elf \
                                        -exception application/genexception.${CROSS}.elf \
                                        -variant 34Kc \
                                        -endian little \
                                        -trace 3 \
                                        $@

else
  echo "C Platform not built"
fi


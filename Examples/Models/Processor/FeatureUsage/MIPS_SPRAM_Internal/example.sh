#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=IMG_MIPS32R2LE
make -C application CROSS=${CROSS}
make -C platform NOVLNV=1

# Run C Platform
if [ -e platform/platform.${IMPERAS_ARCH}.exe ]; then

  echo "Run ISPRAM/DSPRAM example"
  platform/platform.${IMPERAS_ARCH}.exe -program application/main.${CROSS}.elf \
                                        -spram1 application/ispram1.hex \
                                        -spram2 application/ispram2.hex \
                                        -variant 24Kc \
                                        -endian little \
                                        -trace 3 \
                                        $@

else
  echo "C Platform not built"
fi


#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

make -C platform

./platform/platform.${IMPERAS_ARCH}.exe \
    -output simulate.log \
    $*




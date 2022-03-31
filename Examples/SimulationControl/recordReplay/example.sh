#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application CROSS=${CROSS}

make -C module

make -C harness

mkdir -p recdir

./harness/harness.${IMPERAS_ARCH}.exe \
    --program u1/cpu1=application/application.${CROSS}.elf \
    --wallclock \
    --myrecord \
    $*

./harness/harness.${IMPERAS_ARCH}.exe \
    --program u1/cpu1=application/application.${CROSS}.elf \
    --wallclock \
    --myreplay \
    $*

# if we wanted to use built in support for control record / replay

#./harness/harness.${IMPERAS_ARCH}.exe \
#    --program u1/cpu1=application/application.${CROSS}.elf \
#    --wallclock \
#    --modelrecorddir recdir

#./harness/harness.${IMPERAS_ARCH}.exe \
#    --program u1/cpu1=application/application.${CROSS}.elf \
#    --wallclock \
#    --modelreplaydir recdir

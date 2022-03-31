#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

# compile the application
make -C application CROSS=${CROSS}

# generate and compile the iGen created module
make -C module 

# compile the hand coded C harness
make -C harness

# run the module using the local C harness

# tracing using configuration of CPU instance in module
echo "Trace using configuration of processor instance in module"
harness/harness.${IMPERAS_ARCH}.exe --program application/application.${CROSS}.elf --configurecpuinstance $*

# tracing using standard command line parser
echo "Trace using command line"
harness/harness.${IMPERAS_ARCH}.exe --program application/application.${CROSS}.elf --trace --traceshowicount --traceafter 2000 $*

echo "Direct trace output to a file"
harness/harness.${IMPERAS_ARCH}.exe \
    --program    application/application.${CROSS}.elf \
    --trace \
    --traceshowicount \
    --traceafter 2000 \
    --tracecount 10 \
    --tracefile  instructions.txt \
    $*

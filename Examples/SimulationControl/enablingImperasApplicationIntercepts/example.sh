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

# not enabled
echo "Run: Imperas Intercepts not enabled"
harness/harness.${IMPERAS_ARCH}.exe --program application/application.${CROSS}.elf $*

# enable using configuration of CPU instance in module
echo "Run: Imperas Intercepts enabled by configuration of processor instance in module"
harness/harness.${IMPERAS_ARCH}.exe --program application/application.${CROSS}.elf --configurecpuinstance $*

# enable with standard command line parser
echo "Run: Imperas Intercepts enabled by Standard command line"
harness/harness.${IMPERAS_ARCH}.exe --program application/application.${CROSS}.elf --imperasintercepts $*

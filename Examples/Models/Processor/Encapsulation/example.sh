#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(pwd)

make all XTHOME=$(pwd)/externalISS

platform.exe -program testcase.risc32

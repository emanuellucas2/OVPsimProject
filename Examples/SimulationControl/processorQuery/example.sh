#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


make -C harness NOVLNV=1


harness/harness.${IMPERAS_ARCH}.exe
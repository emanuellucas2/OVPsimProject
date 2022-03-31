#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


make -C application
make -C module
make -C harness

  
harness/harness.${IMPERAS_ARCH}.exe "$@"

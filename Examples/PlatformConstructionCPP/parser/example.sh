#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# compile the hand coded C harness
make -C harness

# -help shows new flags
harness/harness.${IMPERAS_ARCH}.exe \
           -help \
           | tee app1.log

# The new flags work correctly                 
harness/harness.${IMPERAS_ARCH}.exe \
           -extra1 \
           -extra2 33 \
           -output app2.log
           
# The new flag -extra2 required an argument                
harness/harness.${IMPERAS_ARCH}.exe \
           -extra1 \
           -extra2  \
           | tee  app1Error.log

# The new flag -extra2 required an integer argument                
harness/harness.${IMPERAS_ARCH}.exe \
           -extra1 \
           -extra2 q2 \
           | tee  app2Error.log
           
# The parser rejects an unexpected argument                
harness/harness.${IMPERAS_ARCH}.exe \
           -noWay 99 \
           | tee  app3Error.log

# The short form new flags work correctly                 
harness/harness.${IMPERAS_ARCH}.exe \
           -X \
           -Y 99  \
           -output app3.log
           


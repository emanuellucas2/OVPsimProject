#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# stop if error
set -e 

make -C platform    NOVLNV=1

make -C module      NOVLNV=1 

make -C peripheral  NOVLNV=1 

make -C applicationTx   

make -C applicationRx   

filename="portnumber.txt"
rm -f $filename

# Start Rx platform in background
platform/platform.${IMPERAS_ARCH}.exe \
    -topname    rx \
    -program    rx/m1/proc1=applicationRx/application.RISCV32.elf \
    -modeldiags 0x17 \
    -override   rx/m1/per1/portFile=$filename \
    -override   rx/m1/per1/client=F \
    -override   rx/m1/per1/portnum=0 \
    -output     rx.log \
    &

# when the port number is known it is written to the port file
# so, wait for the port file to appear
timeout=30
while [ ! -f $filename ]; do
    echo "wait for $filename timeout=$timeout"
    if [ $timeout -le 0 ]; then
        echo "# TIMEOUT waiting for $filename"
        exit
    fi
    sleep 1
    timeout=$(($timeout - 1))
done

portnum=$(cat $filename)
  
# Start Tx platform in background
platform/platform.${IMPERAS_ARCH}.exe \
    -topname    tx \
    -program    tx/m1/proc1=applicationTx/application.RISCV32.elf \
    -override   tx/m1/per1/client=T \
    -override   tx/m1/per1/portnum=$portnum \
    -override   tx/m1/per1/finishOnDisconnect=T \
    -modeldiags 0x17 \
    -output     tx.log


echo Finished

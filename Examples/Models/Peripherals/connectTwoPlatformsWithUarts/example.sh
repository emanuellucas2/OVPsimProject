#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C applicationSend           CROSS=$CROSS
make -C applicationSendForever    CROSS=$CROSS
make -C applicationReceive        CROSS=$CROSS

make -C module

portFile=portNumber.txt
rm -f $portFile

echo First platform: Server which sends bytes to socket.

harness.exe \
    --modulefile module/model \
    --program    applicationSend/application.$CROSS.elf  \
    --override   simpleCpuMemoryUart/periph0/client=0  \
    --override   simpleCpuMemoryUart/periph0/portnum=0 \
    --override   simpleCpuMemoryUart/periph0/portFile=$portFile \
    --output     server.log \
    &

# Wait for port number file to exist before reading the port number for 
# the client to use.

declare -i count=0
while [ ! -f $portFile ]; do
  sleep 1
  count=$(($count + 1))
  echo "waiting $count"
  if [ $count -ge 10 ]; then 
    echo "FAILED: Did not find $portFile"
    exit 1
  fi
done

PORTNUM=$(cat $portFile)
  
echo Second platform: client which reads bytes from socket.

OUTDIR=applicationReceive \
  harness.exe \
    --modulefile module/model \
    --program    applicationReceive/application.$CROSS.elf  \
    --override   simpleCpuMemoryUart/periph0/client=1  \
    --override   simpleCpuMemoryUart/periph0/portnum=$PORTNUM \
    --override   simpleCpuMemoryUart/periph0/hostname=localhost \
    --override   simpleCpuMemoryUart/periph0/finishOnDisconnect=1 \
    --output     client.log
 

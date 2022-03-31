#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application  CROSS=${CROSS}
make -C module       NOVLNV=1
make -C peripheral   NOVLNV=1

ANSWER=
echo "Do you want to open a browser to see the visualization [y/N]"
read ANSWER
if [ "${ANSWER}" = "y" ]; then
  if [ -x /usr/bin/firefox ]; then 
	(sleep 1; firefox http://localhost:8000) &
  elif [ "$(uname)" = "MINGW32_NT-6.1" ]; then 
    (sleep 1; explorer http://localhost:8000) &
  else
    echo "Use 'firefox http://localhost:8000' to see visualization"
  fi
fi

harness.exe --modulefile module \
    --objfilenoentry application/asmtest.${CROSS}.elf \
    --override processorExternalInterrupt/timerPeripheral/diagnosticlevel=3 \
    --override processorExternalInterrupt/httpvisportnum=8000 \
    --verbose --wallclock --output imperas.log \
    --httpvis \
    $*

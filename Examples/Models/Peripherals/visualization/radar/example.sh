#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=ARM7TDMI

#  compile the application
make -C application CROSS=${CROSS}

#  generate and compile the iGen created module
make -C module NOVLNV=1

#  compile the peripheral
make -C peripheral NOVLNV=1

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

# run the harness
harness.exe \
    --verbose --output imperas.log \
    --modulefile module/model.${IMPERAS_SHRSUF} \
    --program application/application.${CROSS}.elf \
    --override simpleMonitor/radar/diagnosticlevel=1 \
    \
    --httpvis \
    --override simpleMonitor/radar/httpvisportnum=8000 \
    $*

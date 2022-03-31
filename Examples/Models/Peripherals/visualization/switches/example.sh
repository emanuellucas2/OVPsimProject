#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

make -C application
make -C module           NOVLNV=1 
make -C peripheral       NOVLNV=1

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

harness.exe \
    --modulefile module/model.${IMPERAS_SHRSUF} \
    --program application/app.OR1K.elf \
    --verbose --output imperas.log \
    --stoponcontrolc \
    --httpvis \
    --override test/pse0/httpvisportnum=8000 \
    "$@"

#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg --nobanner || exit

# check for existence of cli.axf
if [ ! -f cli.axf ]; then
  echo "Error: cannot find file cli.axf, Please refer to README, Exiting"
  exit 1
fi

ANSWER=
echo "Do you want to open a browser to see the visualization [y/N]"
read ANSWER
if [ "${ANSWER}" = "y" ]; then
  if [ -x /usr/bin/firefox ]; then 
	(sleep 1; firefox visualization.html) &
  elif [ "$(uname)" = "MINGW32_NT-6.1" ]; then 
    (sleep 1; explorer visualization.html) &
  else
    echo "Use 'firefox visualization.html' to see visualization"
  fi
fi

harness.exe \
     --modulevendor   imperas.ovpworld.org \
     --modulelibrary  module \
     --modulename     ArmuKernel \
     --moduleversion  1.0 \
     --output imperas.log --verbose \
     \
    --extlib   ArmuKernel/cpu1_CPU0/pm=imperas.com/intercept/processorMonitorHttpvis/1.0 \
    --override ArmuKernel/cpu1_CPU0/pm/httpvisportnum=8000 \
    --extlib   ArmuKernel/cpu1_CPU1/pm=imperas.com/intercept/processorMonitorHttpvis/1.0 \
    --override ArmuKernel/cpu1_CPU1/pm/httpvisportnum=8001 \
    --extlib   ArmuKernel/cpu1_CPU2/pm=imperas.com/intercept/processorMonitorHttpvis/1.0 \
    --override ArmuKernel/cpu1_CPU2/pm/httpvisportnum=8002 \
    --extlib   ArmuKernel/cpu1_CPU3/pm=imperas.com/intercept/processorMonitorHttpvis/1.0 \
    --override ArmuKernel/cpu1_CPU3/pm/httpvisportnum=8003 \
    --extlib   ArmuKernel/cpu1_CPU0/pb=imperas.com/intercept/powerButtonHttpvis/1.0 \
    --override ArmuKernel/cpu1_CPU0/pb/httpvisportnum=8030 \
    --httpvis \
     "$@"

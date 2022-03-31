#!/bin/bash
# Run_MultiCore2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.ARM9T-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM940T \
    --numprocessors 2 --hishare 0x000fffff --loshare 0x0   \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@"



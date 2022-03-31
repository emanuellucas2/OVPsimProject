#!/bin/bash
# Run_MultiCore2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.RH850-O1-g.elf \
    --processorvendor renesas.ovpworld.org --processorname rh850 --variant RH850G3M \
    --numprocessors 2 --hishare 0x0010ffff --loshare 0x00100000   \
    "$@"



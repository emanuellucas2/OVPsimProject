#!/bin/bash
# Run_MultiCore2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.AARCH32-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant AArch32 \
    --numprocessors 2 --hishare 0x801fffff --loshare 0x80008000   \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@"



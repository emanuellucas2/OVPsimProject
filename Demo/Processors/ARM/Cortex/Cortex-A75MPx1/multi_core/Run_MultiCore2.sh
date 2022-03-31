#!/bin/bash
# Run_MultiCore2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.AARCH64-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A75MPx1 \
    --numprocessors 2 --hishare 0x800FFFFF --loshare 0x80000000   \
    --parameter endian=little    \
    "$@"



#!/bin/bash
# Run_Fibonacci.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.ARM_CORTEX_M4F-O3-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M4F \
    --numprocessors 1     \
    --parameter UAL=1 --parameter endian=little --override iss/cpu*/enableVFPAtReset=T  \
    "$@" \
    -argv 39


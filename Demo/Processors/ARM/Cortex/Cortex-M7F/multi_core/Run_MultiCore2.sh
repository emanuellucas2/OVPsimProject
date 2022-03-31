#!/bin/bash
# Run_MultiCore2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.ARM_CORTEX_M7F-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M7F \
    --numprocessors 2 --hishare 0x000fffff --loshare 0x0   \
    --parameter UAL=1 --parameter endian=little --override iss/cpu*/enableVFPAtReset=T  \
    "$@"



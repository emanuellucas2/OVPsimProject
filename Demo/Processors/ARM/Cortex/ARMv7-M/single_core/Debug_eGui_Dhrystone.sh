#!/bin/bash
# Debug_eGui_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M3-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant ARMv7-M \
    --numprocessors 1     \
    --parameter UAL=1 --parameter endian=little   \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"



#!/bin/bash
# Debug_eGui_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.AARCH32-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A32MPx1 \
    --numprocessors 1     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"



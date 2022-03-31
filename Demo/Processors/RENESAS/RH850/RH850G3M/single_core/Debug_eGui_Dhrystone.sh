#!/bin/bash
# Debug_eGui_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RH850-O1-g.elf \
    --processorvendor renesas.ovpworld.org --processorname rh850 --variant RH850G3M \
    --numprocessors 1     \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"



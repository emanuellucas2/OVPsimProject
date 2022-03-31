#!/bin/bash
# Debug_eGui_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O1-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V8_00 \
    --numprocessors 1     \
    --parameter endian=big    \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"



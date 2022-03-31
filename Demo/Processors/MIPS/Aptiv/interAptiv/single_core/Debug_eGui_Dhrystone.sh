#!/bin/bash
# Debug_eGui_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.IMG_MIPS32R2-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32_r1r5 --variant interAptiv \
    --numprocessors 1     \
    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"


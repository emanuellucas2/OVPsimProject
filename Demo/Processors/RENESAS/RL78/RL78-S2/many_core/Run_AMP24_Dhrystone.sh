#!/bin/bash
# Run_AMP24_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone_rl78/dhrystone_rl78.RL78-O1-g.elf \
    --processorvendor renesas.ovpworld.org --processorname rl78 --variant RL78-S2 \
    --numprocessors 24     \
    "$@" \
    -argv 500000


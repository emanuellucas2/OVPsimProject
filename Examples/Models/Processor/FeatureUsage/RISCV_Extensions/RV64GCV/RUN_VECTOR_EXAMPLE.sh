#!/bin/bash

# Check Installation supports the base requirements for this example
checkinstall.exe -p install.pkg --nobanner || exit

apps=$(ls *.elf | sort -d)
PS3='Please Choose Vector Example: '
select app in $apps
do
    break
done
echo "Selected Example $app"

${IMPERAS_ISS} \
    --verbose \
    --output imperas.vector.log \
    --program ${app} \
    --processorvendor riscv.ovpworld.org --processorname riscv \
    --variant RVB64I \
    --override iss/cpu0/add_Extensions=MAFDCVSU \
    --override iss/cpu0/vector_version=0.8 \
    --override iss/cpu0/VLEN=512 \
    --override iss/cpu0/SLEN=64 \
    "$@"

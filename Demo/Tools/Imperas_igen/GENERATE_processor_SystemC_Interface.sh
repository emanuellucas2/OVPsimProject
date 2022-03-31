#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg  --build --nobanner --warnonly || exit

echo
echo "------------------------------------------------------------------"
echo "- Generate Processor Model TLM 2.0 Interface from Compiled Model -"
echo "------------------------------------------------------------------"
echo "Press any key to continue . . ."
read ANSWER

igen.exe --modellibrary    processor          \
         --modelname       or1k               \
         --modelvendor     ovpworld.org       \
         --modelversion    1.0                \
         --variant         generic            \
         --writetlm        or1k.igen.tlm.hpp  \
         --overwrite                            || exit

echo
echo "-----------------------"
echo "- View Generated File -"
echo "-----------------------"
echo "Press any key to continue . . ."
read ANSWER

echo "- Open SystemC Interface file or1k.igen.tlm.hpp"
egui.exe -open or1k.igen.tlm.hpp
echo "Press any key to continue . . ."
read ANSWER

echo
echo "------------"
echo "- Complete -"
echo "------------"

#
# Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
#
# The contents of this file are provided under the Software License
# Agreement that you accepted before downloading this file.
#
# This source forms part of the Software and can be used for educational,
# training, and demonstration purposes but cannot be used for derivative
# works except in cases where the derivative works require OVP technology
# to run.
#
# For open source models released under licenses that you can use for
# derivative works, please visit www.OVPworld.org or www.imperas.com
# for the location of the open source models.
#

set vendor  sifive.ovpworld.org
set library peripheral
set name    PRCI
set version 1.0

imodelnewperipheral  \
	-name ${name} -vendor ${vendor} -library ${library} -version ${version}  \
	-imagefile pse.pse \
	-constructor constructor \
	-releasestatus ovp

iadddocumentation -name Description -text "Power Reset Clocking Interrupt (PRCI) block for SiFive FU540 chip"

iadddocumentation -name Limitations -text "None"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Reference   -text "SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)"
iadddocumentation -name Limitations -text "Register only model. Reset values based on typical post-ZSBL configuration (1GHz coreclk, 500MHz tlclk)."

imodeladdbusslaveport -name bport1 -mustbeconnected -size 0x1000

# REG address block
imodeladdaddressblock -name REG  -port bport1 -size 0x1000 -offset 0 -width 32
imodeladdlocalmemory  -name rsvd -addressblock bport1/REG -size 0x1000 \
                      -writefunction reservedWR -readfunction reservedRD
  
imodeladdmmregister -addressblock bport1/REG -name hfxosccfg -offset 0x00 -access rw -writefunction hfxosccfgWrite -writemask 0x80000000
    # Note: Based on HiFiveUnleashed hardware, bit positions in document appear to be wrong (31:30, not 30:29) 
    imodeladdfield -name XOSC_RDY   -bitoffset 30 -width 1  
    imodeladdfield -name XOSCCFG_EN -bitoffset 31 -width 1
    # Note: Reset values for post-ZSBL configuration
    imodeladdreset -name reset  -value 0xc0000000     

# parameter allows reset value to be changed from default
set corepllcfg0_Reset_Default 0x82110ec0
imodeladdformal -name corepllcfg0_Reset -type uns32 -defaultvalue ${corepllcfg0_Reset_Default}

imodeladdmmregister -addressblock bport1/REG -name corepllcfg0 -offset 0x04 -access rw -writemask 0x0031ffff
    imodeladdfield -name DIVR   -bitoffset  0 -width 6  
    imodeladdfield -name DIVF   -bitoffset  6 -width 9
    imodeladdfield -name DIVQ   -bitoffset 15 -width 3
    imodeladdfield -name RANGE  -bitoffset 18 -width 3
    imodeladdfield -name BYPASS -bitoffset 24 -width 1
    imodeladdfield -name FSE    -bitoffset 25 -width 1
    imodeladdfield -name LOCK   -bitoffset 31 -width 1
    # Note: Reset values for post-ZSBL configuration
    imodeladdreset -name reset  -value  ${corepllcfg0_Reset_Default}
  
imodeladdmmregister -addressblock bport1/REG -name ddrpllcfg0 -offset 0x0c -access rw -writemask 0x0031ffff
    imodeladdfield -name DIVR   -bitoffset  0 -width 6  
    imodeladdfield -name DIVF   -bitoffset  6 -width 9
    imodeladdfield -name DIVQ   -bitoffset 15 -width 3
    imodeladdfield -name RANGE  -bitoffset 18 -width 3
    imodeladdfield -name BYPASS -bitoffset 24 -width 1
    imodeladdfield -name FSE    -bitoffset 25 -width 1
    imodeladdfield -name LOCK   -bitoffset 31 -width 1
    # Note: Reset values for post-ZSBL configuration
    imodeladdreset -name reset  -value 0x82110dc0    
  
imodeladdmmregister -addressblock bport1/REG -name ddrpllcfg1 -offset 0x10 -access rw -writemask 0x01000000
    # Note: Based on HiFiveUnleashed hardware, bit position in document appear to be wrong (31. not 24)
    imodeladdfield -name CKE   -bitoffset  31 -width 1 
    # Note: Reset values for post-ZSBL configuration
    imodeladdreset -name reset  -value 0x80000000         
  
imodeladdmmregister -addressblock bport1/REG -name gemgxlpllcfg0 -offset 0x1c -access rw -writemask 0x0031ffff
    imodeladdfield -name DIVR   -bitoffset  0 -width 6  
    imodeladdfield -name DIVF   -bitoffset  6 -width 9
    imodeladdfield -name DIVQ   -bitoffset 15 -width 3
    imodeladdfield -name RANGE  -bitoffset 18 -width 3
    imodeladdfield -name BYPASS -bitoffset 24 -width 1
    imodeladdfield -name FSE    -bitoffset 25 -width 1
    imodeladdfield -name LOCK   -bitoffset 31 -width 1
    # Note: Reset values for post-ZSBL configuration
    imodeladdreset -name reset  -value 0x82128ec0 
  
imodeladdmmregister -addressblock bport1/REG -name gemgxlpllcfg1 -offset 0x20 -access rw -writemask 0x80000000
    # Note: Based on HiFiveUnleashed hardware, bit position in document appear to be wrong (31. not 24)
    imodeladdfield -name CKE   -bitoffset  24 -width 1 
    # Note: Reset values for post-ZSBL configuration
    imodeladdreset -name reset  -value 0x80000000   
  
imodeladdmmregister -addressblock bport1/REG -name coreclksel -offset 0x24 -access rw -writemask 0x00000001
    imodeladdfield -name CORECLKSEL -bitoffset  0 -width 1   
    # Note: Reset values for post-ZSBL configuration 
    imodeladdreset -name reset  -value 0x00000000
  
imodeladdmmregister -addressblock bport1/REG -name devicesresetreg -offset 0x28 -access rw -writemask 0x0000002f
    imodeladdfield -name DDR_CTRL_RST_N -bitoffset  0 -width 1
    imodeladdfield -name DDR_AXI_RST_N  -bitoffset  1 -width 1
    imodeladdfield -name DDR_AHB_RST_N  -bitoffset  2 -width 1
    imodeladdfield -name DDR_PHY_RST_N  -bitoffset  3 -width 1
    imodeladdfield -name GEMGXL_RST_N   -bitoffset  5 -width 1 
    # Note: Reset values for post-ZSBL configuration
    imodeladdreset -name reset  -value 0x0000002f      

imodeladdnetport -name reset  -type input  -updatefunction resetCB


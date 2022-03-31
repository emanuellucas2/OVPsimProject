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
# NAME : GD5446

imodelnewperipheral  \
                -name    GD5446  \
                -vendor  cirrus.ovpworld.org  \
                -library peripheral  \
                -version 1.0  \
                -extensionfile model \
                -constructor constructor \
                -destructor  destructor

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "Cirrus CL GD5446 VGA controller."

iadddocumentation  \
                -name Limitations  \
                -text "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform. 
                       The VGA peripheral utilises memory mapping. 
                       This requires the use of ICM memory for the frame buffers, which currently may stop its use in SystemC TLM2 platforms."

iadddocumentation  \
                -name Reference  \
                -text "CL-GD5446 Preliminary Databook, Version 2.0, November 1996" 
       
  imodeladdbusslaveport  \
                -name config  \
                -size 0x30  \
                -mustbeconnected

    imodeladdaddressblock  \
                -name ab  \
                -port config  \
                -width 8  \
                -size 0x30  \
                -offset 0x0
      imodeladdmmregister  \
                -name cr_index  \
                -addressblock config/ab  \
                -width 8  \
                -access rw  \
                -offset 0x04

      imodeladdmmregister  \
                -name cr  \
                -addressblock config/ab  \
                -width 8  \
                -access rw  \
                -offset 0x05

      imodeladdmmregister  \
                -name gr_index  \
                -addressblock config/ab  \
                -width 8  \
                -access rw  \
                -offset 0x1e

      imodeladdmmregister  \
                -name ar_index  \
                -addressblock config/ab  \
                -width 8  \
                -access rw  \
                -offset 0x10

      imodeladdmmregister  \
                -name ar  \
                -addressblock config/ab  \
                -width 8  \
                -access r  \
                -offset 0x11

      imodeladdmmregister  \
                -name msrWrite  \
                -addressblock config/ab  \
                -width 8  \
                -access w  \
                -offset 0x12

      imodeladdmmregister  \
                -name st00  \
                -addressblock config/ab  \
                -width 8  \
                -access r  \
                -offset 0x12

      imodeladdmmregister  \
                -name gr  \
                -addressblock config/ab  \
                -width 8  \
                -access rw  \
                -offset 0x1f

      imodeladdmmregister  \
                -name sr_index  \
                -addressblock config/ab  \
                -width 8  \
                -access rw  \
                -offset 0x14

      imodeladdmmregister  \
                -name sr  \
                -addressblock config/ab  \
                -width 8  \
                -access rw  \
                -offset 0x15

      imodeladdmmregister  \
                -name fcrWrite  \
                -addressblock config/ab  \
                -width 8  \
                -access w  \
                -offset 0x0a

      imodeladdmmregister  \
                -name st01  \
                -addressblock config/ab  \
                -width 8  \
                -access r  \
                -offset 0x0a

      imodeladdmmregister  \
                -name dac_read_index  \
                -addressblock config/ab  \
                -width 8  \
                -access rw  \
                -offset 0x17

      imodeladdmmregister  \
                -name dac_write_index  \
                -addressblock config/ab  \
                -width 8  \
                -access rw  \
                -offset 0x18

      imodeladdmmregister  \
                -name dac_cache  \
                -addressblock config/ab  \
                -width 8  \
                -access rw  \
                -offset 0x19

      imodeladdmmregister  \
                -name fcrRead  \
                -addressblock config/ab  \
                -width 8  \
                -access r  \
                -offset 0x1a

      imodeladdmmregister  \
                -name msrRead  \
                -addressblock config/ab  \
                -width 8  \
                -access r  \
                -offset 0x1c

  imodeladdbusslaveport  \
                -name memory  \
                -size 0x400000  \
                -mustbeconnected  \
                -remappable

  imodeladdbusslaveport  \
                -name PCIconfig  \
                -size 0x800  \
                -remappable

imodeladdformal -name PCIslot  -type uns32
iadddocumentation -name Description  -text "Specify which PCI slot the device occupies."

imodeladdformal -name PCIfunction -type uns32
iadddocumentation -name Description -text "Specify which PCI function the device responds to."


  imodeladdformal -name scanDelay -type uns32 -defaultvalue 200
  iadddocumentation  \
                -name Description  \
                -text "Number of uS between frame refreshes."

  imodeladdformal -name noGraphics -type bool
  iadddocumentation  \
                -name Description  \
                -text "If non:zero, disables the graphics window."

  imodeladdformal -name title -type string
  iadddocumentation  \
                -name Description  \
                -text "Title for the VGA screen."


  imodeladdformal -name endian -type string -defaultValue "little"
  iadddocumentation  \
                -name Description  \
                -text "Set the system endian, \"big\" or \"little\"; used for writing boot code. Default is \"little\" endian."

imodeladdformal -name pixelChecksum -type boolean			  
  iadddocumentation -name Description \
                -text "Write a checksum of each screen contents"
			  
			  


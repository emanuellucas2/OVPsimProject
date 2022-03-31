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
# NAME : SmartLoaderLinux

imodelnewperipheral  \
                -name SmartLoaderLinux  \
                -vendor mips.ovpworld.org  \
                -library peripheral  \
                -version 1.0  \
                -imagefile pse.pse \
                -releasestatus ovp  \
                -constructor constructor \
                -destructor  destructor

  iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

  iadddocumentation  \
                -name Description  \
                -text "Smart peripheral creates memory initialisation for a MIPS32 based Linux kernel boot.
    Performs the generation of boot code at the reset vector (virtual address 0xbfc00000) of the MIPS32 processor. 
    Loads both the linux kernel and initial ramdisk into memory and patches the boot code to jump to the kernel start. 
    Initialises the MIPS32 registers and Linux command line."

  iadddocumentation  \
                -name Reference  \
                -text "MIPS Malta User Manual. MIPS Boot code reference."

  iadddocumentation  \
		-name Limitations  \
		-text "None"

  imodeladdbusmasterport  \
                -name mport  \
                -addresswidthmin 32 \
                -addresswidthmax 40 
                
  iadddocumentation  \
                -name Description  \
                -text "This is a master port to access the memory in the system for initalisation of initrd and writing boot code to the reset vector"

  imodeladdbusslaveport  \
                -name idport  \
                -size 4
  iadddocumentation  \
                -name Description  \
                -text "This is a slave port that provides the boardId for Malta (default 0x420)"
  imodeladdaddressblock -port idport -name ab -offset 0 -size 4 -width 32
  imodeladdlocalmemory -addressblock idport/ab -name id -access r -size 4 -readfunction readBoardId -writefunction writeBoardId


  imodeladdformal  \
                -name kernel  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "This must specify the name of the Linux kernel that is being loaded. This must be consistent with the imagefile loaded and specified by the imagefile attribute on the processor."


  imodeladdformal  \
                -name dtb  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Optionally specific the flattened device tree blob file specifying the development board details for the Linux kernel to read."


  imodeladdformal  \
                -name envpaddress  \
                -type uns32 -defaultvalue 0x80002000
  iadddocumentation  \
                -name Description  \
                -text "The hex address in virtual memory that contains the command line. Default 0x80002000."


  imodeladdformal  \
                -name initrd  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Specify a compressed initial ram disk file file for loading."


  imodeladdformal  \
                -name root  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Specify the root filesystem for booting. This is a string of the form '/dev/hda1'."


  imodeladdformal  \
                -name boardid  \
                -type uns32
  iadddocumentation  \
                -name Description  \
                -text "Allows the boardID to be configured. Defaults to 0x420 for Malta with CoreLV."


  imodeladdformal  \
                -name memsize  \
                -type uns32 -defaultvalue [expr 128*1024*1024]
  iadddocumentation  \
                -name Description  \
                -text "The decimal size of the available memory. For Example 128MBytes is 134217728."


  imodeladdformal  \
                -name command  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "This attribute allows an additional kernal command(s) to be added."


  imodeladdformal  \
                -name nonelinux  \
                -type bool
  iadddocumentation  \
                -name Description  \
                -text "This attribute allows a non linux program to be loaded onto the Malta platform. 
                                         The program elf should be passed as though it was the kernel file."


  imodeladdformal  \
                -name bootimage  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "This attribute is used to pass a new boot image for the non:volatile memory 
                                         that contains the reset vector from which the procesor starts execution."


  imodeladdformal  \
                -name endian  \
                -defaultValue "little" \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Set the system endian, \"big\" or \"little\"; used for writing boot code. Default is \"little\" endian."

imodeladdformal -name goldfish  -type bool
iadddocumentation  -name Description   -text "This attribute is used to indicate that the peripheral is being used to configure the Android Goldfish platform."

imodeladdformal  \
                -name writebootimage  \
                -type string
iadddocumentation  \
              -name Description  \
              -text "This attribute is used to control the writing of a file of the boot code containing the reset vector from which the procesor starts execution."

imodeladdformal  \
                 -name fixuplinuxstart  \
                 -type uns32
iadddocumentation  \
                 -name Description  \
                 -text "This attribute is used to set the address at which the the code should be 'fixed' 
                        to add the setup required for booting a linux kernel
                        a0 = number of kernel arguments
                        a1 = command table start
                        a2 = command line arguments start
                        a3 = size fo physical ram"

imodeladdformal    -name disablebootgen -type bool
iadddocumentation  -name Description    -text "Disable the generation of boot code."
     
imodeladdformal   -name disable  -type bool
iadddocumentation  -name Description  -text "Disable this peripheral. Only provides the boardId in this case."

imodeladdformal   -name PCIslot     -type uns32
iadddocumentation -name Description -text "Specify the PCI slot."
                  
imodeladdformal   -name PCIfunction -type uns32
iadddocumentation -name Description -text "Specify the PCI function number."

set pageBitsDefault 12
imodeladdformal   -name pagebits -type uns32 -defaultvalue $pageBitsDefault
iadddocumentation -name Description -text "Specify the number of bits to be used when aligning the initrd data (should match page size configured into kernel). default=$pageBitsDefault."

imodeladdformal   -name initrdhigh -type bool
iadddocumentation -name Description -text "Locate the initial ramdisk in top of memory. By default the ramdisk is located in the next page after the top of the kernel image."

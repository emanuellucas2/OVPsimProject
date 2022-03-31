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

imodelnewperipheral  \
    -name        intc \
    -vendor      ovpworld.org  \
    -library     peripheral \
    -version     1.0 \
    -constructor constructor \
    -destructor  destructor  \
    -nbyteregisters 

iadddocumentation -name Description -text "Dual 32 channel interrupt controller"
iadddocumentation -name Description -text "Each channel has 32 inputs and one output. The channels are not connected."
iadddocumentation -name Description -text "Each channel has a control register and a register for each of the 32 inputs."
iadddocumentation -name Description -text "With the control priority bit clear each input will produce an interrupt when it transitions to the active state.
 With it set, an interrupt is produced only if the priority in the input register is higher than the current priority."

imodeladdnetport -name systemReset -type input  -updatefunction resetDevice
iadddocumentation -name Description -text "Device reset"

imodeladdnetport -name intin%u -type input -loarray 0 -hiarray 63 -updatefunction interruptArrived -updatefunctionargument _index
iadddocumentation -name Description -text "Interrupt Request Inputs"

imodeladdnetport -name intout -type output -loarray 1 -hiarray 2
iadddocumentation -name Description -text "Interrupt Outputs to the processor"

imodeladdbusslaveport -name sp1 -size 128 -mustbeconnected
iadddocumentation -name Description -text "Register Slave Port"

# Address block for 8 bit control registers
imodeladdaddressblock -name ch%u -loarray 0 -hiarray 1 -port sp1 -width 8  -offset 0 -size 64 

# common control register
imodeladdmmregister -addressblock sp1/ch%u -name channelControl    -offset 0 -writefunction writeChannelControl 
  iadddocumentation -name Description -text "Control register for one channel"
    imodeladdreset -name systemReset 
    
  
    imodeladdfield      -mmregister sp1/ch%u/channelControl -name enable   -bitoffset 0 -width 1  -reset 0
      iadddocumentation -name Description -text "A one in this bit will enable the channel"
    
    imodeladdfield      -mmregister sp1/ch%u/channelControl -name usePriority -bitoffset 1 -width 1  -reset 0
      iadddocumentation -name Description -text "A one in this bit will make the channel use the priority system"
      
    imodeladdfield      -mmregister sp1/ch%u/channelControl -name currentPriority  -bitoffset 4 -width 4  -reset 0
      iadddocumentation -name Description -text "This field holds the current interrupt priority level"

# one register per input
imodeladdmmregister -addressblock sp1/ch%u -name pinControl%u -loarray 0 -hiarray 31    -offset 32 -writefunction writePinControl
  iadddocumentation -name Description -text "Control register for one input"
      imodeladdreset -name systemReset 

      imodeladdfield      -mmregister sp1/ch%u/pinControl%u -name enable    -bitoffset 0 -width 1  -reset 0
        iadddocumentation -name Description -text "Enable this input"
        
      imodeladdfield      -mmregister sp1/ch%u/pinControl%u -name invert    -bitoffset 1 -width 1  -reset 0
        iadddocumentation -name Description -text "Make this input active low"
      
      imodeladdfield      -mmregister sp1/ch%u/pinControl%u -name asserted  -bitoffset 2 -width 1  -reset 0 
        iadddocumentation -name Description -text "Show if this input is asserted. Write a zero to clear."
        
      imodeladdfield      -mmregister sp1/ch%u/pinControl%u -name raw       -bitoffset 3 -width 1  -reset 0 -access r
        iadddocumentation -name Description -text "Raw value of the interrupt input"
      
      imodeladdfield      -mmregister sp1/ch%u/pinControl%u -name priority   -bitoffset 4 -width 4  -reset 1
        iadddocumentation -name Description -text "Priority of this input (0-15)"




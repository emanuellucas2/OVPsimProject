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

set range    0x1000
set regWidth 32

imodelnewperipheral  \
    -imagefile pse.pse  \
    -name      gem \
    -vendor    cadence.ovpworld.org  \
    -library   peripheral \
    -version   1.0 \
    \
    -constructor constructor \
    -destructor destructor \
    -releasestatus ovp

iadddocumentation -name Description -text "Model of Cadence Gigabit Ethernet Controller (GEM). For further details please consult README-EMAC.txt"
iadddocumentation -name Description -text "This model is based upon the data and use in the Xilinx Zynq"
iadddocumentation -name Description -text "Basic network Tx/Rx functionality tested using Xilinx Linux Kernel using wget and other similar tools"
iadddocumentation -name Description -text "Tested with Xilinx SDK Example driver."
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "This model is based upon the data from the Xilinx Zynq platform, other registers may not be included."
iadddocumentation -name Limitations -text "Does not implement: VLAN, pause frames, filtering or timestamps."
iadddocumentation -name Reference   -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

# Irq net port
imodeladdnetport -name irq -type output
iadddocumentation -name Description -text "IRQ Pin"

#
# Interface to the packetnet network. The maxbytes parameter sets the maximum
# packet length supported by this network, enforced by the simulator.
# Max Ethernet Frame = 1522 bytes
# size indicator 2 bytes (unsigned short int)
# total = 1524
imodeladdpacketnetport \
    -name phy \
    -maxbytes 1524
iadddocumentation -name Description -text "The port to connect the packetnet virtual network"

set port  bport1
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32


imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead





# Master port
imodeladdbusmasterport -name bport2 -addresswidth 32 -mustbeconnected
iadddocumentation -name Description -text "DMA Master Port"

set registers {
    net_ctrl              0x00000000 32 rw 0x00000000  auto auto  -  "Network Control"
    net_cfg               0x00000004 32 rw 0x00080000  -  -  -  "Network Configuration"
    net_status            0x00000008 32 r  0x00000004  -  -  -  "Network Status"
    user_io               0x0000000c 32 rw 0x00000000  -  -  -  "User IO (Not in TRM)"
    dma_cfg               0x00000010 32 rw 0x00020784  -  -  -  "DMA Configuration"
    tx_status             0x00000014 32 rw 0x00000000  - auto -  "Transmit Status"
    rx_qbar               0x00000018 32 rw 0x00000000  - auto -  "Receive Buffer Queue Base Address"
    tx_qbar               0x0000001C 32 rw 0x00000000  - auto -  "Transmit Buffer Queue Base Address"
    rx_status             0x00000020 32 rw 0x00000000  - auto -  "Receive Status"
    intr_status           0x00000024 32 rw 0x00000000  auto auto -  "Interrupt Status"
    intr_en               0x00000028 32  w 0x00000000  - auto -  "Interrupt Enable"
    intr_dis              0x0000002C 32  w 0x00000000  - auto -  "Interrupt Disable"
    intr_mask             0x00000030 32 rw 0x0001FFFF  - auto -  "Interrupt Mask Status"
    phy_maint             0x00000034 32 rw 0x00000000  - auto -  "PHY Maintenance"
    rx_pauseq             0x00000038 32 r  0x00000000  -  -  -  "Received Pause Quantum"
    tx_pauseq             0x0000003C 32 rw 0x0000FFFF  -  -  -  "Transmit Pause Quantum"
    gem_jml               0x00000048 32 rw 0x000005EE  -  -  -  "GEM Jumbo Max Length"
    hash_bot              0x00000080 32 rw 0x00000000  -  -  -  "Hash Register Bottom [31:0]"
    hash_top              0x00000084 32 rw 0x00000000  -  -  -  "Hash Register Top [63:32]"
    spec_addr1_bot        0x00000088 32 rw 0x00000000  -  -  -  "Specific Address 1 Bottom [31:0]"
    spec_addr1_top        0x0000008C 32 rw 0x00000000  -  -  -  "Specific Address 1 Top [47:32]"
    spec_addr2_bot        0x00000090 32 rw 0x00000000  -  -  -  "Specific Address 2 Bottom [31:0]"
    spec_addr2_top        0x00000094 32 rw 0x00000000  -  -  -  "Specific Address 2 Top [47:32]"
    spec_addr3_bot        0x00000098 32 rw 0x00000000  -  -  -  "Specific Address 3 Bottom [31:0]"
    spec_addr3_top        0x0000009C 32 rw 0x00000000  -  -  -  "Specific Address 3 Top [47:32]"
    spec_addr4_bot        0x000000A0 32 rw 0x00000000  -  -  -  "Specific Address 4 Bottom [31:0]"
    spec_addr4_top        0x000000A4 32 rw 0x00000000  -  -  -  "Specific Address 4 Top [47:32]"
    type_id_match1        0x000000A8 32 rw 0x00000000  -  -  -  "Type ID Match 1"
    type_id_match2        0x000000AC 32 rw 0x00000000  -  -  -  "Type ID Match 2"
    type_id_match3        0x000000B0 32 rw 0x00000000  -  -  -  "Type ID Match 3"
    type_id_match4        0x000000B4 32 rw 0x00000000  -  -  -  "Type ID Match 4"
    wake_on_lan           0x000000B8 32 rw 0x00000000  -  -  -  "Wake on LAN Register"
    ipg_stretch           0x000000BC 32 rw 0x00000000  -  -  -  "IPG stretch register"
    stacked_vlan          0x000000C0 32 rw 0x00000000  -  -  -  "Stacked VLAN Register"
    tx_pfc_pause          0x000000C4 32 rw 0x00000000  -  -  -  "Transmit PFC Pause Register"
    spec_addr1_mask_bot   0x000000C8 32 rw 0x00000000  -  -  -  "Specific Address Mask 1 Bottom [31:0]"
    spec_addr1_mask_top   0x000000CC 32 rw 0x00000000  -  -  -  "Specific Address Mask 1 Top [47:32]"
    rx_ptp_uni            0x000000D4 32 rw 0x00000000  -  -  -  "PTP RX Unicast address (Not in TRM)"
    tx_ptp_uni            0x000000D8 32 rw 0x00000000  -  -  -  "PTP TX Unicast address (Not in TRM)"
    module_id             0x000000FC 32 r  0x00020118  -  -  -  "Module ID"
    octets_tx_bot         0x00000100 32 r  0x00000000  -  -  -  "Octets transmitted [31:0] (in frames without error)"
    octets_tx_top         0x00000104 32 r  0x00000000  -  -  -  "Octets transmitted [47:32] (in frames without error)"
    frames_tx             0x00000108 32 r  0x00000000  -  -  -  "Frames Transmitted"
    broadcast_frames_tx   0x0000010C 32 r  0x00000000  -  -  -  "Broadcast frames Tx"
    multi_frames_tx       0x00000110 32 r  0x00000000  -  -  -  "Multicast frames Tx"
    pause_frames_tx       0x00000114 32 r  0x00000000  -  -  -  "Pause frames Tx"
    frames_64b_tx         0x00000118 32 r  0x00000000  -  -  -  "Frames Tx, 64-byte length"
    frames_65to127b_tx    0x0000011C 32 r  0x00000000  -  -  -  "Frames Tx, 65 to 127-byte length"
    frames_128to255b_tx   0x00000120 32 r  0x00000000  -  -  -  "Frames Tx, 128 to 255-byte length"
    frames_256to511b_tx   0x00000124 32 r  0x00000000  -  -  -  "Frames Tx, 256 to 511-byte length"
    frames_512to1023b_tx  0x00000128 32 r  0x00000000  -  -  -  "Frames Tx, 512 to 1023-byte length"
    frames_1024to1518b_tx 0x0000012C 32 r  0x00000000  -  -  -  "Frame Tx, 1024 to 1518-byte length"
    frames_1519bplus_tx   0x00000130 32 r  0x00000000  -  -  -  "Frame Tx, 1519+byte length (Not in TRM)"
    tx_under_runs         0x00000134 32 r  0x00000000  -  -  -  "Transmit under runs"
    single_collisn_frames 0x00000138 32 r  0x00000000  -  -  -  "Single Collision Frames"
    multi_collisn_frames  0x0000013C 32 r  0x00000000  -  -  -  "Multiple Collision Frames"
    excessive_collisns    0x00000140 32 r  0x00000000  -  -  -  "Excessive Collisions"
    late_collisns         0x00000144 32 r  0x00000000  -  -  -  "Late Collisions"
    deferred_tx_frames    0x00000148 32 r  0x00000000  -  -  -  "Deferred Transmission Frames"
    carrier_sense_errs    0x0000014C 32 r  0x00000000  -  -  -  "Carrier Sense Errors."
    octets_rx_bot         0x00000150 32 r  0x00000000  -  -  -  "Octets Received [31:0]"
    octets_rx_top         0x00000154 32 r  0x00000000  -  -  -  "Octets Received [47:32]"
    frames_rx             0x00000158 32 r  0x00000000  -  -  -  "Frames Received"
    bdcast_frames_rx      0x0000015C 32 r  0x00000000  -  -  -  "Broadcast Frames Rx"
    multi_frames_rx       0x00000160 32 r  0x00000000  -  -  -  "Multicast Frames Rx"
    pause_rx              0x00000164 32 r  0x00000000  -  -  -  "Pause Frames Rx"
    frames_64b_rx         0x00000168 32 r  0x00000000  -  -  -  "Frames Rx, 64-byte length"
    frames_65to127b_rx    0x0000016C 32 r  0x00000000  -  -  -  "Frames Rx, 65 to 127-byte length"
    frames_128to255b_rx   0x00000170 32 r  0x00000000  -  -  -  "Frames Rx, 128 to 255-byte length"
    frames_256to511b_rx   0x00000174 32 r  0x00000000  -  -  -  "Frames Rx, 256 to 511-byte length"
    frames_512to1023b_rx  0x00000178 32 r  0x00000000  -  -  -  "Frames Rx, 512 to 1023-byte length"
    frames_1024to1518b_rx 0x0000017C 32 r  0x00000000  -  -  -  "Frames Rx, 1024 to 1518-byte length"
    frames_1519bplus_rx   0x00000180 32 r  0x00000000  -  -  -  "Frames Rx, 1519+byte length (Not in TRM)"
    undersz_rx            0x00000184 32 r  0x00000000  -  -  -  "Undersize frames received"
    oversz_rx             0x00000188 32 r  0x00000000  -  -  -  "Oversize frames received"
    jab_rx                0x0000018C 32 r  0x00000000  -  -  -  "Jabbers received"
    fcs_errors            0x00000190 32 r  0x00000000  -  -  -  "Frame check sequence errors"
    length_field_errors   0x00000194 32 r  0x00000000  -  -  -  "Length field frame errors"
    rx_symbol_errors      0x00000198 32 r  0x00000000  -  -  -  "Receive symbol errors"
    align_errors          0x0000019C 32 r  0x00000000  -  -  -  "Alignment errors"
    rx_resource_errors    0x000001A0 32 r  0x00000000  -  -  -  "Receive resource errors"
    rx_overrun_errors     0x000001A4 32 r  0x00000000  -  -  -  "Receive overrun errors"
    ip_hdr_csum_errors    0x000001A8 32 r  0x00000000  -  -  -  "IP header checksum errors"
    tcp_csum_errors       0x000001AC 32 r  0x00000000  -  -  -  "TCP checksum errors"
    udp_csum_errors       0x000001B0 32 r  0x00000000  -  -  -  "UDP checksum error"
    timer_strobe_s        0x000001C8 32 rw 0x00000000  -  -  -  "1588 timer sync strobe seconds"
    timer_strobe_ns       0x000001CC 32 rw 0x00000000  -  -  -  "1588 timer sync strobe nanoseconds"
    timer_s               0x000001D0 32 rw 0x00000000  -  -  -  "1588 timer seconds"
    timer_ns              0x000001D4 32 rw 0x00000000  -  -  -  "1588 timer nanoseconds"
    timer_adjust          0x000001D8 32 rw 0x00000000  -  -  -  "1588 timer adjust"
    timer_incr            0x000001DC 32 rw 0x00000000  -  -  -  "1588 timer increment"
    ptp_tx_s              0x000001E0 32 r  0x00000000  -  -  -  "PTP event frame transmitted seconds"
    ptp_tx_ns             0x000001E4 32 r  0x00000000  -  -  -  "PTP event frame transmitted nanoseconds"
    ptp_rx_s              0x000001E8 32 r  0x00000000  -  -  -  "PTP event frame received seconds"
    ptp_rx_ns             0x000001EC 32 r  0x00000000  -  -  -  "PTP event frame received nanoseconds."
    ptp_peer_tx_s         0x000001F0 32 r  0x00000000  -  -  -  "PTP peer event frame transmitted seconds"
    ptp_peer_tx_ns        0x000001F4 32 r  0x00000000  -  -  -  "PTP peer event frame transmitted nanoseconds"
    ptp_peer_rx_s         0x000001F8 32 r  0x00000000  -  -  -  "PTP peer event frame received seconds"
    ptp_peer_rx_ns        0x000001FC 32 r  0x00000000  -  -  -  "PTP peer event frame received nanoseconds."
    design_cfg1           0x00000280 32 r  0x00000000  -  -  -  "Design Configuration 1 (Not in TRM)"
    design_cfg2           0x00000284 32 r  0x2A813FFF  -  -  -  "Design Configuration 2"
    design_cfg3           0x00000288 32 r  0x00000000  -  -  -  "Design Configuration 3"
    design_cfg4           0x0000028C 32 r  0x00000000  -  -  -  "Design Configuration 4"
    design_cfg5           0x00000290 32 r  0x00572045  -  -  -  "Design Configuration 5"
    design_cfg6           0x00000294 32 r  0x00000000  -  -  -  "Design Configuration 6 (Not in TRM)"
    tx_bd_cntrl           0x000004cc 32 rw 0x00000000  -  -  -  "TX descriptor control (Not in TRM)"
    rx_bd_cntrl           0x000004d0 32 rw 0x00000000  -  -  -  "RX descriptor control (Not in TRM)"



}

foreach {rname roffset rsize raccess reset readFunc writeFunc bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {$rsize != "32"} {
      set rsize 32
  }

#DEBUG    puts "Generate: rname $rname roffset $roffset rsize $rsize raccess $raccess reset $reset readFunc $readFunc writeFunc $writeFunc bits $bits description $description"

  set command "imodeladdmmregister -addressblock ${port}/${block} -name $rname -width 32 -offset $roffset -access $raccess"
  if { $readFunc == "-" } {
    set defaultcb 1
  } elseif { $readFunc == "auto" } {
    set command "${command} -readfunction Read${rname}"
  } else {
    set command "${command} -readfunction $readFunc"
  }

  if { $writeFunc == "-" } {
    set defaultcb 1
  } elseif { $writeFunc == "auto" } {
    set command "${command} -writefunction Write${rname}"
  } else {
    set command "${command} -writefunction $writeFunc"
  }

  eval $command
  
  if { $description != "-" } {
      iadddocumentation  -handle ${port}/${block}/$rname \
                         -name Description  \
                         -text $description
  }

  if { $bits != "-" } {
    foreach { n o w } $bits {
        imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
    }
  }

  imodeladdreset -mmregister ${port}/${block}/$rname -name resetNet -value $reset
}


imodeladdbusslaveport  -name phyport -size 0x100
imodeladdaddressblock  -name ab -port phyport -size 0x100 -offset 0 -width 16


    # PHY Regs, not directly accessible on the bus
set phy_registers {
    MII_BMCR            0x00 16 rw 0x0000 - - -    "Basic mode control register"
    MII_BMSR            0x01 16 r  0xFF2C - - -    "Basic mode status register"
    MII_PHYSID1         0x02 16 r  0x2000 - - -    "PHYS ID 1"
    MII_PHYSID2         0x03 16 r  0xa201 - - -    "PHYS ID 2"
    MII_ADVERTISE       0x04 16 rw 0x01E1 - - -    "Advertisement control reg"
    MII_LPA             0x05 16 r  0x0FFF - - -    "Link partner ability reg"
    MII_EXPANSION       0x06 16 r  0x0000 - - -    "Expansion register"
    MII_DUMMY1          0x07 16 rw 0x0000 - - -    "Dummy"
    MII_DUMMY2          0x08 16 rw 0x0000 - - -    "Dummy"
    MII_CTRL1000        0x09 16 rw 0x0000 - - -    "1000BASE-T control"
    MII_STAT1000        0x0a 16 r  0x3C00 - - -    "1000BASE-T status"
    MII_DUMMY3          0x0b 16 rw 0x0000 - - -    "Dummy"
    MII_DUMMY4          0x0c 16 rw 0x0000 - - -    "Dummy"
    MII_MMD_CTRL        0x0d 16 rw 0x0000 - - -    "MMD Access Control Register"
    MII_MMD_DATA        0x0e 16 rw 0x0000 - - -    "MMD Access Data Register"
    MII_ESTATUS         0x0f 16 r  0x0000 - - -    "Extended Status"
    MII_DUMMY5          0x10 16 rw 0x0000 - - -    "Dummy"
    MII_STS             0x11 16 r  0x8000 - - -    "Status"
    MII_DCOUNTER        0x12 16 r  0x0000 - - -    "Disconnect counter"
    MII_FCSCOUNTER      0x13 16 r  0x0000 - - -    "False carrier counter"
    MII_NWAYTEST        0x14 16 r  0x0000 - - -    "N-way auto-neg test reg"
    MII_RERRCOUNTER     0x15 16 r  0x0000 - - -    "Receive error counter"
    MII_SREVISION       0x16 16 r  0x0000 - - -    "Silicon revision"
    MII_LBRERROR        0x18 16 r  0x0000 - - -    "Lpback, rx, bypass error"
    MII_PHYADDR         0x19 16 r  0x0000 - - -    "PHY address"
    MII_TPISTATUS       0x1b 16 r  0x0000 - - -    "TPI status for 10mbps"
    MII_NCONFIG         0x1c 16 rw 0x0000 - - -    "Network interface config"
}

foreach {rname roffset rsize raccess reset readFunc writeFunc bits description} $phy_registers {
    set o [expr "$roffset*2"]
    set command "imodeladdmmregister -addressblock phyport/ab -name $rname -width 16 -offset $o -access $raccess"

    eval $command
  
    if { $description != "-" } {
        iadddocumentation  -handle phyport/ab/$rname \
                           -name Description  \
                           -text $description
    }

    imodeladdreset -mmregister phyport/ab/$rname -name resetNet -value $reset

}

#
# Formal attributes
#
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
imodeladdformalmacro -name BHM_ETHERNET_OPEN_AUTO_FORMALS

imodeladdformal   -name pollDelay -type uns32
iadddocumentation -name Description -text "Read pollDelay"

imodeladdformal   -name outfile -type string
iadddocumentation -name Description -text "Wireshark capture file"

  imodeladdfield -access w -name flush_next_rx_dpram_ -bitoffset 18 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Flush the next packet from the external RX  DPRAM. Writing one to this bit will only have an effect if  the DMA is not currently writing a packet already  stored in the DPRAM to memory."

  imodeladdfield -access w -name tx_pfc_pri_pri_pause_f -bitoffset 17 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Transmit PFC Priority Based Pause Frame. Takes  the values stored in the Transmit PFC Pause  Register"

  imodeladdfield -access w -name en_pfc_pri_pause_rx -bitoffset 16 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Enable PFC Priority Based Pause Reception  capabilities. Setting this bit will enable PFC negotiation and  recognition of priority based pause frames."

  imodeladdfield -access rw -name str_rx_timestamp -bitoffset 15 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Store receive time stamp to memory. Setting this  bit to one will cause the CRC of every received  frame to be replaced with the value of the  nanoseconds field of the 1588 timer that was  captured as the receive frame passed the message  time stamp point. Set to zero for normal  operation."

  imodeladdfield -access w -name tx_zeroq_pause_frame -bitoffset 12 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Transmit zero quantum pause frame. Writing one  to this bit causes a pause frame with zero  quantum to be transmitted."

  imodeladdfield -access w -name tx_pause_frame -bitoffset 11 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Transmit pause frame - writing one to this bit  causes a pause frame to be transmitted."

  imodeladdfield -access w -name tx_halt -bitoffset 10 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Transmit halt - writing one to this bit halts  transmission as soon as any ongoing frame  transmission ends."

  imodeladdfield -access w -name start_tx -bitoffset 9 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Start transmission - writing one to this bit starts  transmission."

  imodeladdfield -access rw -name back_pressure -bitoffset 8 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Back pressure - if set in 10M or 100M half duplex  mode will force collisions on all received frames."

  imodeladdfield -access rw -name wren_stat_regs -bitoffset 7 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Write enable for statistics registers - setting this bit  to one means the statistics registers can be written  for functional test purposes."

  imodeladdfield -access w -name incr_stat_regs -bitoffset 6 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Incremental statistics registers - this bit is write  only. Writing a one increments all the statistics registers  by one for test purposes."

  imodeladdfield -access w -name clear_stat_regs -bitoffset 5 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Clear statistics registers - this bit is write only. Writing a one clears the statistics registers."

  imodeladdfield -access rw -name mgmt_port_en -bitoffset 4 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Management port enable - set to one to enable the  management port. When zero forces mdio to high  impedance state and mdc low."

  imodeladdfield -access rw -name tx_en -bitoffset 3 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Transmit enable - when set, it enables the GEM  transmitter to send data. When reset transmission  will stop immediately, the transmit pipeline and  control registers will be cleared and the transmit  queue pointer register will reset to point to the  start of the transmit descriptor list."

  imodeladdfield -access rw -name rx_en -bitoffset 2 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Receive enable - when set, it enables the GEM to  receive data. When reset frame reception will stop  immediately and the receive pipeline will be  cleared. The receive queue pointer register is unaffected."

  imodeladdfield -access rw -name loopback_local -bitoffset 1 -width 1 -mmregister bport1/ab/net_ctrl
  iadddocumentation -name Description -text "Loop back local - asserts the loopback_local signal  to the system clock generator. Also connects txd to  rxd, tx_en to rx_dv and forces full duplex mode.  Bit 11 of the network configuration register must  be set low to disable TBI mode when in internal  loopback. rx_clk and tx_clk may malfunction as  the GEM is switched into and out of internal loop  back. It is important that receive and transmit  circuits have already been disabled when making  the switch into and out of internal loop back.  Local loopback functionality isn't available in the  EP107 Zynq Emulation Platform, because the  clocking doesn't map well into an FPGA."

  imodeladdfield -access rw -name unidir_en -bitoffset 31 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "NA."

  imodeladdfield -access rw -name ignore_ipg_rx_er -bitoffset 30 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Ignore IPG rx_er. When set rx_er has no effect on  the GEM's operation when rx_dv is low. Set this  when using the RGMII wrapper in half-duplex  mode."

  imodeladdfield -access rw -name rx_bad_preamble -bitoffset 29 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Receive bad preamble. When set frames with  non-standard preamble are not rejected."

  imodeladdfield -access rw -name ipg_stretch_en -bitoffset 28 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "IPG stretch enable - when set the transmit IPG can  be increased above 96 bit times depending on the  previous frame length using the IPG stretch  register."

  imodeladdfield -access rw -name sgmii_en -bitoffset 27 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "SGMII mode enable - changes behavior of the  auto-negotiation advertisement and link partner  ability registers to meet the requirements of  SGMII and reduces the duration of the link timer  from 10 ms to 1.6 ms"

  imodeladdfield -access rw -name ignore_rx_fcs -bitoffset 26 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Ignore RX FCS - when set frames with FCS/CRC  errors will not be rejected. FCS error statistics will  still be collected for frames with bad FCS and FCS  status will be recorded in frame's DMA  descriptor. For normal operation this bit must be set to zero."

  imodeladdfield -access rw -name rx_hd_while_tx -bitoffset 25 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Enable frames to be received in half-duplex mode  while transmitting."

  imodeladdfield -access rw -name rx_chksum_offld_en -bitoffset 24 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Receive checksum offload enable - when set, the  receive checksum engine is enabled. Frames with  bad IP, TCP or UDP checksums are discarded."

  imodeladdfield -access rw -name dis_cp_pause_frame -bitoffset 23 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Disable copy of pause frames - set to one to prevent valid pause frames being copied to memory. When set, pause frames are not copied to memory regardless of the state of the copy all frames bit; whether a hash match is found or whether a type ID match is identified. If a destination address match is found the pause frame will be copied to memory.  Note that valid pause frames received will still increment pause statistics and pause the transmission of frames as required."

  imodeladdfield -access rw -name dbus_width -bitoffset 21 -width 2 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Data bus width. Only valid bus widths may be  written if the system is configured to a maximum  width less than 128-bits. Zynq defines  gem_dma_bus_width_def as 2'b00. 00: 32 bit AMBA AHB data bus width 01: 64 bit AMBA AHB data bus width 10: 128 bit AMBA AHB data bus width 11: 128 bit AMBA AHB data bus width"

  imodeladdfield -access rw -name mdc_clk_div -bitoffset 18 -width 3 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "MDC clock division - set according to cpu_1xclk  speed. These three bits determine the number cpu_1xclk  will be divided by to generate MDC. For  conformance with the 802.3 specification, MDC  must not exceed 2.5 MHz (MDC is only active  during MDIO read and write operations). 000: divide cpu_1xclk by 8 (cpu_1xclk up to 20  MHz) 001: divide cpu_1xclk by 16 (cpu_1xclk up to 40  MHz) 010: divide cpu_1xclk by 32 (cpu_1xclk up to 80  MHz) 011: divide cpu_1xclk by 48 (cpu_1xclk up to  120MHz) 100: divide cpu_1xclk by 64 (cpu_1xclk up to 160  MHz) 101: divide cpu_1xclk by 96 (cpu_1xclk up to 240  MHz) 110: divide cpu_1xclk by 128 (cpu_1xclk up to 320  MHz) 111: divide cpu_1xclk by 224 (cpu_1xclk up to 540  MHz)"

  imodeladdfield -access rw -name fcs_remove -bitoffset 17 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "FCS remove - setting this bit will cause received  frames to be written to memory without their  frame check sequence (last 4 bytes). The frame  length indicated will be reduced by four bytes in  this mode."

  imodeladdfield -access rw -name len_err_frame_disc -bitoffset 16 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Length field error frame discard - setting this bit  causes frames with a measured length shorter  than the extracted length field (as indicated by  bytes 13 and 14 in a non-VLAN tagged frame) to  be discarded. This only applies to frames with a  length field less than 0x0600."

  imodeladdfield -access rw -name rx_buf_offset -bitoffset 14 -width 2 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Receive buffer offset - indicates the number of  bytes by which the received data is offset from the  start of the receive buffer."

  imodeladdfield -access rw -name pause_en -bitoffset 13 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Pause enable - when set, transmission will pause  if a non zero 802.3 classic pause frame is received  and PFC has not been negotiated."

  imodeladdfield -access rw -name retry_test -bitoffset 12 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Retry test - must be set to zero for normal  operation. If set to one the backoff between collisions will  always be one slot time. Setting this bit to one  helps test the too many retries condition. Also  used in the pause frame tests to reduce the pause  counter's decrement time from 512 bit times, to  every rx_clk cycle."

  imodeladdfield -access rw -name pcs_sel -bitoffset 11 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "NA 0: GMII/MII interface enabled, TBI disabled 1: TBI enabled, GMII/MII disabled"

  imodeladdfield -access rw -name gige_en -bitoffset 10 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Gigabit mode enable - setting this bit configures  the GEM for 1000 Mbps operation. 0: 10/100 operation using MII or TBI interface 1: Gigabit operation using GMII or TBI interface"

  imodeladdfield -access rw -name ext_addr_match_en -bitoffset 9 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "External address match enable - when set the  external address match interface can be used to  copy frames to memory."

  imodeladdfield -access rw -name rx_1536_byte_frames -bitoffset 8 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Receive 1536 byte frames - setting this bit means  the GEM will accept frames up to 1536 bytes in  length. Normally the GEM would reject any  frame above 1518 bytes."

  imodeladdfield -access rw -name uni_hash_en -bitoffset 7 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Unicast hash enable - when set, unicast frames  will be accepted when the 6 bit hash function of  the destination address points to a bit that is set in  the hash register."

  imodeladdfield -access rw -name multi_hash_en -bitoffset 6 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Multicast hash enable - when set, multicast  frames will be accepted when the 6 bit hash  function of the destination address points to a bit  that is set in the hash register."

  imodeladdfield -access rw -name no_broadcast -bitoffset 5 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "No broadcast - when set to logic one, frames  addressed to the broadcast address of all ones will  not be accepted."

  imodeladdfield -access rw -name copy_all -bitoffset 4 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Copy all frames - when set to logic one, all valid  frames will be accepted."

  imodeladdfield -access rw -name disc_non_vlan -bitoffset 2 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Discard non-VLAN frames - when set only VLAN tagged frames will be passed to the address matching logic."

  imodeladdfield -access rw -name full_duplex -bitoffset 1 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Full duplex - if set to logic one, the transmit block  ignores the state of collision and carrier sense and  allows receive while transmitting. Also controls  the half-duplex pin."

  imodeladdfield -access rw -name speed -bitoffset 0 -width 1 -mmregister bport1/ab/net_cfg
  iadddocumentation -name Description -text "Speed - set to logic one to indicate 100Mbps  operation, logic zero for 10Mbps. The value of this  pin is reflected on the speed_mode\[0\] output pin."

  imodeladdfield -access r -name pfc_pri_pause_neg -bitoffset 6 -width 1 -mmregister bport1/ab/net_status
  iadddocumentation -name Description -text "Set when PFC Priority Based Pause has been  negotiated."

  imodeladdfield -access r -name pcs_autoneg_pause_tx -bitoffset 5 -width 1 -mmregister bport1/ab/net_status
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access r -name pcs_autoneg_pause_rx -bitoffset 4 -width 1 -mmregister bport1/ab/net_status
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access r -name pcs_autoneg_dup_res -bitoffset 3 -width 1 -mmregister bport1/ab/net_status
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access r -name phy_mgmt_idle -bitoffset 2 -width 1 -mmregister bport1/ab/net_status
  iadddocumentation -name Description -text "The PHY management logic is idle (i.e. has  completed)."

  imodeladdfield -access r -name mdio_in_pin_status -bitoffset 1 -width 1 -mmregister bport1/ab/net_status
  iadddocumentation -name Description -text "Returns status of the mdio_in pin"

  imodeladdfield -access r -name pcs_link_state -bitoffset 0 -width 1 -mmregister bport1/ab/net_status
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access rw -name disc_when_no_ahb -bitoffset 24 -width 1 -mmregister bport1/ab/dma_cfg
  iadddocumentation -name Description -text "When set, the GEM DMA will automatically  discard receive packets from the receiver packet  buffer memory when no AHB resource is  available. When low, then received packets will remain to be  stored in the SRAM based packet buffer until  AHB buffer resource next becomes available."

  imodeladdfield -access rw -name ahb_mem_rx_buf_size -bitoffset 16 -width 8 -mmregister bport1/ab/dma_cfg
  iadddocumentation -name Description -text "DMA receive buffer size in AHB system memory. The value defined by these bits determines the  size of buffer to use in main AHB system memory  when writing received data. The value is defined in multiples of 64 bytes such  that a value of 0x01 corresponds to buffers of 64  bytes, 0x02 corresponds to 128 bytes etc. For example: 0x02: 128 byte 0x18: 1536 byte (1*max length frame/buffer) 0xA0: 10240 byte (1*10k jumbo frame/buffer) Note that this value should never be written as  zero."

  imodeladdfield -access rw -name csum_gen_offload_en -bitoffset 11 -width 1 -mmregister bport1/ab/dma_cfg
  iadddocumentation -name Description -text "Transmitter IP, TCP and UDP checksum  generation offload enable. When set, the  transmitter checksum generation engine is  enabled, to calculate and substitute checksums for  transmit frames. When clear, frame data is  unaffected. If the GEM is not configured to use the DMA  packet buffer, this bit is not implemented and will  be treated as reserved, read as zero, ignored on  write. Zynq uses packet buffer."

  imodeladdfield -access rw -name tx_pktbuf_memsz_sel -bitoffset 10 -width 1 -mmregister bport1/ab/dma_cfg
  iadddocumentation -name Description -text "Transmitter packet buffer memory size select -  Having this bit at zero halves the amount of  memory used for the transmit packet buffer. This  reduces the amount of memory used by the GEM.  It is important to set this bit to one if the full  configured physical memory is available. The  value in brackets below represents the size that  would result for the default maximum configured  memory size of 4 kB. 1: Use full configured addressable space (4 kB) 0: Do not use top address bit (2 kB) If the GEM is not configured to use the DMA  packet buffer, this bit is not implemented and will  be treated as reserved, read as zero, ignored on  write. Zynq uses packet buffer."

  imodeladdfield -access rw -name rx_pktbuf_memsz_sel -bitoffset 8 -width 2 -mmregister bport1/ab/dma_cfg
  iadddocumentation -name Description -text "Receiver packet buffer memory size select -  Having these bits at less than 11 reduces the  amount of memory used for the receive packet  buffer. This reduces the amount of memory used  by the GEM. It is important to set these bits both  to one if the full configured physical memory is  available. The value in brackets below represents  the size that would result for the default  maximum configured memory size of 8 kBs. 00: Do not use top three address bits (1 kB) 01: Do not use top two address bits (2 kB) 10: Do not use top address bit (4 kB) 11: Use full configured addressable space (8 kB) If the controller is not configured to use the DMA  packet buffer, these bits are not implemented and  will be treated as reserved, read as zero, ignored  on write. Zynq uses packet buffer."

  imodeladdfield -access rw -name ahb_endian_swp_pkt_ -bitoffset 7 -width 1 -mmregister bport1/ab/dma_cfg
  iadddocumentation -name Description -text "AHB endian swap mode enable for packet data  accesses - When set, selects swapped endianism  for AHB transfers. When clear, selects little endian  mode."

  imodeladdfield -access rw -name ahb_endian_swp_mgm -bitoffset 6 -width 1 -mmregister bport1/ab/dma_cfg
  iadddocumentation -name Description -text "AHB endian swap mode enable for management  descriptor accesses - When set, selects swapped  endianism for AHB transfers. When clear, selects  little endian mode."

  imodeladdfield -access rw -name ahb_fixed_burst_len -bitoffset 0 -width 5 -mmregister bport1/ab/dma_cfg
  iadddocumentation -name Description -text "AHB fixed burst length for DMA data operations  - Selects the burst length to attempt to use on the  AHB when transferring frame data. Not used for  DMA management operations and only used  where space and data size allow. Otherwise  SINGLE type AHB transfers are used. Upper bits become non-writeable if the  configured DMA TX and RX FIFO sizes are  smaller than required to support the selected  burst size. One-hot priority encoding enforced automatically  on register writes as follows, where 'x' represents  don't care: 00001: Always use SINGLE AHB bursts 0001x: Always use SINGLE AHB bursts 001xx: Attempt to use INCR4 AHB bursts  (default) 01xxx: Attempt to use INCR8 AHB bursts 1xxxx: Attempt to use INCR16 AHB bursts others: reserved"

  imodeladdfield -access rw -name hresp_not_ok -bitoffset 8 -width 1 -mmregister bport1/ab/tx_status
  iadddocumentation -name Description -text "Hresp not OK - set when the DMA block sees  hresp not OK. Cleared by writing a one to this bit."

  imodeladdfield -access rw -name late_collision -bitoffset 7 -width 1 -mmregister bport1/ab/tx_status
  iadddocumentation -name Description -text "Late collision occurred - only set if the condition  occurs in gigabit mode, as retry is not attempted. Cleared by writing a one to this bit."

  imodeladdfield -access rw -name tx_under_run -bitoffset 6 -width 1 -mmregister bport1/ab/tx_status
  iadddocumentation -name Description -text "Transmit under run - this bit is set if the  transmitter was forced to terminate a frame that it  had already began transmitting due to further  data being unavailable. This bit is set if a transmitter status write back has  not completed when another status write back is  attempted. When using the DMA interface configured for  internal FIFO mode, this bit is also set when the  transmit DMA has written the SOP data into the  FIFO and either the AHB bus was not granted in  time for further data, or because an AHB not OK  response was returned, or because a used bit was  read. When using the DMA interface configured for  packet buffer mode, this bit will never be set. When using the external FIFO interface, this bit is  also set when the tx_r_underflow input is  asserted during a frame transfer. Cleared by  writing a 1."

  imodeladdfield -access rw -name tx_complete -bitoffset 5 -width 1 -mmregister bport1/ab/tx_status
  iadddocumentation -name Description -text "Transmit complete - set when a frame has been  transmitted. Cleared by writing a one to this bit."

  imodeladdfield -access rw -name tx_corr_ahb_err -bitoffset 4 -width 1 -mmregister bport1/ab/tx_status
  iadddocumentation -name Description -text "Transmit frame corruption due to AHB error - set  if an error occurs whilst midway through reading  transmit frame from the AHB, including HRESP  errors and buffers exhausted mid frame (if the  buffers run out during transmission of a frame  then transmission stops, FCS shall be bad and  tx_er asserted). Also set in DMA packet buffer mode if single  frame is too large for configured packet buffer  memory size. Cleared by writing a one to this bit."

  imodeladdfield -access r -name tx_go -bitoffset 3 -width 1 -mmregister bport1/ab/tx_status
  iadddocumentation -name Description -text "Transmit go - if high transmit is active. When using the exposed FIFO interface, this bit  represents bit 3 of the network control register. When using the DMA interface this bit represents  the tx_go variable as specified in the transmit  buffer description."

  imodeladdfield -access rw -name retry_limit_exceeded -bitoffset 2 -width 1 -mmregister bport1/ab/tx_status
  iadddocumentation -name Description -text "Retry limit exceeded - cleared by writing a one to  this bit."

  imodeladdfield -access rw -name collision -bitoffset 1 -width 1 -mmregister bport1/ab/tx_status
  iadddocumentation -name Description -text "Collision occurred - set by the assertion of  collision. Cleared by writing a one to this bit. When  operating in 10/100 mode, this status indicates  either a collision or a late collision. In gigabit  mode, this status is not set for a late collision."

  imodeladdfield -access rw -name used_bit_read -bitoffset 0 -width 1 -mmregister bport1/ab/tx_status
  iadddocumentation -name Description -text "Used bit read - set when a transmit buffer  descriptor is read with its used bit set. Cleared by  writing a one to this bit."

  imodeladdfield -access rw -name rx_q_baseaddr -bitoffset 2 -width 30 -mmregister bport1/ab/rx_qbar
  iadddocumentation -name Description -text "Receive buffer queue base address - written with  the address of the start of the receive queue."

  imodeladdfield -access rw -name tx_q_base_addr -bitoffset 2 -width 30 -mmregister bport1/ab/tx_qbar
  iadddocumentation -name Description -text "Transmit buffer queue base address - written with  the address of the start of the transmit queue."

  imodeladdfield -access rw -name hresp_not_ok -bitoffset 3 -width 1 -mmregister bport1/ab/rx_status
  iadddocumentation -name Description -text "Hresp not OK - set when the DMA block sees  hresp not OK. Cleared by writing a one to this bit."

  imodeladdfield -access rw -name rx_overrun -bitoffset 2 -width 1 -mmregister bport1/ab/rx_status
  iadddocumentation -name Description -text "Receive overrun - this bit is set if either the  gem_dma RX FIFO or external RX FIFO were  unable to store the receive frame due to a FIFO  overflow, or if the receive status, reported by the  gem_rx module to the gem_dma was not taken at  end of frame. This bit is also set in DMA packet  buffer mode if the packet buffer overflows. For  DMA operation the buffer will be recovered if an  overrun occurs. This bit is cleared by writing a  one to it."

  imodeladdfield -access rw -name frame_recd -bitoffset 1 -width 1 -mmregister bport1/ab/rx_status
  iadddocumentation -name Description -text "Frame received - one or more frames have been  received and placed in memory. Cleared by  writing a one to this bit."

  imodeladdfield -access rw -name buffer_not_avail -bitoffset 0 -width 1 -mmregister bport1/ab/rx_status
  iadddocumentation -name Description -text "Buffer not available - an attempt was made to get  a new buffer and the pointer indicated that it was  owned by the processor. The DMA will reread the  pointer each time an end of frame is received until  a valid pointer is found. This bit is set following  each descriptor read attempt that fails, even if  consecutive pointers are unsuccessful and  software has in the mean time cleared the status  flag. Cleared by writing a one to this bit."

  imodeladdfield -access rw -name tsu_sec_incr -bitoffset 26 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "TSU seconds register increment - indicates the  register has incremented."

  imodeladdfield -access rw -name pdelay_resp_tx -bitoffset 25 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "PTP pdelay_resp frame transmitted - indicates a  PTP pdelay_resp frame has been transmitted."

  imodeladdfield -access rw -name pdelay_req_tx -bitoffset 24 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "PTP pdelay_req frame transmitted - indicates a  PTP pdelay_req frame has been transmitted."

  imodeladdfield -access rw -name pdelay_resp_rx -bitoffset 23 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "PTP pdelay_resp frame received - indicates a PTP  pdelay_resp frame has been received."

  imodeladdfield -access rw -name pdelay_req_rx -bitoffset 22 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "PTP pdelay_req frame received - indicates a PTP  pdelay_req frame has been received."

  imodeladdfield -access rw -name sync_tx -bitoffset 21 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "PTP sync frame transmitted - indicates a PTP sync  frame has been transmitted."

  imodeladdfield -access rw -name delay_req_tx -bitoffset 20 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "PTP delay_req frame transmitted - indicates a  PTP delay_req frame has been transmitted."

  imodeladdfield -access rw -name sync_rx -bitoffset 19 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "PTP sync frame received - indicates a PTP sync  frame has been received."

  imodeladdfield -access rw -name delay_req_rx -bitoffset 18 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "PTP delay_req frame received - indicates a PTP  delay_req frame has been received."

  imodeladdfield -access rw -name partner_pg_rx -bitoffset 17 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access rw -name autoneg_complete -bitoffset 16 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access rw -name ext_intr -bitoffset 15 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "External interrupt - set when a rising edge has  been detected on the ext_interrupt_in input pin."

  imodeladdfield -access rw -name pause_tx -bitoffset 14 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "Pause frame transmitted - indicates a pause frame  has been successfully transmitted after being  initiated from the network control register or from  the tx_pause control pin."

  imodeladdfield -access rw -name pause_zero -bitoffset 13 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "Pause time zero - set when either the pause time  register at address 0x38 decrements to zero, or  when a valid pause frame is received with a zero  pause quantum field."

  imodeladdfield -access rw -name pause_nonzeroq_rx -bitoffset 12 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "Pause frame with non-zero pause quantum  received - indicates a valid pause has been  received that has a non-zero pause quantum field."

  imodeladdfield -access rw -name hresp_not_ok -bitoffset 11 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "Hresp not OK - set when the DMA block sees  hresp not OK."

  imodeladdfield -access rw -name rx_overrun -bitoffset 10 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "Receive overrun - set when the receive overrun  status bit gets set."

  imodeladdfield -access rw -name link_chng -bitoffset 9 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access rw -name tx_complete -bitoffset 7 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "Transmit complete - set when a frame has been  transmitted."

  imodeladdfield -access r -name tx_corrupt_ahb_err -bitoffset 6 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "Transmit frame corruption due to AHB error - set  if an error occurs while midway through reading  transmit frame from the AHB, including HRESP  errors and buffers exhausted mid frame (if the  buffers run out during transmission of a frame  then transmission stops, FCS shall be bad and  tx_er asserted). Also set in DMA packet buffer mode if single  frame is too large for configured packet buffer  memory size. Cleared on a read."

  imodeladdfield -access rw -name retry_ex_late_collisn -bitoffset 5 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "Retry limit exceeded or late collision - transmit  error. Late collision will only cause this status bit to be  set in gigabit mode (as a retry is not attempted)."

  imodeladdfield -access rw -name tx_used_read -bitoffset 3 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "TX used bit read - set when a transmit buffer  descriptor is read with its used bit set."

  imodeladdfield -access rw -name rx_used_read -bitoffset 2 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "RX used bit read - set when a receive buffer  descriptor is read with its used bit set."

  imodeladdfield -access rw -name rx_complete -bitoffset 1 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "Receive complete - a frame has been stored in  memory."

  imodeladdfield -access rw -name mgmt_sent -bitoffset 0 -width 1 -mmregister bport1/ab/intr_status
  iadddocumentation -name Description -text "Management frame sent - the PHY maintenance  register has completed its operation."

  imodeladdfield -access w -name tsu_sec_incr -bitoffset 26 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable TSU seconds register increment interrupt"

  imodeladdfield -access w -name pdelay_resp_tx -bitoffset 25 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable PTP pdelay_resp frame transmitted  interrupt"

  imodeladdfield -access w -name pdelay_req_tx -bitoffset 24 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable PTP pdelay_req frame transmitted  interrupt"

  imodeladdfield -access w -name pdelay_resp_rx -bitoffset 23 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable PTP pdelay_resp frame received interrupt"

  imodeladdfield -access w -name pdelay_req_rx -bitoffset 22 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable PTP pdelay_req frame received interrupt"

  imodeladdfield -access w -name sync_tx -bitoffset 21 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable PTP sync frame transmitted interrupt"

  imodeladdfield -access w -name delay_req_tx -bitoffset 20 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable PTP delay_req frame transmitted  interrupt"

  imodeladdfield -access w -name sync_rx -bitoffset 19 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable PTP sync frame received interrupt"

  imodeladdfield -access w -name delay_req_rx -bitoffset 18 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable PTP delay_req frame received interrupt"

  imodeladdfield -access w -name partner_pg_rx -bitoffset 17 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access w -name autoneg_complete -bitoffset 16 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access w -name ext_intr -bitoffset 15 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable external interrupt"

  imodeladdfield -access w -name pause_tx -bitoffset 14 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable pause frame transmitted interrupt"

  imodeladdfield -access w -name pause_zero -bitoffset 13 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable pause time zero interrupt"

  imodeladdfield -access w -name pause_nonzeroq -bitoffset 12 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable pause frame with non-zero pause  quantum interrupt"

  imodeladdfield -access w -name hresp_not_ok -bitoffset 11 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable hresp not OK interrupt"

  imodeladdfield -access w -name rx_overrun -bitoffset 10 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable receive overrun interrupt"

  imodeladdfield -access w -name link_chng -bitoffset 9 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable link change interrupt"

  imodeladdfield -access w -name tx_complete -bitoffset 7 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable transmit complete interrupt"

  imodeladdfield -access w -name tx_corrupt_ahb_err -bitoffset 6 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable transmit frame corruption due to AHB  error interrupt"

  imodeladdfield -access w -name retry_ex_late_collisn -bitoffset 5 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable retry limit exceeded or late collision  interrupt"

  imodeladdfield -access w -name tx_underrun -bitoffset 4 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable transmit buffer under run interrupt"

  imodeladdfield -access w -name tx_used_read -bitoffset 3 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable transmit used bit read interrupt"

  imodeladdfield -access w -name rx_used_read -bitoffset 2 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable receive used bit read interrupt"

  imodeladdfield -access w -name rx_complete -bitoffset 1 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable receive complete interrupt"

  imodeladdfield -access w -name mgmt_done -bitoffset 0 -width 1 -mmregister bport1/ab/intr_en
  iadddocumentation -name Description -text "Enable management done interrupt"

  imodeladdfield -access w -name tsu_sec_incr -bitoffset 26 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable TSU seconds register increment interrupt"

  imodeladdfield -access w -name pdelay_resp_tx -bitoffset 25 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable PTP pdelay_resp frame transmitted  interrupt"

  imodeladdfield -access w -name pdelay_req_tx -bitoffset 24 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable PTP pdelay_req frame transmitted  interrupt"

  imodeladdfield -access w -name pdelay_resp_rx -bitoffset 23 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable PTP pdelay_resp frame received interrupt"

  imodeladdfield -access w -name pdelay_req_rx -bitoffset 22 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable PTP pdelay_req frame received interrupt"

  imodeladdfield -access w -name sync_tx -bitoffset 21 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable PTP sync frame transmitted interrupt"

  imodeladdfield -access w -name delay_req_tx -bitoffset 20 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable PTP delay_req frame transmitted  interrupt"

  imodeladdfield -access w -name sync_rx -bitoffset 19 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable PTP sync frame received interrupt"

  imodeladdfield -access w -name delay_req_rx -bitoffset 18 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable PTP delay_req frame received interrupt"

  imodeladdfield -access w -name partner_pg_rx -bitoffset 17 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access w -name autoneg_complete -bitoffset 16 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access w -name ext_intr -bitoffset 15 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable external interrupt"

  imodeladdfield -access w -name pause_tx -bitoffset 14 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable pause frame transmitted interrupt"

  imodeladdfield -access w -name pause_zero -bitoffset 13 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable pause time zero interrupt"

  imodeladdfield -access w -name pause_nonzeroq -bitoffset 12 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable pause frame with non-zero pause  quantum interrupt"

  imodeladdfield -access w -name hresp_not_ok -bitoffset 11 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable hresp not OK interrupt"

  imodeladdfield -access w -name rx_overrun -bitoffset 10 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable receive overrun interrupt"

  imodeladdfield -access w -name link_chng -bitoffset 9 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable link change interrupt"

  imodeladdfield -access w -name tx_complete -bitoffset 7 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable transmit complete interrupt"

  imodeladdfield -access w -name tx_corrupt_ahb_err -bitoffset 6 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable transmit frame corruption due to AHB  error interrupt"

  imodeladdfield -access w -name retry_ex_late_collisn -bitoffset 5 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable retry limit exceeded or late collision  interrupt"

  imodeladdfield -access w -name tx_underrun -bitoffset 4 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable transmit buffer under run interrupt"

  imodeladdfield -access w -name tx_used_read -bitoffset 3 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable transmit used bit read interrupt"

  imodeladdfield -access w -name rx_used_read -bitoffset 2 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable receive used bit read interrupt"

  imodeladdfield -access w -name rx_complete -bitoffset 1 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable receive complete interrupt"

  imodeladdfield -access w -name mgmt_done -bitoffset 0 -width 1 -mmregister bport1/ab/intr_dis
  iadddocumentation -name Description -text "Disable management done interrupt"

  imodeladdfield -access rw -name pdelay_resp_tx -bitoffset 25 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "PTP pdelay_resp frame transmitted mask."

  imodeladdfield -access rw -name pdelay_req_tx -bitoffset 24 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "PTP pdelay_req frame transmitted mask."

  imodeladdfield -access rw -name pdelay_resp_rx -bitoffset 23 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "PTP pdelay_resp frame received mask."

  imodeladdfield -access rw -name pdelay_req_rx -bitoffset 22 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "PTP pdelay_req frame received mask."

  imodeladdfield -access rw -name sync_tx -bitoffset 21 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "PTP sync frame transmitted mask."

  imodeladdfield -access rw -name delay_req_tx -bitoffset 20 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "PTP delay_req frame transmitted mask."

  imodeladdfield -access rw -name sync_rx -bitoffset 19 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "PTP sync frame received mask."

  imodeladdfield -access rw -name delay_req_rx -bitoffset 18 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "PTP delay_req frame received mask."

  imodeladdfield -access rw -name partner_pg_rx -bitoffset 17 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access rw -name autoneg_complete -bitoffset 16 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "NA"

  imodeladdfield -access rw -name ext_intr -bitoffset 15 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "External interrupt mask."

  imodeladdfield -access rw -name pause_tx -bitoffset 14 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Pause frame transmitted interrupt mask."

  imodeladdfield -access rw -name pause_zero -bitoffset 13 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Pause time zero interrupt mask."

  imodeladdfield -access rw -name pause_nonzeroq -bitoffset 12 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Pause frame with non-zero pause quantum  interrupt mask."

  imodeladdfield -access rw -name hresp_not_ok -bitoffset 11 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Hresp not OK interrupt mask."

  imodeladdfield -access rw -name rx_overrun -bitoffset 10 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Receive overrun interrupt mask."

  imodeladdfield -access rw -name link_chng -bitoffset 9 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Link change interrupt mask."

  imodeladdfield -access rw -name tx_complete -bitoffset 7 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Transmit complete interrupt mask."

  imodeladdfield -access rw -name tx_corrupt_ahb_err -bitoffset 6 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Transmit frame corruption due to AHB error  interrupt"

  imodeladdfield -access rw -name retry_ex_late_collisn -bitoffset 5 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Retry limit exceeded or late collision (gigabit  mode only)"

  imodeladdfield -access rw -name tx_underrun -bitoffset 4 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Transmit buffer under run interrupt mask."

  imodeladdfield -access rw -name tx_used_read -bitoffset 3 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Transmit used bit read interrupt mask."

  imodeladdfield -access rw -name rx_used_read -bitoffset 2 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Receive used bit read interrupt mask."

  imodeladdfield -access rw -name rx_complete -bitoffset 1 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Receive complete interrupt mask."

  imodeladdfield -access rw -name mgmt_done -bitoffset 0 -width 1 -mmregister bport1/ab/intr_mask
  iadddocumentation -name Description -text "Management done interrupt mask."

  imodeladdfield -access rw -name clause_22 -bitoffset 30 -width 1 -mmregister bport1/ab/phy_maint
  iadddocumentation -name Description -text "Must be written to 1 for Clause 22 operation. Check your PHY's spec to see if it is clause 22 or  clause 45 compliant."

  imodeladdfield -access rw -name operation -bitoffset 28 -width 2 -mmregister bport1/ab/phy_maint
  iadddocumentation -name Description -text "Operation. 10 is read. 01 is write."

  imodeladdfield -access rw -name phy_addr -bitoffset 23 -width 5 -mmregister bport1/ab/phy_maint
  iadddocumentation -name Description -text "PHY address."

  imodeladdfield -access rw -name reg_addr -bitoffset 18 -width 5 -mmregister bport1/ab/phy_maint
  iadddocumentation -name Description -text "Register address - specifies the register in the PHY  to access."

  imodeladdfield -access rw -name must_10 -bitoffset 16 -width 2 -mmregister bport1/ab/phy_maint
  iadddocumentation -name Description -text "Must be written to 10."

  imodeladdfield -access rw -name data -bitoffset 0 -width 16 -mmregister bport1/ab/phy_maint
  iadddocumentation -name Description -text "For a write operation this is written with the data  to be written to the PHY. After a read operation  this contains the data read from the PHY."

  imodeladdfield -access r -name rx_pauseq -bitoffset 0 -width 16 -mmregister bport1/ab/rx_pauseq
  iadddocumentation -name Description -text "Received pause quantum - stores the current  value of the received pause quantum register  which is decremented every 512 bit times."

  imodeladdfield -access rw -name tx_pauseq -bitoffset 0 -width 16 -mmregister bport1/ab/tx_pauseq
  iadddocumentation -name Description -text "Transmit pause quantum - written with the pause  quantum value for pause frame transmission."

  imodeladdfield -access rw -name addr_msbs -bitoffset 0 -width 16 -mmregister bport1/ab/spec_addr1_top
  iadddocumentation -name Description -text "Specific address 1. The most significant bits of the  destination address, that is bits 47:32."

  imodeladdfield -access rw -name addr_msbs -bitoffset 0 -width 16 -mmregister bport1/ab/spec_addr2_top
  iadddocumentation -name Description -text "Specific address 2. The most significant bits of the  destination address, that is bits 47:32."

  imodeladdfield -access rw -name addr_msbs -bitoffset 0 -width 16 -mmregister bport1/ab/spec_addr3_top
  iadddocumentation -name Description -text "Specific address 3. The most significant bits of the  destination address, that is bits 47:32."

  imodeladdfield -access rw -name addr_msbs -bitoffset 0 -width 16 -mmregister bport1/ab/spec_addr4_top
  iadddocumentation -name Description -text "Specific address 4. The most significant bits of the  destination address, that is bits 47:32."

  imodeladdfield -access rw -name copy_en -bitoffset 31 -width 1 -mmregister bport1/ab/type_id_match1
  iadddocumentation -name Description -text "Enable copying of type ID match 1 matched  frames"

  imodeladdfield -access rw -name type_id_match1 -bitoffset 0 -width 16 -mmregister bport1/ab/type_id_match1
  iadddocumentation -name Description -text "Type ID match 1. For use in comparisons with  received frames type ID/length field."

  imodeladdfield -access rw -name copy_en -bitoffset 31 -width 1 -mmregister bport1/ab/type_id_match2
  iadddocumentation -name Description -text "Enable copying of type ID match 2 matched  frames"

  imodeladdfield -access rw -name type_id_match2 -bitoffset 0 -width 16 -mmregister bport1/ab/type_id_match2
  iadddocumentation -name Description -text "Type ID match 2. For use in comparisons with  received frames type ID/length field."

  imodeladdfield -access rw -name copy_en -bitoffset 31 -width 1 -mmregister bport1/ab/type_id_match3
  iadddocumentation -name Description -text "Enable copying of type ID match 3 matched  frames"

  imodeladdfield -access rw -name type_id_match3 -bitoffset 0 -width 16 -mmregister bport1/ab/type_id_match3
  iadddocumentation -name Description -text "Type ID match 3. For use in comparisons with  received frames type ID/length field."

  imodeladdfield -access rw -name copy_en -bitoffset 31 -width 1 -mmregister bport1/ab/type_id_match4
  iadddocumentation -name Description -text "Enable copying of type ID match 4 matched  frames"

  imodeladdfield -access rw -name type_id_match4 -bitoffset 0 -width 16 -mmregister bport1/ab/type_id_match4
  iadddocumentation -name Description -text "Type ID match 4. For use in comparisons with  received frames type ID/length field."

  imodeladdfield -access rw -name multi_hash_en -bitoffset 19 -width 1 -mmregister bport1/ab/wake_on_lan
  iadddocumentation -name Description -text "Wake on LAN multicast hash event enable. When  set multicast hash events will cause the wol  output to be asserted."

  imodeladdfield -access rw -name spec_addr_reg1_en -bitoffset 18 -width 1 -mmregister bport1/ab/wake_on_lan
  iadddocumentation -name Description -text "Wake on LAN specific address register 1 event  enable. When set specific address 1 events will  cause the wol output to be asserted."

  imodeladdfield -access rw -name arp_req_en -bitoffset 17 -width 1 -mmregister bport1/ab/wake_on_lan
  iadddocumentation -name Description -text "Wake on LAN ARP request event enable. When  set ARP request events will cause the wol output  to be asserted."

  imodeladdfield -access rw -name magic_pkt_en -bitoffset 16 -width 1 -mmregister bport1/ab/wake_on_lan
  iadddocumentation -name Description -text "Wake on LAN magic packet event enable. When  set magic packet events will cause the wol output  to be asserted."

  imodeladdfield -access rw -name arp_req_ip_addr -bitoffset 0 -width 16 -mmregister bport1/ab/wake_on_lan
  iadddocumentation -name Description -text "Wake on LAN ARP request IP address. Written to  define the least significant 16 bits of the target IP  address that is matched to generate a Wake on  LAN event. A value of zero will not generate an  event, even if this is matched by the received  frame."

  imodeladdfield -access rw -name ipg_stretch -bitoffset 0 -width 16 -mmregister bport1/ab/ipg_stretch
  iadddocumentation -name Description -text "Bits 7:0 are multiplied with the previously  transmitted frame length (including preamble)  bits 15:8 +1 divide the frame length. If the  resulting number is greater than 96 and bit 28 is  set in the network configuration register then the  resulting number is used for the transmit  inter-packet-gap. 1 is added to bits 15:8 to prevent  a divide by zero."

  imodeladdfield -access rw -name stacked_vlan_en -bitoffset 31 -width 1 -mmregister bport1/ab/stacked_vlan
  iadddocumentation -name Description -text "Enable Stacked VLAN processing mode"

  imodeladdfield -access rw -name user_def_vlan_type -bitoffset 0 -width 16 -mmregister bport1/ab/stacked_vlan
  iadddocumentation -name Description -text "User defined VLAN_TYPE field. When Stacked  VLAN is enabled, the first VLAN tag in a received  frame will only be accepted if the VLAN type field  is equal to this user defined VLAN_TYPE OR  equal to the standard VLAN type (0x8100). Note  that the second VLAN tag of a Stacked VLAN  packet will only be matched correctly if its  VLAN_TYPE field equals 0x8100."

  imodeladdfield -access rw -name pauseq_sel -bitoffset 8 -width 8 -mmregister bport1/ab/tx_pfc_pause
  iadddocumentation -name Description -text "If bit 17 of the network control register is written  with a one then for each entry equal to zero in the  Transmit PFC Pause Register\[15:8\], the PFC pause  frame's pause quantum field associated with that  entry will be taken from the transmit pause  quantum register. For each entry equal to one in  the Transmit PFC Pause Register \[15:8\], the pause  quantum associated with that entry will be zero."

  imodeladdfield -access rw -name pri_en_vec_val -bitoffset 0 -width 8 -mmregister bport1/ab/tx_pfc_pause
  iadddocumentation -name Description -text ""

  imodeladdfield -access rw -name mask_bits_top -bitoffset 0 -width 32 -mmregister bport1/ab/spec_addr1_mask_bot
  iadddocumentation -name Description -text "Setting a bit to one masks the corresponding bit in  the specific address 1 register"

  imodeladdfield -access rw -name mask_bits_top -bitoffset 0 -width 16 -mmregister bport1/ab/spec_addr1_mask_top
  iadddocumentation -name Description -text "Setting a bit to one masks the corresponding bit in  the specific address 1 register"

  imodeladdfield -access r -name module_id -bitoffset 16 -width 16 -mmregister bport1/ab/module_id
  iadddocumentation -name Description -text "Module identification number - for the GEM, this  value is fixed at 0x0002."

  imodeladdfield -access r -name module_rev -bitoffset 0 -width 16 -mmregister bport1/ab/module_id
  iadddocumentation -name Description -text ""

  imodeladdfield -access r -name octets_tx_bot -bitoffset 0 -width 32 -mmregister bport1/ab/octets_tx_bot
  iadddocumentation -name Description -text "Transmitted octets in frame without errors \[31:0\]. The number of octets transmitted in valid frames  of any type. This counter is 48-bits, and is read  through two registers. This count does not  include octets from automatically generated  pause frames."

  imodeladdfield -access r -name octets_tx_top -bitoffset 0 -width 16 -mmregister bport1/ab/octets_tx_top
  iadddocumentation -name Description -text "Transmitted octets in frame without errors \[47:32\].  The number of octets transmitted in valid frames  of any type. This counter is 48-bits, and is read  through two registers. This count does not  include octets from automatically generated  pause frames."

  imodeladdfield -access r -name frames_tx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_tx
  iadddocumentation -name Description -text "Frames transmitted without error. A 32 bit register counting the number of frames successfully transmitted, i.e., no under run and not too many retries. Excludes pause frames."

  imodeladdfield -access r -name broadcasr_frames_tx -bitoffset 0 -width 32 -mmregister bport1/ab/broadcast_frames_tx
  iadddocumentation -name Description -text "Broadcast frames transmitted without error. A 32 bit register counting the number of broadcast frames successfully transmitted without error, i.e., no under run and not too many retries. Excludes pause frames."

  imodeladdfield -access r -name multi_frames_tx -bitoffset 0 -width 32 -mmregister bport1/ab/multi_frames_tx
  iadddocumentation -name Description -text "Multicast frames transmitted without error. A 32  bit register counting the number of multicast  frames successfully transmitted without error, i.e.,  no under run and not too many retries. Excludes  pause frames."

  imodeladdfield -access r -name pause_frames_tx -bitoffset 0 -width 16 -mmregister bport1/ab/pause_frames_tx
  iadddocumentation -name Description -text "Transmitted pause frames - a 16 bit register  counting the number of pause frames  transmitted. Only pause frames triggered by the  register interface or through the external pause  pins are counted as pause frames. Pause frames  received through the external FIFO interface are  counted in the frames transmitted counter."

  imodeladdfield -access r -name frames_64b_tx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_64b_tx
  iadddocumentation -name Description -text "64 byte frames transmitted without error. A 32 bit  register counting the number of 64 byte frames  successfully transmitted without error, i.e., no  under run and not too many retries. Excludes  pause frames."

  imodeladdfield -access r -name frames_65to127b_tx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_65to127b_tx
  iadddocumentation -name Description -text "65 to127 byte frames transmitted without error. A  32 bit register counting the number of 65 to127  byte frames successfully transmitted without  error, i.e., no under run and not too many retries."

  imodeladdfield -access r -name frames_128to255b_tx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_128to255b_tx
  iadddocumentation -name Description -text "128 to 255 byte frames transmitted without error.  A 32 bit register counting the number of 128 to 255  byte frames successfully transmitted without  error, i.e., no under run and not too many retries."

  imodeladdfield -access r -name frames_256to511b_tx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_256to511b_tx
  iadddocumentation -name Description -text "256 to 511 byte frames transmitted without error. A 32 bit register counting the number of 256 to 511 byte frames successfully transmitted without error, i.e., no under run and not too many retries. A 32 bit register counting the number of 128 to 255  byte frames successfully transmitted without  error, i.e., no under run and not too many retries."

  imodeladdfield -access r -name frames_512to1023b_tx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_512to1023b_tx
  iadddocumentation -name Description -text "512 to 1023 byte frames transmitted without error.  A 32 bit register counting the number of 512 to  1023 byte frames successfully transmitted  without error, i.e., no under run and not too many  retries."

  imodeladdfield -access r -name frames_1023to11518b_tx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_1024to1518b_tx
  iadddocumentation -name Description -text "1024 to 1518 byte frames transmitted without  error. A 32 bit register counting the number of  1024 to 1518 byte frames successfully transmitted  without error, i.e., no under run and not too many  retries."

  imodeladdfield -access r -name tx_under_runs -bitoffset 0 -width 10 -mmregister bport1/ab/tx_under_runs
  iadddocumentation -name Description -text "Transmit under runs - a 10 bit register counting  the number of frames not transmitted due to a  transmit under run. If this register is incremented  then no other statistics register is incremented."

  imodeladdfield -access r -name single_collisn -bitoffset 0 -width 18 -mmregister bport1/ab/single_collisn_frames
  iadddocumentation -name Description -text "Single collision frames - an 18 bit register counting  the number of frames experiencing a single  collision before being successfully transmitted,  i.e. no under run."

  imodeladdfield -access r -name multi_collisn -bitoffset 0 -width 18 -mmregister bport1/ab/multi_collisn_frames
  iadddocumentation -name Description -text "Multiple collision frames - an 18 bit register  counting the number of frames experiencing  between two and fifteen collisions prior to being  successfully transmitted, i.e., no under run and  not too many retries."

  imodeladdfield -access r -name excessive_collisns -bitoffset 0 -width 10 -mmregister bport1/ab/excessive_collisns
  iadddocumentation -name Description -text "Excessive collisions - a 10 bit register counting the number of frames that failed to be transmitted because they experienced 16 collisions."

  imodeladdfield -access r -name late_collisns -bitoffset 0 -width 10 -mmregister bport1/ab/late_collisns
  iadddocumentation -name Description -text "Late collisions - a 10 bit register counting the number of late collision occurring after the slot time (512 bits) has expired. In 10/100 mode, late collisions are counted twice i.e., both as a collision and a late collision. In gigabit mode, a late collision causes the transmission to be aborted, thus the single and multi collision registers are not updated."

  imodeladdfield -access r -name deferred_tx_frames -bitoffset 0 -width 10 -mmregister bport1/ab/deferred_tx_frames
  iadddocumentation -name Description -text "Deferred transmission frames - an 18 bit register counting the number of frames experiencing deferral due to carrier sense being active on their first attempt at transmission. Frames involved in any collision are not counted nor are frames that experienced a transmit under run."

  imodeladdfield -access r -name carrier_sense_errs -bitoffset 0 -width 10 -mmregister bport1/ab/carrier_sense_errs
  iadddocumentation -name Description -text "Carrier sense errors - a 10 bit register counting the  number of frames transmitted where carrier sense  was not seen during transmission or where carrier  sense was deasserted after being asserted in a  transmit frame without collision (no under run).  Only incremented in half duplex mode. The only  effect of a carrier sense error is to increment this  register. The behavior of the other statistics  registers is unaffected by the detection of a carrier  sense error."

  imodeladdfield -access r -name octets_rx_bot -bitoffset 0 -width 32 -mmregister bport1/ab/octets_rx_bot
  iadddocumentation -name Description -text "Received octets in frame without errors \[31:0\]. The  number of octets received in valid frames of any  type. This counter is 48-bits and is read through  two registers. This count does not include octets  from pause frames, and is only incremented if the  frame is successfully filtered and copied to  memory."

  imodeladdfield -access r -name octets_rx_top -bitoffset 0 -width 16 -mmregister bport1/ab/octets_rx_top
  iadddocumentation -name Description -text "Received octets in frame without errors \[47:32\].  The number of octets received in valid frames of  any type. This counter is 48-bits and is read  through two registers. This count does not  include octets from pause frames, and is only  incremented if the frame is successfully filtered  and copied to memory."

  imodeladdfield -access r -name frames_rx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_rx
  iadddocumentation -name Description -text "Frames received without error. A 32 bit register  counting the number of frames successfully  received. Excludes pause frames, and is only  incremented if the frame is successfully filtered  and copied to memory."

  imodeladdfield -access r -name bdcast_frames_rx -bitoffset 0 -width 32 -mmregister bport1/ab/bdcast_frames_rx
  iadddocumentation -name Description -text "Broadcast frames received without error. A 32 bit  register counting the number of broadcast frames  successfully received without error. Excludes  pause frames, and is only incremented if the  frame is successfully filtered and copied to  memory."

  imodeladdfield -access r -name multi_frames_rx -bitoffset 0 -width 32 -mmregister bport1/ab/multi_frames_rx
  iadddocumentation -name Description -text "Multicast frames received without error. A 32 bit  register counting the number of multicast frames  successfully received without error. Excludes  pause frames, and is only incremented if the  frame is successfully filtered and copied to  memory."

  imodeladdfield -access r -name pause_rx -bitoffset 0 -width 16 -mmregister bport1/ab/pause_rx
  iadddocumentation -name Description -text "Received pause frames - a 16 bit register counting the number of pause frames received without error."

  imodeladdfield -access r -name frames_64b_rx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_64b_rx
  iadddocumentation -name Description -text "64 byte frames received without error. A 32 bit register counting the number of 64 byte frames successfully received without error. Excludes pause frames, and is only incremented if the frame is successfully filtered and copied to memory."

  imodeladdfield -access r -name frames_65to127b_rx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_65to127b_rx
  iadddocumentation -name Description -text "65 to 127 byte frames received without error. A 32 bit register counting the number of 65 to 127 byte frames successfully received without error. Excludes pause frames, and is only incremented if the frame is successfully filtered and copied to memory."

  imodeladdfield -access r -name frames_128to255b_rx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_128to255b_rx
  iadddocumentation -name Description -text "128 to 255 byte frames received without error. A  32 bit register counting the number of 128 to 255  byte frames successfully received without error.  Excludes pause frames, and is only incremented if  the frame is successfully filtered and copied to  memory."

  imodeladdfield -access r -name frames_256to511b_rx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_256to511b_rx
  iadddocumentation -name Description -text "256 to 511 byte frames received without error. A 32 bit register counting the number of 256 to 511 byte frames successfully transmitted without error. Excludes pause frames, and is only incremented if the frame is successfully filtered and copied to memory."

  imodeladdfield -access r -name frames_512to1023b_rx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_512to1023b_rx
  iadddocumentation -name Description -text "512 to 1023 byte frames received without error. A  32 bit register counting the number of 512 to 1023  byte frames successfully received without error.  Excludes pause frames, and is only incremented if  the frame is successfully filtered and copied to  memory."

  imodeladdfield -access r -name frames_1023to11518b_rx -bitoffset 0 -width 32 -mmregister bport1/ab/frames_1024to1518b_rx
  iadddocumentation -name Description -text "1024 to 1518 byte frames received without error. A  32 bit register counting the number of 1024 to 1518  byte frames successfully received without error.  Excludes pause frames, and is only incremented if  the frame is successfully filtered and copied to  memory."

  imodeladdfield -access r -name undersz_rx -bitoffset 0 -width 10 -mmregister bport1/ab/undersz_rx
  iadddocumentation -name Description -text "Undersize frames received - a 10 bit register  counting the number of frames received less than  64 bytes in length (10/100 mode or gigabit mode,  full duplex) that do not have either a CRC error or  an alignment error."

  imodeladdfield -access r -name oversz_rx -bitoffset 0 -width 10 -mmregister bport1/ab/oversz_rx
  iadddocumentation -name Description -text "Oversize frames received - a 10 bit register counting the number of frames received exceeding 1518 bytes (1536 bytes if bit 8 is set in network configuration register) in length but do not have either a CRC error, an alignment error nor a receive symbol error."

  imodeladdfield -access r -name jab_rx -bitoffset 0 -width 10 -mmregister bport1/ab/jab_rx
  iadddocumentation -name Description -text "Jabbers received - a 10 bit register counting the number of frames received exceeding 1518 bytes (1536 if bit 8 set in network configuration register) in length and have either a CRC error, an alignment error or a receive symbol error."

  imodeladdfield -access r -name fcs_erros -bitoffset 0 -width 10 -mmregister bport1/ab/fcs_errors
  iadddocumentation -name Description -text "Frame check sequence errors - a 10 bit register counting frames that are an integral number of bytes, have bad CRC and are between 64 and 1518 bytes in length. This register is also incremented if a symbol error is detected and the frame is of valid length and has an integral number of bytes. This register is incremented for a frame with bad FCS, regardless of whether it is copied to memory due to ignore FCS mode being enabled in bit 26 of the network configuration register.H524"

  imodeladdfield -access r -name length_field_errors -bitoffset 0 -width 10 -mmregister bport1/ab/length_field_errors
  iadddocumentation -name Description -text "Length field frame errors - this 10-bit register  counts the number of frames received that have a  measured length shorter than that extracted from  the length field (bytes 13 and 14). This condition is  only counted if the value of the length field is less  than 0x0600, the frame is not of excessive length  and checking is enabled through bit 16 of the  network configuration register."

  imodeladdfield -access r -name rx_symbol_errors -bitoffset 0 -width 10 -mmregister bport1/ab/rx_symbol_errors
  iadddocumentation -name Description -text "Receive symbol errors - a 10-bit register counting  the number of frames that had rx_er asserted  during reception. For 10/100 mode symbol errors  are counted regardless of frame length checks. For  gigabit mode the frame must satisfy slot time  requirements in order to count a symbol error."

  imodeladdfield -access r -name align_errors -bitoffset 0 -width 10 -mmregister bport1/ab/align_errors
  iadddocumentation -name Description -text "Alignment errors - a 10 bit register counting  frames that are not an integral number of bytes  long and have bad CRC when their length is  truncated to an integral number of bytes and are  between 64 and 1518 bytes in length. This register  is also incremented if a symbol error is detected  and the frame is of valid length and does not have  an integral number of bytes."

  imodeladdfield -access r -name rx_resource_errors -bitoffset 0 -width 18 -mmregister bport1/ab/rx_resource_errors
  iadddocumentation -name Description -text "Receive resource errors - an 18 bit register  counting the number of frames that were  successfully received by the MAC (correct  address matched frame and adequate slot time)  but could not be copied to memory because no  receive buffer was available. This will be either  because the AHB bus was not granted in time or  because a hresp not OK was returned."

  imodeladdfield -access r -name rx_overrun_errors -bitoffset 0 -width 10 -mmregister bport1/ab/rx_overrun_errors
  iadddocumentation -name Description -text "Receive overruns - a 10 bit register counting the  number of frames that are address recognized but  were not copied to memory due to a receive  overrun."

  imodeladdfield -access r -name ip_hdr_csum_errors -bitoffset 0 -width 8 -mmregister bport1/ab/ip_hdr_csum_errors
  iadddocumentation -name Description -text "0 IP header checksum errors - an 8-bit register  counting the number of frames discarded due to  an incorrect IP header checksum, but are between  64 and 1518 bytes and do not have a CRC error, an  alignment error, nor a symbol error."

  imodeladdfield -access r -name tcp_csum_errors -bitoffset 0 -width 8 -mmregister bport1/ab/tcp_csum_errors
  iadddocumentation -name Description -text "TCP checksum errors - an 8-bit register counting the number of frames discarded due to an incorrect TCP checksum, but are between 64 and 1518 bytes and do not have a CRC error, an alignment error, nor a symbol error."

  imodeladdfield -access r -name udp_csum_errors -bitoffset 0 -width 8 -mmregister bport1/ab/udp_csum_errors
  iadddocumentation -name Description -text "UDP checksum errors - an 8-bit register counting the number of frames discarded due to an incorrect UDP checksum, but are between 64 and 1518 bytes and do not have a CRC error, an alignment error, nor a symbol error."

  imodeladdfield -access r -name timer_strobe_s -bitoffset 0 -width 32 -mmregister bport1/ab/timer_strobe_s
  iadddocumentation -name Description -text "The value of the Timer Seconds register"

  imodeladdfield -access rw -name ns_reg_val -bitoffset 0 -width 30 -mmregister bport1/ab/timer_strobe_ns
  iadddocumentation -name Description -text "The value of the Timer Nanoseconds register"

  imodeladdfield -access rw -name timer_s -bitoffset 0 -width 32 -mmregister bport1/ab/timer_s
  iadddocumentation -name Description -text "Timer count in seconds. This register is writeable. It increments by one when the 1588 nanoseconds counter counts to one second. It may also be incremented when the timer adjust register is written."

  imodeladdfield -access rw -name timer_ct_ns -bitoffset 0 -width 30 -mmregister bport1/ab/timer_ns
  iadddocumentation -name Description -text "Timer count in nanoseconds. This register is writeable. It can also be adjusted by writes to the 1588 timer adjust register. It increments by the value of the 1588 timer increment register each clock cycle."

  imodeladdfield -access w -name add_subn -bitoffset 31 -width 1 -mmregister bport1/ab/timer_adjust
  iadddocumentation -name Description -text "Write as one to subtract from the 1588 timer. Write  as zero to add to it."

  imodeladdfield -access w -name ns_delta -bitoffset 0 -width 30 -mmregister bport1/ab/timer_adjust
  iadddocumentation -name Description -text "The number of nanoseconds to increment or decrement the 1588 timer nanoseconds register. If necessary, the 1588 seconds register will be incremented or decremented."

  imodeladdfield -access rw -name incr_b4_alt -bitoffset 16 -width 8 -mmregister bport1/ab/timer_incr
  iadddocumentation -name Description -text "The number of increments after which the  alternative increment is used."

  imodeladdfield -access rw -name alt_ct_ns_delta -bitoffset 8 -width 8 -mmregister bport1/ab/timer_incr
  iadddocumentation -name Description -text "Alternative count of nanoseconds by which the  1588 timer nanoseconds register will be  incremented each clock cycle."

  imodeladdfield -access rw -name ns_delta -bitoffset 0 -width 8 -mmregister bport1/ab/timer_incr
  iadddocumentation -name Description -text "A count of nanoseconds by which the 1588 timer nanoseconds register will be incremented each clock cycle."

  imodeladdfield -access r -name ptp_tx_s -bitoffset 0 -width 32 -mmregister bport1/ab/ptp_tx_s
  iadddocumentation -name Description -text "The register is updated with the value that the  1588 timer seconds register held when the SFD of  a PTP transmit primary event crosses the MII  interface. The actual update occurs when the  GEM recognizes the frame as a PTP sync or  delay_req frame. An interrupt is issued when the  register is updated."

  imodeladdfield -access r -name ns_reg_val -bitoffset 0 -width 30 -mmregister bport1/ab/ptp_tx_ns
  iadddocumentation -name Description -text "The register is updated with the value that the 1588 timer nanoseconds register held when the SFD of a PTP transmit primary event crosses the MII interface. The actual update occurs when the GEM recognizes the frame as a PTP sync or delay_req frame. An interrupt is issued when the register is updated."

  imodeladdfield -access r -name ptp_rx_s -bitoffset 0 -width 32 -mmregister bport1/ab/ptp_rx_s
  iadddocumentation -name Description -text "The register is updated with the value that the 1588 timer seconds register held when the SFD of a PTP receive primary event crosses the MII interface. The actual update occurs when the GEM recognizes the frame as a PTP pdelay_req or pdelay_resp frame. An interrupt is issued when the register is updated."

  imodeladdfield -access r -name ns_reg_val -bitoffset 0 -width 30 -mmregister bport1/ab/ptp_rx_ns
  iadddocumentation -name Description -text "The register is updated with the value that the 1588 timer nanoseconds register held when the SFD of a PTP receive primary event crosses the MII interface. The actual update occurs when the GEM recognizes the frame as a PTP sync or delay_req frame. An interrupt is issued when the register is updated."

  imodeladdfield -access r -name ptp_peer_tx_s -bitoffset 0 -width 32 -mmregister bport1/ab/ptp_peer_tx_s
  iadddocumentation -name Description -text "The register is updated with the value that the 1588 timer seconds register held when the SFD of a PTP receive peer event crosses the MII interface. The actual update occurs when the GEM recognizes the frame as a PTP pdelay_req or pdelay_resp frame. An interrupt is issued when the register is updated."

  imodeladdfield -access r -name ns_reg_val -bitoffset 0 -width 30 -mmregister bport1/ab/ptp_peer_tx_ns
  iadddocumentation -name Description -text "The register is updated with the value that the  1588 timer nanoseconds register held when the  SFD of a PTP transmit peer event crosses the MII  interface. The actual update occurs when the  GEM recognizes the frame as a PTP pdelay_req or  pdelay_resp frame. An interrupt is issued when  the register is updated."

  imodeladdfield -access r -name ptp_peer_rx_s -bitoffset 0 -width 32 -mmregister bport1/ab/ptp_peer_rx_s
  iadddocumentation -name Description -text "The register is updated with the value that the  1588 timer seconds register held when the SFD of  a PTP receive peer event crosses the MII interface.  The actual update occurs when the GEM  recognizes the frame as a PTP pdelay_req or  pdelay_resp frame. An interrupt is issued when  the register is updated."

  imodeladdfield -access r -name ns_reg_val -bitoffset 0 -width 30 -mmregister bport1/ab/ptp_peer_rx_ns
  iadddocumentation -name Description -text "The register is updated with the value that the  1588 timer nanoseconds register held when the  SFD of a PTP receive peer event crosses the MII  interface. The actual update occurs when the  GEM recognizes the frame as a PTP pdelay_req or  pdelay_resp frame. An interrupt is issued when  the register is updated."

  imodeladdfield -access r -name gem_tx_pbuf_addr -bitoffset 26 -width 4 -mmregister bport1/ab/design_cfg2
  iadddocumentation -name Description -text "Takes the value of the `gem_tx_pbuf_addr  DEFINE. Max address bits for Tx packet buffer  (10-bits for maximum 4 kB buffer). Buffer size for  Tx packet buffer mode will be 4kB. This will allow one standard packet to be received  while another is transferred to system memory by  the DMA interface."

  imodeladdfield -access r -name gem_rx_pbuf_addr -bitoffset 22 -width 4 -mmregister bport1/ab/design_cfg2
  iadddocumentation -name Description -text "Takes the value of the `gem_rx_pbuf_addr  DEFINE. Max address bits for Rx packet buffer  (10-bits for maximum 4 kB buffer). Buffer size for  Rx packet buffer mode will be 4kB. This will allow one standard packet to be received  while another is transferred to system memory by  the DMA interface."

  imodeladdfield -access r -name gem_tx_pkt_buffer -bitoffset 21 -width 1 -mmregister bport1/ab/design_cfg2
  iadddocumentation -name Description -text "Takes the value of the `gem_tx_pkt_buffer DEFINE. Defined for Zynq. Includes the transmitter packet buffer"

  imodeladdfield -access r -name gem_rx_pkt_buffer -bitoffset 20 -width 1 -mmregister bport1/ab/design_cfg2
  iadddocumentation -name Description -text "Takes the value of the `gem_rx_pkt_buffer  DEFINE. Defined for Zynq. Includes the receiver  packet buffer."

  imodeladdfield -access r -name gem_hprot_value -bitoffset 16 -width 4 -mmregister bport1/ab/design_cfg2
  iadddocumentation -name Description -text "Takes the value of the `gem_hprot_value DEFINE.  For Zynq, set the fixed AHB HPROT value used  during transfers."

  imodeladdfield -access r -name gem_jumbo_max_length -bitoffset 0 -width 16 -mmregister bport1/ab/design_cfg2
  iadddocumentation -name Description -text "Takes the value of the `gem_jumbo_max_length DEFINE. Maximum length of jumbo frames accepted by receiver. This is set to the size of the smallest of the two packet buffer, minus a margin for packet headers. However, Zynq will not support jumbo frames."

  imodeladdfield -access r -name gem_rx_base2_fifo_siz -bitoffset 16 -width 16 -mmregister bport1/ab/design_cfg3
  iadddocumentation -name Description -text "Takes the value of the `gem_rx_base2_fifo_size  DEFINE. Base-2 equivalent of `gem_rx_fifo_size"

  imodeladdfield -access r -name gem_rx_fifo_size -bitoffset 0 -width 16 -mmregister bport1/ab/design_cfg3
  iadddocumentation -name Description -text "Takes the value of the `gem_rx_fifo_size DEFINE.  Set the size of the small Rx FIFO for grant latency.  Extended to 16 deep to allow buffering of 64 byte  maximum AHB burst size in Zynq."

  imodeladdfield -access r -name gem_tx_base2_fifo_size -bitoffset 16 -width 16 -mmregister bport1/ab/design_cfg4
  iadddocumentation -name Description -text "Takes the value of the `gem_tx_base2_fifo_size  DEFINE. Base-2 equivalent of `gem_tx_fifo_size."

  imodeladdfield -access r -name gem_tx_fifo_size -bitoffset 0 -width 16 -mmregister bport1/ab/design_cfg4
  iadddocumentation -name Description -text "Takes the value of the `gem_tx_fifo_size DEFINE. Set the size of the small TX FIFO for grant latency"

  imodeladdfield -access r -name gem_tsu_clk -bitoffset 28 -width 1 -mmregister bport1/ab/design_cfg5
  iadddocumentation -name Description -text "Takes the value of the `gem_tsu_clk DEFINE.  Undefined in Zynq. 1588 Time Stamp Unit clock  sourced from pclk rather than independent  tsu_clk."

  imodeladdfield -access r -name gem_rx_buffer_length_ -bitoffset 20 -width 8 -mmregister bport1/ab/design_cfg5
  iadddocumentation -name Description -text "Takes the value of the `gem_rx_buffer_length_def  DEFINE. Set the default buffer length used by Rx  DMA to 128 bytes."

  imodeladdfield -access r -name gem_tx_pbuf_size_def -bitoffset 19 -width 1 -mmregister bport1/ab/design_cfg5
  iadddocumentation -name Description -text "Takes the value of the `gem_tx_pbuf_size_def  DEFINE. Full 4 kB Tx packet buffer size -  dedicated memory resource in Zynq."

  imodeladdfield -access r -name gem_rx_pbuf_size_def -bitoffset 17 -width 2 -mmregister bport1/ab/design_cfg5
  iadddocumentation -name Description -text "Takes the value of the `gem_rx_pbuf_size_def DEFINE. Full 4 kB Rx packet buffer size - dedicated memory resource in Zynq."

  imodeladdfield -access r -name gem_endian_swap_def -bitoffset 15 -width 2 -mmregister bport1/ab/design_cfg5
  iadddocumentation -name Description -text "Takes the value of the `gem_endian_swap_def  DEFINE. Set to big endian data, little endian  management descriptors in Zynq."

  imodeladdfield -access r -name gem_mdc_clock_div -bitoffset 12 -width 3 -mmregister bport1/ab/design_cfg5
  iadddocumentation -name Description -text "Takes the value of the `gem_mdc_clock_div  DEFINE. Set default MDC clock divisor (can still  be programmed) in Zynq."

  imodeladdfield -access r -name gem_dma_bus_width -bitoffset 10 -width 2 -mmregister bport1/ab/design_cfg5
  iadddocumentation -name Description -text "Takes the value of the `gem_dma_bus_width_def  DEFINE. Limit to 32-bit AHB bus in Zynq."

  imodeladdfield -access r -name gem_phy_ident -bitoffset 9 -width 1 -mmregister bport1/ab/design_cfg5
  iadddocumentation -name Description -text "Takes the value of the `gem_phy_ident DEFINE.  Undefined in Zynq. Only used in PCS."

  imodeladdfield -access r -name gem_tsu -bitoffset 8 -width 1 -mmregister bport1/ab/design_cfg5
  iadddocumentation -name Description -text "Takes the value of the `gem_tsu DEFINE. Defined  in Zynq. Include support for 1588 Time Stamp  Unit."

  imodeladdfield -access r -name gem_tx_fifo_cnt_width -bitoffset 4 -width 4 -mmregister bport1/ab/design_cfg5
  iadddocumentation -name Description -text "Takes the value of the `gem_tx_fifo_cnt_width  DEFINE. Width for `gem_tx_fifo_size"

  imodeladdfield -access r -name gem_rx_fifo_cnt_width -bitoffset 0 -width 4 -mmregister bport1/ab/design_cfg5
  iadddocumentation -name Description -text "Takes the value of the `gem_rx_fifo_cnt_width  DEFINE. Width for `gem_rx_fifo_size."

   

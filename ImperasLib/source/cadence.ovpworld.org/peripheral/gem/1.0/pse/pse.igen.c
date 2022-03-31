/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////


#include "pse.igen.h"
/////////////////////////////// Port Declarations //////////////////////////////

bport1_ab_dataT bport1_ab_data;

phyport_ab_dataT phyport_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "gem", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

static PPM_READ_CB(read_16) {  return *(Uns16*)user; }

static PPM_WRITE_CB(write_16) { *(Uns16*)user = data; }

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

static PPM_WRITE_CB(write_32) { *(Uns32*)user = data; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x1000);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x1000);
    handles.phyport = ppmCreateSlaveBusPort("phyport", 256);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abnet_ctrl_reg = ppmCreateRegister(
            "ab_net_ctrl",
            "Network Control",
            handles.bport1,
            0x0,
            4,
            Readnet_ctrl,
            Writenet_ctrl,
            view32,
            &(bport1_ab_data.net_ctrl.value),
            True
        );

        ppmCreateRegisterField(abnet_ctrl_reg, "flush_next_rx_dpram_", "Flush the next packet from the external RX  DPRAM. Writing one to this bit will only have an effect if  the DMA is not currently writing a packet already  stored in the DPRAM to memory.", 18, 1, 0, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "tx_pfc_pri_pri_pause_f", "Transmit PFC Priority Based Pause Frame. Takes  the values stored in the Transmit PFC Pause  Register", 17, 1, 0, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "en_pfc_pri_pause_rx", "Enable PFC Priority Based Pause Reception  capabilities. Setting this bit will enable PFC negotiation and  recognition of priority based pause frames.", 16, 1, 0, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "str_rx_timestamp", "Store receive time stamp to memory. Setting this  bit to one will cause the CRC of every received  frame to be replaced with the value of the  nanoseconds field of the 1588 timer that was  captured as the receive frame passed the message  time stamp point. Set to zero for normal  operation.", 15, 1, 1, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "tx_zeroq_pause_frame", "Transmit zero quantum pause frame. Writing one  to this bit causes a pause frame with zero  quantum to be transmitted.", 12, 1, 0, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "tx_pause_frame", "Transmit pause frame - writing one to this bit  causes a pause frame to be transmitted.", 11, 1, 0, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "tx_halt", "Transmit halt - writing one to this bit halts  transmission as soon as any ongoing frame  transmission ends.", 10, 1, 0, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "start_tx", "Start transmission - writing one to this bit starts  transmission.", 9, 1, 0, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "back_pressure", "Back pressure - if set in 10M or 100M half duplex  mode will force collisions on all received frames.", 8, 1, 1, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "wren_stat_regs", "Write enable for statistics registers - setting this bit  to one means the statistics registers can be written  for functional test purposes.", 7, 1, 1, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "incr_stat_regs", "Incremental statistics registers - this bit is write  only. Writing a one increments all the statistics registers  by one for test purposes.", 6, 1, 0, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "clear_stat_regs", "Clear statistics registers - this bit is write only. Writing a one clears the statistics registers.", 5, 1, 0, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "mgmt_port_en", "Management port enable - set to one to enable the  management port. When zero forces mdio to high  impedance state and mdc low.", 4, 1, 1, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "tx_en", "Transmit enable - when set, it enables the GEM  transmitter to send data. When reset transmission  will stop immediately, the transmit pipeline and  control registers will be cleared and the transmit  queue pointer register will reset to point to the  start of the transmit descriptor list.", 3, 1, 1, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "rx_en", "Receive enable - when set, it enables the GEM to  receive data. When reset frame reception will stop  immediately and the receive pipeline will be  cleared. The receive queue pointer register is unaffected.", 2, 1, 1, 1);
        ppmCreateRegisterField(abnet_ctrl_reg, "loopback_local", "Loop back local - asserts the loopback_local signal  to the system clock generator. Also connects txd to  rxd, tx_en to rx_dv and forces full duplex mode.  Bit 11 of the network configuration register must  be set low to disable TBI mode when in internal  loopback. rx_clk and tx_clk may malfunction as  the GEM is switched into and out of internal loop  back. It is important that receive and transmit  circuits have already been disabled when making  the switch into and out of internal loop back.  Local loopback functionality isn't available in the  EP107 Zynq Emulation Platform, because the  clocking doesn't map well into an FPGA.", 1, 1, 1, 1);
    }
    {
        registerHandle abnet_cfg_reg = ppmCreateRegister(
            "ab_net_cfg",
            "Network Configuration",
            handles.bport1,
            0x4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.net_cfg.value),
            True
        );

        ppmCreateRegisterField(abnet_cfg_reg, "unidir_en", "NA.", 31, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "ignore_ipg_rx_er", "Ignore IPG rx_er. When set rx_er has no effect on  the GEM's operation when rx_dv is low. Set this  when using the RGMII wrapper in half-duplex  mode.", 30, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "rx_bad_preamble", "Receive bad preamble. When set frames with  non-standard preamble are not rejected.", 29, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "ipg_stretch_en", "IPG stretch enable - when set the transmit IPG can  be increased above 96 bit times depending on the  previous frame length using the IPG stretch  register.", 28, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "sgmii_en", "SGMII mode enable - changes behavior of the  auto-negotiation advertisement and link partner  ability registers to meet the requirements of  SGMII and reduces the duration of the link timer  from 10 ms to 1.6 ms", 27, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "ignore_rx_fcs", "Ignore RX FCS - when set frames with FCS/CRC  errors will not be rejected. FCS error statistics will  still be collected for frames with bad FCS and FCS  status will be recorded in frame's DMA  descriptor. For normal operation this bit must be set to zero.", 26, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "rx_hd_while_tx", "Enable frames to be received in half-duplex mode  while transmitting.", 25, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "rx_chksum_offld_en", "Receive checksum offload enable - when set, the  receive checksum engine is enabled. Frames with  bad IP, TCP or UDP checksums are discarded.", 24, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "dis_cp_pause_frame", "Disable copy of pause frames - set to one to prevent valid pause frames being copied to memory. When set, pause frames are not copied to memory regardless of the state of the copy all frames bit; whether a hash match is found or whether a type ID match is identified. If a destination address match is found the pause frame will be copied to memory.  Note that valid pause frames received will still increment pause statistics and pause the transmission of frames as required.", 23, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "dbus_width", "Data bus width. Only valid bus widths may be  written if the system is configured to a maximum  width less than 128-bits. Zynq defines  gem_dma_bus_width_def as 2'b00. 00: 32 bit AMBA AHB data bus width 01: 64 bit AMBA AHB data bus width 10: 128 bit AMBA AHB data bus width 11: 128 bit AMBA AHB data bus width", 21, 2, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "mdc_clk_div", "MDC clock division - set according to cpu_1xclk  speed. These three bits determine the number cpu_1xclk  will be divided by to generate MDC. For  conformance with the 802.3 specification, MDC  must not exceed 2.5 MHz (MDC is only active  during MDIO read and write operations). 000: divide cpu_1xclk by 8 (cpu_1xclk up to 20  MHz) 001: divide cpu_1xclk by 16 (cpu_1xclk up to 40  MHz) 010: divide cpu_1xclk by 32 (cpu_1xclk up to 80  MHz) 011: divide cpu_1xclk by 48 (cpu_1xclk up to  120MHz) 100: divide cpu_1xclk by 64 (cpu_1xclk up to 160  MHz) 101: divide cpu_1xclk by 96 (cpu_1xclk up to 240  MHz) 110: divide cpu_1xclk by 128 (cpu_1xclk up to 320  MHz) 111: divide cpu_1xclk by 224 (cpu_1xclk up to 540  MHz)", 18, 3, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "fcs_remove", "FCS remove - setting this bit will cause received  frames to be written to memory without their  frame check sequence (last 4 bytes). The frame  length indicated will be reduced by four bytes in  this mode.", 17, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "len_err_frame_disc", "Length field error frame discard - setting this bit  causes frames with a measured length shorter  than the extracted length field (as indicated by  bytes 13 and 14 in a non-VLAN tagged frame) to  be discarded. This only applies to frames with a  length field less than 0x0600.", 16, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "rx_buf_offset", "Receive buffer offset - indicates the number of  bytes by which the received data is offset from the  start of the receive buffer.", 14, 2, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "pause_en", "Pause enable - when set, transmission will pause  if a non zero 802.3 classic pause frame is received  and PFC has not been negotiated.", 13, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "retry_test", "Retry test - must be set to zero for normal  operation. If set to one the backoff between collisions will  always be one slot time. Setting this bit to one  helps test the too many retries condition. Also  used in the pause frame tests to reduce the pause  counter's decrement time from 512 bit times, to  every rx_clk cycle.", 12, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "pcs_sel", "NA 0: GMII/MII interface enabled, TBI disabled 1: TBI enabled, GMII/MII disabled", 11, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "gige_en", "Gigabit mode enable - setting this bit configures  the GEM for 1000 Mbps operation. 0: 10/100 operation using MII or TBI interface 1: Gigabit operation using GMII or TBI interface", 10, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "ext_addr_match_en", "External address match enable - when set the  external address match interface can be used to  copy frames to memory.", 9, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "rx_1536_byte_frames", "Receive 1536 byte frames - setting this bit means  the GEM will accept frames up to 1536 bytes in  length. Normally the GEM would reject any  frame above 1518 bytes.", 8, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "uni_hash_en", "Unicast hash enable - when set, unicast frames  will be accepted when the 6 bit hash function of  the destination address points to a bit that is set in  the hash register.", 7, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "multi_hash_en", "Multicast hash enable - when set, multicast  frames will be accepted when the 6 bit hash  function of the destination address points to a bit  that is set in the hash register.", 6, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "no_broadcast", "No broadcast - when set to logic one, frames  addressed to the broadcast address of all ones will  not be accepted.", 5, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "copy_all", "Copy all frames - when set to logic one, all valid  frames will be accepted.", 4, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "disc_non_vlan", "Discard non-VLAN frames - when set only VLAN tagged frames will be passed to the address matching logic.", 2, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "full_duplex", "Full duplex - if set to logic one, the transmit block  ignores the state of collision and carrier sense and  allows receive while transmitting. Also controls  the half-duplex pin.", 1, 1, 1, 1);
        ppmCreateRegisterField(abnet_cfg_reg, "speed", "Speed - set to logic one to indicate 100Mbps  operation, logic zero for 10Mbps. The value of this  pin is reflected on the speed_mode[0] output pin.", 0, 1, 1, 1);
    }
    {
        registerHandle abnet_status_reg = ppmCreateRegister(
            "ab_net_status",
            "Network Status",
            handles.bport1,
            0x8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.net_status.value),
            True
        );

        ppmCreateRegisterField(abnet_status_reg, "pfc_pri_pause_neg", "Set when PFC Priority Based Pause has been  negotiated.", 6, 1, 1, 0);
        ppmCreateRegisterField(abnet_status_reg, "pcs_autoneg_pause_tx", "NA", 5, 1, 1, 0);
        ppmCreateRegisterField(abnet_status_reg, "pcs_autoneg_pause_rx", "NA", 4, 1, 1, 0);
        ppmCreateRegisterField(abnet_status_reg, "pcs_autoneg_dup_res", "NA", 3, 1, 1, 0);
        ppmCreateRegisterField(abnet_status_reg, "phy_mgmt_idle", "The PHY management logic is idle (i.e. has  completed).", 2, 1, 1, 0);
        ppmCreateRegisterField(abnet_status_reg, "mdio_in_pin_status", "Returns status of the mdio_in pin", 1, 1, 1, 0);
        ppmCreateRegisterField(abnet_status_reg, "pcs_link_state", "NA", 0, 1, 1, 0);
    }
    {
        ppmCreateRegister(
            "ab_user_io",
            "User IO (Not in TRM)",
            handles.bport1,
            0xc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.user_io.value),
            True
        );
    }
    {
        registerHandle abdma_cfg_reg = ppmCreateRegister(
            "ab_dma_cfg",
            "DMA Configuration",
            handles.bport1,
            0x10,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.dma_cfg.value),
            True
        );

        ppmCreateRegisterField(abdma_cfg_reg, "disc_when_no_ahb", "When set, the GEM DMA will automatically  discard receive packets from the receiver packet  buffer memory when no AHB resource is  available. When low, then received packets will remain to be  stored in the SRAM based packet buffer until  AHB buffer resource next becomes available.", 24, 1, 1, 1);
        ppmCreateRegisterField(abdma_cfg_reg, "ahb_mem_rx_buf_size", "DMA receive buffer size in AHB system memory. The value defined by these bits determines the  size of buffer to use in main AHB system memory  when writing received data. The value is defined in multiples of 64 bytes such  that a value of 0x01 corresponds to buffers of 64  bytes, 0x02 corresponds to 128 bytes etc. For example: 0x02: 128 byte 0x18: 1536 byte (1*max length frame/buffer) 0xA0: 10240 byte (1*10k jumbo frame/buffer) Note that this value should never be written as  zero.", 16, 8, 1, 1);
        ppmCreateRegisterField(abdma_cfg_reg, "csum_gen_offload_en", "Transmitter IP, TCP and UDP checksum  generation offload enable. When set, the  transmitter checksum generation engine is  enabled, to calculate and substitute checksums for  transmit frames. When clear, frame data is  unaffected. If the GEM is not configured to use the DMA  packet buffer, this bit is not implemented and will  be treated as reserved, read as zero, ignored on  write. Zynq uses packet buffer.", 11, 1, 1, 1);
        ppmCreateRegisterField(abdma_cfg_reg, "tx_pktbuf_memsz_sel", "Transmitter packet buffer memory size select -  Having this bit at zero halves the amount of  memory used for the transmit packet buffer. This  reduces the amount of memory used by the GEM.  It is important to set this bit to one if the full  configured physical memory is available. The  value in brackets below represents the size that  would result for the default maximum configured  memory size of 4 kB. 1: Use full configured addressable space (4 kB) 0: Do not use top address bit (2 kB) If the GEM is not configured to use the DMA  packet buffer, this bit is not implemented and will  be treated as reserved, read as zero, ignored on  write. Zynq uses packet buffer.", 10, 1, 1, 1);
        ppmCreateRegisterField(abdma_cfg_reg, "rx_pktbuf_memsz_sel", "Receiver packet buffer memory size select -  Having these bits at less than 11 reduces the  amount of memory used for the receive packet  buffer. This reduces the amount of memory used  by the GEM. It is important to set these bits both  to one if the full configured physical memory is  available. The value in brackets below represents  the size that would result for the default  maximum configured memory size of 8 kBs. 00: Do not use top three address bits (1 kB) 01: Do not use top two address bits (2 kB) 10: Do not use top address bit (4 kB) 11: Use full configured addressable space (8 kB) If the controller is not configured to use the DMA  packet buffer, these bits are not implemented and  will be treated as reserved, read as zero, ignored  on write. Zynq uses packet buffer.", 8, 2, 1, 1);
        ppmCreateRegisterField(abdma_cfg_reg, "ahb_endian_swp_pkt_", "AHB endian swap mode enable for packet data  accesses - When set, selects swapped endianism  for AHB transfers. When clear, selects little endian  mode.", 7, 1, 1, 1);
        ppmCreateRegisterField(abdma_cfg_reg, "ahb_endian_swp_mgm", "AHB endian swap mode enable for management  descriptor accesses - When set, selects swapped  endianism for AHB transfers. When clear, selects  little endian mode.", 6, 1, 1, 1);
        ppmCreateRegisterField(abdma_cfg_reg, "ahb_fixed_burst_len", "AHB fixed burst length for DMA data operations  - Selects the burst length to attempt to use on the  AHB when transferring frame data. Not used for  DMA management operations and only used  where space and data size allow. Otherwise  SINGLE type AHB transfers are used. Upper bits become non-writeable if the  configured DMA TX and RX FIFO sizes are  smaller than required to support the selected  burst size. One-hot priority encoding enforced automatically  on register writes as follows, where 'x' represents  don't care: 00001: Always use SINGLE AHB bursts 0001x: Always use SINGLE AHB bursts 001xx: Attempt to use INCR4 AHB bursts  (default) 01xxx: Attempt to use INCR8 AHB bursts 1xxxx: Attempt to use INCR16 AHB bursts others: reserved", 0, 5, 1, 1);
    }
    {
        registerHandle abtx_status_reg = ppmCreateRegister(
            "ab_tx_status",
            "Transmit Status",
            handles.bport1,
            0x14,
            4,
            read_32,
            Writetx_status,
            view32,
            &(bport1_ab_data.tx_status.value),
            True
        );

        ppmCreateRegisterField(abtx_status_reg, "hresp_not_ok", "Hresp not OK - set when the DMA block sees  hresp not OK. Cleared by writing a one to this bit.", 8, 1, 1, 1);
        ppmCreateRegisterField(abtx_status_reg, "late_collision", "Late collision occurred - only set if the condition  occurs in gigabit mode, as retry is not attempted. Cleared by writing a one to this bit.", 7, 1, 1, 1);
        ppmCreateRegisterField(abtx_status_reg, "tx_under_run", "Transmit under run - this bit is set if the  transmitter was forced to terminate a frame that it  had already began transmitting due to further  data being unavailable. This bit is set if a transmitter status write back has  not completed when another status write back is  attempted. When using the DMA interface configured for  internal FIFO mode, this bit is also set when the  transmit DMA has written the SOP data into the  FIFO and either the AHB bus was not granted in  time for further data, or because an AHB not OK  response was returned, or because a used bit was  read. When using the DMA interface configured for  packet buffer mode, this bit will never be set. When using the external FIFO interface, this bit is  also set when the tx_r_underflow input is  asserted during a frame transfer. Cleared by  writing a 1.", 6, 1, 1, 1);
        ppmCreateRegisterField(abtx_status_reg, "tx_complete", "Transmit complete - set when a frame has been  transmitted. Cleared by writing a one to this bit.", 5, 1, 1, 1);
        ppmCreateRegisterField(abtx_status_reg, "tx_corr_ahb_err", "Transmit frame corruption due to AHB error - set  if an error occurs whilst midway through reading  transmit frame from the AHB, including HRESP  errors and buffers exhausted mid frame (if the  buffers run out during transmission of a frame  then transmission stops, FCS shall be bad and  tx_er asserted). Also set in DMA packet buffer mode if single  frame is too large for configured packet buffer  memory size. Cleared by writing a one to this bit.", 4, 1, 1, 1);
        ppmCreateRegisterField(abtx_status_reg, "tx_go", "Transmit go - if high transmit is active. When using the exposed FIFO interface, this bit  represents bit 3 of the network control register. When using the DMA interface this bit represents  the tx_go variable as specified in the transmit  buffer description.", 3, 1, 1, 0);
        ppmCreateRegisterField(abtx_status_reg, "retry_limit_exceeded", "Retry limit exceeded - cleared by writing a one to  this bit.", 2, 1, 1, 1);
        ppmCreateRegisterField(abtx_status_reg, "collision", "Collision occurred - set by the assertion of  collision. Cleared by writing a one to this bit. When  operating in 10/100 mode, this status indicates  either a collision or a late collision. In gigabit  mode, this status is not set for a late collision.", 1, 1, 1, 1);
        ppmCreateRegisterField(abtx_status_reg, "used_bit_read", "Used bit read - set when a transmit buffer  descriptor is read with its used bit set. Cleared by  writing a one to this bit.", 0, 1, 1, 1);
    }
    {
        registerHandle abrx_qbar_reg = ppmCreateRegister(
            "ab_rx_qbar",
            "Receive Buffer Queue Base Address",
            handles.bport1,
            0x18,
            4,
            read_32,
            Writerx_qbar,
            view32,
            &(bport1_ab_data.rx_qbar.value),
            True
        );

        ppmCreateRegisterField(abrx_qbar_reg, "rx_q_baseaddr", "Receive buffer queue base address - written with  the address of the start of the receive queue.", 2, 30, 1, 1);
    }
    {
        registerHandle abtx_qbar_reg = ppmCreateRegister(
            "ab_tx_qbar",
            "Transmit Buffer Queue Base Address",
            handles.bport1,
            0x1c,
            4,
            read_32,
            Writetx_qbar,
            view32,
            &(bport1_ab_data.tx_qbar.value),
            True
        );

        ppmCreateRegisterField(abtx_qbar_reg, "tx_q_base_addr", "Transmit buffer queue base address - written with  the address of the start of the transmit queue.", 2, 30, 1, 1);
    }
    {
        registerHandle abrx_status_reg = ppmCreateRegister(
            "ab_rx_status",
            "Receive Status",
            handles.bport1,
            0x20,
            4,
            read_32,
            Writerx_status,
            view32,
            &(bport1_ab_data.rx_status.value),
            True
        );

        ppmCreateRegisterField(abrx_status_reg, "hresp_not_ok", "Hresp not OK - set when the DMA block sees  hresp not OK. Cleared by writing a one to this bit.", 3, 1, 1, 1);
        ppmCreateRegisterField(abrx_status_reg, "rx_overrun", "Receive overrun - this bit is set if either the  gem_dma RX FIFO or external RX FIFO were  unable to store the receive frame due to a FIFO  overflow, or if the receive status, reported by the  gem_rx module to the gem_dma was not taken at  end of frame. This bit is also set in DMA packet  buffer mode if the packet buffer overflows. For  DMA operation the buffer will be recovered if an  overrun occurs. This bit is cleared by writing a  one to it.", 2, 1, 1, 1);
        ppmCreateRegisterField(abrx_status_reg, "frame_recd", "Frame received - one or more frames have been  received and placed in memory. Cleared by  writing a one to this bit.", 1, 1, 1, 1);
        ppmCreateRegisterField(abrx_status_reg, "buffer_not_avail", "Buffer not available - an attempt was made to get  a new buffer and the pointer indicated that it was  owned by the processor. The DMA will reread the  pointer each time an end of frame is received until  a valid pointer is found. This bit is set following  each descriptor read attempt that fails, even if  consecutive pointers are unsuccessful and  software has in the mean time cleared the status  flag. Cleared by writing a one to this bit.", 0, 1, 1, 1);
    }
    {
        registerHandle abintr_status_reg = ppmCreateRegister(
            "ab_intr_status",
            "Interrupt Status",
            handles.bport1,
            0x24,
            4,
            Readintr_status,
            Writeintr_status,
            view32,
            &(bport1_ab_data.intr_status.value),
            True
        );

        ppmCreateRegisterField(abintr_status_reg, "tsu_sec_incr", "TSU seconds register increment - indicates the  register has incremented.", 26, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "pdelay_resp_tx", "PTP pdelay_resp frame transmitted - indicates a  PTP pdelay_resp frame has been transmitted.", 25, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "pdelay_req_tx", "PTP pdelay_req frame transmitted - indicates a  PTP pdelay_req frame has been transmitted.", 24, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "pdelay_resp_rx", "PTP pdelay_resp frame received - indicates a PTP  pdelay_resp frame has been received.", 23, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "pdelay_req_rx", "PTP pdelay_req frame received - indicates a PTP  pdelay_req frame has been received.", 22, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "sync_tx", "PTP sync frame transmitted - indicates a PTP sync  frame has been transmitted.", 21, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "delay_req_tx", "PTP delay_req frame transmitted - indicates a  PTP delay_req frame has been transmitted.", 20, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "sync_rx", "PTP sync frame received - indicates a PTP sync  frame has been received.", 19, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "delay_req_rx", "PTP delay_req frame received - indicates a PTP  delay_req frame has been received.", 18, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "partner_pg_rx", "NA", 17, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "autoneg_complete", "NA", 16, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "ext_intr", "External interrupt - set when a rising edge has  been detected on the ext_interrupt_in input pin.", 15, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "pause_tx", "Pause frame transmitted - indicates a pause frame  has been successfully transmitted after being  initiated from the network control register or from  the tx_pause control pin.", 14, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "pause_zero", "Pause time zero - set when either the pause time  register at address 0x38 decrements to zero, or  when a valid pause frame is received with a zero  pause quantum field.", 13, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "pause_nonzeroq_rx", "Pause frame with non-zero pause quantum  received - indicates a valid pause has been  received that has a non-zero pause quantum field.", 12, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "hresp_not_ok", "Hresp not OK - set when the DMA block sees  hresp not OK.", 11, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "rx_overrun", "Receive overrun - set when the receive overrun  status bit gets set.", 10, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "link_chng", "NA", 9, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "tx_complete", "Transmit complete - set when a frame has been  transmitted.", 7, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "tx_corrupt_ahb_err", "Transmit frame corruption due to AHB error - set  if an error occurs while midway through reading  transmit frame from the AHB, including HRESP  errors and buffers exhausted mid frame (if the  buffers run out during transmission of a frame  then transmission stops, FCS shall be bad and  tx_er asserted). Also set in DMA packet buffer mode if single  frame is too large for configured packet buffer  memory size. Cleared on a read.", 6, 1, 1, 0);
        ppmCreateRegisterField(abintr_status_reg, "retry_ex_late_collisn", "Retry limit exceeded or late collision - transmit  error. Late collision will only cause this status bit to be  set in gigabit mode (as a retry is not attempted).", 5, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "tx_used_read", "TX used bit read - set when a transmit buffer  descriptor is read with its used bit set.", 3, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "rx_used_read", "RX used bit read - set when a receive buffer  descriptor is read with its used bit set.", 2, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "rx_complete", "Receive complete - a frame has been stored in  memory.", 1, 1, 1, 1);
        ppmCreateRegisterField(abintr_status_reg, "mgmt_sent", "Management frame sent - the PHY maintenance  register has completed its operation.", 0, 1, 1, 1);
    }
    {
        registerHandle abintr_en_reg = ppmCreateRegister(
            "ab_intr_en",
            "Interrupt Enable",
            handles.bport1,
            0x28,
            4,
            0,
            Writeintr_en,
            view32,
            &(bport1_ab_data.intr_en.value),
            True
        );

        ppmCreateRegisterField(abintr_en_reg, "tsu_sec_incr", "Enable TSU seconds register increment interrupt", 26, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "pdelay_resp_tx", "Enable PTP pdelay_resp frame transmitted  interrupt", 25, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "pdelay_req_tx", "Enable PTP pdelay_req frame transmitted  interrupt", 24, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "pdelay_resp_rx", "Enable PTP pdelay_resp frame received interrupt", 23, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "pdelay_req_rx", "Enable PTP pdelay_req frame received interrupt", 22, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "sync_tx", "Enable PTP sync frame transmitted interrupt", 21, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "delay_req_tx", "Enable PTP delay_req frame transmitted  interrupt", 20, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "sync_rx", "Enable PTP sync frame received interrupt", 19, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "delay_req_rx", "Enable PTP delay_req frame received interrupt", 18, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "partner_pg_rx", "NA", 17, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "autoneg_complete", "NA", 16, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "ext_intr", "Enable external interrupt", 15, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "pause_tx", "Enable pause frame transmitted interrupt", 14, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "pause_zero", "Enable pause time zero interrupt", 13, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "pause_nonzeroq", "Enable pause frame with non-zero pause  quantum interrupt", 12, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "hresp_not_ok", "Enable hresp not OK interrupt", 11, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "rx_overrun", "Enable receive overrun interrupt", 10, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "link_chng", "Enable link change interrupt", 9, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "tx_complete", "Enable transmit complete interrupt", 7, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "tx_corrupt_ahb_err", "Enable transmit frame corruption due to AHB  error interrupt", 6, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "retry_ex_late_collisn", "Enable retry limit exceeded or late collision  interrupt", 5, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "tx_underrun", "Enable transmit buffer under run interrupt", 4, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "tx_used_read", "Enable transmit used bit read interrupt", 3, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "rx_used_read", "Enable receive used bit read interrupt", 2, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "rx_complete", "Enable receive complete interrupt", 1, 1, 0, 1);
        ppmCreateRegisterField(abintr_en_reg, "mgmt_done", "Enable management done interrupt", 0, 1, 0, 1);
    }
    {
        registerHandle abintr_dis_reg = ppmCreateRegister(
            "ab_intr_dis",
            "Interrupt Disable",
            handles.bport1,
            0x2c,
            4,
            0,
            Writeintr_dis,
            view32,
            &(bport1_ab_data.intr_dis.value),
            True
        );

        ppmCreateRegisterField(abintr_dis_reg, "tsu_sec_incr", "Disable TSU seconds register increment interrupt", 26, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "pdelay_resp_tx", "Disable PTP pdelay_resp frame transmitted  interrupt", 25, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "pdelay_req_tx", "Disable PTP pdelay_req frame transmitted  interrupt", 24, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "pdelay_resp_rx", "Disable PTP pdelay_resp frame received interrupt", 23, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "pdelay_req_rx", "Disable PTP pdelay_req frame received interrupt", 22, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "sync_tx", "Disable PTP sync frame transmitted interrupt", 21, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "delay_req_tx", "Disable PTP delay_req frame transmitted  interrupt", 20, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "sync_rx", "Disable PTP sync frame received interrupt", 19, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "delay_req_rx", "Disable PTP delay_req frame received interrupt", 18, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "partner_pg_rx", "NA", 17, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "autoneg_complete", "NA", 16, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "ext_intr", "Disable external interrupt", 15, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "pause_tx", "Disable pause frame transmitted interrupt", 14, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "pause_zero", "Disable pause time zero interrupt", 13, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "pause_nonzeroq", "Disable pause frame with non-zero pause  quantum interrupt", 12, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "hresp_not_ok", "Disable hresp not OK interrupt", 11, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "rx_overrun", "Disable receive overrun interrupt", 10, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "link_chng", "Disable link change interrupt", 9, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "tx_complete", "Disable transmit complete interrupt", 7, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "tx_corrupt_ahb_err", "Disable transmit frame corruption due to AHB  error interrupt", 6, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "retry_ex_late_collisn", "Disable retry limit exceeded or late collision  interrupt", 5, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "tx_underrun", "Disable transmit buffer under run interrupt", 4, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "tx_used_read", "Disable transmit used bit read interrupt", 3, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "rx_used_read", "Disable receive used bit read interrupt", 2, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "rx_complete", "Disable receive complete interrupt", 1, 1, 0, 1);
        ppmCreateRegisterField(abintr_dis_reg, "mgmt_done", "Disable management done interrupt", 0, 1, 0, 1);
    }
    {
        registerHandle abintr_mask_reg = ppmCreateRegister(
            "ab_intr_mask",
            "Interrupt Mask Status",
            handles.bport1,
            0x30,
            4,
            read_32,
            Writeintr_mask,
            view32,
            &(bport1_ab_data.intr_mask.value),
            True
        );

        ppmCreateRegisterField(abintr_mask_reg, "pdelay_resp_tx", "PTP pdelay_resp frame transmitted mask.", 25, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "pdelay_req_tx", "PTP pdelay_req frame transmitted mask.", 24, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "pdelay_resp_rx", "PTP pdelay_resp frame received mask.", 23, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "pdelay_req_rx", "PTP pdelay_req frame received mask.", 22, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "sync_tx", "PTP sync frame transmitted mask.", 21, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "delay_req_tx", "PTP delay_req frame transmitted mask.", 20, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "sync_rx", "PTP sync frame received mask.", 19, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "delay_req_rx", "PTP delay_req frame received mask.", 18, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "partner_pg_rx", "NA", 17, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "autoneg_complete", "NA", 16, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "ext_intr", "External interrupt mask.", 15, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "pause_tx", "Pause frame transmitted interrupt mask.", 14, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "pause_zero", "Pause time zero interrupt mask.", 13, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "pause_nonzeroq", "Pause frame with non-zero pause quantum  interrupt mask.", 12, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "hresp_not_ok", "Hresp not OK interrupt mask.", 11, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "rx_overrun", "Receive overrun interrupt mask.", 10, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "link_chng", "Link change interrupt mask.", 9, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "tx_complete", "Transmit complete interrupt mask.", 7, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "tx_corrupt_ahb_err", "Transmit frame corruption due to AHB error  interrupt", 6, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "retry_ex_late_collisn", "Retry limit exceeded or late collision (gigabit  mode only)", 5, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "tx_underrun", "Transmit buffer under run interrupt mask.", 4, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "tx_used_read", "Transmit used bit read interrupt mask.", 3, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "rx_used_read", "Receive used bit read interrupt mask.", 2, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "rx_complete", "Receive complete interrupt mask.", 1, 1, 1, 1);
        ppmCreateRegisterField(abintr_mask_reg, "mgmt_done", "Management done interrupt mask.", 0, 1, 1, 1);
    }
    {
        registerHandle abphy_maint_reg = ppmCreateRegister(
            "ab_phy_maint",
            "PHY Maintenance",
            handles.bport1,
            0x34,
            4,
            read_32,
            Writephy_maint,
            view32,
            &(bport1_ab_data.phy_maint.value),
            True
        );

        ppmCreateRegisterField(abphy_maint_reg, "clause_22", "Must be written to 1 for Clause 22 operation. Check your PHY's spec to see if it is clause 22 or  clause 45 compliant.", 30, 1, 1, 1);
        ppmCreateRegisterField(abphy_maint_reg, "operation", "Operation. 10 is read. 01 is write.", 28, 2, 1, 1);
        ppmCreateRegisterField(abphy_maint_reg, "phy_addr", "PHY address.", 23, 5, 1, 1);
        ppmCreateRegisterField(abphy_maint_reg, "reg_addr", "Register address - specifies the register in the PHY  to access.", 18, 5, 1, 1);
        ppmCreateRegisterField(abphy_maint_reg, "must_10", "Must be written to 10.", 16, 2, 1, 1);
        ppmCreateRegisterField(abphy_maint_reg, "data", "For a write operation this is written with the data  to be written to the PHY. After a read operation  this contains the data read from the PHY.", 0, 16, 1, 1);
    }
    {
        registerHandle abrx_pauseq_reg = ppmCreateRegister(
            "ab_rx_pauseq",
            "Received Pause Quantum",
            handles.bport1,
            0x38,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.rx_pauseq.value),
            True
        );

        ppmCreateRegisterField(abrx_pauseq_reg, "rx_pauseq", "Received pause quantum - stores the current  value of the received pause quantum register  which is decremented every 512 bit times.", 0, 16, 1, 0);
    }
    {
        registerHandle abtx_pauseq_reg = ppmCreateRegister(
            "ab_tx_pauseq",
            "Transmit Pause Quantum",
            handles.bport1,
            0x3c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.tx_pauseq.value),
            True
        );

        ppmCreateRegisterField(abtx_pauseq_reg, "tx_pauseq", "Transmit pause quantum - written with the pause  quantum value for pause frame transmission.", 0, 16, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_gem_jml",
            "GEM Jumbo Max Length",
            handles.bport1,
            0x48,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.gem_jml.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_hash_bot",
            "Hash Register Bottom [31:0]",
            handles.bport1,
            0x80,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.hash_bot.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_hash_top",
            "Hash Register Top [63:32]",
            handles.bport1,
            0x84,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.hash_top.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_spec_addr1_bot",
            "Specific Address 1 Bottom [31:0]",
            handles.bport1,
            0x88,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.spec_addr1_bot.value),
            True
        );
    }
    {
        registerHandle abspec_addr1_top_reg = ppmCreateRegister(
            "ab_spec_addr1_top",
            "Specific Address 1 Top [47:32]",
            handles.bport1,
            0x8c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.spec_addr1_top.value),
            True
        );

        ppmCreateRegisterField(abspec_addr1_top_reg, "addr_msbs", "Specific address 1. The most significant bits of the  destination address, that is bits 47:32.", 0, 16, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_spec_addr2_bot",
            "Specific Address 2 Bottom [31:0]",
            handles.bport1,
            0x90,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.spec_addr2_bot.value),
            True
        );
    }
    {
        registerHandle abspec_addr2_top_reg = ppmCreateRegister(
            "ab_spec_addr2_top",
            "Specific Address 2 Top [47:32]",
            handles.bport1,
            0x94,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.spec_addr2_top.value),
            True
        );

        ppmCreateRegisterField(abspec_addr2_top_reg, "addr_msbs", "Specific address 2. The most significant bits of the  destination address, that is bits 47:32.", 0, 16, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_spec_addr3_bot",
            "Specific Address 3 Bottom [31:0]",
            handles.bport1,
            0x98,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.spec_addr3_bot.value),
            True
        );
    }
    {
        registerHandle abspec_addr3_top_reg = ppmCreateRegister(
            "ab_spec_addr3_top",
            "Specific Address 3 Top [47:32]",
            handles.bport1,
            0x9c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.spec_addr3_top.value),
            True
        );

        ppmCreateRegisterField(abspec_addr3_top_reg, "addr_msbs", "Specific address 3. The most significant bits of the  destination address, that is bits 47:32.", 0, 16, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_spec_addr4_bot",
            "Specific Address 4 Bottom [31:0]",
            handles.bport1,
            0xa0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.spec_addr4_bot.value),
            True
        );
    }
    {
        registerHandle abspec_addr4_top_reg = ppmCreateRegister(
            "ab_spec_addr4_top",
            "Specific Address 4 Top [47:32]",
            handles.bport1,
            0xa4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.spec_addr4_top.value),
            True
        );

        ppmCreateRegisterField(abspec_addr4_top_reg, "addr_msbs", "Specific address 4. The most significant bits of the  destination address, that is bits 47:32.", 0, 16, 1, 1);
    }
    {
        registerHandle abtype_id_match1_reg = ppmCreateRegister(
            "ab_type_id_match1",
            "Type ID Match 1",
            handles.bport1,
            0xa8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.type_id_match1.value),
            True
        );

        ppmCreateRegisterField(abtype_id_match1_reg, "copy_en", "Enable copying of type ID match 1 matched  frames", 31, 1, 1, 1);
        ppmCreateRegisterField(abtype_id_match1_reg, "type_id_match1", "Type ID match 1. For use in comparisons with  received frames type ID/length field.", 0, 16, 1, 1);
    }
    {
        registerHandle abtype_id_match2_reg = ppmCreateRegister(
            "ab_type_id_match2",
            "Type ID Match 2",
            handles.bport1,
            0xac,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.type_id_match2.value),
            True
        );

        ppmCreateRegisterField(abtype_id_match2_reg, "copy_en", "Enable copying of type ID match 2 matched  frames", 31, 1, 1, 1);
        ppmCreateRegisterField(abtype_id_match2_reg, "type_id_match2", "Type ID match 2. For use in comparisons with  received frames type ID/length field.", 0, 16, 1, 1);
    }
    {
        registerHandle abtype_id_match3_reg = ppmCreateRegister(
            "ab_type_id_match3",
            "Type ID Match 3",
            handles.bport1,
            0xb0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.type_id_match3.value),
            True
        );

        ppmCreateRegisterField(abtype_id_match3_reg, "copy_en", "Enable copying of type ID match 3 matched  frames", 31, 1, 1, 1);
        ppmCreateRegisterField(abtype_id_match3_reg, "type_id_match3", "Type ID match 3. For use in comparisons with  received frames type ID/length field.", 0, 16, 1, 1);
    }
    {
        registerHandle abtype_id_match4_reg = ppmCreateRegister(
            "ab_type_id_match4",
            "Type ID Match 4",
            handles.bport1,
            0xb4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.type_id_match4.value),
            True
        );

        ppmCreateRegisterField(abtype_id_match4_reg, "copy_en", "Enable copying of type ID match 4 matched  frames", 31, 1, 1, 1);
        ppmCreateRegisterField(abtype_id_match4_reg, "type_id_match4", "Type ID match 4. For use in comparisons with  received frames type ID/length field.", 0, 16, 1, 1);
    }
    {
        registerHandle abwake_on_lan_reg = ppmCreateRegister(
            "ab_wake_on_lan",
            "Wake on LAN Register",
            handles.bport1,
            0xb8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.wake_on_lan.value),
            True
        );

        ppmCreateRegisterField(abwake_on_lan_reg, "multi_hash_en", "Wake on LAN multicast hash event enable. When  set multicast hash events will cause the wol  output to be asserted.", 19, 1, 1, 1);
        ppmCreateRegisterField(abwake_on_lan_reg, "spec_addr_reg1_en", "Wake on LAN specific address register 1 event  enable. When set specific address 1 events will  cause the wol output to be asserted.", 18, 1, 1, 1);
        ppmCreateRegisterField(abwake_on_lan_reg, "arp_req_en", "Wake on LAN ARP request event enable. When  set ARP request events will cause the wol output  to be asserted.", 17, 1, 1, 1);
        ppmCreateRegisterField(abwake_on_lan_reg, "magic_pkt_en", "Wake on LAN magic packet event enable. When  set magic packet events will cause the wol output  to be asserted.", 16, 1, 1, 1);
        ppmCreateRegisterField(abwake_on_lan_reg, "arp_req_ip_addr", "Wake on LAN ARP request IP address. Written to  define the least significant 16 bits of the target IP  address that is matched to generate a Wake on  LAN event. A value of zero will not generate an  event, even if this is matched by the received  frame.", 0, 16, 1, 1);
    }
    {
        registerHandle abipg_stretch_reg = ppmCreateRegister(
            "ab_ipg_stretch",
            "IPG stretch register",
            handles.bport1,
            0xbc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ipg_stretch.value),
            True
        );

        ppmCreateRegisterField(abipg_stretch_reg, "ipg_stretch", "Bits 7:0 are multiplied with the previously  transmitted frame length (including preamble)  bits 15:8 +1 divide the frame length. If the  resulting number is greater than 96 and bit 28 is  set in the network configuration register then the  resulting number is used for the transmit  inter-packet-gap. 1 is added to bits 15:8 to prevent  a divide by zero.", 0, 16, 1, 1);
    }
    {
        registerHandle abstacked_vlan_reg = ppmCreateRegister(
            "ab_stacked_vlan",
            "Stacked VLAN Register",
            handles.bport1,
            0xc0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.stacked_vlan.value),
            True
        );

        ppmCreateRegisterField(abstacked_vlan_reg, "stacked_vlan_en", "Enable Stacked VLAN processing mode", 31, 1, 1, 1);
        ppmCreateRegisterField(abstacked_vlan_reg, "user_def_vlan_type", "User defined VLAN_TYPE field. When Stacked  VLAN is enabled, the first VLAN tag in a received  frame will only be accepted if the VLAN type field  is equal to this user defined VLAN_TYPE OR  equal to the standard VLAN type (0x8100). Note  that the second VLAN tag of a Stacked VLAN  packet will only be matched correctly if its  VLAN_TYPE field equals 0x8100.", 0, 16, 1, 1);
    }
    {
        registerHandle abtx_pfc_pause_reg = ppmCreateRegister(
            "ab_tx_pfc_pause",
            "Transmit PFC Pause Register",
            handles.bport1,
            0xc4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.tx_pfc_pause.value),
            True
        );

        ppmCreateRegisterField(abtx_pfc_pause_reg, "pauseq_sel", "If bit 17 of the network control register is written  with a one then for each entry equal to zero in the  Transmit PFC Pause Register[15:8], the PFC pause  frame's pause quantum field associated with that  entry will be taken from the transmit pause  quantum register. For each entry equal to one in  the Transmit PFC Pause Register [15:8], the pause  quantum associated with that entry will be zero.", 8, 8, 1, 1);
        ppmCreateRegisterField(abtx_pfc_pause_reg, "pri_en_vec_val", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abspec_addr1_mask_bot_reg = ppmCreateRegister(
            "ab_spec_addr1_mask_bot",
            "Specific Address Mask 1 Bottom [31:0]",
            handles.bport1,
            0xc8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.spec_addr1_mask_bot.value),
            True
        );

        ppmCreateRegisterField(abspec_addr1_mask_bot_reg, "mask_bits_top", "Setting a bit to one masks the corresponding bit in  the specific address 1 register", 0, 32, 1, 1);
    }
    {
        registerHandle abspec_addr1_mask_top_reg = ppmCreateRegister(
            "ab_spec_addr1_mask_top",
            "Specific Address Mask 1 Top [47:32]",
            handles.bport1,
            0xcc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.spec_addr1_mask_top.value),
            True
        );

        ppmCreateRegisterField(abspec_addr1_mask_top_reg, "mask_bits_top", "Setting a bit to one masks the corresponding bit in  the specific address 1 register", 0, 16, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_rx_ptp_uni",
            "PTP RX Unicast address (Not in TRM)",
            handles.bport1,
            0xd4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.rx_ptp_uni.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_tx_ptp_uni",
            "PTP TX Unicast address (Not in TRM)",
            handles.bport1,
            0xd8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.tx_ptp_uni.value),
            True
        );
    }
    {
        registerHandle abmodule_id_reg = ppmCreateRegister(
            "ab_module_id",
            "Module ID",
            handles.bport1,
            0xfc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.module_id.value),
            True
        );

        ppmCreateRegisterField(abmodule_id_reg, "module_id", "Module identification number - for the GEM, this  value is fixed at 0x0002.", 16, 16, 1, 0);
        ppmCreateRegisterField(abmodule_id_reg, "module_rev", 0, 0, 16, 1, 0);
    }
    {
        registerHandle aboctets_tx_bot_reg = ppmCreateRegister(
            "ab_octets_tx_bot",
            "Octets transmitted [31:0] (in frames without error)",
            handles.bport1,
            0x100,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.octets_tx_bot.value),
            True
        );

        ppmCreateRegisterField(aboctets_tx_bot_reg, "octets_tx_bot", "Transmitted octets in frame without errors [31:0]. The number of octets transmitted in valid frames  of any type. This counter is 48-bits, and is read  through two registers. This count does not  include octets from automatically generated  pause frames.", 0, 32, 1, 0);
    }
    {
        registerHandle aboctets_tx_top_reg = ppmCreateRegister(
            "ab_octets_tx_top",
            "Octets transmitted [47:32] (in frames without error)",
            handles.bport1,
            0x104,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.octets_tx_top.value),
            True
        );

        ppmCreateRegisterField(aboctets_tx_top_reg, "octets_tx_top", "Transmitted octets in frame without errors [47:32].  The number of octets transmitted in valid frames  of any type. This counter is 48-bits, and is read  through two registers. This count does not  include octets from automatically generated  pause frames.", 0, 16, 1, 0);
    }
    {
        registerHandle abframes_tx_reg = ppmCreateRegister(
            "ab_frames_tx",
            "Frames Transmitted",
            handles.bport1,
            0x108,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_tx.value),
            True
        );

        ppmCreateRegisterField(abframes_tx_reg, "frames_tx", "Frames transmitted without error. A 32 bit register counting the number of frames successfully transmitted, i.e., no under run and not too many retries. Excludes pause frames.", 0, 32, 1, 0);
    }
    {
        registerHandle abbroadcast_frames_tx_reg = ppmCreateRegister(
            "ab_broadcast_frames_tx",
            "Broadcast frames Tx",
            handles.bport1,
            0x10c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.broadcast_frames_tx.value),
            True
        );

        ppmCreateRegisterField(abbroadcast_frames_tx_reg, "broadcasr_frames_tx", "Broadcast frames transmitted without error. A 32 bit register counting the number of broadcast frames successfully transmitted without error, i.e., no under run and not too many retries. Excludes pause frames.", 0, 32, 1, 0);
    }
    {
        registerHandle abmulti_frames_tx_reg = ppmCreateRegister(
            "ab_multi_frames_tx",
            "Multicast frames Tx",
            handles.bport1,
            0x110,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.multi_frames_tx.value),
            True
        );

        ppmCreateRegisterField(abmulti_frames_tx_reg, "multi_frames_tx", "Multicast frames transmitted without error. A 32  bit register counting the number of multicast  frames successfully transmitted without error, i.e.,  no under run and not too many retries. Excludes  pause frames.", 0, 32, 1, 0);
    }
    {
        registerHandle abpause_frames_tx_reg = ppmCreateRegister(
            "ab_pause_frames_tx",
            "Pause frames Tx",
            handles.bport1,
            0x114,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.pause_frames_tx.value),
            True
        );

        ppmCreateRegisterField(abpause_frames_tx_reg, "pause_frames_tx", "Transmitted pause frames - a 16 bit register  counting the number of pause frames  transmitted. Only pause frames triggered by the  register interface or through the external pause  pins are counted as pause frames. Pause frames  received through the external FIFO interface are  counted in the frames transmitted counter.", 0, 16, 1, 0);
    }
    {
        registerHandle abframes_64b_tx_reg = ppmCreateRegister(
            "ab_frames_64b_tx",
            "Frames Tx, 64-byte length",
            handles.bport1,
            0x118,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_64b_tx.value),
            True
        );

        ppmCreateRegisterField(abframes_64b_tx_reg, "frames_64b_tx", "64 byte frames transmitted without error. A 32 bit  register counting the number of 64 byte frames  successfully transmitted without error, i.e., no  under run and not too many retries. Excludes  pause frames.", 0, 32, 1, 0);
    }
    {
        registerHandle abframes_65to127b_tx_reg = ppmCreateRegister(
            "ab_frames_65to127b_tx",
            "Frames Tx, 65 to 127-byte length",
            handles.bport1,
            0x11c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_65to127b_tx.value),
            True
        );

        ppmCreateRegisterField(abframes_65to127b_tx_reg, "frames_65to127b_tx", "65 to127 byte frames transmitted without error. A  32 bit register counting the number of 65 to127  byte frames successfully transmitted without  error, i.e., no under run and not too many retries.", 0, 32, 1, 0);
    }
    {
        registerHandle abframes_128to255b_tx_reg = ppmCreateRegister(
            "ab_frames_128to255b_tx",
            "Frames Tx, 128 to 255-byte length",
            handles.bport1,
            0x120,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_128to255b_tx.value),
            True
        );

        ppmCreateRegisterField(abframes_128to255b_tx_reg, "frames_128to255b_tx", "128 to 255 byte frames transmitted without error.  A 32 bit register counting the number of 128 to 255  byte frames successfully transmitted without  error, i.e., no under run and not too many retries.", 0, 32, 1, 0);
    }
    {
        registerHandle abframes_256to511b_tx_reg = ppmCreateRegister(
            "ab_frames_256to511b_tx",
            "Frames Tx, 256 to 511-byte length",
            handles.bport1,
            0x124,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_256to511b_tx.value),
            True
        );

        ppmCreateRegisterField(abframes_256to511b_tx_reg, "frames_256to511b_tx", "256 to 511 byte frames transmitted without error. A 32 bit register counting the number of 256 to 511 byte frames successfully transmitted without error, i.e., no under run and not too many retries. A 32 bit register counting the number of 128 to 255  byte frames successfully transmitted without  error, i.e., no under run and not too many retries.", 0, 32, 1, 0);
    }
    {
        registerHandle abframes_512to1023b_tx_reg = ppmCreateRegister(
            "ab_frames_512to1023b_tx",
            "Frames Tx, 512 to 1023-byte length",
            handles.bport1,
            0x128,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_512to1023b_tx.value),
            True
        );

        ppmCreateRegisterField(abframes_512to1023b_tx_reg, "frames_512to1023b_tx", "512 to 1023 byte frames transmitted without error.  A 32 bit register counting the number of 512 to  1023 byte frames successfully transmitted  without error, i.e., no under run and not too many  retries.", 0, 32, 1, 0);
    }
    {
        registerHandle abframes_1024to1518b_tx_reg = ppmCreateRegister(
            "ab_frames_1024to1518b_tx",
            "Frame Tx, 1024 to 1518-byte length",
            handles.bport1,
            0x12c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_1024to1518b_tx.value),
            True
        );

        ppmCreateRegisterField(abframes_1024to1518b_tx_reg, "frames_1023to11518b_tx", "1024 to 1518 byte frames transmitted without  error. A 32 bit register counting the number of  1024 to 1518 byte frames successfully transmitted  without error, i.e., no under run and not too many  retries.", 0, 32, 1, 0);
    }
    {
        ppmCreateRegister(
            "ab_frames_1519bplus_tx",
            "Frame Tx, 1519+byte length (Not in TRM)",
            handles.bport1,
            0x130,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_1519bplus_tx.value),
            True
        );
    }
    {
        registerHandle abtx_under_runs_reg = ppmCreateRegister(
            "ab_tx_under_runs",
            "Transmit under runs",
            handles.bport1,
            0x134,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.tx_under_runs.value),
            True
        );

        ppmCreateRegisterField(abtx_under_runs_reg, "tx_under_runs", "Transmit under runs - a 10 bit register counting  the number of frames not transmitted due to a  transmit under run. If this register is incremented  then no other statistics register is incremented.", 0, 10, 1, 0);
    }
    {
        registerHandle absingle_collisn_frames_reg = ppmCreateRegister(
            "ab_single_collisn_frames",
            "Single Collision Frames",
            handles.bport1,
            0x138,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.single_collisn_frames.value),
            True
        );

        ppmCreateRegisterField(absingle_collisn_frames_reg, "single_collisn", "Single collision frames - an 18 bit register counting  the number of frames experiencing a single  collision before being successfully transmitted,  i.e. no under run.", 0, 18, 1, 0);
    }
    {
        registerHandle abmulti_collisn_frames_reg = ppmCreateRegister(
            "ab_multi_collisn_frames",
            "Multiple Collision Frames",
            handles.bport1,
            0x13c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.multi_collisn_frames.value),
            True
        );

        ppmCreateRegisterField(abmulti_collisn_frames_reg, "multi_collisn", "Multiple collision frames - an 18 bit register  counting the number of frames experiencing  between two and fifteen collisions prior to being  successfully transmitted, i.e., no under run and  not too many retries.", 0, 18, 1, 0);
    }
    {
        registerHandle abexcessive_collisns_reg = ppmCreateRegister(
            "ab_excessive_collisns",
            "Excessive Collisions",
            handles.bport1,
            0x140,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.excessive_collisns.value),
            True
        );

        ppmCreateRegisterField(abexcessive_collisns_reg, "excessive_collisns", "Excessive collisions - a 10 bit register counting the number of frames that failed to be transmitted because they experienced 16 collisions.", 0, 10, 1, 0);
    }
    {
        registerHandle ablate_collisns_reg = ppmCreateRegister(
            "ab_late_collisns",
            "Late Collisions",
            handles.bport1,
            0x144,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.late_collisns.value),
            True
        );

        ppmCreateRegisterField(ablate_collisns_reg, "late_collisns", "Late collisions - a 10 bit register counting the number of late collision occurring after the slot time (512 bits) has expired. In 10/100 mode, late collisions are counted twice i.e., both as a collision and a late collision. In gigabit mode, a late collision causes the transmission to be aborted, thus the single and multi collision registers are not updated.", 0, 10, 1, 0);
    }
    {
        registerHandle abdeferred_tx_frames_reg = ppmCreateRegister(
            "ab_deferred_tx_frames",
            "Deferred Transmission Frames",
            handles.bport1,
            0x148,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.deferred_tx_frames.value),
            True
        );

        ppmCreateRegisterField(abdeferred_tx_frames_reg, "deferred_tx_frames", "Deferred transmission frames - an 18 bit register counting the number of frames experiencing deferral due to carrier sense being active on their first attempt at transmission. Frames involved in any collision are not counted nor are frames that experienced a transmit under run.", 0, 10, 1, 0);
    }
    {
        registerHandle abcarrier_sense_errs_reg = ppmCreateRegister(
            "ab_carrier_sense_errs",
            "Carrier Sense Errors.",
            handles.bport1,
            0x14c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.carrier_sense_errs.value),
            True
        );

        ppmCreateRegisterField(abcarrier_sense_errs_reg, "carrier_sense_errs", "Carrier sense errors - a 10 bit register counting the  number of frames transmitted where carrier sense  was not seen during transmission or where carrier  sense was deasserted after being asserted in a  transmit frame without collision (no under run).  Only incremented in half duplex mode. The only  effect of a carrier sense error is to increment this  register. The behavior of the other statistics  registers is unaffected by the detection of a carrier  sense error.", 0, 10, 1, 0);
    }
    {
        registerHandle aboctets_rx_bot_reg = ppmCreateRegister(
            "ab_octets_rx_bot",
            "Octets Received [31:0]",
            handles.bport1,
            0x150,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.octets_rx_bot.value),
            True
        );

        ppmCreateRegisterField(aboctets_rx_bot_reg, "octets_rx_bot", "Received octets in frame without errors [31:0]. The  number of octets received in valid frames of any  type. This counter is 48-bits and is read through  two registers. This count does not include octets  from pause frames, and is only incremented if the  frame is successfully filtered and copied to  memory.", 0, 32, 1, 0);
    }
    {
        registerHandle aboctets_rx_top_reg = ppmCreateRegister(
            "ab_octets_rx_top",
            "Octets Received [47:32]",
            handles.bport1,
            0x154,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.octets_rx_top.value),
            True
        );

        ppmCreateRegisterField(aboctets_rx_top_reg, "octets_rx_top", "Received octets in frame without errors [47:32].  The number of octets received in valid frames of  any type. This counter is 48-bits and is read  through two registers. This count does not  include octets from pause frames, and is only  incremented if the frame is successfully filtered  and copied to memory.", 0, 16, 1, 0);
    }
    {
        registerHandle abframes_rx_reg = ppmCreateRegister(
            "ab_frames_rx",
            "Frames Received",
            handles.bport1,
            0x158,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_rx.value),
            True
        );

        ppmCreateRegisterField(abframes_rx_reg, "frames_rx", "Frames received without error. A 32 bit register  counting the number of frames successfully  received. Excludes pause frames, and is only  incremented if the frame is successfully filtered  and copied to memory.", 0, 32, 1, 0);
    }
    {
        registerHandle abbdcast_frames_rx_reg = ppmCreateRegister(
            "ab_bdcast_frames_rx",
            "Broadcast Frames Rx",
            handles.bport1,
            0x15c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.bdcast_frames_rx.value),
            True
        );

        ppmCreateRegisterField(abbdcast_frames_rx_reg, "bdcast_frames_rx", "Broadcast frames received without error. A 32 bit  register counting the number of broadcast frames  successfully received without error. Excludes  pause frames, and is only incremented if the  frame is successfully filtered and copied to  memory.", 0, 32, 1, 0);
    }
    {
        registerHandle abmulti_frames_rx_reg = ppmCreateRegister(
            "ab_multi_frames_rx",
            "Multicast Frames Rx",
            handles.bport1,
            0x160,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.multi_frames_rx.value),
            True
        );

        ppmCreateRegisterField(abmulti_frames_rx_reg, "multi_frames_rx", "Multicast frames received without error. A 32 bit  register counting the number of multicast frames  successfully received without error. Excludes  pause frames, and is only incremented if the  frame is successfully filtered and copied to  memory.", 0, 32, 1, 0);
    }
    {
        registerHandle abpause_rx_reg = ppmCreateRegister(
            "ab_pause_rx",
            "Pause Frames Rx",
            handles.bport1,
            0x164,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.pause_rx.value),
            True
        );

        ppmCreateRegisterField(abpause_rx_reg, "pause_rx", "Received pause frames - a 16 bit register counting the number of pause frames received without error.", 0, 16, 1, 0);
    }
    {
        registerHandle abframes_64b_rx_reg = ppmCreateRegister(
            "ab_frames_64b_rx",
            "Frames Rx, 64-byte length",
            handles.bport1,
            0x168,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_64b_rx.value),
            True
        );

        ppmCreateRegisterField(abframes_64b_rx_reg, "frames_64b_rx", "64 byte frames received without error. A 32 bit register counting the number of 64 byte frames successfully received without error. Excludes pause frames, and is only incremented if the frame is successfully filtered and copied to memory.", 0, 32, 1, 0);
    }
    {
        registerHandle abframes_65to127b_rx_reg = ppmCreateRegister(
            "ab_frames_65to127b_rx",
            "Frames Rx, 65 to 127-byte length",
            handles.bport1,
            0x16c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_65to127b_rx.value),
            True
        );

        ppmCreateRegisterField(abframes_65to127b_rx_reg, "frames_65to127b_rx", "65 to 127 byte frames received without error. A 32 bit register counting the number of 65 to 127 byte frames successfully received without error. Excludes pause frames, and is only incremented if the frame is successfully filtered and copied to memory.", 0, 32, 1, 0);
    }
    {
        registerHandle abframes_128to255b_rx_reg = ppmCreateRegister(
            "ab_frames_128to255b_rx",
            "Frames Rx, 128 to 255-byte length",
            handles.bport1,
            0x170,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_128to255b_rx.value),
            True
        );

        ppmCreateRegisterField(abframes_128to255b_rx_reg, "frames_128to255b_rx", "128 to 255 byte frames received without error. A  32 bit register counting the number of 128 to 255  byte frames successfully received without error.  Excludes pause frames, and is only incremented if  the frame is successfully filtered and copied to  memory.", 0, 32, 1, 0);
    }
    {
        registerHandle abframes_256to511b_rx_reg = ppmCreateRegister(
            "ab_frames_256to511b_rx",
            "Frames Rx, 256 to 511-byte length",
            handles.bport1,
            0x174,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_256to511b_rx.value),
            True
        );

        ppmCreateRegisterField(abframes_256to511b_rx_reg, "frames_256to511b_rx", "256 to 511 byte frames received without error. A 32 bit register counting the number of 256 to 511 byte frames successfully transmitted without error. Excludes pause frames, and is only incremented if the frame is successfully filtered and copied to memory.", 0, 32, 1, 0);
    }
    {
        registerHandle abframes_512to1023b_rx_reg = ppmCreateRegister(
            "ab_frames_512to1023b_rx",
            "Frames Rx, 512 to 1023-byte length",
            handles.bport1,
            0x178,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_512to1023b_rx.value),
            True
        );

        ppmCreateRegisterField(abframes_512to1023b_rx_reg, "frames_512to1023b_rx", "512 to 1023 byte frames received without error. A  32 bit register counting the number of 512 to 1023  byte frames successfully received without error.  Excludes pause frames, and is only incremented if  the frame is successfully filtered and copied to  memory.", 0, 32, 1, 0);
    }
    {
        registerHandle abframes_1024to1518b_rx_reg = ppmCreateRegister(
            "ab_frames_1024to1518b_rx",
            "Frames Rx, 1024 to 1518-byte length",
            handles.bport1,
            0x17c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_1024to1518b_rx.value),
            True
        );

        ppmCreateRegisterField(abframes_1024to1518b_rx_reg, "frames_1023to11518b_rx", "1024 to 1518 byte frames received without error. A  32 bit register counting the number of 1024 to 1518  byte frames successfully received without error.  Excludes pause frames, and is only incremented if  the frame is successfully filtered and copied to  memory.", 0, 32, 1, 0);
    }
    {
        ppmCreateRegister(
            "ab_frames_1519bplus_rx",
            "Frames Rx, 1519+byte length (Not in TRM)",
            handles.bport1,
            0x180,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.frames_1519bplus_rx.value),
            True
        );
    }
    {
        registerHandle abundersz_rx_reg = ppmCreateRegister(
            "ab_undersz_rx",
            "Undersize frames received",
            handles.bport1,
            0x184,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.undersz_rx.value),
            True
        );

        ppmCreateRegisterField(abundersz_rx_reg, "undersz_rx", "Undersize frames received - a 10 bit register  counting the number of frames received less than  64 bytes in length (10/100 mode or gigabit mode,  full duplex) that do not have either a CRC error or  an alignment error.", 0, 10, 1, 0);
    }
    {
        registerHandle aboversz_rx_reg = ppmCreateRegister(
            "ab_oversz_rx",
            "Oversize frames received",
            handles.bport1,
            0x188,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.oversz_rx.value),
            True
        );

        ppmCreateRegisterField(aboversz_rx_reg, "oversz_rx", "Oversize frames received - a 10 bit register counting the number of frames received exceeding 1518 bytes (1536 bytes if bit 8 is set in network configuration register) in length but do not have either a CRC error, an alignment error nor a receive symbol error.", 0, 10, 1, 0);
    }
    {
        registerHandle abjab_rx_reg = ppmCreateRegister(
            "ab_jab_rx",
            "Jabbers received",
            handles.bport1,
            0x18c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.jab_rx.value),
            True
        );

        ppmCreateRegisterField(abjab_rx_reg, "jab_rx", "Jabbers received - a 10 bit register counting the number of frames received exceeding 1518 bytes (1536 if bit 8 set in network configuration register) in length and have either a CRC error, an alignment error or a receive symbol error.", 0, 10, 1, 0);
    }
    {
        registerHandle abfcs_errors_reg = ppmCreateRegister(
            "ab_fcs_errors",
            "Frame check sequence errors",
            handles.bport1,
            0x190,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.fcs_errors.value),
            True
        );

        ppmCreateRegisterField(abfcs_errors_reg, "fcs_erros", "Frame check sequence errors - a 10 bit register counting frames that are an integral number of bytes, have bad CRC and are between 64 and 1518 bytes in length. This register is also incremented if a symbol error is detected and the frame is of valid length and has an integral number of bytes. This register is incremented for a frame with bad FCS, regardless of whether it is copied to memory due to ignore FCS mode being enabled in bit 26 of the network configuration register.H524", 0, 10, 1, 0);
    }
    {
        registerHandle ablength_field_errors_reg = ppmCreateRegister(
            "ab_length_field_errors",
            "Length field frame errors",
            handles.bport1,
            0x194,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.length_field_errors.value),
            True
        );

        ppmCreateRegisterField(ablength_field_errors_reg, "length_field_errors", "Length field frame errors - this 10-bit register  counts the number of frames received that have a  measured length shorter than that extracted from  the length field (bytes 13 and 14). This condition is  only counted if the value of the length field is less  than 0x0600, the frame is not of excessive length  and checking is enabled through bit 16 of the  network configuration register.", 0, 10, 1, 0);
    }
    {
        registerHandle abrx_symbol_errors_reg = ppmCreateRegister(
            "ab_rx_symbol_errors",
            "Receive symbol errors",
            handles.bport1,
            0x198,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.rx_symbol_errors.value),
            True
        );

        ppmCreateRegisterField(abrx_symbol_errors_reg, "rx_symbol_errors", "Receive symbol errors - a 10-bit register counting  the number of frames that had rx_er asserted  during reception. For 10/100 mode symbol errors  are counted regardless of frame length checks. For  gigabit mode the frame must satisfy slot time  requirements in order to count a symbol error.", 0, 10, 1, 0);
    }
    {
        registerHandle abalign_errors_reg = ppmCreateRegister(
            "ab_align_errors",
            "Alignment errors",
            handles.bport1,
            0x19c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.align_errors.value),
            True
        );

        ppmCreateRegisterField(abalign_errors_reg, "align_errors", "Alignment errors - a 10 bit register counting  frames that are not an integral number of bytes  long and have bad CRC when their length is  truncated to an integral number of bytes and are  between 64 and 1518 bytes in length. This register  is also incremented if a symbol error is detected  and the frame is of valid length and does not have  an integral number of bytes.", 0, 10, 1, 0);
    }
    {
        registerHandle abrx_resource_errors_reg = ppmCreateRegister(
            "ab_rx_resource_errors",
            "Receive resource errors",
            handles.bport1,
            0x1a0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.rx_resource_errors.value),
            True
        );

        ppmCreateRegisterField(abrx_resource_errors_reg, "rx_resource_errors", "Receive resource errors - an 18 bit register  counting the number of frames that were  successfully received by the MAC (correct  address matched frame and adequate slot time)  but could not be copied to memory because no  receive buffer was available. This will be either  because the AHB bus was not granted in time or  because a hresp not OK was returned.", 0, 18, 1, 0);
    }
    {
        registerHandle abrx_overrun_errors_reg = ppmCreateRegister(
            "ab_rx_overrun_errors",
            "Receive overrun errors",
            handles.bport1,
            0x1a4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.rx_overrun_errors.value),
            True
        );

        ppmCreateRegisterField(abrx_overrun_errors_reg, "rx_overrun_errors", "Receive overruns - a 10 bit register counting the  number of frames that are address recognized but  were not copied to memory due to a receive  overrun.", 0, 10, 1, 0);
    }
    {
        registerHandle abip_hdr_csum_errors_reg = ppmCreateRegister(
            "ab_ip_hdr_csum_errors",
            "IP header checksum errors",
            handles.bport1,
            0x1a8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ip_hdr_csum_errors.value),
            True
        );

        ppmCreateRegisterField(abip_hdr_csum_errors_reg, "ip_hdr_csum_errors", "0 IP header checksum errors - an 8-bit register  counting the number of frames discarded due to  an incorrect IP header checksum, but are between  64 and 1518 bytes and do not have a CRC error, an  alignment error, nor a symbol error.", 0, 8, 1, 0);
    }
    {
        registerHandle abtcp_csum_errors_reg = ppmCreateRegister(
            "ab_tcp_csum_errors",
            "TCP checksum errors",
            handles.bport1,
            0x1ac,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.tcp_csum_errors.value),
            True
        );

        ppmCreateRegisterField(abtcp_csum_errors_reg, "tcp_csum_errors", "TCP checksum errors - an 8-bit register counting the number of frames discarded due to an incorrect TCP checksum, but are between 64 and 1518 bytes and do not have a CRC error, an alignment error, nor a symbol error.", 0, 8, 1, 0);
    }
    {
        registerHandle abudp_csum_errors_reg = ppmCreateRegister(
            "ab_udp_csum_errors",
            "UDP checksum error",
            handles.bport1,
            0x1b0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.udp_csum_errors.value),
            True
        );

        ppmCreateRegisterField(abudp_csum_errors_reg, "udp_csum_errors", "UDP checksum errors - an 8-bit register counting the number of frames discarded due to an incorrect UDP checksum, but are between 64 and 1518 bytes and do not have a CRC error, an alignment error, nor a symbol error.", 0, 8, 1, 0);
    }
    {
        registerHandle abtimer_strobe_s_reg = ppmCreateRegister(
            "ab_timer_strobe_s",
            "1588 timer sync strobe seconds",
            handles.bport1,
            0x1c8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.timer_strobe_s.value),
            True
        );

        ppmCreateRegisterField(abtimer_strobe_s_reg, "timer_strobe_s", "The value of the Timer Seconds register", 0, 32, 1, 0);
    }
    {
        registerHandle abtimer_strobe_ns_reg = ppmCreateRegister(
            "ab_timer_strobe_ns",
            "1588 timer sync strobe nanoseconds",
            handles.bport1,
            0x1cc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.timer_strobe_ns.value),
            True
        );

        ppmCreateRegisterField(abtimer_strobe_ns_reg, "ns_reg_val", "The value of the Timer Nanoseconds register", 0, 30, 1, 1);
    }
    {
        registerHandle abtimer_s_reg = ppmCreateRegister(
            "ab_timer_s",
            "1588 timer seconds",
            handles.bport1,
            0x1d0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.timer_s.value),
            True
        );

        ppmCreateRegisterField(abtimer_s_reg, "timer_s", "Timer count in seconds. This register is writeable. It increments by one when the 1588 nanoseconds counter counts to one second. It may also be incremented when the timer adjust register is written.", 0, 32, 1, 1);
    }
    {
        registerHandle abtimer_ns_reg = ppmCreateRegister(
            "ab_timer_ns",
            "1588 timer nanoseconds",
            handles.bport1,
            0x1d4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.timer_ns.value),
            True
        );

        ppmCreateRegisterField(abtimer_ns_reg, "timer_ct_ns", "Timer count in nanoseconds. This register is writeable. It can also be adjusted by writes to the 1588 timer adjust register. It increments by the value of the 1588 timer increment register each clock cycle.", 0, 30, 1, 1);
    }
    {
        registerHandle abtimer_adjust_reg = ppmCreateRegister(
            "ab_timer_adjust",
            "1588 timer adjust",
            handles.bport1,
            0x1d8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.timer_adjust.value),
            True
        );

        ppmCreateRegisterField(abtimer_adjust_reg, "add_subn", "Write as one to subtract from the 1588 timer. Write  as zero to add to it.", 31, 1, 0, 1);
        ppmCreateRegisterField(abtimer_adjust_reg, "ns_delta", "The number of nanoseconds to increment or decrement the 1588 timer nanoseconds register. If necessary, the 1588 seconds register will be incremented or decremented.", 0, 30, 0, 1);
    }
    {
        registerHandle abtimer_incr_reg = ppmCreateRegister(
            "ab_timer_incr",
            "1588 timer increment",
            handles.bport1,
            0x1dc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.timer_incr.value),
            True
        );

        ppmCreateRegisterField(abtimer_incr_reg, "incr_b4_alt", "The number of increments after which the  alternative increment is used.", 16, 8, 1, 1);
        ppmCreateRegisterField(abtimer_incr_reg, "alt_ct_ns_delta", "Alternative count of nanoseconds by which the  1588 timer nanoseconds register will be  incremented each clock cycle.", 8, 8, 1, 1);
        ppmCreateRegisterField(abtimer_incr_reg, "ns_delta", "A count of nanoseconds by which the 1588 timer nanoseconds register will be incremented each clock cycle.", 0, 8, 1, 1);
    }
    {
        registerHandle abptp_tx_s_reg = ppmCreateRegister(
            "ab_ptp_tx_s",
            "PTP event frame transmitted seconds",
            handles.bport1,
            0x1e0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ptp_tx_s.value),
            True
        );

        ppmCreateRegisterField(abptp_tx_s_reg, "ptp_tx_s", "The register is updated with the value that the  1588 timer seconds register held when the SFD of  a PTP transmit primary event crosses the MII  interface. The actual update occurs when the  GEM recognizes the frame as a PTP sync or  delay_req frame. An interrupt is issued when the  register is updated.", 0, 32, 1, 0);
    }
    {
        registerHandle abptp_tx_ns_reg = ppmCreateRegister(
            "ab_ptp_tx_ns",
            "PTP event frame transmitted nanoseconds",
            handles.bport1,
            0x1e4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ptp_tx_ns.value),
            True
        );

        ppmCreateRegisterField(abptp_tx_ns_reg, "ns_reg_val", "The register is updated with the value that the 1588 timer nanoseconds register held when the SFD of a PTP transmit primary event crosses the MII interface. The actual update occurs when the GEM recognizes the frame as a PTP sync or delay_req frame. An interrupt is issued when the register is updated.", 0, 30, 1, 0);
    }
    {
        registerHandle abptp_rx_s_reg = ppmCreateRegister(
            "ab_ptp_rx_s",
            "PTP event frame received seconds",
            handles.bport1,
            0x1e8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ptp_rx_s.value),
            True
        );

        ppmCreateRegisterField(abptp_rx_s_reg, "ptp_rx_s", "The register is updated with the value that the 1588 timer seconds register held when the SFD of a PTP receive primary event crosses the MII interface. The actual update occurs when the GEM recognizes the frame as a PTP pdelay_req or pdelay_resp frame. An interrupt is issued when the register is updated.", 0, 32, 1, 0);
    }
    {
        registerHandle abptp_rx_ns_reg = ppmCreateRegister(
            "ab_ptp_rx_ns",
            "PTP event frame received nanoseconds.",
            handles.bport1,
            0x1ec,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ptp_rx_ns.value),
            True
        );

        ppmCreateRegisterField(abptp_rx_ns_reg, "ns_reg_val", "The register is updated with the value that the 1588 timer nanoseconds register held when the SFD of a PTP receive primary event crosses the MII interface. The actual update occurs when the GEM recognizes the frame as a PTP sync or delay_req frame. An interrupt is issued when the register is updated.", 0, 30, 1, 0);
    }
    {
        registerHandle abptp_peer_tx_s_reg = ppmCreateRegister(
            "ab_ptp_peer_tx_s",
            "PTP peer event frame transmitted seconds",
            handles.bport1,
            0x1f0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ptp_peer_tx_s.value),
            True
        );

        ppmCreateRegisterField(abptp_peer_tx_s_reg, "ptp_peer_tx_s", "The register is updated with the value that the 1588 timer seconds register held when the SFD of a PTP receive peer event crosses the MII interface. The actual update occurs when the GEM recognizes the frame as a PTP pdelay_req or pdelay_resp frame. An interrupt is issued when the register is updated.", 0, 32, 1, 0);
    }
    {
        registerHandle abptp_peer_tx_ns_reg = ppmCreateRegister(
            "ab_ptp_peer_tx_ns",
            "PTP peer event frame transmitted nanoseconds",
            handles.bport1,
            0x1f4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ptp_peer_tx_ns.value),
            True
        );

        ppmCreateRegisterField(abptp_peer_tx_ns_reg, "ns_reg_val", "The register is updated with the value that the  1588 timer nanoseconds register held when the  SFD of a PTP transmit peer event crosses the MII  interface. The actual update occurs when the  GEM recognizes the frame as a PTP pdelay_req or  pdelay_resp frame. An interrupt is issued when  the register is updated.", 0, 30, 1, 0);
    }
    {
        registerHandle abptp_peer_rx_s_reg = ppmCreateRegister(
            "ab_ptp_peer_rx_s",
            "PTP peer event frame received seconds",
            handles.bport1,
            0x1f8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ptp_peer_rx_s.value),
            True
        );

        ppmCreateRegisterField(abptp_peer_rx_s_reg, "ptp_peer_rx_s", "The register is updated with the value that the  1588 timer seconds register held when the SFD of  a PTP receive peer event crosses the MII interface.  The actual update occurs when the GEM  recognizes the frame as a PTP pdelay_req or  pdelay_resp frame. An interrupt is issued when  the register is updated.", 0, 32, 1, 0);
    }
    {
        registerHandle abptp_peer_rx_ns_reg = ppmCreateRegister(
            "ab_ptp_peer_rx_ns",
            "PTP peer event frame received nanoseconds.",
            handles.bport1,
            0x1fc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ptp_peer_rx_ns.value),
            True
        );

        ppmCreateRegisterField(abptp_peer_rx_ns_reg, "ns_reg_val", "The register is updated with the value that the  1588 timer nanoseconds register held when the  SFD of a PTP receive peer event crosses the MII  interface. The actual update occurs when the  GEM recognizes the frame as a PTP pdelay_req or  pdelay_resp frame. An interrupt is issued when  the register is updated.", 0, 30, 1, 0);
    }
    {
        ppmCreateRegister(
            "ab_design_cfg1",
            "Design Configuration 1 (Not in TRM)",
            handles.bport1,
            0x280,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.design_cfg1.value),
            True
        );
    }
    {
        registerHandle abdesign_cfg2_reg = ppmCreateRegister(
            "ab_design_cfg2",
            "Design Configuration 2",
            handles.bport1,
            0x284,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.design_cfg2.value),
            True
        );

        ppmCreateRegisterField(abdesign_cfg2_reg, "gem_tx_pbuf_addr", "Takes the value of the `gem_tx_pbuf_addr  DEFINE. Max address bits for Tx packet buffer  (10-bits for maximum 4 kB buffer). Buffer size for  Tx packet buffer mode will be 4kB. This will allow one standard packet to be received  while another is transferred to system memory by  the DMA interface.", 26, 4, 1, 0);
        ppmCreateRegisterField(abdesign_cfg2_reg, "gem_rx_pbuf_addr", "Takes the value of the `gem_rx_pbuf_addr  DEFINE. Max address bits for Rx packet buffer  (10-bits for maximum 4 kB buffer). Buffer size for  Rx packet buffer mode will be 4kB. This will allow one standard packet to be received  while another is transferred to system memory by  the DMA interface.", 22, 4, 1, 0);
        ppmCreateRegisterField(abdesign_cfg2_reg, "gem_tx_pkt_buffer", "Takes the value of the `gem_tx_pkt_buffer DEFINE. Defined for Zynq. Includes the transmitter packet buffer", 21, 1, 1, 0);
        ppmCreateRegisterField(abdesign_cfg2_reg, "gem_rx_pkt_buffer", "Takes the value of the `gem_rx_pkt_buffer  DEFINE. Defined for Zynq. Includes the receiver  packet buffer.", 20, 1, 1, 0);
        ppmCreateRegisterField(abdesign_cfg2_reg, "gem_hprot_value", "Takes the value of the `gem_hprot_value DEFINE.  For Zynq, set the fixed AHB HPROT value used  during transfers.", 16, 4, 1, 0);
        ppmCreateRegisterField(abdesign_cfg2_reg, "gem_jumbo_max_length", "Takes the value of the `gem_jumbo_max_length DEFINE. Maximum length of jumbo frames accepted by receiver. This is set to the size of the smallest of the two packet buffer, minus a margin for packet headers. However, Zynq will not support jumbo frames.", 0, 16, 1, 0);
    }
    {
        registerHandle abdesign_cfg3_reg = ppmCreateRegister(
            "ab_design_cfg3",
            "Design Configuration 3",
            handles.bport1,
            0x288,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.design_cfg3.value),
            True
        );

        ppmCreateRegisterField(abdesign_cfg3_reg, "gem_rx_base2_fifo_siz", "Takes the value of the `gem_rx_base2_fifo_size  DEFINE. Base-2 equivalent of `gem_rx_fifo_size", 16, 16, 1, 0);
        ppmCreateRegisterField(abdesign_cfg3_reg, "gem_rx_fifo_size", "Takes the value of the `gem_rx_fifo_size DEFINE.  Set the size of the small Rx FIFO for grant latency.  Extended to 16 deep to allow buffering of 64 byte  maximum AHB burst size in Zynq.", 0, 16, 1, 0);
    }
    {
        registerHandle abdesign_cfg4_reg = ppmCreateRegister(
            "ab_design_cfg4",
            "Design Configuration 4",
            handles.bport1,
            0x28c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.design_cfg4.value),
            True
        );

        ppmCreateRegisterField(abdesign_cfg4_reg, "gem_tx_base2_fifo_size", "Takes the value of the `gem_tx_base2_fifo_size  DEFINE. Base-2 equivalent of `gem_tx_fifo_size.", 16, 16, 1, 0);
        ppmCreateRegisterField(abdesign_cfg4_reg, "gem_tx_fifo_size", "Takes the value of the `gem_tx_fifo_size DEFINE. Set the size of the small TX FIFO for grant latency", 0, 16, 1, 0);
    }
    {
        registerHandle abdesign_cfg5_reg = ppmCreateRegister(
            "ab_design_cfg5",
            "Design Configuration 5",
            handles.bport1,
            0x290,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.design_cfg5.value),
            True
        );

        ppmCreateRegisterField(abdesign_cfg5_reg, "gem_tsu_clk", "Takes the value of the `gem_tsu_clk DEFINE.  Undefined in Zynq. 1588 Time Stamp Unit clock  sourced from pclk rather than independent  tsu_clk.", 28, 1, 1, 0);
        ppmCreateRegisterField(abdesign_cfg5_reg, "gem_rx_buffer_length_", "Takes the value of the `gem_rx_buffer_length_def  DEFINE. Set the default buffer length used by Rx  DMA to 128 bytes.", 20, 8, 1, 0);
        ppmCreateRegisterField(abdesign_cfg5_reg, "gem_tx_pbuf_size_def", "Takes the value of the `gem_tx_pbuf_size_def  DEFINE. Full 4 kB Tx packet buffer size -  dedicated memory resource in Zynq.", 19, 1, 1, 0);
        ppmCreateRegisterField(abdesign_cfg5_reg, "gem_rx_pbuf_size_def", "Takes the value of the `gem_rx_pbuf_size_def DEFINE. Full 4 kB Rx packet buffer size - dedicated memory resource in Zynq.", 17, 2, 1, 0);
        ppmCreateRegisterField(abdesign_cfg5_reg, "gem_endian_swap_def", "Takes the value of the `gem_endian_swap_def  DEFINE. Set to big endian data, little endian  management descriptors in Zynq.", 15, 2, 1, 0);
        ppmCreateRegisterField(abdesign_cfg5_reg, "gem_mdc_clock_div", "Takes the value of the `gem_mdc_clock_div  DEFINE. Set default MDC clock divisor (can still  be programmed) in Zynq.", 12, 3, 1, 0);
        ppmCreateRegisterField(abdesign_cfg5_reg, "gem_dma_bus_width", "Takes the value of the `gem_dma_bus_width_def  DEFINE. Limit to 32-bit AHB bus in Zynq.", 10, 2, 1, 0);
        ppmCreateRegisterField(abdesign_cfg5_reg, "gem_phy_ident", "Takes the value of the `gem_phy_ident DEFINE.  Undefined in Zynq. Only used in PCS.", 9, 1, 1, 0);
        ppmCreateRegisterField(abdesign_cfg5_reg, "gem_tsu", "Takes the value of the `gem_tsu DEFINE. Defined  in Zynq. Include support for 1588 Time Stamp  Unit.", 8, 1, 1, 0);
        ppmCreateRegisterField(abdesign_cfg5_reg, "gem_tx_fifo_cnt_width", "Takes the value of the `gem_tx_fifo_cnt_width  DEFINE. Width for `gem_tx_fifo_size", 4, 4, 1, 0);
        ppmCreateRegisterField(abdesign_cfg5_reg, "gem_rx_fifo_cnt_width", "Takes the value of the `gem_rx_fifo_cnt_width  DEFINE. Width for `gem_rx_fifo_size.", 0, 4, 1, 0);
    }
    {
        ppmCreateRegister(
            "ab_design_cfg6",
            "Design Configuration 6 (Not in TRM)",
            handles.bport1,
            0x294,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.design_cfg6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_tx_bd_cntrl",
            "TX descriptor control (Not in TRM)",
            handles.bport1,
            0x4cc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.tx_bd_cntrl.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_rx_bd_cntrl",
            "RX descriptor control (Not in TRM)",
            handles.bport1,
            0x4d0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.rx_bd_cntrl.value),
            True
        );
    }

    {
        ppmCreateRegister(
            "ab_MII_BMCR",
            "Basic mode control register",
            handles.phyport,
            0x0,
            2,
            read_16,
            write_16,
            view16,
            &(phyport_ab_data.MII_BMCR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_BMSR",
            "Basic mode status register",
            handles.phyport,
            0x2,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_BMSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_PHYSID1",
            "PHYS ID 1",
            handles.phyport,
            0x4,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_PHYSID1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_PHYSID2",
            "PHYS ID 2",
            handles.phyport,
            0x6,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_PHYSID2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_ADVERTISE",
            "Advertisement control reg",
            handles.phyport,
            0x8,
            2,
            read_16,
            write_16,
            view16,
            &(phyport_ab_data.MII_ADVERTISE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_LPA",
            "Link partner ability reg",
            handles.phyport,
            0xa,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_LPA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_EXPANSION",
            "Expansion register",
            handles.phyport,
            0xc,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_EXPANSION.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_DUMMY1",
            "Dummy",
            handles.phyport,
            0xe,
            2,
            read_16,
            write_16,
            view16,
            &(phyport_ab_data.MII_DUMMY1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_DUMMY2",
            "Dummy",
            handles.phyport,
            0x10,
            2,
            read_16,
            write_16,
            view16,
            &(phyport_ab_data.MII_DUMMY2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_CTRL1000",
            "1000BASE-T control",
            handles.phyport,
            0x12,
            2,
            read_16,
            write_16,
            view16,
            &(phyport_ab_data.MII_CTRL1000.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_STAT1000",
            "1000BASE-T status",
            handles.phyport,
            0x14,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_STAT1000.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_DUMMY3",
            "Dummy",
            handles.phyport,
            0x16,
            2,
            read_16,
            write_16,
            view16,
            &(phyport_ab_data.MII_DUMMY3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_DUMMY4",
            "Dummy",
            handles.phyport,
            0x18,
            2,
            read_16,
            write_16,
            view16,
            &(phyport_ab_data.MII_DUMMY4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_MMD_CTRL",
            "MMD Access Control Register",
            handles.phyport,
            0x1a,
            2,
            read_16,
            write_16,
            view16,
            &(phyport_ab_data.MII_MMD_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_MMD_DATA",
            "MMD Access Data Register",
            handles.phyport,
            0x1c,
            2,
            read_16,
            write_16,
            view16,
            &(phyport_ab_data.MII_MMD_DATA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_ESTATUS",
            "Extended Status",
            handles.phyport,
            0x1e,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_ESTATUS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_DUMMY5",
            "Dummy",
            handles.phyport,
            0x20,
            2,
            read_16,
            write_16,
            view16,
            &(phyport_ab_data.MII_DUMMY5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_STS",
            "Status",
            handles.phyport,
            0x22,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_STS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_DCOUNTER",
            "Disconnect counter",
            handles.phyport,
            0x24,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_DCOUNTER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_FCSCOUNTER",
            "False carrier counter",
            handles.phyport,
            0x26,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_FCSCOUNTER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_NWAYTEST",
            "N-way auto-neg test reg",
            handles.phyport,
            0x28,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_NWAYTEST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_RERRCOUNTER",
            "Receive error counter",
            handles.phyport,
            0x2a,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_RERRCOUNTER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_SREVISION",
            "Silicon revision",
            handles.phyport,
            0x2c,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_SREVISION.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_LBRERROR",
            "Lpback, rx, bypass error",
            handles.phyport,
            0x30,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_LBRERROR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_PHYADDR",
            "PHY address",
            handles.phyport,
            0x32,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_PHYADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_TPISTATUS",
            "TPI status for 10mbps",
            handles.phyport,
            0x36,
            2,
            read_16,
            0,
            view16,
            &(phyport_ab_data.MII_TPISTATUS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MII_NCONFIG",
            "Network interface config",
            handles.phyport,
            0x38,
            2,
            read_16,
            write_16,
            view16,
            &(phyport_ab_data.MII_NCONFIG.value),
            True
        );
    }

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.bport2 = ppmOpenAddressSpace("bport2");
    if (!handles.bport2) {
        bhmMessage("E", "PPM_MPNC", "Could not connect port 'bport2'");
    }
}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        phyport_ab_data.MII_NCONFIG.value = (Uns16)(phyport_ab_data.MII_NCONFIG.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_TPISTATUS.value = (Uns16)(phyport_ab_data.MII_TPISTATUS.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_PHYADDR.value = (Uns16)(phyport_ab_data.MII_PHYADDR.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_LBRERROR.value = (Uns16)(phyport_ab_data.MII_LBRERROR.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_SREVISION.value = (Uns16)(phyport_ab_data.MII_SREVISION.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_RERRCOUNTER.value = (Uns16)(phyport_ab_data.MII_RERRCOUNTER.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_NWAYTEST.value = (Uns16)(phyport_ab_data.MII_NWAYTEST.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_FCSCOUNTER.value = (Uns16)(phyport_ab_data.MII_FCSCOUNTER.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_DCOUNTER.value = (Uns16)(phyport_ab_data.MII_DCOUNTER.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_STS.value = (Uns16)(phyport_ab_data.MII_STS.value & ~(0xffff)) | ((0xffff) & (0x8000));
        phyport_ab_data.MII_DUMMY5.value = (Uns16)(phyport_ab_data.MII_DUMMY5.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_ESTATUS.value = (Uns16)(phyport_ab_data.MII_ESTATUS.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_MMD_DATA.value = (Uns16)(phyport_ab_data.MII_MMD_DATA.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_MMD_CTRL.value = (Uns16)(phyport_ab_data.MII_MMD_CTRL.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_DUMMY4.value = (Uns16)(phyport_ab_data.MII_DUMMY4.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_DUMMY3.value = (Uns16)(phyport_ab_data.MII_DUMMY3.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_STAT1000.value = (Uns16)(phyport_ab_data.MII_STAT1000.value & ~(0xffff)) | ((0xffff) & (0x3C00));
        phyport_ab_data.MII_CTRL1000.value = (Uns16)(phyport_ab_data.MII_CTRL1000.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_DUMMY2.value = (Uns16)(phyport_ab_data.MII_DUMMY2.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_DUMMY1.value = (Uns16)(phyport_ab_data.MII_DUMMY1.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_EXPANSION.value = (Uns16)(phyport_ab_data.MII_EXPANSION.value & ~(0xffff)) | ((0xffff) & (0x0000));
        phyport_ab_data.MII_LPA.value = (Uns16)(phyport_ab_data.MII_LPA.value & ~(0xffff)) | ((0xffff) & (0x0FFF));
        phyport_ab_data.MII_ADVERTISE.value = (Uns16)(phyport_ab_data.MII_ADVERTISE.value & ~(0xffff)) | ((0xffff) & (0x01E1));
        phyport_ab_data.MII_PHYSID2.value = (Uns16)(phyport_ab_data.MII_PHYSID2.value & ~(0xffff)) | ((0xffff) & (0xa201));
        phyport_ab_data.MII_PHYSID1.value = (Uns16)(phyport_ab_data.MII_PHYSID1.value & ~(0xffff)) | ((0xffff) & (0x2000));
        phyport_ab_data.MII_BMSR.value = (Uns16)(phyport_ab_data.MII_BMSR.value & ~(0xffff)) | ((0xffff) & (0xFF2C));
        phyport_ab_data.MII_BMCR.value = (Uns16)(phyport_ab_data.MII_BMCR.value & ~(0xffff)) | ((0xffff) & (0x0000));
        bport1_ab_data.rx_bd_cntrl.value = (Uns32)(bport1_ab_data.rx_bd_cntrl.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.tx_bd_cntrl.value = (Uns32)(bport1_ab_data.tx_bd_cntrl.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.design_cfg6.value = (Uns32)(bport1_ab_data.design_cfg6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.design_cfg5.value = (Uns32)(bport1_ab_data.design_cfg5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00572045));
        bport1_ab_data.design_cfg4.value = (Uns32)(bport1_ab_data.design_cfg4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.design_cfg3.value = (Uns32)(bport1_ab_data.design_cfg3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.design_cfg2.value = (Uns32)(bport1_ab_data.design_cfg2.value & ~(0xffffffff)) | ((0xffffffff) & (0x2A813FFF));
        bport1_ab_data.design_cfg1.value = (Uns32)(bport1_ab_data.design_cfg1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ptp_peer_rx_ns.value = (Uns32)(bport1_ab_data.ptp_peer_rx_ns.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ptp_peer_rx_s.value = (Uns32)(bport1_ab_data.ptp_peer_rx_s.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ptp_peer_tx_ns.value = (Uns32)(bport1_ab_data.ptp_peer_tx_ns.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ptp_peer_tx_s.value = (Uns32)(bport1_ab_data.ptp_peer_tx_s.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ptp_rx_ns.value = (Uns32)(bport1_ab_data.ptp_rx_ns.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ptp_rx_s.value = (Uns32)(bport1_ab_data.ptp_rx_s.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ptp_tx_ns.value = (Uns32)(bport1_ab_data.ptp_tx_ns.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ptp_tx_s.value = (Uns32)(bport1_ab_data.ptp_tx_s.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.timer_incr.value = (Uns32)(bport1_ab_data.timer_incr.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.timer_adjust.value = (Uns32)(bport1_ab_data.timer_adjust.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.timer_ns.value = (Uns32)(bport1_ab_data.timer_ns.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.timer_s.value = (Uns32)(bport1_ab_data.timer_s.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.timer_strobe_ns.value = (Uns32)(bport1_ab_data.timer_strobe_ns.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.timer_strobe_s.value = (Uns32)(bport1_ab_data.timer_strobe_s.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.udp_csum_errors.value = (Uns32)(bport1_ab_data.udp_csum_errors.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.tcp_csum_errors.value = (Uns32)(bport1_ab_data.tcp_csum_errors.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ip_hdr_csum_errors.value = (Uns32)(bport1_ab_data.ip_hdr_csum_errors.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.rx_overrun_errors.value = (Uns32)(bport1_ab_data.rx_overrun_errors.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.rx_resource_errors.value = (Uns32)(bport1_ab_data.rx_resource_errors.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.align_errors.value = (Uns32)(bport1_ab_data.align_errors.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.rx_symbol_errors.value = (Uns32)(bport1_ab_data.rx_symbol_errors.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.length_field_errors.value = (Uns32)(bport1_ab_data.length_field_errors.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.fcs_errors.value = (Uns32)(bport1_ab_data.fcs_errors.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.jab_rx.value = (Uns32)(bport1_ab_data.jab_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.oversz_rx.value = (Uns32)(bport1_ab_data.oversz_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.undersz_rx.value = (Uns32)(bport1_ab_data.undersz_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_1519bplus_rx.value = (Uns32)(bport1_ab_data.frames_1519bplus_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_1024to1518b_rx.value = (Uns32)(bport1_ab_data.frames_1024to1518b_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_512to1023b_rx.value = (Uns32)(bport1_ab_data.frames_512to1023b_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_256to511b_rx.value = (Uns32)(bport1_ab_data.frames_256to511b_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_128to255b_rx.value = (Uns32)(bport1_ab_data.frames_128to255b_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_65to127b_rx.value = (Uns32)(bport1_ab_data.frames_65to127b_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_64b_rx.value = (Uns32)(bport1_ab_data.frames_64b_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.pause_rx.value = (Uns32)(bport1_ab_data.pause_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.multi_frames_rx.value = (Uns32)(bport1_ab_data.multi_frames_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.bdcast_frames_rx.value = (Uns32)(bport1_ab_data.bdcast_frames_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_rx.value = (Uns32)(bport1_ab_data.frames_rx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.octets_rx_top.value = (Uns32)(bport1_ab_data.octets_rx_top.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.octets_rx_bot.value = (Uns32)(bport1_ab_data.octets_rx_bot.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.carrier_sense_errs.value = (Uns32)(bport1_ab_data.carrier_sense_errs.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.deferred_tx_frames.value = (Uns32)(bport1_ab_data.deferred_tx_frames.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.late_collisns.value = (Uns32)(bport1_ab_data.late_collisns.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.excessive_collisns.value = (Uns32)(bport1_ab_data.excessive_collisns.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.multi_collisn_frames.value = (Uns32)(bport1_ab_data.multi_collisn_frames.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.single_collisn_frames.value = (Uns32)(bport1_ab_data.single_collisn_frames.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.tx_under_runs.value = (Uns32)(bport1_ab_data.tx_under_runs.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_1519bplus_tx.value = (Uns32)(bport1_ab_data.frames_1519bplus_tx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_1024to1518b_tx.value = (Uns32)(bport1_ab_data.frames_1024to1518b_tx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_512to1023b_tx.value = (Uns32)(bport1_ab_data.frames_512to1023b_tx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_256to511b_tx.value = (Uns32)(bport1_ab_data.frames_256to511b_tx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_128to255b_tx.value = (Uns32)(bport1_ab_data.frames_128to255b_tx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_65to127b_tx.value = (Uns32)(bport1_ab_data.frames_65to127b_tx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_64b_tx.value = (Uns32)(bport1_ab_data.frames_64b_tx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.pause_frames_tx.value = (Uns32)(bport1_ab_data.pause_frames_tx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.multi_frames_tx.value = (Uns32)(bport1_ab_data.multi_frames_tx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.broadcast_frames_tx.value = (Uns32)(bport1_ab_data.broadcast_frames_tx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.frames_tx.value = (Uns32)(bport1_ab_data.frames_tx.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.octets_tx_top.value = (Uns32)(bport1_ab_data.octets_tx_top.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.octets_tx_bot.value = (Uns32)(bport1_ab_data.octets_tx_bot.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.module_id.value = (Uns32)(bport1_ab_data.module_id.value & ~(0xffffffff)) | ((0xffffffff) & (0x00020118));
        bport1_ab_data.tx_ptp_uni.value = (Uns32)(bport1_ab_data.tx_ptp_uni.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.rx_ptp_uni.value = (Uns32)(bport1_ab_data.rx_ptp_uni.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.spec_addr1_mask_top.value = (Uns32)(bport1_ab_data.spec_addr1_mask_top.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.spec_addr1_mask_bot.value = (Uns32)(bport1_ab_data.spec_addr1_mask_bot.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.tx_pfc_pause.value = (Uns32)(bport1_ab_data.tx_pfc_pause.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.stacked_vlan.value = (Uns32)(bport1_ab_data.stacked_vlan.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ipg_stretch.value = (Uns32)(bport1_ab_data.ipg_stretch.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.wake_on_lan.value = (Uns32)(bport1_ab_data.wake_on_lan.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.type_id_match4.value = (Uns32)(bport1_ab_data.type_id_match4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.type_id_match3.value = (Uns32)(bport1_ab_data.type_id_match3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.type_id_match2.value = (Uns32)(bport1_ab_data.type_id_match2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.type_id_match1.value = (Uns32)(bport1_ab_data.type_id_match1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.spec_addr4_top.value = (Uns32)(bport1_ab_data.spec_addr4_top.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.spec_addr4_bot.value = (Uns32)(bport1_ab_data.spec_addr4_bot.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.spec_addr3_top.value = (Uns32)(bport1_ab_data.spec_addr3_top.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.spec_addr3_bot.value = (Uns32)(bport1_ab_data.spec_addr3_bot.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.spec_addr2_top.value = (Uns32)(bport1_ab_data.spec_addr2_top.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.spec_addr2_bot.value = (Uns32)(bport1_ab_data.spec_addr2_bot.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.spec_addr1_top.value = (Uns32)(bport1_ab_data.spec_addr1_top.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.spec_addr1_bot.value = (Uns32)(bport1_ab_data.spec_addr1_bot.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.hash_top.value = (Uns32)(bport1_ab_data.hash_top.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.hash_bot.value = (Uns32)(bport1_ab_data.hash_bot.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.gem_jml.value = (Uns32)(bport1_ab_data.gem_jml.value & ~(0xffffffff)) | ((0xffffffff) & (0x000005EE));
        bport1_ab_data.tx_pauseq.value = (Uns32)(bport1_ab_data.tx_pauseq.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000FFFF));
        bport1_ab_data.rx_pauseq.value = (Uns32)(bport1_ab_data.rx_pauseq.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_maint.value = (Uns32)(bport1_ab_data.phy_maint.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.intr_mask.value = (Uns32)(bport1_ab_data.intr_mask.value & ~(0xffffffff)) | ((0xffffffff) & (0x0001FFFF));
        bport1_ab_data.intr_dis.value = (Uns32)(bport1_ab_data.intr_dis.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.intr_en.value = (Uns32)(bport1_ab_data.intr_en.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.intr_status.value = (Uns32)(bport1_ab_data.intr_status.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.rx_status.value = (Uns32)(bport1_ab_data.rx_status.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.tx_qbar.value = (Uns32)(bport1_ab_data.tx_qbar.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.rx_qbar.value = (Uns32)(bport1_ab_data.rx_qbar.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.tx_status.value = (Uns32)(bport1_ab_data.tx_status.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.dma_cfg.value = (Uns32)(bport1_ab_data.dma_cfg.value & ~(0xffffffff)) | ((0xffffffff) & (0x00020784));
        bport1_ab_data.user_io.value = (Uns32)(bport1_ab_data.user_io.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.net_status.value = (Uns32)(bport1_ab_data.net_status.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000004));
        bport1_ab_data.net_cfg.value = (Uns32)(bport1_ab_data.net_cfg.value & ~(0xffffffff)) | ((0xffffffff) & (0x00080000));
        bport1_ab_data.net_ctrl.value = (Uns32)(bport1_ab_data.net_ctrl.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of Cadence Gigabit Ethernet Controller (GEM). For further details please consult README-EMAC.txt");
        ppmDocAddText(doc2_node, "This model is based upon the data and use in the Xilinx Zynq");
        ppmDocAddText(doc2_node, "Basic network Tx/Rx functionality tested using Xilinx Linux Kernel using wget and other similar tools");
        ppmDocAddText(doc2_node, "Tested with Xilinx SDK Example driver.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is based upon the data from the Xilinx Zynq platform, other registers may not be included.");
        ppmDocAddText(doc_22_node, "Does not implement: VLAN, pause frames, filtering or timestamps.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
    reset_resetNet(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}


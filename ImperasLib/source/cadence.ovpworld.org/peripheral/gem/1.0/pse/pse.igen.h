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

#ifndef PSE_IGEN_H
#define PSE_IGEN_H                      

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/bhmHttp.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

#ifdef _PSE_
//////////////////////////////////// Externs ///////////////////////////////////

extern Uns32 diagnosticLevel;


/////////////////////////// Dynamic Diagnostic Macros //////////////////////////

// Bottom two bits of word used for PSE diagnostics
#define PSE_DIAG_LOW                    (BHM_DIAG_MASK_LOW(diagnosticLevel))
#define PSE_DIAG_MEDIUM                 (BHM_DIAG_MASK_MEDIUM(diagnosticLevel))

#define PSE_DIAG_HIGH                   (BHM_DIAG_MASK_HIGH(diagnosticLevel))
// Next two bits of word used for PSE semihost/intercept library diagnostics
#define PSE_DIAG_SEMIHOST               (BHM_DIAG_MASK_SEMIHOST(diagnosticLevel))

#endif
/////////////////////////// Register data declaration //////////////////////////

typedef struct bport1_ab_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 1;
            Uns32 loopback_local : 1;
            Uns32 rx_en : 1;
            Uns32 tx_en : 1;
            Uns32 mgmt_port_en : 1;
            Uns32 clear_stat_regs : 1;
            Uns32 incr_stat_regs : 1;
            Uns32 wren_stat_regs : 1;
            Uns32 back_pressure : 1;
            Uns32 start_tx : 1;
            Uns32 tx_halt : 1;
            Uns32 tx_pause_frame : 1;
            Uns32 tx_zeroq_pause_frame : 1;
            Uns32 __pad13 : 2;
            Uns32 str_rx_timestamp : 1;
            Uns32 en_pfc_pri_pause_rx : 1;
            Uns32 tx_pfc_pri_pri_pause_f : 1;
            Uns32 flush_next_rx_dpram_ : 1;
        } bits;
    } net_ctrl;
    union { 
        Uns32 value;
        struct {
            Uns32 speed : 1;
            Uns32 full_duplex : 1;
            Uns32 disc_non_vlan : 1;
            Uns32 __pad3 : 1;
            Uns32 copy_all : 1;
            Uns32 no_broadcast : 1;
            Uns32 multi_hash_en : 1;
            Uns32 uni_hash_en : 1;
            Uns32 rx_1536_byte_frames : 1;
            Uns32 ext_addr_match_en : 1;
            Uns32 gige_en : 1;
            Uns32 pcs_sel : 1;
            Uns32 retry_test : 1;
            Uns32 pause_en : 1;
            Uns32 rx_buf_offset : 2;
            Uns32 len_err_frame_disc : 1;
            Uns32 fcs_remove : 1;
            Uns32 mdc_clk_div : 3;
            Uns32 dbus_width : 2;
            Uns32 dis_cp_pause_frame : 1;
            Uns32 rx_chksum_offld_en : 1;
            Uns32 rx_hd_while_tx : 1;
            Uns32 ignore_rx_fcs : 1;
            Uns32 sgmii_en : 1;
            Uns32 ipg_stretch_en : 1;
            Uns32 rx_bad_preamble : 1;
            Uns32 ignore_ipg_rx_er : 1;
            Uns32 unidir_en : 1;
        } bits;
    } net_cfg;
    union { 
        Uns32 value;
        struct {
            Uns32 pcs_link_state : 1;
            Uns32 mdio_in_pin_status : 1;
            Uns32 phy_mgmt_idle : 1;
            Uns32 pcs_autoneg_dup_res : 1;
            Uns32 pcs_autoneg_pause_rx : 1;
            Uns32 pcs_autoneg_pause_tx : 1;
            Uns32 pfc_pri_pause_neg : 1;
        } bits;
    } net_status;
    union { 
        Uns32 value;
    } user_io;
    union { 
        Uns32 value;
        struct {
            Uns32 ahb_fixed_burst_len : 5;
            Uns32 __pad5 : 1;
            Uns32 ahb_endian_swp_mgm : 1;
            Uns32 ahb_endian_swp_pkt_ : 1;
            Uns32 rx_pktbuf_memsz_sel : 2;
            Uns32 tx_pktbuf_memsz_sel : 1;
            Uns32 csum_gen_offload_en : 1;
            Uns32 __pad12 : 4;
            Uns32 ahb_mem_rx_buf_size : 8;
            Uns32 disc_when_no_ahb : 1;
        } bits;
    } dma_cfg;
    union { 
        Uns32 value;
        struct {
            Uns32 used_bit_read : 1;
            Uns32 collision : 1;
            Uns32 retry_limit_exceeded : 1;
            Uns32 tx_go : 1;
            Uns32 tx_corr_ahb_err : 1;
            Uns32 tx_complete : 1;
            Uns32 tx_under_run : 1;
            Uns32 late_collision : 1;
            Uns32 hresp_not_ok : 1;
        } bits;
    } tx_status;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 2;
            Uns32 rx_q_baseaddr : 30;
        } bits;
    } rx_qbar;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 2;
            Uns32 tx_q_base_addr : 30;
        } bits;
    } tx_qbar;
    union { 
        Uns32 value;
        struct {
            Uns32 buffer_not_avail : 1;
            Uns32 frame_recd : 1;
            Uns32 rx_overrun : 1;
            Uns32 hresp_not_ok : 1;
        } bits;
    } rx_status;
    union { 
        Uns32 value;
        struct {
            Uns32 mgmt_sent : 1;
            Uns32 rx_complete : 1;
            Uns32 rx_used_read : 1;
            Uns32 tx_used_read : 1;
            Uns32 __pad4 : 1;
            Uns32 retry_ex_late_collisn : 1;
            Uns32 tx_corrupt_ahb_err : 1;
            Uns32 tx_complete : 1;
            Uns32 __pad8 : 1;
            Uns32 link_chng : 1;
            Uns32 rx_overrun : 1;
            Uns32 hresp_not_ok : 1;
            Uns32 pause_nonzeroq_rx : 1;
            Uns32 pause_zero : 1;
            Uns32 pause_tx : 1;
            Uns32 ext_intr : 1;
            Uns32 autoneg_complete : 1;
            Uns32 partner_pg_rx : 1;
            Uns32 delay_req_rx : 1;
            Uns32 sync_rx : 1;
            Uns32 delay_req_tx : 1;
            Uns32 sync_tx : 1;
            Uns32 pdelay_req_rx : 1;
            Uns32 pdelay_resp_rx : 1;
            Uns32 pdelay_req_tx : 1;
            Uns32 pdelay_resp_tx : 1;
            Uns32 tsu_sec_incr : 1;
        } bits;
    } intr_status;
    union { 
        Uns32 value;
        struct {
            Uns32 mgmt_done : 1;
            Uns32 rx_complete : 1;
            Uns32 rx_used_read : 1;
            Uns32 tx_used_read : 1;
            Uns32 tx_underrun : 1;
            Uns32 retry_ex_late_collisn : 1;
            Uns32 tx_corrupt_ahb_err : 1;
            Uns32 tx_complete : 1;
            Uns32 __pad8 : 1;
            Uns32 link_chng : 1;
            Uns32 rx_overrun : 1;
            Uns32 hresp_not_ok : 1;
            Uns32 pause_nonzeroq : 1;
            Uns32 pause_zero : 1;
            Uns32 pause_tx : 1;
            Uns32 ext_intr : 1;
            Uns32 autoneg_complete : 1;
            Uns32 partner_pg_rx : 1;
            Uns32 delay_req_rx : 1;
            Uns32 sync_rx : 1;
            Uns32 delay_req_tx : 1;
            Uns32 sync_tx : 1;
            Uns32 pdelay_req_rx : 1;
            Uns32 pdelay_resp_rx : 1;
            Uns32 pdelay_req_tx : 1;
            Uns32 pdelay_resp_tx : 1;
            Uns32 tsu_sec_incr : 1;
        } bits;
    } intr_en;
    union { 
        Uns32 value;
        struct {
            Uns32 mgmt_done : 1;
            Uns32 rx_complete : 1;
            Uns32 rx_used_read : 1;
            Uns32 tx_used_read : 1;
            Uns32 tx_underrun : 1;
            Uns32 retry_ex_late_collisn : 1;
            Uns32 tx_corrupt_ahb_err : 1;
            Uns32 tx_complete : 1;
            Uns32 __pad8 : 1;
            Uns32 link_chng : 1;
            Uns32 rx_overrun : 1;
            Uns32 hresp_not_ok : 1;
            Uns32 pause_nonzeroq : 1;
            Uns32 pause_zero : 1;
            Uns32 pause_tx : 1;
            Uns32 ext_intr : 1;
            Uns32 autoneg_complete : 1;
            Uns32 partner_pg_rx : 1;
            Uns32 delay_req_rx : 1;
            Uns32 sync_rx : 1;
            Uns32 delay_req_tx : 1;
            Uns32 sync_tx : 1;
            Uns32 pdelay_req_rx : 1;
            Uns32 pdelay_resp_rx : 1;
            Uns32 pdelay_req_tx : 1;
            Uns32 pdelay_resp_tx : 1;
            Uns32 tsu_sec_incr : 1;
        } bits;
    } intr_dis;
    union { 
        Uns32 value;
        struct {
            Uns32 mgmt_done : 1;
            Uns32 rx_complete : 1;
            Uns32 rx_used_read : 1;
            Uns32 tx_used_read : 1;
            Uns32 tx_underrun : 1;
            Uns32 retry_ex_late_collisn : 1;
            Uns32 tx_corrupt_ahb_err : 1;
            Uns32 tx_complete : 1;
            Uns32 __pad8 : 1;
            Uns32 link_chng : 1;
            Uns32 rx_overrun : 1;
            Uns32 hresp_not_ok : 1;
            Uns32 pause_nonzeroq : 1;
            Uns32 pause_zero : 1;
            Uns32 pause_tx : 1;
            Uns32 ext_intr : 1;
            Uns32 autoneg_complete : 1;
            Uns32 partner_pg_rx : 1;
            Uns32 delay_req_rx : 1;
            Uns32 sync_rx : 1;
            Uns32 delay_req_tx : 1;
            Uns32 sync_tx : 1;
            Uns32 pdelay_req_rx : 1;
            Uns32 pdelay_resp_rx : 1;
            Uns32 pdelay_req_tx : 1;
            Uns32 pdelay_resp_tx : 1;
        } bits;
    } intr_mask;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 16;
            Uns32 must_10 : 2;
            Uns32 reg_addr : 5;
            Uns32 phy_addr : 5;
            Uns32 operation : 2;
            Uns32 clause_22 : 1;
        } bits;
    } phy_maint;
    union { 
        Uns32 value;
        struct {
            Uns32 rx_pauseq : 16;
        } bits;
    } rx_pauseq;
    union { 
        Uns32 value;
        struct {
            Uns32 tx_pauseq : 16;
        } bits;
    } tx_pauseq;
    union { 
        Uns32 value;
    } gem_jml;
    union { 
        Uns32 value;
    } hash_bot;
    union { 
        Uns32 value;
    } hash_top;
    union { 
        Uns32 value;
    } spec_addr1_bot;
    union { 
        Uns32 value;
        struct {
            Uns32 addr_msbs : 16;
        } bits;
    } spec_addr1_top;
    union { 
        Uns32 value;
    } spec_addr2_bot;
    union { 
        Uns32 value;
        struct {
            Uns32 addr_msbs : 16;
        } bits;
    } spec_addr2_top;
    union { 
        Uns32 value;
    } spec_addr3_bot;
    union { 
        Uns32 value;
        struct {
            Uns32 addr_msbs : 16;
        } bits;
    } spec_addr3_top;
    union { 
        Uns32 value;
    } spec_addr4_bot;
    union { 
        Uns32 value;
        struct {
            Uns32 addr_msbs : 16;
        } bits;
    } spec_addr4_top;
    union { 
        Uns32 value;
        struct {
            Uns32 type_id_match1 : 16;
            Uns32 __pad16 : 15;
            Uns32 copy_en : 1;
        } bits;
    } type_id_match1;
    union { 
        Uns32 value;
        struct {
            Uns32 type_id_match2 : 16;
            Uns32 __pad16 : 15;
            Uns32 copy_en : 1;
        } bits;
    } type_id_match2;
    union { 
        Uns32 value;
        struct {
            Uns32 type_id_match3 : 16;
            Uns32 __pad16 : 15;
            Uns32 copy_en : 1;
        } bits;
    } type_id_match3;
    union { 
        Uns32 value;
        struct {
            Uns32 type_id_match4 : 16;
            Uns32 __pad16 : 15;
            Uns32 copy_en : 1;
        } bits;
    } type_id_match4;
    union { 
        Uns32 value;
        struct {
            Uns32 arp_req_ip_addr : 16;
            Uns32 magic_pkt_en : 1;
            Uns32 arp_req_en : 1;
            Uns32 spec_addr_reg1_en : 1;
            Uns32 multi_hash_en : 1;
        } bits;
    } wake_on_lan;
    union { 
        Uns32 value;
        struct {
            Uns32 ipg_stretch : 16;
        } bits;
    } ipg_stretch;
    union { 
        Uns32 value;
        struct {
            Uns32 user_def_vlan_type : 16;
            Uns32 __pad16 : 15;
            Uns32 stacked_vlan_en : 1;
        } bits;
    } stacked_vlan;
    union { 
        Uns32 value;
        struct {
            Uns32 pri_en_vec_val : 8;
            Uns32 pauseq_sel : 8;
        } bits;
    } tx_pfc_pause;
    union { 
        Uns32 value;
        struct {
            Uns32 mask_bits_top : 32;
        } bits;
    } spec_addr1_mask_bot;
    union { 
        Uns32 value;
        struct {
            Uns32 mask_bits_top : 16;
        } bits;
    } spec_addr1_mask_top;
    union { 
        Uns32 value;
    } rx_ptp_uni;
    union { 
        Uns32 value;
    } tx_ptp_uni;
    union { 
        Uns32 value;
        struct {
            Uns32 module_rev : 16;
            Uns32 module_id : 16;
        } bits;
    } module_id;
    union { 
        Uns32 value;
        struct {
            Uns32 octets_tx_bot : 32;
        } bits;
    } octets_tx_bot;
    union { 
        Uns32 value;
        struct {
            Uns32 octets_tx_top : 16;
        } bits;
    } octets_tx_top;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_tx : 32;
        } bits;
    } frames_tx;
    union { 
        Uns32 value;
        struct {
            Uns32 broadcasr_frames_tx : 32;
        } bits;
    } broadcast_frames_tx;
    union { 
        Uns32 value;
        struct {
            Uns32 multi_frames_tx : 32;
        } bits;
    } multi_frames_tx;
    union { 
        Uns32 value;
        struct {
            Uns32 pause_frames_tx : 16;
        } bits;
    } pause_frames_tx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_64b_tx : 32;
        } bits;
    } frames_64b_tx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_65to127b_tx : 32;
        } bits;
    } frames_65to127b_tx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_128to255b_tx : 32;
        } bits;
    } frames_128to255b_tx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_256to511b_tx : 32;
        } bits;
    } frames_256to511b_tx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_512to1023b_tx : 32;
        } bits;
    } frames_512to1023b_tx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_1023to11518b_tx : 32;
        } bits;
    } frames_1024to1518b_tx;
    union { 
        Uns32 value;
    } frames_1519bplus_tx;
    union { 
        Uns32 value;
        struct {
            Uns32 tx_under_runs : 10;
        } bits;
    } tx_under_runs;
    union { 
        Uns32 value;
        struct {
            Uns32 single_collisn : 18;
        } bits;
    } single_collisn_frames;
    union { 
        Uns32 value;
        struct {
            Uns32 multi_collisn : 18;
        } bits;
    } multi_collisn_frames;
    union { 
        Uns32 value;
        struct {
            Uns32 excessive_collisns : 10;
        } bits;
    } excessive_collisns;
    union { 
        Uns32 value;
        struct {
            Uns32 late_collisns : 10;
        } bits;
    } late_collisns;
    union { 
        Uns32 value;
        struct {
            Uns32 deferred_tx_frames : 10;
        } bits;
    } deferred_tx_frames;
    union { 
        Uns32 value;
        struct {
            Uns32 carrier_sense_errs : 10;
        } bits;
    } carrier_sense_errs;
    union { 
        Uns32 value;
        struct {
            Uns32 octets_rx_bot : 32;
        } bits;
    } octets_rx_bot;
    union { 
        Uns32 value;
        struct {
            Uns32 octets_rx_top : 16;
        } bits;
    } octets_rx_top;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_rx : 32;
        } bits;
    } frames_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 bdcast_frames_rx : 32;
        } bits;
    } bdcast_frames_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 multi_frames_rx : 32;
        } bits;
    } multi_frames_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 pause_rx : 16;
        } bits;
    } pause_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_64b_rx : 32;
        } bits;
    } frames_64b_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_65to127b_rx : 32;
        } bits;
    } frames_65to127b_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_128to255b_rx : 32;
        } bits;
    } frames_128to255b_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_256to511b_rx : 32;
        } bits;
    } frames_256to511b_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_512to1023b_rx : 32;
        } bits;
    } frames_512to1023b_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 frames_1023to11518b_rx : 32;
        } bits;
    } frames_1024to1518b_rx;
    union { 
        Uns32 value;
    } frames_1519bplus_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 undersz_rx : 10;
        } bits;
    } undersz_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 oversz_rx : 10;
        } bits;
    } oversz_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 jab_rx : 10;
        } bits;
    } jab_rx;
    union { 
        Uns32 value;
        struct {
            Uns32 fcs_erros : 10;
        } bits;
    } fcs_errors;
    union { 
        Uns32 value;
        struct {
            Uns32 length_field_errors : 10;
        } bits;
    } length_field_errors;
    union { 
        Uns32 value;
        struct {
            Uns32 rx_symbol_errors : 10;
        } bits;
    } rx_symbol_errors;
    union { 
        Uns32 value;
        struct {
            Uns32 align_errors : 10;
        } bits;
    } align_errors;
    union { 
        Uns32 value;
        struct {
            Uns32 rx_resource_errors : 18;
        } bits;
    } rx_resource_errors;
    union { 
        Uns32 value;
        struct {
            Uns32 rx_overrun_errors : 10;
        } bits;
    } rx_overrun_errors;
    union { 
        Uns32 value;
        struct {
            Uns32 ip_hdr_csum_errors : 8;
        } bits;
    } ip_hdr_csum_errors;
    union { 
        Uns32 value;
        struct {
            Uns32 tcp_csum_errors : 8;
        } bits;
    } tcp_csum_errors;
    union { 
        Uns32 value;
        struct {
            Uns32 udp_csum_errors : 8;
        } bits;
    } udp_csum_errors;
    union { 
        Uns32 value;
        struct {
            Uns32 timer_strobe_s : 32;
        } bits;
    } timer_strobe_s;
    union { 
        Uns32 value;
        struct {
            Uns32 ns_reg_val : 30;
        } bits;
    } timer_strobe_ns;
    union { 
        Uns32 value;
        struct {
            Uns32 timer_s : 32;
        } bits;
    } timer_s;
    union { 
        Uns32 value;
        struct {
            Uns32 timer_ct_ns : 30;
        } bits;
    } timer_ns;
    union { 
        Uns32 value;
        struct {
            Uns32 ns_delta : 30;
            Uns32 __pad30 : 1;
            Uns32 add_subn : 1;
        } bits;
    } timer_adjust;
    union { 
        Uns32 value;
        struct {
            Uns32 ns_delta : 8;
            Uns32 alt_ct_ns_delta : 8;
            Uns32 incr_b4_alt : 8;
        } bits;
    } timer_incr;
    union { 
        Uns32 value;
        struct {
            Uns32 ptp_tx_s : 32;
        } bits;
    } ptp_tx_s;
    union { 
        Uns32 value;
        struct {
            Uns32 ns_reg_val : 30;
        } bits;
    } ptp_tx_ns;
    union { 
        Uns32 value;
        struct {
            Uns32 ptp_rx_s : 32;
        } bits;
    } ptp_rx_s;
    union { 
        Uns32 value;
        struct {
            Uns32 ns_reg_val : 30;
        } bits;
    } ptp_rx_ns;
    union { 
        Uns32 value;
        struct {
            Uns32 ptp_peer_tx_s : 32;
        } bits;
    } ptp_peer_tx_s;
    union { 
        Uns32 value;
        struct {
            Uns32 ns_reg_val : 30;
        } bits;
    } ptp_peer_tx_ns;
    union { 
        Uns32 value;
        struct {
            Uns32 ptp_peer_rx_s : 32;
        } bits;
    } ptp_peer_rx_s;
    union { 
        Uns32 value;
        struct {
            Uns32 ns_reg_val : 30;
        } bits;
    } ptp_peer_rx_ns;
    union { 
        Uns32 value;
    } design_cfg1;
    union { 
        Uns32 value;
        struct {
            Uns32 gem_jumbo_max_length : 16;
            Uns32 gem_hprot_value : 4;
            Uns32 gem_rx_pkt_buffer : 1;
            Uns32 gem_tx_pkt_buffer : 1;
            Uns32 gem_rx_pbuf_addr : 4;
            Uns32 gem_tx_pbuf_addr : 4;
        } bits;
    } design_cfg2;
    union { 
        Uns32 value;
        struct {
            Uns32 gem_rx_fifo_size : 16;
            Uns32 gem_rx_base2_fifo_siz : 16;
        } bits;
    } design_cfg3;
    union { 
        Uns32 value;
        struct {
            Uns32 gem_tx_fifo_size : 16;
            Uns32 gem_tx_base2_fifo_size : 16;
        } bits;
    } design_cfg4;
    union { 
        Uns32 value;
        struct {
            Uns32 gem_rx_fifo_cnt_width : 4;
            Uns32 gem_tx_fifo_cnt_width : 4;
            Uns32 gem_tsu : 1;
            Uns32 gem_phy_ident : 1;
            Uns32 gem_dma_bus_width : 2;
            Uns32 gem_mdc_clock_div : 3;
            Uns32 gem_endian_swap_def : 2;
            Uns32 gem_rx_pbuf_size_def : 2;
            Uns32 gem_tx_pbuf_size_def : 1;
            Uns32 gem_rx_buffer_length_ : 8;
            Uns32 gem_tsu_clk : 1;
        } bits;
    } design_cfg5;
    union { 
        Uns32 value;
    } design_cfg6;
    union { 
        Uns32 value;
    } tx_bd_cntrl;
    union { 
        Uns32 value;
    } rx_bd_cntrl;
} bport1_ab_dataT, *bport1_ab_dataTP;

typedef struct phyport_ab_dataS { 
    union { 
        Uns16 value;
    } MII_BMCR;
    union { 
        Uns16 value;
    } MII_BMSR;
    union { 
        Uns16 value;
    } MII_PHYSID1;
    union { 
        Uns16 value;
    } MII_PHYSID2;
    union { 
        Uns16 value;
    } MII_ADVERTISE;
    union { 
        Uns16 value;
    } MII_LPA;
    union { 
        Uns16 value;
    } MII_EXPANSION;
    union { 
        Uns16 value;
    } MII_DUMMY1;
    union { 
        Uns16 value;
    } MII_DUMMY2;
    union { 
        Uns16 value;
    } MII_CTRL1000;
    union { 
        Uns16 value;
    } MII_STAT1000;
    union { 
        Uns16 value;
    } MII_DUMMY3;
    union { 
        Uns16 value;
    } MII_DUMMY4;
    union { 
        Uns16 value;
    } MII_MMD_CTRL;
    union { 
        Uns16 value;
    } MII_MMD_DATA;
    union { 
        Uns16 value;
    } MII_ESTATUS;
    union { 
        Uns16 value;
    } MII_DUMMY5;
    union { 
        Uns16 value;
    } MII_STS;
    union { 
        Uns16 value;
    } MII_DCOUNTER;
    union { 
        Uns16 value;
    } MII_FCSCOUNTER;
    union { 
        Uns16 value;
    } MII_NWAYTEST;
    union { 
        Uns16 value;
    } MII_RERRCOUNTER;
    union { 
        Uns16 value;
    } MII_SREVISION;
    union { 
        Uns16 value;
    } MII_LBRERROR;
    union { 
        Uns16 value;
    } MII_PHYADDR;
    union { 
        Uns16 value;
    } MII_TPISTATUS;
    union { 
        Uns16 value;
    } MII_NCONFIG;
} phyport_ab_dataT, *phyport_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

extern phyport_ab_dataT phyport_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle bport2;
    void                 *bport1;
    void                 *phyport;
    ppmNetHandle          irq;
    ppmPacketnetHandle    phy;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(Readintr_status);
PPM_REG_READ_CB(Readnet_ctrl);
PPM_REG_WRITE_CB(Writeintr_dis);
PPM_REG_WRITE_CB(Writeintr_en);
PPM_REG_WRITE_CB(Writeintr_mask);
PPM_REG_WRITE_CB(Writeintr_status);
PPM_REG_WRITE_CB(Writenet_ctrl);
PPM_REG_WRITE_CB(Writephy_maint);
PPM_REG_WRITE_CB(Writerx_qbar);
PPM_REG_WRITE_CB(Writerx_status);
PPM_REG_WRITE_CB(Writetx_qbar);
PPM_REG_WRITE_CB(Writetx_status);
PPM_READ_CB(regNoDefinitionRead);
PPM_WRITE_CB(regNoDefinitionWrite);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/ab/buffer : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER_OFFSET + myAddress];

#define BPORT1_AB_BUFFER_OFFSET         0x0
#define BPORT1_AB_BUFFER_SIZE           0x1000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_NET_CTRL_WIDTH        32
#define BPORT1_AB_NET_CFG_WIDTH         32
#define BPORT1_AB_NET_STATUS_WIDTH      32
#define BPORT1_AB_USER_IO_WIDTH         32
#define BPORT1_AB_DMA_CFG_WIDTH         32
#define BPORT1_AB_TX_STATUS_WIDTH       32
#define BPORT1_AB_RX_QBAR_WIDTH         32
#define BPORT1_AB_TX_QBAR_WIDTH         32
#define BPORT1_AB_RX_STATUS_WIDTH       32
#define BPORT1_AB_INTR_STATUS_WIDTH     32
#define BPORT1_AB_INTR_EN_WIDTH         32
#define BPORT1_AB_INTR_DIS_WIDTH        32
#define BPORT1_AB_INTR_MASK_WIDTH       32
#define BPORT1_AB_PHY_MAINT_WIDTH       32
#define BPORT1_AB_RX_PAUSEQ_WIDTH       32
#define BPORT1_AB_TX_PAUSEQ_WIDTH       32
#define BPORT1_AB_GEM_JML_WIDTH         32
#define BPORT1_AB_HASH_BOT_WIDTH        32
#define BPORT1_AB_HASH_TOP_WIDTH        32
#define BPORT1_AB_SPEC_ADDR1_BOT_WIDTH  32
#define BPORT1_AB_SPEC_ADDR1_TOP_WIDTH  32
#define BPORT1_AB_SPEC_ADDR2_BOT_WIDTH  32
#define BPORT1_AB_SPEC_ADDR2_TOP_WIDTH  32
#define BPORT1_AB_SPEC_ADDR3_BOT_WIDTH  32
#define BPORT1_AB_SPEC_ADDR3_TOP_WIDTH  32
#define BPORT1_AB_SPEC_ADDR4_BOT_WIDTH  32
#define BPORT1_AB_SPEC_ADDR4_TOP_WIDTH  32
#define BPORT1_AB_TYPE_ID_MATCH1_WIDTH  32
#define BPORT1_AB_TYPE_ID_MATCH2_WIDTH  32
#define BPORT1_AB_TYPE_ID_MATCH3_WIDTH  32
#define BPORT1_AB_TYPE_ID_MATCH4_WIDTH  32
#define BPORT1_AB_WAKE_ON_LAN_WIDTH     32
#define BPORT1_AB_IPG_STRETCH_WIDTH     32
#define BPORT1_AB_STACKED_VLAN_WIDTH    32
#define BPORT1_AB_TX_PFC_PAUSE_WIDTH    32
#define BPORT1_AB_SPEC_ADDR1_MASK_BOT_WIDTH  32
#define BPORT1_AB_SPEC_ADDR1_MASK_TOP_WIDTH  32
#define BPORT1_AB_RX_PTP_UNI_WIDTH      32
#define BPORT1_AB_TX_PTP_UNI_WIDTH      32
#define BPORT1_AB_MODULE_ID_WIDTH       32
#define BPORT1_AB_OCTETS_TX_BOT_WIDTH   32
#define BPORT1_AB_OCTETS_TX_TOP_WIDTH   32
#define BPORT1_AB_FRAMES_TX_WIDTH       32
#define BPORT1_AB_BROADCAST_FRAMES_TX_WIDTH  32
#define BPORT1_AB_MULTI_FRAMES_TX_WIDTH  32
#define BPORT1_AB_PAUSE_FRAMES_TX_WIDTH  32
#define BPORT1_AB_FRAMES_64B_TX_WIDTH   32
#define BPORT1_AB_FRAMES_65TO127B_TX_WIDTH  32
#define BPORT1_AB_FRAMES_128TO255B_TX_WIDTH  32
#define BPORT1_AB_FRAMES_256TO511B_TX_WIDTH  32
#define BPORT1_AB_FRAMES_512TO1023B_TX_WIDTH  32
#define BPORT1_AB_FRAMES_1024TO1518B_TX_WIDTH  32
#define BPORT1_AB_FRAMES_1519BPLUS_TX_WIDTH  32
#define BPORT1_AB_TX_UNDER_RUNS_WIDTH   32
#define BPORT1_AB_SINGLE_COLLISN_FRAMES_WIDTH  32
#define BPORT1_AB_MULTI_COLLISN_FRAMES_WIDTH  32
#define BPORT1_AB_EXCESSIVE_COLLISNS_WIDTH  32
#define BPORT1_AB_LATE_COLLISNS_WIDTH   32
#define BPORT1_AB_DEFERRED_TX_FRAMES_WIDTH  32
#define BPORT1_AB_CARRIER_SENSE_ERRS_WIDTH  32
#define BPORT1_AB_OCTETS_RX_BOT_WIDTH   32
#define BPORT1_AB_OCTETS_RX_TOP_WIDTH   32
#define BPORT1_AB_FRAMES_RX_WIDTH       32
#define BPORT1_AB_BDCAST_FRAMES_RX_WIDTH  32
#define BPORT1_AB_MULTI_FRAMES_RX_WIDTH  32
#define BPORT1_AB_PAUSE_RX_WIDTH        32
#define BPORT1_AB_FRAMES_64B_RX_WIDTH   32
#define BPORT1_AB_FRAMES_65TO127B_RX_WIDTH  32
#define BPORT1_AB_FRAMES_128TO255B_RX_WIDTH  32
#define BPORT1_AB_FRAMES_256TO511B_RX_WIDTH  32
#define BPORT1_AB_FRAMES_512TO1023B_RX_WIDTH  32
#define BPORT1_AB_FRAMES_1024TO1518B_RX_WIDTH  32
#define BPORT1_AB_FRAMES_1519BPLUS_RX_WIDTH  32
#define BPORT1_AB_UNDERSZ_RX_WIDTH      32
#define BPORT1_AB_OVERSZ_RX_WIDTH       32
#define BPORT1_AB_JAB_RX_WIDTH          32
#define BPORT1_AB_FCS_ERRORS_WIDTH      32
#define BPORT1_AB_LENGTH_FIELD_ERRORS_WIDTH  32
#define BPORT1_AB_RX_SYMBOL_ERRORS_WIDTH  32
#define BPORT1_AB_ALIGN_ERRORS_WIDTH    32
#define BPORT1_AB_RX_RESOURCE_ERRORS_WIDTH  32
#define BPORT1_AB_RX_OVERRUN_ERRORS_WIDTH  32
#define BPORT1_AB_IP_HDR_CSUM_ERRORS_WIDTH  32
#define BPORT1_AB_TCP_CSUM_ERRORS_WIDTH  32
#define BPORT1_AB_UDP_CSUM_ERRORS_WIDTH  32
#define BPORT1_AB_TIMER_STROBE_S_WIDTH  32
#define BPORT1_AB_TIMER_STROBE_NS_WIDTH  32
#define BPORT1_AB_TIMER_S_WIDTH         32
#define BPORT1_AB_TIMER_NS_WIDTH        32
#define BPORT1_AB_TIMER_ADJUST_WIDTH    32
#define BPORT1_AB_TIMER_INCR_WIDTH      32
#define BPORT1_AB_PTP_TX_S_WIDTH        32
#define BPORT1_AB_PTP_TX_NS_WIDTH       32
#define BPORT1_AB_PTP_RX_S_WIDTH        32
#define BPORT1_AB_PTP_RX_NS_WIDTH       32
#define BPORT1_AB_PTP_PEER_TX_S_WIDTH   32
#define BPORT1_AB_PTP_PEER_TX_NS_WIDTH  32
#define BPORT1_AB_PTP_PEER_RX_S_WIDTH   32
#define BPORT1_AB_PTP_PEER_RX_NS_WIDTH  32
#define BPORT1_AB_DESIGN_CFG1_WIDTH     32
#define BPORT1_AB_DESIGN_CFG2_WIDTH     32
#define BPORT1_AB_DESIGN_CFG3_WIDTH     32
#define BPORT1_AB_DESIGN_CFG4_WIDTH     32
#define BPORT1_AB_DESIGN_CFG5_WIDTH     32
#define BPORT1_AB_DESIGN_CFG6_WIDTH     32
#define BPORT1_AB_TX_BD_CNTRL_WIDTH     32
#define BPORT1_AB_RX_BD_CNTRL_WIDTH     32
#define PHYPORT_AB_MII_BMCR_WIDTH       16
#define PHYPORT_AB_MII_BMSR_WIDTH       16
#define PHYPORT_AB_MII_PHYSID1_WIDTH    16
#define PHYPORT_AB_MII_PHYSID2_WIDTH    16
#define PHYPORT_AB_MII_ADVERTISE_WIDTH  16
#define PHYPORT_AB_MII_LPA_WIDTH        16
#define PHYPORT_AB_MII_EXPANSION_WIDTH  16
#define PHYPORT_AB_MII_DUMMY1_WIDTH     16
#define PHYPORT_AB_MII_DUMMY2_WIDTH     16
#define PHYPORT_AB_MII_CTRL1000_WIDTH   16
#define PHYPORT_AB_MII_STAT1000_WIDTH   16
#define PHYPORT_AB_MII_DUMMY3_WIDTH     16
#define PHYPORT_AB_MII_DUMMY4_WIDTH     16
#define PHYPORT_AB_MII_MMD_CTRL_WIDTH   16
#define PHYPORT_AB_MII_MMD_DATA_WIDTH   16
#define PHYPORT_AB_MII_ESTATUS_WIDTH    16
#define PHYPORT_AB_MII_DUMMY5_WIDTH     16
#define PHYPORT_AB_MII_STS_WIDTH        16
#define PHYPORT_AB_MII_DCOUNTER_WIDTH   16
#define PHYPORT_AB_MII_FCSCOUNTER_WIDTH  16
#define PHYPORT_AB_MII_NWAYTEST_WIDTH   16
#define PHYPORT_AB_MII_RERRCOUNTER_WIDTH  16
#define PHYPORT_AB_MII_SREVISION_WIDTH  16
#define PHYPORT_AB_MII_LBRERROR_WIDTH   16
#define PHYPORT_AB_MII_PHYADDR_WIDTH    16
#define PHYPORT_AB_MII_TPISTATUS_WIDTH  16
#define PHYPORT_AB_MII_NCONFIG_WIDTH    16

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif

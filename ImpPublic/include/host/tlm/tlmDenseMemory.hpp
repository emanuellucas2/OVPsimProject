/**********************************************************************
  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2008 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.
 *********************************************************************/

/* Derived from TLM examples memory.cpp by Imperas Software LTD.
 *
 * This is an example of a memory model with a TLM interface.
 *
 * It is not sparse, so requires as much virtual memory as it's size
 * in bytes.. For example, on the 32bit host a memory > 2G will generally
 * fail to load.
 *
 * The memory supports DMI, which is turned ON by default.
 *
 * To turn off DMI and invalidate DMI active regions.
 * instance.stopDMI();
 *
 * To turn DMI on again.
 * instance.startDMI();
 */

#pragma once

#include "tlm.h"                                // TLM headers
#include "tlm_utils/simple_target_socket.h"

#include "op/op.hpp"

using namespace std;
using namespace sc_core;

namespace cw {

class module;
class tlmModule;

class tlmMemory {
  public:

    tlmMemory
    (
          sc_dt::uint64      high_address       ///< memory size (bytes-1)
        , unsigned int       memory_width       ///< memory width (bytes)
    );

    void operation(
          tlm::tlm_generic_payload  &gp           ///< TLM2 GP reference
        , sc_time          &delay_time   ///< transaction delay
    );

    unsigned int debug(
          tlm::tlm_generic_payload  &gp           ///< TLM2 GP reference
        , sc_time          &delay_time   ///< transaction delay
    );

    void get_delay(
        tlm::tlm_generic_payload  &gp           ///< TLM2 GP reference
      , sc_time          &delay_time   ///< time to be updated
    );

    unsigned char* get_mem_ptr(void);

  private:

     bool             check_address(tlm::tlm_generic_payload  &gp);
     sc_dt::uint64    m_high_address;          ///< memory size (bytes-1)
     unsigned int     m_memory_width;          ///< memory width (bytes)
     unsigned char    *m_memory;               ///< memory      ///< limits to one message
};

class tlmRam:  public sc_module {
  public:

    tlmRam (
        tlmModule       &parent
      , sc_module_name   module_name              ///< SC module name
      , sc_dt::uint64    high_address             ///< memory size (bytes-1)
      , unsigned int     memory_width = 4         ///< memory width (bytes)
    );

  private:
    void         custom_b_transport(tlm::tlm_generic_payload &payload, sc_time &delay_time);
    unsigned int debug_transport   (tlm::tlm_generic_payload &payload);
    bool         get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi&  dmi_data);

  public:
    tlm_utils::simple_target_socket<tlmRam>  sp1;
    tlmMemory *getMemory() { return &m_target_memory; }   ///< return a pointer to the memory
    void dmi(bool on);      ///< If true, starts DMI, if false stops DMI and invalidates its region

  private:
    sc_dt::uint64       m_high_address;
    unsigned int        m_memory_width;
    tlmMemory           m_target_memory;
    bool                dmiOn;
};

} // end namespace cw

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

#pragma once

#include <cstdio>
#include "sysc/tracing/sc_trace.h"
#include "sysc/kernel/sc_simcontext.h"
#include "tlm.h"

#include "op/op.hpp"

using namespace sc_core;
using namespace op;

namespace cw {

class time_advance : public sc_trace_file
{

protected:

    // These are all virtual functions in sc_trace_file. They need to be defined here.

	 // Additional functions to support v2.3.2, thanks to Chen, Dun-Jie @ NCKU
     void trace(const sc_event& object, const std::string& name) {}
     void trace(const sc_time& object, const std::string& name) {}
	 //
     void trace(const bool& object, const std::string& name) {}
     virtual void trace( const sc_dt::sc_bit& object,  const std::string& name) {}
     void trace(const sc_dt::sc_logic& object, const std::string& name) {}
     void trace(const unsigned char& object, const std::string& name, int width) {}
     void trace(const unsigned short& object, const std::string& name, int width) {}
     void trace(const unsigned int& object, const std::string& name, int width) {}
     void trace(const unsigned long& object, const std::string& name, int width) {}
     void trace(const char& object, const std::string& name, int width) {}
     void trace(const short& object, const std::string& name, int width) {}
     void trace(const int& object, const std::string& name, int width) {}
     void trace(const long& object, const std::string& name, int width) {}
     void trace(const sc_dt::int64& object, const std::string& name, int width) {}
     void trace(const sc_dt::uint64& object, const std::string& name, int width) {}
     void trace(const float& object, const std::string& name) {}
     void trace(const double& object, const std::string& name) {}
     void trace (const sc_dt::sc_uint_base& object, const std::string& name) {}
     void trace (const sc_dt::sc_int_base& object, const std::string& name) {}
     void trace (const sc_dt::sc_unsigned& object, const std::string& name) {}
     void trace (const sc_dt::sc_signed& object, const std::string& name) {}
     void trace( const sc_dt::sc_fxval& object, const std::string& name ) {}
     void trace( const sc_dt::sc_fxval_fast& object, const std::string& name ) {}
     void trace( const sc_dt::sc_fxnum& object, const std::string& name ) {}
     void trace( const sc_dt::sc_fxnum_fast& object, const std::string& name )  {}
     virtual void trace(const sc_dt::sc_bv_base& object, const std::string& name) {}
     virtual void trace(const sc_dt::sc_lv_base& object, const std::string& name) {}
     void trace(const unsigned& object, const std::string& name, const char** enum_literals) {}

     void write_comment(const std::string& comment) {}
     void delta_cycles(bool flag) {  }


private:
     typedef bool (*timeFn)(optTime time, void *user);
     timeFn  advanceFn;
     void   *userData;

public:
     // this is the only virtual function we actually need !!
     void cycle(bool this_is_a_delta_cycle)
     {
         if (!this_is_a_delta_cycle && advanceFn) {
             if (!advanceFn(sc_time_stamp().to_seconds(), userData)) {
                 sc_stop();
             }
         }
     }

    // constructor and destructor
    time_advance()  {}
    ~time_advance() {}

    void set_time_unit( int exponent10_seconds ) {}
    void set_time_unit( double v, sc_time_unit tu) {}

    // call a static function when time changes, with no dependence on its class.
    void setCallback(timeFn fn, void *user) { advanceFn = fn; userData = user; }
};

/// The Module object.

class tlmModule : public sc_module, public module {

private:

    // A root module
    bool            isRoot;

    // registers the time advance callback.
    time_advance   *tAdvance;

    // period of one quantum for all processors
    sc_time         globalQuantum;

    static Bool advance(optTime t, void *user) {
        tlmModule *p = (tlmModule*) user;

        return p->timeAdvance(t);
    }

    // defining this virtual fn from sc_module causes our startup to be called
    // before simulation starts
    void start_of_simulation(void){
        preSimulate();
    }

    // defining this virtual fn from sc_module causes our shutdown to be called
    // before SystemC starts calling destructors.
    void end_of_simulation(void) {
        postSimulate();
    }

    void start() {
        // register the time callback
        if(isRoot) {
            tAdvance = new time_advance();
            tAdvance->setCallback(advance, this);

            sc_time t (1, SC_MS);
            globalQuantum = t;

            // register the trace callback
            sc_get_curr_simcontext()->add_trace_file(tAdvance);
        }
    }

public:

    /// The constructor. Ensure this is called before any other constructors.
    /// It must be called only once.
    tlmModule(sc_module_name module_name);
    tlmModule(sc_module_name module_name, params p);

    /// Destructor (not usually called explicitly).

    ~tlmModule() { postSimulate(); }

    /// Override the default global quantum (length of each time-slice).
    /// Should be called from the platform constructor (not during simulation).

    void    quantum(sc_time q) { globalQuantum = q; }

    /// Return the current global quantum.
    /// @return current quantum.

    sc_time quantum() { return globalQuantum; }
};

} // end namespace cw


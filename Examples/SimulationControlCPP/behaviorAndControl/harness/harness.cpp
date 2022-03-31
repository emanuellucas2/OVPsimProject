/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

/* This is a C++ platform that demonstrates some features of OVPsim */

#include <iostream>

using namespace std;

#include "op/op.hpp"
using namespace op;


#include "arm_Cortex-A57MPx1.hpp"

////////////////////////// SLAVE DEVICE ///////////////////////////
//
// simple bus slave implemented as callbacks
//
class callbackSlave : public busSlave {

public:

   // overload virtual read function
   void read(
            object       *inititator,
            Addr          addr,
            Uns32         bytes,
            void*         data,
            void*         userData,
            Addr          VA,
            Bool          isFetch
    ) {
        cout << "Hello-read " << hex << addr <<  endl;
    }
    
   // overload virtual write function
    void write(
            object       *inititator,
            Addr          addr,
            Uns32         bytes,
            const void*   data,
            void*         userData,
            Addr          VA
    ){
        cout << "Hello-write " << hex << addr << endl;
    }
    
    // constructor
    callbackSlave(bus &b, const char *name, Addr lo, Addr hi)
       : busSlave(b, name, 0, OP_PRIV_RWX, lo, hi, 1, 1, 0, 0)
    {
    }
};

//////////////////////// NATIVE MEMORY /////////////////////////////////

class nativeRam : public busSlave {

private:
    char *native;
    
    // allocate space for ram on the heap
    void *allocRam(Uns32 max) {
        native = new char[max+1];
        return native;
    }
    
public:
    nativeRam(bus &b, const char *name, Addr lo, Addr hi)
        : busSlave(b, name, 0, OP_PRIV_RWX, lo, hi, (void*)allocRam(hi-lo))
    {
    }
    
    ~nativeRam() {
        delete[] native;
    }
};

/////////////////////////////////////////////////////////////////////
//
// Top level of platform
//

class top : public module {

    private:

        params paramsForRoot(void) {
            params p;
            p.set("verbose", true);
            return p;
        }

        params paramsForCpu(void) {
            params p;
            p.set("defaultsemihost", true);
            return p;
        }

    public:
        bus                 bus1;
        arm_Cortex_A57MPx1  cpu;

        nativeRam           prog;
        nativeRam           heap;
        nativeRam           stack;

        callbackSlave       slave;

        top(const char *name="top")
          : module (name,paramsForRoot())
          , bus1   (*this, "b1",    32)
          , cpu    (*this, "cpu",   paramsForCpu())
          , prog   (bus1,  "prog",  0x80000000, 0x800fffff)
          , heap   (bus1,  "heap",  0xe0000000, 0xefffffff)
          , stack  (bus1,  "stack", 0xffffffff - 0x000fffff, 0xffffffff)
          , slave  (bus1,  "periph",0xc0000000, 0xc000ffff)
        {
            // connections
            bus1.connect(cpu, "INSTRUCTION");
            bus1.connect(cpu, "DATA");

            cpu.applicationLoad("application/hello.AARCH64.elf", OP_LDR_SET_START|OP_LDR_FAIL_IS_ERROR);
        }
};

///////////////////////////////////// INTROSPECTION /////////////////////////////////////

static void queryRegs(processor *p) {

    reg   *r = 0;
    Uns32 c  = 0;
    
    // display the first 50 registers
    while((r = p->regNext(r)) && c < 50) {

        cout << "    Reg " << dec << c << "  " << r->name() << endl;

        Uns32 bits = r->bits();
        cout << "       bits " << bits << endl;

        if(bits <= 32) {

            Uns32 v = 0;

            p->regRead(r, &v);
            cout << "       hex  " << hex << v << endl;
        }
        c++;
    }
}

static void queryProcessor(processor *p) {
    cout << "Processor " << p->name() << endl;
    queryRegs(p);
    
    processor *ch;
    for(ch = p->child(); ch; ch = ch->siblingNext()) {
        queryProcessor(ch);
    }
}

////////////////////////////////// MAIN ///////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    // session control
    session    ses;
    
    // standard command line parser
    parser     par(argc, argv);
    
    // platform
    top        t;
    
    t.cpu.simulate(10000);
    queryProcessor(&t.cpu);
}

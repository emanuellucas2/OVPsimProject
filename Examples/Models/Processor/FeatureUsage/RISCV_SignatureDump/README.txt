

 Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com

 The contents of this file are provided under the Software License
 Agreement that you accepted before downloading this file.

 This source forms part of the Software and can be used for educational,
 training, and demonstration purposes but cannot be used for derivative
 works except in cases where the derivative works require OVP technology
 to run.

 For open source models released under licenses that you can use for
 derivative works, please visit www.ovpworld.org or www.imperas.com
 for the location of the open source models.



File:README.txt

INTRODUCTION -------------------------------------------------------

This example shows the execution of a fibonacci sequence generator as 
a bare metal application, using semihosted printf, on the RISC-V processor
using the RVB64I variant with extensions MAC and SU enabled.

RISC-V Signature File ----------------------------------------------

A script is provided to configure the platform to generate a signature
output after executing a test application.

To run the example, execute one of the scripts. 

The signature file is the content of a memory region and is written either
at the end of execution or on a specific event.

The default usage (RISC-V compliant) is with tests built with the riscv 
environment that define symbols 'begin_signature' and 'end_signature' 
and is called on the call to the function 'write_tohost'.

However, parameters can be set allowing the definition of any region and 
the generation of the signature file at the end of simulation.

Configuration Parameters ---------------------------------------------

  - SignatureFile   : The name of the file created containing the signature  
  - SignatureAtEnd  : Write the signature file at the end of simulation.
  - ResultReg       : The register examined to indicate if the test passed 
                      or failed. Permitted values 3=gp, 10=a0, 28=t3 (default)

Defining the Start of memory containing signature  
  - StartAddress    : The address of the memory
  - StartSymbol     : The symbol, default 'begin_signature'  

Defining the End of memory containing signature  
  - EndAddress      : The address of the memory  
  - EndSymbol       : The symbol, default 'end_signature'  
  - ByteCount       : The size in bytes, from the StartAddress or StartSymbol

NOTE:
The signature format, defined by RISCV.org, is arranged 16 bytes per line. 
This requires that the size of the signature memory is always on a 16-byte
boundary. The size is reduced to the previous boundary if too big. By 
reducing the size it is possible to ensure that only data intended for the 
signature is included and not additional 'random' data.

Example run under Linux ----------------------------------------------

> $ cd examples/fibonacci  
> $ RUN_RV64_fibonacci_signature_dump.sh  

... 
> Info (SIGNATURE_DUMP) Found Symbol 'resultArray' in application at 0x1fbf8  
> Info (SIGNATURE_DUMP) Signature File enabled, file 'fib.sig.dat.txt'.  
> Info (SIGNATURE_DUMP) Extracting signature from 0x1fbf8 size 48 bytes  
> Info (SIGNATURE_DUMP) Symbol 'resultArray' at 0x1fbf8  
> starting fib(38)...  
> fib(0) = 0  
> fib(1) = 1  
> fib(2) = 1  
> fib(3) = 2  
...  
> fib(35) = 9227465  
> fib(36) = 14930352  
> fib(37) = 24157817  
> finishing...  
...
>    
> 
> Info (SIGNATURE_DUMP) Destructor. Generate Signature file  
> 6279e990593722150d08050302010100  
> dd28b57342311120f12fc26d55183ddb  
> 0000000000000000000079b0c9e7e205  
>  

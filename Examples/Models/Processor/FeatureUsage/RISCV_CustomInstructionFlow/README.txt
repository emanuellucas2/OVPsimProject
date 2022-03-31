# Description
This example shows the flow from the analysis of an application to the creation of a 
custom instruction and the re-analysis.
It also includes the generation of coverage and profiling information for the custom instruction
to aid the developer in the creation of efficient behavioral code.

# Makefile Targets

  A Makefile is provided to build everything that is required
  It provides the following targets (use make help to see this list)
  build (default) : build the test applications and the custom instruction extension library
                    that allow the RUN scripts to be executed.
  build-gcov      : build GCOV versions of the RISCV processor model and the instruction 
                    extension library so that all tests subsequently executed will be used
                    to gather coverage data.
  lcov            : generate lcov data files
  view            : view lcov data using eGui
  html            : generate and view (using firefox) HTML view of lcov data
  doc             : generate a PDF document of the extended RISCV processor

# Applications

  test_main.c     : Common test application core, this includes the code from 
                              test_lib_c to create test_c
                    or code from 
                              test_lib_asm to create test_asm
  test_lib_c.c    : Algorithm code C implementation
  test_lib_asm.c  : Algorithm code with assembler code to include custom instructions
  
# Other loaded code
  exception.S    : call _exit on an undefined instruction execution to terminate the simulation.
                   Loaded at the exception vector 0x00000000

# Extension libraries
  instructionExtensionCFunctionCallLib : 
        custom extension instruction definition implemented using a call to a C description of the behaviour
  instructionExtensionLib : 
        custom extension instruction definition implemented using VMI API
  timingToolLib : 
        library that provides basic timing annotation onto the application execution
        This loads the file 'custom_instruction_timing.txt' that defines base instruction delays

# Scripts
  RUN_STAGES   : This script is provided to allow one of the following to be selected and execute

   Executing a C application implementation
     1 : Instruction Accurate simulation C application
           Execute the C application on the instruction accurate simulator
     2 : Cycle Approximate simulation C application
           Add timing to 1) and re-run
     3 : Basic Block profile C application
           Add basic block profiling to 2) and re-run  
     4 : Profile C application
           Add C application profiling to 2) and re-run 

   Executing with a Custom instruction implemented
     5 : Add custom instructions to application
           Use a modified application that uses custom instructions in place of the C functions
           Without the custom instruction available this run will fail and terminate on an exception
     6 : Add custom instructions to model
           Load the custom instructions into the simulation using an extension library
     7 : Cycle Approximate simulation (custom instructions)
           Add timing to 6) and re-run
     8 : Profile custom instructions application
           Add C application profiling to 7) and re-run
     9 : Trace custom instructions
           Enable tracing for a few instructions within the processLine function to see the custom 
           instructions execution
    10 : Debug custom instructions
           Enable debug with eGui

    15 : Documenting custom instructions (Linux Only)
           Generate and view (evince) a PDF document for the processor and the custom instructions
    16 : Documenting custom instructions
           Generate a LaTex document for the processor and the custom instructions

   Examine in detail the custom instructions
           The following stages are intended for the developer of the custom instructions
    20 : Custom Instruction Coverage
           Execute the test application and use an extension library to monitor the execution of
           instructions. On completion show the list of all instructions and counts of times executed
    21 : Custom Instruction Called C Function Profile
           Execute the test application and use the simulators instruction profiling to provide an 
           output that provides an indication of the host time each instruction takes to execute. In this
           example the extension instruction is created by calling a C implementation of its behavior.
           This profile information can be used to indicate a badly coded instruction.
    22 : Custom Instruction Profile
           Re-execute the simulators instruction profiling, as used in 21. In this example the extension
           instruction is using the VMI MT API functions. This is a much more efficient implementation.

    25 : Model Source Line Coverage
           The RISCV processor model and the custom extension library are re-built for line coverage. When
           a test is executed using this model the lines executed are recorded. This provides a view if 
           testing has adequately tested all model code lines.


  RUN_EXAMPLE   : This script allows the selection of different options to create a single simulation
                  execute application (default executes application including custom instruction)

# Options
  When the script is executed the following options can be selected before selecting 20: to start the 
  simulation
  0: Application
      Select either the application implementing the chacha20 as C functions or using custom instructions 
  1: Add Custom Instruction Extension
      Enable the custom instruction execution. Without the custom instruction enabled the application
      will take an undefined instructions exception which is trapped causing the simulation to terminate
  2: Instruction Executed
      Enable monitoring of instructions executed. This provides information for the instructions that have
      and have not been executed 
  3: Instruction Tracing
      Enable the trace of instructions around the same execution location to show difference when running
      the C code with and without the custom instruction. The point at which tracing is enabled is set 
      so that the function call or custom instruction execution is apparent. If the application is modified
      these must be modified
  4: Timing Approximation (estimate execution time)
      Load a model timing library and report expected execution time
  5: Timing Approximation (stretch time to estimated time)
      Load a model timing library and extend the simulation time in line with the expected execution time
  6: Application code coverage
      Generate code line coverage information for the executing application.
  7: Application profiling
      Generate a profile of the executing application
  8: Instruction Implementation profiling
      Enable simulator instruction profiling. This provides a list of the instructions executed and the 
      time taken to execute allowing a view of the implementation efficiency.
  9: Model Code Coverage
      Generate 
 10: Debug
      Enable debug using eGui with MPD
      NOTE: In eGui make use of the simulator disassembly option to correctly view the custom instructions.
            This is done by disabling the GDB disassembly interface before opening the disassembly view.
            Initially run to the code containing the custom instructions
            In the DebuggerConsole set a breakpoint on the function containing the custom instructions
            $ break processLine
            Run the simulation
            When stopped in the function. In the DebuggerConsole use the command 'set usegdb 0/1' to 
            turn off/on the use of GDB
            $ set usegdb 0
            open the disassembly Window (this can be done using the i icon to enter disassembly mode)
            $ set usegdb 1
 11: Instruction profiling
      Load the instruction profiling intercept library. This provides a report of the counts of instructions
      executed by an entire program as well as on a per function basis.
      

# EXAMPLES
1) Compare execution of C versus Custom Instruction implementations.
  - run the C application implementation
    $ RUN_EXAMPLE.sh
        select  0) to select the C function implementation
        select 20) to run the simulation
        Note the result printed to stdout and the Elapsed time
  - run the C application implementation using custom instructions
    $ RUN_EXAMPLE.sh
        select  1) to enable the custom instructions
        select 20) to run the simulation
        Note the result printed to stdout and the Elapsed time

2) Generate an instruction coverage for the custom instructions
    $ RUN_EXAMPLE.sh
        select  1) to enable the custom instructions
        select  2) to enable instruction execution coverage
        select 20) to run the simulation
    $ cat coverageReports/cpu0.icr.txt

3) Generate Code Coverage for the processor model and the extension library
   This allows a set of tests to be executed on the processor model, including the extensions,
   and to determine how much of the model has been executed.
    $ make build-gcov
    $ RUN_EXAMPLE.sh
        select  1) to enable the custom instructions
        select  9) to enable Code Coverage - this selects the RISCV model compiled for coverage
            NOTE: Any set of tests can be executed but the local RISCV model object must be 
                  used as this is compiled and linked with GCOV libraries
                  The model may also be used with tracing enabled to show disassembly being 
                  exercised or generating documentation to show documentation nodes used.
        select 20) to run the simulation with this specific test
    $ make lcov
        This will generate coverage information
    $ make view
        This will open the coverage information in eGui

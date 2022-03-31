This document gives instructions on running the Imperas eGui Eclipse-based
IDE on the FreeRTOS_arm demo. It assumes the reader is familiar with 
debugging in an Eclipse environment and highlights the extensions to Eclipse 
provided by eGui.

REQUIRED PACKAGES
-----------------
The following packages are required:

      eGui_Eclipse
      Demo_FreeRTOS_arm
      Imperas_SDK or Imperas_Dev
      armv7.toolchain
      OVPpse.toolchain
    
Install these packages and setup the Imperas environment.
   

COPY THE DEMO DIRECTORY
--------------------------
Make a copy of the FreeRTOS_arm demo:

       cp -r $IMPERAS_HOME/Demo/Platforms/FreeRTOS_arm <dirname>
       
(Note: these instructions assume a bash shell on Linux or an Msys shell
on Windows)
       
    
REBUILD APPLICATION LOCALLY
---------------------------   
Re-build the FreeRTOS application locally so source files may be found
by the debugger:
   
       make all -C <dirname>/FreeRTOS_arm


START EGUI IDE
--------------
Start the Imperas eGui IDE:

       egui.exe

When prompted for a workspace select a directory. For example, 'ImperasWorkspace' in your home directory is a good choice.
This is where eGui will store your settings between sessions.
   
IMPORTANT NOTE: Do NOT specify a workspace in the FreeRTOS_arm directory, as a 
workspace should not be in a directory that is imported as a project
to that workspace and doing so may cause the import to fail.

You should now be in the Imperas eGui which is a special version of 
Eclipse with the ability to connect to the Imperas MPD debugger which
supports debug of platforms containing multiple processors and peripherals.


IMPORT FreeRTOS_arm AS A PROJECT
---------------------------------------
The first thing to do is to import the local copy of the FreeRTOS_arm 
directory as an eclipse project. Select:
   
       File->Import
       
which brings up the Import dialog box. Now select:
   
       C/C++->Existing Code as Makefile Project
      
and click 'Next'. 

This brings up the 'New Project' dialog box. In 'Existing Code Location' 
select <dirname>/FreeRTOS_arm, and under 'Toolchain for Indexer 
Settings' select '<None>' and then click 'Finish'.

This only needs to be done once for a workspace. Once imported the project
will appear whenever you start again with the same workspace. An attempt to 
re-import a project directory will give an error.


SWITCH TO C/C++ PERSPECTIVE
---------------------------
Switch to the C/C++ perspective by selecting:

        Window->Open Perspective->C/C++
        
and click 'Next'.

The FreeRTOS_arm project should be visible in the 'Project
Explorer' view.


LAUNCH DEBUG SESSION
--------------------
Three launch configuration files have been provided in the 
FreeRTOS_arm demo directory so a debug session may be easily launched
in egui:

1) FreeRTOS_Platform external tools launch configuration:

  Launches the simulator with a debug port. It also configures the platform
  to load the VAP tools.

2) FreeRTOS_MPD debug configuration:

  Launches the Imperas-connect feature of eGui which connects to the debug
  port of a running simulator and supports interactive debug.
  
3) FreeRTOS_Debug launch group:
  This is a shortcut to launch the above 1) and 2) configurations.

These launch configurations may be modified to pass different parameters to
the simulation or may be copied and modified to run other platforms.   

You may launch a debug session by selecting:

       Run->Run configurations...
   
This brings up the 'Run Configurations' dialog box. 
Select 'Launch Group->FreeRTOS_Debug' and then click 'Run'.

If a dialog box explaining that the perspective will be switched is 
displayed, select the 'Remember my decision' box and click 'Yes'.


EGUI FEATURES
-------------   
You are now in the Debug perspective ready to debug. There are several 
views here that are different then the standard eclipse views:
   
   Debug: 
       This shows each processor and peripheral in the platform being debugged
       along with a stack trace for each. The selection made in this view
       changes the information shown in other views.
       
   Console: 
       This shows the various consoles available (see below).
       
   Programmers View: 
       This shows the Imperas Programmers view info for the processor or 
       peripheral instance selected in the Debug view.
   
There are several console views that may be selected using the 'Display 
Selected Console' icon on the Console tab, including:
   
   FreeRTOS_MPD [Imperas - Connect] mpd:
       This console shows messages from the Imperas MPD debugger and allows
       MPD commands to be typed in it
   
    FreeRTOS_Platform [Program]:
       This shows the simulator output messages
   
   FreeRTOS_MPD [Imperas - Connect] gdb traces:
       This console shows communications between eGui and MPD and is used 
       for debugging. It may be ignored and will go away in the future.

See TIPS below for ideas on how to manage the consoles in Egui.


DEBUG SESSION
-------------
The simulation is stopped before executing the first instruction. 
All the standard Eclipse Resume, Suspend, Step, Instruction Mode, etc... 
commands are available.

In addition the MPD console may be used to issue MPD commands. 'help' and
'::ihelp' will show the available commands which are described in the
Imperas Debugger User Guide.

First, select the 'ID #1 [cpu1] Cortex-M3 armm' line in the debug view 
window. (You may need to open the FreeRTOS_MPD/cpus [Cortex-M3 armm] drop down
lists if not already open.)

In the MPD console window (labeled 'FreeRTOS_MPD [Imperas - Connect] mpd') enter 
the following commands:
       break main
       ::ostrace
   
Now select Resume (the green arrow icon, or press F8) and the simulation
will run up to the entry to the main() function. The source to the main 
function should be displayed. (Tip: Resume will be greyed out unless a 
runnable element is selected in the Debug view)

The Breakpoints view displays the breakpoints and may be used to manipulate 
them.


PERIPHERAL DEBUG
----------------
To set a breakpoint in the LED peripheral expand the LEDRegister entry in 
the debug view until you see a line that says 'config() at led.user.c' and
select that line. 

(If the source file window shows a 'Can't find a source file at...' message
then see 'SETTING THE PATH FOR MODEL SOURCE FILES' below.)

Now find the showLEDs() in the led.user.c source file window function
near the beginning of the file and double click in the left margin
opposite the bhmMessage function call, which will add a breakpoint.

Press Resume (or F8) a few times and the simulation will break each time 
that line is reached. When at the breakpoint in the peripheral you can 
also examine the state of the processor and other peripherals.

For example, expanding the cpu1 entry in the debug view will allow you
to examine the call stack of the processor that resulted in the access of
the LED peripheral.

Note - You may see 'thread-select: processor id xx is not valid' error
messages. This problem is known and will be fixed in the future.


TERMINATING DEBUG SESSION
-------------------------
To terminate the simulation select Terminate (the red square icon or
CTRL-F2).

After terminating the simulation may be re-run using the Run button (the
green circle with white arrow icon). Note that breakpoints are persistent,
use the Breakpoints view to disable or delete them if desired.


SETTING THE PATH FOR MODEL SOURCE FILES
---------------------------------------
If no source is displayed in a source file window then do the following to
set up the mapping to the the Imperas model source:

1) Select the 'Edit Source Lookup Path' button in the source file window
   Note the path name shown on the 'Can't find a source file at...' message.

2) Select:
       Add->Path Mapping
   and 'OK'. This will bring up the Path Mappings dialog.

3) Enter 'ImperasLib Source Path' in the Name field.

4) Select 'Add' and enter under 'Compilation path' the build path which is
   displayed in the 'Can't find a source file at...' message, up to and 
   including '/ImperasLib.source'. 
   
   This will be something like:
       '/home/release/engineering/20150717.0/Imperas/ImperasLib/source'

5) Select the 'Local file system path' field and browse to the 
   'ImperasLib/source' directory in your Imperas installation directory.
   (This is the directory Specified by the IMPERAS_HOME environment variable.)
    
6) Select OK in each of the open windows. The model source should now be 
   visible.

CAUTION: Everything that matches the Path Mapping Compilation path entry will
   be modified by eclipse. Specifying a path that includes things not intended
   to be remapped can cause issues. In particular, attempting to add a Path
   Mapping for the IMPERAS_HOME directory has been know to cause problems.  
    
TIPS
----

You may find it useful to see both the Program and MPD consoles at the 
same time. This may be done by clicking the 'Open Console' icon in the
Console tab and selecting 'New Console View'. The new Console tab may  
be dragged to a new area of the screen where it will open a new window.
Then by changing the displayed console and pinning it you may see multiple 
consoles at the same time.

The small windows in Eclipse can be limiting - double clicking a tab, 
such as a console tab is an easy way to make that tab full screen.
Double clicking it again reverts back to the normal display.
   
   
       
       
       

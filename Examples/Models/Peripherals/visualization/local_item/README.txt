 
  Copyright (c) 2005-2021 Imperas Software Ltd. All Rights Reserved.

  The contents of this file are provided under the Software License
  Agreement that you accepted before downloading this file.

  This source forms part of the Software and can be used for educational,
  training, and demonstration purposes but cannot be used for derivative
  works except in cases where the derivative works require OVP technology
  to run.

  For open source models released under licenses that you can use for
  derivative works, please visit www.ovpworld.org or www.imperas.com
  for the location of the open source models.


RUNNING THE EXAMPLES -----------------------------------------------

Building the Executables
    A shell script (example.sh/.bat) that is included that runs the provided
    Makefiles to compile up the executables and application. This requires
    certain tools chains to be installed. There will be warnings if these
    are not installed.
    
    To build all parts of the example use the command

>make -C application
>make -C module               NOVLNV=1 
>make -C peripheral           NOVLNV=1 
    
Running the example
    The example is run using the shell script (example.sh/.bat) after it has
    compiled the application and executable.
    
    You will be asked if you want to run the browser to see the visualization.
    
    You can run any browser if you connect it to the correct machine/portnumber. The
    portnumber is specified in the run script (example.sh/.bat).

Image showing platform configuration
    There is a .jpg file in this directory which shows a picture of the module
    and configuration of the example being run.


NOTES -------------------------------------------------------------

Browser fails to load visualization in browser

On some older versions of Windows or with some browsers the browser 
may not initially load the visualization. 
If this occurs, please
 a) Start the browser independently 
    Find the line in the simulator output corresponding to
      Info (HTTP_PORT) 'test/pse0' listening on port <PORT NUMBER>
    in the browser open the page
      http://localhost:<PORT NUMBER>
 b) Re-load the page in the browser
 c) Try a different browser


#
# Copyright (c) 2005-2021 Imperas Software Ltd. All Rights Reserved.
#
# THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS
# OF IMPERAS SOFTWARE LTD. USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED
# EXCEPT AS MAY BE PROVIDED FOR IN A WRITTEN AGREEMENT WITH IMPERAS SOFTWARE LTD.
#


#
# environment
#
set root $::imperas::IMPERAS_HOME

#
# Conditionally include the skeleton generator
#
if {[file exists $root/bin/tcl/cpuskel.tcl]} {
    source $root/bin/tcl/cpuskel.tcl
}

proc igenAtExit {} {
    icpu::atexit
}

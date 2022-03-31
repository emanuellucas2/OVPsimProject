# Ethernet Model

## Specifications


### PHY


### GMAC


## Tested Configurations


## Supported Network Modes
The SMSC model allows Ethernet traffic on the target (virtual) machine to be tunneled to the host machine.
This can be done in two different ways.  The SLIRP (a.k.a. User) mode uses sockets on the host. The TAP
mode uses an existing TAP interface on the host.  By default the model uses SLIRP mode.  It can be switched
to TAP mode by overriding the "tapDevice" parameter, specifying the host TAP interface to be used.

The advantages of SLIRP mode are that it doesn't require administrator privileges on the host and usually
runs without further network configuration on the host.  The disadvantages are that it works on IP level and
does not support non-IP Ethernet frames, and the IP communication has to originate on the target, roughly speaking.

In addition, the model supports recording of the in and out traffic and replaying of the in traffic.  This is
controlled through the "infile" and "outfile" parameters.  The capture files use pcap format and can be
accessed with tools like WireShark and tcpdump.

The network backend of the SMSC model is implemented with the OVP BHM and PPM API.  More information
can be found in the OVP BHM and PPM API Function Reference.


## Configuring Network
In order to communicate from the target to host and/or Internet some network configuration may be needed,
both on target and on host.  This section lists the necessary steps to get the tunneling working, and
following sections show some example configurations.  The exact steps will depend on OS versions and on
the existing kernel and network configurations on host and target.

The first five steps to get tunneling working differ based on the host operating system.  The
last steps are the same regardless of the host.

###############################################################################
## TAP Setup for Linux Host Platforms 
 1. For TAP mode, create a TAP device on host.  Ensure it's accessible by the user starting simulation.
    For example, on Linux do:
      host> tunctl -u <user> -t tap0                            # create tap0 interface, owned by <user>
    Normally, this loads automatically the tun driver as needed, but it may be necessary to do this manually.

 2. For TAP mode, configure host's TAP interface.  For example, on a Linux host do:
      host> ifconfig tap0 192.168.9.4 up                        # start tap0
    Make sure that target.eth0 and host.tap0 are on the same private network, e.g. 192.168.9.0/24.

 3. For TAP mode, ensure connectivity between tap0 and other interfaces on the host.  Different
    approaches are possible, e.g. IP forwarding, bridging, proxy ARP.  For IP forwarding on a
    Linux host, do:
      host> sysctl -w net.ipv4.ip_forward=1                     # enable IP forwarding

 4. Modify host's firewall as needed, especially in TAP mode.  For a linux host try:
      host> iptables -t filter -I FORWARD -i tap0 -j ACCEPT     # modify host forward filtering as needed
    In some cases this isn't enough.  Inspect the "filter" table with:
      host> iptables -t filter -L                               # list IP filter's table

 5. In TAP mode, configure SNAT as needed.  If the tap0 interface uses a reserved IP address, e.g.
    192.168.9.4, the packets that it sends to Internet must have their source IP translated
    using SNAT (Source Network Address Translation, or masquerading), otherwise response packets
    will never reach back to it.  On a Linux host this can be done like:
      host> iptables -t nat -A POSTROUTING -o wlan0 -j MASQUERADE   # force SNAT if Inet router needs it
    where wlan0 is a host interface connected to Internet.

###############################################################################
## TAP Setup for Windows Host Platforms 
 1. Download the TAP-windows virtual ethernet adapter from
      http://openvpn.net/index.php/download/community-downloads.html
    and install it by running the installer as administrator:
      + When choosing components, select "TAP Virtual Ethernet Adapter" to install
        a virtual network interface; and "TAP Utilities" to provides menu commands
          "TAP-Windows - Utilites - Add a new TAP virtual ethernet adapter" and
          "TAP-Windows - Utilites - Delete ALL TAP virtual ethernet adapters".
        that can be run later as the administrator to change things.
      + Choose an installation directory.  The default should work fine.
    After installation, "Device Manager" will show an additional entry under "Network adapters"
    with a name starting with "Tap-Windows Adapter V9".  In addition, within the "Control Panel"
    context "Network and Internet - Network Connections" there will be an additional entry 
    referencing the added network adapter.  This entry usually is named something like
    "Local Area Connection <n>" and has the initial state "Network cable unplugged".

    ################################ CAUTION ##################################
    If you are using OpenVPN for virtual private networking, it seems to use
    the last TAP-windows virtual adapter installed.  To verify, disconnect and then
    re-connect with OpenVPN while watching the status of the icons in the
    "Network and Internet - Network Connections".  Then, in the next step, choose a 
    "TAP_Windows Adapter V9 <n>" that is shown with the state "Network cable unplugged".
    ###########################################################################
       
 2. Configure the host's TAP interface.  This includes giving the network connection a
    name that is easily referenced via a command line argument and IP address.  These steps
    can be done in the GUI from the "Network and Internet - Network Connections":
      + Select the icon for the connection and rename it to a (preferable short) single word
        name like "tap0".
      + Assign an IP address by executing "Properties" for the icon, double-clicking on
        "Internet Protocol Version 4 (TCP/IPv4)", selecting "Use the following IP address", and
        then entering an "IP address" and "Subnet mask".  For example 192.168.9.4 and 255.255.255.0,
        respectively.
    The IP address can also be changed from the command line as administrator by using this command:
      + netsh interface ipv4 set adddress static tap0 192.168.9.4 255.255.255.0

 3. Ensure connectivity between the virtual ethernet address and other interfaces on the host.
    This is done by enabling IP routing on the Windows host.  For example,
    run services.msc and ensure that "Routing and Remote Access" service is enabled and
    either started or set to automatically start.
    On Windows XP and older you may need to tweak the registry, as described in this
    article http://support.microsoft.com/kb/315236.
    The command prompt can be used to verify that IP routing is enabled, e.g.
      host> ipconfig /all

 4. Modify host's firewall as needed, especially in TAP mode.
    For example, it may be necessary to enable ICMP requests in order to ping host.tap0 from
    target.eth0, e.g.
    host> netsh firewall set icmpsetting 8 enable

 5. In TAP mode, configure Internet Connection Sharing.
    This is done differently in Vista and later than XP and older.  More information
    can be found in the Help and Support Center, and in Microsoft's knowledge base,
    e.g. http://support.microsoft.com/kb/314066/en-us (for XP),
    http://windows.microsoft.com/en-us/windows/using-internet-connection-sharing#1TC=windows-7 (for Windows 7, Vista).
    For example, on Vista run services.msc and enable "Internet Connection Sharing",
    then edit the properties of the Internet network connection to enable sharing with tap0.
    NOTE: this may change the manually assigned IP to tap0 in step 2 above, and the
    following examples need to be tweaked accordingly.

 5.5 Temporarily disable anti-virus software or configure the software to make an
     exception for the platform executable - platform.exe.  This is needed as the
     accesses to the host resources by the virtual platform may be mistaken as
     those made by code that the anti-virus software is designed to thwart.


###############################################################################
## Common Steps for TAP Setup 
 6. Find out the SMSC instances that will be used by target kernel.

 7. Start simulation, using the desired network mode for each SMSC instance.  To start the platform
    with the instance0 in SLIRP (default) mode and instance1 in TAP mode, do:
      host> platform.exe --override platform/instance1/tapDevice=tap0 # start simulation

 8. Verify that the target OS has loaded the corresponding NIC driver and it has successfully initialized
    the model.  To check this on Linux, do:
      target> ifconfig -a                                       # check that eth0 is registered

 9. Configure the network interface, e.g. eth0, on target, if the previous step shows that it isn't configured
    already.  On a Linux target this can be done with:
      target> ifconfig eth0 10.0.2.7 netmask 255.255.255.0 up   # start and configure eth0
    In SLIRP mode, target.eth0 interface and slirp.gw interface have to be on the same network, which is
    usually 10.0.2.0/24.  See http://wiki.qemu.org/Documentation/Networking for more information on SLIRP.
    In TAP mode, target.eth0 and host.tap0 interfaces have to be on the same network.  Following examples
    use 192.168.9.0/24.  See e.g. http://bochs.sourceforge.net/doc/docbook/user/config-tuntap.html.

10. Update target's IP routing.  After configuring the eth0 interface on the previous step, the target should
    know how to communicate with nodes from eth0's network (e.g. 10.0.2 or 192.168.9).  On Linux this can be
    verified with:
      target> route -n                                          # check routing to eth0's network
    To update the routing on a Linux target for communication with nodes on other networks, do:
      target> route add default gw 10.0.2.2                     # add default GW

11. Update target's DNS resolution.  On a Linux target, do:
      target> echo "nameserver 10.0.2.3" > /etc/resolv.conf     # set up DNS (SLIRP mode)
      target> echo "nameserver 192.168.0.1" > /etc/resolv.conf  # set up DNS (TAP mode, see examples)

## Example Uses

### Manual Target Network Configuration
```
  host> platform.exe                                            # start simulation
  target> ifconfig eth0 10.0.2.7 netmask 255.255.255.0 up       # start and configure eth0
  target> route add default gw 10.0.2.2                         # add default GW
  target> echo "nameserver 10.0.2.3" > /etc/resolv.conf         # set up DNS
  target> lynx http://www.google.com/                           # browse google
```

### DHCP Target Network Configuration
```
  host> platform.exe                                            # start simulation
  target> ifconfig eth0 up                                      # start eth0
  target> udhcpc -i eth0                                        # lease an IP address from DHCP server
  target> # if network scripts are missing, proceed with manual configuration, using the leased address
  target> ifconfig eth0 10.0.2.15 netmask 255.255.255.0         # configure eth0
  target> route add default gw 10.0.2.2                         # add default GW
  target> echo "nameserver 10.0.2.3" > /etc/resolv.conf         # set up DNS
  target> lynx http://www.google.com/                           # browse google
```

### Linux Host TAP Networking Configuration with IP Routing (requires root access)
- target.eth0 / host.tap0 connectivity:
```
  host> tunctl -u <user> -t tap0                                # create tap0 interface, owned by <user>
  host> ifconfig tap0 192.168.9.4 up                            # start tap0
  host> platform.exe --override platform/instance1/tapDevice=tap0 # start simulation
  target> ifconfig eth0 192.168.9.3 up                          # start eth0
  target> ping -c 1 192.168.9.4                                 # check connection
```

- host.tap0 / Internet connectivity, using IP forwarding and NAT
  (this example assumes that host has a wlan0 interface with a reserved address, e.g. 192.168.0.5,
  connected to an Internet router 192.168.0.1, which provides also DNS):
```
  host> sysctl -w net.ipv4.ip_forward=1                         # enable IP forwarding
  host> iptables -t nat -A POSTROUTING -o wlan0 -j MASQUERADE   # force SNAT if Inet router needs it
  host> iptables -t filter -I FORWARD -i tap0 -j ACCEPT         # modify host forward filtering as needed
  target> route add default gw 192.168.9.4                      # add default GW
  target> echo "nameserver 192.168.0.1" > /etc/resolv.conf      # set up DNS
  target> lynx http://www.google.com/                           # browse Google
```
         target                  host               Internet router
           |                     / \                      |
192.168.9.3|         192.168.9.4/   \192.168.0.5          |192.168.0.1
          eth0               tap0   wlan0                /
             \_______________/         \________________/

### Linux Host TAP Networking Configuration Bridging Two Targets (requires root access)
- target1.eth0 / target2.eth0 / host.br0 connectivity:
```
  host> tunctl -u <user> -t tap0                                # create tap interfaces, owned by <user>
  host> tunctl -u <user> -t tap1
  host> ifconfig tap0 0.0.0.0 down                              # ensure tap interfaces are unconfigured
  host> ifconfig tap1 0.0.0.0 down
  host> brctl addbr br0                                         # create a bridge interface
  host> brctl addif br0 tap0                                    # attach tap interfaces to the bridge
  host> brctl addif br0 tap1
  host> ifconfig tap0 up                                        # activate bridge and its ports
  host> ifconfig tap1 up
  host> ifconfig br0 up
    or
  host> ifconfig br0 192.168.9.1 up                             # bridge may be assigned an IP address to communicate with host
  host> ebtables -t filter -L                                   # check that filtering doesn't limit bridge's functionality
  host> platform.exe --override platform/instance1/tapDevice=tap0 # start simulation
  host> platform.exe --override platform/instance1/tapDevice=tap1
  target1> ifconfig eth0 192.168.9.3 up                         # start eth0 on targets
  target2> ifconfig eth0 192.168.9.4 up
  target1> ping -c 1 192.168.9.1                                # check connections
  target2> ping -c 1 192.168.9.3
```
        target1                 host                  target2
          |                      |[192.168.9.1]         |
          |                     br0                     |
          |192.168.9.3    port1/   \port2               |192.168.9.4
         eth0               tap0   tap1                eth0
            \_______________/         \________________/


### Windows Host TAP Networking Configuration with IP Routing (requires administrator access)
- target.eth0 / host.tap0 connectivity:
```
  host> # ensure Tap-windows has been installed and named "tap0"
  host> netsh interface ipv4 set address tap0 static 192.168.9.4 255.255.255.0
  host> netsh interface ipv4 set interface tap0 Forwarding=enabled
  host> platform.exe --override platform/instance1/tapDevice=tap0 # start simulation
  target> ifconfig eth0 192.168.9.3 up                          # start eth0
  target> ping -c 1 192.168.9.4
  host> ping 192.168.9.3

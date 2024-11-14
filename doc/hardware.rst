###############
Flight Hardware
###############

All flight data is handled via Ethernet. On the flight computer
we have a hard-coded set of network addresses, recorded here.

When running locally the ports are the same, but localhost is used
for all IP addresses.


Avionics Network Information
============================

Flight Computer
^^^^^^^^^^^^^^^

 - IP Addr: ``10.0.0.10``
 - MAC Addr: ?
 - Data Listen Port: ``36000``
 - Arm Message Port: ``35666``
 - RC Servo Message Port: ``35667``


Sensor Board
^^^^^^^^^^^^

 - IP Addr: ``10.0.0.20``
 - MAC Addr: ``E6:10:20:30:40:11``
 - Listen Port: ``35001``
 - Transmit Ports:

   - ADIS: ``35020``
   - MPL: ``35010``
   - MPU: ``35002``


Roll Board
^^^^^^^^^^

 - IP Addr: ``10.0.0.30``
 - MAC Addr: ``E6:10:20:30:40:aa``
 - Listen Port: ``35003``
 - Transmit Port: ``35004``


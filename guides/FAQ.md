# MSCL FAQs

If you need more help, please reach out on the
[MicroStrain Support Portal](https://support.microstrain.com)

### How do I set up a connection to a WSDA-2000 / WSDA-1500 ethernet BaseStation?

Using a TCP/IP connection vs. a USB/Serial connection in MSCL is as simple as
changing one line of code:

```c++
// Creating a USB/Serial Connection
mscl::Connection serialConnection = mscl::Connection::Serial("COM3");

// Change to a tcp connection for a WSDA-1500
mscl::Connection tcpConnection = mscl::Connection::TcpIp("192.100.26.1", 5000);

mscl::BaseStation baseStation(tcpConnection);
```

### I am using a WSDA-2000 ethernet BaseStation, but having trouble communicating with it / Wireless Nodes.

Depending on your network latency, you may need to adjust the timeout for
communicating with the BaseStation:

```c++
mscl::BaseStation baseStation(connection);

// Set the timeout to 2 seconds
baseStation.timeout(2000);
```

### My Wireless Node won't respond to commands.

To communicate with a Wireless Node, all the following must be true:

- The Node is powered on, and within range of the BaseStation
- The Node is on the same frequency as the BaseStation
- The Node is in Idle Mode (not sampling and not sleeping)

If all of the above is true, you may want to try adding some retries. MSCL can
perform these for you for all read/write eeprom commands:

```c++
mscl::WirelessNode node(123, baseStation);

node.readWriteRetries(3);
```

### I'm attempting to connect to a device on Linux, and I'm getting a Connection error.

The /dev/tty* devices usually have a group of `dialout`. You will either need to
make sure you own the device you are accessing, or add your user to the 
`dialout` group (`usermod -a -G dialout YOUR_USER_NAME`).

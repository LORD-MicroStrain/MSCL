# MSCL FAQs

The following are some frequently asked questions from MSCL users. It can also be useful to view previous [Issues](https://github.com/LORD-MicroStrain/MSCL/issues?utf8=%E2%9C%93&q=)

If you need more help, please [Create a New Issue](https://github.com/LORD-MicroStrain/MSCL/issues/new), or contact richard.stoneback@lord.com

### How do I set up a connection to a WSDA-2000 / WSDA-1500 ethernet BaseStation?

Using a TCP/IP connection vs a USB/Serial connection in MSCL is as simple as changing 1 line of code:

```py
# creating a USB/Serial Connection
serialConnection = mscl.Connection.Serial("COM3")

# change to a tcp connection for a WSDA-1500
tcpConnection = mscl.Connection.TcpIp("192.100.26.1", 5000)

baseStation = mscl.BaseStation(tcpConnection)
```

### I am using a WSDA-2000 ethernet BaseStation, but am having trouble communicating with it / Wireless Nodes.

Depending on your network latency, you may need to adjust the timeout for communicating with the BaseStation:

```py
baseStation = mscl.BaseStation(connection)

# set the timeout to 2 seconds
baseStation.timeout(2000)
```

### My Wireless Node won't respond to commands.

In order to communicate with a Wireless Node, all of the following must be true:
- The Node is powered on, and within range of the BaseStation
- The Node is on the same frequency as the BaseStation
- The Node is in Idle Mode (not sampling, and not sleeping)

If all of the above is true, you may want to try adding some retries. MSCL can perform these for you for all read/write eeprom commands:

```py
node = mscl.WirelessNode(123, baseStation)

node.readWriteRetries(3)
```

### I'm attempting to connect to a device on Linux, and I'm getting a Connection error.

The /dev/tty* devices usually have a group of `dialout`. You will either need to make sure the device you are accessing is owned by you, or add your user to the `dialout` group (`usermod -a -G dialout YOUR_USER_NAME`).

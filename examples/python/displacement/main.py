from __future__ import print_function
import sys
import os
import platform

# TODO: Make sure the script can find the MSCL library for this to work
# Import the MSCL library
import MSCL as mscl

################################################################################
# TODO: Modify any of these options according to your use case

# Toggle certain parts of the example on/off
SET_TO_IDLE        = True
GET_CURRENT_CONFIG = True
SET_CURRENT_CONFIG = True
START_SAMPLING     = True
PARSE_DATA         = True

# Update the communication port
if platform.system() == "Windows":
    COM_PORT = "COM1"
elif platform.system() == "Linux":
    COM_PORT = "/dev/tty/ACM0"

# We recommend at least 115200 for the baudrate on our devices
BAUDRATE = 115200
################################################################################

def main():
    try:
        # Create a SerialConnection with the COM port and (optional) baudrate
        connection = mscl.Connection.Serial(COM_PORT, BAUDRATE)

        # Create a DisplacementNode with the connection
        node = mscl.DisplacementNode(connection)

        print("Node Information:")
        print("Model Name: {0}".format(node.modelName()))
        print("Model Number: {0}".format(node.modelNumber()))
        print("Serial: {0}".format(node.serialNumber()))
        print("Firmware: {0}\n".format(node.firmwareVersion()))

        if SET_TO_IDLE:
            # Example: Set to Idle
            setToIdle(node)

        if GET_CURRENT_CONFIG:
            # Example: Get Configuration
            getCurrentConfig(node)

        if SET_CURRENT_CONFIG:
            # Example: Set Configuration
            setCurrentConfig(node)       # Warning: this example changes settings on your Node

        if START_SAMPLING:
            # Example: Start Sampling
            startSampling(node)

        if PARSE_DATA:
            # Example: Parse Data
            parseData(node)

    except mscl.Error as e:
        sys.stderr.write("Error: {0}\n".format(e.what()))

def setToIdle(node):
    node.setToIdle()

# Example: Get Current Configuration
#  Shows how to read current configuration settings a Displacement Device.
def getCurrentConfig(node):
    cals = node.getAnalogToDisplacementCal()

    print("Analog to Displacement Cal: Slope: {0:06.3f} Offset: {1:06.3f}".format(cals.slope(), cals.offset()))
    print("Output Data Rate:", node.getDisplacementOutputDataRate().prettyStr())

def setCurrentConfig(node):
    # Seed the device time with the current PC time
    # Note: you can pass your own time to this function as a
    #      parameter in nanoseconds since unix epoch

    node.setDeviceTime()

def startSampling(node):
    node.resume()

# Example: Parse Data
#  Shows how to parse incoming data from a Displacement Device.
#  Note that this example does not start a Node sampling (assumes it already is).
def parseData(node):
    # Endless loop of reading in data
    while True:
        # Loop through all the data packets from the node, with a timeout of 500 milliseconds
        for packet in node.getDataPackets(500):

            # Print out the data
            print("Packet Received: ", end="")

            # Loop through all the data points in the packet
            for dataPoint in packet.data():
                print("{0}: ".format(dataPoint.channelName()), end="")

                # Print out the channel data
                # Note: The as_string() function is being used here for simplicity.
                #      Other methods (i.e., as_float, as_uint16, as_Vector) are also available.
                #      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                print("{0} ".format(dataPoint.as_string()), end="")

                # If the dataPoint is invalid
                if not dataPoint.valid():
                    print("[Invalid] ", end="")

            print("")

# Run the example
if __name__ == "__main__":
    main()

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

        # Create an InertialNode with the connection
        node = mscl.InertialNode(connection)

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

    # Note: you can also disable the datastream for each class/category
    #       separately if desired, by using the enableDataStream command shown in
    #       the startSampling example, but passing a second parameter of 'false'

# Example: Get Current Configuration
#  Shows how to read current configuration settings an Inertial Device.
def getCurrentConfig(node):
    # Many other settings are available than shown below
    # Reference the documentation for the full list of commands

    # If the node supports AHRS/IMU
    if node.features().supportsCategory(mscl.MipTypes.CLASS_AHRS_IMU):
        # Get a list of the AHRS/IMU channels currently active on the Node
        ahrsImuActiveChs = node.getActiveChannelFields(mscl.MipTypes.CLASS_AHRS_IMU)

        print("AHRS/IMU Channels")
        print("-----------------")

        for channel in ahrsImuActiveChs:
            print("Channel Field: 0x{0:04X}".format(channel.channelField()))
            print("Sample Rate: {0}\n".format(channel.sampleRate().prettyStr()))

    # If the node supports Estimation Filter
    if node.features().supportsCategory(mscl.MipTypes.CLASS_ESTFILTER):
        # Get a list of the Estimation Filter channels currently active on the Node
        estFilterActiveChs = node.getActiveChannelFields(mscl.MipTypes.CLASS_ESTFILTER)

        print("\nEstimation Filter Channels")
        print("--------------------------")

        for channel in estFilterActiveChs:
            print("Channel Field: 0x{0:04X}".format(channel.channelField()))
            print("Sample Rate: {0}\n".format(channel.sampleRate().prettyStr()))

    # If the node supports GNSS
    if node.features().supportsCategory(mscl.MipTypes.CLASS_GNSS):
        # Get a list of the GNSS channels currently active on the Node
        gnssActiveChs = node.getActiveChannelFields(mscl.MipTypes.CLASS_GNSS)

        print("\nGNSS Channels")
        print("--------------------------")

        for channel in gnssActiveChs:
            print("Channel Field: 0x{0:04X}".format(channel.channelField()))
            print("Sample Rate: {0}\n".format(channel.sampleRate().prettyStr()))

    if node.features().supportsCommand(mscl.MipTypes.CMD_EF_ALTITUDE_AID_CTRL):
        print("Altitude Aiding enabled?: {0}".format("TRUE" if node.getAltitudeAid() else "FALSE"))

    if node.features().supportsCommand(mscl.MipTypes.CMD_EF_ANTENNA_OFFSET):
        offset = node.getAntennaOffset()
        print("Antenna Offset: X = {0:06.3f} Y = {1:06.3f} Z = {2:06.3f}".format(offset.x(), offset.y(), offset.z()))
    elif node.features().supportsCommand(mscl.MipTypes.CMD_EF_MULTI_ANTENNA_OFFSET):
        for gnssReceiverInfo in node.features().gnssReceiverInfo():
            offset = node.getMultiAntennaOffset(gnssReceiverInfo.id)
            print("Antenna {0} Offset: X = {1:06.3f} Y = {2:06.3f} Z = {3:06.3f}".format(gnssReceiverInfo.id, offset.x(), offset.y(), offset.z()))

    if node.features().supportsCommand(mscl.MipTypes.CMD_EF_PITCH_ROLL_AID_CTRL):
        print("Pitch/Roll Aiding enabled?: {0}".format("TRUE" if node.getPitchRollAid() else "FALSE"))

def setCurrentConfig(node):
    # Many other settings are available than shown below
    # Reference the documentation for the full list of commands

    # If the node supports AHRS/IMU
    if node.features().supportsCategory(mscl.MipTypes.CLASS_AHRS_IMU):
        ahrsImuChs = mscl.MipChannels()
        ahrsImuChs.append(mscl.MipChannel(mscl.MipTypes.CH_FIELD_SENSOR_SCALED_ACCEL_VEC, mscl.SampleRate.Hertz(500)))
        ahrsImuChs.append(mscl.MipChannel(mscl.MipTypes.CH_FIELD_SENSOR_SCALED_GYRO_VEC, mscl.SampleRate.Hertz(100)))

        # Apply to the node
        node.setActiveChannelFields(mscl.MipTypes.CLASS_AHRS_IMU, ahrsImuChs)

    # If the node supports Estimation Filter
    if node.features().supportsCategory(mscl.MipTypes.CLASS_ESTFILTER):
        estFilterChs = mscl.MipChannels()
        estFilterChs.append(mscl.MipChannel(mscl.MipTypes.CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS, mscl.SampleRate.Hertz(100)))

        # Apply to the node
        node.setActiveChannelFields(mscl.MipTypes.CLASS_ESTFILTER, estFilterChs)

    # If the node supports GNSS
    if node.features().supportsCategory(mscl.MipTypes.CLASS_GNSS):
        gnssChs = mscl.MipChannels()
        gnssChs.append(mscl.MipChannel(mscl.MipTypes.CH_FIELD_GNSS_LLH_POSITION, mscl.SampleRate.Hertz(1)))

        # Apply to the node
        node.setActiveChannelFields(mscl.MipTypes.CLASS_GNSS, gnssChs)

    if node.features().supportsCommand(mscl.MipTypes.CMD_EF_ALTITUDE_AID_CTRL):
        node.setAltitudeAid(False)

    if node.features().supportsCommand(mscl.MipTypes.CMD_EF_ANTENNA_OFFSET):
        offset = mscl.PositionOffset(0.0, 0.0, 0.0)
        node.setAntennaOffset(offset)
    elif node.features().supportsCommand(mscl.MipTypes.CMD_EF_MULTI_ANTENNA_OFFSET):
        offset = mscl.PositionOffset(0.0, 0.0, 0.0)

        for gnssReceiverInfo in node.features().gnssReceiverInfo():
            node.setMultiAntennaOffset(gnssReceiverInfo.id, offset)

    if node.features().supportsCommand(mscl.MipTypes.CMD_EF_PITCH_ROLL_AID_CTRL):
        node.setPitchRollAid(True)

def startSampling(node):
    # Each class/category is separated into its own command.
    # You can enable them individually if, say, you only want the Estimation Filter channels to be streamed

    if node.features().supportsCategory(mscl.MipTypes.CLASS_AHRS_IMU):
        node.enableDataStream(mscl.MipTypes.CLASS_AHRS_IMU)

    if node.features().supportsCategory(mscl.MipTypes.CLASS_ESTFILTER):
        node.enableDataStream(mscl.MipTypes.CLASS_ESTFILTER)

    if node.features().supportsCategory(mscl.MipTypes.CLASS_GNSS):
        node.enableDataStream(mscl.MipTypes.CLASS_GNSS)

# Example: Parse Data
#  Shows how to parse incoming data from an Inertial Device.
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

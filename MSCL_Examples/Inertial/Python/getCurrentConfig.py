# Updated: 2/21/2024

import sys

# TODO: change this path to match your setup
# import the mscl library.
arch = sys.maxsize > 2**32 and "x64" or "x32"
sys.path.append("../../../Output/Python{sys.version_info.major}.{sys.version_info.minor}/{arch}/Release")

import mscl

# TODO: change these constants to match your setup
COM_PORT = "COM4"

try:
    #create a Serial Connection with the specified COM Port, default baud rate of 921600
    connection = mscl.Connection.Serial(COM_PORT)

    #create an InertialNode with the connection
    node = mscl.InertialNode(connection)

    #many other settings are available than shown below
    #reference the documentation for the full list of commands

    #if the node supports AHRS/IMU
    if node.features().supportsCategory(mscl.MipTypes.CLASS_AHRS_IMU):
        #get a list of the AHRS/IMU channels currently active on the Node
        ahrsImuActiveChs = node.getActiveChannelFields(mscl.MipTypes.CLASS_AHRS_IMU)

        print("AHRS/IMU Channels")
        print("-----------------")
        for ch in ahrsImuActiveChs:
            print("Channel Field:", ch.channelField())
            print("Sample Rate:", ch.sampleRate().prettyStr())

    #if the node supports Estimation Filter
    if node.features().supportsCategory(mscl.MipTypes.CLASS_ESTFILTER):
        #get a list of the Estimation Filter channels currently active on the Node
        estFilterActiveChs = node.getActiveChannelFields(mscl.MipTypes.CLASS_ESTFILTER)

        print("Estimation Filter Channels")
        print("--------------------------")
        for ch in estFilterActiveChs:
            print("Channel Field:", ch.channelField())
            print("Sample Rate:", ch.sampleRate().prettyStr())

    #if the node supports GNSS
    if node.features().supportsCategory(mscl.MipTypes.CLASS_GNSS):
        #get a list of the GNSS channels currently active on the Node
        gnssActiveChs = node.getActiveChannelFields(mscl.MipTypes.CLASS_GNSS)

        print("GNSS Channels")
        print("--------------------------")
        for ch in gnssActiveChs:
            print("Channel Field:", ch.channelField())
            print("Sample Rate:", ch.sampleRate().prettyStr())

    print("Altitude Aiding enabled?:", node.getAltitudeAid())

    offset = node.getAntennaOffset()
    print("Antenna Offset: x=", offset.x(), " y=", offset.y(), " z=", offset.z())

    print("Pitch/Roll Aiding enabled?:", node.getPitchRollAid())

except mscl.Error as e:
    print("Error:", e)

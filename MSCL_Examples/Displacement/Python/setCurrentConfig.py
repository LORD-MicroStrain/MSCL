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
    #create a Serial Connection with the specified COM Port
    connection = mscl.Connection.Serial(COM_PORT, 115200)

    #create a DisplacementNode with the connection
    node = mscl.DisplacementNode(connection)

    #seed the device time with the current PC time
    #Note: you can pass your own time to this function as a
    #      parameter in nanoseconds since unix epoch
    node.setDeviceTime()

except mscl.Error as e:
    print("Error:", e)

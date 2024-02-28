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
    node = mscl.DisplacmentNode(connection)

    cals = node.getAnalogToDisplacementCal();
    print("Analog to Displacement Cal: Slope:",cals.slope(), "Offset:", cals.offset())

    print("Output Data Rate:", node.getDisplacementOutputDataRate().prettyStr())

except mscl.Error as e:
    print("Error:", e)

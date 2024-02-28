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

    print(node.modelName())
    print(node.modelNumber())
    print(node.serialNumber())
    print(node.firmwareVersion())

    node.setToIdle()

    #Note: you can also disable the datastream for each class/category
    #      separately if desired, by using the enableDataStream command shown in
    #      the startSampling example, but passing a second parameter of 'false'

except mscl.Error as e:
    print("Error:", e)

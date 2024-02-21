# MSCL Example: NodePing
#   This examples shows how to open a connection with a Base Station,
#   ping a Node, and get the result and its information
#
# Updated: 2/21/2024

import sys

# TODO: change this path to match your setup
# import the mscl library.
arch = sys.maxsize > 2**32 and "x64" or "x32"
sys.path.append("../../../Output/Python{sys.version_info.major}.{sys.version_info.minor}/{arch}/Release")

import mscl

# TODO: change these constants to match your setup
COM_PORT = "COM3"
NODE_ADDRESS = 65364

try:
    # create a Serial Connection with the specified COM Port, default baud rate of 921600
    connection = mscl.Connection.Serial(COM_PORT)

    # create a BaseStation with the connection
    baseStation = mscl.BaseStation(connection)

    # create a WirelessNode with the BaseStation we created
    node = mscl.WirelessNode(NODE_ADDRESS, baseStation)

    print("Attempting to ping the Node...")

    # ping the Node
    response = node.ping()

    # if the ping response was a success
    if response.success():
        # get some details from the response
        print("Successfully pinged Node", NODE_ADDRESS)
        print("Base Station RSSI:", response.baseRssi())
        print("Node RSSI:", response.nodeRssi())
    else:
        print("Failed to ping Node", NODE_ADDRESS)

except Exception as e:
    print("Error:", e    )

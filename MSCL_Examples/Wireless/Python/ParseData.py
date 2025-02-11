# MSCL Example: ParseData
#   This example shows how to parse incoming data from a Wireless Node.
#   This example does not start a Node sampling. To receive data, a Node
#   must be put into a sampling mode (Sync Sampling, Low Duty Cycle, etc.)
#
# Updated: 12/18/2024

import sys
import os

# TODO: change this path to match your setup
# import the mscl library.
arch = sys.maxsize > 2 ** 32 and "x64" or "x32"
sys.path.append(os.path.abspath("{}/../../../Output/Python/{}.{}/{}/Release".format(os.path.dirname(os.path.realpath(__file__)),
    sys.version_info.major, sys.version_info.minor, arch)))

import mscl

# TODO: change these constants to match your setup
COM_PORT = "COM3"

try:
    # create a Serial Connection with the specified COM Port, default baud rate of 921600
    connection = mscl.Connection.Serial(COM_PORT)

    # create a BaseStation with the connection
    baseStation = mscl.BaseStation(connection)

    # endless loop of reading in data
    while True:

        # get all the data sweeps that have been collected by the BaseStation, with a timeout of 500 milliseconds
        sweeps = baseStation.getData(500)

        for sweep in sweeps:
            # print out information about the sweep
            print("Packet Received",)
            print("Node", sweep.nodeAddress(),)
            print("Timestamp", sweep.timestamp(),)
            print("Tick", sweep.tick(),)
            print("Sample Rate", sweep.sampleRate().prettyStr(),)
            print("Base RSSI: ", sweep.baseRssi(),)
            print("Node RSSI: ", sweep.nodeRssi(),)

            print("DATA: ",)
            # iterate over each point in the sweep
            for dataPoint in sweep.data():

                #print out the channel data
                #Note: The as_string() function is being used here for simplicity.
                #      Other methods (ie. as_float, as_uint16, as_Vector) are also available.
                #      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                print(dataPoint.channelName(), ":", dataPoint.as_string(),)

            print("")


except Exception as e:
    print("Error:", e)

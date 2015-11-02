# MSCL Example: ParseData
#   This example shows how to parse incoming data from a Wireless Node.
#   This example does not start a Node sampling. To receive data, a Node
#   must be put into a sampling mode (Sync Sampling, Low Duty Cycle, etc.)
#
# Updated: 11/02/2015

# import the mscl library
import sys
sys.path.append("../../dependencies/Python")
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

        # get all of the data sweeps that have been collected by the BaseStation, with a timeout of 500 milliseconds
        sweeps = baseStation.getData(500)

        for sweep in sweeps:
            # print out information about the sweep
            print "Packet Received",
            print "Node", sweep.nodeAddress(),
            print "Timestamp", sweep.timestamp(),
            print "Tick", sweep.tick(),
            print "Sample Rate", sweep.sampleRate().prettyStr(),
            print "Base RSSI: ", sweep.baseRssi(),
            print "Node RSSI: ", sweep.nodeRssi(),

            print "DATA: ",
            # iterate over each point in the sweep
            for dataPoint in sweep.data():
                # just printing this out as a string. Other methods (ie. as_float, as_uint16) are also available.
                print dataPoint.channelName(), ":", dataPoint.as_string(),

            print ""
            

except Exception, e:
    print "Error:", e

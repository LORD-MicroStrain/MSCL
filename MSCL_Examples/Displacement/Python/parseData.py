#MSCL Example: ParseData
#   This example shows how to parse incoming data from a Displacement Device.
#   This example does not start a Node sampling. To receive data, a Node
#   must be put into a sampling mode.

#import the mscl library
import sys
sys.path.append("../../dependencies/Python")
import mscl

#TODO: change these constants to match your setup
COM_PORT = "COM4"

try:
    #create a Serial Connection with the specified COM Port
    connection = mscl.Connection.Serial(COM_PORT, 115200)

    #create a DisplacementNode with the connection
    node = mscl.DisplacementNode(connection)

    #endless loop of reading in data
    while (True):        
        #get all the data packets from the node, with a timeout of 500 milliseconds
        packets = node.getDataPackets(500)
        
        for packet in packets:

            #print out the data
            print "Packet Received: ",

            #iterate over all the data points in the packet
            for dataPoint in packet.data():

                #print out the channel data
                #Note: The as_string() function is being used here for simplicity. 
                #      Other methods (ie. as_float, as_uint16, as_Vector) are also available.
                #      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                print dataPoint.channelName() + ":", dataPoint.as_string() + " ",

            print ""
    
except mscl.Error, e:
    print "Error:", e

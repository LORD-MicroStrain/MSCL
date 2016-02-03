#MSCL Example: ParseData
#   This example shows how to parse incoming data from an Inertial Device.
#   This example does not start a Node sampling. To receive data, a Node
#   must be put into a sampling mode.
#
#Updated: 01/18/2016

#import the mscl library
import sys
sys.path.append("../../dependencies/Python")
import mscl

#TODO: change these constants to match your setup
COM_PORT = "COM15"

try:
    #create a Serial Connection with the specified COM Port, default baud rate of 921600
    connection = mscl.Connection.Serial(COM_PORT)

    #create an InertialNode with the connection
    node = mscl.InertialNode(connection)

    #endless loop of reading in data
    while (True):        
        #get all the data packets from the node, with a timeout of 500 milliseconds
        packets = node.getDataPackets(500)
        
        for packet in packets:

            #print out the data
            print "Packet Received: ",

            #iterate over all the data points in the packet
            for dataPoint in packet.data():
                print dataPoint,
                print ": ",
                print dataPoint.as_string() + " ",  #Just printing this out as a string. Other methods (ie. as_float, as_uint16, as_Vector) are also available.
                
                #if the dataPoint is invalid
                if(dataPoint.valid() == False):
                    print "[Invalid] ",

            print ""
    
except mscl.Error, e:
    print "Error:", e

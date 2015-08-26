# MSCL Example: ArmedDatalogging
#   This example shows how to create and start an Armed Datalogging sampling network.
#
# Updated: 02/25/2015

# import the mscl library
import sys
sys.path.append("../../dependencies/Python")
import mscl

# TODO: change these constants to match your setup
COM_PORT = "COM3"
NODE_ADDRESS = 31849

try:
    # create a SerialConnection with the specified COM Port, default baud rate of 921600
    connection = mscl.Connection.Serial(COM_PORT)

    # create a BaseStation with the connection
    baseStation = mscl.BaseStation(connection)
    
    # create a WirelessNode with the BaseStation we created
    node = mscl.WirelessNode(NODE_ADDRESS, baseStation)

    # create a ArmedDataloggingNetwork object, giving it the BaseStation that
    # will be the master BaseStation for the network
    network = mscl.ArmedDataloggingNetwork(baseStation)

    # add a WirelessNode to the network
    #    Note: The Node must already be configured for Armed Datalogging before adding
    #    to the network, or else Error_InvalidConfig will be thrown.
    # TODO: Repeat this for all WirelessNodes that you want in the network
    print "Adding node to the network...",
    network.addNode(node, "This is an optional <50-char message.")
    print "Done."

    # start all the nodes in the network sampling.
    print "Starting the network...",
    network.startSampling()
    print "Done."

except Exception, e:
    print "Error:", e    

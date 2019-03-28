# MSCL Example: SynchronizedSampling
#   This example shows how to create and start a Synchronized Sampling network.

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

    # create a SyncSamplingNetwork object, giving it the BaseStation that will be the master BaseStation for the network
    network = mscl.SyncSamplingNetwork(baseStation)

    # add a WirelessNode to the network
    #   Note: The Node must already be configured for Sync Sampling before
    #   adding to the network, or else Error_InvalidConfig will be thrown.
    # TODO: Repeat this for all WirelessNodes that you want in the network
    print "Adding node to the network...",
    network.addNode(node)
    print "Done."

    # can get information about the network
    print "Network info: "
    print "Network OK: ", network.ok()
    print "Percent of Bandwidth: ", network.percentBandwidth()
    print "Lossless Enabled: ", network.lossless()

    # apply the network configuration to every node in the network
    print "Applying network configuration",
    network.applyConfiguration()
    print "Done."

    # start all the nodes in the network sampling. The master BaseStation's beacon will be enabled with the system time.
    #   Note: if you wish to provide your own start time (not use the system time),
    #   pass a mscl::Timestamp object as a second parameter to this function.
    #   Note: if you do not want to enable a beacon at this time, use the startSampling
    #   noBeacon() function. (A beacon is required for the nodes to actually start sending data).
    print "Starting the network...",
    network.startSampling()
    print "Done."

    # =======================================================================================
    # Many other functions are available for the SyncSamplingNetwork:
    #
    # network.lossless()			//enable or disable "lossless" mode for the network (default of enabled).
    # network.ok()					//check whether or not the network is "OK" meaning all nodes fit in the network and have communicated successfully.
    # network.percentBandwidth()	//get the percent of bandwidth for the entire network.
    # network.refresh()				//refreshes the entire network. Should be called any time a change is made to the node after it has been added to the network.
    # network.removeNode()			//remove a node from the network.
    # network.getNodeNetworkInfo()	//get network information for an individual node in the network (TDMA address, percent bandwidth, etc.)
    # =======================================================================================

except Exception, e:
    print "Error:", e    

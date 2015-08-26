# MSCL Example: StopNode
#   This example shows how to "stop" a Wireless Node, taking the Node
#   out of its sampling or sleeping mode and putting it into its
#   idle state so that it can be communicated with.
#   Note: Stopping a Node may take up to a maximum of 2 minutes.
#
# Updated: 02/26/2015

# import the mscl library
import sys
sys.path.append("../../dependencies/Python")
import mscl

# TODO: change these constants to match your setup
COM_PORT = "COM3"
NODE_ADDRESS = 31849

try:
    # create a Serial Connection with the specified COM Port, default baud rate of 921600
    connection = mscl.Connection.Serial(COM_PORT)

    # create a BaseStation with the connection
    baseStation = mscl.BaseStation(connection)
    
    # create a WirelessNode with the BaseStation we created
    node = mscl.WirelessNode(NODE_ADDRESS, baseStation)

    # call the stop function and get the resulting StopNodeStatus object
    stopStatus = node.stop()

    print "Stopping Node",

    # using the StopNodeStatus object, check if the Stop Node operation is complete.
    #   Note: we are specifying a timeout of 300 millisecond here which is the maximum
    #       amount of time that the complete function will block if the Stop Node
    #       operation has not finished. Leaving this blank defaults to a timeout of 10ms.
    while not stopStatus.complete(300):
        # Note: the Stop Node operation can be canceled by calling stopStatus.cancel()
        print ".",

    # at this point, the Stop Node operation has completed

    # check the result of the Stop Node operation
    result = stopStatus.result()
    if result == mscl.StopNodeStatus.stopNodeResult_success:
        # Stop Node completed successfully
        print "Successfully stopped the Node!"
    elif result == mscl.StopNodeStatus.stopNodeResult_canceled:
        # Stop Node has been canceled by the user
        print "Stop Node was canceled!"
    else:
        # Failed to perform the Stop Node operation
        print "Stop Node has failed!"

except Exception, e:
    print "Error:", e    

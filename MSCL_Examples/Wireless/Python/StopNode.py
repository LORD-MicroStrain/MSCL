# MSCL Example: StopNode
#   This example shows how to "stop" a Wireless Node, taking the Node
#   out of its sampling or sleeping mode and putting it into its
#   idle state so that it can be communicated with.
#   Note: Stopping a Node may take up to a maximum of 2 minutes.
#
# Updated: 11/02/2015

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

    # call the set to idle function and get the resulting SetToIdleStatus object
    status = node.setToIdle()

    print "Setting Node to Idle",

    # using the SetToIdleStatus object, check if the Set to Idle operation is complete.
    # Note: we are specifying a timeout of 300 milliseconds here which is the maximum
    #   amount of time that the complete function will block if the Set to Idle
    #   operation has not finished. Leaving this blank defaults to a timeout of 10ms.
    while not status.complete(300):
        # Note: the Set to Idle operation can be canceled by calling status.cancel()
        print ".",

    # at this point, the Set to Idle operation has completed

    # check the result of the Set to Idle operation
    result = status.result()
    if result == mscl.SetToIdleStatus.setToIdleResult_success:
        # completed successfully
        print "Successfully set to idle!"
    elif result == mscl.SetToIdleStatus.setToIdleResult_canceled:
        # canceled by the user
        print "Set to Idle was canceled!"
    else:
        # Failed to perform the operation
        print "Set to Idle has failed!"

except Exception, e:
    print "Error:", e    

# MSCL Example: ConfigureNode
#   This example shows how to get and set the configuration options for a Wireless Node.
#   Warning: Running this example will change the configuration on the Wireless Node.
#
# Updated: 04/01/2015

# import the mscl library
import sys
sys.path.append("../../dependencies/Python")
import mscl

# TODO: change these constants to match your setup
COM_PORT = "COM3"
NODE_ADDRESS = 31849


# Function: getCurrentConfig
#   This function demonstrates how to obtain the current configuration
#   settings of a Wireless Node with MSCL.
#
#   Note:	More settings are available than are demoed here.
#           Reference the documentation for the full list of functions.
def getCurrentConfig(node):
    print "Current Configuration Settings"

    # read some of the current configuration settings on the node
    print "# of Triggers:", node.getNumDatalogSessions()
    print "User Inactivity Timeout:", node.getInactivityTimeout(), "seconds"
    print "Total active channels:", node.getActiveChannels().count()
    print "# of sweeps:", node.getNumSweeps()

    # get a list of the supported channels
    supportedChannels = node.channels()

    # loop through all of the channels
    for channel in supportedChannels:
        # print out some information about the channels
        print "Channel #:", channel
        print "Slope:", supportedChannels[channel].getLinearEquation().slope()
        print "Offset:", supportedChannels[channel].getLinearEquation().offset()
    

# Function: setCurrentConfig
#   This function demonstrates how to change the configuration
#   settings of a Wireless Node with MSCL.
#
#   Note:	More settings are available than are demoed here.
#           Reference the documentation for the full list of functions.
def setCurrentConfig(node):
    print "Changing configuration settings."

    # create a WirelessNodeConfig which is used to set all node configuration options
    config = mscl.WirelessNodeConfig()

    # set the configuration options that we want to change
    config.bootMode(mscl.WirelessTypes.bootMode_normal)
    config.inactivityTimeout(7200)
    config.samplingMode(mscl.WirelessTypes.samplingMode_sync)
    config.sampleRate(mscl.WirelessTypes.sampleRate_256Hz)
    config.unlimitedDuration(True)

    # attempt to verify the configuration with the Node we want to apply it to
    #   Note that this step is not required before applying, however the apply will throw an
    #   Error_InvalidNodeConfig exception if the config fails to verify.
    issues = mscl.ConfigIssues()
    if not node.verifyConfig(config, issues):
        print "Failed to verify the configuration. The following issues were found:"

        # print out all of the issues that were found
        for issue in issues:
            print issue.description()

        print "Configuration will not be applied."

    else:
        # apply the configuration to the Node
        #   Note that if this writes multiple options to the Node.
        #   If an Error_NodeCommunication exception is thrown, it is possible that
        #   some options were successfully applied, while others failed.
        #   It is recommended to keep calling applyConfig until no exception is thrown.
        node.applyConfig(config)

    print "Done."


try:
    # create a Serial Connection with the specified COM Port, default baud rate of 921600
    connection = mscl.Connection.Serial(COM_PORT)

    # create a BaseStation with the connection
    baseStation = mscl.BaseStation(connection)
    
    # create a WirelessNode with the BaseStation we created
    node = mscl.WirelessNode(NODE_ADDRESS, baseStation)

    # run the example showing how to retrieve the Node's current configuration
    getCurrentConfig(node)

    # run the example showing how to update/change the Node's current configuration
    setCurrentConfig(node)

except Exception, e:
    print "Error:", e    

# MSCL Example: ConfigureNode
#   This example shows how to get and set the configuration options for a Wireless Node.
#   Warning: Running this example will change the configuration on the Wireless Node.
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
NODE_ADDRESS = 65364


# Function: getCurrentConfig
#   This function demonstrates how to obtain the current configuration
#   settings of a Wireless Node with MSCL.
#
#   Note:	More settings are available than are demoed here.
#           Reference the documentation for the full list of functions.
def getCurrentConfig(node):
    print("Current Configuration Settings")

    # read some of the current configuration settings on the node
    print("# of Triggers:", node.getNumDatalogSessions())
    print("User Inactivity Timeout:", node.getInactivityTimeout(), "seconds")
    print("Total active channels:", node.getActiveChannels().count())
    print("# of sweeps:", node.getNumSweeps())

    # If a configuration function requires a ChannelMask parameter, this indicates that the
    # option may affect 1 or more channels on the Node. For instance, a hardware gain may
    # affect ch1 and ch2 with just 1 setting. If you know the mask for your Node, you can just provide
    # that mask when asking for the configuration. If you want to programatically determine
    # the mask for each setting, you can ask for the Node's ChannelGroups. See below.

    chGroups = node.features().channelGroups()

    # iterate over each channel group
    for group in chGroups:
        # get all of the settings for this group (ie. may contain linear equation and hardware gain).
        groupSettings = group.settings()

        # iterate over each setting for this group
        for setting in groupSettings:

            # if the group contains the linear equation setting
            if setting == mscl.WirelessTypes.chSetting_linearEquation:
                # we can now pass the channel mask (group.channels()) for this group to the node.getLinearEquation function.
                # Note: once this channel mask is known for a specific node (+ fw version), it should never change
                le = node.getLinearEquation(group.channels())

                print("Linear Equation for: ", group.name())
                print("Slope: ", le.slope())
                print("Offset: ", le.offset())


# Function: setCurrentConfig
#   This function demonstrates how to change the configuration
#   settings of a Wireless Node with MSCL.
#
#   Note:	More settings are available than are demoed here.
#           Reference the documentation for the full list of functions.
def setCurrentConfig(node):
    print("Changing configuration settings.")

    # create a WirelessNodeConfig which is used to set all node configuration options
    config = mscl.WirelessNodeConfig()

    # set the configuration options that we want to change
    config.defaultMode(mscl.WirelessTypes.defaultMode_idle)
    config.inactivityTimeout(7200)
    config.samplingMode(mscl.WirelessTypes.samplingMode_sync)
    config.sampleRate(mscl.WirelessTypes.sampleRate_256Hz)
    config.unlimitedDuration(True)

    # attempt to verify the configuration with the Node we want to apply it to
    #   Note that this step is not required before applying, however the apply will throw an
    #   Error_InvalidNodeConfig exception if the config fails to verify.
    issues = mscl.ConfigIssues()
    if not node.verifyConfig(config, issues):
        print("Failed to verify the configuration. The following issues were found:")

        # print out all of the issues that were found
        for issue in issues:
            print(issue.description())

        print("Configuration will not be applied.")

    else:
        # apply the configuration to the Node
        #   Note that if this writes multiple options to the Node.
        #   If an Error_NodeCommunication exception is thrown, it is possible that
        #   some options were successfully applied, while others failed.
        #   It is recommended to keep calling applyConfig until no exception is thrown.
        node.applyConfig(config)

    print("Done.")


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

except Exception as e:
    print("Error:", e)

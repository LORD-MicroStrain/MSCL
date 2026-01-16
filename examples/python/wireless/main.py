from __future__ import print_function
import sys
import os
import platform

# TODO: Make sure the script can find the MSCL library for this to work
# Import the MSCL library
import MSCL as mscl

################################################################################
# TODO: Modify any of these options according to your use case

# Toggle certain parts of the example on/off
PING_NODE             = True
SET_TO_IDLE           = True
GET_CURRENT_CONFIG    = True
SET_CURRENT_CONFIG    = True
START_SYNC_SAMPLING   = True
PARSE_DATA            = True
ENABLE_DISABLE_BEACON = True

# Update the communication port
if platform.system() == "Windows":
    COM_PORT = "COM1"
elif platform.system() == "Linux":
    COM_PORT = "/dev/tty/ACM0"

# Basestations use a baudrate of 3000000
BAUDRATE = 3000000

# Add more node addresses to this list as needed
NODE_ADDRESSES = [
    12345
]
################################################################################

def main():
    try:
        # Create a SerialConnection with the COM port and (optional) baudrate
        connection = mscl.Connection.Serial(COM_PORT, BAUDRATE)

        # Create a BaseStation with the SerialConnection
        baseStation = mscl.BaseStation(connection)

        # Due to the nature of wireless devices, it is possible to lose packets over the air.
        # MSCL has a built-in way of performing retries whenever an eeprom address is attempted to be read.
        # By default, this value is set to 0. You may wish to keep it at 0 and handle retries yourself depending on your application.
        baseStation.readWriteRetries(3)

        if START_SYNC_SAMPLING:
            networkNodes = []

        for NODE_ADDRESS in NODE_ADDRESSES:
            # Create a Wireless Node with the BaseStation
            node = mscl.WirelessNode(NODE_ADDRESS, baseStation)

            if START_SYNC_SAMPLING:
                networkNodes.append(node)

            node.readWriteRetries(3)

            if PING_NODE:
                # Example: Ping Node
                pingNode(node)

            if SET_TO_IDLE:
                # Example: Set to Idle
                setToIdle(node)

            if GET_CURRENT_CONFIG:
                # Example: Get Configuration
                getCurrentConfig(node)

            if SET_CURRENT_CONFIG:
                # Example: Set Configuration
                setCurrentConfig(node)       # Warning: this example changes settings on your Node

        if START_SYNC_SAMPLING:
            # Example: Start Sampling
            startSyncSampling(baseStation, networkNodes)

        if PARSE_DATA:
            # Example: Parse Data
            parseData(baseStation)

        if ENABLE_DISABLE_BEACON:
            # Example: Enable and Disable beacon
            enableDisableBeacon(baseStation)

    except mscl.Error as e:
        sys.stderr.write("Error: {0}\n".format(e.what()))

def pingNode(node):
    response = node.ping()

    if response.success():
        # Get some details from the response
        print("Successfully pinged Node {0}".format(node.nodeAddress()))
        print("Base Station RSSI: {0}".format(response.baseRssi()))
        print("Node RSSI: {0}".format(response.nodeRssi()))

        # We can talk to the Node, so let's get some more info
        print("Node Information:")
        print("Model Number: {0}".format(node.model()))
        print("Serial: {0}".format(node.serial()))
        print("Firmware: {0}\n".format(node.firmwareVersion()))
    else:
        # Note: To communicate with a Wireless Node, all the following must be true:
        #  - The Node is powered on, and within range of the BaseStation
        #  - The Node is on the same frequency as the BaseStation
        #  - The Node is in Idle Mode (not sampling, and not sleeping)
        #  - The Node is on the same communication protocol as the BaseStation (LXRS vs LXRS+)
        print("Failed to ping Node {0}".format(node.nodeAddress()))

def setToIdle(node):
    # Call the set to idle function and get the resulting SetToIdleStatus object
    #  Note: This starts the set to idle node command, which is an ongoing operation. The SetToIdleStatus should be queried for progress.
    status = node.setToIdle()

    print("Setting Node to Idle")

    # Using the SetToIdleStatus object, check if the Set to Idle operation is complete.
    # Note: we are specifying a timeout of 300 milliseconds here, which is the maximum
    #      amount of time that the complete function will block if the Set to Idle
    #      operation has not finished. Leaving this blank defaults to a timeout of 10ms.
    while not status.complete(300):
        # Note: the Set to Idle operation can be canceled by calling status.cancel()
        print(".", end="")

    # At this point, the Set to Idle operation has completed

    # Check the result of the Set to Idle operation
    result = status.result()

    # Completed successfully
    if result == mscl.SetToIdleStatus.setToIdleResult_success:
        print("Successfully set to idle!")
    # Canceled by the user
    elif result == mscl.SetToIdleStatus.setToIdleResult_canceled:
        # canceled by the user
        print("Set to Idle was canceled!")
    # Failed to perform the operation
    else:
        # Failed to perform the operation
        print("Set to Idle has failed!")

def getCurrentConfig(node):
    print("Current Configuration Settings")

    # Read some of the current configuration settings on the node
    print("# of Triggers: {0}".format(node.getNumDatalogSessions()))
    print("User Inactivity Timeout: {0} seconds".format(node.getInactivityTimeout()))
    print("Total active channels: {0}".format(node.getActiveChannels().count()))
    print("# of sweeps: {0}".format(node.getNumSweeps()))

    # If a configuration function requires a ChannelMask parameter, this indicates that the
    # option may affect 1 or more channels on the Node. For instance, a hardware gain may
    # affect ch1 and ch2 with just 1 setting. If you know the mask for your Node, you can provide
    # that mask when asking for the configuration. If you want to programmatically determine
    # the mask for each setting, you can ask for the Node's ChannelGroups. See below.

    # Get the ChannelGroups that the node supports
    chGroups = node.features().channelGroups()

    # Iterate over each channel group
    for group in chGroups:
        # Get all the settings for this group (i.e., may contain linear equation and hardware gain).
        groupSettings = group.settings()

        # Iterate over each setting for this group
        for setting in groupSettings:
            # If the group contains the linear equation setting
            if setting == mscl.WirelessTypes.chSetting_linearEquation:
                # We can now pass the channel mask (group.channels()) for this group to the node.getLinearEquation function.
                # Note: once this channel mask is known for a specific node (+ fw version), it should never change
                le = node.getLinearEquation(group.channels())

                print("Linear Equation for: {0}".format(group.name()))
                print("Slope: {0:06.3f}".format(le.slope()))
                print("Offset: {0:06.3f}".format(le.offset()))

def setCurrentConfig(node):
    # Just changing a small subset of settings for this example.
    # More settings are available. Please reference the documentation for the full list of functions.

    print("\nChanging configuration settings...", end="")

    # Create a WirelessNodeConfig which is used to set all node configuration options
    config = mscl.WirelessNodeConfig()

    # Set the configuration options that we want to change
    config.defaultMode(mscl.WirelessTypes.defaultMode_idle)
    config.inactivityTimeout(7200)
    config.samplingMode(mscl.WirelessTypes.samplingMode_sync)
    config.sampleRate(mscl.WirelessTypes.sampleRate_256Hz)
    config.unlimitedDuration(True)

    # Attempt to verify the configuration with the Node we want to apply it to
    #  Note that this step is not required before applying; however, the apply will throw an
    #  Error_InvalidNodeConfig exception if the config fails to verify.
    issues = mscl.ConfigIssues()

    if not node.verifyConfig(config, issues):
        print("\nFailed to verify the configuration. The following issues were found:")

        # Print out all the issues that were found
        for issue in issues:
            print(issue.description())

        print("Configuration will not be applied.")
    else:
        # Apply the configuration to the Node
        #  Note that this writes multiple options to the Node.
        #  If an Error_NodeCommunication exception is thrown, it is possible that
        #  some options were successfully applied, while others failed.
        #  It is recommended to keep calling applyConfig until no exception is thrown.
        node.applyConfig(config)

    print("Done.")

def startSampling(baseStation, nodes):
    # Create a SyncSamplingNetwork object, giving it the BaseStation that will be the master BaseStation for the network.
    network = mscl.SyncSamplingNetwork(baseStation)

    # Add the WirelessNodes to the network.
    # Note: The Nodes must already be configured for Sync Sampling before adding to the network, or else Error_InvalidNodeConfig will be thrown.
    for node in nodes:
        print("Adding node {0} to the network...".format(node.nodeAddress()), end="")
        network.addNode(node)
        print("Done.")

    # Can get information about the network
    print("Network info:")
    print("Network OK: {0}".format("TRUE" if network.ok() else "FALSE"))
    print("Percent of Bandwidth: {0:04.02f}%", network.percentBandwidth())
    print("Lossless Enabled: {0}".format("TRUE" if network.lossless() else "FALSE"))

    # Apply the network configuration to every node in the network
    print("Applying network configuration...", end="")
    network.applyConfiguration()
    print("Done.")

    # Start all the nodes in the network sampling. The master BaseStation's beacon will be enabled with the system time.
    #  Note: if you wish to provide your own start time (not use the system time), pass a mscl::Timestamp object as a second parameter to this function.
    #  Note: if you do not want to enable a beacon at this time, use the startSampling_noBeacon() function. (The nodes will wait until they hear a beacon to start sampling).
    print("Starting the network...", end="")
    network.startSampling()
    print("Done.")

    #=======================================================================================
    # Many other functions are available for the SyncSamplingNetwork:
    #
    # network.lossless()                        # enable or disable "lossless" mode for the network (default of enabled).
    # network.ok()                              # check whether the network is "OK" meaning all nodes fit in the network and have communicated successfully.
    # network.percentBandwidth()                # get the percentage of bandwidth for the entire network.
    # network.refresh()                         # refreshes the entire network. Should be called any time a change is made to the node after it has been added to the network.
    # network.removeNode()                      # remove a node from the network.
    # network.getNodeNetworkInfo(nodeAddress)   # get network information for an individual node in the network (TDMA address, percent bandwidth, etc.)
    #=======================================================================================

def parseData(baseStation):
    # Endless loop of reading in data
    while True:
        # Loop through all the data sweeps that have been collected by the BaseStation, with a timeout of 10 milliseconds
        for sweep in node.getData(10):
            # Print out information about the sweep
            print("Packet Received: ", end="")
            print("Node {0}".format(sweep.nodeAddress()), end="")
            print("Timestamp: {0}".format(sweep.timestamp()), end="")
            print("Tick: {0}".format(sweep.tick()), end="")
            print("Sample Rate: {0}".format(sweep.sampleRate().prettyStr()), end="")
            print("Base RSSI: {0}".format(sweep.baseRssi()), end="")
            print("Node RSSI: {0}".format(sweep.nodeRssi()), end="")

            print("DATA: ", end="")

            # Iterate over each point in the sweep
            for dataPoint in sweep.data():
                # Print out the channel name
                print("{0}: ".format(dataPoint.channelName()), end="")

                # Print out the channel data
                # Note: The as_string() function is being used here for simplicity.
                #      Other methods (i.e., as_float, as_uint16, as_Vector) are also available.
                #      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                print("{0} ".format(dataPoint.as_string()), end="")

            print("")

def enableDisableBeacon(baseStation):
    # Make sure we can ping the base station
    if not baseStation.ping():
        print("Failed to ping the Base Station")

    if baseStation.features().supportsBeaconStatus():
        status = baseStation.beaconStatus()
        print("Beacon current status: Enabled?: {0}".format("TRUE" if status.enabled() else "FALSE"), end="")
        print(" Time: {0}".format(status.timestamp()))

    print("Attempting to enable the beacon...")

    # Enable the beacon on the Base Station using the PC time
    beaconTime = baseStation.enableBeacon()

    # If we got here, no exception was thrown, so enableBeacon was successful
    print("Successfully enabled the beacon on the Base Station")
    print("Beacon's initial Timestamp: {0}".format(beaconTime))

    print("Beacon is active")
    print("Sleeping for 3 seconds...")
    sleep(3)

    # Disable the beacon on the Base Station
    baseStation.disableBeacon()

    # If we got here, no exception was thrown, so disableBeacon was successful
    print("Successfully disabled the beacon on the Base Station")

# Run the example
if __name__ == "__main__":
    main()

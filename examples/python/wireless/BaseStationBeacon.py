# MSCL Example: BaseStationBeacon
#   This example shows how to Enable and Disable the
#   beacon (used for Synchronized Sampling) on a base station
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

from time import sleep

# TODO: change these constants to match your setup
COM_PORT = "COM3"

try:
    # create a Serial Connection with the specified COM Port, default baud rate of 921600
    connection = mscl.Connection.Serial(COM_PORT)

    # create a BaseStation with the connection
    baseStation = mscl.BaseStation(connection)

    # make sure we can ping the base station
    if not baseStation.ping():
        print("Failed to ping the Base Station")

    if baseStation.features().supportsBeaconStatus():
        status = baseStation.beaconStatus()
        print("Beacon current status: Enabled?", status.enabled(), "Time:", status.timestamp())

    print("Attempting to enable the beacon...")

    # enable the beacon on the Base Station using the PC time
    startTime = baseStation.enableBeacon()

    # if we got here, no exception was thrown, so enableBeacon was successful
    print("Successfully enabled the beacon on the Base Station")
    print("Beacon's initial Timestamp:", startTime)

    print("Beacon is active")
    print("Sleeping for 3 seconds...")
    sleep(3)

    # disable the beacon on the Base Station
    baseStation.disableBeacon()

    # if we got here, no exception was thrown, so disableBeacon was successful
    print("Successfully disabled the beacon on the Base Station")

except Exception as e:
    print("Error:", e)

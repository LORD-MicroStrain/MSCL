# MSCL Example: BaseStationBeacon
#   This example shows how to Enable and Disable the 
#   beacon (used for Synchronized Sampling) on a base station
#
# Updated: 02/25/2015

from time import sleep

# import the mscl library
import sys
sys.path.append("../../dependencies/Python")
import mscl

# TODO: change these constants to match your setup
COM_PORT = "COM3"

try:
    # create a Serial Connection with the specified COM Port, default baud rate of 921600
    connection = mscl.Connection.Serial(COM_PORT)

    # create a BaseStation with the connection
    baseStation = mscl.BaseStation(connection)

    # make sure we can ping the base station
    if not baseStation.ping():
        print "Failed to ping the Base Station"

    print "Attempting to enable the beacon..."

    # enable the beacon on the Base Station using the PC time
    startTime = baseStation.enableBeacon()

    # if we got here, no exception was thrown, so enableBeacon was successful
    print "Successfully enabled the beacon on the Base Station"
    print "Beacon's initial Timestamp:", startTime

    print "Beacon is active"
    print "Sleeping for 3 seconds..."
    sleep(3)

    # disable the beacon on the Base Station
    baseStation.disableBeacon()

    # if we got here, no exception was thrown, so disableBeacon was successful
    print "Successfully disabled the beacon on the Base Station"

except Exception, e:
    print "Error:", e

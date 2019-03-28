#import the mscl library
import sys
sys.path.append("../../dependencies/Python")
import mscl

#TODO: change these constants to match your setup
COM_PORT = "COM4"

try:
    #create a Serial Connection with the specified COM Port
    connection = mscl.Connection.Serial(COM_PORT, 115200)

    #create a DisplacementNode with the connection
    node = mscl.DisplacementNode(connection)

    #seed the device time with the current PC time
    #Note: you can pass your own time to this function as a
    #      parameter in nanoseconds since unix epoch
    node.setDeviceTime()

except mscl.Error, e:
    print "Error:", e

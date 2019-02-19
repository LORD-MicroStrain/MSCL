#import the mscl library
import sys
sys.path.append("../../dependencies/Python")
import mscl

#TODO: change these constants to match your setup
COM_PORT = "COM4"

try:
    #create a Serial Connection with the specified COM Port
    connection = mscl.Connection.Serial(COM_PORT, 115200)

    #create an DisplacementNode with the connection
    node = mscl.DisplacementNode(connection)

    node.setToIdle()

except mscl.Error, e:
    print "Error:", e

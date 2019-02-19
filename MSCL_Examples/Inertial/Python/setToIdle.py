#import the mscl library
import sys
sys.path.append("../../dependencies/Python")
import mscl

#TODO: change these constants to match your setup
COM_PORT = "COM4"

try:
    #create a Serial Connection with the specified COM Port, default baud rate of 921600
    connection = mscl.Connection.Serial(COM_PORT)

    #create an InertialNode with the connection
    node = mscl.InertialNode(connection)

    node.setToIdle()

    #Note: you can also disable the datastream for each class/category
    #      seperately if desired, by using the enableDataStream command shown in
    #      the startSampling example, but passing a second parameter of 'false'

except mscl.Error, e:
    print "Error:", e
